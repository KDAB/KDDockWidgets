/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "SegmentedIndicators_p.h"
#include "../DropArea_p.h"
#include "Config.h"

#include <QPainter>
#include <QPainterPath>

using namespace KDDockWidgets;

int SegmentedIndicators::s_segmentGirth = 50;
int SegmentedIndicators::s_segmentPenWidth = 4;
qreal SegmentedIndicators::s_draggedWindowOpacity = 0.7;
QColor SegmentedIndicators::s_segmentPenColor = Qt::black;
QColor SegmentedIndicators::s_segmentBrushColor = QColor(0xbb, 0xd5, 0xee, /*alpha=*/200);
QColor SegmentedIndicators::s_hoveredSegmentBrushColor = QColor(0x3574c5);
int SegmentedIndicators::s_centralIndicatorMaxWidth = 300;
int SegmentedIndicators::s_centralIndicatorMaxHeight = 160;


SegmentedIndicators::SegmentedIndicators(DropArea *dropArea)
    : DropIndicatorOverlayInterface(dropArea)
{
    // If the app didn't choose opacity then we choose a suitable default value.
    // ClassicIndicators works fine with an opaque dragged window because the indicators have higher Z,
    // However for SegmentedIndicators the indicators are in the main window, so lower Z. Make the
    // dragged window translucent a bit, so we can see the indicators
    const bool userChoseOpacity = !qIsNaN(Config::self().draggedWindowOpacity());
    if (!userChoseOpacity)
        Config::self().setDraggedWindowOpacity(s_draggedWindowOpacity);
}

SegmentedIndicators::~SegmentedIndicators()
{
}

DropLocation SegmentedIndicators::hover_impl(QPoint pt)
{
    m_hoveredPt = mapFromGlobal(pt);
    updateSegments();
    setCurrentDropLocation(dropLocationForPos(m_hoveredPt));

    return currentDropLocation();
}

DropLocation SegmentedIndicators::dropLocationForPos(QPoint pos) const
{
    for (auto it = m_segments.cbegin(), end = m_segments.cend(); it != end; ++it) {
        if (it.value().containsPoint(pos, Qt::OddEvenFill)) {
            return it.key();
        }
    }

    return DropLocation_None;
}

void SegmentedIndicators::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    drawSegments(&p);
}

QHash<DropLocation, QPolygon> SegmentedIndicators::segmentsForRect(QRect r, bool inner, bool useOffset) const
{
    const int halfPenWidth = s_segmentPenWidth / 2;

    const int l = s_segmentGirth;
    const int top = (r.y() == 0 && useOffset) ? l : r.y();
    const int left = (r.x() == 0 && useOffset) ? l : r.x();
    const int right = (rect().right() == r.right() && useOffset) ? r.right() - l : r.right();
    const int bottom = (rect().bottom() == r.bottom() && useOffset) ? r.bottom() - l : r.bottom();
    const QPoint topLeft = { left + halfPenWidth, top + halfPenWidth };
    const QPoint topRight = { right, top + halfPenWidth };
    const QPoint bottomLeft = { left + halfPenWidth, bottom };
    const QPoint bottomRight = { right, bottom };

    const QVector<QPoint> leftPoints = { topLeft, bottomLeft,
                                         QPoint(left, bottom) + QPoint(l, -l),
                                         topLeft + QPoint(l, l), topLeft };

    const QVector<QPoint> rightPoints = { topRight, bottomRight,
                                          bottomRight + QPoint(-l, -l),
                                          topRight + QPoint(-l, l) };

    const QVector<QPoint> topPoints = { topLeft, topRight,
                                        topRight + QPoint(-l, l),
                                        topLeft + QPoint(l, l) };

    const QVector<QPoint> bottomPoints = { bottomLeft, bottomRight,
                                           bottomRight + QPoint(-l, -l),
                                           bottomLeft + QPoint(l, -l) };

    if (inner) {
        QPolygon bounds = QVector<QPoint> { topLeft + QPoint(l, l),
                                            topRight + QPoint(-l, l),
                                            bottomRight + QPoint(-l, -l),
                                            bottomLeft + QPoint(l, -l) };
        const int maxWidth = bounds.boundingRect().width();
        const QPoint centerPos = bounds.boundingRect().center();

        // Build the center
        const int indicatorWidth = qMin(s_centralIndicatorMaxWidth, maxWidth - 100);
        const int indicatorHeight = qMin(s_centralIndicatorMaxHeight, int(indicatorWidth * 0.60));
        const int tabWidth = int(indicatorWidth * 0.267);
        const int tabHeight = int(indicatorHeight * 0.187);
        const int centerRectLeft = centerPos.x() - indicatorWidth / 2;
        const int centerRectRight = centerPos.x() + indicatorWidth / 2;
        const int centerRectBottom = centerPos.y() + indicatorHeight / 2;
        const int centerRectTop = centerPos.y() - indicatorHeight / 2;


        const auto center = QVector<QPoint> {
            { centerRectLeft, centerRectTop },
            { centerRectLeft + tabWidth, centerRectTop },
            { centerRectLeft + tabWidth, centerRectTop + tabHeight },
            { centerRectRight, centerRectTop + tabHeight },
            { centerRectRight, centerRectBottom },
            { centerRectLeft, centerRectBottom },
        };

        return {
            { DropLocation_Left, leftPoints },
            { DropLocation_Top, topPoints },
            { DropLocation_Right, rightPoints },
            { DropLocation_Bottom, bottomPoints },
            { DropLocation_Center, center }
        };
    } else {
        return {
            { DropLocation_OutterLeft, leftPoints },
            { DropLocation_OutterTop, topPoints },
            { DropLocation_OutterRight, rightPoints },
            { DropLocation_OutterBottom, bottomPoints }
        };
    }
}

void SegmentedIndicators::updateSegments()
{
    m_segments.clear();

    const auto outterSegments = segmentsForRect(rect(), /*inner=*/false);

    for (auto indicator : { DropLocation_OutterLeft, DropLocation_OutterRight, DropLocation_OutterTop, DropLocation_OutterBottom }) {
        if (dropIndicatorVisible(indicator)) {
            m_segments.insert(indicator, outterSegments.value(indicator));
        }
    }

    const bool hasOutter = !m_segments.isEmpty();
    const bool useOffset = hasOutter;
    const auto innerSegments = segmentsForRect(hoveredFrameRect(), /*inner=*/true, useOffset);

    for (auto indicator : { DropLocation_Left, DropLocation_Top, DropLocation_Right, DropLocation_Bottom, DropLocation_Center }) {
        if (dropIndicatorVisible(indicator)) {
            m_segments.insert(indicator, innerSegments.value(indicator));
        }
    }

    update();
}

void SegmentedIndicators::drawSegments(QPainter *p)
{
    for (DropLocation loc : { DropLocation_Left,
                              DropLocation_Top,
                              DropLocation_Right,
                              DropLocation_Bottom,
                              DropLocation_Center,
                              DropLocation_OutterLeft,
                              DropLocation_OutterTop,
                              DropLocation_OutterRight,
                              DropLocation_OutterBottom })
        drawSegment(p, m_segments.value(loc));
}

void SegmentedIndicators::drawSegment(QPainter *p, const QPolygon &segment)
{
    if (segment.isEmpty())
        return;

    QPen pen(s_segmentPenColor);
    pen.setWidth(s_segmentPenWidth);
    p->setPen(pen);
    QColor brush(s_segmentBrushColor);

    if (segment.containsPoint(m_hoveredPt, Qt::OddEvenFill))
        brush = s_hoveredSegmentBrushColor;

    p->setBrush(brush);
    p->drawPolygon(segment);
}

QPoint KDDockWidgets::SegmentedIndicators::posForIndicator(DropLocation) const
{
    /// Doesn't apply to segmented indicators, completely different concept
    return {};
}

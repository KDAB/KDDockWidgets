/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "SegmentedIndicatorsOverlay.h"
#include "kddockwidgets/core/indicators/SegmentedIndicators.h"

#include <QPainter>

using namespace KDDockWidgets;
using namespace KDDockWidgets::qtwidgets;
using namespace KDDockWidgets::Core;

QColor SegmentedIndicatorsOverlay::s_segmentPenColor = Qt::black;
QColor SegmentedIndicatorsOverlay::s_segmentBrushColor = QColor(0xbb, 0xd5, 0xee, /*alpha=*/200);
QColor SegmentedIndicatorsOverlay::s_hoveredSegmentBrushColor = QColor(0x3574c5);

SegmentedIndicatorsOverlay::SegmentedIndicatorsOverlay(
    Core::SegmentedIndicators *controller, QWidget *parent)
    : View<QWidget>(controller, ViewType::None, parent)
    , m_controller(controller)
{
}

SegmentedIndicatorsOverlay::~SegmentedIndicatorsOverlay()
{
}

void SegmentedIndicatorsOverlay::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    drawSegments(&p);
}


void SegmentedIndicatorsOverlay::drawSegments(QPainter *p)
{
    const QHash<DropLocation, QPolygon> segments = m_controller->segments();
    for (DropLocation loc :
         { DropLocation_Left, DropLocation_Top, DropLocation_Right, DropLocation_Bottom,
           DropLocation_Center, DropLocation_OutterLeft, DropLocation_OutterTop,
           DropLocation_OutterRight, DropLocation_OutterBottom })
        drawSegment(p, segments.value(loc));
}

void SegmentedIndicatorsOverlay::drawSegment(QPainter *p, const QPolygon &segment)
{
    if (segment.isEmpty())
        return;

    QPen pen(SegmentedIndicatorsOverlay::s_segmentPenColor);
    pen.setWidth(SegmentedIndicators::s_segmentPenWidth);
    p->setPen(pen);
    QColor brush(SegmentedIndicatorsOverlay::s_segmentBrushColor);

    if (segment.containsPoint(m_controller->hoveredPt(), Qt::OddEvenFill))
        brush = SegmentedIndicatorsOverlay::s_hoveredSegmentBrushColor;

    p->setBrush(brush);
    p->drawPolygon(segment);
}

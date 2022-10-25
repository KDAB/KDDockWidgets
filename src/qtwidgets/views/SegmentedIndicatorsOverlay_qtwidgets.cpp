/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "SegmentedIndicatorsOverlay_qtwidgets.h"
#include "kddockwidgets/controllers/indicators/SegmentedIndicators.h"

#include <QPainter>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;
using namespace KDDockWidgets::Controllers;

SegmentedIndicatorsOverlay_qtwidgets::SegmentedIndicatorsOverlay_qtwidgets(
    Controllers::SegmentedIndicators *controller, QWidget *parent)
    : View_qtwidgets<QWidget>(controller, Type::None, parent)
    , m_controller(controller)
{
}

SegmentedIndicatorsOverlay_qtwidgets::~SegmentedIndicatorsOverlay_qtwidgets()
{
}

void SegmentedIndicatorsOverlay_qtwidgets::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    drawSegments(&p);
}


void SegmentedIndicatorsOverlay_qtwidgets::drawSegments(QPainter *p)
{
    const QHash<DropLocation, QPolygon> segments = m_controller->segments();
    for (DropLocation loc :
         { DropLocation_Left, DropLocation_Top, DropLocation_Right, DropLocation_Bottom,
           DropLocation_Center, DropLocation_OutterLeft, DropLocation_OutterTop,
           DropLocation_OutterRight, DropLocation_OutterBottom })
        drawSegment(p, segments.value(loc));
}

void SegmentedIndicatorsOverlay_qtwidgets::drawSegment(QPainter *p, const QPolygon &segment)
{
    if (segment.isEmpty())
        return;

    QPen pen(SegmentedIndicators::s_segmentPenColor);
    pen.setWidth(SegmentedIndicators::s_segmentPenWidth);
    p->setPen(pen);
    QColor brush(SegmentedIndicators::s_segmentBrushColor);

    if (segment.containsPoint(m_controller->hoveredPt(), Qt::OddEvenFill))
        brush = SegmentedIndicators::s_hoveredSegmentBrushColor;

    p->setBrush(brush);
    p->drawPolygon(segment);
}

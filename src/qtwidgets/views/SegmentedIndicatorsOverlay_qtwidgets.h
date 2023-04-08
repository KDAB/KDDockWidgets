/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "View_qtwidgets.h"

namespace KDDockWidgets {

namespace Core {
class SegmentedIndicators;
}

namespace qtwidgets {

class DOCKS_EXPORT SegmentedIndicatorsOverlay : public View_qtwidgets<QWidget>
{
    Q_OBJECT
public:
    explicit SegmentedIndicatorsOverlay(Core::SegmentedIndicators *controller,
                                        QWidget *parent = nullptr);
    ~SegmentedIndicatorsOverlay() override;

    static QColor s_segmentPenColor;
    static QColor s_segmentBrushColor;
    static QColor s_hoveredSegmentBrushColor;

protected:
    void paintEvent(QPaintEvent *) override;

private:
    void drawSegments(QPainter *p);
    void drawSegment(QPainter *p, const QPolygon &segment);
    Core::SegmentedIndicators *const m_controller;
};

}

}

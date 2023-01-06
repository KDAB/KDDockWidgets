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

namespace Controllers {
class SegmentedIndicators;
}

namespace Views {

class DOCKS_EXPORT SegmentedIndicatorsOverlay_qtwidgets : public View_qtwidgets<QWidget>
{
    Q_OBJECT
public:
    explicit SegmentedIndicatorsOverlay_qtwidgets(Controllers::SegmentedIndicators *controller,
                                                  QWidget *parent = nullptr);
    ~SegmentedIndicatorsOverlay_qtwidgets() override;

protected:
    void paintEvent(QPaintEvent *) override;

private:
    void drawSegments(QPainter *p);
    void drawSegment(QPainter *p, const QPolygon &segment);
    Controllers::SegmentedIndicators *const m_controller;
};

}

}

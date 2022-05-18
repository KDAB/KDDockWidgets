/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_CLASSICINDICATORS_WINDOW_QTWIDGETS_H
#define KD_CLASSICINDICATORS_WINDOW_QTWIDGETS_H
#pragma once

#include "controllers/DropIndicatorOverlay.h"
#include "controllers/indicators/ClassicIndicators.h"

#include <QImage>
#include <QWidget>
#include <QResizeEvent>

namespace KDDockWidgets {

class Indicator;

namespace Controllers {
class ClassicIndicators;
}

class IndicatorWindow : public QWidget
{
    Q_OBJECT
public:
    explicit IndicatorWindow(Controllers::ClassicIndicators *classicIndicators);
    DropLocation hover(QPoint globalPos);
    void updatePositions();
    QPoint posForIndicator(DropLocation) const;

private:
    void updateIndicatorVisibility();
    void resizeEvent(QResizeEvent *ev) override;

    // When the compositor doesn't support translucency, we use a mask instead
    // Only happens on Linux
    void updateMask();

    Indicator *indicatorForLocation(DropLocation loc) const;

    Controllers::ClassicIndicators *const classicIndicators;
    Indicator *const m_center;
    Indicator *const m_left;
    Indicator *const m_right;
    Indicator *const m_bottom;
    Indicator *const m_top;
    Indicator *const m_outterLeft;
    Indicator *const m_outterRight;
    Indicator *const m_outterBottom;
    Indicator *const m_outterTop;
    QVector<Indicator *> m_indicators;
};

}

#endif

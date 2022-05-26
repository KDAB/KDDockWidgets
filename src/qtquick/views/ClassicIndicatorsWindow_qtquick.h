/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_CLASSICINDICATORS_WINDOW_QTQUICK_H
#define KD_CLASSICINDICATORS_WINDOW_QTQUICK_H
#pragma once

#include "controllers/DropIndicatorOverlay.h"
#include "controllers/indicators/ClassicIndicators.h"
#include "views/ClassicIndicatorWindow.h"

#include <QQuickView>

namespace KDDockWidgets {

namespace Controllers {
class ClassicIndicators;
}

class IndicatorWindow_qtquick : public QQuickView, public Views::ClassicIndicatorWindow
{
    Q_OBJECT
    Q_PROPERTY(KDDockWidgets::Controllers::ClassicIndicators *classicIndicators READ classicIndicators CONSTANT)
public:
    explicit IndicatorWindow_qtquick(Controllers::ClassicIndicators *);

    Q_INVOKABLE QString iconName(int loc, bool active) const;
    Controllers::ClassicIndicators *classicIndicators() const;
    QQuickItem *indicatorForLocation(DropLocation loc) const;

    DropLocation hover(QPoint globalPos) override;
    void updatePositions() override;
    QPoint posForIndicator(DropLocation) const override;
    void raise() override;
    void setVisible(bool) override;
    bool isWindow() const override;
    void setGeometry(QRect) override;
    void resize(QSize) override;
    void setObjectName(const QString &) override;

private:
    DropLocation locationForIndicator(const QQuickItem *) const;
    QQuickItem *indicatorForPos(QPoint) const;
    QVector<QQuickItem *> indicatorItems() const;
    Controllers::ClassicIndicators *const m_classicIndicators;
};
}

#endif

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_CLASSICINDICATORS_WINDOW_QTQUICK_H
#define KD_CLASSICINDICATORS_WINDOW_QTQUICK_H
#pragma once

#include "views/ClassicIndicatorWindowViewInterface.h"

#include <QQuickView>

namespace KDDockWidgets {

namespace Controllers {
class ClassicIndicators;
}

class IndicatorWindow_qtquick : public QQuickView, public Views::ClassicIndicatorWindowViewInterface
{
    Q_OBJECT
    Q_PROPERTY(bool innerLeftIndicatorVisible READ innerLeftIndicatorVisible NOTIFY
                   indicatorsVisibleChanged)
    Q_PROPERTY(bool innerRightIndicatorVisible READ innerRightIndicatorVisible NOTIFY
                   indicatorsVisibleChanged)
    Q_PROPERTY(
        bool innerTopIndicatorVisible READ innerTopIndicatorVisible NOTIFY indicatorsVisibleChanged)
    Q_PROPERTY(bool innerBottomIndicatorVisible READ innerBottomIndicatorVisible NOTIFY
                   indicatorsVisibleChanged)
    Q_PROPERTY(bool outterLeftIndicatorVisible READ outterLeftIndicatorVisible NOTIFY
                   indicatorsVisibleChanged)
    Q_PROPERTY(bool outterRightIndicatorVisible READ outterRightIndicatorVisible NOTIFY
                   indicatorsVisibleChanged)
    Q_PROPERTY(bool outterTopIndicatorVisible READ outterTopIndicatorVisible NOTIFY
                   indicatorsVisibleChanged)
    Q_PROPERTY(bool outterBottomIndicatorVisible READ outterBottomIndicatorVisible NOTIFY
                   indicatorsVisibleChanged)
    Q_PROPERTY(bool tabIndicatorVisible READ tabIndicatorVisible NOTIFY indicatorsVisibleChanged)
    Q_PROPERTY(QRect hoveredFrameRect READ hoveredFrameRect NOTIFY hoveredFrameRectChanged)
    Q_PROPERTY(KDDockWidgets::DropLocation currentDropLocation READ currentDropLocation NOTIFY
                   currentDropLocationChanged)
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

    // Property getters for QML:
    bool innerLeftIndicatorVisible() const;
    bool innerRightIndicatorVisible() const;
    bool innerTopIndicatorVisible() const;
    bool innerBottomIndicatorVisible() const;
    bool outterLeftIndicatorVisible() const;
    bool outterRightIndicatorVisible() const;
    bool outterTopIndicatorVisible() const;
    bool outterBottomIndicatorVisible() const;
    bool tabIndicatorVisible() const;
    QRect hoveredFrameRect() const;
    DropLocation currentDropLocation() const;

Q_SIGNALS:
    void indicatorsVisibleChanged();
    void hoveredFrameRectChanged();
    void currentDropLocationChanged();

private:
    DropLocation locationForIndicator(const QQuickItem *) const;
    QQuickItem *indicatorForPos(QPoint) const;
    QVector<QQuickItem *> indicatorItems() const;
    Controllers::ClassicIndicators *const m_classicIndicators;
};
}

#endif

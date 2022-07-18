/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * @file
 * @brief Implements a QTabWidget derived class with support for docking and undocking
 * KDockWidget::DockWidget as tabs .
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifndef KD_TABBAR_QUICK_P_H
#define KD_TABBAR_QUICK_P_H
#pragma once

#include "View_qtquick.h"
#include "views/TabBarViewInterface.h"

#include <QPointer>
#include <QHash>

#include "kdbindings/signal.h"

namespace KDDockWidgets::Controllers {
class TabBar;
}

namespace KDDockWidgets::Views {

class DockWidget;
class TabWidget;

class DOCKS_EXPORT TabBar_qtquick
    : public View_qtquick,
      public TabBarViewInterface
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem *tabBarQmlItem READ tabBarQmlItem WRITE setTabBarQmlItem NOTIFY tabBarQmlItemChanged)
    Q_PROPERTY(bool tabBarAutoHide READ tabBarAutoHide NOTIFY tabBarAutoHideChanged)
public:
    explicit TabBar_qtquick(Controllers::TabBar *controller, QQuickItem *parent = nullptr);
    int tabAt(QPoint localPos) const override;

    QQuickItem *tabBarQmlItem() const;
    void setTabBarQmlItem(QQuickItem *);

    QString text(int index) const override;
    QRect rectForTab(int index) const override;

    void moveTabTo(int from, int to) override;
    Controllers::DockWidget *currentDockWidget() const override;
    bool tabsAreMovable() const override;

    /// Returns whether the tab bar should hide when there's only 1 tab visible
    /// Default true, unless Flag_HideTitleBarWhenTabsVisible
    bool tabBarAutoHide() const;

Q_SIGNALS:
    void tabBarQmlItemChanged();
    void tabBarAutoHideChanged();

protected:
    bool event(QEvent *ev) override;
    void init() override;

private:
    QQuickItem *tabAt(int index) const;
    QPointer<QQuickItem> m_tabBarQmlItem;
    KDBindings::ScopedConnection m_tabBarAutoHideChanged;
};
}

#endif

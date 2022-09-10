/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

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

#include <QAbstractListModel>
#include <QPointer>
#include <QHash>

#include "kdbindings/signal.h"

namespace KDDockWidgets::Controllers {
class TabBar;
}

namespace KDDockWidgets::Views {

class DockWidget;
class DockWidgetModel;
class TabWidget;
class Stack_qtquick;

class DOCKS_EXPORT TabBar_qtquick : public View_qtquick, public TabBarViewInterface
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem *tabBarQmlItem READ tabBarQmlItem WRITE setTabBarQmlItem NOTIFY
                   tabBarQmlItemChanged)
    Q_PROPERTY(bool tabBarAutoHide READ tabBarAutoHide NOTIFY tabBarAutoHideChanged)
    Q_PROPERTY(DockWidgetModel *dockWidgetModel READ dockWidgetModel CONSTANT)
public:
    explicit TabBar_qtquick(Controllers::TabBar *controller, QQuickItem *parent = nullptr);

    DockWidgetModel *dockWidgetModel() const;

    int tabAt(QPoint localPos) const override;
    QQuickItem *tabBarQmlItem() const;
    void setTabBarQmlItem(QQuickItem *);

    QString text(int index) const override;
    QRect rectForTab(int index) const override;

    void moveTabTo(int from, int to) override;
    Q_INVOKABLE void setCurrentIndex(int index) override;
    Stack_qtquick *stackView() const;
    void renameTab(int index, const QString &) override;
    void changeTabIcon(int index, const QIcon &icon) override;
    /// Returns whether the tab bar should hide when there's only 1 tab visible
    /// Default true, unless Flag_HideTitleBarWhenTabsVisible
    bool tabBarAutoHide() const;

    void removeDockWidget(Controllers::DockWidget *) override;
    void insertDockWidget(int index, Controllers::DockWidget *, const QIcon &,
                          const QString &title) override;

Q_SIGNALS:
    void tabBarQmlItemChanged();
    void tabBarAutoHideChanged();

protected:
    bool event(QEvent *ev) override;
    void init() override;

private:
    QQuickItem *tabAt(int index) const;
    DockWidgetModel *const m_dockWidgetModel;
    QPointer<QQuickItem> m_tabBarQmlItem;
    KDBindings::ScopedConnection m_tabBarAutoHideChanged;
};

class DockWidgetModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    enum Role {
        Role_Title = Qt::UserRole
    };

    explicit DockWidgetModel(Controllers::TabBar *, QObject *parent);
    int count() const;
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    Controllers::DockWidget *dockWidgetAt(int index) const;
    Controllers::DockWidget *currentDockWidget() const;
    void setCurrentDockWidget(Controllers::DockWidget *);
    void remove(Controllers::DockWidget *);
    int indexOf(const Controllers::DockWidget *);
    bool insert(Controllers::DockWidget *dw, int index);
    bool contains(Controllers::DockWidget *dw) const;
    int currentIndex() const;
    void setCurrentIndex(int index);

protected:
    QHash<int, QByteArray> roleNames() const override;

Q_SIGNALS:
    void countChanged();
    void dockWidgetRemoved();

private:
    void emitDataChangedFor(Controllers::DockWidget *);

    Controllers::TabBar *const m_tabBar = nullptr;
    QVector<Controllers::DockWidget *> m_dockWidgets;
    QHash<Controllers::DockWidget *, QVector<QMetaObject::Connection>>
        m_connections; // To make it easy to disconnect from lambdas
    bool m_removeGuard = false;
    Controllers::DockWidget *m_currentDockWidget = nullptr;
};

}

#endif

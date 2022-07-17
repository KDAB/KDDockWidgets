/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * @file
 * @brief The QQuickItem counter part of TabWidgetQuick. Handles GUI while TabWidget handles state.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifndef KDTABWIDGETQUICK_P_H
#define KDTABWIDGETQUICK_P_H
#pragma once

#include "View_qtquick.h"
#include "views/StackViewInterface.h"

#include <QAbstractListModel>
#include <QVector>

#include "kdbindings/signal.h"

namespace KDDockWidgets {
namespace Controllers {
class DockWidget;
class Group;
class TabBar;
}

namespace Views {


class DockWidgetModel;

class DOCKS_EXPORT Stack_qtquick
    : public View_qtquick,
      public StackViewInterface
{
    Q_OBJECT
    Q_PROPERTY(DockWidgetModel *dockWidgetModel READ dockWidgetModel CONSTANT)
    Q_PROPERTY(QObject *tabBar READ tabBarViewObj NOTIFY tabBarChanged)
public:
    explicit Stack_qtquick(Controllers::Stack *controller,
                           QQuickItem *parent = nullptr);

    int numDockWidgets() const override;
    void removeDockWidget(Controllers::DockWidget *) override;
    int indexOfDockWidget(const Controllers::DockWidget *) const override;
    DockWidgetModel *dockWidgetModel() const;
    Controllers::DockWidget *dockwidgetAt(int index) const override;
    int currentIndex() const override;
    bool insertDockWidget(int index, Controllers::DockWidget *, const QIcon &, const QString &title) override;
    Q_INVOKABLE void setCurrentDockWidget(int index) override;
    void setDocumentMode(bool) override;
    Controllers::DockWidget *currentDockWidget() const;

    /// @brief Returns the tab bar as a QObject for QML.
    /// As the base class is not a QObject.
    QObject *tabBarViewObj() const;

    /// @brief Returns the stack controller associated with this view
    Controllers::Stack *stack() const;

    /// Returns whether the tab bar should hide when there's only 1 tab visible
    /// Default true, unless Flag_HideTitleBarWhenTabsVisible
    bool tabBarAutoHide() const;

Q_SIGNALS:
    void tabBarChanged();
    void tabBarAutoHideChanged();

protected:
    bool isPositionDraggable(QPoint p) const override;
    void renameTab(int index, const QString &) override;
    void changeTabIcon(int index, const QIcon &) override;
    void init() override;

private:
    Q_DISABLE_COPY(Stack_qtquick)
    DockWidgetModel *const m_dockWidgetModel;
    Controllers::DockWidget *m_currentDockWidget = nullptr;
    KDBindings::ScopedConnection m_tabBarAutoHideChanged;
};

class DockWidgetModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Role {
        Role_Title = Qt::UserRole
    };

    explicit DockWidgetModel(QObject *parent);
    int count() const;
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    Controllers::DockWidget *dockWidgetAt(int index) const;
    void remove(Controllers::DockWidget *);
    int indexOf(const Controllers::DockWidget *);
    bool insert(Controllers::DockWidget *dw, int index);
    bool contains(Controllers::DockWidget *dw) const;

protected:
    QHash<int, QByteArray> roleNames() const override;

Q_SIGNALS:
    void countChanged();
    void dockWidgetRemoved();

private:
    void emitDataChangedFor(Controllers::DockWidget *);
    QVector<Controllers::DockWidget *> m_dockWidgets;
    QHash<Controllers::DockWidget *, QVector<QMetaObject::Connection>> m_connections; // To make it easy to disconnect from lambdas
    bool m_removeGuard = false;
};

}
}

#endif

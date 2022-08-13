/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "../Controller.h"
#include "../private/Draggable_p.h"
#include "Group.h"
#include "TabBar.h"

#include "kdbindings/signal.h"

namespace KDDockWidgets::Controllers {

class Group;
class TabBar;

class DOCKS_EXPORT Stack : public Controller, public Draggable
{
    Q_OBJECT
public:
    explicit Stack(Group *group, StackOptions);
    virtual ~Stack() override;

    /**
     * @brief returns the number of dock widgets in this TabWidget
     */
    int numDockWidgets() const;

    /// @brief Returns the current dock widget
    DockWidget *currentDockWidget() const;

    /// Sets whether the tab bar should be hidden when there's only 1 tab shown
    /// Default is true.
    /// See Config::Flag_AlwaysShowTabs to change this behaviour
    void setTabBarAutoHide(bool);
    bool tabBarAutoHide() const;

    ///@brief appends a dock widget into this TabWidget
    void addDockWidget(DockWidget *);

    /**
     * @brief inserts @p dockwidget into the TabWidget, at @p index
     * @param dockwidget the dockwidget to insert
     * @param index The index to where to put it
     */
    bool insertDockWidget(DockWidget *dockwidget, int index);

    /**
     * @brief Returns whether dockwidget @p dw is contained in this tab widget
     * Equivalent to indexOf(dw) != -1
     */
    bool contains(DockWidget *dw) const;

    /**
     * @brief Returns the tab bar
     */
    Controllers::TabBar *tabBar() const;

    ///@brief getter for the group
    Group *group() const;

    // Draggable interface
    std::unique_ptr<WindowBeingDragged> makeWindow() override;
    DockWidget *singleDockWidget() const override;
    bool isWindow() const override;
    bool isMDI() const override;
    bool isPositionDraggable(QPoint p) const override;

    StackOptions options() const;

    /// @brief Enables document mode. Default is false.
    void setDocumentMode(bool);

    /// Emitted when the tabBarAutoHide boolean member changes
    KDBindings::Signal<bool> tabBarAutoHideChanged;

public: // TODOm3
    void onTabInserted();
    void onTabRemoved();
    void onCurrentTabChanged(int index);
    bool onMouseDoubleClick(QPoint localPos);

private:
    TabBar *const m_tabBar;
    Group *const m_group;
    bool m_tabBarAutoHide = true;
    const StackOptions m_options;

    Q_DISABLE_COPY(Stack)
};

}

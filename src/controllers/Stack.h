/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "../Controller.h"
#include "../private/Draggable_p.h"
#include "Group.h"
#include "TabBar.h"

#include <QPointer>

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

    /**
     * @brief Removes a dock widget from the TabWidget
     */
    void removeDockWidget(DockWidget *);

    /**
     * @brief Returns the index of the dock widget, or -1 if it doesn't exist
     */
    int indexOfDockWidget(const DockWidget *) const;

    /**
     * @brief Sets the current dock widget index
     */
    void setCurrentDockWidget(int index);
    void setCurrentDockWidget(DockWidget *);

    /// @brief Returns the current dock widget
    DockWidget *currentDockWidget() const;

    bool insertDockWidget(int index, DockWidget *, const QIcon &, const QString &title);

    void setTabBarAutoHide(bool);

    ///@brief rename's the tab's text
    void renameTab(int index, const QString &);

    ///@brief change the tab's icon
    void changeTabIcon(int index, const QIcon &);

    /**
     * @brief Returns the current index
     */
    int currentIndex() const;

    ///@brief appends a dock widget into this TabWidget
    void addDockWidget(DockWidget *);

    /**
     * @brief Returns the dock widget tabbed at index @p index
     */
    DockWidget *dockwidgetAt(int index) const;

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

Q_SIGNALS:
    void currentTabChanged(int index);
    void currentDockWidgetChanged(KDDockWidgets::Controllers::DockWidget *);
    void countChanged();

public: // TODOm3
    void onTabInserted();
    void onTabRemoved();
    void onCurrentTabChanged(int index);
    bool onMouseDoubleClick(QPoint localPos);

private:
    TabBar *const m_tabBar;
    Group *const m_group;
    const StackOptions m_options;

    Q_DISABLE_COPY(Stack)
};

}

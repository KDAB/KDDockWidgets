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
#include "controllers/Frame.h"
#include "controllers/TabBar.h"

#include <QPointer>

namespace KDDockWidgets::Controllers {

class Frame;
class TabBar;

class DOCKS_EXPORT Stack : public Controller, public Draggable
{
    Q_OBJECT
public:
    explicit Stack(Frame *frame, TabWidgetOptions); // TODO: Rename TabWidgetOptions
    virtual ~Stack() override;

    /**
     * @brief returns the number of dock widgets in this TabWidget
     */
    int numDockWidgets() const;

    /**
     * @brief Removes a dock widget from the TabWidget
     */
    void removeDockWidget(DockWidgetBase *);

    /**
     * @brief Returns the index of the dock widget, or -1 if it doesn't exist
     */
    int indexOfDockWidget(const DockWidgetBase *) const;

    /**
     * @brief Sets the current dock widget index
     */
    void setCurrentDockWidget(int index);
    void setCurrentDockWidget(DockWidgetBase *);

    /// @brief Returns the current dock widget
    DockWidgetBase *currentDockWidget() const;

    bool insertDockWidget(int index, DockWidgetBase *, const QIcon &, const QString &title);

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
    void addDockWidget(DockWidgetBase *);

    /**
     * @brief Returns the dock widget tabbed at index @p index
     */
    DockWidgetBase *dockwidgetAt(int index) const;

    /**
     * @brief inserts @p dockwidget into the TabWidget, at @p index
     * @param dockwidget the dockwidget to insert
     * @param index The index to where to put it
     */
    bool insertDockWidget(DockWidgetBase *dockwidget, int index);

    /**
     * @brief Returns whether dockwidget @p dw is contained in this tab widget
     * Equivalent to indexOf(dw) != -1
     */
    bool contains(DockWidgetBase *dw) const;

    /**
     * @brief Returns the tab bar
     */
    Controllers::TabBar *tabBar() const;

    ///@brief getter for the frame
    Frame *frame() const;

    // Draggable interface
    std::unique_ptr<WindowBeingDragged> makeWindow() override;
    DockWidgetBase *singleDockWidget() const override;
    bool isWindow() const override;
    bool isMDI() const override;
    bool isPositionDraggable(QPoint p) const override;

    TabWidgetOptions options() const;

Q_SIGNALS:
    void currentTabChanged(int index);
    void currentDockWidgetChanged(KDDockWidgets::Controllers::DockWidgetBase *);
    void countChanged();

public: // TODO
    void onTabInserted();
    void onTabRemoved();
    void onCurrentTabChanged(int index);
    bool onMouseDoubleClick(QPoint localPos);

private:
    TabBar *const m_tabBar;
    Frame *const m_frame;
    const TabWidgetOptions m_options;

    Q_DISABLE_COPY(Stack)
};

}

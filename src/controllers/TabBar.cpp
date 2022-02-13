/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "TabBar.h"
#include "private/Draggable_p.h"
#include "Controller.h"
#include "controllers/Stack.h"
#include "controllers/FloatingWindow.h"
#include "views_qtwidgets/TabBar_qtwidgets.h"
#include "private/DragController_p.h"
#include "private/Utils_p.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::Controllers;

Controllers::TabBar::TabBar(Stack *tabWidget)
    : Controller(new Views::TabBar_qtwidgets(this, tabWidget->asWidget())) // TODO: Config::self().frameworkWidgetFactory()->createTabBar(this)
    , Draggable(view()->asQWidget())
    , m_tabWidget(tabWidget)
{
}

Controllers::TabBar::~TabBar()
{
}

bool Controllers::TabBar::dragCanStart(QPoint pressPos, QPoint pos) const
{
    // Here we allow the user to re-order tabs instead of dragging them off.
    // To do that we just return false here, and QTabBar will handle the mouse event, assuming QTabBar::isMovable.

    const bool defaultResult = Draggable::dragCanStart(pressPos, pos);
    auto view = static_cast<Views::TabBar_qtwidgets *>(this->view()); // TODO

    if (!defaultResult || !view->isMovable()) {
        // Nothing more to do. If the drag wouldn't start anyway, return false.
        // And if the tabs aren't movable, just return the default result, which just considers
        // QApplication::startDragDistances
        return defaultResult;
    }

    const int index = view->tabAt(view->mapFromGlobal(pos));
    if (index == -1)
        return defaultResult;

    const int deltaX = qAbs(pos.x() - pressPos.x());
    const int deltaY = qAbs(pos.y() - pressPos.y());

    if (deltaY > 5 * QApplication::startDragDistance()) {
        // Moving up or down too much results in a detach. No tab re-ordering allowed.
        return true;
    } else if (deltaY > QApplication::startDragDistance() && deltaX < QApplication::startDragDistance()) {
        // Moved a bit up or down, but not left/right, then detach too.
        // Only if it's going considerably left/right we allow to re-order tabs.
        return true;
    }

    return false;
}

DockWidgetBase *Controllers::TabBar::dockWidgetAt(int index) const
{
    if (index < 0 || index >= numDockWidgets())
        return nullptr;

    return m_tabWidget->dockwidgetAt(index);
}

DockWidgetBase *Controllers::TabBar::dockWidgetAt(QPoint localPos) const
{
    return dockWidgetAt(static_cast<Views::TabBar_qtwidgets *>(view())->tabAt(localPos));
}

std::unique_ptr<WindowBeingDragged> Controllers::TabBar::makeWindow()
{
    auto dock = m_lastPressedDockWidget;
    m_lastPressedDockWidget = nullptr; // TODO check if we still have this dock, it might have been deleted

    const bool hideTitleBarWhenTabsVisible = Config::self().flags() & Config::Flag_HideTitleBarWhenTabsVisible;
    const bool alwaysShowTabs = Config::self().flags() & Config::Flag_AlwaysShowTabs;

    if (hideTitleBarWhenTabsVisible) {
        if (dock) {
            if (alwaysShowTabs && hasSingleDockWidget()) {
                // Case #1. User is dragging a tab but there's only 1 tab (and tabs are always visible), so drag everything instead, no detaching happens
                return m_tabWidget->makeWindow();
            }
        } else {
            // Case #2. User is dragging on the QTabBar background, not on an actual tab.
            // As Flag_HideTitleBarWhenTabsVisible is set, we let the user drag through the tab widget background.
            return m_tabWidget->makeWindow();
        }
    } else {
        if (dock && hasSingleDockWidget() && alwaysShowTabs) {
            // Case #3. window with title bar and single tab, no detaching should happen, just use the title bar.
            return {};
        }
    }

    if (!dock)
        return {};

    FloatingWindow *floatingWindow = frame()->detachTab(dock);
    if (!floatingWindow)
        return {};

    auto draggable = KDDockWidgets::usesNativeTitleBar() ? static_cast<Draggable *>(floatingWindow)
                                                         : static_cast<Draggable *>(this);
    return std::unique_ptr<WindowBeingDragged>(new WindowBeingDragged(floatingWindow, draggable));
}

bool Controllers::TabBar::isWindow() const
{
    // Same semantics as tab widget, no need to duplicate logic
    return m_tabWidget->isWindow();
}

void Controllers::TabBar::onMousePress(QPoint localPos)
{
    m_lastPressedDockWidget = dockWidgetAt(localPos);
    Frame *frame = this->frame();
    if ((Config::self().flags() & Config::Flag_TitleBarIsFocusable) && !frame->isFocused()) {
        // User clicked on a tab which was already focused
        // A tab changing also counts as a change of scope
        frame->FocusScope::focus(Qt::MouseFocusReason);
    }
}

void Controllers::TabBar::onMouseDoubleClick(QPoint localPos)
{
    if (DockWidgetBase *dw = dockWidgetAt(localPos))
        dw->setFloating(true);
}

bool Controllers::TabBar::hasSingleDockWidget() const
{
    return numDockWidgets() == 1;
}

int Controllers::TabBar::numDockWidgets() const
{
    return m_tabWidget->numDockWidgets();
}


DockWidgetBase *Controllers::TabBar::singleDockWidget() const
{
    return m_tabWidget->singleDockWidget();
}

bool Controllers::TabBar::isMDI() const
{
    Frame *f = frame();
    return f && f->isMDI();
}

Frame *Controllers::TabBar::frame() const
{
    return m_tabWidget->frame();
}

void Controllers::TabBar::moveTabTo(int from, int to)
{
    auto view = static_cast<Views::TabBar_qtwidgets *>(this->view()); // TODO
    view->moveTabTo(from, to);
}

QString Controllers::TabBar::text(int index) const
{
    // TODO: We can store the text in the controller

    auto view = static_cast<Views::TabBar_qtwidgets *>(this->view()); // TODO
    return view->text(index);
}

QRect Controllers::TabBar::rectForTab(int index) const
{
    auto view = static_cast<Views::TabBar_qtwidgets *>(this->view()); // TODO
    return view->rectForTab(index);
}

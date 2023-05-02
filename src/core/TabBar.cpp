/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "TabBar.h"
#include "core/Draggable_p.h"
#include "Controller.h"
#include "core/Stack.h"
#include "core/FloatingWindow.h"
#include "core/DockWidget_p.h"
#include "views/TabBarViewInterface.h"
#include "Platform.h"

#include "core/DragController_p.h"
#include "core/Utils_p.h"
#include "Config.h"
#include "core/ViewFactory.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;

Core::TabBar::TabBar(Stack *stack)
    : Controller(ViewType::TabBar, Config::self().viewFactory()->createTabBar(this, stack->view()))
    , Draggable(view())
    , m_stack(stack)
{
    view()->init();
    dynamic_cast<Core::TabBarViewInterface *>(view())->setTabsAreMovable(tabsAreMovable());
}

Core::TabBar::~TabBar()
{
}

bool Core::TabBar::tabsAreMovable() const
{
    return Config::self().flags() & Config::Flag_AllowReorderTabs;
}

bool Core::TabBar::dragCanStart(QPoint pressPos, QPoint pos) const
{
    // Here we allow the user to re-order tabs instead of dragging them off.
    // To do that we just return false here, and QTabBar will handle the mouse event, assuming
    // QTabBar::isMovable.

    const bool defaultResult = Draggable::dragCanStart(pressPos, pos);

    if (!defaultResult || !tabsAreMovable()) {
        // Nothing more to do. If the drag wouldn't start anyway, return false.
        // And if the tabs aren't movable, just return the default result, which just considers
        // startDragDistance
        return defaultResult;
    }

    const int index =
        dynamic_cast<Core::TabBarViewInterface *>(view())->tabAt(view()->mapFromGlobal(pos));
    if (index == -1)
        return defaultResult;

    const int deltaX = qAbs(pos.x() - pressPos.x());
    const int deltaY = qAbs(pos.y() - pressPos.y());

    const int startDragDistance = Platform::instance()->startDragDistance();

    if (deltaY > 5 * startDragDistance) {
        // Moving up or down too much results in a detach. No tab re-ordering allowed.
        return true;
    } else if (deltaY > startDragDistance && deltaX < startDragDistance) {
        // Moved a bit up or down, but not left/right, then detach too.
        // Only if it's going considerably left/right we allow to re-order tabs.
        return true;
    }

    return false;
}

Core::DockWidget *Core::TabBar::dockWidgetAt(int index) const
{
    if (index < 0 || index >= numDockWidgets())
        return nullptr;

    return const_cast<DockWidget *>(m_dockWidgets.value(index));
}

Core::DockWidget *Core::TabBar::dockWidgetAt(QPoint localPos) const
{
    return dockWidgetAt(dynamic_cast<Core::TabBarViewInterface *>(view())->tabAt(localPos));
}

int TabBar::indexOfDockWidget(const Core::DockWidget *dw) const
{
    return m_dockWidgets.indexOf(dw);
}

void TabBar::removeDockWidget(Core::DockWidget *dw)
{
    const bool wasCurrent = dw == m_currentDockWidget;
    const int index = m_dockWidgets.indexOf(dw);

    if (wasCurrent) {
        const bool isLast = index == m_dockWidgets.count() - 1;
        const int newCurrentIndex = isLast ? index - 1 : index + 1;
        setCurrentIndex(newCurrentIndex);
    }

    dw->disconnect(this);

    m_removeGuard = true;
    // The view might call setCurrenteIndex() before our m_dockWidgets reflectig the state.
    // m_removeGuard protects against that.
    dynamic_cast<Core::TabBarViewInterface *>(view())->removeDockWidget(dw);
    m_removeGuard = false;

    m_dockWidgets.removeOne(dw);
    group()->onDockWidgetCountChanged();
}

void TabBar::insertDockWidget(int index, Core::DockWidget *dw, const Icon &icon,
                              const QString &title)
{
    if (auto oldGroup = dw->dptr()->group()) {
        if (auto oldTabBar = oldGroup->tabBar()) {
            if (oldTabBar != this) {
                oldTabBar->removeDockWidget(dw);
            }
        }
    }

    m_dockWidgets.insert(index, dw);
    connect(dw, &DockWidget::aboutToDelete, this, &TabBar::removeDockWidget);

    dynamic_cast<Core::TabBarViewInterface *>(view())->insertDockWidget(index, dw, icon, title);
    if (!m_currentDockWidget)
        setCurrentDockWidget(dw);

    group()->onDockWidgetCountChanged();
}

std::unique_ptr<WindowBeingDragged> Core::TabBar::makeWindow()
{
    auto dock = m_lastPressedDockWidget;
    m_lastPressedDockWidget =
        nullptr; // TODO check if we still have this dock, it might have been deleted

    const bool hideTitleBarWhenTabsVisible =
        Config::self().flags() & Config::Flag_HideTitleBarWhenTabsVisible;
    const bool alwaysShowTabs = Config::self().flags() & Config::Flag_AlwaysShowTabs;

    if (hideTitleBarWhenTabsVisible) {
        if (dock) {
            if (alwaysShowTabs && hasSingleDockWidget()) {
                // Case #1. User is dragging a tab but there's only 1 tab (and tabs are always
                // visible), so drag everything instead, no detaching happens
                return m_stack->makeWindow();
            }
        } else {
            // Case #2. User is dragging on the QTabBar background, not on an actual tab.
            // As Flag_HideTitleBarWhenTabsVisible is set, we let the user drag through the tab
            // widget background.
            return m_stack->makeWindow();
        }
    } else {
        if (dock && hasSingleDockWidget() && alwaysShowTabs) {
            // Case #3. window with title bar and single tab, no detaching should happen, just use
            // the title bar.
            return {};
        }
    }

    if (!dock)
        return {};

    FloatingWindow *floatingWindow = group()->detachTab(dock);
    if (!floatingWindow)
        return {};

    auto draggable = KDDockWidgets::usesNativeTitleBar() ? static_cast<Draggable *>(floatingWindow)
                                                         : static_cast<Draggable *>(this);
    return std::unique_ptr<WindowBeingDragged>(new WindowBeingDragged(floatingWindow, draggable));
}

bool Core::TabBar::isWindow() const
{
    // Same semantics as tab widget, no need to duplicate logic
    return m_stack->isWindow();
}

void Core::TabBar::onMousePress(QPoint localPos)
{
    m_lastPressedDockWidget = dockWidgetAt(localPos);
    Group *group = this->group();
    if ((Config::self().flags() & Config::Flag_TitleBarIsFocusable) && !group->isFocused()) {
        // User clicked on a tab which was already focused
        // A tab changing also counts as a change of scope
        group->FocusScope::focus(Qt::MouseFocusReason);
    }
}

void Core::TabBar::onMouseDoubleClick(QPoint localPos)
{
    if (DockWidget *dw = dockWidgetAt(localPos))
        dw->setFloating(true);
}

bool Core::TabBar::hasSingleDockWidget() const
{
    return numDockWidgets() == 1;
}

int Core::TabBar::numDockWidgets() const
{
    return m_dockWidgets.size();
}

Core::DockWidget *Core::TabBar::singleDockWidget() const
{
    return m_stack->singleDockWidget();
}

bool Core::TabBar::isMDI() const
{
    Group *f = group();
    return f && f->isMDI();
}

Group *Core::TabBar::group() const
{
    return m_stack->group();
}

Stack *TabBar::stack() const
{
    return m_stack;
}

void Core::TabBar::moveTabTo(int from, int to)
{
    auto fromDw = m_dockWidgets.takeAt(from);
    m_dockWidgets.insert(to, fromDw);
    dynamic_cast<Core::TabBarViewInterface *>(view())->moveTabTo(from, to);
}

QString Core::TabBar::text(int index) const
{
    return dynamic_cast<Core::TabBarViewInterface *>(view())->text(index);
}

QRect Core::TabBar::rectForTab(int index) const
{
    return dynamic_cast<Core::TabBarViewInterface *>(view())->rectForTab(index);
}

DockWidget *TabBar::currentDockWidget() const
{
    return m_currentDockWidget;
}

void TabBar::setCurrentDockWidget(DockWidget *dw)
{
    if (m_removeGuard) // We're in the middle of a remove.
        return;

    if (dw == m_currentDockWidget)
        return;

    setCurrentIndex(indexOfDockWidget(dw));
}

int TabBar::currentIndex() const
{
    if (!m_currentDockWidget)
        return -1;

    return m_dockWidgets.indexOf(m_currentDockWidget);
}

void TabBar::setCurrentIndex(int index)
{
    if (m_removeGuard) // We're in the middle of a remove.
        return;

    auto newCurrentDw = dockWidgetAt(index);
    if (newCurrentDw == m_currentDockWidget)
        return;

    m_currentDockWidget = newCurrentDw;
    Q_EMIT currentDockWidgetChanged(newCurrentDw);
    dynamic_cast<Core::TabBarViewInterface *>(view())->setCurrentIndex(index);
}

void TabBar::renameTab(int index, const QString &text)
{
    dynamic_cast<Core::TabBarViewInterface *>(view())->renameTab(index, text);
}

void TabBar::changeTabIcon(int index, const Icon &icon)
{
    dynamic_cast<Core::TabBarViewInterface *>(view())->changeTabIcon(index, icon);
}

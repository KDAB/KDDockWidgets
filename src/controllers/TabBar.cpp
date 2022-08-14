/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "TabBar.h"
#include "private/Draggable_p.h"
#include "Controller.h"
#include "controllers/Stack.h"
#include "controllers/FloatingWindow.h"
#include "controllers/DockWidget_p.h"
#include "views/TabBarViewInterface.h"
#include "Platform.h"

#include "private/DragController_p.h"
#include "private/Utils_p.h"
#include "Config.h"
#include "kddockwidgets/ViewFactory.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::Controllers;

Controllers::TabBar::TabBar(Stack *tabWidget)
    : Controller(Type::TabBar, Config::self().viewFactory()->createTabBar(this, tabWidget->view()))
    , Draggable(view())
    , m_tabWidget(tabWidget)
{
    view()->init();
}

Controllers::TabBar::~TabBar()
{
}

bool Controllers::TabBar::tabsAreMovable() const
{
    return dynamic_cast<Views::TabBarViewInterface *>(view())->tabsAreMovable();
}

bool Controllers::TabBar::dragCanStart(QPoint pressPos, QPoint pos) const
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
        dynamic_cast<Views::TabBarViewInterface *>(view())->tabAt(view()->mapFromGlobal(pos));
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

Controllers::DockWidget *Controllers::TabBar::dockWidgetAt(int index) const
{
    if (index < 0 || index >= numDockWidgets())
        return nullptr;

    return const_cast<DockWidget *>(m_dockWidgets.value(index));
}

Controllers::DockWidget *Controllers::TabBar::dockWidgetAt(QPoint localPos) const
{
    return dockWidgetAt(dynamic_cast<Views::TabBarViewInterface *>(view())->tabAt(localPos));
}

int TabBar::indexOfDockWidget(const Controllers::DockWidget *dw) const
{
    return m_dockWidgets.indexOf(dw);
}

void TabBar::removeDockWidget(Controllers::DockWidget *dw)
{
    const bool wasCurrent = dw == m_currentDockWidget;
    const int index = m_dockWidgets.indexOf(dw);

    if (wasCurrent) {
        const bool isLast = index == m_dockWidgets.count() - 1;
        const int newCurrentIndex = isLast ? index - 1 : index + 1;
        setCurrentIndex(newCurrentIndex);
    }

    dw->disconnect(this);
    m_dockWidgets.removeOne(dw);
    dynamic_cast<Views::TabBarViewInterface *>(view())->removeDockWidget(dw);
}

bool TabBar::insertDockWidget(int index, Controllers::DockWidget *dw, const QIcon &icon,
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

    return dynamic_cast<Views::TabBarViewInterface *>(view())->insertDockWidget(index, dw, icon,
                                                                                title);
}

std::unique_ptr<WindowBeingDragged> Controllers::TabBar::makeWindow()
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
                return m_tabWidget->makeWindow();
            }
        } else {
            // Case #2. User is dragging on the QTabBar background, not on an actual tab.
            // As Flag_HideTitleBarWhenTabsVisible is set, we let the user drag through the tab
            // widget background.
            return m_tabWidget->makeWindow();
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

bool Controllers::TabBar::isWindow() const
{
    // Same semantics as tab widget, no need to duplicate logic
    return m_tabWidget->isWindow();
}

void Controllers::TabBar::onMousePress(QPoint localPos)
{
    m_lastPressedDockWidget = dockWidgetAt(localPos);
    Group *group = this->group();
    if ((Config::self().flags() & Config::Flag_TitleBarIsFocusable) && !group->isFocused()) {
        // User clicked on a tab which was already focused
        // A tab changing also counts as a change of scope
        group->FocusScope::focus(Qt::MouseFocusReason);
    }
}

void Controllers::TabBar::onMouseDoubleClick(QPoint localPos)
{
    if (DockWidget *dw = dockWidgetAt(localPos))
        dw->setFloating(true);
}

bool Controllers::TabBar::hasSingleDockWidget() const
{
    return numDockWidgets() == 1;
}

int Controllers::TabBar::numDockWidgets() const
{
    return dynamic_cast<Views::TabBarViewInterface *>(view())->numDockWidgets();
}

Controllers::DockWidget *Controllers::TabBar::singleDockWidget() const
{
    return m_tabWidget->singleDockWidget();
}

bool Controllers::TabBar::isMDI() const
{
    Group *f = group();
    return f && f->isMDI();
}

Group *Controllers::TabBar::group() const
{
    return m_tabWidget->group();
}

Stack *TabBar::stack() const
{
    return m_tabWidget;
}

void Controllers::TabBar::moveTabTo(int from, int to)
{
    dynamic_cast<Views::TabBarViewInterface *>(view())->moveTabTo(from, to);
}

QString Controllers::TabBar::text(int index) const
{
    return dynamic_cast<Views::TabBarViewInterface *>(view())->text(index);
}

QRect Controllers::TabBar::rectForTab(int index) const
{
    return dynamic_cast<Views::TabBarViewInterface *>(view())->rectForTab(index);
}

DockWidget *TabBar::currentDockWidget() const
{
    return m_currentDockWidget;
}

void TabBar::setCurrentDockWidget(DockWidget *dw)
{
    if (dw == m_currentDockWidget)
        return;

    m_currentDockWidget = dw;
    setCurrentIndex(indexOfDockWidget(dw));
    Q_EMIT currentDockWidgetChanged(dw);
}

int TabBar::currentIndex() const
{
    if (!m_currentDockWidget)
        return -1;

    return m_dockWidgets.indexOf(m_currentDockWidget);
}

void TabBar::setCurrentIndex(int index)
{
    auto newCurrentDw = dockWidgetAt(index);
    if (newCurrentDw == m_currentDockWidget)
        return;

    m_currentDockWidget = newCurrentDw;
    Q_EMIT currentDockWidgetChanged(newCurrentDw);
    dynamic_cast<Views::TabBarViewInterface *>(view())->setCurrentIndex(index);
}

void TabBar::renameTab(int index, const QString &text)
{
    dynamic_cast<Views::TabBarViewInterface *>(view())->renameTab(index, text);
}

void TabBar::changeTabIcon(int index, const QIcon &icon)
{
    dynamic_cast<Views::TabBarViewInterface *>(view())->changeTabIcon(index, icon);
}

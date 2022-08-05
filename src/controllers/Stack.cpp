/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Stack.h"
#include "Config.h"
#include "kddockwidgets/ViewFactory.h"
#include "private/Logging_p.h"
#include "private/Utils_p.h"
#include "private/WindowBeingDragged_p.h"
#include "DockWidget_p.h"

#include "views/StackViewInterface.h"
#include "controllers/TabBar.h"
#include "controllers/Group.h"
#include "controllers/FloatingWindow.h"

#include <QDebug>
#include <QPointer>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Controllers;

Stack::Stack(Group *group, StackOptions options)
    : Controller(Type::Stack, Config::self().viewFactory()->createStack(this, group->view()))
    , Draggable(view(),
                Config::self().flags()
                    & (Config::Flag_HideTitleBarWhenTabsVisible | Config::Flag_AlwaysShowTabs))
    , m_tabBar(new TabBar(this))
    , m_group(group)
    , m_options(options)
{
    view()->init();
}

Stack::~Stack()
{
    delete m_tabBar;
}

StackOptions Stack::options() const
{
    return m_options;
}

void Stack::setCurrentDockWidget(DockWidget *dw)
{
    setCurrentDockWidget(indexOfDockWidget(dw));
}

bool Stack::isPositionDraggable(QPoint p) const
{
    return dynamic_cast<Views::StackViewInterface *>(view())->isPositionDraggable(p);
}

Controllers::DockWidget *Stack::currentDockWidget() const
{
    return dockwidgetAt(currentIndex());
}

void Stack::addDockWidget(DockWidget *dock)
{
    insertDockWidget(dock, numDockWidgets());
}

bool Stack::insertDockWidget(DockWidget *dock, int index)
{
    Q_ASSERT(dock);
    qCDebug(addwidget) << Q_FUNC_INFO << dock << "; count before=" << numDockWidgets();

    if (index < 0)
        index = 0;
    if (index > numDockWidgets())
        index = numDockWidgets();

    if (contains(dock)) {
        qWarning() << Q_FUNC_INFO << "Refusing to add already existing widget";
        return false;
    }

    QPointer<Group> oldFrame = dock->d->group();
    insertDockWidget(index, dock, dock->icon(IconPlace::TabBar), dock->title());
    setCurrentDockWidget(index);

    if (oldFrame && oldFrame->beingDeletedLater()) {
        // give it a push and delete it immediately.
        // Having too many deleteLater() puts us in an inconsistent state. For example if
        // LayoutSaver::saveState() would to be called while the Frame hadn't been deleted yet it
        // would count with that group unless hacks. Also the unit-tests are full of
        // waitForDeleted() due to deleteLater.

        // Ideally we would just remove the deleteLater from Group.cpp, but QStack::insertTab()
        // would crash, as it accesses the old tab-widget we're stealing from

        delete oldFrame;
    }

    return true;
}

bool Stack::contains(DockWidget *dw) const
{
    return indexOfDockWidget(dw) != -1;
}

Group *Stack::group() const
{
    return m_group;
}

std::unique_ptr<WindowBeingDragged> Stack::makeWindow()
{
    // This is called when using Flag_HideTitleBarWhenTabsVisible
    // For detaching individual tabs, TabBar::makeWindow() is called.

    if (auto fw = view()->rootView()->asFloatingWindowController()) {
        if (fw->hasSingleFrame()) {
            // We're already in a floating window, and it only has 1 dock widget.
            // So there's no detachment to be made, we just move the window.
            return std::unique_ptr<WindowBeingDragged>(new WindowBeingDragged(fw, this));
        }
    }

    QRect r = m_group->view()->geometry();

    const QPoint globalPoint = view()->mapToGlobal(QPoint(0, 0));

    auto floatingWindow = new FloatingWindow(m_group, {});
    r.moveTopLeft(globalPoint);
    floatingWindow->setSuggestedGeometry(r, SuggestedGeometryHint_GeometryIsFromDocked);
    floatingWindow->view()->show();

    return std::unique_ptr<WindowBeingDragged>(new WindowBeingDragged(floatingWindow, this));
}

bool Stack::isWindow() const
{
    if (auto fw = view()->rootView()->asFloatingWindowController()) {
        // Case of dragging via the tab widget when the title bar is hidden
        return fw->hasSingleFrame();
    }

    return false;
}

Controllers::DockWidget *Stack::singleDockWidget() const
{
    if (m_group->hasSingleDockWidget())
        return m_group->dockWidgets().first();

    return nullptr;
}

bool Stack::isMDI() const
{
    return m_group && m_group->isMDI();
}

void Stack::onTabInserted()
{
    m_group->onDockWidgetCountChanged();
}

void Stack::onTabRemoved()
{
    m_group->onDockWidgetCountChanged();
}

void Stack::onCurrentTabChanged(int index)
{
    Q_UNUSED(index);
}

bool Stack::onMouseDoubleClick(QPoint localPos)
{
    // User clicked the empty space of the tab widget and we don't have title bar
    // We float the entire group.

    if (!(Config::self().flags() & Config::Flag_HideTitleBarWhenTabsVisible)
        || tabBar()->dockWidgetAt(localPos))
        return false;

    Group *group = this->group();

    // When using MainWindowOption_HasCentralFrame. The central group is never detachable.
    if (group->isCentralFrame())
        return false;

    if (FloatingWindow *fw = group->floatingWindow()) {
        if (!fw->hasSingleFrame()) {
            makeWindow();
            return true;
        }
    } else if (group->isInMainWindow()) {
        makeWindow();
        return true;
    }

    return false;
}

void Stack::setTabBarAutoHide(bool is)
{
    if (is == m_tabBarAutoHide)
        return;

    m_tabBarAutoHide = is;
    tabBarAutoHideChanged.emit(is);
}

bool Stack::tabBarAutoHide() const
{
    return m_tabBarAutoHide;
}

void Stack::renameTab(int index, const QString &text)
{
    dynamic_cast<Views::StackViewInterface *>(view())->renameTab(index, text);
}

Controllers::TabBar *Stack::tabBar() const
{
    return m_tabBar;
}

int Stack::currentIndex() const
{
    return dynamic_cast<Views::StackViewInterface *>(view())->currentIndex();
}

int Stack::numDockWidgets() const
{
    auto svi = dynamic_cast<Views::StackViewInterface *>(view());
    Q_ASSERT(svi);
    return svi->numDockWidgets();
}

void Stack::changeTabIcon(int index, const QIcon &icon)
{
    dynamic_cast<Views::StackViewInterface *>(view())->changeTabIcon(index, icon);
}

Controllers::DockWidget *Stack::dockwidgetAt(int index) const
{
    return dynamic_cast<Views::StackViewInterface *>(view())->dockwidgetAt(index);
}

int Stack::indexOfDockWidget(const DockWidget *dw) const
{
    return dynamic_cast<Views::StackViewInterface *>(view())->indexOfDockWidget(dw);
}

void Stack::removeDockWidget(DockWidget *dw)
{
    dynamic_cast<Views::StackViewInterface *>(view())->removeDockWidget(dw);
}

bool Stack::insertDockWidget(int index, DockWidget *dw, const QIcon &icon, const QString &title)
{
    return dynamic_cast<Views::StackViewInterface *>(view())->insertDockWidget(index, dw, icon,
                                                                               title);
}

void Stack::setCurrentDockWidget(int index)
{
    dynamic_cast<Views::StackViewInterface *>(view())->setCurrentDockWidget(index);
}

void Stack::setDocumentMode(bool is)
{
    dynamic_cast<Views::StackViewInterface *>(view())->setDocumentMode(is);
}

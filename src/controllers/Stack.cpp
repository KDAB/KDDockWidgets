/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Stack.h"
#include "Config.h"
#include "views_qtwidgets/Stack_qtwidgets.h"
#include "kddockwidgets/FrameworkWidgetFactory.h"
#include "private/Logging_p.h"
#include "private/Utils_p.h"
#include "private/WindowBeingDragged_p.h"
#include "DockWidget_p.h"

#include "controllers/TabBar.h"
#include "controllers/Frame.h"
#include "controllers/FloatingWindow.h"

#include <QDebug>
#include <QTabBar> // TODO Remove
#include <qobject.h>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Controllers;

Stack::Stack(Frame *frame, TabWidgetOptions options)
    : Controller(Config::self().frameworkWidgetFactory()->createTabWidget(this, frame))
    , Draggable(view()->asQWidget(), Config::self().flags() & (Config::Flag_HideTitleBarWhenTabsVisible | Config::Flag_AlwaysShowTabs))
    , m_tabBar(new TabBar(this))
    , m_frame(frame)
    , m_options(options)
{
    qobject_cast<Views::Stack_qtwidgets *>(view()->asQWidget())->init();
}

Stack::~Stack()
{
    delete m_tabBar;
}

TabWidgetOptions Stack::options() const
{
    return m_options;
}

void Stack::setCurrentDockWidget(DockWidgetBase *dw)
{
    setCurrentDockWidget(indexOfDockWidget(dw));
}

bool Stack::isPositionDraggable(QPoint p) const // TODO: Move to view
{
    auto view = qobject_cast<Views::Stack_qtwidgets *>(this->view()->asQWidget()); // TODO
    if (view->tabPosition() != QTabWidget::North) { // TODO
        qWarning() << Q_FUNC_INFO << "Not implemented yet. Only North is supported";
        return false;
    }

    return p.y() >= 0 && p.y() <= view->tabBar()->height();
}

DockWidgetBase *Stack::currentDockWidget() const
{
    return dockwidgetAt(currentIndex());
}

void Stack::addDockWidget(DockWidgetBase *dock)
{
    insertDockWidget(dock, numDockWidgets());
}

bool Stack::insertDockWidget(DockWidgetBase *dock, int index)
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

    QPointer<Frame> oldFrame = dock->d->frame();
    insertDockWidget(index, dock, dock->icon(DockWidgetBase::IconPlace::TabBar), dock->title());
    setCurrentDockWidget(index);

    if (oldFrame && oldFrame->beingDeletedLater()) {
        // give it a push and delete it immediately.
        // Having too many deleteLater() puts us in an inconsistent state. For example if LayoutSaver::saveState()
        // would to be called while the Frame hadn't been deleted yet it would count with that frame unless hacks.
        // Also the unit-tests are full of waitForDeleted() due to deleteLater.

        // Ideally we would just remove the deleteLater from frame.cpp, but QStack::insertTab()
        // would crash, as it accesses the old tab-widget we're stealing from

        delete oldFrame;
    }

    return true;
}

bool Stack::contains(DockWidgetBase *dw) const
{
    return indexOfDockWidget(dw) != -1;
}

Frame *Stack::frame() const
{
    return m_frame;
}

std::unique_ptr<WindowBeingDragged> Stack::makeWindow()
{
    // This is called when using Flag_HideTitleBarWhenTabsVisible
    // For detaching individual tabs, TabBar::makeWindow() is called.
    if (auto view = qobject_cast<Views::FloatingWindow_qtwidgets *>(asWidget()->window())) {
        if (view->floatingWindow()->hasSingleFrame()) {
            // We're already in a floating window, and it only has 1 dock widget.
            // So there's no detachment to be made, we just move the window.
            return std::unique_ptr<WindowBeingDragged>(new WindowBeingDragged(view->floatingWindow(), this));
        }
    }

    QRect r = m_frame->view()->geometry();

    const QPoint globalPoint = view()->mapToGlobal(QPoint(0, 0));

    auto floatingWindow = new FloatingWindow(m_frame, {});
    r.moveTopLeft(globalPoint);
    floatingWindow->setSuggestedGeometry(r, SuggestedGeometryHint_GeometryIsFromDocked);
    floatingWindow->view()->show();

    return std::unique_ptr<WindowBeingDragged>(new WindowBeingDragged(floatingWindow, this));
}

bool Stack::isWindow() const
{
    if (auto view = qobject_cast<Views::FloatingWindow_qtwidgets *>(asWidget()->window())) {
        // Case of dragging via the tab widget when the title bar is hidden
        return view->floatingWindow()->hasSingleFrame();
    }

    return false;
}

DockWidgetBase *Stack::singleDockWidget() const
{
    if (m_frame->hasSingleDockWidget())
        return m_frame->dockWidgets().first();

    return nullptr;
}

bool Stack::isMDI() const
{
    return m_frame && m_frame->isMDI();
}

void Stack::onTabInserted()
{
    m_frame->onDockWidgetCountChanged();
}

void Stack::onTabRemoved()
{
    m_frame->onDockWidgetCountChanged();
}

void Stack::onCurrentTabChanged(int index)
{
    Q_UNUSED(index);
}

bool Stack::onMouseDoubleClick(QPoint localPos)
{
    // User clicked the empty space of the tab widget and we don't have title bar
    // We float the entire frame.

    if (!(Config::self().flags() & Config::Flag_HideTitleBarWhenTabsVisible) || tabBar()->dockWidgetAt(localPos))
        return false;

    Frame *frame = this->frame();

    // When using MainWindowOption_HasCentralFrame. The central frame is never detachable.
    if (frame->isCentralFrame())
        return false;

    if (FloatingWindow *fw = frame->floatingWindow()) {
        if (!fw->hasSingleFrame()) {
            makeWindow();
            return true;
        }
    } else if (frame->isInMainWindow()) {
        makeWindow();
        return true;
    }

    return false;
}

void Stack::setTabBarAutoHide(bool is)
{
    // TODO
    qobject_cast<Views::Stack_qtwidgets *>(view()->asQWidget())->setTabBarAutoHide(is);
}

void Stack::renameTab(int index, const QString &text)
{
    // TODO
    qobject_cast<Views::Stack_qtwidgets *>(view()->asQWidget())->renameTab(index, text);
}

Controllers::TabBar *Stack::tabBar() const
{
    return m_tabBar;
}

int Stack::currentIndex() const
{
    // TODO
    return qobject_cast<Views::Stack_qtwidgets *>(view()->asQWidget())->currentIndex();
}

int Stack::numDockWidgets() const
{
    // TODO
    return qobject_cast<Views::Stack_qtwidgets *>(view()->asQWidget())->numDockWidgets();
}

void Stack::changeTabIcon(int index, const QIcon &icon)
{
    // TODO
    qobject_cast<Views::Stack_qtwidgets *>(view()->asQWidget())->changeTabIcon(index, icon);
}

DockWidgetBase *Stack::dockwidgetAt(int index) const
{
    // TODO
    return qobject_cast<Views::Stack_qtwidgets *>(view()->asQWidget())->dockwidgetAt(index);
}

int Stack::indexOfDockWidget(const DockWidgetBase *dw) const
{
    // TODO
    return qobject_cast<Views::Stack_qtwidgets *>(view()->asQWidget())->indexOfDockWidget(dw);
}

void Stack::removeDockWidget(DockWidgetBase *dw)
{
    qobject_cast<Views::Stack_qtwidgets *>(view()->asQWidget())->removeDockWidget(dw);
}

bool Stack::insertDockWidget(int index, DockWidgetBase *dw, const QIcon &icon, const QString &title)
{
    return qobject_cast<Views::Stack_qtwidgets *>(view()->asQWidget())->insertDockWidget(index, dw, icon, title);
}

void Stack::setCurrentDockWidget(int index)
{
    return qobject_cast<Views::Stack_qtwidgets *>(view()->asQWidget())->setCurrentDockWidget(index);
}

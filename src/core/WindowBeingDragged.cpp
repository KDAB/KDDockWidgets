/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "kddockwidgets/KDDockWidgets.h"
#include "WindowBeingDragged_p.h"
#include "DragController_p.h"
#include "Logging_p.h"
#include "Utils_p.h"

#include "kddockwidgets/core/TitleBar.h"
#include "kddockwidgets/core/Stack.h"
#include "kddockwidgets/core/Group.h"
#include "kddockwidgets/core/Platform.h"
#include "kddockwidgets/core/Layout.h"
#include "kddockwidgets/core/FloatingWindow.h"

#ifdef QT_GUI_LIB
#include <QPainter>
#endif

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;

static Draggable *bestDraggable(Draggable *draggable)
{
    if (!draggable)
        return nullptr;

    // When de detach a title bar it will get hidden and we only the title bar of the FloatingWindow
    // is visible
    /// Apparently that causes problems with grabbing the mouse, so instead use a visible draggable.
    // grabbing mouse on an hidden window works usually, it's some edge case on Windows with MFC.
    if (auto titleBar = draggable->asView()->asTitleBarController()) {
        if (titleBar->isVisible())
            return draggable;

        auto fw = titleBar->window()->asFloatingWindowController();
        if (!fw) // defensive, doesn't happen
            return draggable;

        if (fw->titleBar() == titleBar) {
            // Defensive, doesn't happen
            return draggable;
        } else {
            if (KDDockWidgets::usesNativeTitleBar())
                return fw;
            return fw->titleBar();
        }
    } else {
        return draggable;
    }
}

WindowBeingDragged::WindowBeingDragged(FloatingWindow *fw, Draggable *draggable)
    : m_floatingWindow(fw)
    , m_draggable(bestDraggable(draggable))
    , m_draggableView(m_draggable ? m_draggable->asView() : nullptr)
    , m_guard(m_draggableView)
{
    init();
    updateTransparency(/*enable=*/true);
}

WindowBeingDragged::WindowBeingDragged(Draggable *draggable)
    : m_draggable(draggable)
    , m_draggableView(m_draggable->asView())
    , m_guard(m_draggableView)
{
    if (!isWayland()) {
        spdlog::error("Wrong ctor called."); // Doesn't happen
        Q_ASSERT(false);
        return;
    }
}

#ifdef DOCKS_DEVELOPER_MODE

// Just used by tests
WindowBeingDragged::WindowBeingDragged(FloatingWindow *fw)
    : m_floatingWindow(fw)
    , m_draggable(nullptr)
    , m_guard(nullptr)
{
}

#endif

WindowBeingDragged::~WindowBeingDragged()
{
    grabMouse(false);
    updateTransparency(/*enable=*/false);
}

void WindowBeingDragged::init()
{
    Q_ASSERT(m_floatingWindow);
    grabMouse(true);
    m_floatingWindow->view()->raise();
}

void WindowBeingDragged::updateTransparency(bool enable)
{
    // Wayland doesn't support setting opacity
    if (isWayland() || !m_floatingWindow)
        return;

    qreal opacity = Config::self().draggedWindowOpacity();
    const bool transparencySupported = !qIsNaN(opacity) && !qFuzzyCompare(1.0, opacity);
    if (transparencySupported) {
        // We're using transparency, set it or unset it:
        if (enable) {
            if (Config::self().transparencyOnlyOverDropIndicator()) {
                if (DragController::instance()->currentDropLocation() == DropLocation_None)
                    opacity = 1;
            }
        } else {
            opacity = 1;
        }

        m_floatingWindow->view()->setWindowOpacity(opacity);
    }
}

void WindowBeingDragged::grabMouse(bool grab)
{
    if (!m_guard)
        return;

    spdlog::debug("WindowBeingDragged: fw={}, grab={}, draggableView={} ", ( void * )m_floatingWindow, grab, ( void * )m_draggableView);

    if (grab)
        DragController::instance()->grabMouseFor(m_draggableView);
    else
        DragController::instance()->releaseMouse(m_draggableView);
}

QStringList WindowBeingDragged::affinities() const
{
    return m_floatingWindow ? m_floatingWindow->affinities() : QStringList();
}

QSize WindowBeingDragged::size() const
{
    if (m_floatingWindow)
        return m_floatingWindow->size();

    return QSize();
}

QSize WindowBeingDragged::minSize() const
{
    if (m_floatingWindow)
        return m_floatingWindow->layout()->layoutMinimumSize();

    return {};
}

QSize WindowBeingDragged::maxSize() const
{
    if (m_floatingWindow)
        return m_floatingWindow->layout()->layoutMaximumSizeHint();

    return {};
}

bool WindowBeingDragged::contains(Layout *layout) const
{
    if (!layout)
        return false;

    if (m_floatingWindow)
        return m_floatingWindow->layout() == layout;

    if (auto fw = m_draggableView->rootView()->asFloatingWindowController()) {
        // We're not dragging via the floating window itself, but via the tab bar. Still might
        // represent floating window though.
        return fw->layout() == layout && fw->hasSingleFrame();
    }

    return false;
}

QVector<DockWidget *> WindowBeingDragged::dockWidgets() const
{
    if (m_floatingWindow)
        return m_floatingWindow->dockWidgets();

    return {};
}

Draggable *WindowBeingDragged::draggable() const
{
    return m_draggable;
}

Pixmap WindowBeingDragged::pixmap() const
{
    return {};
}

FloatingWindow *WindowBeingDragged::floatingWindow() const
{
    return m_floatingWindow;
}

Core::View *WindowBeingDragged::floatingWindowView() const
{
    if (m_floatingWindow)
        return m_floatingWindow->view();

    return nullptr;
}

WindowBeingDraggedWayland::WindowBeingDraggedWayland(Draggable *draggable)
    : WindowBeingDragged(draggable)
{
    if (!isWayland()) {
        // Doesn't happen
        spdlog::error("This CTOR is only called on Wayland");
        Q_ASSERT(false);
        return;
    }

    if (auto tb = draggable->asView()->asTitleBarController()) {
        if (auto fw = tb->floatingWindow()) {
            // case #1: we're dragging the whole floating window by its titlebar
            m_floatingWindow = fw;
        } else if (Group *group = tb->group()) {
            m_group = group;
        } else {
            spdlog::error("Shouldn't happen. TitleBar of what ?");
        }
    } else if (auto fw = draggable->asView()->asFloatingWindowController()) {
        // case #2: the floating window itself is the draggable, happens on platforms that support
        // native dragging. Not the case for Wayland. But adding this case for completeness.
        m_floatingWindow = fw;
    } else if (auto tabBar = draggable->asView()->asTabBarController()) {
        if (Platform::instance()->isQtWidgets())
            m_dockWidget = tabBar->currentDockWidget();
    } else if (auto stack = draggable->asView()->asStackController()) {
        if (Platform::instance()->isQtWidgets())
            m_group = stack->group();
    } else {
        spdlog::error("Unknown draggable {} please fix)", ( void * )draggable);
    }
}

WindowBeingDraggedWayland::~WindowBeingDraggedWayland()
{
}

Pixmap WindowBeingDraggedWayland::pixmap() const
{
#ifdef QT_GUI_LIB
    QPixmap pixmap(size());
    QPainter p(&pixmap);
    p.setOpacity(0.7);

    if (m_floatingWindow) {
        m_floatingWindow->view()->render(&p);
    } else if (m_group) {
        m_group->view()->render(&p);
    } else if (m_dockWidget) {
        m_dockWidget->view()->render(&p);
    }

    return pixmap;
#else
    // Wayland not support on our flutter frontend yet
    return {};
#endif
}

QStringList WindowBeingDraggedWayland::affinities() const
{
    if (m_floatingWindow)
        return WindowBeingDragged::affinities();
    else if (m_group)
        return m_group->affinities();
    else if (m_dockWidget)
        return { m_dockWidget->affinities() };

    return {};
}

QVector<DockWidget *> WindowBeingDraggedWayland::dockWidgets() const
{
    if (m_floatingWindow)
        return WindowBeingDragged::dockWidgets();
    else if (m_group)
        return m_group->dockWidgets();
    else if (m_dockWidget)
        return { m_dockWidget };

    return {};
}

QSize WindowBeingDraggedWayland::size() const
{
    if (m_floatingWindow)
        return WindowBeingDragged::size();
    else if (m_group)
        return m_group->size();
    else if (m_dockWidget)
        return m_dockWidget->size();

    spdlog::error("Unknown size, shouldn't happen");
    return QSize();
}

QSize WindowBeingDraggedWayland::minSize() const
{
    if (m_floatingWindow) {
        return WindowBeingDragged::minSize();
    } else if (m_group) {
        return m_group->view()->minSize();
    } else if (m_dockWidget) {
        return m_dockWidget->view()->minSize();
    }

    spdlog::error("Unknown minSize, shouldn't happen");
    return {};
}

QSize WindowBeingDraggedWayland::maxSize() const
{
    if (m_floatingWindow) {
        return WindowBeingDragged::maxSize();
    } else if (m_group) {
        return m_group->view()->maxSizeHint();
    } else if (m_dockWidget) {
        return m_dockWidget->view()->maxSizeHint();
    }

    spdlog::error("Unknown maxSize, shouldn't happen");
    return {};
}

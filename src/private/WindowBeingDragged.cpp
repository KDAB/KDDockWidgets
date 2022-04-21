/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "KDDockWidgets.h"
#include "WindowBeingDragged_p.h"
#include "DragController_p.h"
#include "LayoutWidget_p.h"
#include "Logging_p.h"
#include "Utils_p.h"

#include "controllers/TitleBar.h"
#include "controllers/Stack.h"
#include "controllers/Frame.h"

#include <QPixmap>
#include <QPainter>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Controllers;

static Draggable *bestDraggable(Draggable *draggable)
{
    if (!draggable)
        return nullptr;

    // When de detach a title bar it will get hidden and we only the title bar of the FloatingWindow is visible
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

WindowBeingDragged::WindowBeingDragged(Controllers::FloatingWindow *fw, Draggable *draggable)
    : m_floatingWindow(fw)
    , m_draggable(bestDraggable(draggable))
    , m_draggableWidget(m_draggable ? m_draggable->asView() : nullptr)
    , m_guard(m_draggableWidget ? m_draggableWidget->asQObject() : nullptr)
{
    init();

    if (!isWayland()) { // Wayland doesn't support setting opacity
        // Set opacity while dragging, if needed
        const qreal opacity = Config::self().draggedWindowOpacity();
        if (!qIsNaN(opacity) && !qFuzzyCompare(1.0, opacity))
            fw->view()->setWindowOpacity(opacity);
    }
}

WindowBeingDragged::WindowBeingDragged(Draggable *draggable)
    : m_draggable(draggable)
    , m_draggableWidget(m_draggable->asView())
    , m_guard(m_draggableWidget ? m_draggableWidget->asQObject() : nullptr)
{
    if (!isWayland()) {
        qWarning() << Q_FUNC_INFO << "Wrong ctor called."; // Doesn't happen
        Q_ASSERT(false);
        return;
    }
}

#ifdef DOCKS_DEVELOPER_MODE

// Just used by tests
WindowBeingDragged::WindowBeingDragged(Controllers::FloatingWindow *fw)
    : m_floatingWindow(fw)
    , m_draggable(nullptr)
{
}

#endif

WindowBeingDragged::~WindowBeingDragged()
{
    grabMouse(false);

    if (!isWayland()) { // Wayland doesn't support setting opacity
        // Restore opacity to fully opaque if needed
        const qreal opacity = Config::self().draggedWindowOpacity();
        if (!qIsNaN(opacity) && !qFuzzyCompare(1.0, opacity))
            m_floatingWindow->view()->setWindowOpacity(1);
    }
}

void WindowBeingDragged::init()
{
    Q_ASSERT(m_floatingWindow);
    grabMouse(true);
    m_floatingWindow->view()->raise();
}

void WindowBeingDragged::grabMouse(bool grab)
{
    if (!m_guard)
        return;

    qCDebug(hovering) << "WindowBeingDragged: grab " << m_floatingWindow << grab << m_draggableWidget;
    if (grab)
        DragController::instance()->grabMouseFor(m_draggableWidget);
    else
        DragController::instance()->releaseMouse(m_draggableWidget);
}

QStringList WindowBeingDragged::affinities() const
{
    return m_floatingWindow ? m_floatingWindow->affinities()
                            : QStringList();
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
        return m_floatingWindow->layoutWidget()->layoutMinimumSize();

    return {};
}

QSize WindowBeingDragged::maxSize() const
{
    if (m_floatingWindow)
        return m_floatingWindow->layoutWidget()->layoutMaximumSizeHint();

    return {};
}

bool WindowBeingDragged::contains(LayoutWidget *layoutWidget) const
{
    if (!layoutWidget)
        return false;

    if (m_floatingWindow)
        return m_floatingWindow->layoutWidget() == layoutWidget;

    if (auto fw = m_draggableWidget->window()->asFloatingWindowController()) {
        // We're not dragging via the floating window itself, but via the tab bar. Still might represent floating window though.
        return fw->layoutWidget() == layoutWidget && fw->hasSingleFrame();
    }

    return false;
}

QVector<DockWidgetBase *> WindowBeingDragged::dockWidgets() const
{
    if (m_floatingWindow)
        return m_floatingWindow->dockWidgets();

    return {};
}

Draggable *WindowBeingDragged::draggable() const
{
    return m_draggable;
}

WindowBeingDraggedWayland::WindowBeingDraggedWayland(Draggable *draggable)
    : WindowBeingDragged(draggable)
{
    if (!isWayland()) {
        // Doesn't happen
        qWarning() << Q_FUNC_INFO << "This CTOR is only called on Wayland";
        Q_ASSERT(false);
        return;
    }

    if (auto tb = draggable->asView()->asTitleBarController()) {
        if (auto fw = tb->floatingWindow()) {
            // case #1: we're dragging the whole floating window by its titlebar
            m_floatingWindow = fw;
        } else if (Controllers::Frame *frame = tb->frame()) {
            m_frame = frame;
        } else {
            qWarning() << Q_FUNC_INFO << "Shouldn't happen. TitleBar of what ?";
        }
    } else if (auto fw = draggable->asView()->asFloatingWindowController()) {
        // case #2: the floating window itself is the draggable, happens on platforms that support
        // native dragging. Not the case for Wayland. But adding this case for completeness.
        m_floatingWindow = fw;
#ifdef KDDOCKWIDGETS_QTWIDGETS
    } else if (auto tabBar = draggable->asView()->asTabBarController()) {
        m_dockWidget = tabBar->currentDockWidget();
    } else if (auto stack = draggable->asView()->asStackController()) {
        m_frame = stack->frame();
#endif
    } else {
        qWarning() << "Unknown draggable" << draggable << "please fix";
    }
}

WindowBeingDraggedWayland::~WindowBeingDraggedWayland()
{
}

QPixmap WindowBeingDraggedWayland::pixmap() const
{
    QPixmap pixmap(size());
    QPainter p(&pixmap);
    p.setOpacity(0.7);

    if (m_floatingWindow) {
        m_floatingWindow->view()->asQWidget()->render(&p);
    } else if (m_frame) {
        m_frame->view()->asQWidget()->render(&p);
    } else if (m_dockWidget) {
        m_dockWidget->view()->asQWidget()->render(&p);
    }

    return pixmap;
}

QStringList WindowBeingDraggedWayland::affinities() const
{
    if (m_floatingWindow)
        return WindowBeingDragged::affinities();
    else if (m_frame)
        return m_frame->affinities();
    else if (m_dockWidget)
        return { m_dockWidget->affinities() };

    return {};
}

QVector<DockWidgetBase *> WindowBeingDraggedWayland::dockWidgets() const
{
    if (m_floatingWindow)
        return WindowBeingDragged::dockWidgets();
    else if (m_frame)
        return m_frame->dockWidgets();
    else if (m_dockWidget)
        return { m_dockWidget };

    return {};
}

QSize WindowBeingDraggedWayland::size() const
{
    if (m_floatingWindow)
        return WindowBeingDragged::size();
    else if (m_frame)
        return m_frame->size();
    else if (m_dockWidget)
        return m_dockWidget->size();

    qWarning() << Q_FUNC_INFO << "Unknown size, shouldn't happen";
    return QSize();
}

QSize WindowBeingDraggedWayland::minSize() const
{
    if (m_floatingWindow) {
        return WindowBeingDragged::minSize();
    } else if (m_frame) {
        return m_frame->view()->minSize();
    } else if (m_dockWidget) {
        return m_dockWidget->view()->minSize();
    }

    qWarning() << Q_FUNC_INFO << "Unknown minSize, shouldn't happen";
    return {};
}

QSize WindowBeingDraggedWayland::maxSize() const
{
    if (m_floatingWindow) {
        return WindowBeingDragged::maxSize();
    } else if (m_frame) {
        return m_frame->view()->maxSizeHint();
    } else if (m_dockWidget) {
        return m_dockWidget->view()->maximumSize();
    }

    qWarning() << Q_FUNC_INFO << "Unknown maxSize, shouldn't happen";
    return {};
}

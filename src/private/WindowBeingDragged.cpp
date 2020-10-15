/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "WindowBeingDragged_p.h"
#include "DragController_p.h"
#include "Logging_p.h"
#include "Utils_p.h"
#include "DropArea_p.h"

#include <QPixmap>

using namespace KDDockWidgets;

static Draggable* bestDraggable(Draggable *draggable)
{
    if (!draggable)
        return nullptr;

    // When de detach a title bar it will get hidden and we only the title bar of the FloatingWindow is visible
    /// Apparently that causes problems with grabbing the mouse, so instead use a visible draggable.
    // grabbing mouse on an hidden window works usually, it's some edge case on Windows with MFC.
    if (auto titleBar = qobject_cast<TitleBar*>(draggable->asWidget())) {
        if (titleBar->isVisible())
            return draggable;

        auto fw = qobject_cast<FloatingWindow*>(titleBar->window());
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
    , m_draggable(bestDraggable(draggable)->asWidget())
    , m_affinities(fw->affinities())
{
    init();

    if (!isWayland()) { // Wayland doesn't support setting opacity
        // Set opacity while dragging, if needed
        const qreal opacity = Config::self().draggedWindowOpacity();
        if (!qIsNaN(opacity) && !qFuzzyCompare(1.0, opacity))
            fw->setWindowOpacity(opacity);
    }
}
#if DOCKS_DEVELOPER_MODE

// Just used by tests
WindowBeingDragged::WindowBeingDragged(FloatingWindow *fw)
    : m_floatingWindow(fw)
    , m_draggable(nullptr)
    , m_affinities(fw->affinities())
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
            m_floatingWindow->setWindowOpacity(1);
    }
}

void WindowBeingDragged::init()
{
    Q_ASSERT(m_floatingWindow);
    grabMouse(true);
    m_floatingWindow->raise();
}

void WindowBeingDragged::grabMouse(bool grab)
{
    if (!m_draggable)
        return;

    qCDebug(hovering) << "WindowBeingDragged: grab " << m_floatingWindow << grab << m_draggable;
    if (grab)
        DragController::instance()->grabMouseFor(m_draggable);
    else
        DragController::instance()->releaseMouse(m_draggable);
}

QStringList WindowBeingDragged::affinities() const
{
    return m_affinities;
}

QSize WindowBeingDragged::size() const
{
    if (m_floatingWindow)
        return m_floatingWindow->size();

    return QSize();
}

QSize WindowBeingDragged::minSize() const
{
    if (m_floatingWindow) {
        Layouting::ItemContainer *root = m_floatingWindow->dropArea()->rootItem();
        return root->minSize();
    }

    return {};
}

QSize WindowBeingDragged::maxSize() const
{
    if (m_floatingWindow) {
        Layouting::ItemContainer *root = m_floatingWindow->dropArea()->rootItem();
        return root->maxSizeHint();
    }

    return {};
}

bool WindowBeingDragged::contains(DropArea *dropArea) const
{
    if (!dropArea)
        return false;

    return m_floatingWindow && m_floatingWindow->dropArea() == dropArea;
}

QPixmap WindowBeingDragged::pixmap() const
{
    QPixmap pixmap(size());

    if (m_floatingWindow)
        m_floatingWindow->render(&pixmap);

    return pixmap;
}

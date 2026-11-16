/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "DragControllerWayland_p.h"
#include "core/Logging_p.h"
#include "core/ScopedValueRollback_p.h"
#include "kddockwidgets/core/Platform.h"
#include "kddockwidgets/core/DropArea.h"
#include "Config.h"

#ifdef KDDW_HAS_WAYLAND_TOPLEVEL_DRAG
#include "core/Utils_p.h"
#include "kddockwidgets/core/FloatingWindow.h"
#include "qtcommon/Window_p.h"

#include <QDataStream>
#include <QWindow>

#include <QtGui/private/qguiapplication_p.h>
#include <QtWaylandClient/private/qwaylanddisplay_p.h>
#include <QtWaylandClient/private/qwaylandintegration_p.h>
#endif

using namespace KDDockWidgets::Core;

StateDraggingWayland::StateDraggingWayland(DragController *parent)
    : StateDragging(parent)
{
}

StateDraggingWayland::~StateDraggingWayland()
{
}

void StateDraggingWayland::onEntry()
{
    KDDW_DEBUG("StateDraggingWayland entered");

    if (DragController::instance()->m_inQDrag) {
        // Maybe we can exit the state due to the nested event loop of QDrag::Exec();
        KDDW_ERROR("Impossible!");
        return;
    }

    ScopedValueRollback guard(DragController::instance()->m_inQDrag, true);

    auto mimeData = new WaylandMimeData();
    Drag drag(this);
    drag.setMimeData(mimeData);

#ifdef KDDW_HAS_WAYLAND_TOPLEVEL_DRAG
    // Checked here and not when creating the state, as the DragController can be created before the
    // flags are set. QtQuick's Platform creates it, for example.
    if (Config::self().flags() & Config::Flag_WaylandToplevelDrag) {
        if (!setupToplevelDrag(mimeData)) {
            q->dragCanceled.emit();
            return;
        }
    } else
#endif
    {
        q->m_windowBeingDragged =
            std::unique_ptr<WindowBeingDragged>(new WindowBeingDraggedWayland(q->m_draggable));
        drag.setPixmap(q->m_windowBeingDragged->pixmap());
    }

    Platform::instance()->installGlobalEventFilter(q);
    KDDW_DEBUG("Started QDrag");
    const Qt::DropAction result = drag.exec();
    KDDW_DEBUG("QDrag finished with result={}", int(result));

    Platform::instance()->removeGlobalEventFilter(q);
    // If we're still dragging then KDDW didn't get the drop. Either the drag was cancelled, or the
    // drop was accepted by someone else, like the desktop or another application
    if (result == Qt::IgnoreAction || isActiveState())
        q->dragCanceled.emit();
}

bool StateDraggingWayland::handleMouseButtonRelease(QPoint /*globalPos*/)
{
    KDDW_DEBUG(Q_FUNC_INFO);
    q->dragCanceled.emit();
    return true;
}

bool StateDraggingWayland::handleMouseMove(QPoint)
{
    // Wayland uses QDrag to drag stuff while other platforms use mouse.
    // So override handleMouseMove() just so the regular mouse stuff doesn't run.

    return false;
}

bool StateDraggingWayland::handleDragEnter(DragMoveEvent *ev, DropArea *dropArea, QPoint globalEventPos)
{
    auto mimeData = object_cast<const WaylandMimeData *>(ev->mimeData());
    if (!mimeData || !q->m_windowBeingDragged)
        return false; // Not for us, some other user drag.

    if (q->m_windowBeingDragged->contains(dropArea)) {
        ev->ignore();
        return true;
    }

    dropArea->hover(q->m_windowBeingDragged.get(), globalEventPos);

    ev->accept();
    return true;
}

bool StateDraggingWayland::handleDragLeave(DropArea *dropArea)
{
    KDDW_DEBUG(Q_FUNC_INFO);
    dropArea->removeHover();
    return true;
}

bool StateDraggingWayland::handleDrop(DropEvent *ev, DropArea *dropArea, QPoint globalEventPos)
{
    KDDW_DEBUG(Q_FUNC_INFO);
    auto mimeData = object_cast<const WaylandMimeData *>(ev->mimeData());
    if (!mimeData || !q->m_windowBeingDragged)
        return false; // Not for us, some other user drag.

    if (dropArea->drop(q->m_windowBeingDragged.get(), globalEventPos)) {
        ev->setDropAction(Qt::MoveAction);
        ev->accept();
        q->dropped.emit();
    } else {
        q->dragCanceled.emit();
    }

    dropArea->removeHover();
    return true;
}

bool StateDraggingWayland::handleDragMove(DragMoveEvent *ev, DropArea *dropArea, QPoint globalEventPos)
{
    KDDW_DEBUG("StateDraggingWayland::handleDragMove");

    auto mimeData = object_cast<const WaylandMimeData *>(ev->mimeData());
    if (!mimeData || !q->m_windowBeingDragged) {
        KDDW_DEBUG("StateDraggingWayland::handleDragMove. Early bailout hasMimeData={} windowBeingDragged={}", mimeData != nullptr, bool(q->m_windowBeingDragged));
        return false; // Not for us, some other user drag.
    }

    // Without accepting, the drop is refused on release
    ev->setAccepted(dropArea->hover(q->m_windowBeingDragged.get(), globalEventPos) != DropLocation_None);

    return true;
}

#ifdef KDDW_HAS_WAYLAND_TOPLEVEL_DRAG

bool StateDraggingWayland::setupToplevelDrag(QMimeData *mimeData)
{
    // Where the window was grabbed, relative to the window the drag started in. From the global
    // position, as Draggable::mapToWindow() doesn't account for margins, which QtQuick's floating
    // windows have. Before makeWindow(), which can move the draggable to another window.
    Point offset = q->m_offset;
    if (auto window = q->m_draggable->asView()->window())
        offset = window->mapFromGlobal(q->m_pressPos);

    q->m_windowBeingDragged = q->m_draggable->makeWindow();
    if (!q->m_windowBeingDragged) {
        KDDW_ERROR("StateDraggingWayland: Failed to create window");
        return false;
    }

    auto fw = q->m_windowBeingDragged->floatingWindow();
    if (!fw) {
        KDDW_ERROR("StateDraggingWayland: No FloatingWindow");
        return false;
    }

    auto window = fw->view()->window();
    if (!window) {
        KDDW_ERROR("StateDraggingWayland: No window");
        return false;
    }

    auto qtWindow = static_cast<QtCommon::Window *>(window.get())->qtWindow();
    if (!qtWindow) {
        KDDW_ERROR("StateDraggingWayland: No QWindow");
        return false;
    }

    // The window the drag started in can be wider than the new one. Like StateDragging::onEntry(),
    // keep the pointer over it.
    if (offset.x() > fw->width())
        offset.setX(fw->width() / 2);

    auto serialize = [](const auto &object) {
        QByteArray data;
        QDataStream dataStream(&data, QIODevice::WriteOnly);
        dataStream << object;
        return data;
    };

    mimeData->setData(QStringLiteral("application/x-qt-mainwindowdrag-window"),
                      serialize(reinterpret_cast<qintptr>(qtWindow))); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
    mimeData->setData(QStringLiteral("application/x-qt-mainwindowdrag-position"), serialize(offset));

    return true;
}

#endif

bool KDDockWidgets::Core::isWaylandToplevelDragSupported()
{
#ifdef KDDW_HAS_WAYLAND_TOPLEVEL_DRAG
    if (!isWayland())
        return false;

    auto integration = static_cast<QtWaylandClient::QWaylandIntegration *>(QGuiApplicationPrivate::platformIntegration());
    return integration->display()->hasRegistryGlobal(u"xdg_toplevel_drag_manager_v1");
#else
    return false;
#endif
}

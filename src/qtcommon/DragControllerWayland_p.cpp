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
#include "kddockwidgets/core/FloatingWindow.h"
#include "qtcommon/Window_p.h"
#include "Config.h"

#include <QWindow>
#include <QDataStream>

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
    q->m_windowBeingDragged =
        std::unique_ptr<WindowBeingDragged>(new WindowBeingDraggedWayland(q->m_draggable));

    auto mimeData = new WaylandMimeData();
    Drag drag(this);
    drag.setMimeData(mimeData);
    drag.setPixmap(q->m_windowBeingDragged->pixmap());

    Platform::instance()->installGlobalEventFilter(q);
    KDDW_DEBUG("Started QDrag");
    const Qt::DropAction result = drag.exec();
    KDDW_DEBUG("QDrag finished with result={}", int(result));

    Platform::instance()->removeGlobalEventFilter(q);
    if (result == Qt::IgnoreAction)
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

    dropArea->hover(q->m_windowBeingDragged.get(), globalEventPos);

    return true;
}

StateDraggingWaylandToplevel::StateDraggingWaylandToplevel(DragController *parent)
    : StateDraggingWayland(parent)
{
}

StateDraggingWaylandToplevel::~StateDraggingWaylandToplevel()
{
}

void StateDraggingWaylandToplevel::onEntry()
{
    KDDW_DEBUG("StateDraggingWaylandToplevel entered");

    if (DragController::instance()->m_inQDrag) {
        KDDW_ERROR("Impossible!");
        return;
    }

    ScopedValueRollback guard(DragController::instance()->m_inQDrag, true);

    q->m_windowBeingDragged = q->m_draggable->makeWindow();
    if (!q->m_windowBeingDragged) {
        KDDW_ERROR("StateDraggingWaylandToplevel: Failed to create window");
        q->dragCanceled.emit();
        return;
    }

    auto fw = q->m_windowBeingDragged->floatingWindow();
    if (!fw) {
        KDDW_ERROR("StateDraggingWaylandToplevel: No FloatingWindow");
        q->dragCanceled.emit();
        return;
    }

    auto window = fw->view()->window();
    if (!window) {
        KDDW_ERROR("StateDraggingWaylandToplevel: No window");
        q->dragCanceled.emit();
        return;
    }

    auto qtWindow = static_cast<QtCommon::Window *>(window.get())->qtWindow();
    if (!qtWindow) {
        KDDW_ERROR("StateDraggingWaylandToplevel: No QWindow");
        q->dragCanceled.emit();
        return;
    }

    auto serialize = [](const auto &object) {
        QByteArray data;
        QDataStream dataStream(&data, QIODevice::WriteOnly);
        dataStream << object;
        return data;
    };

    auto mimeData = new WaylandMimeData();
    mimeData->setData(QStringLiteral("application/x-qt-mainwindowdrag-window"),
                      serialize(reinterpret_cast<qintptr>(qtWindow))); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
    mimeData->setData(QStringLiteral("application/x-qt-mainwindowdrag-position"),
                      serialize(QCursor::pos()));

    Drag drag(this);
    drag.setMimeData(mimeData);

    Platform::instance()->installGlobalEventFilter(q);
    KDDW_DEBUG("Started QDrag (toplevel)");
    const Qt::DropAction result = drag.exec();
    KDDW_DEBUG("QDrag (toplevel) finished with result={}", int(result));

    Platform::instance()->removeGlobalEventFilter(q);
    if (result == Qt::IgnoreAction)
        q->dragCanceled.emit();
}

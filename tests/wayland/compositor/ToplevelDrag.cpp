/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "ToplevelDrag.h"

#include <QLoggingCategory>
#include <QWaylandCompositor>
#include <QWaylandDrag>
#include <QWaylandQuickShellSurfaceItem>
#include <QWaylandSeat>
#include <QWaylandXdgSurface>

Q_DECLARE_LOGGING_CATEGORY(lcTestCompositor)

/// An xdg_toplevel_drag_v1, there's one per drag
class ToplevelDrag : public QtWaylandServer::xdg_toplevel_drag_v1
{
public:
    ToplevelDrag(ToplevelDragManager *manager, struct ::wl_client *client, uint32_t id, int version)
        : QtWaylandServer::xdg_toplevel_drag_v1(client, int(id), version)
        , m_manager(manager)
    {
    }

protected:
    void xdg_toplevel_drag_v1_destroy_resource(Resource *) override
    {
        if (m_manager)
            m_manager->detach(this);
        delete this;
    }

    void xdg_toplevel_drag_v1_destroy(Resource *resource) override
    {
        wl_resource_destroy(resource->handle);
    }

    void xdg_toplevel_drag_v1_attach(Resource *resource, struct ::wl_resource *toplevelResource,
                                     int32_t x_offset, int32_t y_offset) override
    {
        if (!m_manager)
            return;

        if (m_manager->m_attachedDrag == this && m_manager->m_attachedToplevel) {
            wl_resource_post_error(resource->handle, error_toplevel_attached,
                                   "a toplevel is already attached");
            return;
        }

        QWaylandXdgToplevel *toplevel = QWaylandXdgToplevel::fromResource(toplevelResource);
        if (!toplevel) {
            qCWarning(lcTestCompositor) << "xdg_toplevel_drag_v1.attach: unknown toplevel";
            return;
        }

        m_manager->attach(this, toplevel, QPoint(x_offset, y_offset));
    }

private:
    const QPointer<ToplevelDragManager> m_manager;
};

ToplevelDragManager::ToplevelDragManager(QWaylandCompositor *compositor, ItemForSurface itemForSurface)
    : QWaylandCompositorExtensionTemplate(compositor)
    , m_compositor(compositor)
    , m_itemForSurface(std::move(itemForSurface))
{
    connect(compositor->defaultSeat()->drag(), &QWaylandDrag::dragStarted, this,
            &ToplevelDragManager::onDragStarted);
}

ToplevelDragManager::~ToplevelDragManager() = default;

void ToplevelDragManager::initialize()
{
    QWaylandCompositorExtensionTemplate::initialize();
    init(m_compositor->display(), 1);
}

void ToplevelDragManager::xdg_toplevel_drag_manager_v1_destroy(Resource *resource)
{
    wl_resource_destroy(resource->handle);
}

void ToplevelDragManager::xdg_toplevel_drag_manager_v1_get_xdg_toplevel_drag(Resource *resource, uint32_t id,
                                                                             struct ::wl_resource *)
{
    new ToplevelDrag(this, resource->client(), id, resource->version());
}

void ToplevelDragManager::pointerMoved(QPointF scenePos)
{
    m_pointerPos = scenePos;
    moveAttachedToplevel();
}

void ToplevelDragManager::dragEnding()
{
    // The toplevel stays where it is. Forget about it, as the client only destroys the
    // xdg_toplevel_drag_v1 on wl_data_source's dnd_finished or cancelled, and QtWaylandCompositor
    // doesn't send dnd_finished. The next drag would move it otherwise.
    m_dragInProgress = false;
    restoreAttachedItem();
    m_attachedDrag = nullptr;
    m_attachedToplevel = nullptr;
}

void ToplevelDragManager::attach(ToplevelDrag *drag, QWaylandXdgToplevel *toplevel, QPoint offset)
{
    qCDebug(lcTestCompositor) << "Toplevel attached to drag" << toplevel << "offset=" << offset;

    restoreAttachedItem();
    m_attachedDrag = drag;
    m_attachedToplevel = toplevel;
    m_offset = offset;

    // Toplevels can be attached mid-drag, which is how a detached tab becomes a window
    moveAttachedToplevel();
}

void ToplevelDragManager::detach(ToplevelDrag *drag)
{
    if (m_attachedDrag != drag)
        return;

    qCDebug(lcTestCompositor) << "Toplevel detached from drag" << m_attachedToplevel.data();
    restoreAttachedItem();
    m_attachedDrag = nullptr;
    m_attachedToplevel = nullptr;
}

void ToplevelDragManager::onDragStarted()
{
    m_dragInProgress = true;
    moveAttachedToplevel();
}

void ToplevelDragManager::moveAttachedToplevel()
{
    if (!m_dragInProgress || !m_attachedToplevel || !m_attachedToplevel->xdgSurface())
        return;

    // Not found while unmapped, the next pointer move tries again
    auto item = qobject_cast<QWaylandQuickShellSurfaceItem *>(
        m_itemForSurface(m_attachedToplevel->xdgSurface()->surface()));
    if (!item)
        return;

    if (m_disabledItem != item) {
        restoreAttachedItem();
        m_disabledItem = item;
        m_disabledItemButtons = item->acceptedMouseButtons();
        item->setAcceptedMouseButtons(Qt::NoButton);
        item->raise();
    }

    // Move it so the pointer is at m_offset, in surface coordinates
    const QPointF surfaceOrigin = item->mapToScene(item->mapFromSurface(QPointF(0, 0)));
    QQuickItem *moveItem = item->moveItem();
    moveItem->setPosition(moveItem->position() + (m_pointerPos - QPointF(m_offset) - surfaceOrigin));
}

void ToplevelDragManager::restoreAttachedItem()
{
    // Restored before the button is released, as Qt Quick doesn't deliver the release to a
    // mouse grabber which doesn't accept the button, and then there would be no drop
    if (m_disabledItem)
        m_disabledItem->setAcceptedMouseButtons(m_disabledItemButtons);
    m_disabledItem = nullptr;
}

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "qwayland-server-xdg-toplevel-drag-v1.h"

#include <QWaylandCompositorExtensionTemplate>
#include <QPoint>
#include <QPointF>
#include <QPointer>

#include <functional>

QT_BEGIN_NAMESPACE
class QWaylandCompositor;
class QWaylandQuickItem;
class QWaylandSurface;
class QWaylandXdgToplevel;
QT_END_NAMESPACE

class ToplevelDrag;

/// Server side of xdg-toplevel-drag-v1. Moves the attached toplevel along with the pointer while
/// a drag is in progress, like desktop compositors do.
///
/// TestExtension tells it about pointer moves and when the drag ends, as all the test's input
/// goes through it.
class ToplevelDragManager : public QWaylandCompositorExtensionTemplate<ToplevelDragManager>,
                            public QtWaylandServer::xdg_toplevel_drag_manager_v1
{
    Q_OBJECT
public:
    using ItemForSurface = std::function<QWaylandQuickItem *(QWaylandSurface *)>;

    ToplevelDragManager(QWaylandCompositor *compositor, ItemForSurface itemForSurface);
    ~ToplevelDragManager() override;
    void initialize() override;

    /// Called before the pointer moves to @p scenePos
    void pointerMoved(QPointF scenePos);

    /// Called before the button is released or the drag is cancelled
    void dragEnding();

protected:
    void xdg_toplevel_drag_manager_v1_destroy(Resource *resource) override;
    void xdg_toplevel_drag_manager_v1_get_xdg_toplevel_drag(Resource *resource, uint32_t id,
                                                            struct ::wl_resource *data_source) override;

private:
    friend class ToplevelDrag;
    void attach(ToplevelDrag *drag, QWaylandXdgToplevel *toplevel, QPoint offset);
    void detach(ToplevelDrag *drag);
    void onDragStarted();
    void moveAttachedToplevel();
    void restoreAttachedItem();

    QWaylandCompositor *const m_compositor;
    const ItemForSurface m_itemForSurface;

    ToplevelDrag *m_attachedDrag = nullptr;
    QPointer<QWaylandXdgToplevel> m_attachedToplevel;
    QPoint m_offset; // Where the pointer is, in the attached toplevel's surface coordinates
    QPointF m_pointerPos;
    bool m_dragInProgress = false;

    // The attached toplevel mustn't be the drag target, so it doesn't accept mouse buttons
    // during the drag, which is what QWaylandQuickOutput::pickClickableItem() looks at
    QPointer<QWaylandQuickItem> m_disabledItem;
    Qt::MouseButtons m_disabledItemButtons;
};

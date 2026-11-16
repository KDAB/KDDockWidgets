/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "core/DragController_p.h"

#include <QMimeData>

namespace KDDockWidgets {

namespace Core {

// Used on wayland only to use QDrag instead of setting geometry on mouse-move.
class StateDraggingWayland : public StateDragging
{
    Q_OBJECT
public:
    explicit StateDraggingWayland(DragController *parent);
    ~StateDraggingWayland() override;
    void onEntry() override;

    bool handleMouseButtonRelease(QPoint globalPos) override;
    bool handleDragEnter(DragMoveEvent *, DropArea *, QPoint globalEventPos) override;
    bool handleDragMove(DragMoveEvent *, DropArea *, QPoint globalEventPos) override;
    bool handleDragLeave(DropArea *) override;
    bool handleDrop(DropEvent *, DropArea *, QPoint globalEventPos) override;
    bool handleMouseMove(QPoint globalPos) override;

private:
#ifdef KDDW_HAS_WAYLAND_TOPLEVEL_DRAG
    /// Sets up the drag to use xdg-toplevel-drag, so the window itself is dragged instead of a
    /// pixmap. Returns false if the window couldn't be created.
    bool setupToplevelDrag(QMimeData *mimeData);
#endif
};

/// Returns whether xdg-toplevel-drag can be used. Needs Qt >= 6.8 and compositor support.
bool isWaylandToplevelDragSupported();

// A sub-class just so we don't use QMimeData directly. We'll only accept drops if its mime data
// Can be qobject_casted to this class. For safety.
class WaylandMimeData : public QMimeData
{
    Q_OBJECT
public:
};

}
}

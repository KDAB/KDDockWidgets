/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import QtQuick
import QtQuick.Window
import QtWayland.Compositor
import QtWayland.Compositor.XdgShell

WaylandCompositor {
    id: compositor
    socketName: kddwSocketName

    // New toplevels are cascaded, so they're deterministic but don't fully overlap
    property int windowsCreated: 0

    WaylandOutput {
        sizeFollowsWindow: true

        window: Window {
            width: kddwOutputSize.width
            height: kddwOutputSize.height
            visible: true
            color: "#303030"

            WaylandMouseTracker {
                id: mouseTracker
                anchors.fill: parent
                windowSystemCursorEnabled: false

                Repeater {
                    model: ListModel {
                        id: toplevels
                    }

                    ShellSurfaceItem {
                        id: toplevelItem
                        shellSurface: model.shellSurface
                        x: model.initialX
                        y: model.initialY
                        autoCreatePopupItems: true
                        onSurfaceDestroyed: toplevels.remove(index)

                        // Like desktop compositors, activate new windows once they're shown
                        Connections {
                            target: toplevelItem.surface
                            function onHasContentChanged() {
                                if (toplevelItem.surface.hasContent)
                                    toplevelItem.takeFocus();
                            }
                        }
                    }
                }

                // Clients wait for frame callbacks on their drag icon, so it needs to be shown
                WaylandQuickItem {
                    x: mouseTracker.mouseX
                    y: mouseTracker.mouseY
                    surface: compositor.defaultSeat ? compositor.defaultSeat.drag.icon : null
                    visible: surface !== null
                    inputEventsEnabled: false
                }

                WaylandCursorItem {
                    x: mouseTracker.mouseX
                    y: mouseTracker.mouseY
                    seat: compositor.defaultSeat
                    inputEventsEnabled: false
                }
            }
        }
    }

    XdgShell {
        onToplevelCreated: (toplevel, xdgSurface) => {
            const offset = (compositor.windowsCreated % 10) * 40;
            compositor.windowsCreated++;
            toplevels.append({ shellSurface: xdgSurface, initialX: offset, initialY: offset });
        }
    }
}

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2025 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sergio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import QtQuick 2.6
import QtQuick.Controls 2.12
import com.kdab.dockwidgets 2.0 as KDDW

// Example showing how to delete dock widgets when they're closed

// We present two ways to do so:
// 1 - Pass DockWidgetOption_DeleteOnClose options to DockWidgets
// 2 - Listen to the 'closed' signal and call deleteDockWidget() manually

ApplicationWindow {
    visible: true
    width: 1000
    height: 800

    KDDW.DockingArea {
        id: root
        anchors.fill: parent

        uniqueName: "MainLayout-1"

        KDDW.DockWidget {
            id: dock1
            uniqueName: "dock1"
            options: KDDW.KDDockWidgets.DockWidgetOption_DeleteOnClose

            Rectangle {
                id: guest4
                color: "#2E8BC0"
                anchors.fill: parent
            }
        }

        KDDW.DockWidget {
            id: dock2
            uniqueName: "dock2"

            Rectangle {
                color: "#2E8BC0"
                anchors.fill: parent
            }

            onClosed: {
                if (dock2.lastCloseReason === KDDW.KDDockWidgets.CloseReason.TitleBarCloseButton) {
                    dock2.deleteDockWidgetLater();
                    console.log("dock2 deleted on close");
                }
            }
        }

        Component.onCompleted: {
            addDockWidget(dock1, KDDW.KDDockWidgets.Location_OnBottom);
            addDockWidget(dock2, KDDW.KDDockWidgets.Location_OnBottom);
        }
    }
}

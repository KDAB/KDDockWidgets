/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import QtQuick 2.6
import QtQuick.Controls 2.12
import com.kdab.dockwidgets 2.0 as KDDW

ApplicationWindow {
    visible: true
    width: 1000
    height: 800

    KDDW.DockingArea {
        anchors.fill: parent

        uniqueName: "MyWindowName-titleBarHasMinimizeButton"

        KDDW.DockWidget {
            id: dock1
            uniqueName: "dock1"
            floatingWindowFlags: KDDW.KDDockWidgets.FloatingWindowFlags.TitleBarHasMinimizeButton

            Rectangle {
                anchors.fill: parent
                color: "blue"
            }
        }

        Component.onCompleted: {
            // Never added to the layout, so it starts out floating.
            dock1.open();
        }
    }
}

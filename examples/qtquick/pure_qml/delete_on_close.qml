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

// Example showing how to pass options to DockWidgets, for example DockWidgetOption_DeleteOnClose

ApplicationWindow {
    visible: true
    width: 1000
    height: 800

    KDDW.DockingArea {
        id: root
        anchors.fill: parent

        uniqueName: "MainLayout-1"

        KDDW.DockWidget {
            id: mydockwidget
            uniqueName: "mydockwidget"
            options: KDDW.KDDockWidgets.DockWidgetOption_DeleteOnClose

            Rectangle {
                id: guest4
                color: "#2E8BC0"
                anchors.fill: parent
            }
        }

        Component.onCompleted: {
            addDockWidget(mydockwidget, KDDW.KDDockWidgets.Location_OnBottom);
        }
    }
}

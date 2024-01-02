/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sergio Martins <sergio.martins@kdab.com>

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
        id: dockWidgetArea
        anchors.fill: parent

        uniqueName: "MyMainLayout"

        KDDW.DockWidget {
            id: dock4
            uniqueName: "dock4"
            source: "qrc:/Guest4.qml"
            onIsFocusedChanged: {
              console.log("Dock4 focus changed to: " + isFocused);
            }
        }

        Component.onCompleted: {
            // The other 3 dock widgets are created via C++ in main.cpp
            // For illustration purposes, here's a .qml version. Maybe its the preferred form even.
            addDockWidget(dock4, KDDW.KDDockWidgets.Location_OnBottom);
        }
    }
}

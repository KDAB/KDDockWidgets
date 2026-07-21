/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
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
    title: "KDDockWidgets - QtQuick C++ API example"

    // All dock widget creation happens in C++ (see main.cpp). This QML file
    // only sets up the top-level window, the menu and the docking area.
    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")

            Action {
                text: qsTr("&New DockWidget")
                onTriggered: dockWidgetFactory.newDockWidget()
            }

            MenuSeparator {}

            Action {
                text: qsTr("&Save layout")
                onTriggered: dockWidgetFactory.saveLayout()
            }

            Action {
                text: qsTr("&Restore layout")
                onTriggered: dockWidgetFactory.restoreLayout()
            }

            MenuSeparator {}

            Action {
                text: qsTr("&Quit")
                onTriggered: Qt.quit()
            }
        }
    }

    KDDW.DockingArea {
        id: root
        anchors.fill: parent

        // Each main layout needs a unique id
        uniqueName: "MainLayout-1"
    }
}

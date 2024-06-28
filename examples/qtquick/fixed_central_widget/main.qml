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
    width: 1600
    height: 800

    Rectangle {
        id: someTopArea
        color: "#CFD4C5"
        height: 50
        anchors {
            left: parent.left
            right: parent.right
        }
    }

    KDDW.DockingArea {
        id: root
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            top: someTopArea.bottom
        }

        persistentCentralItemFileName: ":/CentralWidget.qml"
        options: KDDW.KDDockWidgets.MainWindowOption_HasCentralWidget

        // Each main layout needs a unique id
        uniqueName: "MainLayout-1"

        KDDW.DockWidget {
            id: dock4
            uniqueName: "dock4" // Each dock widget needs a unique id
            source: ":/SomeDockWidget.qml"
        }

        KDDW.DockWidget {
            id: dock5
            uniqueName: "dock5"
            Rectangle {
                id: guest
                color: "#2E8BC0"
                anchors.fill: parent
            }
        }

        KDDW.DockWidget {
            id: dock6
            uniqueName: "dock6"
            Rectangle {
                color: "#2E8BC0"
                anchors.fill: parent
            }
        }

        Component.onCompleted: {
            addDockWidget(dock5, KDDW.KDDockWidgets.Location_OnRight, null, Qt.size(500, 0));
            addDockWidget(dock4, KDDW.KDDockWidgets.Location_OnLeft, null, Qt.size(300, 0));
            dock5.addDockWidgetAsTab(dock6);
        }
    }

    function toggleDockWidget(dw) {
        if (dw.dockWidget.isOpen()) {
            dw.dockWidget.close();
        } else {
            dw.dockWidget.show();
        }
    }
}

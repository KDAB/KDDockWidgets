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

    footer: Label {
        text: "dock 4 is floating: " + dock4.isFloating
    }

    KDDW.DockingArea {
        anchors.fill: parent

        // Each main layout needs a unique id
        uniqueName: "MyWindowName-1"

        KDDW.DockWidget {
            id: dock4
            uniqueName: "dock4"
            Rectangle {
                anchors.fill: parent
                color: "blue"
                visible: true
            }
        }

        KDDW.DockWidget {
            id: dock5
            uniqueName: "dock5"
            Item {}
        }

        Component.onCompleted: {
            // Add dock4 to the Bottom location
            addDockWidget(dock4, KDDW.KDDockWidgets.Location_OnBottom);
            dock5.show();
        }

    }
}

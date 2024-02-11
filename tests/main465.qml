/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
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
        visible: true
        anchors.fill: parent
        uniqueName: "MyWindowName-1"
        affinities: ["affinity_one", "affinity_two"]

        Component.onCompleted: {
            dock1.show();
            dock2.show();
        }
    }

    KDDW.DockWidget {
        id: dock1
        uniqueName: "dock1"
        affinities: ["affinity_one", "affinity_two"]
        Rectangle {
            anchors.fill: parent
            color: "#373F51"
            visible: true
        }
    }

    KDDW.DockWidget {
        id: dock2
        uniqueName: "dock2"
        Rectangle {
            anchors.fill: parent
            color: "#0D5D56"
            visible: true
        }
    }
}

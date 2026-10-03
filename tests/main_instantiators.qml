/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/


/// @brief Used by tst_instantiators, which calls the instantiators API from C++

import QtQuick 2.6
import QtQuick.Controls 2.12
import com.kdab.dockwidgets 2.0 as KDDW

ApplicationWindow {
    visible: true
    width: 1000
    height: 800

    KDDW.DockingArea {
        objectName: "area"
        anchors.fill: parent
        uniqueName: "instantiators-mw"

        KDDW.DockWidget {
            objectName: "dockA"
            uniqueName: "dockA"
            title: "Dock A"
            Rectangle {
                anchors.fill: parent
                color: "#475B63"
            }
        }

        KDDW.DockWidget {
            objectName: "dockB"
            uniqueName: "dockB"
            Rectangle {
                anchors.fill: parent
                color: "#729B79"
            }
        }

        KDDW.DockWidget {
            objectName: "dockC"
            uniqueName: "dockC"
            Rectangle {
                anchors.fill: parent
                color: "#BACDB0"
            }
        }
    }
}

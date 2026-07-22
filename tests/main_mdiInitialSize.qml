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

    KDDW.MDIDockingArea {
        id: dockingArea
        anchors.fill: parent
        uniqueName: "mdiInitialSizeMainWindow"
    }

    KDDW.DockWidget {
        id: dock1
        uniqueName: "mdiInitialSizeDock"
        Rectangle {
            anchors.fill: parent
            color: "#413C58"
        }
    }

    Component.onCompleted: {
        dockingArea.addDockWidget(dock1, Qt.point(20, 20), Qt.size(520, 800));
    }
}

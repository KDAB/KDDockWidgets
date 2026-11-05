/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>

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
        id: area
        anchors.fill: parent
        options: KDDW.KDDockWidgets.MainWindowOption_HasCentralWidget
        uniqueName: "MyWindowName-1"

        persistentCentralItemComponent: Rectangle {
            // Uses an id from this file, to check the item sees its declaring context
            objectName: "central-" + area.uniqueName
            color: "red"
            anchors.fill: parent
        }
    }
}

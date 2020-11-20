/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import QtQuick 2.9

Rectangle {
    id: root

    property QtObject titleBarCpp
    readonly property string title: titleBarCpp ? titleBarCpp.title : ""

    // So the tests can send mouse events programatically
    readonly property QtObject mouseAreaForTests: dragMouseArea

    visible: titleBarCpp && titleBarCpp.visible
    implicitHeight: 30

    MouseArea {
        id: dragMouseArea
        anchors.fill: parent
        onDoubleClicked: {
            if (titleBarCpp) {
                titleBarCpp.onDoubleClicked();
            }
        }
    }

    onTitleBarCppChanged: {
        if (titleBarCpp)
            titleBarCpp.filterEvents(dragMouseArea)
    }
}

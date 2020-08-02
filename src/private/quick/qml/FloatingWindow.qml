/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import QtQuick 2.9
import "." as KDDW

Rectangle {
    id: root
    readonly property QtObject floatingWindowCpp: parent
    readonly property QtObject titleBarCpp: floatingWindowCpp ? floatingWindowCpp.titleBar : null
    readonly property QtObject dropAreaCpp: floatingWindowCpp ? floatingWindowCpp.dropArea : null

    color: "yellow"
    anchors.fill: parent

    KDDW.TitleBar {
        id: titleBar
        height: 30
        titleBarCpp: root.titleBarCpp
        visible: titleBarCpp && titleBarCpp.visible

        anchors {
            top:  parent.top
            left: parent.left
            right: parent.right
        }
    }

    KDDW.DropArea {
        id: dropArea
        dropAreaCpp: root.dropAreaCpp
        anchors {
            left: parent.left
            right: parent.right
            top: titleBar.bottom
            bottom: parent.bottom
        }
    }

    onDropAreaCppChanged: {
        // Parent the cpp obj to the visual obj. So the user can style it
        if (dropAreaCpp) {
            dropAreaCpp.parent = dropArea;
            dropAreaCpp.anchors.fill = dropArea;
        }
    }
}

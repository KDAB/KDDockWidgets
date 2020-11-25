/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import QtQuick 2.9
import "." as KDDW

Item {
    id: root
    readonly property QtObject floatingWindowCpp: parent
    readonly property QtObject titleBarCpp: floatingWindowCpp ? floatingWindowCpp.titleBar : null
    readonly property QtObject dropAreaCpp: floatingWindowCpp ? floatingWindowCpp.dropArea : null
    readonly property int titleBarHeight: titleBarCpp ? titleBarCpp.titleBarHeight : 0

    anchors.fill: parent

    KDDW.TitleBar {
        id: titleBar
        height: root.titleBarHeight
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

        onHeightChanged: {
            // console.log("FloatingWindow.qml.dropArea height changed to " + height + " ; root.height= " + root.height)
        }
    }

    onDropAreaCppChanged: {
        // Parent the cpp obj to the visual obj. So the user can style it
        if (dropAreaCpp) {
            //console.log("Setup start: height=" + height + "; dropArea.height=" + dropAreaCpp.height);
            dropAreaCpp.parent = dropArea;
            dropAreaCpp.anchors.fill = dropArea;
            //console.log("Setup done: height=" + height + "; dropArea.height=" + dropAreaCpp.height);
        }
    }

    onHeightChanged: {
        // console.log("FloatingWindow.qml.root height changed to " + height)
    }

    onWidthChanged: {
        // console.log("FloatingWindow.qml.root width changed to " + width)
    }
}

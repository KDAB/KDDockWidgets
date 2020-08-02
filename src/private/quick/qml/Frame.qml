/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import QtQuick 2.9
import QtQuick.Controls 2.9
import QtQuick.Layouts 1.9 

Rectangle {
    id: root
    property QtObject frameCpp
    readonly property QtObject titleBarCpp: frameCpp ? frameCpp.titleBar : null

    color: "cyan"
    anchors.fill: parent

    onFrameCppChanged: {
        frameCpp.setStackLayout(stackLayout);
    }

    TitleBar {
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

    TabBar {
        id: tabbar
        visible: count > 1
        anchors {
            left: parent.left
            right: parent.right
            top: titleBar.visible ? titleBar.bottom
                                  : parent.top
        }

        width: parent.width

        Repeater {
            model: root.frameCpp ? root.frameCpp.tabTitles : 0
            TabButton {
                text: modelData
            }
        }
    }

    StackLayout {
        id: stackLayout
        anchors {
            left: parent.left
            right: parent.right
            top: tabbar.visible ? tabbar.bottom : parent.top
            bottom: parent.bottom
        }

        currentIndex: tabbar.currentIndex
    }
}

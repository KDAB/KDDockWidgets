/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import QtQuick 2.9

TitleBarBase {
    id: root

    Text {
        id: title
        text: root.title
        anchors {
            left: parent.left
            leftMargin: 5
        }
    }

    Rectangle {
        id: floatButton
        color: "red"
        anchors {
            top: parent.top
            bottom: parent.bottom
            right: closeButton.left
            topMargin: 5
            bottomMargin: 5
            rightMargin: 5
        }
        width: height

        MouseArea {
            anchors.fill: parent
            onClicked: {
                titleBarCpp.onFloatClicked();
            }
        }
    }

    Rectangle {
        id: closeButton
        color: "red"
        anchors {
            top: parent.top
            bottom: parent.bottom
            right: parent.right
            topMargin: 5
            bottomMargin: 5
            leftMargin: 5
        }
        width: height
        MouseArea {
            anchors.fill: parent
            onClicked: {
                titleBarCpp.onCloseClicked();
            }
        }
    }
}

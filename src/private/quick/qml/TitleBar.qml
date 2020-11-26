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

    readonly property QtObject floatButton: floatButton
    readonly property QtObject closeButton: closeButton

    onTitleBarCppChanged: {
        if (titleBarCpp) {
            // Setting just so the unit-tests can access the buttons
            titleBarCpp.titleBarQmlItem = this;
        }
    }

    Text {
        id: title
        text: root.title
        anchors {
            left: parent ? parent.left : undefined
            leftMargin: 5
            verticalCenter: parent.verticalCenter
        }
    }

    TitleBarButton {
        id: floatButton
        visible: root.titleBarCpp && root.titleBarCpp.floatButtonVisible
        imageSource: "qrc:/img/dock-float.png"
        anchors {
            verticalCenter: parent ? parent.verticalCenter : undefined
            right: closeButton.left
            topMargin: 5
            bottomMargin: 5
            rightMargin: 2
        }
        onClicked: {
            titleBarCpp.onFloatClicked();
        }
    }

    TitleBarButton {
        id: closeButton
        enabled: root.titleBarCpp && root.titleBarCpp.closeButtonEnabled
        imageSource: "qrc:/img/close.png"
        anchors {
            verticalCenter: parent ? parent.verticalCenter : undefined
            right: parent ? parent.right : undefined
            topMargin: 5
            bottomMargin: 5
            leftMargin: 5
            rightMargin: 2
        }
        onClicked: {
            titleBarCpp.onCloseClicked();
        }
    }
}

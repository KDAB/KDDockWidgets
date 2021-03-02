/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
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
    readonly property int nonContentsHeight: titleBar.heightWhenVisible + tabbar.height
    property int contentsMargin: 2
    property int titleBarContentsMargin: 1
    property bool hasCustomMouseEventRedirector: false
    property int mouseResizeMargin: contentsMargin
    property bool isMDI: frameCpp && frameCpp.isMDI

    anchors.fill: parent

    radius: 2
    color: "transparent"
    border {
        color: "#b8b8b8"
        width: 1
    }

    onFrameCppChanged: {
        if (frameCpp) {
            frameCpp.setStackLayout(stackLayout);

            // When Frame is in MDI mode, we need to detect when the mouse over the edges
            frameCpp.redirectMouseEvents(mouseArea)
        }
    }

    onNonContentsHeightChanged: {
        if (frameCpp)
            frameCpp.geometryUpdated();
    }

    MouseArea {
        anchors {
            left: parent.left
            top: parent.top
            bottom: parent.bottom
        }

        hoverEnabled: true
        width: root.mouseResizeMargin
        cursorShape: enabled ? Qt.SizeHorCursor : Qt.ArrowCursor // Even if disabled the MouseArea changes cursor, as it's different than Item.enabled, so explicitly change cursor if disabled
        z: mouseArea.z + 1
        enabled: root.isMDI && !_kddwDragController.isDragging
        onPressed: { mouse.accepted = false; }
        onReleased: { mouse.accepted = false; }
    }

    MouseArea {
        anchors {
            right: parent.right
            top: parent.top
            bottom: parent.bottom
        }

        hoverEnabled: true
        width: root.mouseResizeMargin
        cursorShape: enabled ? Qt.SizeHorCursor : Qt.ArrowCursor
        z: mouseArea.z + 1
        enabled: root.isMDI && !_kddwDragController.isDragging
        onPressed: { mouse.accepted = false; }
        onReleased: { mouse.accepted = false; }
    }

    MouseArea {
        anchors {
            right: parent.right
            top: parent.top
            left: parent.left
        }

        hoverEnabled: true
        height: root.mouseResizeMargin
        cursorShape: enabled ? Qt.SizeVerCursor : Qt.ArrowCursor
        z: mouseArea.z + 1
        enabled: root.isMDI && !_kddwDragController.isDragging
        onPressed: { mouse.accepted = false; }
        onReleased: { mouse.accepted = false; }
    }

    MouseArea {
        anchors {
            right: parent.right
            left: parent.left
            bottom: parent.bottom
        }

        hoverEnabled: true
        height: root.mouseResizeMargin
        cursorShape: enabled ? Qt.SizeVerCursor : Qt.ArrowCursor
        z: mouseArea.z + 1
        enabled: root.isMDI && !_kddwDragController.isDragging
        onPressed: { mouse.accepted = false; }
        onReleased: { mouse.accepted = false; }
    }

    MouseArea {
        anchors {
            right: parent.right
            bottom: parent.bottom
        }

        hoverEnabled: true
        height: root.mouseResizeMargin
        width: height

        cursorShape: enabled ? Qt.SizeFDiagCursor : Qt.ArrowCursor
        z: mouseArea.z + 2
        enabled: root.isMDI && !_kddwDragController.isDragging
        onPressed: { mouse.accepted = false; }
        onReleased: { mouse.accepted = false; }
    }

    MouseArea {
        anchors {
            left: parent.left
            top: parent.top
        }

        hoverEnabled: true
        height: root.mouseResizeMargin
        width: height

        cursorShape: enabled ? Qt.SizeFDiagCursor : Qt.ArrowCursor
        z: mouseArea.z + 2
        enabled: root.isMDI && !_kddwDragController.isDragging
        onPressed: { mouse.accepted = false; }
        onReleased: { mouse.accepted = false; }
    }

    MouseArea {
        anchors {
            right: parent.right
            top: parent.top
        }

        hoverEnabled: true
        height: root.mouseResizeMargin
        width: height

        cursorShape: enabled ? Qt.SizeBDiagCursor : Qt.ArrowCursor
        z: mouseArea.z + 2
        enabled: root.isMDI && !_kddwDragController.isDragging
        onPressed: { mouse.accepted = false; }
        onReleased: { mouse.accepted = false; }
    }

    MouseArea {
        anchors {
            left: parent.left
            bottom: parent.bottom
        }

        hoverEnabled: true
        height: root.mouseResizeMargin
        width: height

        cursorShape: enabled ? Qt.SizeBDiagCursor : Qt.ArrowCursor
        z: mouseArea.z + 2
        enabled: root.isMDI && !_kddwDragController.isDragging
        onPressed: { mouse.accepted = false; }
        onReleased: { mouse.accepted = false; }
    }


    MouseArea {
        id: mouseArea
        objectName: "frameMouseArea"
        anchors.fill: parent

        Loader {
            id: titleBar
            readonly property QtObject titleBarCpp: root.titleBarCpp
            source: frameCpp ? _kddw_widgetFactory.titleBarFilename(frameCpp.userType)
                             : ""

            anchors {
                top:  parent ? parent.top : undefined
                left: parent ? parent.left : undefined
                right: parent ? parent.right : undefined
                topMargin: root.titleBarContentsMargin
                leftMargin: root.titleBarContentsMargin
                rightMargin: root.titleBarContentsMargin
            }
        }

        Connections {
            target: frameCpp
            function onCurrentIndexChanged() {
                tabbar.currentIndex = frameCpp.currentIndex;
            }
        }

        MouseArea {
            id: dragMouseArea
            objectName: "kddwTabBarDragMouseArea"
            hoverEnabled: true
            anchors.fill: tabbar
            enabled: tabbar.visible
            z: 10
        }

        TabBar {
            id: tabbar

            readonly property QtObject tabBarCpp: root.frameCpp ? root.frameCpp.tabWidget.tabBar
                                                                : null

            visible: count > 1
            anchors {
                left: parent ? parent.left : undefined
                right: parent ? parent.right : undefined
                top: (titleBar && titleBar.visible) ? titleBar.bottom
                                                    : (parent ? parent.top : undefined)
                topMargin: 1
                leftMargin: 1
                rightMargin: 1
            }

            width: parent.width

            onCurrentIndexChanged: {
                if (root && root.frameCpp)
                    root.frameCpp.tabWidget.setCurrentDockWidget(currentIndex);
            }

            onTabBarCppChanged: {
                if (tabBarCpp) {
                    if (!root.hasCustomMouseEventRedirector)
                        tabBarCpp.redirectMouseEvents(dragMouseArea)

                    // Setting just so the unit-tests can access the buttons
                    tabBarCpp.tabBarQmlItem = this;
                }
            }

            Repeater {
                model: root.frameCpp ? root.frameCpp.tabWidget.dockWidgetModel : 0
                TabButton {
                    text: title
                }
            }
        }

        StackLayout {
            id: stackLayout
            anchors {
                left: parent ? parent.left : undefined
                right: parent ? parent.right : undefined
                top: (parent && tabbar.visible) ? tabbar.bottom : ((titleBar && titleBar.visible) ? titleBar.bottom
                                                                                                  : parent ? parent.top : undefined)
                bottom: parent ? parent.bottom : undefined

                leftMargin: root.contentsMargin
                rightMargin: root.contentsMargin
                bottomMargin: root.contentsMargin
            }

            currentIndex: tabbar.currentIndex
        }
    }
}

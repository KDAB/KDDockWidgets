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
    readonly property int nonContentsHeight: (titleBar.item ? titleBar.item.heightWhenVisible : 0) + tabbar.height + (2 * contentsMargin) + titleBarContentsMargin
    property int contentsMargin: 2
    property int titleBarContentsMargin: 1
    property bool hasCustomMouseEventRedirector: false
    property int mouseResizeMargin: contentsMargin
    readonly property bool isMDI: frameCpp && frameCpp.isMDI
    readonly property bool resizeAllowed: root.isMDI && !_kddwDragController.isDragging && _kddwDockRegistry && (!_kddwDockRegistry.frameInMDIResize || _kddwDockRegistry.frameInMDIResize === frameCpp)

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

    ResizeHandlerHelper {
        anchors {
            left: parent.left
            top: parent.top
            bottom: parent.bottom
        }

        shape:  Qt.SizeHorCursor
        z: mouseArea.z + 1
    }

    ResizeHandlerHelper {
        anchors {
            right: parent.right
            top: parent.top
            bottom: parent.bottom
        }

        shape:  Qt.SizeHorCursor
        z: mouseArea.z + 1
    }


    ResizeHandlerHelper {
        anchors {
            right: parent.right
            top: parent.top
            left: parent.left
        }

        shape:  Qt.SizeVerCursor
        z: mouseArea.z + 1
    }

    ResizeHandlerHelper {
        anchors {
            right: parent.right
            left: parent.left
            bottom: parent.bottom
        }

        shape:  Qt.SizeVerCursor
        z: mouseArea.z + 1
    }

    ResizeHandlerHelper {
        anchors {
            right: parent.right
            bottom: parent.bottom
        }

        shape:  Qt.SizeFDiagCursor
        z: mouseArea.z + 2
    }

    ResizeHandlerHelper {
        anchors {
            left: parent.left
            top: parent.top
        }

        shape:  Qt.SizeFDiagCursor
        z: mouseArea.z + 2
    }

    ResizeHandlerHelper {
        anchors {
            right: parent.right
            top: parent.top
        }

        shape:  Qt.SizeBDiagCursor
        z: mouseArea.z + 2
    }

    ResizeHandlerHelper {
        anchors {
            left: parent.left
            bottom: parent.bottom
        }

        shape:  Qt.SizeBDiagCursor
        z: mouseArea.z + 2
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

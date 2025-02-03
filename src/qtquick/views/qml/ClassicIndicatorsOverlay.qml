/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sergio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import QtQuick 2.9
import com.kdab.dockwidgets 2.0

Item {
    id: root
    anchors.fill: parent
    readonly property int outterMargin: 10
    readonly property int innerMargin: 10
    readonly property QtObject innerIndicators: innerIndicators
    readonly property ClassicDropIndicatorOverlay overlayWindow: _kddw_overlayWindow
    visible: width > 50 && height > 50 // don't show if window is too small'

    ClassicIndicator {
        overlayWindow: root.overlayWindow
        visible: root.overlayWindow && root.overlayWindow.outterLeftIndicatorVisible
        indicatorType: KDDockWidgets.DropLocation_OutterLeft
        anchors {
            left: parent.left
            leftMargin: root.outterMargin
            verticalCenter: parent.verticalCenter
        }
    }

    ClassicIndicator {
        overlayWindow: root.overlayWindow
        visible: root.overlayWindow && root.overlayWindow.outterRightIndicatorVisible
        indicatorType: KDDockWidgets.DropLocation_OutterRight
        anchors {
            right: parent.right
            rightMargin: root.outterMargin
            verticalCenter: parent.verticalCenter
        }
    }

    ClassicIndicator {
        overlayWindow: root.overlayWindow
        visible: root.overlayWindow && root.overlayWindow.outterTopIndicatorVisible
        indicatorType: KDDockWidgets.DropLocation_OutterTop
        anchors {
            top: parent.top
            topMargin: root.outterMargin
            horizontalCenter: parent.horizontalCenter
        }
    }

    ClassicIndicator {
        overlayWindow: root.overlayWindow
        visible: root.overlayWindow && root.overlayWindow.outterBottomIndicatorVisible
        indicatorType: KDDockWidgets.DropLocation_OutterBottom
        anchors {
            bottom: parent.bottom
            bottomMargin: root.outterMargin
            horizontalCenter: parent.horizontalCenter
        }
    }

    Item {
        id: innerIndicators
        objectName: "innerIndicators"

        x: root.overlayWindow ? (root.overlayWindow.hoveredGroupRect.x + (root.overlayWindow.hoveredGroupRect.width / 2)) : 0
        y: root.overlayWindow ? (root.overlayWindow.hoveredGroupRect.y + (root.overlayWindow.hoveredGroupRect.height / 2)) : 0

        width: (centerIndicator * 3) + (2 * innerMargin)
        height: width
        visible: root.overlayWindow && (root.overlayWindow.innerLeftIndicatorVisible || root.overlayWindow.innerRightIndicatorVisible || root.overlayWindow.innerTopIndicatorVisible || root.overlayWindow.innerBottomIndicatorVisible || root.overlayWindow.tabIndicatorVisible)

        ClassicIndicator {
            id: innerLeft
            overlayWindow: root.overlayWindow
            visible: root.overlayWindow && root.overlayWindow.innerLeftIndicatorVisible
            indicatorType: KDDockWidgets.DropLocation_Left
            anchors {
                right: centerIndicator.left
                rightMargin: root.innerMargin
                verticalCenter: parent.verticalCenter
            }
        }

        ClassicIndicator {
            id: centerIndicator
            overlayWindow: root.overlayWindow
            visible: root.overlayWindow && root.overlayWindow.tabIndicatorVisible
            indicatorType: KDDockWidgets.DropLocation_Center
            anchors.centerIn: parent
        }

        ClassicIndicator {
            id: innerRight
            overlayWindow: root.overlayWindow
            visible: root.overlayWindow && root.overlayWindow.innerRightIndicatorVisible
            indicatorType: KDDockWidgets.DropLocation_Right
            anchors {
                left: centerIndicator.right
                leftMargin: root.innerMargin
                verticalCenter: parent.verticalCenter
            }
        }

        ClassicIndicator {
            id: innerTop
            overlayWindow: root.overlayWindow
            visible: root.overlayWindow && root.overlayWindow.innerTopIndicatorVisible
            indicatorType: KDDockWidgets.DropLocation_Top
            anchors {
                bottom: centerIndicator.top
                bottomMargin: root.innerMargin
                horizontalCenter: parent.horizontalCenter
            }
        }

        ClassicIndicator {
            id: innerBottom
            overlayWindow: root.overlayWindow
            visible: root.overlayWindow && root.overlayWindow.innerBottomIndicatorVisible
            indicatorType: KDDockWidgets.DropLocation_Bottom
            anchors {
                top: centerIndicator.bottom
                topMargin: root.innerMargin
                horizontalCenter: parent.horizontalCenter
            }
        }
    }
}

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sergio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import QtQuick 2.9
import com.kdab.dockwidgets 1.0

Item {
    id: root
    anchors.fill: parent
    readonly property int outterMargin: 10
    readonly property int innerMargin: 10
    readonly property QtObject innerIndicators: innerIndicators
    visible: width > 50 && height > 50 // don't show if window is too small'

    ClassicIndicator {
        visible: _window.classicIndicators.outterLeftIndicatorVisible
        indicatorType: KDDockWidgets.DropLocation_OutterLeft
        anchors {
            left: parent.left
            leftMargin: outterMargin
            verticalCenter: parent.verticalCenter
        }
    }

    ClassicIndicator {
        visible: _window.classicIndicators.outterRightIndicatorVisible
        indicatorType: KDDockWidgets.DropLocation_OutterRight
        anchors {
            right: parent.right
            rightMargin: outterMargin
            verticalCenter: parent.verticalCenter
        }
    }

    ClassicIndicator {
        visible: _window.classicIndicators.outterTopIndicatorVisible
        indicatorType: KDDockWidgets.DropLocation_OutterTop
        anchors {
            top: parent.top
            topMargin: outterMargin
            horizontalCenter: parent.horizontalCenter
        }
    }

    ClassicIndicator {
        visible: _window.classicIndicators.outterBottomIndicatorVisible
        indicatorType: KDDockWidgets.DropLocation_OutterBottom
        anchors {
            bottom: parent.bottom
            bottomMargin: outterMargin
            horizontalCenter: parent.horizontalCenter
        }
    }

    Item {
        id: innerIndicators
        objectName: "innerIndicators"

        x: _window.classicIndicators.hoveredFrameRect.x + (_window.classicIndicators.hoveredFrameRect.width / 2)
        y: _window.classicIndicators.hoveredFrameRect.y + (_window.classicIndicators.hoveredFrameRect.height / 2)

        width: (centerIndicator * 3) + (2 * innerMargin)
        height: width
        visible: _window.classicIndicators.innerLeftIndicatorVisible || _window.classicIndicators.innerRightIndicatorVisible ||
                 _window.classicIndicators.innerTopIndicatorVisible || _window.classicIndicators.innerBottomIndicatorVisible || _window.classicIndicators.tabIndicatorVisible

        ClassicIndicator {
            id: innerLeft
            visible: _window.classicIndicators.innerLeftIndicatorVisible
            indicatorType: KDDockWidgets.DropLocation_Left
            anchors {
                right: centerIndicator.left
                rightMargin: innerMargin
                verticalCenter: parent.verticalCenter
            }
        }

        ClassicIndicator {
            id: centerIndicator
            visible: _window.classicIndicators.tabIndicatorVisible
            indicatorType: KDDockWidgets.DropLocation_Center
            anchors.centerIn: parent
        }

        ClassicIndicator {
            id: innerRight
            visible: _window.classicIndicators.innerRightIndicatorVisible
            indicatorType: KDDockWidgets.DropLocation_Right
            anchors {
                left: centerIndicator.right
                leftMargin: innerMargin
                verticalCenter: parent.verticalCenter
            }
        }

        ClassicIndicator {
            id: innerTop
            visible: _window.classicIndicators.innerTopIndicatorVisible
            indicatorType: KDDockWidgets.DropLocation_Top
            anchors {
                bottom: centerIndicator.top
                bottomMargin: innerMargin
                horizontalCenter: parent.horizontalCenter
            }
        }

        ClassicIndicator {
            id: innerBottom
            visible: _window.classicIndicators.innerBottomIndicatorVisible
            indicatorType: KDDockWidgets.DropLocation_Bottom
            anchors {
                top: centerIndicator.bottom
                topMargin: innerMargin
                horizontalCenter: parent.horizontalCenter
            }
        }
    }
}

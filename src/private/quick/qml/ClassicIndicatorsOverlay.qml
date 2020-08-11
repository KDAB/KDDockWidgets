/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
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

    ClassicIndicator {
        indicatorType: DropIndicatorOverlayInterface.DropLocation_OutterLeft
        anchors {
            left: parent.left
            leftMargin: outterMargin
            verticalCenter: parent.verticalCenter
        }
    }

    ClassicIndicator {
        indicatorType: DropIndicatorOverlayInterface.DropLocation_OutterRight
        anchors {
            right: parent.right
            rightMargin: outterMargin
            verticalCenter: parent.verticalCenter
        }
    }

    ClassicIndicator {
        indicatorType: DropIndicatorOverlayInterface.DropLocation_OutterTop
        anchors {
            top: parent.top
            topMargin: outterMargin
            horizontalCenter: parent.horizontalCenter
        }
    }

    ClassicIndicator {
        indicatorType: DropIndicatorOverlayInterface.DropLocation_OutterBottom
        anchors {
            bottom: parent.bottom
            bottomMargin: outterMargin
            horizontalCenter: parent.horizontalCenter
        }
    }

    Item {
        id: innerIndicators
        anchors.centerIn: parent
        width: (centerIndicator * 3) + (2 * innerMargin)
        height: width

        ClassicIndicator {
            indicatorType: DropIndicatorOverlayInterface.DropLocation_Left
            anchors {
                right: centerIndicator.left
                rightMargin: innerMargin
                verticalCenter: parent.verticalCenter
            }
        }

        ClassicIndicator {
            id: centerIndicator
            indicatorType: DropIndicatorOverlayInterface.DropLocation_Center
            anchors.centerIn: parent
        }


        ClassicIndicator {
            indicatorType: DropIndicatorOverlayInterface.DropLocation_Right
            anchors {
                left: centerIndicator.right
                leftMargin: innerMargin
                verticalCenter: parent.verticalCenter
            }
        }

        ClassicIndicator {
            indicatorType: DropIndicatorOverlayInterface.DropLocation_Top
            anchors {
                bottom: centerIndicator.top
                bottomMargin: innerMargin
                horizontalCenter: parent.horizontalCenter
            }
        }

        ClassicIndicator {
            indicatorType: DropIndicatorOverlayInterface.DropLocation_Bottom
            anchors {
                top: centerIndicator.bottom
                topMargin: innerMargin
                horizontalCenter: parent.horizontalCenter
            }
        }
    }
}

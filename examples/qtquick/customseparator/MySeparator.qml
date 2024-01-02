/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import QtQuick 2.6

Rectangle {
    id: root
    anchors.fill: parent
    color: "orange"

    // Might be needed as MouseArea overlaps with the dock widgets, since it's bigger than
    // its parent.
    z: 2

    readonly property QtObject kddwSeparator: parent

    MouseArea {
        cursorShape: kddwSeparator ? (kddwSeparator.isVertical ? Qt.SizeVerCursor : Qt.SizeHorCursor)
                                   : Qt.SizeHorCursor

        // Make the MouseArea bigger than its parent, so it can detect mouse easier
        // Since we're using only 2px of thickness.
        readonly property int hoverThreshold: 2
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            bottom: parent.bottom
            leftMargin: (kddwSeparator && !kddwSeparator.isVertical) ? -hoverThreshold : 0
            rightMargin: (kddwSeparator && !kddwSeparator.isVertical) ? -hoverThreshold : 0
            topMargin: (kddwSeparator && kddwSeparator.isVertical) ? -hoverThreshold : 0
            bottomMargin: (kddwSeparator && kddwSeparator.isVertical) ? -hoverThreshold : 0
        }

        // uncomment for debugging your mouse area
        // Rectangle {
        //     color: "red"
        //     anchors.fill: parent
        // }

        onPressed: {
            kddwSeparator.onMousePressed();
        }

        onReleased: {
            kddwSeparator.onMouseReleased();
        }

        onPositionChanged: (mouse) => {
            kddwSeparator.onMouseMoved(Qt.point(mouse.x, mouse.y));
        }

        onDoubleClicked: {
            kddwSeparator.onMouseDoubleClicked();
        }
    }
}

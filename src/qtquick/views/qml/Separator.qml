/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import QtQuick 2.6
import com.kdab.dockwidgets 2.0

Rectangle {
    id: root
    anchors.fill: parent
    color: "#eff0f1"

    readonly property SeparatorView kddwSeparator: parent // qmllint disable incompatible-type

    MouseArea {
        cursorShape: root.kddwSeparator ? (root.kddwSeparator.isVertical ? Qt.SizeVerCursor : Qt.SizeHorCursor) : Qt.SizeHorCursor
        anchors.fill: parent
        onPressed: {
            root.kddwSeparator.onMousePressed();
        }

        onReleased: {
            root.kddwSeparator.onMouseReleased();
        }

        onPositionChanged: mouse => {
            root.kddwSeparator.onMouseMoved(Qt.point(mouse.x, mouse.y));
        }

        onDoubleClicked: {
            root.kddwSeparator.onMouseDoubleClicked();
        }
    }
}

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import "qrc:/"
import QtQuick 2.6
import com.kdab.kddockwidgets.multisplitter 1.0;

Rectangle {
    id: root
    color: "cyan"
    radius: 9
    border {
        color: "black"
        width: 2
    }

    readonly property alias multiSplitterItem: root.parent

    anchors.fill: parent

    Indicator {
        location: KDMultiSplitter.Location_OnLeft;
        anchors.centerIn: parent
        anchors.horizontalCenterOffset: -width
        relativeTo: multiSplitterItem
    }

    Indicator {
        location: KDMultiSplitter.Location_OnRight;
        anchors.centerIn: parent
        anchors.horizontalCenterOffset: width
        relativeTo: multiSplitterItem
    }

    Indicator {
        location: KDMultiSplitter.Location_OnTop;
        anchors.centerIn: parent
        anchors.verticalCenterOffset: -height
        relativeTo: multiSplitterItem
    }

    Indicator {
        location: KDMultiSplitter.Location_OnBottom;
        anchors.centerIn: parent
        anchors.verticalCenterOffset: height
        relativeTo: multiSplitterItem
    }
}

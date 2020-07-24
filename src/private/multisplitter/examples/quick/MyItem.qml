/*
  This file is part of KDDockWidgets.

  Copyright (C) 2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

import "qrc:/"
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

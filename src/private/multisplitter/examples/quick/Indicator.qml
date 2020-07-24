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

import com.kdab.kddockwidgets.multisplitter 1.0;

Image {
    id: root
    property int location: KDMultiSplitter.Location_None;
    property QtObject relativeTo: null

    width: 48
    height: 48

    function locationToStr() {
        switch (root.location) {
        case KDMultiSplitter.Location_OnLeft:
            return "left";
        case KDMultiSplitter.Location_OnRight:
            return "right";
        case KDMultiSplitter.Location_OnTop:
            return "top";
        case KDMultiSplitter.Location_OnBottom:
            return "bottom";
        }
    }

    function imageFileName() {
        if (relativeTo)
            return "inner_%1.png".arg(locationToStr())
        return "outter_%1.png".arg(locationToStr())
    }

    source:  "qrc:///img/classic_indicators/" + imageFileName()

    MouseArea {
        anchors.fill: parent
        onClicked: {
            _controller.addItem(root.location, root.relativeTo);
        }
    }
}

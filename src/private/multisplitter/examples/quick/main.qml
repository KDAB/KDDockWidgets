/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import QtQuick 2.6
import com.kdab.kddockwidgets.multisplitter 1.0

MultiSplitter {
    id: root

    Indicator {
        location: KDMultiSplitter.Location_OnLeft;
        anchors {
            verticalCenter: parent.verticalCenter
            left: parent.left
            leftMargin: 4
        }
        z: 10
    }

    Indicator {
        location: KDMultiSplitter.Location_OnRight;
        anchors {
            verticalCenter: parent.verticalCenter
            right: parent.right
            rightMargin: 4
        }
        z: 10
    }

    Indicator {
        location: KDMultiSplitter.Location_OnTop;
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 4
        }
        z: 10
    }

    Indicator {
        location: KDMultiSplitter.Location_OnBottom;
        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: parent.bottom
            bottomMargin: 4
        }
        z: 10
    }
}

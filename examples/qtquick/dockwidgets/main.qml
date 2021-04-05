/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sergio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import QtQuick 2.6
import QtQuick.Controls 2.12
import com.kdab.dockwidgets 1.0 as KDDW

KDDW.MainWindow {
    id: root

    Repeater {
        model: 3
        KDDW.DockWidget {
            uniqueName: "fromRepeater-" + index
            source: ":/Another.qml"
        }
    }

    KDDW.DockWidget {
        id: dock4
        uniqueName: "dock4"
        source: ":/Another.qml"
    }

    Button {
        text: "Toggle Another"
        anchors {
            bottom: parent.bottom
            left: parent.left
            margins: 5
        }
        z: 10

        onClicked: {
            if (dock4.dockWidget.visible) {
                dock4.dockWidget.close();
            } else {
                dock4.dockWidget.show();
            }
        }
    }

    Component.onCompleted: {
        root.init("MyWindowName-1");
    }
}

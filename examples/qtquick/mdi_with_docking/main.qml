/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sergio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import QtQuick 2.6
import QtQuick.Controls 2.12
import com.kdab.dockwidgets 2.0 as KDDW

ApplicationWindow {
    visible: true
    width: 1300
    height: 1300

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")

            Action {
                text: qsTr("Close All")
                onTriggered: {
                   _kddwDockRegistry.clear();
                }
            }

            MenuSeparator { }
            Action { text: qsTr("&Quit")
                onTriggered: {
                    Qt.quit();
                }
            }
        }
    }

    KDDW.DockingArea {
        options: KDDW.KDDockWidgets.MainWindowOption_HasCentralWidget
        anchors.fill: parent

        // Each main layout needs a unique id
        uniqueName: "MainLayout-1"

        KDDW.DockWidget {
            id: dock5
            uniqueName: "dock5"
            Rectangle {
                id: guest
                color: "pink"
                anchors.fill: parent
            }
        }

        KDDW.DockWidget {
            id: dock6
            uniqueName: "dock6"
            Rectangle {
                color: "black"
                anchors.fill: parent
            }
        }

        Component.onCompleted: {
            // Add dock4 to the Bottom location
            addDockWidget(dock5, KDDW.KDDockWidgets.Location_OnLeft, null, Qt.size(150, 0));

            // Add dock5 to the left of dock4
            addDockWidget(dock6, KDDW.KDDockWidgets.Location_OnBottom, null, Qt.size(0, 150));
        }
    }
}

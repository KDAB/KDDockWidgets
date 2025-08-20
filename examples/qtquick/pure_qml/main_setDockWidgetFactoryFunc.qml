/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2025 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sergio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// This example shows how to use KDDockWidgets::Config::setDockWidgetFactoryFunc() in pure QML
// If you don't know what it is, you can ignore this example, as it's not a common use case.
// See the documentation in Config.h for more information
//
// Usage:
//
// Run main_example1.qml and "File->Save Layout" and quit.
// Run main_setDockWidgetFactoryFunc.qml and "File->Restore", it should recreate the original layout
// with dock widgets created dynamically.
//
// $ cd pure_qml/
// $ qml -I <kddw build directory> main_example1.qml -platform xcb
// $ qml -I <kddw build directory> main_setDockWidgetFactoryFunc.qml -platform xcb

import QtQuick 2.6
import QtQuick.Controls 2.12
import com.kdab.dockwidgets 2.0 as KDDW

ApplicationWindow {
    id: window
    visible: true
    width: 1000
    height: 800

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")

            Action {
                text: qsTr("Restore layout")
                onTriggered: {
                    layoutSaver.restoreFromFile("mySavedLayout.json");
                }
            }

            MenuSeparator {}

            Action {
                text: qsTr("&Quit")
                onTriggered: {
                    Qt.quit();
                }
            }
        }
    }

    KDDW.DockingArea {
        id: root
        anchors.fill: parent

        uniqueName: "MainLayout-1"
    }

    KDDW.LayoutSaver {
        id: layoutSaver
    }

    Component {
        id: dockWidgetComponent
        KDDW.DockWidget {
            Rectangle {
                color: "blue"
                anchors.fill: parent
            }
        }
    }

    Component.onCompleted: {
        KDDW.Config.dockWidgetFactoryFunc = function (dockWidgetId) {
            console.log("QML: Creating dockwidget " + dockWidgetId);

            var dockWidget = dockWidgetComponent.createObject(null, {
                uniqueName: dockWidgetId
            });

            return dockWidget;
        };
    }
}

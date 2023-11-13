/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sergio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/// @brief Tests that focus is restored to the line edits when changing tab

import QtQuick 2.6
import QtQuick.Controls 2.12
import com.kdab.dockwidgets 2.0 as KDDW

ApplicationWindow {
    visible: true
    width: 1000
    height: 800

    KDDW.DockingArea {
        anchors.fill: parent
        uniqueName: "MyWindowName-1"

        KDDW.DockWidget {
            id: dock1
            uniqueName: "dock1"
            Rectangle {
                objectName: "guest1rectangle"
                anchors.fill: parent
                color: "#475B63"
                TextInput {
                    text: "dock1 focus=" + focus + "; activeFocus=" + activeFocus
                    focus: true
                    anchors.margins: 10
                    anchors.left: parent.left
                    onFocusChanged: {
                      console.log("FOO111 " + focus);
                      _kddwDockRegistry.halt();
                    }
                }
                onFocusChanged: {
                    console.log("Guest1.focusChanged " + focus);
                }
            }
        }

        KDDW.DockWidget {
            id: dock2
            uniqueName: "dock2"
            Rectangle {
                anchors.fill: parent
                color: "#729B79"
                TextInput {
                    id: field2
                    text: "dock2 focus=" + focus + "; activeFocus=" + activeFocus
                    focus: true
                    anchors.margins: 10
                    anchors.left: parent.left
                }
                Button {
                    text: "focus"
                    anchors.right: parent.right
                    onClicked: {
                      field2.focus = true;
                    }
                }
            }
        }

        KDDW.DockWidget {
            id: dock3
            uniqueName: "dock3"
            Rectangle {
                anchors.fill: parent
                color: "#BACDB0"
                TextInput {
                    id: field3
                    text: "dock3 focus=" + focus + "; activeFocus=" + activeFocus
                    focus: true
                    anchors.margins: 10
                    anchors.left: parent.left
                    // onFocusChanged: {
                    //   console.log("FOO " + focus);
                    //   _kddwDockRegistry.halt();
                    // }
                }
                Button {
                    text: "focus"
                    anchors.right: parent.right
                    onClicked: {
                      field3.focus = true;
                    }
                }
            }
        }

        Component.onCompleted: {
            // Add dock4 to the Bottom location
            addDockWidget(dock1, KDDW.KDDockWidgets.Location_OnLeft);
            addDockWidget(dock2, KDDW.KDDockWidgets.Location_OnRight);
            dock2.addDockWidgetAsTab(dock3);
        }
    }
}

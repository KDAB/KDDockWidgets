/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sergio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import QtQuick 2.6

// Will be moved to a plugin in the future, if there's enough demand
import "qrc:/kddockwidgets/qtquick/views/qml/" as KDDW

/// Example of a QML Tab Bar that doesn't use QtQuick.Controls, just for demo purposes.
/// Se the comments named "#HERE#" for important things you shouldn't forget.

KDDW.TabBarBase {
    id: root

    implicitHeight: 30
    currentTabIndex: 0

    /// #HERE#. This function required in all derived tab bars. It's called by C++;
    /// Returns the tab bar (QQuickItem*) at the specified index.
    function getTabAtIndex(index) {
        return tabBarRow.children[index];
    }

    /// #HERE#. This function required in all derived tab bars. It's called by C++;
    /// Returns an int, with the index of the tab that's at the specified position.
    function getTabIndexAtPosition(globalPoint) {
        for (var i = 0; i < tabBarRow.children.length; ++i) {
            var tab = tabBarRow.children[i];
            var localPt = tab.mapFromGlobal(globalPoint.x, globalPoint.y);
            if (tab.contains(localPt)) {
                return i;
            }
        }

        return -1;
    }

    Row {
        id: tabBarRow

        /// #HERE#: If you're going to add any custom MouseAreas please use set a higher Z than the builtin one
        z: root.mouseAreaZ.z + 1

        anchors.fill: parent
        spacing: 2

        /// Needed only if you want to style hovered tabs differently
        property int hoveredIndex: -1;

        /// ##HERE## The list of tabs is stored in a C++ model. This repeater populates our tab bar
        Repeater {
            model: root.groupCpp ? root.groupCpp.tabBar.dockWidgetModel : 0
            Rectangle {
                id: tab
                height: parent.height
                width: 150
                color: (tabBarRow.hoveredIndex == index) ? "#ba7600" : "orange"
                border.color: "black"

                // ##HERE## Illustrating how to have a different style in case the tab is current
                border.width: index == root.groupCpp.currentIndex ? 3 : 1

                // ##HERE## The index of the tab. This is required in all custom tab bar implementations
                // It is be used by "getTabAtIndex()" and "getTabIndexAtPosition()" functions
                readonly property int tabIndex: index

                Text {
                    anchors.centerIn: parent
                    text: title
                }

                // Optionally, and for illustration purposes, we add a close button
                Rectangle {
                    id: closeButton
                    color: "transparent"
                    radius: 3
                    border.width: closeButtonMouseArea.containsMouse ? 1 : 0
                    border.color: "black"

                    height: 17
                    width: height
                    anchors {
                        right: parent.right
                        rightMargin: 4
                        verticalCenter: parent.verticalCenter
                    }
                    Image {
                        source: "qrc:/img/close.png"
                        anchors.centerIn: parent

                        MouseArea {
                            id: closeButtonMouseArea
                            anchors.fill: parent
                            hoverEnabled: true
                            onClicked: {
                                tabBarCpp.closeAtIndex(index);
                            }
                        }
                    }
                }
            }
        }

        Connections {
            target: tabBarCpp

            function onHoveredTabIndexChanged(index) {
                tabBarRow.hoveredIndex = index;
            }
        }
    }
}

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
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
        return tabBar.children[index];
    }

    /// #HERE#. This function required in all derived tab bars. It's called by C++;
    /// Returns an int, with the index of the tab that's at the specified position.
    function getTabIndexAtPosition(globalPoint) {
        for (var i = 0; i < tabBar.children.length; ++i) {
            var tab = tabBar.children[i];
            var localPt = tab.mapFromGlobal(globalPoint.x, globalPoint.y);
            if (tab.contains(localPt)) {
                return i;
            }
        }

        return -1;
    }

    Row {
        id: tabBar

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
                width: 100
                color: (tabBar.hoveredIndex == index) ? "#ba7600" : "orange"
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

                /// ##HERE## Tells the C++ backend that the current tab should change
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        root.currentTabIndex = index;
                    }
                }
            }
        }

        Connections {
            target: tabBarCpp

            function onHoveredTabIndexChanged(index) {
                tabBar.hoveredIndex = index;
            }
        }
    }
}

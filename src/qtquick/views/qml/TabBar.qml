/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import QtQuick 2.9
import QtQuick.Controls 2.9


TabBarBase {
    id: root

    function getTabAtIndex(index) {

        // Iterate the internal ListView's children to find our tab
        for(var i = 0; i < tabBar.children.length; ++i) {
            var isListView = tabBar.children[i].toString().startsWith("QQuickListView");
            if (isListView) {
                var listView = tabBar.children[i];
                if (index < listView.children.length)
                    return listView.children[0].children[index];
            }
        }

        return null;
    }

    implicitHeight: tabBar.implicitHeight

    onCurrentTabIndexChanged: {
        // A change coming from C++
        tabBar.currentIndex = root.currentTabIndex
    }

    TabBar {
        id: tabBar

        width: parent.width

        onCurrentIndexChanged: {
            // Tells the C++ backend that the current dock widget has changed
            root.currentTabIndex = this.currentIndex
        }



        // If the currentIndex changes in the C++ backend then update it here
        Connections {
            target: root.groupCpp
            function onCurrentIndexChanged() {
                root.currentTabIndex = groupCpp.currentIndex;
            }
        }

        Repeater {
            /// The list of tabs is stored in a C++ model. This repeater populates our TabBar.
            model: root.groupCpp ? root.groupCpp.tabWidget.dockWidgetModel : 0
            TabButton {
                readonly property int tabIndex: index
                text: title
            }
        }
    }
}

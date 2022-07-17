/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import QtQuick 2.9
import QtQuick.Controls 2.9

Item {
        id: root

        readonly property bool hasCustomMouseEventRedirector: parent.hasCustomMouseEventRedirector

        /// This is our C++ Group_qtquick.cpp
        readonly property QtObject groupCpp: parent.groupCpp

        /// This is our C++ TabBar_qtquick.cpp
        readonly property QtObject tabBarCpp: groupCpp ? groupCpp.tabWidget.tabBar : null

        /// The number of tabs
        readonly property int count: groupCpp ? groupCpp.tabWidget.dockWidgetModel.count : 0

        property int currentTabIndex: -1

        /// Don't override in custom TabBar's.
        visible: tabBarCpp ? (tabBarCpp.tabBarAutoHide ? count > 1 : true) : count > 1

        /// Don't override in custom TabBar's. Change implicitHeight instead.
        height: visible ? implicitHeight : 0

        /// Feel free to customize
        width: parent ? parent.width : 0

        onCurrentTabIndexChanged: {
            // Tells the C++ backend that the current dock widget has changed
            if (groupCpp)
                groupCpp.tabWidget.setCurrentDockWidget(currentTabIndex);
        }

        // If the currentIndex changes in the C++ backend then update it here
        Connections {
            target: root.groupCpp
            function onCurrentIndexChanged() {
                root.currentTabIndex =  groupCpp.currentIndex;
            }
        }

        onTabBarCppChanged: {
            if (tabBarCpp) {
                if (!root.hasCustomMouseEventRedirector)
                    tabBarCpp.redirectMouseEvents(dragMouseArea)

                // Setting just so the unit-tests can access the buttons
                tabBarCpp.tabBarQmlItem = this;
            }
        }
    }

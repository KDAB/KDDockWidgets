/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import QtQuick 2.9
import QtQuick.Controls 2.9

TabBar {
        id: root

        property bool hasCustomMouseEventRedirector: false

        /// This is our C++ Group_qtquick.cpp
        property QtObject groupCpp: null

        /// This is our C++ TabBar_qtquick.cpp
        property QtObject tabBarCpp: groupCpp ? groupCpp.tabWidget.tabBar : null

        /// Don't override in custom TabBar's.
        visible: tabBarCpp ? (tabBarCpp.tabBarAutoHide ? count > 1 : true) : count > 1

        /// Don't override in custom TabBar's. Change implicitHeight instead.
        height: visible ? implicitHeight : 0

        /// Feel free to customize
        width: parent ? parent.width : 0

        onCurrentIndexChanged: {
            // Tells the C++ backend that the current dock widget has changed
            if (groupCpp)
                groupCpp.tabWidget.setCurrentDockWidget(currentIndex);
        }

        onTabBarCppChanged: {
            if (tabBarCpp) {
                if (!root.hasCustomMouseEventRedirector)
                    tabBarCpp.redirectMouseEvents(dragMouseArea)

                // Setting just so the unit-tests can access the buttons
                tabBarCpp.tabBarQmlItem = this;
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

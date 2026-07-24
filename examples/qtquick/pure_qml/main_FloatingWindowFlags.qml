/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sergio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// This example shows the effect of each KDDW.KDDockWidgets.FloatingWindowFlags value.
// Pick an entry from the "Floating Window Flags" menu and a new dock widget will be
// created and opened floating, with only that flag set.
//
// Usage:
//
// $ cd pure_qml/
// $ qml -I <kddw build directory> FloatingWindowFlags.qml -platform xcb

import QtQuick 2.6
import QtQuick.Controls 2.12
import com.kdab.dockwidgets 2.0 as KDDW

ApplicationWindow {
    id: window
    visible: true
    width: 1000
    height: 800
    title: qsTr("FloatingWindowFlags example")

    menuBar: MenuBar {
        Menu {
            title: qsTr("&Floating Window Flags")

            Action {
                text: qsTr("NoFlags")
                onTriggered: createDockWidgetWithFlag("NoFlags")
            }

            Action {
                text: qsTr("FromGlobalConfig")
                onTriggered: createDockWidgetWithFlag("FromGlobalConfig")
            }

            Action {
                text: qsTr("TitleBarHasMinimizeButton")
                onTriggered: createDockWidgetWithFlag("TitleBarHasMinimizeButton")
            }

            Action {
                text: qsTr("TitleBarHasMaximizeButton")
                onTriggered: createDockWidgetWithFlag("TitleBarHasMaximizeButton")
            }

            Action {
                text: qsTr("KeepAboveIfNotUtilityWindow")
                onTriggered: createDockWidgetWithFlag("KeepAboveIfNotUtilityWindow")
            }

            Action {
                text: qsTr("NativeTitleBar")
                onTriggered: createDockWidgetWithFlag("NativeTitleBar")
            }

            Action {
                text: qsTr("HideTitleBarWhenTabsVisible")
                onTriggered: createDockWidgetWithFlag("HideTitleBarWhenTabsVisible")
            }

            Action {
                text: qsTr("AlwaysTitleBarWhenFloating")
                onTriggered: createDockWidgetWithFlag("AlwaysTitleBarWhenFloating")
            }

            Action {
                text: qsTr("DontUseParentForFloatingWindows")
                onTriggered: createDockWidgetWithFlag("DontUseParentForFloatingWindows")
            }

            Action {
                text: qsTr("UseQtWindow")
                onTriggered: createDockWidgetWithFlag("UseQtWindow")
            }

            Action {
                text: qsTr("UseQtTool")
                onTriggered: createDockWidgetWithFlag("UseQtTool")
            }

            Action {
                text: qsTr("StartsMinimized")
                onTriggered: createDockWidgetWithFlag("StartsMinimized")
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

        // Each main layout needs a unique id
        uniqueName: "MainLayout-1"

        KDDW.DockWidget {
            id: instructions
            uniqueName: "instructions"
            title: qsTr("Instructions")

            Rectangle {
                anchors.fill: parent
                color: "#f0f0f0"

                Text {
                    anchors.centerIn: parent
                    anchors.margins: 20
                    width: parent.width - 40
                    wrapMode: Text.WordWrap
                    text: qsTr("Use the \"Floating Window Flags\" menu to create a new floating dock widget with a single KDDW.KDDockWidgets.FloatingWindowFlags value applied.")
                }
            }
        }

        Component.onCompleted: {
            addDockWidget(instructions, KDDW.KDDockWidgets.Location_OnLeft);
        }
    }

    // Creates a new dock widget, sets a single floatingWindowFlags value on it and opens
    // it floating, so its effect on the floating window can be observed.
    function createDockWidgetWithFlag(flagName) {
        var uniqueName = KDDW.Singletons.helpers.generateUuid();

        var code = `import com.kdab.dockwidgets 2.0 as KDDW;
                    import QtQuick 2.6;
                    KDDW.DockWidget {
                        uniqueName: "${uniqueName}";
                        title: "${flagName}";
                        floatingWindowFlags: KDDW.KDDockWidgets.FloatingWindowFlags.${flagName};
                        Rectangle {
                            color: "#85baa1";
                            anchors.fill: parent;
                            Text {
                                anchors.centerIn: parent
                                text: "${flagName}"
                            }
                        }
                    }`;

        var newDW = Qt.createQmlObject(code, root);
        newDW.open();
    }
}

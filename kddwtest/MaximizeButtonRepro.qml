// Bug 3: Flag_TitleBarHasMaximizeButton removes the undock button on MDI docks
// without adding a maximize button.
//
// Steps to reproduce:
//   1. In main.cpp, uncomment the Flag_TitleBarHasMaximizeButton line
//      (it is right above the initFrontend() call).
//   2. Rebuild and run — the flag must be set before initFrontend().
//   3. Open this tab. Observe the MDI dock title bar: the undock button is gone.
//   4. No maximize button appears in its place.
//
// Root cause:
//   TitleBar::supportsFloatingButton() returns false whenever
//   Flag_TitleBarHasMaximizeButton is set — regardless of context.
//   TitleBar::supportsMaximizeButton() returns false for MDI docks because it
//   requires m_floatingWindow != nullptr. The two conditions together mean the
//   flag removes the only button and adds nothing.
//
// Expected:
//   On MDI docks (not yet floating), the undock button should remain.
//   On floating windows, the maximize button should appear and the undock
//   button may be hidden. The mutual exclusion should be context-sensitive.

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import com.kdab.dockwidgets 2.0 as KDDW

Item {
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 8
        spacing: 8

        Label {
            text: "Bug 2: Flag_TitleBarHasMaximizeButton removes the undock button on MDI docks without adding a maximize button"
            font.bold: true
            wrapMode: Text.WordWrap
            Layout.fillWidth: true
        }

        Label {
            text: "To reproduce: in main.cpp uncomment the Flag_TitleBarHasMaximizeButton line, rebuild, and run.\n" +
                  "With the flag active the MDI dock below has no undock button AND no maximize button."
            wrapMode: Text.WordWrap
            Layout.fillWidth: true
        }

        KDDW.MDIDockingArea {
            id: mdiArea2
            uniqueName: "bug2-mdi"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

    KDDW.DockWidget {
        id: bug2Dock
        uniqueName: "bug2-dock"
        title: "No undock button, no maximize button"

        Rectangle {
            color: "#dce"
            anchors.fill: parent
            Label {
                anchors.centerIn: parent
                text: "With Flag_TitleBarHasMaximizeButton set:\n" +
                      "• undock button is gone\n" +
                      "• maximize button does not appear\n" +
                      "(supportsMaximizeButton() requires m_floatingWindow)"
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WordWrap
            }
        }
    }

    Component.onCompleted: {
        mdiArea2.addDockWidget(bug2Dock, Qt.point(40, 40))
    }
}

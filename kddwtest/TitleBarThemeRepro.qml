// Bug 6: KDDW titlebar does not follow the active QtQuick Controls theme.
//
// Steps to reproduce:
//   Set your OS to dark mode, then run the application.
//   QQC2 automatically picks up the OS dark theme (via QPA / platform theme).
//
//   1. Observe that the application background and controls are dark.
//   2. The KDDW dock titlebar remains light-coloured (hardcoded grey) and does
//      not adapt to the dark theme.
//
// Root cause:
//   The KDDW QML titlebar (TitleBar.qml / TitleBarBase.qml inside KDDW) is
//   painted with hardcoded colours / Rectangle fills rather than reading from
//   the active palette (SystemPalette or Control.palette). It does not inherit
//   from a QQC2 Control, so it never participates in palette propagation.
//
// Expected:
//   The titlebar should derive its colours from the active QQC2 palette so
//   that it looks correct in any theme (dark OS, high-contrast, custom palette).

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import com.kdab.dockwidgets 2.0 as KDDW

Item {
    id: root

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 8
        spacing: 8

        Label {
            text: "Bug 6: KDDW titlebar ignores the QtQuick Controls theme"
            font.bold: true
            wrapMode: Text.WordWrap
            Layout.fillWidth: true
        }

        Label {
            text: "Set your OS to dark mode and run the app.\n" +
                  "QQC2 picks up the OS dark theme automatically.\n" +
                  "The application background turns dark but the KDDW dock\n" +
                  "titlebar stays hardcoded light grey."
            wrapMode: Text.WordWrap
            Layout.fillWidth: true
        }

        KDDW.MDIDockingArea {
            id: mdiArea6
            uniqueName: "bug6-mdi"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

    KDDW.DockWidget {
        id: bug6Dock
        uniqueName: "bug6-dock"
        title: "This titlebar should match the dark theme"

        Rectangle {
            anchors.fill: parent
            color: window.palette.base
            Label {
                anchors.centerIn: parent
                text: "Content correctly follows the OS dark theme palette.\n" +
                      "Compare it with the titlebar above."
                color: window.palette.text
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WordWrap
            }
        }
    }

    Component.onCompleted: {
        mdiArea6.addDockWidget(bug6Dock, Qt.point(40, 40))
    }
}

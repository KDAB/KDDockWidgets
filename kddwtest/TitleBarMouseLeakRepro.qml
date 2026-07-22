// Bug 5: KDDW MDI titlebar leaks mouse events to content underneath.
//
// Steps to reproduce:
//   1. Two docks are opened: "Back" (with a SplitView) and "Front" (on top).
//      The front dock is positioned so its titlebar overlaps the SplitView
//      resize handle in the back dock.
//   2. Hover the mouse over the front dock's titlebar, near the split handle
//      visible underneath it.
//   3. Observe that the cursor changes to a horizontal resize arrow (↔) even
//      though the mouse is over the front dock's titlebar — it should be the
//      default arrow cursor.
//
// Root cause:
//   The KDDW titlebar QQuickItem does not install a HoverHandler that accepts
//   and overrides the cursor, and does not call event->accept() for hover
//   events. Qt's input delivery therefore walks past the titlebar and finds the
//   SplitView handle in the dock below, which sets the ↔ cursor.
//
// Expected:
//   Moving the mouse over any part of a titlebar should always produce the
//   default arrow cursor, regardless of what is rendered underneath.

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
            text: "Bug 5: KDDW titlebar leaks mouse events"
            font.bold: true
            wrapMode: Text.WordWrap
            Layout.fillWidth: true
        }

        Label {
            text: "The \"Front\" dock's titlebar overlaps the SplitView handle in the \"Back\" dock.\n" +
                  "Hover over the front titlebar near the handle: the splitter shows a hover effect."
            wrapMode: Text.WordWrap
            Layout.fillWidth: true
        }

        KDDW.MDIDockingArea {
            id: mdiArea5
            uniqueName: "bug5-mdi"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

    // Back dock: contains a SplitView whose resize handle is the cursor source.
    KDDW.DockWidget {
        id: backDock
        uniqueName: "bug5-back-dock"
        title: "Back dock (SplitView inside)"

        SplitView {
            anchors.fill: parent
            orientation: Qt.Horizontal

            Rectangle {
                SplitView.preferredWidth: 120
                color: "#cde"
                Label { anchors.centerIn: parent; text: "Left\npane"; horizontalAlignment: Text.AlignHCenter }
            }
            Rectangle {
                color: "#dce"
                Label { anchors.centerIn: parent; text: "Right\npane"; horizontalAlignment: Text.AlignHCenter }
            }
        }
    }

    // Front dock: positioned so its titlebar sits right over the split handle.
    KDDW.DockWidget {
        id: frontDock
        uniqueName: "bug5-front-dock"
        title: "hover here     -> <- (titlebar over the split handle)"

        Rectangle {
            color: "#edc"
            anchors.fill: parent
            Label {
                anchors.centerIn: parent
                text: "Front dock content"
            }
        }
    }

    Component.onCompleted: {
        backDock.width  = 400
        backDock.height = 260
        mdiArea5.addDockWidget(backDock, Qt.point(20, 20))

        frontDock.width  = 260
        frontDock.height = 160
        mdiArea5.addDockWidget(frontDock, Qt.point(40, 80))
    }
}

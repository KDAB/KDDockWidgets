// Bug 1: OS titlebar close button on a floating MDI window does not emit
// DockWidget::closed.
//
// Steps to reproduce:
//   1. Click "Open Dock" to add a dock to the MDI area.
//   2. Drag the dock by its title bar to undock it into a floating OS window.
//   3. Close the floating window using the OS titlebar X button.
//   4. The status label still says "Dock is open" — closed() was never emitted.
//   5. Click "Open Dock" again. Nothing happens — the dock is still registered
//      in DockRegistry under its uniqueName, so KDDW finds the existing (hidden)
//      instance instead of creating a new one.
//
// Root cause:
//   QuickView::event() in src/qtquick/views/FloatingWindow.cpp does not handle
//   QEvent::Close. The event falls through to QQuickView::event() which hides
//   the window but never calls FloatingWindow::onCloseEvent, so the
//   DockWidget::closed signal is never emitted.
//
// Expected:
//   Closing the OS window should emit DockWidget::closed and unregister the
//   dock from DockRegistry, allowing it to be re-opened.

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
            text: "Bug 1: OS titlebar close of a floating MDI window does not emit closed()"
            font.bold: true
            wrapMode: Text.WordWrap
            Layout.fillWidth: true
        }

        Label {
            id: statusLabel
            text: "Dock is not open."
            wrapMode: Text.WordWrap
            Layout.fillWidth: true
        }

        Button {
            text: "Open Dock"
            onClicked: {
                if (bugDock.isOpen) {
                    statusLabel.text = "Dock is already open (re-open failed — stuck in DockRegistry)."
                    return
                }
                mdiArea.addDockWidget(bugDock, Qt.point(40, 40))
                statusLabel.text = "Dock is open. Undock it, then close via OS X button."
            }
        }

        KDDW.MDIDockingArea {
            id: mdiArea
            uniqueName: "bug1-mdi"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

    KDDW.DockWidget {
        id: bugDock
        uniqueName: "bug1-dock"
        title: "Close me via the OS X button"

        onClosed: {
            statusLabel.text = "closed() signal received — dock is gone. Re-open works now."
        }

        Rectangle {
            color: "#cde"
            anchors.fill: parent
            Label {
                anchors.centerIn: parent
                text: "1. Drag me out to float\n2. Close via OS titlebar X\n3. Check the status above"
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }
}

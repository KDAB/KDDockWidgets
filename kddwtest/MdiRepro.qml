// Bug 4: Per-dock FloatingWindowFlags cannot be set from QML.
//
// Steps to reproduce:
//   1. Observe the dock below — drag it out to float.
//   2. The floating window has the default title-bar buttons (close, float).
//   3. There is no QML property on DockWidget to customise which buttons
//      appear in the floating window's title bar (e.g. hide the close button,
//      add a maximize button, etc.).
//
// Root cause:
//   DockWidget::setFloatingWindowFlags(FloatingWindowFlags) exists in C++ and
//   controls which buttons appear when this specific dock is floating.
//   The corresponding property is not exposed to QML — there is no
//   floatingWindowFlags QML property on the DockWidget QML type, and
//   FloatingWindowFlags is not registered as a QML enum / flags type.
//
// Workaround:
//   None from pure QML. C++-side code can call
//   dockWidget->setFloatingWindowFlags(...) after obtaining the C++ pointer,
//   but that requires mixing C++ and QML.
//
// Expected:
//   DockWidget should expose a floatingWindowFlags property in QML, e.g.:
//
//     KDDW.DockWidget {
//         floatingWindowFlags: KDDW.KDDockWidgets.FloatingWindowFlag_TitleBarHasMaximizeButton
//     }

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
            text: "Bug 4: Per-dock FloatingWindowFlags cannot be set from QML"
            font.bold: true
            wrapMode: Text.WordWrap
            Layout.fillWidth: true
        }

        Label {
            text: "DockWidget.setFloatingWindowFlags() exists in C++ but is not exposed as a QML property.\n" +
                  "There is no way to customise per-dock floating title-bar buttons from QML alone.\n\n" +
                  "Drag the dock below out to float — you cannot control which buttons appear from QML."
            wrapMode: Text.WordWrap
            Layout.fillWidth: true
        }

        KDDW.MDIDockingArea {
            id: mdiArea4
            uniqueName: "bug4-mdi"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

    KDDW.DockWidget {
        id: bug4Dock
        uniqueName: "bug4-dock"
        title: "No floatingWindowFlags property in QML"

        // Ideally we could write:
        //   floatingWindowFlags: KDDW.KDDockWidgets.FloatingWindowFlag_TitleBarHasMaximizeButton
        // but that property does not exist on the QML type.

        Rectangle {
            color: "#ced"
            anchors.fill: parent
            Label {
                anchors.centerIn: parent
                text: "Drag me out to float.\n" +
                      "Floating title-bar buttons cannot be\n" +
                      "customised from QML (no floatingWindowFlags property)."
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WordWrap
            }
        }
    }

    Component.onCompleted: {
        mdiArea4.addDockWidget(bug4Dock, Qt.point(40, 40))
    }
}

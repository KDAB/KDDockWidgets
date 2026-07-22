// Bug 2: Initial dock size cannot be set from QML.
//
// The left dock uses the workaround: set dockWidget.width/height before
// adding it. The right dock has no size hint and opens tiny.
//
// Root cause:
//   InitialOption is not constructible from QML, so addDockWidget() cannot
//   be given an initial size from QML.

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
            text: "Bug 3: Initial dock size cannot be set from QML"
            font.bold: true
            wrapMode: Text.WordWrap
            Layout.fillWidth: true
        }

        Label {
            text: "The workaround dock sets dockWidget.width/height before adding it.\n" +
                  "The other dock has no size hint and opens tiny."
            wrapMode: Text.WordWrap
            Layout.fillWidth: true
        }

        KDDW.MDIDockingArea {
            id: mdiArea3
            uniqueName: "bug3-mdi"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

    KDDW.DockWidget {
        id: dockWithSize
        uniqueName: "bug3-dock-sized"
        width: 320
        height: 100

        title: "Workaround"

        Rectangle {
            color: "#cdc"
            anchors.fill: parent
            Label {
                anchors.centerIn: parent
                text: "320 × 200\n(workaround via dockWidget.width/height)"
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }

    KDDW.DockWidget {
        id: dockNoSize
        uniqueName: "bug3-dock-unsized"
        width: 520
        height: 800

        title: "This should be 520x800"
        Rectangle {
            color: "#edd"
            implicitWidth: 24
            implicitHeight: 24
            Label {
                anchors.centerIn: parent
                text: "This should be 520x800, but it is " + dockNoSize.dockWidget.width + "x" + dockNoSize.dockWidget.height
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }

    Component.onCompleted: {
        dockWithSize.dockWidget.width = 320;
        dockWithSize.dockWidget.height = 200;
        mdiArea3.addDockWidget(dockWithSize, Qt.point(20, 20));

        mdiArea3.addDockWidget(dockNoSize, Qt.point(360, 20));
    }
}

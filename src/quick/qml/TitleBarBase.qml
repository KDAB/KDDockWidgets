import QtQuick 2.9

Rectangle {
    id: root

    property QtObject titleBarCpp
    readonly property string title: titleBarCpp ? titleBarCpp.title : ""

    visible: titleBarCpp && titleBarCpp.visible
    implicitHeight: 30
}

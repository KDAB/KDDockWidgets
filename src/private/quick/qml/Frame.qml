import QtQuick 2.9

Rectangle {
    id: root
    property QtObject frameCpp

    color: "cyan"
    anchors.fill: parent

    TitleBar {
        height: 30
        titleBarCpp: frameCpp ? frameCpp.titleBar : null
        anchors {
            top:  parent.top
            left: parent.left
            right: parent.right
        }
    }
}

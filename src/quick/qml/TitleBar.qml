import QtQuick 2.9

TitleBarBase {
    id: root

    Text {
        id: title
        text: root.title
        anchors {
            left: parent.left
            leftMargin: 5
        }
    }

    Rectangle {
        id: floatButton
        color: "red"
        anchors {
            top: parent.top
            bottom: parent.bottom
            right: closeButton.left
            topMargin: 5
            bottomMargin: 5
            rightMargin: 5
        }
        width: height

        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log("Float clicked")
            }
        }
    }

    Rectangle {
        id: closeButton
        color: "red"
        anchors {
            top: parent.top
            bottom: parent.bottom
            right: parent.right
            topMargin: 5
            bottomMargin: 5
            leftMargin: 5
        }
        width: height
        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log("Close clicked")
            }
        }
    }
}

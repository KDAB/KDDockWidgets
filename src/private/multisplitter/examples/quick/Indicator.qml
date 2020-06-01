import QtQuick 2.6
import com.kdab.kddockwidgets.multisplitter 1.0;

Rectangle {
    id: root
    property int location: KDMultiSplitter.Location_None;
    property QtObject relativeTo: null

    color: "yellow"
    width: 35
    height: 35
    radius: 4
    border.color: "black"
    border.width: 2

    MouseArea {
        anchors.fill: parent
        onClicked: {
            _controller.addItem(root.location, root.relativeTo);
        }
    }
}

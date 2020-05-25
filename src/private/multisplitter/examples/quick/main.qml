import com.kdab.kddockwidgets.multisplitter 1.0
import QtQuick 2.6

MultiSplitter {
    id: root
    MouseArea {
        anchors.fill: parent
        onClicked: {
            _controller.addItem();
        }
    }
}

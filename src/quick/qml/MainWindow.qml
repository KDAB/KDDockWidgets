import QtQuick 2.9
import com.kdab.dockwidgets 1.0

MainWindowQuick {
    id: root
    dropArea: dropArea
    anchors.fill: parent

    Item {
        id: centralItem // mimic the hierarchy of QtWidgets
        anchors.fill: parent

        DropAreaWithCentralFrame {
            id: dropArea
            anchors.fill: parent
        }
    }
}

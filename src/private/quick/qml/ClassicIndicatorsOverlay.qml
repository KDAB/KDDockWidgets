import QtQuick 2.9
import com.kdab.dockwidgets 1.0

Item {
    id: root
    anchors.fill: parent
    readonly property int outterMargin: 10

    ClassicIndicator {
        indicatorType: DropIndicatorOverlayInterface.DropLocation_OutterLeft
        anchors {
            left: parent.left
            leftMargin: outterMargin
            verticalCenter: parent.verticalCenter
        }
    }

    ClassicIndicator {
        indicatorType: DropIndicatorOverlayInterface.DropLocation_OutterRight
        anchors {
            right: parent.right
            rightMargin: outterMargin
            verticalCenter: parent.verticalCenter
        }
    }

    ClassicIndicator {
        indicatorType: DropIndicatorOverlayInterface.DropLocation_OutterTop
        anchors {
            top: parent.top
            topMargin: outterMargin
            horizontalCenter: parent.horizontalCenter
        }
    }

    ClassicIndicator {
        indicatorType: DropIndicatorOverlayInterface.DropLocation_OutterBottom
        anchors {
            bottom: parent.bottom
            bottomMargin: outterMargin
            horizontalCenter: parent.horizontalCenter
        }
    }
}

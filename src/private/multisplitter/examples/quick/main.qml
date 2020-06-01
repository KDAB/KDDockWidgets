import com.kdab.kddockwidgets.multisplitter 1.0
import QtQuick 2.6

MultiSplitter {
    id: root

    Indicator {
        location: KDMultiSplitter.Location_OnLeft;
        anchors {
            verticalCenter: parent.verticalCenter
            left: parent.left
            leftMargin: 4
        }
        z: 10
    }

    Indicator {
        location: KDMultiSplitter.Location_OnRight;
        anchors {
            verticalCenter: parent.verticalCenter
            right: parent.right
            rightMargin: 4
        }
        z: 10
    }

    Indicator {
        location: KDMultiSplitter.Location_OnTop;
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 4
        }
        z: 10
    }

    Indicator {
        location: KDMultiSplitter.Location_OnBottom;
        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: parent.bottom
            bottomMargin: 4
        }
        z: 10
    }
}

import QtQuick 2.9
import com.kdab.dockwidgets 1.0

Image {
    id: root

    property int indicatorType: DropIndicatorOverlayInterface.DropLocation_None

    source: "qrc:/img/classic_indicators/" + _window.iconName(indicatorType, true) + ".png";
    width: 64
    height: 64
}

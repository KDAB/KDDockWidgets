
import QtQuick 2.6
import com.kdab.dockwidgets 1.0 as KDDW

KDDW.MainWindow {
    id: root


    Component.onCompleted: {
        root.init("MyWindowName-1");
    }
}


# cpp

This example shows how to drive the QtQuick frontend entirely from C++, as an alternative to
declaring dock widgets in QML.

`main.qml` only sets up the top-level window.
All dock widget creation happens in `main.cpp`, through a `DockWidgetFactory` object which is
exposed to QML as a context property.

View the source in [GitHub](https://github.com/KDAB/KDDockWidgets/blob/main/examples/qtquick/cpp/).

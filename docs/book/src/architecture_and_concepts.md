# Architecture and Concepts

`KDDockWidgets` is divided into `Core` and one `frontend` for each supported `GUI toolkit`.<br>
The `Core` is pure `C++` with no dependency on `Qt`. Business logic and state often lives here, and classes are
namespaced with `KDDockWidgets::Core::`.<br>
We have two complete frontends, `qtwidgets` and `qtquick` and a third one called `flutter`, which is lacking some futures still. Their code is namespaced with `KDDockWidgets::QtWidgets`, `KDDockWidgets::QtQuick` and `KDDockWidgets::Flutter` respectively.

## Views and Controllers

`View` is a fancy word that meant `QWidget`. Since we introduced support for non-QtWidget toolkits we needed to drop the QWidget nomenculature. For QtQuick, views are `QQuickItem`s, and for Flutter, they are `StatefullWidget`.

While views are something graphical, which depends on the rendering technology you're using, `Controllers` on the other hand are gui-agnostic, they live in `Core`, and are reused by all frontends.

Here's a list of controllers and views:
- TitleBar
- TabBar
- Stack
- Group
- DockWidget
- MainWindow
- FloatingWindow
- DropArea

For each of the above there's a View and a Controller. For example, for TitleBar, there's `Core::TitleBar`, implemented in `src/core/TitleBar.cpp`, which is rendered by `QtWidgets::TitleBar` (or `QtQuick::TitleBar` or `Flutter::TitleBar`), implemented in `/src/qtwidgets/views/TitleBar.cpp` and so on.

Porting to another GUI toolkit involves reimplementing all views.

## Platform, Screen, Window, ViewFactory
Not everything is a View/Controller. There's a bunch of other abstractions that need to be implemented when creating a new frontend.

While Qt has `QGuiApplication`, `QScreen`, `QWindow` we have similar abstractions but in a more toolkit agnostic way. See all the pure virtual methods in Core::Platform, Core::Screen, Core::Window and View::Factory and implement them.

## Layouting engine

This is like the core of the core, it lives in src/core/layouting. The code there doesn't know anything about docking
or dnd. It implements our layouting, which is a recursively nested layout. Imagine a layout composed nested  QVBoxLayout and QHBoxLayout supporting any depth. min/max/preferred sizes are supported and recursively propagated up.
See `src/core/layouting/examples` for how to use just this layouting engine without any docking. This is pure C++ and doesn't depend on Qt.

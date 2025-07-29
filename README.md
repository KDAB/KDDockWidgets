# KDDockWidgets

![Build Status](https://github.com/KDAB/KDDockWidgets/actions/workflows/build-qt5.yml/badge.svg)
![Build Status](https://github.com/KDAB/KDDockWidgets/actions/workflows/build-qt6.yml/badge.svg)
![Build Status](https://github.com/KDAB/KDDockWidgets/actions/workflows/valgrind-leakcheck.yml/badge.svg)
![Build Status](https://github.com/KDAB/KDDockWidgets/actions/workflows/qt6-asan.yml/badge.svg)
![Build Status](https://github.com/KDAB/KDDockWidgets/actions/workflows/qt6-lsan.yml/badge.svg)

![KDDockWidgetsLogo](https://github.com/KDAB/KDDockWidgets/blob/2.0/images/kddockwidgets.png?raw=true)

Our [manual](https://kdab.github.io/KDDockWidgets)
is the docs entry point for everything related to `KDDockWidgets`.
This README only provides minimal information.

<br>
<br>
<br>
<br>

`KDDockWidgets` is a Qt dock widget library written by KDAB, suitable for replacing
`QDockWidget` and implementing advanced functionalities missing in Qt.

Although `KDDockWidgets` is ready to be used out of the box, it can also be seen
as a framework to allow building very tailored custom docking systems. It tries
to expose every internal widget and every knob for the app developer to tune.

## Features

- Supports QtWidgets and QtQuick/QML
- Provide advanced docking that QDockWidget doesn't support
  - Native window resize on Windows (allowing for Aero-snap even with custom title bar decorations)
  - Arrow drop indicators for great drop precision
  - Allow for totally different, user provided, drop indicator types
  - Nesting dock widgets in a floating window and docking that group back to main window
  - Docking to any main window, not only to the parent main window
  - Docking to center of main window, or simply removing the concept of "central widget"
  - Main window supporting detachable tabs in center widget
  - Detaching arbitrary tabs from a tab bar into a dock area
  - Supporting more than 1 main window
  - Support for affinities, making some dock widgets only dockable on certain main windows
  - Allow to hide TitleBar and just show tabs. Allows dragging via the tab bar.
  - Exposing inner helper widgets so the user can customize them or provide his own
    - Customize tab widgets
    - Customize title bars
    - Customize window frames
    - Custom widget separators
- Cross-platform (macOS, Linux, Windows, WebAssembly, Wayland, X11/XCB, EGLFS are working)
  See README-Wayland.md and README-WASM.md for platform specific information.
- Layouting engine honouring min/max size constraints and some size policies
- PySide2 bindings
- Clean codebase
  - Not mixing GUI with state with logic with animations
  - Great test coverage, even the GUI and DnD operations are tested. 200 tests currently.
  - Fuzzer for doing random testing and finding bugs
- Lazy separator resize
- Reordering tabs with mouse
- Partial layout save/restore, affecting only a chosen sub-set
- Double click on title bar to maximize
- Double click on separator to distribute equally
- Show close button on tabs
- Allow to make a dock widget non-closable and/or non-dockable
- Optional minimize and maximize button on the title bar
- FloatingWindows can be utility windows or full native

## Screen capture

![Screen capture](./screencap.gif?raw=true "The docking system in action")

## Showcases

Read about how [NVIDIA implemented KDDockWidgets](https://www.kdab.com/why-kdab/proven-excellence/nvidia-improved-developer-tools-with-kddockwidgets/) in their their NSight Suite developer toolkit, which is built with Qt. 

## Licensing

KDDockWidgets is © Klarälvdalens Datakonsult AB (KDAB) and is licensed according
to the terms of the [GPL 2.0](LICENSES/GPL-2.0-only.txt) or [GPL 3.0](LICENSES/GPL-3.0-only.txt).

Contact KDAB at <info@kdab.com> to inquire about commercial licensing.

## About KDAB

KDDockWidgets is supported and maintained by Klarälvdalens Datakonsult AB (KDAB).

The [KDAB](https://www.kdab.com) Group is a globally recognized provider for software consulting, development and training, specializing in embedded devices and complex cross-platform desktop applications. In addition to being leading experts in Qt, C++ and 3D technologies for over two decades, KDAB provides deep expertise across the stack, including Linux, Rust and modern UI frameworks. With 100+ employees from 20 countries and offices in Sweden, Germany, USA, France and UK, KDAB serves clients around the world.

Please visit <https://www.kdab.com> to meet the people who write code like this.


Blogs and publications: https://www.kdab.com/resources

Videos (Tutorials and more): https://www.youtube.com/@KDABtv

Software Developer Training for Qt, Modern C++, Rust, OpenGL and more: https://training.kdab.com

Software Consulting and Development Services for Embedded and Desktop Applications https://www.kdab.com/services/

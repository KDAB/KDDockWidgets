KDDockWidgets
=============
`KDDockWidgets` is a Qt dock widget library written by KDAB, suitable for replacing
`QDockWidget` and implementing advanced functionalities missing in Qt.

Although `KDDockWidgets` is ready to be used out of the box, it can also be seen
as a framework to allow building very tailored custom docking systems. It tries
to expose every internal widget and every knob for the app developer to tune.


Motivation
==========
Throughout the years KDAB contributed and funded bug fixes and features to `QDockWidget`.
Sadly, this was very painful. Each bug fix or feature took many days of implementation,
and an equal number of days just to fix dozens of regressions.

`QDockWidget` mixes GUI code with logic with state, making it very hard
to move forward with new features. Furthermore, our customers were getting more
creative with their requests, so it was clear we needed a better docking framework.

You will find more information in these places:

 * [our official home page](https://www.kdab.com/development-resources/qt-tools/kddockwidgets)
 * [online detailed browsable API reference](https://docs.kdab.com/kddockwidgets)
 * [our example programs](examples/)

We also have an [in browser demo](https://demos.kdab.com/wasm/kddockwidgets/dockwidgets.html). Note
however that this demo isn't fully featured, as it's running on Qt for WebAssembly.

Features
========
- Provide advanced docking that QDockWidgets doesn't support
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
- Crossplatform (macOS, Linux, Windows, WebAssembly, Wayland, X11/XCB, EGLFS are working)
  See README-Wayland.md and README-WASM.md for platform specific information.
- Layouting engine honouring min/max size constraints and some size policies
- PySide2 bindings
- Clean codebase
  - Not mixing GUI with state with logic with animations
  - Great test coverage, even the gui and DnD operations are tested. 200 tests currently.
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

Screen capture
==============
![Screen capture](./screencap.gif?raw=true "The docking system in action")


Roadmap
========
  - QtQuick support

Trying out the examples
=======================
A full demo lives in `examples/dockwidgets/`, it showcasts most of the features.
A simpler example lives in `examples/minimal/`, which might be more indicated
to learn the API, as it's less overwelming than the full demo.


Open a terminal capable of building Qt5 applications.
Make sure you have cmake, ninja, compiler, Qt, etc in PATH.

Adapt the instructions to suit your cmake generator and operating system.
Build and install the KDDockWidgets framework:

```
$ cmake -G Ninja -DCMAKE_INSTALL_PREFIX=/path/where/to/install ../path/to/kddockwidgets
$ cmake --build .
$ cmake --build . --target install
```

Now build and run the example:
```
$ cd path/to/kddockwidgets/examples/dockwidgets/
$ cmake -G Ninja -DCMAKE_PREFIX_PATH=/path/where/to/install
$ cmake --build .
$ ./kddockwidgets_example

```

The installation directory defaults to `c:\KDAB\KDDockWidgets-<version>` on Windows
and `/usr/local/KDAB/KDDockWidgets-<version>` on non-Windows.  You can change this
location by passing the option `-DCMAKE_INSTALL_PREFIX=/install/path` to cmake.

Using
=====
From your CMake project, add

    find_package(KDDockWidgets CONFIG)

and link to the imported target `KDAB::kddockwidgets`.
That's all you need to do (the imported target also brings in the include directories)

You may also need to modify the `CMAKE_MODULE_PATH` environment variable depending
on where you installed KDDockWidgets.


Python Bindings
================
Make sure you have pyside2, shiboken2 and shiboken2-generator installed.
As this time, you cannot get shiboken2-generator because the wheels are not on PyPi.
To use the wheels do this:

```
% pip3 install \
    --index-url=http://download.qt.io/official_releases/QtForPython/ \
    --trusted-host download.qt.io \
    shiboken2 pyside2 shiboken2_generator
```

For more info visit https://doc.qt.io/qtforpython/shiboken2/gettingstarted.html

Once QtForPython is installed you are ready to generate the PySide bindings
for KDDockwWidgets.

Next pass `-DKDDockWidgets_PYTHON_BINDINGS=ON` to CMake, followed by the
make command.

The bindings will be installed to the passed `-DCMAKE_INSTALL_PREFIX`, which
might require setting the `PYTHONPATH` env variable to point to that path when
running applications.  Alternatively, configure the bindings install location
by passing `-DKDDockWidgets_PYTHON_BINDINGS_INSTALL_PREFIX=/usr/lib/python3.8/site-packages`
to CMake (adjust to the python path on your system).

To run the KDDW python example
```
$ export PYTHONPATH=/kddw/install/path # Only if needed
$ cd python/examples/
$ rcc -g python -o rc_assets.py ../../examples/dockwidgets/resources_example.qrc
$ python3 main.py
```


Supported Qt versions and toolchains
=====================================
KDDockWidgets requires Qt >= 5.9 (or >=5.12 if Python bindings are enabled).
The QtQuick support will require Qt >= 5.15.
Qt 6 is supported.

Regarding compilers, whatever toolchain is able to build Qt 5.9 should also be
fine. Note however that MSVC 2013 isn't supported anymore due to compiler crashes.


Licensing
=========
KDDockWidgets is (C) 2018-2021, Klarälvdalens Datakonsult AB, and is licensed according to
the terms of the [GPL 2.0](LICENSES/GPL-2.0-only.txt) or [GPL 3.0](LICENSES/GPL-3.0-only.txt).

Contact KDAB at <info@kdab.com> to inquire about commercial licensing.


Get Involved
============
KDAB will happily accept external contributions; however, **all** contributions require a
signed [Copyright Assignment Agreement](docs/KDDockWidgets-CopyrightAssignmentForm.docx).

Contact info@kdab.com for more information.

Please submit your contributions or issue reports from our GitHub space at
https://github.com/KDAB/KDDockWidgets


About KDAB
==========
KDDockWidgets is supported and maintained by Klarälvdalens Datakonsult AB (KDAB).

The KDAB Group is the global No.1 software consultancy for Qt, C++ and
OpenGL applications across desktop, embedded and mobile platforms.

The KDAB Group provides consulting and mentoring for developing Qt applications
from scratch and in porting from all popular and legacy frameworks to Qt.
We continue to help develop parts of Qt and are one of the major contributors
to the Qt Project. We can give advanced or standard trainings anywhere
around the globe on Qt as well as C++, OpenGL, 3D and more.

Please visit https://www.kdab.com to meet the people who write code like this.

Stay up-to-date with KDAB product announcements:

* [KDAB Newsletter](https://news.kdab.com)
* [KDAB Blogs](https://www.kdab.com/category/blogs)
* [KDAB on Twitter](https://twitter.com/KDABQt)

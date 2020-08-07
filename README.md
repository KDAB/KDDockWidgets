KDDockWidgets
==============
`KDDockWidgets` is a KDAB effort to provide an advanced docking system for Qt.

Throughout the years KDAB contributed and funded bug fixes and features to `QDockWidget`.
Sadly, this was very painful. Each bug fix or feature took many days of implementation,
and an equal number of days just to fix dozens of regressions.

`QDockWidget` mixes GUI code with logic with state, making it very hard
to move forward with new features. Furthermore, our customers were getting more
creative with their requests, so it was clear we needed a better docking framework.

You will find more information in these places:

 * [our official home page](https://www.kdab.com/kddockwidgets)
 * [online detailed browsable API reference](https://docs.kdab.com/kddockwidgets)
 * [our example programs](examples/)

Features
========
- Provide advanced docking that QDockWidgets doesn't support
  - Nesting dock widgets in a floating window and docking that group back to main window
  - Docking to any main window, not only to the parent main window
  - Docking to center of main window, or simply removing the concept of "central widget"
  - Main window supporting detachable tabs in center widget
  - Detaching arbitrary tabs from a tab bar into a dock area
  - Exposing inner helper widgets so the user can customize them or provide his own
    - Customize tab widgets
    - Customize title bars
    - Customize window frames

- Clean codebase
  - Not mixing GUI with state with logic with animations
  - Unit-test everything, even the GUI and DnD operations (140 tests currently)
  - Fuzzer for doing random testing

![Screen capture](./screencap.gif?raw=true "The docking system in action")


Roadmap
========
  - Different forms of docking indicators (through plugins)
  - QtQuick support


Trying out the demo
====================

Open a terminal capable of building Qt5 applications.
Make sure you have cmake, ninja, compiler, Qt, etc in PATH.

Feel free to adapt the instructions to suit your cmake generator and operating system.
Build and install the KDDockWidgets framework:

```
$ cmake -G Ninja -DCMAKE_INSTALL_PREFIX=/path/where/to/install ../path/to/kddockwidgets
$ make
$ make install
```

Now build and run the example:
```
$ cd path/to/kddockwidgets/examples/dockwidgets/
$ cmake -DCMAKE_PREFIX_PATH=/path/where/to/install
$ make
$ ./kddockwidgets_example

```

The installation directory defaults to `c:\KDAB\KDDockWidgets-<version>` on Windows
and `/usr/local/KDAB/KDDockWidgets-<version>` on non-Windows.  You can change this
location by passing the option `-DCMAKE_INSTALL_PREFIX=/install/path` to cmake.


Python Bindings
================

To generate PySide2 bindings, pass `-DOPTION_BUILD_PYTHON_BINDINGS=ON` to CMake.
The bindings will be installed to the passed `-DCMAKE_INSTALL_PREFIX`. Which
might require setting the `PYTHONPATH` env variable to point to that path when
running applications. Alternatively, pass `-DPYTHON_BINDINGS_INSTALL_PREFIX=/usr/lib/python3.8/site-packages`
to CMake (adjust to the python path on your system).

To run the KDDW python example
```
$ export PYTHONPATH=/kddw/install/path # Only if needed
$ cd python/examples/
$ rcc -g python -o rc_assets.py ../../examples/dockwidgets/resources_example.qrc
$ python3 main.py
```


Supported Qt versions
======================
KDDockWidgets requires Qt >= 5.9 (or >=5.12 if Python bindings are enabled).


Licensing
=========
KDDockWidgets is (C) 2018-2020, Klarälvdalens Datakonsult AB, and is licensed according to
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

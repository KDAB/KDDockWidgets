# Installation

## Requirements

- CMake >= 3.15
- Qt 5.15.x or Qt6 >= 6.2
- Ninja (Other generators might work but are untested)
- C++17 capable compiler. Minimum VS2019 on Windows.
- Qt X11Extras module if on Linux/X11
- Qt Quick and QuickControls2 modules if using the QtQuick support
- Qt private development headers, for instance, for Qt5:
  - SUSE: libqt5-qtbase-private-headers-devel
  - Ubuntu, debian-based: qtbase5-private-dev
  - Fedora, redhat-based: qt5-qtbase-private-devel
  - others: consult your distro

## Building

Although the build system supports many options, you'll mostly use `-DKDDockWidgets_QT6=ON`, or don't use any option, which defaults to `Qt 5`.

By default, KDDW will be built with support for both `QtWidgets` and `QtQuick`. If you want to save some binary space and compile time,
consider passing `-DKDDockWidgets_FRONTENDS="qtwidgets"` or `-DKDDockWidgets_FRONTENDS="qtquick"`.

Open a terminal capable of building Qt applications (make sure you have cmake, ninja, compiler, Qt, etc in PATH) and run:

```bash
cmake -G Ninja -DCMAKE_INSTALL_PREFIX=/path/where/to/install ../path/to/kddockwidgets
cmake --build .
cmake --build . --target install
```

Feel free to use your favorite IDE instead.

The installation directory defaults to `c:\KDAB\KDDockWidgets-<version>` on Windows
and `/usr/local/KDAB/KDDockWidgets-<version>` on non-Windows.

Change the installation location by passing the option `-DCMAKE_INSTALL_PREFIX=/install/path` to CMake.


## Using

Now that you've built and installed KDDW, you can use it.

Let's start by building an example:

```bash
cd path/to/kddockwidgets/examples/dockwidgets/
cmake -G Ninja -DCMAKE_PREFIX_PATH=/path/where/to/install
cmake --build .
./bin/qtwidgets_dockwidgets
```

## Linking your own app to KDDockWidgets

You can simply inspect the examples to see how it's done. But the gist is:

Edit your `CMakeLists.txt`:

```cmake
find_package(KDDockWidgets REQUIRED) // For Qt6, use KDDockWidgets-qt6 instead here.
...
target_link_libraries(myapp PRIVATE KDAB::kddockwidgets)
```
Finally, don't forget to build your app with `-DCMAKE_PREFIX_PATH=/path/to/installed/kddw/`.

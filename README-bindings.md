# KDDockWidgets and Python bindings

These are the instructions for building the Python bindings for KDDockWidgets.

Currently unsupported:

- debug builds
- builds against Qt debug libraries
- static builds
- python2 bindings
- only some 32-bit platforms are supported.  see <https://wiki.qt.io/Qt_for_Python>

Also, there are no plans to support the qmake buildsystem.

## Prerequisites

You will need:

- a compiler with C++14 support (C++17 for Qt6 builds)
- Python3.7 or higher
- Qt5 version 5.12 or higher
- Qt6 version 6.2 or higher
- QtForPython provided by the Qt project.

## Install PySide2 for Qt5

Make sure you have PySide2, shiboken2 and shiboken2-generator installed.
As this time, you cannot get shiboken2-generator because the wheels are not on PyPi.
To use the wheels do this:

```bash
% pip3 install \
    --index-url=http://download.qt.io/official_releases/QtForPython/ \
    --trusted-host download.qt.io \
    shiboken2 pyside2 shiboken2_generator
```

For more info visit <https://doc.qt.io/qtforpython/shiboken2/gettingstarted.html>

afterwards run:

```bash
pip3 list | grep PySide
```

Note the version *must* match the same Qt you intend to use when building KDDockWidgets.

## Install PySide6 for Qt6

Follow the same instructions as [the previous section](#Install PySide2 for Qt5),
except installing `shiboken6 pyside6 shiboken6_generator` with pip3.

## Building KDDockWidgets Python Bindings

Tell CMake to build the bindings by passing the `-DKDDockWidgets_PYTHON_BINDINGS=True' option.
Then run `cmake --build` as usual.

The bindings will be installed to `CMAKE_INSTALL_PREFIX`, which might require setting
the `PYTHONPATH` env variable to point to that path when running applications.

For example, if you install to the default location on linux you would:

```bash
  export PYTHONPATH=/usr/local/KDAB/KDDockWidgets-1.7.0/lib64/python3.10/site-packages
```

Alternatively, configure the bindings install location by passing (for example)
`-DKDDockWidgets_PYTHON_BINDINGS_INSTALL_PREFIX=/usr/lib/python3.8/site-packages` to CMake
and adjust to the PYTHONPATH accordingly, as necessary.

To run the KDDW python example

```bash
    export PYTHONPATH=/kddw/install/path # Only if needed
    cd python/examples/
    rcc -g python -o rc_assets.py ../../examples/dockwidgets/resources_example.qrc
    python3 main.py
```

### Build Issues

- If you see errors like "Unable to locate Clang's built-in include directory"
  then first mROUBLESHOOTINGake sure you have llvm installed.  If you still have problems try
  setting the environment variable `LLVM_INSTALL_DIR` to point to your llvm installation.

  Examples:

```bash
    export LLVM_INSTALL_DIR=/usr/local/opt/llvm-11
    set "LLVM_INSTALL_DIR=C:\Program Files\LLVM" #Windows
```

- When building the examples you may encounter errors loading shared libraries from shiboken2_generator.

  Try:

```bash
    export LD_LIBRARY_PATH=/usr/local/lib/python/dist-packages/PySide2/Qt/lib #linux
    export DYLD_LIBRARY_PATH=/usr/local/lib/python/dist-packages/PySide2/Qt/lib #Mac
    (Adjust to wherever your PySide is installed)
```

- On Windows the `libclang.dll` that ship with QtForPython is not compatible with MSVC2019.
  To fix this, copy the `libclang.dll` that comes with llvm into shiboken2, like so:

```bash
    cd C:\Python37\Lib\site-packages\shiboken2_generator
    copy libclang.dll libclang.dll.save
    copy "C:\Program Files\llvm\bin\libclang.dll" libclang.dll
    (Python3 installation in C:\Python37 and llvm in c:\Program Files\llvm. adjust as needed)
```

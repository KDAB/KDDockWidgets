# Flutter

> ⚠️ This document is intended for KDDW developers.<br>
> ⚠️ The flutter port is not ready for the general public.<br>
> ⚠️ The flutter port is on hold, waiting for multi-window support upstream.

## Requirements

- Flutter >= 3.24

- CMake, Ninja

- KDDW (git clone <https://github.com/KDAB/KDDockWidgets.git>)

## Build instructions

Adjust paths as needed.<br>
Checkout branch `main`.

Preparatives:

```bash
export KDDW_SOURCE_DIR=/home/user/somewhere/kddockwidgets/
export KDDW_BINDINGS_LIB=/path/to/libkddockwidgets.so # (or dylib or dll)
```

Release build (Recommended):

```bash
cd $KDDW_SOURCE_DIR
cmake --preset=release-flutter
cmake --build build-release-flutter
cd examples/flutter/
flutter pub get
flutter run -d linux # adjust device as needed

# (optional) run flutter tests:
cd $KDDW_SOURCE_DIR/src/flutter/dart/ && flutter pub get && flutter test
```

If you want to run the C++ tests, then you need a developer build:

Developer build:

```bash
cd $KDDW_SOURCE_DIR
cmake --preset=dev-flutter
cmake --build build-dev-flutter
cd build-dev-flutter && ctest
```

## Pending work

- Support flutter multi-window

- More styling

- Figure out packaging, probably once Dart's Native Assets is released

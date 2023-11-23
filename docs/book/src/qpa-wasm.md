# WebAssembly

KDDockWidgets works with WebAssembly with the following known limitations:

- Classic drop indicators are not supported, only the segmented ones. This is because
  WASM doesn't support windows with translucency.

- Might be slow on Linux, depending on your browser, while dragging or resizing windows.
  Please file a bug with Qt, as it's out of scope for KDDW to fix.

- Qt 5 WASM probably works, but is unsupported and untested.

## Demo

A demo is available at <https://demos.kdab.com/wasm/kddockwidgets/dockwidgets.html>.

## Building KDDW

This can be done by following the generic instructions at <https://doc.qt.io/qt-6/wasm.html>.

For a Linux system, it's something like this (adjust paths):
```
$ source ~/emsdk/emsdk_env.sh
$ em++ --version # Needs to be 3.1.37 for Qt 6.6.0
$ cd KDDockWidgets/
$ ~/Qt/6.6.0/wasm_multithread/bin/qt-cmake --preset=wasm-release
$ cd build-wasm-release/
$ ninja kddockwidgets
$ ninja qtwidgets_dockwidgets
$ ninja qtquick_dockwidgets
```

Above we're building just 2 examples, as they take very long to compile. But feel free to just run `ninja`.


## Builds tips for your own app

- Link to `libkddockwidgets-qt6.a`
- As the build is static, don't forget to initialize KDDW's resources:

```cpp
#ifdef QT_STATIC
    Q_INIT_RESOURCE(kddockwidgets_resources);
#endif
```

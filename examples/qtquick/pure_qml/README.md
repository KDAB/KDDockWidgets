Here's some examples that don't require writing any C++ code.

The only requirements are that you build KDDW with `-DKDDockWidgets_QML_MODULE=ON` and that your loader knows where to find
the KDDW plugin, for instance:


```
$ qml -I <kddw build directory> main_example1.qml -platform xcb
```

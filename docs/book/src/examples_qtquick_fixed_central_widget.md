# fixed central widget

This example shows a layout with a persistent central widget. This widget can't be detached and
can't be docked over.

In main.qml they key source lines for this mode are:

```
options: KDDW.KDDockWidgets.MainWindowOption_HasCentralWidget
persistentCentralItemComponent: CentralWidget {}
```

The central item can also be loaded from a file, with `persistentCentralItemFileName: ":/CentralWidget.qml"`.

View the source in [GitHub](https://github.com/KDAB/KDDockWidgets/blob/main/examples/qtquick/fixed_central_widget/main.qml).

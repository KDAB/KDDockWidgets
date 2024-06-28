# fixed central widget

This example shows a layout with a persistent central widget. This widget can't be detached and
can't be docked over.

In main.qml they key source lines for this mode are:

```
persistentCentralItemFileName: ":/CentralWidget.qml"
options: KDDW.KDDockWidgets.MainWindowOption_HasCentralWidget
```

View the source in [GitHub](https://github.com/KDAB/KDDockWidgets/blob/main/examples/qtquick/fixed_central_widget/main.qml).

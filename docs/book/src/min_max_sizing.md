# min/max sizing

## QtWidgets

KDDW will honour min/max constraints set on the guest widget.<br>
You can run the example `qtwidgets_dockwidgets -g` to see the max-size in action.<br>
Setting the constraints directly on `DockWidget` is not advised.

## QtQuick

Minimum and maximum sizes are supported.<br>
There's no public API to set them, but you can set special properties called `kddockwidgets_min_size`
and `kddockwidgets_max_size` on your guest item.<br>
For an example, run the `qtquick_dockwidgets` sample executable, then go to "File" menu, and chose
`Create widget with min-size` or `Create widget with max-size`.

Set these properties before the dock widget is shown, as changing them afterwards isn't reliably propagated to the layout yet.

Note that while KDDW floating windows and docked widgets will honour the min/max sizes, the main window itself won't, as that's an item completely controlled by the user. Maybe we could expose the main window's KDDW layout min/max size, then users could use that to calculate the main window's min/max.

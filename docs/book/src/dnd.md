# Drag and Drop

This page lists available ways to have more fine-grained control over DnD.

## Methods to control visible dock indicators

- `Config::setDropIndicatorsInhibited()`
- `Config::setDropIndicatorAllowedFunc()`
  See the example `qtwidgets_dockwidgets --hide-certain-docking-indicators`

# Methods to control if a dock widget can be detached

- `Config::setDragAboutToStartFunc()`


# Make a single dock widget non-dockable

- `DockWidgetOption::DockWidgetOption_NotDockable`

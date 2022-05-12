# Concepts

Before digging into code we need to learn some high level concepts which will make it easy to learn the API afterwards.

## Views or Widgets

A view, or widget is the most basic GUI element usually provided by your framework.
KDDockWidget's has its roots in the Qt QWidget GUI framework, hence the term widget will appear in many places. However, since KDDW's goal is to support other GUI toolkits, we've introduced a more generic term, view.

For the QtWidget frontend, a view will be internally implemented as a QWidget, while for the QtQuick frontend it will be implemented as a QQuickItem.


## Guest View

This is the view that the user (library user) wants to dock. It has some custom content that is only relevant for the application. From KDDW's prespective we don't care what's inside, we'll just help dock it.


## DockWidget

The DockWidget is a visual container for the Guest, in other words, its visual parent.
Visually, DockWidget and Guest might be indistiguishable, except for some margin added by DockWidget. One reason to have this extra indirection is that it allows us to have a common API to deal with the Guest. Since guest is provided by the application developer it doesn't have any interface.


## TitleBar

A TitleBar is the area that has the dock widget title and the float and close buttons.
Usually KDDW won't use native OS title bars but draw its own.


## TabBar

DockWidgets can be grouped together in tabs. A tab bar is just a group of tabs.
In Qt this is something like QTabBar.

## Stack

A stack is closely related to TabBar. A stack is a group of dock widgets where only one is visible at a time, the visible one is controlled by the current tab.
In Qt this would be QTabWidget.


## Frame

The Frame is a container that ties the previous concepts all together.
It's composed of 1 or more tabbed DockWidgets, a TitleBar, a Stack and a TabBar.


## Layout

Represents a docking layout. Currently 2 are supported, the traditional nested docking with resizable splitters (this is the default), implemented by MultiSplitter. And a MDI layout, where the dock widgets can be arbitrary positioned and even overlap inside an area.

The layouts deal in Frame. You add Frame objects to a layout.


## Separator

A visual separator between two widgets, which allows the user to resize dock widgets with mouse.


## FloatingWindow

When a dock widget isn't embedded into a window it's said to be floating. It's its own
top-level native window. This class ties all the previous together. It contains one layout, which contains multiple frames.


## MainWindow

Not much different from FloatingWindow technically, but users will often add status bar, tool bar and menu bars to a main window, while FloatingWindow is just an utility window (Qt::Tool). MainWindow also has support for a SideBar.

## SideBar

A side bar is a place in the MainWindow where you can "minimize" dock widgets.
It's also called the auto-hide future. When you send a dock widget to the sidebar it will close but show a button in the sidebar, if you press it, it will show the dock widget as an overlay.


## Drop Indicators

When dragging a dock widgets, KDDW will highlight the places where you can drop it, so
it embedds in the correct position.


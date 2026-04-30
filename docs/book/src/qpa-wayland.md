# Wayland

Wayland is supported and has been tested on KDE (Kwin) and weston.

## Limitations

Wayland works very differently than traditional desktops and imposes us some
limitations. Here's a list of different behaviours which KDDockWidgets will have
when running on Wayland:

- A title bar can either be used for drag&dock or for moving the window around.

- For this reason, floating windows now have two title bars.
  The native one, drawn by the server and the client one, drawn by KDDockWidgets.
  The native one allows you to drag the window around but not drop/dock.
  The client title bar allows you to perform a drag and drop/dock but not move the window around.

- You can detach a window by:
  - Clicking the title-bar's float button
  - Double-clicking the title bar of a docked widget
  - Double-clicking a tab
  - If no title bar is shown, double-clicking the empty space of the tab bar will detach
  the entire group of tabbed dock widgets

- Layout save/restore won't restore the position of floating windows, as wayland
  doesn't allow us to set geometry.

- Kwin specific:
  - The pixmap that's shown during a drag can't be bigger than 250x250. Might be a bug.

## Experimental: xdg-toplevel-drag

With `Config::Flag_WaylandToplevelDrag`, KDDockWidgets uses the
[xdg-toplevel-drag](https://wayland.app/protocols/xdg-toplevel-drag-v1) protocol. The window itself
moves with the pointer while dragging, instead of a pixmap, like on other platforms:

- Dragging a tab or a docked title bar detaches it into a floating window right away, which then
  follows the pointer.
- Floating windows have only KDDockWidgets' title bar, which both moves them and docks them.

It needs:

- Qt >= 6.8, and Qt's private Wayland client headers when building KDDockWidgets, as Qt has no
  public API to know whether the compositor supports the protocol. KDDockWidgets then links to
  QtWaylandClient, even if only used on X11. Pass `-DKDDockWidgets_WAYLAND_TOPLEVEL_DRAG=OFF` to
  CMake to avoid that.
- A compositor which supports xdg-toplevel-drag.

Otherwise the flag is ignored, with a warning, and the limitations above apply.

Known limitations:

- Resizing floating windows doesn't work properly. Without the native title bar they have no
  native decorations, so KDDockWidgets resizes them itself, and it moves the window when resizing
  from the left or top edges, which Wayland doesn't allow. The window then grows instead.
- A maximized floating window isn't restored to its normal size before being dragged, like it is
  on other platforms.
- While dragging, the cursor shows "forbidden" wherever nothing accepts the drop, like over empty
  space or the desktop, although releasing there is fine. The compositor picks that cursor. Try fixing it
  upstream, see [QTBUG-152325](https://qt-project.atlassian.net/browse/QTBUG-152325).

All in all it's pretty decent and usable. Any further improvements should be done at the server or
protocol level now.

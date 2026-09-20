// This file is part of KDDockWidgets.
//
// SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
//
// SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
//
// Contact KDAB at <info@kdab.com> for commercial licensing options.

use crate::manager::DockManager;
use crate::{DockWidgetState, DragState, GroupView, IndicatorView, Location, SeparatorGeometry};
use slint::{Image, Model, Rgba8Pixel, SharedPixelBuffer, VecModel};
use std::cell::RefCell;
use std::rc::Rc;

/// What [`DockingArea::new`]'s snapshot hook returns: a snapshot of the
/// whole window, in physical pixels, plus the scale factor needed to map
/// [`DockingArea`]'s own logical-pixel geometry into it.
type WindowSnapshot = (SharedPixelBuffer<Rgba8Pixel>, f32);

/// The app's handle on one docking area, and the whole API an app needs:
/// it decides where dock widgets go, and everything else (Group geometry,
/// tabs, separator dragging, resizing) happens on its own.
///
/// Create one with [`install!`](crate::install), which binds it to the
/// `DropArea` of a window:
///
/// ```ignore
/// let ui = AppWindow::new()?;
/// let docking = kddockwidgets::install!(&ui);
///
/// docking.add_dock_widget("output", Location::OnLeft, None);
/// docking.add_dock_widget("editor", Location::OnRight, None);
/// docking.add_dock_widget_as_tab("console", "editor");
/// ```
///
/// Dock widgets themselves are declared in Slint, inside the `DropArea`, and
/// are referred to here by their `unique-name`. The two sides can come in
/// either order: naming a dock widget that hasn't been declared (yet) is
/// fine, it takes effect as soon as it shows up.
///
/// Cloning is cheap (it's a handle, all clones share one layout) and the
/// window's callbacks hold a clone of their own, so an app that has no
/// further use for it can just drop it.
#[derive(Clone)]
pub struct DockingArea {
    manager: Rc<RefCell<DockManager>>,
    sync_ui: Rc<dyn Fn(&DockingArea)>,
    snapshot: Rc<dyn Fn() -> Option<WindowSnapshot>>,
    /// The dragged Group's content, captured once at drag start (see
    /// [`drag_started`](Self::drag_started)) and redrawn following the
    /// pointer for the rest of the drag. `None` while not dragging, or if
    /// the platform's renderer doesn't support [`slint::Window::take_snapshot`]
    /// (e.g. the headless testing backend used by `slint_example`'s GUI
    /// tests) -- the drag still works, just without the ghost image.
    ghost_image: Rc<RefCell<Option<Image>>>,
}

impl DockingArea {
    /// Opens `name` in a new Group, at `location` -- relative to
    /// `relative_to`'s Group if given, otherwise to the whole area.
    ///
    /// Passing `relative_to` is what produces nesting: a dock widget added
    /// `OnBottom` of one that is itself side by side with others splits only
    /// that one's space, instead of becoming a full-width row.
    ///
    /// Does nothing if `name` is already open.
    pub fn add_dock_widget(&self, name: &str, location: Location, relative_to: Option<&str>) {
        self.mutate(|m| m.add_dock_widget(name, location, relative_to));
    }

    /// Opens `name` as a new tab next to the already open `existing`.
    ///
    /// Does nothing if `name` is already open, or if `existing` isn't.
    pub fn add_dock_widget_as_tab(&self, name: &str, existing: &str) {
        self.mutate(|m| m.add_dock_widget_as_tab(name, existing));
    }

    /// Closes `name`, removing its Group from the layout if it was that
    /// Group's last tab. The dock widget itself stays alive and can be
    /// reopened with [`add_dock_widget`](Self::add_dock_widget).
    pub fn close(&self, name: &str) {
        self.mutate(|m| m.close(name));
    }

    /// Makes `name` the current tab of its Group.
    pub fn set_current(&self, name: &str) {
        self.mutate(|m| m.set_current(name));
    }

    /// Overrides the title `name`'s Slint `DockWidget` declared.
    pub fn set_title(&self, name: &str, title: &str) {
        self.mutate(|m| m.set_title(name, title));
    }

    pub fn is_open(&self, name: &str) -> bool {
        self.manager.borrow().is_open(name)
    }

    /// Where `name` currently is, or `None` if it isn't open.
    pub fn dock_widget_state(&self, name: &str) -> Option<DockWidgetState> {
        self.manager.borrow().dock_widget_state(name)
    }

    /// Every Group currently in the layout, in a stable order.
    pub fn groups(&self) -> Vec<GroupView> {
        self.manager.borrow().groups()
    }

    /// Every Separator currently in the layout, in a stable order.
    pub fn separators(&self) -> Vec<SeparatorGeometry> {
        self.manager.borrow().separators()
    }

    /// Every drop indicator currently shown (empty if no drag is in
    /// progress). See [`drag_started`](Self::drag_started).
    pub fn indicators(&self) -> Vec<IndicatorView> {
        self.manager.borrow().indicators()
    }

    /// Ghost and rubber band geometry for the in-progress drag, or `None` if
    /// there isn't one.
    pub fn drag_state(&self) -> Option<DragState> {
        self.manager.borrow().drag_state()
    }

    /// The dragged Group's snapshot, captured at drag start. `None` while
    /// not dragging, or if the platform couldn't produce one (see
    /// [`ghost_image`](Self::ghost_image)'s doc comment).
    pub fn drag_ghost_image(&self) -> Option<Image> {
        self.ghost_image.borrow().clone()
    }

    fn mutate(&self, f: impl FnOnce(&mut DockManager)) {
        f(&mut self.manager.borrow_mut());
        self.refresh();
    }
}

/// Plumbing for [`install!`](crate::install). None of this is meant to be
/// called by apps: it's the UI side of the area talking back to it.
#[doc(hidden)]
impl DockingArea {
    /// `snapshot` grabs the whole window (physical pixels) plus its scale
    /// factor, for cropping out the ghost image at the start of a drag. It
    /// can only be built where the generated `AppWindow` type is in scope,
    /// which is why [`install!`](crate::install) is the one passing it.
    pub fn new(
        sync_ui: impl Fn(&DockingArea) + 'static,
        snapshot: impl Fn() -> Option<WindowSnapshot> + 'static,
    ) -> Self {
        Self {
            manager: Rc::new(RefCell::new(DockManager::new())),
            sync_ui: Rc::new(sync_ui),
            snapshot: Rc::new(snapshot),
            ghost_image: Rc::new(RefCell::new(None)),
        }
    }

    /// Pushes the current layout back into the Slint side.
    pub fn refresh(&self) {
        (self.sync_ui)(self);
    }

    /// A `DockWidget` reporting the title and minimum size it was declared
    /// with. Lengths come in as Slint's `length`, i.e. logical pixels.
    pub fn register(&self, name: &str, title: &str, min_width: f32, min_height: f32) {
        self.mutate(|m| {
            m.register(
                name,
                title,
                min_width.ceil() as i32,
                min_height.ceil() as i32,
            )
        });
    }

    /// The `DropArea` reporting its own size. Sizes of zero (which is what a
    /// `DropArea` reports before the window is first laid out) are ignored:
    /// the layouting engine has nothing sensible to do with them.
    pub fn resize(&self, width: f32, height: f32) {
        if width >= 1.0 && height >= 1.0 {
            self.mutate(|m| m.resize(width as i32, height as i32));
        }
    }

    pub fn separator_pressed(&self, id: i32) {
        self.mutate(|m| m.separator_press(id));
    }

    pub fn separator_released(&self, id: i32) {
        self.mutate(|m| m.separator_release(id));
    }

    /// `(dx, dy)` is relative to where the Separator was last put, see
    /// `Separator` in `ui/separator.slint`.
    pub fn separator_moved(&self, id: i32, dx: f32, dy: f32) {
        self.mutate(|m| m.separator_move(id, dx as i32, dy as i32));
    }

    /// A titlebar (`whole_group: true`) or tab (`false`) reporting that a
    /// drag started. `(x, y)` is the pointer's position, in DropArea-local
    /// coordinates (`ui/droparea.slint` converts from window-absolute
    /// before forwarding here, since that's the only coordinate space every
    /// nested TouchArea that can start a drag shares without threading a
    /// DropArea reference down to each of them).
    ///
    /// Takes the ghost snapshot synchronously, before the first `refresh()`,
    /// so the very first frame the UI draws the ghost already has it.
    pub fn drag_started(&self, name: &str, whole_group: bool, x: f32, y: f32) {
        if !whole_group {
            // Picking up a tab makes it current first: partly "you're now
            // holding this one" semantics, partly necessity -- a
            // DockWidget only renders while it's the current tab of its
            // Group (see ui/dockwidget.slint), so without this there'd be
            // nothing but a stale or blank frame for the snapshot below to
            // capture. set_current()'s own refresh() updates Slint's
            // property graph synchronously; take_snapshot() re-renders
            // on demand from whatever the current values are when it's
            // called, not from whatever was last drawn on screen, so by
            // the time capture_ghost() runs the newly current tab's
            // content is what it actually sees.
            self.set_current(name);
        }

        self.manager
            .borrow_mut()
            .drag_started(name, whole_group, x as i32, y as i32);
        let ghost_rect = self.manager.borrow().drag_state();
        *self.ghost_image.borrow_mut() = ghost_rect
            .and_then(|r| self.capture_ghost(r.ghost_x, r.ghost_y, r.ghost_width, r.ghost_height));
        self.refresh();
    }

    pub fn drag_moved(&self, x: f32, y: f32) {
        self.mutate(|m| m.drag_moved(x as i32, y as i32));
    }

    pub fn drag_ended(&self, x: f32, y: f32) {
        self.mutate(|m| m.drag_ended(x as i32, y as i32));
        *self.ghost_image.borrow_mut() = None;
    }

    pub fn drag_cancelled(&self) {
        self.mutate(|m| m.drag_cancelled());
        *self.ghost_image.borrow_mut() = None;
    }

    /// Crops `(x, y, width, height)` (DropArea-local, logical pixels) out of
    /// a fresh window snapshot. `None` if the platform can't produce one
    /// (see [`ghost_image`](Self)'s doc comment) or the rect is empty.
    fn capture_ghost(&self, x: i32, y: i32, width: i32, height: i32) -> Option<Image> {
        if width <= 0 || height <= 0 {
            return None;
        }
        let (buffer, scale_factor) = (self.snapshot)()?;
        crop_snapshot(&buffer, scale_factor, x, y, width, height)
    }
}

/// Crops `(x, y, width, height)` -- in the same logical-pixel space as the
/// rest of this crate's geometry -- out of `buffer`, a window snapshot in
/// *physical* pixels (hence `scale_factor`). Clamped to `buffer`'s own
/// bounds: rounding a logical rect that's flush against the window's edge
/// can otherwise land a pixel outside it.
fn crop_snapshot(
    buffer: &SharedPixelBuffer<Rgba8Pixel>,
    scale_factor: f32,
    x: i32,
    y: i32,
    width: i32,
    height: i32,
) -> Option<Image> {
    let (src_width, src_height) = (buffer.width() as i32, buffer.height() as i32);
    if src_width <= 0 || src_height <= 0 {
        return None;
    }

    let sx = ((x as f32) * scale_factor).round() as i32;
    let sy = ((y as f32) * scale_factor).round() as i32;
    let sx = sx.clamp(0, src_width - 1);
    let sy = sy.clamp(0, src_height - 1);
    let sw = (((width as f32) * scale_factor).round() as i32).clamp(1, src_width - sx);
    let sh = (((height as f32) * scale_factor).round() as i32).clamp(1, src_height - sy);

    const BPP: usize = 4; // Rgba8Pixel
    let src_bytes = buffer.as_bytes();
    let mut cropped = SharedPixelBuffer::<Rgba8Pixel>::new(sw as u32, sh as u32);
    let dst_bytes = cropped.make_mut_bytes();
    let row_bytes = sw as usize * BPP;
    for row in 0..sh {
        let src_offset = (((sy + row) * src_width + sx) as usize) * BPP;
        let dst_offset = row as usize * row_bytes;
        dst_bytes[dst_offset..dst_offset + row_bytes]
            .copy_from_slice(&src_bytes[src_offset..src_offset + row_bytes]);
    }
    Some(Image::from_rgba8(cropped))
}

/// Reconciles `model`'s rows with `desired`, matched by `id_of`: existing
/// ids are updated in place, new ones appended, stale ones dropped. Order
/// isn't preserved -- nothing depends on Group/Separator draw order -- only
/// identity. `id_of` can return any `PartialEq` key, not just an integer id
/// -- e.g. a dock widget's `unique-name` for a Group's own tab list, see
/// `install!`.
///
/// Identity is the whole point: a `for` loop's `Repeater` throws away and
/// rebuilds all of its elements whenever the `ModelRc` it is bound to
/// changes identity, even for an identical set of rows. Handing it a fresh
/// model on every refresh therefore tore down every Group and Separator on
/// every callback; mid-drag that included the very Separator whose TouchArea
/// was capturing the mouse, which silently ended the drag before its first
/// `moved` event. Updating rows in place (`set_row_data`) only rebinds that
/// row's properties and leaves its element -- and its interactive state --
/// alone.
///
/// The same trap exists one level down: a Group's tab list (`GroupData`'s
/// own `dockwidgets` field) is *itself* a `ModelRc`, so rebuilding it fresh
/// on every refresh tears down the tab bar's `TouchArea`s just the same, even
/// while `groups` itself is being synced through this very function. That's
/// exactly what silently killed a tab drag before it could reach its first
/// `moved` event: `drag_started()` refreshes synchronously, and until
/// `install!` started caching one `dockwidgets` model per Group id and
/// syncing *its* rows too (instead of rebuilding it on every `GroupData`),
/// that refresh tore down the very tab bar row whose `TouchArea` was mid-drag.
#[doc(hidden)]
pub fn sync_rows<T: Clone + 'static, K: PartialEq>(
    model: &VecModel<T>,
    desired: Vec<T>,
    id_of: impl Fn(&T) -> K,
) {
    for item in &desired {
        let id = id_of(item);
        match (0..model.row_count()).find(|&i| model.row_data(i).is_some_and(|r| id_of(&r) == id)) {
            Some(i) => model.set_row_data(i, item.clone()),
            None => model.push(item.clone()),
        }
    }
    for i in (0..model.row_count()).rev() {
        if model
            .row_data(i)
            .is_some_and(|r| !desired.iter().any(|d| id_of(d) == id_of(&r)))
        {
            model.remove(i);
        }
    }
}

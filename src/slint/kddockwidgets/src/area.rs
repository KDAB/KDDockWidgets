// This file is part of KDDockWidgets.
//
// SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
//
// SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
//
// Contact KDAB at <info@kdab.com> for commercial licensing options.

use crate::manager::DockManager;
use crate::{DockWidgetState, GroupView, Location, SeparatorGeometry};
use slint::{Model, VecModel};
use std::cell::RefCell;
use std::rc::Rc;

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

    fn mutate(&self, f: impl FnOnce(&mut DockManager)) {
        f(&mut self.manager.borrow_mut());
        self.refresh();
    }
}

/// Plumbing for [`install!`](crate::install). None of this is meant to be
/// called by apps: it's the UI side of the area talking back to it.
#[doc(hidden)]
impl DockingArea {
    pub fn new(sync_ui: impl Fn(&DockingArea) + 'static) -> Self {
        Self { manager: Rc::new(RefCell::new(DockManager::new())), sync_ui: Rc::new(sync_ui) }
    }

    /// Pushes the current layout back into the Slint side.
    pub fn refresh(&self) {
        (self.sync_ui)(self);
    }

    /// A `DockWidget` reporting the title and minimum size it was declared
    /// with. Lengths come in as Slint's `length`, i.e. logical pixels.
    pub fn register(&self, name: &str, title: &str, min_width: f32, min_height: f32) {
        self.mutate(|m| m.register(name, title, min_width.ceil() as i32, min_height.ceil() as i32));
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
}

/// Reconciles `model`'s rows with `desired`, matched by `id_of`: existing
/// ids are updated in place, new ones appended, stale ones dropped. Order
/// isn't preserved -- nothing depends on Group/Separator draw order -- only
/// identity.
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
#[doc(hidden)]
pub fn sync_rows<T: Clone + 'static>(model: &VecModel<T>, desired: Vec<T>, id_of: impl Fn(&T) -> i32) {
    let mut desired_ids = Vec::with_capacity(desired.len());
    for item in desired {
        let id = id_of(&item);
        desired_ids.push(id);
        match (0..model.row_count()).find(|&i| model.row_data(i).is_some_and(|r| id_of(&r) == id)) {
            Some(i) => model.set_row_data(i, item),
            None => model.push(item),
        }
    }
    for i in (0..model.row_count()).rev() {
        if model.row_data(i).is_some_and(|r| !desired_ids.contains(&id_of(&r))) {
            model.remove(i);
        }
    }
}

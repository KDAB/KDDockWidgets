// This file is part of KDDockWidgets.
//
// SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
//
// SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
//
// Contact KDAB at <info@kdab.com> for commercial licensing options.

//! Rust side of the KDDockWidgets Slint prototype.
//!
//! An app needs two things from this crate: the `ui/` Slint components,
//! imported as a Slint library (`import { DropArea, DockWidget } from
//! "@kddockwidgets";`), and [`DockingArea`], the Rust handle on one of those
//! `DropArea`s:
//!
//! ```ignore
//! slint::include_modules!();
//! use kddockwidgets::Location;
//!
//! let ui = AppWindow::new()?;
//! let docking = kddockwidgets::install!(&ui);
//!
//! docking.add_dock_widget("editor", Location::OnLeft, None);
//! docking.add_dock_widget_as_tab("console", "editor");
//! ```
//!
//! [`install!`] wires the two sides together; everything below it is
//! internal, but public for apps that want a layout without a UI:
//! - [`DockingLayout`], a safe wrapper around KDDockWidgets' own C++
//!   layouting engine (see `cpp/bridge.h`), which computes where every
//!   Group and Separator goes, keyed by integer Group ids;
//! - on top of it, a name-keyed layer mapping dock widgets (by their
//!   `unique-name`) to Groups and tabs, which is what [`DockingArea`] hands
//!   out as [`GroupView`]s and [`DockWidgetState`]s.

mod area;
mod ffi;
mod indicators;
mod install;
mod manager;

pub use area::DockingArea;
pub use ffi::bridge::{DropRect, GroupGeometry, Location, SeparatorGeometry};
pub use manager::{DockWidgetState, DragState, DropLocation, GroupView, IndicatorView};

#[doc(hidden)]
pub use area::sync_rows;
#[doc(hidden)]
pub use indicators::indicator_image;

/// Re-exported for [`install!`], whose expansion needs to name Slint's own
/// types in a crate that may well call its `slint` dependency something else.
#[doc(hidden)]
pub use slint;

use cxx::UniquePtr;

/// Owns one KDDockWidgets layouting tree.
///
/// There is one `DockingLayout` per top-level `DropArea` (just one, for now,
/// since this app isn't multi-window yet). It only tracks geometry: the
/// caller is expected to keep its own data (titles, colors, which tab is
/// current, ...) keyed by the same `id` used here, and to re-read
/// [`groups`](Self::groups)/[`separators`](Self::separators) after every
/// mutating call to refresh whatever it displays.
pub struct DockingLayout {
    engine: UniquePtr<ffi::bridge::DockingEngine>,
}

impl DockingLayout {
    pub fn new() -> Self {
        Self {
            engine: ffi::bridge::new_docking_engine(),
        }
    }

    /// Resizes the whole layout. Call this whenever the DropArea is resized.
    pub fn resize(&mut self, width: i32, height: i32) {
        self.engine.pin_mut().resize(width, height);
    }

    /// Adds a new Group with the given minimum content size and the given
    /// id, chosen by the caller. Ids must be unique and non-zero.
    pub fn add_group(&mut self, id: i32, min_width: i32, min_height: i32, location: Location) {
        self.engine
            .pin_mut()
            .addGroup(id, min_width, min_height, location);
    }

    /// Like [`add_group`](Self::add_group), but `location` is relative to
    /// an existing Group (`relative_to_id`) instead of the whole layout.
    /// This is what produces actual nesting: adding a Group OnBottom
    /// relative to one that's itself side by side with others only splits
    /// that one Group's own space, rather than the whole layout.
    pub fn add_group_relative_to(
        &mut self,
        id: i32,
        min_width: i32,
        min_height: i32,
        location: Location,
        relative_to_id: i32,
    ) {
        self.engine.pin_mut().addGroupRelativeTo(
            id,
            min_width,
            min_height,
            location,
            relative_to_id,
        );
    }

    /// Removes the Group with the given id. No-op if not found.
    pub fn remove_group(&mut self, id: i32) {
        self.engine.pin_mut().removeGroup(id);
    }

    /// Changes the minimum size of an existing Group. No-op if not found.
    pub fn set_group_min_size(&mut self, id: i32, min_width: i32, min_height: i32) {
        self.engine
            .pin_mut()
            .setGroupMinSize(id, min_width, min_height);
    }

    /// Moves an existing Group elsewhere in the layout, keeping its id.
    /// `relative_to_id` of `None` means relative to the whole layout. No-op
    /// if `id` isn't found, or equals `relative_to_id`.
    pub fn move_group(
        &mut self,
        id: i32,
        min_width: i32,
        min_height: i32,
        location: Location,
        relative_to_id: Option<i32>,
    ) {
        self.engine.pin_mut().moveGroup(
            id,
            min_width,
            min_height,
            location,
            relative_to_id.unwrap_or(0),
        );
    }

    /// The rect a Group with `dragged_id`'s current size would land in if
    /// dropped at `location` relative to `relative_to_id` (`None` for the
    /// whole layout), without moving anything. Used for the drag-and-drop
    /// preview rubber band.
    pub fn drop_rect(
        &self,
        dragged_id: i32,
        location: Location,
        relative_to_id: Option<i32>,
    ) -> DropRect {
        self.engine
            .dropRect(dragged_id, location, relative_to_id.unwrap_or(0))
    }

    /// Starts an interactive drag of the Separator with the given id. No-op
    /// if not found.
    pub fn separator_press(&mut self, id: i32) {
        self.engine.pin_mut().separatorMousePress(id);
    }

    /// Ends an interactive drag started by [`separator_press`](Self::separator_press).
    pub fn separator_release(&mut self, id: i32) {
        self.engine.pin_mut().separatorMouseRelease(id);
    }

    /// Moves the Separator with the given id by `(dx, dy)` from its last
    /// reported position. No-op if not found or not currently being dragged
    /// (see [`separator_press`](Self::separator_press)).
    pub fn separator_move(&mut self, id: i32, dx: i32, dy: i32) {
        self.engine.pin_mut().separatorMouseMove(id, dx, dy);
    }

    /// Current geometry of every Group, in no particular order.
    pub fn groups(&self) -> Vec<GroupGeometry> {
        self.engine.groups()
    }

    /// Current geometry of every Separator, in no particular order.
    pub fn separators(&self) -> Vec<SeparatorGeometry> {
        self.engine.separators()
    }
}

impl Default for DockingLayout {
    fn default() -> Self {
        Self::new()
    }
}

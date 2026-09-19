// This file is part of KDDockWidgets.
//
// SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
//
// SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
//
// Contact KDAB at <info@kdab.com> for commercial licensing options.

//! Rust side of the KDDockWidgets Slint prototype.
//!
//! This crate currently ships two things:
//! - the `ui/` Slint components (TitleBar, DockWidget, Group, Separator,
//!   DropArea), consumed by the `slint_example` crate through Slint's
//!   library import syntax (`import { DropArea } from "@kddockwidgets";`);
//! - [`DockingLayout`], a safe wrapper around KDDockWidgets' own C++
//!   layouting engine (see `cpp/bridge.h`), which computes where every
//!   Group and Separator goes. This crate deliberately knows nothing about
//!   tabs, titles or colors — see the `slint_example` crate for that.

mod ffi;

pub use ffi::ffi::{GroupGeometry, Location, SeparatorGeometry};

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
    engine: UniquePtr<ffi::ffi::DockingEngine>,
}

impl DockingLayout {
    pub fn new() -> Self {
        Self { engine: ffi::ffi::new_docking_engine() }
    }

    /// Resizes the whole layout. Call this whenever the DropArea is resized.
    pub fn resize(&mut self, width: i32, height: i32) {
        self.engine.pin_mut().resize(width, height);
    }

    /// Adds a new Group with the given minimum content size and the given
    /// id, chosen by the caller. Ids must be unique and non-zero.
    pub fn add_group(&mut self, id: i32, min_width: i32, min_height: i32, location: Location) {
        self.engine.pin_mut().addGroup(id, min_width, min_height, location);
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
        self.engine.pin_mut().addGroupRelativeTo(id, min_width, min_height, location, relative_to_id);
    }

    /// Removes the Group with the given id. No-op if not found.
    pub fn remove_group(&mut self, id: i32) {
        self.engine.pin_mut().removeGroup(id);
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

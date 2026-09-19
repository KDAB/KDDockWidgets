// This file is part of KDDockWidgets.
//
// SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
//
// SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
//
// Contact KDAB at <info@kdab.com> for commercial licensing options.

use crate::{DockingLayout, GroupGeometry, Location, SeparatorGeometry};
use std::collections::HashMap;

/// Used for dock widgets placed before their Slint side has registered
/// its real minimum size, see [`DockManager::register`].
const DEFAULT_MIN_SIZE: (i32, i32) = (100, 150);

/// Where a dock widget currently is, as needed by the Slint `DockWidget` to
/// position its content.
#[derive(Debug, Clone, Copy, PartialEq)]
pub struct DockWidgetState {
    /// Geometry of the Group hosting it, including the Group's own title
    /// and tab bars. The Slint side subtracts those.
    pub group_geometry: GroupGeometry,
    /// Whether it's the current tab in its Group.
    pub is_current: bool,
}

/// A Group, as displayed: its geometry plus its tabs.
#[derive(Debug, Clone)]
pub struct GroupView {
    pub geometry: GroupGeometry,
    /// `(unique_name, title)` of each tab, in tab order.
    pub dock_widgets: Vec<(String, String)>,
    pub current_index: usize,
}

struct DockWidgetInfo {
    title: String,
    min_size: (i32, i32),
}

struct Group {
    dock_widgets: Vec<String>,
    current_index: usize,
}

/// Name-keyed layer on top of [`DockingLayout`]: tracks which dock widget
/// lives in which Group, tab order, titles and minimum sizes.
///
/// Dock widgets themselves are declared in Slint and identified by their
/// `unique-name`. There are two independent inputs, which can come in any
/// order:
/// - [`register`](Self::register), called by the Slint `DockWidget` itself,
///   supplies its title and minimum size;
/// - [`add_dock_widget`](Self::add_dock_widget) and friends, called by the
///   app, decide where it goes. A dock widget that was never added (or was
///   closed) isn't open, and isn't shown.
pub struct DockManager {
    layout: DockingLayout,
    dock_widgets: HashMap<String, DockWidgetInfo>,
    groups: HashMap<i32, Group>,
    group_of: HashMap<String, i32>,
    geometries: HashMap<i32, GroupGeometry>,
    next_group_id: i32,
}

impl DockManager {
    pub fn new() -> Self {
        Self {
            layout: DockingLayout::new(),
            dock_widgets: HashMap::new(),
            groups: HashMap::new(),
            group_of: HashMap::new(),
            geometries: HashMap::new(),
            next_group_id: 1,
        }
    }

    pub fn resize(&mut self, width: i32, height: i32) {
        self.layout.resize(width, height);
        self.update_geometries();
    }

    /// Records a dock widget's title and minimum size (including the
    /// Group's title and tab bars). Can be called again to update them.
    pub fn register(&mut self, name: &str, title: &str, min_width: i32, min_height: i32) {
        self.dock_widgets
            .insert(name.to_owned(), DockWidgetInfo { title: title.to_owned(), min_size: (min_width, min_height) });
        if let Some(&group_id) = self.group_of.get(name) {
            self.update_group_min_size(group_id);
        }
    }

    pub fn set_title(&mut self, name: &str, title: &str) {
        if let Some(info) = self.dock_widgets.get_mut(name) {
            info.title = title.to_owned();
        }
    }

    pub fn is_open(&self, name: &str) -> bool {
        self.group_of.contains_key(name)
    }

    /// Opens `name` in a new Group. `location` is relative to `relative_to`'s
    /// Group if given and open, otherwise to the whole layout. No-op if
    /// already open.
    pub fn add_dock_widget(&mut self, name: &str, location: Location, relative_to: Option<&str>) {
        if self.is_open(name) {
            return;
        }

        let id = self.next_group_id;
        self.next_group_id += 1;
        let (min_width, min_height) = self.min_size_of(name);
        match relative_to.and_then(|r| self.group_of.get(r)) {
            Some(&relative_to_id) => {
                self.layout.add_group_relative_to(id, min_width, min_height, location, relative_to_id)
            }
            None => self.layout.add_group(id, min_width, min_height, location),
        }

        self.groups.insert(id, Group { dock_widgets: vec![name.to_owned()], current_index: 0 });
        self.group_of.insert(name.to_owned(), id);
        self.update_geometries();
    }

    /// Opens `name` as a new tab in the Group `existing` is in. No-op if
    /// `name` is already open or `existing` isn't.
    pub fn add_dock_widget_as_tab(&mut self, name: &str, existing: &str) {
        if self.is_open(name) {
            return;
        }
        let Some(&id) = self.group_of.get(existing) else {
            return;
        };

        self.groups.get_mut(&id).unwrap().dock_widgets.push(name.to_owned());
        self.group_of.insert(name.to_owned(), id);
        self.update_group_min_size(id);
    }

    /// Removes `name` from its Group, and the Group from the layout if it was
    /// its last tab. The dock widget stays registered, it's just no longer
    /// open.
    pub fn close(&mut self, name: &str) {
        let Some(id) = self.group_of.remove(name) else {
            return;
        };
        let group = self.groups.get_mut(&id).unwrap();
        group.dock_widgets.retain(|n| n != name);

        if group.dock_widgets.is_empty() {
            self.groups.remove(&id);
            self.layout.remove_group(id);
            self.update_geometries();
        } else {
            group.current_index = group.current_index.min(group.dock_widgets.len() - 1);
            self.update_group_min_size(id);
        }
    }

    /// Starts an interactive drag of the Separator with the given id.
    pub fn separator_press(&mut self, id: i32) {
        self.layout.separator_press(id);
    }

    /// Ends an interactive drag of the Separator with the given id.
    pub fn separator_release(&mut self, id: i32) {
        self.layout.separator_release(id);
    }

    /// Moves the Separator with the given id by `(dx, dy)` from its last
    /// reported position, and refreshes Group geometries accordingly.
    pub fn separator_move(&mut self, id: i32, dx: i32, dy: i32) {
        self.layout.separator_move(id, dx, dy);
        self.update_geometries();
    }

    /// Makes `name` the current tab of its Group.
    pub fn set_current(&mut self, name: &str) {
        let Some(id) = self.group_of.get(name) else {
            return;
        };
        let group = self.groups.get_mut(id).unwrap();
        if let Some(index) = group.dock_widgets.iter().position(|n| n == name) {
            group.current_index = index;
        }
    }

    /// `None` if `name` isn't open.
    pub fn dock_widget_state(&self, name: &str) -> Option<DockWidgetState> {
        let id = self.group_of.get(name)?;
        let group = &self.groups[id];
        Some(DockWidgetState {
            group_geometry: *self.geometries.get(id)?,
            is_current: group.dock_widgets[group.current_index] == name,
        })
    }

    /// Every Group, sorted by `(y, x, id)` so that the order is stable
    /// (the engine's own order isn't).
    pub fn groups(&self) -> Vec<GroupView> {
        let mut groups: Vec<GroupView> = self
            .groups
            .iter()
            .filter_map(|(id, group)| {
                Some(GroupView {
                    geometry: *self.geometries.get(id)?,
                    dock_widgets: group
                        .dock_widgets
                        .iter()
                        .map(|name| {
                            let title = self.dock_widgets.get(name).map_or(name.as_str(), |i| i.title.as_str());
                            (name.clone(), title.to_owned())
                        })
                        .collect(),
                    current_index: group.current_index,
                })
            })
            .collect();
        groups.sort_by_key(|g| (g.geometry.y, g.geometry.x, g.geometry.id));
        groups
    }

    /// Every Separator, sorted by `(y, x, id)`.
    pub fn separators(&self) -> Vec<SeparatorGeometry> {
        let mut separators = self.layout.separators();
        separators.sort_by_key(|s| (s.y, s.x, s.id));
        separators
    }

    fn min_size_of(&self, name: &str) -> (i32, i32) {
        self.dock_widgets.get(name).map_or(DEFAULT_MIN_SIZE, |i| i.min_size)
    }

    /// A Group's minimum size is the largest of its tabs' in each dimension.
    fn update_group_min_size(&mut self, id: i32) {
        let Some(group) = self.groups.get(&id) else {
            return;
        };
        let (min_width, min_height) = group
            .dock_widgets
            .iter()
            .map(|name| self.min_size_of(name))
            .fold((0, 0), |(w, h), (mw, mh)| (w.max(mw), h.max(mh)));
        self.layout.set_group_min_size(id, min_width, min_height);
        self.update_geometries();
    }

    fn update_geometries(&mut self) {
        self.geometries = self.layout.groups().into_iter().map(|g| (g.id, g)).collect();
    }
}

impl Default for DockManager {
    fn default() -> Self {
        Self::new()
    }
}

// This file is part of KDDockWidgets.
//
// SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
//
// SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
//
// Contact KDAB at <info@kdab.com> for commercial licensing options.

use crate::{DockingLayout, DropRect, GroupGeometry, Location, SeparatorGeometry};
use std::collections::HashMap;

/// Used for dock widgets placed before their Slint side has registered
/// its real minimum size, see [`DockManager::register`].
const DEFAULT_MIN_SIZE: (i32, i32) = (100, 150);

/// Side length of a drop indicator icon, and the gaps around it. Loosely
/// mirrors the QtQuick frontend's `ClassicIndicatorsOverlay.qml`
/// (`outterMargin`, `innerMargin`), but at half its fixed 64x64 icon size:
/// that size was tuned for QtQuick's own, typically much larger, example
/// apps. At 64px, the inner cluster's footprint alone (three icons plus two
/// margins, `INDICATOR_SIZE * 3 + INNER_MARGIN * 2`) is over 200px square --
/// bigger than some of this prototype's own nested Groups (e.g.
/// slint_example's Files/Search/Git, nested under Editor/Console). Must
/// match `dropindicators.slint`'s hardcoded `width`/`height` on each
/// indicator `Image`.
const INDICATOR_SIZE: i32 = 32;
const INNER_MARGIN: i32 = 6;
const OUTER_MARGIN: i32 = 6;

/// Mirrors `GroupMetrics` in `ui/types.slint` -- kept in sync by hand, the
/// same way `INDICATOR_SIZE`/margins above mirror `dropindicators.slint`'s
/// fixed icon size. Used only to compute a tab drag's ghost source rect
/// (`ghost_source_rect`): the dragged dock widget's own content area,
/// excluding the Group's title and tab bars.
const GROUP_BORDER_WIDTH: i32 = 1;
const GROUP_HEADER_HEIGHT: i32 = GROUP_BORDER_WIDTH + 24 /* title-bar-height */ + 22 /* tab-bar-height */;

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

/// The nine places a drop can land, mirroring the QtQuick frontend's
/// `ClassicDropIndicatorOverlay`. `Outer*` splits the whole layout; the rest
/// are relative to whichever Group is currently hovered.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum DropLocation {
    Left,
    Top,
    Right,
    Bottom,
    Center,
    OuterLeft,
    OuterTop,
    OuterRight,
    OuterBottom,
}

impl DropLocation {
    /// The engine's own (4-way) `Location` this corresponds to. Panics for
    /// `Center`, which has no engine equivalent -- it merges tabs instead of
    /// inserting a new Group, see [`DockManager::apply_drop`].
    fn to_engine_location(self) -> Location {
        match self {
            DropLocation::Left | DropLocation::OuterLeft => Location::OnLeft,
            DropLocation::Top | DropLocation::OuterTop => Location::OnTop,
            DropLocation::Right | DropLocation::OuterRight => Location::OnRight,
            DropLocation::Bottom | DropLocation::OuterBottom => Location::OnBottom,
            DropLocation::Center => unreachable!("Center has no engine Location"),
        }
    }

    fn is_outer(self) -> bool {
        matches!(
            self,
            DropLocation::OuterLeft
                | DropLocation::OuterTop
                | DropLocation::OuterRight
                | DropLocation::OuterBottom
        )
    }
}

/// One visible drop indicator icon: where to draw it, and whether the
/// pointer is currently over it (which picks the "active" artwork and is
/// what a drop actually commits to).
#[derive(Debug, Clone, Copy, PartialEq)]
pub struct IndicatorView {
    pub location: DropLocation,
    pub x: i32,
    pub y: i32,
    pub active: bool,
}

/// Everything needed to draw the drag-and-drop preview: the ghost image
/// (tracking the pointer, offset by where it grabbed the Group) and the
/// rubber band showing where a drop would land, if the pointer is currently
/// over an indicator.
///
/// The ghost's actual pixels aren't here -- that's a `slint::Image`, and
/// this crate's non-`area` modules stay Slint-agnostic -- only its geometry.
#[derive(Debug, Clone, Copy, PartialEq)]
pub struct DragState {
    pub ghost_x: i32,
    pub ghost_y: i32,
    pub ghost_width: i32,
    pub ghost_height: i32,
    pub rubber_band: Option<DropRect>,
}

struct DockWidgetInfo {
    title: String,
    min_size: (i32, i32),
}

struct Group {
    dock_widgets: Vec<String>,
    current_index: usize,
}

/// State for an in-progress drag, started by [`DockManager::drag_started`].
struct Drag {
    /// The dock widget grabbed -- always meaningful, even for a whole-Group
    /// drag (it's whichever tab the title bar belonged to), since it's what
    /// picks the ghost image and, for a tab-only drag, what gets detached.
    name: String,
    group_id: i32,
    /// Titlebar drag (moves the whole Group) vs. tab drag (may detach just
    /// that one dock widget, see [`DockManager::apply_drop`]).
    whole_group: bool,
    /// Offset from the dragged Group's top-left to where the pointer
    /// grabbed it, so the ghost tracks the pointer without jumping to be
    /// centered under it.
    grab_dx: i32,
    grab_dy: i32,
    pointer_x: i32,
    pointer_y: i32,
    hovered_group: Option<i32>,
    current: Option<DropLocation>,
}

/// Name-keyed layer on top of [`DockingLayout`]: tracks which dock widget
/// lives in which Group, tab order, titles and minimum sizes. This is the
/// state behind [`DockingArea`](crate::DockingArea), which is what apps
/// actually talk to.
///
/// Dock widgets themselves are declared in Slint and identified by their
/// `unique-name`. There are two independent inputs, which can come in any
/// order:
/// - [`register`](Self::register), called by the Slint `DockWidget` itself,
///   supplies its title and minimum size;
/// - [`add_dock_widget`](Self::add_dock_widget) and friends, called by the
///   app, decide where it goes. A dock widget that was never added (or was
///   closed) isn't open, and isn't shown.
pub(crate) struct DockManager {
    layout: DockingLayout,
    dock_widgets: HashMap<String, DockWidgetInfo>,
    groups: HashMap<i32, Group>,
    group_of: HashMap<String, i32>,
    geometries: HashMap<i32, GroupGeometry>,
    next_group_id: i32,
    area_width: i32,
    area_height: i32,
    drag: Option<Drag>,
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
            area_width: 0,
            area_height: 0,
            drag: None,
        }
    }

    pub fn resize(&mut self, width: i32, height: i32) {
        self.area_width = width;
        self.area_height = height;
        self.layout.resize(width, height);
        self.update_geometries();
    }

    /// Records a dock widget's title and minimum size (including the
    /// Group's title and tab bars). Can be called again to update them.
    pub fn register(&mut self, name: &str, title: &str, min_width: i32, min_height: i32) {
        self.dock_widgets.insert(
            name.to_owned(),
            DockWidgetInfo {
                title: title.to_owned(),
                min_size: (min_width, min_height),
            },
        );
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
            Some(&relative_to_id) => self.layout.add_group_relative_to(
                id,
                min_width,
                min_height,
                location,
                relative_to_id,
            ),
            None => self.layout.add_group(id, min_width, min_height, location),
        }

        self.groups.insert(
            id,
            Group {
                dock_widgets: vec![name.to_owned()],
                current_index: 0,
            },
        );
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

        self.groups
            .get_mut(&id)
            .unwrap()
            .dock_widgets
            .push(name.to_owned());
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

    /// Starts dragging `name`'s Group: `whole_group` is true for a titlebar
    /// drag (moves every tab), false for a tab drag (may detach just that
    /// tab, see [`apply_drop`](Self::apply_drop)). `(x, y)` is the pointer's
    /// starting position, in DropArea-local coordinates. No-op if `name`
    /// isn't open.
    pub fn drag_started(&mut self, name: &str, whole_group: bool, x: i32, y: i32) {
        let Some(&group_id) = self.group_of.get(name) else {
            return;
        };
        let Some((rx, ry, _, _)) = self.ghost_source_rect(group_id, whole_group) else {
            return;
        };
        self.drag = Some(Drag {
            name: name.to_owned(),
            group_id,
            whole_group,
            grab_dx: x - rx,
            grab_dy: y - ry,
            pointer_x: x,
            pointer_y: y,
            hovered_group: None,
            current: None,
        });
        self.update_drag(x, y);
    }

    /// Updates the in-progress drag's pointer position, recomputing which
    /// Group (if any) is hovered and which indicator (if any) is active.
    /// No-op if no drag is in progress.
    pub fn drag_moved(&mut self, x: i32, y: i32) {
        self.update_drag(x, y);
    }

    /// Ends the in-progress drag at `(x, y)`, committing the move if the
    /// pointer was over an indicator, discarding it otherwise (i.e.
    /// releasing over empty space cancels the drag). No-op if no drag was in
    /// progress.
    pub fn drag_ended(&mut self, x: i32, y: i32) {
        self.update_drag(x, y);
        let Some(drag) = self.drag.take() else {
            return;
        };
        if let Some(location) = drag.current {
            self.apply_drop(drag, location);
        }
    }

    /// Abandons the in-progress drag without moving anything.
    pub fn drag_cancelled(&mut self) {
        self.drag = None;
    }

    /// Every indicator currently visible (empty if no drag is in progress).
    pub fn indicators(&self) -> Vec<IndicatorView> {
        let Some(drag) = &self.drag else {
            return Vec::new();
        };
        self.visible_locations(drag.group_id, drag.hovered_group)
            .into_iter()
            .map(|(location, x, y)| IndicatorView {
                location,
                x,
                y,
                active: Some(location) == drag.current,
            })
            .collect()
    }

    /// Ghost and rubber band geometry for the in-progress drag, or `None` if
    /// there isn't one.
    pub fn drag_state(&self) -> Option<DragState> {
        let drag = self.drag.as_ref()?;
        let (_, _, width, height) = self.ghost_source_rect(drag.group_id, drag.whole_group)?;
        Some(DragState {
            ghost_x: drag.pointer_x - drag.grab_dx,
            ghost_y: drag.pointer_y - drag.grab_dy,
            ghost_width: width,
            ghost_height: height,
            rubber_band: drag
                .current
                .map(|location| self.drop_rect_for(drag, location)),
        })
    }

    /// The rect a drag's ghost is captured from and tracks: the whole Group
    /// (chrome included) for a titlebar drag, or just the dragged dock
    /// widget's own content area for a tab drag -- the same formula
    /// `DockWidget` itself positions by in `ui/dockwidget.slint`. A tab
    /// drag can't use the whole Group either way: only the *current* tab's
    /// content is ever actually rendered (`DockWidget`'s own `visible`
    /// binding gates on it), which is why `DockingArea::drag_started` makes
    /// the dragged tab current before capturing anything.
    fn ghost_source_rect(&self, group_id: i32, whole_group: bool) -> Option<(i32, i32, i32, i32)> {
        let geo = self.geometries.get(&group_id)?;
        Some(if whole_group {
            (geo.x, geo.y, geo.width, geo.height)
        } else {
            (
                geo.x + GROUP_BORDER_WIDTH,
                geo.y + GROUP_HEADER_HEIGHT,
                (geo.width - 2 * GROUP_BORDER_WIDTH).max(0),
                (geo.height - GROUP_HEADER_HEIGHT - GROUP_BORDER_WIDTH).max(0),
            )
        })
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
                            let title = self
                                .dock_widgets
                                .get(name)
                                .map_or(name.as_str(), |i| i.title.as_str());
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
        self.dock_widgets
            .get(name)
            .map_or(DEFAULT_MIN_SIZE, |i| i.min_size)
    }

    /// A Group's minimum size is the largest of its tabs' in each dimension.
    fn group_min_size(&self, id: i32) -> (i32, i32) {
        let Some(group) = self.groups.get(&id) else {
            return (0, 0);
        };
        group
            .dock_widgets
            .iter()
            .map(|name| self.min_size_of(name))
            .fold((0, 0), |(w, h), (mw, mh)| (w.max(mw), h.max(mh)))
    }

    fn update_group_min_size(&mut self, id: i32) {
        let (min_width, min_height) = self.group_min_size(id);
        self.layout.set_group_min_size(id, min_width, min_height);
        self.update_geometries();
    }

    fn update_geometries(&mut self) {
        self.geometries = self
            .layout
            .groups()
            .into_iter()
            .map(|g| (g.id, g))
            .collect();
    }

    fn hovered_group_at(&self, x: i32, y: i32) -> Option<i32> {
        self.geometries
            .iter()
            .find(|(_, g)| g.visible && point_in_rect(x, y, g.x, g.y, g.width, g.height))
            .map(|(&id, _)| id)
    }

    /// Recomputes `hovered_group` and `current` for the in-progress drag
    /// from the pointer's new position. No-op if no drag is in progress.
    fn update_drag(&mut self, x: i32, y: i32) {
        let Some(drag) = self.drag.as_ref() else {
            return;
        };
        let hovered_group = self.hovered_group_at(x, y);
        let current = self
            .visible_locations(drag.group_id, hovered_group)
            .into_iter()
            .find(|&(_, ix, iy)| point_in_rect(x, y, ix, iy, INDICATOR_SIZE, INDICATOR_SIZE))
            .map(|(location, _, _)| location);

        let drag = self.drag.as_mut().unwrap();
        drag.pointer_x = x;
        drag.pointer_y = y;
        drag.hovered_group = hovered_group;
        drag.current = current;
    }

    /// Every indicator that should currently be shown, as `(location, x, y)`
    /// top-left corners (each icon is `INDICATOR_SIZE` square), for a drag
    /// whose source is `source_group`, while `hovered_group` (if any) is
    /// under the pointer.
    ///
    /// Mirrors `Core::DropIndicatorOverlay::dropIndicatorVisible`, with one
    /// simplification specific to this prototype not supporting detaching
    /// into floating windows: inner indicators and Center are suppressed
    /// entirely over the dragged Group's own Group (every such drop would
    /// either be a no-op or, worse, try to nest a Group inside itself),
    /// rather than being shown but rejected case-by-case.
    fn visible_locations(
        &self,
        source_group: i32,
        hovered_group: Option<i32>,
    ) -> Vec<(DropLocation, i32, i32)> {
        // Matches ClassicIndicatorsOverlay.qml's `visible: width > 50 && height > 50`.
        if self.area_width <= 50 || self.area_height <= 50 {
            return Vec::new();
        }

        let mut out = Vec::new();

        // Outer indicators split the whole layout, so they're always shown
        // -- except while hovering the only Group there is, where they'd be
        // redundant with the (suppressed) inner ones. Upstream also keeps
        // them in that case if another window might be obscuring the
        // target; that doesn't apply here, there's only ever one window.
        let hide_outer = hovered_group.is_some() && self.groups.len() == 1;
        if !hide_outer {
            let cx = self.area_width / 2 - INDICATOR_SIZE / 2;
            let cy = self.area_height / 2 - INDICATOR_SIZE / 2;
            out.push((DropLocation::OuterLeft, OUTER_MARGIN, cy));
            out.push((
                DropLocation::OuterRight,
                self.area_width - OUTER_MARGIN - INDICATOR_SIZE,
                cy,
            ));
            out.push((DropLocation::OuterTop, cx, OUTER_MARGIN));
            out.push((
                DropLocation::OuterBottom,
                cx,
                self.area_height - OUTER_MARGIN - INDICATOR_SIZE,
            ));
        }

        if let Some(hovered) = hovered_group {
            if hovered != source_group {
                if let Some(geo) = self.geometries.get(&hovered) {
                    let cx = geo.x + geo.width / 2 - INDICATOR_SIZE / 2;
                    let cy = geo.y + geo.height / 2 - INDICATOR_SIZE / 2;
                    out.push((DropLocation::Center, cx, cy));
                    out.push((DropLocation::Left, cx - INNER_MARGIN - INDICATOR_SIZE, cy));
                    out.push((DropLocation::Right, cx + INNER_MARGIN + INDICATOR_SIZE, cy));
                    out.push((DropLocation::Top, cx, cy - INNER_MARGIN - INDICATOR_SIZE));
                    out.push((DropLocation::Bottom, cx, cy + INNER_MARGIN + INDICATOR_SIZE));
                }
            }
        }

        out
    }

    /// The preview rect for dropping the dragged Group at `location`. For
    /// `Center` that's simply the hovered Group's own rect (the drop doesn't
    /// resize anything, it just adds a tab); for everything else it asks the
    /// engine what dropping there would actually produce.
    fn drop_rect_for(&self, drag: &Drag, location: DropLocation) -> DropRect {
        if location == DropLocation::Center {
            // Only reachable once `hovered_group` is set: Center is never
            // in `visible_locations`'s output otherwise.
            let hovered = drag
                .hovered_group
                .expect("Center indicator implies a hovered Group");
            let geo = self.geometries[&hovered];
            return DropRect {
                x: geo.x,
                y: geo.y,
                width: geo.width,
                height: geo.height,
            };
        }
        let relative_to = if location.is_outer() {
            None
        } else {
            drag.hovered_group
        };
        self.layout
            .drop_rect(drag.group_id, location.to_engine_location(), relative_to)
    }

    /// Commits a drop at `location` for the just-ended `drag`.
    fn apply_drop(&mut self, drag: Drag, location: DropLocation) {
        // A titlebar drag always moves the whole Group; so does a tab drag
        // out of a Group with only that one tab, since detaching it would
        // just leave an identical, immediately-removed Group behind.
        let move_whole = drag.whole_group
            || self
                .groups
                .get(&drag.group_id)
                .is_some_and(|g| g.dock_widgets.len() <= 1);

        match location {
            DropLocation::Center => {
                if let Some(target) = drag.hovered_group {
                    self.drop_center(&drag, target, move_whole);
                }
            }
            _ => {
                let engine_location = location.to_engine_location();
                let relative_to = if location.is_outer() {
                    None
                } else {
                    drag.hovered_group
                };
                self.drop_at(&drag, engine_location, relative_to, move_whole);
            }
        }
        self.update_geometries();
    }

    /// Drops onto an inner/outer indicator: repositions the whole dragged
    /// Group, or detaches just the dragged tab into a brand-new one.
    fn drop_at(
        &mut self,
        drag: &Drag,
        location: Location,
        relative_to: Option<i32>,
        move_whole: bool,
    ) {
        if relative_to == Some(drag.group_id) {
            return; // Dropping a Group relative to itself is meaningless.
        }

        if move_whole {
            let (min_width, min_height) = self.group_min_size(drag.group_id);
            self.layout
                .move_group(drag.group_id, min_width, min_height, location, relative_to);
            return;
        }

        // Detach just the dragged tab into a new Group, the same way
        // add_dock_widget/add_dock_widget_as_tab build one.
        if let Some(old_group) = self.groups.get_mut(&drag.group_id) {
            old_group.dock_widgets.retain(|n| n != &drag.name);
            old_group.current_index = old_group
                .current_index
                .min(old_group.dock_widgets.len().saturating_sub(1));
        }
        self.update_group_min_size(drag.group_id);

        let id = self.next_group_id;
        self.next_group_id += 1;
        let (min_width, min_height) = self.min_size_of(&drag.name);
        match relative_to {
            Some(r) => self
                .layout
                .add_group_relative_to(id, min_width, min_height, location, r),
            None => self.layout.add_group(id, min_width, min_height, location),
        }
        self.groups.insert(
            id,
            Group {
                dock_widgets: vec![drag.name.clone()],
                current_index: 0,
            },
        );
        self.group_of.insert(drag.name.clone(), id);
    }

    /// Drops onto the Center indicator: merges the dragged tab(s) into
    /// `target_group`'s tab bar instead of inserting a new Group.
    fn drop_center(&mut self, drag: &Drag, target_group: i32, move_whole: bool) {
        if target_group == drag.group_id {
            return;
        }

        let moved_names: Vec<String> = if move_whole {
            let Some(group) = self.groups.remove(&drag.group_id) else {
                return;
            };
            self.layout.remove_group(drag.group_id);
            group.dock_widgets
        } else {
            let Some(old_group) = self.groups.get_mut(&drag.group_id) else {
                return;
            };
            old_group.dock_widgets.retain(|n| n != &drag.name);
            old_group.current_index = old_group
                .current_index
                .min(old_group.dock_widgets.len().saturating_sub(1));
            self.update_group_min_size(drag.group_id);
            vec![drag.name.clone()]
        };

        for name in &moved_names {
            self.group_of.insert(name.clone(), target_group);
        }
        if let Some(target) = self.groups.get_mut(&target_group) {
            target.dock_widgets.extend(moved_names);
        }
        self.update_group_min_size(target_group);
    }
}

fn point_in_rect(x: i32, y: i32, rx: i32, ry: i32, rw: i32, rh: i32) -> bool {
    x >= rx && x < rx + rw && y >= ry && y < ry + rh
}

impl Default for DockManager {
    fn default() -> Self {
        Self::new()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    /// Two side-by-side Groups, "a" on the left and "b" on the right, in an
    /// 800x600 area -- big enough that indicator geometry never clips.
    fn setup_two_groups() -> DockManager {
        let mut m = DockManager::new();
        m.resize(800, 600);
        m.register("a", "A", 50, 50);
        m.register("b", "B", 50, 50);
        m.add_dock_widget("a", Location::OnLeft, None);
        m.add_dock_widget("b", Location::OnRight, None);
        m
    }

    fn group_id_of(m: &DockManager, name: &str) -> i32 {
        m.group_of[name]
    }

    /// Center of the indicator at `location`, panicking if it isn't
    /// currently visible -- tests always drive a drag through indicator
    /// centers rather than hard-coding pixel positions, so they don't need
    /// to know INDICATOR_SIZE/margins themselves.
    fn indicator_center(m: &DockManager, location: DropLocation) -> (i32, i32) {
        let indicator = m
            .indicators()
            .into_iter()
            .find(|i| i.location == location)
            .unwrap_or_else(|| panic!("{location:?} indicator isn't visible"));
        (
            indicator.x + INDICATOR_SIZE / 2,
            indicator.y + INDICATOR_SIZE / 2,
        )
    }

    #[test]
    fn dragging_the_titlebar_onto_center_merges_the_whole_group_as_tabs() {
        let mut m = setup_two_groups();
        let (a_id, b_id) = (group_id_of(&m, "a"), group_id_of(&m, "b"));
        let a_geo = m.geometries[&a_id];

        m.drag_started("a", true, a_geo.x + 5, a_geo.y + 5);
        let b_geo = m.geometries[&b_id];
        m.drag_moved(b_geo.x + b_geo.width / 2, b_geo.y + b_geo.height / 2); // hover b first, to reveal its Center indicator
        let (cx, cy) = indicator_center(&m, DropLocation::Center);
        m.drag_moved(cx, cy);
        m.drag_ended(cx, cy);

        assert_eq!(
            m.groups.len(),
            1,
            "a's now-empty Group should have been removed"
        );
        assert!(!m.groups.contains_key(&a_id));
        assert_eq!(
            m.groups[&b_id].dock_widgets,
            vec!["b".to_string(), "a".to_string()]
        );
    }

    #[test]
    fn dragging_one_tab_out_of_a_multi_tab_group_detaches_just_that_tab() {
        let mut m = setup_two_groups();
        m.register("c", "C", 50, 50);
        m.add_dock_widget_as_tab("c", "a"); // a's Group is now ["a", "c"]
        let (a_id, b_id) = (group_id_of(&m, "a"), group_id_of(&m, "b"));

        let a_geo = m.geometries[&a_id];
        m.drag_started("c", false, a_geo.x + 5, a_geo.y + 5);
        let b_geo = m.geometries[&b_id];
        m.drag_moved(b_geo.x + b_geo.width / 2, b_geo.y + b_geo.height / 2);
        let (rx, ry) = indicator_center(&m, DropLocation::Right);
        m.drag_moved(rx, ry);
        m.drag_ended(rx, ry);

        assert_eq!(
            m.groups[&a_id].dock_widgets,
            vec!["a".to_string()],
            "c should have left a's Group"
        );
        let c_id = group_id_of(&m, "c");
        assert!(
            c_id != a_id && c_id != b_id,
            "c should be in a brand-new Group"
        );
        assert_eq!(m.groups[&c_id].dock_widgets, vec!["c".to_string()]);
        assert_eq!(m.groups.len(), 3);
    }

    #[test]
    fn dragging_the_only_tab_in_a_group_moves_the_whole_group_instead_of_detaching() {
        let mut m = setup_two_groups();
        let (a_id, b_id) = (group_id_of(&m, "a"), group_id_of(&m, "b"));
        let a_geo = m.geometries[&a_id];

        // "a" is alone in its Group, so a *tab* drag (whole_group: false)
        // should behave exactly like a titlebar drag.
        m.drag_started("a", false, a_geo.x + 5, a_geo.y + 5);
        let b_geo = m.geometries[&b_id];
        m.drag_moved(b_geo.x + b_geo.width / 2, b_geo.y + b_geo.height / 2);
        let (cx, cy) = indicator_center(&m, DropLocation::Center);
        m.drag_moved(cx, cy);
        m.drag_ended(cx, cy);

        assert_eq!(m.groups.len(), 1);
        assert_eq!(
            m.groups[&b_id].dock_widgets,
            vec!["b".to_string(), "a".to_string()]
        );
    }

    #[test]
    fn releasing_away_from_any_indicator_cancels_the_drag() {
        let mut m = setup_two_groups();
        let a_id = group_id_of(&m, "a");
        let a_geo = m.geometries[&a_id];

        m.drag_started("a", true, a_geo.x + 5, a_geo.y + 5);
        m.drag_ended(a_geo.x + 5, a_geo.y + 5); // back near the start, not over any indicator

        assert_eq!(m.groups.len(), 2);
        assert_eq!(m.groups[&a_id].dock_widgets, vec!["a".to_string()]);
        assert_eq!(
            m.geometries[&a_id], a_geo,
            "layout should be untouched by a cancelled drag"
        );
    }

    #[test]
    fn hovering_the_dragged_groups_own_group_shows_no_inner_or_center_indicators() {
        let mut m = setup_two_groups();
        let a_id = group_id_of(&m, "a");
        let a_geo = m.geometries[&a_id];

        m.drag_started("a", true, a_geo.x + 5, a_geo.y + 5); // starts already hovering its own Group
        let indicators = m.indicators();

        assert!(
            !indicators.is_empty(),
            "outer indicators should still be visible"
        );
        assert!(
            indicators.iter().all(|i| matches!(
                i.location,
                DropLocation::OuterLeft | DropLocation::OuterTop | DropLocation::OuterRight | DropLocation::OuterBottom
            )),
            "no inner/Center indicator should be shown over the dragged Group's own Group: {indicators:?}"
        );
    }

    #[test]
    fn dropping_on_an_outer_indicator_repositions_the_whole_group_in_the_layout() {
        let mut m = setup_two_groups();
        let a_id = group_id_of(&m, "a");
        let a_geo = m.geometries[&a_id];

        m.drag_started("a", true, a_geo.x + 5, a_geo.y + 5);
        let (ox, oy) = indicator_center(&m, DropLocation::OuterBottom);
        m.drag_moved(ox, oy);
        m.drag_ended(ox, oy);

        assert_eq!(m.groups.len(), 2, "moving is a reposition, not a merge");
        let new_geo = m.geometries[&a_id];
        assert!(
            new_geo.y > a_geo.y,
            "expected a to move down: before {a_geo:?}, after {new_geo:?}"
        );
    }

    #[test]
    fn a_titlebar_drags_ghost_covers_the_whole_group() {
        let mut m = setup_two_groups();
        let a_id = group_id_of(&m, "a");
        let a_geo = m.geometries[&a_id];

        m.drag_started("a", true, a_geo.x + 5, a_geo.y + 5);
        let state = m.drag_state().expect("a drag should be in progress");

        assert_eq!(state.ghost_width, a_geo.width);
        assert_eq!(state.ghost_height, a_geo.height);
    }

    #[test]
    fn a_tab_drags_ghost_is_cropped_to_just_the_dock_widgets_content_area() {
        let mut m = setup_two_groups();
        m.register("c", "C", 50, 50);
        m.add_dock_widget_as_tab("c", "a"); // a's Group is now ["a", "c"]
        let a_id = group_id_of(&m, "a");
        let a_geo = m.geometries[&a_id];

        m.drag_started("c", false, a_geo.x + 5, a_geo.y + 5);
        let state = m.drag_state().expect("a drag should be in progress");

        assert!(
            state.ghost_width < a_geo.width,
            "ghost should exclude the Group's border, not span its full width: {} vs {}",
            state.ghost_width,
            a_geo.width
        );
        assert!(
            state.ghost_height < a_geo.height,
            "ghost should exclude the title/tab bar chrome, not span the Group's full height: {} vs {}",
            state.ghost_height,
            a_geo.height
        );
    }
}

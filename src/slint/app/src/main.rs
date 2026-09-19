// This file is part of KDDockWidgets.
//
// SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
//
// SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
//
// Contact KDAB at <info@kdab.com> for commercial licensing options.

slint::include_modules!();

use kddockwidgets::{DockingLayout, GroupGeometry, Location, SeparatorGeometry};
use slint::{Color, ComponentHandle, ModelRc, VecModel};
use std::cell::RefCell;
use std::collections::HashMap;
use std::rc::Rc;

/// The width/height reported to the layouting engine as this dock widget's
/// minimum size. 100 matches DockWidget's own hardcoded width in
/// ui/dockwidget.slint; the height leaves room for the title bar (24px) and
/// tab bar (22px) above some minimal content.
const MIN_DOCKWIDGET_WIDTH: i32 = 100;
const MIN_DOCKWIDGET_HEIGHT: i32 = 150;

/// Everything about a Group that Rust owns and the C++ engine doesn't know
/// about: titles, colors, and which tab is current.
struct GroupTabs {
    dockwidgets: Vec<(String, Color)>,
    current_index: i32,
}

struct AppState {
    layout: DockingLayout,
    tabs: HashMap<i32, GroupTabs>,
    next_id: i32,
}

impl AppState {
    /// Adds a Group relative to the whole layout. Returns its id, e.g. to
    /// later nest another Group under it with `add_group_relative_to`.
    fn add_group(&mut self, dockwidgets: Vec<(String, Color)>, location: Location) -> i32 {
        let id = self.next_id;
        self.next_id += 1;
        self.layout.add_group(id, MIN_DOCKWIDGET_WIDTH, MIN_DOCKWIDGET_HEIGHT, location);
        self.tabs.insert(id, GroupTabs { dockwidgets, current_index: 0 });
        id
    }

    /// Adds a Group nested under an existing one, splitting only that
    /// Group's own space rather than the whole layout.
    fn add_group_relative_to(&mut self, dockwidgets: Vec<(String, Color)>, location: Location, relative_to_id: i32) -> i32 {
        let id = self.next_id;
        self.next_id += 1;
        self.layout.add_group_relative_to(id, MIN_DOCKWIDGET_WIDTH, MIN_DOCKWIDGET_HEIGHT, location, relative_to_id);
        self.tabs.insert(id, GroupTabs { dockwidgets, current_index: 0 });
        id
    }

    /// Group geometries, sorted into a stable, deterministic order (the
    /// engine's own `groups()` comes back in arbitrary order). Both
    /// `refresh` and the close/current-changed callbacks use this, so that
    /// an index coming back from the UI always means the same Group.
    fn sorted_groups(&self) -> Vec<GroupGeometry> {
        let mut groups = self.layout.groups();
        groups.sort_by_key(|g| (g.y, g.x, g.id));
        groups
    }

    fn sorted_separators(&self) -> Vec<SeparatorGeometry> {
        let mut separators = self.layout.separators();
        separators.sort_by_key(|s| (s.y, s.x, s.id));
        separators
    }
}

fn refresh(ui: &AppWindow, state: &AppState) {
    let groups = state
        .sorted_groups()
        .into_iter()
        .filter_map(|g| {
            let tabs = state.tabs.get(&g.id)?;
            let dockwidgets: Vec<DockWidgetData> = tabs
                .dockwidgets
                .iter()
                .map(|(title, color)| DockWidgetData { title: title.into(), color: *color })
                .collect();
            Some(GroupData {
                visible: g.visible,
                x: g.x as f32,
                y: g.y as f32,
                width: g.width as f32,
                height: g.height as f32,
                dockwidgets: ModelRc::new(VecModel::from(dockwidgets)),
                current_index: tabs.current_index,
            })
        })
        .collect::<Vec<_>>();

    let separators = state
        .sorted_separators()
        .into_iter()
        .map(|s| SeparatorData {
            x: s.x as f32,
            y: s.y as f32,
            width: s.width as f32,
            height: s.height as f32,
            is_vertical: s.is_vertical,
        })
        .collect::<Vec<_>>();

    ui.set_groups(ModelRc::new(VecModel::from(groups)));
    ui.set_separators(ModelRc::new(VecModel::from(separators)));
}

fn main() {
    let ui = AppWindow::new().expect("failed to create AppWindow");

    let mut state = AppState { layout: DockingLayout::new(), tabs: HashMap::new(), next_id: 1 };

    // Not all side by side: Output and Editor/Console sit left/right of each
    // other, but Files/Search/Git is nested below Editor/Console rather than
    // being a third column. That nesting is why root ends up as a
    // horizontal container with two children — [Output] and a vertical box
    // holding [Editor/Console, Files/Search/Git] — instead of one flat row.
    state.add_group(vec![("Output".into(), Color::from_rgb_u8(0x81, 0x8f, 0xb4))], Location::OnLeft);
    let editor_id = state.add_group(
        vec![
            ("Editor".into(), Color::from_rgb_u8(0x43, 0x55, 0x85)),
            ("Console".into(), Color::from_rgb_u8(0x2f, 0x3b, 0x5c)),
        ],
        Location::OnRight,
    );
    state.add_group_relative_to(
        vec![
            ("Files".into(), Color::from_rgb_u8(0xf5, 0xe8, 0xc7)),
            ("Search".into(), Color::from_rgb_u8(0xd8, 0xc9, 0x9a)),
            ("Git".into(), Color::from_rgb_u8(0xb8, 0xa8, 0x77)),
        ],
        Location::OnBottom,
        editor_id,
    );

    // Matches AppWindow's preferred-width/height in ui/app.slint. The
    // `resized` callback below takes over once the window is actually shown
    // and the real size is known.
    state.layout.resize(900, 600);

    refresh(&ui, &state);

    let state = Rc::new(RefCell::new(state));

    ui.on_resized({
        let ui_weak = ui.as_weak();
        let state = state.clone();
        move |width, height| {
            let mut state = state.borrow_mut();
            state.layout.resize(width as i32, height as i32);
            if let Some(ui) = ui_weak.upgrade() {
                refresh(&ui, &state);
            }
        }
    });

    ui.on_close_requested({
        let ui_weak = ui.as_weak();
        let state = state.clone();
        move |group_index, dockwidget_index| {
            let mut state = state.borrow_mut();
            let Some(group) = state.sorted_groups().get(group_index as usize).copied() else {
                return;
            };
            let id = group.id;
            let Some(group_tabs) = state.tabs.get_mut(&id) else { return };

            let dockwidget_index = dockwidget_index as usize;
            if dockwidget_index < group_tabs.dockwidgets.len() {
                group_tabs.dockwidgets.remove(dockwidget_index);
            }

            if group_tabs.dockwidgets.is_empty() {
                state.tabs.remove(&id);
                state.layout.remove_group(id);
            } else {
                let group_tabs = state.tabs.get_mut(&id).unwrap();
                group_tabs.current_index =
                    group_tabs.current_index.min(group_tabs.dockwidgets.len() as i32 - 1);
            }

            if let Some(ui) = ui_weak.upgrade() {
                refresh(&ui, &state);
            }
        }
    });

    ui.on_current_changed({
        let ui_weak = ui.as_weak();
        let state = state.clone();
        move |group_index, dockwidget_index| {
            let mut state = state.borrow_mut();
            let Some(group) = state.sorted_groups().get(group_index as usize).copied() else {
                return;
            };
            if let Some(group_tabs) = state.tabs.get_mut(&group.id) {
                group_tabs.current_index = dockwidget_index;
            }
            if let Some(ui) = ui_weak.upgrade() {
                refresh(&ui, &state);
            }
        }
    });

    ui.run().expect("failed to run AppWindow");
}

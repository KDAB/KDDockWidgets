// This file is part of KDDockWidgets.
//
// SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
//
// SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
//
// Contact KDAB at <info@kdab.com> for commercial licensing options.

slint::include_modules!();

use kddockwidgets::{DockManager, Location};
use slint::{ComponentHandle, Model, ModelRc, VecModel};
use std::cell::RefCell;
use std::rc::Rc;

/// Backing storage for `Docking.groups`/`.separators`, kept alive for the
/// whole run and mutated in place. This matters: a `for` loop's `Repeater`
/// compares the *identity* of the `ModelRc` it's bound to on every access,
/// and replaces its whole set of row elements (destroying and recreating
/// them) whenever that identity changes -- even if the new model has the
/// exact same content. Handing it a fresh `ModelRc::new(VecModel::from(...))`
/// on every refresh, as this used to do, tore down every Group/Separator on
/// every single callback; mid-drag, that included the Separator whose
/// TouchArea was actively capturing the mouse, silently ending the drag
/// before the first `moved` event. `sync_by_id` below updates existing rows
/// in place (`set_row_data`) instead, which only rebinds that row's
/// properties and leaves its element alone.
#[derive(Clone)]
struct UiModels {
    groups: Rc<VecModel<GroupData>>,
    separators: Rc<VecModel<SeparatorData>>,
}

/// Reconciles `model`'s rows with `desired`, matched by `id_of`: existing
/// ids are updated in place, new ones appended, stale ones dropped. Order
/// isn't preserved -- nothing here depends on Group/Separator draw order --
/// only identity, which is what keeps a row's element (and any interactive
/// state, like a Separator being dragged) alive across refreshes.
fn sync_by_id<T: Clone + 'static>(model: &VecModel<T>, desired: Vec<T>, id_of: impl Fn(&T) -> i32) {
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

/// Pushes the manager's current state into the `Docking` global.
fn refresh(ui: &AppWindow, manager: &DockManager, models: &UiModels) {
    let groups = manager
        .groups()
        .into_iter()
        .map(|g| {
            let dockwidgets: Vec<DockWidgetData> = g
                .dock_widgets
                .into_iter()
                .map(|(name, title)| DockWidgetData { unique_name: name.into(), title: title.into() })
                .collect();
            GroupData {
                id: g.geometry.id,
                visible: g.geometry.visible,
                x: g.geometry.x as f32,
                y: g.geometry.y as f32,
                width: g.geometry.width as f32,
                height: g.geometry.height as f32,
                dockwidgets: ModelRc::new(VecModel::from(dockwidgets)),
                current_index: g.current_index as i32,
            }
        })
        .collect::<Vec<_>>();

    let separators = manager
        .separators()
        .into_iter()
        .map(|s| SeparatorData {
            id: s.id,
            x: s.x as f32,
            y: s.y as f32,
            width: s.width as f32,
            height: s.height as f32,
            is_vertical: s.is_vertical,
        })
        .collect::<Vec<_>>();

    sync_by_id(&models.groups, groups, |g| g.id);
    sync_by_id(&models.separators, separators, |s| s.id);

    let docking = ui.global::<Docking>();
    docking.set_revision(docking.get_revision() + 1);
}

/// Forwards the `Docking` global's callbacks to `manager`. This is framework
/// glue rather than app code, it only lives here because the Slint-generated
/// types only exist in this crate.
fn connect(ui: &AppWindow, manager: Rc<RefCell<DockManager>>) {
    let docking = ui.global::<Docking>();

    let models = UiModels {
        groups: Rc::new(VecModel::from(Vec::<GroupData>::new())),
        separators: Rc::new(VecModel::from(Vec::<SeparatorData>::new())),
    };
    docking.set_groups(ModelRc::from(models.groups.clone()));
    docking.set_separators(ModelRc::from(models.separators.clone()));

    // Runs `f` on the manager, then refreshes the UI
    let mutate = {
        let ui_weak = ui.as_weak();
        let manager = manager.clone();
        let models = models.clone();
        move |f: &dyn Fn(&mut DockManager)| {
            f(&mut manager.borrow_mut());
            if let Some(ui) = ui_weak.upgrade() {
                refresh(&ui, &manager.borrow(), &models);
            }
        }
    };
    let mutate = Rc::new(mutate);

    docking.on_register({
        let mutate = mutate.clone();
        move |name, title, min_width, min_height| {
            mutate(&|m| m.register(&name, &title, min_width.ceil() as i32, min_height.ceil() as i32))
        }
    });
    docking.on_title_changed({
        let mutate = mutate.clone();
        move |name, title| mutate(&|m| m.set_title(&name, &title))
    });
    docking.on_close_requested({
        let mutate = mutate.clone();
        move |name| mutate(&|m| m.close(&name))
    });
    docking.on_current_changed({
        let mutate = mutate.clone();
        move |name| mutate(&|m| m.set_current(&name))
    });
    docking.on_resized({
        let mutate = mutate.clone();
        move |width, height| mutate(&|m| m.resize(width as i32, height as i32))
    });

    docking.on_separator_pressed({
        let mutate = mutate.clone();
        move |id| mutate(&|m| m.separator_press(id))
    });
    docking.on_separator_released({
        let mutate = mutate.clone();
        move |id| mutate(&|m| m.separator_release(id))
    });
    docking.on_separator_moved({
        let mutate = mutate.clone();
        move |id, dx, dy| mutate(&|m| m.separator_move(id, dx as i32, dy as i32))
    });

    docking.on_dock_state({
        let manager = manager.clone();
        move |name, _revision| {
            let Some(state) = manager.borrow().dock_widget_state(&name) else {
                return DockState::default();
            };
            let g = state.group_geometry;
            DockState {
                is_open: true,
                is_current: state.is_current,
                x: g.x as f32,
                y: g.y as f32,
                width: g.width as f32,
                height: g.height as f32,
            }
        }
    });

    refresh(ui, &manager.borrow(), &models);
    docking.set_ready(true);
}

fn main() {
    let ui = AppWindow::new().expect("failed to create AppWindow");

    let mut manager = DockManager::new();

    // Not all side by side: Output and Editor/Console sit left/right of each
    // other, but Files/Search/Git is nested below Editor/Console rather than
    // being a third column.
    manager.add_dock_widget("output", Location::OnLeft, None);
    manager.add_dock_widget("editor", Location::OnRight, None);
    manager.add_dock_widget_as_tab("console", "editor");
    manager.add_dock_widget("files", Location::OnBottom, Some("editor"));
    manager.add_dock_widget_as_tab("search", "files");
    manager.add_dock_widget_as_tab("git", "files");

    // Matches AppWindow's preferred-width/height in ui/app.slint. The
    // `resized` callback takes over once the window is actually shown and
    // the real size is known.
    manager.resize(900, 600);

    connect(&ui, Rc::new(RefCell::new(manager)));

    ui.run().expect("failed to run AppWindow");
}

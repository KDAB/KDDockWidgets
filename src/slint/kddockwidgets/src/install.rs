// This file is part of KDDockWidgets.
//
// SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
//
// SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
//
// Contact KDAB at <info@kdab.com> for commercial licensing options.

//! The one piece of this crate that has to be a macro.
//!
//! Slint generates its Rust types (the `Docking` global, `GroupData`, ...)
//! in whichever crate runs the Slint compiler, which is the app's, never
//! this one. A macro is how code written here gets to name those types: it
//! is expanded in the app, where they exist.

/// Binds a window's `DropArea` to a fresh [`DockingArea`](crate::DockingArea),
/// and returns it.
///
/// This installs every `Docking` callback, so an app never sees Groups,
/// separators, registration or resizing -- only [`DockingArea`](crate::DockingArea)'s
/// own API:
///
/// ```ignore
/// slint::include_modules!();
///
/// let ui = AppWindow::new()?;
/// let docking = kddockwidgets::install!(&ui);
/// docking.add_dock_widget("editor", kddockwidgets::Location::OnLeft, None);
/// ```
///
/// Two requirements on the app's `.slint` side:
/// - its main file must re-export the global, `export { Docking } from
///   "@kddockwidgets";`, otherwise Slint generates no Rust for it;
/// - the call must sit where `slint::include_modules!()`'s types are in
///   scope, since that is what the expansion refers to.
#[macro_export]
macro_rules! install {
    ($ui:expr) => {{
        let ui = $ui;
        let ui_weak = $crate::slint::ComponentHandle::as_weak(ui);
        let groups = ::std::rc::Rc::new($crate::slint::VecModel::<GroupData>::default());
        let separators = ::std::rc::Rc::new($crate::slint::VecModel::<SeparatorData>::default());
        // One stable tab-list model per Group id, so a Group's own refresh
        // (which set_row_data()'s a fresh GroupData row) doesn't also swap
        // out *its* dockwidgets model -- see sync_rows's doc comment for why
        // that would tear down a tab's TouchArea mid-drag.
        let dockwidget_models: ::std::rc::Rc<
            ::std::cell::RefCell<
                ::std::collections::HashMap<
                    i32,
                    ::std::rc::Rc<$crate::slint::VecModel<DockWidgetData>>,
                >,
            >,
        > = ::std::rc::Rc::new(::std::cell::RefCell::new(::std::collections::HashMap::new()));

        let area = $crate::DockingArea::new(
            {
                let (groups, separators) = (groups.clone(), separators.clone());
                let dockwidget_models = dockwidget_models.clone();
                let ui_weak = ui_weak.clone();
                move |area: &$crate::DockingArea| {
                    let group_views = area.groups();
                    let mut models = dockwidget_models.borrow_mut();
                    let mut live_group_ids = ::std::vec::Vec::with_capacity(group_views.len());
                    let rows: ::std::vec::Vec<GroupData> = group_views
                        .iter()
                        .map(|g| {
                            live_group_ids.push(g.geometry.id);
                            let tabs = models
                                .entry(g.geometry.id)
                                .or_insert_with(|| {
                                    ::std::rc::Rc::new($crate::slint::VecModel::default())
                                })
                                .clone();
                            let desired_tabs: ::std::vec::Vec<DockWidgetData> = g
                                .dock_widgets
                                .iter()
                                .map(|(name, title)| DockWidgetData {
                                    unique_name: name.as_str().into(),
                                    title: title.as_str().into(),
                                })
                                .collect();
                            $crate::sync_rows(&tabs, desired_tabs, |dw: &DockWidgetData| {
                                dw.unique_name.clone()
                            });
                            GroupData {
                                id: g.geometry.id,
                                visible: g.geometry.visible,
                                x: g.geometry.x as f32,
                                y: g.geometry.y as f32,
                                width: g.geometry.width as f32,
                                height: g.geometry.height as f32,
                                current_index: g.current_index as i32,
                                dockwidgets: $crate::slint::ModelRc::from(tabs),
                            }
                        })
                        .collect();
                    models.retain(|id, _| live_group_ids.contains(id));
                    drop(models);
                    $crate::sync_rows(&groups, rows, |g: &GroupData| g.id);

                    let rows = area
                        .separators()
                        .iter()
                        .map(|s| SeparatorData {
                            id: s.id,
                            x: s.x as f32,
                            y: s.y as f32,
                            width: s.width as f32,
                            height: s.height as f32,
                            is_vertical: s.is_vertical,
                        })
                        .collect();
                    $crate::sync_rows(&separators, rows, |s: &SeparatorData| s.id);

                    // Slint doesn't track dependencies through callbacks, so
                    // dock-state() bindings only re-evaluate because of this.
                    if let Some(ui) = $crate::slint::Weak::upgrade(&ui_weak) {
                        let docking = $crate::slint::ComponentHandle::global::<Docking>(&ui);

                        // Indicators are ephemeral (only exist during a drag)
                        // and nothing about them is interactive, so unlike
                        // groups/separators above there's no row identity
                        // worth preserving: a fresh model every refresh is
                        // fine.
                        let indicator_rows: ::std::vec::Vec<IndicatorData> = area
                            .indicators()
                            .into_iter()
                            .map(|i| IndicatorData {
                                x: i.x as f32,
                                y: i.y as f32,
                                image: $crate::indicator_image(i.location, i.active),
                            })
                            .collect();
                        docking.set_indicators($crate::slint::ModelRc::new(
                            $crate::slint::VecModel::from(indicator_rows),
                        ));

                        docking.set_drag(match area.drag_state() {
                            Some(state) => DragData {
                                active: true,
                                ghost_x: state.ghost_x as f32,
                                ghost_y: state.ghost_y as f32,
                                ghost_width: state.ghost_width as f32,
                                ghost_height: state.ghost_height as f32,
                                ghost_image: area.drag_ghost_image().unwrap_or_default(),
                                rubber_band_visible: state.rubber_band.is_some(),
                                rubber_band_x: state.rubber_band.map_or(0.0, |r| r.x as f32),
                                rubber_band_y: state.rubber_band.map_or(0.0, |r| r.y as f32),
                                rubber_band_width: state
                                    .rubber_band
                                    .map_or(0.0, |r| r.width as f32),
                                rubber_band_height: state
                                    .rubber_band
                                    .map_or(0.0, |r| r.height as f32),
                            },
                            None => DragData::default(),
                        });

                        docking.set_revision(docking.get_revision() + 1);
                    }
                }
            },
            {
                let ui_weak = ui_weak.clone();
                // Grabs the whole window plus its scale factor, for cropping
                // out the drag ghost. `take_snapshot()` isn't implemented by
                // every renderer (notably the headless testing backend used
                // by slint_example's GUI tests), so this can fail; a drag
                // still works without a ghost image, see
                // DockingArea::drag_started.
                move || {
                    let ui = $crate::slint::Weak::upgrade(&ui_weak)?;
                    let window = $crate::slint::ComponentHandle::window(&ui);
                    let buffer = window.take_snapshot().ok()?;
                    Some((buffer, window.scale_factor()))
                }
            },
        );

        let docking = $crate::slint::ComponentHandle::global::<Docking>(ui);
        docking.set_groups($crate::slint::ModelRc::from(groups));
        docking.set_separators($crate::slint::ModelRc::from(separators));

        docking.on_register({
            let area = area.clone();
            move |name, title, min_width, min_height| {
                area.register(&name, &title, min_width, min_height)
            }
        });
        docking.on_title_changed({
            let area = area.clone();
            move |name, title| area.set_title(&name, &title)
        });
        docking.on_close_requested({
            let area = area.clone();
            move |name| area.close(&name)
        });
        docking.on_current_changed({
            let area = area.clone();
            move |name| area.set_current(&name)
        });
        docking.on_resized({
            let area = area.clone();
            move |width, height| area.resize(width, height)
        });
        docking.on_separator_pressed({
            let area = area.clone();
            move |id| area.separator_pressed(id)
        });
        docking.on_separator_released({
            let area = area.clone();
            move |id| area.separator_released(id)
        });
        docking.on_separator_moved({
            let area = area.clone();
            move |id, dx, dy| area.separator_moved(id, dx, dy)
        });
        docking.on_drag_started({
            let area = area.clone();
            move |name, whole_group, x, y| area.drag_started(&name, whole_group, x, y)
        });
        docking.on_drag_moved({
            let area = area.clone();
            move |x, y| area.drag_moved(x, y)
        });
        docking.on_drag_ended({
            let area = area.clone();
            move |x, y| area.drag_ended(x, y)
        });
        docking.on_drag_cancelled({
            let area = area.clone();
            move || area.drag_cancelled()
        });
        docking.on_dock_state({
            let area = area.clone();
            move |name, _revision| match area.dock_widget_state(&name) {
                Some(state) => DockState {
                    is_open: true,
                    is_current: state.is_current,
                    x: state.group_geometry.x as f32,
                    y: state.group_geometry.y as f32,
                    width: state.group_geometry.width as f32,
                    height: state.group_geometry.height as f32,
                    tab_count: state.tab_count as i32,
                },
                None => DockState::default(),
            }
        });

        area.refresh();

        // DockWidgets only register themselves once this is set, see
        // ui/dockwidget.slint.
        docking.set_ready(true);

        area
    }};
}

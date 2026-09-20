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

        let area = $crate::DockingArea::new({
            let (groups, separators) = (groups.clone(), separators.clone());
            move |area: &$crate::DockingArea| {
                let rows = area
                    .groups()
                    .iter()
                    .map(|g| GroupData {
                        id: g.geometry.id,
                        visible: g.geometry.visible,
                        x: g.geometry.x as f32,
                        y: g.geometry.y as f32,
                        width: g.geometry.width as f32,
                        height: g.geometry.height as f32,
                        current_index: g.current_index as i32,
                        dockwidgets: $crate::slint::ModelRc::new($crate::slint::VecModel::from(
                            g.dock_widgets
                                .iter()
                                .map(|(name, title)| DockWidgetData {
                                    unique_name: name.as_str().into(),
                                    title: title.as_str().into(),
                                })
                                .collect::<::std::vec::Vec<_>>(),
                        )),
                    })
                    .collect();
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
                    docking.set_revision(docking.get_revision() + 1);
                }
            }
        });

        let docking = $crate::slint::ComponentHandle::global::<Docking>(ui);
        docking.set_groups($crate::slint::ModelRc::from(groups));
        docking.set_separators($crate::slint::ModelRc::from(separators));

        docking.on_register({
            let area = area.clone();
            move |name, title, min_width, min_height| area.register(&name, &title, min_width, min_height)
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

// This file is part of KDDockWidgets.
//
// SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
//
// SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
//
// Contact KDAB at <info@kdab.com> for commercial licensing options.

slint::include_modules!();

use kddockwidgets::Location;

/// Builds the `AppWindow` with the sample layout, but doesn't show it. Split
/// out from [`run()`] so tests can drive the same app without entering the
/// event loop.
pub fn create_app() -> AppWindow {
    let ui = AppWindow::new().expect("failed to create AppWindow");

    // The dock widgets themselves (and their content) are declared in
    // ui/app.slint; this only decides where they go. Dropping the handle
    // afterwards is fine: the window's own callbacks keep it alive.
    let docking = kddockwidgets::install!(&ui);

    // Not all side by side: Output and Editor/Console sit left/right of each
    // other, but Files/Search/Git is nested below Editor/Console rather than
    // being a third column.
    docking.add_dock_widget("output", Location::OnLeft, None);
    docking.add_dock_widget("editor", Location::OnRight, None);
    docking.add_dock_widget_as_tab("console", "editor");
    docking.add_dock_widget("files", Location::OnBottom, Some("editor"));
    docking.add_dock_widget_as_tab("search", "files");
    docking.add_dock_widget_as_tab("git", "files");

    ui
}

pub fn run() {
    create_app().run().expect("failed to run AppWindow");
}

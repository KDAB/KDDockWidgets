// This file is part of KDDockWidgets.
//
// SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
//
// SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
//
// Contact KDAB at <info@kdab.com> for commercial licensing options.

//! In-process GUI tests, run headless via `i-slint-backend-testing` (no
//! display needed, works in CI). They drive the same app the binary shows
//! (`slint_example::create_app()`, see src/lib.rs) and inspect its rendered
//! element tree rather than `DockManager`'s Rust-side state directly, so
//! they also catch breakage in the .slint side of things (e.g. a binding
//! that stops a tab or title from actually being drawn).
//!
//! Element lookups rely on `Text`'s implicit `accessible-label: text;` (see
//! kddockwidgets/ui/titlebar.slint and group.slint), and on a `visible:
//! false` element -- and its descendants -- being excluded from
//! `ElementHandle` queries entirely, which is how "is this dock widget's
//! content currently on screen" gets checked below.

use i_slint_backend_testing::ElementHandle;
use slint::platform::PointerEventButton;
use slint_example::AppWindow;

/// Creates the app and runs one throwaway full-tree query over it.
///
/// The `for`-repeaters behind Group's tab bar (see kddockwidgets/ui/group.slint)
/// aren't materialized by the time `create_app()` returns -- nothing has
/// driven a layout/update pass yet, since tests never call `ui.run()`. The
/// very first `ElementHandle` traversal is what triggers that, but doesn't
/// see the results within that same call; a second traversal (any of them)
/// does. Without this, a test whose *first* lookup targets something that
/// only exists inside a tab bar repeater (e.g. "Console", which unlike
/// "Editor" has no un-repeated title-bar occurrence to fall back on) finds
/// nothing.
fn new_app() -> AppWindow {
    let ui = slint_example::create_app();
    ElementHandle::find_by_element_type_name(&ui, "Group").count();
    ui
}

/// Number of elements (tab labels and/or the Group's title bar) currently
/// showing `label` as their accessible label.
fn label_count(ui: &AppWindow, label: &str) -> usize {
    ElementHandle::find_by_accessible_label(ui, label).count()
}

fn group_count(ui: &AppWindow) -> usize {
    ElementHandle::find_by_element_type_name(ui, "Group").count()
}

fn open_dock_widget_count(ui: &AppWindow) -> usize {
    ElementHandle::find_by_element_type_name(ui, "DockWidget").count()
}

#[test]
fn dock_widgets_and_tabs_are_visible() {
    i_slint_backend_testing::init_no_event_loop();
    let ui = new_app();

    // Three groups: Output alone; Editor+Console tabbed together; Files,
    // Search and Git tabbed together, nested below Editor/Console. See the
    // layout comment in slint_example::create_app().
    assert_eq!(group_count(&ui), 3);
    assert_eq!(ElementHandle::find_by_element_type_name(&ui, "Separator").count(), 2);

    // Every dock widget's title is drawn somewhere: as its tab, and -- if
    // it's the current tab of its group -- in the title bar too.
    for title in ["Output", "Editor", "Console", "Files", "Search", "Git"] {
        assert!(label_count(&ui, title) >= 1, "no visible tab/title for {title}");
    }

    // The first dock widget added to each group starts as its current tab
    // (see Group::current_index in kddockwidgets/src/manager.rs), so only
    // Output, Editor and Files have their content actually on screen.
    assert_eq!(open_dock_widget_count(&ui), 3);
    assert_eq!(label_count(&ui, "Editor"), 2, "current tab: tab bar + title bar");
    assert_eq!(label_count(&ui, "Console"), 1, "not current: tab bar only");
    assert_eq!(label_count(&ui, "Files"), 2, "current tab: tab bar + title bar");
    assert_eq!(label_count(&ui, "Search"), 1, "not current: tab bar only");
}

#[test]
fn clicking_a_tab_switches_the_current_dock_widget() {
    i_slint_backend_testing::init_no_event_loop();
    let ui = new_app();

    let console_tab = ElementHandle::find_by_accessible_label(&ui, "Console")
        .next()
        .expect("Console's tab not found");
    console_tab.mock_single_click(PointerEventButton::Left);

    assert_eq!(label_count(&ui, "Console"), 2, "now current: tab bar + title bar");
    assert_eq!(label_count(&ui, "Editor"), 1, "demoted: tab bar only");
    assert_eq!(open_dock_widget_count(&ui), 3, "still one open widget per group");
}

#[test]
fn closing_a_dock_widget_removes_its_group_once_empty() {
    i_slint_backend_testing::init_no_event_loop();
    let ui = new_app();

    // Output is alone in its Group, so closing it (via its title bar's
    // close button) should remove that Group entirely rather than leaving
    // an empty one -- see DockManager::close in kddockwidgets/src/manager.rs.
    let close_output = ElementHandle::find_by_accessible_label(&ui, "Close Output")
        .next()
        .expect("Output's close button not found");
    close_output.mock_single_click(PointerEventButton::Left);

    assert_eq!(label_count(&ui, "Output"), 0);
    assert_eq!(group_count(&ui), 2);
    assert_eq!(open_dock_widget_count(&ui), 2);
}

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
//! element tree rather than the Rust-side layout state directly, so
//! they also catch breakage in the .slint side of things (e.g. a binding
//! that stops a tab or title from actually being drawn).
//!
//! Element lookups rely on `Text`'s implicit `accessible-label: text;` (see
//! kddockwidgets/ui/titlebar.slint and group.slint), and on a `visible:
//! false` element -- and its descendants -- being excluded from
//! `ElementHandle` queries entirely, which is how "is this dock widget's
//! content currently on screen" gets checked below.

use i_slint_backend_testing::ElementHandle;
use slint::platform::{PointerEventButton, WindowEvent};
use slint::{ComponentHandle, LogicalPosition};
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
    assert_eq!(
        ElementHandle::find_by_element_type_name(&ui, "Separator").count(),
        2
    );

    // Every dock widget's title is drawn somewhere: as its tab (unless
    // it's alone in its Group, see below), and -- if it's the current tab
    // of its group -- in the title bar too.
    for title in ["Output", "Editor", "Console", "Files", "Search", "Git"] {
        assert!(
            label_count(&ui, title) >= 1,
            "no visible tab/title for {title}"
        );
    }

    // The first dock widget added to each group starts as its current tab
    // (see Group::current_index in kddockwidgets/src/manager.rs), so only
    // Output, Editor and Files have their content actually on screen.
    assert_eq!(open_dock_widget_count(&ui), 3);
    assert_eq!(
        label_count(&ui, "Output"),
        1,
        "alone in its Group: tab bar is hidden (see group.slint), title bar only"
    );
    assert_eq!(
        label_count(&ui, "Editor"),
        2,
        "current tab: tab bar + title bar"
    );
    assert_eq!(label_count(&ui, "Console"), 1, "not current: tab bar only");
    assert_eq!(
        label_count(&ui, "Files"),
        2,
        "current tab: tab bar + title bar"
    );
    assert_eq!(label_count(&ui, "Search"), 1, "not current: tab bar only");
}

#[test]
fn groups_cover_the_whole_drop_area() {
    i_slint_backend_testing::init_no_event_loop();
    let ui = new_app();

    // The layouting engine only ever learns how big the area is from DropArea
    // reporting its own size (kddockwidgets/ui/droparea.slint). If that report
    // stops arriving, every Group collapses to 0x0 while still being there --
    // which the other tests, counting elements, would happily pass.
    let (mut right, mut bottom) = (0.0f32, 0.0f32);
    for group in ElementHandle::find_by_element_type_name(&ui, "Group") {
        let (position, size) = (group.absolute_position(), group.size());
        assert!(
            size.width > 0.0 && size.height > 0.0,
            "collapsed group at {position:?}"
        );
        right = right.max(position.x + size.width);
        bottom = bottom.max(position.y + size.height);
    }

    let window = ui.window().size().to_logical(ui.window().scale_factor());
    assert!(
        right >= window.width - 1.0,
        "groups reach {right}, window is {} wide",
        window.width
    );
    assert!(
        bottom >= window.height - 1.0,
        "groups reach {bottom}, window is {} tall",
        window.height
    );
}

#[test]
fn clicking_a_tab_switches_the_current_dock_widget() {
    i_slint_backend_testing::init_no_event_loop();
    let ui = new_app();

    let console_tab = ElementHandle::find_by_accessible_label(&ui, "Console")
        .next()
        .expect("Console's tab not found");
    console_tab.mock_single_click(PointerEventButton::Left);

    assert_eq!(
        label_count(&ui, "Console"),
        2,
        "now current: tab bar + title bar"
    );
    assert_eq!(label_count(&ui, "Editor"), 1, "demoted: tab bar only");
    assert_eq!(
        open_dock_widget_count(&ui),
        3,
        "still one open widget per group"
    );
}

#[test]
fn closing_a_dock_widget_removes_its_group_once_empty() {
    i_slint_backend_testing::init_no_event_loop();
    let ui = new_app();

    // Output is alone in its Group, so closing it (via its title bar's
    // close button) should remove that Group entirely rather than leaving
    // an empty one -- see DockingArea::close in kddockwidgets/src/area.rs.
    let close_output = ElementHandle::find_by_accessible_label(&ui, "Close Output")
        .next()
        .expect("Output's close button not found");
    close_output.mock_single_click(PointerEventButton::Left);

    assert_eq!(label_count(&ui, "Output"), 0);
    assert_eq!(group_count(&ui), 2);
    assert_eq!(open_dock_widget_count(&ui), 2);
}

#[test]
fn the_tab_bar_disappears_once_a_group_is_down_to_one_tab() {
    i_slint_backend_testing::init_no_event_loop();
    let ui = new_app();

    // Editor's Group starts with two tabs (Editor, Console): tab bar
    // shown, so Editor's label is duplicated (tab bar + title bar, it's
    // current). Making Console current, then closing it, leaves Editor
    // alone in its Group -- group.slint should hide the tab bar entirely
    // at that point, the same as Output's Group (see
    // dock_widgets_and_tabs_are_visible above), not just remove Console's
    // own tab from it.
    assert_eq!(
        label_count(&ui, "Editor"),
        2,
        "tab bar + title bar, still two tabs"
    );

    ElementHandle::find_by_accessible_label(&ui, "Console")
        .next()
        .expect("Console's tab not found")
        .mock_single_click(PointerEventButton::Left);
    ElementHandle::find_by_accessible_label(&ui, "Close Console")
        .next()
        .expect("Console's close button not found")
        .mock_single_click(PointerEventButton::Left);

    assert_eq!(label_count(&ui, "Console"), 0);
    assert_eq!(
        label_count(&ui, "Editor"),
        1,
        "tab bar should now be hidden: title bar only, alone in its Group"
    );
    assert_eq!(
        group_count(&ui),
        3,
        "Editor's Group itself should survive, just down to one tab"
    );
}

/// The center of `element`, in window-absolute logical pixels.
fn center_of(element: &ElementHandle) -> LogicalPosition {
    let (position, size) = (element.absolute_position(), element.size());
    LogicalPosition::new(
        position.x + size.width / 2.0,
        position.y + size.height / 2.0,
    )
}

/// The Group whose bounds contain a dock widget currently showing `label`
/// (its tab, or its title bar if it's the current tab) -- i.e. "the Group
/// dock widget `label` is in right now". Groups aren't otherwise
/// identifiable from the outside (see kddockwidgets/src/manager.rs: ids are
/// assigned internally, and the element tree carries no unique-name), so
/// this is how these tests pick one out.
fn group_showing(ui: &AppWindow, label: &str) -> ElementHandle {
    let label_position = ElementHandle::find_by_accessible_label(ui, label)
        .next()
        .unwrap_or_else(|| panic!("no visible tab/title for {label}"))
        .absolute_position();
    ElementHandle::find_by_element_type_name(ui, "Group")
        .find(|group| {
            let (position, size) = (group.absolute_position(), group.size());
            label_position.x >= position.x
                && label_position.x <= position.x + size.width
                && label_position.y >= position.y
                && label_position.y <= position.y + size.height
        })
        .unwrap_or_else(|| panic!("no Group contains {label}'s label"))
}

/// Drives a full press-move-release drag from `start` to `end`, the same
/// sequence `ui/titlebar.slint` and `ui/group.slint`'s tab TouchAreas expect
/// (see their drag-threshold handling). A single move straight to `end` both
/// crosses the 4px drag threshold and puts the drag exactly where the test
/// wants it dropped -- DockManager::update_drag only looks at the pointer's
/// current position, not the path it took to get there.
fn drag(ui: &AppWindow, start: LogicalPosition, end: LogicalPosition) {
    let window = ui.window();
    window.dispatch_event(WindowEvent::PointerPressed {
        position: start,
        button: PointerEventButton::Left,
    });
    window.dispatch_event(WindowEvent::PointerMoved { position: end });
    window.dispatch_event(WindowEvent::PointerReleased {
        position: end,
        button: PointerEventButton::Left,
    });
}

#[test]
fn dragging_a_titlebar_onto_another_groups_center_merges_them_as_tabs() {
    i_slint_backend_testing::init_no_event_loop();
    let ui = new_app();

    // Output is alone in its Group, so either the tab or the title bar
    // works as a drag handle; dropping dead center on Editor's Group hits
    // its Center indicator (see DockManager::visible_locations: it's
    // positioned exactly at the hovered Group's own center).
    let output = ElementHandle::find_by_accessible_label(&ui, "Output")
        .next()
        .expect("Output's label not found");
    let start = center_of(&output);
    let target = center_of(&group_showing(&ui, "Editor"));

    drag(&ui, start, target);

    assert_eq!(
        group_count(&ui),
        2,
        "Output's now-empty Group should have been removed"
    );
    assert!(
        label_count(&ui, "Output") >= 1,
        "Output should still exist, now as a tab of Editor's Group"
    );
    assert_eq!(
        group_showing(&ui, "Output").absolute_position(),
        group_showing(&ui, "Editor").absolute_position(),
        "Output should have joined Editor's Group, not started a new one"
    );
}

#[test]
fn dragging_one_tab_out_of_a_multi_tab_group_moves_just_that_tab() {
    i_slint_backend_testing::init_no_event_loop();
    let ui = new_app();

    // Console is one of two tabs in Editor's Group (see
    // slint_example::create_app), so this drags only Console -- Editor
    // should be left behind in its own Group, unlike the titlebar-drag test
    // above.
    let console = ElementHandle::find_by_accessible_label(&ui, "Console")
        .next()
        .expect("Console's tab not found");
    let start = center_of(&console);
    let target = center_of(&group_showing(&ui, "Files"));

    drag(&ui, start, target);

    assert_eq!(
        group_count(&ui),
        3,
        "moving one tab shouldn't create or remove any Group"
    );
    assert_eq!(
        group_showing(&ui, "Console").absolute_position(),
        group_showing(&ui, "Files").absolute_position(),
        "Console should have moved into Files' Group"
    );
    assert_ne!(
        group_showing(&ui, "Editor").absolute_position(),
        group_showing(&ui, "Console").absolute_position(),
        "Editor should be left behind in its own Group"
    );
}

#[test]
fn starting_a_tab_drag_makes_it_current_even_if_the_drag_is_then_cancelled() {
    i_slint_backend_testing::init_no_event_loop();
    let ui = new_app();

    // Console isn't Editor's current tab (Editor is, see
    // dock_widgets_and_tabs_are_visible above) -- picking it up to drag
    // should make it current regardless of where the drag ends up, both for
    // "you're now holding this one" semantics and because a DockWidget only
    // renders while it's the current tab (see dockwidget.slint), which is
    // what DockingArea::drag_started's ghost snapshot depends on.
    let console = ElementHandle::find_by_accessible_label(&ui, "Console")
        .next()
        .expect("Console's tab not found");
    let start = center_of(&console);
    // Past the 4px drag threshold, but still nowhere near any indicator, so
    // the drag is cancelled on release instead of committed.
    let end = LogicalPosition::new(start.x + 10.0, start.y);

    drag(&ui, start, end);

    assert_eq!(
        group_count(&ui),
        3,
        "a cancelled drag shouldn't touch the layout"
    );
    assert_eq!(
        label_count(&ui, "Console"),
        2,
        "Console should now be current: tab bar + title bar"
    );
    assert_eq!(
        label_count(&ui, "Editor"),
        1,
        "Editor should have been demoted: tab bar only"
    );
}

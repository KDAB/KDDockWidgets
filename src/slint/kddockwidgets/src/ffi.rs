// This file is part of KDDockWidgets.
//
// SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
//
// SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
//
// Contact KDAB at <info@kdab.com> for commercial licensing options.

//! Raw cxx bindings to `cpp/bridge.h`. Nothing here understands Slint; see
//! [`crate::layout`] for the safe, Slint-facing wrapper.

#[cxx::bridge(namespace = "kddw_slint")]
pub mod ffi {

    /// Mirrors `KDDockWidgets::Location`, see `cpp/bridge.h`.
    #[derive(Debug, Clone, Copy, PartialEq, Eq)]
    enum Location {
        OnLeft,
        OnTop,
        OnRight,
        OnBottom,
    }

    /// Geometry of one Group, as computed by the layouting engine.
    #[derive(Debug, Clone, Copy, PartialEq)]
    struct GroupGeometry {
        id: i32,
        visible: bool,
        x: i32,
        y: i32,
        width: i32,
        height: i32,
    }

    /// Geometry of one Separator between Groups.
    #[derive(Debug, Clone, Copy, PartialEq)]
    struct SeparatorGeometry {
        id: i32,
        x: i32,
        y: i32,
        width: i32,
        height: i32,
        is_vertical: bool,
    }

    /// A plain rectangle, used for the drag-and-drop preview (see
    /// `DockingEngine::dropRect`).
    #[derive(Debug, Clone, Copy, PartialEq)]
    struct DropRect {
        x: i32,
        y: i32,
        width: i32,
        height: i32,
    }

    unsafe extern "C++" {
        include!("kddockwidgets/cpp/bridge.h");

        type DockingEngine;

        fn new_docking_engine() -> UniquePtr<DockingEngine>;

        fn resize(self: Pin<&mut DockingEngine>, width: i32, height: i32);
        fn addGroup(
            self: Pin<&mut DockingEngine>,
            id: i32,
            min_width: i32,
            min_height: i32,
            location: Location,
        );
        fn addGroupRelativeTo(
            self: Pin<&mut DockingEngine>,
            id: i32,
            min_width: i32,
            min_height: i32,
            location: Location,
            relative_to_id: i32,
        );
        fn removeGroup(self: Pin<&mut DockingEngine>, id: i32);
        fn setGroupMinSize(self: Pin<&mut DockingEngine>, id: i32, min_width: i32, min_height: i32);

        // Moves an existing Group elsewhere in the layout: same as removing
        // it and calling addGroup/addGroupRelativeTo again with a fresh id,
        // except it keeps the id (and thus what the Rust side has correlated
        // with it) stable. `relative_to_id` of 0 means relative to the whole
        // layout, like addGroup.
        fn moveGroup(
            self: Pin<&mut DockingEngine>,
            id: i32,
            min_width: i32,
            min_height: i32,
            location: Location,
            relative_to_id: i32,
        );

        // The rect a Group with `dragged_id`'s current size would land in if
        // dropped at `location` relative to `relative_to_id` (0 for the whole
        // layout), without actually moving anything. Drives the drop-preview
        // rubber band. Returns a zeroed rect if either id isn't found.
        fn dropRect(
            self: &DockingEngine,
            dragged_id: i32,
            location: Location,
            relative_to_id: i32,
        ) -> DropRect;

        fn separatorMousePress(self: Pin<&mut DockingEngine>, id: i32);
        fn separatorMouseRelease(self: Pin<&mut DockingEngine>, id: i32);
        fn separatorMouseMove(self: Pin<&mut DockingEngine>, id: i32, dx: i32, dy: i32);

        fn groups(self: &DockingEngine) -> Vec<GroupGeometry>;
        fn separators(self: &DockingEngine) -> Vec<SeparatorGeometry>;
    }
}

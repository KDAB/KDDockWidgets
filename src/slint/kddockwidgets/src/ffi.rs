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

    unsafe extern "C++" {
        include!("kddockwidgets/cpp/bridge.h");

        type DockingEngine;

        fn new_docking_engine() -> UniquePtr<DockingEngine>;

        fn resize(self: Pin<&mut DockingEngine>, width: i32, height: i32);
        fn addGroup(self: Pin<&mut DockingEngine>, id: i32, min_width: i32, min_height: i32, location: Location);
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

        fn groups(self: &DockingEngine) -> Vec<GroupGeometry>;
        fn separators(self: &DockingEngine) -> Vec<SeparatorGeometry>;
    }
}

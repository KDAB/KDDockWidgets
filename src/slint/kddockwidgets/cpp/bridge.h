// This file is part of KDDockWidgets.
//
// SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
//
// SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
//
// Contact KDAB at <info@kdab.com> for commercial licensing options.

// Thin C++ wrapper around KDDockWidgets' standalone layouting engine
// (KDDockWidgets::Core::Item / ItemBoxContainer), exposed to Rust through cxx.
//
// There is no GUI on the C++ side: this class only tracks geometry. The Slint
// side is a "dumb" renderer that displays whatever geometry the engine
// computes; see ui/droparea.slint.

#pragma once

#include "rust/cxx.h"

#include <cstdint>
#include <memory>

namespace kddw_slint {

// GroupGeometry, SeparatorGeometry and Location are "shared" types: they are
// defined once, in src/ffi.rs, and cxx generates their real C++ definition
// into a header of its own (target/.../cxxbridge/include/kddockwidgets/src/ffi.rs.h).
// This file only forward-declares them, which is enough to declare
// DockingEngine's methods below. bridge.cpp includes the generated header
// for the full definitions before implementing those methods.
//
// (We can't just #include the generated header here: cxx makes it #include
// this file first, so the reverse #include would only see an empty, still-
// being-processed version of it. Forward declarations avoid that entirely.)
struct GroupGeometry;
struct SeparatorGeometry;
struct DropRect;
enum class Location : std::uint8_t;

// Owns one KDDockWidgets layouting tree. There is one DockingEngine per
// top-level DropArea (only one, for now, since this app isn't multi-window
// yet).
class DockingEngine
{
public:
    DockingEngine();
    ~DockingEngine();

    // Resizes the whole layout. Called whenever the DropArea is resized.
    void resize(std::int32_t width, std::int32_t height);

    // Adds a new Group with the given minimum content size and the given id,
    // chosen by the caller. Ids must be unique and non-zero. `location` is
    // relative to the whole layout.
    void addGroup(std::int32_t id, std::int32_t minWidth, std::int32_t minHeight, Location location);

    // Like addGroup, but `location` is relative to an existing Group
    // (`relativeToId`) instead of the whole layout. This is what produces
    // actual nesting: e.g. adding a Group OnBottom relative to one that's
    // itself side by side with others only splits that one Group's own
    // space, rather than the whole layout. No-op (falls back to addGroup)
    // if `relativeToId` isn't a known Group.
    void addGroupRelativeTo(std::int32_t id, std::int32_t minWidth, std::int32_t minHeight, Location location,
                            std::int32_t relativeToId);

    // Removes the Group with the given id. No-op if not found.
    void removeGroup(std::int32_t id);

    // Changes the minimum size of an existing Group. No-op if not found.
    void setGroupMinSize(std::int32_t id, std::int32_t minWidth, std::int32_t minHeight);

    // Moves an existing Group elsewhere in the layout: removes it and
    // re-inserts a Group with the same id at `location`, relative to
    // `relativeToId` (0 for the whole layout) if given and known, otherwise
    // to the whole layout. No-op if `id` isn't found. `id == relativeToId`
    // is also a no-op (moving a Group relative to itself is meaningless).
    //
    // Implemented as remove-then-insert -- the same two steps an app would
    // take by calling removeGroup() then addGroup()/addGroupRelativeTo()
    // itself -- but done as one call, so callers (and tests) never observe
    // the layout with the Group briefly missing.
    void moveGroup(std::int32_t id, std::int32_t minWidth, std::int32_t minHeight, Location location,
                   std::int32_t relativeToId);

    // The rect a Group with `draggedId`'s current size would land in if
    // dropped at `location` relative to `relativeToId` (0 for the whole
    // layout), without moving anything. Drives the drag-and-drop preview
    // rubber band. Returns a zeroed rect if either id isn't found.
    DropRect dropRect(std::int32_t draggedId, Location location, std::int32_t relativeToId) const;

    // Interactive dragging of the Separator with the given id (as reported
    // by SeparatorGeometry::id). No-op if not found.
    //
    // `separatorMouseMove`'s dx/dy are deltas from the separator's last
    // reported position, not absolute coordinates: see the comment on
    // Separator's TouchArea in ui/separator.slint for why a `moved` event's
    // mouse position doubles as such a delta.
    void separatorMousePress(std::int32_t id);
    void separatorMouseRelease(std::int32_t id);
    void separatorMouseMove(std::int32_t id, std::int32_t dx, std::int32_t dy);

    rust::Vec<GroupGeometry> groups() const;
    rust::Vec<SeparatorGeometry> separators() const;

private:
    struct Impl;
    std::unique_ptr<Impl> d;
};

std::unique_ptr<DockingEngine> new_docking_engine();

}

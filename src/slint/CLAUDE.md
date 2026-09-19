# src/slint

A standalone Rust/Slint prototype of a KDDockWidgets frontend. Not wired into
the top-level CMake build; built and tested independently via `cargo`, from
this directory:

```
cargo build
cargo run -p slint_example
```

## Layout

- `kddockwidgets/` — the framework crate. Ships Slint components
  (`ui/*.slint`) plus a Rust wrapper (`DockingLayout`, in `src/lib.rs`) around
  KDDockWidgets' own C++ layouting engine.
- `slint_example/` — a sample app: owns tab/title/color data and wires it to
  the framework's `DropArea`.

## Why this reaches outside `src/slint`

`kddockwidgets/build.rs` is the one place that goes outside this directory: it
points straight at the repo's top-level `CMakeLists.txt` (via the `cmake`
crate) with `KDDockWidgets_FRONTENDS=none`, the same Qt-free "none" frontend
used by `src/core/layouting/examples/slint`. That gives us
`Core::Item`/`ItemBoxContainer` — the actual layouting engine — without
pulling in Qt. Everything else in this directory is self-contained.

Also passed: `KDDockWidgets_STATIC=ON`, `..._EXAMPLES/TESTS/DOCS=OFF`, and
`..._NO_SPDLOG=ON`. The last one matters: we don't run `cmake --install` (this
configuration has no supported install step), so we link the static lib
straight out of the build tree — which means we'd otherwise have to
hand-reconstruct spdlog/fmt's link flags ourselves instead of getting them
transitively. Skipping spdlog avoids that entirely.

## The C++ bridge (`kddockwidgets/cpp/bridge.{h,cpp}`, `src/ffi.rs`)

Thin wrapper: owns one `ItemBoxContainer`, tracks Group/Separator geometry,
nothing else (no tabs, no titles, no widget content — that's all on the Rust
side, correlated by an `id` the Rust caller chooses).

Two things worth knowing if you touch this code:

- **`bridge.h` only forward-declares the shared types** (`GroupGeometry`,
  `SeparatorGeometry`, `Location`); `bridge.cpp` includes the cxx-generated
  header for the full definitions. This isn't optional style — cxx makes the
  generated header `#include` `bridge.h` *before* defining those types, so if
  `bridge.h` tried to include the generated header back, it'd see an empty,
  still-being-processed version of it. Forward declarations sidestep the
  cycle. See the comment in `bridge.h` for the details.
- **The separator factory must be installed before constructing
  `ItemBoxContainer`**, not after — its constructor asserts one is already
  registered. `DockingEngine`'s constructor does this with a function-local
  static lambda specifically to get the ordering right; getting this backwards
  is a real bug we hit once (`std::abort()` inside
  `ItemBoxContainer::Private::Private`, immediately on startup).
- `groups()`/`separators()` come back in **unspecified order** (they're built
  by iterating a `std::unordered_map`). The Rust side always re-sorts by
  `(y, x, id)` before building anything the UI reads or before mapping a UI
  callback's index back to an id — see `sorted_groups`/`sorted_separators` in
  `slint_example/src/main.rs`. Don't zip the raw output against another list by
  position.

## Slint side

- Slint's built-in `TabWidget` explicitly rejects `for`/`if` children
  ("dynamic tabs are currently not supported"), so `Group` has its own
  hand-rolled tab bar instead, built with `for`.
- `DropArea` does no layout math itself — it just places whatever
  `GroupData`/`SeparatorData` it's given at their given x/y/width/height. All
  positioning comes from the C++ engine.
- The layout isn't a single flat row: `DockingLayout::add_group_relative_to`
  nests a Group under an existing one (splitting just that Group's own
  space) rather than the whole layout, via KDDockWidgets'
  `insertItemRelativeTo`. `slint_example/src/main.rs` uses this for its
  Files/Search/Git group, nested below Editor/Console rather than being a
  third column.
- `slint_example/build.rs` maps the `@kddockwidgets` library import to
  `kddockwidgets/ui/lib.slint`. Since only the `slint_example` crate ever runs
  the Slint compiler, structs declared in the framework's `.slint` files (e.g.
  `GroupData`) get their Rust bindings generated directly in `slint_example`
  — no need to share Slint-generated Rust types across crates (which would
  need Slint's experimental `experimental-module-builds` feature).

## Known gaps (intentional, for now)

- `DockWidget` content is just a colored rectangle — no way to embed real
  user content yet. This is the next open design question.
- No separator dragging, no drag-and-drop.
- Not multi-window.

## CI

`.github/workflows/slint.yml` builds/tests this workspace, **Linux only**.
Windows/macOS haven't been verified — the cxx + cmake-crate combination here
hasn't been tried on either, and is exactly the kind of thing that tends to
need real testing rather than just extending the matrix and hoping.

## Pre-commit hooks apply here too

This code goes through the repo's usual `clang-format`/`codespell`/REUSE
pre-commit hooks. One gotcha already hit: codespell's dictionary flags the
bare identifier `OnTop` (e.g. `Location::OnTop`, in both `bridge.cpp` and
`ffi.rs`) as a typo for "on top" and **silently rewrites it** rather than just
warning — breaking the build. `ontop` is now in `.codespellrc`'s
`ignore-words-list` for this reason. If a commit fails and you see files
modified afterwards, check `git diff` before re-committing; don't assume the
hook's rewrite was correct.

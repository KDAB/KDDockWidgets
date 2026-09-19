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
  (`ui/*.slint`), a Rust wrapper (`DockingLayout`, in `src/lib.rs`) around
  KDDockWidgets' own C++ layouting engine, and `DockManager`
  (`src/manager.rs`) on top of it, which maps dock widgets by `unique-name`
  to Groups/tabs.
- `slint_example/` — a sample app: declares its DockWidgets (with the Slint
  logo as content) in `ui/app.slint`, places them from Rust by name.

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
  by iterating a `std::unordered_map`). `DockManager` re-sorts by `(y, x, id)`
  before handing them out, so the UI's models are stable. UI callbacks carry
  a dock widget's `unique-name`, never an index, so nothing maps indexes back.
- Separator dragging (`separatorMousePress`/`Release`/`Move`) reuses
  `Core::LayoutingSeparator`'s own press/release/move API, the same one the
  Qt frontends use — the bridge doesn't reimplement any drag math. The one
  wrinkle is that `onMouseMove`'s `Point` is an absolute target position, not
  a delta, but Slint only hands us a delta (see the next section); the
  bridge reconstructs an absolute position as `sep->position() + delta`,
  which only works if `sep->position()` reflects the last move *before* the
  next delta arrives — true here because `separatorMouseMove` calls
  `LayoutingSeparator::setGeometry` synchronously, and `DockManager`
  refreshes `Docking.separators` before returning to the event loop.

## How user content works (DockWidget)

Slint can't reparent elements, so unlike the QtQuick frontend a
`DockWidget`'s content never moves into its Group. The app declares
DockWidgets (with arbitrary content as children) directly inside `DropArea`,
where they stay; each one positions itself over the content area of whatever
Group it's in. Group only draws chrome (title bar + tab bar).

- Everything goes through the `Docking` global (`ui/docking.slint`). The app
  must re-export it from its main `.slint` file, and forward its callbacks to
  `DockManager` — see `connect()` in `slint_example/src/main.rs`. That glue
  can't live in the framework crate, because the Slint-generated types only
  exist in the crate running the Slint compiler.
- A DockWidget reads its geometry through `pure callback dock-state(name,
  revision)`. `revision` is a dummy arg that Rust bumps after every change:
  Slint doesn't track dependencies through callbacks, so without it the
  bindings would never re-evaluate.
- DockWidgets **register** (title + min size from their content's layout)
  from an `if Docking.ready: ... init =>` child, not a plain `init`: `init` of
  statically declared elements runs inside `AppWindow::new()`, before Rust can
  install handlers, and would be silently lost. This means registration
  happens *after* Rust's initial `add_dock_widget` calls, which is why
  `DockManager` accepts both in either order and updates the Group's min size
  in the C++ engine afterwards (`setGroupMinSize`).
- Placement is decided from Rust by name (`add_dock_widget`,
  `add_dock_widget_as_tab`). A DockWidget that was never added, or was closed
  (X button → `DockManager::close`, which removes its Group from the C++
  layout once empty), has `is-open: false` and is hidden, but stays alive.
- Slint has no "destroyed" callback, so a DockWidget removed from a `for`
  model isn't unregistered automatically; the app would need to call
  `DockManager::close` itself.
- `GroupMetrics` (in `types.slint`) holds the chrome sizes shared by Group
  (which draws them) and DockWidget (which offsets its content by them).

## Slint side

- Slint's built-in `TabWidget` explicitly rejects `for`/`if` children
  ("dynamic tabs are currently not supported"), so `Group` has its own
  hand-rolled tab bar instead, built with `for`.
- `DropArea` does no layout math itself — it just places whatever
  `GroupData`/`SeparatorData` Rust put in `Docking.groups`/`.separators` at
  their given x/y/width/height. All positioning comes from the C++ engine.
- The layout isn't a single flat row: `add_dock_widget(name, loc,
  Some(other))` nests a Group under an existing one (splitting just that
  Group's own space) rather than the whole layout, via KDDockWidgets'
  `insertItemRelativeTo`. `slint_example/src/main.rs` uses this for its
  Files/Search/Git group, nested below Editor/Console rather than being a
  third column.
- `Separator` (`ui/separator.slint`) drags itself via a trick borrowed from
  the old `src/core/layouting/examples/slint` prototype: it never moves
  itself, so a `TouchArea`'s `moved` event fires with `mouse-x`/`mouse-y`
  relative to the separator's *last-set* `x`/`y` — which, as long as Rust
  updates those from `Docking.separators` before the next mouse-move event
  arrives, doubles as the delta since the last move. `DropArea` forwards
  `pressed`/`released`/`moved` straight to `Docking`, which `main.rs` forwards
  to `DockManager::separator_press/release/move`.
- `slint_example/build.rs` maps the `@kddockwidgets` library import to
  `kddockwidgets/ui/lib.slint`. Since only the `slint_example` crate ever runs
  the Slint compiler, structs declared in the framework's `.slint` files (e.g.
  `GroupData`) get their Rust bindings generated directly in `slint_example`
  — no need to share Slint-generated Rust types across crates (which would
  need Slint's experimental `experimental-module-builds` feature).

## Known gaps (intentional, for now)

- No drag-and-drop (dropping a DockWidget onto another to redock it).
  Separator dragging (resizing) does work.
- No way to reopen a closed DockWidget from the UI (Rust can, via
  `add_dock_widget`).
- Not multi-window. With the no-reparenting design above, content can't
  move between windows either; floating windows will need a different idea.

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

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
  (`ui/*.slint`) and, in layers:
  - `DockingLayout` (`src/lib.rs`), a Rust wrapper around KDDockWidgets' own
    C++ layouting engine, keyed by integer Group ids;
  - `DockManager` (`src/manager.rs`), crate-internal, which maps dock widgets
    by `unique-name` to Groups/tabs on top of it;
  - `DockingArea` (`src/area.rs`) — **the app-facing API**, a cheap-to-clone
    handle bound to one Slint `DropArea` — and `install!` (`src/install.rs`),
    which creates one and wires up every `Docking` callback.
- `slint_example/` — a sample app: declares its DockWidgets (with the Slint
  logo as content) in `ui/app.slint`, places them from Rust by name.

The whole Rust side of an app is:

```rust
slint::include_modules!();

let ui = AppWindow::new()?;
let docking = kddockwidgets::install!(&ui);
docking.add_dock_widget("editor", Location::OnLeft, None);
docking.add_dock_widget_as_tab("console", "editor");
```

Groups, separators, tab bars, registration and resizing never show up in app
code; `DockingArea` only talks about dock widgets, by name.

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
  `LayoutingSeparator::setGeometry` synchronously, and `DockingArea`
  refreshes `Docking.separators` before returning to the event loop.

## How user content works (DockWidget)

Slint can't reparent elements, so unlike the QtQuick frontend a
`DockWidget`'s content never moves into its Group. The app declares
DockWidgets (with arbitrary content as children) directly inside `DropArea`,
where they stay; each one positions itself over the content area of whatever
Group it's in. Group only draws chrome (title bar + tab bar).

- Everything goes through the `Docking` global (`ui/docking.slint`), but no
  app ever touches it: `kddockwidgets::install!(&ui)` fills in every callback
  and hands back a `DockingArea`. The one thing an app must still do itself is
  re-export the global from its main `.slint` file (`export { Docking } from
  "@kddockwidgets";`), since Slint only generates Rust for globals exported
  from the file it compiles.
- `install!` is a macro because it has to be: Slint generates its Rust types
  (the `Docking` global, `GroupData`, ...) in whichever crate runs the Slint
  compiler, i.e. the app's, so framework code can only name them by being
  expanded there. Everything that *doesn't* need those types (`sync_rows`, the
  geometry bookkeeping, all the callback bodies) stays in ordinary Rust in
  `src/area.rs`, so the macro body is just type plumbing. It therefore has to
  be invoked where `slint::include_modules!()`'s types are in scope.
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
- `DropArea` uses the same `if Docking.ready` trick to report its initial
  size, so apps don't have to tell the layout how big it is; `changed
  width`/`height` take over from there. `DockingArea::resize` ignores
  zero-sized reports, which is what a `DropArea` says before the window has
  been laid out once.
- Placement is decided from Rust by name (`add_dock_widget`,
  `add_dock_widget_as_tab`). A DockWidget that was never added, or was closed
  (X button → `DockingArea::close`, which removes its Group from the C++
  layout once empty), has `is-open: false` and is hidden, but stays alive.
- Slint has no "destroyed" callback, so a DockWidget removed from a `for`
  model isn't unregistered automatically; the app would need to call
  `DockingArea::close` itself.
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
  `insertItemRelativeTo`. `slint_example/src/lib.rs` uses this for its
  Files/Search/Git group, nested below Editor/Console rather than being a
  third column.
- `Separator` (`ui/separator.slint`) drags itself via a trick borrowed from
  the old `src/core/layouting/examples/slint` prototype: it never moves
  itself, so a `TouchArea`'s `moved` event fires with `mouse-x`/`mouse-y`
  relative to the separator's *last-set* `x`/`y` — which, as long as Rust
  updates those from `Docking.separators` before the next mouse-move event
  arrives, doubles as the delta since the last move. `DropArea` forwards
  `pressed`/`released`/`moved` straight to `Docking`, which `install!` forwards
  to `DockingArea::separator_pressed/released/moved`.
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

## GUI tests (`slint_example/tests/gui.rs`)

In-process tests using `i-slint-backend-testing` (pinned with `=`, matching
`slint`'s exact resolved version in `Cargo.lock`), run headless by
`cargo test` — no display needed, so they run in CI as-is. They drive
`slint_example::create_app()` (`slint_example/src/lib.rs`; `main.rs` is now
just a one-line call into it, so tests can reach the same app the binary
runs) and inspect the rendered element tree via `ElementHandle`, rather than
asserting on the Rust-side layout state directly — that way they also
catch a `.slint`-side binding that stops something from actually being
drawn, not just a Rust-side logic bug.

- `slint_example/build.rs` passes `.with_debug_info(true)` to
  `CompilerConfiguration`, which the `ElementHandle` API requires (element
  type names, ids, and descendant traversal are silently unavailable
  without it — see `MISSING_DEBUG_INFO_MESSAGE` in the `i-slint-backend-testing`
  source if this ever regresses).
- Lookups mostly go through `ElementHandle::find_by_accessible_label`, not
  `find_by_element_id`: `Text` elements get an implicit
  `accessible-label: text` (mirroring their own `text` property) for free,
  so a dock widget's title is findable with no `.slint` changes. The one
  addition made for testability, `titlebar.slint`'s close button, needed an
  explicit `accessible-role: button` before `accessible-label` was legal to
  set at all (the compiler rejects `accessible-label` without a role).
- An element with `visible: false` — and everything nested inside it — is
  invisible to every `ElementHandle` query, not just to rendering. This is
  exactly the mechanism the tests lean on to check "is this dock widget's
  content actually the one on screen", since `DockWidget`'s own `visible`
  binding gates on `is-current` (see `dockwidget.slint`).
- **Call `create_app()` and then throw away one full-tree `ElementHandle`
  query before asserting anything.** The tab-bar `for` repeater inside
  `Group` (`group.slint`) isn't materialized yet when `create_app()`
  returns — nothing has driven a layout/update pass, since tests never call
  `ui.run()`. The first traversal after creation is what triggers that, but
  doesn't see the new rows within that same call; a second traversal does.
  Skipping this warm-up is invisible for titles that also appear
  unrepeated in a Group's title bar (e.g. "Editor", current by default),
  and only bites for a title that exists *only* inside the tab bar (e.g.
  "Console", not current) — that lookup silently returns nothing. `new_app()`
  in `tests/gui.rs` does this once so every test gets it for free.

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

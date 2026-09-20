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
- `moveGroup` (repositioning a Group for drag-and-drop, see below) is
  implemented as erase-then-`addGroup`/`addGroupRelativeTo` under the same
  id, in one call — the same two steps `DockManager` already takes to open a
  new one, just without exposing the moment in between where the Group is
  briefly gone. `dropRect` mirrors `Core::DropArea::rectForDrop`: a
  throwaway stack `Core::Item`, sized like the Group actually being dragged,
  fed to `ItemBoxContainer::suggestedDropRect` — the same call the Qt
  frontends' own rubber band uses.

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
- A Group with only one tab hides its tab bar entirely (`group.slint`,
  `data.dockwidgets.length > 1`) -- nothing to switch between. DockWidget
  can't just keep using `GroupMetrics.header-height` for its own content
  offset then: it computes a local `header-height` from `DockState.tab-count`
  instead (set in `DockManager::dock_widget_state`), leaving out the tab bar's
  share whenever there's only one. Registration's own min-size report
  (`Docking.register`, on `if Docking.ready: ... init =>`) is the one place
  that still uses the constant, unconditionally: at that point the dock
  widget doesn't know its eventual Group's tab count yet, and reporting the
  larger (tab-bar-included) size is a safe overestimate either way -- it
  just means a lone dock widget's Group ends up very slightly roomier than
  strictly necessary, never too cramped.

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

## Drag-and-drop

Dragging a Group's titlebar, or one of its tabs, to redock it elsewhere. Like
separator dragging, this is computed in Rust (`DockManager` in
`src/manager.rs`) and only rendered by Slint (`ui/dropindicators.slint`).

- **No detaching, by design** (see "Not multi-window" below): the dragged
  Group never leaves the layout mid-drag, and there's no floating preview
  window. Instead `DockManager::drag_started`/`_moved`/`_ended`/`_cancelled`
  track an in-progress drag purely as state (which Group/dock widget, the
  pointer's current position, which indicator -- if any -- it's over), and
  the actual move only happens once, in `DockManager::apply_drop`, when the
  drag ends over a valid indicator. Releasing over empty space is a no-op
  cancel, not an error case.
- **Indicator geometry and hit-testing are computed in Rust**
  (`DockManager::visible_locations`/`update_drag`), the same way Group and
  Separator geometry are -- `ui/dropindicators.slint` just draws whatever
  `Docking.indicators`/`.drag` say, with no `TouchArea` of its own. This
  isn't just consistency with the rest of the crate: it's forced. The
  `TouchArea` that started the drag holds the pointer grab for its whole
  duration (see below), so an indicator's own `TouchArea` would never
  receive events even if one existed.
- **Simplification vs. the QtQuick frontend's indicator rules**
  (`Core::DropIndicatorOverlay::dropIndicatorVisible`): inner indicators and
  Center are hidden entirely while hovering the dragged Group's *own* Group,
  rather than being shown and rejected case by case. Every such drop would
  either be a no-op (dropping a Group back where it came from) or worse (try
  to nest a Group's Item inside itself), so there's nothing a real drop there
  could mean under this prototype's simplified rules. Outer indicators follow
  upstream's own rule as-is: hidden only while hovering the sole Group in the
  whole layout.
- **The drop matrix** (`DockManager::apply_drop`/`drop_at`/`drop_center`): a
  titlebar drag always moves the *whole* Group (kept under its same id, via
  `DockingEngine::moveGroup` -- destroy-then-recreate the C++ `Guest`, see
  the bridge section below). A tab drag out of a Group with only that one tab
  behaves identically (detaching it would just leave an empty Group behind
  to immediately remove). Otherwise, a tab drag detaches just that one dock
  widget into a brand-new Group (inner/outer indicators) or merges it into
  the target's tab bar (Center) -- the source Group keeps its remaining tabs
  and its id.
- **No cursor pixmap.** Slint's `mouse-cursor` only takes a handful of
  built-in shapes (see `i-slint-common::BuiltInMouseCursor`), nothing custom
  -- and since nothing detaches, there's no floating window to give a real
  drag pixmap anyway. The substitute (`DockingArea::drag_started`, drawn by
  `dropindicators.slint`'s ghost `Image`) is a snapshot taken via
  `slint::Window::take_snapshot()` and redrawn following the pointer at 55%
  opacity, inside the DropArea. This silently produces no ghost (the drag
  still works) wherever `take_snapshot()` isn't implemented -- notably the
  headless testing backend the GUI tests run under
  (`i-slint-backend-testing`'s `TestingWindow` has no override for it, so it
  hits `Renderer::take_snapshot`'s default `Err`).
  - The snapshot is cropped differently depending on what's being dragged
    (`DockManager::ghost_source_rect`): the whole Group (chrome included)
    for a titlebar drag, but just the dragged dock widget's own content area
    for a tab drag -- the same rect `DockWidget` itself positions by in
    `ui/dockwidget.slint` (`GroupMetrics`' border/header sizes, mirrored as
    plain constants in `manager.rs` since Rust has no access to that Slint
    global). A whole-Group screenshot would be wrong there: it'd show
    whichever tab is *currently* current, title/tab bars and all, not the
    dock widget actually being picked up.
  - That's also why `DockingArea::drag_started` makes a tab drag's dock
    widget current *before* anything else: `DockWidget`'s own `visible`
    binding gates on `is-current` (`dockwidget.slint`), so a background
    tab's content isn't being rendered at all at the moment the drag starts
    -- there'd be nothing correct to crop out otherwise. `set_current()`'s
    `refresh()` call updates Slint's property graph synchronously, and
    `take_snapshot()` re-renders from whatever the current values are when
    it's called (not from whatever was last painted on screen), so this
    ordering is enough on its own -- no explicit "wait for a repaint" step
    needed. This is a real, user-visible side effect (the tab becomes
    current for good, not just for the snapshot), not just an implementation
    detail: it also happens to be the more natural "you're now holding this
    one" behavior. `starting_a_tab_drag_makes_it_current_even_if_the_drag_is_then_cancelled`
    in `tests/gui.rs` covers it.
- **Drop indicator artwork** (`src/indicators.rs`) is decoded from the same
  PNGs the QtQuick frontend uses (`src/img/classic_indicators/`, copied to
  `ui/img/` -- renamed `outter_*` → `outer_*`, see "Pre-commit hooks" below),
  but *not* via Slint's `@image-url()`: that macro needs a literal path at
  compile time, so unlike `ClassicIndicator.qml` (which builds a
  `"qrc:/img/...").png"` path string at runtime) it can't pick one of the
  eighteen files by a runtime-computed name. `slint::Image::load_from_data()`
  can, so the indicator images are decoded directly in Rust and handed to
  Slint as plain `image`-typed struct fields (`IndicatorData`/`DragData` in
  `types.slint`) -- one more thing, alongside the ghost, that doesn't need
  `install!` at all, since `slint::Image` is an ordinary published type, not
  one Slint only generates inside the app's own compiled `.slint`. Decoded
  images are cached in a `thread_local!`, not a `static`: `slint::Image`
  isn't `Sync`.
- **A drag threshold, not a plain click handler.** Both `TitleBar`'s own
  `TouchArea` (`ui/titlebar.slint`) and each tab's (`ui/group.slint`'s `for`
  loop) use `pointer-event` (down/up) plus `moved` together, exactly the
  pattern `ui/separator.slint` already used for resizing: `down` records the
  press position, `moved` compares against it and only fires `drag-started`
  past a 4px threshold, `up` fires either `drag-ended` (if that threshold was
  crossed) or, for a tab, `current-changed` (a plain click). Coordinates
  passed up (`self.absolute-position.x + self.mouse-x`, etc.) are
  window-absolute -- neither component knows where the enclosing `DropArea`
  is, only `ui/droparea.slint` does, so that's the one place that converts to
  DropArea-local (subtracting its own `absolute-position`) before forwarding
  to `Docking`.
- **A second, one-level-down `sync_rows` trap.** `GroupData`'s own
  `dockwidgets` field is itself a `ModelRc`; naively rebuilding it fresh on
  every refresh (as the original code did, since nothing needed it to
  survive a refresh yet) tears down a tab's `TouchArea` exactly like handing
  `Docking.groups` a fresh model on every refresh would (see `sync_rows`'s
  doc comment) -- invisible for a `clicked`-only tab (a single, synchronous
  event has no state to lose), but fatal for a drag: `drag_started()`
  refreshes synchronously, mid-gesture, destroying the very `TouchArea`
  holding the pointer grab before its first `moved` event, exactly the
  failure mode the doc comment already describes for Separators. Hit this
  for real while adding the GUI drag tests below: the drag would start (its
  ghost snapshot got taken) but a subsequent release never reached
  `drag_ended`. Fixed by giving `sync_rows` a generic (not just `i32`) key
  type and caching one tab-list `VecModel` per Group id in `install!`
  (`dockwidget_models`), synced the same way `groups`/`separators` are.
- **No Escape-to-cancel.** `Docking.drag-cancelled()`/
  `DockingArea::drag_cancelled` exist and work (nothing currently calls
  them), for whenever keyboard handling during a drag gets wired up.
  Releasing over empty space already cancels a drag today.

## Known gaps (intentional, for now)

- No way to reopen a closed DockWidget from the UI (Rust can, via
  `add_dock_widget`).
- Not multi-window: dragging redocks within the one window, but never
  detaches into a floating one. With the no-reparenting design above,
  content can't move between windows either; floating windows will need a
  different idea.
- No Escape-to-cancel for an in-progress drag (see "Drag-and-drop" above).

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
- The drag-and-drop tests drive real `slint::platform::WindowEvent`s
  (`PointerPressed`/`Moved`/`Released` via `ui.window().dispatch_event`, see
  `drag()`) rather than calling `DockingArea` directly, specifically to
  exercise the `.slint`-side `TouchArea` wiring -- that's how the
  per-Group-tab-list `sync_rows` bug (see "Drag-and-drop" above) got caught.
  A single `PointerMoved` straight to the target both crosses the 4px drag
  threshold and places the drop, since `DockManager::update_drag` only looks
  at the pointer's current position, never the path it took. Dropping dead
  center on a Group's own bounds reliably hits its Center indicator without
  the test needing to know `INDICATOR_SIZE`/margins itself, since Center is
  positioned exactly at the hovered Group's own centroid (`group_showing`'s
  companion `center_of` helper relies on this). Groups aren't otherwise
  identifiable from the element tree (ids are internal, and elements carry no
  `unique-name`), so `group_showing(ui, label)` -- "the Group currently
  showing this dock widget" -- is how these tests pick one out, before *and*
  after a drop.

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

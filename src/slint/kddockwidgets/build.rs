// This file is part of KDDockWidgets.
//
// SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
//
// SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
//
// Contact KDAB at <info@kdab.com> for commercial licensing options.

//! Builds two things:
//!
//! 1. KDDockWidgets' own standalone layouting engine (the "none" frontend:
//!    no Qt, just `Core::Item`/`ItemBoxContainer`), via its real CMakeLists.txt.
//!    This is the one piece of this crate that reaches outside `src/slint`,
//!    by design: it's the same C++ engine used by
//!    `src/core/layouting/examples/slint`.
//! 2. `cpp/bridge.cpp`, our thin C++ wrapper around that engine, together
//!    with the cxx glue declared in `src/ffi.rs`.

use std::env;
use std::path::PathBuf;

fn main() {
    let manifest_dir = PathBuf::from(env::var("CARGO_MANIFEST_DIR").unwrap());
    // .../KDDockWidgets/src/slint/kddockwidgets -> .../KDDockWidgets
    let kddw_root = manifest_dir
        .parent()
        .and_then(|p| p.parent())
        .and_then(|p| p.parent())
        .expect("kddockwidgets crate is expected at <KDDockWidgets>/src/slint/kddockwidgets")
        .to_path_buf();
    let kddw_src = kddw_root.join("src");

    println!("cargo:rerun-if-changed=cpp/bridge.h");
    println!("cargo:rerun-if-changed=cpp/bridge.cpp");
    println!("cargo:rerun-if-changed=src/ffi.rs");

    // --- 1. Build the standalone layouting engine ---
    //
    // We point cmake straight at KDDockWidgets' own top-level CMakeLists.txt
    // (the same one used for the C++/Qt build), asking for the Qt-free
    // "none" frontend. We build only the `kddockwidgets` target and skip
    // `install`: this configuration doesn't have a supported install step
    // (it's missing some generated CMake package files), and we don't need
    // one — we link the static lib directly out of the build tree below, the
    // same way `src/core/layouting/examples/slint` reaches into the source
    // tree for the private headers it needs.
    let dst = cmake::Config::new(&kddw_root)
        .define("KDDockWidgets_FRONTENDS", "none")
        .define("KDDockWidgets_STATIC", "ON")
        .define("KDDockWidgets_EXAMPLES", "OFF")
        .define("KDDockWidgets_TESTS", "OFF")
        .define("KDDockWidgets_DOCS", "OFF")
        // Avoid depending on the system's spdlog/fmt: since we don't run
        // `cmake --install` (see below), we'd have to reconstruct their
        // link flags ourselves rather than getting them transitively.
        .define("KDDockWidgets_NO_SPDLOG", "ON")
        .define("CMAKE_POSITION_INDEPENDENT_CODE", "ON")
        .build_target("kddockwidgets")
        .build();
    let build_dir = dst.join("build");

    println!("cargo:rustc-link-search=native={}", build_dir.join("lib").display());
    println!("cargo:rustc-link-lib=static=kddockwidgets");

    // --- 2. Compile our bridge against it ---
    cxx_build::bridge("src/ffi.rs")
        .file("cpp/bridge.cpp")
        .std("c++17")
        // Private KDDW headers (core/layouting/*_p.h, KDDockWidgets.h, ...).
        .include(&kddw_src)
        // "kddockwidgets/KDDockWidgets.h" etc. forwarding headers.
        .include(kddw_src.join("fwd_headers"))
        // kdbindings/, kdtoolbox/.
        .include(kddw_src.join("3rdparty"))
        // nlohmann/json.hpp.
        .include(kddw_src.join("3rdparty/nlohmann"))
        // The kddockwidgets_export.h that CMake generated for us above.
        .include(&build_dir)
        .warnings(false)
        .compile("kddw_bridge");
}

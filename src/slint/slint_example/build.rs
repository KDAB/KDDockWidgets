// This file is part of KDDockWidgets.
//
// SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
//
// SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
//
// Contact KDAB at <info@kdab.com> for commercial licensing options.

use std::collections::HashMap;
use std::path::PathBuf;

fn main() {
    // Makes `import { ... } from "@kddockwidgets";` resolve to the
    // kddockwidgets crate's Slint component library.
    let library_paths =
        HashMap::from([("kddockwidgets".to_string(), PathBuf::from("../kddockwidgets/ui/lib.slint"))]);

    let config = slint_build::CompilerConfiguration::new().with_library_paths(library_paths);
    slint_build::compile_with_config("ui/app.slint", config).unwrap();
}

// This file is part of KDDockWidgets.
//
// SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
//
// SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
//
// Contact KDAB at <info@kdab.com> for commercial licensing options.

//! Artwork for the drop indicators, copied from the QtQuick frontend's
//! `src/img/classic_indicators/` (see `ui/img/`).
//!
//! The QtQuick version (`ClassicIndicator.qml`) picks a file at runtime by
//! building a path string (`"qrc:/img/classic_indicators/" + name + ".png"`).
//! Slint's `@image-url()` has no equivalent: it needs a literal path at
//! compile time, so it can only ever produce one fixed [`slint::Image`], not
//! pick between several by a runtime-computed name. Decoding the PNGs
//! ourselves with [`slint::Image::load_from_data`] sidesteps that, as a
//! bonus keeping this entirely on the Rust side -- unlike everything else
//! that needs Slint-generated types, this doesn't need `install!`, so it
//! stays ordinary code apps never have to know exists.

use crate::manager::DropLocation;
use slint::Image;

fn decode(bytes: &[u8]) -> Image {
    Image::load_from_data(bytes, Some("png")).expect("embedded drop-indicator PNG failed to decode")
}

thread_local! {
    // Matches image_index()'s layout: (inactive, active) pairs in
    // Outer{Left,Top,Right,Bottom}, {Left,Top,Right,Bottom}, Center order.
    //
    // A thread_local, not a plain static: slint::Image isn't Sync (Slint's
    // UI types are single-threaded by design, same as the rest of this
    // crate assumes), so a `static` holding one wouldn't compile. Decoding
    // once per thread and cloning the (cheaply-shared) handle out is also
    // just faster than re-decoding these on every indicator redraw, which
    // happens on every pointer move during a drag.
    static IMAGES: [Image; 18] = [
        decode(include_bytes!("../ui/img/outer_left.png")),
        decode(include_bytes!("../ui/img/outer_left_active.png")),
        decode(include_bytes!("../ui/img/outer_top.png")),
        decode(include_bytes!("../ui/img/outer_top_active.png")),
        decode(include_bytes!("../ui/img/outer_right.png")),
        decode(include_bytes!("../ui/img/outer_right_active.png")),
        decode(include_bytes!("../ui/img/outer_bottom.png")),
        decode(include_bytes!("../ui/img/outer_bottom_active.png")),
        decode(include_bytes!("../ui/img/inner_left.png")),
        decode(include_bytes!("../ui/img/inner_left_active.png")),
        decode(include_bytes!("../ui/img/inner_top.png")),
        decode(include_bytes!("../ui/img/inner_top_active.png")),
        decode(include_bytes!("../ui/img/inner_right.png")),
        decode(include_bytes!("../ui/img/inner_right_active.png")),
        decode(include_bytes!("../ui/img/inner_bottom.png")),
        decode(include_bytes!("../ui/img/inner_bottom_active.png")),
        decode(include_bytes!("../ui/img/center.png")),
        decode(include_bytes!("../ui/img/center_active.png")),
    ];
}

fn image_index(location: DropLocation, active: bool) -> usize {
    let base = match location {
        DropLocation::OuterLeft => 0,
        DropLocation::OuterTop => 2,
        DropLocation::OuterRight => 4,
        DropLocation::OuterBottom => 6,
        DropLocation::Left => 8,
        DropLocation::Top => 10,
        DropLocation::Right => 12,
        DropLocation::Bottom => 14,
        DropLocation::Center => 16,
    };
    base + usize::from(active)
}

/// The artwork for one drop indicator. Used by [`install!`](crate::install)
/// to build `IndicatorData` rows; not meant to be called by apps directly.
#[doc(hidden)]
pub fn indicator_image(location: DropLocation, active: bool) -> Image {
    IMAGES.with(|images| images[image_index(location, active)].clone())
}

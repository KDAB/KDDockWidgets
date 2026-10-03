/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

// llvm-cov ignores LCOV_EXCL_* markers, so functions that can't or shouldn't be covered
// (Wayland-only code, internal sanity checks) opt out of instrumentation instead.
// It's a no-op unless building with clang.
#if defined(__clang__)
#define KDDW_NO_COVERAGE __attribute__((no_profile_instrument_function))
#else
#define KDDW_NO_COVERAGE
#endif

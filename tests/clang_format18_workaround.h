/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "core/Platform.h"

/// These macros are workaround for clang-format-18 bug:
///    -    KDDW_CO_AWAIT Platform::instance()->tests_wait(1);
///    +    KDDW_CO_AWAIT Platform::instance() -> tests_wait(1);
/// This is avoided when wrapped in a macro.

#define EVENT_LOOP(millis) \
    KDDW_CO_AWAIT          \
    KDDockWidgets::Core::Platform::instance()->tests_wait(millis)

#define WAIT_FOR_RESIZE(window) \
    KDDW_CO_AWAIT               \
    KDDockWidgets::Core::Platform::instance()->tests_waitForResize(window)

#define WAIT_FOR_DELETED(window) \
    KDDW_CO_AWAIT                \
    KDDockWidgets::Core::Platform::instance()->tests_waitForDeleted(window)

#define WAIT_FOR_EVENT(window, event) \
    KDDW_CO_AWAIT                     \
    KDDockWidgets::Core::Platform::instance()->tests_waitForEvent(window, event)

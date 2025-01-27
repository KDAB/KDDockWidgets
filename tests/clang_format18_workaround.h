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
///    -    Platform::instance()->tests_wait(1);
///    +    Platform::instance() -> tests_wait(1);
/// This is avoided when wrapped in a macro.

#define EVENT_LOOP(millis) \
    KDDockWidgets::Core::Platform::instance()->tests_wait(millis)

#define WAIT_FOR_RESIZE(window) \
    KDDockWidgets::Core::Platform::instance()->tests_waitForResize(window)

#define WAIT_FOR_DELETED(window) \
    KDDockWidgets::Core::Platform::instance()->tests_waitForDeleted(window)

#define WAIT_FOR_EVENT(window, event) \
    KDDockWidgets::Core::Platform::instance()->tests_waitForEvent(window, event)

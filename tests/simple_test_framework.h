/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/// We require coroutine support to be able to run C++ with flutter
/// as we need to suspend the tests and run the flutter event loop
/// to process events. For this reason we can't use doctest, as it doesn't
/// support coroutines and has several internal functions that don't return awaitables.
/// We're now using a custom "testing framework" until finding something better.
/// For now it just has the minimum required to run tests

#pragma once

#define KDDW_TEST_RETURN(res)                                             \
    if (!res)                                                             \
        qDebug() << "FAILED: at" << Q_FUNC_INFO << "; line=" << __LINE__; \
    KDDW_CO_RETURN res;

// TODOm4: Investigate something more fancy
#define CHECK Q_ASSERT
#define CHECK_EQ(a, b) Q_ASSERT((a) == (b))

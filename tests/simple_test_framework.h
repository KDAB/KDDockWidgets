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

#include "KDDockWidgets.h"
#include "core/Platform.h"
#include "core/Logging_p.h"

#include <string>
#include <functional>
#include <iostream>
#include <cassert>

#if defined(_MSC_VER)
#define KDDW_FUNC_INFO __FUNCSIG__
#elif defined(__GNUC__)
#define KDDW_FUNC_INFO __PRETTY_FUNCTION__
#else
#define KDDW_FUNC_INFO "unknown"
#endif

#define KDDW_TEST_RETURN(res)                                           \
    if (!res)                                                           \
        KDDW_WARN("FAILED: at={} ; line={}", KDDW_FUNC_INFO, __LINE__); \
    KDDW_CO_RETURN res;

#define CHECK assert
#define CHECK_EQ(a, b) assert((a) == (b))

struct KDDWTest
{
    std::string name;
    std::function<KDDW_QCORO_TASK()> func;

    KDDW_QCORO_TASK run()
    {
        std::cout << "Running " << name << std::endl;
        auto result = KDDW_CO_AWAIT func();
        if (!result)
            std::cerr << "FAILED! " << name << std::endl;
        KDDW_TEST_RETURN(result);
    }

    static KDDW_QCORO_TASK run(const std::vector<KDDWTest> &tests)
    {
        std::cout << "Running tests for Platform " << KDDockWidgets::Core::Platform::instance()->name() << "\n";
        for (KDDWTest test : tests) {
            auto result = KDDW_CO_AWAIT test.run();
            if (!result) {
                KDDW_TEST_RETURN(result);
            }
        }
        KDDW_TEST_RETURN(true);
    }
};

#define TEST(name)      \
    {                   \
        KDDWTest        \
        {               \
            #name, name \
        }               \
    }

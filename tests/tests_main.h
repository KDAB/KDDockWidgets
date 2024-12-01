/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/// Contains our main() for running tests which require C++ co-routine support
/// Allows for better C++ interop with flutter's event loop

#pragma once

#include "KDDockWidgets.h"
#include "simple_test_framework.h"
#include "core/Platform.h"

#include <iostream>

#ifdef KDDW_HAS_SPDLOG
#include "fatal_logger.h"
#endif

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;

static std::vector<KDDWTest> s_testsToRun;

int main(int argc, char **argv)
{
#ifdef KDDW_HAS_SPDLOG
    FatalLogger::create();
#endif

    if (argc >= 2) {
        auto it = std::find_if(s_tests.cbegin(), s_tests.cend(), [argv](const KDDWTest &test) {
            return test.name == argv[1];
        });

        if (it == s_tests.cend()) {
            std::cerr << "Unknown test " << argv[1] << "\n";
            return 1;
        } else {
            s_testsToRun = { *it };
        }
    } else {
        s_testsToRun = s_tests;
    }

    for (FrontendType type : Core::Platform::frontendTypes()) {
        Core::Platform::tests_initPlatform(argc, argv, type);
#ifndef KDDW_TESTS_NO_FATAL_WARNINGS
        Core::Platform::instance()->installMessageHandler();
#endif

        auto result = KDDWTest::run(s_testsToRun);
        if (!result)
            return result;

        std::cout << "SUCCESS\n\n";
        Core::Platform::instance()->uninstallMessageHandler();
        Core::Platform::tests_deinitPlatform();
    }
    return 0;
}

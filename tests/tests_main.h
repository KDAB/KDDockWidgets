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

#ifdef KDDW_FRONTEND_FLUTTER

#include "../flutter/Platform.h"
#include "flutter_tests_embedder/tests_embedder.h"

#include <qcoro5/qcoro/qcorocore.h>

#endif

int main(int argc, char **argv)
{
#ifdef KDDW_FRONTEND_FLUTTER
    KDDockWidgets::flutter::Platform::s_runTestsFunc = []() -> KDDW_QCORO_TASK {
        for (auto test : s_tests) {
            auto result = co_await test();
            if (!result) {
                KDDW_TEST_RETURN(result);
            }
        }
        KDDW_TEST_RETURN(true);
    };

    KDDockWidgets::flutter::TestsEmbedder embedder(argc, argv);
    const int result = embedder.run();

    qDebug() << Q_FUNC_INFO << "tests ended with result=" << result;
    return result;

#else
    for (FrontendType type : Core::Platform::frontendTypes()) {
        Core::Platform::tests_initPlatform(argc, argv, type);
#ifndef KDDW_TESTS_NO_FATAL_WARNINGS
        Core::Platform::instance()->installMessageHandler();
#endif

        std::cout << "Running tests for Platform " << Core::Platform::instance()->name() << "\n";

        for (auto test : s_tests) {
            auto result = test();
            if (!result)
                return result;
        }

        if (Core::Platform::instance()->m_numWarningsEmitted > 0) {
            std::cout << "ABORTING! Test caused a warning.\n";
            return 1;
        }

        std::cout << "SUCCESS\n\n";
        Core::Platform::instance()->uninstallMessageHandler();
        Core::Platform::tests_deinitPlatform();
    }
    return 0;
#endif
}

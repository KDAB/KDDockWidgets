/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifdef KDDW_HAS_SPDLOG
#include "fatal_logger.h"
#endif

#include "core/Platform.h"
#include <QTest>

int main(int argc, char *argv[])
{
#ifdef KDDW_HAS_SPDLOG
    KDDockWidgets::FatalLogger::create();
#endif

    const auto frontends = KDDockWidgets::Core::Platform::frontendTypes();
    for (auto frontend : frontends) {
        KDDockWidgets::Core::Platform::tests_initPlatform(argc, argv, frontend);

        KDDW_TEST_NAME test;
        const int exitCode = QTest::qExec(&test, argc, argv);
        if (exitCode != 0)
            return exitCode;

        KDDockWidgets::Core::Platform::tests_deinitPlatform();
    }
}

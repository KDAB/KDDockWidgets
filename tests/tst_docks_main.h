/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Platform.h"
#include "utils.h"
#include "kddockwidgets/ViewFactory.h"
#include "kddockwidgets/core/Window.h"

#include <QDebug>
#include <QtTest/QTest>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Tests;
using namespace KDDockWidgets::Core;
using namespace Layouting;

class TestDocks;

int main(int argc, char *argv[])
{
    int exitCode = 0;
    for (FrontendType type : Platform::frontendTypes()) {
        qDebug() << "\nTesting platform" << type << ":\n";
        KDDockWidgets::Core::Platform::tests_initPlatform(argc, argv, type);

        TestDocks test;

        const int code = QTest::qExec(&test, argc, argv);
        if (code != 0)
            exitCode = 1;
        KDDockWidgets::Core::Platform::tests_deinitPlatform();
    }

    return exitCode;
}

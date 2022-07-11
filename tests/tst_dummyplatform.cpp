/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#define DOCTEST_CONFIG_IMPLEMENT

#include "Platform.h"
#include "dummy/Window_dummy.h"

#include <doctest/doctest.h>

using namespace KDDockWidgets;


TEST_CASE("Test pure-virtuals implemented")
{
    Window_dummy dummy;
}

int main(int argc, char **argv)
{
    doctest::Context ctx;
    ctx.applyCommandLine(argc, argv);

    Platform::tests_initPlatform(argc, argv, FrontendType::Dummy);

    const int exitCode = ctx.run();
    Platform::tests_deinitPlatform();

    return exitCode;
}

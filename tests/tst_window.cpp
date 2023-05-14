/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// There's a benign warning:
// Group.qml:221: ReferenceError: parent is not defined
// TODO: Try to fix the warning
#define KDDW_TESTS_NO_FATAL_WARNINGS

#include "simple_test_framework.h"
#include "core/View_p.h"
#include "kddockwidgets/core/Platform.h"
#include "kddockwidgets/core/Window.h"

using namespace KDDockWidgets::Core;

KDDW_QCORO_TASK tst_windowCtor()
{
    auto window = Platform::instance()->tests_createWindow();
    CHECK(window);
    CHECK(window->isVisible());

    window->destroy();

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_setVisible()
{
    auto window = Platform::instance()->tests_createWindow();
    CHECK(window);
    CHECK(window->isVisible());

    window->setVisible(false);
    CHECK(!window->isVisible());

    window->setVisible(true);
    CHECK(window->isVisible());

    window->destroy();

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_handle()
{
    auto window = Platform::instance()->tests_createWindow();
    CHECK(window->handle());
    window->destroy();

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_resize()
{
    auto window = Platform::instance()->tests_createWindow();
    const QSize newSize(501, 502);
    window->resize(newSize.width(), newSize.height());

    Platform::instance()->tests_wait(100);

    CHECK_EQ(window->size(), newSize);

    window->destroy();

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_activate()
{
    auto window = Platform::instance()->tests_createWindow();
    // CHECK(window->isActive());

    // TODO

    window->destroy();

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_equals()
{
    auto window1 = Platform::instance()->tests_createWindow();
    auto window2 = Platform::instance()->tests_createWindow();

    CHECK(window1->equals(window1));
    CHECK(!window1->equals(window2));
    CHECK(!window1->equals({}));

    window1->destroy();
    window2->destroy();

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_geometry()
{
    auto window = Platform::instance()->tests_createWindow();

    const QRect geo = QRect(10, 10, 1000, 1000);
    window->setGeometry(geo);

    Platform::instance()->tests_wait(100);
    CHECK_EQ(window->geometry(), geo);

    window->destroy();

    KDDW_TEST_RETURN(true);
}

static const auto s_tests = std::vector<std::function<KDDW_QCORO_TASK()>> {
    tst_windowCtor,
    tst_setVisible,
    tst_handle,
    tst_resize,
    tst_activate,
    tst_equals,
    tst_geometry
};

#include "tests_main.h"

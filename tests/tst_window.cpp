/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "main.h"
#include "private/View_p.h"
#include "Platform.h"

TEST_CASE("Window CTOR")
{
    auto window = Platform::instance()->tests_createWindow();
    REQUIRE(window);
    CHECK(window->isVisible());

    window->destroy();
}

TEST_CASE("Window::setVisible")
{
    auto window = Platform::instance()->tests_createWindow();
    REQUIRE(window);
    CHECK(window->isVisible());

    window->setVisible(false);
    CHECK(!window->isVisible());

    window->setVisible(true);
    CHECK(window->isVisible());

    window->destroy();
}

TEST_CASE("Window::handle")
{
    auto window = Platform::instance()->tests_createWindow();
    CHECK(window->handle());
    window->destroy();
}

TEST_CASE("Window::resize, size")
{
    auto window = Platform::instance()->tests_createWindow();
    const QSize newSize(501, 502);
    window->resize(newSize.width(), newSize.height());

    Platform::instance()->tests_wait(100);

    CHECK_EQ(window->size(), newSize);

    window->destroy();
}

TEST_CASE("Window::activate")
{
    auto window = Platform::instance()->tests_createWindow();
    // CHECK(window->isActive());

    // TODO

    window->destroy();
}

TEST_CASE("Window::equals")
{
    auto window1 = Platform::instance()->tests_createWindow();
    auto window2 = Platform::instance()->tests_createWindow();

    CHECK(window1->equals(window1));
    CHECK(!window1->equals(window2));
    CHECK(!window1->equals({}));

    window1->destroy();
    window2->destroy();
}

TEST_CASE("Window::geometry")
{
    auto window = Platform::instance()->tests_createWindow();

    const QRect geo = QRect(10, 10, 1000, 1000);
    window->setGeometry(geo);

    Platform::instance()->tests_wait(100);
    CHECK_EQ(window->geometry(), geo);

    window->destroy();
}

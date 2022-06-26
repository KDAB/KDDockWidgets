/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

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

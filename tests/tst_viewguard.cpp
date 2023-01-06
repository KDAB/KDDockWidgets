/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Waqar Ahmed <waqar.ahmed@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "main.h"
#include "ViewGuard.h"
#include "Platform.h"

#include <doctest/doctest.h>

using namespace KDDockWidgets;

TEST_CASE("ViewGuard test")
{
    ViewGuard g(nullptr);
    CHECK(g.isNull());

    {
        auto view = Platform::instance()->tests_createView({});
        g = view;
        CHECK(!g.isNull());
        delete view;
    }

    CHECK(g.isNull());

    // Test when ViewGuard is destroyed before view
    // May not crash without ASAN
    auto view = Platform::instance()->tests_createView({});
    {
        ViewGuard gg(view);
        CHECK(!gg.isNull());
    }
    delete view;
}

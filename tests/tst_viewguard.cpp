/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Waqar Ahmed <waqar.ahmed@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "ViewGuard.h"
#include "qtwidgets/views/ViewWrapper_qtwidgets.h"

#include <doctest/doctest.h>

using namespace KDDockWidgets;

TEST_CASE("ViewGuard test")
{
    ViewGuard g(nullptr);
    CHECK(g.isNull());

    {
        Views::ViewWrapper_qtwidgets wv(static_cast<QWidget *>(nullptr));
        g = &wv;
        CHECK(!g.isNull());
    }

    CHECK(g.isNull());

    // Test when ViewGuard is destroyed before view
    // May not crash without ASAN
    Views::ViewWrapper_qtwidgets wv(static_cast<QWidget *>(nullptr));
    {
        ViewGuard gg(&wv);
        CHECK(!gg.isNull());
    }
}

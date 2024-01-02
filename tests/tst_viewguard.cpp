/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Waqar Ahmed <waqar.ahmed@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "simple_test_framework.h"
#include "core/ViewGuard.h"
#include "core/ObjectGuard_p.h"
#include "core/Platform.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;

KDDW_QCORO_TASK tst_viewGuard()
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
    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_objectGuard()
{
    {
        ObjectGuard<Controller> guard;
        CHECK(!guard);
        CHECK(guard.isNull());
        CHECK(guard.data() == nullptr);
    }

    {
        auto c = new Controller(ViewType::DockWidget, nullptr);
        ObjectGuard<Controller> guard(c);
        CHECK(guard);
        CHECK(!guard.isNull());
        CHECK(guard.data() != nullptr);

        delete c;
        CHECK(!guard);
        CHECK(guard.isNull());
        CHECK(guard.data() == nullptr);

        auto c2 = new Controller(ViewType::DockWidget, nullptr);

        // Test assignment
        guard = c2;
        CHECK(guard);
        CHECK(!guard.isNull());
        CHECK(guard.data() != nullptr);

        delete c2;
        CHECK(!guard);
        CHECK(guard.isNull());
        CHECK(guard.data() == nullptr);
    }

    KDDW_TEST_RETURN(true);
}

static const auto s_tests = std::vector<KDDWTest> { TEST(tst_objectGuard) };

#include "tests_main.h"

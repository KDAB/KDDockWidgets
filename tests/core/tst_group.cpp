/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "../simple_test_framework.h"
#include "core/Group.h"
#include "core/Platform.h"
#include "kddockwidgets/Config.h"

using namespace KDDockWidgets;

KDDW_QCORO_TASK tst_groupCtor()
{
    auto group = new Core::Group(nullptr, {});
    CHECK(group->view()->is(Core::ViewType::Group));
    CHECK(group->view()->asWrapper()->is(Core::ViewType::Group));
    delete group;

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_dragRect()
{
    auto group = new Core::Group(nullptr, {});
    // This used to crash. Test that it doesn't.
    group->dragRect();
    delete group;

    KDDW_TEST_RETURN(true);
}

static const auto s_tests = std::vector<KDDWTest> { TEST(tst_groupCtor), TEST(tst_dragRect) };

#include "../tests_main.h"

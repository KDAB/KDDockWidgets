/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "../simple_test_framework.h"
#include "kddockwidgets/core/Group.h"
#include "kddockwidgets/core/Platform.h"

using namespace KDDockWidgets;

KDDW_QCORO_TASK tst_groupCtor()
{
    auto group = new Core::Group(nullptr, {});
    CHECK(group->view()->is(Core::ViewType::Frame));
    CHECK(group->view()->asWrapper()->is(Core::ViewType::Frame));
    delete group;

    KDDW_TEST_RETURN(true);
}

static const auto s_testMap = std::map<const char *, std::function<KDDW_QCORO_TASK()>> { TEST(tst_groupCtor) };

#include "../tests_main.h"

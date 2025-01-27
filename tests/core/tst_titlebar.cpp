/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "../simple_test_framework.h"
#include "core/Platform.h"
#include "core/TitleBar.h"
#include "core/Group.h"

using namespace KDDockWidgets;

bool tst_titleBarCtor()
{
    auto group = new Core::Group(nullptr, {});
    auto tb = new Core::TitleBar(group);
    CHECK(tb->view()->is(Core::ViewType::TitleBar));
    CHECK(tb->view()->asWrapper()->is(Core::ViewType::TitleBar));
    delete tb;
    delete group;

    KDDW_TEST_RETURN(true);
}

static const auto s_tests = std::vector<KDDWTest> { TEST(tst_titleBarCtor) };

#include "../tests_main.h"

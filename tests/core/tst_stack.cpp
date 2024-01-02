/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "../simple_test_framework.h"
#include "core/Platform.h"
#include "core/Group.h"
#include "core/Stack.h"


using namespace KDDockWidgets;

KDDW_QCORO_TASK tst_stackCtor()
{
    Core::Group group(nullptr, {});
    Core::Stack stack(&group, {});
    CHECK(stack.view()->is(Core::ViewType::Stack));
    CHECK(stack.view()->asWrapper()->is(Core::ViewType::Stack));

    KDDW_TEST_RETURN(true);
}

static const auto s_tests = std::vector<KDDWTest> { TEST(tst_stackCtor) };

#include "../tests_main.h"

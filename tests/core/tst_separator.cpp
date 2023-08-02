/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "../simple_test_framework.h"
#include "core/Separator.h"
#include "core/Platform.h"

using namespace KDDockWidgets;

KDDW_QCORO_TASK tst_separatorCtor()
{
    auto hostView = Core::Platform::instance()->createView(nullptr);

    {
        Core::Separator separator(hostView);
        CHECK(separator.view()->is(Core::ViewType::Separator));
        CHECK(separator.view()->asWrapper()->is(Core::ViewType::Separator));
    }

    delete hostView;


    KDDW_TEST_RETURN(true);
}

static const auto s_tests = std::vector<KDDWTest> { TEST(tst_separatorCtor) };

#include "../tests_main.h"

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "simple_test_framework.h"
#include "core/View_p.h"
#include "kddockwidgets/core/ViewFactory.h"
#include "kddockwidgets/core/Platform.h"
#include "Config.h"

#include <string>

using namespace KDDockWidgets::Core;

KDDW_QCORO_TASK tst_platform()
{
    auto plat = Platform::instance();
    CHECK(plat);

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_name()
{
    // Checks that Platform::name() returns something
    auto plat = Platform::instance();
    CHECK(!std::string(plat->name()).empty());

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_createDefaultViewFactory()
{
    auto plat = Platform::instance();
    ViewFactory *vf = plat->createDefaultViewFactory();
    CHECK(vf);
    delete vf;

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_startDragDistance()
{
    auto plat = Platform::instance();
    const int defaultDistance = plat->startDragDistance();
    CHECK(defaultDistance >= -1);

    const int newDistance = defaultDistance + 1;
    KDDockWidgets::Config::self().setStartDragDistance(newDistance);
    CHECK_EQ(plat->startDragDistance(), newDistance);

    KDDW_TEST_RETURN(true);
}

static const auto s_tests = std::vector<std::function<KDDW_QCORO_TASK()>> { tst_platform,
                                                                            tst_name,
                                                                            tst_createDefaultViewFactory,
                                                                            tst_startDragDistance };

#include "tests_main.h"

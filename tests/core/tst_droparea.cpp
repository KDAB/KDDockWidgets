/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "../simple_test_framework.h"
#include "core/DropArea.h"
#include "core/Group.h"
#include "Config.h"
#include "core/DockWidget.h"
#include "core/ViewFactory.h"
#include "core/Platform.h"
#include "tests/utils.h"
#include "../clang_format18_workaround.h"

using namespace KDDockWidgets;

KDDW_QCORO_TASK tst_dropAreaCtor()
{
    // Tests that ctor runs and doesn't leak
    Core::DropArea da(nullptr, {});

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_addWidget()
{
    auto group = new Core::Group();
    Core::DropArea da(nullptr, {});
    da.addWidget(group->view(), KDDockWidgets::Location_OnLeft);

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_addWidgetHidden()
{
    // Test adding a widget that starts hidden

    auto dw = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();
    Core::DropArea da(nullptr, {});
    da.addDockWidget(dw, KDDockWidgets::Location_OnLeft, nullptr,
                     InitialVisibilityOption::StartHidden);

    CHECK(!dw->isOpen());
    CHECK(!dw->toggleAction()->isChecked());
    dw->open();
    CHECK(dw->isOpen());
    CHECK(dw->toggleAction()->isChecked());

    auto group = dw->dptr()->group();
    delete dw;
    WAIT_FOR_DELETED(group);

    KDDW_TEST_RETURN(true);
}

static const auto s_tests = std::vector<KDDWTest> {
    TEST(tst_dropAreaCtor),
    TEST(tst_addWidget),
    TEST(tst_addWidgetHidden)
};

#include "../tests_main.h"

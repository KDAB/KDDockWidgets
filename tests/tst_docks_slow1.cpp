/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// We don't care about performance related checks in the tests
// clazy:excludeall=ctor-missing-parent-argument,missing-qobject-macro,range-loop,missing-typeinfo,detaching-member,function-args-by-ref,non-pod-global-static,reserve-candidates,qstring-allocations

// A test that was extracted out from tst_docks.cpp as it was too slow
// By using a separate executable it can be parallelized by ctest.

#include "utils.h"
#include "simple_test_framework.h"
#include "Config.h"
#include "core/Position_p.h"
#include "core/WindowBeingDragged_p.h"
#include "core/LayoutSaver_p.h"
#include "core/layouting/Item_p.h"
#include "core/ViewFactory.h"
#include "core/MDILayout.h"
#include "core/DropArea.h"
#include "core/MainWindow.h"
#include "core/DockWidget.h"
#include "core/DockWidget_p.h"
#include "core/Separator.h"
#include "core/TabBar.h"
#include "core/Stack.h"
#include "core/SideBar.h"
#include "core/Platform.h"

#include <iostream>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;
using namespace KDDockWidgets::Tests;


KDDW_QCORO_TASK tst_invalidPlaceholderPosition()
{
    auto func = [](bool restore1First) -> KDDW_QCORO_TASK {
        // Tests a bug I saw: 3 widgets stacked, close the top one, then the second top one
        // result: the bottom most one didn't have it's top separator at y=0

        EnsureTopLevelsDeleted e;
        auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
        auto dock2 = createDockWidget("2", Platform::instance()->tests_createView({ true }));
        auto dock3 = createDockWidget("3", Platform::instance()->tests_createView({ true }));

        Core::DropArea *layout = m->multiSplitter();

        // Stack: 1, 2, 3 vertically
        m->addDockWidget(dock3, Location_OnTop);
        m->addDockWidget(dock2, Location_OnTop);
        m->addDockWidget(dock1, Location_OnTop);

        auto group1 = dock1->dptr()->group();
        auto group2 = dock2->dptr()->group();
        auto group3 = dock3->dptr()->group();
        CHECK_EQ(group1->view()->y(), 0);

        // Close 1
        CHECK(dock1->isOpen());
        CHECK(dock1->view()->isVisible());
        dock1->close();
        CHECK(!dock1->isOpen());
        CHECK(!dock1->view()->isVisible());

        WAIT_FOR_RESIZE(group2->view());

        // Check that group2 moved up to y=0
        CHECK_EQ(group2->view()->y(), 0);

        // Close 2
        dock2->close();
        WAIT_FOR_RESIZE(dock3->view());

        CHECK(layout->checkSanity());
        CHECK_EQ(layout->count(), 3);
        CHECK_EQ(layout->placeholderCount(), 2);

        // Check that group3 moved up to y=1
        CHECK_EQ(group3->view()->y(), 0);

        // Now restore:
        auto toRestore1 = restore1First ? dock1 : dock2;
        auto toRestore2 = restore1First ? dock2 : dock1;

        toRestore1->open();
        CHECK_EQ(layout->placeholderCount(), 1);
        CHECK(dock3->isVisible());
        CHECK(!dock3->size().isNull());

        toRestore2->open();

        WAIT_FOR_RESIZE(group3->view());
        CHECK(layout->checkSanity());
        CHECK_EQ(layout->count(), 3);
        CHECK_EQ(layout->placeholderCount(), 0);
        layout->checkSanity();

        dock1->destroyLater();
        dock2->destroyLater();

        CHECK(KDDW_CO_AWAIT Platform::instance()->tests_waitForDeleted(dock2));

        KDDW_TEST_RETURN(true);
    };

    if (!KDDW_CO_AWAIT func(true)) {
        KDDW_TEST_RETURN(false);
    }

    if (!KDDW_CO_AWAIT func(false)) {
        KDDW_TEST_RETURN(false);
    }

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_startHidden()
{
    // A really simple test for InitialVisibilityOption::StartHidden
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }), {}, {},
                                  /*show=*/false);
    m->addDockWidget(dock1, Location_OnRight, nullptr, InitialVisibilityOption::StartHidden);
    delete dock1;

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_startHidden2()
{
    EnsureTopLevelsDeleted e;
    {
        auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }), {},
                                      {}, false);
        auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }), {},
                                      {}, false);

        auto dropArea = m->dropArea();
        Core::DropArea *layout = dropArea;

        m->addDockWidget(dock1, Location_OnTop, nullptr, InitialVisibilityOption::StartHidden);
        CHECK(layout->checkSanity());

        CHECK_EQ(layout->count(), 1);
        CHECK_EQ(layout->placeholderCount(), 1);

        m->addDockWidget(dock2, Location_OnTop);
        CHECK(layout->checkSanity());

        CHECK_EQ(layout->count(), 2);
        CHECK_EQ(layout->placeholderCount(), 1);

        dock1->open();

        CHECK_EQ(layout->count(), 2);
        CHECK_EQ(layout->placeholderCount(), 0);

        WAIT_FOR_RESIZE(dock2->view());
    }

    {
        auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }), {},
                                      {}, false);
        auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }), {},
                                      {}, false);
        auto dock3 = createDockWidget("dock3", Platform::instance()->tests_createView({ true }), {},
                                      {}, false);

        auto dropArea = m->dropArea();
        Core::DropArea *layout = dropArea;
        m->addDockWidget(dock1, Location_OnLeft, nullptr, InitialVisibilityOption::StartHidden);

        m->addDockWidget(dock2, Location_OnBottom, nullptr, InitialVisibilityOption::StartHidden);
        m->addDockWidget(dock3, Location_OnRight, nullptr, InitialVisibilityOption::StartHidden);

        dock1->open();

        CHECK_EQ(layout->count(), 3);
        CHECK_EQ(layout->placeholderCount(), 2);

        dock2->open();
        dock3->open();
        WAIT_FOR_RESIZE(dock2->view());
        layout->checkSanity();
    }

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_invalidJSON()
{
    auto func = [](QString layoutFileName, int numDockWidgets, std::string expectedWarning, bool expectedResult) -> KDDW_QCORO_TASK {
        const QString absoluteLayoutFileName = resourceFileName(QStringLiteral("layouts/") + layoutFileName);

        EnsureTopLevelsDeleted e;
        auto m1 = createMainWindow(Size(800, 500), MainWindowOption_None, "MyMainWindow1");
        for (int i = 0; i < numDockWidgets; ++i) {
            createDockWidget(QString("dock-") + QString::number(i),
                             Platform::instance()->tests_createView({ true }));
        }

        SetExpectedWarning sew(expectedWarning);

        LayoutSaver restorer;
        CHECK_EQ(restorer.restoreFromFile(absoluteLayoutFileName), expectedResult);

        KDDW_TEST_RETURN(true);
    };

    if (!KDDW_CO_AWAIT func("unsupported-serialization-version.json", 10, "Serialization format is too old", false)) {
        KDDW_TEST_RETURN(false);
    }

    if (!KDDW_CO_AWAIT func("invalid.json", 29, "", false)) {
        KDDW_TEST_RETURN(false);
    }

    if (!KDDW_CO_AWAIT func("overlapping-item.json", 2, "Unexpected pos", true)) {
        KDDW_TEST_RETURN(false);
    }

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_keepLast()
{
    // 1 event loop for DelayedDelete. Avoids LSAN warnings.
    EVENT_LOOP(1);
    KDDW_TEST_RETURN(true);
}

static const auto s_tests = std::vector<KDDWTest> {
    TEST(tst_invalidPlaceholderPosition),
    TEST(tst_startHidden),
    TEST(tst_startHidden2),
    TEST(tst_invalidJSON),
    TEST(tst_keepLast), // Keep this test at the end
};

#include "tests_main.h"

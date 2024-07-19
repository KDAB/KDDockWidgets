/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "../simple_test_framework.h"
#include "core/Group.h"
#include "core/Stack.h"
#include "core/TabBar.h"
#include "core/Platform.h"
#include "kddockwidgets/Config.h"
#include "core/ViewFactory.h"

#include "../clang_format18_workaround.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;

KDDW_QCORO_TASK tst_tabBarCtor()
{
    Core::Group group(nullptr, {});
    Core::Stack stack(&group, {});
    Core::TabBar tabBar(&stack);
    CHECK(tabBar.view()->is(ViewType::TabBar));
    CHECK(tabBar.view()->asWrapper()->is(ViewType::TabBar));

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_tabBarIndexes()
{
    Core::Group group(nullptr, {});
    Core::TabBar *tabBar = group.tabBar();

    // Starts empty:
    CHECK_EQ(tabBar->numDockWidgets(), 0);
    CHECK_EQ(tabBar->currentIndex(), -1);
    CHECK_EQ(tabBar->currentDockWidget(), nullptr);
    CHECK_EQ(tabBar->indexOfDockWidget(nullptr), -1);

    // Add 3: [dw0, dw1, dw2]
    auto dw0 = Config::self().viewFactory()->createDockWidget("dw0")->asDockWidgetController();
    auto dw1 = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();
    auto dw2 = Config::self().viewFactory()->createDockWidget("dw2")->asDockWidgetController();
    tabBar->insertDockWidget(0, dw0, {}, {});
    tabBar->insertDockWidget(1, dw1, {}, {});
    tabBar->insertDockWidget(2, dw2, {}, {});

    CHECK_EQ(tabBar->indexOfDockWidget(dw0), 0);
    CHECK_EQ(tabBar->indexOfDockWidget(dw2), 2);
    CHECK_EQ(tabBar->numDockWidgets(), 3);
    CHECK_EQ(tabBar->currentIndex(), 0);
    CHECK_EQ(tabBar->currentDockWidget(), dw0);

    // Prepend: [dw3, dw0, dw1, dw2]
    // Doesn't change the current dockwidget, but the index did shift
    auto dw3 = Config::self().viewFactory()->createDockWidget("dw3")->asDockWidgetController();
    tabBar->insertDockWidget(0, dw3, {}, {});
    CHECK_EQ(tabBar->numDockWidgets(), 4);
    CHECK_EQ(tabBar->currentIndex(), 1);
    CHECK_EQ(tabBar->currentDockWidget(), dw0);
    CHECK_EQ(tabBar->indexOfDockWidget(dw3), 0);
    CHECK_EQ(tabBar->indexOfDockWidget(dw0), 1);

    // Set index=2 as current
    tabBar->setCurrentIndex(2);
    CHECK_EQ(tabBar->currentIndex(), 2);
    CHECK_EQ(tabBar->currentDockWidget(), dw1);

    // Append: [dw3, dw0, dw1, dw2, dw4]
    // Doesn't change the current dock widget
    auto dw4 = Config::self().viewFactory()->createDockWidget("dw4")->asDockWidgetController();
    tabBar->insertDockWidget(4, dw4, {}, {});
    CHECK_EQ(tabBar->numDockWidgets(), 5);
    CHECK_EQ(tabBar->currentIndex(), 2);
    CHECK_EQ(tabBar->currentDockWidget(), dw1);

    // Remove the current: [dw3, dw0, dw2, dw4]
    // Index is maintained, the next dockwidget is current now
    tabBar->removeDockWidget(dw1);
    CHECK_EQ(tabBar->indexOfDockWidget(dw2), 2);
    CHECK_EQ(tabBar->indexOfDockWidget(dw1), -1);
    CHECK_EQ(tabBar->numDockWidgets(), 4);
    CHECK_EQ(tabBar->currentIndex(), 2);
    CHECK_EQ(tabBar->currentDockWidget(), dw2);

    // Set last as current and remove it: [dw3, dw0, dw2]
    tabBar->setCurrentIndex(3);
    CHECK_EQ(tabBar->numDockWidgets(), 4);
    CHECK_EQ(tabBar->currentIndex(), 3);
    CHECK_EQ(tabBar->currentDockWidget(), dw4);
    tabBar->removeDockWidget(dw4);
    CHECK_EQ(tabBar->numDockWidgets(), 3);
    CHECK_EQ(tabBar->currentIndex(), 2);
    CHECK_EQ(tabBar->currentDockWidget(), dw2);

    // Remove the 1st, index will shift, but current won't change: [dw0, dw2]
    tabBar->removeDockWidget(dw3);
    CHECK_EQ(tabBar->numDockWidgets(), 2);
    CHECK_EQ(tabBar->currentIndex(), 1);
    CHECK_EQ(tabBar->currentDockWidget(), dw2);

    // Remove the rest
    tabBar->removeDockWidget(dw0);
    tabBar->removeDockWidget(dw2);
    CHECK_EQ(tabBar->numDockWidgets(), 0);
    CHECK_EQ(tabBar->currentIndex(), -1);
    CHECK_EQ(tabBar->currentDockWidget(), nullptr);

    delete dw0;
    delete dw1;
    delete dw2;
    delete dw3;
    delete dw4;

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_tabBarDWDestroyed()
{
    /// Tests if indexes are correct if dock widget destroyed itself
    Core::Group group(nullptr, {});
    Core::TabBar *tabBar = group.tabBar();

    // Add 3: [dw0, dw1, dw2]
    auto dw0 = Config::self().viewFactory()->createDockWidget("dock0")->asDockWidgetController();
    auto dw1 = Config::self().viewFactory()->createDockWidget("dock1")->asDockWidgetController();
    auto dw2 = Config::self().viewFactory()->createDockWidget("dock2")->asDockWidgetController();
    tabBar->insertDockWidget(0, dw0, {}, {});
    tabBar->insertDockWidget(1, dw1, {}, {});
    tabBar->insertDockWidget(2, dw2, {}, {});

    CHECK_EQ(tabBar->numDockWidgets(), 3);
    CHECK_EQ(tabBar->currentIndex(), 0);
    CHECK_EQ(tabBar->currentDockWidget(), dw0);

    // Delete dw1: [dw0, dw2]

    delete dw1;
    CHECK_EQ(tabBar->numDockWidgets(), 2);
    CHECK_EQ(tabBar->currentIndex(), 0);
    CHECK_EQ(tabBar->currentDockWidget(), dw0);

    // Delete the current
    delete dw0;
    CHECK_EQ(tabBar->numDockWidgets(), 1);
    CHECK_EQ(tabBar->currentIndex(), 0);
    CHECK_EQ(tabBar->currentDockWidget(), dw2);

    delete dw2;
    CHECK_EQ(tabBar->numDockWidgets(), 0);
    CHECK_EQ(tabBar->currentIndex(), -1);
    CHECK_EQ(tabBar->currentDockWidget(), nullptr);

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_tabBarDWClosed()
{
    {
        /// Tests if indexes are correct if dock widget are closed (but not destroyed)
        /// Tests if indexes are correct if dock widget destroyed itself
        Core::Group group(nullptr, {});
        Core::TabBar *tabBar = group.tabBar();

        // Add 3: [dw0, dw1, dw2]
        auto dw0 = Config::self().viewFactory()->createDockWidget("dock0")->asDockWidgetController();
        auto dw1 = Config::self().viewFactory()->createDockWidget("dock1")->asDockWidgetController();
        auto dw2 = Config::self().viewFactory()->createDockWidget("dock2")->asDockWidgetController();
        tabBar->insertDockWidget(0, dw0, {}, {});
        tabBar->insertDockWidget(1, dw1, {}, {});
        tabBar->insertDockWidget(2, dw2, {}, {});

        CHECK_EQ(tabBar->numDockWidgets(), 3);
        CHECK_EQ(tabBar->currentIndex(), 0);
        CHECK_EQ(tabBar->currentDockWidget(), dw0);

        if (Platform::instance()->isQtQuick()) {
            // Workaround for QtQuick, which works fine with adding dock widgets through
            // DropArea::addDockWidget(). But not when using TabBar isolated.
            dw0->view()->setParent(group.view());
            dw1->view()->setParent(group.view());
            dw2->view()->setParent(group.view());
        }

        // Close middle one: [dw0, dw2]
        dw1->close();
        CHECK_EQ(tabBar->numDockWidgets(), 2);
        CHECK_EQ(tabBar->currentIndex(), 0);
        CHECK_EQ(tabBar->currentDockWidget(), dw0);

        // Close current
        dw0->close();
        CHECK_EQ(tabBar->numDockWidgets(), 1);
        CHECK_EQ(tabBar->currentIndex(), 0);
        CHECK_EQ(tabBar->currentDockWidget(), dw2);

        delete dw0;
        delete dw1;
        delete dw2;
    }

    // 1 event loop for DelayedDelete. Avoids LSAN warnings.
    EVENT_LOOP(1);

    KDDW_TEST_RETURN(true);
}

static const auto s_tests = std::vector<KDDWTest> {
    TEST(tst_tabBarCtor),
    TEST(tst_tabBarIndexes),
    TEST(tst_tabBarDWDestroyed),
    TEST(tst_tabBarDWClosed)
};

#include "../tests_main.h"

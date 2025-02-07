/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "core/Group.h"
#include "core/Stack.h"
#include "core/TabBar.h"
#include "core/Platform.h"
#include "kddockwidgets/Config.h"
#include "core/ViewFactory.h"

#include <QTest>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;

class TestTabBar : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void tst_tabBarCtor();
    void tst_tabBarIndexes();
    void tst_tabBarDWDestroyed();
    void tst_tabBarDWClosed();
};

void TestTabBar::tst_tabBarCtor()
{
    Core::Group group(nullptr, {});
    Core::Stack stack(&group, {});
    Core::TabBar tabBar(&stack);
    QVERIFY(tabBar.view()->is(ViewType::TabBar));
    QVERIFY(tabBar.view()->asWrapper()->is(ViewType::TabBar));
}

void TestTabBar::tst_tabBarIndexes()
{
    Core::Group group(nullptr, {});
    Core::TabBar *tabBar = group.tabBar();

    // Starts empty:
    QCOMPARE(tabBar->numDockWidgets(), 0);
    QCOMPARE(tabBar->currentIndex(), -1);
    QCOMPARE(tabBar->currentDockWidget(), nullptr);
    QCOMPARE(tabBar->indexOfDockWidget(nullptr), -1);

    // Add 3: [dw0, dw1, dw2]
    auto dw0 = Config::self().viewFactory()->createDockWidget("dw0")->asDockWidgetController();
    auto dw1 = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();
    auto dw2 = Config::self().viewFactory()->createDockWidget("dw2")->asDockWidgetController();
    tabBar->insertDockWidget(0, dw0, {}, {});
    tabBar->insertDockWidget(1, dw1, {}, {});
    tabBar->insertDockWidget(2, dw2, {}, {});

    QCOMPARE(tabBar->indexOfDockWidget(dw0), 0);
    QCOMPARE(tabBar->indexOfDockWidget(dw2), 2);
    QCOMPARE(tabBar->numDockWidgets(), 3);
    QCOMPARE(tabBar->currentIndex(), 0);
    QCOMPARE(tabBar->currentDockWidget(), dw0);

    // Prepend: [dw3, dw0, dw1, dw2]
    // Doesn't change the current dockwidget, but the index did shift
    auto dw3 = Config::self().viewFactory()->createDockWidget("dw3")->asDockWidgetController();
    tabBar->insertDockWidget(0, dw3, {}, {});
    QCOMPARE(tabBar->numDockWidgets(), 4);
    QCOMPARE(tabBar->currentIndex(), 1);
    QCOMPARE(tabBar->currentDockWidget(), dw0);
    QCOMPARE(tabBar->indexOfDockWidget(dw3), 0);
    QCOMPARE(tabBar->indexOfDockWidget(dw0), 1);

    // Set index=2 as current
    tabBar->setCurrentIndex(2);
    QCOMPARE(tabBar->currentIndex(), 2);
    QCOMPARE(tabBar->currentDockWidget(), dw1);

    // Append: [dw3, dw0, dw1, dw2, dw4]
    // Doesn't change the current dock widget
    auto dw4 = Config::self().viewFactory()->createDockWidget("dw4")->asDockWidgetController();
    tabBar->insertDockWidget(4, dw4, {}, {});
    QCOMPARE(tabBar->numDockWidgets(), 5);
    QCOMPARE(tabBar->currentIndex(), 2);
    QCOMPARE(tabBar->currentDockWidget(), dw1);

    // Remove the current: [dw3, dw0, dw2, dw4]
    // Index is maintained, the next dockwidget is current now
    tabBar->removeDockWidget(dw1);
    QCOMPARE(tabBar->indexOfDockWidget(dw2), 2);
    QCOMPARE(tabBar->indexOfDockWidget(dw1), -1);
    QCOMPARE(tabBar->numDockWidgets(), 4);
    QCOMPARE(tabBar->currentIndex(), 2);
    QCOMPARE(tabBar->currentDockWidget(), dw2);

    // Set last as current and remove it: [dw3, dw0, dw2]
    tabBar->setCurrentIndex(3);
    QCOMPARE(tabBar->numDockWidgets(), 4);
    QCOMPARE(tabBar->currentIndex(), 3);
    QCOMPARE(tabBar->currentDockWidget(), dw4);
    tabBar->removeDockWidget(dw4);
    QCOMPARE(tabBar->numDockWidgets(), 3);
    QCOMPARE(tabBar->currentIndex(), 2);
    QCOMPARE(tabBar->currentDockWidget(), dw2);

    // Remove the 1st, index will shift, but current won't change: [dw0, dw2]
    tabBar->removeDockWidget(dw3);
    QCOMPARE(tabBar->numDockWidgets(), 2);
    QCOMPARE(tabBar->currentIndex(), 1);
    QCOMPARE(tabBar->currentDockWidget(), dw2);

    // Remove the rest
    tabBar->removeDockWidget(dw0);
    tabBar->removeDockWidget(dw2);
    QCOMPARE(tabBar->numDockWidgets(), 0);
    QCOMPARE(tabBar->currentIndex(), -1);
    QCOMPARE(tabBar->currentDockWidget(), nullptr);

    delete dw0;
    delete dw1;
    delete dw2;
    delete dw3;
    delete dw4;
}

void TestTabBar::tst_tabBarDWDestroyed()
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

    QCOMPARE(tabBar->numDockWidgets(), 3);
    QCOMPARE(tabBar->currentIndex(), 0);
    QCOMPARE(tabBar->currentDockWidget(), dw0);

    // Delete dw1: [dw0, dw2]

    delete dw1;
    QCOMPARE(tabBar->numDockWidgets(), 2);
    QCOMPARE(tabBar->currentIndex(), 0);
    QCOMPARE(tabBar->currentDockWidget(), dw0);

    // Delete the current
    delete dw0;
    QCOMPARE(tabBar->numDockWidgets(), 1);
    QCOMPARE(tabBar->currentIndex(), 0);
    QCOMPARE(tabBar->currentDockWidget(), dw2);

    delete dw2;
    QCOMPARE(tabBar->numDockWidgets(), 0);
    QCOMPARE(tabBar->currentIndex(), -1);
    QCOMPARE(tabBar->currentDockWidget(), nullptr);
}

void TestTabBar::tst_tabBarDWClosed()
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

        QCOMPARE(tabBar->numDockWidgets(), 3);
        QCOMPARE(tabBar->currentIndex(), 0);
        QCOMPARE(tabBar->currentDockWidget(), dw0);

        if (Platform::instance()->isQtQuick()) {
            // Workaround for QtQuick, which works fine with adding dock widgets through
            // DropArea::addDockWidget(). But not when using TabBar isolated.
            dw0->view()->setParent(group.view());
            dw1->view()->setParent(group.view());
            dw2->view()->setParent(group.view());
        }

        // Close middle one: [dw0, dw2]
        dw1->close();
        QCOMPARE(tabBar->numDockWidgets(), 2);
        QCOMPARE(tabBar->currentIndex(), 0);
        QCOMPARE(tabBar->currentDockWidget(), dw0);

        // Close current
        dw0->close();
        QCOMPARE(tabBar->numDockWidgets(), 1);
        QCOMPARE(tabBar->currentIndex(), 0);
        QCOMPARE(tabBar->currentDockWidget(), dw2);

        delete dw0;
        delete dw1;
        delete dw2;
    }

    // 1 event loop for DelayedDelete. Avoids LSAN warnings.
    QTest::qWait(1);
}

#define KDDW_TEST_NAME TestTabBar
#include "../test_main_qt.h"

#include "tst_tabbar.moc"

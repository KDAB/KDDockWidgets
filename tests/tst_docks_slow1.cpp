/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// We don't care about performance related checks in the tests
// clazy:excludeall=ctor-missing-parent-argument,missing-qobject-macro,range-loop,missing-typeinfo,detaching-member,function-args-by-ref,non-pod-global-static,reserve-candidates,qstring-allocations

// A test that was extracted out from tst_docks.cpp as it was too slow
// By using a separate executable it can be paralellized by ctest.

#include "utils.h"
#include "Config.h"
#include "LayoutSaver_p.h"
#include "Position_p.h"
#include "WindowBeingDragged_p.h"
#include "Platform.h"
#include "multisplitter/Item_p.h"
#include "kddockwidgets/ViewFactory.h"
#include "Action.h"
#include "kddockwidgets/controllers/MDILayout.h"
#include "kddockwidgets/controllers/DropArea.h"
#include "kddockwidgets/controllers/MainWindow.h"
#include "kddockwidgets/controllers/DockWidget.h"
#include "kddockwidgets/controllers/DockWidget_p.h"
#include "kddockwidgets/controllers/Separator.h"
#include "kddockwidgets/controllers/TabBar.h"
#include "kddockwidgets/controllers/Stack.h"
#include "kddockwidgets/controllers/SideBar.h"

#include <QtTest/QtTest>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Controllers;
using namespace Layouting;
using namespace KDDockWidgets::Tests;

class TestDocks : public QObject
{
    Q_OBJECT

public Q_SLOTS:
    void initTestCase()
    {
        KDDockWidgets::Platform::instance()->installMessageHandler();
    }

    void cleanupTestCase()
    {
        KDDockWidgets::Platform::instance()->uninstallMessageHandler();
    }

private Q_SLOTS:
    void tst_invalidPlaceholderPosition_data();
    void tst_invalidPlaceholderPosition();
};

void TestDocks::tst_invalidPlaceholderPosition_data()
{
    QTest::addColumn<bool>("restore1First");
    QTest::newRow("restore1First") << true;
    QTest::newRow("restore2First") << false;
}

void TestDocks::tst_invalidPlaceholderPosition()
{
    QFETCH(bool, restore1First);

    // Tests a bug I saw: 3 widgets stacked, close the top one, then the second top one
    // result: the bottom most one didn't have it's top separator at y=0

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("2", Platform::instance()->tests_createView({ true }));
    auto dock3 = createDockWidget("3", Platform::instance()->tests_createView({ true }));

    Controllers::DropArea *layout = m->multiSplitter();

    // Stack: 1, 2, 3 vertically
    m->addDockWidget(dock3, Location_OnTop);
    m->addDockWidget(dock2, Location_OnTop);
    m->addDockWidget(dock1, Location_OnTop);

    auto group1 = dock1->dptr()->group();
    auto group2 = dock2->dptr()->group();
    auto group3 = dock3->dptr()->group();
    QCOMPARE(group1->view()->y(), 0);

    // Close 1
    dock1->close();
    Platform::instance()->tests_waitForResize(group2->view());

    // Check that group2 moved up to y=1
    QCOMPARE(group2->view()->y(), 0);

    // Close 2
    dock2->close();
    Platform::instance()->tests_waitForResize(dock3->view());

    QVERIFY(layout->checkSanity());
    QCOMPARE(layout->count(), 3);
    QCOMPARE(layout->placeholderCount(), 2);

    // Check that group3 moved up to y=1
    QCOMPARE(group3->view()->y(), 0);

    // Now restore:
    auto toRestore1 = restore1First ? dock1 : dock2;
    auto toRestore2 = restore1First ? dock2 : dock1;

    toRestore1->open();
    QCOMPARE(layout->placeholderCount(), 1);
    QVERIFY(dock3->isVisible());
    QVERIFY(!dock3->size().isNull());

    toRestore2->open();

    Platform::instance()->tests_waitForResize(group3->view());
    QVERIFY(layout->checkSanity());
    QCOMPARE(layout->count(), 3);
    QCOMPARE(layout->placeholderCount(), 0);
    layout->checkSanity();

    dock1->deleteLater();
    dock2->deleteLater();
    QVERIFY(Platform::instance()->tests_waitForDeleted(dock2));
}

#include "tst_docks_main.h"

#include <tst_docks_slow1.moc>

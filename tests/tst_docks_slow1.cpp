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
#include "multisplitter/Item_p.h"
#include "kddockwidgets/core/ViewFactory.h"
#include "Action.h"
#include "kddockwidgets/core/MDILayout.h"
#include "kddockwidgets/core/DropArea.h"
#include "kddockwidgets/core/MainWindow.h"
#include "kddockwidgets/core/DockWidget.h"
#include "kddockwidgets/core/DockWidget_p.h"
#include "kddockwidgets/core/Separator.h"
#include "kddockwidgets/core/TabBar.h"
#include "kddockwidgets/core/Stack.h"
#include "kddockwidgets/core/SideBar.h"
#include "kddockwidgets/core/Platform.h"

#include <QtTest/QTest>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;
using namespace Layouting;
using namespace KDDockWidgets::Tests;

class TestDocks : public QObject
{
    Q_OBJECT

public Q_SLOTS:
    void initTestCase()
    {
        KDDockWidgets::Core::Platform::instance()->installMessageHandler();
    }

    void cleanupTestCase()
    {
        KDDockWidgets::Core::Platform::instance()->uninstallMessageHandler();
    }

private Q_SLOTS:
    void tst_invalidPlaceholderPosition_data();
    void tst_invalidPlaceholderPosition();
    void tst_startHidden();
    void tst_startHidden2();
    void tst_invalidJSON_data();
    void tst_invalidJSON();
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

    Core::DropArea *layout = m->multiSplitter();

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

void TestDocks::tst_startHidden()
{
    // A really simple test for InitialVisibilityOption::StartHidden

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }), {}, {},
                                  /*show=*/false);
    m->addDockWidget(dock1, Location_OnRight, nullptr, InitialVisibilityOption::StartHidden);
    delete dock1;
}

void TestDocks::tst_startHidden2()
{
    EnsureTopLevelsDeleted e;
    {
        auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }), {},
                                      {}, false);
        auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }), {},
                                      {}, false);

        auto dropArea = m->dropArea();
        Core::DropArea *layout = dropArea;

        m->addDockWidget(dock1, Location_OnTop, nullptr, InitialVisibilityOption::StartHidden);
        QVERIFY(layout->checkSanity());

        QCOMPARE(layout->count(), 1);
        QCOMPARE(layout->placeholderCount(), 1);

        m->addDockWidget(dock2, Location_OnTop);
        QVERIFY(layout->checkSanity());

        QCOMPARE(layout->count(), 2);
        QCOMPARE(layout->placeholderCount(), 1);

        qDebug() << dock1->isVisible();
        dock1->open();

        QCOMPARE(layout->count(), 2);
        QCOMPARE(layout->placeholderCount(), 0);

        Platform::instance()->tests_waitForResize(dock2->view());
    }

    {
        auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
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

        QCOMPARE(layout->count(), 3);
        QCOMPARE(layout->placeholderCount(), 2);

        dock2->open();
        dock3->open();
        Platform::instance()->tests_waitForResize(dock2->view());
        layout->checkSanity();
    }
}

void TestDocks::tst_invalidJSON_data()
{
    // Be sure that the main windows in the json are called "MyMainWindow1" and the dock widgets
    // dock-x where x starts at 0
    QTest::addColumn<QString>("layoutFileName");
    QTest::addColumn<int>("numDockWidgets");
    QTest::addColumn<QString>("expectedWarning");
    QTest::addColumn<bool>("expectedResult");
    QTest::newRow("unsupported-serialization-version")
        << "unsupported-serialization-version.json" << 10 << "Serialization format is too old"
        << false;
    QTest::newRow("invalid") << "invalid.json" << 29 << "" << false;
    QTest::newRow("overlapping-item") << "overlapping-item.json" << 2 << "Unexpected pos" << true;
}

void TestDocks::tst_invalidJSON()
{
    QFETCH(QString, layoutFileName);
    QFETCH(int, numDockWidgets);
    QFETCH(QString, expectedWarning);
    QFETCH(bool, expectedResult);

    const QString absoluteLayoutFileName = QStringLiteral(":/layouts/%1").arg(layoutFileName);

    EnsureTopLevelsDeleted e;
    auto m1 = createMainWindow(QSize(800, 500), MainWindowOption_None, "MyMainWindow1");
    for (int i = 0; i < numDockWidgets; ++i) {
        createDockWidget(QStringLiteral("dock-%1").arg(i),
                         Platform::instance()->tests_createView({ true }));
    }

    SetExpectedWarning sew(expectedWarning);

    LayoutSaver restorer;
    QCOMPARE(restorer.restoreFromFile(absoluteLayoutFileName), expectedResult);
}

#include "tst_docks_main.h"

#include <tst_docks_slow1.moc>

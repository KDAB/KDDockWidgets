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

#define NOMINMAX

#include "utils.h"
#include "Config.h"
#include "core/Position_p.h"
#include "core/WindowBeingDragged_p.h"
#include "core/LayoutSaver_p.h"
#include "core/Logging_p.h"
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

#include <QtTest/QTest>

#include <iostream>
#include <cstdlib>

#ifdef KDDW_HAS_SPDLOG
#include "fatal_logger.h"
#endif

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;
using namespace KDDockWidgets::Tests;

class TestDocks : public QObject
{
    Q_OBJECT
public Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

private Q_SLOTS:
    void tst_tabTitleUpdatesWhenUnFloating();
    void tst_resizeWindow_data();
    void tst_resizeWindow();
    void tst_0_data();
    void tst_0();
    void tst_setVisibleFalseWhenSideBySide_data();
    void tst_setVisibleFalseWhenSideBySide();
    void tst_tabBarWithHiddenTitleBar_data();
    void tst_tabBarWithHiddenTitleBar();
};

void TestDocks::initTestCase()
{
    KDDockWidgets::Core::Platform::instance()->installMessageHandler();
}

void TestDocks::cleanupTestCase()
{
    KDDockWidgets::Core::Platform::instance()->uninstallMessageHandler();
}

void TestDocks::tst_resizeWindow_data()
{
    QTest::addColumn<bool>("doASaveRestore");
    QTest::newRow("false") << false;
    QTest::newRow("true") << true;
}

void TestDocks::tst_resizeWindow()
{
    QFETCH(bool, doASaveRestore);

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(501, 500), MainWindowOption_None);
    auto dock1 = createDockWidget(
        "1", Platform::instance()->tests_createView({ true, {}, Size(100, 100) }));
    auto dock2 = createDockWidget(
        "2", Platform::instance()->tests_createView({ true, {}, Size(100, 100) }));
    ObjectGuard<Core::FloatingWindow> fw1 = dock1->floatingWindow();
    ObjectGuard<Core::FloatingWindow> fw2 = dock2->floatingWindow();
    m->addDockWidget(dock1, Location_OnLeft);
    m->addDockWidget(dock2, Location_OnRight);

    auto layout = m->multiSplitter();

    layout->checkSanity();

    const int oldWidth1 = dock1->width();
    const int oldWidth2 = dock2->width();

    QVERIFY(oldWidth2 - oldWidth1 <= 1); // They're not equal if separator thickness if even

    if (doASaveRestore) {
        LayoutSaver saver;
        saver.restoreLayout(saver.serializeLayout());
    }

    m->view()->showMaximized();
    WAIT_FOR_RESIZE(m->view());

    const int maximizedWidth1 = dock1->width();
    const int maximizedWidth2 = dock2->width();

    const double relativeDifference =
        std::abs((maximizedWidth1 - maximizedWidth2) / (1.0 * layout->layoutWidth()));

    QVERIFY(relativeDifference <= 0.01);

    m->view()->showNormal();
    WAIT_FOR_RESIZE(m->view());

    const int newWidth1 = dock1->width();
    const int newWidth2 = dock2->width();

    QCOMPARE(oldWidth1, newWidth1);
    QCOMPARE(oldWidth2, newWidth2);
    layout->checkSanity();

    delete fw1;
    delete fw2;
}

void TestDocks::tst_0_data()
{
    QTest::addColumn<int>("thickness");
    QTest::newRow("2") << 2;
    QTest::newRow("1") << 1;
    QTest::newRow("0") << 0;
}

void TestDocks::tst_0()
{
    QFETCH(int, thickness);
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setSeparatorThickness(thickness);

    auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
    m->view()->resize(Size(502, 500));
    m->show();

    auto d1 = createDockWidget("1", Platform::instance()->tests_createFocusableView({ true }));
    auto d2 = createDockWidget("2", Platform::instance()->tests_createFocusableView({ true }));

    m->addDockWidget(d1, Location_OnLeft);
    m->addDockWidget(d2, Location_OnRight);
}

void TestDocks::tst_setVisibleFalseWhenSideBySide_data()
{
    QTest::addColumn<bool>("useSetVisible");
    QTest::newRow("false") << false;
    // QTest::newRow("true") << true; // We don't support closing dock widgets via
    // setVisible(false). (Yet ? Maybe never).
}

void TestDocks::tst_tabTitleUpdatesWhenUnFloating()
{
    // Tests #468
    // setTitle() is changing title bar title but not tabbar

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(500, 500), {}, "tst_marginsAfterRestore");
    auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("2", Platform::instance()->tests_createView({ true }));

    auto connectIt = [](auto dock) {
        dock->dptr()->isFloatingChanged.connect([dock](bool floating) {
            dock->setTitle(QString("%1-%2").arg(dock->uniqueName()).arg(floating));
        });
    };

    connectIt(dock1);
    connectIt(dock2);

    m->addDockWidget(dock1, Location_OnLeft);
    dock1->addDockWidgetAsTab(dock2);

    QVERIFY(dock2->isCurrentTab());
    QCOMPARE(dock1->titleBar()->title(), "2-0");
    Core::TabBar *tb = dock1->dptr()->group()->tabBar();

    QCOMPARE(tb->text(0), "1-0");
    QCOMPARE(tb->text(1), "2-0");

    // Now unfloat:
    dock1->titleBar()->onFloatClicked();

    // Since they are tabbed, they're not considered floating, but the group is floating
    QVERIFY(!dock1->isFloating());
    QVERIFY(!dock2->isFloating());
    QCOMPARE(dock1->titleBar()->title(), "2-0");
    QCOMPARE(tb->text(0), "1-0");
    QCOMPARE(tb->text(1), "2-0");

    // Put back in main window
    dock1->titleBar()->onFloatClicked();
    QVERIFY(!dock1->isFloating());
    QVERIFY(!dock2->isFloating());

    QCOMPARE(dock1->titleBar()->title(), "2-0");
    tb = dock1->dptr()->group()->tabBar();
    QCOMPARE(tb->text(0), "1-0");
    QCOMPARE(tb->text(1), "2-0");

    // Place docks side by side
    m->addDockWidget(dock2, Location_OnRight);
    QCOMPARE(dock1->titleBar()->title(), "1-0");
    QCOMPARE(dock2->titleBar()->title(), "2-0");

    // Now float:
    dock2->titleBar()->onFloatClicked();
    QCOMPARE(dock2->titleBar()->title(), "2-1");

    // Now dock again:
    dock2->titleBar()->onFloatClicked();
    QCOMPARE(dock2->titleBar()->title(), "2-0");
}

void TestDocks::tst_setVisibleFalseWhenSideBySide()
{
    QFETCH(bool, useSetVisible);

    auto setVisible = [useSetVisible](Core::DockWidget *dw, bool visible) {
        if (useSetVisible)
            dw->setVisible(visible);
        else if (visible)
            dw->open();
        else
            dw->close();
    };

    EnsureTopLevelsDeleted e;

    auto m = createMainWindow();
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));
    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    m->addDockWidget(dock2, KDDockWidgets::Location_OnRight);

    const Rect oldGeo = dock1->geometry();

    // 1. Just toggle visibility and check that stuff remained sane
    QVERIFY(dock1->titleBar()->isVisible());
    setVisible(dock1, false);

    QVERIFY(!dock1->titleBar());
    QVERIFY(!dock1->isTabbed());
    QVERIFY(dock1->isFloating());

    setVisible(dock1, true);
    QVERIFY(dock1->titleBar()->isVisible());
    QVERIFY(!dock1->isTabbed());
    QVERIFY(!dock1->isFloating());
    QCOMPARE(dock1->geometry(), oldGeo);

    // 2. Check that the parent group also is hidden now
    // auto fw1 = dock1->window();
    setVisible(dock1, false);
    QVERIFY(!dock1->dptr()->group());
    delete dock1;
}

void TestDocks::tst_tabBarWithHiddenTitleBar_data()
{
    QTest::addColumn<bool>("hiddenTitleBar");
    QTest::addColumn<bool>("tabsAlwaysVisible");

    QTest::newRow("false-false") << false << false;
    QTest::newRow("true-false") << true << false;

    QTest::newRow("false-true") << false << true;
    QTest::newRow("true-true") << true << true;
}

void TestDocks::tst_tabBarWithHiddenTitleBar()
{
    {
        EnsureTopLevelsDeleted e;
        QFETCH(bool, hiddenTitleBar);
        QFETCH(bool, tabsAlwaysVisible);

        const auto originalFlags = KDDockWidgets::Config::self().flags();

        auto newFlags = originalFlags;

        if (hiddenTitleBar)
            newFlags = newFlags | KDDockWidgets::Config::Flag_HideTitleBarWhenTabsVisible;

        if (tabsAlwaysVisible)
            newFlags = newFlags | KDDockWidgets::Config::Flag_AlwaysShowTabs;

        KDDockWidgets::Config::self().setFlags(newFlags);

        auto m = createMainWindow();

        auto d1 = createDockWidget("1", Platform::instance()->tests_createFocusableView({ true }));
        auto d2 = createDockWidget("2", Platform::instance()->tests_createFocusableView({ true }));
        m->addDockWidget(d1, Location_OnTop);

        if (tabsAlwaysVisible) {
            if (hiddenTitleBar)
                QVERIFY(!d1->dptr()->group()->titleBar()->isVisible());
            else
                QVERIFY(d1->dptr()->group()->titleBar()->isVisible());
        } else {
            QVERIFY(d1->dptr()->group()->titleBar()->isVisible());
        }

        d1->addDockWidgetAsTab(d2);

        QVERIFY(d2->dptr()->group()->titleBar()->isVisible() ^ hiddenTitleBar);

        d2->close();
        m->layout()->checkSanity();
        delete d2;
        if (tabsAlwaysVisible) {
            if (hiddenTitleBar)
                QVERIFY(!d1->dptr()->group()->titleBar()->isVisible());
            else
                QVERIFY(d1->dptr()->group()->titleBar()->isVisible());
        } else {
            QVERIFY(d1->dptr()->group()->titleBar()->isVisible());
        }
    }

    // 1 event loop for DelayedDelete. Avoids LSAN warnings.
    EVENT_LOOP(1);
}

int main(int argc, char *argv[])
{
#ifdef KDDW_HAS_SPDLOG
    FatalLogger::create();
#endif

    int exitCode = 0;
    for (FrontendType type : Platform::frontendTypes()) {
        KDDW_INFO("\nTesting platform {}\n", int(type));
        KDDockWidgets::Core::Platform::tests_initPlatform(argc, argv, type);

        TestDocks test;

        const int code = QTest::qExec(&test, argc, argv);
        if (code != 0)
            exitCode = 1;
        KDDockWidgets::Core::Platform::tests_deinitPlatform();
    }

    return exitCode;
}

#include "tst_docks_slow8.moc"

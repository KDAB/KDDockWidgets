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
#include "simple_test_framework.h"
#include "Config.h"
#include "core/LayoutSaver_p.h"
#include "core/Position_p.h"
#include "core/WindowBeingDragged_p.h"
#include "core/layouting/Item_p.h"
#include "kddockwidgets/core/ViewFactory.h"
#include "kddockwidgets/core/Action.h"
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

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;
using namespace KDDockWidgets::Tests;

KDDW_QCORO_TASK tst_dock2FloatingWidgetsTabbed()
{
    EnsureTopLevelsDeleted e;

    if (KDDockWidgets::usesNativeTitleBar())
        KDDW_CO_RETURN(true); // Unit-tests can't drag via tab, yet

    auto dock1 = createDockWidget("doc1");
    auto fw1 = dock1->floatingWindow();
    fw1->view()->setGeometry(QRect(500, 500, 400, 400));
    CHECK(dock1);
    QPointer<Core::Group> group1 = dock1->dptr()->group();

    auto titlebar1 = fw1->titleBar();
    auto dock2 = createDockWidget("doc2");

    CHECK(dock1->isFloating());
    CHECK(dock2->isFloating());

    QPoint finalPoint = dock2->window()->geometry().center() + QPoint(7, 7);
    drag(titlebar1->view(), titlebar1->mapToGlobal(QPoint(5, 5)), finalPoint, ButtonAction_Press);

    // It morphed into a FloatingWindow
    QPointer<Core::Group> group2 = dock2->dptr()->group();
    if (!dock2->floatingWindow()) {
        qWarning() << "dock2->floatingWindow()=" << dock2->floatingWindow();
        CHECK(false);
    }
    CHECK(group2);
    CHECK_EQ(group2->dockWidgetCount(), 1);

    releaseOn(finalPoint, titlebar1->view());
    CHECK_EQ(group2->dockWidgetCount(), 2); // 2.2 Frame has 2 widgets when one is dropped
    CHECK(Platform::instance()->tests_waitForDeleted(group1));

    // 2.3 Detach tab1 to empty space
    QPoint globalPressPos = dragPointForWidget(group2.data(), 0);
    Core::TabBar *tabBar = group2->stack()->tabBar();
    CHECK(tabBar);
    drag(tabBar->view(), globalPressPos,
         group2->view()->windowGeometry().bottomRight() + QPoint(10, 10));

    CHECK(group2->dockWidgetCount() == 1);
    CHECK(dock1->floatingWindow());

    // 2.4 Drag the first dock over the second
    group1 = dock1->dptr()->group();
    group2 = dock2->dptr()->group();
    fw1 = dock1->floatingWindow();
    globalPressPos = fw1->titleBar()->mapToGlobal(QPoint(100, 5));
    finalPoint = dock2->window()->geometry().center() + QPoint(7, 7);
    drag(fw1->titleBar()->view(), globalPressPos, finalPoint);

    CHECK_EQ(group2->dockWidgetCount(), 2);

    // 2.5 Detach and drop to the same place, should tab again
    globalPressPos = dragPointForWidget(group2.data(), 0);
    tabBar = group2->stack()->tabBar();

    finalPoint = dock2->window()->geometry().center() + QPoint(7, 7);
    drag(tabBar->view(), globalPressPos, finalPoint);
    CHECK_EQ(group2->dockWidgetCount(), 2);

    // 2.6 Drag the tabbed group over a 3rd floating window
    auto dock3 = createDockWidget("doc3");
    Platform::instance()->tests_wait(1000); // Test is flaky otherwise

    auto fw2 = dock2->floatingWindow();
    finalPoint = dock3->window()->geometry().center() + QPoint(7, 7);
    drag(fw2->titleBar()->view(), group2->mapToGlobal(QPoint(10, 10)), finalPoint);

    CHECK(Platform::instance()->tests_waitForDeleted(group1));
    CHECK(Platform::instance()->tests_waitForDeleted(group2));
    CHECK(dock3->dptr()->group());
    CHECK_EQ(dock3->dptr()->group()->dockWidgetCount(), 3);

    auto fw3 = dock3->floatingWindow();
    CHECK(fw3);
    CHECK(fw3->dropArea()->checkSanity());

    // 2.7 Drop the window into a MainWindow
    {
        auto m = createMainWindow();
        m->show();
        m->view()->setGeometry(QRect(500, 300, 300, 300));
        CHECK(!dock3->isFloating());
        auto fw3 = dock3->floatingWindow();
        drag(fw3->titleBar()->view(), dock3->window()->mapToGlobal(QPoint(10, 10)),
             m->geometry().center());
        CHECK(!dock3->isFloating());
        CHECK(dock3->window()->equals(m->view()));
        CHECK_EQ(dock3->dptr()->group()->dockWidgetCount(), 3);
        CHECK(m->dropArea()->checkSanity());

        delete dock1;
        delete dock2;
        delete dock3;
        CHECK(Platform::instance()->tests_waitForDeleted(group2));
        CHECK(Platform::instance()->tests_waitForDeleted(fw3));
    }

    KDDW_CO_RETURN(true);
}

KDDW_QCORO_TASK tst_restoreSimple()
{
    EnsureTopLevelsDeleted e;
    // Tests restoring a very simple layout, composed of just 1 docked widget

    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto layout = m->multiSplitter();
    auto dock1 = createDockWidget("one", Platform::instance()->tests_createFocusableView({ true }));
    auto dock2 = createDockWidget("two", Platform::instance()->tests_createFocusableView({ true }));
    auto dock3 =
        createDockWidget("three", Platform::instance()->tests_createFocusableView({ true }));

    m->addDockWidget(dock1, Location_OnTop);

    // Dock2 floats at 150,150
    const QPoint dock2FloatingPoint = QPoint(150, 150);
    dock2->view()->window()->setFramePosition(dock2FloatingPoint);
    CHECK(dock2->isVisible());
    Platform::instance()->tests_wait(1000); // Wait for group to settle

    const QPoint dock3FloatingPoint = QPoint(200, 200);
    dock3->view()->window()->setFramePosition(dock3FloatingPoint);
    dock3->close();

    LayoutSaver saver;
    CHECK(saver.saveToFile(QStringLiteral("layout_tst_restoreSimple.json")));
    auto f1 = dock1->dptr()->group();
    dock2->window()->move(QPoint(0, 0)); // Move *after* we saved.
    dock3->window()->move(QPoint(0, 0)); // Move *after* we saved.
    dock1->close();
    dock2->close();
    CHECK(!dock2->isVisible());
    CHECK_EQ(layout->count(), 1);
    CHECK(Platform::instance()->tests_waitForDeleted(f1));
    CHECK_EQ(layout->placeholderCount(), 1);

    CHECK_EQ(DockRegistry::self()->floatingWindows().size(), 0);
    CHECK(saver.restoreFromFile(QStringLiteral("layout_tst_restoreSimple.json")));
    CHECK(layout->checkSanity());
    CHECK_EQ(layout->count(), 1);
    CHECK_EQ(layout->placeholderCount(), 0);
    CHECK(dock1->isVisible());
    CHECK_EQ(saver.restoredDockWidgets().size(), 3);

    // Test a crash I got:
    dock1->setFloating(true);
    CHECK(layout->checkSanity());
    dock1->setFloating(false);

    auto fw2 = dock2->floatingWindow();
    CHECK(fw2);
    CHECK(fw2->isVisible());
    CHECK(fw2->view()->isRootView());

    CHECK_EQ(fw2->view()->window()->framePosition(), dock2FloatingPoint);

    CHECK(fw2->view()->window()->transientParent());
    CHECK(m->view()->window()->equals(fw2->view()->window()->transientParent()));
    CHECK(dock2->isFloating());
    CHECK(dock2->isVisible());

    CHECK(!dock3->isVisible()); // Remains closed
    CHECK(dock3->view()->parentView() == nullptr);

    dock3->open();
    dock3->dptr()->morphIntoFloatingWindow(); // as it would take 1 event loop. Do it now so we can
                                              // compare already.

    Platform::instance()->tests_wait(300);
    CHECK_EQ(dock3->view()->window()->framePosition(), dock3FloatingPoint);

    KDDW_CO_RETURN(true);
}

KDDW_QCORO_TASK tst_restoreSimplest()
{
    EnsureTopLevelsDeleted e;
    // Tests restoring a very simple layout, composed of just 1 docked widget
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto layout = m->multiSplitter();
    auto dock1 = createDockWidget("one", Platform::instance()->tests_createFocusableView({ true }));
    m->addDockWidget(dock1, Location_OnTop);

    LayoutSaver saver;
    CHECK(saver.saveToFile(QStringLiteral("layout_tst_restoreSimplest.json")));

    Platform::instance()->tests_wait(300);

    CHECK(layout->checkSanity());
    CHECK(saver.restoreFromFile(QStringLiteral("layout_tst_restoreSimplest.json")));
    CHECK(layout->checkSanity());

    KDDW_CO_RETURN(true);
}

static const auto s_tests = std::vector<std::function<KDDW_QCORO_TASK()>> { tst_dock2FloatingWidgetsTabbed,
                                                                            tst_restoreSimple,
                                                                            tst_restoreSimplest };

#include "tests_main.h"

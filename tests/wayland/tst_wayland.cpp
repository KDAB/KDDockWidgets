/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// Tests that need a real Wayland compositor. Run them through kddw_test_compositor:
//   kddw_test_compositor -- tst_wayland

#include "WaylandTestUtils.h"
#include "../utils.h"

#include "core/DockWidget.h"
#include "core/DockWidget_p.h"
#include "core/DragController_p.h"
#include "core/Group.h"
#include "core/MainWindow.h"
#include "core/Platform.h"
#include "core/Stack.h"
#include "core/TabBar.h"
#include "core/TitleBar.h"

#include <QTest>

#include <memory>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;
using namespace KDDockWidgets::Tests;
using namespace KDDockWidgets::Tests::Wayland;

class TestWayland : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void tst_dragDockWidgetOntoAnother();
    void tst_doubleClickTabDetaches();
    void tst_dragTabToEmptySpaceKeepsItDocked();

private:
    std::unique_ptr<TestInput> m_input;
};

void TestWayland::initTestCase()
{
    if (Platform::instance()->displayType() != Platform::DisplayType::Wayland) {
        const QString message =
            QStringLiteral("tst_wayland needs to run inside kddw_test_compositor. Run it with either:\n"
                           "    ctest --test-dir %1 -L wayland\n"
                           "    KDDW_TEST_FRONTEND=1 %2 [--visible] [--step-delay <msecs>] -- %3")
                .arg(QStringLiteral(KDDW_BUILD_DIR), QStringLiteral(KDDW_TEST_COMPOSITOR),
                     QCoreApplication::applicationFilePath());
        QFAIL(qPrintable(message));
    }

    m_input = std::make_unique<TestInput>();
    QVERIFY2(m_input->waitForActive(), "kddw_test_v1 not found. Run the test through kddw_test_compositor");
}

void TestWayland::cleanupTestCase()
{
    // Before the platform and its QGuiApplication are destroyed
    m_input.reset();
}

void TestWayland::tst_dragDockWidgetOntoAnother()
{
    // Drags dock1 by its title bar and drops it onto the center of dock2, so they get tabbed

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));
    m->addDockWidget(dock1, Location_OnLeft);
    m->addDockWidget(dock2, Location_OnRight);
    QVERIFY(waitForMapped(m->view()));

    Group *group1 = dock1->dptr()->group();
    Group *group2 = dock2->dptr()->group();
    QVERIFY(group1 != group2);
    QVERIFY(!dock1->isTabbed());

    View *titleBar = dock1->titleBar()->view();
    m_input->drag(titleBar, titleBar->rect().center(), group2->view(), group2->view()->rect().center());
    QVERIFY(m_input->commitAndWait());

    QTRY_COMPARE(dock1->dptr()->group(), group2);
    QCOMPARE(group2->dockWidgetCount(), 2);
    QVERIFY(dock1->isTabbed());
    QVERIFY(dock2->isTabbed());
    QVERIFY(!dock1->isFloating());
}

void TestWayland::tst_doubleClickTabDetaches()
{
    // On Wayland, dragging a tab out to empty space doesn't detach it, as the compositor cancels
    // drags that aren't dropped onto a window. Double-clicking the tab detaches it instead.

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));
    m->addDockWidget(dock1, Location_OnLeft);
    dock1->addDockWidgetAsTab(dock2);
    QVERIFY(waitForMapped(m->view()));
    QVERIFY(dock2->isTabbed());

    TabBar *tabBar = dock2->dptr()->group()->stack()->tabBar();
    m_input->moveTo(tabBar->view(), tabBar->rectForTab(tabBar->indexOfDockWidget(dock2)).center());
    m_input->doubleClick();
    QVERIFY(m_input->commitAndWait());

    QTRY_VERIFY(dock2->isFloating());
    QVERIFY(!dock1->isFloating());
    QVERIFY(!dock1->isTabbed());
    QVERIFY(dock1->isInMainWindow());
}

void TestWayland::tst_dragTabToEmptySpaceKeepsItDocked()
{
    // Releasing a drag over no window makes the compositor cancel it, so the tab stays put

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));
    m->addDockWidget(dock1, Location_OnLeft);
    dock1->addDockWidgetAsTab(dock2);
    QVERIFY(waitForMapped(m->view()));

    int numCanceled = 0;
    KDBindings::ScopedConnection connection =
        DragController::instance()->dragCanceled.connect([&numCanceled] { ++numCanceled; });

    Group *group = dock2->dptr()->group();
    TabBar *tabBar = group->stack()->tabBar();
    m_input->startDrag(tabBar->view(), tabBar->rectForTab(tabBar->indexOfDockWidget(dock2)).center());
    m_input->moveToAbsolute(Point(1500, 900)); // The main window is at 0,0 and 800x500
    m_input->release();
    QVERIFY(m_input->commitAndWait());

    QTRY_COMPARE(numCanceled, 1);
    QVERIFY(!DragController::instance()->isDragging());
    QVERIFY(!dock2->isFloating());
    QCOMPARE(dock2->dptr()->group(), group);
    QCOMPARE(group->dockWidgetCount(), 2);
}

#define KDDW_TEST_NAME TestWayland
#include "../test_main_qt.h"

#include "tst_wayland.moc"

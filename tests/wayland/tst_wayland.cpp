/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// Tests that need a real Wayland compositor. They start kddw_test_compositor themselves, see
// ensureCompositor(). Use KDDW_TEST_COMPOSITOR_ARGS="--visible" to watch them.

#include "WaylandTestUtils.h"
#include "../utils.h"
#ifdef KDDW_HAS_SPDLOG
#include "../fatal_logger.h"
#endif

#include "core/DockWidget.h"
#include "core/DockWidget_p.h"
#include "core/DragController_p.h"
#include "core/Group.h"
#include "core/MainWindow.h"
#include "core/Platform.h"
#include "core/Stack.h"
#include "core/TabBar.h"
#include "core/TitleBar.h"
#include "qtcommon/View.h"

#include <qpa/qplatformwindow_p.h>

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QTabBar>
#include <QTest>
#include <QWidget>

#include <algorithm>

#include <memory>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;
using namespace KDDockWidgets::Tests;
using namespace KDDockWidgets::Tests::Wayland;

namespace {

/// Returns whether QTabBar is showing the floating copy of a tab it shows while reordering.
/// It's a QMovableTabWidget, which has no Q_OBJECT, so look for a plain QWidget child.
bool isShowingMovingTab(QTabBar *tabBar)
{
    const auto children = tabBar->findChildren<QWidget *>(Qt::FindDirectChildrenOnly);
    return std::any_of(children.cbegin(), children.cend(), [](QWidget *child) {
        return child->metaObject() == &QWidget::staticMetaObject && child->isVisible();
    });
}

/// A window, not part of KDDW, which accepts any drop. Like the desktop or another application
/// accepting a drop would.
class DropAcceptingWindow : public QWidget
{
public:
    DropAcceptingWindow()
    {
        setAcceptDrops(true);
        resize(300, 300);
    }

    int numDrops = 0;

protected:
    void dragEnterEvent(QDragEnterEvent *ev) override
    {
        ev->acceptProposedAction();
    }

    void dragMoveEvent(QDragMoveEvent *ev) override
    {
        ev->acceptProposedAction();
    }

    void dropEvent(QDropEvent *ev) override
    {
        ++numDrops;
        ev->acceptProposedAction();
    }
};

wl_surface *surfaceFor(QWidget *widget)
{
    auto waylandWindow = widget->windowHandle()->nativeInterface<QNativeInterface::Private::QWaylandWindow>();
    return waylandWindow ? waylandWindow->surface() : nullptr;
}

}

class TestWayland : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void tst_dragDockWidgetOntoAnother();
    void tst_doubleClickTabDetaches();
    void tst_dragTabToEmptySpaceKeepsItDocked();
    void tst_cancelledTabReorderDragResetsTabBar();
    void tst_tabDroppedOntoForeignWindowResetsTabBar();

private:
    std::unique_ptr<TestInput> m_input;
};

void TestWayland::initTestCase()
{
    if (Platform::instance()->displayType() != Platform::DisplayType::Wayland) {
        QFAIL("tst_wayland needs to run against kddw_test_compositor, don't pass -platform");
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
    if (!Platform::instance()->isQtWidgets())
        QSKIP("Not tested with QtQuick yet");

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
    if (!Platform::instance()->isQtWidgets())
        QSKIP("Not tested with QtQuick yet");

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
    if (!Platform::instance()->isQtWidgets())
        QSKIP("Not tested with QtQuick yet");

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

void TestWayland::tst_cancelledTabReorderDragResetsTabBar()
{
    if (!Platform::instance()->isQtWidgets())
        QSKIP("Not tested with QtQuick yet");

    // Regression test for #762: dragging a tab sideways reorders it within QTabBar, and once past
    // the last tab KDDW starts its drag too. QTabBar never gets the mouse release, which the drag's
    // nested event loop consumes, so after a cancelled drag it stays stuck mid-reorder.

    EnsureTopLevelsDeleted e;
    Config::self().setFlags(Config::self().flags() | Config::Flag_AllowReorderTabs);

    auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));
    m->addDockWidget(dock1, Location_OnLeft);
    dock1->addDockWidgetAsTab(dock2);
    QVERIFY(waitForMapped(m->view()));

    Group *group = dock1->dptr()->group();
    TabBar *tabBar = group->stack()->tabBar();
    auto qtabBar = qobject_cast<QTabBar *>(QtCommon::View_qt::asQWidget(tabBar->view()));
    if (!qtabBar)
        QSKIP("Only for the QtWidgets frontend");
    QVERIFY(!isShowingMovingTab(qtabBar));

    // Drag the first tab right, along the tab bar and past the last tab
    const Point start = tabBar->rectForTab(0).center();
    const Point end(tabBar->rectForTab(1).right() + 50, start.y());
    m_input->moveTo(tabBar->view(), start);
    m_input->press();
    constexpr int steps = 20;
    for (int i = 1; i <= steps; ++i)
        m_input->moveTo(tabBar->view(), start + (end - start) * i / steps);
    m_input->wait_for_drag_start(/*timeout_msecs=*/5000);

    // Release over no window, which cancels the drag
    m_input->moveToAbsolute(Point(1500, 900));
    m_input->release();
    QVERIFY(m_input->commitAndWait());

    QTRY_VERIFY(!DragController::instance()->isDragging());
    QVERIFY(!dock1->isFloating());
    QCOMPARE(group->dockWidgetCount(), 2);

    QVERIFY(!isShowingMovingTab(qtabBar));
}

void TestWayland::tst_tabDroppedOntoForeignWindowResetsTabBar()
{
    if (!Platform::instance()->isQtWidgets())
        QSKIP("Not tested with QtQuick yet");

    // Like tst_cancelledTabReorderDragResetsTabBar, but the tab is dropped onto a window which
    // accepts the drop, like the desktop or another application might. QDrag::exec() then
    // doesn't return Qt::IgnoreAction, which mustn't leave DragController stuck in its dragging
    // state, nor QTabBar stuck mid-reorder (PR #766).

    EnsureTopLevelsDeleted e;
    Config::self().setFlags(Config::self().flags() | Config::Flag_AllowReorderTabs);

    auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));
    m->addDockWidget(dock1, Location_OnLeft);
    dock1->addDockWidgetAsTab(dock2);
    QVERIFY(waitForMapped(m->view()));

    auto foreignWindow = std::make_unique<DropAcceptingWindow>();
    foreignWindow->show();
    QVERIFY(QTest::qWaitForWindowExposed(foreignWindow->windowHandle()));

    // Side by side, so they don't overlap
    m_input->set_window_position(Wayland::surfaceFor(m->view()), 0, 0);
    m_input->set_window_position(surfaceFor(foreignWindow.get()), 850, 0);
    QVERIFY(m_input->commitAndWait());

    Group *group = dock1->dptr()->group();
    TabBar *tabBar = group->stack()->tabBar();
    auto qtabBar = qobject_cast<QTabBar *>(QtCommon::View_qt::asQWidget(tabBar->view()));
    QVERIFY(qtabBar);
    QVERIFY(!isShowingMovingTab(qtabBar));

    // Drag the first tab right, along the tab bar and past the last tab
    const Point start = tabBar->rectForTab(0).center();
    const Point end(tabBar->rectForTab(1).right() + 50, start.y());
    m_input->moveTo(tabBar->view(), start);
    m_input->press();
    constexpr int steps = 20;
    for (int i = 1; i <= steps; ++i)
        m_input->moveTo(tabBar->view(), start + (end - start) * i / steps);
    m_input->wait_for_drag_start(/*timeout_msecs=*/5000);

    // Release over the foreign window, which accepts the drop
    for (int i = 1; i <= steps; ++i)
        m_input->pointer_move(surfaceFor(foreignWindow.get()), wl_fixed_from_int(10 * i), wl_fixed_from_int(10 * i));
    m_input->release();
    QVERIFY(m_input->commitAndWait());

    QTRY_COMPARE(foreignWindow->numDrops, 1);
    QVERIFY(!dock1->isFloating());
    QCOMPARE(group->dockWidgetCount(), 2);

    QTRY_VERIFY(!DragController::instance()->isDragging());
    QVERIFY(!isShowingMovingTab(qtabBar));
}

int main(int argc, char *argv[])
{
    if (!ensureCompositor(KDDW_TEST_COMPOSITOR))
        return 1;

#ifdef KDDW_HAS_SPDLOG
    FatalLogger::create();
#endif

    for (auto frontend : Platform::frontendTypes()) {
        Platform::tests_initPlatform(argc, argv, frontend);
        TestWayland test;
        const int exitCode = QTest::qExec(&test, argc, argv);
        Platform::tests_deinitPlatform();
        if (exitCode != 0)
            return exitCode;
    }

    return 0;
}

#include "tst_wayland.moc"

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

#include "Config.h"
#include "core/DockWidget.h"
#include "core/DockWidget_p.h"
#include "core/DragController_p.h"
#include "core/FloatingWindow.h"
#include "core/Group.h"
#include "core/MainWindow.h"
#include "core/Platform.h"
#include "core/Stack.h"
#include "core/TabBar.h"
#include "core/TitleBar.h"
#include "qtcommon/View.h"
#ifdef KDDW_FRONTEND_QTQUICK
#include "qtquick/views/TabBar.h"
#include "qtquick/views/TitleBar.h"
#endif

#include <qpa/qplatformwindow_p.h>

#include <QDropEvent>
#include <QPainter>
#include <QRasterWindow>
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
/// accepting a drop would. Not a QWidget, as QtQuick doesn't create a QApplication.
class DropAcceptingWindow : public QRasterWindow
{
public:
    DropAcceptingWindow()
    {
        resize(300, 300);
    }

    int numDrops = 0;

protected:
    bool event(QEvent *ev) override
    {
        switch (ev->type()) {
        case QEvent::Drop:
            ++numDrops;
            [[fallthrough]];
        case QEvent::DragEnter:
        case QEvent::DragMove:
            static_cast<QDropEvent *>(ev)->acceptProposedAction();
            return true;
        default:
            return QRasterWindow::event(ev);
        }
    }

    void paintEvent(QPaintEvent *) override
    {
        // Something needs to be drawn for the window to be mapped
        QPainter(this).fillRect(QRect(QPoint(), size()), Qt::white);
    }
};

/// Returns the rect of tab @p index, relative to @p tabBar
Rect tabRect(TabBar *tabBar, int index)
{
#ifdef KDDW_FRONTEND_QTQUICK
    // QtQuick's rectForTab() is relative to the tab, not to the tab bar
    if (auto quickTabBar = dynamic_cast<QtQuick::TabBar *>(tabBar->view())) {
        const Rect globalRect = quickTabBar->globalRectForTab(index);
        return Rect(tabBar->view()->mapFromGlobal(globalRect.topLeft()), globalRect.size());
    }
#endif
    return tabBar->rectForTab(index);
}

/// Returns the center of the tab of @p dw, relative to @p tabBar
Point tabCenter(TabBar *tabBar, DockWidget *dw)
{
    return tabRect(tabBar, tabBar->indexOfDockWidget(dw)).center();
}

/// Returns the QTabBar of @p tabBar, or nullptr with QtQuick
QTabBar *qtabBarFor(TabBar *tabBar)
{
    return qobject_cast<QTabBar *>(QtCommon::View_qt::asQObject(tabBar->view()));
}

/// The drag modes to test. Set KDDW_TEST_DRAG_MODE to "pixmap" or "toplevel" to only run one.
std::vector<bool> dragModes()
{
    const QString mode = qEnvironmentVariable("KDDW_TEST_DRAG_MODE");
    if (mode == QLatin1String("pixmap"))
        return { false };
    if (mode == QLatin1String("toplevel"))
        return { true };
    if (!mode.isEmpty())
        qWarning() << "Unknown KDDW_TEST_DRAG_MODE" << mode << "expected pixmap or toplevel";

    return { false, true };
}

/// Whether the current run asked for Flag_WaylandToplevelDrag. It's ignored without support.
bool s_toplevelDragRequested = false;

/// Returns whether xdg-toplevel-drag can be used. kddw_test_compositor supports it unless told not to.
bool toplevelDragIsSupported()
{
    return !qEnvironmentVariable("KDDW_TEST_COMPOSITOR_ARGS").contains(QLatin1String("--no-toplevel-drag"));
}

/// Returns whether drags use xdg-toplevel-drag, where the dragged window itself moves, instead
/// of a pixmap
bool isToplevelDrag()
{
    return Config::self().flags() & Config::Flag_WaylandToplevelDrag;
}

/// Returns whether @p dw, whose tab was dragged out of @p group and not dropped onto KDDW, is
/// where it should be. With pixmap drags it stays in @p group. With xdg-toplevel-drag it became a
/// floating window as soon as the drag started, and stays one.
bool isWhereUndroppedTabShouldBe(DockWidget *dw, Group *group)
{
    if (isToplevelDrag())
        return dw->isFloating() && dw->dptr()->group() != group;
    return !dw->isFloating() && dw->dptr()->group() == group;
}

/// Returns the center of @p titleBar, relative to its view
Point titleBarCenter(TitleBar *titleBar)
{
#ifdef KDDW_FRONTEND_QTQUICK
    // QtQuick's TitleBar view isn't what's shown, its titleBarQmlItem is
    if (auto quickTitleBar = dynamic_cast<QtQuick::TitleBar *>(titleBar->view())) {
        if (auto item = quickTitleBar->property("titleBarQmlItem").value<QQuickItem *>()) {
            const QPointF center = item->mapToGlobal(item->boundingRect().center());
            return titleBar->view()->mapFromGlobal(center.toPoint());
        }
    }
#endif
    return titleBar->view()->rect().center();
}

wl_surface *surfaceFor(QWindow *window)
{
    auto waylandWindow = window->nativeInterface<QNativeInterface::Private::QWaylandWindow>();
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
    void tst_dragTabToEmptySpace();
    void tst_cancelledTabReorderDragResetsTabBar();
    void tst_tabDroppedOntoForeignWindowResetsTabBar();
    void tst_dragTabOverDropIndicators();
    void tst_dragTabOntoMainWindow();
    void tst_windowPosition();
    void tst_draggedOutTabFollowsPointer();
    void tst_dragFloatingWindowByTitleBar();
    void tst_toplevelDragNeedsSupport();

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

    // With xdg-toplevel-drag dock1 leaves the main window as soon as the drag starts, so dock2
    // takes all of it, and its center moves
    View *dest = isToplevelDrag() ? m->dropArea()->view() : group2->view();
    TitleBar *titleBar = dock1->titleBar();
    m_input->drag(titleBar->view(), titleBarCenter(titleBar), dest, dest->rect().center());
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
    m_input->moveTo(tabBar->view(), tabCenter(tabBar, dock2));
    m_input->doubleClick();
    QVERIFY(m_input->commitAndWait());

    QTRY_VERIFY(dock2->isFloating());
    QVERIFY(!dock1->isFloating());
    QVERIFY(!dock1->isTabbed());
    QVERIFY(dock1->isInMainWindow());
}

void TestWayland::tst_dragTabToEmptySpace()
{
    // Releasing a drag over no window makes the compositor cancel it. With pixmap drags the tab
    // stays put, with xdg-toplevel-drag it stays a floating window

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
    m_input->startDrag(tabBar->view(), tabCenter(tabBar, dock2));
    m_input->moveToAbsolute(Point(1500, 900)); // The main window is at 0,0 and 800x500
    m_input->release();
    QVERIFY(m_input->commitAndWait());

    QTRY_COMPARE(numCanceled, 1);
    QVERIFY(!DragController::instance()->isDragging());
    QVERIFY(isWhereUndroppedTabShouldBe(dock2, group));
    QCOMPARE(group->dockWidgetCount(), isToplevelDrag() ? 1 : 2);
}

void TestWayland::tst_cancelledTabReorderDragResetsTabBar()
{
    // Regression test for #762: dragging a tab sideways reorders it within QTabBar, and once past
    // the last tab KDDW starts its drag too. QTabBar never gets the mouse release, which the drag's
    // nested event loop consumes, so after a cancelled drag it stays stuck mid-reorder.

    if (!Platform::instance()->isQtWidgets())
        QSKIP("QtQuick can't reorder tabs by dragging them");

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
    QTabBar *qtabBar = qtabBarFor(tabBar);
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

    // Release over no window, which cancels the drag
    m_input->moveToAbsolute(Point(1500, 900));
    m_input->release();
    QVERIFY(m_input->commitAndWait());

    QTRY_VERIFY(!DragController::instance()->isDragging());
    QVERIFY(isWhereUndroppedTabShouldBe(dock1, group));
    QCOMPARE(group->dockWidgetCount(), isToplevelDrag() ? 1 : 2);

    QVERIFY(!isShowingMovingTab(qtabBar));
}

void TestWayland::tst_tabDroppedOntoForeignWindowResetsTabBar()
{
    // Like tst_cancelledTabReorderDragResetsTabBar, but the tab is dropped onto a window which
    // accepts the drop, like the desktop or another application might. QDrag::exec() then
    // doesn't return Qt::IgnoreAction, which mustn't leave DragController stuck in its dragging
    // state, nor QTabBar stuck mid-reorder (PR #766).
    // QtQuick can't reorder tabs by dragging them, so there the tab is just dragged off.

    EnsureTopLevelsDeleted e;
    const bool reorderTabs = Platform::instance()->isQtWidgets();
    if (reorderTabs)
        Config::self().setFlags(Config::self().flags() | Config::Flag_AllowReorderTabs);

    auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));
    m->addDockWidget(dock1, Location_OnLeft);
    dock1->addDockWidgetAsTab(dock2);
    QVERIFY(waitForMapped(m->view()));

    auto foreignWindow = std::make_unique<DropAcceptingWindow>();
    foreignWindow->show();
    QVERIFY(QTest::qWaitForWindowExposed(foreignWindow.get()));

    // Side by side, so they don't overlap
    m_input->set_window_position(Wayland::surfaceFor(m->view()), 0, 0);
    m_input->set_window_position(surfaceFor(foreignWindow.get()), 850, 0);
    QVERIFY(m_input->commitAndWait());

    Group *group = dock1->dptr()->group();
    TabBar *tabBar = group->stack()->tabBar();
    QTabBar *qtabBar = qtabBarFor(tabBar);
    QVERIFY(!qtabBar || !isShowingMovingTab(qtabBar));

    constexpr int steps = 20;
    if (reorderTabs) {
        // Drag the first tab right, along the tab bar and past the last tab
        const Point start = tabBar->rectForTab(0).center();
        const Point end(tabBar->rectForTab(1).right() + 50, start.y());
        m_input->moveTo(tabBar->view(), start);
        m_input->press();
        for (int i = 1; i <= steps; ++i)
            m_input->moveTo(tabBar->view(), start + (end - start) * i / steps);
        m_input->wait_for_drag_start(/*timeout_msecs=*/5000);
    } else {
        m_input->startDrag(tabBar->view(), tabCenter(tabBar, dock1));
    }

    // Release over the foreign window, which accepts the drop
    for (int i = 1; i <= steps; ++i)
        m_input->pointer_move(surfaceFor(foreignWindow.get()), wl_fixed_from_int(10 * i), wl_fixed_from_int(10 * i));
    m_input->release();
    QVERIFY(m_input->commitAndWait());

    QTRY_COMPARE(foreignWindow->numDrops, 1);
    QVERIFY(isWhereUndroppedTabShouldBe(dock1, group));
    QCOMPARE(group->dockWidgetCount(), isToplevelDrag() ? 1 : 2);

    QTRY_VERIFY(!DragController::instance()->isDragging());
    QVERIFY(!qtabBar || !isShowingMovingTab(qtabBar));
}

void TestWayland::tst_dragTabOverDropIndicators()
{
    // Drags a tab out of a tab group and over the drop indicators of the group next to it.
    // With QtQuick, WindowBeingDraggedWayland didn't know which dock widget was being dragged,
    // so it had no size, which crashed (PR #783)

    EnsureTopLevelsDeleted e;
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));
    auto dock3 = createDockWidget("dock3", Platform::instance()->tests_createView({ true }));
    dock1->addDockWidgetAsTab(dock2);
    dock1->addDockWidgetToContainingWindow(dock3, Location_OnRight);

    FloatingWindow *fw = dock1->floatingWindow();
    QVERIFY(fw);
    QCOMPARE(dock3->floatingWindow(), fw);
    fw->view()->setSize(800, 500);
    QVERIFY(waitForMapped(fw->view()));

    Group *group3 = dock3->dptr()->group();
    QVERIFY(dock2->dptr()->group() != group3);

    TabBar *tabBar = dock2->dptr()->group()->stack()->tabBar();
    m_input->drag(tabBar->view(), tabCenter(tabBar, dock2), group3->view(), group3->view()->rect().center());
    QVERIFY(m_input->commitAndWait());

    QTRY_VERIFY(!DragController::instance()->isDragging());
    QTRY_COMPARE(dock2->dptr()->group(), group3);
    QCOMPARE(group3->dockWidgetCount(), 2);
}

void TestWayland::tst_dragTabOntoMainWindow()
{
    // Drags a tab out of a floating window and drops it onto a dock widget of a main window.
    // With QtQuick, the main window's drop area didn't receive the drag, as it lacked
    // ItemAcceptsDrops. Floating windows were fine, as they wrap theirs in a QML DropArea.

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));
    auto dock3 = createDockWidget("dock3", Platform::instance()->tests_createView({ true }));
    m->addDockWidget(dock3, Location_OnLeft);
    dock1->addDockWidgetAsTab(dock2);
    FloatingWindow *fw = dock1->floatingWindow();
    QVERIFY(fw);
    fw->view()->setSize(500, 400);
    QVERIFY(waitForMapped(m->view()));
    QVERIFY(waitForMapped(fw->view()));
    m_input->set_window_position(Wayland::surfaceFor(m->view()), 0, 0);
    m_input->set_window_position(Wayland::surfaceFor(fw->view()), 850, 0);
    QVERIFY(m_input->commitAndWait());

    Group *group3 = dock3->dptr()->group();
    TabBar *tabBar = dock2->dptr()->group()->stack()->tabBar();
    m_input->drag(tabBar->view(), tabCenter(tabBar, dock2), group3->view(), group3->view()->rect().center());
    QVERIFY(m_input->commitAndWait());

    QTRY_VERIFY(!DragController::instance()->isDragging());
    QTRY_COMPARE(dock2->dptr()->group(), group3);
    QCOMPARE(group3->dockWidgetCount(), 2);
    QVERIFY(dock2->isInMainWindow());
}

void TestWayland::tst_windowPosition()
{
    // Tests the test harness itself, which tells us where windows are, as Wayland clients can't know

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
    QVERIFY(waitForMapped(m->view()));

    m_input->set_window_position(Wayland::surfaceFor(m->view()), 120, 80);
    QCOMPARE(m_input->windowPosition(m->view()), Point(120, 80));

    m_input->set_window_position(Wayland::surfaceFor(m->view()), 850, 0);
    QCOMPARE(m_input->windowPosition(m->view()), Point(850, 0));
}

void TestWayland::tst_draggedOutTabFollowsPointer()
{
    // With xdg-toplevel-drag a tab dragged out becomes a window which follows the pointer, and
    // stays where it's released. The pointer needs to be over it, even if the tab was further right
    // than the new window is wide.

    if (!isToplevelDrag())
        QSKIP("Only with xdg-toplevel-drag");

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
    auto dock0 = createDockWidget("dock0", Platform::instance()->tests_createView({ true }));
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));
    m->addDockWidget(dock0, Location_OnLeft);
    m->addDockWidget(dock1, Location_OnRight);
    dock1->addDockWidgetAsTab(dock2);
    QVERIFY(waitForMapped(m->view()));
    m_input->set_window_position(Wayland::surfaceFor(m->view()), 0, 0);
    QVERIFY(m_input->commitAndWait());

    TabBar *tabBar = dock2->dptr()->group()->stack()->tabBar();
    m_input->startDrag(tabBar->view(), tabCenter(tabBar, dock2));
    const Point releasePos(1200, 600);
    m_input->moveToAbsolute(releasePos);
    m_input->release();
    QVERIFY(m_input->commitAndWait());

    QTRY_VERIFY(!DragController::instance()->isDragging());
    FloatingWindow *fw = dock2->floatingWindow();
    QVERIFY(fw);

    const std::optional<Point> pos = m_input->windowPosition(fw->view());
    QVERIFY(pos);
    const Rect windowRect(*pos, fw->view()->size());
    QVERIFY2(windowRect.contains(releasePos),
             qPrintable(QStringLiteral("window=%1,%2 %3x%4")
                            .arg(windowRect.x())
                            .arg(windowRect.y())
                            .arg(windowRect.width())
                            .arg(windowRect.height())));
}

void TestWayland::tst_dragFloatingWindowByTitleBar()
{
    // With xdg-toplevel-drag floating windows are moved by dragging KDDW's title bar, there's no
    // native one. The pointer stays where it grabbed the title bar.

    if (!isToplevelDrag())
        QSKIP("Only with xdg-toplevel-drag, otherwise the native title bar moves floating windows");

    EnsureTopLevelsDeleted e;
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    FloatingWindow *fw = dock1->floatingWindow();
    QVERIFY(fw);
    QVERIFY(waitForMapped(fw->view()));
    m_input->set_window_position(Wayland::surfaceFor(fw->view()), 100, 100);
    QVERIFY(m_input->commitAndWait());

    TitleBar *titleBar = fw->titleBar();
    const Point pressPos = titleBarCenter(titleBar);
    const Point pressPosInWindow = mapToSurface(titleBar->view(), pressPos);
    m_input->startDrag(titleBar->view(), pressPos);
    const Point releasePos(700, 500);
    m_input->moveToAbsolute(releasePos);
    m_input->release();
    QVERIFY(m_input->commitAndWait());

    QTRY_VERIFY(!DragController::instance()->isDragging());
    QCOMPARE(dock1->floatingWindow(), fw);
    QCOMPARE(m_input->windowPosition(fw->view()), releasePos - pressPosInWindow);
}

void TestWayland::tst_toplevelDragNeedsSupport()
{
    // Without xdg-toplevel-drag support Flag_WaylandToplevelDrag needs to be ignored. Otherwise
    // the native title bar isn't forced, and floating windows can't be moved.
    // Run with KDDW_TEST_COMPOSITOR_ARGS=--no-toplevel-drag to test that.

    if (!s_toplevelDragRequested)
        QSKIP("Only when Flag_WaylandToplevelDrag is set");

    const bool supported = toplevelDragIsSupported();
    if (!supported)
        QEXPECT_FAIL("", "Flag_WaylandToplevelDrag is used even if the compositor lacks support", Abort);
    QCOMPARE(isToplevelDrag(), supported);
    QCOMPARE(bool(Config::self().flags() & Config::Flag_NativeTitleBar), !supported);
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
        for (const bool toplevelDrag : dragModes()) {
            Config::Flags flags = Config::Flag_Default;
            if (toplevelDrag)
                flags |= Config::Flag_WaylandToplevelDrag;
            Config::self().setFlags(flags);
            s_toplevelDragRequested = toplevelDrag;

            qInfo().noquote() << "Using" << (isToplevelDrag() ? "xdg-toplevel-drag" : "pixmap drags");
            TestWayland test;
            const int exitCode = QTest::qExec(&test, argc, argv);
            if (exitCode != 0)
                return exitCode;
        }
        Platform::tests_deinitPlatform();
    }

    return 0;
}

#include "tst_wayland.moc"

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/// @file
/// @brief Here lives the tests that only apply to QtWidgets
/// either because they haven't been ported to QtQuick yet or because they are really
/// QtWidgets specific.

#define NOMINMAX

#include "kddockwidgets/KDDockWidgets.h"
#include "../utils.h"
#include "Config.h"
#include "LayoutSaver.h"
#include "core/Logging_p.h"
#include "core/DragController_p.h"
#include "core/layouting/Item_p.h"
#include "core/layouting/LayoutingSeparator_p.h"
#include "core/WindowBeingDragged_p.h"

#include "qtwidgets/ViewFactory.h"
#include "core/LayoutSaver_p.h"
#include "core/Platform.h"
#include "core/Action_p.h"
#include "core/DropArea.h"
#include "core/Separator.h"
#include "core/Group.h"
#include "core/DockWidget.h"
#include "core/MainWindow.h"
#include "core/SideBar.h"

#include "qtwidgets/views/MDIArea.h"
#include "qtwidgets/views/Stack.h"
#include "qtwidgets/views/MainWindow.h"
#include "qtwidgets/views/ViewWrapper_p.h"
#include "qtwidgets/views/DockWidget.h"
#include "qtwidgets/views/TitleBar.h"
#include "qtcommon/View.h"

#include "ui_mainwindow.h"

#ifdef KDDW_HAS_SPDLOG
#include "../fatal_logger.h"
#endif

#include "../src/qtwidgets/DebugWidgetViewer_p.h"

#include <QObject>
#include <QPushButton>
#include <QMenuBar>
#include <QTabBar>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLineEdit>
#include <QGraphicsProxyWidget>
#include <QtTest/QTest>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;
using namespace KDDockWidgets::Tests;

namespace {

// For testing overriding DockWidget::closeEvent()
// You can override the guest's closeEvent() instead. That's already tested elsewhere.
class NonClosableDockWidget : public QtWidgets::DockWidget
{
public:
    using QtWidgets::DockWidget::DockWidget;
    void closeEvent(QCloseEvent *ev) override
    {
        ev->ignore();
    }
};

}

inline Core::DockWidget *createDockWidget(const QString &name, QWidget *w,
                                          DockWidgetOptions options = {},
                                          LayoutSaverOptions layoutSaverOptions = {},
                                          bool show = true, const QString &affinityName = {})
{
    w->setFocusPolicy(Qt::StrongFocus);
    auto dock = newDockWidget(name, options, layoutSaverOptions);
    dock->setAffinityName(affinityName);
    dock->setGuestView(QtWidgets::ViewWrapper::create(w));
    dock->setObjectName(name);
    dock->view()->setGeometry(QRect(0, 0, 400, 400));
    if (show) {
        dock->open();
        dock->dptr()->morphIntoFloatingWindow();
        dock->view()->activateWindow();
        Q_ASSERT(dock->window());
        if (Platform::instance()->tests_waitForWindowActive(dock->view()->window(), 1000)) {
            return dock;
        }
        KDDW_WARN("KDDockWidgets::Tests::createDockWidget: Couldn't activate window");
        return nullptr;
    } else {
        return dock;
    }
}

class EmbeddedWindow : public QWidget
{
public:
    explicit EmbeddedWindow(Core::MainWindow *m)
        : mainWindow(m)
    {
    }

    ~EmbeddedWindow() override;

    Core::MainWindow *const mainWindow;
};
EmbeddedWindow::~EmbeddedWindow() = default;


inline EmbeddedWindow *createEmbeddedMainWindow(QSize sz)
{
    // Tests a MainWindow which isn't a top-level window, but is embedded in another window
    auto mainwindow = createMainWindow(QSize(600, 600), MainWindowOption_HasCentralGroup).release();

    auto window = new EmbeddedWindow(mainwindow);

    auto lay = new QVBoxLayout(window);
    lay->setContentsMargins(100, 100, 100, 100);
    lay->addWidget(dynamic_cast<QWidget *>(mainwindow->view()));

    window->show();
    window->resize(sz);
    return window;
}

class TestQtWidgets : public QObject
{
    Q_OBJECT

public Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

private Q_SLOTS:
    // TODO: Port these to QtQuick
    void tst_mainWindowAlwaysHasCentralWidget();
    void tst_dockableMainWindows();
    void tst_mdi_mixed_with_docking();
    void tst_mdi_mixed_with_docking2();
    void tst_mdi_mixed_with_docking_setMDISize();
    void tst_deleteOnClose();
    void tstCloseNestedMdi();
    void tstCloseNestedMDIPropagates();
    void tstQGraphicsProxyWidget();

    // But these are fine to be widget only:
    void tst_controllerToView();
    void tst_designerMainWindow();
    void tst_tabsNotClickable();
    void tst_embeddedMainWindow();
    void tst_restoreEmbeddedMainWindow();
    void tst_negativeAnchorPositionWhenEmbedded();
    void tst_negativeAnchorPositionWhenEmbedded_data();
    void tst_closeRemovesFromSideBar();
    void tst_sideBarHidden();
    void tst_restoreSideBar();
    void tst_restoreSideBar2();
    void tst_toggleActionOnSideBar();
    void tst_deleteOnCloseWhenOnSideBar();
    void tst_openWhenOnSideBar();
    void tst_isOpenSideBar();
    void tst_sidebarOverlayShowsAutohide();
    void tst_sidebarOverlayGetsHiddenOnClick();
    void tst_sidebarGrouping();
    void tst_sidebarCrash();
    void tst_sidebarCrash2();
    void tst_sidebarCloseReason();
    void tst_sidebarSide();
    void tst_floatRemovesFromSideBar();
    void tst_overlayedGeometryIsSaved();
    void tst_overlayCrash();
    void tst_setAsCurrentTab();
    void tst_crash326();
    void tst_restoreWithIncompleteFactory();
    void tst_deleteDockWidget();
    void tst_standaloneTitleBar();
    void tst_titleBarTitle();
    void tst_widgetAddQAction();
    void tst_currentTabChanged();
    void tst_moveTab();
    void tst_moveTab_data();
    void tst_nestedMainWindowToggle();
    void tst_nestedMainWindowFloatButton();
    void tst_nestedMainWindowSaveRestore_data();
    void tst_nestedMainWindowSaveRestore();
    void tst_focusBetweenTabs();
    void addDockWidgetToSide();
    void addDockWidgetToSide2();
    void addDockWidgetToSide3();
    void addDockWidgetToSide4();
    void addDockWidgetToSide5();
    void addDockWidgetToSideCrash();
    void userHiddenButton();
    void tst_tabAsCentralWidget();
    void tst_nonClosable();
    void tst_crashDuringRestore();
    void tst_toggleVsShowHidden();
    void tst_indicatorsNotShowing();
    void tst_neighbourSqueezeStrategy();
    void tst_tabBarIcons();
    void tst_debugWidgetViewer();
    void tst_addDockWidgetToContainingWindowNested();
    void tst_restoreInvalidPercentages();

    // And fix these
    void tst_floatingWindowDeleted();
    void tst_addToSmallMainWindow6();
    void tst_minSizeChanges();
    void tst_maxSizePropagates();
    void tst_maxSizePropagates2();
    void tst_maxSizedFloatingWindow();
    void tst_restoreWithRemapping();
    void tst_restoreResizesLayout();
    void tst_restoreNonRelativeFloatingWindowGeometry();
    void tst_maxSizeHonouredWhenDropped();
    void tst_fixedSizePolicy();
    void tst_maxSizeHonouredWhenAnotherDropped();
    void tst_addToHiddenMainWindow();
    void tst_maximumSizePolicy();
    void tst_complex();
    void tst_restoreFloatingMaximizedState();
    void tst_findAncestor();
};

void TestQtWidgets::tst_designerMainWindow()
{
    // Tests that a KDDW main window doesn't crash if the user used setupUI() on it.
    // setupUI() triggers a QMainWindow::setCentralWidget() call which overrides KDDW's own central widget
    // solution is for KDDW users to call manualInit() later

    EnsureTopLevelsDeleted e;
    QtWidgets::MainWindow mw("mw1", MainWindowOptions(MainWindowOption_HasCentralWidget) | MainWindowOption_ManualInit);
    auto dock1 = createDockWidget("dock1", new QWidget());
    mw.show();

    QVERIFY(!mw.centralWidget());

    Ui_MainWindow ui; // autogenerated by mainwindow.ui
    ui.setupUi(&mw);

    QVERIFY(mw.centralWidget()->objectName() != "MyCentralWidget");
    mw.manualInit();
    QCOMPARE(mw.centralWidget()->objectName(), "MyCentralWidget");

    mw.mainWindow()->addDockWidget(dock1, KDDockWidgets::Location_OnRight);
    QTest::qWait(1);
    QVERIFY(dock1->isVisible());
}

void TestQtWidgets::tst_tabsNotClickable()
{
    // Well, not a great unit-test, as it's only repro when it's Windows sending the native event
    // Can't repro with fabricated events. Uncomment the WAIT and test different configs manually
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(
        KDDockWidgets::Config::Flag_Default
        | KDDockWidgets::Config::Flag_HideTitleBarWhenTabsVisible);

    auto dock1 = createDockWidget("dock1", new QWidget());
    auto dock2 = createDockWidget("dock2", new QWidget());
    dock1->addDockWidgetAsTab(dock2);

    auto group = dock1->dptr()->group();
    QCOMPARE(group->currentIndex(), 1);

    QTest::qWait(500); // wait for window to get proper geometry

    const QPoint clickPoint = group->tabBar()->mapToGlobal(group->tabBar()->rectForTab(0).center());
    QCursor::setPos(clickPoint); // Just for visual debug when needed

    pressOn(clickPoint, group->tabBar()->view());
    releaseOn(clickPoint, group->tabBar()->view());

    // WAIT // Uncomment for MANUAL test. Also test by adding Flag_AlwaysShowTabs

    QCOMPARE(group->currentIndex(), 0);
}

void TestQtWidgets::tst_mainWindowAlwaysHasCentralWidget()
{
    EnsureTopLevelsDeleted e;

    auto m = createMainWindow();

    QWidget *central = dynamic_cast<QtWidgets::MainWindow *>(m->view())->centralWidget();
    auto dropArea = m->dropArea();
    QVERIFY(dropArea);

    ObjectGuard<Core::Group> centralGroup = Group::fromItem(dropArea->centralFrame());
    QVERIFY(central);
    QVERIFY(dropArea);
    QCOMPARE(dropArea->count(), 1);
    QVERIFY(centralGroup);
    QCOMPARE(centralGroup->dockWidgetCount(), 0);

    // Add a tab
    auto dock = createDockWidget("doc1");
    m->addDockWidgetAsTab(dock);
    QCOMPARE(dropArea->count(), 1);
    QCOMPARE(centralGroup->dockWidgetCount(), 1);

    // Detach tab
    QPoint globalPressPos = dragPointForWidget(centralGroup.data(), 0);
    auto tabBar = centralGroup->tabBar()->view();
    QVERIFY(tabBar);
    drag(tabBar, globalPressPos, m->geometry().bottomRight() + QPoint(30, 30));

    QVERIFY(centralGroup);
    QCOMPARE(dropArea->count(), 1);
    QCOMPARE(centralGroup->dockWidgetCount(), 0);
    QVERIFY(dropArea->checkSanity());
}

void TestQtWidgets::tst_dockableMainWindows()
{
    EnsureTopLevelsDeleted e;

    auto m1 = createMainWindow();
    auto dock1 = createDockWidget("dock1", new QPushButton("foo"));
    m1->addDockWidget(dock1, Location_OnTop);

    auto m2 = new KDDockWidgets::QtWidgets::MainWindow("mainwindow-dockable");
    auto m2Container = createDockWidget("mainwindow-dw", ( View * )m2);
    auto menubar = m2->menuBar();
    menubar->addMenu("File");
    menubar->addMenu("View");
    menubar->addMenu("Help");
    m2Container->open();

    auto dock21 = createDockWidget("dock21", new QPushButton("foo"));
    auto dock22 = createDockWidget("dock22", new QPushButton("foo"));
    m2->mainWindow()->addDockWidget(dock21, Location_OnLeft);
    m2->mainWindow()->addDockWidget(dock22, Location_OnRight);

    auto fw = m2Container->floatingWindow();
    Core::TitleBar *fwTitleBar = fw->titleBar();

    QVERIFY(fw->hasSingleGroup());
    QVERIFY(fw->hasSingleDockWidget());

    // Check that the inner-inner dock widgets have a visible title-bar
    QVERIFY(dock21->titleBar()->isVisible());
    QVERIFY(dock22->titleBar()->isVisible());
    QVERIFY(dock21->titleBar() != fwTitleBar);
    QVERIFY(dock22->titleBar() != fwTitleBar);

    const QPoint startPoint = fwTitleBar->mapToGlobal(QPoint(5, 5));
    const QPoint destination = startPoint + QPoint(20, 20);

    // Check that we don't get the "Refusing to itself" warning. not actually dropping anywhere
    drag(fwTitleBar->view(), startPoint, destination);

    // The FloatingWindow has a single DockWidget, so it shows the title bar, while the Frame
    // doesn't
    QVERIFY(fwTitleBar->isVisible());
    QVERIFY(!m2Container->dptr()->group()->titleBar()->isVisible());

    fw->dropArea()->addDockWidget(dock1, Location::Location_OnLeft, nullptr);
    // Now the FloatingWindow has two dock widgets, so our main window dock widget also shows the
    // title bar
    QVERIFY(fwTitleBar->isVisible());
    QVERIFY(m2Container->dptr()->group()->titleBar()->isVisible());

    // Put it how it was, FloatingWindow is single dock again
    auto group1 = dock1->dptr()->group();
    dock1->close();
    Platform::instance()->tests_waitForDeleted(group1);
    QVERIFY(fwTitleBar->isVisible());
    QVERIFY(!m2Container->dptr()->group()->titleBar()->isVisible());

    // Repeat, but instead of closing dock1, we float it
    fw->dropArea()->addDockWidget(dock1, Location::Location_OnLeft, nullptr);
    QVERIFY(fwTitleBar->isVisible());
    QVERIFY(m2Container->dptr()->group()->titleBar()->isVisible());
    group1 = dock1->dptr()->group();
    group1->titleBar()->onFloatClicked();
    QVERIFY(fwTitleBar->isVisible());

    QVERIFY(!m2Container->dptr()->group()->titleBar()->isVisible());

    fw->dropArea()->addDockWidget(dock1, Location::Location_OnLeft, nullptr);
}

void TestQtWidgets::tst_mdi_mixed_with_docking()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(500, 500), MainWindowOption_HasCentralWidget);
    auto dock1 = createDockWidget("1", new QPushButton("1"));

    m->addDockWidget(dock1, Location_OnBottom);

    auto mdiArea = new QtWidgets::MDIArea();
    m->setPersistentCentralView(QtWidgets::ViewWrapper::create(mdiArea));

    auto mdiWidget1 = createDockWidget("mdi1", new QPushButton("mdi1"));
    auto mdiWidget2 = createDockWidget("mdi2", new QPushButton("mdi12"));

    mdiArea->addDockWidget(mdiWidget1, QPoint(10, 10));
    mdiArea->addDockWidget(mdiWidget2, QPoint(50, 50));


    // We don't support LayoutSaver with mdi yet, but it shouldn't crash
    // so test it as well
    LayoutSaver saver;
    saver.serializeLayout();

    Core::Group *groupMDI1 = mdiWidget1->d->group();
    Core::Group *group1 = dock1->d->group();
    QVERIFY(!group1->isMDI());
    QVERIFY(groupMDI1->isMDI());
    QVERIFY(!group1->mdiLayout());
    QVERIFY(groupMDI1->mdiLayout());

    QVERIFY(!dock1->titleBar()->isMDI());

    auto tb1 = mdiWidget1->titleBar();
    QVERIFY(tb1->isMDI());
    QVERIFY(Platform::instance()->tests_waitForEvent(tb1->view(), QEvent::Show));
    QVERIFY(tb1->isVisible());

    // Press the float button
    tb1->onFloatClicked();

    QVERIFY(mdiWidget1->d->lastPosition()->lastItem());
    QVERIFY(mdiWidget1->titleBar()->isVisible());
    QVERIFY(mdiWidget1->isFloating());

    // Dock again, and check it went back
    mdiWidget1->titleBar()->onFloatClicked();
    QVERIFY(!mdiWidget1->isFloating());
}

void TestQtWidgets::tst_mdi_mixed_with_docking2()
{
    // Here, the MDI dock widgets are themselves main windows which will show drop-indicators.
    // It will be super nested: MainWindow -> MDI -> MainWindow

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(1000, 500), MainWindowOption_HasCentralWidget);
    auto dock1 = createDockWidget("1", new QPushButton("1"));

    m->addDockWidget(dock1, Location_OnBottom);

    auto mdiArea = new QtWidgets::MDIArea();

    m->setPersistentCentralView(QtWidgets::ViewWrapper::create(mdiArea));


    auto createSheet = [](int id) -> Core::DockWidget * {
        auto dock =
            newDockWidget(QStringLiteral("dw-sheet-%1").arg(id), DockWidgetOption_MDINestable);
        auto btn = new QPushButton(QStringLiteral("Sheet %1").arg(id));
        dock->setGuestView(QtWidgets::ViewWrapper::create(btn));
        dock->setTitle(QStringLiteral("Sheet %1").arg(id));

        return dock;
    };

    auto mdiWidget1 = createSheet(1);
    auto mdiWidget2 = createSheet(2);
    auto mdiWidget3 = createSheet(3);
    /*auto mdiWidget4 = createSheet(4);
    auto mdiWidget5 = createSheet(5);
    auto mdiWidget6 = createSheet(6);*/


    mdiArea->addDockWidget(mdiWidget1, QPoint(10, 10));
    mdiArea->addDockWidget(mdiWidget2, QPoint(50, 50));

    Core::Group *group1 = mdiWidget1->d->group();
    Core::Group *mdiFrame1 = group1->mdiFrame();

    ObjectGuard<Core::Group> group2 = mdiWidget2->d->group();
    ObjectGuard<Core::Group> mdiFrame2 = group2->mdiFrame();
    ObjectGuard<DropArea> dropArea2 = group2->mdiDropAreaWrapper();

    ObjectGuard<DropArea> dropArea1 = group1->mdiDropAreaWrapper();
    dropArea1->addDockWidget(mdiWidget3, Location_OnLeft, nullptr);

    QVERIFY(!group1->isMDI());
    QVERIFY(group1->isMDIWrapper());
    QVERIFY(group1->mdiDockWidgetWrapper());
    QVERIFY(dropArea1->isMDIWrapper());
    QVERIFY(dropArea2->isMDIWrapper());
    QVERIFY(!mdiFrame1->isMDIWrapper());
    QVERIFY(mdiFrame1->isMDI());
    QVERIFY(!mdiWidget1->d->isMDIWrapper());

    // Test title bars:

    auto tb1 = mdiWidget1->titleBar();
    auto mdiTb1 = mdiFrame1->titleBar();
    auto mdiTb2 = mdiFrame2->titleBar();

    Platform::instance()->tests_waitForEvent(mdiTb1, QEvent::Show);

    QVERIFY(mdiTb1->isVisible());
    QVERIFY(mdiTb2->isVisible());
    QVERIFY(tb1->isVisible());
    QCOMPARE(tb1->title(), QString("Sheet 1"));
    QCOMPARE(mdiTb1->title(), QString("dockwidgets-unit-tests"));
    QCOMPARE(mdiTb2->title(), QString("Sheet 2"));

    QVERIFY(tb1 != mdiTb1);
    QCOMPARE(mdiWidget2->titleBar(), mdiTb2);

    // Test that closing will delete the wrappers:
    mdiWidget2->close();
    QVERIFY(!mdiWidget2->isOpen());

    Platform::instance()->tests_waitForDeleted(dropArea2);
    QVERIFY(dropArea2.isNull());
    QVERIFY(Platform::instance()->tests_waitForDeleted(mdiFrame2));
    QVERIFY(!mdiFrame2);

    mdiWidget1->close();
    QVERIFY(!mdiWidget1->isOpen());
    QTest::qWait(500); // wait some event loops to make sure there's no delete later. (There isn't,
                       // but a bug could introduce them)
    QVERIFY(!dropArea1.isNull()); // Not deleted, as sheet3 is still there
    QCOMPARE(dropArea1->visibleCount(), 1);
    QVERIFY(mdiTb1->isVisible());
    QCOMPARE(mdiWidget3->titleBar(), mdiTb1);
    Core::Group *group3 = mdiWidget3->d->group();
    QVERIFY(!group3->titleBar()->isVisible());

    mdiWidget3->close();
    QVERIFY(Platform::instance()->tests_waitForDeleted(dropArea1));
    QVERIFY(!mdiWidget3->isOpen());
    QVERIFY(dropArea1.isNull());

    // Reopen everything again:

    mdiArea->addDockWidget(mdiWidget1, QPoint(10, 10));
    mdiArea->addDockWidget(mdiWidget2, QPoint(50, 50));
    group1 = mdiWidget1->d->group();
    mdiFrame1 = group1->mdiFrame();
    dropArea1 = group1->mdiDropAreaWrapper();
    dropArea1->addDockWidget(mdiWidget3, Location_OnLeft, nullptr);

    // Test floating:
    group2 = mdiWidget2->d->group();
    ObjectGuard<Core::DockWidget> dwWrapper2 = group2->mdiDockWidgetWrapper();
    dropArea2 = group2->mdiDropAreaWrapper();
    QVERIFY(mdiWidget2->isVisible());
    QVERIFY(group2->isMDIWrapper());
    QVERIFY(dwWrapper2->d->isMDIWrapper());
    mdiFrame2 = group2->mdiFrame();
    mdiWidget2->setFloating(true);
    QVERIFY(mdiWidget2->isFloating());

    QVERIFY(!mdiWidget2->d->group()->isMDI());
    QVERIFY(!mdiWidget2->d->group()->isMDIWrapper());
    QVERIFY(Platform::instance()->tests_waitForDeleted(mdiFrame2));

    QVERIFY(dropArea2.isNull());
    QVERIFY(dwWrapper2.isNull());

    auto mdiFrames = mdiArea->groups();
    QCOMPARE(mdiFrames.count(), 1);
    mdiFrame1 = mdiFrames.first();
    QVERIFY(mdiFrame1->isMDI());
    QVERIFY(mdiFrame1->hasNestedMDIDockWidgets());
    auto mdiTitleBar1 = mdiFrame1->titleBar();
    QVERIFY(mdiFrame1->titleBar()->isVisible());
    mdiTitleBar1->makeWindow();

    QVERIFY(Platform::instance()->tests_waitForDeleted(mdiFrame1));
    QCOMPARE(mdiArea->groups().size(), 0);

    // Dock again:
    mdiArea->addDockWidget(mdiWidget1, QPoint(10, 10));
    mdiArea->addDockWidget(mdiWidget2, QPoint(50, 50));

    group1 = mdiWidget1->d->group();
    dropArea1 = group1->mdiDropAreaWrapper();
    dropArea1->addDockWidget(mdiWidget3, Location_OnLeft, nullptr);

    // Detach an internal dock widget by dragging
    const QPoint globalSrc = mdiWidget1->mapToGlobal(QPoint(5, 5));
    const QPoint globalDest = globalSrc + QPoint(100, 100);

    drag(mdiWidget1->view(), globalDest);

    QCOMPARE(mdiArea->groups().count(), 2);
    auto mdiTitleBar = mdiArea->groups().first()->titleBar();
    QVERIFY(mdiTitleBar->isVisible());

    QVERIFY(!mdiWidget3->isFloating());
    QVERIFY(mdiWidget3->d->lastPosition()->lastItem());
    mdiTitleBar->onFloatClicked();
    QVERIFY(mdiWidget3->isFloating());

    QVERIFY(Platform::instance()->tests_waitForDeleted(mdiArea->groups().constFirst()));
    QCOMPARE(mdiArea->groups().size(), 1);

    QVERIFY(!mdiWidget2->isFloating());
    Core::Group *lastMdiFrame = mdiArea->groups().constFirst();
    QVERIFY(lastMdiFrame->titleBar()->isVisible());
    QVERIFY(!lastMdiFrame->titleBar()->isFloating());
    lastMdiFrame->titleBar()->onFloatClicked();
    QVERIFY(mdiWidget2->isFloating());

    // put it in the MDI area again
    mdiWidget2->titleBar()->onFloatClicked();
    QVERIFY(!mdiWidget2->isFloating());
}

void TestQtWidgets::tst_mdi_mixed_with_docking_setMDISize()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(1000, 500), MainWindowOption_HasCentralWidget);
    auto dock1 = createDockWidget("1", new QPushButton("1"));

    m->addDockWidget(dock1, Location_OnBottom);

    auto mdiArea = new QtWidgets::MDIArea();
    m->setPersistentCentralView(QtWidgets::ViewWrapper::create(mdiArea));

    auto createSheet = [](int id) -> Core::DockWidget * {
        auto dock =
            newDockWidget(QStringLiteral("dw-sheet-%1").arg(id), DockWidgetOption_MDINestable);
        dock->setGuestView(QtWidgets::ViewWrapper::create(
            new QPushButton(QStringLiteral("Sheet %1").arg(id))));
        dock->setTitle(QStringLiteral("Sheet %1").arg(id));

        return dock;
    };

    auto mdiWidget1 = createSheet(1);
    auto mdiWidget2 = createSheet(2);

    mdiArea->addDockWidget(mdiWidget1, QPoint(10, 10));
    mdiArea->addDockWidget(mdiWidget2, QPoint(50, 50));

    Core::Group *group1 = mdiArea->groups().at(0);

    const QSize sz1 = group1->view()->size();
    const QSize increment(200, 200);

    QVERIFY(mdiWidget1->d->mdiLayout());
    mdiWidget1->setMDISize(sz1 + increment);

    QCOMPARE(group1->size(), sz1 + increment);
}

// No need to port to QtQuick
void TestQtWidgets::tst_floatingWindowDeleted()
{
    // Tests a case where the empty floating dock widget wouldn't be deleted
    // Doesn't repro QTBUG-83030 unfortunately, as we already have an event loop running
    // but let's leave this here nonetheless
    class MyMainWindow : public KDDockWidgets::QtWidgets::MainWindow
    {
    public:
        MyMainWindow()
            : KDDockWidgets::QtWidgets::MainWindow("tst_floatingWindowDeleted",
                                                   MainWindowOption_None)
        {
            auto dock1 = newDockWidget(QStringLiteral("DockWidget #1"));
            auto myWidget = new QWidget();
            dock1->setGuestView(QtWidgets::ViewWrapper::create((myWidget)));
            dock1->view()->resize(QSize(600, 600));
            dock1->open();

            auto dock2 = newDockWidget(QStringLiteral("DockWidget #2"));
            myWidget = new QWidget();
            dock2->setGuestView(QtWidgets::ViewWrapper::create(myWidget));
            dock2->view()->resize(QSize(600, 600));
            dock2->open();

            dock1->addDockWidgetAsTab(dock2);
        }
    };

    MyMainWindow m;
}

void TestQtWidgets::tst_addToSmallMainWindow6()
{
    EnsureTopLevelsDeleted e;
    // Test test shouldn't spit any warnings

    QWidget container;
    auto lay = new QVBoxLayout(&container);
    auto m = Platform::instance()->createMainWindow("MyMainWindow_tst_addToSmallMainWindow8", {},
                                                    MainWindowOption_None);
    auto qmainwindow = dynamic_cast<QtWidgets::MainWindow *>(m->view());
    lay->addWidget(qmainwindow);
    container.resize(100, 100);
    Platform::instance()->tests_waitForEvent(&container, QEvent::Resize);
    container.show();
    Platform::instance()->tests_waitForResize(m);
    auto dock1 = createDockWidget(
        "dock1", Platform::instance()->tests_createView({ true, {}, QSize(50, 240) }));
    auto dock2 = createDockWidget(
        "dock2", Platform::instance()->tests_createView({ true, {}, QSize(50, 240) }));
    m->addDockWidget(dock1, KDDockWidgets::Location_OnBottom);
    m->addDockWidget(dock2, KDDockWidgets::Location_OnBottom);
    Platform::instance()->tests_waitForResize(m);
    QVERIFY(m->dropArea()->checkSanity());
    delete m;
}

void TestQtWidgets::tst_sideBarHidden()
{
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_AutoHideSupport);
    auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None);
    auto dw1 = newDockWidget(QStringLiteral("1"));
    m1->addDockWidget(dw1, Location_OnBottom);

    auto sb = m1->sideBar(SideBarLocation::South);
    QVERIFY(sb);
    QVERIFY(sb->isEmpty());
    QVERIFY(!sb->isVisible());

    m1->moveToSideBar(dw1);
    QVERIFY(!sb->isEmpty());
    QVERIFY(sb->isVisible());
}

void TestQtWidgets::tst_closeRemovesFromSideBar()
{
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_AutoHideSupport);
    auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None);
    auto dw1 = newDockWidget(QStringLiteral("1"));
    auto fw1 = dw1->window();
    m1->addDockWidget(dw1, Location_OnBottom);
    m1->moveToSideBar(dw1);

    QVERIFY(!dw1->isOverlayed());
    QVERIFY(!dw1->isVisible());
    QVERIFY(dw1->isInSideBar());

    Core::SideBar *sb = m1->sideBarForDockWidget(dw1);
    QVERIFY(sb);

    // Overlay it:
    sb->toggleOverlay(dw1);
    QVERIFY(dw1->isOverlayed());
    QVERIFY(dw1->isVisible());
    QCOMPARE(dw1->sideBarLocation(), sb->location());
    QVERIFY(dw1->isInMainWindow());
    QVERIFY(!dw1->isFloating());

    // Close it while it's overlayed:
    dw1->close();
    QVERIFY(!dw1->isInMainWindow());
    QVERIFY(!dw1->isOverlayed());
    QVERIFY(!dw1->isVisible());
    QCOMPARE(dw1->sideBarLocation(), SideBarLocation::None);
}

void TestQtWidgets::tst_restoreSideBar()
{
    SideBarLocation loc;
    QByteArray serialized; // serialization after having 1 sidebar visible
    QByteArray beforeSideBarSerialized; // serialization without any sidebar visible

    {
        LayoutSaver saver;
        EnsureTopLevelsDeleted e;
        KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_AutoHideSupport);
        auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None, "MW1");
        auto dw1 = newDockWidget(QStringLiteral("1"));
        auto fw1 = dw1->window();
        m1->addDockWidget(dw1, Location_OnBottom);
        beforeSideBarSerialized = saver.serializeLayout();
        QVERIFY(!m1->anySideBarIsVisible());
        m1->moveToSideBar(dw1);
        QVERIFY(m1->anySideBarIsVisible());

        QVERIFY(!dw1->isOverlayed());
        QVERIFY(!dw1->isVisible());
        loc = dw1->sideBarLocation();
        QVERIFY(loc != SideBarLocation::None);

        serialized = saver.serializeLayout();

        m1.reset();
    }

    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_AutoHideSupport);
    auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None, "MW1");
    auto dw1 = newDockWidget(QStringLiteral("1"));
    auto fw1 = dw1->window();
    m1->addDockWidget(dw1, Location_OnBottom);
    QVERIFY(!m1->anySideBarIsVisible());
    QVERIFY(!dw1->isOverlayed());
    QVERIFY(dw1->isVisible());
    QVERIFY(!dw1->isFloating());
    QVERIFY(dw1->isInMainWindow());

    LayoutSaver restorer;
    restorer.restoreLayout(serialized);

    QVERIFY(!dw1->isOverlayed());
    QVERIFY(!dw1->isVisible());
    QVERIFY(!dw1->isInMainWindow());
    QVERIFY(m1->anySideBarIsVisible());

    QCOMPARE(loc, dw1->sideBarLocation());

    restorer.restoreLayout(beforeSideBarSerialized);
    QVERIFY(!dw1->isOverlayed());
    QVERIFY(dw1->isVisible());
    QVERIFY(!dw1->isFloating());
    QVERIFY(dw1->isInMainWindow());
    QVERIFY(!m1->anySideBarIsVisible());

    QCOMPARE(LayoutSaver::sideBarDockWidgetsInLayout(serialized), { "1" });
}

void TestQtWidgets::tst_restoreSideBar2()
{
    // Tests a case where the layout size would be bigger than the parent DropArea
    EnsureTopLevelsDeleted e;

    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_AutoHideSupport);
    KDDockWidgets::QtWidgets::MainWindow m1("MyMainWindow");
    m1.resize(QSize(1197, 1197));

    auto dw1 = new KDDockWidgets::QtWidgets::DockWidget(
        QStringLiteral("DockWidget #0"));
    auto dw2 = new KDDockWidgets::QtWidgets::DockWidget(
        QStringLiteral("DockWidget #1"));
    auto dw3 = new KDDockWidgets::QtWidgets::DockWidget(
        QStringLiteral("DockWidget #2"));
    m1.addDockWidget(dw1, KDDockWidgets::Location_OnTop);
    m1.addDockWidget(dw2, KDDockWidgets::Location_OnRight, dw1);
    m1.addDockWidget(dw3, KDDockWidgets::Location_OnLeft);
    m1.show();
    auto layout = m1.mainWindow()->layout();
    QCOMPARE(layout->size().width(), layout->layoutSize().width());
    QCOMPARE(layout->size().height(), layout->layoutSize().height());

    LayoutSaver saver;
    saver.restoreFromFile(":/layouts/sidebar_restore.json");

    QVERIFY(dw1->isOpen());
    QVERIFY(!dw2->isOpen());
    QVERIFY(dw3->dockWidget()->isInSideBar());
    QVERIFY(layout->checkSanity());

    QCOMPARE(layout->size(), layout->layoutSize());
}

void TestQtWidgets::tst_openWhenOnSideBar()
{
    // Calling DW::open() when on sidebar should open it in its previous docked position
    // and remove it from overlay

    {
        EnsureTopLevelsDeleted e;

        KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_AutoHideSupport);
        auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None, "MW1");
        auto dw1 = newDockWidget("1");
        m1->addDockWidget(dw1, Location_OnBottom);
        dw1->moveToSideBar();
        QTest::qWait(100);

        QVERIFY(!m1->overlayedDockWidget());
        QVERIFY(m1->anySideBarIsVisible());

        QVERIFY(!dw1->dptr()->m_lastPositions->wasFloating());
        dw1->open();

        QVERIFY(!m1->overlayedDockWidget());
        QVERIFY(!m1->anySideBarIsVisible());
        QVERIFY(dw1->isInMainWindow());
    }

    {
        EnsureTopLevelsDeleted e;

        KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_AutoHideSupport);
        auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None, "MW1");
        auto dw1 = newDockWidget("1");
        m1->addDockWidget(dw1, Location_OnBottom);
        dw1->moveToSideBar();
        QTest::qWait(100);

        QVERIFY(!m1->overlayedDockWidget());
        QVERIFY(m1->anySideBarIsVisible());

        // overlay and deoverlay
        m1->toggleOverlayOnSideBar(dw1);
        m1->toggleOverlayOnSideBar(dw1);

        // open should go to docked position, not floating
        dw1->open();

        QVERIFY(!m1->overlayedDockWidget());
        QVERIFY(!m1->anySideBarIsVisible());

        QVERIFY(dw1->isInMainWindow());
    }
}

void TestQtWidgets::tst_isOpenSideBar()
{
    // Tests that DockWidget::isOpen() toggles when we toggle the overlay
    EnsureTopLevelsDeleted e;

    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_AutoHideSupport);
    auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None, "MW1");
    auto dw1 = newDockWidget("1");
    m1->addDockWidget(dw1, Location_OnBottom);
    dw1->moveToSideBar();

    QVERIFY(!m1->overlayedDockWidget());
    QVERIFY(m1->anySideBarIsVisible());
    QVERIFY(!dw1->isOpen());

    // overlay it:
    m1->toggleOverlayOnSideBar(dw1);
    QVERIFY(m1->overlayedDockWidget());
    QVERIFY(m1->anySideBarIsVisible());
    QVERIFY(dw1->isOpen());

    // close overlay:
    m1->toggleOverlayOnSideBar(dw1);
    QVERIFY(!m1->overlayedDockWidget());
    QVERIFY(m1->anySideBarIsVisible());

    QVERIFY(!dw1->isOpen());
}

void TestQtWidgets::tst_toggleActionOnSideBar()
{
    // When a dock widget is in the sidebar and we use DockWidget::toggleAction() then it should
    // toggle visibility without removing it from the sidebar

    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_AutoHideSupport);
    auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None, "MW1");
    auto dw1 = newDockWidget("1");
    m1->addDockWidget(dw1, Location_OnBottom);
    dw1->moveToSideBar();

    QVERIFY(!dw1->isVisible());
    QVERIFY(!dw1->isOverlayed());
    QVERIFY(dw1->isInSideBar());
    QVERIFY(!dw1->isInMainWindow());

    auto action = dw1->toggleAction();
    action->trigger();

    QVERIFY(dw1->isVisible());
    QVERIFY(dw1->isOverlayed());
    QVERIFY(dw1->isInMainWindow());

    QVERIFY(dw1->isInSideBar());
    action->trigger();

    QVERIFY(!dw1->isOverlayed());
    QVERIFY(!dw1->isInMainWindow());

    QVERIFY(dw1->isInSideBar());
    QVERIFY(!dw1->isInMainWindow());


    // Count how many times toggleActions triggers:
    int openCount = 0;
    int closeCount = 0;
    KDBindings::ScopedConnection conn = action->d->toggled.connect([&](bool t) {
        if (t)
            openCount++;
        else
            closeCount++;
    });

    // Make it visible on sidebar:
    m1->toggleOverlayOnSideBar(dw1);
    QCOMPARE(openCount, 1);
    QCOMPARE(closeCount, 0);

    // close it on sidebar
    m1->toggleOverlayOnSideBar(dw1);
    QCOMPARE(openCount, 1);
    QCOMPARE(closeCount, 1);

    // Make visible on sidebar again
    m1->toggleOverlayOnSideBar(dw1);
    QCOMPARE(openCount, 2);
    QCOMPARE(closeCount, 1);

    // Click the unpin button, docks in main window, no toggling should happen
    dw1->titleBar()->onAutoHideClicked();
    QCOMPARE(openCount, 2);
    QCOMPARE(closeCount, 1);
}

void TestQtWidgets::tst_deleteOnCloseWhenOnSideBar()
{
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_AutoHideSupport);
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    ObjectGuard<Core::DockWidget> dock1 = createDockWidget(
        "dock1", Platform::instance()->tests_createView({ true, {}, QSize(400, 400) }),
        DockWidgetOption_DeleteOnClose);
    m->addDockWidget(dock1, Location_OnLeft);

    dock1->moveToSideBar();
    QVERIFY(dock1);
    QVERIFY(dock1->isInSideBar());

    QTest::qWait(500);
    QVERIFY(dock1);
}

void TestQtWidgets::tst_sidebarOverlayShowsAutohide()
{
    // Tests that overlayed widgets show the "Disable auto-hide" button

    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_AutoHideSupport);

    auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None, "MW1");
    auto dw1 = newDockWidget(QStringLiteral("1"));

    m1->addDockWidget(dw1, Location_OnBottom);
    QVERIFY(dw1->titleBar()->supportsAutoHideButton());

    m1->moveToSideBar(dw1);
    m1->overlayOnSideBar(dw1);

    QVERIFY(dw1->isOverlayed());

    auto titleBar = dw1->titleBar();
    QVERIFY(titleBar->isVisible());
    QVERIFY(titleBar->supportsAutoHideButton());

    delete dw1;
}

void TestQtWidgets::tst_sidebarOverlayGetsHiddenOnClick()
{
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_AutoHideSupport);

    {
        // Case #1 click on another dockwidget should hide the overlay

        auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None, "MW1");
        auto dw1 = newDockWidget(QStringLiteral("1"));
        auto dw2 = newDockWidget(QStringLiteral("2"));

        m1->addDockWidget(dw1, Location_OnBottom);
        m1->addDockWidget(dw2, Location_OnBottom);

        m1->moveToSideBar(dw1);
        m1->overlayOnSideBar(dw1);

        QVERIFY(dw1->isOverlayed());

        Tests::clickOn(dw2->mapToGlobal(dw2->rect().bottomLeft() + QPoint(5, -5)), dw2->view());
        QVERIFY(!dw1->isOverlayed());
        QVERIFY(dw1->isInSideBar());

        auto widget2 = Platform::instance()->tests_createView({ true });
        dw2->setGuestView(widget2->asWrapper());
        m1->overlayOnSideBar(dw1);
        QVERIFY(dw1->isOverlayed());
        Tests::clickOn(widget2->mapToGlobal(widget2->rect().bottomLeft() + QPoint(5, -5)), widget2);
        QVERIFY(!dw1->isOverlayed());

        m1.reset();
        delete dw1;
    }

    {
        // Case #1 click on empty main window space, should hide the overlay

        auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None, "MW1");
        auto dw1 = newDockWidget(QStringLiteral("1"));

        m1->addDockWidget(dw1, Location_OnBottom);

        m1->moveToSideBar(dw1);
        m1->overlayOnSideBar(dw1);

        QVERIFY(dw1->isOverlayed());

        const QPoint localPt(100, 250);
        Tests::clickOn(m1->mapToGlobal(m1->rect().topLeft() + localPt),
                       m1->view()->childViewAt(localPt).get());
        QVERIFY(!dw1->isOverlayed());
    }
}

void TestQtWidgets::tst_sidebarGrouping()
{
    // Tests Flag_AutoHideAsTabGroups
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_AutoHideSupport | KDDockWidgets::Config::Flag_AutoHideAsTabGroups);

    {
        auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None, "MW1");
        auto dw1 = newDockWidget(QStringLiteral("1"));
        auto dw2 = newDockWidget(QStringLiteral("2"));

        m1->addDockWidget(dw1, Location_OnBottom);
        dw1->addDockWidgetAsTab(dw2);

        dw1->titleBar()->onAutoHideClicked();
        QVERIFY(dw1->isInSideBar());
        QVERIFY(dw2->isInSideBar());
        QVERIFY(!dw1->isOverlayed());
        QVERIFY(!dw2->isOverlayed());

        m1->overlayOnSideBar(dw1);
        QVERIFY(dw1->isOverlayed());
        QVERIFY(!dw2->isOverlayed());

        dw1->titleBar()->onAutoHideClicked();
        QVERIFY(!dw1->isInSideBar());
        QVERIFY(!dw2->isInSideBar());
        QVERIFY(!dw1->isOverlayed());
        QVERIFY(!dw2->isOverlayed());
    }
}

void TestQtWidgets::tst_sidebarCrash()
{
    // Tests a crash that happened when toggling overlay a few times

    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_AutoHideSupport);

    auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None, "MW1");
    auto dw1 = newDockWidget(QStringLiteral("1"));
    m1->addDockWidget(dw1, Location_OnBottom);

    dw1->titleBar()->onAutoHideClicked();
    QVERIFY(dw1->isInSideBar());

    m1->overlayOnSideBar(dw1);

    dw1->titleBar()->onAutoHideClicked();
    QVERIFY(!dw1->isInSideBar());
    QVERIFY(!dw1->isOverlayed());

    dw1->titleBar()->onAutoHideClicked();
    QVERIFY(dw1->isInSideBar());

    QTest::qWait(1000);

    m1->toggleOverlayOnSideBar(dw1);
}

void TestQtWidgets::tst_sidebarCrash2()
{
    // Tests a crash, only reproduceable with an ASAN build of Qt
    // While unpinning, the QToolButton would be deleted while still on the stack

    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_AutoHideSupport);

    auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None, "MW1");
    auto dw1 = newDockWidget(QStringLiteral("1"));
    m1->addDockWidget(dw1, Location_OnBottom);
    m1->moveToSideBar(dw1);
    m1->overlayOnSideBar(dw1);

    auto titleBarWidget = qobject_cast<QtWidgets::TitleBar *>(QtCommon::View_qt::asQWidget(dw1->titleBar()->view()));
    QVERIFY(titleBarWidget && titleBarWidget->isVisible());

    auto button = titleBarWidget->m_autoHideButton;
    QVERIFY(button && button->isVisible());

    auto globalPos = button->mapToGlobal(QPoint(5, 5));

    auto b = QtWidgets::ViewWrapper::create(button);
    Tests::clickOn(globalPos, b.get());
}

void TestQtWidgets::tst_sidebarCloseReason()
{
    {
        EnsureTopLevelsDeleted e;
        KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_AutoHideSupport);

        auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None, "MW1");
        auto dw1 = newDockWidget(QStringLiteral("1"));
        m1->addDockWidget(dw1, Location_OnBottom);

        CloseReason expectedLastReason = CloseReason::Unspecified;
        KDBindings::ScopedConnection conn = dw1->toggleAction()->d->toggled.connect([&expectedLastReason, dw1](bool open) {
            // We also check that the value is actually set *before* the QAction firing
            // as users connect to the action
            if (!open)
                Q_ASSERT(dw1->lastCloseReason() == expectedLastReason);
        });

        expectedLastReason = CloseReason::MovedToSideBar;
        dw1->titleBar()->onAutoHideClicked();
        QVERIFY(dw1->isInSideBar());
        QVERIFY(!dw1->isOpen());

        QCOMPARE(dw1->lastCloseReason(), expectedLastReason);

        m1->overlayOnSideBar(dw1);
        QVERIFY(dw1->isInSideBar());
        QVERIFY(dw1->isOpen());

        expectedLastReason = CloseReason::OverlayCollapse;
        m1->clearSideBarOverlay();
        QCOMPARE(dw1->lastCloseReason(), expectedLastReason);

        m1->overlayOnSideBar(dw1);
        QVERIFY(dw1->isInSideBar());
        QVERIFY(dw1->isOpen());
        expectedLastReason = CloseReason::TitleBarCloseButton;
        dw1->titleBar()->onCloseClicked();
        QCOMPARE(dw1->lastCloseReason(), expectedLastReason);

        expectedLastReason = CloseReason::MovedToSideBar;
        dw1->open();
        m1->moveToSideBar(dw1);
        QCOMPARE(dw1->lastCloseReason(), expectedLastReason);
    }
}

void TestQtWidgets::tst_sidebarSide()
{
    // Tests which sidebar is chosen

    {
        // Tests that if a dock widget is touching top and bottom border, it will go to
        // left sidebar if it's closer to it.
        EnsureTopLevelsDeleted e;
        KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_AutoHideSupport);

        auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None, "MW1");
        auto dw1 = newDockWidget(QStringLiteral("1"));
        auto dw2 = newDockWidget(QStringLiteral("2"));
        auto dw3 = newDockWidget(QStringLiteral("3"));
        auto dw4 = newDockWidget(QStringLiteral("4"));
        m1->addDockWidget(dw1, Location_OnRight);
        m1->addDockWidget(dw2, Location_OnRight);
        m1->addDockWidget(dw3, Location_OnRight);
        m1->addDockWidget(dw4, Location_OnRight);
        m1->layoutEqually();

        dw2->titleBar()->onAutoHideClicked();

        auto sb = m1->sideBarForDockWidget(dw2);
        QVERIFY(sb);
        QCOMPARE(sb->location(), SideBarLocation::West);
    }
}

void TestQtWidgets::tst_floatRemovesFromSideBar()
{
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_AutoHideSupport);

    auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None, "MW1");
    auto dw1 = newDockWidget(QStringLiteral("1"));
    m1->addDockWidget(dw1, Location_OnBottom);

    m1->moveToSideBar(dw1);
    m1->overlayOnSideBar(dw1);

    QVERIFY(dw1->isOverlayed());
    QVERIFY(!dw1->isFloating());
    QVERIFY(dw1->isInMainWindow());

    dw1->setFloating(true);
    QVERIFY(!dw1->isOverlayed());
    QVERIFY(dw1->isFloating());
    QVERIFY(!dw1->isInMainWindow());

    QCOMPARE(dw1->sideBarLocation(), SideBarLocation::None);

    // Also test a crash I got
    m1->addDockWidget(dw1, Location_OnBottom);

    auto tb = dw1->titleBar();
    QVERIFY(tb->isVisible());

    tb->onFloatClicked();
}

void TestQtWidgets::tst_overlayedGeometryIsSaved()
{
    // Tests that after resizing an overlayed widget, and then hide+show, its size is preserved
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_AutoHideSupport);

    auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None, "MW1");
    auto dw1 = newDockWidget(QStringLiteral("1"));
    m1->addDockWidget(dw1, Location_OnBottom);

    m1->moveToSideBar(dw1, SideBarLocation::North);
    m1->overlayOnSideBar(dw1);

    Core::Group *group = dw1->dptr()->group();
    QVERIFY(group->isOverlayed());
    QCOMPARE(dw1->sideBarLocation(), SideBarLocation::North);
    QVERIFY(group->height() > 0);

    const int newHeight = group->height() + 300;
    group->view()->setHeight(newHeight);

    m1->toggleOverlayOnSideBar(dw1);
    m1->toggleOverlayOnSideBar(dw1);

    group = dw1->dptr()->group();
    QCOMPARE(group->height(), newHeight);
}

void TestQtWidgets::tst_overlayCrash()
{
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_AutoHideSupport);

    auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None, "MW1");
    auto dw1 = newDockWidget(QStringLiteral("1"));
    m1->addDockWidget(dw1, Location_OnBottom);

    auto dw2 = newDockWidget(QStringLiteral("2"));
    m1->addDockWidget(dw2, Location_OnBottom);

    m1->moveToSideBar(dw1);
    m1->toggleOverlayOnSideBar(dw1);

    dw1->close();

    auto tb = dw2->titleBar();
    QVERIFY(tb->isVisible());

    pressOn(tb->mapToGlobal(QPoint(5, 5)), tb->view());
}

void TestQtWidgets::tst_embeddedMainWindow()
{
    EnsureTopLevelsDeleted e;
    // Tests a MainWindow which isn't a top-level window, but is embedded in another window
    EmbeddedWindow *window = createEmbeddedMainWindow(QSize(800, 800));

    auto dock1 = createDockWidget("1", new QPushButton("1"));
    window->mainWindow->addDockWidget(dock1, Location_OnTop);
    dock1->setFloating(true);
    auto dropArea = window->mainWindow->dropArea();
    auto fw = dock1->floatingWindow();

    dragFloatingWindowTo(fw, dropArea, DropLocation_Left);

    auto layout = dropArea;
    QVERIFY(Platform::instance()->tests_waitForDeleted(fw));
    QCOMPARE(layout->count(), 2); // 2, as it has the central group
    QCOMPARE(layout->visibleCount(), 2);
    layout->checkSanity();

    delete window;
}

void TestQtWidgets::tst_restoreEmbeddedMainWindow()
{
    EnsureTopLevelsDeleted e;
    // Tests a MainWindow which isn't a top-level window, but is embedded in another window
    EmbeddedWindow *window = createEmbeddedMainWindow(QSize(800, 800));

    auto dock1 = createDockWidget("1", new QPushButton("1"));
    window->mainWindow->addDockWidget(dock1, Location_OnTop);

    const QPoint originalPos(250, 250);
    const QSize originalSize = window->size();
    window->move(originalPos);

    LayoutSaver saver;
    QByteArray saved = saver.serializeLayout();
    QVERIFY(!saved.isEmpty());

    window->resize(555, 555);
    const QPoint newPos(500, 500);
    window->move(newPos);
    QVERIFY(saver.restoreLayout(saved));

    QCOMPARE(window->pos(), originalPos);
    QCOMPARE(window->size(), originalSize);
    window->mainWindow->layout()->checkSanity();

    delete window;
}

void TestQtWidgets::tst_negativeAnchorPositionWhenEmbedded_data()
{
    QTest::addColumn<bool>("embedded");

    QTest::newRow("false") << false;
    QTest::newRow("true") << true;
}

void TestQtWidgets::tst_negativeAnchorPositionWhenEmbedded()
{
    QFETCH(bool, embedded);
    EnsureTopLevelsDeleted e;

    MainWindow *m = nullptr;
    if (embedded) {
        auto em = createEmbeddedMainWindow(QSize(500, 500));
        m = em->mainWindow;
    } else {
        m = createMainWindow(QSize(500, 500), MainWindowOption_HasCentralGroup).release();
        m->view()->resize(QSize(500, 500));
        m->show();
    }
    auto layout = m->multiSplitter();

    auto w1 = Platform::instance()->tests_createView({ true, {}, QSize(400, 400) });
    auto w2 = Platform::instance()->tests_createView({ true, {}, QSize(400, 400) });
    auto d1 = createDockWidget("1", w1);
    auto d2 = createDockWidget("2", w2);
    auto d3 = createDockWidget("3", w2);

    m->addDockWidget(d1, Location_OnLeft);
    m->addDockWidget(d2, Location_OnLeft);
    m->addDockWidget(d3, Location_OnLeft);

    layout->checkSanity();

    delete static_cast<QtWidgets::ViewWrapper *>(m->window().get())->widget();
}

// For #443
void TestQtWidgets::tst_restoreWithRemapping()
{
    EnsureTopLevelsDeleted e;
    QByteArray savedState;

    // 1. Create a saved state and immediately delete the main window and dock widgets
    auto m = createMainWindow(QSize(500, 500), MainWindowOption_None, "mainWindow1");
    auto dock1 = createDockWidget("1", new QPushButton("1"));
    m->addDockWidget(dock1, Location_OnLeft);
    auto dock2 = createDockWidget("2", new QPushButton("2"));
    m->addDockWidget(dock2, Location_OnRight);

    LayoutSaver saver;
    savedState = saver.serializeLayout();

    dock1->setUniqueName("2");
    dock2->setUniqueName("1");

    // 2. Restore the dock widgets via factory
    LayoutSaver restorer;
    restorer.restoreLayout(savedState);

    // dock 1 is now on the right of dock 2
    QVERIFY(dock1->dptr()->group()->view()->x() > dock2->dptr()->group()->view()->x());
}

void TestQtWidgets::tst_restoreResizesLayout()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(500, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1", new QPushButton("1"));
    m->addDockWidget(dock1, Location_OnLeft);

    LayoutSaver saver;
    QVERIFY(saver.saveToFile("layout_tst_restoreResizesLayout.json"));

    // Now resize the window, and then restore. The layout should have the new size

    auto layout = m->multiSplitter();
    m->view()->resize(QSize(1050, 1050));
    QCOMPARE(m->size(), QSize(1050, 1050));

    LayoutSaver restorer(RestoreOption_RelativeToMainWindow);
    QVERIFY(restorer.restoreFromFile("layout_tst_restoreResizesLayout.json"));
    QVERIFY(layout->checkSanity());

    QCOMPARE(m->dropArea()->size(), layout->layoutSize());
    QVERIFY(layout->checkSanity());
}

void TestQtWidgets::tst_restoreNonRelativeFloatingWindowGeometry()
{
    // Tests that disabling RelativeFloatingWindowGeometry works

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(500, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1", new QPushButton("1"));

    // Also test that invisible dock doesn't change size
    auto dock2 = createDockWidget("2", new QPushButton("2"), {}, {}, /*show=*/false);

    LayoutSaver saver(RestoreOption_RelativeToMainWindow);
    saver.dptr()->m_restoreOptions.setFlag(InternalRestoreOption::RelativeFloatingWindowGeometry,
                                           false);

    const QByteArray saved = saver.serializeLayout();

    const QSize floatingWindowSize = dock1->window()->size();
    const QSize floatingWindowSize2 = dock2->window()->size();

    m->view()->resize(QSize(m->width() * 2, m->height()));
    saver.restoreLayout(saved);

    QVERIFY(dock2->isFloating());
    QVERIFY(!dock2->isOpen());

    QCOMPARE(dock1->window()->size(), floatingWindowSize);
    QCOMPARE(dock2->window()->size(), floatingWindowSize2);
}

void TestQtWidgets::tst_maximumSizePolicy()
{
    EnsureTopLevelsDeleted e;

    const int maxHeight = 250;
    auto widget =
        Platform::instance()->tests_createView({ true, QSize(250, maxHeight), QSize(200, 200) });
    QtCommon::View_qt::asQWidget(widget)->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

    auto dock1 = createDockWidget("dock1", widget);
    dock1->open();
    dock1->window()->resize(QSize(500, 500));
    auto window1 = dock1->window();
    dock1->close();
    dock1->open();
    auto oldFw2 = dock1->window();

    const int tolerance = 50;
    QVERIFY(dock1->window()->height() <= maxHeight + tolerance); // +tolerance as the floating
                                                                 // window is a bit bigger, due to
                                                                 // margins etc.
    QVERIFY(dock1->height() <= maxHeight);

    auto m1 = createMainWindow();
    auto dock2 = createDockWidget("dock2", new QPushButton("foo"));
    m1->addDockWidget(dock2, Location_OnTop);
    m1->view()->resize(QSize(2000, 3000));

    // Make the floating window big, and see if the suggested highlight is still small
    dock1->window()->resize(QSize(dock1->width(), 800));

    {
        WindowBeingDragged wbd1(dock1->floatingWindow());
        const QRect highlightRect =
            m1->multiSplitter()->rectForDrop(&wbd1, Location_OnBottom, nullptr);
        QVERIFY(highlightRect.height() <= maxHeight + tolerance);
    }

    // Now drop it, and check too
    m1->addDockWidget(dock1, Location_OnBottom);
    QVERIFY(dock1->height() <= maxHeight);
}

void TestQtWidgets::tst_minSizeChanges()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(600, 600), MainWindowOption_None);
    m->show();
    auto w1 = Platform::instance()->tests_createView({ true, {}, QSize(400, 400) });
    auto w2 = Platform::instance()->tests_createView({ true, {}, QSize(400, 400) });

    auto d1 = newDockWidget("1");
    d1->setGuestView(w1->asWrapper());
    auto d2 = newDockWidget("2");
    d2->setGuestView(w2->asWrapper());

    m->addDockWidget(d1, Location_OnTop);
    m->addDockWidget(d2, Location_OnTop, nullptr, InitialVisibilityOption::StartHidden);
    auto layout = m->multiSplitter();

    // 1. d2 is a placeholder, let's change its min size before showing it
    w2->setMinimumSize(QSize(800, 800));
    d2->open();

    Item *item2 = layout->itemForGroup(d2->dptr()->group());

    QVERIFY(layout->checkSanity());

    Platform::instance()->tests_waitForResize(m->view());

    QVERIFY(item2->width() >= 800);
    QVERIFY(item2->height() >= 800);
    QVERIFY(m->height() >= 1200);

    // 2. d1 is visible, let's change its min size
    w1->setMinimumSize(QSize(800, 800));

    Platform::instance()->tests_waitForResize(m->view());
    layout->checkSanity();

    QVERIFY(m->height() >= 1600);

    // add a small one to the middle
    auto w3 = Platform::instance()->tests_createView({ true, {}, QSize(100, 100) });
    auto d3 = newDockWidget("3");
    d3->setGuestView(w3->asWrapper());
    m->addDockWidget(d3, Location_OnTop, d1);
}

void TestQtWidgets::tst_maxSizePropagates()
{
    // Tests that the DockWidget gets the min and max size of its guest widget
    EnsureTopLevelsDeleted e;
    auto dock1 = newDockWidget("dock1");

    auto w = Platform::instance()->tests_createView({ true, {}, QSize(200, 200) });
    w->setMinimumSize(QSize(120, 120));
    w->setMaximumSize(QSize(500, 500));
    dock1->setGuestView(w->asWrapper());
    dock1->open();


    QCOMPARE(dock1->view()->minSize(), w->minSize());
    QCOMPARE(dock1->view()->maxSizeHint(), w->maxSizeHint());

    w->setMinimumSize(QSize(121, 121));
    w->setMaximumSize(QSize(501, 501));

    Platform::instance()->tests_waitForEvent(w, QEvent::LayoutRequest);

    QCOMPARE(dock1->view()->minSize(), w->minSize());
    QCOMPARE(dock1->view()->maxSizeHint(), w->maxSizeHint());

    // Now let's see if our Frame also has proper size-constraints
    Core::Group *group = dock1->dptr()->group();
    QCOMPARE(group->view()->maxSizeHint().expandedTo(w->maxSizeHint()),
             group->view()->maxSizeHint());
}

void TestQtWidgets::tst_maxSizedFloatingWindow()
{
    // Tests that FloatingWindows get a proper max-size, if its dock widget has one
    EnsureTopLevelsDeleted e;
    auto dock1 = newDockWidget("dock1");
    auto dock2 = newDockWidget("dock2");
    auto w = Platform::instance()->tests_createView({ true });
    w->setMinimumSize(QSize(120, 100));
    w->setMaximumSize(QSize(300, 300));
    dock1->setGuestView(w->asWrapper());

    dock1->open();
    dock2->open();

    auto window1 = dock1->window();
    auto window2 = dock2->window();
    Platform::instance()->tests_waitForEvent(window1.get(), QEvent::LayoutRequest);

    QVERIFY(window1->maxSizeHint().width() < 500);
    QVERIFY(window1->maxSizeHint().height() < 500);
    QVERIFY(window2->maxSizeHint().width() > 500);
    QVERIFY(window2->maxSizeHint().height() > 500);

    auto hasMax = [&window1] {
        const QSize max = window1->maxSizeHint();
        return max.width() < 500 && max.height() < 500;
    };

    // Adding side-by-side, we don't honour max size (yet)
    dock1->addDockWidgetToContainingWindow(dock2, Location_OnBottom);
    Platform::instance()->tests_waitForEvent(window1.get(), QEvent::LayoutRequest);
    QVERIFY(window1->maxSizeHint().width() > 500);
    QVERIFY(window1->maxSizeHint().height() > 500);

    // Close dw2, we have a single dock widget again, we honour max-size
    dock2->close();
    Platform::instance()->tests_waitForEvent(window1.get(), QEvent::LayoutRequest);
    QVERIFY(hasMax());

    dock1->addDockWidgetAsTab(dock2);
    Platform::instance()->tests_waitForEvent(window1.get(), QEvent::LayoutRequest);
    QVERIFY(!hasMax());

    dock2->close();
    Platform::instance()->tests_waitForEvent(window1.get(), QEvent::LayoutRequest);
    QVERIFY(hasMax());
}

void TestQtWidgets::tst_maxSizeHonouredWhenAnotherDropped()
{
    // dock1 is docked, and has small max-height.
    // When dropping dock2, which is small too, dock2 should occupy all the height except dock1's
    // max-height i.e. dock2 should expand and eat all available space

    EnsureTopLevelsDeleted e;
    auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None);
    auto dock1 = newDockWidget("dock1");

    auto w = Platform::instance()->tests_createView({ true, {}, QSize(400, 400) });
    w->setMinimumSize(QSize(120, 100));
    w->setMaximumSize(QSize(300, 150));
    dock1->setGuestView(w->asWrapper());
    m1->addDockWidget(dock1, Location_OnLeft);

    auto dock2 = newDockWidget("dock2");
    m1->addDockWidget(dock2, Location_OnBottom);

    auto root = m1->multiSplitter()->rootItem();
    auto separator = root->separators().constFirst();
    const int min1 = root->minPosForSeparator_global(separator);
    const int max2 = root->maxPosForSeparator_global(separator);

    QVERIFY(separator->position() >= min1);
    QVERIFY(separator->position() <= max2);
    const int item1MaxHeight = dock1->dptr()->group()->view()->maxSizeHint().height();
    QVERIFY(dock1->dptr()->group()->view()->height() <= item1MaxHeight);
    root->dumpLayout();
    QCOMPARE(dock2->dptr()->group()->view()->height(),
             root->height() - item1MaxHeight - Item::layoutSpacing);
}

void TestQtWidgets::tst_addToHiddenMainWindow()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(1000, 1000), MainWindowOption_HasCentralGroup, {}, false);
    auto w1 = Platform::instance()->tests_createView({ true, {}, QSize(400, 400) });
    auto w2 = Platform::instance()->tests_createView({ true, {}, QSize(400, 400) });
    auto d1 = createDockWidget("1", w1);
    auto d2 = createDockWidget("2", w2);

    m->addDockWidget(d1, Location_OnTop);
    m->addDockWidget(d2, Location_OnTop);

    QVERIFY(!m->isVisible());
    d1->setFloating(true);
    d2->setFloating(false);
    m->layout()->checkSanity();
}

void TestQtWidgets::tst_maxSizePropagates2()
{
    EnsureTopLevelsDeleted e;
    auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None);
    auto dock1 = newDockWidget("dock1");

    auto w = Platform::instance()->tests_createView({ true, {}, QSize(200, 200) });
    w->setMinimumSize(QSize(120, 120));
    w->setMaximumSize(QSize(300, 500));
    dock1->setGuestView(w->asWrapper());
    dock1->open();

    auto dock2 = newDockWidget("dock2");
    auto dock3 = newDockWidget("dock3");
    auto dock4 = newDockWidget("dock4");
    m1->addDockWidget(dock2, Location_OnLeft);
    m1->addDockWidget(dock3, Location_OnRight);
    m1->addDockWidget(dock4, Location_OnBottom, dock3);
    m1->addDockWidget(dock1, Location_OnLeft, dock4);

    Core::Group *group1 = dock1->dptr()->group();

    Core::ItemBoxContainer *root = m1->multiSplitter()->rootItem();
    Item *item1 = root->itemForView(group1->asLayoutingGuest());
    auto vertSep1 = root->separators().constFirst();
    const int min1 = root->minPosForSeparator_global(vertSep1);

    ItemBoxContainer *container1 = item1->parentBoxContainer();
    auto innerVertSep1 = container1->separators().constFirst();
    const int minInnerSep = container1->minPosForSeparator_global(innerVertSep1);
    const int maxInnerSep = container1->maxPosForSeparator_global(innerVertSep1);

    root->requestSeparatorMove(vertSep1, -(vertSep1->position() - min1));
    QVERIFY(group1->width() <= group1->view()->maxSizeHint().width());

    container1->requestSeparatorMove(innerVertSep1, -(innerVertSep1->position() - minInnerSep));
    QVERIFY(group1->width() <= group1->view()->maxSizeHint().width());

    container1->requestSeparatorMove(innerVertSep1, maxInnerSep - innerVertSep1->position());
    QVERIFY(group1->width() <= group1->view()->maxSizeHint().width());
}

void TestQtWidgets::tst_maxSizeHonouredWhenDropped()
{
    EnsureTopLevelsDeleted e;
    auto m1 = createMainWindow();
    auto dock1 = newDockWidget("dock1");
    auto dock2 = newDockWidget("dock2");
    m1->addDockWidget(dock1, Location_OnTop);
    m1->view()->resize(QSize(2000, 2000));

    auto w2 = Platform::instance()->tests_createView({ true, {}, { 0, 0 } });
    dock2->setGuestView(w2->asWrapper());
    const int maxWidth = 200;
    w2->setMaximumSize(QSize(maxWidth, 200));
    m1->addDockWidget(dock2, Location_OnLeft);
    const int droppedWidth = dock2->dptr()->group()->width();
    QVERIFY(droppedWidth < maxWidth + 50); // +50 to cover any margins and waste by QTabWidget

    // Try again, but now dropping a multisplitter
    dock2->setFloating(true);
    auto fw = dock2->floatingWindow();

    m1->dropArea()->drop(fw->view(), Location_OnLeft, nullptr);
    QCOMPARE(dock2->dptr()->group()->width(), droppedWidth);
}

void TestQtWidgets::tst_fixedSizePolicy()
{
    // tests that KDDW also takes into account QSizePolicy::Fixed for calculating the max size hint.
    // Since QPushButton for example doesn't set QWidget::maximumSize(), but instead uses sizeHint()
    // + QSizePolicy::Fixed.
    EnsureTopLevelsDeleted e;
    auto button = new QPushButton("one");
    auto dock1 = createDockWidget("dock1", button);
    Core::Group *group = dock1->dptr()->group();

    // Just a precondition from the test. If QPushButton ever changes, replace with a QWidget and
    // set fixed size policy
    QCOMPARE(button->sizePolicy().verticalPolicy(), QSizePolicy::Fixed);

    const int buttonMaxHeight = button->sizeHint().height();

    QWidget *dockWidget1 = QtCommon::View_qt::asQWidget(dock1->view());
    QCOMPARE(dockWidget1->sizePolicy().verticalPolicy(),
             button->sizePolicy().verticalPolicy());
    QCOMPARE(dockWidget1->sizePolicy().horizontalPolicy(),
             button->sizePolicy().horizontalPolicy());

    QCOMPARE(group->view()->maxSizeHint().height(),
             qMax(buttonMaxHeight, Core::Item::hardcodedMinimumSize.height()));
}

void TestQtWidgets::tst_restoreFloatingMaximizedState()
{
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_TitleBarHasMaximizeButton);
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    const QRect originalNormalGeometry = dock1->floatingWindow()->view()->normalGeometry();
    dock1->floatingWindow()->view()->showMaximized();

    QCOMPARE(dock1->floatingWindow()->view()->window()->windowState(), WindowState::Maximized);

    LayoutSaver saver;
    const QByteArray saved = saver.serializeLayout();

    saver.restoreLayout(saved);
    QCOMPARE(dock1->floatingWindow()->view()->window()->windowState(), WindowState::Maximized);

    QCOMPARE(dock1->floatingWindow()->view()->normalGeometry(), originalNormalGeometry);

    dock1->floatingWindow()->view()->showNormal();
    QCOMPARE(dock1->floatingWindow()->view()->normalGeometry(), originalNormalGeometry);
}

void TestQtWidgets::tst_complex()
{
    // Tests some anchors out of bounds I got

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(600, 500), MainWindowOption_None);
    auto layout = m->multiSplitter();
    m->view()->resize(QSize(3266, 2239));
    m->show();

    Core::DockWidget::List docks;

    QVector<KDDockWidgets::Location> locations = {
        Location_OnLeft, Location_OnLeft, Location_OnLeft, Location_OnRight,
        Location_OnRight, Location_OnRight, Location_OnRight, Location_OnBottom,
        Location_OnBottom, Location_OnBottom, Location_OnBottom, Location_OnBottom,
        Location_OnBottom, Location_OnBottom, Location_OnBottom, Location_OnBottom,
        Location_OnBottom, Location_OnBottom, Location_OnBottom, Location_OnBottom,
        Location_OnBottom
    };

    QVector<KDDockWidgets::InitialVisibilityOption> options = {
        InitialVisibilityOption::StartVisible, InitialVisibilityOption::StartVisible,
        InitialVisibilityOption::StartHidden, InitialVisibilityOption::StartHidden,
        InitialVisibilityOption::StartVisible, InitialVisibilityOption::StartHidden,
        InitialVisibilityOption::StartHidden, InitialVisibilityOption::StartHidden,
        InitialVisibilityOption::StartHidden, InitialVisibilityOption::StartHidden,
        InitialVisibilityOption::StartHidden, InitialVisibilityOption::StartVisible,
        InitialVisibilityOption::StartVisible, InitialVisibilityOption::StartHidden,
        InitialVisibilityOption::StartHidden, InitialVisibilityOption::StartHidden,
        InitialVisibilityOption::StartHidden, InitialVisibilityOption::StartHidden,
        InitialVisibilityOption::StartHidden, InitialVisibilityOption::StartHidden,
        InitialVisibilityOption::StartHidden
    };

    QVector<bool> floatings = { true, false, true, false, false, false, false,
                                false, false, false, false, false, true, false,
                                false, true, true, true, true, true, false };

    QVector<QSize> minSizes = { QSize(316, 219), QSize(355, 237), QSize(293, 66), QSize(158, 72),
                                QSize(30, 141), QSize(104, 143), QSize(104, 105), QSize(84, 341),
                                QSize(130, 130), QSize(404, 205), QSize(296, 177), QSize(914, 474),
                                QSize(355, 237), QSize(104, 104), QSize(104, 138), QSize(1061, 272),
                                QSize(165, 196), QSize(296, 177), QSize(104, 104), QSize(355, 237),
                                QSize(104, 138) };

    const int num = 21;
    for (int i = 0; i < num; ++i) {
        auto widget = Platform::instance()->tests_createView({ true, {}, minSizes.at(i) });
        auto dw = newDockWidget(QString::number(i));
        dw->setGuestView(widget->asWrapper());
        docks << dw;
    }

    for (int i = 0; i < num; ++i) {
        m->addDockWidget(docks[i], locations[i], nullptr, options[i]);
        layout->checkSanity();
        docks[i]->setFloating(floatings[i]);
        layout->checkSanity();
    }

    m->show();

    // Cleanup
    qDeleteAll(docks);
    qDeleteAll(DockRegistry::self()->groups());
}


void TestQtWidgets::tst_deleteOnClose()
{
    // QtQuick doesn't support autohide/pin/sidebar yet.
    // Tests that restoring the side-bar-overlay will call the users dock widget factory in case
    // the dock widget was deleted already
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_AutoHideSupport);
    KDDockWidgets::Config::self().setDockWidgetFactoryFunc([](const QString &name) {
        return createDockWidget(
            name, Platform::instance()->tests_createView({ true, {}, QSize(400, 400) }),
            DockWidgetOption_DeleteOnClose);
    });

    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    ObjectGuard<Core::DockWidget> dock1 =
        createDockWidget("1", Platform::instance()->tests_createView({ true, {}, QSize(400, 400) }),
                         DockWidgetOption_DeleteOnClose);
    m->addDockWidget(dock1, Location_OnLeft);
    m->moveToSideBar(dock1);
    m->overlayOnSideBar(dock1);
    LayoutSaver saver;
    const QByteArray saved = saver.serializeLayout();

    QVERIFY(dock1->isVisible());
    dock1->close();
    QVERIFY(Platform::instance()->tests_waitForDeleted(dock1));
    QVERIFY(!dock1.data());

    saver.restoreLayout(saved);
}

void TestQtWidgets::tstCloseNestedMdi()
{
    // Tests a bug where closing a mdi dock widget would close its main window too
    EnsureTopLevelsDeleted e;

    auto m = createMainWindow(QSize(1000, 500), MainWindowOption_HasCentralWidget);
    ObjectGuard<Core::MainWindow> p = m.get();

    auto mdi = new QtWidgets::MDIArea();
    m->setPersistentCentralView(mdi->asWrapper());

    auto dock1 = new QtWidgets::DockWidget(QStringLiteral("MyDock1"));
    dock1->setWidget(new QPushButton("1"));

    mdi->addDockWidget(dock1, {});

    dock1->dockWidget()->titleBar()->onCloseClicked();
    QVERIFY(p);
    QVERIFY(m->isVisible());
}

void TestQtWidgets::tstCloseNestedMDIPropagates()
{
    auto m = createMainWindow(QSize(1000, 500), MainWindowOption_HasCentralWidget);
    ObjectGuard<Core::MainWindow> p = m.get();

    auto mdi = new QtWidgets::MDIArea();
    m->setPersistentCentralView(mdi->asWrapper());

    auto dock1 = new KDDockWidgets::QtWidgets::DockWidget(QStringLiteral("MyDock1"));
    auto nonClosableWidget = Platform::instance()->tests_createNonClosableView();
    dock1->dockWidget()->setGuestView(nonClosableWidget->asWrapper());
    mdi->addDockWidget(dock1, {});

    auto dock2 = new KDDockWidgets::QtWidgets::DockWidget(QStringLiteral("MyDock2"));
    auto nonClosableWidget2 = Platform::instance()->tests_createNonClosableView();
    dock2->dockWidget()->setGuestView(nonClosableWidget2->asWrapper());
    dock2->open();

    Platform::instance()->tests_waitForEvent(dock1->controller(), QEvent::Show);
    QVERIFY(dock1->isVisible());
    QVERIFY(dock2->isVisible());

    m->close();

    QVERIFY(dock2->isVisible());
    QVERIFY(dock1->isVisible());
}

void TestQtWidgets::tst_setAsCurrentTab()
{
    EnsureTopLevelsDeleted e;

    // For issue #312, which is QtWidget only. The controller has the correct current index but
    // not the QTabBar.
    auto dw = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();
    auto dw2 = Config::self().viewFactory()->createDockWidget("dw2")->asDockWidgetController();
    auto dw3 = Config::self().viewFactory()->createDockWidget("dw3")->asDockWidgetController();

    dw->view()->show();
    dw->addDockWidgetAsTab(dw2);
    dw->addDockWidgetAsTab(dw3);

    Core::Group *group = dw->d->group();
    auto tabBar = group->tabBar();
    QTabBar *tabBarWidget = qobject_cast<QTabBar *>(QtCommon::View_qt::asQWidget(tabBar->view()));

    QVERIFY(!dw->isCurrentTab());
    QVERIFY(!dw2->isCurrentTab());
    QVERIFY(dw3->isCurrentTab());
    QCOMPARE(tabBarWidget->currentIndex(), 2);

    dw->setAsCurrentTab();

    QVERIFY(dw->isCurrentTab());
    QVERIFY(!dw2->isCurrentTab());
    QVERIFY(!dw3->isCurrentTab());

    QCOMPARE(group->currentIndex(), 0);
    QCOMPARE(group->currentDockWidget(), dw);

    QCOMPARE(tabBar->currentIndex(), 0);

    QCOMPARE(tabBarWidget->currentIndex(), 0);
}

void TestQtWidgets::initTestCase()
{
    KDDockWidgets::Core::Platform::instance()->installMessageHandler();
}

void TestQtWidgets::cleanupTestCase()
{
    KDDockWidgets::Core::Platform::instance()->uninstallMessageHandler();
}

void TestQtWidgets::tst_crash326()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(500, 500), MainWindowOption_HasCentralWidget);
    auto dock1 = createDockWidget("1", new QPushButton("1"), {}, {}, false);
    m->addDockWidget(dock1, KDDockWidgets::Location_OnBottom);
    ObjectGuard<Group> originalGroup = dock1->d->group();
    dock1->close();
    QVERIFY(dock1->parent() == nullptr);
    QVERIFY(originalGroup != dock1->d->group());
    QVERIFY(originalGroup->beingDeletedLater());

    dock1->show();
    QVERIFY(originalGroup != dock1->d->group());
}

void TestQtWidgets::tst_restoreWithIncompleteFactory()
{
    EnsureTopLevelsDeleted e;
    SetExpectedWarning ignoreWarning("Couldn't find dock widget");
    KDDockWidgets::Config::self().setDockWidgetFactoryFunc([](const QString &name) -> KDDockWidgets::Core::DockWidget * {
        if (name.contains(QStringLiteral("centralDockWidget")))
            return nullptr;

        auto w = new KDDockWidgets::QtWidgets::DockWidget(name);
        w->setWidget(new QWidget());
        return w->asDockWidgetController();
    });

    auto m = createMainWindow(QSize(500, 500), MainWindowOption_None, "MainWindow1");

    LayoutSaver saver;
    saver.restoreFromFile(":/layouts/restoreWithIncompleteFactory.json");

    auto layout = m->multiSplitter();
    QCOMPARE(layout->separators().size(), 0);
}

void TestQtWidgets::tst_deleteDockWidget()
{
    // Tests deleting the dock widget directly
    // The layout should readjust

    EnsureTopLevelsDeleted e;
    auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None, "MW1");
    auto dw1 = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();
    m1->addDockWidget(dw1, Location_OnBottom);
    auto dw3 = Config::self().viewFactory()->createDockWidget("dw3")->asDockWidgetController();
    m1->addDockWidget(dw3, Location_OnTop);

    auto dw2 = Config::self().viewFactory()->createDockWidget("dw2")->asDockWidgetController();

    m1->addDockWidget(dw2, KDDockWidgets::Location_OnLeft, dw1);
    dw2->setFloating(true);

    // There's one separator, separating dock 1 from dock 3
    QCOMPARE(m1->multiSplitter()->separators().size(), 1);

    delete dw1;

    // Frame is deleted delayed
    QTest::qWait(1000);

    // Dock3 now occupies everything, separator was deleted
    QVERIFY(m1->multiSplitter()->separators().isEmpty());
}

void TestQtWidgets::tst_findAncestor()
{
    EnsureTopLevelsDeleted e;
    QVERIFY(KDDockWidgets::findAncestor<QWidget>(nullptr) == nullptr);

    auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None, "MW1");
    auto dw1 = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();
    m1->addDockWidget(dw1, Location_OnBottom);

    auto mainWindow = QtCommon::View_qt::asQWidget(m1->view());
    auto dockWidget = QtCommon::View_qt::asQWidget(dw1->view());

    QCOMPARE(mainWindow, KDDockWidgets::findAncestor<QMainWindow>(mainWindow));
    QCOMPARE(mainWindow, KDDockWidgets::findAncestor<QMainWindow>(dockWidget));
}

void TestQtWidgets::tst_standaloneTitleBar()
{
    QWidget window;

    QtWidgets::TitleBar titleBar(&window);
    titleBar.asTitleBarController()->setTitle("some title");

    auto lay = new QVBoxLayout(&window);
    lay->addWidget(&titleBar);
    lay->addStretch();

    window.show();

    QVERIFY(window.isVisible());
    titleBar.asTitleBarController()->onCloseClicked();
    QVERIFY(!window.isVisible());
}

void TestQtWidgets::tst_titleBarTitle()
{
    EnsureTopLevelsDeleted e;
    auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None, "MW1");
    auto dock1 = new KDDockWidgets::QtWidgets::DockWidget(QStringLiteral("MyDock1"));
    m1->addDockWidget(dock1->asDockWidgetController(), Location_OnBottom);

    auto tb = dock1->actualTitleBar();
    QCOMPARE(dock1->asDockWidgetController()->title(), "MyDock1");
    QCOMPARE(tb->title(), "MyDock1");

    dock1->setTitle("Other");
    QCOMPARE(tb->title(), "Other");
}

void TestQtWidgets::tst_widgetAddQAction()
{
    auto dock1 = new KDDockWidgets::QtWidgets::DockWidget(QStringLiteral("MyDock1"));

    QWidget w;
    w.addAction(dock1->toggleAction());

    delete dock1;
}

void TestQtWidgets::tst_currentTabChanged()
{
    // Tests that QtWidgets::DockWidget::isCurrentTabConnection is emitted

    auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None, "MW1");
    auto dock1 = new KDDockWidgets::QtWidgets::DockWidget(QStringLiteral("MyDock1"));
    auto dock2 = new KDDockWidgets::QtWidgets::DockWidget(QStringLiteral("MyDock2"));

    int count1 = 0;
    int count2 = 0;
    connect(dock1, &QtWidgets::DockWidget::isCurrentTabChanged, [&count1](bool isCurrent) {
        if (isCurrent)
            count1++;
        else
            count1--;
    });

    connect(dock2, &QtWidgets::DockWidget::isCurrentTabChanged, [&count2](bool isCurrent) {
        if (isCurrent)
            count2++;
        else
            count2--;
    });

    m1->addDockWidget(dock1->asDockWidgetController(), Location_OnBottom);
    QCOMPARE(count1, 1);
    QCOMPARE(count2, 0);

    dock1->addDockWidgetAsTab(dock2);
    QCOMPARE(count1, 0);
    QCOMPARE(count2, 1);

    // already current
    dock2->dockWidget()->setAsCurrentTab();
    QCOMPARE(count1, 0);
    QCOMPARE(count2, 1);

    dock1->dockWidget()->setAsCurrentTab();
    QCOMPARE(count1, 1);
    QCOMPARE(count2, 0);

    dock2->dockWidget()->setAsCurrentTab();
    QCOMPARE(count1, 0);
    QCOMPARE(count2, 1);
}

void TestQtWidgets::tst_moveTab_data()
{
    QTest::addColumn<bool>("moveViaController");

    QTest::newRow("true") << true;
    QTest::newRow("false") << false;
}

void TestQtWidgets::tst_moveTab()
{
    QFETCH(bool, moveViaController);

    EnsureTopLevelsDeleted e;
    Config::self().setFlags(Config::Flag_AllowReorderTabs);
    auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None, "MW1");
    auto dockA = Config::self().viewFactory()->createDockWidget("dwA")->asDockWidgetController();
    auto dockB = Config::self().viewFactory()->createDockWidget("dwB")->asDockWidgetController();

    auto qwidgetA = QtCommon::View_qt::asQWidget(dockA->view());
    auto qwidgetB = QtCommon::View_qt::asQWidget(dockB->view());

    m1->addDockWidget(dockA, Location_OnBottom);
    dockA->addDockWidgetAsTab(dockB);

    Core::TabBar *tb = dockA->d->group()->tabBar();
    QVERIFY(tb);
    tb->setCurrentIndex(0);
    QCOMPARE(tb->currentDockWidget(), dockA);
    auto qtabbar = qobject_cast<QTabBar *>(QtCommon::View_qt::asQWidget(tb->view()));
    auto qtabwidget = qobject_cast<QTabWidget *>(QtCommon::View_qt::asQWidget(tb->stack()->view()));
    QVERIFY(qtabbar);
    QVERIFY(qtabwidget);
    QCOMPARE(qtabbar->currentIndex(), 0);
    QCOMPARE(qtabwidget->currentIndex(), 0);
    QCOMPARE(qtabwidget->widget(0), qwidgetA);
    QCOMPARE(qtabwidget->widget(1), qwidgetB);

    if (moveViaController) {
        tb->moveTabTo(0, 1);
    } else {
        qtabbar->moveTab(0, 1);
    }

    QCOMPARE(qtabbar->currentIndex(), 1);
    QCOMPARE(qtabwidget->widget(0), qwidgetB);
    QCOMPARE(qtabwidget->widget(1), qwidgetA);

    QCOMPARE(tb->currentIndex(), 1);
    QCOMPARE(tb->currentDockWidget(), dockA);
}

void TestQtWidgets::tst_nestedMainWindowSaveRestore_data()
{
    QTest::addColumn<bool>("nestFurther");

    QTest::newRow("true") << true; // parented to DockWidget
    QTest::newRow("false") << false; // parented to intermediate container
}

void TestQtWidgets::tst_nestedMainWindowSaveRestore()
{
    // This is for #508 . Do not change this configuration.
    // tests that a save/restore of tabbed nested main windows does not
    // hide the main window


    QFETCH(bool, nestFurther);
    EnsureTopLevelsDeleted e;

    auto mainWindow = createMainWindow(QSize(1000, 1000), MainWindowOption_None, "MW1");
    auto nestedMainWindow1 = createMainWindow(QSize(500, 500), MainWindowOption_None, "MW1.1");
    nestedMainWindow1->setAffinities({ "foo1" });
    auto nestedMainWindow2 = createMainWindow(QSize(500, 500), MainWindowOption_None, "MW1.2");
    nestedMainWindow2->setAffinities({ "foo2" });

    auto containerDock1 = new KDDockWidgets::QtWidgets::DockWidget(QStringLiteral("Nested MainWindow Dock container1"));
    auto containerDock2 = new KDDockWidgets::QtWidgets::DockWidget(QStringLiteral("Nested MainWindow Dock container2"));
    auto nestedMainWindowQWidget1 = static_cast<QMainWindow *>(QtCommon::View_qt::asQWidget(nestedMainWindow1->view()));
    auto nestedMainWindowQWidget2 = static_cast<QMainWindow *>(QtCommon::View_qt::asQWidget(nestedMainWindow2->view()));


    if (nestFurther) {
        auto container1 = new QWidget();
        auto container2 = new QWidget();
        auto lay1 = new QVBoxLayout(container1);
        auto lay2 = new QVBoxLayout(container2);
        lay1->addWidget(nestedMainWindowQWidget1);
        lay2->addWidget(nestedMainWindowQWidget2);

        containerDock1->setWidget(container1);
        containerDock2->setWidget(container2);
    } else {
        containerDock1->setWidget(nestedMainWindowQWidget1);
        containerDock2->setWidget(nestedMainWindowQWidget2);
    }

    mainWindow->addDockWidget(containerDock1->asDockWidgetController(), KDDockWidgets::Location_OnRight);
    mainWindow->addDockWidget(containerDock2->asDockWidgetController(), KDDockWidgets::Location_OnRight);

    containerDock1->addDockWidgetAsTab(containerDock2);
    containerDock1->setAsCurrentTab();

    LayoutSaver saver;
    QVERIFY(saver.restoreLayout(saver.serializeLayout()));
    QVERIFY(mainWindow->isVisible());
}

void TestQtWidgets::tst_nestedMainWindowFloatButton()
{
    // Bug 1 reported in #464:
    // Dockwidget, inside MainWindow inside MainWindow.
    // Float inner main window
    // DockWidget's float button stops working
    EnsureTopLevelsDeleted e;
    auto mainWindow = createMainWindow(QSize(1000, 1000), MainWindowOption_None, "MW1");
    auto nestedMainWindow = createMainWindow(QSize(1000, 1000), MainWindowOption_None, "MW2");
    mainWindow->setObjectName("root main window");

    auto containerDock = new KDDockWidgets::QtWidgets::DockWidget(QStringLiteral("Nested MainWindow Dock container"));
    auto nestedMainWindowQWidget = static_cast<QMainWindow *>(QtCommon::View_qt::asQWidget(nestedMainWindow->view()));
    containerDock->setWidget(nestedMainWindowQWidget);
    mainWindow->addDockWidget(containerDock->asDockWidgetController(), Location_OnBottom);

    auto nestedDock = new KDDockWidgets::QtWidgets::DockWidget(QStringLiteral("Nested Dock"));
    nestedMainWindow->addDockWidget(nestedDock->asDockWidgetController(), Location_OnBottom);
    nestedMainWindowQWidget->menuBar()->addMenu("Inner menu");
    nestedMainWindowQWidget->setObjectName("nested main window");

    QVERIFY(!containerDock->isFloating());
    QVERIFY(!nestedDock->isFloating());
    QVERIFY(containerDock->dockWidget()->isInMainWindow());
    QVERIFY(nestedDock->dockWidget()->isInMainWindow());

    containerDock->setFloating(true);

    QVERIFY(containerDock->isFloating());
    QVERIFY(!nestedDock->isFloating());
    QVERIFY(!containerDock->dockWidget()->isInMainWindow());
    QVERIFY(nestedDock->dockWidget()->isInMainWindow());
}

void TestQtWidgets::tst_nestedMainWindowToggle()
{
    EnsureTopLevelsDeleted e;
    auto mainWindow = createMainWindow(QSize(1000, 1000), MainWindowOption_None, "MW1");
    auto nestedMainWindow = createMainWindow(QSize(1000, 1000), MainWindowOption_None, "MW2");
    mainWindow->setObjectName("root main window");

    auto dock1 = new KDDockWidgets::QtWidgets::DockWidget(QStringLiteral("Nested MainWindow Dock container"));
    auto nestedMainWindowQWidget = static_cast<QMainWindow *>(QtCommon::View_qt::asQWidget(nestedMainWindow->view()));
    dock1->setWidget(nestedMainWindowQWidget);
    mainWindow->addDockWidget(dock1->asDockWidgetController(), Location_OnBottom);

    auto nestedDock = new KDDockWidgets::QtWidgets::DockWidget(QStringLiteral("Nested Dock"));
    nestedMainWindow->addDockWidget(nestedDock->asDockWidgetController(), Location_OnBottom);
    nestedMainWindowQWidget->menuBar()->addMenu("Just a visual cue, to notice the nesting");
    nestedMainWindowQWidget->setObjectName("nested main window");
    QPointer<QObject> guard = nestedMainWindowQWidget;

    // Close dock1:
    QVERIFY(dock1->isOpen());
    QVERIFY(nestedDock->isOpen());

    dock1->close();
    QVERIFY(guard); // For some reason nested main window was being deleted
    QVERIFY(!dock1->isOpen());
    QVERIFY(!nestedDock->isOpen());

    // Reopen dock1, the nested dockwidgets should also reopen

    dock1->open();

    QVERIFY(guard);
    QVERIFY(dock1->isOpen());
    QVERIFY(dock1->isVisible());
    QVERIFY(nestedMainWindowQWidget->isVisible());

    QEXPECT_FAIL("", "Bug #360, to be fixed", Continue);
    QVERIFY(nestedDock->isOpen());
}

void TestQtWidgets::tstQGraphicsProxyWidget()
{
    // Tests that using a QGraphicsProxyWidget doesn't crash

    auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None, "MW1");
    auto dock1 = new KDDockWidgets::QtWidgets::DockWidget(QStringLiteral("MyDock1"));
    m1->addDockWidget(dock1->asDockWidgetController(), Location_OnBottom);

    auto qgv = new QGraphicsView();
    dock1->setWidget(qgv);
    qgv->setVisible(true);

    auto scene = new QGraphicsScene();
    qgv->setScene(scene);

    auto lineEdit = new QLineEdit();
    auto proxyWidget = new QGraphicsProxyWidget();
    proxyWidget->setWidget(lineEdit);
    lineEdit->setText("Test");

    QVERIFY(lineEdit->graphicsProxyWidget());
    QVERIFY(lineEdit->isWindow());

    scene->addItem(proxyWidget);
}

void TestQtWidgets::tst_focusBetweenTabs()
{
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_TitleBarIsFocusable);
    auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_None, "mw1");

    auto floatingDock = new QtWidgets::DockWidget(QStringLiteral("floatingDock"));
    auto leFloating = new QLineEdit("floating");
    floatingDock->setWidget(leFloating);
    floatingDock->show();

    auto dock1 = new QtWidgets::DockWidget(QStringLiteral("MyDock1"));
    auto le1 = new QLineEdit("text1");
    dock1->setWidget(le1);

    auto dock2 = new QtWidgets::DockWidget(QStringLiteral("MyDock2"));
    auto le2 = new QLineEdit("text2");
    dock2->setWidget(le2);

    auto dock3 = new QtWidgets::DockWidget(QStringLiteral("MyDock3"));
    auto le3 = new QLineEdit("text3");
    dock3->setWidget(le3);

    m1->addDockWidget(dock1->asDockWidgetController(), Location_OnLeft);
    m1->addDockWidget(dock2->asDockWidgetController(), Location_OnRight);
    dock2->addDockWidgetAsTab(dock3);

    // 1. Setup: Give focus to le2 and le3, just so our focus scope remembers they were focused.
    le1->setFocus();
    leFloating->setFocus();
    QVERIFY(dock3->dockWidget()->isCurrentTab());
    m1->view()->activateWindow();
    EVENT_LOOP(1);
    le3->setFocus();

    QVERIFY(le3->hasFocus());
    dock2->setAsCurrentTab();
    QVERIFY(dock2->dockWidget()->isCurrentTab());
    le2->setFocus();
    EVENT_LOOP(1);
    QVERIFY(le2->hasFocus());

    // 2. Now, cycling tabs should toggle focus between le2 and le3
    dock3->setAsCurrentTab();
    QVERIFY(le3->hasFocus());
    QVERIFY(!le2->hasFocus());

    dock2->setAsCurrentTab();
    QVERIFY(le2->hasFocus());
    QVERIFY(!le3->hasFocus());

    // 3. Check that focusing titlebar focuses the previous focused line edit as well
    auto titlebar1 = dock1->actualTitleBar()->view();
    titlebar1->setFocus(Qt::MouseFocusReason);
    QVERIFY(le1->hasFocus());
    QVERIFY(!le2->hasFocus());
    QVERIFY(!le3->hasFocus());

    // 4. Test with a floating window as well
    floatingDock->rootView()->activateWindow();
    QVERIFY(Platform::instance()->tests_waitForWindowActive(floatingDock->window(), 1000));
    QVERIFY(floatingDock->window()->isActive());
    auto titlebarFloating = floatingDock->actualTitleBar()->view();
    QVERIFY(titlebarFloating->isVisible());
    titlebarFloating->setFocus(Qt::MouseFocusReason);
    EVENT_LOOP(1000);

    QVERIFY(leFloating->hasFocus());
    QVERIFY(!le1->hasFocus());
    QVERIFY(!le2->hasFocus());
    QVERIFY(!le3->hasFocus());
}

void TestQtWidgets::addDockWidgetToSide()
{
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_TitleBarIsFocusable);
    auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_HasCentralGroup, "mw1");

    auto d1 = new QtWidgets::DockWidget("d1");
    auto d2 = new QtWidgets::DockWidget("d2");
    auto d3 = new QtWidgets::DockWidget("d3");
    auto d4 = new QtWidgets::DockWidget("d4");
    auto dTop = new QtWidgets::DockWidget("dTop");
    auto dTop2 = new QtWidgets::DockWidget("dTop2");
    QVERIFY(!d1->isOpen());
    QVERIFY(!d1->toggleAction()->isChecked());
    m1->addDockWidgetToSide(d1->asDockWidgetController(), KDDockWidgets::Location_OnLeft);
    QVERIFY(d1->isOpen());
    QVERIFY(d1->toggleAction()->isChecked());
    m1->addDockWidgetToSide(d2->asDockWidgetController(), KDDockWidgets::Location_OnLeft);
    m1->addDockWidgetToSide(d3->asDockWidgetController(), KDDockWidgets::Location_OnRight);
    m1->addDockWidgetToSide(dTop->asDockWidgetController(), KDDockWidgets::Location_OnTop);
    m1->addDockWidgetToSide(dTop2->asDockWidgetController(), KDDockWidgets::Location_OnTop);
    m1->addDockWidgetToSide(d4->asDockWidgetController(), KDDockWidgets::Location_OnRight);

    auto root = m1->layout()->rootItem()->asBoxContainer();
    QVERIFY(root->isVertical());

    auto topContainer = root->childItems()[0]->asBoxContainer();
    QVERIFY(!topContainer->isVertical());
    QCOMPARE(topContainer->numChildren(), 2);

    QCOMPARE(Group::fromItem(topContainer->childItems()[0])->objectName(), "dTop");
    QCOMPARE(Group::fromItem(topContainer->childItems()[1])->objectName(), "dTop2");

    auto bottomContainer = root->childItems()[1]->asBoxContainer();
    QVERIFY(!bottomContainer->isVertical());
    QCOMPARE(bottomContainer->numChildren(), 3);

    auto leftContainer = bottomContainer->childItems()[0]->asBoxContainer();
    auto rightContainer = bottomContainer->childItems()[2]->asBoxContainer();
    QVERIFY(leftContainer->isVertical());
    QVERIFY(rightContainer->isVertical());
    QCOMPARE(leftContainer->numChildren(), 2);
    QCOMPARE(rightContainer->numChildren(), 2);

    QCOMPARE(Group::fromItem(leftContainer->childItems()[0])->objectName(), "d1");
    QCOMPARE(Group::fromItem(leftContainer->childItems()[1])->objectName(), "d2");
    QCOMPARE(Group::fromItem(rightContainer->childItems()[0])->objectName(), "d3");
    QCOMPARE(Group::fromItem(rightContainer->childItems()[1])->objectName(), "d4");
}

void TestQtWidgets::addDockWidgetToSide2()
{
    // Tests adding relative to a StartHidden

    EnsureTopLevelsDeleted e;
    auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_HasCentralGroup, "mw1");

    auto d1 = new QtWidgets::DockWidget("d1");
    auto d2 = new QtWidgets::DockWidget("d2");

    QVERIFY(!d1->isOpen());
    QVERIFY(!d1->toggleAction()->isChecked());
    m1->addDockWidgetToSide(d1->asDockWidgetController(), KDDockWidgets::Location_OnRight, InitialVisibilityOption::StartHidden);
    QVERIFY(!d1->isOpen());
    QVERIFY(!d1->toggleAction()->isChecked());

    m1->addDockWidgetToSide(d2->asDockWidgetController(), KDDockWidgets::Location_OnRight);

    d1->show();

    auto root = m1->layout()->rootItem()->asBoxContainer();
    QVERIFY(root->isHorizontal());
    QCOMPARE(root->numChildren(), 2);
}

void TestQtWidgets::addDockWidgetToSide3()
{
    // Tests adding relative to a StartHidden but the new one is also hidden
    EnsureTopLevelsDeleted e;
    auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_HasCentralGroup, "mw1");

    auto d1 = new QtWidgets::DockWidget("d1");
    auto d2 = new QtWidgets::DockWidget("d2");
    m1->addDockWidgetToSide(d1->asDockWidgetController(), KDDockWidgets::Location_OnRight, InitialVisibilityOption::StartHidden);
    m1->addDockWidgetToSide(d2->asDockWidgetController(), KDDockWidgets::Location_OnRight, InitialVisibilityOption::StartHidden);

    auto root = m1->layout()->rootItem()->asBoxContainer();
    QVERIFY(root->isHorizontal());
    QCOMPARE(root->numChildren(), 2);

    d1->show();
    d2->show();

    auto inner = root->childItems()[1]->asBoxContainer();
    QVERIFY(inner);
    QVERIFY(inner->isVertical());
    QCOMPARE(inner->numChildren(), 2);
    QCOMPARE(inner->numVisibleChildren(), 2);
}

void TestQtWidgets::addDockWidgetToSide4()
{
    // Tests a case where generated layout would be off by a few pixels
    EnsureTopLevelsDeleted e;
    auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_HasCentralGroup, "mw1");

    auto dummy1 = new QtWidgets::DockWidget("dummy1");
    auto dummy2 = new QtWidgets::DockWidget("dummy2");
    m1->addDockWidget(dummy1->asDockWidgetController(), KDDockWidgets::Location_OnRight, nullptr, InitialVisibilityOption::StartHidden);
    m1->addDockWidget(dummy2->asDockWidgetController(), KDDockWidgets::Location_OnLeft, nullptr, InitialVisibilityOption::StartHidden);

    auto leftVisible = new QtWidgets::DockWidget("leftVisible");
    auto leftHidden = new QtWidgets::DockWidget("leftHidden");
    auto bottomHidden = new QtWidgets::DockWidget("bottomHidden");
    auto rightVisible = new QtWidgets::DockWidget("rightVisible");
    auto leftVisible2 = new QtWidgets::DockWidget("leftVisible2");
    auto bottomHidden2 = new QtWidgets::DockWidget("bottomHidden2");
    auto rightHidden = new QtWidgets::DockWidget("rightHidden");
    auto rightHidden2 = new QtWidgets::DockWidget("rightHidden2");

    m1->addDockWidgetToSide(leftVisible->asDockWidgetController(), KDDockWidgets::Location_OnLeft);
    m1->addDockWidgetToSide(leftHidden->asDockWidgetController(), KDDockWidgets::Location_OnLeft, InitialVisibilityOption::StartHidden);
    m1->addDockWidgetToSide(bottomHidden->asDockWidgetController(), KDDockWidgets::Location_OnBottom, InitialVisibilityOption::StartHidden);

    m1->addDockWidgetToSide(leftVisible2->asDockWidgetController(), KDDockWidgets::Location_OnLeft);

    m1->addDockWidgetToSide(bottomHidden2->asDockWidgetController(), KDDockWidgets::Location_OnBottom, InitialVisibilityOption::StartHidden);
    m1->addDockWidgetToSide(rightHidden->asDockWidgetController(), KDDockWidgets::Location_OnRight, InitialVisibilityOption::StartHidden);
    m1->addDockWidgetToSide(rightHidden2->asDockWidgetController(), KDDockWidgets::Location_OnRight, InitialVisibilityOption::StartHidden);

    leftVisible->open();

    QVERIFY(m1->layout()->checkSanity());
    m1->addDockWidgetToSide(rightVisible->asDockWidgetController(), KDDockWidgets::Location_OnRight);
    QVERIFY(m1->layout()->checkSanity());
}

void TestQtWidgets::addDockWidgetToSide5()
{
    // Tests a case where generated layout would be off by a few pixels
    EnsureTopLevelsDeleted e;
    auto m1 = createMainWindow(QSize(1002, 1002), MainWindowOption_HasCentralGroup, "mw1");

    auto rightVisible = new QtWidgets::DockWidget("rightVisible");
    auto rightHidden = new QtWidgets::DockWidget("rightHidden");
    auto rightHidden2 = new QtWidgets::DockWidget("rightHidden2");

    m1->addDockWidgetToSide(rightHidden->asDockWidgetController(), KDDockWidgets::Location_OnRight, InitialVisibilityOption::StartHidden);
    m1->addDockWidgetToSide(rightHidden2->asDockWidgetController(), KDDockWidgets::Location_OnRight, InitialVisibilityOption::StartHidden);

    QVERIFY(m1->layout()->checkSanity());
    m1->addDockWidgetToSide(rightVisible->asDockWidgetController(), KDDockWidgets::Location_OnRight);
    QVERIFY(m1->layout()->checkSanity());
}

void TestQtWidgets::addDockWidgetToSideCrash()
{
    // There used to be a crash when adding this layout setup.
    // This test just ensures it doesn't regress
    {
        EnsureTopLevelsDeleted e;
        auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_HasCentralGroup, "mw1");

        auto bottom1 = new QtWidgets::DockWidget("bottom1");
        auto left1 = new QtWidgets::DockWidget("left1");
        auto bottom2 = new QtWidgets::DockWidget("bottom2");
        auto right1 = new QtWidgets::DockWidget("right1");

        m1->addDockWidgetToSide(bottom1->asDockWidgetController(), KDDockWidgets::Location_OnBottom, InitialVisibilityOption::StartHidden);
        m1->addDockWidgetToSide(left1->asDockWidgetController(), KDDockWidgets::Location_OnLeft);
        m1->addDockWidgetToSide(bottom2->asDockWidgetController(), KDDockWidgets::Location_OnBottom, InitialVisibilityOption::StartHidden);

        QVERIFY(m1->layout()->checkSanity());
        bottom1->open();
        bottom2->open();
        QVERIFY(m1->layout()->checkSanity());

        auto centralGroup = m1->dropArea()->centralGroup();
        auto centralItem = centralGroup->layoutItem();
        Core::Item *neighbor = centralItem->outermostNeighbor(KDDockWidgets::Location_OnRight, /*visibleOnly=*/false);
        QVERIFY(!neighbor);

        m1->addDockWidgetToSide(right1->asDockWidgetController(), KDDockWidgets::Location_OnRight);
    }

    {
        EnsureTopLevelsDeleted e;
        auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_HasCentralGroup, "mw1");

        auto dummy1 = new QtWidgets::DockWidget("dummy1");
        auto dummy2 = new QtWidgets::DockWidget("dummy2");

        auto left1 = new QtWidgets::DockWidget("left1");
        auto bottom1 = new QtWidgets::DockWidget("bottom1");
        auto left2 = new QtWidgets::DockWidget("left2");

        m1->addDockWidgetToSide(dummy1->asDockWidgetController(), KDDockWidgets::Location_OnLeft, InitialVisibilityOption::StartHidden);
        m1->addDockWidgetToSide(dummy2->asDockWidgetController(), KDDockWidgets::Location_OnRight, InitialVisibilityOption::StartHidden);
        m1->addDockWidgetToSide(left1->asDockWidgetController(), KDDockWidgets::Location_OnLeft, InitialVisibilityOption::StartHidden);
        m1->addDockWidgetToSide(bottom1->asDockWidgetController(), KDDockWidgets::Location_OnBottom, InitialVisibilityOption::StartHidden);
        m1->addDockWidgetToSide(left2->asDockWidgetController(), KDDockWidgets::Location_OnLeft, InitialVisibilityOption::StartVisible);
    }
}

void TestQtWidgets::userHiddenButton()
{
    EnsureTopLevelsDeleted e;
    auto d1 = new QtWidgets::DockWidget("d1");
    d1->show();
    auto tb = d1->actualTitleBar();
    auto tbWidget = QtCommon::View_qt::asQWidget(tb->view());
    auto buttons = tbWidget->findChildren<QAbstractButton *>();
    QCOMPARE(buttons.size(), 5);

    const auto numVisible = std::count_if(buttons.cbegin(), buttons.cend(), [](auto button) {
        return button->isVisible();
    });

    QCOMPARE(numVisible, 2);

    // Hide float and close:
    tb->setUserHiddenButtons(TitleBarButtonTypes(TitleBarButtonType::Close) | TitleBarButtonType::Float);

    // 0 visible buttons now:
    QCOMPARE(std::count_if(buttons.cbegin(), buttons.cend(), [](auto button) {
                 return button->isVisible();
             }),
             0);
}

void TestQtWidgets::tst_tabAsCentralWidget()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(600, 600), MainWindowOption_HasCentralWidget);
    auto tabWidget = new QTabWidget();
    auto tab1 = new QWidget();
    auto tab2 = new QWidget();
    tabWidget->addTab(tab1, "tab1");
    tabWidget->addTab(tab2, "tab2");

    m->setPersistentCentralView(QtWidgets::ViewWrapper::create(tabWidget));

    auto d1 = new QtWidgets::DockWidget("d1");
    auto d2 = new QtWidgets::DockWidget("d2");
    auto d3 = new QtWidgets::DockWidget("d3");
    m->addDockWidget(d1->dockWidget(), KDDockWidgets::Location_OnRight);
    m->addDockWidget(d2->dockWidget(), KDDockWidgets::Location_OnRight);
    m->addDockWidget(d3->dockWidget(), KDDockWidgets::Location_OnRight);
}

void TestQtWidgets::tst_nonClosable()
{
    EnsureTopLevelsDeleted e;
    auto d1 = NonClosableDockWidget("d1");
    d1.open();
    QVERIFY(d1.isOpen());
    d1.close();
    QVERIFY(d1.isOpen());
    d1.forceClose();
    QVERIFY(!d1.isOpen());
}

void TestQtWidgets::tst_crashDuringRestore()
{
    // Contrived case where if dockWidget->open() was called during restore it would crash

    EnsureTopLevelsDeleted e;
    auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_HasCentralGroup, "mw1");
    auto d1 = new QtWidgets::DockWidget("d1");
    auto d3 = new QtWidgets::DockWidget("d3");
    m1->addDockWidget(d1->asDockWidgetController(), Location_OnRight);
    d1->addDockWidgetAsTab(d3);

    connect(d3->toggleAction(), &QAction::toggled, this, [d3](bool) {
        d3->open();
    });

    LayoutSaver saver;
    const QByteArray saved = saver.serializeLayout();

    saver.restoreLayout(saved);
}

void TestQtWidgets::tst_toggleVsShowHidden()
{
    // Tests that the QAction doesn't fire when adding as hidden
    EnsureTopLevelsDeleted e;
    auto m1 = createMainWindow(QSize(1000, 1000), MainWindowOption_HasCentralGroup, "mw1");
    auto d1 = new QtWidgets::DockWidget("d1");
    QVERIFY(!d1->toggleAction()->isChecked());
    QVERIFY(!d1->isOpen());
    int count = 0;
    connect(d1->toggleAction(), &QAction::toggled, this, [&count](bool) {
        count++;
    });

    m1->addDockWidget(d1->asDockWidgetController(), Location_OnRight, nullptr, KDDockWidgets::InitialVisibilityOption::StartHidden);
    QVERIFY(!d1->toggleAction()->isChecked());
    QVERIFY(!d1->isOpen());

    QCOMPARE(count, 0);
}

void TestQtWidgets::tst_neighbourSqueezeStrategy()
{
    // Tests NeighbourSqueezeStrategy::ImmediateNeighboursFirst
    {
        EnsureTopLevelsDeleted e;
        InitialOption::s_defaultNeighbourSqueezeStrategy = NeighbourSqueezeStrategy::ImmediateNeighboursFirst;
        auto m1 = createMainWindow(QSize(1000, 500), {}, "mw1");

        auto d1 = new QtWidgets::DockWidget("d1");
        auto d2 = new QtWidgets::DockWidget("d2");
        auto d3 = new QtWidgets::DockWidget("d3");
        auto d4 = new QtWidgets::DockWidget("d4");

        m1->addDockWidget(d1->dockWidget(), KDDockWidgets::Location_OnRight);
        m1->addDockWidget(d2->dockWidget(), KDDockWidgets::Location_OnRight);
        m1->addDockWidget(d3->dockWidget(), KDDockWidgets::Location_OnBottom);
        InitialOption opt = QSize(100, 0);
        opt.visibility = InitialVisibilityOption::StartHidden;
        m1->addDockWidget(d4->dockWidget(), KDDockWidgets::Location_OnRight, d2->dockWidget(), opt);
        m1->layoutEqually();

        auto group1 = d1->dockWidget()->dptr()->group();
        const auto sz1 = group1->size();
        d4->open();
        QCOMPARE(sz1, group1->size());
    }
}

namespace {

class Stack464 : public QtWidgets::Stack
{
public:
    using QtWidgets::Stack::Stack;
    void init() override
    {
        m_stack->setHideDisabledButtons(TitleBarButtonType::Close);

        QtWidgets::Stack::init(); // important
    }
};

class ViewFactory464 : public QtWidgets::ViewFactory
{
public:
    Core::View *createStack(Core::Stack *controller, Core::View *parent) const override
    {
        return new Stack464(controller, QtCommon::View_qt::asQWidget(parent));
    }
};

}

void TestQtWidgets::tst_debugWidgetViewer()
{
    // Tests that DebugWidgetViewer builds and can be created destroyed
    // not worth doing fancy tests as it's a debugging aid
    DebugWidgetViewer viewer;
}

void TestQtWidgets::tst_addDockWidgetToContainingWindowNested()
{
    {
        EnsureTopLevelsDeleted e;

        auto m1 = createMainWindow(QSize(1000, 500), {}, "mw1");
        auto d1 = new QtWidgets::DockWidget("d1");
        auto d2 = new QtWidgets::DockWidget("d2");

        m1->addDockWidget(d1->dockWidget(), Location_OnRight);
        d1->dockWidget()->addDockWidgetToContainingWindow(d2->dockWidget(), KDDockWidgets::Location_OnLeft);

        QVERIFY(d1->dockWidget()->isInMainWindow());
        QVERIFY(d2->dockWidget()->isInMainWindow());
    }

    {
        // Tests using addDockWidgetToContainingWindow when dock is nested
        EnsureTopLevelsDeleted e;

        auto m1 = createMainWindow(QSize(1000, 500), {}, "mw1");
        auto nestedMainWindow = createMainWindow(QSize(1000, 500), {}, "mw2");

        auto d1 = new KDDockWidgets::QtWidgets::DockWidget(QStringLiteral("Nested MainWindow Dock container"));
        auto nestedMainWindowQWidget = static_cast<QMainWindow *>(QtCommon::View_qt::asQWidget(nestedMainWindow->view()));
        d1->setWidget(nestedMainWindowQWidget);
        m1->addDockWidget(d1->asDockWidgetController(), Location_OnBottom);

        auto d2 = new QtWidgets::DockWidget("d2");
        nestedMainWindow->addDockWidget(d2->dockWidget(), Location_OnRight);

        auto d3 = new QtWidgets::DockWidget("d3");
        d2->dockWidget()->addDockWidgetToContainingWindow(d3->dockWidget(), Location_OnRight);

        QVERIFY(d1->dockWidget()->isInMainWindow());
        QVERIFY(d2->dockWidget()->isInMainWindow());
        QVERIFY(d3->dockWidget()->isInMainWindow());

        QCOMPARE(d1->dockWidget()->mainWindow(), m1.get());
        QCOMPARE(d2->dockWidget()->mainWindow(), nestedMainWindow.get());
        QCOMPARE(d3->dockWidget()->mainWindow(), nestedMainWindow.get());
    }
}

void TestQtWidgets::tst_tabBarIcons()
{
    {
        EnsureTopLevelsDeleted e;
        auto &config = Config::self();
        config.setFlags(config.flags()
                        | KDDockWidgets::Config::Flag_HideTitleBarWhenTabsVisible
                        | KDDockWidgets::Config::Flag_TabsHaveCloseButton
                        | KDDockWidgets::Config::Flag_CloseOnlyCurrentTab
                        | KDDockWidgets::Config::Flag_ShowButtonsOnTabBarIfTitleBarHidden);

        auto d1 = new QtWidgets::DockWidget("d1", KDDockWidgets::DockWidgetOption_NotClosable);
        auto d2 = new QtWidgets::DockWidget("d2", KDDockWidgets::DockWidgetOption_NotClosable);

        d1->addDockWidgetAsTab(d2);

        auto stack = d1->dockWidget()->dptr()->group()->stack();
        auto tabWidget = qobject_cast<QtWidgets::Stack *>(QtCommon::View_qt::asQWidget(stack->view()));
        QVERIFY(tabWidget);

        auto closeButton = tabWidget->button(TitleBarButtonType::Close);
        QVERIFY(closeButton);
        QVERIFY(closeButton->isVisible());
        QVERIFY(!closeButton->isEnabled());
    }

    {
        EnsureTopLevelsDeleted e;
        auto &config = Config::self();
        config.setFlags(config.flags()
                        | KDDockWidgets::Config::Flag_HideTitleBarWhenTabsVisible
                        | KDDockWidgets::Config::Flag_TabsHaveCloseButton
                        | KDDockWidgets::Config::Flag_CloseOnlyCurrentTab
                        | KDDockWidgets::Config::Flag_ShowButtonsOnTabBarIfTitleBarHidden);
        config.setViewFactory(new ViewFactory464());

        auto d1 = new QtWidgets::DockWidget("d1", KDDockWidgets::DockWidgetOption_NotClosable);
        auto d2 = new QtWidgets::DockWidget("d2", KDDockWidgets::DockWidgetOption_NotClosable);

        d1->addDockWidgetAsTab(d2);

        auto stack = d1->dockWidget()->dptr()->group()->stack();
        auto tabWidget = qobject_cast<QtWidgets::Stack *>(QtCommon::View_qt::asQWidget(stack->view()));
        QVERIFY(tabWidget);

        auto closeButton = tabWidget->button(TitleBarButtonType::Close);
        QVERIFY(closeButton);
        QVERIFY(!closeButton->isVisible());
        QVERIFY(!closeButton->isEnabled());
    }
}

void TestQtWidgets::tst_indicatorsNotShowing()
{
    // Tests bug #474, where wrong top level window is detected under cursor
    EnsureTopLevelsDeleted e;
    const Point globalPos = { 600, 300 };
    QCursor::setPos(globalPos);

    auto m1 = createMainWindow(QSize(1000, 500), {}, "mw1");
    auto m2 = createMainWindow(QSize(1000, 500), {}, "mw2");
    // m2->setAffinities({ "m2" });
    auto d2 = new QtWidgets::DockWidget("d2");
    // d2->setAffinities({ "m2" });
    d2->show();
    QTest::qWait(200);
    m2->view()->move(0, 0);
    m1->view()->move(500, 250);
    m1->view()->raiseAndActivate();
    m1->view()->setWindowTitle("m1");

    auto mainWindow1 = dynamic_cast<QtWidgets::MainWindow *>(m1->view());
    QVERIFY(QTest::qWaitForWindowActive(mainWindow1));

    auto dc = DragController::instance();

    dc->programmaticStartDrag(d2->dockWidget()->titleBar(), globalPos, { 10, 5 });

    auto tlw = dc->qtTopLevelUnderCursor();
    QVERIFY(tlw);

    /// Fixed on windows and Linux. Other platforms don't have the required API
    /// to get correct z-order of windows under cursor
    const bool supportsZOrderedWindowSearch = KDDockWidgets::isWindows() || (KDDockWidgets::isXCB() && KDDockWidgets::linksToXLib());
    if (!supportsZOrderedWindowSearch)
        QEXPECT_FAIL("", "Not supported on this platform", Continue);

    QCOMPARE(tlw->controller(), m1.get());

    dc->programmaticStopDrag();
}

void TestQtWidgets::tst_restoreInvalidPercentages()
{
    EnsureTopLevelsDeleted e;

    auto m = createMainWindow(Size(500, 500), MainWindowOption_HasCentralWidget, "mainWindowId1");

    createDockWidget("_kddw_internal_dummy", Platform::instance()->tests_createView({ true }));
    createDockWidget("_kddw_internal_dummy2", Platform::instance()->tests_createView({ true }));
    for (int i = 0; i <= 8; ++i) {
        new QtWidgets::DockWidget(QStringLiteral("dockwidget_tests_%1").arg(i));
    }

    bool ok = false;
    LayoutSaver restorer;
    const QByteArray data = Platform::instance()->readFile(":/layouts/invalidPercentages.json", /*by-ref*/ ok);
    QVERIFY(ok);
    QVERIFY(restorer.restoreLayout(data));

    LayoutSaver saver;
    QVERIFY(!saver.serializeLayout().isEmpty());
}


void TestQtWidgets::tst_controllerToView()
{
    EnsureTopLevelsDeleted e;
    auto dw = createDockWidget("dw1", Platform::instance()->tests_createView({ true }));
    auto dwView = KDDockWidgets::controllerToView<QtWidgets::DockWidget>(dw);

    std::vector<Core::DockWidget *> dws = { dw };
    auto dwViews = KDDockWidgets::controllersToViews<QtWidgets::DockWidget>(dws);

    QCOMPARE(dw->view(), dwView);
    QCOMPARE(dws[0]->view(), dwView);
}

int main(int argc, char *argv[])
{
#ifdef KDDW_HAS_SPDLOG
    FatalLogger::create();
#endif

    // Might be disabled by env var
    const auto frontends = Platform::frontendTypes();
    if (std::find(frontends.cbegin(), frontends.cend(), FrontendType::QtWidgets)
        == frontends.cend())
        return 0;

    Platform::tests_initPlatform(argc, argv, FrontendType::QtWidgets);

    TestQtWidgets test;
    const int exitCode = QTest::qExec(&test, argc, argv);
    Platform::tests_deinitPlatform();

    return exitCode;
}

#include "tst_qtwidgets.moc"

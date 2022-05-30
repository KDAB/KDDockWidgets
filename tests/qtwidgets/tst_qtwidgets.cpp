/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/// @file
/// @brief Here lives the tests that only apply to QtWidgets
/// either because they haven't been ported to QtQuick yet or because they are really
/// QtWidgets specific.

#include "Platform.h"
#include "KDDockWidgets.h"
#include "../utils.h"
#include "Config.h"
#include "LayoutSaver.h"
#include "LayoutSaver_p.h"
#include "WindowBeingDragged_p.h"
#include "ViewFactory.h"

#include "multisplitter/Item_p.h"

#include "controllers/DropArea.h"
#include "controllers/Separator.h"
#include "controllers/Frame.h"
#include "controllers/DockWidget.h"
#include "controllers/MainWindow.h"

#include "qtwidgets/MDIArea.h"
#include "qtwidgets/views/MainWindow_qtwidgets.h"
#include "qtwidgets/views/ViewWrapper_qtwidgets.h"
#include "Platform.h"

#include <QObject>
#include <QPushButton>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QtTest/QtTest>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Controllers;
using namespace KDDockWidgets::Tests;
using namespace Layouting;

/// Helper function so we don't write such a big line everywhere
inline Controllers::DockWidget *newDockWidget(const QString &uniqueName,
                                              Controllers::DockWidget::Options opts = {},
                                              Controllers::DockWidget::LayoutSaverOptions layoutSaverOptions = {})
{
    return Config::self().viewFactory()->createDockWidget(uniqueName, opts, layoutSaverOptions)->asDockWidgetController();
}


inline Controllers::DockWidget *createDockWidget(const QString &name, QWidget *w,
                                                 Controllers::DockWidget::Options options = {},
                                                 Controllers::DockWidget::LayoutSaverOptions layoutSaverOptions = {},
                                                 bool show = true,
                                                 const QString &affinityName = {})
{
    w->setFocusPolicy(Qt::StrongFocus);
    auto dock = newDockWidget(name, options, layoutSaverOptions);
    dock->setAffinityName(affinityName);
    dock->setGuestView(std::shared_ptr<ViewWrapper>(new Views::ViewWrapper_qtwidgets(w)));
    dock->setObjectName(name);
    dock->view()->setGeometry(QRect(0, 0, 400, 400));
    if (show) {
        dock->show();
        dock->dptr()->morphIntoFloatingWindow();
        dock->view()->activateWindow();
        Q_ASSERT(dock->window());
        if (Platform::instance()->tests_waitForWindowActive(dock->view()->window(), 1000)) {
            return dock;
        }
        qWarning() << Q_FUNC_INFO << "Couldn't activate window";
        return nullptr;
    } else {
        return dock;
    }
};

inline EmbeddedWindow *createEmbeddedMainWindow(QSize sz)
{
    static int count = 0;
    count++;
    // Tests a MainWindow which isn't a top-level window, but is embedded in another window
    auto mainwindow = createMainWindow(QSize(600, 600), MainWindowOption_HasCentralFrame).release();

    auto window = new EmbeddedWindow(mainwindow);

    auto lay = new QVBoxLayout(window);
    lay->setContentsMargins(100, 100, 100, 100);
    lay->addWidget(qobject_cast<QWidget *>(mainwindow->view()->asQObject()));

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

    // But these are fine to be widget only:
    void tst_tabsNotClickable();
    void tst_embeddedMainWindow();
    void tst_restoreEmbeddedMainWindow();
    void tst_negativeAnchorPositionWhenEmbedded();
    void tst_negativeAnchorPositionWhenEmbedded_data();
    void tst_closeRemovesFromSideBar();
    void tst_restoreSideBar();
    void tst_toggleActionOnSideBar();
    void tst_deleteOnCloseWhenOnSideBar();
    void tst_sidebarOverlayShowsAutohide();
    void tst_sidebarOverlayGetsHiddenOnClick();
    void tst_floatRemovesFromSideBar();
    void tst_overlayedGeometryIsSaved();
    void tst_overlayCrash();

    // And fix these
    void tst_floatingWindowDeleted();
    void tst_addToSmallMainWindow6();
    void tst_minSizeChanges();
    void tst_maxSizePropagates();
    void tst_maxSizePropagates2();
    void tst_maxSizedFloatingWindow();
    void tst_restoreResizesLayout();
    void tst_restoreNonRelativeFloatingWindowGeometry();
    void tst_maxSizeHonouredWhenDropped();
    void tst_fixedSizePolicy();
    void tst_maxSizeHonouredWhenAnotherDropped();
    void tst_addToHiddenMainWindow();
    void tst_maximumSizePolicy();
    void tst_complex();
    void tst_restoreFloatingMaximizedState();
};

void TestQtWidgets::tst_tabsNotClickable()
{
    // Well, not a great unit-test, as it's only repro when it's Windows sending the native event
    // Can't repro with fabricated events. Uncomment the WAIT and test different configs manually
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_Default | KDDockWidgets::Config::Flag_HideTitleBarWhenTabsVisible);

    auto dock1 = createDockWidget("dock1", new QWidget());
    auto dock2 = createDockWidget("dock2", new QWidget());
    dock1->addDockWidgetAsTab(dock2);

    auto frame = dock1->dptr()->frame();
    QCOMPARE(frame->currentIndex(), 1);

    QTest::qWait(500); // wait for window to get proper geometry

    const QPoint clickPoint = frame->tabBar()->mapToGlobal(frame->tabBar()->rectForTab(0).center());
    QCursor::setPos(clickPoint); // Just for visual debug when needed

    pressOn(clickPoint, frame->tabBar()->view());
    releaseOn(clickPoint, frame->tabBar()->view());

    // WAIT // Uncomment for MANUAL test. Also test by adding Flag_AlwaysShowTabs

    QCOMPARE(frame->currentIndex(), 0);
}

void TestQtWidgets::tst_mainWindowAlwaysHasCentralWidget()
{
    EnsureTopLevelsDeleted e;

    auto m = createMainWindow();

    QWidget *central = qobject_cast<Views::MainWindow_qtwidgets *>(m->view()->asQObject())->centralWidget();
    auto dropArea = m->dropArea();
    QVERIFY(dropArea);

    QPointer<Controllers::Frame> centralFrame = dropArea->centralFrame()->asFrameController();
    QVERIFY(central);
    QVERIFY(dropArea);
    QCOMPARE(dropArea->count(), 1);
    QVERIFY(centralFrame);
    QCOMPARE(centralFrame->dockWidgetCount(), 0);

    // Add a tab
    auto dock = createDockWidget("doc1", Qt::green);
    m->addDockWidgetAsTab(dock);
    QCOMPARE(dropArea->count(), 1);
    QCOMPARE(centralFrame->dockWidgetCount(), 1);

    qDebug() << "Central widget width=" << central->size() << "; mainwindow="
             << m->size();

    // Detach tab
    QPoint globalPressPos = dragPointForWidget(centralFrame.data(), 0);
    auto tabBar = centralFrame->tabBar()->view();
    QVERIFY(tabBar);
    qDebug() << "Detaching tab from dropArea->size=" << dropArea->size() << "; dropArea=" << dropArea;
    drag(tabBar, globalPressPos, m->geometry().bottomRight() + QPoint(30, 30));

    QVERIFY(centralFrame);
    QCOMPARE(dropArea->count(), 1);
    QCOMPARE(centralFrame->dockWidgetCount(), 0);
    QVERIFY(dropArea->checkSanity());
}

void TestQtWidgets::tst_dockableMainWindows()
{
    EnsureTopLevelsDeleted e;

    auto m1 = createMainWindow();
    auto dock1 = createDockWidget("dock1", new QPushButton("foo"));
    m1->addDockWidget(dock1, Location_OnTop);

    auto m2 = new KDDockWidgets::Views::MainWindow_qtwidgets("mainwindow-dockable");
    auto m2Container = createDockWidget("mainwindow-dw", ( View * )m2);
    auto menubar = m2->menuBar();
    menubar->addMenu("File");
    menubar->addMenu("View");
    menubar->addMenu("Help");
    m2Container->show();

    auto dock21 = createDockWidget("dock21", new QPushButton("foo"));
    auto dock22 = createDockWidget("dock22", new QPushButton("foo"));
    m2->mainWindow()->addDockWidget(dock21, Location_OnLeft);
    m2->mainWindow()->addDockWidget(dock22, Location_OnRight);

    auto fw = m2Container->floatingWindow();
    Controllers::TitleBar *fwTitleBar = fw->titleBar();

    QVERIFY(fw->hasSingleFrame());
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

    // The FloatingWindow has a single DockWidget, so it shows the title bar, while the Frame doesn't
    QVERIFY(fwTitleBar->isVisible());
    QVERIFY(!m2Container->dptr()->frame()->titleBar()->isVisible());

    fw->dropArea()->addDockWidget(dock1, Location::Location_OnLeft, nullptr);
    // Now the FloatingWindow has two dock widgets, so our main window dock widget also shows the title bar
    QVERIFY(fwTitleBar->isVisible());
    QVERIFY(m2Container->dptr()->frame()->titleBar()->isVisible());

    // Put it how it was, FloatingWindow is single dock again
    auto frame1 = dock1->dptr()->frame();
    dock1->close();
    Platform::instance()->tests_waitForDeleted(frame1);
    QVERIFY(fwTitleBar->isVisible());
    QVERIFY(!m2Container->dptr()->frame()->titleBar()->isVisible());

    // Repeat, but instead of closing dock1, we float it
    fw->dropArea()->addDockWidget(dock1, Location::Location_OnLeft, nullptr);
    QVERIFY(fwTitleBar->isVisible());
    QVERIFY(m2Container->dptr()->frame()->titleBar()->isVisible());
    frame1 = dock1->dptr()->frame();
    frame1->titleBar()->onFloatClicked();
    QVERIFY(fwTitleBar->isVisible());

    QVERIFY(!m2Container->dptr()->frame()->titleBar()->isVisible());

    fw->dropArea()->addDockWidget(dock1, Location::Location_OnLeft, nullptr);
}

void TestQtWidgets::tst_mdi_mixed_with_docking()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(500, 500), MainWindowOption_HasCentralWidget);
    auto dock1 = createDockWidget("1", new QPushButton("1"));

    m->addDockWidget(dock1, Location_OnBottom);

    auto mdiArea = new MDIArea();
    m->setPersistentCentralWidget(std::shared_ptr<ViewWrapper>(new Views::ViewWrapper_qtwidgets(mdiArea)));

    auto mdiWidget1 = createDockWidget("mdi1", new QPushButton("mdi1"));
    auto mdiWidget2 = createDockWidget("mdi2", new QPushButton("mdi12"));

    mdiArea->addDockWidget(mdiWidget1, QPoint(10, 10));
    mdiArea->addDockWidget(mdiWidget2, QPoint(50, 50));

    Controllers::Frame *frameMDI1 = mdiWidget1->d->frame();
    Controllers::Frame *frame1 = dock1->d->frame();
    QVERIFY(!frame1->isMDI());
    QVERIFY(frameMDI1->isMDI());
    QVERIFY(!frame1->mdiLayoutWidget());
    QVERIFY(frameMDI1->mdiLayoutWidget());

    QVERIFY(!dock1->titleBar()->isMDI());

    auto tb1 = mdiWidget1->titleBar();
    QVERIFY(tb1->isMDI());
    QVERIFY(Platform::instance()->tests_waitForEvent(tb1->view(), QEvent::Show));
    QVERIFY(tb1->isVisible());

    // Press the float button
    tb1->onFloatClicked();

    QVERIFY(mdiWidget1->d->lastPosition()->isValid());
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

    auto mdiArea = new MDIArea();

    m->setPersistentCentralWidget(std::shared_ptr<ViewWrapper>(new Views::ViewWrapper_qtwidgets(mdiArea)));


    auto createSheet = [](int id) -> Controllers::DockWidget * {
        auto dock = newDockWidget(QStringLiteral("dw-sheet-%1").arg(id), DockWidget::Option_MDINestable);
        auto btn = new QPushButton(QStringLiteral("Sheet %1").arg(id));
        auto btnw = std::shared_ptr<ViewWrapper>(new Views::ViewWrapper_qtwidgets(btn));
        dock->setGuestView(btnw);
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

    Controllers::Frame *frame1 = mdiWidget1->d->frame();
    Controllers::Frame *mdiFrame1 = frame1->mdiFrame();

    QPointer<Controllers::Frame> frame2 = mdiWidget2->d->frame();
    QPointer<Controllers::Frame> mdiFrame2 = frame2->mdiFrame();
    QPointer<DropArea> dropArea2 = frame2->mdiDropAreaWrapper();

    QPointer<DropArea> dropArea1 = frame1->mdiDropAreaWrapper();
    dropArea1->addDockWidget(mdiWidget3, Location_OnLeft, nullptr);

    QVERIFY(!frame1->isMDI());
    QVERIFY(frame1->isMDIWrapper());
    QVERIFY(frame1->mdiDockWidgetWrapper());
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
    QVERIFY(!mdiFrame2);

    mdiWidget1->close();
    QVERIFY(!mdiWidget1->isOpen());
    QTest::qWait(500); // wait some event loops to make sure there's no delete later. (There isn't, but a bug could introduce them)
    QVERIFY(!dropArea1.isNull()); // Not deleted, as sheet3 is still there
    QCOMPARE(dropArea1->visibleCount(), 1);
    QVERIFY(mdiTb1->isVisible());
    QCOMPARE(mdiWidget3->titleBar(), mdiTb1);
    Controllers::Frame *frame3 = mdiWidget3->d->frame();
    QVERIFY(!frame3->titleBar()->isVisible());

    mdiWidget3->close();
    QVERIFY(Platform::instance()->tests_waitForDeleted(dropArea1));
    QVERIFY(!mdiWidget3->isOpen());
    QVERIFY(dropArea1.isNull());

    // Reopen everything again:

    mdiArea->addDockWidget(mdiWidget1, QPoint(10, 10));
    mdiArea->addDockWidget(mdiWidget2, QPoint(50, 50));
    frame1 = mdiWidget1->d->frame();
    mdiFrame1 = frame1->mdiFrame();
    dropArea1 = frame1->mdiDropAreaWrapper();
    dropArea1->addDockWidget(mdiWidget3, Location_OnLeft, nullptr);

    // Test floating:
    frame2 = mdiWidget2->d->frame();
    QPointer<Controllers::DockWidget> dwWrapper2 = frame2->mdiDockWidgetWrapper();
    dropArea2 = frame2->mdiDropAreaWrapper();
    QVERIFY(mdiWidget2->isVisible());
    QVERIFY(frame2->isMDIWrapper());
    QVERIFY(dwWrapper2->d->isMDIWrapper());
    mdiFrame2 = frame2->mdiFrame();
    mdiWidget2->setFloating(true);
    QVERIFY(mdiWidget2->isFloating());

    QVERIFY(!mdiWidget2->d->frame()->isMDI());
    QVERIFY(!mdiWidget2->d->frame()->isMDIWrapper());
    QVERIFY(Platform::instance()->tests_waitForDeleted(mdiFrame2));

    QVERIFY(dropArea2.isNull());
    QVERIFY(dwWrapper2.isNull());

    auto mdiFrames = mdiArea->frames();
    QCOMPARE(mdiFrames.count(), 1);
    mdiFrame1 = mdiFrames.first();
    QVERIFY(mdiFrame1->isMDI());
    QVERIFY(mdiFrame1->hasNestedMDIDockWidgets());
    auto mdiTitleBar1 = mdiFrame1->titleBar();
    QVERIFY(mdiFrame1->titleBar()->isVisible());
    mdiTitleBar1->makeWindow();

    QVERIFY(Platform::instance()->tests_waitForDeleted(mdiFrame1));
    QCOMPARE(mdiArea->frames().size(), 0);

    // Dock again:
    mdiArea->addDockWidget(mdiWidget1, QPoint(10, 10));
    mdiArea->addDockWidget(mdiWidget2, QPoint(50, 50));

    frame1 = mdiWidget1->d->frame();
    dropArea1 = frame1->mdiDropAreaWrapper();
    dropArea1->addDockWidget(mdiWidget3, Location_OnLeft, nullptr);

    // Detach an internal dock widget by dragging
    const QPoint globalSrc = mdiWidget1->mapToGlobal(QPoint(5, 5));
    const QPoint globalDest = globalSrc + QPoint(100, 100);

    drag(mdiWidget1->view(), globalDest);

    QCOMPARE(mdiArea->frames().count(), 2);
    auto mdiTitleBar = mdiArea->frames().first()->titleBar();
    QVERIFY(mdiTitleBar->isVisible());

    QVERIFY(!mdiWidget3->isFloating());
    QVERIFY(mdiWidget3->d->lastPosition()->isValid());
    mdiTitleBar->onFloatClicked();
    QVERIFY(mdiWidget3->isFloating());

    QVERIFY(Platform::instance()->tests_waitForDeleted(mdiArea->frames().constFirst()));
    QCOMPARE(mdiArea->frames().size(), 1);

    QVERIFY(!mdiWidget2->isFloating());
    Controllers::Frame *lastMdiFrame = mdiArea->frames().constFirst();
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

    auto mdiArea = new MDIArea();
    m->setPersistentCentralWidget(std::shared_ptr<ViewWrapper>(new Views::ViewWrapper_qtwidgets(mdiArea)));

    auto createSheet = [](int id) -> Controllers::DockWidget * {
        auto dock = newDockWidget(QStringLiteral("dw-sheet-%1").arg(id), Controllers::DockWidget::Option_MDINestable);
        dock->setGuestView(std::shared_ptr<ViewWrapper>(new Views::ViewWrapper_qtwidgets(new QPushButton(QStringLiteral("Sheet %1").arg(id)))));
        dock->setTitle(QStringLiteral("Sheet %1").arg(id));

        return dock;
    };

    auto mdiWidget1 = createSheet(1);
    auto mdiWidget2 = createSheet(2);

    mdiArea->addDockWidget(mdiWidget1, QPoint(10, 10));
    mdiArea->addDockWidget(mdiWidget2, QPoint(50, 50));

    Controllers::Frame *frame1 = mdiArea->frames().at(0);

    const QSize sz1 = frame1->view()->size();
    const QSize increment(200, 200);

    QVERIFY(mdiWidget1->d->mdiLayout());
    mdiWidget1->setMDISize(sz1 + increment);

    QCOMPARE(frame1->size(), sz1 + increment);
}

// No need to port to QtQuick
void TestQtWidgets::tst_floatingWindowDeleted()
{
    // Tests a case where the empty floating dock widget wouldn't be deleted
    // Doesn't repro QTBUG-83030 unfortunately, as we already have an event loop running
    // but let's leave this here nonetheless
    class MyMainWindow : public KDDockWidgets::Views::MainWindow_qtwidgets
    {
    public:
        MyMainWindow()
            : KDDockWidgets::Views::MainWindow_qtwidgets("tst_floatingWindowDeleted", MainWindowOption_None)
        {
            auto dock1 = newDockWidget(QStringLiteral("DockWidget #1"));
            auto myWidget = new QWidget();
            dock1->setGuestView(std::shared_ptr<ViewWrapper>(new Views::ViewWrapper_qtwidgets(myWidget)));
            dock1->view()->resize(QSize(600, 600));
            dock1->show();

            auto dock2 = newDockWidget(QStringLiteral("DockWidget #2"));
            myWidget = new QWidget();
            dock2->setGuestView(std::shared_ptr<ViewWrapper>(new Views::ViewWrapper_qtwidgets(myWidget)));
            dock2->view()->resize(QSize(600, 600));
            dock2->show();

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
    auto qmainwindow = qobject_cast<Views::MainWindow_qtwidgets *>(m->view()->asQObject());
    lay->addWidget(qmainwindow);
    container.resize(100, 100);
    Platform::instance()->tests_waitForEvent(&container, QEvent::Resize);
    container.show();
    Platform::instance()->tests_waitForResize(m);
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true, {}, QSize(50, 240) }));
    auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true, {}, QSize(50, 240) }));
    m->addDockWidget(dock1, KDDockWidgets::Location_OnBottom);
    m->addDockWidget(dock2, KDDockWidgets::Location_OnBottom);
    Platform::instance()->tests_waitForResize(m);
    QVERIFY(m->dropArea()->checkSanity());
    delete m;
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

    Controllers::SideBar *sb = m1->sideBarForDockWidget(dw1);
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

    QAction *action = dw1->toggleAction();
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
}

void TestQtWidgets::tst_deleteOnCloseWhenOnSideBar()
{
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_AutoHideSupport);
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    QPointer<Controllers::DockWidget> dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true, {}, QSize(400, 400) }), Controllers::DockWidget::Option_DeleteOnClose);
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
        Tests::clickOn(m1->mapToGlobal(m1->rect().topLeft() + localPt), m1->view()->childViewAt(localPt).get());
        QVERIFY(!dw1->isOverlayed());
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

    Controllers::Frame *frame = dw1->dptr()->frame();
    QVERIFY(frame->isOverlayed());
    QCOMPARE(dw1->sideBarLocation(), SideBarLocation::North);
    QVERIFY(frame->height() > 0);

    const int newHeight = frame->height() + 300;
    frame->view()->setHeight(newHeight);

    m1->toggleOverlayOnSideBar(dw1);
    m1->toggleOverlayOnSideBar(dw1);

    frame = dw1->dptr()->frame();
    QCOMPARE(frame->height(), newHeight);
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
    QCOMPARE(layout->count(), 2); // 2, as it has the central frame
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
        m = createMainWindow(QSize(500, 500), MainWindowOption_HasCentralFrame).release();
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

    delete static_cast<Views::ViewWrapper_qtwidgets *>(m->window().get())->widget();
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
    auto widget = Platform::instance()->tests_createView({ true, QSize(250, maxHeight), QSize(200, 200) });
    widget->setSizePolicy({ QSizePolicy::Preferred, QSizePolicy::Maximum });

    auto dock1 = createDockWidget("dock1", widget);
    dock1->show();
    dock1->window()->resize(QSize(500, 500));
    auto window1 = dock1->window();
    dock1->close();
    dock1->show();
    auto oldFw2 = dock1->window();

    const int tolerance = 50;
    QVERIFY(dock1->window()->height() <= maxHeight + tolerance); // +tolerance as the floating window is a bit bigger, due to margins etc.
    QVERIFY(dock1->height() <= maxHeight);

    auto m1 = createMainWindow();
    auto dock2 = createDockWidget("dock2", new QPushButton("foo"));
    m1->addDockWidget(dock2, Location_OnTop);
    m1->view()->resize(QSize(2000, 3000));

    // Make the floating window big, and see if the suggested highlight is still small
    dock1->window()->resize(QSize(dock1->width(), 800));

    {
        WindowBeingDragged wbd1(dock1->floatingWindow());
        const QRect highlightRect = m1->multiSplitter()->rectForDrop(&wbd1, Location_OnBottom, nullptr);
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
    d2->show();

    Item *item2 = layout->itemForFrame(d2->dptr()->frame());

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
    dock1->show();


    QCOMPARE(dock1->view()->minSize(), w->minSize());
    QCOMPARE(dock1->view()->maximumSize(), w->maximumSize());

    w->setMinimumSize(QSize(121, 121));
    w->setMaximumSize(QSize(501, 501));

    Platform::instance()->tests_waitForEvent(w, QEvent::LayoutRequest);

    QCOMPARE(dock1->view()->minSize(), w->minSize());
    QCOMPARE(dock1->view()->maximumSize(), w->maximumSize());

    // Now let's see if our Frame also has proper size-constraints
    Controllers::Frame *frame = dock1->dptr()->frame();
    QCOMPARE(frame->view()->maxSizeHint().expandedTo(w->maximumSize()), frame->view()->maxSizeHint());
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

    dock1->show();
    dock2->show();

    auto window1 = dock1->window();
    auto window2 = dock2->window();
    Platform::instance()->tests_waitForEvent(window1.get(), QEvent::LayoutRequest);

    QVERIFY(window1->maximumSize().width() < 500);
    QVERIFY(window1->maximumSize().height() < 500);
    QVERIFY(window2->maximumSize().width() > 500);
    QVERIFY(window2->maximumSize().height() > 500);

    auto hasMax = [&window1] {
        const QSize max = window1->maximumSize();
        return max.width() < 500 && max.height() < 500;
    };

    // Adding side-by-side, we don't honour max size (yet)
    dock1->addDockWidgetToContainingWindow(dock2, Location_OnBottom);
    Platform::instance()->tests_waitForEvent(window1.get(), QEvent::LayoutRequest);
    QVERIFY(window1->maximumSize().width() > 500);
    QVERIFY(window1->maximumSize().height() > 500);

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
    // When dropping dock2, which is small too, dock2 should occupy all the height except dock1's max-height
    // i.e. dock2 should expand and eat all available space

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
    Controllers::Separator *separator = root->separators().constFirst();
    const int min1 = root->minPosForSeparator_global(separator);
    const int max2 = root->maxPosForSeparator_global(separator);

    QVERIFY(separator->position() >= min1);
    QVERIFY(separator->position() <= max2);
    const int item1MaxHeight = dock1->dptr()->frame()->view()->maxSizeHint().height();
    QVERIFY(dock1->dptr()->frame()->view()->height() <= item1MaxHeight);
    root->dumpLayout();
    QCOMPARE(dock2->dptr()->frame()->view()->height(),
             root->height() - item1MaxHeight - Item::separatorThickness);
}

void TestQtWidgets::tst_addToHiddenMainWindow()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(1000, 1000), MainWindowOption_HasCentralFrame, {}, false);
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
    dock1->show();

    auto dock2 = newDockWidget("dock2");
    auto dock3 = newDockWidget("dock3");
    auto dock4 = newDockWidget("dock4");
    m1->addDockWidget(dock2, Location_OnLeft);
    m1->addDockWidget(dock3, Location_OnRight);
    m1->addDockWidget(dock4, Location_OnBottom, dock3);
    m1->addDockWidget(dock1, Location_OnLeft, dock4);

    Controllers::Frame *frame1 = dock1->dptr()->frame();

    Layouting::ItemBoxContainer *root = m1->multiSplitter()->rootItem();
    Item *item1 = root->itemForWidget(frame1->view());
    auto vertSep1 = root->separators().constFirst();
    const int min1 = root->minPosForSeparator_global(vertSep1);

    ItemBoxContainer *container1 = item1->parentBoxContainer();
    auto innerVertSep1 = container1->separators().constFirst();
    const int minInnerSep = container1->minPosForSeparator_global(innerVertSep1);
    const int maxInnerSep = container1->maxPosForSeparator_global(innerVertSep1);

    root->requestSeparatorMove(vertSep1, -(vertSep1->position() - min1));
    QVERIFY(frame1->width() <= frame1->view()->maxSizeHint().width());

    container1->requestSeparatorMove(innerVertSep1, -(innerVertSep1->position() - minInnerSep));
    QVERIFY(frame1->width() <= frame1->view()->maxSizeHint().width());

    container1->requestSeparatorMove(innerVertSep1, maxInnerSep - innerVertSep1->position());
    QVERIFY(frame1->width() <= frame1->view()->maxSizeHint().width());
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
    const int droppedWidth = dock2->dptr()->frame()->width();
    QVERIFY(droppedWidth < maxWidth + 50); // +50 to cover any margins and waste by QTabWidget

    // Try again, but now dropping a multisplitter
    dock2->setFloating(true);
    auto fw = dock2->floatingWindow();

    m1->dropArea()->drop(fw->view(), Location_OnLeft, nullptr);
    QCOMPARE(dock2->dptr()->frame()->width(), droppedWidth);
}

void TestQtWidgets::tst_fixedSizePolicy()
{
    // tests that KDDW also takes into account QSizePolicy::Fixed for calculating the max size hint.
    // Since QPushButton for example doesn't set QWidget::maximumSize(), but instead uses sizeHint()
    // + QSizePolicy::Fixed.
    EnsureTopLevelsDeleted e;
    auto button = new QPushButton("one");
    auto dock1 = createDockWidget("dock1", button);
    Controllers::Frame *frame = dock1->dptr()->frame();

    // Just a precondition from the test. If QPushButton ever changes, replace with a QWidget and set fixed size policy
    QCOMPARE(button->sizePolicy().verticalPolicy(), QSizePolicy::Fixed);

    const int buttonMaxHeight = button->sizeHint().height();

    QCOMPARE(dock1->view()->sizeHint(), button->sizeHint());
    QCOMPARE(dock1->view()->sizePolicy().verticalPolicy(), button->sizePolicy().verticalPolicy());
    QCOMPARE(dock1->view()->sizePolicy().horizontalPolicy(), button->sizePolicy().horizontalPolicy());

    QCOMPARE(frame->view()->maxSizeHint().height(), qMax(buttonMaxHeight, Layouting::Item::hardcodedMinimumSize.height()));
}

void TestQtWidgets::tst_restoreFloatingMaximizedState()
{
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_TitleBarHasMaximizeButton);
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    const QRect originalNormalGeometry = dock1->floatingWindow()->normalGeometry();
    dock1->floatingWindow()->showMaximized();
    qDebug() << originalNormalGeometry;

    QCOMPARE(dock1->floatingWindow()->view()->window()->windowState(), Qt::WindowMaximized);

    LayoutSaver saver;
    const QByteArray saved = saver.serializeLayout();

    saver.restoreLayout(saved);
    QCOMPARE(dock1->floatingWindow()->view()->window()->windowState(), Qt::WindowMaximized);



    QCOMPARE(dock1->floatingWindow()->normalGeometry(), originalNormalGeometry);

    dock1->floatingWindow()->showNormal();
    QCOMPARE(dock1->floatingWindow()->normalGeometry(), originalNormalGeometry);
}

void TestQtWidgets::tst_complex()
{
    // Tests some anchors out of bounds I got

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(600, 500), MainWindowOption_None);
    auto layout = m->multiSplitter();
    m->view()->resize(QSize(3266, 2239));
    m->show(); // TODO: Remove and see if it crashes

    Controllers::DockWidget::List docks;

    QVector<KDDockWidgets::Location> locations = { Location_OnLeft, Location_OnLeft, Location_OnLeft,
                                                   Location_OnRight, Location_OnRight, Location_OnRight, Location_OnRight,
                                                   Location_OnBottom, Location_OnBottom, Location_OnBottom, Location_OnBottom, Location_OnBottom,
                                                   Location_OnBottom, Location_OnBottom, Location_OnBottom, Location_OnBottom, Location_OnBottom,
                                                   Location_OnBottom, Location_OnBottom, Location_OnBottom, Location_OnBottom };

    QVector<KDDockWidgets::InitialVisibilityOption> options = { InitialVisibilityOption::StartVisible, InitialVisibilityOption::StartVisible,
                                                                InitialVisibilityOption::StartHidden, InitialVisibilityOption::StartHidden,
                                                                InitialVisibilityOption::StartVisible,
                                                                InitialVisibilityOption::StartHidden, InitialVisibilityOption::StartHidden, InitialVisibilityOption::StartHidden, InitialVisibilityOption::StartHidden, InitialVisibilityOption::StartHidden, InitialVisibilityOption::StartHidden,
                                                                InitialVisibilityOption::StartVisible, InitialVisibilityOption::StartVisible,
                                                                InitialVisibilityOption::StartHidden, InitialVisibilityOption::StartHidden, InitialVisibilityOption::StartHidden, InitialVisibilityOption::StartHidden, InitialVisibilityOption::StartHidden, InitialVisibilityOption::StartHidden, InitialVisibilityOption::StartHidden, InitialVisibilityOption::StartHidden };

    QVector<bool> floatings = { true, false, true, false, false, false, false, false, false, false, false, false,
                                true, false, false, true, true, true, true, true, false };

    QVector<QSize> minSizes = {
        QSize(316, 219),
        QSize(355, 237),
        QSize(293, 66),
        QSize(158, 72),
        QSize(30, 141),
        QSize(104, 143),
        QSize(104, 105),
        QSize(84, 341),
        QSize(130, 130),
        QSize(404, 205),
        QSize(296, 177),
        QSize(914, 474),
        QSize(355, 237),
        QSize(104, 104),
        QSize(104, 138),
        QSize(1061, 272),
        QSize(165, 196),
        QSize(296, 177),
        QSize(104, 104),
        QSize(355, 237),
        QSize(104, 138)
    };

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
    qDeleteAll(DockRegistry::self()->frames());
}

void TestQtWidgets::initTestCase()
{
    KDDockWidgets::Platform::instance()->installMessageHandler();
}

void TestQtWidgets::cleanupTestCase()
{
    KDDockWidgets::Platform::instance()->uninstallMessageHandler();
}

int main(int argc, char *argv[])
{
    KDDockWidgets::Platform::tests_initPlatform(argc, argv, KDDockWidgets::FrontendType::QtWidgets);

    if (shouldSkipTests())
        return 0;

    TestQtWidgets test;
    const int exitCode = QTest::qExec(&test, argc, argv);
    KDDockWidgets::Platform::tests_deinitPlatform();

    return exitCode;
}

#include "tst_qtwidgets.moc"

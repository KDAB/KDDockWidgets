/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// We don't care about performance related checks in the tests
// clazy:excludeall=ctor-missing-parent-argument,missing-qobject-macro,range-loop,missing-typeinfo,detaching-member,function-args-by-ref,non-pod-global-static,reserve-candidates,qstring-allocations

#include "Config.h"
#include "core/DragController_p.h"
#include "utils.h"
#include "core/LayoutSaver_p.h"
#include "core/ScopedValueRollback_p.h"
#include "core/Position_p.h"
#include "core/TitleBar_p.h"
#include "core/TabBar_p.h"
#include "core/Action_p.h"
#include "core/WindowBeingDragged_p.h"
#include "core/Logging_p.h"
#include "core/layouting/Item_p.h"
#include "core/layouting/LayoutingGuest_p.h"
#include "core/layouting/LayoutingSeparator_p.h"
#include "core/ViewFactory.h"
#include "core/Action.h"
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

#include <QTest>

#include <cstdlib>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;
using namespace KDDockWidgets::Tests;


inline int lengthForSize(Size sz, Qt::Orientation o)
{
    return o == Qt::Vertical ? sz.height() : sz.width();
}

inline int widgetMinLength(View *view, Qt::Orientation o)
{
    const Size sz = view->minSize();
    return lengthForSize(sz, o);
}

inline int widgetMinLength(Core::Group *group, Qt::Orientation o)
{
    const Size sz = group->view()->minSize();
    return lengthForSize(sz, o);
}

class TestDocks : public QObject
{
public:
    Q_OBJECT
private Q_SLOTS:
    void tst_simple1();
    void tst_simple2();
    void tst_resizeWindow2();
    void tst_hasPreviousDockedLocation();
    void tst_hasPreviousDockedLocation2();
    void tst_LayoutSaverOpenedDocks();
    void tst_ghostSeparator();
    void tst_detachFromMainWindow();
    void tst_floatingWindowSize();
    void tst_tabbingWithAffinities();
    void tst_floatingWindowTitleBug();
    void tst_setFloatingSimple();
    void tst_dragOverTitleBar();
    void tst_setFloatingGeometry();
    void tst_restoreEmpty();
    void tst_restoreCentralFrame();
    void tst_restoreNonExistingDockWidget();
    void tst_shutdown();
    void tst_closeDockWidgets();
    void tst_closeReason();
    void tst_layoutEqually();
    void tst_doubleClose();
    void tst_maximizeAndRestore();
    void tst_restoreWithNonClosableWidget();
    void tst_restoreCrash();
    void tst_restoreSideBySide();
    void tst_restoreGroupOptions();
    void tst_restoreWithAffinity();
    void tst_marginsAfterRestore();
    void tst_restoreWithNewDockWidgets();
    void tst_restoreWithDockFactory();
    void tst_restoreWithDockFactory2();
    void tst_dontCloseDockWidgetBeforeRestore();
    void tst_dontCloseDockWidgetBeforeRestore3();
    void tst_dontCloseDockWidgetBeforeRestore4();
    void tst_skipRestoreInsideMainWindow();
    void tst_restoreWithNativeTitleBar();
    void tst_closeOnlyCurrentTab();
    void tst_tabWidgetCurrentIndex();
    void tst_propagateResize2();
    void tst_startClosed();
    void tst_closeReparentsToNull();
    void tst_invalidAnchorGroup();
    void tst_addAsPlaceholder();
    void tst_repeatedShowHide();
    void tst_removeItem();
    void tst_clear();
    void tst_crash();
    void tst_refUnrefItem();
    void tst_placeholderCount();
    void tst_availableLengthForOrientation();
    void tst_closeTabOfCentralFrame();
    void tst_centralGroupAffinity();
    void tst_setAsCurrentTab();
    void tst_placeholderDisappearsOnReadd();
    void tst_placeholdersAreRemovedProperly();
    void tst_closeAllDockWidgets();
    void tst_toggleMiddleDockCrash();
    void tst_stealFrame();
    void tst_setFloatingWhenWasTabbed();
    void tst_setWidget();
    void tst_floatingLastPosAfterDoubleClose();
    void tst_registry();
    void tst_honourGeometryOfHiddenWindow();
    void tst_posAfterLeftDetach();
    void tst_propagateMinSize();
    void tst_createFloatingWindow();
    void tst_unfloatTabbedFloatingWidgets();
    void tst_unfloatTabbedFloatingWidgets2();
    void tst_resizeViaAnchorsAfterPlaceholderCreation();
    void tst_rectForDropCrash();
    void tst_addDockWidgetToMainWindow();
    void tst_addDockWidgetToContainingWindow();
    void tst_setFloatingAfterDraggedFromTabToSideBySide();
    void tst_setFloatingAFrameWithTabs();
    void tst_toggleDockWidgetWithHiddenTitleBar();
    void tst_anchorFollowingItselfAssert();
    void tst_isInMainWindow();
    void tst_sizeConstraintWarning();
    void tst_stuckSeparator();
    void tst_dockNotFillingSpace();
    void tst_titlebar_getter();
    void tst_addingOptionHiddenTabbed();
    void tst_maxSizedHonouredAfterRemoved();
    void tst_addDockWidgetAsTabToDockWidget();
    void tst_closeTabHidesDockWidget();
    void tst_propagateSizeHonoursMinSize();
    void tst_floatingAction();
    void tst_constraintsPropagateUp();
    void tst_addToSmallMainWindow4();
    void tst_addToSmallMainWindow5();
    void tst_dragBySingleTab();
    void tst_deleteOnClose();
    void tst_toggleAction();
    void tst_redocksToPreviousTabIndex();
    void tst_toggleTabbed2();
    void tst_resizePropagatesEvenly();
    void tst_persistentCentralWidget();
    void tst_titlebarNumDockWidgetsChanged();
    void tst_closed();
    void tst_restoreFlagsFromVersion16();
    void tst_map();
    void tst_childViewAt();
    void tst_detachPos();
    void tst_floatMaintainsSize();
    void tst_scopedValueRollback();
    void tst_size();
    void tst_point();
    void tst_rect();
    void tst_resizeInLayout();
    void tst_mainWindowToggle();
    void tst_startDragging();
    void tst_placeholderInFloatingWindow();
    void tst_closeGroup();
    void tst_dockWidgetTabIndexOverride();
    void tst_restoreWithCentralFrameWithTabs();
    void tst_preferredInitialSize();
    void tst_preferredInitialSizeVsMinSize();
    void tst_fairResizeAfterRemoveWidget();
    void tst_minMaxGuest();
    void tst_doesntHaveNativeTitleBar();
    void tst_sizeAfterRedock();
    void tst_honourUserGeometry();
    void tst_restoreMaximizedState();
    void tst_restoreFloatingMinimizedState();
    void tst_dockInternal();
    void tst_samePositionAfterHideRestore();
    void tst_restoreTwice();
    void tst_restoreAfterResize();
    void tst_restoreNestedAndTabbed();
    void tst_restoreWithPlaceholder();
    void tst_restoreAfterMinSizeChanges();
    void tst_lastFloatingPositionIsRestored();
    void tst_restoreNonClosable();
    void tst_restoreNlohmanException();
    void tst_restoreWithInvalidCurrentTab();
    void tst_restoreRestoresMainWindowPosition();
    void tst_dontCloseDockWidgetBeforeRestore2();
    void tst_doubleClickTabToDetach();
    void tst_doubleClickTabBarRestore();
    void tst_doubleClickTabRestore();
    void tst_tabTitleChanges();
    void tst_preventClose();
    void tst_addAndReadd();
    void tst_notClosable();
    void tst_availableSizeWithPlaceholders();
    void tst_moreTitleBarCornerCases();
    void tst_raise();
    void tst_nonDockable();
    void tst_flagDoubleClick();
    void tst_constraintsAfterPlaceholder();
    void tst_addToSmallMainWindow1();
    void tst_addToSmallMainWindow2();
    void tst_addToSmallMainWindow3();
    void tst_titleBarFocusedWhenTabsChange();
    void tst_toggleTabbed();
    void tst_currentTabMatchesDockWidget();
    void tst_addMDIDockWidget();
    void tst_mdiZorder();
    void tst_mdiCrash();
    void tst_mdiZorder2();
    void tst_mdiSetSize();
    void tst_mixedMDIRestoreToArea();
    void tst_redockToMDIRestoresPosition();
    void tst_maximizeButton();
    void tst_restoreAfterUnminimized();
    void tst_doubleScheduleDelete();
    void tst_minimizeRestoreBug();
    void tst_keepLast();
};

void TestDocks::tst_simple1()
{
    // Simply create a MainWindow
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    m->layout()->checkSanity();
}

void TestDocks::tst_simple2()
{
    // Simply create a MainWindow, and dock something on top
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dw = createDockWidget(
        "dw", Platform::instance()->tests_createView({ true, {}, Size(100, 100) }));
    auto fw = dw->floatingWindow();
    m->addDockWidget(dw, KDDockWidgets::Location_OnTop);
    m->layout()->checkSanity();
    delete fw;
}

void TestDocks::tst_minMaxGuest()
{
    // Tests some min/max size cases, regarding guest and the dock widget

    EnsureTopLevelsDeleted e;

    auto guest = Platform::instance()->tests_createView({ true });
    auto dockA = createDockWidget("0", guest);

    {
        const Size newMinSize = { 500, 501 };
        QCOMPARE(dockA->view()->minSize(), guest->minSize());
        QVERIFY(newMinSize != dockA->view()->minSize());

        dockA->view()->setMinimumSize(newMinSize);

        // There was a QtQuick bug where the returned minSize() wasn't correct
        QVERIFY(newMinSize == dockA->view()->minSize());
    }

    {
        const int newWidth = 502;
        QVERIFY(newWidth != dockA->view()->minSize().width());

        dockA->view()->setFixedWidth(newWidth);

        // There was a QtQuick bug where the returned minSize() wasn't correct
        QVERIFY(newWidth == dockA->view()->minSize().width());
    }
}

void TestDocks::tst_doesntHaveNativeTitleBar()
{
    // Tests that a floating window doesn't have a native title bar
    // This test is mostly to test a bug that was happening with QtQuick, where the native title bar
    // would appear on linux
    EnsureTopLevelsDeleted e;

    auto dw1 = createDockWidget("dock1");
    Core::FloatingWindow *fw = dw1->floatingWindow();
    QVERIFY(fw);
    QVERIFY(fw->view()->flags() & Qt::Tool);

#if defined(Q_OS_LINUX)
    QVERIFY(fw->view()->flags() & Qt::FramelessWindowHint);
#elif defined(Q_OS_WIN)
    QVERIFY(!(fw->view()->flags() & Qt::FramelessWindowHint));
#endif
}

void TestDocks::tst_resizeWindow2()
{
    // Tests that resizing the width of the main window will never move horizontal anchors

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(501, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1");
    auto dock2 = createDockWidget("2");

    Core::FloatingWindow *fw1 = dock1->floatingWindow();
    Core::FloatingWindow *fw2 = dock2->floatingWindow();
    m->addDockWidget(dock1, Location_OnTop);
    m->addDockWidget(dock2, Location_OnBottom);

    auto layout = m->multiSplitter();
    auto anchor = layout->separators().at(0);
    const int oldPosY = anchor->position();
    m->view()->resize(Size(m->width() + 10, m->height()));
    QCOMPARE(anchor->position(), oldPosY);
    layout->checkSanity();

    delete fw1;
    delete fw2;
}

void TestDocks::tst_hasPreviousDockedLocation()
{
    // Tests Core::DockWidget::hasPreviousDockedLocation()

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(501, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1");
    m->layout()->checkSanity();
    m->multiSplitter()->setObjectName("mainWindow-dropArea");
    dock1->floatingWindow()->layout()->view()->setViewName("first-dropArea1");
    dock1->floatingWindow()->layout()->checkSanity();
    auto window1 = dock1->window();
    QVERIFY(dock1->isFloating());
    QVERIFY(!dock1->hasPreviousDockedLocation());
    QVERIFY(dock1->setFloating(true));
    QVERIFY(!dock1->setFloating(false)); // No docking location, so it's not docked
    QVERIFY(dock1->isFloating());
    QVERIFY(!dock1->hasPreviousDockedLocation());

    m->addDockWidget(dock1, Location_OnBottom);
    m->layout()->checkSanity();

    QVERIFY(!dock1->isFloating());
    QVERIFY(dock1->setFloating(true));

    auto ms1 = dock1->floatingWindow()->layout();
    ms1->view()->setViewName("dropArea1");
    ms1->checkSanity();
    QVERIFY(dock1->hasPreviousDockedLocation());
    auto window11 = dock1->window();
    QVERIFY(dock1->setFloating(false));
}

void TestDocks::tst_hasPreviousDockedLocation2()
{
    // Tests with LayoutSaver

    QByteArray saved;

    // #1 Tests after a restore
    {
        EnsureTopLevelsDeleted e;
        auto m = createMainWindow(Size(501, 500), MainWindowOption_None, "mainWindow1");
        auto dock1 = createDockWidget("1");
        QVERIFY(!dock1->hasPreviousDockedLocation());

        m->addDockWidget(dock1, Location_OnBottom);
        QVERIFY(!dock1->hasPreviousDockedLocation());
        dock1->setFloating(true);
        QVERIFY(dock1->hasPreviousDockedLocation());

        LayoutSaver saver;
        saved = saver.serializeLayout();
        saver.restoreLayout(saved);
        QVERIFY(dock1->hasPreviousDockedLocation());
        QVERIFY(dock1->isFloating());
    }

    // #2. Tests after a restore but with a fresh main window
    {
        EnsureTopLevelsDeleted e;
        auto m = createMainWindow(Size(501, 500), MainWindowOption_None, "mainWindow1");
        auto dock1 = createDockWidget("1");
        QVERIFY(!dock1->hasPreviousDockedLocation());
        LayoutSaver saver;
        saver.restoreLayout(saved);

        QVERIFY(dock1->hasPreviousDockedLocation());
        QVERIFY(dock1->isFloating());
    }

    // #3. Tests after a restore but with a fresh main window
    {
        EnsureTopLevelsDeleted e;
        auto m = createMainWindow(Size(501, 500), MainWindowOption_None, "mainWindow1");
        LayoutSaver saver;
        saver.restoreLayout(saved);

        // QEXPECT_FAIL: We can't uncomment this yet, not supported, but we should.
        // auto dock1 = createDockWidget("1");
        // QVERIFY(dock1->hasPreviousDockedLocation());
    }

    // #4. Tests with StartHidden
    QByteArray saved2;
    {
        EnsureTopLevelsDeleted e;
        auto m = createMainWindow(Size(501, 500), MainWindowOption_None, "mainWindow2");
        auto dock2 = createDockWidget("2", Platform::instance()->tests_createView({ true, {}, { 100, 100 } }), {}, {}, false);
        QVERIFY(dock2->isFloating());
        m->addDockWidget(dock2, Location_OnBottom, nullptr, InitialVisibilityOption::StartHidden);
        QVERIFY(dock2->hasPreviousDockedLocation());

        LayoutSaver saver2;
        saved2 = saver2.serializeLayout();
        delete dock2;
    }

    {
        EnsureTopLevelsDeleted e;
        auto m = createMainWindow(Size(501, 500), MainWindowOption_None, "mainWindow2");
        auto dock2 = createDockWidget("2", Platform::instance()->tests_createView({ true, {}, { 100, 100 } }), {}, {}, false);

        LayoutSaver saver2;
        saver2.restoreLayout(saved2);
        QVERIFY(dock2->hasPreviousDockedLocation());
        delete dock2;
    }

    // To process 1 event loop and do some delete later. Makes asan happy.
    QTest::qWait(1);
}

void TestDocks::tst_LayoutSaverOpenedDocks()
{
    QByteArray saved1;
    QByteArray saved2;

    {
        EnsureTopLevelsDeleted e;
        auto m = createMainWindow(Size(501, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("1");
        auto dock2 = createDockWidget("2");
        auto dock3 = createDockWidget("3");
        dock1->close();
        dock2->close();
        dock3->close();

        LayoutSaver saver;
        saved1 = saver.serializeLayout();
    }

    {
        EnsureTopLevelsDeleted e;
        auto m = createMainWindow(Size(501, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("1");
        createDockWidget("2");
        auto dock3 = createDockWidget("3");
        dock3->close();
        m->addDockWidget(dock1, KDDockWidgets::Location_OnRight);

        LayoutSaver saver;
        saved2 = saver.serializeLayout();
    }

    QVERIFY(LayoutSaver::openedDockWidgetsInLayout(saved1).isEmpty());
    QVERIFY(LayoutSaver::openedDockWidgetsInLayout(saved2) == Vector<QString>({ "1", "2" }));
}

void TestDocks::tst_ghostSeparator()
{
    // Tests a situation where a separator wouldn't be removed after a widget had been removed
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(501, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1");
    auto dock2 = createDockWidget("2");
    auto dock3 = createDockWidget("3");

    ObjectGuard<Core::FloatingWindow> fw1 = dock1->floatingWindow();
    ObjectGuard<Core::FloatingWindow> fw2 = dock2->floatingWindow();
    ObjectGuard<Core::FloatingWindow> fw3 = dock3->floatingWindow();

    dock1->addDockWidgetToContainingWindow(dock2, Location_OnRight);
    QCOMPARE(fw1->multiSplitter()->separators().size(), 1);
    QCOMPARE(Core::Separator::numSeparators(), 1);

    m->addDockWidget(dock3, Location_OnBottom);
    QCOMPARE(m->multiSplitter()->separators().size(), 0);
    QCOMPARE(Core::Separator::numSeparators(), 1);

    m->multiSplitter()->addMultiSplitter(fw1->multiSplitter(), Location_OnRight);
    QCOMPARE(m->multiSplitter()->separators().size(), 2);

    if (Config::self().internalFlags() & Config::InternalFlag_DeleteSeparatorsLater)
        Platform::instance()->tests_wait(100);

    QCOMPARE(Core::Separator::numSeparators(), 2);

    delete fw1;
    delete fw2;
    delete fw3;
}

void TestDocks::tst_detachFromMainWindow()
{
    // Tests a situation where clicking the float button wouldn't work on QtQuick
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(501, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1");
    auto fw1 = dock1->window();
    m->addDockWidget(dock1, Location_OnTop);

    QVERIFY(m->layout()->mainWindow() != nullptr);
    QVERIFY(!dock1->isFloating());
    Core::TitleBar *tb = dock1->titleBar();
    QVERIFY(tb == dock1->dptr()->group()->titleBar());
    QVERIFY(tb->isVisible());
    QVERIFY(!tb->isFloating());
}

void TestDocks::tst_detachPos()
{
    // Tests a situation where detaching a dock widget would send it to a bogus position
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(501, 500), MainWindowOption_None);
    auto dock1 = createDockWidget(
        "1", Platform::instance()->tests_createView({ true, {}, Size(100, 100) }), {}, {},
        /** show = */ false); // we're creating the dock widgets without showing them as floating
                              // initially, so it doesn't record the previous floating position
    auto dock2 =
        createDockWidget("2", Platform::instance()->tests_createView({ true, {}, Size(100, 100) }),
                         {}, {}, /** show = */ false);

    QVERIFY(!dock1->isVisible());
    QVERIFY(!dock2->isVisible());

    m->addDockWidget(dock1, Location_OnLeft);
    m->addDockWidget(dock2, Location_OnRight);

    QVERIFY(!dock1->dptr()->lastPosition()->lastFloatingGeometry().isValid());
    QVERIFY(!dock2->dptr()->lastPosition()->lastFloatingGeometry().isValid());

    const int previousWidth = dock1->width();
    dock1->setFloating(true);
    QTest::qWait(400); // Needed for QtQuick

    QVERIFY(std::abs(previousWidth - dock1->width()) < 15); // 15px of difference when floating is fine,
                                                            // due to margins and what not.
}

void TestDocks::tst_floatingWindowSize()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(501, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1");
    auto fw1 = dock1->window();

    QTest::qWait(100);

    QVERIFY(!fw1->geometry().isNull());
    QCOMPARE(fw1->size(), fw1->window()->size());
}

void TestDocks::tst_tabbingWithAffinities()
{
    EnsureTopLevelsDeleted e;
    // Tests that dock widgets with different affinities should not tab together

    auto m1 = createMainWindow(Size(1000, 1000), MainWindowOption_None);
    m1->setAffinities({ "af1", "af2" });

    auto dw1 = newDockWidget("1");
    dw1->setAffinities({ "af1" });
    dw1->open();

    auto dw2 = newDockWidget("2");
    dw2->setAffinities({ "af2" });
    dw2->open();

    Core::FloatingWindow *fw1 = dw1->floatingWindow();
    Core::FloatingWindow *fw2 = dw2->floatingWindow();

    {
        SetExpectedWarning ignoreWarning("Refusing to dock widget with incompatible affinity");
        dw1->addDockWidgetAsTab(dw2);
        QVERIFY(!dw1->window()->equals(dw2->window()));
    }

    m1->addDockWidget(dw1, Location_OnBottom);
    QVERIFY(!dw1->isFloating());

    {
        SetExpectedWarning ignoreWarning("Refusing to dock widget with incompatible affinity");
        auto dropArea = m1->dropArea();
        WindowBeingDragged wbd(fw2, fw2);
        QVERIFY(!dropArea->drop(&wbd, dw1->dptr()->group(), DropLocation_Center));
        QVERIFY(!dw1->window()->equals(dw2->window()));
    }

    delete fw1;
    delete fw2;
}

void TestDocks::tst_sizeAfterRedock()
{
    EnsureTopLevelsDeleted e;
    auto dw1 = newDockWidget(QStringLiteral("1"));
    auto dw2 = newDockWidget(QStringLiteral("2"));
    dw2->setGuestView(
        Platform::instance()->tests_createView({ true, {}, Size(100, 100) })->asWrapper());

    dw1->addDockWidgetToContainingWindow(dw2, Location_OnBottom);
    const int height2 = dw2->dptr()->group()->height();

    dw2->setFloating(true);
    QTest::qWait(100);

    QCOMPARE(height2, dw2->window()->height());
    auto oldFw2 = dw2->floatingWindow();

    // Redock
    Core::FloatingWindow *fw1 = dw1->floatingWindow();
    DropArea *dropArea = fw1->dropArea();

    Core::DropArea *ms1 = fw1->multiSplitter();
    {
        WindowBeingDragged wbd2(oldFw2);
        const Rect suggestedDropRect = ms1->rectForDrop(&wbd2, Location_OnBottom, nullptr);
        QCOMPARE(suggestedDropRect.height(), height2);
    }

    dropArea->drop(dw2->floatingWindow()->view(), Location_OnBottom, nullptr);

    QCOMPARE(dw2->dptr()->group()->height(), height2);

    delete oldFw2;
}

void TestDocks::tst_honourUserGeometry()
{
    EnsureTopLevelsDeleted e;
    auto m1 = createMainWindow(Size(1000, 1000), MainWindowOption_None);
    auto dw1 = newDockWidget(QStringLiteral("1"));
    QVERIFY(!dw1->view()->hasAttribute(Qt::WA_PendingMoveEvent));

    const Point pt(10, 10);
    dw1->view()->move(pt);
    dw1->open();
    Core::FloatingWindow *fw1 = dw1->floatingWindow();
    QCOMPARE(fw1->view()->window()->geometry().topLeft(), pt);
}

void TestDocks::tst_floatingWindowTitleBug()
{
    // Test for #74
    EnsureTopLevelsDeleted e;
    auto dw1 = newDockWidget(QStringLiteral("1"));
    auto dw2 = newDockWidget(QStringLiteral("2"));
    auto dw3 = newDockWidget(QStringLiteral("3"));

    dw1->setObjectName(QStringLiteral("1"));
    dw2->setObjectName(QStringLiteral("2"));
    dw3->setObjectName(QStringLiteral("3"));

    dw1->open();
    dw1->addDockWidgetAsTab(dw2);
    dw1->addDockWidgetToContainingWindow(dw3, Location_OnBottom);

    dw1->titleBar()->onFloatClicked();

    QCOMPARE(dw3->titleBar()->title(), QLatin1String("3"));
}

void TestDocks::tst_restoreTwice()
{
    // Tests that restoring multiple times doesn't hide the floating windows for some reason
    EnsureTopLevelsDeleted e;

    auto m =
        createMainWindow(Size(500, 500), MainWindowOption_HasCentralGroup, "tst_restoreTwice");
    auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
    m->addDockWidgetAsTab(dock1);

    auto dock2 = createDockWidget("2", Platform::instance()->tests_createView({ true }));
    auto dock3 = createDockWidget("3", Platform::instance()->tests_createView({ true }));

    dock2->dptr()->morphIntoFloatingWindow();
    dock3->dptr()->morphIntoFloatingWindow();

    {
        LayoutSaver saver;
        QVERIFY(saver.saveToFile(QStringLiteral("layout_tst_restoreTwice.json")));
        QVERIFY(saver.restoreFromFile(QStringLiteral("layout_tst_restoreTwice.json")));
        QVERIFY(dock2->isVisible());
        QVERIFY(dock3->isVisible());
    }

    {
        LayoutSaver saver;
        QVERIFY(saver.restoreFromFile(QStringLiteral("layout_tst_restoreTwice.json")));
        QVERIFY(dock2->isVisible());
        QVERIFY(dock3->isVisible());
        QVERIFY(dock2->window()->controller()->isVisible());
        QVERIFY(dock3->window()->controller()->isVisible());
        auto fw = dock2->floatingWindow();
        QVERIFY(fw);
    }
}

void TestDocks::tst_restoreWithInvalidCurrentTab()
{
    auto test = [](bool strictMode) {
        EnsureTopLevelsDeleted e;
        KDDockWidgets::Config::self().setLayoutSaverStrictMode(strictMode);

        DockWidgetFactoryFunc dwFunc = [](const QString &dwName) {
            return Config::self().viewFactory()->createDockWidget(dwName)->asDockWidgetController();
        };

        /// MainWindow factory for the easy cases.
        MainWindowFactoryFunc mwFunc = [](const QString &mwName, MainWindowOptions mainWindowOptions) {
            return Platform::instance()->createMainWindow(mwName, {}, mainWindowOptions);
        };

        KDDockWidgets::Config::self().setDockWidgetFactoryFunc(dwFunc);
        KDDockWidgets::Config::self().setMainWindowFactoryFunc(mwFunc);

        LayoutSaver saver;

        bool ok = false;
        LayoutSaver restorer;
        const QByteArray data = Platform::instance()->readFile(":/layouts/invalidCurrentTab.json", /*by-ref*/ ok);
        QVERIFY(ok);

        // In strict mode we expect it to fail. This also tests that it's not failing with a crash, as it was before.
        if (strictMode)
            QVERIFY(!restorer.restoreLayout(data));
        else
            QVERIFY(restorer.restoreLayout(data));

        delete DockRegistry::self()->mainwindows().first();
    };

    // We test both in strict mode and in non-strict mode. Since neither should crash.

    test(false);

    SetExpectedWarning ignoreWarning("Invalid tab index");

    test(true);
}

void TestDocks::tst_restoreNlohmanException()
{
    LayoutSaver saver;

    bool ok = false;
    LayoutSaver::Layout layout;
    const QByteArray data = Platform::instance()->readFile(":/layouts/nlohman_exception.json", /*by-ref*/ ok);
    QVERIFY(ok);
    QVERIFY(layout.fromJson(data));
}

void TestDocks::tst_restoreEmpty()
{
    EnsureTopLevelsDeleted e;

    // Create an empty main window, save it to disk.
    auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
    auto layout = m->multiSplitter();
    LayoutSaver saver;
    const Size oldSize = m->size();
    QVERIFY(saver.saveToFile(QStringLiteral("layout_tst_restoreEmpty.json")));
    saver.restoreFromFile(QStringLiteral("layout_tst_restoreEmpty.json"));
    QVERIFY(m->layout()->checkSanity());
    QCOMPARE(layout->separators().size(), 0);
    QCOMPARE(layout->count(), 0);
    QCOMPARE(m->size(), oldSize);
    QVERIFY(layout->checkSanity());
}

void TestDocks::tst_restoreCentralFrame()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(800, 500));
    auto layout = m->multiSplitter();

    QCOMPARE(layout->count(), 1);
    Item *item = m->dropArea()->centralFrame();
    QVERIFY(item);
    auto group = Group::fromItem(item);
    QCOMPARE(group->options(), FrameOption_IsCentralFrame | FrameOption_AlwaysShowsTabs);
    QVERIFY(!group->titleBar()->isVisible());

    LayoutSaver saver;
    QVERIFY(saver.saveToFile(QStringLiteral("layout_tst_restoreCentralFrame.json")));
    QVERIFY(saver.restoreFromFile(QStringLiteral("layout_tst_restoreCentralFrame.json")));

    QCOMPARE(layout->count(), 1);
    item = m->dropArea()->centralFrame();
    QVERIFY(item);
    group = Group::fromItem(item);
    QCOMPARE(group->options(), FrameOption_IsCentralFrame | FrameOption_AlwaysShowsTabs);
    QVERIFY(!group->titleBar()->isVisible());
}

void TestDocks::tst_restoreMaximizedState()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();

    m->view()->showMaximized();

    QCOMPARE(m->view()->window()->windowState(), WindowState::Maximized);
    LayoutSaver saver;

    const QByteArray saved = saver.serializeLayout();
    m->view()->showNormal();
    QVERIFY(m->view()->window()->windowState() != WindowState::Maximized);

    saver.restoreLayout(saved);
    QCOMPARE(m->view()->window()->windowState(), WindowState::Maximized);
}

void TestDocks::tst_minimizeRestoreBug()
{
    // Tests a bug where an unminimized window would have StartsMinimized in its serialization

    EnsureTopLevelsDeleted e;
    auto m = Platform::instance()->createMainWindow("MyMainLayout", {}, {});

    auto d1 = createDockWidget("Dock #1");
    createDockWidget("Dock #2");
    createDockWidget("Dock #3");
    auto d4 = createDockWidget("dock4");

    bool ok = false;
    LayoutSaver restorer;
    const QByteArray data = Platform::instance()->readFile(":/layouts/minimizeBug.json", /*by-ref*/ ok);
    QVERIFY(ok);
    QVERIFY(restorer.restoreLayout(data));
    QVERIFY(d1->isOpen());
    QVERIFY(d4->isOpen());
    QCOMPARE(m->view()->window()->windowState(), WindowState::None);

    QVERIFY(!(d1->floatingWindow()->floatingWindowFlags() & FloatingWindowFlag::StartsMinimized));
    delete m;
}

void TestDocks::tst_restoreFloatingMinimizedState()
{
    EnsureTopLevelsDeleted e;
    auto dock1 = createDockWidget(
        "dock1", Platform::instance()->tests_createView({ true, {}, Size(100, 100) }));
    dock1->floatingWindow()->view()->showMinimized();

    QCOMPARE(dock1->floatingWindow()->view()->window()->windowState(), WindowState::Minimized);

    LayoutSaver saver;
    const QByteArray saved = saver.serializeLayout();

    saver.restoreLayout(saved);
#ifdef KDDW_FRONTEND_QT_WINDOWS
    // QtQuick is using hack for QTBUG-120269
    if (Platform::instance()->isQtQuick())
        Platform::instance()->tests_wait(1000);

    // For QtWidgets we're not using the workaround. Needs to be tested.
    QCOMPARE(dock1->floatingWindow()->view()->window()->windowState(), WindowState::Minimized);
#else
    QCOMPARE(dock1->floatingWindow()->view()->window()->windowState(), WindowState::Minimized);
#endif
}

void TestDocks::tst_restoreNonExistingDockWidget()
{
    // If the layout is old and doesn't know about some dock widget, then we need to float it
    // before restoring the MainWindow's layout

    QByteArray saved;
    const Size defaultMainWindowSize = { 500, 500 };

    {
        EnsureTopLevelsDeleted e;
        auto m = createMainWindow(defaultMainWindowSize, MainWindowOption_None, "mainwindow1");
        LayoutSaver saver;
        saved = saver.serializeLayout();
    }

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(defaultMainWindowSize, MainWindowOption_None, "mainwindow1");
    auto dock2 = createDockWidget(
        "dock2", Platform::instance()->tests_createView({ true, {}, Size(100, 100) }));
    m->addDockWidget(dock2, Location_OnBottom);
    LayoutSaver restorer;
    SetExpectedWarning sew("Couldn't find dock widget");
    QVERIFY(restorer.restoreLayout(saved));
    auto da = m->dropArea();
    QVERIFY(m->dropArea()->checkSanity());
    QCOMPARE(da->groups().size(), 0);

    QVERIFY(dock2->isOpen());
    QVERIFY(dock2->isFloating());
}

void TestDocks::tst_setFloatingSimple()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dock1 = createDockWidget(
        "dock1", Platform::instance()->tests_createView({ true, {}, Size(100, 100) }));
    m->addDockWidget(dock1, Location_OnTop);
    auto l = m->multiSplitter();
    dock1->setFloating(true);
    QVERIFY(l->checkSanity());
    dock1->setFloating(false);
    QVERIFY(l->checkSanity());
    dock1->setFloating(true);
    QVERIFY(l->checkSanity());
    dock1->setFloating(false);
    QVERIFY(l->checkSanity());
}

void TestDocks::tst_nonDockable()
{
    { // First test without Option_NotDockable
        EnsureTopLevelsDeleted e;
        auto dock = newDockWidget("1");
        dock->open();

        Core::TitleBar *tb = dock->titleBar();
        QVERIFY(tb->isVisible());
        QVERIFY(tb->isFloatButtonVisible());
    }

    {
        EnsureTopLevelsDeleted e;
        // Test that when using Option_NotDockable we don't get a dock/undock icon
        auto dock = newDockWidget("1", DockWidgetOption_NotDockable);
        dock->open();

        Core::TitleBar *tb = dock->titleBar();
        QVERIFY(tb->isVisible());
        QVERIFY(!tb->isFloatButtonVisible());
    }
}

void TestDocks::tst_closeDockWidgets()
{
    EnsureTopLevelsDeleted e;
    auto dock1 = createDockWidget("hello1");
    auto dock2 = createDockWidget("hello2");

    auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
    m->addDockWidget(dock1, Location_OnBottom);
    m->addDockWidget(dock2, Location_OnBottom);

    QVERIFY(m->closeDockWidgets(true));
    QCOMPARE(m->layout()->visibleCount(), 0);
}

void TestDocks::tst_closeReason()
{
    QByteArray saved;

    {
        EnsureTopLevelsDeleted e;
        auto dock1 = createDockWidget("d1");
        dock1->open();
        QCOMPARE(dock1->lastCloseReason(), CloseReason::Unspecified);

        // TitleBar close
        dock1->titleBar()->onCloseClicked();
        QVERIFY(!dock1->isOpen());
        QCOMPARE(dock1->lastCloseReason(), CloseReason::TitleBarCloseButton);

        // Programmatic close
        dock1->open();
        dock1->close();
        QVERIFY(!dock1->isOpen());
        QCOMPARE(dock1->lastCloseReason(), CloseReason::Unspecified);

        // Close via QAction
        dock1->open();
        dock1->toggleAction()->setChecked(false);
        QVERIFY(!dock1->isOpen());
        QCOMPARE(dock1->lastCloseReason(), CloseReason::Action);

        LayoutSaver saver;
        saved = saver.serializeLayout();
    }

    {
        EnsureTopLevelsDeleted e;
        auto dock1 = createDockWidget("d1");
        QCOMPARE(dock1->lastCloseReason(), CloseReason::Unspecified);
        LayoutSaver restorer;
        restorer.restoreLayout(saved);
        QCOMPARE(dock1->lastCloseReason(), CloseReason::Action);
    }

    {
        // Restore before having the actual dock widget:

        EnsureTopLevelsDeleted e;
        LayoutSaver restorer;
        restorer.restoreLayout(saved);

        auto dock1 = createDockWidget("d1", LayoutSaverOption::CheckForPreviousRestore);
        QCOMPARE(dock1->lastCloseReason(), CloseReason::Action);
    }
}

void TestDocks::tst_layoutEqually()
{
    EnsureTopLevelsDeleted e;

    const QString mainWindowId = "{7829427d-88e3-402e-9120-50c628dfd0bc}";
    auto m = createMainWindow(Size(800, 500), MainWindowOption_None, mainWindowId);
    m->setAffinities({ mainWindowId });

    auto dock1 = createDockWidget(
        "Favorite-481", Platform::instance()->tests_createView({ true, {}, Size(536, 438) }));
    auto dock2 = createDockWidget(
        "Favorite-482", Platform::instance()->tests_createView({ true, {}, Size(229, 118) }));
    auto dock3 = createDockWidget(
        "Favorite-483", Platform::instance()->tests_createView({ true, {}, Size(356, 90) }));
    dock1->setAffinities({ mainWindowId });
    dock2->setAffinities({ mainWindowId });
    dock3->setAffinities({ mainWindowId });

    LayoutSaver restorer;
    restorer.restoreFromFile(resourceFileName("layouts/layoutEquallyCrash.json"));

    m->layoutEqually();
}

void TestDocks::tst_doubleClose()
{
    {
        // Via close()
        EnsureTopLevelsDeleted e;
        auto dock1 = createDockWidget("hello");
        dock1->close();
        dock1->close();
    }
    {
        // Via the button
        EnsureTopLevelsDeleted e;
        auto dock1 = createDockWidget("hello");
        auto fw1 = dock1->floatingWindow();

        auto t = dock1->dptr()->group()->titleBar();
        t->onCloseClicked();
        t->onCloseClicked();

        delete dock1;
        delete fw1;
    }
    {
        // Test for #141, double delete would ruin lastPositions()
        EnsureTopLevelsDeleted e;
        auto m = createMainWindow();
        auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
        m->addDockWidget(dock1, Location_OnBottom);

        QVERIFY(!dock1->dptr()->lastPosition()->wasFloating());
        QVERIFY(!dock1->isFloating());
        QVERIFY(dock1->isOpen());

        dock1->close();
        QVERIFY(!dock1->isOpen());
        QVERIFY(!dock1->dptr()->lastPosition()->wasFloating());
        QVERIFY(dock1->isFloating());

        dock1->close();
        QVERIFY(!dock1->isOpen());
        QVERIFY(dock1->isFloating());
        QVERIFY(!dock1->dptr()->lastPosition()->wasFloating());
    }
}

void TestDocks::tst_dockInternal()
{
    /**
     * Here we dock relative to an existing widget, and not to the drop-area.
     */
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    auto dropArea = m->dropArea();

    auto centralFrame = Group::fromItem(dropArea->items()[0]);
    nestDockWidget(dock1, dropArea, centralFrame, KDDockWidgets::Location_OnRight);

    QVERIFY(dock1->width() < dropArea->layoutWidth() - centralFrame->width());
}

void TestDocks::tst_maximizeAndRestore()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));

    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    m->addDockWidget(dock2, KDDockWidgets::Location_OnRight);

    auto dropArea = m->dropArea();
    QVERIFY(dropArea->checkSanity());

    m->view()->showMaximized();
    WAIT_FOR_RESIZE(m->view());

    QVERIFY(dropArea->checkSanity());
    m->view()->showNormal();
    WAIT_FOR_RESIZE(m->view());

    QVERIFY(dropArea->checkSanity());
}

void TestDocks::tst_propagateResize2()
{
    // |5|1|2|
    // | |3|4|

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));
    m->addDockWidget(dock1, KDDockWidgets::Location_OnTop);
    m->addDockWidget(dock2, KDDockWidgets::Location_OnRight, dock1);

    auto dock3 = createDockWidget("dock3", Platform::instance()->tests_createView({ true }));
    auto dock4 = createDockWidget("dock4", Platform::instance()->tests_createView({ true }));

    m->addDockWidget(dock3, KDDockWidgets::Location_OnBottom);
    m->addDockWidget(dock4, KDDockWidgets::Location_OnRight, dock3);

    auto dock5 = createDockWidget("dock5", Platform::instance()->tests_createView({ true }));
    m->addDockWidget(dock5, KDDockWidgets::Location_OnLeft);

    auto dropArea = m->dropArea();
    dropArea->checkSanity();
}

void TestDocks::tst_shutdown()
{
    EnsureTopLevelsDeleted e;
    createDockWidget("doc1");

    auto m = createMainWindow();
    m->show();
    QVERIFY(Platform::instance()->tests_waitForWindowActive(m->view()->window()));
}

void TestDocks::tst_closeReparentsToNull()
{
    EnsureTopLevelsDeleted e;
    auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
    auto fw1 = dock1->window();
    QVERIFY(dock1->view()->parentView() != nullptr);
    dock1->close();
    QVERIFY(dock1->view()->parentView() == nullptr);
    delete dock1;
}

void TestDocks::tst_invalidAnchorGroup()
{
    // Tests a bug I got. Should not warn.
    EnsureTopLevelsDeleted e;

    {
        auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
        auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));

        ObjectGuard<Core::FloatingWindow> fw = dock2->dptr()->morphIntoFloatingWindow();
        nestDockWidget(dock1, fw->dropArea(), nullptr, KDDockWidgets::Location_OnTop);

        dock1->close();
        WAIT_FOR_RESIZE(dock2->view());
        auto layout = fw->dropArea();
        layout->checkSanity();

        dock2->close();
        dock1->destroyLater();
        dock2->destroyLater();
        WAIT_FOR_DELETED(dock1);
    }

    {
        // Stack 1, 2, 3, close 2, close 1

        auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
        auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));
        auto dock3 = createDockWidget("dock3", Platform::instance()->tests_createView({ true }));

        m->addDockWidget(dock3, Location_OnTop);
        m->addDockWidget(dock2, Location_OnTop);
        m->addDockWidget(dock1, Location_OnTop);

        dock2->close();
        dock1->close();

        dock1->destroyLater();
        dock2->destroyLater();
        WAIT_FOR_DELETED(dock1);
    }
}

void TestDocks::tst_doubleScheduleDelete()
{
    EnsureTopLevelsDeleted e;
    auto dock1 =
        createDockWidget("dock1", Platform::instance()->tests_createView({ true }), {}, {}, false);
    dock1->show();

    dock1->dptr()->group()->scheduleDeleteLater();
    dock1->dptr()->group()->scheduleDeleteLater();

    QTest::qWait(100);
}

void TestDocks::tst_repeatedShowHide()
{
    EnsureTopLevelsDeleted e;

    auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
    auto dock1 =
        createDockWidget("dock1", Platform::instance()->tests_createView({ true }), {}, {}, false);
    m->addDockWidget(dock1, Location_OnBottom);
    dock1->close();
    dock1->show();
    dock1->close();
    dock1->show();
    dock1->close();
    dock1->show();
}

void TestDocks::tst_addAsPlaceholder()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
    auto dock1 =
        createDockWidget("dock1", Platform::instance()->tests_createView({ true }), {}, {}, false);
    auto dock2 =
        createDockWidget("dock2", Platform::instance()->tests_createView({ true }), {}, {}, false);

    m->addDockWidget(dock1, Location_OnBottom);
    m->addDockWidget(dock2, Location_OnTop, nullptr, InitialVisibilityOption::StartHidden);

    auto dropArea = m->dropArea();
    Core::DropArea *layout = dropArea;

    QVERIFY(!dock2->isOpen());
    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 1);
    QVERIFY(!dock2->isVisible());

    dock2->open();
    QVERIFY(dock2->isOpen());
    QVERIFY(!dock2->isFloating());
    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 0);

    layout->checkSanity();

    // Cleanup
    dock2->destroyLater();
    WAIT_FOR_DELETED(dock2);
}

void TestDocks::tst_removeItem()
{
    // Tests that MultiSplitterLayout::removeItem() works
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    auto dock2 =
        createDockWidget("dock2", Platform::instance()->tests_createView({ true }), {}, {}, false);
    auto dock3 = createDockWidget("dock3", Platform::instance()->tests_createView({ true }));

    m->addDockWidget(dock1, Location_OnBottom);
    m->addDockWidget(dock2, Location_OnTop, nullptr, InitialVisibilityOption::StartHidden);
    Item *item2 = dock2->dptr()->lastPosition()->lastItem();

    auto dropArea = m->dropArea();
    Core::DropArea *layout = dropArea;

    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 1);

    // 1. Remove an item that's a placeholder

    layout->removeItem(item2);

    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);

    // 2. Remove an item that has an actual widget
    Item *item1 = dock1->dptr()->lastPosition()->lastItem();
    layout->removeItem(item1);
    QCOMPARE(layout->count(), 0);
    QCOMPARE(layout->placeholderCount(), 0);

    // 3. Remove an item that has anchors following one of its other anchors (Tests that anchors
    // stop following) Stack 1, 2, 3
    m->addDockWidget(dock3, Location_OnBottom);
    m->addDockWidget(dock2, Location_OnBottom);
    m->addDockWidget(dock1, Location_OnBottom);
    QCOMPARE(layout->count(), 3);
    QCOMPARE(layout->placeholderCount(), 0);

    dock2->close();
    auto group1 = dock1->dptr()->group();
    dock1->close();
    QVERIFY(WAIT_FOR_DELETED(group1));

    QCOMPARE(layout->count(), 3);
    QCOMPARE(layout->placeholderCount(), 2);

    // Now remove the items
    layout->removeItem(dock2->dptr()->lastPosition()->lastItem());
    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 1);
    layout->checkSanity();
    layout->removeItem(dock1->dptr()->lastPosition()->lastItem());
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);

    // Add again
    m->addDockWidget(dock2, Location_OnBottom);
    m->addDockWidget(dock1, Location_OnBottom);
    dock2->close();
    group1 = dock1->dptr()->group();
    dock1->close();
    QVERIFY(WAIT_FOR_DELETED(group1));

    // Now remove the items, but first dock1
    layout->removeItem(dock1->dptr()->lastPosition()->lastItem());
    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 1);
    layout->checkSanity();
    layout->removeItem(dock2->dptr()->lastPosition()->lastItem());
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);
    layout->checkSanity();

    // Add again, stacked as 1, 2, 3, then close 2 and 3.
    m->addDockWidget(dock2, Location_OnTop);
    m->addDockWidget(dock1, Location_OnTop);

    auto group2 = dock2->dptr()->group();
    dock2->close();
    WAIT_FOR_DELETED(group2);

    auto group3 = dock3->dptr()->group();
    dock3->close();
    WAIT_FOR_DELETED(group3);

    // The second anchor is now following the 3rd, while the 3rd is following 'bottom'
    layout->removeItem(dock3->dptr()->lastPosition()->lastItem()); // will trigger the 3rd anchor to
                                                                   // be removed
    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 1);
    layout->checkSanity();

    dock1->destroyLater();
    dock2->destroyLater();
    dock3->destroyLater();
    WAIT_FOR_DELETED(dock3);
}

void TestDocks::tst_clear()
{
    // Tests MultiSplitterLayout::clear()
    EnsureTopLevelsDeleted e;
    QCOMPARE(Core::Group::dbg_numFrames(), 0);

    auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("2", Platform::instance()->tests_createView({ true }));
    auto dock3 = createDockWidget("3", Platform::instance()->tests_createView({ true }));
    auto fw3 = dock3->floatingWindow();

    m->addDockWidget(dock1, Location_OnLeft);
    m->addDockWidget(dock2, Location_OnRight);
    m->addDockWidget(dock3, Location_OnRight);
    QVERIFY(WAIT_FOR_DELETED(fw3));
    dock3->close();

    QCOMPARE(Core::Group::dbg_numFrames(), 3);

    auto layout = m->multiSplitter();
    layout->clearLayout();

    QCOMPARE(layout->count(), 0);
    QCOMPARE(layout->placeholderCount(), 0);
    layout->checkSanity();

    // Cleanup
    dock3->destroyLater();
    QVERIFY(WAIT_FOR_DELETED(dock3));
}

void TestDocks::tst_samePositionAfterHideRestore()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("2", Platform::instance()->tests_createView({ true }));
    auto dock3 = createDockWidget("3", Platform::instance()->tests_createView({ true }));

    m->addDockWidget(dock1, Location_OnLeft);
    m->addDockWidget(dock2, Location_OnRight);
    m->addDockWidget(dock3, Location_OnRight);
    Rect geo2 = dock2->dptr()->group()->view()->geometry();
    dock2->setFloating(true);

    auto fw2 = dock2->floatingWindow();
    dock2->setFloating(false);
    QVERIFY(WAIT_FOR_DELETED(fw2));
    QCOMPARE(geo2, dock2->dptr()->group()->view()->geometry());
    m->layout()->checkSanity();
}

void TestDocks::tst_startClosed()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));

    auto dropArea = m->dropArea();
    Core::DropArea *layout = dropArea;

    m->addDockWidget(dock1, Location_OnTop);
    Core::Group *group1 = dock1->dptr()->group();
    dock1->close();
    WAIT_FOR_DELETED(group1);

    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 1);

    m->addDockWidget(dock2, Location_OnTop);

    layout->checkSanity();

    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 1);

    dock1->open();
    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 0);
}

void TestDocks::tst_crash()
{
    // tests some crash I got

    EnsureTopLevelsDeleted e;

    auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));
    auto layout = m->multiSplitter();

    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    Item *item1 = layout->itemForGroup(dock1->dptr()->group());
    dock1->addDockWidgetAsTab(dock2);

    QVERIFY(!dock1->isFloating());
    dock1->setFloating(true);
    QVERIFY(dock1->isFloating());
    QVERIFY(!dock1->isInMainWindow());

    Item *layoutItem = dock1->dptr()->lastPosition()->lastItem(dock1);
    QVERIFY(layoutItem && DockRegistry::self()->itemIsInMainWindow(layoutItem));
    QCOMPARE(layoutItem, item1);

    QCOMPARE(layout->placeholderCount(), 0);
    QCOMPARE(layout->count(), 1);

    // Move from tab to bottom
    m->addDockWidget(dock2, KDDockWidgets::Location_OnBottom);

    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 1);
}

void TestDocks::tst_refUnrefItem()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));
    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    m->addDockWidget(dock2, KDDockWidgets::Location_OnRight);
    auto dropArea = m->dropArea();
    auto layout = dropArea;
    ObjectGuard<Core::Group> group1 = dock1->dptr()->group();
    ObjectGuard<Core::Group> group2 = dock2->dptr()->group();
    ObjectGuard<Item> item1 = layout->itemForGroup(group1);
    ObjectGuard<Item> item2 = layout->itemForGroup(group2);
    QVERIFY(item1.data());
    QVERIFY(item2.data());
    QCOMPARE(item1->refCount(), 2); // 2 - the item and its group, which can be persistent
    QCOMPARE(item2->refCount(), 2);

    // 1. Delete a dock widget directly. It should delete its group and also the Item
    delete dock1;
    WAIT_FOR_DELETED(group1);
    QVERIFY(!group1.data());
    QVERIFY(!item1.data());

    // 2. Delete dock3, but neither the group or the item is deleted, since there were two tabs to
    // begin with
    auto dock3 = createDockWidget("dock3", Platform::instance()->tests_createView({ true }));
    QCOMPARE(item2->refCount(), 2);
    dock2->addDockWidgetAsTab(dock3);
    QCOMPARE(item2->refCount(), 3);
    delete dock3;
    QVERIFY(item2.data());
    QCOMPARE(group2->dockWidgets().size(), 1);

    // 3. Close dock2. group2 should be deleted, but item2 preserved.
    QCOMPARE(item2->refCount(), 2);
    dock2->close();
    WAIT_FOR_DELETED(group2);
    QVERIFY(dock2);
    QVERIFY(item2.data());
    QCOMPARE(item2->refCount(), 1);
    QCOMPARE(dock2->dptr()->lastPosition()->lastItem(), item2.data());
    delete dock2;

    QVERIFY(!item2.data());
    QCOMPARE(layout->count(), 1);

    // 4. Move a closed dock widget from one mainwindow to another
    // It should delete its old placeholder
    auto dock4 = createDockWidget("dock4", Platform::instance()->tests_createView({ true }));
    m->addDockWidget(dock4, KDDockWidgets::Location_OnLeft);

    ObjectGuard<Core::Group> group4 = dock4->dptr()->group();
    ObjectGuard<Item> item4 = layout->itemForGroup(group4);
    dock4->close();
    WAIT_FOR_DELETED(group4);
    QCOMPARE(item4->refCount(), 1);
    QVERIFY(item4->isPlaceholder());
    layout->checkSanity();

    auto m2 = createMainWindow();
    m2->addDockWidget(dock4, KDDockWidgets::Location_OnLeft);
    m2->layout()->checkSanity();
    QVERIFY(!item4.data());
}

void TestDocks::tst_placeholderCount()
{
    EnsureTopLevelsDeleted e;
    // Tests MultiSplitterLayout::count(),visibleCount() and placeholdercount()

    // 1. MainWindow with just the initial group.
    auto m = createMainWindow();
    auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("2", Platform::instance()->tests_createView({ true }));
    auto dropArea = m->dropArea();
    auto layout = dropArea;

    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->visibleCount(), 1);
    QCOMPARE(layout->placeholderCount(), 0);

    // 2. MainWindow with central group and left widget
    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->visibleCount(), 2);
    QCOMPARE(layout->placeholderCount(), 0);

    // 3. Add another dockwidget, this time tabbed in the center. It won't increase count, as it
    // reuses an existing group.
    m->addDockWidgetAsTab(dock2);
    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->visibleCount(), 2);
    QCOMPARE(layout->placeholderCount(), 0);

    // 4. Float dock1. It should create a placeholder
    dock1->setFloating(true);

    auto fw = dock1->floatingWindow();

    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->visibleCount(), 1);
    QCOMPARE(layout->placeholderCount(), 1);

    // 5. Re-dock dock1. It should reuse the placeholder
    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->visibleCount(), 2);
    QCOMPARE(layout->placeholderCount(), 0);

    // 6. Again
    dock1->setFloating(true);
    fw = dock1->floatingWindow();
    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->visibleCount(), 2);
    QCOMPARE(layout->placeholderCount(), 0);
    layout->checkSanity();

    WAIT_FOR_DELETED(fw);
}

void TestDocks::tst_availableLengthForOrientation()
{
    EnsureTopLevelsDeleted e;

    // 1. Test a completely empty window, it's available space is its size minus the static
    // separators thickness
    auto m = createMainWindow(Size(800, 500), MainWindowOption_None); // Remove central group
    auto dropArea = m->dropArea();
    Core::DropArea *layout = dropArea;

    int availableWidth = layout->availableLengthForOrientation(Qt::Horizontal);
    int availableHeight = layout->availableLengthForOrientation(Qt::Vertical);
    QCOMPARE(availableWidth, layout->layoutWidth());
    QCOMPARE(availableHeight, layout->layoutHeight());

    // 2. Now do the same, but we have some widget docked

    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    m->addDockWidget(dock1, Location_OnLeft);

    const int dock1MinWidth =
        layout->itemForGroup(dock1->dptr()->group())->minLength(Qt::Horizontal);
    const int dock1MinHeight =
        layout->itemForGroup(dock1->dptr()->group())->minLength(Qt::Vertical);

    availableWidth = layout->availableLengthForOrientation(Qt::Horizontal);
    availableHeight = layout->availableLengthForOrientation(Qt::Vertical);
    QCOMPARE(availableWidth, layout->layoutWidth() - dock1MinWidth);
    QCOMPARE(availableHeight, layout->layoutHeight() - dock1MinHeight);
    m->layout()->checkSanity();
}

void TestDocks::tst_setAsCurrentTab()
{
    EnsureTopLevelsDeleted e;

    // Tests DockWidget::setAsCurrentTab() and DockWidget::isCurrentTab()
    // 1. a single dock widget is current, by definition
    auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
    QVERIFY(dock1->isCurrentTab());

    // 2. Tab dock2 to the group, dock2 is current now
    auto dock2 = createDockWidget("2", Platform::instance()->tests_createView({ true }));
    dock1->addDockWidgetAsTab(dock2);

    QVERIFY(!dock1->isCurrentTab());
    QVERIFY(dock2->isCurrentTab());

    // 3. Set dock1 as current
    dock1->setAsCurrentTab();
    QVERIFY(dock1->isCurrentTab());
    QVERIFY(!dock2->isCurrentTab());

    auto fw = dock1->floatingWindow();
    QVERIFY(fw);
    fw->layout()->checkSanity();

    delete dock1;
    delete dock2;
    WAIT_FOR_DELETED(fw);
}

void TestDocks::tst_placeholderDisappearsOnReadd()
{
    // This tests that addMultiSplitter also updates refcount of placeholders

    // 1. Detach a widget and dock it on the opposite side. Placeholder
    // should have been deleted and anchors properly positioned

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(800, 500), MainWindowOption_None); // Remove central group
    Core::DropArea *layout = m->multiSplitter();

    ObjectGuard<Core::DockWidget> dock1 =
        createDockWidget("1", Platform::instance()->tests_createView({ true }));
    m->addDockWidget(dock1, Location_OnLeft);
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);

    dock1->setFloating(true);
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 1);

    dock1->dptr()->morphIntoFloatingWindow();
    auto fw = dock1->floatingWindow();
    layout->addMultiSplitter(fw->dropArea(), Location_OnRight);

    QCOMPARE(layout->placeholderCount(), 0);
    QCOMPARE(layout->count(), 1);

    layout->checkSanity();
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);

    // The dock1 should occupy the entire width
    QCOMPARE(dock1->dptr()->group()->width(), layout->layoutWidth());

    QVERIFY(WAIT_FOR_DELETED(fw));
}

void TestDocks::tst_placeholdersAreRemovedProperly()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(800, 500), MainWindowOption_None); // Remove central group
    Core::DropArea *layout = m->multiSplitter();
    ObjectGuard<Core::DockWidget> dock1 =
        createDockWidget("1", Platform::instance()->tests_createView({ true }));
    ObjectGuard<Core::DockWidget> dock2 =
        createDockWidget("2", Platform::instance()->tests_createView({ true }));
    m->addDockWidget(dock1, Location_OnLeft);
    Item *item = layout->items().constFirst();
    m->addDockWidget(dock2, Location_OnRight);
    QVERIFY(!item->isPlaceholder());
    dock1->setFloating(true);
    QVERIFY(item->isPlaceholder());

    QCOMPARE(layout->separators().size(), 0);
    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 1);
    layout->removeItem(item);
    QCOMPARE(layout->separators().size(), 0);
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);

    // 2. Recreate the placeholder. This time delete the dock widget to see if placeholder is
    // deleted too.
    m->addDockWidget(dock1, Location_OnLeft);
    dock1->setFloating(true);
    delete dock1;
    QCOMPARE(layout->separators().size(), 0);
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);
    layout->checkSanity();
}

void TestDocks::tst_floatMaintainsSize()
{
    // Tests that when we make a window float by pressing the float button, it will popup with
    // the same size it had when docked

    EnsureTopLevelsDeleted e;
    auto dw1 = newDockWidget("1");
    auto dw2 = newDockWidget("2");

    dw1->addDockWidgetToContainingWindow(dw2, Location_OnRight);
    const int oldWidth2 = dw2->width();
    dw1->open();

    dw2->setFloating(true);
    QTest::qWait(100);

    QVERIFY(std::abs(dw2->width() - oldWidth2) < 16); // 15px for margins
}

void TestDocks::tst_preferredInitialSize()
{
    {
        EnsureTopLevelsDeleted e;
        auto dw1 = newDockWidget("1");
        auto dw2 = newDockWidget("2");
        auto m = createMainWindow(Size(1200, 1200), MainWindowOption_None);

        m->addDockWidget(dw1, Location_OnTop);
        m->addDockWidget(dw2, Location_OnBottom, nullptr, Size(0, 200));

        QCOMPARE(dw2->sizeInLayout().height(), 200);
    }

    {
        // With addDockWidgetToSide

        EnsureTopLevelsDeleted e;
        auto dw1 = newDockWidget("1");
        auto m = createMainWindow(Size(1200, 1200), MainWindowOption_HasCentralGroup);
        m->addDockWidgetToSide(dw1, Location_OnLeft, Size(250, 250));

        QCOMPARE(dw1->sizeInLayout().width(), 250);
    }

    {
        // With StartHidden

        EnsureTopLevelsDeleted e;
        auto dw1 = newDockWidget("1");
        auto m = createMainWindow(Size(1200, 1200), MainWindowOption_HasCentralGroup);
        InitialOption opt;
        opt.visibility = InitialVisibilityOption::StartHidden;
        opt.preferredSize = Size(250, 200);
        m->addDockWidget(dw1, Location_OnLeft, nullptr, opt);
        dw1->open();
        QCOMPARE(dw1->sizeInLayout().width(), 250);
    }

    {
        // With some nesting

        EnsureTopLevelsDeleted e;
        auto dw1 = newDockWidget("1");
        auto dw2 = newDockWidget("2");
        auto m = createMainWindow(Size(1200, 1200), MainWindowOption_HasCentralGroup);
        InitialOption opt;
        opt.visibility = InitialVisibilityOption::StartHidden;
        opt.preferredSize = Size(250, 200);
        m->addDockWidget(dw1, Location_OnLeft, nullptr, opt);
        m->addDockWidget(dw2, Location_OnBottom, dw1, opt);

        dw1->open();
        dw2->open();

        QCOMPARE(dw1->sizeInLayout().width(), 250);
    }

    {
        // One dock on each side of central

        EnsureTopLevelsDeleted e;
        auto dw1 = newDockWidget("1");
        auto dw2 = newDockWidget("2");
        auto m = createMainWindow(Size(1200, 1200), MainWindowOption_HasCentralGroup);
        InitialOption opt;
        opt.visibility = InitialVisibilityOption::StartHidden;
        opt.preferredSize = Size(250, 200);
        m->addDockWidget(dw1, Location_OnLeft, nullptr, opt);
        m->addDockWidget(dw2, Location_OnRight, nullptr, opt);

        dw1->open();
        dw2->open();

        QCOMPARE(dw1->sizeInLayout().width(), 250);
        QCOMPARE(dw2->sizeInLayout().width(), 250);
    }

    {
        // Case where parent container is vertical and our preferred size only has width set
        EnsureTopLevelsDeleted e;
        auto dw1 = newDockWidget("1");
        auto dw2 = newDockWidget("2");
        auto dw3 = newDockWidget("3");
        auto m = createMainWindow(Size(1200, 1200), MainWindowOption_HasCentralGroup);

        m->addDockWidgetToSide(dw1, Location_OnLeft, InitialVisibilityOption::StartHidden);
        m->addDockWidgetToSide(dw2, Location_OnLeft, InitialVisibilityOption::StartHidden);

        InitialOption opt;
        opt.visibility = InitialVisibilityOption::StartVisible;
        opt.preferredSize = Size(201, 200);
        m->addDockWidgetToSide(dw3, Location_OnLeft, opt);
        QCOMPARE(dw3->sizeInLayout().width(), 201);
    }

    {
        // Case where parent container is vertical and our preferred size only has width set
        // (same as previous, but with all hidden at first)
        EnsureTopLevelsDeleted e;
        auto dw1 = newDockWidget("1");
        auto dw2 = newDockWidget("2");
        auto dw3 = newDockWidget("3");
        auto m = createMainWindow(Size(1200, 1200), MainWindowOption_HasCentralGroup);

        m->addDockWidgetToSide(dw1, Location_OnLeft, InitialVisibilityOption::StartHidden);
        m->addDockWidgetToSide(dw2, Location_OnLeft, InitialVisibilityOption::StartHidden);

        InitialOption opt;
        opt.visibility = InitialVisibilityOption::StartHidden;
        opt.preferredSize = Size(201, 200);
        m->addDockWidgetToSide(dw3, Location_OnLeft, opt);
        dw3->open();
        QCOMPARE(dw3->sizeInLayout().width(), 201);
    }
}

void TestDocks::tst_preferredInitialSizeVsMinSize()
{
    // Tests what happens if we ask for a preferredInitial size smaller than min-size
    // Should use the min size instead

    auto createDw = [](const QString &name, Size min) -> Core::DockWidget * {
        auto dw = newDockWidget(name);
        dw->setGuestView(Platform::instance()->tests_createView({ true, {}, min })->asWrapper());
        return dw;
    };

    {
        EnsureTopLevelsDeleted e;
        const int minHeight = 201;
        const int preferredHeight = 200;
        auto dw1 = newDockWidget("1");
        auto dw2 = createDw("2", { 201, minHeight });
        auto m = createMainWindow(Size(1200, 1200), MainWindowOption_None);

        m->addDockWidget(dw1, Location_OnTop);
        m->addDockWidget(dw2, Location_OnBottom, nullptr, Size(0, preferredHeight));

        QVERIFY(dw2->sizeInLayout().height() >= minHeight);
    }

    {
        // With addDockWidgetToSide

        EnsureTopLevelsDeleted e;
        const int minWidth = 300;
        auto dw1 = createDw("1", { minWidth, 300 });
        auto m = createMainWindow(Size(1200, 1200), MainWindowOption_HasCentralGroup);
        m->addDockWidgetToSide(dw1, Location_OnLeft, Size(250, 250));

        QVERIFY(dw1->sizeInLayout().width() >= minWidth);
    }

    {
        // With StartHidden

        EnsureTopLevelsDeleted e;
        const int minWidth = 300;
        auto dw1 = createDw("1", { minWidth, 300 });
        auto m = createMainWindow(Size(1200, 1200), MainWindowOption_HasCentralGroup);
        InitialOption opt;
        opt.visibility = InitialVisibilityOption::StartHidden;
        opt.preferredSize = Size(minWidth - 50, 200);
        m->addDockWidget(dw1, Location_OnLeft, nullptr, opt);
        dw1->open();
        QVERIFY(dw1->sizeInLayout().width() >= minWidth);
    }

    {
        // With some nesting

        EnsureTopLevelsDeleted e;
        const int minWidth = 300;
        auto dw1 = createDw("1", { minWidth, 300 });
        auto dw2 = newDockWidget("2");
        auto m = createMainWindow(Size(1200, 1200), MainWindowOption_HasCentralGroup);
        InitialOption opt;
        opt.visibility = InitialVisibilityOption::StartHidden;
        opt.preferredSize = Size(minWidth - 50, 200);
        m->addDockWidget(dw1, Location_OnLeft, nullptr, opt);
        m->addDockWidget(dw2, Location_OnBottom, dw1, opt);

        dw1->open();
        dw2->open();

        QVERIFY(dw1->sizeInLayout().width() >= minWidth);
    }

    {
        // One dock on each side of central

        EnsureTopLevelsDeleted e;
        const int minWidth = 300;
        auto dw1 = createDw("1", { minWidth, 300 });
        auto dw2 = createDw("2", { minWidth, 300 });
        auto m = createMainWindow(Size(1200, 1200), MainWindowOption_HasCentralGroup);
        InitialOption opt;
        opt.visibility = InitialVisibilityOption::StartHidden;
        opt.preferredSize = Size(minWidth - 50, 200);
        m->addDockWidget(dw1, Location_OnLeft, nullptr, opt);
        m->addDockWidget(dw2, Location_OnRight, nullptr, opt);

        dw1->open();
        dw2->open();

        QVERIFY(dw1->sizeInLayout().width() >= minWidth);
        QVERIFY(dw2->sizeInLayout().width() >= minWidth);
    }

    {
        // Case where parent container is vertical and our preferred size only has width set
        EnsureTopLevelsDeleted e;
        auto dw1 = newDockWidget("1");
        auto dw2 = newDockWidget("2");
        const int minWidth = 300;
        auto dw3 = createDw("3", { minWidth, 300 });
        auto m = createMainWindow(Size(1200, 1200), MainWindowOption_HasCentralGroup);

        m->addDockWidgetToSide(dw1, Location_OnLeft, InitialVisibilityOption::StartHidden);
        m->addDockWidgetToSide(dw2, Location_OnLeft, InitialVisibilityOption::StartHidden);

        InitialOption opt;
        opt.visibility = InitialVisibilityOption::StartVisible;
        opt.preferredSize = Size(minWidth - 50, 200);
        m->addDockWidgetToSide(dw3, Location_OnLeft, opt);
        QVERIFY(dw3->sizeInLayout().width() >= minWidth);
    }

    {
        // Case where parent container is vertical and our preferred size only has width set
        // (same as previous, but with all hidden at first)
        EnsureTopLevelsDeleted e;
        auto dw1 = newDockWidget("1");
        auto dw2 = newDockWidget("2");
        const int minWidth = 300;
        auto dw3 = createDw("3", { minWidth, 300 });
        auto m = createMainWindow(Size(1200, 1200), MainWindowOption_HasCentralGroup);

        m->addDockWidgetToSide(dw1, Location_OnLeft, InitialVisibilityOption::StartHidden);
        m->addDockWidgetToSide(dw2, Location_OnLeft, InitialVisibilityOption::StartHidden);

        InitialOption opt;
        opt.visibility = InitialVisibilityOption::StartHidden;
        opt.preferredSize = Size(minWidth - 50, 200);
        m->addDockWidgetToSide(dw3, Location_OnLeft, opt);
        dw3->open();
        QVERIFY(dw3->sizeInLayout().width() >= minWidth);
    }
}

void TestDocks::tst_closeAllDockWidgets()
{
    EnsureTopLevelsDeleted e;

    auto m = createMainWindow();
    auto dropArea = m->dropArea();
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));
    auto dock3 = createDockWidget("dock3", Platform::instance()->tests_createView({ true }));
    auto dock4 = createDockWidget("dock4", Platform::instance()->tests_createView({ true }));
    auto dock5 = createDockWidget("dock5", Platform::instance()->tests_createView({ true }));
    auto dock6 = createDockWidget("dock6", Platform::instance()->tests_createView({ true }));

    ObjectGuard<Core::FloatingWindow> fw = dock3->dptr()->morphIntoFloatingWindow();

    nestDockWidget(dock4, dropArea, nullptr, KDDockWidgets::Location_OnRight);
    nestDockWidget(dock5, dropArea, nullptr, KDDockWidgets::Location_OnTop);

    const int oldFWHeight = fw->height();
    nestDockWidget(dock6, fw->dropArea(), nullptr, KDDockWidgets::Location_OnTop);

    QVERIFY(oldFWHeight <= fw->height());
    QCOMPARE(fw->groups().size(), 2);

    QVERIFY(dock3->window()->equals(fw->view()));
    QVERIFY(dock4->window()->equals(m->view()));
    QVERIFY(dock5->window()->equals(m->view()));
    QVERIFY(dock6->window()->equals(fw->view()));
    auto layout = m->multiSplitter();
    layout->checkSanity();
    DockRegistry::self()->clear();
    layout->checkSanity();

    WAIT_FOR_DELETED(fw);
    QVERIFY(!fw);

    QVERIFY(dock1->window()->equals(dock1->view()));
    QVERIFY(dock2->window()->equals(dock2->view()));
    QVERIFY(dock3->window()->equals(dock3->view()));
    QVERIFY(dock4->window()->equals(dock4->view()));
    QVERIFY(dock5->window()->equals(dock5->view()));
    QVERIFY(dock6->window()->equals(dock6->view()));

    QVERIFY(!dock1->isVisible());
    QVERIFY(!dock2->isVisible());
    QVERIFY(!dock3->isVisible());
    QVERIFY(!dock4->isVisible());
    QVERIFY(!dock5->isVisible());
    QVERIFY(!dock6->isVisible());

    delete dock1;
    delete dock2;
    delete dock3;
    delete dock4;
    delete dock5;
    delete dock6;
}

void TestDocks::tst_toggleMiddleDockCrash()
{
    // tests some crash I got

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(800, 500), MainWindowOption_None); // Remove central group
    Core::DropArea *layout = m->multiSplitter();
    ObjectGuard<Core::DockWidget> dock1 =
        createDockWidget("1", Platform::instance()->tests_createView({ true }));
    ObjectGuard<Core::DockWidget> dock2 =
        createDockWidget("2", Platform::instance()->tests_createView({ true }));
    ObjectGuard<Core::DockWidget> dock3 =
        createDockWidget("3", Platform::instance()->tests_createView({ true }));

    m->addDockWidget(dock1, Location_OnLeft);
    m->addDockWidget(dock2, Location_OnRight);
    m->addDockWidget(dock3, Location_OnRight);

    QCOMPARE(layout->count(), 3);
    QCOMPARE(layout->placeholderCount(), 0);

    auto group = dock2->dptr()->group();
    dock2->close();
    QVERIFY(WAIT_FOR_DELETED(group));

    QCOMPARE(layout->count(), 3);
    QCOMPARE(layout->placeholderCount(), 1);
    QVERIFY(layout->checkSanity());

    dock2->open();
    layout->checkSanity();
}

void TestDocks::tst_stealFrame()
{
    // Tests using addWidget() with dock widgets which are already in a layout
    EnsureTopLevelsDeleted e;
    auto m1 = createMainWindow(Size(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));

    auto m2 = createMainWindow(Size(800, 500), MainWindowOption_None);
    auto dock3 = createDockWidget("dock3", Platform::instance()->tests_createView({ true }));
    auto dock4 = createDockWidget("dock4", Platform::instance()->tests_createView({ true }));

    auto dropArea1 = m1->dropArea();
    auto dropArea2 = m2->dropArea();

    m1->addDockWidget(dock1, Location_OnRight);
    m1->addDockWidget(dock2, Location_OnRight);
    m2->addDockWidget(dock3, Location_OnRight);
    m2->addDockWidget(dock4, Location_OnRight);

    // 1. MainWindow #1 steals a widget from MainWindow2 and vice-versa
    m1->addDockWidget(dock3, Location_OnRight);
    m1->addDockWidget(dock4, Location_OnRight);
    m2->addDockWidget(dock1, Location_OnRight);
    ObjectGuard<Item> item2 = dropArea1->itemForGroup(dock2->dptr()->group());
    m2->addDockWidget(dock2, Location_OnRight);
    QVERIFY(!item2.data());

    QCOMPARE(dropArea1->count(), 2);
    QCOMPARE(dropArea2->count(), 2);
    QCOMPARE(dropArea1->placeholderCount(), 0);
    QCOMPARE(dropArea2->placeholderCount(), 0);

    // 2. MainWindow #1 steals a widget from MainWindow2 and vice-versa, but adds as tabs
    dock1->addDockWidgetAsTab(dock3);
    ObjectGuard<Core::Group> f2 = dock2->dptr()->group();
    dock4->addDockWidgetAsTab(dock2);
    QVERIFY(WAIT_FOR_DELETED(f2.data()));
    QVERIFY(!f2.data());

    QCOMPARE(dropArea1->count(), 1);
    QCOMPARE(dropArea2->count(), 1);
    QCOMPARE(dropArea1->placeholderCount(), 0);
    QCOMPARE(dropArea2->placeholderCount(), 0);

    // 3. Test stealing a tab from the same tab-widget we're in. Nothing happens
    {
        SetExpectedWarning sew(
            "Already contains "); // Suppress the aborting this
                                  // time
        dock1->addDockWidgetAsTab(dock3);
        QCOMPARE(dock1->dptr()->group()->dockWidgetCount(), 2);
    }

    // 4. Steal from another tab which resides in another Frame, which resides in the same main
    // window
    m1->addDockWidget(dock1, Location_OnTop);
    f2 = dock2->dptr()->group();
    dock1->addDockWidgetAsTab(dock2);
    QCOMPARE(dock1->dptr()->group()->dockWidgetCount(), 2);
    QCOMPARE(dock4->dptr()->group()->dockWidgetCount(), 1);

    QCOMPARE(dropArea1->count(), 2);
    QCOMPARE(dropArea1->placeholderCount(), 0);

    // 5. And also steal a side-by-side one into the tab
    ObjectGuard<Core::Group> f4 = dock4->dptr()->group();
    dock1->addDockWidgetAsTab(dock4);
    QVERIFY(WAIT_FOR_DELETED(f4.data()));
    QCOMPARE(dropArea1->count(), 1);
    QCOMPARE(dropArea1->placeholderCount(), 0);

    // 6. Steal from tab to side-by-side within the same MainWindow
    m1->addDockWidget(dock1, Location_OnLeft);
    QCOMPARE(dropArea1->count(), 2);
    QCOMPARE(dropArea1->placeholderCount(), 0);

    // 6. side-by-side to side-by-side within same MainWindow
    m2->addDockWidget(dock1, Location_OnRight);
    QCOMPARE(dropArea2->count(), 2);
    QCOMPARE(dropArea2->placeholderCount(), 0);

    {
        SetExpectedWarning sew(
            "Invalid parameters "); // Suppress the aborting
                                    // this time
        m2->addDockWidget(dock1, Location_OnLeft, dock1);
        QCOMPARE(dropArea2->count(), 2); // Nothing happened
        QCOMPARE(dropArea2->placeholderCount(), 0);
        QVERIFY(dock1->isVisible());
    }

    QVERIFY(dock1->isVisible());
    m2->addDockWidget(dock1, Location_OnLeft, nullptr); // Should not warn

    QVERIFY(dock1->isVisible());
    QCOMPARE(dropArea2->count(), 2); // Nothing happened
    QCOMPARE(dropArea2->placeholderCount(), 0);

    m2->addDockWidget(dock1, Location_OnLeft, nullptr);
    QVERIFY(dock1->isVisible());
    QCOMPARE(dropArea2->count(), 2); // Nothing happened
    QCOMPARE(dropArea2->placeholderCount(), 0);
    dropArea1->checkSanity();
    dropArea2->checkSanity();
}

void TestDocks::tst_setFloatingWhenWasTabbed()
{
    // Tests DockWidget::isTabbed() and DockWidget::setFloating(false|true) when tabbed (it should
    // redock) setFloating(false) for side-by-side is tested in another function

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));

    // 1. Two floating dock widgets. They are floating, not tabbed.
    QVERIFY(!dock1->isTabbed());
    QVERIFY(!dock2->isTabbed());
    QVERIFY(dock1->isFloating());
    QVERIFY(dock2->isFloating());

    // 2. Dock a floating dock into another floating dock. They're not floating anymore, just
    // tabbed.
    dock1->addDockWidgetAsTab(dock2);
    QVERIFY(dock1->isTabbed());
    QVERIFY(dock2->isTabbed());
    QVERIFY(!dock1->isFloating());
    QVERIFY(!dock2->isFloating());

    // 2.1 Set one of them invisible. // Not much will happen, the tab will be still there, just
    // showing an empty space. Users should use close() instead. Tabwidgets control visibility, they
    // hide the widget when it's not the current tab.
    dock2->setVisible(false);
    QVERIFY(dock2->isTabbed());
    QVERIFY(!dock1->isFloating());
    QCOMPARE(dock2->dptr()->group()->dockWidgetCount(), 2);
    // 3. Set one floating. Now both cease to be tabbed, and both are floating.
    dock1->setFloating(true);
    QVERIFY(dock1->isFloating());
    QVERIFY(dock2->isFloating());
    QVERIFY(!dock1->isTabbed());
    QVERIFY(!dock2->isTabbed());

    // 4. Dock one floating dock into another, side-by-side. They're neither docking or tabbed now.
    dock1->addDockWidgetToContainingWindow(dock2, KDDockWidgets::Location_OnLeft);
    QVERIFY(!dock1->isFloating());
    QVERIFY(!dock2->isFloating());
    QVERIFY(!dock1->isTabbed());
    QVERIFY(!dock2->isTabbed());

    // 5. float one of them, now both are floating, not tabbed anymore.
    dock2->setFloating(true);
    QVERIFY(dock1->isFloating());
    QVERIFY(dock2->isFloating());
    QVERIFY(!dock1->isTabbed());
    QVERIFY(!dock2->isTabbed());

    // 6. With two dock widgets tabbed, detach 1, and reattach it, via
    // DockWidget::setFloating(false)
    m->addDockWidgetAsTab(dock1);
    m->addDockWidgetAsTab(dock2);

    dock2->setFloating(true);
    QVERIFY(dock1->isTabbed());
    QVERIFY(!dock2->isTabbed());
    QVERIFY(!dock1->isFloating());
    QVERIFY(dock2->isFloating());

    QCOMPARE(dock2->dptr()->lastPosition()->lastTabIndex(), 1);
    QVERIFY(dock2->dptr()->lastPosition()->lastItem());
    dock2->setFloating(false);

    QVERIFY(dock1->isTabbed());
    QVERIFY(dock2->isTabbed());
    QVERIFY(!dock1->isFloating());
    QVERIFY(!dock2->isFloating());

    // 7. Call setFloating(true) on an already docked widget
    auto dock3 = createDockWidget("dock3", Platform::instance()->tests_createView({ true }));
    dock3->setFloating(true);
    dock3->setFloating(true);

    // 8. Tab 3 together, detach the middle one, reattach the middle one, it should go to the
    // middle.
    m->addDockWidgetAsTab(dock3);
    dock2->setFloating(true);
    QVERIFY(dock2->isFloating());
    dock2->setFloating(false);
    QVERIFY(!dock2->isFloating());
    QVERIFY(dock2->isTabbed());
    QCOMPARE(dock2->dptr()->group()->indexOfDockWidget(dock2), 1);

    // 10. Float dock1, and dock it to main window as tab. This tests Option_AlwaysShowsTabs.
    dock1->setFloating(true);
    dock2->setFloating(true);
    dock3->setFloating(true);

    m->addDockWidgetAsTab(dock1);
    QVERIFY(!dock1->isFloating());
    QVERIFY(dock1->isTabbed());
    dock1->setFloating(true);
    dock1->setFloating(false);
    QCOMPARE(dock1->dptr()->group()->dockWidgetCount(), 1);
    // Cleanup
    m->addDockWidgetAsTab(dock2);
    m->addDockWidgetAsTab(dock3);
    m->destroyLater();
    auto window = m.release();
    WAIT_FOR_DELETED(window);
}

void TestDocks::tst_tabTitleChanges()
{
    // Tests that the tab's title changes if the dock widget's title changes
    EnsureTopLevelsDeleted e;
    auto dw1 = newDockWidget(QStringLiteral("1"));
    auto dw2 = newDockWidget(QStringLiteral("2"));

    dw1->addDockWidgetAsTab(dw2);

    Core::TabBar *tb = dw1->dptr()->group()->stack()->tabBar();
    QCOMPARE(tb->text(0), QStringLiteral("1"));
    dw1->setTitle(QStringLiteral("other"));
    QCOMPARE(tb->text(0), QStringLiteral("other"));
}

void TestDocks::tst_setWidget()
{
    EnsureTopLevelsDeleted e;
    auto dw = newDockWidget(QStringLiteral("FOO"));
    auto button1 = Platform::instance()->tests_createView({ true });
    auto button2 = Platform::instance()->tests_createView({ true });
    dw->setGuestView(button1->asWrapper());
    dw->setGuestView(button2->asWrapper());
    delete button1;
    delete dw;
}

void TestDocks::tst_floatingLastPosAfterDoubleClose()
{
    EnsureTopLevelsDeleted e;
    auto d1 = newDockWidget(QStringLiteral("a"));
    QVERIFY(d1->dptr()->lastPosition()->lastFloatingGeometry().isNull());
    QVERIFY(!d1->isVisible());
    d1->close();
    QVERIFY(d1->dptr()->lastPosition()->lastFloatingGeometry().isNull());
    delete d1;
}

void TestDocks::tst_honourGeometryOfHiddenWindow()
{
    EnsureTopLevelsDeleted e;

    auto d1 = newDockWidget("1");
    auto guest = Platform::instance()->tests_createFocusableView({ true });
    d1->setGuestView(guest->asWrapper());

    QVERIFY(!d1->isVisible());

    // Clear had a bug where it saved the position of all dock widgets being closed
    DockRegistry::self()->clear();

    const Rect suggestedGeo(150, 150, 300, 500);
    d1->view()->setGeometry(suggestedGeo);

    d1->open();
    QCOMPARE(d1->window()->window()->geometry(), suggestedGeo);
}

void TestDocks::tst_registry()
{
    EnsureTopLevelsDeleted e;
    auto dr = DockRegistry::self();

    QCOMPARE(dr->dockwidgets().size(), 0);
    auto dw = newDockWidget(QStringLiteral("dw1"));
    auto guest = Platform::instance()->tests_createView({});
    dw->setGuestView(guest->asWrapper());
    delete dw;
}

void TestDocks::tst_posAfterLeftDetach()
{
    {
        EnsureTopLevelsDeleted e;
        auto fw = createFloatingWindow();
        auto dock2 = createDockWidget("doc2");
        QTest::qWait(100);
        nestDockWidget(dock2, fw->dropArea(), nullptr, KDDockWidgets::Location_OnRight);
        QTest::qWait(100);
        QVERIFY(fw->dropArea()->checkSanity());
        // When dragging the right one there was a bug where it jumped
        const Point globalSrc = dock2->mapToGlobal(Point(0, 0));
        const int offset = 10;
        const Point globalDest = globalSrc + Point(offset, 0);
        QVERIFY(dock2->isVisible());

        // Flutter is a bit slower showing stuff, needs 1 event loop
        QTest::qWait(100);

        drag(dock2->view(), globalDest);
        QVERIFY(fw->dropArea()->checkSanity());
        const Point actualEndPos = dock2->mapToGlobal(Point(0, 0));
        QVERIFY(actualEndPos.x() - globalSrc.x()
                < offset + 5); // 5px so we have margin for window system fluctuations. The actual
                               // bug was a very big jump like 50px, so a 5 margin is fine to test
                               // that the bug doesn't happen

        delete dock2;
        fw->destroyLater();
        WAIT_FOR_DELETED(fw);
    }

    {
        EnsureTopLevelsDeleted e;
        auto fw = createFloatingWindow();
        auto dock2 = createDockWidget("doc2");
        nestDockWidget(dock2, fw->dropArea(), nullptr, KDDockWidgets::Location_OnRight);
        QVERIFY(fw->dropArea()->checkSanity());

        const int originalX = dock2->mapToGlobal(Point(0, 0)).x();
        dock2->dptr()->group()->titleBar()->makeWindow();
        const int finalX = dock2->mapToGlobal(Point(0, 0)).x();

        QVERIFY(finalX - originalX < 10); // 10 or some other small number that is less than say 200

        delete dock2;
        fw->destroyLater();
        WAIT_FOR_DELETED(fw);
    }
}

void TestDocks::tst_preventClose()
{
    EnsureTopLevelsDeleted e;

    auto nonClosableWidget = Platform::instance()->tests_createNonClosableView();
    auto dock1 = newDockWidget("1");
    dock1->setGuestView(nonClosableWidget->asWrapper());

    // 1. Test a floating dock widget
    dock1->view()->resize(Size(200, 200));
    dock1->open();
    QVERIFY(dock1->isVisible());
    dock1->close();
    QVERIFY(dock1->isVisible());

    // 2. Morph it into a FlatingWindow
    dock1->dptr()->morphIntoFloatingWindow();
    dock1->close();
    QVERIFY(dock1->isVisible());
    dock1->dptr()->group()->titleBar()->onCloseClicked();
    QVERIFY(dock1->isVisible());
    auto fw = dock1->floatingWindow();
    fw->view()->close();
    QVERIFY(dock1->isVisible());

    // Put into a main window
    auto m = createMainWindow();
    m->addDockWidget(dock1, KDDockWidgets::Location_OnRight);
    m->close();
    QVERIFY(dock1->isVisible());
}

void TestDocks::tst_propagateMinSize()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dropArea = m->dropArea();

    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));
    auto dock3 = createDockWidget("dock3", Platform::instance()->tests_createView({ true }));

    nestDockWidget(dock1, dropArea, nullptr, KDDockWidgets::Location_OnRight);
    nestDockWidget(dock2, dropArea, nullptr, KDDockWidgets::Location_OnRight);
    nestDockWidget(dock3, dropArea, nullptr, KDDockWidgets::Location_OnRight);
}

void TestDocks::tst_createFloatingWindow()
{
    EnsureTopLevelsDeleted e;

    auto dock = createDockWidget("doc1");
    QVERIFY(dock);
    QVERIFY(dock->isFloating());

    QCOMPARE(dock->uniqueName(), QLatin1String("doc1")); // 1.0 objectName() is inherited

    ObjectGuard<Core::FloatingWindow> window = dock->floatingWindow();
    QVERIFY(window); // 1.1 DockWidget creates a FloatingWindow and is reparented
    QVERIFY(window->dropArea()->checkSanity());
    dock->destroyLater();
    QVERIFY(WAIT_FOR_DELETED(dock));
    QVERIFY(WAIT_FOR_DELETED(window)); // 1.2 Floating Window is destroyed
                                       // when DockWidget is destroyed
    QVERIFY(!window);
}

void TestDocks::tst_addAndReadd()
{
    EnsureTopLevelsDeleted e;

    // 1. This just tests some crash I got.
    // Make a dock widget float and immediately reattach it
    auto m = createMainWindow();

    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    dock1->setFloating(true);
    m->layout()->checkSanity();
    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    dock1->dptr()->group()->titleBar()->makeWindow();
    m->layout()->checkSanity();
    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    dock1->dptr()->group()->titleBar()->makeWindow();
    m->layout()->checkSanity();

    auto fw = dock1->floatingWindow();
    QVERIFY(fw);
    auto dropArea = m->dropArea();
    dragFloatingWindowTo(fw, dropArea, DropLocation_Right);
    QVERIFY(dock1->dptr()->group()->titleBar()->isVisible());
    fw->titleBar()->makeWindow();
    m->layout()->checkSanity();

    // Cleanup
    delete dock1;
    WAIT_FOR_DELETED(fw);
}

void TestDocks::tst_addToSmallMainWindow1()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));
    auto dock3 = createDockWidget("dock3", Platform::instance()->tests_createView({ true }));
    auto dock4 = createDockWidget("dock4", Platform::instance()->tests_createView({ true }));

    const int mainWindowLength = 400;

    m->view()->window()->resize(mainWindowLength, mainWindowLength);
    QTest::qWait(100);

    dock1->view()->resize(Size(800, 800));
    dock2->view()->resize(Size(800, 800));
    dock3->view()->resize(Size(800, 800));

    // Add as tabbed:
    m->addDockWidgetAsTab(dock1);

    QCOMPARE(m->height(), mainWindowLength);

    QTest::qWait(300);
    if (dock1->height() > mainWindowLength) {
        KDDW_INFO("dock1->height={} ; mainWindowLength={}", dock1->height(), mainWindowLength);
        QVERIFY(false);
    }

    QVERIFY(dock1->width() <= mainWindowLength);

    // Add in area:
    m->addDockWidget(dock2, Location_OnLeft);
    m->addDockWidget(dock3, Location_OnTop, dock2);
    m->addDockWidget(dock4, Location_OnBottom);

    auto dropArea = m->dropArea();

    QVERIFY(dropArea->checkSanity());
    QVERIFY(dock2->width() < mainWindowLength);
    QVERIFY(dock3->height() < m->height());
    QVERIFY(dock4->height() < m->height());
}

void TestDocks::tst_addToSmallMainWindow2()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dropArea = m->dropArea();
    auto dock1 = createDockWidget(
        "dock1", Platform::instance()->tests_createView({ true, {}, Size(100, 100) }));
    auto dock2 = createDockWidget(
        "dock2", Platform::instance()->tests_createView({ true, {}, Size(100, 100) }));
    m->addDockWidgetAsTab(dock1);
    m->view()->window()->resize(osWindowMinWidth(), 200);

    WAIT_FOR_RESIZE(m->view());

    QVERIFY(std::abs(m->width() - osWindowMinWidth()) < 30); // Not very important verification. Anyway,
                                                             // using 15 to account for margins and what
                                                             // not.
    m->addDockWidget(dock2, KDDockWidgets::Location_OnRight);
    if (Platform::instance()->isQtWidgets())
        QVERIFY(WAIT_FOR_RESIZE(m.get()));
    else
        QTest::qWait(100);


    QVERIFY(dropArea->layoutWidth() > osWindowMinWidth());
    Margins margins = m->centerWidgetMargins();
    QCOMPARE(dropArea->layoutWidth(), m->width() - margins.left() - margins.right());
    QVERIFY(m->dropArea()->checkSanity());
}

void TestDocks::tst_addToSmallMainWindow3()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dropArea = m->dropArea();
    auto dock1 =
        createDockWidget("dock1", Platform::instance()->tests_createView({ true, {}, { 0, 0 } }));
    auto dock2 =
        createDockWidget("dock2", Platform::instance()->tests_createView({ true, {}, { 0, 0 } }));
    m->addDockWidgetAsTab(dock1);
    m->view()->window()->resize(osWindowMinWidth(), 200);
    QTest::qWait(200);
    QVERIFY(std::abs(m->width() - osWindowMinWidth()) < 15); // Not very important verification. Anyway,
                                                             // using 15 to account for margins and what
                                                             // not.

    auto fw = dock2->dptr()->morphIntoFloatingWindow();
    QVERIFY(fw->isVisible());
    QVERIFY(dropArea->checkSanity());
    dragFloatingWindowTo(fw, dropArea, DropLocation_Right);
    QVERIFY(m->dropArea()->checkSanity());
    delete fw;
}

void TestDocks::tst_addToSmallMainWindow4()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(100, 100), MainWindowOption_None);

    QTest::qWait(100);
    QCOMPARE(m->height(), 100);

    auto dropArea = m->dropArea();
    auto dock1 = createDockWidget(
        "dock1", Platform::instance()->tests_createView({ true, {}, Size(50, 50) }));
    auto dock2 = createDockWidget(
        "dock2", Platform::instance()->tests_createView({ true, {}, Size(50, 50) }));
    Core::DropArea *layout = dropArea;
    m->addDockWidget(dock1, KDDockWidgets::Location_OnBottom);
    WAIT_FOR_RESIZE(m->view());

    m->addDockWidget(dock2, KDDockWidgets::Location_OnBottom);
    WAIT_FOR_RESIZE(m->view());
    QVERIFY(m->dropArea()->checkSanity());

    const int item2MinHeight =
        layout->itemForGroup(dock2->dptr()->group())->minLength(Qt::Vertical);
    QCOMPARE(dropArea->layoutHeight(),
             dock1->dptr()->group()->height() + item2MinHeight + Item::layoutSpacing);
}

void TestDocks::tst_addToSmallMainWindow5()
{
    EnsureTopLevelsDeleted e;
    // Test test shouldn't spit any warnings

    auto m = createMainWindow(Size(100, 100), MainWindowOption_None);
    auto dock1 = createDockWidget(
        "dock1", Platform::instance()->tests_createView({ true, {}, Size(50, 240) }));
    auto dock2 = createDockWidget(
        "dock2", Platform::instance()->tests_createView({ true, {}, Size(50, 240) }));
    m->addDockWidget(dock1, KDDockWidgets::Location_OnBottom);
    m->addDockWidget(dock2, KDDockWidgets::Location_OnBottom);
    QVERIFY(m->dropArea()->checkSanity());
}

void TestDocks::tst_fairResizeAfterRemoveWidget()
{
    // 1. Add 3 dock widgets horizontally, remove the middle one, make sure
    // both left and right widgets get a share of the new available space

    EnsureTopLevelsDeleted e;

    Core::DockWidget *dock1 =
        createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    Core::DockWidget *dock2 =
        createDockWidget("dock2", Platform::instance()->tests_createView({ true }));
    Core::DockWidget *dock3 =
        createDockWidget("dock3", Platform::instance()->tests_createView({ true }));

    dock1->addDockWidgetToContainingWindow(dock2, Location_OnRight);
    dock1->addDockWidgetToContainingWindow(dock3, Location_OnRight, dock2);

    auto fw = dock1->floatingWindow();

    ObjectGuard<Core::Group> group2 = dock2->dptr()->group();

    const int oldWidth1 = dock1->dptr()->group()->width();
    const int oldWidth3 = dock3->dptr()->group()->width();
    Core::DropArea *layout = fw->dropArea();
    QCOMPARE(layout->count(), 3);
    QCOMPARE(layout->visibleCount(), 3);
    QCOMPARE(layout->placeholderCount(), 0);

    delete dock2;
    Platform::instance()->tests_waitForDeleted(group2);
    QVERIFY(!group2);

    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->visibleCount(), 2);
    QCOMPARE(layout->placeholderCount(), 0);

    const int delta1 = (dock1->dptr()->group()->width() - oldWidth1);
    const int delta3 = (dock3->dptr()->group()->width() - oldWidth3);

    QVERIFY(delta1 > 0);
    QVERIFY(delta3 > 0);
    QVERIFY(std::abs(delta3 - delta1) <= 1); // Both dock1 and dock3 should have increased by the same
                                             // amount
}

void TestDocks::tst_restoreNonClosable()
{
    // Tests that restoring state also restores the Option_NotClosable option

    {
        // Basic case:

        EnsureTopLevelsDeleted e;
        auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
        auto dock1 =
            createDockWidget("one", Platform::instance()->tests_createFocusableView({ true }),
                             DockWidgetOption_NotClosable);
        QCOMPARE(dock1->options(), DockWidgetOption_NotClosable);

        LayoutSaver saver;
        const QByteArray saved = saver.serializeLayout();
        QVERIFY(saver.restoreLayout(saved));
        QCOMPARE(dock1->options(), DockWidgetOption_NotClosable);
    }

    {
        // Case from issue #137
        auto m = createMainWindow(Size(800, 500), MainWindowOption_None);

        auto dock1 =
            createDockWidget("1", Platform::instance()->tests_createFocusableView({ true }));
        auto dock2 =
            createDockWidget("2", Platform::instance()->tests_createFocusableView({ true }),
                             DockWidgetOption_NotClosable);
        auto dock3 =
            createDockWidget("3", Platform::instance()->tests_createFocusableView({ true }));

        m->addDockWidget(dock1, Location_OnLeft);
        m->addDockWidget(dock2, Location_OnLeft);
        m->addDockWidget(dock3, Location_OnLeft);

        QCOMPARE(dock2->options(), DockWidgetOption_NotClosable);
        dock2->setFloating(true);
        QCOMPARE(dock2->options(), DockWidgetOption_NotClosable);

        Core::TitleBar *tb = dock2->dptr()->group()->actualTitleBar();
        QVERIFY(tb->isVisible());
        QVERIFY(!tb->closeButtonEnabled());

        LayoutSaver saver;
        const QByteArray saved = saver.serializeLayout();

        QVERIFY(saver.restoreLayout(saved));
        QCOMPARE(dock2->options(), DockWidgetOption_NotClosable);

        tb = dock2->dptr()->group()->actualTitleBar();
        QVERIFY(tb->isVisible());

        QVERIFY(!tb->closeButtonEnabled());
    }
}

void TestDocks::tst_restoreRestoresMainWindowPosition()
{
    // Tests that MainWindow position is restored by LayoutSaver
    {
        EnsureTopLevelsDeleted e;
        auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
        const Point originalPos = m->pos();

        LayoutSaver saver;
        const QByteArray saved = saver.serializeLayout();

        m->view()->move(originalPos + Point(100, 100));

        saver.restoreLayout(saved);
        QCOMPARE(originalPos, m->pos());
    }
}

void TestDocks::tst_resizeViaAnchorsAfterPlaceholderCreation()
{
    EnsureTopLevelsDeleted e;

    // Stack 1, 2, 3, close 2, close 2
    {
        auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
        Core::DropArea *layout = m->multiSplitter();
        auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
        auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));
        auto dock3 = createDockWidget("dock3", Platform::instance()->tests_createView({ true }));
        m->addDockWidget(dock3, Location_OnTop);
        m->addDockWidget(dock2, Location_OnTop);
        m->addDockWidget(dock1, Location_OnTop);
        QCOMPARE(layout->separators().size(), 2);
        dock2->close();
        WAIT_FOR_RESIZE(dock3->view());
        QCOMPARE(layout->separators().size(), 1);
        layout->checkSanity();

        // Cleanup:
        dock2->destroyLater();
        WAIT_FOR_DELETED(dock2);
    }

    {
        auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
        auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));
        auto dock3 = createDockWidget("dock3", Platform::instance()->tests_createView({ true }));
        auto dock4 = createDockWidget("dock4", Platform::instance()->tests_createView({ true }));
        m->addDockWidget(dock1, Location_OnRight);
        m->addDockWidget(dock2, Location_OnRight);
        m->addDockWidget(dock3, Location_OnRight);
        m->addDockWidget(dock4, Location_OnRight);

        Core::DropArea *layout = m->multiSplitter();

        Item *item1 = layout->itemForGroup(dock1->dptr()->group());
        Item *item2 = layout->itemForGroup(dock2->dptr()->group());
        Item *item3 = layout->itemForGroup(dock3->dptr()->group());
        Item *item4 = layout->itemForGroup(dock4->dptr()->group());

        const auto separators = layout->separators();
        QCOMPARE(separators.size(), 3);

        auto anchor1 = separators[0];
        int boundToTheRight = layout->rootItem()->maxPosForSeparator(anchor1);
        int expectedBoundToTheRight = layout->layoutWidth() - 3 * Item::layoutSpacing
            - item2->minLength(Qt::Horizontal) - item3->minLength(Qt::Horizontal)
            - item4->minLength(Qt::Horizontal);

        QCOMPARE(boundToTheRight, expectedBoundToTheRight);

        dock3->close();
        WAIT_FOR_RESIZE(dock2->view());

        QVERIFY(!item1->isPlaceholder());
        QVERIFY(!item2->isPlaceholder());
        QVERIFY(item3->isPlaceholder());
        QVERIFY(!item4->isPlaceholder());

        boundToTheRight = layout->rootItem()->maxPosForSeparator(anchor1);
        expectedBoundToTheRight = layout->layoutWidth() - 2 * Item::layoutSpacing
            - item2->minLength(Qt::Horizontal) - item4->minLength(Qt::Horizontal);

        QCOMPARE(boundToTheRight, expectedBoundToTheRight);
        dock3->destroyLater();
        WAIT_FOR_DELETED(dock3);
    }
}

void TestDocks::tst_rectForDropCrash()
{
    // Tests a crash I got in MultiSplitterLayout::rectForDrop() (asserts being hit)
    EnsureTopLevelsDeleted e;

    auto m = createMainWindow();
    m->view()->resize(Size(500, 500));
    m->show();

    auto layout = m->multiSplitter();

    auto w1 = Platform::instance()->tests_createView({ true, {}, Size(400, 400) });
    auto w2 = Platform::instance()->tests_createView({ true, {}, Size(400, 400) });

    auto d1 = createDockWidget("1", w1);
    auto d2 = createDockWidget("2", w2);

    m->addDockWidget(d1, Location_OnTop);
    Item *centralItem = m->dropArea()->centralFrame();
    {
        WindowBeingDragged wbd2(d2->floatingWindow());
        layout->rectForDrop(&wbd2, Location_OnTop, centralItem);
    }
    layout->checkSanity();
}

void TestDocks::tst_restoreAfterResize()
{
    // Tests a crash I got when the layout received a resize event *while* restoring

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(500, 500), {}, "tst_restoreAfterResize");
    auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
    m->addDockWidget(dock1, Location_OnLeft);
    auto layout = m->multiSplitter();
    const Size oldContentsSize = layout->layoutSize();
    const Size oldWindowSize = m->size();
    LayoutSaver saver;
    QVERIFY(saver.saveToFile(QStringLiteral("layout_tst_restoreAfterResize.json")));
    m->view()->resize(Size(1000, 1000));
    QVERIFY(saver.restoreFromFile(QStringLiteral("layout_tst_restoreAfterResize.json")));

    if (oldContentsSize != layout->layoutSize()) {
        // Hard to reproduce but sometimes happens. Added a wait to see if it's timing related
        KDDW_INFO("tst_restoreAfterResize: Unexpected layout size={}, expected={}", layout->layoutSize(), oldContentsSize);
        QTest::qWait(1000);
        QCOMPARE(oldContentsSize, layout->layoutSize());
    }

    QCOMPARE(oldWindowSize, m->size());
}

void TestDocks::tst_restoreWithNonClosableWidget()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(500, 500), {}, "tst_restoreWithNonClosableWidget");
    auto dock1 = createDockWidget("1", Platform::instance()->tests_createNonClosableView(),
                                  DockWidgetOption_NotClosable);
    m->addDockWidget(dock1, Location_OnLeft);
    auto layout = m->multiSplitter();

    LayoutSaver saver;
    QVERIFY(saver.saveToFile(QStringLiteral("layout_tst_restoreWithNonClosableWidget.json")));
    QVERIFY(saver.restoreFromFile(QStringLiteral("layout_tst_restoreWithNonClosableWidget.json")));
    QVERIFY(layout->checkSanity());
}

void TestDocks::tst_restoreNestedAndTabbed()
{
    // Just a more involved test

    Point oldFW4Pos;
    Rect oldGeo;
    {
        EnsureTopLevelsDeleted e;
        auto m =
            createMainWindow(Size(800, 500), MainWindowOption_None, "tst_restoreNestedAndTabbed");
        m->view()->move(500, 500);
        oldGeo = m->geometry();
        auto layout = m->multiSplitter();
        auto dock1 =
            createDockWidget("1", Platform::instance()->tests_createFocusableView({ true }));
        auto dock2 =
            createDockWidget("2", Platform::instance()->tests_createFocusableView({ true }));
        auto dock3 =
            createDockWidget("3", Platform::instance()->tests_createFocusableView({ true }));
        auto dock4 =
            createDockWidget("4", Platform::instance()->tests_createFocusableView({ true }));
        auto dock5 =
            createDockWidget("5", Platform::instance()->tests_createFocusableView({ true }));
        dock4->addDockWidgetAsTab(dock5);
        oldFW4Pos = dock4->window()->pos();

        m->addDockWidget(dock1, Location_OnLeft);
        m->addDockWidget(dock2, Location_OnRight);
        dock2->addDockWidgetAsTab(dock3);
        dock2->setAsCurrentTab();
        QCOMPARE(dock2->dptr()->group()->currentTabIndex(), 0);
        QCOMPARE(dock4->dptr()->group()->currentTabIndex(), 1);

        LayoutSaver saver;
        QVERIFY(saver.saveToFile(QStringLiteral("layout_tst_restoreNestedAndTabbed.json")));
        QVERIFY(layout->checkSanity());

        // Let it be destroyed, we'll restore a new one
    }

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(800, 500), MainWindowOption_None, "tst_restoreNestedAndTabbed");
    auto layout = m->multiSplitter();
    auto dock1 = createDockWidget("1", Platform::instance()->tests_createFocusableView({ true }));
    auto dock2 = createDockWidget("2", Platform::instance()->tests_createFocusableView({ true }));
    auto dock3 = createDockWidget("3", Platform::instance()->tests_createFocusableView({ true }));
    auto dock4 = createDockWidget("4", Platform::instance()->tests_createFocusableView({ true }));
    auto dock5 = createDockWidget("5", Platform::instance()->tests_createFocusableView({ true }));

    LayoutSaver saver;
    QVERIFY(saver.restoreFromFile(QStringLiteral("layout_tst_restoreNestedAndTabbed.json")));
    QVERIFY(layout->checkSanity());

    auto fw4 = dock4->floatingWindow();
    QVERIFY(fw4);
    QCOMPARE(dock4->window()->window(), dock5->window()->window());
    QCOMPARE(fw4->pos(), oldFW4Pos);

    QVERIFY(dock1->window()->equals(m->view()));
    QVERIFY(dock2->window()->equals(m->view()));
    QVERIFY(dock3->window()->equals(m->view()));

    QCOMPARE(dock2->dptr()->group()->currentTabIndex(), 0);
    QCOMPARE(dock4->dptr()->group()->currentTabIndex(), 1);

    QCOMPARE(m->geometry(), oldGeo);
}

void TestDocks::tst_restoreCrash()
{
    EnsureTopLevelsDeleted e;

    {
        // Create a main window, with a left dock, save it to disk.
        auto m = createMainWindow({}, {}, "tst_restoreCrash");
        auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
        m->addDockWidget(dock1, Location_OnLeft);
        LayoutSaver saver;
        QVERIFY(saver.saveToFile(QStringLiteral("layout_tst_restoreCrash.json")));
    }

    // Restore
    auto m = createMainWindow({}, {}, "tst_restoreCrash");
    auto layout = m->multiSplitter();
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    QVERIFY(dock1->isFloating());
    QVERIFY(layout->checkSanity());

    LayoutSaver saver;
    QVERIFY(saver.restoreFromFile(QStringLiteral("layout_tst_restoreCrash.json")));
    QVERIFY(layout->checkSanity());
    QVERIFY(!dock1->isFloating());
}

void TestDocks::tst_restoreSideBySide()
{
    // Save a layout that has a floating window with nesting
    EnsureTopLevelsDeleted e;

    Size item2MinSize;
    {
        EnsureTopLevelsDeleted e1;
        // MainWindow:
        auto m =
            createMainWindow(Size(500, 500), MainWindowOption_HasCentralGroup, "tst_restoreTwice");
        auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
        m->addDockWidgetAsTab(dock1);
        auto layout = m->multiSplitter();

        // FloatingWindow:
        auto dock2 = createDockWidget("2", Platform::instance()->tests_createView({ true }));
        auto dock3 = createDockWidget("3", Platform::instance()->tests_createView({ true }));
        dock2->addDockWidgetToContainingWindow(dock3, Location_OnRight);
        auto fw2 = dock2->floatingWindow();
        item2MinSize = fw2->layout()->itemForGroup(dock2->dptr()->group())->minSize();
        LayoutSaver saver;
        QVERIFY(saver.saveToFile(QStringLiteral("layout_tst_restoreSideBySide.json")));
        QVERIFY(layout->checkSanity());
    }

    {
        auto m =
            createMainWindow(Size(500, 500), MainWindowOption_HasCentralGroup, "tst_restoreTwice");
        auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
        auto dock2 = createDockWidget("2", Platform::instance()->tests_createView({ true }));
        auto dock3 = createDockWidget("3", Platform::instance()->tests_createView({ true }));

        LayoutSaver restorer;
        QVERIFY(restorer.restoreFromFile(QStringLiteral("layout_tst_restoreSideBySide.json")));

        QVERIFY(dock1->window()->equals(m->view()));
        QVERIFY(dock2->window()->equals(dock3->window()));
    }
}

void TestDocks::tst_restoreGroupOptions()
{
    // tests that saving with some Config flags and restoring with other Config flags
    // doesn't get us into trouble. Namely we shouldn't restore "alwaysShowFlags" and
    // just follow current config flags
    QByteArray saved;

    {
        EnsureTopLevelsDeleted e;

        KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_HideTitleBarWhenTabsVisible
                                               | KDDockWidgets::Config::Flag_AlwaysShowTabs);

        auto m = createMainWindow({ 500, 500 }, {}, "mw1");

        auto d1 = createDockWidget("1", Platform::instance()->tests_createFocusableView({ true }));
        m->addDockWidget(d1, Location_OnTop);

        LayoutSaver saver;
        saved = saver.serializeLayout();
    } // flags are reset at end of scope

    auto m = createMainWindow({ 500, 500 }, {}, "mw1");
    auto d1 = createDockWidget("1", Platform::instance()->tests_createFocusableView({ true }));

    LayoutSaver saver;
    QVERIFY(saver.restoreLayout(saved));

    Group *group = d1->dptr()->group();
    QVERIFY(!group->options()); // Shouldn't have FrameOption_AlwaysShowsTabs anymore
}

void TestDocks::tst_dockWidgetTabIndexOverride()
{
    EnsureTopLevelsDeleted e;
    Config::self().setDockWidgetTabIndexOverrideFunc([](Core::DockWidget *, Core::Group *, int) {
        return 0;
    });

    auto m =
        createMainWindow(Size(500, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("2", Platform::instance()->tests_createView({ true }));
    m->addDockWidget(dock1, Location_OnTop);
    dock1->addDockWidgetAsTab(dock2);

    /// Redocking will use our override func and move it to index 0
    QVERIFY(dock2->tabIndex() == 1);
    dock2->setFloating(true);
    dock2->setFloating(false);
    QVERIFY(dock2->tabIndex() == 0);
}

void TestDocks::tst_closeGroup()
{
    // Tests closing a whole group via Group::close()
    EnsureTopLevelsDeleted e;

    auto m =
        createMainWindow(Size(500, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("2", Platform::instance()->tests_createView({ true }));
    m->addDockWidget(dock1, Location_OnTop);
    dock1->addDockWidgetAsTab(dock2);

    QVERIFY(dock1->isOpen());
    QVERIFY(dock2->isOpen());

    auto group = dock1->d->group();
    QVERIFY(group->close());
    QVERIFY(!dock1->isOpen());
    QVERIFY(!dock2->isOpen());
}

void TestDocks::tst_placeholderInFloatingWindow()
{
    // Tests that placeholders in floating windows get priority
    // over main window placeholders if the last state was floating

    EnsureTopLevelsDeleted e;

    auto m =
        createMainWindow(Size(500, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("2", Platform::instance()->tests_createView({ true }));

    // Make dock1 have a placeholder in the main window:
    m->addDockWidget(dock1, Location_OnTop);
    dock2->setFloating(true);
    QVERIFY(!dock1->hasPreviousDockedLocation());
    auto lastPos1 = dock1->d->lastPosition();
    QVERIFY(lastPos1->lastItem());
    QVERIFY(lastPos1->placeholderCount() == 2);

    // float it, then nest it with dock2 (floating)
    dock1->setFloating(true);

    Platform::instance()->tests_wait(1); // needed as FloatingWindow gets shown delayed
    QVERIFY(lastPos1->placeholderCount() == 2);

    dock2->addDockWidgetToContainingWindow(dock1, Location_OnTop);

    Platform::instance()->tests_wait(1); // needed as FloatingWindow gets deleteLater()
    QVERIFY(lastPos1->placeholderCount() == 2);

    dock1->close();
    dock1->show();

    Platform::instance()->tests_wait(1);
    QVERIFY(lastPos1->placeholderCount() == 2);

    QVERIFY(!dock1->isInMainWindow());
    QVERIFY(dock1->floatingWindow() == dock2->floatingWindow());

    // Do it again
    dock1->close();
    dock1->show();
    QVERIFY(dock1->floatingWindow() == dock2->floatingWindow());

    // Float by titlebar
    dock1->titleBar()->onFloatClicked();
    Platform::instance()->tests_wait(1); // needed as FloatingWindow gets deleteLater()
    QVERIFY(lastPos1->placeholderCount() == 3);

    auto previousPos = lastPos1->lastItem(dock1);
    QVERIFY(previousPos);
    dock1->titleBar()->onFloatClicked();
    QVERIFY(dock1->floatingWindow() == dock2->floatingWindow());

    Platform::instance()->tests_wait(10);
}

void TestDocks::tst_restoreWithCentralFrameWithTabs()
{
    EnsureTopLevelsDeleted e;
    auto m =
        createMainWindow(Size(500, 500), MainWindowOption_HasCentralGroup, "tst_restoreTwice");
    auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("2", Platform::instance()->tests_createView({ true }));
    m->addDockWidgetAsTab(dock1);
    m->addDockWidgetAsTab(dock2);

    QCOMPARE(DockRegistry::self()->groups().size(), 1);

    LayoutSaver saver;
    const QByteArray saved = saver.serializeLayout();
    QVERIFY(saver.restoreLayout(saved));

    QCOMPARE(DockRegistry::self()->groups().size(), 1);
}

void TestDocks::tst_restoreAfterMinSizeChanges()
{
    {
        EnsureTopLevelsDeleted e;
        auto m = createMainWindow(Size(1000, 1000), {}, "tst_restoreWithPlaceholder");

        auto guest = Platform::instance()->tests_createView({ true });
        auto dockA = createDockWidget("A", guest);
        const auto minSize = Size(300, 300);
        dockA->view()->setMinimumSize(minSize);

        guest = Platform::instance()->tests_createView({ true });
        auto dockB = createDockWidget("B", guest);

        m->addDockWidget(dockB, Location_OnLeft);
        m->addDockWidget(dockA, Location_OnLeft, nullptr, minSize);

        LayoutSaver saver;
        const auto saved = saver.serializeLayout();

        // Min size increaseses:
        dockA->view()->setMinimumSize({ 600, 300 });
        dockA->close();
        dockB->close();

        saver.restoreLayout(saved);
    }

    // Now from an existing saved layout
    {
        auto m = createMainWindow(Size(500, 500), MainWindowOption_HasCentralWidget, "mainWindowId1");

        createDockWidget("_kddw_internal_dummy");
        createDockWidget("_kddw_internal_dummy2");
        for (int i = 0; i <= 8; ++i) {
            auto dock = createDockWidget((std::string("dockwidget_tests_") + std::to_string(i)).c_str());
            dock->view()->setMinimumSize({ 300, 300 });
        }

        bool ok = false;
        LayoutSaver restorer;
        const QByteArray data = Platform::instance()->readFile(":/layouts/minSizeChanges.json", /*by-ref*/ ok);
        QVERIFY(ok);
        QVERIFY(restorer.restoreLayout(data));
    }
}

void TestDocks::tst_restoreWithPlaceholder()
{
    // Float dock1, save and restore, then unfloat and see if dock2 goes back to where it was

    EnsureTopLevelsDeleted e;
    {
        auto m = createMainWindow(Size(500, 500), {}, "tst_restoreWithPlaceholder");

        auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
        m->addDockWidget(dock1, Location_OnLeft);
        auto layout = m->multiSplitter();
        dock1->setFloating(true);

        LayoutSaver saver;
        QVERIFY(saver.saveToFile(QStringLiteral("layout_tst_restoreWithPlaceholder.json")));

        dock1->close();

        QVERIFY(saver.restoreFromFile(QStringLiteral("layout_tst_restoreWithPlaceholder.json")));
        QVERIFY(layout->checkSanity());

        QVERIFY(dock1->isFloating());
        QVERIFY(dock1->isVisible());
        QCOMPARE(layout->count(), 1);
        QCOMPARE(layout->placeholderCount(), 1);

        dock1->setFloating(false); // Put it back. Should go back because the placeholder was
                                   // restored.

        QVERIFY(!dock1->isFloating());
        QVERIFY(dock1->isVisible());
        QCOMPARE(layout->count(), 1);
        QCOMPARE(layout->placeholderCount(), 0);
    }

    // Try again, but on a different main window
    auto m = createMainWindow(Size(500, 500), {}, "tst_restoreWithPlaceholder");
    auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
    auto layout = m->multiSplitter();

    LayoutSaver saver;
    QVERIFY(saver.restoreFromFile(QStringLiteral("layout_tst_restoreWithPlaceholder.json")));
    QVERIFY(layout->checkSanity());

    QVERIFY(dock1->isFloating());
    QVERIFY(dock1->isVisible());
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 1);

    dock1->setFloating(false); // Put it back. Should go back because the placeholder was restored.

    QVERIFY(!dock1->isFloating());
    QVERIFY(dock1->isVisible());
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);
}

void TestDocks::tst_restoreWithAffinity()
{
    EnsureTopLevelsDeleted e;

    auto m1 = createMainWindow(Size(500, 500));
    m1->setAffinities({ "a1" });
    auto m2 = createMainWindow(Size(500, 500));
    m2->setAffinities({ "a2" });

    auto dock1 =
        createDockWidget("1", Platform::instance()->tests_createView({ true }), {}, {}, true, "a1");
    m1->addDockWidget(dock1, Location_OnLeft);

    auto dock2 =
        createDockWidget("2", Platform::instance()->tests_createView({ true }), {}, {}, true, "a2");
    dock2->setFloating(true);
    dock2->open();

    LayoutSaver saver;
    saver.setAffinityNames({ "a1" });
    const QByteArray saved1 = saver.serializeLayout();

    ObjectGuard<Core::FloatingWindow> fw2 = dock2->floatingWindow();
    saver.restoreLayout(saved1);

    // Restoring affinity 1 shouldn't close affinity 2
    QVERIFY(!fw2.isNull());
    QVERIFY(dock2->isVisible());

    // Close all and restore again
    DockRegistry::self()->clear();
    QVERIFY(!dock2->isVisible());

    saver.restoreLayout(saved1);

    // dock2 continues closed
    QVERIFY(!dock2->isVisible());

    // dock1 was restored
    QVERIFY(dock1->isVisible());
    QVERIFY(!dock1->isFloating());
    QVERIFY(dock1->window()->equals(m1->view()));
}

void TestDocks::tst_marginsAfterRestore()
{
    EnsureTopLevelsDeleted e;
    {
        EnsureTopLevelsDeleted e1;
        // MainWindow:
        auto m = createMainWindow(Size(500, 500), {}, "tst_marginsAfterRestore");
        auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
        m->addDockWidget(dock1, Location_OnLeft);
        auto layout = m->multiSplitter();

        LayoutSaver saver;
        QVERIFY(saver.saveToFile(QStringLiteral("layout_tst_marginsAfterRestore.json")));
        QVERIFY(saver.restoreFromFile(QStringLiteral("layout_tst_marginsAfterRestore.json")));
        QVERIFY(layout->checkSanity());

        dock1->setFloating(true);

        auto fw = dock1->floatingWindow();
        QVERIFY(fw);
        layout->addWidget(fw->dropArea()->view(), Location_OnRight);

        layout->checkSanity();
    }
}

void TestDocks::tst_mainWindowToggle()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(500, 500), {}, "tst_marginsAfterRestore");
    auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
    m->addDockWidget(dock1, Location_OnLeft);
    QVERIFY(dock1->isOpen());
    QVERIFY(m->isVisible());

    m->close();
    QVERIFY(!m->isVisible());
    QVERIFY(!dock1->isOpen());
    Platform::instance()->tests_wait(1000);
    m->setVisible(true);
    QVERIFY(m->isVisible());

    /// TODO: uncomment once #360 is fixed
    // QVERIFY(dock1->isOpen());
}

void TestDocks::tst_startDragging()
{
    auto dc = DragController::instance();

    {
        EnsureTopLevelsDeleted e;
        auto m = createMainWindow(Size(500, 500), {}, "tst_marginsAfterRestore");
        auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
        m->addDockWidget(dock1, Location_OnLeft);

        QVERIFY(!dock1->isFloating());
        QVERIFY(!dc->isDragging());

        QVERIFY(dock1->startDragging());
        QVERIFY(dc->isDragging());
        QVERIFY(dock1->isFloating());

        dc->programmaticStopDrag();
        QVERIFY(!dc->isDragging());
    }
}

void TestDocks::tst_restoreWithNewDockWidgets()
{
    // Tests that if the LayoutSaver doesn't know about some dock widget
    // when it saves the layout, then it won't close it when restoring layout
    // it will just be ignored.
    EnsureTopLevelsDeleted e;
    LayoutSaver saver;
    const QByteArray saved = saver.serializeLayout();
    QVERIFY(!saved.isEmpty());

    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    dock1->open();

    QVERIFY(saver.restoreLayout(saved));
    QVERIFY(dock1->isVisible());
}

void TestDocks::tst_restoreWithDockFactory()
{
    // Tests that restore the layout with a missing dock widget will recreate the dock widget using
    // a factory

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(501, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
    m->addDockWidget(dock1, Location_OnLeft);
    auto layout = m->multiSplitter();

    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->placeholderCount(), 0);
    QCOMPARE(layout->visibleCount(), 1);

    LayoutSaver saver;
    QByteArray saved = saver.serializeLayout();
    QVERIFY(!saved.isEmpty());
    ObjectGuard<Core::Group> f1 = dock1->dptr()->group();
    delete dock1;
    WAIT_FOR_DELETED(f1);
    QVERIFY(!f1);

    // Directly deleted don't leave placeolders. We could though.
    QCOMPARE(layout->count(), 0);

    {
        // We don't know how to create the dock widget
        QVERIFY(saver.restoreLayout(saved));
        QCOMPARE(layout->count(), 1);
    }

    // Now try with a factory func
    DockWidgetFactoryFunc func = [](const QString &) {
        return createDockWidget("1", Platform::instance()->tests_createView({ true }), {}, {},
                                /*show=*/false);
    };

    KDDockWidgets::Config::self().setDockWidgetFactoryFunc(func);
    QVERIFY(saver.restoreLayout(saved));
    QCOMPARE(layout->count(), 1);
    QCOMPARE(layout->visibleCount(), 1);
    layout->checkSanity();
}

void TestDocks::tst_restoreWithDockFactory2()
{
    // Teste that the factory function can do id remapping.
    // For example, if id "foo" is missing, the factory can return a
    // dock widget with id "bar" if it feels like it

    auto m = createMainWindow(Size(501, 500), MainWindowOption_None);

    auto dock1 = createDockWidget("dw1", Platform::instance()->tests_createView({ true }));
    m->addDockWidget(dock1, Location_OnLeft);
    dock1->setFloating(true);

    LayoutSaver saver;
    const QByteArray saved = saver.serializeLayout();
    delete dock1;

    DockWidgetFactoryFunc func = [](const QString &) {
        // A factory func which does id remapping
        return createDockWidget("dw2", Platform::instance()->tests_createView({ true }), {}, {},
                                /*show=*/false);
    };

    KDDockWidgets::Config::self().setDockWidgetFactoryFunc(func);
    saver.restoreLayout(saved);
}

void TestDocks::tst_addDockWidgetToMainWindow()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));

    m->addDockWidget(dock1, Location_OnRight, nullptr);
    m->addDockWidget(dock2, Location_OnTop, dock1);
    QVERIFY(m->dropArea()->checkSanity());

    QVERIFY(dock1->window()->equals(m->view()));
    QVERIFY(dock2->window()->equals(m->view()));

    QVERIFY(dock1->dptr()->group()->view()->y() > dock2->dptr()->group()->view()->y());
    QCOMPARE(dock1->dptr()->group()->view()->x(), dock2->dptr()->group()->view()->x());
}

void TestDocks::tst_addDockWidgetToContainingWindow()
{
    { // Test with a floating window
        EnsureTopLevelsDeleted e;

        auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
        auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));
        auto dock3 = createDockWidget("dock3", Platform::instance()->tests_createView({ true }));

        dock1->addDockWidgetToContainingWindow(dock2, Location_OnRight);
        dock1->addDockWidgetToContainingWindow(dock3, Location_OnTop, dock2);

        QVERIFY(dock1->window()->equals(dock2->window()));
        QVERIFY(dock2->window()->equals(dock3->window()));

        QVERIFY(dock3->dptr()->group()->view()->y() < dock2->dptr()->group()->view()->y());
        QVERIFY(dock1->dptr()->group()->view()->x() < dock2->dptr()->group()->view()->x());
        QCOMPARE(dock2->dptr()->group()->view()->x(), dock3->dptr()->group()->view()->x());
    }

    { // Also test with a main window
        EnsureTopLevelsDeleted e;

        auto m = createMainWindow();
        auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
        auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));

        m->addDockWidget(dock1, Location_OnRight, nullptr);
        dock1->addDockWidgetToContainingWindow(dock2, Location_OnRight);

        QCOMPARE(dock1->window()->window(), dock2->window()->window());
        QVERIFY(m->view()->equals(dock2->window()));
    }
}

void TestDocks::tst_notClosable()
{
    {
        EnsureTopLevelsDeleted e;
        auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }),
                                      DockWidgetOption_NotClosable);
        auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));
        dock1->addDockWidgetAsTab(dock2);

        auto fw = dock1->floatingWindow();
        QVERIFY(fw);
        Core::TitleBar *titlebarFW = fw->titleBar();
        Core::TitleBar *titleBarFrame = fw->groups().at(0)->titleBar();
        QVERIFY(titlebarFW->isCloseButtonVisible());
        QVERIFY(!titlebarFW->isCloseButtonEnabled());
        QVERIFY(!titleBarFrame->isCloseButtonVisible());
        QVERIFY(!titleBarFrame->isCloseButtonEnabled());

        dock1->setOptions(DockWidgetOption_None);
        QVERIFY(titlebarFW->isCloseButtonVisible());
        QVERIFY(titlebarFW->isCloseButtonEnabled());
        QVERIFY(!titleBarFrame->isCloseButtonVisible());
        QVERIFY(!titleBarFrame->isCloseButtonEnabled());

        dock1->setOptions(DockWidgetOption_NotClosable);
        QVERIFY(titlebarFW->isCloseButtonVisible());
        QVERIFY(!titlebarFW->isCloseButtonEnabled());
        QVERIFY(!titleBarFrame->isCloseButtonVisible());
        QVERIFY(!titleBarFrame->isCloseButtonEnabled());
    }

    {
        // Now dock dock1 into dock1 instead
        EnsureTopLevelsDeleted e;
        auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }),
                                      DockWidgetOption_NotClosable);
        auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));

        dock2->dptr()->morphIntoFloatingWindow();
        dock2->addDockWidgetAsTab(dock1);

        auto fw = dock1->floatingWindow();
        QVERIFY(fw);
        Core::TitleBar *titlebarFW = fw->titleBar();
        Core::TitleBar *titleBarFrame = fw->groups().at(0)->titleBar();

        QVERIFY(titlebarFW->isCloseButtonVisible());
        QVERIFY(!titleBarFrame->isCloseButtonVisible());
        QVERIFY(!titleBarFrame->isCloseButtonEnabled());
    }
}

void TestDocks::tst_dragOverTitleBar()
{
    // Tests that dragging over the title bar is returning DropLocation_None

    EnsureTopLevelsDeleted e;
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));

    DropArea *da = dock1->floatingWindow()->dropArea();
    Core::FloatingWindow *fw1 = dock1->floatingWindow();
    Core::FloatingWindow *fw2 = dock2->floatingWindow();
    {
        WindowBeingDragged wbd(fw2, fw2);

        const Point titleBarPoint = fw1->titleBar()->mapToGlobal(Point(5, 5));

        auto loc = da->hover(&wbd, titleBarPoint);
        QCOMPARE(loc, DropLocation_None);
    }

    delete fw1;
    delete fw2;
}

void TestDocks::tst_setFloatingGeometry()
{
    EnsureTopLevelsDeleted e;
    auto dock1 = createDockWidget(
        "dock1", Platform::instance()->tests_createView({ true, {}, Size(100, 100) }));

    QVERIFY(dock1->isVisible());
    const Rect requestedGeo = Rect(70, 70, 400, 400);
    dock1->setFloatingGeometry(requestedGeo);
    QCOMPARE(dock1->window()->geometry(), requestedGeo);

    dock1->close();
    QVERIFY(!dock1->isVisible());

    const Rect requestedGeo2 = Rect(80, 80, 400, 400);
    dock1->setFloatingGeometry(requestedGeo2);
    dock1->open();

    QCOMPARE(dock1->window()->geometry(), requestedGeo2);
}

void TestDocks::tst_setFloatingAfterDraggedFromTabToSideBySide()
{
    EnsureTopLevelsDeleted e;
    {
        auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
        auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));
        auto dropArea = m->dropArea();
        auto layout = dropArea;

        m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
        dock1->addDockWidgetAsTab(dock2);

        // Move from tab to bottom
        m->addDockWidget(dock2, KDDockWidgets::Location_OnBottom);

        QCOMPARE(layout->count(), 2);
        QCOMPARE(layout->placeholderCount(), 0);

        dock2->setFloating(true);
        dock2->setFloating(false);
        QCOMPARE(layout->count(), 2);
        QCOMPARE(layout->placeholderCount(), 0);
        QVERIFY(!dock2->isFloating());
    }

    {
        // 2. Try again, but now detach from tab before putting it on the bottom. What was happening
        // was that MultiSplitterLayout::addWidget() called with a MultiSplitter as widget wasn't
        // setting the layout items for the dock widgets
        auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
        auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));
        auto dropArea = m->dropArea();
        auto layout = dropArea;

        m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
        dock1->addDockWidgetAsTab(dock2);
        Item *oldItem2 = dock2->dptr()->lastPosition()->lastItem();
        QCOMPARE(oldItem2, layout->itemForGroup(dock2->dptr()->group()));


        // Detach tab
        dock1->dptr()->group()->detachTab(dock2);
        QVERIFY(layout->checkSanity());
        auto fw2 = dock2->floatingWindow();
        QVERIFY(fw2);
        QCOMPARE(dock2->dptr()->lastPosition()->lastItem(dock2), oldItem2);
        Item *item2 = fw2->dropArea()->itemForGroup(dock2->dptr()->group());
        QVERIFY(item2);
        QVERIFY(item2->host() == fw2->dropArea()->asLayoutingHost());
        QVERIFY(!layout->itemForGroup(dock2->dptr()->group()));

        // Move from tab to bottom
        layout->addWidget(fw2->dropArea()->view(), KDDockWidgets::Location_OnRight, nullptr);
        QVERIFY(layout->checkSanity());
        QVERIFY(dock2->dptr()->lastPosition()->lastItem());
        QCOMPARE(layout->count(), 2);
        QCOMPARE(layout->placeholderCount(), 0);

        dock2->setFloating(true);
        QVERIFY(layout->checkSanity());

        dock2->setFloating(false);

        QCOMPARE(layout->count(), 2);
        QCOMPARE(layout->placeholderCount(), 0);
        QVERIFY(!dock2->isFloating());
        QVERIFY(layout->checkSanity());

        WAIT_FOR_DELETED(fw2);
    }
}

void TestDocks::tst_setFloatingAFrameWithTabs()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dropArea = m->dropArea();
    auto layout = dropArea;
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));
    m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    dock1->addDockWidgetAsTab(dock2);

    // Make it float
    dock1->dptr()->group()->titleBar()->onFloatClicked();

    auto fw = dock1->floatingWindow();
    QVERIFY(fw);
    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 1);

    auto group1 = dock1->dptr()->group();
    QVERIFY(group1->layoutItem());

    // Attach it again
    dock1->dptr()->group()->titleBar()->onFloatClicked();

    QCOMPARE(layout->count(), 2);
    QCOMPARE(layout->placeholderCount(), 0);
    QVERIFY(dock1->window()->equals(m->view()));

    WAIT_FOR_DELETED(fw);
}

void TestDocks::tst_toggleDockWidgetWithHiddenTitleBar()
{
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_HideTitleBarWhenTabsVisible
                                           | KDDockWidgets::Config::Flag_AlwaysShowTabs);
    auto m = createMainWindow();

    auto d1 = createDockWidget("1", Platform::instance()->tests_createFocusableView({ true }));
    m->addDockWidget(d1, Location_OnTop);

    QVERIFY(!d1->dptr()->group()->titleBar()->isVisible());

    d1->toggleAction()->setChecked(false);
    auto f1 = d1->dptr()->group();
    WAIT_FOR_DELETED(f1);
    SetExpectedWarning expected("Trying to use a group that's being deleted");
    d1->toggleAction()->setChecked(true);
    QVERIFY(d1->dptr()->group());
    QVERIFY(!d1->dptr()->group()->titleBar()->isVisible());
}

void TestDocks::tst_availableSizeWithPlaceholders()
{
    // Tests MultiSplitterLayout::available() with and without placeholders. The result should be
    // the same.

    EnsureTopLevelsDeleted e;
    std::vector<DockDescriptor> docks1 = {
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
    };

    std::vector<DockDescriptor> docks2 = {
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartVisible },
    };

    std::vector<DockDescriptor> empty;

    auto m1 = createMainWindow(docks1);
    auto m2 = createMainWindow(docks2);
    auto m3 = createMainWindow(empty);

    auto layout1 = m1->multiSplitter();
    auto layout2 = m2->multiSplitter();
    auto layout3 = m3->multiSplitter();

    auto f20 = docks2.at(0).createdDock->dptr()->group();

    docks2.at(0).createdDock->close();
    docks2.at(1).createdDock->close();
    docks2.at(2).createdDock->close();
    QVERIFY(WAIT_FOR_DELETED(f20));

    QCOMPARE(layout1->layoutSize(), layout2->layoutSize());
    QCOMPARE(layout1->layoutSize(), layout3->layoutSize());

    QCOMPARE(layout1->availableSize(), layout2->availableSize());
    QCOMPARE(layout1->availableSize(), layout3->availableSize());

    // Now show 1 widget in m1 and m3
    docks1.at(0).createdDock->open();
    m3->addDockWidget(docks2.at(0).createdDock, Location_OnBottom); // just steal from m2

    QCOMPARE(layout1->layoutSize(), layout3->layoutSize());

    Core::Group *f10 = docks1.at(0).createdDock->dptr()->group();
    Item *item10 = layout1->itemForGroup(f10);
    Item *item30 = layout3->itemForGroup(docks2.at(0).createdDock->dptr()->group());

    QCOMPARE(item10->geometry(), item30->geometry());
    QCOMPARE(item10->guest()->minSize(), item10->guest()->minSize());
    QCOMPARE(item10->minSize(), item30->minSize());
    QCOMPARE(layout1->availableSize(), layout3->availableSize());

    layout1->checkSanity();
    layout2->checkSanity();
    layout3->checkSanity();

    // Cleanup
    docks1.at(0).createdDock->destroyLater();
    docks1.at(1).createdDock->destroyLater();
    docks1.at(2).createdDock->destroyLater();
    docks2.at(0).createdDock->destroyLater();
    docks2.at(1).createdDock->destroyLater();
    docks2.at(2).createdDock->destroyLater();
    QVERIFY(WAIT_FOR_DELETED(docks2.at(2).createdDock));
}

void TestDocks::tst_anchorFollowingItselfAssert()
{
    // 1. Tests that we don't assert in Anchor::setFollowee()
    //  ASSERT: "this != m_followee" in file ../src/layouting/Anchor.cpp
    EnsureTopLevelsDeleted e;
    std::vector<DockDescriptor> docks = {
        { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnTop, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible }
    };

    auto m = createMainWindow(docks);
    auto dropArea = m->dropArea();
    Core::DropArea *layout = dropArea;
    layout->checkSanity();

    auto dock1 = docks.at(1).createdDock;
    auto dock2 = docks.at(2).createdDock;
    dock2->setFloating(true);
    auto fw2 = dock2->floatingWindow();
    dropArea->addWidget(fw2->dropArea()->view(), Location_OnLeft, dock1->dptr()->group()->layoutItem());
    dock2->setFloating(true);
    fw2 = dock2->floatingWindow();
    dropArea->addWidget(fw2->dropArea()->view(), Location_OnRight, dock1->dptr()->group()->layoutItem());

    docks.at(0).createdDock->destroyLater();
    docks.at(4).createdDock->destroyLater();
    WAIT_FOR_DELETED(docks.at(4).createdDock);
}

void TestDocks::tst_moreTitleBarCornerCases()
{
    {
        EnsureTopLevelsDeleted e;
        auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
        auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));
        dock1->open();
        dock2->open();
        auto fw2 = dock2->window();
        dock1->addDockWidgetToContainingWindow(dock2, Location_OnLeft);
        QVERIFY(dock1->dptr()->group()->titleBar()->isVisible());
        QVERIFY(dock2->dptr()->group()->titleBar()->isVisible());
        QVERIFY(dock1->dptr()->group()->titleBar() != dock2->dptr()->group()->titleBar());
        auto fw = dock1->floatingWindow();
        QVERIFY(fw->titleBar()->isVisible());
        QVERIFY(fw->titleBar() != dock1->dptr()->group()->titleBar());
        QVERIFY(fw->titleBar() != dock2->dptr()->group()->titleBar());
    }

    {
        EnsureTopLevelsDeleted e;
        auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
        auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));
        dock1->open();
        dock2->open();
        auto fw1 = dock1->floatingWindow();
        auto fw2 = dock2->floatingWindow();
        fw1->dropArea()->drop(fw2->view(), Location_OnRight, nullptr);
        QVERIFY(fw1->titleBar()->isVisible());
        QVERIFY(dock1->dptr()->group()->titleBar()->isVisible());
        QVERIFY(dock2->dptr()->group()->titleBar()->isVisible());
        QVERIFY(dock1->dptr()->group()->titleBar() != dock2->dptr()->group()->titleBar());
        QVERIFY(fw1->titleBar() != dock1->dptr()->group()->titleBar());
        QVERIFY(fw1->titleBar() != dock2->dptr()->group()->titleBar());
    }

    {
        // Tests that restoring a single floating dock widget doesn't make it show two title-bars
        // As reproduced myself... and fixed in this commit

        EnsureTopLevelsDeleted e;
        auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
        dock1->open();

        auto fw1 = dock1->floatingWindow();
        QVERIFY(!dock1->dptr()->group()->titleBar()->isVisible());
        QVERIFY(fw1->titleBar()->isVisible());

        LayoutSaver saver;
        const QByteArray saved = saver.serializeLayout();
        saver.restoreLayout(saved);

        delete fw1; // the old window

        fw1 = dock1->floatingWindow();
        QVERIFY(fw1);
        QVERIFY(fw1->isVisible());
        QVERIFY(dock1->isVisible());
        QVERIFY(!dock1->dptr()->group()->titleBar()->isVisible());
        QVERIFY(fw1->titleBar()->isVisible());
    }
}

void TestDocks::tst_isInMainWindow()
{
    EnsureTopLevelsDeleted e;
    auto dw = newDockWidget(QStringLiteral("FOO"));
    dw->open();
    auto fw = dw->window();
    QVERIFY(!dw->isInMainWindow());
    auto m1 = createMainWindow(Size(2560, 809), MainWindowOption_None, "MainWindow1");
    m1->addDockWidget(dw, KDDockWidgets::Location_OnLeft);
    QVERIFY(dw->isInMainWindow());

    // Also test after creating the MainWindow, as the FloatingWindow will get parented to it
    auto dw2 = newDockWidget(QStringLiteral("2"));
    dw2->open();
    QVERIFY(!dw2->isInMainWindow());
}

void TestDocks::tst_sizeConstraintWarning()
{
    // Tests that we don't get the warning: MultiSplitterLayout::checkSanity: Widget has height= 122
    // but minimum is 144 KDDockWidgets::Item Code autogenerated by the fuzzer:
    EnsureTopLevelsDeleted e;
    SetExpectedWarning sew("Dock widget was already opened, can't be used with InitialVisibilityOption::StartHidden");

    auto window = createMainWindow();
    std::vector<Core::DockWidget *> listDockWidget;
    {
        auto dock = newDockWidget("foo-0");
        dock->setGuestView(Platform::instance()->tests_createFocusableView({ true })->asWrapper());
        listDockWidget.push_back(dock);
    }
    {
        auto dock = newDockWidget("foo-1");
        dock->setGuestView(Platform::instance()->tests_createFocusableView({ true })->asWrapper());
        listDockWidget.push_back(dock);
    }
    {
        auto dock = newDockWidget("foo-2");
        dock->setGuestView(Platform::instance()->tests_createFocusableView({ true })->asWrapper());
        listDockWidget.push_back(dock);
    }
    {
        auto dock = newDockWidget("foo-3");
        dock->setGuestView(Platform::instance()->tests_createFocusableView({ true })->asWrapper());
        listDockWidget.push_back(dock);
    }
    {
        auto dock = newDockWidget("foo-4");
        dock->setGuestView(Platform::instance()->tests_createFocusableView({ true })->asWrapper());
        listDockWidget.push_back(dock);
    }
    {
        auto dock = newDockWidget("foo-5");
        dock->setGuestView(Platform::instance()->tests_createFocusableView({ true })->asWrapper());
        listDockWidget.push_back(dock);
    }
    {
        auto dock = newDockWidget("foo-6");
        dock->setGuestView(Platform::instance()->tests_createFocusableView({ true })->asWrapper());
        listDockWidget.push_back(dock);
    }
    {
        auto dock = newDockWidget("foo-7");
        dock->setGuestView(Platform::instance()->tests_createFocusableView({ true })->asWrapper());
        listDockWidget.push_back(dock);
    }
    {
        auto dock = newDockWidget("foo-8");
        dock->setGuestView(Platform::instance()->tests_createFocusableView({ true })->asWrapper());
        listDockWidget.push_back(dock);
    }
    {
        auto dock = newDockWidget("foo-9");
        dock->setGuestView(Platform::instance()->tests_createFocusableView({ true })->asWrapper());
        listDockWidget.push_back(dock);
    }
    {
        auto dock = newDockWidget("foo-10");
        dock->setGuestView(Platform::instance()->tests_createFocusableView({ true })->asWrapper());
        listDockWidget.push_back(dock);
    }
    {
        auto dock = newDockWidget("foo-11");
        dock->setGuestView(Platform::instance()->tests_createFocusableView({ true })->asWrapper());
        listDockWidget.push_back(dock);
    }
    {
        auto dock = newDockWidget("foo-12");
        dock->setGuestView(Platform::instance()->tests_createFocusableView({ true })->asWrapper());
        listDockWidget.push_back(dock);
    }
    {
        auto dock = newDockWidget("foo-13");
        dock->setGuestView(Platform::instance()->tests_createFocusableView({ true })->asWrapper());
        listDockWidget.push_back(dock);
    }
    {
        auto dock = newDockWidget("foo-14");
        dock->setGuestView(Platform::instance()->tests_createFocusableView({ true })->asWrapper());
        listDockWidget.push_back(dock);
    }
    {
        auto dock = newDockWidget("foo-15");
        dock->setGuestView(Platform::instance()->tests_createFocusableView({ true })->asWrapper());
        listDockWidget.push_back(dock);
    }
    {
        auto dock = newDockWidget("foo-16");
        dock->setGuestView(Platform::instance()->tests_createFocusableView({ true })->asWrapper());
        listDockWidget.push_back(dock);
    }
    {
        auto dock = newDockWidget("foo-17");
        dock->setGuestView(Platform::instance()->tests_createFocusableView({ true })->asWrapper());
        listDockWidget.push_back(dock);
    }
    {
        auto dock = newDockWidget("foo-18");
        dock->setGuestView(Platform::instance()->tests_createFocusableView({ true })->asWrapper());
        listDockWidget.push_back(dock);
    }

    auto dropArea = window->dropArea();
    window->addDockWidget(listDockWidget.at(0), static_cast<Location>(2));
    dropArea->checkSanity();

    window->addDockWidget(listDockWidget.at(1), static_cast<Location>(1));
    dropArea->checkSanity();

    listDockWidget.at(2 - 1)->addDockWidgetAsTab(listDockWidget.at(2));
    dropArea->checkSanity();

    window->addDockWidget(listDockWidget.at(3 - 1), static_cast<Location>(2), listDockWidget.at(3),
                          static_cast<InitialVisibilityOption>(1));
    dropArea->checkSanity();

    listDockWidget.at(4 - 1)->addDockWidgetAsTab(listDockWidget.at(4));
    dropArea->checkSanity();

    window->addDockWidget(listDockWidget.at(5), static_cast<Location>(1));
    dropArea->checkSanity();

    window->addDockWidget(listDockWidget.at(6), static_cast<Location>(1));
    dropArea->checkSanity();

    window->addDockWidget(listDockWidget.at(7), static_cast<Location>(4));
    dropArea->checkSanity();

    window->addDockWidget(listDockWidget.at(8 - 1), static_cast<Location>(1), listDockWidget.at(8),
                          static_cast<InitialVisibilityOption>(1));
    dropArea->checkSanity();

    window->addDockWidget(listDockWidget.at(9), static_cast<Location>(2));
    dropArea->checkSanity();

    window->addDockWidget(listDockWidget.at(10 - 1), static_cast<Location>(2),
                          listDockWidget.at(10), static_cast<InitialVisibilityOption>(1));
    dropArea->checkSanity();

    listDockWidget.at(11 - 1)->addDockWidgetAsTab(listDockWidget.at(11));
    dropArea->checkSanity();

    listDockWidget.at(12 - 1)->addDockWidgetAsTab(listDockWidget.at(12));
    dropArea->checkSanity();

    window->addDockWidget(listDockWidget.at(13), static_cast<Location>(4));
    dropArea->checkSanity();

    window->addDockWidget(listDockWidget.at(14), static_cast<Location>(2));
    dropArea->checkSanity();

    window->addDockWidget(listDockWidget.at(15), static_cast<Location>(3));
    dropArea->checkSanity();

    window->addDockWidget(listDockWidget.at(16), static_cast<Location>(4));
    dropArea->checkSanity();

    listDockWidget.at(17 - 1)->addDockWidgetAsTab(listDockWidget.at(17));
    dropArea->checkSanity();
    listDockWidget.at(18 - 1)->addDockWidgetAsTab(listDockWidget.at(18));
    dropArea->checkSanity();

    auto docks = DockRegistry::self()->dockwidgets();
    auto lastDock = docks.last();
    for (auto dock : docks)
        dock->destroyLater();

    WAIT_FOR_DELETED(lastDock);
}

void TestDocks::tst_stuckSeparator()
{
    const QString absoluteLayoutFileName = resourceFileName(QStringLiteral("layouts/stuck-separator.json"));

    EnsureTopLevelsDeleted e;
    auto m1 = createMainWindow(Size(2560, 809), MainWindowOption_None, "MainWindow1");
    const int numDockWidgets = 26;
    Core::DockWidget *dw25 = nullptr;
    for (int i = 0; i < numDockWidgets; ++i) {
        auto createdDw = createDockWidget(QString("dock-") + QString::number(i));
        if (i == 25)
            dw25 = createdDw;
    }

    LayoutSaver restorer;
    QVERIFY(restorer.restoreFromFile(absoluteLayoutFileName));

    Core::Group *group25 = dw25->dptr()->group();
    ItemBoxContainer *root = m1->multiSplitter()->rootItem();
    Item *item25 = root->itemForView(group25->asLayoutingGuest());
    ItemBoxContainer *container25 = item25->parentBoxContainer();
    auto separators = container25->separators();
    QCOMPARE(separators.size(), 1);

    auto separator25 = separators.constFirst();
    const int sepMin = container25->minPosForSeparator_global(separator25);
    const int sepMax = container25->maxPosForSeparator_global(separator25);

    QVERIFY(sepMin <= sepMax);

    for (auto dw : DockRegistry::self()->dockwidgets()) {
        delete dw;
    }
}

void TestDocks::tst_titlebar_getter()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(1000, 1000), MainWindowOption_HasCentralGroup);
    m->view()->resize(Size(500, 500));
    m->show();

    auto w1 = Platform::instance()->tests_createView({ true, {}, Size(400, 400) });
    auto d1 = createDockWidget("1", w1);

    m->addDockWidget(d1, Location_OnTop);

    QVERIFY(d1->titleBar()->isVisible());
    d1->setFloating(true);
    QVERIFY(d1->floatingWindow());
    QVERIFY(d1->floatingWindow()->isVisible());
    QVERIFY(d1->titleBar()->isVisible());
}

void TestDocks::tst_dockNotFillingSpace()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(1000, 1000));
    m->view()->resize(Size(500, 500));
    m->show();

    auto d1 = createDockWidget("1", Platform::instance()->tests_createFocusableView({ true }));
    auto d2 = createDockWidget("2", Platform::instance()->tests_createFocusableView({ true }));
    auto d3 = createDockWidget("3", Platform::instance()->tests_createFocusableView({ true }));

    m->addDockWidget(d1, Location_OnTop);
    m->addDockWidget(d2, Location_OnBottom);
    m->addDockWidget(d3, Location_OnBottom);

    Core::Group *group2 = d2->dptr()->group();
    d1->close();
    d2->close();
    WAIT_FOR_DELETED(group2);

    auto layout = m->multiSplitter();
    QVERIFY(layout->checkSanity());

    delete d1;
    delete d2;
}

void TestDocks::tst_lastFloatingPositionIsRestored()
{
    EnsureTopLevelsDeleted e;

    auto m1 = createMainWindow();
    auto dock1 = createDockWidget("dock1");
    dock1->open();
    Point targetPos = Point(340, 340);
    dock1->window()->window()->setFramePosition(targetPos);
    QCOMPARE(dock1->window()->window()->frameGeometry().topLeft(), targetPos);
    auto oldFw = dock1->window();
    WAIT_FOR_EVENT(dock1->window().get(), Event::Move);

    LayoutSaver saver;
    QByteArray saved = saver.serializeLayout();

    dock1->window()->move(0, 0);
    dock1->close();

    saver.restoreLayout(saved);
    QCOMPARE(dock1->window()->window()->frameGeometry().topLeft(), targetPos);

    // Adjust to what we got without the group
    targetPos = dock1->window()->geometry().topLeft();

    // Now dock it:
    m1->addDockWidget(dock1, Location_OnTop);
    QCOMPARE(dock1->dptr()->lastPosition()->lastFloatingGeometry().topLeft(), targetPos);

    dock1->setFloating(true);
    QCOMPARE(dock1->window()->geometry().topLeft(), targetPos);

    saver.restoreLayout(saved);
    QCOMPARE(dock1->window()->geometry().topLeft(), targetPos);

    // Dock again and save:
    m1->addDockWidget(dock1, Location_OnTop);
    saved = saver.serializeLayout();
    dock1->setFloating(true);
    dock1->window()->move(0, 0);
    saver.restoreLayout(saved);
    QVERIFY(!dock1->isFloating());
    dock1->setFloating(true);
    QCOMPARE(dock1->window()->geometry().topLeft(), targetPos);
}

void TestDocks::tst_titleBarFocusedWhenTabsChange()
{
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_TitleBarIsFocusable);

    auto le1 = Platform::instance()->tests_createFocusableView({ true });
    le1->setViewName("le1");
    auto dock1 = createDockWidget(QStringLiteral("dock1"), le1);
    auto dock2 = createDockWidget(QStringLiteral("dock2"),
                                  Platform::instance()->tests_createFocusableView({ true }));
    auto dock3 = createDockWidget(QStringLiteral("dock3"),
                                  Platform::instance()->tests_createFocusableView({ true }));
    auto oldFw1 = dock1->window();
    auto oldFw2 = dock2->window();
    auto oldFw3 = dock3->window();

    auto m1 = createMainWindow(Size(2560, 809), MainWindowOption_None, "MainWindow1");

    m1->addDockWidget(dock1, Location_OnLeft);
    m1->addDockWidget(dock2, Location_OnRight);
    dock2->addDockWidgetAsTab(dock3);

    Core::TitleBar *titleBar1 = dock1->titleBar();
    dock1->guestView()->setFocus(Qt::MouseFocusReason);

    QVERIFY(dock1->isFocused()
            || (WAIT_FOR_EVENT(dock1->guestView().get(), Event::FocusIn)));
    QVERIFY(titleBar1->isFocused());

    auto group2 = dock2->dptr()->group();

    Core::TabBar *tb2 = group2->tabBar();
    QCOMPARE(tb2->currentIndex(), 1); // Was the last to be added

    const Rect rect0 = tb2->rectForTab(0);
    const Point globalPos = tb2->view()->mapToGlobal(rect0.topLeft()) + Point(5, 5);
    Tests::clickOn(globalPos, tb2->view());

    QVERIFY(!titleBar1->isFocused());
    QVERIFY(dock2->titleBar()->isFocused());

    // Test that clicking on a tab that is already current will also set focus
    dock1->view()->setFocus(Qt::MouseFocusReason);
    QVERIFY(dock1->titleBar()->isFocused());
    QVERIFY(!dock2->titleBar()->isFocused());

    if (Platform::instance()->isQtWidgets()) {
        // Not yet ready for QtQuick. The TitleBar.qml is clicked, but we check the C++
        // TitleBar for focus
        Tests::clickOn(globalPos, tb2->view());
        QVERIFY(!dock1->titleBar()->isFocused());
        QVERIFY(dock2->titleBar()->isFocused());
    }
}

void TestDocks::tst_floatingAction()
{
    // Tests DockWidget::floatAction()

    {
        EnsureTopLevelsDeleted e;
        // 1. Create a MainWindow with two docked dock-widgets, then float the first one.
        auto m = createMainWindow();
        auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
        auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));
        m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
        m->addDockWidget(dock2, KDDockWidgets::Location_OnRight);

        auto action = dock1->floatAction();
        QVERIFY(!dock1->isFloating());
        QVERIFY(!action->isChecked());
        QVERIFY(action->isEnabled());
        QCOMPARE(action->toolTip(), Object::tr("Detach"));

        action->toggle();

        QVERIFY(dock1->isFloating());
        QVERIFY(action->isChecked());
        QVERIFY(action->isEnabled());
        QCOMPARE(action->toolTip(), Object::tr("Dock"));

        auto fw = dock1->floatingWindow();
        QVERIFY(fw);

        // 2. Put it back, via setFloating(). It should return to its place.
        action->toggle();

        QVERIFY(!dock1->isFloating());
        QVERIFY(!action->isChecked());
        QVERIFY(action->isEnabled());
        QVERIFY(!dock1->isTabbed());
        QCOMPARE(action->toolTip(), Object::tr("Detach"));

        WAIT_FOR_DELETED(fw);
    }

    {
        EnsureTopLevelsDeleted e;
        // 1. Create a MainWindow with one docked dock-widgets, and one floating.
        auto m = createMainWindow();
        auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
        auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));
        m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);

        // The floating window action should be disabled as it has no previous place
        auto action = dock2->floatAction();
        QVERIFY(dock2->isFloating());
        QVERIFY(action->isChecked());
        QVERIFY(!action->isEnabled());
        QCOMPARE(action->toolTip(), Object::tr("Dock"));

        m->addDockWidget(dock2, KDDockWidgets::Location_OnRight);

        QVERIFY(!dock2->isFloating());
        QVERIFY(!action->isChecked());
        QVERIFY(action->isEnabled());
        QCOMPARE(action->toolTip(), Object::tr("Detach"));

        action->toggle();
        QVERIFY(dock2->isFloating());
        QVERIFY(action->isChecked());
        QVERIFY(action->isEnabled());
        QCOMPARE(action->toolTip(), Object::tr("Dock"));

        auto fw = dock2->floatingWindow();
        QVERIFY(fw);

        // 2. Put it back, via setFloating(). It should return to its place.
        action->toggle();

        QVERIFY(!dock1->isFloating());
        QVERIFY(!action->isChecked());
        QVERIFY(action->isEnabled());
        QVERIFY(!dock1->isTabbed());
        QCOMPARE(action->toolTip(), Object::tr("Detach"));

        WAIT_FOR_DELETED(fw);
    }
    {
        EnsureTopLevelsDeleted e;
        // 3. A floating window with two tabs
        auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
        auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));

        bool dock1IsFloating = dock1->floatAction()->isChecked();
        bool dock2IsFloating = dock2->floatAction()->isChecked();

        KDBindings::ScopedConnection conn1 = dock1->floatAction()->d->toggled.connect([&dock1IsFloating](bool t) {
            assert(dock1IsFloating != t);
            dock1IsFloating = t;
        });

        KDBindings::ScopedConnection conn2 = dock2->floatAction()->d->toggled.connect([&dock2IsFloating](bool t) {
            assert(dock2IsFloating != t);
            dock2IsFloating = t;
        });

        auto fw2 = dock2->floatingWindow();
        QVERIFY(dock1->isFloating());
        QVERIFY(dock2->isFloating());
        QVERIFY(dock1->floatAction()->isChecked());
        QVERIFY(dock2->floatAction()->isChecked());

        dock1->addDockWidgetAsTab(dock2);
        QVERIFY(!dock1->isFloating());
        QVERIFY(!dock2->isFloating());
        QVERIFY(!dock1->floatAction()->isChecked());
        QVERIFY(!dock2->floatAction()->isChecked());

        dock2->setFloating(true);

        QVERIFY(dock1->isFloating());
        QVERIFY(dock1->floatAction()->isChecked());
        QVERIFY(dock2->isFloating());
        QVERIFY(dock2->floatAction()->isChecked());

        QVERIFY(dock1IsFloating);
        QVERIFY(dock2IsFloating);

        delete fw2;
    }

    {
        EnsureTopLevelsDeleted e;
        // If the dock widget is alone then it's floating, but we suddenly dock a widget
        // side-by-side to it, then both aren't floating anymore. This test tests if the signal was
        // emitted

        auto dock1 = createDockWidget("one", Platform::instance()->tests_createView({ true }));
        auto dock2 = createDockWidget("two", Platform::instance()->tests_createView({ true }));

        QVERIFY(dock1->isFloating());
        QVERIFY(dock2->isFloating());
        QVERIFY(dock1->floatAction()->isChecked());
        QVERIFY(dock2->floatAction()->isChecked());
        auto oldFw2 = dock2->window();

        int floatActionCount1 = 0;
        int floatActionCount2 = 0;
        int floatingChangedCount1 = 0;
        int floatingChangedCount2 = 0;

        KDBindings::ScopedConnection conn1 = dock1->floatAction()->d->toggled.connect([&floatActionCount1] {
            floatActionCount1++;
        });

        KDBindings::ScopedConnection conn2 = dock2->floatAction()->d->toggled.connect([&floatActionCount2] {
            floatActionCount2++;
        });

        dock1->d->isFloatingChanged.connect([&floatingChangedCount1] {
            floatingChangedCount1++;
        });

        dock2->d->isFloatingChanged.connect([&floatingChangedCount2] {
            floatingChangedCount2++;
        });

        dock1->addDockWidgetToContainingWindow(dock2, Location_OnRight);

        QCOMPARE(floatActionCount1, 1);
        QCOMPARE(floatActionCount2, 1);
        QCOMPARE(floatingChangedCount1, 1);
        QCOMPARE(floatingChangedCount2, 1);

        QVERIFY(!dock1->isFloating());
        QVERIFY(!dock2->isFloating());

        QVERIFY(!dock2->floatAction()->isChecked());
        QVERIFY(!dock1->floatAction()->isChecked());
    }

    {
        EnsureTopLevelsDeleted e;
        // Like before, but now we use addMultiSplitter()

        auto dock1 = createDockWidget("one", Platform::instance()->tests_createView({ true }));
        auto dock2 = createDockWidget("two", Platform::instance()->tests_createView({ true }));

        QVERIFY(dock1->isFloating());
        QVERIFY(dock2->isFloating());
        QVERIFY(dock1->floatAction()->isChecked());
        QVERIFY(dock2->floatAction()->isChecked());
        auto oldFw2 = dock2->floatingWindow();

        int floatingChangedCount1 = 0;
        int floatingChangedCount2 = 0;

        dock1->d->isFloatingChanged.connect([&floatingChangedCount1] {
            floatingChangedCount1++;
        });

        dock2->d->isFloatingChanged.connect([&floatingChangedCount2] {
            floatingChangedCount2++;
        });

        auto dropArea1 = dock1->floatingWindow()->dropArea();
        dropArea1->drop(oldFw2->view(), Location_OnRight, nullptr);

        QCOMPARE(floatingChangedCount1, 1);
        QCOMPARE(floatingChangedCount2, 1);

        QVERIFY(!dock1->isFloating());
        QVERIFY(!dock2->isFloating());
        QVERIFY(!dock2->floatAction()->isChecked());
        QVERIFY(!dock1->floatAction()->isChecked());

        // Let's now remove dock1, dock2 should be floating
        dock1->setFloating(true);
        QVERIFY(dock1->isFloating());
        QVERIFY(dock2->isFloating());
        QVERIFY(dock2->floatAction()->isChecked());
        QVERIFY(dock1->floatAction()->isChecked());
    }

    {
        EnsureTopLevelsDeleted e;
        // Same test as before, but now tab instead of side-by-side
        auto dock1 = createDockWidget("one", Platform::instance()->tests_createView({ true }));
        auto dock2 = createDockWidget("two", Platform::instance()->tests_createView({ true }));

        QVERIFY(dock1->isFloating());
        QVERIFY(dock2->isFloating());
        QVERIFY(dock1->floatAction()->isChecked());
        QVERIFY(dock2->floatAction()->isChecked());
        auto oldFw2 = dock2->window();

        int floatingChangedCount1 = 0;
        int floatingChangedCount2 = 0;

        dock1->d->isFloatingChanged.connect([&floatingChangedCount1] {
            floatingChangedCount1++;
        });

        dock2->d->isFloatingChanged.connect([&floatingChangedCount2] {
            floatingChangedCount2++;
        });

        dock1->addDockWidgetAsTab(dock2);

        QCOMPARE(floatingChangedCount1, 1);

        // On earlier Qt versions this is flaky, but technically correct.
        // Windows can get hidden while being reparented and floating changes momentarily.
        QVERIFY(floatingChangedCount2 == 1 || floatingChangedCount2 == 3);
        QCOMPARE(floatingChangedCount1, 1);

        QVERIFY(!dock1->isFloating());
        QVERIFY(!dock2->isFloating());

        QVERIFY(!dock2->floatAction()->isChecked());
        QVERIFY(!dock1->floatAction()->isChecked());
    }

    {
        EnsureTopLevelsDeleted e;

        // Here we test:
        // - main window with 1 docked widgets, and a dockwidget2 that's floating
        // - tab dock1 into dockwidget2 (they are tabbed now)
        // - toggle the float action of dockwidget1
        auto m = createMainWindow();
        auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
        auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));

        m->addDockWidget(dock1, Location_OnLeft);
        dock2->show();

        dock2->addDockWidgetAsTab(dock1);

        QVERIFY(!dock1->isFloating());
        QVERIFY(!dock2->isFloating());

        {
            SetExpectedWarning sew("Got exception in signal");
            dock1->floatAction()->toggle();
        }

        QVERIFY(dock1->isFloating());
        QVERIFY(dock2->isFloating());
    }
}

void TestDocks::tst_raise()
{
    // Tests DockWidget::raise();
    EnsureTopLevelsDeleted e;

    auto dock1 = createDockWidget("1");
    auto dock2 = createDockWidget("2");

    dock1->addDockWidgetAsTab(dock2);
    dock1->setAsCurrentTab();
    QVERIFY(dock1->isCurrentTab());
    QVERIFY(!dock2->isCurrentTab());
    dock2->raise();
    QVERIFY(!dock1->isCurrentTab());
    QVERIFY(dock2->isCurrentTab());
}

void TestDocks::tst_dontCloseDockWidgetBeforeRestore()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }), {},
                                  LayoutSaverOption::Skip);
    auto dock3 = createDockWidget("dock3", Platform::instance()->tests_createView({ true }), {},
                                  LayoutSaverOption::Skip);
    auto dock4 = createDockWidget("4", Platform::instance()->tests_createView({ true }), {}, {},
                                  /*show=*/false);

    m->addDockWidget(dock1, Location_OnBottom);
    m->addDockWidget(dock2, Location_OnBottom);

    // Dock #3 floats, while #1 and #2 are docked.
    dock3->setFloating(true);
    QVERIFY(dock3->isOpen());
    QVERIFY(dock3->isFloating());
    QVERIFY(!dock3->isInMainWindow());

    LayoutSaver saver;
    const QByteArray saved = saver.serializeLayout();
    dock3->close();

    // Not open anymore
    QVERIFY(!dock3->isOpen());

    QVERIFY(saver.restoreLayout(saved));

    // #3 is still closed, the restore will skip it
    QVERIFY(!dock3->isOpen());
    QVERIFY(!dock3->isInMainWindow());

    auto dock5 = createDockWidget("5", Platform::instance()->tests_createView({ true }), {},
                                  LayoutSaverOption::Skip);

    dock4->open();
    dock5->open();

    QVERIFY(saver.restoreLayout(saved));
    QVERIFY(!dock4->isOpen());
    QVERIFY(dock5->isOpen()); // #5 is still open, it ignored restore
}

void TestDocks::tst_dontCloseDockWidgetBeforeRestore2()
{
    // In this case we have a floating window with two dock widgets tabbed, both having
    // LayoutSaverOption::Skip Meaning the whole window should be skipped

    EnsureTopLevelsDeleted e;
    auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }), {},
                                  LayoutSaverOption::Skip);
    auto dock3 = createDockWidget("dock3", Platform::instance()->tests_createView({ true }), {},
                                  LayoutSaverOption::Skip);

    dock2->close();
    dock3->close();

    LayoutSaver saver;
    const QByteArray saved = saver.serializeLayout(); // This layout has 0 docks visible

    dock2->open();
    dock3->open();
    QVERIFY(saver.restoreLayout(saved));
    QVERIFY(dock2->isVisible()); // They're still visible
    QVERIFY(dock3->isVisible());

    // Now tab and restore again
    dock2->addDockWidgetAsTab(dock3);
    QVERIFY(saver.restoreLayout(saved));
    QVERIFY(dock2->isOpen());
    QVERIFY(dock3->isOpen());
    QVERIFY(dock3->isVisible());
    QCOMPARE(dock3->dptr()->group(), dock2->dptr()->group());

    LayoutSaver::Layout layout;
    layout.fromJson(saved);
    QVERIFY(layout.closedDockWidgets.isEmpty());
    QVERIFY(layout.floatingWindows.isEmpty());
}

void TestDocks::tst_dontCloseDockWidgetBeforeRestore3()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }), {},
                                  LayoutSaverOption::Skip);
    dock1->close();
    dock2->close();

    LayoutSaver saver;
    const QByteArray saved = saver.serializeLayout(); // This layout has 0 docks visible

    m->addDockWidget(dock1, Location_OnBottom);
    m->addDockWidget(dock2, Location_OnBottom);

    QVERIFY(saver.restoreLayout(saved));

    QVERIFY(!dock1->isOpen()); // Gets closed by the restore
    QVERIFY(dock2->isOpen()); // Dock2 remains open, it ignores restore
    QVERIFY(dock2->isFloating());
}

void TestDocks::tst_dontCloseDockWidgetBeforeRestore4()
{
    // Tests a case where the dock widget would get an invalid size.
    // Widgets which skip layout restore were be skipping LayoutSaver::onResize()

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow({ 1000, 1000 }, {});
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }), {},
                                  LayoutSaverOption::Skip);

    m->addDockWidget(dock1, Location_OnBottom);
    m->addDockWidget(dock2, Location_OnBottom);

    QTest::qWait(100);
    dock1->close();
    dock2->close();

    LayoutSaver saver;
    const QByteArray saved = saver.serializeLayout();

    QTest::qWait(100);
    dock2->open();

    QVERIFY(saver.restoreLayout(saved));
    QVERIFY(dock2->isOpen());

    QTest::qWait(100);
    Core::FloatingWindow *fw = dock2->floatingWindow();
    DropArea *da = fw->dropArea();
    QVERIFY(da->checkSanity());
    QCOMPARE(da->layoutSize(), da->rootItem()->size());
    QVERIFY(std::abs(fw->width() - da->layoutWidth()) < 30);
}

void TestDocks::tst_skipRestoreInsideMainWindow()
{
    // Tests that a docked widget doesn't get redocked when restoring if it has LayoutSaverOption::Skip
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow({ 1000, 1000 }, {});
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }), {},
                                  LayoutSaverOption::Skip);
    m->addDockWidget(dock1, Location_OnBottom);

    LayoutSaver saver;
    const QByteArray saved = saver.serializeLayout();

    dock1->close();
    QVERIFY(!dock1->isOpen());
    saver.restoreLayout(saved);
    QVERIFY(!dock1->isOpen());
}

void TestDocks::tst_closeOnlyCurrentTab()
{
    {
        // Case of a floating window with tabs
        EnsureTopLevelsDeleted e;
        KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_CloseOnlyCurrentTab);

        auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
        auto dock2 = createDockWidget("2", Platform::instance()->tests_createView({ true }));
        auto dock3 = createDockWidget("3", Platform::instance()->tests_createView({ true }));

        /// Floating window with 3 tabs
        dock1->addDockWidgetAsTab(dock2);
        dock1->addDockWidgetAsTab(dock3);

        Core::TitleBar *tb = dock1->titleBar();
        QVERIFY(tb->isVisible());
        dock1->setAsCurrentTab();
        Core::Group *group = dock1->dptr()->group();
        QCOMPARE(group->currentIndex(), 0);

        tb->onCloseClicked();

        QVERIFY(!dock1->isOpen());
        QVERIFY(dock2->isOpen());
        QVERIFY(dock3->isOpen());
    }

    {
        // Case of a floating window with tabs
        EnsureTopLevelsDeleted e;
        KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_CloseOnlyCurrentTab);

        auto m = createMainWindow();
        auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
        auto dock2 = createDockWidget("2", Platform::instance()->tests_createView({ true }));
        auto dock3 = createDockWidget("3", Platform::instance()->tests_createView({ true }));

        m->addDockWidget(dock1, Location_OnLeft);
        m->addDockWidget(dock2, Location_OnRight);

        dock2->addDockWidgetAsTab(dock3);
        Core::Group *group = dock2->dptr()->group();
        QCOMPARE(group->currentIndex(), 1);
        Core::TitleBar *tb = group->titleBar();
        QVERIFY(tb->isVisible());
        tb->onCloseClicked();

        QVERIFY(!dock3->isOpen());
        QVERIFY(dock2->isOpen());
        QVERIFY(dock1->isOpen());
        QCOMPARE(group->dockWidgetCount(), 1);
    }
}

void TestDocks::tst_tabWidgetCurrentIndex()
{
    EnsureTopLevelsDeleted e;

    auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("2", Platform::instance()->tests_createView({ true }));
    auto dock3 = createDockWidget("3", Platform::instance()->tests_createView({ true }));
    auto fw2 = dock2->window();
    auto fw3 = dock3->window();

    Core::DockWidget *currentDw = nullptr;
    auto group = dock1->dptr()->group();
    group->tabBar()->dptr()->currentDockWidgetChanged.connect([&currentDw](Core::DockWidget *dw) { currentDw = dw; });

    QCOMPARE(group->tabBar()->currentIndex(), 0);
    dock1->addDockWidgetAsTab(dock2);

    QCOMPARE(group->tabBar()->currentIndex(), 1);
    QCOMPARE(group->currentDockWidget(), currentDw);
    QCOMPARE(dock2, currentDw);

    dock2->close();

    QCOMPARE(group->tabBar()->currentIndex(), 0);
    QCOMPARE(dock1, currentDw);
}

void TestDocks::tst_doubleClickTabBarRestore()
{
    if (!Platform::instance()->isQtWidgets()) {
        // Only implemented for QtWidgets.
        // for QtQuick the tabs take the full width and there's no empty "tab widget" background
        // so solution will have to be different. To be done once it's requested.
        return;
    }

    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_HideTitleBarWhenTabsVisible | KDDockWidgets::Config::Flag_AlwaysShowTabs);

    auto m = createMainWindow(Size(501, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
    m->addDockWidget(dock1, Location_OnTop);
    QVERIFY(!dock1->isFloating());

    auto group = dock1->dptr()->group();
    auto tabWidget = group->stack()->view();

    Tests::doubleClickOn(tabWidget->mapToGlobal(Point(20, 20)), group->view()->window());
    QVERIFY(dock1->isFloating());

    group = dock1->dptr()->group();
    tabWidget = group->stack()->view();

    // click on the end of the tabWidget so we don't hit a tab
    Tests::doubleClickOn(tabWidget->mapToGlobal(Point(tabWidget->width() - 50, 20)), group->view()->window());
    QVERIFY(!dock1->isFloating());
    QVERIFY(dock1->isInMainWindow());
}

void TestDocks::tst_doubleClickTabRestore()
{
    // Like tst_doubleClickTabBarRestore but we click on the tab itself

    if (!Platform::instance()->isQtWidgets()) {
        // Only implemented for QtWidgets.
        // for QtQuick the tabs take the full width and there's no empty "tab widget" background
        // so solution will have to be different. To be done once it's requested.
        return;
    }

    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_HideTitleBarWhenTabsVisible | KDDockWidgets::Config::Flag_AlwaysShowTabs);

    auto m = createMainWindow(Size(501, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
    m->addDockWidget(dock1, Location_OnTop);
    QVERIFY(!dock1->isFloating());

    auto group = dock1->dptr()->group();
    auto tabWidget = group->stack()->view();

    Tests::doubleClickOn(tabWidget->mapToGlobal(Point(20, 20)), group->view()->window());
    QVERIFY(dock1->isFloating());

    group = dock1->dptr()->group();
    tabWidget = group->stack()->view();

    // click on the end of the tabWidget so we don't hit a tab
    Tests::doubleClickOn(tabWidget->mapToGlobal(Point(20, 20)), group->view()->window());
    QVERIFY(!dock1->isFloating());
    QVERIFY(dock1->isInMainWindow());
}


void TestDocks::tst_doubleClickTabToDetach()
{
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    // Platform::instance()->tests_doubleClickOn(QWindow) doesn't work anymore on Qt6
    // which refactored mouse delivery.
    return;
#endif

    EnsureTopLevelsDeleted e;

    auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("2", Platform::instance()->tests_createView({ true }));

    auto fw2 = dock2->window();

    dock1->addDockWidgetAsTab(dock2);

    auto group = dock1->dptr()->group();
    QCOMPARE(group->currentIndex(), 1);

    auto tb = group->stack()->view();
    Tests::doubleClickOn(tb->mapToGlobal(Point(20, 20)), group->view()->window());

    QVERIFY(dock1->isFloating());
    QVERIFY(dock2->isFloating());
    QVERIFY(dock1->floatingWindow() != dock2->floatingWindow());
}

void TestDocks::tst_addingOptionHiddenTabbed()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(501, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("2", Platform::instance()->tests_createView({ true }));
    m->addDockWidget(dock1, Location_OnTop);

    QCOMPARE(dock1->dptr()->group()->dockWidgetCount(), 1);
    dock1->addDockWidgetAsTab(dock2, InitialVisibilityOption::StartHidden);
    QCOMPARE(dock1->dptr()->group()->dockWidgetCount(), 1);
    dock2->open();
    QCOMPARE(dock1->dptr()->group()->dockWidgetCount(), 2);

    QVERIFY(dock1->dptr()->group() == dock2->dptr()->group());
}

void TestDocks::tst_flagDoubleClick()
{
    {
        EnsureTopLevelsDeleted e;
        KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_DoubleClickMaximizes);
        auto m = createMainWindow(Size(500, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
        auto dock2 = createDockWidget("2", Platform::instance()->tests_createView({ true }));
        m->addDockWidget(dock1, Location_OnTop);

        Core::FloatingWindow *fw2 = dock2->floatingWindow();
        QVERIFY(!fw2->view()->isMaximized());
        Core::TitleBar *t2 = dock2->titleBar();

        Point pos = t2->mapToGlobal(Point(5, 5));
        Platform::instance()->tests_doubleClickOn(pos, t2->view());
        QVERIFY(fw2->view()->isMaximized());
        delete fw2;

        Core::TitleBar *t1 = dock1->titleBar();
        QVERIFY(!t1->isFloating());
        pos = t1->mapToGlobal(Point(5, 5));
        Platform::instance()->tests_doubleClickOn(pos, t1->view());
        QVERIFY(t1->isFloating());
        QVERIFY(!dock1->window()->isMaximized());
    }

    {
        EnsureTopLevelsDeleted e;
        auto m = createMainWindow(Size(500, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));

        m->addDockWidget(dock1, Location_OnTop);

        Core::TitleBar *t1 = dock1->titleBar();
        QVERIFY(!t1->isFloating());
        Point pos = t1->mapToGlobal(Point(5, 5));
        Platform::instance()->tests_doubleClickOn(pos, t1->view());
        QVERIFY(t1->isFloating());
        QVERIFY(dock1->isFloating());
        QVERIFY(!dock1->window()->isMaximized());

        pos = t1->mapToGlobal(Point(5, 5));
        Platform::instance()->tests_doubleClickOn(pos, t1->view());
        QVERIFY(!dock1->isFloating());
    }
}

void TestDocks::tst_maxSizedHonouredAfterRemoved()
{
    EnsureTopLevelsDeleted e;
    auto m1 = createMainWindow(Size(1000, 1000), MainWindowOption_None);
    auto dock1 = newDockWidget("dock1");
    dock1->open();

    auto w = Platform::instance()->tests_createView({ true, {}, Size(100, 100) });
    w->setMinimumSize(Size(120, 100));
    w->setMaximumSize(Size(300, 150));
    dock1->setGuestView(w->asWrapper());
    m1->dropArea()->addMultiSplitter(dock1->floatingWindow()->multiSplitter(), Location_OnLeft);

    auto dock2 = newDockWidget("dock2");
    dock2->open();
    m1->dropArea()->addMultiSplitter(dock2->floatingWindow()->multiSplitter(), Location_OnTop);

    auto root = m1->multiSplitter()->rootItem();

    // Wait 1 event loop so we get layout invalidated and get max-size constraints
    QTest::qWait(10);

    auto sep = root->separators().constFirst();
    root->requestEqualSize(sep); // Since we're not calling honourMaxSizes() after a widget changes
                                 // its max size afterwards yet
    const int sepMin = root->minPosForSeparator_global(sep);
    const int sepMax = root->maxPosForSeparator_global(sep);

    QVERIFY(sep->position() >= sepMin);
    QVERIFY(sep->position() <= sepMax);

    auto dock3 = newDockWidget("dock3");
    dock3->open();
    m1->dropArea()->addMultiSplitter(dock3->floatingWindow()->multiSplitter(), Location_OnBottom);

    dock1->setFloating(true);
    m1->dropArea()->addMultiSplitter(dock1->floatingWindow()->multiSplitter(), Location_OnBottom,
                                     dock2->dptr()->group());

    // Close dock2 and check if dock1's max-size is still honoured
    dock2->close();
    QTest::qWait(100); // wait for the resize, so dock1 gets taller"

    QVERIFY(dock1->dptr()->group()->view()->height()
            <= dock1->dptr()->group()->view()->maxSizeHint().height());
    delete dock2;
}

void TestDocks::tst_addDockWidgetAsTabToDockWidget()
{
    EnsureTopLevelsDeleted e;
    {
        // Dock into a non-morphed floating dock widget
        auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
        auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));

        dock1->addDockWidgetAsTab(dock2);

        auto window1 = dock1->window();
        auto window2 = dock2->window();
        QCOMPARE(window1->window(), window2->window());
        QCOMPARE(dock1->dptr()->group(), dock2->dptr()->group());
        QCOMPARE(dock1->dptr()->group()->dockWidgetCount(), 2);
        dock1->destroyLater();
        dock2->destroyLater();
        WAIT_FOR_DELETED(dock2);
    }
    {
        // Dock into a morphed dock widget
        auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
        dock1->dptr()->morphIntoFloatingWindow();
        auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));

        dock1->addDockWidgetAsTab(dock2);

        auto window1 = dock1->window();
        auto window2 = dock2->window();
        QCOMPARE(window1->window(), window2->window());
        QCOMPARE(dock1->dptr()->group(), dock2->dptr()->group());
        QCOMPARE(dock1->dptr()->group()->dockWidgetCount(), 2);
        dock1->destroyLater();
        dock2->destroyLater();
        WAIT_FOR_DELETED(dock2);
    }
    {
        // Dock a morphed dock widget into a morphed dock widget
        auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
        dock1->dptr()->morphIntoFloatingWindow();
        auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));
        dock2->dptr()->morphIntoFloatingWindow();
        auto originalWindow2 = dock2->window();

        dock1->addDockWidgetAsTab(dock2);

        auto window1 = dock1->window();
        auto window2 = dock2->window();
        QCOMPARE(window1->window(), window2->window());
        QCOMPARE(dock1->dptr()->group(), dock2->dptr()->group());
        QCOMPARE(dock1->dptr()->group()->dockWidgetCount(), 2);
        WAIT_FOR_DELETED(originalWindow2.get());

        dock1->destroyLater();
        dock2->destroyLater();
        WAIT_FOR_DELETED(dock2);
    }
    {
        // Dock to an already docked widget
        auto m = createMainWindow();
        auto dropArea = m->dropArea();
        auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
        nestDockWidget(dock1, dropArea, nullptr, KDDockWidgets::Location_OnLeft);

        auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));
        dock1->addDockWidgetAsTab(dock2);
        QVERIFY(dock1->window()->equals(m->view()));
        QVERIFY(dock2->window()->equals(m->view()));
        QCOMPARE(dock1->dptr()->group(), dock2->dptr()->group());
        QCOMPARE(dock1->dptr()->group()->dockWidgetCount(), 2);
    }
}

void TestDocks::tst_closeTabHidesDockWidget()
{
    // Tests that closing some tabbed dock widgets will hide them
    // QtQuick had a bug where they would still be visible
    {
        EnsureTopLevelsDeleted e;
        auto dock1 = createDockWidget("doc1");
        auto dock2 = createDockWidget("doc2");
        auto dock3 = createDockWidget("doc3");

        dock1->addDockWidgetAsTab(dock2);
        dock1->addDockWidgetAsTab(dock3);

        dock1->forceClose();
        QVERIFY(!dock1->isOpen());
        QVERIFY(!dock1->isVisible());

        dock2->forceClose();
        QVERIFY(!dock2->isOpen());
        QVERIFY(!dock2->isVisible());

        dock3->forceClose();
        QVERIFY(!dock3->isOpen());
        QVERIFY(!dock3->isVisible());
    }

    {
        EnsureTopLevelsDeleted e;
        auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("doc1");
        auto dock2 = createDockWidget("doc2");
        auto dock3 = createDockWidget("doc3");
        m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
        m->addDockWidget(dock2, KDDockWidgets::Location_OnLeft);
        m->addDockWidget(dock3, KDDockWidgets::Location_OnLeft);

        dock2->addDockWidgetAsTab(dock1);
        dock2->addDockWidgetAsTab(dock3);

        dock1->close();
        QVERIFY(!dock1->isOpen());
        QVERIFY(!dock1->isVisible());
        QCOMPARE(dock1->parent(), nullptr);

        dock2->close();
        QVERIFY(!dock2->isOpen());
        QCOMPARE(dock2->parent(), nullptr);
        QVERIFY(!dock2->isVisible());

        dock3->close();
        QVERIFY(!dock3->isOpen());
        QVERIFY(!dock3->isVisible());
        QCOMPARE(dock3->parent(), nullptr);
        QVERIFY(!dock2->isVisible());
    }
}

void TestDocks::tst_propagateSizeHonoursMinSize()
{
    // Here we dock a widget on the left size, and on the right side.
    // When docking the second one, the 1st one shouldn't be squeezed too much, as it has a min size

    EnsureTopLevelsDeleted e;

    auto m = createMainWindow();
    CreateViewOptions opts;
    opts.isVisible = true;
    opts.minSize = { 80, 29 };
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView(opts));
    auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView(opts));
    auto dropArea = m->dropArea();
    int min1 = widgetMinLength(dock1->view(), Qt::Horizontal);
    int min2 = widgetMinLength(dock2->view(), Qt::Horizontal);

    QVERIFY(dock1->width() >= min1);
    QVERIFY(dock2->width() >= min2);

    nestDockWidget(dock1, dropArea, nullptr, KDDockWidgets::Location_OnRight);
    nestDockWidget(dock2, dropArea, nullptr, KDDockWidgets::Location_OnLeft);

    // Calculate again, as the window group has disappeared
    min1 = widgetMinLength(dock1->view(), Qt::Horizontal);
    min2 = widgetMinLength(dock2->view(), Qt::Horizontal);

    auto l = m->dropArea();
    l->checkSanity();

    if (dock1->width() < min1) {
        KDDW_INFO("dock1->width()={}, \nmin1={}, \ndock min sizes={}, \ngroup1->width()={}, \ngroup1->min={}", dock1->width(), min1,
                  dock1->view()->minSize(), dock1->dptr()->group()->view()->width(), lengthForSize(dock1->dptr()->group()->view()->minSize(), Qt::Horizontal));
        l->dumpLayout();
        QVERIFY(false);
    }

    QVERIFY(dock2->width() >= min2);

    // Dock on top of center widget:
    m = createMainWindow();

    dock1 = createDockWidget("one", Platform::instance()->tests_createFocusableView({ true }));
    m->addDockWidgetAsTab(dock1);
    auto dock3 =
        createDockWidget("three", Platform::instance()->tests_createFocusableView({ true }));
    m->addDockWidget(dock3, Location_OnTop);
    QVERIFY(m->dropArea()->checkSanity());

    min1 = widgetMinLength(dock1->view(), Qt::Vertical);
    QVERIFY(dock1->height() >= min1);
}

void TestDocks::tst_constraintsPropagateUp()
{
    // Mostly for QtQuick, which doesn't have any layouts, so we need to make the propagation
    // Manually in DockWidgetQuick::minimumSize(), in Frame_qtquick, etc.

    EnsureTopLevelsDeleted e;
    const int minWidth = 500;
    const int minHeight = 400;
    const Size minSz = { minWidth, minHeight };
    auto guestWidget =
        Platform::instance()->tests_createView({ true, {}, Size(minWidth, minHeight) });
    auto dock1 = createDockWidget("dock1", guestWidget);
    auto dock2 = createDockWidget(
        "dock2", Platform::instance()->tests_createView({ true, {}, Size(minWidth, minHeight) }));

    QCOMPARE(widgetMinLength(guestWidget, Qt::Vertical), minHeight);
    QCOMPARE(widgetMinLength(guestWidget, Qt::Horizontal), minWidth);
    QCOMPARE(dock1->view()->minSize(), minSz);

    auto group1 = dock1->dptr()->group();

    QVERIFY(std::abs(widgetMinLength(group1, Qt::Horizontal) - minWidth) < 10); // 10px for styling
                                                                                // differences
    QVERIFY(std::abs(widgetMinLength(group1, Qt::Vertical) - (minHeight + group1->nonContentsHeight()))
            < 10); // 10px for styling differences

    // Add dock2 side-by side, so the Frame now has a title bar.
    auto oldFw2 = dock2->window();
    dock1->addDockWidgetToContainingWindow(dock2, Location_OnLeft);
    Core::TitleBar *tb = dock1->titleBar();
    QVERIFY(tb->isVisible());
    QVERIFY(std::abs(widgetMinLength(group1, Qt::Vertical) - (minHeight + group1->nonContentsHeight()))
            < 10);
}

void TestDocks::tst_constraintsAfterPlaceholder()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(500, 500), MainWindowOption_None);
    const int minHeight = 400;
    auto dock1 = createDockWidget(
        "dock1", Platform::instance()->tests_createView({ true, {}, Size(400, minHeight) }));
    auto dock2 = createDockWidget(
        "dock2", Platform::instance()->tests_createView({ true, {}, Size(400, minHeight) }));
    auto dock3 = createDockWidget(
        "dock3", Platform::instance()->tests_createView({ true, {}, Size(400, minHeight) }));
    auto dropArea = m->dropArea();
    Core::DropArea *layout = dropArea;

    // Stack 3, 2, 1
    m->addDockWidget(dock1, Location_OnTop);
    m->addDockWidget(dock2, Location_OnTop);
    m->addDockWidget(dock3, Location_OnTop);

    if (Platform::instance()->isQtWidgets())
        QVERIFY(WAIT_FOR_RESIZE(m.get()));

    QVERIFY(m->view()->minSize().height() > minHeight * 3); // > since some vertical space is occupied
                                                            // by the separators

    // Now close dock1 and check again
    dock1->close();
    WAIT_FOR_RESIZE(dock2->view());

    Item *item2 = layout->itemForGroup(dock2->dptr()->group());
    Item *item3 = layout->itemForGroup(dock3->dptr()->group());

    Margins margins = m->centerWidgetMargins();
    const int expectedMinHeight = item2->minLength(Qt::Vertical) + item3->minLength(Qt::Vertical)
        + 1 * Item::layoutSpacing + margins.top() + margins.bottom();

    QCOMPARE(m->view()->minSize().height(), expectedMinHeight);

    dock1->destroyLater();
    WAIT_FOR_DELETED(dock1);
}

void TestDocks::tst_dragBySingleTab()
{
    // Tests dragging via a tab when there's only 1 tab, and we're using Flag_AlwaysShowTabs
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_AlwaysShowTabs);
    auto dock1 = createDockWidget(
        "dock1", Platform::instance()->tests_createView({ true, {}, Size(400, 400) }));
    dock1->open();

    auto group1 = dock1->dptr()->group();

    Point globalPressPos = dragPointForWidget(group1, 0);
    Core::TabBar *tabBar = group1->stack()->tabBar();
    QVERIFY(tabBar);
    SetExpectedWarning sew("No window being dragged for"); // because dragging by tab does nothing
                                                           // in this case
    drag(tabBar->view(), globalPressPos, Point(0, 0));

    delete dock1;
    WAIT_FOR_DELETED(group1);
}

void TestDocks::tst_deleteOnClose()
{
    {
        EnsureTopLevelsDeleted e;
        // Tests that DockWidget::close() deletes itself if Option_DeleteOnClose is set
        ObjectGuard<Core::DockWidget> dock1 = createDockWidget(
            "1", Platform::instance()->tests_createView({ true, {}, Size(400, 400) }),
            DockWidgetOption_DeleteOnClose);
        dock1->open();
        dock1->close();

        QVERIFY(WAIT_FOR_DELETED(dock1));
    }

    {
        // Tests that if it's closed via LayoutSaver it's also destroyed when having
        // Option_DeleteOnClose
        EnsureTopLevelsDeleted e;

        ObjectGuard<Core::DockWidget> dock1 = createDockWidget(
            "1", Platform::instance()->tests_createView({ true, {}, Size(400, 400) }),
            DockWidgetOption_DeleteOnClose, {}, /*show=*/false);
        ObjectGuard<Core::DockWidget> dock2 = createDockWidget(
            "2", Platform::instance()->tests_createView({ true, {}, Size(400, 400) }), {}, {},
            /*show=*/false);
        LayoutSaver saver;
        const QByteArray saved = saver.serializeLayout();
        dock1->open();
        dock2->open();
        QVERIFY(dock1->isVisible());
        QVERIFY(dock2->isVisible());

        QVERIFY(saver.restoreLayout(saved));
        QVERIFY(!dock1->isVisible());
        QVERIFY(!dock2->isVisible());

        QVERIFY(WAIT_FOR_DELETED(dock1));
        QVERIFY(dock2.data());
        delete dock2;
    }
}

void TestDocks::tst_toggleAction()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget(
        "dock1", Platform::instance()->tests_createView({ true, {}, Size(400, 400) }));
    auto dock2 = createDockWidget(
        "dock2", Platform::instance()->tests_createView({ true, {}, Size(400, 400) }));
    auto dock3 = createDockWidget(
        "dock3", Platform::instance()->tests_createView({ true, {}, Size(400, 400) }));

    m->addDockWidget(dock1, Location_OnLeft);
    m->addDockWidget(dock2, Location_OnRight);
    m->addDockWidget(dock3, Location_OnRight);

    auto root = m->multiSplitter()->rootItem();
    QCOMPARE(root->visibleCount_recursive(), 3);
    QVERIFY(dock2->toggleAction()->isChecked());
    ObjectGuard<Core::Group> group2 = dock2->dptr()->group();
    dock2->toggleAction()->toggle();
    QVERIFY(!dock2->toggleAction()->isChecked());

    QVERIFY(!dock2->isVisible());
    QVERIFY(!dock2->isOpen());
    QVERIFY(WAIT_FOR_DELETED(group2));

    QCOMPARE(root->visibleCount_recursive(), 2);
}

void TestDocks::tst_redocksToPreviousTabIndex()
{
    // Checks that when reordering tabs with mouse, floating and redocking, they go back to their
    // previous index

    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_AllowReorderTabs);

    auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
    auto dock0 = createDockWidget(
        "dock0", Platform::instance()->tests_createView({ true, {}, Size(400, 400) }));
    auto dock1 = createDockWidget(
        "dock1", Platform::instance()->tests_createView({ true, {}, Size(400, 400) }));
    m->addDockWidget(dock0, Location_OnLeft);
    dock0->addDockWidgetAsTab(dock1);

    QCOMPARE(dock0->tabIndex(), 0);
    QCOMPARE(dock1->tabIndex(), 1);

    dock0->setFloating(true);
    QCOMPARE(dock1->tabIndex(), 0);

    dock0->setFloating(false);
    QCOMPARE(dock0->tabIndex(), 0);
    QCOMPARE(dock1->tabIndex(), 1);

    Core::Group *group = dock0->dptr()->group();
    auto tb = dock0->dptr()->group()->stack()->tabBar();
    tb->moveTabTo(0, 1);

    if (!Platform::instance()->isQtQuick()) {
        QCOMPARE(dock0->tabIndex(), 1);
        QCOMPARE(dock1->tabIndex(), 0);

        // Also detach via detachTab(), which is what is called when the user detaches with mouse
        group->detachTab(dock0);
        dock0->setFloating(false);

        QCOMPARE(dock0->tabIndex(), 1);
        QCOMPARE(dock1->tabIndex(), 0);
    } else {
        // An XFAIL so we remember to implement this
        // QEXPECT_FAIL("", "TabBar::moveTabTo not implemented for QtQuick yet", Continue);
        // QVERIFY(false);
        KDDW_UNUSED(group);
    }
}

void TestDocks::tst_toggleTabbed()
{
    // Testing the weird bugs reported in #211

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
    auto dock0 = createDockWidget(
        "dock0", Platform::instance()->tests_createView({ true, {}, Size(400, 400) }));
    auto dock1 = createDockWidget(
        "dock1", Platform::instance()->tests_createView({ true, {}, Size(400, 400) }));

    m->addDockWidget(dock0, Location_OnBottom);
    dock0->addDockWidgetAsTab(dock1);

    QVERIFY(dock1->isCurrentTab());
    QVERIFY(dock0->toggleAction()->isChecked());
    QVERIFY(dock1->toggleAction()->isChecked());
    QVERIFY(dock0->isOpen());
    QVERIFY(dock1->isOpen());

    dock0->close();
    QVERIFY(!dock0->isOpen());
    QVERIFY(dock1->isOpen());
    QVERIFY(dock1->toggleAction()->isChecked());
    QVERIFY(dock1->isCurrentTab());
    Core::Group *group = dock1->dptr()->group();
    Core::TabBar *tb = group->tabBar();
    QCOMPARE(tb->currentIndex(), 0);
    QCOMPARE(tb->numDockWidgets(), 1);
    QCOMPARE(group->tabBar()->currentDockWidget(), dock1);
    QVERIFY(!dock0->isVisible());
    QVERIFY(group->isVisible());

    QCOMPARE(group->currentIndex(), 0);
    QCOMPARE(group->tabBar()->currentIndex(), 0);

    QVERIFY(dock1->isVisible());
}

void TestDocks::tst_toggleTabbed2()
{
    // Testing the weird bugs reported in #215
    EnsureTopLevelsDeleted e;
    auto dock0 = createDockWidget(
        "dock0", Platform::instance()->tests_createView({ true, {}, Size(400, 400) }));
    auto dock1 = createDockWidget(
        "dock1", Platform::instance()->tests_createView({ true, {}, Size(400, 400) }));
    dock0->addDockWidgetAsTab(dock1);

    dock0->setAsCurrentTab();

    Core::Group *group1 = dock1->dptr()->group();
    QCOMPARE(group1->currentDockWidget(), dock0);
    QCOMPARE(group1->currentIndex(), 0);

    dock0->setFloating(true);
    Core::Group *group0 = dock0->dptr()->group();

    QCOMPARE(group0->currentIndex(), 0);
    QCOMPARE(group1->currentIndex(), 0);

    QCOMPARE(group0->title(), "dock0");
    QCOMPARE(group1->title(), "dock1");
}

void TestDocks::tst_resizePropagatesEvenly()
{
    // For github issue #186
    // Usually resizing main window will resize dock widgets evenly, but if you resize multiple
    // times then one dock widget is getting too small. Not repro with all layouts, but the
    // following one reproduced it:

    auto m = createMainWindow(Size(1000, 1000), MainWindowOption_None);
    auto dock0 = createDockWidget("dock0", Platform::instance()->tests_createView({ true }));
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));

    m->addDockWidget(dock1, Location_OnLeft);
    m->addDockWidget(dock2, Location_OnTop, dock1);
    m->addDockWidget(dock0, Location_OnRight);

    QVERIFY(std::abs(dock2->height() - dock1->height()) < 2);

    m->view()->resize(m->size() + Size(0, 500));
    for (int i = 1; i < 10; ++i)
        m->view()->resize(m->size() - Size(0, i));

    QVERIFY(std::abs(dock2->height() - dock1->height()) < 3);
}

void TestDocks::tst_addMDIDockWidget()
{
    EnsureTopLevelsDeleted e;

    // Test that adding a MDI dock widget doesn't produce any warning
    auto m = createMainWindow(Size(800, 500), MainWindowOption_MDI);
    auto dock0 = createDockWidget(
        "dock0", Platform::instance()->tests_createView({ true, {}, Size(400, 400) }));
    m->layout()->asMDILayout()->addDockWidget(dock0, Point(0, 0), {});

    // MDI doesn't support LayoutSaver yet, but it was crashing, so add a test
    // to catch further crashes
    LayoutSaver saver;
    const QByteArray saved = saver.serializeLayout();
}

void TestDocks::tst_mdiSetSize()
{
    // Tests that adding a dockwidget to MDI preserves its size
    EnsureTopLevelsDeleted e;

    auto m = createMainWindow(Size(800, 500), MainWindowOption_MDI);

    auto dock0 = createDockWidget(
        "dock0", Platform::instance()->tests_createView({}), {}, {}, false);

    const Size size = { 501, 502 };
    dock0->view()->setSize(size);
    QCOMPARE(dock0->view()->size(), size);

    m->layout()
        ->asMDILayout()
        ->addDockWidget(dock0, Point(10, 10), {});

    auto group = dock0->dptr()->group();
    QCOMPARE(group->pos(), Point(10, 10));

    QCOMPARE(group->size(), size);
}

void TestDocks::tst_mdiCrash()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(800, 500), MainWindowOption_MDI);

    auto dock0 = createDockWidget(
        "dock0", Platform::instance()->tests_createView({ true, {}, Size(200, 200) }));
    auto dock2 = createDockWidget(
        "dock", Platform::instance()->tests_createView({ true, {}, Size(200, 200) }));
    m->layout()->asMDILayout()->addDockWidget(dock0, Point(0, 0), {});
    m->layout()->asMDILayout()->addDockWidget(dock2, Point(0, 0), {});

    Platform::instance()->tests_wait(1000);
    delete dock0;
    delete dock2;


    Platform::instance()->tests_wait(1); // for leaks
}

void TestDocks::tst_mdiZorder()
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    // The test is failing on Qt5+QtQuick.
    // Since it actually runs fine on Qt5+QtQuick when running the examples, will
    // just skip the test instead of spending time on Qt5
    if (Platform::instance()->isQtQuick())
        return;
#endif

    // Tests that clicking a mdi widget will raise its
    EnsureTopLevelsDeleted e;

    auto m = createMainWindow(Size(800, 500), MainWindowOption_MDI);

    auto dock0 = createDockWidget(
        "dock0", Platform::instance()->tests_createView({ true, {}, Size(200, 200) }));

    auto dock1 = createDockWidget(
        "dock1", Platform::instance()->tests_createView({ true, {}, Size(200, 200) }));

    m->layout()->asMDILayout()->addDockWidget(dock0, Point(0, 0), {});
    m->layout()->asMDILayout()->addDockWidget(dock1, Point(100, 100), {});

    dock0->setMDISize({ 200, 200 });
    dock1->setMDISize({ 200, 200 });

    // Dock 1 is over 0
    QCOMPARE(dock0->mdiZ(), 0);
    QCOMPARE(dock1->mdiZ(), 1);

    // Double click dock 0, it should raise
    auto window = dock0->view()->window();
    Tests::doubleClickOn(dock0->mapToGlobal(Point(70, 70)), window);
    QCOMPARE(dock0->mdiZ(), 1);
    QCOMPARE(dock1->mdiZ(), 0);

    // Double click dock 1, it should raise
    Tests::doubleClickOn(dock1->mapToGlobal(Point(150, 150)), window);
    QCOMPARE(dock0->mdiZ(), 0);
    QCOMPARE(dock1->mdiZ(), 1);
}

void TestDocks::tst_mdiZorder2()
{
    // Tests that clicking a mdi widget will NOT raise its when using MDIFlag_NoClickToRaise
    EnsureTopLevelsDeleted e;
    Config::self().setMDIFlags(KDDockWidgets::Config::MDIFlag_NoClickToRaise);

    auto m = createMainWindow(Size(800, 500), MainWindowOption_MDI);

    auto dock0 = createDockWidget(
        "dock0", Platform::instance()->tests_createView({ true, {}, Size(200, 200) }));

    auto dock1 = createDockWidget(
        "dock1", Platform::instance()->tests_createView({ true, {}, Size(200, 200) }));

    m->layout()->asMDILayout()->addDockWidget(dock0, Point(0, 0), {});
    m->layout()->asMDILayout()->addDockWidget(dock1, Point(100, 100), {});

    dock0->setMDISize({ 200, 200 });
    dock1->setMDISize({ 200, 200 });

    // Dock 1 is over 0
    QCOMPARE(dock0->mdiZ(), 0);
    QCOMPARE(dock1->mdiZ(), 1);

    // Double click dock 0, it should NOT raise
    auto window = dock0->view()->window();
    Tests::doubleClickOn(dock0->mapToGlobal(Point(70, 70)), window);
    QCOMPARE(dock0->mdiZ(), 0);
    QCOMPARE(dock1->mdiZ(), 1);
}

void TestDocks::tst_mixedMDIRestoreToArea()
{
    EnsureTopLevelsDeleted e;

    auto m = createMainWindow(Size(800, 500), MainWindowOption_HasCentralWidget);
    auto mdiLayout = new Core::MDILayout(nullptr);
    m->setPersistentCentralView(mdiLayout->view()->asWrapper());

    auto dock0 = createDockWidget(
        "dock0", Platform::instance()->tests_createView({ true, {}, Size(200, 200) }));
    mdiLayout->addDockWidget(dock0, { 10, 10 });

    QVERIFY(!mdiLayout->layoutSize().isEmpty());

    auto pos = dock0->d->lastPosition();
    QVERIFY(pos->lastItem());
    auto originalWindow = dock0->view()->window();
    dock0->setFloating(true);
    dock0->setFloating(false);
    QCOMPARE(dock0->view()->window()->handle(), originalWindow->handle());
}

void TestDocks::tst_redockToMDIRestoresPosition()
{
    // Tests that setFloating(false) puts the dock widget where it was before floating

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(800, 500), MainWindowOption_MDI);
    auto dock0 = createDockWidget(
        "dock0", Platform::instance()->tests_createView({ true, {}, Size(400, 400) }));

    auto layout = m->layout()->asMDILayout();
    const Point initialPoint = Point(500, 500);
    layout->addDockWidget(dock0, initialPoint, {});

    Core::Group *group = dock0->DockWidget::d->group();
    QCOMPARE(group->view()->pos(), initialPoint);

    const Size initialSize = group->size();

    dock0->setFloating(true);
    dock0->setFloating(false);
    group = dock0->DockWidget::d->group();
    QCOMPARE(group->view()->pos(), initialPoint);

    const Point anotherPos = Point(250, 250);
    dock0->setMDIPosition(anotherPos);

    dock0->setFloating(true);
    dock0->setFloating(false);
    group = dock0->DockWidget::d->group();

    Item *item = layout->itemForGroup(group);
    QCOMPARE(item->pos(), anotherPos);
    QCOMPARE(item->geometry(), group->geometry());
    QCOMPARE(group->view()->pos(), anotherPos);
    QCOMPARE(group->size(), initialSize);

    const Size anotherSize = Size(500, 500);
    dock0->setMDISize(anotherSize);
    QCOMPARE(group->size(), anotherSize);
    item = layout->itemForGroup(group);
    QCOMPARE(item->geometry(), group->geometry());
}

void TestDocks::tst_restoreWithNativeTitleBar()
{
#ifdef Q_OS_WIN // Other OS don't support this
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_NativeTitleBar);

    auto dock0 = createDockWidget(
        "dock0", Platform::instance()->tests_createView({ true, {}, Size(400, 400) }));
    dock0->window()->move(100, 100);

    QVERIFY(!dock0->titleBar()->isVisible());
    QVERIFY(!dock0->floatingWindow()->titleBar()->isVisible());
    QVERIFY(!dock0->d->group()->titleBar()->isVisible());

    LayoutSaver saver;
    const QByteArray saved = saver.serializeLayout();
    saver.restoreLayout(saved);
    QVERIFY(!dock0->titleBar()->isVisible());
    QVERIFY(!dock0->floatingWindow()->titleBar()->isVisible());
    QVERIFY(!dock0->d->group()->titleBar()->isVisible());
#endif
}

void TestDocks::tst_closeTabOfCentralFrame()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(500, 500), MainWindowOption_HasCentralGroup,
                              "tst_closeTabOfCentralFrame");
    auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
    m->addDockWidgetAsTab(dock1);
    Core::Group *group = dock1->dptr()->group();
    QVERIFY(group->options() & FrameOption_IsCentralFrame);
    QVERIFY(group->isVisible());
    dock1->close();
    QVERIFY(group->isVisible());
}

void TestDocks::tst_centralGroupAffinity()
{
    EnsureTopLevelsDeleted e;

    auto m =
        createMainWindow(Size(500, 500), MainWindowOption_HasCentralGroup, "tst_centralFrame245");
    const Vector<QString> affinities = { "a" };
    m->setAffinities(affinities);

    Group *centralGroup = m->dropArea()->centralGroup();
    QCOMPARE(centralGroup->affinities(), affinities);
}

void TestDocks::tst_persistentCentralWidget()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(500, 500), MainWindowOption_HasCentralWidget);
    auto dockwidgets = m->dropArea()->dockWidgets();
    QCOMPARE(dockwidgets.size(), 1);

    auto dw = dockwidgets.constFirst();
    dw->close();
    QVERIFY(dw->isOpen());
    QVERIFY(dw->isPersistentCentralDockWidget());
    dw->setFloating(true);
    QVERIFY(!dw->isFloating());


    LayoutSaver saver;
    const QByteArray saved = saver.serializeLayout();
    QVERIFY(!saved.isEmpty());

    QVERIFY(saver.restoreLayout(saved));
}

void TestDocks::tst_unfloatTabbedFloatingWidgets()
{
    EnsureTopLevelsDeleted e;

    /// A main window with 2 tabbed dock widgets.
    /// Tests that we're able to float the entire tab group and
    /// put it back into the main window when float button is pressed again.

    auto m = createMainWindow(Size(1000, 1000), MainWindowOption_None);
    auto dock0 = createDockWidget("0", Platform::instance()->tests_createView({ true }));
    auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
    m->addDockWidget(dock0, Location_OnLeft);
    dock0->addDockWidgetAsTab(dock1);

    dock0->titleBar()->onFloatClicked();
    QVERIFY(dock0->titleBar()->isFloating());
    QVERIFY(!dock0->mainWindow());

    dock0->titleBar()->onFloatClicked();
    QVERIFY(!dock0->titleBar()->isFloating());
    QVERIFY(dock0->mainWindow());
}

void TestDocks::tst_unfloatTabbedFloatingWidgets2()
{
    EnsureTopLevelsDeleted e;

    // Like tst_unfloatTabbedFloatingWidgets, but now there's no main window, just a FloatingWindow
    // with nesting.

    auto dock0 = createDockWidget("0", Platform::instance()->tests_createView({ true }));
    auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("2", Platform::instance()->tests_createView({ true }));

    dock0->open();
    dock1->open();
    dock2->open();

    dock0->addDockWidgetAsTab(dock1);
    dock0->addDockWidgetToContainingWindow(dock2, KDDockWidgets::Location_OnBottom);

    // Float:
    dock0->titleBar()->onFloatClicked();
    QVERIFY(dock0->titleBar()->isFloating());
    QCOMPARE(dock0->floatingWindow(), dock1->floatingWindow());
    QVERIFY(dock0->floatingWindow() != dock2->floatingWindow());

    // redock
    dock0->titleBar()->onFloatClicked();
    QVERIFY(!dock0->titleBar()->isFloating());
    QCOMPARE(dock0->floatingWindow(), dock1->floatingWindow());
    QVERIFY(dock0->floatingWindow() == dock2->floatingWindow());
}

void TestDocks::tst_currentTabMatchesDockWidget()
{
    // Tests that if a dock widget is current, then it's also visible. And vice-versa.

    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(1000, 1000), MainWindowOption_None);
    auto dock0 = createDockWidget("0", Platform::instance()->tests_createView({ true }));
    auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("2", Platform::instance()->tests_createView({ true }));

    m->addDockWidget(dock0, KDDockWidgets::Location_OnBottom);
    dock0->addDockWidgetAsTab(dock1);
    dock0->addDockWidgetAsTab(dock2);

    QVERIFY(!dock0->isCurrentTab());
    QVERIFY(!dock1->isCurrentTab());
    QVERIFY(dock2->isCurrentTab());
    QVERIFY(!dock0->isVisible());
    QVERIFY(!dock1->isVisible());
    QVERIFY(dock2->isVisible());

    // Float and refloat:
    dock1->setFloating(true);
    dock1->setFloating(false);

    QVERIFY(!dock0->isCurrentTab());
    QVERIFY(dock1->isCurrentTab());
    QVERIFY(!dock2->isCurrentTab());

    QVERIFY(!dock0->isVisible());
    QVERIFY(dock1->isVisible());
    QVERIFY(!dock2->isVisible());
}

void TestDocks::tst_titlebarNumDockWidgetsChanged()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(1000, 1000), MainWindowOption_None);
    auto dock0 = createDockWidget("0", Platform::instance()->tests_createView({ true }));
    auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));

    m->addDockWidget(dock0, Location_OnLeft);

    auto tb = dock0->titleBar();

    int numSignalEmittions = 0;
    tb->dptr()->numDockWidgetsChanged.connect([&numSignalEmittions] {
        numSignalEmittions++;
    });

    dock0->addDockWidgetAsTab(dock1);

    QVERIFY(numSignalEmittions > 0);

    {
        // Block to manually test that signal is emitted when using LayoutSaver as well
        // Use debugger or add a connect() in TitleBar's ctor to checks
        LayoutSaver saver;
        const QByteArray saved = saver.serializeLayout();

        dock0->close();
        dock1->close();

        saver.restoreLayout(saved);
    }
}

void TestDocks::tst_closed()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(1000, 1000), MainWindowOption_None);
    auto dockA = createDockWidget("0", Platform::instance()->tests_createView({ true }));
    auto dockB = createDockWidget("1", Platform::instance()->tests_createView({ true }));

    int numCloseA = 0;
    int numCloseB = 0;

    dockA->d->closed.connect([&] { numCloseA++; });
    dockB->d->closed.connect([&] { numCloseB++; });

    dockA->setFloating(true);
    m->addDockWidget(dockB, KDDockWidgets::Location_OnBottom);

    QCOMPARE(numCloseA, 0);
    QCOMPARE(numCloseB, 0);

    dockB->close();
    QCOMPARE(numCloseA, 0);
    QCOMPARE(numCloseB, 1);

    dockA->close();
    QCOMPARE(numCloseA, 1);
    QCOMPARE(numCloseB, 1);
}

void TestDocks::tst_maximizeButton()
{
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_TitleBarHasMaximizeButton);

    auto dock0 = createDockWidget("0", Platform::instance()->tests_createView({ true }));
    dock0->show();

    Window::Ptr window = dock0->floatingWindow()->window()->window();

    QVERIFY(window);
    QCOMPARE(window->windowState(), WindowState::None);

    TitleBar *tb = dock0->titleBar();
    QVERIFY(tb->isVisible());
    QVERIFY(tb->maximizeButtonVisible());
    QCOMPARE(tb->maximizeButtonType(), TitleBarButtonType::Maximize);

    tb->onMaximizeClicked();

    WAIT_FOR_RESIZE(dock0->floatingWindow()->view());

    QVERIFY(tb->maximizeButtonVisible());
    QCOMPARE(tb->maximizeButtonType(), TitleBarButtonType::Normal);
}

void TestDocks::tst_restoreAfterUnminimized()
{
    // Save a layout with a minimized window, then unminimize (show it), restore layout
    // Result should be that the widget gets minimized again

    EnsureTopLevelsDeleted e;
    auto dock0 = createDockWidget("0", Platform::instance()->tests_createView({ true }));
    dock0->show();

    QVERIFY(!dock0->window()->isMinimized());

    dock0->window()->showMinimized();

    QVERIFY(dock0->window()->isMinimized());

    LayoutSaver saver;
    const auto saved = saver.serializeLayout();
    saver.saveToFile("filename.txt");
    dock0->window()->showNormal();

    Platform::instance()->tests_wait(1000);
    QVERIFY(!dock0->window()->isMinimized());
    QVERIFY(saver.restoreLayout(saved));


#ifdef KDDW_FRONTEND_QT_WINDOWS
    // QtQuick is using hack for QTBUG-120269
    if (Platform::instance()->isQtQuick())
        Platform::instance()->tests_wait(1000);

    // For QtWidgets we're not using the workaround. Needs to be tested.
    QVERIFY(dock0->window()->isMinimized());
#else
    QVERIFY(dock0->window()->isMinimized());
#endif
}

void TestDocks::tst_restoreFlagsFromVersion16()
{
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_HideTitleBarWhenTabsVisible);

    // Save a layout with a floating window:
    auto dock1 = createDockWidget("1");

    LayoutSaver saver;
    saver.restoreFromFile(resourceFileName("layouts/1.6layoutWithoutFloatingWindowFlags.json"));

    auto floatingWindow = dock1->floatingWindow();
    QVERIFY(floatingWindow);

    QCOMPARE(int(floatingWindow->floatingWindowFlags()), int(FloatingWindowFlag::HideTitleBarWhenTabsVisible));
}

void TestDocks::tst_map()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(1000, 1000), MainWindowOption_None);
    auto dockA = createDockWidget("0", Platform::instance()->tests_createView({ true }));
    auto dockB = createDockWidget("1", Platform::instance()->tests_createView({ true }));

    m->addDockWidget(dockA, KDDockWidgets::Location_OnTop);
    m->addDockWidget(dockB, KDDockWidgets::Location_OnBottom);

    QTest::qWait(1000);
    const Point localPt = { 10, 10 };
    Point global = dockA->view()->mapToGlobal(localPt);
    QCOMPARE(dockA->view()->mapFromGlobal(global), localPt);

    global = dockB->view()->mapToGlobal(localPt);
    QCOMPARE(dockB->view()->mapFromGlobal(global), localPt);
}

void TestDocks::tst_childViewAt()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(1000, 1000), MainWindowOption_None);
    auto dockA = createDockWidget("0", Platform::instance()->tests_createView({ true }));
    auto dockB = createDockWidget("1", Platform::instance()->tests_createView({ true }));

    m->addDockWidget(dockA, KDDockWidgets::Location_OnTop);
    m->addDockWidget(dockB, KDDockWidgets::Location_OnBottom);
    m->show();

    QTest::qWait(1000);
    const Point localPt = { 100, 200 };
    auto child = m->view()->childViewAt(localPt);
    QVERIFY(child);
    QVERIFY(!child->equals(m->view()));
}

void TestDocks::tst_resizeInLayout()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(1000, 1000), MainWindowOption_None);
    auto dockA = createDockWidget("0", Platform::instance()->tests_createView({ true }));
    auto dockB = createDockWidget("1", Platform::instance()->tests_createView({ true }));
    auto dockC = createDockWidget("2", Platform::instance()->tests_createView({ true }));

    m->addDockWidget(dockA, KDDockWidgets::Location_OnTop);
    m->addDockWidget(dockB, KDDockWidgets::Location_OnBottom);
    m->addDockWidget(dockC, KDDockWidgets::Location_OnBottom);

    m->window()->resize(400, 1000);
    WAIT_FOR_RESIZE(m->view());

    // Nothing happens, since the widget's top is the window's top too:
    const Size dockAOriginalSize = dockA->sizeInLayout();
    dockA->resizeInLayout(0, 500 - dockA->sizeInLayout().height(), 0, 0);
    QCOMPARE(dockAOriginalSize, dockA->sizeInLayout());

    // Move bottom separator down, height is increased to 500
    dockA->resizeInLayout(0, 0, 0, 500 - dockA->sizeInLayout().height());

    QCOMPARE(dockA->sizeInLayout().height(), 500);

    // Move dockB's top separator 50px up, and the bottom one 49px up
    const Size dockBOriginalSize = dockB->sizeInLayout();

    dockB->resizeInLayout(0, 50, 0, -49);

    QCOMPARE(dockA->sizeInLayout().height(), 500 - 50);
    QCOMPARE(dockB->sizeInLayout().height(), dockBOriginalSize.height() + 1);

    // Nothing happens, since the widget's bottom is the window's bottom too:
    Size dockCOriginalSize = dockC->sizeInLayout();
    dockC->resizeInLayout(0, 0, 0, -1);
    QCOMPARE(dockCOriginalSize, dockC->sizeInLayout());

    // Now let's test the cross-axis
    auto dockRight = createDockWidget("right", Platform::instance()->tests_createView({ true }));
    m->addDockWidget(dockRight, KDDockWidgets::Location_OnRight);

    dockCOriginalSize = dockC->sizeInLayout();
    dockC->resizeInLayout(10, 10, 10, 10);

    // bottom wasn't moved
    QCOMPARE(dockC->sizeInLayout().height(), dockCOriginalSize.height() + 10);

    // left wasn't moved
    QCOMPARE(dockC->sizeInLayout().width(), dockCOriginalSize.width() + 10);
}

void TestDocks::tst_keepLast()
{
    // 1 event loop for DelayedDelete. Avoids LSAN warnings.
    QTest::qWait(1);
}

void TestDocks::tst_scopedValueRollback()
{
    bool v1 = false;
    bool v2 = true;

    {
        ScopedValueRollback r1(v1, true);
        QVERIFY(v1);
    }

    {
        ScopedValueRollback r2(v2, false);
        QVERIFY(!v2);
    }

    QVERIFY(!v1);
    QVERIFY(v2);

    {
        ScopedValueRollback r1(v1, false);
        QVERIFY(!v1);
    }

    {
        ScopedValueRollback r2(v2, true);
        QVERIFY(v2);
    }

    QVERIFY(!v1);
    QVERIFY(v2);
}

void TestDocks::tst_point()
{
    Point pt;
    QVERIFY(pt.isNull());
    QCOMPARE(pt, Point(0, 0));

    pt = { 1, 0 };
    QVERIFY(!pt.isNull());

    pt = { -5, 5 };
    QCOMPARE(pt.manhattanLength(), 10);
}

void TestDocks::tst_size()
{
    Size sz;
    QCOMPARE(sz, Size(-1, -1));
    QVERIFY(!sz.isNull());
    QVERIFY(!sz.isValid());
    QVERIFY(sz.isEmpty());

    sz = { 1, 1 };
    QVERIFY(!sz.isNull());
    QVERIFY(sz.isValid());
    QVERIFY(!sz.isEmpty());

    sz = { 1, 0 };
    QVERIFY(!sz.isNull());
    QVERIFY(sz.isValid());
    QVERIFY(sz.isEmpty());

    sz = { 0, 0 };
    QVERIFY(sz.isNull());
    QVERIFY(sz.isValid());
    QVERIFY(sz.isEmpty());

    QCOMPARE(Size(100, 100).expandedTo(Size(50, 200)), Size(100, 200));
    QCOMPARE(Size(100, 100).boundedTo(Size(50, 200)), Size(50, 100));
}

void TestDocks::tst_rect()
{
    Rect r;

    QVERIFY(!r.isValid());
    QVERIFY(r.isEmpty());
    QVERIFY(r.isNull());

    r = { 0, 1, 100, 50 };
    QVERIFY(r.isValid());
    QVERIFY(!r.isEmpty());
    QVERIFY(!r.isNull());
    QCOMPARE(r.width(), 100);
    QCOMPARE(r.height(), 50);
    QCOMPARE(r.y(), 1);
    QCOMPARE(r.x(), 0);
    QCOMPARE(r.size(), Size(100, 50));
    QCOMPARE(r.topLeft(), Point(0, 1));
    QCOMPARE(r.bottomLeft(), Point(0, 50));
    QCOMPARE(r.bottomRight(), Point(99, 50));
    QCOMPARE(r.bottom(), 50);
    QCOMPARE(r.right(), 99);
    QCOMPARE(r.left(), 0);
    QCOMPARE(Rect(0, 0, 50, 50).center(), Point(24, 24));

    r.moveTop(200);
    r.moveLeft(300);
    QCOMPARE(r.topLeft(), Point(300, 200));
    QCOMPARE(r.size(), Size(100, 50));

    r.moveBottom(200);
    r.moveRight(200);
    QCOMPARE(r, Rect(101, 151, 100, 50));

    r.moveTo(0, 0);
    QCOMPARE(r, Rect(0, 0, 100, 50));
    QCOMPARE(r.center(), Point(49, 24));
    Point newCenter(50, 50);
    r.moveCenter(newCenter);
    QCOMPARE(r.center(), Point(50, 50));

    r = { 100, 100, 100, 100 };
    r.setLeft(0);
    QCOMPARE(r.topLeft(), Point(0, 100));
    QCOMPARE(r.size(), Size(200, 100));
    r.setTop(0);
    QCOMPARE(r.topLeft(), Point(0, 0));
    QCOMPARE(r.size(), Size(200, 200));

    r.setRight(99);
    QCOMPARE(r.size(), Size(100, 200));

    r.setBottom(99);
    QCOMPARE(r.size(), Size(100, 100));

    r = { 100, 100, 100, 100 };
    r = r.marginsAdded({ 1, 2, 3, 4 });
    QCOMPARE(r, Rect(99, 98, 104, 106));

    r = { 100, 100, 100, 100 };
    const Rect r2 = { 100, 100, 200, 200 };

    QCOMPARE(r.intersected(r2), Rect(100, 100, 100, 100));
    QVERIFY(r.intersects(r2));

    QVERIFY(Rect(0, 0, 100, 100).contains({ 99, 99, 1, 1 }));
    QVERIFY(!Rect(0, 0, 100, 100).contains({ 99, 99, 2, 2 }));
    QVERIFY(!Rect(0, 0, 100, 100).contains({ 99, 100, 1, 1 }));

    r = { 0, 0, 100, 100 };
    QCOMPARE(r.adjusted(1, 2, 3, 4), Rect(1, 2, 102, 102));
    r.adjust(1, 2, 3, 4);
    QCOMPARE(r, Rect(1, 2, 102, 102));


    r = { 800, 300, 400, 400 };
    QVERIFY(r.contains({ 900, 500 }));
}

#define KDDW_TEST_NAME TestDocks
#include "test_main_qt.h"

#include "tst_docks.moc"

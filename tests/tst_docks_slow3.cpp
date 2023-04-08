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
#include "kddockwidgets/core/MDILayout.h"
#include "kddockwidgets/core/DropArea.h"
#include "kddockwidgets/core/MainWindow.h"
#include "kddockwidgets/core/DockWidget.h"
#include "kddockwidgets/core/DockWidget_p.h"
#include "kddockwidgets/core/Separator.h"
#include "kddockwidgets/core/TabBar.h"
#include "kddockwidgets/core/Stack.h"
#include "kddockwidgets/core/SideBar.h"
#include "utils_qt.h"

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
    void tst_dockWidgetGetsFocusWhenDocked();
    void tst_closeShowWhenNoCentralFrame();
    void tst_close();
    void tst_positionWhenShown();
};

void TestDocks::tst_dockWidgetGetsFocusWhenDocked()
{
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_TitleBarIsFocusable);

    // We drag dw2 onto dw2 and drop it

    auto dw1 = Config::self()
                   .viewFactory()
                   ->createDockWidget("1")
                   ->asDockWidgetController();
    auto dw2 = Config::self()
                   .viewFactory()
                   ->createDockWidget("2")
                   ->asDockWidgetController();
    auto le1 = Platform::instance()->tests_createFocusableView({ true });
    auto le2 = Platform::instance()->tests_createFocusableView({ true });
    dw1->setGuestView(le1->asWrapper());
    dw2->setGuestView(le2->asWrapper());
    dw2->open();
    dw1->open();
    QTest::qWait(200);

    auto fw1 = dw1->floatingWindow();
    QPointer<Core::FloatingWindow> fw2 = dw2->floatingWindow();

    // Focus dock widget 1 first
    QVERIFY(!dw1->isFocused());
    dw1->window()->activateWindow();

    connect(
        dw1, &Core::DockWidget::isFocusedChanged, dw1, [dw1](bool focused) {
            Q_ASSERT(focused == dw1->isFocused());
        });

    le1->setFocus(Qt::MouseFocusReason);
    QTest::qWait(200);
    QVERIFY(dw1->isFocused());

    QVERIFY(fw1->view()->isActiveWindow());
    dragFloatingWindowTo(fw2, fw1->dropArea(), DropLocation_Left);
    Platform::instance()->tests_waitForEvent(fw1, Event::WindowActivate);

    /// We dropped into floating window 1, it should still be active
    QVERIFY(fw1->view()->isActiveWindow());

    // DockWidget 2 was dropped, it should now be focused
    QVERIFY(!dw1->isFocused());
    QVERIFY(dw2->isFocused());

    delete fw1;
    delete fw2;
}

void TestDocks::tst_closeShowWhenNoCentralFrame()
{
    EnsureTopLevelsDeleted e;
    // Tests a crash I got when hiding and showing and no central group

    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None); // Remove central group
    QPointer<Core::DockWidget> dock1 =
        createDockWidget("1", Platform::instance()->tests_createView({ true }));
    m->addDockWidget(dock1, Location_OnLeft);
    dock1->close();
    m->layout()->checkSanity();

    QVERIFY(!dock1->dptr()->group());
    QVERIFY(!Platform::instance()->tests_waitForDeleted(dock1)); // It was being deleted due to a
                                                                 // bug
    QVERIFY(dock1);
    dock1->open();
    m->layout()->checkSanity();
}

void TestDocks::tst_close()
{
    EnsureTopLevelsDeleted e;

    // 1.0 Call QWidget::close() on QDockWidget
    auto dock1 = createDockWidget("doc1");
    QAction *toggleAction = dock1->toggleAction();
    QVERIFY(toggleAction->isChecked());

    QVERIFY(dock1->close());

    QVERIFY(!dock1->isVisible());
    QVERIFY(!dock1->window()->controller()->isVisible());
    QVERIFY(dock1->window()->equals(dock1->view()));
    QVERIFY(!toggleAction->isChecked());

    // 1.1 Reshow with show()
    dock1->open();
    auto fw = dock1->floatingWindow();
    QVERIFY(fw);
    QVERIFY(toggleAction->isChecked());
    QVERIFY(dock1->isVisible());
    QVERIFY(dock1->window()->equals(fw->view()));
    QVERIFY(toggleAction->isChecked());

    // 1.2 Reshow with toggleAction instead
    QVERIFY(dock1->close());
    QVERIFY(!toggleAction->isChecked());
    QVERIFY(!dock1->isVisible());
    toggleAction->setChecked(true);
    QVERIFY(dock1->isVisible());

    // 1.3 Use hide() instead
    auto fw1 = dock1->floatingWindow();
    QVERIFY(fw1);

    dock1->close();

    QVERIFY(Platform::instance()->tests_waitForDeleted(fw1));
    QVERIFY(!dock1->isVisible());
    QVERIFY(!dock1->window()->controller()->isVisible());
    QVERIFY(dock1->window()->equals(dock1->view()));
    QVERIFY(!toggleAction->isChecked());

    // 1.4 close a FloatingWindow, via DockWidget::close
    QPointer<Core::FloatingWindow> window = dock1->dptr()->morphIntoFloatingWindow();
    QPointer<Core::Group> group1 = dock1->dptr()->group();
    QVERIFY(dock1->isVisible());
    QVERIFY(dock1->window()->controller()->isVisible());
    QVERIFY(group1->isVisible());
    QVERIFY(dock1->window()->equals(window->view()));

    QVERIFY(dock1->close());
    QVERIFY(!dock1->dptr()->group());
    QVERIFY(Platform::instance()->tests_waitForDeleted(group1));
    QVERIFY(Platform::instance()->tests_waitForDeleted(window));

    // 1.5 close a FloatingWindow, via FloatingWindow::close
    dock1->open();

    window = dock1->dptr()->morphIntoFloatingWindow();
    group1 = dock1->dptr()->group();
    QVERIFY(dock1->isVisible());
    QVERIFY(dock1->window()->controller()->isVisible());
    QVERIFY(group1->isVisible());
    QVERIFY(dock1->window()->equals(window->view()));

    QVERIFY(window->view()->close());

    QVERIFY(!dock1->dptr()->group());
    QVERIFY(Platform::instance()->tests_waitForDeleted(group1));
    QVERIFY(Platform::instance()->tests_waitForDeleted(window));

    // 1.6 Check if space is reclaimed after closing left dock
    Core::DockWidget *centralDock;
    Core::DockWidget *leftDock;
    Core::DockWidget *rightDock;

    auto mainwindow = createSimpleNestedMainWindow(&centralDock, &leftDock, &rightDock);
    auto da = mainwindow->dropArea();

    QVERIFY(da->checkSanity());
    QCOMPARE(leftDock->dptr()->group()->view()->x(), 0);

    QCOMPARE(centralDock->dptr()->group()->view()->x(),
             leftDock->dptr()->group()->view()->geometry().right() + Item::separatorThickness + 1);
    QCOMPARE(rightDock->dptr()->group()->view()->x(),
             centralDock->dptr()->group()->view()->geometry().right() + Item::separatorThickness
                 + 1);
    leftDock->close();
    QTest::qWait(250);
    QCOMPARE(centralDock->dptr()->group()->view()->x(), 0);
    QCOMPARE(rightDock->dptr()->group()->view()->x(),
             centralDock->dptr()->group()->view()->geometry().right() + Item::separatorThickness
                 + 1);

    rightDock->close();
    QTest::qWait(250);
    QMargins margins = mainwindow->centerWidgetMargins();
    QCOMPARE(centralDock->dptr()->group()->view()->width(),
             mainwindow->width() - 0 * 2 - margins.left() - margins.right());
    delete leftDock;
    delete rightDock;
    delete centralDock;

    // 1.9 Close tabbed dock, side docks will maintain their position
    mainwindow = createSimpleNestedMainWindow(&centralDock, &leftDock, &rightDock);
    const int leftX = leftDock->dptr()->group()->view()->x();
    const int rightX = rightDock->dptr()->group()->view()->x();

    centralDock->close();

    QCOMPARE(leftDock->dptr()->group()->view()->x(), leftX);
    QCOMPARE(rightDock->dptr()->group()->view()->x(), rightX);
    delete leftDock;
    delete rightDock;
    delete centralDock;
    delete dock1;


    // 2. Test that closing the single group of a main window doesn't close the main window itself
    {
        auto m = createMainWindow(QSize(800, 500), MainWindowOption_None); // Remove central group
        QPointer<MainWindow> mainWindowPtr = m.get();
        dock1 = createDockWidget("hello");
        m->addDockWidget(dock1, Location_OnLeft);

        // 2.2 Closing should not close the main window
        dock1->close();
        QVERIFY(mainWindowPtr.data());
        delete dock1;
    }

    // 2.1 Test closing the group instead
    {
        auto m = createMainWindow(QSize(800, 500), MainWindowOption_None); // Remove central group
        QPointer<MainWindow> mainWindowPtr = m.get();
        dock1 = createDockWidget("hello");
        m->addDockWidget(dock1, Location_OnLeft);

        // 2.2 Closing should not close the main window
        dock1->dptr()->group()->titleBar()->onCloseClicked();
        QVERIFY(mainWindowPtr.data());
        QVERIFY(mainWindowPtr->isVisible());
        delete dock1;
    }

    // 2.2 Repeat, but with a central group
    {
        auto m = createMainWindow(QSize(800, 500));
        QPointer<MainWindow> mainWindowPtr = m.get();
        dock1 = createDockWidget("hello");
        m->addDockWidget(dock1, Location_OnLeft);

        // 2.2 Closing should not close the main window
        dock1->dptr()->group()->titleBar()->onCloseClicked();
        QVERIFY(mainWindowPtr.data());
        QVERIFY(mainWindowPtr->isVisible());
        delete dock1;
    }
}

void TestDocks::tst_positionWhenShown()
{
    // Tests that when showing a dockwidget it shows in the same position as before
    EnsureTopLevelsDeleted e;
    auto window = createMainWindow();
    auto dock1 = newDockWidget("1");
    dock1->open();
    QTest::qWait(1000); // Wait for group to settle
    const QPoint desiredPos = QPoint(100, 100);
    dock1->view()->window()->setFramePosition(desiredPos);
    QTest::qWait(1000); // Wait for group to settle
    QCOMPARE(dock1->view()->window()->framePosition(), desiredPos);

    dock1->close();
    dock1->open();
    QCOMPARE(dock1->view()->window()->framePosition(), desiredPos);

    // Cleanup
    window->layout()->checkSanity();
    dock1->deleteLater();
    QVERIFY(Platform::instance()->tests_waitForDeleted(dock1));
}

#include "tst_docks_main.h"

#include <tst_docks_slow3.moc>

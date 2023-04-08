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
#include "kddockwidgets/controllers/MDILayout.h"
#include "kddockwidgets/controllers/DropArea.h"
#include "kddockwidgets/controllers/MainWindow.h"
#include "kddockwidgets/controllers/DockWidget.h"
#include "kddockwidgets/controllers/DockWidget_p.h"
#include "kddockwidgets/controllers/Separator.h"
#include "kddockwidgets/controllers/TabBar.h"
#include "kddockwidgets/controllers/Stack.h"
#include "kddockwidgets/controllers/SideBar.h"

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
        KDDockWidgets::Platform::instance()->installMessageHandler();
    }

    void cleanupTestCase()
    {
        KDDockWidgets::Platform::instance()->uninstallMessageHandler();
    }

private Q_SLOTS:
    void tst_invalidLayoutAfterRestore();
    void tst_setFloatingWhenSideBySide();
    void tst_dockWindowWithTwoSideBySideFramesIntoCenter();
    void tst_dockWindowWithTwoSideBySideFramesIntoRight();
    void tst_dockWindowWithTwoSideBySideFramesIntoLeft();
};

void TestDocks::tst_invalidLayoutAfterRestore()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow();
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
    auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));
    auto dock3 = createDockWidget("dock3", Platform::instance()->tests_createView({ true }));
    auto dropArea = m->dropArea();
    Core::DropArea *layout = dropArea;
    // Stack 1, 2, 3
    m->addDockWidget(dock1, Location_OnLeft);
    m->addDockWidget(dock2, Location_OnRight);
    m->addDockWidget(dock3, Location_OnRight);

    const int oldContentsWidth = layout->layoutWidth();

    auto f1 = dock1->dptr()->group();
    dock3->close();
    dock2->close();
    dock1->close();
    QVERIFY(Platform::instance()->tests_waitForDeleted(f1));

    dock3->open();
    dock2->open();
    dock1->open();
    Platform::instance()->tests_waitForEvent(m.get(), Event::LayoutRequest); // So MainWindow min
                                                                             // size is updated

    Item *item1 = layout->itemForFrame(dock1->dptr()->group());
    Item *item3 = layout->itemForFrame(dock3->dptr()->group());
    Item *item4 = dropArea->centralFrame();

    QCOMPARE(layout->count(), 4);
    QCOMPARE(layout->placeholderCount(), 0);

    // Detach dock2
    QPointer<Core::Group> f2 = dock2->dptr()->group();
    f2->detachTab(dock2);
    QVERIFY(!f2.data());
    QTest::qWait(200); // Not sure why. Some event we're waiting for. TODO: Investigate
    auto fw2 = dock2->floatingWindow();
    QCOMPARE(layout->view()->minSize().width(),
             2 * Item::separatorThickness + item1->minSize().width() + item3->minSize().width()
                 + item4->minSize().width());

    // Drop left of dock3
    layout->addWidget(fw2->dropArea()->view(), Location_OnLeft, dock3->dptr()->group());

    QVERIFY(Platform::instance()->tests_waitForDeleted(fw2));
    QCOMPARE(layout->layoutWidth(), oldContentsWidth);
    layout->checkSanity();
}

void TestDocks::tst_setFloatingWhenSideBySide()
{
    // Tests DockWidget::setFloating(false|true) when side-by-side (it should put it where it was)
    EnsureTopLevelsDeleted e;

    {
        // 1. Create a MainWindow with two docked dock-widgets, then float the first one.
        auto m = createMainWindow();
        auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
        auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));
        m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
        m->addDockWidget(dock2, KDDockWidgets::Location_OnRight);

        QPointer<Core::Group> group1 = dock1->dptr()->group();
        dock1->setFloating(true);
        QVERIFY(dock1->isFloating());
        auto fw = dock1->floatingWindow();
        QVERIFY(fw);

        // 2. Put it back, via setFloating(). It should return to its place.
        dock1->setFloating(false);

        QVERIFY(!dock1->isFloating());
        QVERIFY(!dock1->isTabbed());

        Platform::instance()->tests_waitForDeleted(fw);
    }

    {
        // 2. Tests a case where restoring a dock widget wouldn't make it use all its available
        // space
        auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }));
        auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }));
        auto dock3 = createDockWidget("dock3", Platform::instance()->tests_createView({ true }));
        auto dropArea = m->dropArea();
        Core::DropArea *layout = dropArea;
        m->addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
        m->addDockWidget(dock2, KDDockWidgets::Location_OnRight);
        m->addDockWidget(dock3, KDDockWidgets::Location_OnRight);
        auto f2 = dock2->dptr()->group();
        Item *item2 = layout->itemForFrame(f2);
        QVERIFY(item2);
        dock2->close();
        dock3->close();
        Platform::instance()->tests_waitForDeleted(f2);
        dock2->open();
        Platform::instance()->tests_waitForResize(dock2->view());

        QCOMPARE(item2->geometry(), dock2->dptr()->group()->view()->geometry());
        layout->checkSanity();

        // Cleanup
        dock3->deleteLater();
        Platform::instance()->tests_waitForDeleted(dock3);
    }
}

void TestDocks::tst_dockWindowWithTwoSideBySideFramesIntoCenter()
{
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setInternalFlags(KDDockWidgets::Config::InternalFlag_NoAeroSnap);
    KDDockWidgets::Config::self().setFlags({});

    auto m = createMainWindow();
    auto fw = createFloatingWindow();
    auto dock2 = createDockWidget("doc2");
    nestDockWidget(dock2, fw->dropArea(), nullptr, KDDockWidgets::Location_OnLeft);
    QCOMPARE(fw->groups().size(), 2);
    QVERIFY(fw->dropArea()->checkSanity());

    auto fw2 = createFloatingWindow();
    fw2->view()->move(fw->x() + fw->width() + 100, fw->y());

    // QtQuick is a bit more async than QWidgets. Wait for the move.
    Platform::instance()->tests_waitForEvent(fw2->view()->window(), Event::Move);

    auto da2 = fw2->dropArea();
    const QPoint dragDestPos = da2->mapToGlobal(da2->rect().center());

    dragFloatingWindowTo(fw, dragDestPos);
    QVERIFY(fw2->dropArea()->checkSanity());

    QCOMPARE(fw2->groups().size(), 1);
    auto f2 = fw2->groups().constFirst();
    QCOMPARE(f2->dockWidgetCount(), 3);
    QVERIFY(Platform::instance()->tests_waitForDeleted(fw));
    delete fw2;
}

void TestDocks::tst_dockWindowWithTwoSideBySideFramesIntoRight()
{
    EnsureTopLevelsDeleted e;

    auto fw = createFloatingWindow();
    auto dock2 = createDockWidget("doc2");
    nestDockWidget(dock2, fw->dropArea(), nullptr,
                   KDDockWidgets::Location_OnTop); // No we stack on top, unlike in previous test
    QCOMPARE(fw->groups().size(), 2);

    auto fw2 = createFloatingWindow();
    fw2->view()->move(fw->x() + fw->width() + 100, fw->y());

    dragFloatingWindowTo(fw, fw2->dropArea(), DropLocation_Right); // Outer right instead of Left
    QCOMPARE(fw2->groups().size(), 3);
    QVERIFY(fw2->dropArea()->checkSanity());

    fw2->deleteLater();
    Platform::instance()->tests_waitForDeleted(fw2);
}

void TestDocks::tst_dockWindowWithTwoSideBySideFramesIntoLeft()
{
    EnsureTopLevelsDeleted e;

    auto fw = createFloatingWindow();
    fw->setObjectName("fw1");

    auto dock2 = createDockWidget("doc2");
    nestDockWidget(dock2, fw->dropArea(), nullptr, KDDockWidgets::Location_OnLeft);
    QCOMPARE(fw->groups().size(), 2);

    auto fw2 = createFloatingWindow();
    fw2->setObjectName("fw2");
    fw2->view()->move(fw->x() + fw->width() + 100, fw->y());

    QVERIFY(fw2->dropArea()->checkSanity());
    dragFloatingWindowTo(fw, fw2->dropArea(), DropLocation_Left);
    QCOMPARE(fw2->groups().size(), 3);

    QVERIFY(fw2->dropArea()->checkSanity());

    /// Cleanup
    fw2->deleteLater();
    Platform::instance()->tests_waitForDeleted(fw2);
}

#include "tst_docks_main.h"

#include <tst_docks_slow2.moc>

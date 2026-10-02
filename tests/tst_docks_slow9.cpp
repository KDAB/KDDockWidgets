/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

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

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;
using namespace KDDockWidgets::Tests;

class TestDocks : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void tst_invalidAnchorGroup();
    void tst_addToSmallMainWindow4();
    void tst_constraintsAfterPlaceholder();
    void tst_resizeInLayout();
    void tst_keepLast();
};

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

#define KDDW_TEST_NAME TestDocks
#include "test_main_qt.h"

#include "tst_docks_slow9.moc"

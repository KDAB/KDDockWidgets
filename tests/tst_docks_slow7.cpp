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

#include <QtTest/QtTest>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Controllers;
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
    void tst_dragByTabBar();
    void tst_dragByTabBar_data();
};

void TestDocks::tst_dragByTabBar_data()
{
    QTest::addColumn<bool>("documentMode");
    QTest::addColumn<bool>("tabsAlwaysVisible");

    QTest::newRow("false-false") << false << false;
    QTest::newRow("true-false") << true << false;
    QTest::newRow("false-true") << false << true;
    QTest::newRow("true-true") << true << true;
}

static int osWindowMinWidth()
{
#ifdef Q_OS_WIN
    return GetSystemMetrics(SM_CXMIN);
#else
    return 140; // Some random value for our windows. It's only important on Windows
#endif
}

void TestDocks::tst_dragByTabBar()
{
    QFETCH(bool, documentMode);
    QFETCH(bool, tabsAlwaysVisible);

    EnsureTopLevelsDeleted e;
    auto flags = KDDockWidgets::Config::self().flags()
        | KDDockWidgets::Config::Flag_HideTitleBarWhenTabsVisible;
    if (tabsAlwaysVisible)
        flags |= KDDockWidgets::Config::Flag_AlwaysShowTabs;

    KDDockWidgets::Config::self().setFlags(flags);

    auto m = createMainWindow();

    auto dropArea = m->dropArea();
    auto dock1 = createDockWidget(
        "dock1", Platform::instance()->tests_createView({ true, {}, QSize(400, 400) }));

    auto dock2 = createDockWidget(
        "dock2", Platform::instance()->tests_createView({ true, {}, QSize(400, 400) }));
    auto dock3 = createDockWidget(
        "dock3", Platform::instance()->tests_createView({ true, {}, QSize(400, 400) }));
    m->addDockWidgetAsTab(dock1);
    m->view()->resize(QSize(osWindowMinWidth(), 200));

    dock2->addDockWidgetAsTab(dock3);
    if (documentMode)
        dock2->dptr()->group()->stack()->setDocumentMode(true);

    auto fw = dock2->floatingWindow();
    fw->view()->move(m->pos() + QPoint(500, 500));
    QVERIFY(fw->isVisible());
    QVERIFY(!fw->titleBar()->isVisible());

    dragFloatingWindowTo(fw, dropArea, DropLocation_Right);
}

int main(int argc, char *argv[])
{
    int exitCode = 0;
    for (FrontendType type : Platform::frontendTypes()) {
        qDebug() << "\nTesting platform" << type << ":\n";
        KDDockWidgets::Platform::tests_initPlatform(argc, argv, type);

        TestDocks test;

        const int code = QTest::qExec(&test, argc, argv);
        if (code != 0)
            exitCode = 1;
        KDDockWidgets::Platform::tests_deinitPlatform();
    }

    return exitCode;
}

#include <tst_docks_slow7.moc>

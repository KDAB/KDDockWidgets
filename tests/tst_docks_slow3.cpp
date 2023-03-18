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
    void tst_dockWidgetGetsFocusWhenDocked();
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
    QPointer<Controllers::FloatingWindow> fw2 = dw2->floatingWindow();

    // Focus dock widget 1 first
    QVERIFY(!dw1->isFocused());
    dw1->window()->activateWindow();

    connect(
        dw1, &Controllers::DockWidget::isFocusedChanged, dw1, [dw1](bool focused) {
            Q_ASSERT(focused == dw1->isFocused());
        });

    le1->setFocus(Qt::MouseFocusReason);
    QTest::qWait(200);
    QVERIFY(dw1->isFocused());

    QVERIFY(fw1->view()->isActiveWindow());
    dragFloatingWindowTo(fw2, fw1->dropArea(), DropLocation_Left);
    Platform::instance()->tests_waitForEvent(fw1, QEvent::WindowActivate);

    /// We dropped into floating window 1, it should still be active
    QVERIFY(fw1->view()->isActiveWindow());

    // DockWidget 2 was dropped, it should now be focused
    QVERIFY(!dw1->isFocused());
    QVERIFY(dw2->isFocused());

    delete fw1;
    delete fw2;
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

#include <tst_docks_slow3.moc>

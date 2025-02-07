/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "core/FloatingWindow.h"
#include "core/Group.h"
#include "core/TitleBar.h"
#include "core/DockWidget.h"
#include "core/ViewFactory.h"
#include "core/Platform.h"
#include "core/ObjectGuard_p.h"
#include "Config.h"
#include "tests/utils.h"

#include <QTest>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;

class TestFloatingWindow : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void tst_floatingWindowCtor();
    void tst_floatingWindowClose();
};

void TestFloatingWindow::tst_floatingWindowCtor()
{
    Tests::EnsureTopLevelsDeleted ensure;

    auto dw = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();
    QVERIFY(dw->view()->rootView()->is(ViewType::DockWidget));
    QVERIFY(!dw->view()->parentView());

    dw->view()->show();
    QVERIFY(dw->view()->parentView());
    QVERIFY(dw->view()->rootView()->is(ViewType::FloatingWindow));

    QVERIFY(dw->floatingWindow());

    /// Wait for FloatingWindow to be created
    QTest::qWait(100);

    auto rootView = dw->view()->rootView();
    QVERIFY(rootView);

    QVERIFY(rootView->is(ViewType::FloatingWindow));
    QVERIFY(rootView->controller());
    QVERIFY(rootView->controller()->is(ViewType::FloatingWindow));
    QVERIFY(rootView->controller()->isVisible());

    Core::FloatingWindow *fw = dw->floatingWindow();
    QVERIFY(fw);
    QVERIFY(fw->view()->equals(rootView));
}

void TestFloatingWindow::tst_floatingWindowClose()
{
    // Tests that a floating window is deleted after being closed

    auto dw = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();
    dw->view()->show();
    ObjectGuard<Core::FloatingWindow> fw = dw->floatingWindow();
    QVERIFY(fw);

    auto titleBar = fw->titleBar();
    QVERIFY(titleBar);
    QVERIFY(titleBar->isVisible());
    QCOMPARE(fw->groups().length(), 1);
    QVERIFY(!fw->groups().first()->titleBar()->isVisible());
    titleBar->onCloseClicked();
    QVERIFY(!dw->isOpen());
    QVERIFY(Platform::instance()->tests_waitForDeleted(fw));
    QVERIFY(!fw);

    delete dw;
}

#define KDDW_TEST_NAME TestFloatingWindow
#include "../test_main_qt.h"

#include "tst_floatingwindow.moc"

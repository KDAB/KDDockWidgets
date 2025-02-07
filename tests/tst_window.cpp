/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// There's a benign warning:
// Group.qml:221: ReferenceError: parent is not defined
#define KDDW_TESTS_NO_FATAL_WARNINGS

#include "core/View_p.h"
#include "core/Platform.h"
#include "core/Window_p.h"
#include "utils.h"

#include <QTest>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;

class TestWindow : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void tst_windowCtor();
    void tst_setVisible();
    void tst_handle();
    void tst_resize();
    void tst_activate();
    void tst_equals();
    void tst_geometry();
};

void TestWindow::tst_windowCtor()
{
    auto window = Platform::instance()->tests_createWindow();
    QVERIFY(window);
    QVERIFY(window->isVisible());

    window->destroy();
}

void TestWindow::tst_setVisible()
{
    auto window = Platform::instance()->tests_createWindow();
    QVERIFY(window);
    QVERIFY(window->isVisible());

    window->setVisible(false);
    QVERIFY(!window->isVisible());

    window->setVisible(true);
    QVERIFY(window->isVisible());

    window->destroy();
}

void TestWindow::tst_handle()
{
    auto window = Platform::instance()->tests_createWindow();
    QVERIFY(window->handle());
    window->destroy();
}

void TestWindow::tst_resize()
{
    auto window = Platform::instance()->tests_createWindow();
    const KDDockWidgets::Size newSize(501, 502);
    window->resize(newSize.width(), newSize.height());

    EVENT_LOOP(100);

    QCOMPARE(window->size(), newSize);

    window->destroy();
}

void TestWindow::tst_activate()
{
    auto window = Platform::instance()->tests_createWindow();
    // QVERIFY(window->isActive());

    // TODO

    window->destroy();
}

void TestWindow::tst_equals()
{
    auto window1 = Platform::instance()->tests_createWindow();
    auto window2 = Platform::instance()->tests_createWindow();

    QVERIFY(window1->equals(window1));
    QVERIFY(!window1->equals(window2));
    QVERIFY(!window1->equals({}));

    window1->destroy();
    window2->destroy();
}

void TestWindow::tst_geometry()
{
    auto window = Platform::instance()->tests_createWindow();

    const auto geo = KDDockWidgets::Rect(100, 100, 1000, 1000);
    window->setGeometry(geo);

    EVENT_LOOP(100);
    QCOMPARE(window->geometry(), geo);

    window->destroy();
}

#define KDDW_TEST_NAME TestWindow
#include "test_main_qt.h"

#include "tst_window.moc"

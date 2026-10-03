/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "core/View_p.h"
#include "core/ViewFactory.h"
#include "core/Platform.h"
#include "Config.h"
#include "core/DockRegistry.h"
#include "core/FloatingWindow.h"
#include "core/Window_p.h"
#include "utils.h"

#include <QTest>
#include <string>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;

class TestPlatform : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void tst_platform();
    void tst_name();
    void tst_createDefaultViewFactory();
    void tst_startDragDistance();
    void tst_windows();
    void tst_mouseCursor();
    void tst_floatingWindowForHandle();
};

void TestPlatform::tst_platform()
{
    auto plat = Platform::instance();
    QVERIFY(plat);
}

void TestPlatform::tst_name()
{
    // Checks that Platform::name() returns something
    auto plat = Platform::instance();
    QVERIFY(!std::string(plat->name()).empty());
}

void TestPlatform::tst_createDefaultViewFactory()
{
    auto plat = Platform::instance();
    ViewFactory *vf = plat->createDefaultViewFactory();
    QVERIFY(vf);
    delete vf;
}

void TestPlatform::tst_startDragDistance()
{
    auto plat = Platform::instance();
    const int defaultDistance = plat->startDragDistance();
    QVERIFY(defaultDistance >= -1);

    const int newDistance = defaultDistance + 1;
    KDDockWidgets::Config::self().setStartDragDistance(newDistance);
    QCOMPARE(plat->startDragDistance(), newDistance);
}

void TestPlatform::tst_windows()
{
    auto plat = Platform::instance();
    QVERIFY(plat->primaryScreen());
    QVERIFY(!plat->hasActivePopup());

    auto window = plat->tests_createWindow();
    bool found = false;
    for (const auto &w : plat->windows()) {
        if (w->equals(window))
            found = true;
    }
    QVERIFY(found);
    QVERIFY(plat->screenNumberForWindow(window) >= 0);

    window->destroy();
}

void TestPlatform::tst_mouseCursor()
{
    // Just checks that it doesn't crash, and that the stack is balanced
    auto plat = Platform::instance();
    plat->setMouseCursor(Qt::SizeHorCursor);
    plat->setMouseCursor(Qt::SizeVerCursor, /*discardLast=*/true);
    plat->restoreMouseCursor();
    plat->restoreMouseCursor();
}

void TestPlatform::tst_floatingWindowForHandle()
{
    Tests::EnsureTopLevelsDeleted e;
    auto fw = Tests::createFloatingWindow();
    auto window = fw->view()->window();
    QVERIFY(window);

    auto registry = DockRegistry::self();
    QCOMPARE(registry->floatingWindowForHandle(window), fw);
    QCOMPARE(registry->floatingWindowForHandle(window->handle()), fw);

    auto other = Platform::instance()->tests_createWindow();
    QVERIFY(!registry->floatingWindowForHandle(other));
    other->destroy();

    delete fw;
}

#define KDDW_TEST_NAME TestPlatform
#include "test_main_qt.h"

#include "tst_platform.moc"

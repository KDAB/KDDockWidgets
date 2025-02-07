/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Waqar Ahmed <waqar.ahmed@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "core/ViewGuard.h"
#include "core/ObjectGuard_p.h"
#include "core/Platform.h"

#include <QTest>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;

class TestGuards : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void tst_viewGuard();
    void tst_objectGuard();
};

void TestGuards::tst_viewGuard()
{
    ViewGuard g(nullptr);
    QVERIFY(g.isNull());

    {
        auto view = Platform::instance()->tests_createView({});
        g = view;
        QVERIFY(!g.isNull());
        delete view;
    }

    QVERIFY(g.isNull());

    // Test when ViewGuard is destroyed before view
    // May not crash without ASAN
    auto view = Platform::instance()->tests_createView({});
    {
        ViewGuard gg(view);
        QVERIFY(!gg.isNull());
    }
    delete view;
}

void TestGuards::tst_objectGuard()
{
    {
        ObjectGuard<Controller> guard;
        QVERIFY(!guard);
        QVERIFY(guard.isNull());
        QVERIFY(guard.data() == nullptr);
    }

    {
        auto c = new Controller(ViewType::DockWidget, nullptr);
        ObjectGuard<Controller> guard(c);
        QVERIFY(guard);
        QVERIFY(!guard.isNull());
        QVERIFY(guard.data() != nullptr);

        delete c;
        QVERIFY(!guard);
        QVERIFY(guard.isNull());
        QVERIFY(guard.data() == nullptr);

        auto c2 = new Controller(ViewType::DockWidget, nullptr);

        // Test assignment
        guard = c2;
        QVERIFY(guard);
        QVERIFY(!guard.isNull());
        QVERIFY(guard.data() != nullptr);

        delete c2;
        QVERIFY(!guard);
        QVERIFY(guard.isNull());
        QVERIFY(guard.data() == nullptr);
    }
}

#define KDDW_TEST_NAME TestGuards
#include "test_main_qt.h"

#include "tst_viewguard.moc"

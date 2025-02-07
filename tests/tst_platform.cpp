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

#define KDDW_TEST_NAME TestPlatform
#include "test_main_qt.h"

#include "tst_platform.moc"

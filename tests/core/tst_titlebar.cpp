/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "core/TitleBar.h"
#include "core/Group.h"
#include "core/View.h"

#include <QTest>

using namespace KDDockWidgets;

class TestTitleBar : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void tst_titleBarCtor();
};

void TestTitleBar::tst_titleBarCtor()
{
    auto group = new Core::Group(nullptr, {});
    auto tb = new Core::TitleBar(group);
    QVERIFY(tb->view()->is(Core::ViewType::TitleBar));
    QVERIFY(tb->view()->asWrapper()->is(Core::ViewType::TitleBar));
    delete tb;
    delete group;
}

#define KDDW_TEST_NAME TestTitleBar
#include "../test_main_qt.h"

#include "tst_titlebar.moc"

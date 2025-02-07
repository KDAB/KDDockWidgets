/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "core/Group.h"
#include "core/View.h"
#include "kddockwidgets/Config.h"

#include <QTest>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;

class TestGroup : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void tst_groupCtor();
    void tst_dragRect();
};

void TestGroup::tst_groupCtor()
{
    auto group = new Core::Group(nullptr, {});
    QVERIFY(group->view()->is(Core::ViewType::Group));
    QVERIFY(group->view()->asWrapper()->is(Core::ViewType::Group));
    delete group;
}

void TestGroup::tst_dragRect()
{
    auto group = new Core::Group(nullptr, {});
    // This used to crash. Test that it doesn't.
    group->dragRect();
    delete group;
}

#define KDDW_TEST_NAME TestGroup
#include "../test_main_qt.h"

#include "tst_group.moc"

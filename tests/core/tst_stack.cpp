/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "core/Group.h"
#include "core/Stack.h"
#include "core/View.h"

#include <QTest>

using namespace KDDockWidgets;

class TestStack : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void tst_stackCtor();
};

void TestStack::tst_stackCtor()
{
    Core::Group group(nullptr, {});
    Core::Stack stack(&group, {});
    QVERIFY(stack.view()->is(Core::ViewType::Stack));
    QVERIFY(stack.view()->asWrapper()->is(Core::ViewType::Stack));
}

#define KDDW_TEST_NAME TestStack
#include "../test_main_qt.h"

#include "tst_stack.moc"

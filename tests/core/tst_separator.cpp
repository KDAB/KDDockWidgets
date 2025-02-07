/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "core/Separator.h"
#include "core/DropArea.h"

#include <QTest>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;

class TestSeparator : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void tst_separatorCtor();
};

void TestSeparator::tst_separatorCtor()
{
    Core::DropArea dropArea(nullptr, MainWindowOption_None);
    Core::Separator separator(dropArea.asLayoutingHost(), Qt::Vertical, nullptr);
    QVERIFY(separator.view()->is(Core::ViewType::Separator));
    QVERIFY(separator.view()->asWrapper()->is(Core::ViewType::Separator));
}

#define KDDW_TEST_NAME TestSeparator
#include "../test_main_qt.h"

#include "tst_separator.moc"

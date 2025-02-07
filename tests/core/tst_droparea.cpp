/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "../utils.h"
#include "core/DropArea.h"
#include "core/Group.h"
#include "Config.h"
#include "core/DockWidget.h"
#include "core/ViewFactory.h"
#include "core/Platform.h"

#include <QTest>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;

class TestDropArea : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void tst_dropAreaCtor();
    void tst_addWidget();
    void tst_addWidgetHidden();
};

void TestDropArea::tst_dropAreaCtor()
{
    // Tests that ctor runs and doesn't leak
    Core::DropArea da(nullptr, {});
}

void TestDropArea::tst_addWidget()
{
    auto group = new Core::Group();
    Core::DropArea da(nullptr, {});
    da.addWidget(group->view(), KDDockWidgets::Location_OnLeft);
}

void TestDropArea::tst_addWidgetHidden()
{
    // Test adding a widget that starts hidden

    auto dw = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();
    Core::DropArea da(nullptr, {});
    da.addDockWidget(dw, KDDockWidgets::Location_OnLeft, nullptr,
                     InitialVisibilityOption::StartHidden);

    QVERIFY(!dw->isOpen());
    QVERIFY(!dw->toggleAction()->isChecked());
    dw->open();
    QVERIFY(dw->isOpen());
    QVERIFY(dw->toggleAction()->isChecked());

    auto group = dw->dptr()->group();
    delete dw;
    WAIT_FOR_DELETED(group);
}

#define KDDW_TEST_NAME TestDropArea
#include "../test_main_qt.h"

#include "tst_droparea.moc"

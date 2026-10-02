/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "utils.h"
#include "Config.h"
#include "core/Position_p.h"
#include "core/WindowBeingDragged_p.h"
#include "core/LayoutSaver_p.h"
#include "core/layouting/Item_p.h"
#include "core/ViewFactory.h"
#include "core/MDILayout.h"
#include "core/DropArea.h"
#include "core/MainWindow.h"
#include "core/DockWidget.h"
#include "core/DockWidget_p.h"
#include "core/Separator.h"
#include "core/TabBar.h"
#include "core/Stack.h"
#include "core/SideBar.h"

#include <QTest>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;
using namespace KDDockWidgets::Tests;

class TestDocks : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void tst_invalidPlaceholderPosition2();
    void tst_startHidden3();
    void tst_keepLast();
};

void TestDocks::tst_invalidPlaceholderPosition2()
{
    checkInvalidPlaceholderPosition(false);
}

void TestDocks::tst_startHidden3()
{
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }), {},
                                  {}, false);
    auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }), {},
                                  {}, false);
    auto dock3 = createDockWidget("dock3", Platform::instance()->tests_createView({ true }), {},
                                  {}, false);

    auto dropArea = m->dropArea();
    Core::DropArea *layout = dropArea;
    m->addDockWidget(dock1, Location_OnLeft, nullptr, InitialVisibilityOption::StartHidden);

    m->addDockWidget(dock2, Location_OnBottom, nullptr, InitialVisibilityOption::StartHidden);
    m->addDockWidget(dock3, Location_OnRight, nullptr, InitialVisibilityOption::StartHidden);

    dock1->open();

    QCOMPARE(layout->count(), 3);
    QCOMPARE(layout->placeholderCount(), 2);

    dock2->open();
    dock3->open();
    WAIT_FOR_RESIZE(dock2->view());
    layout->checkSanity();
}

void TestDocks::tst_keepLast()
{
    // 1 event loop for DelayedDelete. Avoids LSAN warnings.
    QTest::qWait(1);
}

#define KDDW_TEST_NAME TestDocks
#include "test_main_qt.h"

#include "tst_docks_slow10.moc"

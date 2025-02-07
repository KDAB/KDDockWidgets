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
    void tst_invalidPlaceholderPosition();
    void tst_startHidden();
    void tst_startHidden2();
    void tst_invalidJSON();
    void tst_keepLast();
};

void TestDocks::tst_invalidPlaceholderPosition()
{
    auto func = [](bool restore1First) {
        // Tests a bug I saw: 3 widgets stacked, close the top one, then the second top one
        // result: the bottom most one didn't have it's top separator at y=0

        EnsureTopLevelsDeleted e;
        auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }));
        auto dock2 = createDockWidget("2", Platform::instance()->tests_createView({ true }));
        auto dock3 = createDockWidget("3", Platform::instance()->tests_createView({ true }));

        Core::DropArea *layout = m->multiSplitter();

        // Stack: 1, 2, 3 vertically
        m->addDockWidget(dock3, Location_OnTop);
        m->addDockWidget(dock2, Location_OnTop);
        m->addDockWidget(dock1, Location_OnTop);

        auto group1 = dock1->dptr()->group();
        auto group2 = dock2->dptr()->group();
        auto group3 = dock3->dptr()->group();
        QCOMPARE(group1->view()->y(), 0);

        // Close 1
        QVERIFY(dock1->isOpen());
        QVERIFY(dock1->view()->isVisible());
        dock1->close();
        QVERIFY(!dock1->isOpen());
        QVERIFY(!dock1->view()->isVisible());

        WAIT_FOR_RESIZE(group2->view());

        // Check that group2 moved up to y=0
        QCOMPARE(group2->view()->y(), 0);

        // Close 2
        dock2->close();
        WAIT_FOR_RESIZE(dock3->view());

        QVERIFY(layout->checkSanity());
        QCOMPARE(layout->count(), 3);
        QCOMPARE(layout->placeholderCount(), 2);

        // Check that group3 moved up to y=1
        QCOMPARE(group3->view()->y(), 0);

        // Now restore:
        auto toRestore1 = restore1First ? dock1 : dock2;
        auto toRestore2 = restore1First ? dock2 : dock1;

        toRestore1->open();
        QCOMPARE(layout->placeholderCount(), 1);
        QVERIFY(dock3->isVisible());
        QVERIFY(!dock3->size().isNull());

        toRestore2->open();

        WAIT_FOR_RESIZE(group3->view());
        QVERIFY(layout->checkSanity());
        QCOMPARE(layout->count(), 3);
        QCOMPARE(layout->placeholderCount(), 0);
        layout->checkSanity();

        dock1->destroyLater();
        dock2->destroyLater();

        QVERIFY(Platform::instance()->tests_waitForDeleted(dock2));
    };

    func(true);
    func(false);
}

void TestDocks::tst_startHidden()
{
    // A really simple test for InitialVisibilityOption::StartHidden
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
    auto dock1 = createDockWidget("1", Platform::instance()->tests_createView({ true }), {}, {},
                                  /*show=*/false);
    m->addDockWidget(dock1, Location_OnRight, nullptr, InitialVisibilityOption::StartHidden);
    delete dock1;
}

void TestDocks::tst_startHidden2()
{
    EnsureTopLevelsDeleted e;
    {
        auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
        auto dock1 = createDockWidget("dock1", Platform::instance()->tests_createView({ true }), {},
                                      {}, false);
        auto dock2 = createDockWidget("dock2", Platform::instance()->tests_createView({ true }), {},
                                      {}, false);

        auto dropArea = m->dropArea();
        Core::DropArea *layout = dropArea;

        m->addDockWidget(dock1, Location_OnTop, nullptr, InitialVisibilityOption::StartHidden);
        QVERIFY(layout->checkSanity());

        QCOMPARE(layout->count(), 1);
        QCOMPARE(layout->placeholderCount(), 1);

        m->addDockWidget(dock2, Location_OnTop);
        QVERIFY(layout->checkSanity());

        QCOMPARE(layout->count(), 2);
        QCOMPARE(layout->placeholderCount(), 1);

        dock1->open();

        QCOMPARE(layout->count(), 2);
        QCOMPARE(layout->placeholderCount(), 0);

        WAIT_FOR_RESIZE(dock2->view());
    }

    {
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
}

void TestDocks::tst_invalidJSON()
{
    auto func = [](QString layoutFileName, int numDockWidgets, std::string expectedWarning, bool expectedResult) {
        const QString absoluteLayoutFileName = resourceFileName(QStringLiteral("layouts/") + layoutFileName);

        EnsureTopLevelsDeleted e;
        auto m1 = createMainWindow(Size(800, 500), MainWindowOption_None, "MyMainWindow1");
        for (int i = 0; i < numDockWidgets; ++i) {
            createDockWidget(QString("dock-") + QString::number(i),
                             Platform::instance()->tests_createView({ true }));
        }

        SetExpectedWarning sew(expectedWarning);

        LayoutSaver restorer;
        QCOMPARE(restorer.restoreFromFile(absoluteLayoutFileName), expectedResult);
    };

    func("unsupported-serialization-version.json", 10, "Serialization format is too old", false);
    func("invalid.json", 29, "", false);
    func("overlapping-item.json", 2, "Unexpected pos", true);
}

void TestDocks::tst_keepLast()
{
    // 1 event loop for DelayedDelete. Avoids LSAN warnings.
    QTest::qWait(1);
}

#define KDDW_TEST_NAME TestDocks
#include "test_main_qt.h"

#include "tst_docks_slow1.moc"

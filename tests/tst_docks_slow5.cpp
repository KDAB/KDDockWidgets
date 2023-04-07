/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// We don't care about performance related checks in the tests
// clazy:excludeall=ctor-missing-parent-argument,missing-qobject-macro,range-loop,missing-typeinfo,detaching-member,function-args-by-ref,non-pod-global-static,reserve-candidates,qstring-allocations

// A test that was extracted out from tst_docks.cpp as it was too slow
// By using a separate executable it can be paralellized by ctest.

#include "utils.h"
#include "Config.h"
#include "LayoutSaver_p.h"
#include "Position_p.h"
#include "WindowBeingDragged_p.h"
#include "Platform.h"
#include "multisplitter/Item_p.h"
#include "kddockwidgets/ViewFactory.h"
#include "Action.h"
#include "kddockwidgets/controllers/MDILayout.h"
#include "kddockwidgets/controllers/DropArea.h"
#include "kddockwidgets/controllers/MainWindow.h"
#include "kddockwidgets/controllers/DockWidget.h"
#include "kddockwidgets/controllers/DockWidget_p.h"
#include "kddockwidgets/controllers/Separator.h"
#include "kddockwidgets/controllers/TabBar.h"
#include "kddockwidgets/controllers/Stack.h"
#include "kddockwidgets/controllers/SideBar.h"

#include <QtTest/QTest>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Controllers;
using namespace Layouting;
using namespace KDDockWidgets::Tests;

class TestDocks : public QObject
{
    Q_OBJECT

public Q_SLOTS:
    void initTestCase()
    {
        KDDockWidgets::Platform::instance()->installMessageHandler();
    }

    void cleanupTestCase()
    {
        KDDockWidgets::Platform::instance()->uninstallMessageHandler();
    }

private Q_SLOTS:
    void tst_28NestedWidgets();
    void tst_28NestedWidgets_data();
};

void TestDocks::tst_28NestedWidgets_data()
{
    QTest::addColumn<QVector<DockDescriptor>>("docksToCreate");
    QTest::addColumn<QVector<int>>("docksToHide");

    QVector<DockDescriptor> docks = {
        { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnTop, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible }
    };
    if (Platform::instance()->isQtWidgets())
        QTest::newRow("28") << docks << QVector<int> { 11, 0 };

    docks = {
        { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnTop, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartVisible },

    };

    QVector<int> docksToHide;
    for (int i = 0; i < docks.size(); ++i) {
        docksToHide << i;
    }

    QTest::newRow("anchor_intersection") << docks << docksToHide;

    docks = {
        { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnTop, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
    };
    if (Platform::instance()->isQtWidgets()) {
        // 2. Produced valgrind invalid reads while adding
        QTest::newRow("valgrind") << docks << QVector<int> {};
    }
    docks = {
        { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnTop, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
    };
    if (Platform::instance()->isQtWidgets())
        QTest::newRow("bug_when_closing") << docks << QVector<int> {}; // Q_ASSERT(!isSquashed())

    docks = {
        { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartVisible },
    };
    if (Platform::instance()->isQtWidgets())
        QTest::newRow("bug_when_closing2")
            << docks
            << QVector<int> {}; // Tests for void KDDockWidgets::Anchor::setPosition(int,
                                // KDDockWidgets::Anchor::SetPositionOptions) Negative position -69

    docks = { { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnTop, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible } };

    docksToHide.clear();
    for (int i = 0; i < 28; ++i) {
        if (i != 16 && i != 17 && i != 18 && i != 27)
            docksToHide << i;
    }
    if (Platform::instance()->isQtWidgets())
        QTest::newRow("bug_with_holes") << docks << docksToHide;

    docks = { { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnTop, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnLeft, 17, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible } };

    docksToHide.clear();
    QTest::newRow("add_as_placeholder") << docks << docksToHide;

    docks = { { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden } };

    QTest::newRow("add_as_placeholder_simple") << docks << docksToHide;


    docks = { { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden } };

    docksToHide.clear();
    QTest::newRow("isSquashed_assert") << docks << docksToHide;

    docks = { { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnTop, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden } };

    docksToHide.clear();
    QTest::newRow("negative_pos_warning") << docks << docksToHide;

    docks = { { Location_OnTop, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible } };

    docksToHide.clear();
    QTest::newRow("bug") << docks << docksToHide;

    docks = { { Location_OnTop, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible } };

    docksToHide.clear();
    QTest::newRow("bug2") << docks << docksToHide;

    docks = { { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnTop, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible } };

    docksToHide.clear();
    QTest::newRow("bug3") << docks << docksToHide;
}

void TestDocks::tst_28NestedWidgets()
{
    QFETCH(QVector<DockDescriptor>, docksToCreate);
    QFETCH(QVector<int>, docksToHide);

    // Tests a case that used to cause negative anchor position when turning into placeholder
    EnsureTopLevelsDeleted e;
    auto m = createMainWindow(QSize(800, 500), MainWindowOption_None);
    auto dropArea = m->dropArea();
    Controllers::DropArea *layout = dropArea;

    int i = 0;
    for (DockDescriptor &desc : docksToCreate) {
        desc.createdDock = createDockWidget(
            QString("%1").arg(i), Platform::instance()->tests_createView({ true }), {}, {}, false);

        Controllers::DockWidget *relativeTo = nullptr;
        if (desc.relativeToIndex != -1)
            relativeTo = docksToCreate.at(desc.relativeToIndex).createdDock;
        m->addDockWidget(desc.createdDock, desc.loc, relativeTo, desc.option);
        QVERIFY(layout->checkSanity());
        ++i;
    }

    layout->checkSanity();

    // Run the saver in these complex scenarios:
    LayoutSaver saver;
    const QByteArray saved = saver.serializeLayout();
    QVERIFY(!saved.isEmpty());
    QVERIFY(saver.restoreLayout(saved));

    layout->checkSanity();

    for (int i : docksToHide) {
        docksToCreate.at(i).createdDock->close();
        layout->checkSanity();
        QTest::qWait(200);
    }

    layout->checkSanity();

    for (int i : docksToHide) {
        docksToCreate.at(i).createdDock->deleteLater();
        QVERIFY(Platform::instance()->tests_waitForDeleted(docksToCreate.at(i).createdDock));
    }

    layout->checkSanity();

    // And hide the remaining ones
    i = 0;
    for (auto dock : docksToCreate) {
        if (dock.createdDock && dock.createdDock->isVisible()) {
            dock.createdDock->close();
            QTest::qWait(200); // Wait for the docks to be closed. TODO Replace with a global event
                               // filter and wait for any resize ?
        }
        ++i;
    }

    layout->checkSanity();

    // Cleanup
    for (auto dock : DockRegistry::self()->dockwidgets()) {
        dock->deleteLater();
        QVERIFY(Platform::instance()->tests_waitForDeleted(dock));
    }
}

#include "tst_docks_main.h"

#include <tst_docks_slow5.moc>

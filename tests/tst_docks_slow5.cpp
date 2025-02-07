/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "utils.h"
#include "Config.h"
#include "core/LayoutSaver_p.h"
#include "core/Position_p.h"
#include "core/ViewFactory.h"
#include "core/DropArea.h"
#include "core/MainWindow.h"
#include "core/DockWidget.h"
#include "core/Platform.h"

#include <QTest>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;
using namespace KDDockWidgets::Tests;

class TestDocks : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void tst_28NestedWidgets();
};

void TestDocks::tst_28NestedWidgets()
{
    auto func = [](Vector<DockDescriptor> docksToCreate, Vector<int> docksToHide) {
        // Tests a case that used to cause negative anchor position when turning into placeholder
        EnsureTopLevelsDeleted e;
        auto m = createMainWindow(Size(800, 500), MainWindowOption_None);
        auto dropArea = m->dropArea();
        Core::DropArea *layout = dropArea;

        int i = 0;
        for (DockDescriptor &desc : docksToCreate) {
            desc.createdDock = createDockWidget(
                QString::number(i), Platform::instance()->tests_createView({ true }), {}, {}, false);

            Core::DockWidget *relativeTo = nullptr;
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
            docksToCreate.at(i).createdDock->destroyLater();
            QVERIFY(Platform::instance()->tests_waitForDeleted(docksToCreate.at(i).createdDock));
        }

        layout->checkSanity();

        // And hide the remaining ones
        i = 0;
        for (const auto &dock : docksToCreate) {
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
            dock->destroyLater();
            QVERIFY(Platform::instance()->tests_waitForDeleted(dock));
        }
    };

    Vector<DockDescriptor> docks = {
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

    if (Platform::instance()->isQtWidgets()) {
        func(docks, Vector<int> { 11, 0 });
    }

    docks = {
        { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnTop, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartVisible },
    };

    Vector<int> docksToHide;
    for (int i = 0; i < docks.size(); ++i) {
        docksToHide.push_back(i);
    }

    func(docks, docksToHide);

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
        func(docks, {});
    }

    docks = {
        { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnTop, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
    };

    if (Platform::instance()->isQtWidgets()) {
        func(docks, {});
    }

    docks = {
        { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, 0, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartVisible },
    };
    if (Platform::instance()->isQtWidgets()) {
        // Tests for void KDDockWidgets::Anchor::setPosition(int,
        // KDDockWidgets::Anchor::SetPositionOptions) Negative position -69
        func(docks, {});
    }

    docks = {
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

    docksToHide.clear();
    for (int i = 0; i < 28; ++i) {
        if (i != 16 && i != 17 && i != 18 && i != 27)
            docksToHide.push_back(i);
    }
    if (Platform::instance()->isQtWidgets()) {
        // bug_with_holes
        func(docks, docksToHide);
    }

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

    // add_as_placeholder
    func(docks, docksToHide);

    docks = { { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden } };

    // add_as_placeholder_simple
    func(docks, docksToHide);

    docks = { { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden } };

    docksToHide.clear();

    // isSquashed_assert
    func(docks, docksToHide);

    docks = { { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnTop, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden } };

    docksToHide.clear();

    // negative_pos_warning
    func(docks, docksToHide);

    docks = { { Location_OnTop, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible } };

    docksToHide.clear();
    // bug
    func(docks, docksToHide);

    docks = { { Location_OnTop, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible } };

    docksToHide.clear();
    // bug2
    func(docks, docksToHide);

    docks = { { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnTop, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible } };

    docksToHide.clear();

    // bug3
    func(docks, docksToHide);
}

#define KDDW_TEST_NAME TestDocks
#include "test_main_qt.h"

#include "tst_docks_slow5.moc"

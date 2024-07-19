/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// We don't care about performance related checks in the tests
// clazy:excludeall=ctor-missing-parent-argument,missing-qobject-macro,range-loop,missing-typeinfo,detaching-member,function-args-by-ref,non-pod-global-static,reserve-candidates,qstring-allocations

// A test that was extracted out from tst_docks.cpp as it was too slow
// By using a separate executable it can be parallelized by ctest.

#include "utils.h"
#include "simple_test_framework.h"
#include "Config.h"
#include "core/LayoutSaver_p.h"
#include "core/Position_p.h"
#include "core/WindowBeingDragged_p.h"
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
#include "core/Platform.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;
using namespace KDDockWidgets::Tests;

KDDW_QCORO_TASK tst_28NestedWidgets()
{
    auto func = [](Vector<DockDescriptor> docksToCreate, Vector<int> docksToHide) -> KDDW_QCORO_TASK {
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
            CHECK(layout->checkSanity());
            ++i;
        }

        layout->checkSanity();

        // Run the saver in these complex scenarios:
        LayoutSaver saver;
        const QByteArray saved = saver.serializeLayout();
        CHECK(!saved.isEmpty());
        CHECK(saver.restoreLayout(saved));

        layout->checkSanity();

        for (int i : docksToHide) {
            docksToCreate.at(i).createdDock->close();
            layout->checkSanity();
            EVENT_LOOP(200);
        }

        layout->checkSanity();

        for (int i : docksToHide) {
            docksToCreate.at(i).createdDock->destroyLater();
            CHECK(KDDW_CO_AWAIT Platform::instance()->tests_waitForDeleted(docksToCreate.at(i).createdDock));
        }

        layout->checkSanity();

        // And hide the remaining ones
        i = 0;
        for (auto dock : docksToCreate) {
            if (dock.createdDock && dock.createdDock->isVisible()) {
                dock.createdDock->close();
                EVENT_LOOP(200); // Wait for the docks to be closed. TODO Replace with a global event
                                 // filter and wait for any resize ?
            }
            ++i;
        }

        layout->checkSanity();

        // Cleanup
        for (auto dock : DockRegistry::self()->dockwidgets()) {
            dock->destroyLater();
            CHECK(KDDW_CO_AWAIT Platform::instance()->tests_waitForDeleted(dock));
        }

        KDDW_TEST_RETURN(true);
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
        if (!KDDW_CO_AWAIT func(docks, Vector<int> { 11, 0 })) {
            KDDW_TEST_RETURN(false);
        }
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

    if (!KDDW_CO_AWAIT func(docks, docksToHide)) {
        KDDW_TEST_RETURN(false);
    }

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
        if (!KDDW_CO_AWAIT func(docks, {})) {
            KDDW_TEST_RETURN(false);
        }
    }

    docks = {
        { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnTop, -1, nullptr, InitialVisibilityOption::StartVisible },
        { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
    };

    if (Platform::instance()->isQtWidgets()) {
        if (!KDDW_CO_AWAIT func(docks, {})) {
            KDDW_TEST_RETURN(false);
        }
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
        if (!KDDW_CO_AWAIT func(docks, {})) {
            KDDW_TEST_RETURN(false);
        }
    }

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
            docksToHide.push_back(i);
    }
    if (Platform::instance()->isQtWidgets()) {
        // bug_with_holes
        if (!KDDW_CO_AWAIT func(docks, docksToHide)) {
            KDDW_TEST_RETURN(false);
        }
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
    if (!KDDW_CO_AWAIT func(docks, docksToHide)) {
        KDDW_TEST_RETURN(false);
    }

    docks = { { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden } };

    // add_as_placeholder_simple
    if (!KDDW_CO_AWAIT func(docks, docksToHide)) {
        KDDW_TEST_RETURN(false);
    }

    docks = { { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden } };

    docksToHide.clear();

    // isSquashed_assert
    if (!KDDW_CO_AWAIT func(docks, docksToHide)) {
        KDDW_TEST_RETURN(false);
    }

    docks = { { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnTop, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden } };

    docksToHide.clear();

    // negative_pos_warning
    if (!KDDW_CO_AWAIT func(docks, docksToHide)) {
        KDDW_TEST_RETURN(false);
    }

    docks = { { Location_OnTop, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible } };

    docksToHide.clear();
    // bug
    if (!KDDW_CO_AWAIT func(docks, docksToHide)) {
        KDDW_TEST_RETURN(false);
    }

    docks = { { Location_OnTop, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible } };

    docksToHide.clear();
    // bug2
    if (!KDDW_CO_AWAIT func(docks, docksToHide)) {
        KDDW_TEST_RETURN(false);
    }

    docks = { { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnTop, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnLeft, -1, nullptr, InitialVisibilityOption::StartVisible },
              { Location_OnBottom, -1, nullptr, InitialVisibilityOption::StartHidden },
              { Location_OnRight, -1, nullptr, InitialVisibilityOption::StartVisible } };

    docksToHide.clear();

    // bug3
    if (!KDDW_CO_AWAIT func(docks, docksToHide)) {
        KDDW_TEST_RETURN(false);
    }

    KDDW_TEST_RETURN(true);
}

static const auto s_tests = std::vector<KDDWTest> {
#if !defined(KDDW_FRONTEND_FLUTTER)
    TEST(tst_28NestedWidgets)
#endif
};


#include "tests_main.h"

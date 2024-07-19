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
#include "core/WindowBeingDragged_p.h"
#include "core/layouting/Item_p.h"
#include "core/Position_p.h"
#include "core/ViewFactory.h"
#include "core/LayoutSaver_p.h"
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

KDDW_QCORO_TASK tst_isFocused()
{
    {
        EnsureTopLevelsDeleted e;

        // 1. Create 2 floating windows
        auto dock1 = createDockWidget(QStringLiteral("dock1"),
                                      Platform::instance()->tests_createFocusableView({ true }));
        auto dock2 = createDockWidget(QStringLiteral("dock2"),
                                      Platform::instance()->tests_createFocusableView({ true }));

        EVENT_LOOP(400); // macOS is flaky here, needs dock2 to be shown first before focusing dock1,
                         // otherwise dock1 looses again

        dock1->window()->move(400, 200);

        // 2. Raise dock1 and focus its line edit
        dock1->raise();
        dock1->guestView()->setFocus(Qt::OtherFocusReason);
        WAIT_FOR_EVENT(dock1->guestView().get(), Event::FocusIn);

        CHECK(dock1->isFocused());
        CHECK(!dock2->isFocused());

        // 3. Raise dock2 and focus its line edit
        dock2->view()->raiseAndActivate();
        if (!dock2->window()->window()->isActive())
            WAIT_FOR_EVENT(dock2->view()->window(), Event::WindowActivate);

        dock2->guestView()->setFocus(Qt::OtherFocusReason);
        WAIT_FOR_EVENT(dock1->guestView().get(), Event::FocusIn);

        CHECK(!dock1->isFocused());
        CHECK(dock2->guestView()->hasFocus());
        CHECK(dock2->isFocused());

        // 4. Tab dock1, it's current tab now
        auto oldFw1 = dock1->window();
        dock2->addDockWidgetAsTab(dock1);
        CHECK(dock1->isFocused());
        CHECK(!dock2->isFocused());

        // 5. Set dock2 as current tab again
        dock2->raise();
        CHECK(!dock1->isFocused());
        CHECK(dock2->isFocused());

        // 6. Create dock3, focus it
        auto dock3 = createDockWidget(QStringLiteral("dock3"),
                                      Platform::instance()->tests_createFocusableView({ true }));
        auto oldFw3 = dock3->window();
        dock3->raise();
        dock3->guestView()->setFocus(Qt::OtherFocusReason);
        WAIT_FOR_EVENT(dock1->guestView().get(), Event::FocusIn);
        CHECK(!dock1->isFocused());
        CHECK(!dock2->isFocused());
        CHECK(dock3->isFocused());

        // 4. Add dock3 to the 1st window, nested, focus 2 again
        dock2->addDockWidgetToContainingWindow(dock3, Location_OnLeft);
        dock2->raise();
        dock2->guestView()->setFocus(Qt::OtherFocusReason);
        WAIT_FOR_EVENT(dock2->guestView().get(), Event::FocusIn);
        CHECK(!dock1->isFocused());
        CHECK(dock2->isFocused());
        CHECK(!dock3->isFocused());
    }

    // Spin one event loop so we so some deleteLater()s run. Makes LSAN happy.
    EVENT_LOOP(1000);

    KDDW_CO_RETURN(true);
}

static const auto s_tests = std::vector<KDDWTest> {
#if !defined(KDDW_FRONTEND_FLUTTER)
    TEST(tst_isFocused)
#endif
};

#include "tests_main.h"

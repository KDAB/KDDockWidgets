/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "../simple_test_framework.h"
#include "../utils.h"
#include "core/DockWidget.h"
#include "core/FloatingWindow.h"
#include "core/DockWidget_p.h"
#include "core/Group.h"
#include "core/Platform.h"
#include "core/TitleBar.h"
#include "core/ViewFactory.h"
#include "core/Window_p.h"
#include "Config.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;

KDDW_QCORO_TASK tst_dockWidgetCtor()
{
    Tests::EnsureTopLevelsDeleted e;

    auto dw = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();
    CHECK(dw->view()->is(ViewType::DockWidget));
    CHECK(dw->view()->asWrapper()->is(ViewType::DockWidget));
    dw->view()->show();

    delete dw;

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_setGuestView()
{
    Tests::EnsureTopLevelsDeleted e;

    auto dw = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();
    CHECK(Platform::instance());
    auto childView = Platform::instance()->tests_createView({ true });
    CHECK(childView);
    auto guest = childView->asWrapper();
    CHECK(guest);
    dw->setGuestView(guest);
    CHECK(dw->guestView());
    CHECK(dw->view());
    dw->view()->show();
    EVENT_LOOP(500);

    CHECK(guest->controller());
    CHECK(dw->floatingWindow());
    CHECK(dw->floatingWindow()->isVisible());
    CHECK(dw->isVisible());
    CHECK(guest->isVisible());
    CHECK(guest->controller()->isVisible());
    CHECK(dw->guestView()->equals(guest));
    CHECK(dw->view()->window());
    CHECK(guest->window());

    CHECK(guest->parentView());
    CHECK(guest->parentView()->equals(dw->view()));
    CHECK(dw->view()->rootView()->equals(guest->rootView()));
    CHECK(dw->view()->window()->equals(guest->window()));

    delete dw;

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_toggleAction()
{
    Tests::EnsureTopLevelsDeleted e;

    auto dw = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();

    CHECK(!dw->toggleAction()->isChecked());
    CHECK(dw->toggleAction()->isEnabled());

    delete dw;

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_isOpen()
{
    Tests::EnsureTopLevelsDeleted e;

    auto dw = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();

    // Starts closed
    CHECK(!dw->isOpen());

    dw->open();
    CHECK(dw->isOpen());
    CHECK(dw->isFloating());

    // close() closes
    dw->close();
    CHECK(!dw->isOpen());

    // Dockwidget in a non-current tab is not visible, but still counts as open
    dw->open();
    CHECK(dw->d->group());
    CHECK(dw->isOpen());
    CHECK(dw->isFloating());
    auto dw2 = Config::self().viewFactory()->createDockWidget("dw2")->asDockWidgetController();
    CHECK(dw->isCurrentTab());
    dw->addDockWidgetAsTab(dw2);
    CHECK(dw2->isOpen());
    dw2->setAsCurrentTab();
    CHECK(!dw->isCurrentTab());
    CHECK(dw2->isCurrentTab());
    CHECK(dw->isOpen());
    CHECK(dw2->isOpen());

    delete dw;
    delete dw2;

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_setAsCurrentTab()
{
    Tests::EnsureTopLevelsDeleted e;

    auto dw = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();
    auto dw2 = Config::self().viewFactory()->createDockWidget("dw2")->asDockWidgetController();
    auto dw3 = Config::self().viewFactory()->createDockWidget("dw3")->asDockWidgetController();

    CHECK(dw->view());
    dw->view()->show();
    CHECK(dw->d->group());
    CHECK(dw->isOpen());

    dw->addDockWidgetAsTab(dw2);
    dw->addDockWidgetAsTab(dw3);
    dw->setAsCurrentTab();

    CHECK(dw->isCurrentTab());
    CHECK(!dw2->isCurrentTab());
    CHECK(!dw3->isCurrentTab());

    Core::Group *group = dw->d->group();
    CHECK_EQ(group->currentIndex(), 0);
    CHECK_EQ(group->currentDockWidget(), dw);

    delete dw;
    delete dw2;
    delete dw3;


    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_dwCloseAndReopen()
{
    {
        Tests::EnsureTopLevelsDeleted e;

        // Tests that a floating window is deleted after being closed

        auto dw = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();
        dw->view()->show();
        ObjectGuard<Core::FloatingWindow> fw = dw->floatingWindow();
        CHECK(fw);

        auto titleBar = fw->titleBar();
        CHECK(titleBar);
        CHECK(titleBar->isVisible());
        titleBar->onCloseClicked();
        CHECK(!dw->isOpen());
        CHECK(KDDW_CO_AWAIT Platform::instance()->tests_waitForDeleted(fw));
        CHECK(!fw);

        CHECK(!dw->floatingWindow());
        CHECK(!dw->view()->parentView());
        dw->open();

        delete dw;
    }

    // 1 event loop for DelayedDelete. Avoids LSAN warnings.
    EVENT_LOOP(1);

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_setSize()
{
    {
        Tests::EnsureTopLevelsDeleted e;
        auto dw = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();
        const Size size = Size(501, 502);
        dw->view()->setSize(size);
        CHECK_EQ(dw->view()->size(), size);
    }

    // 1 event loop for DelayedDelete. Avoids LSAN warnings.
    EVENT_LOOP(1);

    KDDW_TEST_RETURN(true);
}

static const auto s_tests = std::vector<KDDWTest> {
    TEST(tst_dockWidgetCtor),
    TEST(tst_toggleAction),
    TEST(tst_setGuestView),
    TEST(tst_isOpen),
    TEST(tst_setAsCurrentTab),
    TEST(tst_dwCloseAndReopen),
    TEST(tst_setSize),
};

#include "../tests_main.h"

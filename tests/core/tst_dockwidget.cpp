/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "../simple_test_framework.h"
#include "kddockwidgets/core/DockWidget.h"
#include "kddockwidgets/core/FloatingWindow.h"
#include "kddockwidgets/core/DockWidget_p.h"
#include "kddockwidgets/core/Group.h"
#include "kddockwidgets/core/Platform.h"
#include "kddockwidgets/core/TitleBar.h"
#include "kddockwidgets/core/Action.h"
#include "kddockwidgets/core/ViewFactory.h"
#include "kddockwidgets/core/Platform.h"
#include "kddockwidgets/core/Window.h"
#include "Config.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;

KDDW_QCORO_TASK tst_dockWidgetCtor()
{
    auto dw = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();
    CHECK(dw->view()->is(ViewType::DockWidget));
    CHECK(dw->view()->asWrapper()->is(ViewType::DockWidget));
    dw->view()->show();

    delete dw;

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_setGuestView()
{
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
    Platform::instance()->tests_wait(500); // TODOm3: Replace with wait for visible or so.

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
    auto dw = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();

    CHECK(!dw->toggleAction()->isChecked());
    CHECK(dw->toggleAction()->isEnabled());
    CHECK(dw->toggleAction()->isCheckable());

    delete dw;

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_isOpen()
{
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
    // Tests that a floating window is deleted after being closed

    auto dw = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();
    dw->view()->show();
    QPointer<Core::FloatingWindow> fw = dw->floatingWindow();
    CHECK(fw);

    auto titleBar = fw->titleBar();
    CHECK(titleBar);
    CHECK(titleBar->isVisible());
    qDebug() << "CLOSING";
    titleBar->onCloseClicked();
    CHECK(!dw->isOpen());
    CHECK(KDDW_CO_AWAIT Platform::instance()->tests_waitForDeleted2(fw));
    CHECK(!fw);

    CHECK(!dw->floatingWindow());
    CHECK(!dw->view()->parentView());
    qDebug() << "OPENING";
    dw->open();

    // KDDW_CO_AWAIT Platform::instance()->tests_wait(100000);

    delete dw;
    KDDW_TEST_RETURN(true);
}

static const auto s_tests = std::vector<std::function<KDDW_QCORO_TASK()>> {
    tst_dockWidgetCtor,
    tst_toggleAction,
    tst_setGuestView,
    tst_isOpen,
    tst_setAsCurrentTab,
    tst_dwCloseAndReopen,
};

#include "../tests_main.h"

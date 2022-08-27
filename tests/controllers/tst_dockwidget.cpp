/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "../main.h"
#include "kddockwidgets/controllers/DockWidget.h"
#include "kddockwidgets/controllers/DockWidget_p.h"
#include "kddockwidgets/controllers/Group.h"
#include "Action.h"
#include "kddockwidgets/ViewFactory.h"
#include "Config.h"
#include "Platform.h"

TEST_CASE("DockWidget Ctor")
{
    auto dw = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();
    CHECK(dw->view()->is(Type::DockWidget));
    CHECK(dw->view()->asWrapper()->is(Type::DockWidget));
    dw->view()->show();

    delete dw;
}

TEST_CASE("setGuestView")
{
    auto dw = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();
    auto guest = Platform::instance()->tests_createView({ true })->asWrapper();
    dw->setGuestView(guest);
    dw->view()->show();
    Platform::instance()->tests_wait(500); // TODOm3: Replace with wait for visible or so.

    CHECK(guest->controller()->isVisible());
    CHECK(dw->guestView()->equals(guest));
    REQUIRE(dw->view()->window());
    REQUIRE(guest->window());
    CHECK(dw->view()->window()->equals(guest->window()));

    delete dw;
}

TEST_CASE("toggleAction")
{
    auto dw = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();

    CHECK(!dw->toggleAction()->isChecked());
    CHECK(dw->toggleAction()->isEnabled());
    CHECK(dw->toggleAction()->isCheckable());

    delete dw;
}

TEST_CASE("isOpen")
{
    auto dw = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();

    // Starts closed
    CHECK(!dw->isOpen());

    // show() makes it open
    dw->show();
    CHECK(dw->isOpen());
    CHECK(dw->isFloating());

    // close() closes
    dw->close();
    CHECK(!dw->isOpen());

    // Dockwidget in a non-current tab is not visible, but still counts as open
    dw->show();
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
}

TEST_CASE("setAsCurrentTab")
{
    auto dw = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();
    auto dw2 = Config::self().viewFactory()->createDockWidget("dw2")->asDockWidgetController();
    auto dw3 = Config::self().viewFactory()->createDockWidget("dw3")->asDockWidgetController();

    dw->view()->show();

    dw->addDockWidgetAsTab(dw2);
    dw->addDockWidgetAsTab(dw3);
    dw->setAsCurrentTab();

    CHECK(dw->isCurrentTab());
    CHECK(!dw2->isCurrentTab());
    CHECK(!dw3->isCurrentTab());

    Controllers::Group *group = dw->d->group();
    CHECK_EQ(group->currentIndex(), 0);
    CHECK_EQ(group->currentDockWidget(), dw);

    delete dw;
    delete dw2;
    delete dw3;
}

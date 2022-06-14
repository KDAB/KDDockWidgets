/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "../main.h"
#include "kddockwidgets/controllers/DockWidget.h"
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

    CHECK(guest->isVisible());
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
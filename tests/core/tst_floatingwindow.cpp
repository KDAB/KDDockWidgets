/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "../main.h"
#include "kddockwidgets/core/FloatingWindow.h"
#include "kddockwidgets/core/Group.h"
#include "kddockwidgets/core/DockWidget.h"
#include "kddockwidgets/core/ViewFactory.h"
#include "Config.h"

using namespace KDDockWidgets::Core;

TEST_CASE("FloatingWindow Ctor")
{
    auto dw = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();
    CHECK(dw->view()->rootView()->is(Type::DockWidget));
    dw->view()->show();

    /// Wait for FloatingWindow to be created
    Platform::instance()->tests_wait(100);

    auto rootView = dw->view()->rootView();
    REQUIRE(rootView);

    CHECK(rootView->is(Type::FloatingWindow));
    REQUIRE(rootView->controller());
    CHECK(rootView->controller()->is(Type::FloatingWindow));
    CHECK(rootView->controller()->isVisible());

    Core::FloatingWindow *fw = dw->floatingWindow();
    REQUIRE(fw);
    CHECK(fw->view()->equals(rootView));

    delete dw;
}

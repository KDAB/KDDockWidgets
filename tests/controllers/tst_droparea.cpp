/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "../main.h"
#include "controllers/DropArea.h"
#include "controllers/Group.h"
#include "Platform.h"
#include "Config.h"
#include "kddockwidgets/controllers/DockWidget.h"
#include "kddockwidgets/ViewFactory.h"
#include "Action.h"

TEST_CASE("DropArea CTOR")
{
    // Tests that ctor runs and doesn't leak
    Controllers::DropArea da(nullptr, {});
}

TEST_CASE("DropArea::addWidget")
{
    auto group = new Controllers::Group();
    Controllers::DropArea da(nullptr, {});
    da.addWidget(group->view(), KDDockWidgets::Location_OnLeft);
}

TEST_CASE("DropArea::addWidget hidden")
{
    // Test adding a widget that starts hidden

    auto dw = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();
    Controllers::DropArea da(nullptr, {});
    da.addDockWidget(dw, KDDockWidgets::Location_OnLeft, nullptr,
                     InitialVisibilityOption::StartHidden);

    CHECK(!dw->isOpen());
    CHECK(!dw->toggleAction()->isChecked());
    dw->open();
    CHECK(dw->isOpen());
    CHECK(dw->toggleAction()->isChecked());

    delete dw;
}

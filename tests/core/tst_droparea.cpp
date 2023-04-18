/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "../main.h"
#include "core/DropArea.h"
#include "core/Group.h"
#include "Config.h"
#include "kddockwidgets/core/DockWidget.h"
#include "kddockwidgets/core/ViewFactory.h"
#include "kddockwidgets/core/Platform.h"
#include "kddockwidgets/core/Action.h"

TEST_CASE("DropArea CTOR")
{
    // Tests that ctor runs and doesn't leak
    Core::DropArea da(nullptr, {});
}

TEST_CASE("DropArea::addWidget")
{
    auto group = new Core::Group();
    Core::DropArea da(nullptr, {});
    da.addWidget(group->view(), KDDockWidgets::Location_OnLeft);
}

TEST_CASE("DropArea::addWidget hidden")
{
    // Test adding a widget that starts hidden

    auto dw = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();
    Core::DropArea da(nullptr, {});
    da.addDockWidget(dw, KDDockWidgets::Location_OnLeft, nullptr,
                     InitialVisibilityOption::StartHidden);

    CHECK(!dw->isOpen());
    CHECK(!dw->toggleAction()->isChecked());
    dw->open();
    CHECK(dw->isOpen());
    CHECK(dw->toggleAction()->isChecked());

    delete dw;
}

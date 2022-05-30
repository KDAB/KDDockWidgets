/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "../main.h"
#include "controllers/DockWidget.h"
#include "ViewFactory.h"
#include "Config.h"

TEST_CASE("DockWidget Ctor")
{
    auto dw = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();
    CHECK(dw->view()->is(Type::DockWidget));
    CHECK(dw->view()->asWrapper()->is(Type::DockWidget));
    dw->view()->show();

    delete dw;
}

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "../main.h"
#include "kddockwidgets/controllers/Group.h"
#include "kddockwidgets/controllers/Stack.h"
#include "kddockwidgets/controllers/TabBar.h"

TEST_CASE("TabBar ctor")
{
    Controllers::Group group(nullptr, {});
    Controllers::Stack stack(&group, {});
    Controllers::TabBar tabBar(&stack);
    CHECK(tabBar.view()->is(Type::TabBar));
    CHECK(tabBar.view()->asWrapper()->is(Type::TabBar));
}

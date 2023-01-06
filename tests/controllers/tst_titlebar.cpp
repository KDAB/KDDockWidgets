/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "../main.h"
#include "kddockwidgets/controllers/TitleBar.h"
#include "kddockwidgets/controllers/Group.h"

TEST_CASE("TitleBar Ctor")
{
    auto group = new Controllers::Group(nullptr, {});
    auto tb = new Controllers::TitleBar(group);
    CHECK(tb->view()->is(Type::TitleBar));
    CHECK(tb->view()->asWrapper()->is(Type::TitleBar));
    delete tb;
    delete group;
}

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "../main.h"
#include "kddockwidgets/core/TitleBar.h"
#include "kddockwidgets/core/Group.h"

TEST_CASE("TitleBar Ctor")
{
    auto group = new Core::Group(nullptr, {});
    auto tb = new Core::TitleBar(group);
    CHECK(tb->view()->is(Core::Type::TitleBar));
    CHECK(tb->view()->asWrapper()->is(Core::Type::TitleBar));
    delete tb;
    delete group;
}

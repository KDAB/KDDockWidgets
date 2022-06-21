/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "../main.h"
#include "kddockwidgets/controllers/Group.h"

TEST_CASE("Group ctor")
{
    auto frame = new Controllers::Group(nullptr, {});
    CHECK(frame->view()->is(Type::Frame));
    CHECK(frame->view()->asWrapper()->is(Type::Frame));
    delete frame;
}

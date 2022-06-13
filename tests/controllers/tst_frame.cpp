/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "../main.h"
#include "kddockwidgets/controllers/Frame.h"

TEST_CASE("Frame ctor")
{
    auto frame = new Controllers::Frame(nullptr, {});
    CHECK(frame->view()->is(Type::Frame));
    CHECK(frame->view()->asWrapper()->is(Type::Frame));
    delete frame;
}

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "../main.h"
#include "kddockwidgets/core/Group.h"
#include "kddockwidgets/core/Stack.h"

TEST_CASE("Stack ctor")
{
    Core::Group group(nullptr, {});
    Core::Stack stack(&group, {});
    CHECK(stack.view()->is(Core::Type::Stack));
    CHECK(stack.view()->asWrapper()->is(Core::Type::Stack));
}

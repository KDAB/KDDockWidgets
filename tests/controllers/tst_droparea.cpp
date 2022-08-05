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

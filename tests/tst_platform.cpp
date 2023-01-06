/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "main.h"
#include "private/View_p.h"
#include <kddockwidgets/ViewFactory.h>
#include "Platform.h"
#include "Config.h"

#include <string>

TEST_CASE("Platform::Platform")
{
    auto plat = Platform::instance();
    REQUIRE(plat);
}

TEST_CASE("Platform::name")
{
    // Checks that Platform::name() returns something
    auto plat = Platform::instance();
    CHECK(!std::string(plat->name()).empty());
}

TEST_CASE("Platform::createDefaultViewFactory")
{
    auto plat = Platform::instance();
    ViewFactory *vf = plat->createDefaultViewFactory();
    REQUIRE(vf);
    delete vf;
}

TEST_CASE("Platform::startDragDistance")
{
    auto plat = Platform::instance();
    const int defaultDistance = plat->startDragDistance();
    CHECK_GE(defaultDistance, -1);

    const int newDistance = defaultDistance + 1;
    Config::self().setStartDragDistance(newDistance);
    CHECK_EQ(plat->startDragDistance(), newDistance);
}

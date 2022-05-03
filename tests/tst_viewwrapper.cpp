/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "main.h"

TEST_CASE("ViewWrapper::setParent")
{
    auto r = Platform::instance()->tests_createView({});
    auto rootView = r->asWrapper();
    REQUIRE(rootView);
    REQUIRE(!rootView->isNull());
    CHECK(rootView->childViews().isEmpty());

    auto c = Platform::instance()->tests_createView({}, r);
    auto childView = c->asWrapper();

    CHECK(!rootView->parentView());
    REQUIRE(childView->parentView());
    CHECK(childView->parentView()->equals(rootView));
    const auto children = rootView->childViews();

    REQUIRE_EQ(children.size(), 1);
    CHECK(children[0]->equals(childView));

    auto r2 = Platform::instance()->tests_createView({});
    auto rootView2 = r2->asWrapper();
    childView->setParent(r2);
    CHECK(childView->parentView()->equals(rootView2));
    CHECK(rootView->childViews().isEmpty());
    CHECK_EQ(rootView2->childViews().size(), 1);

    // Deleting a view will remove it from its parent
    delete c;
    CHECK(rootView2->childViews().isEmpty());

    delete r;
    delete r2;
}

TEST_CASE("ViewWrapper::minSize")
{
    const QSize sizeHint = {};
    const QSize minSize = { 201, 202 };
    auto rootView = Platform::instance()->tests_createView({ true, sizeHint, minSize })->asWrapper();
    CHECK_EQ(rootView->minSize(), minSize);
}

TEST_CASE("ViewWrapper::objectName")
{
    auto rootView = Platform::instance()->tests_createView({})->asWrapper();

    CHECK_EQ(rootView->objectName(), QString());
    const QString newName = QStringLiteral("name1");
    rootView->setObjectName(newName);
    CHECK_EQ(rootView->objectName(), newName);
}

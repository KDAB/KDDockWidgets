/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#define DOCTEST_CONFIG_IMPLEMENT

#include "Platform.h"

#include <doctest/doctest.h>
#include <QDebug>

using namespace KDDockWidgets;


TEST_CASE("View::setParent()")
{
    auto rootView = Platform::instance()->tests_createView();
    REQUIRE(rootView);
    REQUIRE(!rootView->isNull());
    CHECK(rootView->childViews().isEmpty());

    auto childView = Platform::instance()->tests_createView(rootView);

    CHECK(!rootView->parentView());
    REQUIRE(childView->parentView());
    CHECK(childView->parentView()->equals(rootView));
    const auto children = rootView->childViews();

    REQUIRE_EQ(children.size(), 1);
    CHECK(children[0]->equals(childView));

    auto rootView2 = Platform::instance()->tests_createView();
    childView->setParent(rootView2);
    CHECK(childView->parentView()->equals(rootView2));
    CHECK(rootView->childViews().isEmpty());
    CHECK_EQ(rootView2->childViews().size(), 1);

    // Deleting a view will remove it from its parent
    delete childView;
    CHECK(rootView2->childViews().isEmpty());

    delete rootView;
    delete rootView2;
}

TEST_CASE("View::isVisible(),show(),hide()")
{
    auto rootView = Platform::instance()->tests_createView();
    CHECK(!rootView->isVisible());

    rootView->setVisible(true);
    CHECK(rootView->isVisible());

    // Changing parent will make it hide
    auto view2 = Platform::instance()->tests_createView();
    view2->setVisible(true);
    CHECK(view2->isVisible());
    view2->setParent(rootView);
    CHECK(!view2->isVisible());

    view2->setVisible(true);

    // Hiding the parent should hide the children
    CHECK(view2->isVisible());
    CHECK(rootView->isVisible());
    rootView->setVisible(false);
    CHECK(!view2->isVisible());
    CHECK(!rootView->isVisible());

    // test show()
    rootView->show();
    CHECK(rootView->isVisible());
    CHECK(view2->isVisible());

    // test hide()
    rootView->hide();
    CHECK(!rootView->isVisible());
    CHECK(!view2->isVisible());

    delete rootView;
}

int main(int argc, char **argv)
{
    int exitCode = 0;

    doctest::Context ctx;
    ctx.setOption("abort-after", 1);
    ctx.applyCommandLine(argc, argv);
    ctx.setOption("no-breaks", true);

    for (FrontendType type : Platform::frontendTypes()) {

        Platform::tests_initPlatform(argc, argv, type);

        qDebug() << "\nStarting tests for Platform" << Platform::instance()->name();

        const int code = ctx.run();
        if (code != 0)
            exitCode = code;

        Platform::tests_deinitPlatform();
    }

    return exitCode;
}

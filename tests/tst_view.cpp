/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#define DOCTEST_CONFIG_IMPLEMENT

#include "Platform.h"
#include "Window.h"

#include <doctest/doctest.h>
#include <iostream>

using namespace KDDockWidgets;

std::ostream &operator<<(std::ostream &os, QSize size)
{
    os << QStringLiteral("QSize(%1x%2)").arg(size.width()).arg(size.height()).toStdString();
    return os;
}

std::ostream &operator<<(std::ostream &os, QPoint pt)
{
    os << QStringLiteral("QPoint(%1,%2)").arg(pt.x()).arg(pt.y()).toStdString();
    return os;
}

std::ostream &operator<<(std::ostream &os, QRect r)
{
    os << QStringLiteral("QRect(%1,%2 %3x%4)").arg(r.x()).arg(r.y()).arg(r.width()).arg(r.height()).toStdString();
    return os;
}

TEST_CASE("View::setParent()")
{
    auto rootView = Platform::instance()->tests_createView({});
    REQUIRE(rootView);
    REQUIRE(!rootView->isNull());
    CHECK(rootView->childViews().isEmpty());

    auto childView = Platform::instance()->tests_createView({}, rootView);

    CHECK(!rootView->parentView());
    REQUIRE(childView->parentView());
    CHECK(childView->parentView()->equals(rootView));
    const auto children = rootView->childViews();

    REQUIRE_EQ(children.size(), 1);
    CHECK(children[0]->equals(childView));

    auto rootView2 = Platform::instance()->tests_createView({});
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

TEST_CASE("View::windowHandle,rootView,Window::rootView")
{
    auto rootView = Platform::instance()->tests_createView({});
    auto childView = Platform::instance()->tests_createView({ true }, rootView);

    auto window = rootView->window();
    REQUIRE(window);
    CHECK_EQ(window->handle(), childView->window()->handle());
    CHECK(rootView->rootView()->equals(rootView));
    CHECK(childView->rootView()->equals(rootView));

    REQUIRE(window->rootView());
    CHECK(window->rootView()->equals(rootView));
}

TEST_CASE("View::isVisible(),show(),hide()")
{
    auto rootView = Platform::instance()->tests_createView({});
    CHECK(!rootView->isVisible());

    rootView->setVisible(true);
    CHECK(rootView->isVisible());

    // Changing parent will make it hide
    auto view2 = Platform::instance()->tests_createView({});
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

TEST_CASE("View::geometry,pos,x,y,width,height,rect")
{
    // Test with a top-level view first
    auto rootView = Platform::instance()->tests_createView({});
    rootView->show();

    const QRect initialGeo = QRect(200, 201, 500, 501);
    rootView->setGeometry(initialGeo);
    CHECK_EQ(rootView->pos(), initialGeo.topLeft());

    Window::Ptr window = rootView->window();
    CHECK_EQ(window->geometry(), initialGeo);

    CHECK_EQ(rootView->size(), initialGeo.size());
    CHECK_EQ(rootView->x(), initialGeo.x());
    CHECK_EQ(rootView->y(), initialGeo.y());
    CHECK_EQ(rootView->width(), initialGeo.width());
    CHECK_EQ(rootView->height(), initialGeo.height());
    CHECK_EQ(rootView->rect(), QRect(QPoint(0, 0), initialGeo.size()));

    // Now test with child view
    auto childView = Platform::instance()->tests_createView({ true }, rootView);
    CHECK(childView->isVisible());
    const QRect newChildGeo(1, 2, 300, 301);
    childView->setGeometry(newChildGeo);

    Platform::instance()->tests_wait(500);

    CHECK(!childView->isRootView());
    CHECK_EQ(childView->size(), newChildGeo.size());
    CHECK_EQ(childView->x(), newChildGeo.x());
    CHECK_EQ(childView->geometry(), newChildGeo);
}

TEST_CASE("View::sizeHint")
{
    const QSize sizeHint = QSize(200, 200);
    auto rootView = Platform::instance()->tests_createView({ true, sizeHint });
    CHECK_EQ(rootView->sizeHint(), sizeHint);
}

TEST_CASE("View::minSize")
{
    const QSize sizeHint = {};
    const QSize minSize = { 201, 202 };
    auto rootView = Platform::instance()->tests_createView({ true, sizeHint, minSize });
    CHECK_EQ(rootView->minSize(), minSize);

    const QSize newMinSize = { 301, 302 };
    rootView->setMinimumSize(newMinSize);
    CHECK_EQ(rootView->minSize(), newMinSize);
}

int main(int argc, char **argv)
{
    int exitCode = 0;

    doctest::Context ctx;
    ctx.setOption("abort-after", 4);
    ctx.applyCommandLine(argc, argv);
    ctx.setOption("no-breaks", true);

    for (FrontendType type : Platform::frontendTypes()) {

        Platform::tests_initPlatform(argc, argv, type);

        std::cout << "\nStarting tests for Platform" << Platform::instance()->name() << "\n";

        const int code = ctx.run();
        if (code != 0)
            exitCode = code;

        Platform::tests_deinitPlatform();
    }

    return exitCode;
}

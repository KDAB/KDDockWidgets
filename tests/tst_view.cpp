/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "main.h"
#include "private/View_p.h"

TEST_CASE("View::setParent()")
{
    auto rootView = createViewAndWindow({});
    REQUIRE(rootView);
    REQUIRE(!rootView->isNull());
    CHECK(rootView->childViews().isEmpty());

    auto childView = createViewAndWindow({}, rootView);

    CHECK(!rootView->parentView());
    REQUIRE(childView->parentView());
    CHECK(childView->parentView()->equals(rootView));
    const auto children = rootView->childViews();

    REQUIRE_EQ(children.size(), 1);
    CHECK(children[0]->equals(childView));

    auto rootView2 = createViewAndWindow({});
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
    auto rootView = createViewAndWindow({});
    auto childView = createViewAndWindow({ true }, rootView);

    auto window = rootView->window();
    REQUIRE(window);
    CHECK_EQ(window->handle(), childView->window()->handle());
    CHECK(rootView->rootView()->equals(rootView));
    CHECK(childView->rootView()->equals(rootView));

    REQUIRE(window->rootView());
    CHECK(window->rootView()->equals(rootView));

    childView->setParent(nullptr);
    CHECK(childView->rootView()->equals(childView));
}

TEST_CASE("View::isVisible(),show(),hide()")
{
    auto rootView = createViewAndWindow({});
    CHECK(!rootView->controller()->isVisible());

    rootView->controller()->setVisible(true);
    CHECK(rootView->controller()->isVisible());

    // Hiding the parent should hide the children
    auto view2 = createViewAndWindow({});
    view2->setParent(rootView);
    view2->controller()->setVisible(true);
    CHECK(view2->controller()->isVisible());
    CHECK(rootView->controller()->isVisible());
    rootView->controller()->setVisible(false);
    CHECK(!view2->controller()->isVisible());
    CHECK(!rootView->controller()->isVisible());

    // test show()
    rootView->show();
    CHECK(rootView->controller()->isVisible());
    CHECK(view2->controller()->isVisible());

    // test hide()
    rootView->hide();
    CHECK(!rootView->controller()->isVisible());
    CHECK(!view2->controller()->isVisible());

    delete rootView;
}

TEST_CASE("View::geometry,pos,x,y,width,height,rect")
{
    // Test with a top-level view first
    auto rootView = createViewAndWindow({});
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
    auto childView = createViewAndWindow({ true }, rootView);
    CHECK(childView->controller()->isVisible());
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
    auto rootView = createViewAndWindow({ true, sizeHint });
    CHECK_EQ(rootView->sizeHint(), sizeHint);
}

TEST_CASE("View::minSize")
{
    const QSize sizeHint = {};
    const QSize minSize = { 201, 202 };
    auto rootView = createViewAndWindow({ true, sizeHint, minSize });
    CHECK_EQ(rootView->minSize(), minSize);

    const QSize newMinSize = { 301, 302 };
    rootView->setMinimumSize(newMinSize);
    CHECK_EQ(rootView->minSize(), newMinSize);
}

TEST_CASE("View::maxSize")
{
    const QSize sizeHint = {};
    const QSize minSize = { 201, 202 };
    const QSize maxSize = { 500, 501 };
    auto rootView = createViewAndWindow({ true, sizeHint, minSize, maxSize });
    CHECK_EQ(rootView->maxSizeHint(), maxSize);

    const QSize newMaxSize = { 301, 302 };
    rootView->setMaximumSize(newMaxSize);
    CHECK_EQ(rootView->maxSizeHint(), newMaxSize);
}

TEST_CASE("View::objectName")
{
    auto rootView = createViewAndWindow({});

    CHECK_EQ(rootView->objectName(), QString());
    const QString newName = QStringLiteral("name1");
    rootView->setObjectName(newName);
    CHECK_EQ(rootView->objectName(), newName);
}

TEST_CASE("View::closeRequested")
{
    // Tests that the closeRequested signal is emitted

    auto rootView = createViewAndWindow({});
    bool signalArrived = false;
    KDBindings::ScopedConnection connection =
        rootView->d->closeRequested.connect([&signalArrived](QCloseEvent *ev) {
            signalArrived = true;
            CHECK(ev->isAccepted());
        });

    rootView->close();
    CHECK(signalArrived);
}

TEST_CASE("View::focusPolicy, Platform::focusedView")
{
    auto rootView = createViewAndWindow({});
    CHECK_EQ(rootView->focusPolicy(), Qt::NoFocus);
}

TEST_CASE("View::hasFocus")
{
    auto rootView = createViewAndWindow({});
    rootView->show();
    rootView->activateWindow();

    CHECK(rootView->controller()->isVisible());
    Platform::instance()->tests_wait(0);
    CHECK(!rootView->hasFocus());

    rootView->setFocus(Qt::MouseFocusReason);
    Platform::instance()->tests_wait(200); // QWidget::setFocus() requires 1 event loop iteration
    CHECK(rootView->hasFocus());
    CHECK(rootView->equals(Platform::instance()->focusedView()));

    auto child1 = createViewAndWindow({}, rootView);
    CHECK(rootView->hasFocus());
    CHECK(rootView->equals(Platform::instance()->focusedView()));
    child1->controller()->setVisible(true);
    child1->setFocus(Qt::MouseFocusReason);
    Platform::instance()->tests_wait(200); // QWidget::setFocus() requires 1 event loop iteration
    CHECK(child1->hasFocus());
    CHECK(child1->equals(Platform::instance()->focusedView()));
}

TEST_CASE("View::operator qDebug")
{
    View *view = nullptr;
    qDebug() << "Null view=" << view;

    view = createViewAndWindow({});
    qDebug() << "rootView=" << view;
}

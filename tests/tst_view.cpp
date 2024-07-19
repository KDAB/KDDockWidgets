/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "simple_test_framework.h"
#include "core/Platform.h"
#include "core/Window_p.h"
#include "core/View_p.h"
#include "core/ViewGuard.h"

#include "clang_format18_workaround.h"

using namespace KDDockWidgets::Core;
using namespace KDDockWidgets;

inline Core::View *createViewAndWindow(Core::CreateViewOptions opts, Core::View *parent = nullptr)
{
    opts.createWindow = true;
    return Core::Platform::instance()->tests_createView(opts, parent);
}

KDDW_QCORO_TASK tst_viewSetParent()
{
    auto rootView = createViewAndWindow({});
    CHECK(rootView);
    CHECK(!rootView->isNull());
    CHECK(rootView->childViews().isEmpty());

    auto childView = createViewAndWindow({}, rootView);

    CHECK(!rootView->parentView());
    CHECK(childView);
    CHECK(childView->parentView());
    CHECK(childView->parentView()->equals(rootView));
    const auto children = rootView->childViews();

    CHECK_EQ(children.size(), 1);
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

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_viewRoot()
{
    auto rootView = createViewAndWindow({});
    auto childView = createViewAndWindow({ true }, rootView);

    auto window = rootView->window();
    CHECK(window);
    CHECK(childView->rootView()->equals(rootView));
    CHECK_EQ(window->handle(), window->handle());

    CHECK_EQ(rootView->window()->handle(), childView->window()->handle());
    CHECK_EQ(window->handle(), childView->window()->handle());
    CHECK(rootView->rootView()->equals(rootView));
    CHECK(childView->rootView()->equals(rootView));

    CHECK(window->rootView());
    CHECK(window->rootView()->equals(rootView));

    childView->setParent(nullptr);
    CHECK(childView->rootView()->equals(childView));

    delete rootView;
    delete childView;

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_viewIsVisible()
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

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_viewGeometry()
{
    // Test with a top-level view first
    auto rootView = createViewAndWindow({});
    rootView->show();

    const auto initialGeo = Rect(200, 201, 500, 501);
    rootView->setGeometry(initialGeo);
    CHECK_EQ(rootView->pos(), initialGeo.topLeft());

    Core::Window::Ptr window = rootView->window();
    CHECK_EQ(window->geometry(), initialGeo);

    CHECK_EQ(rootView->size(), initialGeo.size());
    CHECK_EQ(rootView->x(), initialGeo.x());
    CHECK_EQ(rootView->y(), initialGeo.y());
    CHECK_EQ(rootView->width(), initialGeo.width());
    CHECK_EQ(rootView->height(), initialGeo.height());
    CHECK_EQ(rootView->rect(), Rect(Point(0, 0), initialGeo.size()));

    // Now test with child view
    auto childView = createViewAndWindow({ true }, rootView);
    CHECK(rootView->isVisible());
    CHECK(childView->isVisible());
    CHECK(childView->controller()->isVisible());
    const Rect newChildGeo(1, 2, 300, 301);
    childView->setGeometry(newChildGeo);

    EVENT_LOOP(500);

    CHECK(!childView->isRootView());
    CHECK_EQ(childView->size(), newChildGeo.size());
    CHECK_EQ(childView->x(), newChildGeo.x());
    CHECK_EQ(childView->geometry(), newChildGeo);

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_viewMinSize()
{
    const Size sizeHint = {};
    const Size minSize = { 201, 202 };
    auto rootView = createViewAndWindow({ true, sizeHint, minSize });
    CHECK_EQ(rootView->minSize(), minSize);

    const Size newMinSize = { 301, 302 };
    rootView->setMinimumSize(newMinSize);
    CHECK_EQ(rootView->minSize(), newMinSize);

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_viewMaxSize()
{
    const Size sizeHint = {};
    const Size minSize = { 201, 202 };
    const Size maxSize = { 500, 501 };
    auto rootView = createViewAndWindow({ true, sizeHint, minSize, maxSize });
    CHECK_EQ(rootView->maxSizeHint(), maxSize);

    const Size newMaxSize = { 301, 302 };
    rootView->setMaximumSize(newMaxSize);
    CHECK_EQ(rootView->maxSizeHint(), newMaxSize);

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_viewObjectName()
{
    auto rootView = createViewAndWindow({});

    CHECK_EQ(rootView->viewName(), QString());
    const QString newName = QStringLiteral("name1");
    rootView->setViewName(newName);
    CHECK_EQ(rootView->viewName(), newName);

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_viewCloseRequested()
{
    // Tests that the closeRequested signal is emitted

    auto rootView = createViewAndWindow({});
    bool signalArrived = false;
    KDBindings::ScopedConnection connection =
        rootView->d->closeRequested.connect([&signalArrived](CloseEvent *ev) {
            signalArrived = true;
            CHECK(ev->isAccepted());
        });

    rootView->close();
    CHECK(signalArrived);
    delete rootView;

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_viewFocusPolicy()
{
    auto rootView = createViewAndWindow({});
    CHECK_EQ(rootView->focusPolicy(), Qt::NoFocus);

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_hasFocus()
{
    auto rootView = createViewAndWindow({});
    rootView->show();
    rootView->activateWindow();

    CHECK(rootView->controller()->isVisible());
    EVENT_LOOP(0);
    CHECK(!rootView->hasFocus());

    rootView->setFocus(Qt::MouseFocusReason);
    EVENT_LOOP(200); // QWidget::setFocus() requires 1 event loop iteration
    CHECK(rootView->hasFocus());
    CHECK(rootView->equals(Platform::instance()->focusedView()));

    auto child1 = createViewAndWindow({}, rootView);
    CHECK(rootView->hasFocus());
    CHECK(rootView->equals(Platform::instance()->focusedView()));
    child1->controller()->setVisible(true);
    child1->setFocus(Qt::MouseFocusReason);
    EVENT_LOOP(200); // QWidget::setFocus() requires 1 event loop iteration
    CHECK(child1->hasFocus());
    CHECK(child1->equals(Platform::instance()->focusedView()));

    KDDW_TEST_RETURN(true);
}

KDDW_QCORO_TASK tst_parentDeletesChildViews()
{
    // Tests that deleting a parent view also deletes its children

    auto rootView = createViewAndWindow({});
    rootView->show();
    rootView->activateWindow();
    CHECK(rootView->controller()->isVisible());
    EVENT_LOOP(0);
    auto child = createViewAndWindow({}, rootView);
    child->show();
    CHECK(child->isVisible());
    CHECK(child->controller());

    ViewGuard guard1(rootView);
    ViewGuard guard2(child);

    delete rootView;
    CHECK(!guard1);
    CHECK(!guard2);

    KDDW_TEST_RETURN(true);
}

static const auto s_tests = std::vector<KDDWTest> {
    TEST(tst_viewSetParent),
    TEST(tst_viewRoot),
    TEST(tst_viewIsVisible),
    TEST(tst_viewGeometry),
    TEST(tst_viewMinSize),
    TEST(tst_viewMaxSize),
    TEST(tst_viewObjectName),
    TEST(tst_viewCloseRequested),
    TEST(tst_viewFocusPolicy),
    TEST(tst_hasFocus),
    TEST(tst_parentDeletesChildViews),
};

#include "tests_main.h"

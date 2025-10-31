/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "core/Platform.h"
#include "core/Window_p.h"
#include "core/View_p.h"
#include "core/ViewGuard.h"
#include "tests/utils.h"

#include <QTest>

using namespace KDDockWidgets::Core;
using namespace KDDockWidgets;

inline Core::View *createViewAndWindow(Core::CreateViewOptions opts, Core::View *parent = nullptr)
{
    opts.createWindow = true;
    return Core::Platform::instance()->tests_createView(opts, parent);
}

class TestView : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void tst_viewSetParent();
    void tst_viewRoot();
    void tst_viewIsVisible();
    void tst_viewGeometry();
    void tst_viewMinSize();
    void tst_viewMaxSize();
    void tst_viewObjectName();
    void tst_viewCloseRequested();
    void tst_viewFocusPolicy();
    void tst_hasFocus();
    void tst_parentDeletesChildViews();
};

void TestView::tst_viewSetParent()
{
    auto rootView = createViewAndWindow({});
    QVERIFY(rootView);
    QVERIFY(!rootView->isNull());
    QVERIFY(rootView->childViews().isEmpty());

    auto childView = createViewAndWindow({}, rootView);

    QVERIFY(!rootView->parentView());
    QVERIFY(childView);
    QVERIFY(childView->parentView());
    QVERIFY(childView->parentView()->equals(rootView));
    const auto children = rootView->childViews();

    QCOMPARE(children.size(), 1);
    QVERIFY(children[0]->equals(childView));

    auto rootView2 = createViewAndWindow({});
    childView->setParent(rootView2);
    QVERIFY(childView->parentView()->equals(rootView2));
    QVERIFY(rootView->childViews().isEmpty());
    QCOMPARE(rootView2->childViews().size(), 1);

    // Deleting a view will remove it from its parent
    delete childView;
    QVERIFY(rootView2->childViews().isEmpty());

    delete rootView;
    delete rootView2;
}

void TestView::tst_viewRoot()
{
    auto rootView = createViewAndWindow({});
    auto childView = createViewAndWindow({ true }, rootView);

    auto window = rootView->window();
    QVERIFY(window);
    QVERIFY(childView->rootView()->equals(rootView));
    QCOMPARE(window->handle(), window->handle());

    QCOMPARE(rootView->window()->handle(), childView->window()->handle());
    QCOMPARE(window->handle(), childView->window()->handle());
    QVERIFY(rootView->rootView()->equals(rootView));
    QVERIFY(childView->rootView()->equals(rootView));

    QVERIFY(window->rootView());
    QVERIFY(window->rootView()->equals(rootView));

    childView->setParent(nullptr);
    QVERIFY(childView->rootView()->equals(childView));

    delete rootView;
    delete childView;
}

void TestView::tst_viewIsVisible()
{
    auto rootView = createViewAndWindow({});
    QVERIFY(!rootView->controller()->isVisible());

    rootView->controller()->setVisible(true);
    QVERIFY(rootView->controller()->isVisible());

    // Hiding the parent should hide the children
    auto view2 = createViewAndWindow({});
    view2->setParent(rootView);
    view2->controller()->setVisible(true);
    QVERIFY(view2->controller()->isVisible());
    QVERIFY(rootView->controller()->isVisible());
    rootView->controller()->setVisible(false);
    QVERIFY(!view2->controller()->isVisible());
    QVERIFY(!rootView->controller()->isVisible());

    // test show()
    rootView->show();
    QVERIFY(rootView->controller()->isVisible());
    QVERIFY(view2->controller()->isVisible());

    // test hide()
    rootView->hide();
    QVERIFY(!rootView->controller()->isVisible());
    QVERIFY(!view2->controller()->isVisible());

    delete rootView;
}

void TestView::tst_viewGeometry()
{
    // Test with a top-level view first
    auto rootView = createViewAndWindow({});
    rootView->show();

    const auto initialGeo = QRect(200, 201, 500, 501);
    rootView->setGeometry(initialGeo);
    QCOMPARE(rootView->pos(), initialGeo.topLeft());

    Core::Window::Ptr window = rootView->window();
    QCOMPARE(window->geometry(), initialGeo);

    QCOMPARE(rootView->size(), initialGeo.size());
    QCOMPARE(rootView->x(), initialGeo.x());
    QCOMPARE(rootView->y(), initialGeo.y());
    QCOMPARE(rootView->width(), initialGeo.width());
    QCOMPARE(rootView->height(), initialGeo.height());
    QCOMPARE(rootView->rect(), QRect(Point(0, 0), initialGeo.size()));

    // Now test with child view
    auto childView = createViewAndWindow({ true }, rootView);
    QVERIFY(rootView->isVisible());
    QVERIFY(childView->isVisible());
    QVERIFY(childView->controller()->isVisible());
    const QRect newChildGeo(1, 2, 300, 301);
    childView->setGeometry(newChildGeo);

    QTest::qWait(500);

    QVERIFY(!childView->isRootView());
    QCOMPARE(childView->size(), newChildGeo.size());
    QCOMPARE(childView->x(), newChildGeo.x());
    QCOMPARE(childView->geometry(), newChildGeo);
}

void TestView::tst_viewMinSize()
{
    const Size sizeHint = {};
    const Size minSize = { 201, 202 };
    auto rootView = createViewAndWindow({ true, sizeHint, minSize });
    QCOMPARE(rootView->minSize(), minSize);

    const Size newMinSize = { 301, 302 };
    rootView->setMinimumSize(newMinSize);
    QCOMPARE(rootView->minSize(), newMinSize);
}

void TestView::tst_viewMaxSize()
{
    const Size sizeHint = {};
    const Size minSize = { 201, 202 };
    const Size maxSize = { 500, 501 };
    auto rootView = createViewAndWindow({ true, sizeHint, minSize, maxSize });
    QCOMPARE(rootView->maxSizeHint(), maxSize);

    const Size newMaxSize = { 301, 302 };
    rootView->setMaximumSize(newMaxSize);
    QCOMPARE(rootView->maxSizeHint(), newMaxSize);
}

void TestView::tst_viewObjectName()
{
    auto rootView = createViewAndWindow({});

    QCOMPARE(rootView->viewName(), QString());
    const QString newName = QStringLiteral("name1");
    rootView->setViewName(newName);
    QCOMPARE(rootView->viewName(), newName);
}

void TestView::tst_viewCloseRequested()
{
    // Tests that the closeRequested signal is emitted

    auto rootView = createViewAndWindow({});
    bool signalArrived = false;
    KDBindings::ScopedConnection connection =
        rootView->d->closeRequested.connect([&signalArrived](QCloseEvent *ev) {
            signalArrived = true;
            QVERIFY(ev->isAccepted());
        });

    rootView->close();
    QVERIFY(signalArrived);
    delete rootView;
}

void TestView::tst_viewFocusPolicy()
{
    auto rootView = createViewAndWindow({});
    QCOMPARE(rootView->focusPolicy(), Qt::NoFocus);
}

void TestView::tst_hasFocus()
{
    auto rootView = createViewAndWindow({});
    rootView->show();
    rootView->activateWindow();

    QVERIFY(rootView->controller()->isVisible());
    QTest::qWait(0);
    QVERIFY(!rootView->hasFocus());

    rootView->setFocus(Qt::MouseFocusReason);
    QTest::qWait(200); // QWidget::setFocus() requires 1 event loop iteration
    QVERIFY(rootView->hasFocus());
    QVERIFY(rootView->equals(Platform::instance()->focusedView()));

    auto child1 = createViewAndWindow({}, rootView);
    QVERIFY(rootView->hasFocus());
    QVERIFY(rootView->equals(Platform::instance()->focusedView()));
    child1->controller()->setVisible(true);
    child1->setFocus(Qt::MouseFocusReason);
    QTest::qWait(200); // QWidget::setFocus() requires 1 event loop iteration
    QVERIFY(child1->hasFocus());
    QVERIFY(child1->equals(Platform::instance()->focusedView()));
}

void TestView::tst_parentDeletesChildViews()
{
    // Tests that deleting a parent view also deletes its children

    auto rootView = createViewAndWindow({});
    rootView->show();
    rootView->activateWindow();
    QVERIFY(rootView->controller()->isVisible());
    QTest::qWait(0);
    auto child = createViewAndWindow({}, rootView);
    child->show();
    QVERIFY(child->isVisible());
    QVERIFY(child->controller());

    ViewGuard guard1(rootView);
    ViewGuard guard2(child);

    delete rootView;
    QVERIFY(!guard1);
    QVERIFY(!guard2);
}

#define KDDW_TEST_NAME TestView
#include "test_main_qt.h"

#include "tst_view.moc"

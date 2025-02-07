/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "../utils.h"
#include "core/DockWidget.h"
#include "core/FloatingWindow.h"
#include "core/DockWidget_p.h"
#include "core/Group.h"
#include "core/Platform.h"
#include "core/TitleBar.h"
#include "core/ViewFactory.h"
#include "core/ObjectGuard_p.h"
#include "Config.h"

#include <QTest>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;

class TestDockWidget : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void tst_dockWidgetCtor();
    void tst_setGuestView();
    void tst_toggleAction();
    void tst_isOpen();
    void tst_setAsCurrentTab();
    void tst_dwCloseAndReopen();
    void tst_setSize();
};

void TestDockWidget::tst_dockWidgetCtor()
{
    Tests::EnsureTopLevelsDeleted e;

    auto dw = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();
    QVERIFY(dw->view()->is(ViewType::DockWidget));
    QVERIFY(dw->view()->asWrapper()->is(ViewType::DockWidget));
    dw->view()->show();

    delete dw;
}

void TestDockWidget::tst_setGuestView()
{
    Tests::EnsureTopLevelsDeleted e;

    auto dw = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();
    QVERIFY(Platform::instance());
    auto childView = Platform::instance()->tests_createView({ true });
    QVERIFY(childView);
    auto guest = childView->asWrapper();
    QVERIFY(guest);
    dw->setGuestView(guest);
    QVERIFY(dw->guestView());
    QVERIFY(dw->view());
    dw->view()->show();
    EVENT_LOOP(500);

    QVERIFY(guest->controller());
    QVERIFY(dw->floatingWindow());
    QVERIFY(dw->floatingWindow()->isVisible());
    QVERIFY(dw->isVisible());
    QVERIFY(guest->isVisible());
    QVERIFY(guest->controller()->isVisible());
    QVERIFY(dw->guestView()->equals(guest));
    QVERIFY(dw->view()->window());
    QVERIFY(guest->window());

    QVERIFY(guest->parentView());
    QVERIFY(guest->parentView()->equals(dw->view()));
    QVERIFY(dw->view()->rootView()->equals(guest->rootView()));
    QVERIFY(dw->view()->window()->equals(guest->window()));

    delete dw;
}

void TestDockWidget::tst_toggleAction()
{
    Tests::EnsureTopLevelsDeleted e;

    auto dw = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();

    QVERIFY(!dw->toggleAction()->isChecked());
    QVERIFY(dw->toggleAction()->isEnabled());

    delete dw;
}

void TestDockWidget::tst_isOpen()
{
    Tests::EnsureTopLevelsDeleted e;

    auto dw = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();

    // Starts closed
    QVERIFY(!dw->isOpen());

    dw->open();
    QVERIFY(dw->isOpen());
    QVERIFY(dw->isFloating());

    // close() closes
    dw->close();
    QVERIFY(!dw->isOpen());

    // Dockwidget in a non-current tab is not visible, but still counts as open
    dw->open();
    QVERIFY(dw->d->group());
    QVERIFY(dw->isOpen());
    QVERIFY(dw->isFloating());
    auto dw2 = Config::self().viewFactory()->createDockWidget("dw2")->asDockWidgetController();
    QVERIFY(dw->isCurrentTab());
    dw->addDockWidgetAsTab(dw2);
    QVERIFY(dw2->isOpen());
    dw2->setAsCurrentTab();
    QVERIFY(!dw->isCurrentTab());
    QVERIFY(dw2->isCurrentTab());
    QVERIFY(dw->isOpen());
    QVERIFY(dw2->isOpen());

    delete dw;
    delete dw2;
}

void TestDockWidget::tst_setAsCurrentTab()
{
    Tests::EnsureTopLevelsDeleted e;

    auto dw = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();
    auto dw2 = Config::self().viewFactory()->createDockWidget("dw2")->asDockWidgetController();
    auto dw3 = Config::self().viewFactory()->createDockWidget("dw3")->asDockWidgetController();

    QVERIFY(dw->view());
    dw->view()->show();
    QVERIFY(dw->d->group());
    QVERIFY(dw->isOpen());

    dw->addDockWidgetAsTab(dw2);
    dw->addDockWidgetAsTab(dw3);
    dw->setAsCurrentTab();

    QVERIFY(dw->isCurrentTab());
    QVERIFY(!dw2->isCurrentTab());
    QVERIFY(!dw3->isCurrentTab());

    Core::Group *group = dw->d->group();
    QCOMPARE(group->currentIndex(), 0);
    QCOMPARE(group->currentDockWidget(), dw);

    delete dw;
    delete dw2;
    delete dw3;
}

void TestDockWidget::tst_dwCloseAndReopen()
{
    {
        Tests::EnsureTopLevelsDeleted e;

        // Tests that a floating window is deleted after being closed

        auto dw = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();
        dw->view()->show();
        ObjectGuard<Core::FloatingWindow> fw = dw->floatingWindow();
        QVERIFY(fw);

        auto titleBar = fw->titleBar();
        QVERIFY(titleBar);
        QVERIFY(titleBar->isVisible());
        titleBar->onCloseClicked();
        QVERIFY(!dw->isOpen());
        QVERIFY(Platform::instance()->tests_waitForDeleted(fw));
        QVERIFY(!fw);

        QVERIFY(!dw->floatingWindow());
        QVERIFY(!dw->view()->parentView());
        dw->open();

        delete dw;
    }

    // 1 event loop for DelayedDelete. Avoids LSAN warnings.
    EVENT_LOOP(1);
}

void TestDockWidget::tst_setSize()
{
    {
        Tests::EnsureTopLevelsDeleted e;
        auto dw = Config::self().viewFactory()->createDockWidget("dw1")->asDockWidgetController();
        const Size size = Size(501, 502);
        dw->view()->setSize(size);
        QCOMPARE(dw->view()->size(), size);
    }

    // 1 event loop for DelayedDelete. Avoids LSAN warnings.
    EVENT_LOOP(1);
}

#define KDDW_TEST_NAME TestDockWidget
#include "../test_main_qt.h"

#include "tst_dockwidget.moc"

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
#include "core/DockRegistry.h"
#include "core/MainWindow.h"
#include "core/SideBar.h"
#include "Config.h"

#include <QTest>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;

static Core::DockWidget *createNotDockable(const QString &name)
{
    return Tests::createDockWidget(name, Platform::instance()->tests_createView({ true }),
                                   DockWidgetOption_NotDockable);
}

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
    void tst_addDockWidgetAsTabErrors();
    void tst_addDockWidgetToContainingWindow();
    void tst_mainWindowAddDockWidgetAsTab();
    void tst_sideBarErrors();
    void tst_duplicateNames();
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
    QTest::qWait(500);

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
    QTest::qWait(1);
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
    QTest::qWait(1);
}

void TestDockWidget::tst_addDockWidgetAsTabErrors()
{
    {
        Tests::EnsureTopLevelsDeleted e;
        auto dw1 = Tests::createDockWidget("dw1");
        auto dw2 = Tests::createDockWidget("dw2");

        {
            SetExpectedWarning sew("Refusing to add dock widget into itself");
            dw1->addDockWidgetAsTab(dw1);
        }

        {
            SetExpectedWarning sew("dock widget is null");
            dw1->addDockWidgetAsTab(nullptr);
        }

        {
            auto notDockable = createNotDockable("notDockable");
            {
                SetExpectedWarning sew("Option_NotDockable not allowed to change");
                notDockable->setOptions(DockWidgetOption_None);
            }
            SetExpectedWarning sew("Refusing to dock non-dockable widget");
            dw1->addDockWidgetAsTab(notDockable);
            delete notDockable;
        }

        dw1->addDockWidgetAsTab(dw2);
        QCOMPARE(dw1->dptr()->group()->dockWidgetCount(), 2);

        {
            SetExpectedWarning sew("Already contains");
            dw1->addDockWidgetAsTab(dw2);
        }
        QCOMPARE(dw1->dptr()->group()->dockWidgetCount(), 2);

        delete dw1;
        delete dw2;
    }

    // 1 event loop for DelayedDelete. Avoids LSAN warnings.
    QTest::qWait(1);
}

void TestDockWidget::tst_addDockWidgetToContainingWindow()
{
    {
        Tests::EnsureTopLevelsDeleted e;
        auto dw1 = Tests::createDockWidget("dw1");
        auto dw2 = Tests::createDockWidget("dw2");
        auto dw3 = Tests::createDockWidget("dw3");
        auto dw4 = Tests::createDockWidget("dw4");

        // Null is a no-op
        dw1->addDockWidgetToContainingWindow(nullptr, Location_OnRight, nullptr);

        {
            auto notDockable = createNotDockable("notDockable");
            SetExpectedWarning sew("Refusing to dock non-dockable widget");
            dw1->addDockWidgetToContainingWindow(notDockable, Location_OnRight, nullptr);
            delete notDockable;
        }

        {
            dw3->setAffinities({ "other" });
            SetExpectedWarning sew("Refusing to dock widget with incompatible affinity");
            dw1->addDockWidgetToContainingWindow(dw3, Location_OnRight, nullptr);
        }

        // dw1 isn't in a main window, so it's docked into its own floating window
        dw1->addDockWidgetToContainingWindow(dw2, Location_OnRight, nullptr);
        QVERIFY(dw1->floatingWindow());
        QCOMPARE(dw1->floatingWindow(), dw2->floatingWindow());

        // dw4 is in a main window, so the main window API is used
        auto m = Tests::createMainWindow();
        m->addDockWidget(dw4, Location_OnLeft);
        auto dw5 = Tests::createDockWidget("dw5");
        dw4->addDockWidgetToContainingWindow(dw5, Location_OnRight, nullptr);
        QCOMPARE(dw5->mainWindow(), m.get());

        delete dw1;
        delete dw2;
        delete dw3;
        delete dw4;
        delete dw5;
        m.reset();
    }

    // 1 event loop for DelayedDelete. Avoids LSAN warnings.
    QTest::qWait(1);
}

void TestDockWidget::tst_mainWindowAddDockWidgetAsTab()
{
    {
        Tests::EnsureTopLevelsDeleted e;

        // Central group supports tabbing
        auto m = Tests::createMainWindow(Size(1000, 1000), MainWindowOption_HasCentralGroup, "mw1");
        auto dw1 = Tests::createDockWidget("dw1");
        auto dw2 = Tests::createDockWidget("dw2");
        m->addDockWidgetAsTab(dw1);
        m->addDockWidgetAsTab(dw2);
        QCOMPARE(dw1->dptr()->group()->dockWidgetCount(), 2);
        QCOMPARE(dw1->dptr()->group(), dw2->dptr()->group());

        {
            auto dw3 = Tests::createDockWidget("dw3");
            dw3->setAffinities({ "other" });
            SetExpectedWarning sew("Refusing to dock widget with incompatible affinity");
            m->addDockWidgetAsTab(dw3);
            delete dw3;
        }

        {
            auto dw3 = createNotDockable("dw3");
            SetExpectedWarning sew("Refusing to dock non-dockable widget");
            m->addDockWidgetAsTab(dw3);
            m->addDockWidget(dw3, Location_OnLeft);
            delete dw3;
        }

        // Without a central group it's not supported
        auto m2 = Tests::createMainWindow(Size(1000, 1000), MainWindowOption_None, "mw2");
        auto dw4 = Tests::createDockWidget("dw4");
        {
            SetExpectedWarning sew("Not supported without MainWindowOption_HasCentralGroup");
            m2->addDockWidgetAsTab(dw4);
            QVERIFY(!dw4->mainWindow());
        }
        {
            SetExpectedWarning sew("A central group is required");
            m2->addDockWidgetToSide(dw4, Location_OnLeft);
        }

        // Neither is it supported with a persistent central widget
        auto m3 = Tests::createMainWindow(Size(1000, 1000), MainWindowOption_HasCentralWidget, "mw3");
        {
            SetExpectedWarning sew("Not supported with MainWindowOption_HasCentralWidget");
            m3->addDockWidgetAsTab(dw4);
        }

        // Not applicable to MDI, silently ignored
        auto m4 = Tests::createMainWindow(Size(1000, 1000), MainWindowOption_MDI, "mw4");
        m4->addDockWidgetAsTab(dw4);
        m4->addDockWidgetToSide(dw4, Location_OnLeft);

        delete dw1;
        delete dw2;
        delete dw4;
        m4.reset();
        m3.reset();
        m2.reset();
        m.reset();
    }

    // 1 event loop for DelayedDelete. Avoids LSAN warnings.
    QTest::qWait(1);
}

void TestDockWidget::tst_sideBarErrors()
{
    if (Platform::instance()->isQtQuick())
        QSKIP("Side bars are not implemented for QtQuick");

    {
        Tests::EnsureTopLevelsDeleted e;
        Config::self().setFlags(Config::Flag_AutoHideSupport);
        auto m = Tests::createMainWindow();
        auto dw1 = Tests::createDockWidget("dw1");
        auto dw2 = Tests::createDockWidget("dw2");
        m->addDockWidget(dw1, Location_OnLeft);
        m->addDockWidget(dw2, Location_OnRight);

        auto sideBar = m->sideBar(SideBarLocation::West);
        QVERIFY(sideBar);

        // Null is a no-op
        sideBar->addDockWidget(nullptr);

        sideBar->addDockWidget(dw1);
        QVERIFY(sideBar->containsDockWidget(dw1));
        {
            SetExpectedWarning sew("Already contains dock widget");
            sideBar->addDockWidget(dw1);
        }

        {
            SetExpectedWarning sew("Doesn't contain dock widget");
            sideBar->removeDockWidget(dw2);
        }

        sideBar->removeDockWidget(dw1);
        QVERIFY(!sideBar->containsDockWidget(dw1));

        delete dw1;
        delete dw2;
        m.reset();
    }

    // 1 event loop for DelayedDelete. Avoids LSAN warnings.
    QTest::qWait(1);
}

void TestDockWidget::tst_duplicateNames()
{
    {
        Tests::EnsureTopLevelsDeleted e;
        auto registry = DockRegistry::self();
        QVERIFY(registry->isSane());

        auto dw1 = Config::self().viewFactory()->createDockWidget("dup")->asDockWidgetController();
        Core::DockWidget *dw2 = nullptr;
        {
            SetExpectedWarning sew("already exists");
            dw2 = Config::self().viewFactory()->createDockWidget("dup")->asDockWidgetController();
        }

        {
            SetExpectedWarning sew("dockWidgets with duplicate names");
            QVERIFY(!registry->isSane());
        }

        delete dw2;
        QVERIFY(registry->isSane());

        auto m1 = Tests::createMainWindow(Size(1000, 1000), MainWindowOption_HasCentralGroup, "dupmw");
        std::unique_ptr<Core::MainWindow> m2;
        {
            SetExpectedWarning sew("already exists");
            m2 = Tests::createMainWindow(Size(1000, 1000), MainWindowOption_HasCentralGroup, "dupmw");
        }

        {
            SetExpectedWarning sew("mainWindow with duplicate names");
            QVERIFY(!registry->isSane());
        }

        m2.reset();
        QVERIFY(registry->isSane());
        QCOMPARE(registry->dockWidgetNames(), Vector<QString>({ "dup" }));
        QCOMPARE(registry->mainWindowsNames(), Vector<QString>({ "dupmw" }));

        m1.reset();
        delete dw1;
    }

    // 1 event loop for DelayedDelete. Avoids LSAN warnings.
    QTest::qWait(1);
}

#define KDDW_TEST_NAME TestDockWidget
#include "../test_main_qt.h"

#include "tst_dockwidget.moc"

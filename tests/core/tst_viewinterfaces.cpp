/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// Tests the MainWindowViewInterface and DockWidgetViewInterface mixins, which are the
// public API of the frontends' MainWindow and DockWidget classes.
// They just forward to the Core controllers, so we check that the forwarding is correct.

#include "../utils.h"
#include "core/DockWidget.h"
#include "core/Group.h"
#include "core/MainWindow.h"
#include "core/Platform.h"
#include "core/SideBar.h"
#include "core/views/DockWidgetViewInterface.h"
#include "core/views/MainWindowViewInterface.h"
#include "Config.h"

#include <QTest>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;

namespace {

MainWindowViewInterface *mainWindowInterface(Core::MainWindow *mainWindow)
{
    return dynamic_cast<MainWindowViewInterface *>(mainWindow->view());
}

DockWidgetViewInterface *dockWidgetInterface(Core::DockWidget *dw)
{
    return dynamic_cast<DockWidgetViewInterface *>(dw->view());
}

}

class TestViewInterfaces : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void tst_mainWindowBasics();
    void tst_mainWindowAddDockWidgets();
    void tst_mainWindowAddDockWidgetsByName();
    void tst_mainWindowSideBar();
    void tst_mainWindowSideBarByName();
    void tst_mainWindowLayoutEqually();
    void tst_mainWindowCloseDockWidgets();
    void tst_mainWindowMdi();
    void tst_dockWidgetBasics();
    void tst_dockWidgetOptions();
    void tst_dockWidgetAffinities();
    void tst_dockWidgetIcon();
    void tst_dockWidgetOpenCloseFloat();
    void tst_dockWidgetAddDockWidgets();
    void tst_dockWidgetMdi();
};

void TestViewInterfaces::tst_mainWindowBasics()
{
    Tests::EnsureTopLevelsDeleted e;

    auto mainWindow = Tests::createMainWindow({ 800, 600 }, MainWindowOption_HasCentralGroup, "mainwindow1");
    auto view = mainWindowInterface(mainWindow.get());
    QVERIFY(view);

    QCOMPARE(view->mainWindow(), mainWindow.get());
    QCOMPARE(view->uniqueName(), QString("mainwindow1"));
    QCOMPARE(view->options(), MainWindowOption_HasCentralGroup);
    QVERIFY(!view->isMDI());

    QVERIFY(view->affinities().isEmpty());
    view->setAffinities({ "affinity1" });
    QCOMPARE(view->affinities(), Vector<QString>({ "affinity1" }));
    QCOMPARE(mainWindow->affinities(), Vector<QString>({ "affinity1" }));
}

void TestViewInterfaces::tst_mainWindowAddDockWidgets()
{
    Tests::EnsureTopLevelsDeleted e;

    auto mainWindow = Tests::createMainWindow();
    auto view = mainWindowInterface(mainWindow.get());

    auto dw1 = Tests::createDockWidget("dw1");
    auto dw2 = Tests::createDockWidget("dw2");
    auto dw3 = Tests::createDockWidget("dw3");

    view->addDockWidget(dockWidgetInterface(dw1), Location_OnLeft);
    QVERIFY(dw1->isOpen());
    QVERIFY(!dw1->isFloating());
    QCOMPARE(dw1->window()->controller(), mainWindow.get());

    view->addDockWidget(dockWidgetInterface(dw2), Location_OnRight, dockWidgetInterface(dw1));
    QVERIFY(dw1->dptr()->group() != dw2->dptr()->group());

    // Tabbed with dw2
    view->addDockWidgetAsTab(dockWidgetInterface(dw3));
    QVERIFY(dw3->isOpen());
    QVERIFY(!dw3->isFloating());

    delete dw1;
    delete dw2;
    delete dw3;
}

void TestViewInterfaces::tst_mainWindowAddDockWidgetsByName()
{
    Tests::EnsureTopLevelsDeleted e;

    auto mainWindow = Tests::createMainWindow();
    auto view = mainWindowInterface(mainWindow.get());

    auto dw1 = Tests::createDockWidget("dw1");
    auto dw2 = Tests::createDockWidget("dw2");
    auto dw3 = Tests::createDockWidget("dw3");

    view->addDockWidget("dw1", Location_OnLeft);
    view->addDockWidget("dw2", Location_OnRight, "dw1");
    QVERIFY(dw1->isOpen());
    QVERIFY(dw2->isOpen());
    QVERIFY(dw1->dptr()->group() != dw2->dptr()->group());

    view->addDockWidgetAsTab("dw3");
    QVERIFY(dw3->isOpen());

    delete dw1;
    delete dw2;
    delete dw3;
}

void TestViewInterfaces::tst_mainWindowSideBar()
{
    if (Platform::instance()->isQtQuick())
        QSKIP("Side bars are not implemented for QtQuick");

    Tests::EnsureTopLevelsDeleted e;

    Config::self().setFlags(Config::Flag_AutoHideSupport);
    auto mainWindow = Tests::createMainWindow();
    auto view = mainWindowInterface(mainWindow.get());

    auto dw1 = Tests::createDockWidget("dw1");
    auto dw2 = Tests::createDockWidget("dw2");
    view->addDockWidget(dockWidgetInterface(dw1), Location_OnLeft);
    view->addDockWidget(dockWidgetInterface(dw2), Location_OnRight);

    QVERIFY(!view->anySideBarIsVisible());
    QVERIFY(!view->sideBarIsVisible(SideBarLocation::West));

    view->moveToSideBar(dockWidgetInterface(dw1), SideBarLocation::West);
    QVERIFY(view->anySideBarIsVisible());
    QVERIFY(view->sideBarIsVisible(SideBarLocation::West));
    QVERIFY(dw1->isInSideBar());
    QVERIFY(!dw1->isOpen());

    // Overlay it, toggling closes the overlay
    view->overlayOnSideBar(dockWidgetInterface(dw1));
    QVERIFY(dw1->isOpen());
    QCOMPARE(mainWindow->overlayedDockWidget(), dw1);
    view->toggleOverlayOnSideBar(dockWidgetInterface(dw1));
    QVERIFY(!mainWindow->overlayedDockWidget());
    view->toggleOverlayOnSideBar(dockWidgetInterface(dw1));
    QCOMPARE(mainWindow->overlayedDockWidget(), dw1);

    view->clearSideBarOverlay();
    QVERIFY(!mainWindow->overlayedDockWidget());
    QVERIFY(dw1->isInSideBar());

    view->restoreFromSideBar(dockWidgetInterface(dw1));
    QVERIFY(!dw1->isInSideBar());
    QVERIFY(dw1->isOpen());
    QVERIFY(!view->anySideBarIsVisible());

    // Without a location the side bar is chosen automatically
    view->moveToSideBar(dockWidgetInterface(dw2));
    QVERIFY(dw2->isInSideBar());
    QVERIFY(view->anySideBarIsVisible());

    // The dock widget version
    view->restoreFromSideBar(dockWidgetInterface(dw2));
    dockWidgetInterface(dw2)->moveToSideBar();
    QVERIFY(dw2->isInSideBar());

    delete dw1;
    delete dw2;
}

void TestViewInterfaces::tst_mainWindowSideBarByName()
{
    if (Platform::instance()->isQtQuick())
        QSKIP("Side bars are not implemented for QtQuick");

    Tests::EnsureTopLevelsDeleted e;

    Config::self().setFlags(Config::Flag_AutoHideSupport);
    auto mainWindow = Tests::createMainWindow();
    auto view = mainWindowInterface(mainWindow.get());

    auto dw1 = Tests::createDockWidget("dw1");
    auto dw2 = Tests::createDockWidget("dw2");
    view->addDockWidget("dw1", Location_OnLeft);
    view->addDockWidget("dw2", Location_OnRight);

    view->moveToSideBar("dw1", SideBarLocation::East);
    QVERIFY(dw1->isInSideBar());
    QVERIFY(view->sideBarIsVisible(SideBarLocation::East));

    view->overlayOnSideBar("dw1");
    QCOMPARE(mainWindow->overlayedDockWidget(), dw1);
    view->toggleOverlayOnSideBar("dw1");
    QVERIFY(!mainWindow->overlayedDockWidget());

    view->restoreFromSideBar("dw1");
    QVERIFY(!dw1->isInSideBar());

    view->moveToSideBar("dw2");
    QVERIFY(dw2->isInSideBar());
    view->restoreFromSideBar("dw2");
    QVERIFY(!dw2->isInSideBar());

    delete dw1;
    delete dw2;
}

void TestViewInterfaces::tst_mainWindowLayoutEqually()
{
    Tests::EnsureTopLevelsDeleted e;

    auto mainWindow = Tests::createMainWindow({ 1000, 800 }, MainWindowOption_None);
    auto view = mainWindowInterface(mainWindow.get());

    auto dw1 = Tests::createDockWidget("dw1");
    auto dw2 = Tests::createDockWidget("dw2");
    auto dw3 = Tests::createDockWidget("dw3");
    view->addDockWidget(dockWidgetInterface(dw1), Location_OnLeft);
    view->addDockWidget(dockWidgetInterface(dw2), Location_OnRight);
    view->addDockWidget(dockWidgetInterface(dw3), Location_OnRight);

    view->layoutEqually();
    const int w1 = dw1->window()->width();
    QVERIFY(w1 > 0);

    const int groupWidth1 = dw1->dptr()->group()->width();
    const int groupWidth2 = dw2->dptr()->group()->width();
    const int groupWidth3 = dw3->dptr()->group()->width();
    QVERIFY(qAbs(groupWidth1 - groupWidth2) <= 2);
    QVERIFY(qAbs(groupWidth2 - groupWidth3) <= 2);

    // Check that these don't crash and keep the layout equal
    view->layoutParentContainerEqually(dockWidgetInterface(dw2));
    view->layoutParentContainerEqually("dw3");
    QVERIFY(dw1->isOpen() && dw2->isOpen() && dw3->isOpen());

    delete dw1;
    delete dw2;
    delete dw3;
}

void TestViewInterfaces::tst_mainWindowCloseDockWidgets()
{
    Tests::EnsureTopLevelsDeleted e;

    auto mainWindow = Tests::createMainWindow();
    auto view = mainWindowInterface(mainWindow.get());

    auto dw1 = Tests::createDockWidget("dw1");
    auto dw2 = Tests::createDockWidget("dw2");
    view->addDockWidget(dockWidgetInterface(dw1), Location_OnLeft);
    view->addDockWidget(dockWidgetInterface(dw2), Location_OnRight);
    QVERIFY(dw1->isOpen());
    QVERIFY(dw2->isOpen());

    QVERIFY(view->closeDockWidgets());
    QVERIFY(!dw1->isOpen());
    QVERIFY(!dw2->isOpen());

    view->addDockWidget(dockWidgetInterface(dw1), Location_OnLeft);
    view->addDockWidget(dockWidgetInterface(dw2), Location_OnRight);
    QVERIFY(dw1->isOpen());
    QVERIFY(dw2->isOpen());

    QVERIFY(view->closeDockWidgets(/*force=*/true));
    QVERIFY(!dw1->isOpen());
    QVERIFY(!dw2->isOpen());

    delete dw1;
    delete dw2;
}

void TestViewInterfaces::tst_mainWindowMdi()
{
    Tests::EnsureTopLevelsDeleted e;

    auto mainWindow = Tests::createMainWindow({ 1000, 800 }, MainWindowOption_MDI);
    auto view = mainWindowInterface(mainWindow.get());
    QVERIFY(view->isMDI());
    QVERIFY(view->options() & MainWindowOption_MDI);
}

void TestViewInterfaces::tst_dockWidgetBasics()
{
    Tests::EnsureTopLevelsDeleted e;

    auto dw = Tests::createDockWidget("dw1");
    auto view = dockWidgetInterface(dw);
    QVERIFY(view);

    QCOMPARE(view->dockWidget(), dw);
    QCOMPARE(view->uniqueName(), QString("dw1"));

    view->setTitle("My title");
    QCOMPARE(view->title(), QString("My title"));
    QCOMPARE(dw->title(), QString("My title"));

    QVERIFY(view->group());
    QCOMPARE(view->group(), dw->dptr()->group());
    QVERIFY(view->actualTitleBar());
    QVERIFY(view->focusCandidate() || !view->focusCandidate()); // Just exercise it, can be null
    QVERIFY(!view->isFocused());

    delete dw;
}

void TestViewInterfaces::tst_dockWidgetOptions()
{
    Tests::EnsureTopLevelsDeleted e;

    auto dw = Tests::createDockWidget("dw1");
    auto view = dockWidgetInterface(dw);

    QVERIFY(!(view->options() & DockWidgetOption_NotClosable));
    view->setOptions(DockWidgetOption_NotClosable);
    QCOMPARE(view->options(), DockWidgetOptions(DockWidgetOption_NotClosable));
    QCOMPARE(dw->options(), DockWidgetOptions(DockWidgetOption_NotClosable));

    delete dw;
}

void TestViewInterfaces::tst_dockWidgetAffinities()
{
    Tests::EnsureTopLevelsDeleted e;

    auto dw = Tests::createDockWidget("dw1");
    auto view = dockWidgetInterface(dw);

    QVERIFY(view->affinities().isEmpty());

    view->setAffinities({ "name1", "name2" });
    QCOMPARE(view->affinities(), Vector<QString>({ "name1", "name2" }));
    QCOMPARE(dw->affinities(), Vector<QString>({ "name1", "name2" }));

    // Affinities can't be changed once set
    auto dw2 = Tests::createDockWidget("dw2");
    dockWidgetInterface(dw2)->setAffinityName("name3");
    QCOMPARE(dockWidgetInterface(dw2)->affinities(), Vector<QString>({ "name3" }));

    delete dw;
    delete dw2;
}

void TestViewInterfaces::tst_dockWidgetIcon()
{
    if (Platform::instance()->isQtQuick())
        QSKIP("Icons are not implemented for QtQuick");

    Tests::EnsureTopLevelsDeleted e;

    auto dw = Tests::createDockWidget("dw1");
    auto view = dockWidgetInterface(dw);

    QVERIFY(view->icon().isNull());
    view->setIcon(Icon());
    QVERIFY(view->icon().isNull());
    QVERIFY(view->icon(IconPlace::TabBar).isNull());

    delete dw;
}

void TestViewInterfaces::tst_dockWidgetOpenCloseFloat()
{
    Tests::EnsureTopLevelsDeleted e;

    auto dw = Tests::createDockWidget("dw1");
    auto view = dockWidgetInterface(dw);

    view->open();
    QVERIFY(view->isOpen());
    QVERIFY(view->isFloating());

    view->raise();
    view->setAsCurrentTab();

    view->forceClose();
    QVERIFY(!view->isOpen());

    // show() is the deprecated version of open()
    view->show();
    QVERIFY(view->isOpen());

    view->setFloating(true);
    QVERIFY(view->isFloating());

    delete dw;
}

void TestViewInterfaces::tst_dockWidgetAddDockWidgets()
{
    Tests::EnsureTopLevelsDeleted e;

    auto dw1 = Tests::createDockWidget("dw1");
    auto dw2 = Tests::createDockWidget("dw2");
    auto dw3 = Tests::createDockWidget("dw3");
    auto view1 = dockWidgetInterface(dw1);

    view1->open();
    view1->addDockWidgetAsTab(dockWidgetInterface(dw2));
    QCOMPARE(dw1->dptr()->group(), dw2->dptr()->group());
    QCOMPARE(dw1->dptr()->group()->dockWidgetCount(), 2);

    view1->addDockWidgetToContainingWindow(dockWidgetInterface(dw3), Location_OnRight, dockWidgetInterface(dw1));
    QVERIFY(dw3->isOpen());
    QVERIFY(dw1->floatingWindow());
    QCOMPARE(dw3->floatingWindow(), dw1->floatingWindow());
    QVERIFY(dw3->dptr()->group() != dw1->dptr()->group());

    delete dw1;
    delete dw2;
    delete dw3;
}

void TestViewInterfaces::tst_dockWidgetMdi()
{
    Tests::EnsureTopLevelsDeleted e;

    auto mainWindow = Tests::createMainWindow({ 1000, 800 }, MainWindowOption_MDI);
    auto mainWindowView = mainWindowInterface(mainWindow.get());

    auto dw = Tests::createDockWidget("dw1");
    auto view = dockWidgetInterface(dw);

    view->setMDIPosition(Point(30, 40));
    view->setMDISize(Size(300, 200));
    view->setMDIZ(1);

    mainWindowView->addDockWidget(view, Location_OnLeft);
    QVERIFY(dw->isOpen());

    view->setMDIPosition(Point(50, 60));
    view->setMDISize(Size(350, 250));
    QVERIFY(dw->isOpen());

    delete dw;
}

#define KDDW_TEST_NAME TestViewInterfaces
#include "../test_main_qt.h"

#include "tst_viewinterfaces.moc"

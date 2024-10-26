/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/// @file
/// @brief Here lives the tests that only apply to QtQuick

#define NOMINMAX

#include "kddockwidgets/KDDockWidgets.h"
#include "qtquick/Platform.h"
#include "qtquick/views/TitleBar.h"
#include "qtquick/views/DockWidget.h"
#include "qtquick/views/MainWindow.h"
#include "qtquick/views/FloatingWindow.h"
#include "core/MDILayout.h"
#include "core/views/MainWindowViewInterface.h"
#include "core/MainWindow.h"
#include "core/Window_p.h"
#include "core/Platform.h"

#include "../utils.h"

#ifdef KDDW_HAS_SPDLOG
#include "../fatal_logger.h"
#endif

#include <QtTest/QTest>
#include <QQmlApplicationEngine>
#include <QQmlContext>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Tests;
using namespace KDDockWidgets::Core;

class TestQtQuick : public QObject
{
    Q_OBJECT

public Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

private Q_SLOTS:
    void tst_restoreRestoresMainWindowPosition();
    void tst_hoverShowsDropIndicators();
    void tst_titlebarNumDockWidgetsChanged();
    void tst_effectiveVisibilityBug();

    /// Tests a situation where DockWidgetInstantiator::isFloatingChanged wasn't being emitted (#350)
    void tst_isFloatingIsEmitted();

    void tst_shutdownCrash();
    void tst_childQmlContext();

    void tst_focusBetweenTabs();
    void tst_setPersistentCentralView();

    void tst_mdiFixedSize();
    void tst_affinities();

    void tst_deleteDockWidget();
    void tst_setViewFactory();
    void tst_quickWindowCreationCallback();
};


void TestQtQuick::initTestCase()
{
    KDDockWidgets::Core::Platform::instance()->installMessageHandler();
}

void TestQtQuick::cleanupTestCase()
{
    KDDockWidgets::Core::Platform::instance()->uninstallMessageHandler();
}

void TestQtQuick::tst_restoreRestoresMainWindowPosition()
{
    // Tests the ApplicationWindow {} case

    QQmlApplicationEngine engine(":/main2.qml");

    const auto mainWindows = DockRegistry::self()->mainwindows();
    QCOMPARE(mainWindows.size(), 1);
    MainWindow *mainWindow = mainWindows.first();
    QVERIFY(mainWindow->isVisible());

    QCOMPARE(mainWindow->pos(), QPoint(0, 0));

    Window::Ptr window = mainWindow->view()->window();

    LayoutSaver saver;
    const QByteArray saved = saver.serializeLayout();

    const QPoint originalPos = window->framePosition();

    const QPoint newPos = originalPos + QPoint(200, 200);
    window->setFramePosition(newPos);
    QCOMPARE(window->framePosition(), newPos);

    QVERIFY(saver.restoreLayout(saved));

    QCOMPARE(window->framePosition(), originalPos);

    delete mainWindow;
}

void TestQtQuick::tst_hoverShowsDropIndicators()
{
    // For QtQuick on Windows, there was a bug where drop indicators wouldn't be shown if
    // MainWindowBase wasn't the root item.

    EnsureTopLevelsDeleted e;
    QQmlApplicationEngine engine(":/main2.qml");

    const auto mainWindows = DockRegistry::self()->mainwindows();
    QCOMPARE(mainWindows.size(), 1);
    MainWindow *m = mainWindows.first();

    m->window()->window()->setFramePosition(QPoint(500, 800));

    auto dock0 = createDockWidget(
        "dock0", Platform::instance()->tests_createView({ true, {}, QSize(400, 400) }));

    auto floatingDockWidget =
        createDockWidget("floatingDockWidget",
                         Platform::instance()->tests_createView({ true, {}, QSize(400, 400) }));

    m->addDockWidget(dock0, Location_OnLeft);

    const QPoint mainWindowCenterPos = m->mapToGlobal(m->geometry().center());

    QTest::qWait(100);

    auto fw = floatingDockWidget->floatingWindow();
    dragFloatingWindowTo(fw, mainWindowCenterPos);

    QCOMPARE(dock0->dptr()->group()->dockWidgetCount(), 2);
}

void TestQtQuick::tst_titlebarNumDockWidgetsChanged()
{
    EnsureTopLevelsDeleted e;
    QQmlApplicationEngine engine(":/main2.qml");

    auto dock0 = createDockWidget(
        "dock0", Platform::instance()->tests_createView({ true, {}, QSize(400, 400) }));
    const auto mainWindows = DockRegistry::self()->mainwindows();
    MainWindow *m = mainWindows.first();
    m->window()->window()->setFramePosition(QPoint(500, 800));
    m->addDockWidget(dock0, Location_OnLeft);

    auto tb = dock0->titleBar();
    auto tbView = static_cast<QtQuick::TitleBar *>(tb->view());

    int numSignalEmittions = 0;
    connect(tbView, &QtQuick::TitleBar::numDockWidgetsChanged,
            [&numSignalEmittions] { numSignalEmittions++; });

    auto dock1 = createDockWidget(
        "dock1", Platform::instance()->tests_createView({ true, {}, QSize(400, 400) }));

    dock0->addDockWidgetAsTab(dock1);

    QVERIFY(numSignalEmittions > 0);
}

void TestQtQuick::tst_isFloatingIsEmitted()
{
    {
        EnsureTopLevelsDeleted e;
        QQmlApplicationEngine engine(":/main350.qml");

        auto dw4 = DockRegistry::self()->dockByName("dock4");
        auto dw5 = DockRegistry::self()->dockByName("dock5");
        QVERIFY(dw4);
        QVERIFY(dw5);

        dw4->setFloating(true);
        dw5->addDockWidgetToContainingWindow(dw4, KDDockWidgets::Location_OnLeft);
        dw4->titleBar()->onFloatClicked();

        QVERIFY(dw4->isFloating());
        auto mw = DockRegistry::self()->mainWindowByName("MyWindowName-1");
        QVERIFY(mw);

        auto floatingDropArea = dw4->floatingWindow()->multiSplitter();
        QVERIFY(floatingDropArea);

        // Add to main window again and make sure signal was emitted

        bool signalReceived = false;
        dw4->d->isFloatingChanged.connect([&signalReceived] {
            signalReceived = true;
        });

        QVERIFY(dw4->isFloating());
        QVERIFY(dw4->floatAction()->isChecked());
        mw->dropArea()->addMultiSplitter(floatingDropArea, KDDockWidgets::Location_OnLeft);
        QVERIFY(!dw4->isFloating());
        QVERIFY(!dw4->floatAction()->isChecked());

        QVERIFY(signalReceived);
    }

    // 1 event loop for DelayedDelete. Avoids LSAN warnings.
    EVENT_LOOP(1);
}

void TestQtQuick::tst_shutdownCrash()
{
    // Currently failing only on Windows.

    // Tests a crash where Core::DockWidget would be referenced while being destroyed

    // EnsureTopLevelsDeleted e;
    // QQmlApplicationEngine engine(":/main2.qml");
    // auto guestView = Platform::instance()->tests_createView({ true, {}, QSize(400, 400) });
    // auto dock1 = createDockWidget("dock1", guestView);

    // QQuickItem *dockWidgeItem = QtCommon::View_qt::asQQuickItem(dock1->view());
    // QVERIFY(dockWidgeItem);
    // Core::Group *group = dock1->dptr()->group();
    // delete dockWidgeItem;
    // delete group;

    // // 1 event loop for DelayedDelete. Avoids LSAN warnings.
    // KDDW_CO_AWAIT Platform::instance()->tests_wait(1);
}

void TestQtQuick::tst_childQmlContext()
{
    // Tests that guest items can have a separate QML context
    EnsureTopLevelsDeleted e;

    {
        QQmlApplicationEngine engine(":/main2.qml");
        auto dock1 = new QtQuick::DockWidget("dock1");
        auto dock2 = new QtQuick::DockWidget("dock2");
        auto dock3 = new QtQuick::DockWidget("dock3");
        auto dock4 = new QtQuick::DockWidget("dock4");

        const auto defaultPropertyValue = QVariant(0);
        const auto overriddenPropertyValue = QVariant(1);

        QQmlContext *rootContext = plat()->qmlEngine()->rootContext();
        rootContext->setContextProperty("_ctxProperty", defaultPropertyValue);

        auto mw = DockRegistry::self()->mainWindowByName("MyWindowName-1");
        QVERIFY(mw);
        mw->addDockWidget(dock1->asDockWidgetController(), KDDockWidgets::Location_OnRight);
        mw->addDockWidget(dock2->asDockWidgetController(), KDDockWidgets::Location_OnRight);
        mw->addDockWidget(dock3->asDockWidgetController(), KDDockWidgets::Location_OnRight);
        mw->addDockWidget(dock4->asDockWidgetController(), KDDockWidgets::Location_OnRight);

        auto guestItem1 = new QQuickItem(dock1);
        dock1->setGuestItem(guestItem1);
        dock2->setGuestItem(":/MyRectangle.qml");
        dock3->setGuestItem(":/MyRectangle.qml");

        QQmlContext subContext(rootContext);
        subContext.setContextProperty("_ctxProperty", overriddenPropertyValue);
        dock4->setGuestItem(":/MyRectangle.qml", &subContext);

        QVERIFY(dock2->dockWidget()->guestView().get());
        auto guestItem2 = dock2->guestItem();
        QVERIFY(guestItem2);
        auto guestItem3 = dock3->guestItem();
        QVERIFY(guestItem3);
        auto guestItem4 = dock4->guestItem();
        QVERIFY(guestItem4);

        QQmlContext *guestContext1 = QtQuick::qmlContextFor(guestItem1);
        QQmlContext *guestContext2 = QtQuick::qmlContextFor(guestItem2);
        QQmlContext *guestContext3 = QtQuick::qmlContextFor(guestItem3);
        QQmlContext *guestContext4 = QtQuick::qmlContextFor(guestItem4);

        QVERIFY(guestContext1);
        QVERIFY(guestContext2);
        QVERIFY(guestContext3);
        QVERIFY(guestContext4);
        QVERIFY(guestContext1 != guestContext2);
        QVERIFY(guestContext1 != guestContext3);
        QVERIFY(guestContext2 != guestContext3);
        QCOMPARE(guestContext4->parentContext(), &subContext);
        QVERIFY(rootContext != guestContext1);
        QVERIFY(rootContext != guestContext2);
        QVERIFY(guestContext1->parentContext() == rootContext);
        QVERIFY(guestContext2->parentContext() == rootContext);
        QVERIFY(guestContext3->parentContext() == rootContext);

        QCOMPARE(guestItem3->property("someValue"), defaultPropertyValue);
        QCOMPARE(guestItem4->property("someValue"), overriddenPropertyValue);

        delete dock1->dockWidget()->dptr()->group();
        delete dock2->dockWidget()->dptr()->group();
        delete dock3->dockWidget()->dptr()->group();
        delete dock4->dockWidget()->dptr()->group();
    }

    // 1 event loop for DelayedDelete. Avoids LSAN warnings.
    EVENT_LOOP(1);
}

void TestQtQuick::tst_focusBetweenTabs()
{
    EnsureTopLevelsDeleted e;
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_TitleBarIsFocusable);
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("_kddwDockRegistry", DockRegistry::self());
    engine.load(":/main_tst_focusBetweenTabs.qml");

    auto dock1 = DockRegistry::self()->dockByName("dock1");
    auto dock2 = DockRegistry::self()->dockByName("dock2");
    auto dock3 = DockRegistry::self()->dockByName("dock3");
    auto floatingDock = DockRegistry::self()->dockByName("floatingDock");

    dock1->view()->rootView()->activateWindow();
    EVENT_LOOP(2000);
    dock1->dptr()->group()->focus();

    QVERIFY(dock1->isFocused());
    QVERIFY(!dock2->isFocused());
    QVERIFY(!dock3->isFocused());
    QVERIFY(!floatingDock->isFocused());

    auto view1 = QtCommon::View_qt::asQQuickItem(dock1->view());
    auto view2 = QtCommon::View_qt::asQQuickItem(dock2->view());
    auto view3 = QtCommon::View_qt::asQQuickItem(dock3->view());
    auto floatingDockView = QtCommon::View_qt::asQQuickItem(floatingDock->view());

    // Refocus these, as they were unfocused due to reparenting:
    auto field1 = view1->findChild<QQuickItem *>("field1");
    auto field2 = view2->findChild<QQuickItem *>("field2");
    auto field3 = view3->findChild<QQuickItem *>("field3");
    auto floatingDockField = floatingDockView->findChild<QQuickItem *>("floatingDockField");
    field2->setFocus(true);
    field3->setFocus(true);
    floatingDockField->setFocus(true);

    QVERIFY(dock1->isFocused());
    QVERIFY(!dock2->isFocused());
    QVERIFY(!dock3->isFocused());

    // All 4 have focus, but only #1 has active focus
    QVERIFY(field1->hasActiveFocus());
    QVERIFY(!field2->hasActiveFocus());
    QVERIFY(!field3->hasActiveFocus());
    QVERIFY(!floatingDockField->hasActiveFocus());
    QVERIFY(field1->hasFocus());
    QVERIFY(field2->hasFocus());
    QVERIFY(field3->hasFocus());
    QVERIFY(floatingDockField->hasFocus());

    dock2->dptr()->group()->focus();

    // Dock3, the current tab, has focus now
    QVERIFY(!field1->hasActiveFocus());
    QVERIFY(!field2->hasActiveFocus());
    QVERIFY(field3->hasActiveFocus());
    QVERIFY(field1->hasFocus());
    QVERIFY(field2->hasFocus());
    QVERIFY(field3->hasFocus());

    // A mouse event instead of these 2 lines would do as well
    dock2->setAsCurrentTab();
    dock2->dptr()->group()->focus();

    QVERIFY(field1->hasFocus());
    QVERIFY(field2->hasFocus());
    QVERIFY(field3->hasFocus());
    QVERIFY(!field1->hasActiveFocus());
    QVERIFY(field2->hasActiveFocus());
    QVERIFY(!field3->hasActiveFocus());

    // Now test if clicking on the dock1 titlebar also forwards focus
    auto tb = dock1->titleBar()->view();
    Tests::clickOn(tb->mapToGlobal({ 10, 10 }), tb);
    QVERIFY(field1->hasFocus());
    QVERIFY(field2->hasFocus());
    QVERIFY(field3->hasFocus());
    QVERIFY(field1->hasActiveFocus());
    QVERIFY(!field2->hasActiveFocus());
    QVERIFY(!field3->hasActiveFocus());

    // Now test titlebar of a floating window
    floatingDock->view()->rootView()->activateWindow();
    QVERIFY(Platform::instance()->tests_waitForWindowActive(floatingDock->view()->window(), 1000));
    auto floatingTb = floatingDock->titleBar()->view();
    Tests::clickOn(floatingTb->mapToGlobal({ 10, 10 }), floatingTb);

    Platform::instance()->tests_wait(1000);

    QVERIFY(field1->hasFocus());
    QVERIFY(field2->hasFocus());
    QVERIFY(field3->hasFocus());
    QVERIFY(floatingDockField->hasFocus());

    QVERIFY(floatingDockField->hasActiveFocus());

    // 1 event loop for DelayedDelete. Avoids LSAN warnings.
    KDDW_CO_AWAIT
    Platform::instance()
        ->tests_wait(1);
}

void TestQtQuick::tst_setPersistentCentralView()
{
    EnsureTopLevelsDeleted e;
    QQmlApplicationEngine engine(":/main_persistentCentralWidget.qml");
    const auto mainWindows = DockRegistry::self()->mainwindows();
    QCOMPARE(mainWindows.size(), 1);
    auto mainWindow = mainWindows.first();
    static_cast<QtQuick::MainWindow *>(mainWindow->view())->setPersistentCentralView(":/MyRectangle2.qml");

    Core::Layout *layout = mainWindow->layout();
    auto rootItem = layout->rootItem();
    QCOMPARE(rootItem->count_recursive(), 1);
    QCOMPARE(mainWindow->size(), rootItem->size());
}

void TestQtQuick::tst_mdiFixedSize()
{
    // Tests that the mdi group is fixed size if the dock widget is fixed size

    EnsureTopLevelsDeleted e;

    auto m = createMainWindow(Size(800, 500), MainWindowOption_MDI);
    const int fixedWidth = 201;
    auto dock0 = createDockWidget(
        "dock0", Platform::instance()->tests_createView({ true, {}, Size(fixedWidth, 400) }));
    dock0->view()->setFixedWidth(fixedWidth);
    m->layout()->asMDILayout()->addDockWidget(dock0, Point(0, 0), {});
    m->view()->resize(1000, 1000);

    QCOMPARE(dock0->view()->minimumWidth(), fixedWidth);
    QCOMPARE(dock0->view()->maxSizeHint().width(), fixedWidth);
    QVERIFY(dock0->isFixedWidth());
    Group *group = dock0->dptr()->group();
    QVERIFY(group->isMDI());
    QVERIFY(group->isFixedWidth());

    // 1 event loop for DelayedDelete. Avoids LSAN warnings.
    Platform::instance()
        ->tests_wait(1);
}

void TestQtQuick::tst_affinities()
{
    // Tests that the QML API for affinites works
    EnsureTopLevelsDeleted e;
    QQmlApplicationEngine engine(":/main465.qml");

    const auto dockingAreas = DockRegistry::self()->mainDockingAreas();
    QCOMPARE(dockingAreas.size(), 1);

    auto dockingArea = dockingAreas.first();
    QCOMPARE(dockingArea->affinities(), QVector<QString>({ "affinity_one", "affinity_two" }));

    auto dock1 = DockRegistry::self()->dockByName("dock1");
    auto dock2 = DockRegistry::self()->dockByName("dock2");
    QVERIFY(dock1);
    QVERIFY(dock2);

    QCOMPARE(dock1->affinities(), QVector<QString>({ "affinity_one", "affinity_two" }));
    QVERIFY(dock2->affinities().isEmpty());
}

void TestQtQuick::tst_deleteDockWidget()
{
    // Tests that we can delete a dock widget directly
    EnsureTopLevelsDeleted e;
    QQmlApplicationEngine engine(":/main465.qml"); // or any other main.qml

    auto dock0 = createDockWidget(
        "dock0", Platform::instance()->tests_createView({}));

    dock0->show();
    delete dock0->view();

    // 1 event loop iteration so we don't have memory leaks
    QTest::qWait(1);
}

void TestQtQuick::tst_effectiveVisibilityBug()
{
    // When saving layout state, we should not store QQuickItem::isVisible(), as that is not the real
    // "isVisible", as it might depend on the parent being visible or not.
    // The correct property to store is QQuickItemPrivate::explicitVisible, and not
    // QQuickItemPrivate::effectiveVisible;
    //
    // See issue #343

    QByteArray serialized;

    {
        EnsureTopLevelsDeleted e;
        // This main .qml has the DropArea wrapped into an Item with visible: false
        QQmlApplicationEngine engine(":/main343.qml");
        LayoutSaver saver;
        serialized = saver.serializeLayout();
        QVERIFY(!serialized.isEmpty());
    }

    EnsureTopLevelsDeleted e;
    // This main .qml has the DropArea wrapped into an Item with visible: true
    // restoring should restore the DropArea with visible true
    QQmlApplicationEngine engine(":/main343_2.qml");
    LayoutSaver restorer;
    QVERIFY(restorer.restoreLayout(serialized));

    const auto mainWindows = DockRegistry::self()->mainwindows();
    QCOMPARE(mainWindows.size(), 1);
    QVERIFY(mainWindows.first()->isVisible());
}

void TestQtQuick::tst_setViewFactory()
{
    // Tests that setting a view factory will refresh the context property
    EnsureTopLevelsDeleted e;
    QQmlApplicationEngine engine(":/main2.qml");
    QQmlContext *rootContext = plat()->qmlEngine()->rootContext();

    QCOMPARE(rootContext->contextProperty("_kddw_widgetFactory").value<QObject *>(), Config::self().viewFactory());

    // now change view factory:
    auto newFactory = Platform::instance()->createDefaultViewFactory();
    Config::self().setViewFactory(newFactory);
    QCOMPARE(rootContext->contextProperty("_kddw_widgetFactory").value<QObject *>(), newFactory);
}

void TestQtQuick::tst_quickWindowCreationCallback()
{
    EnsureTopLevelsDeleted e;
    QQmlApplicationEngine engine(":/main2.qml");

    int callCount = 0;
    auto onWindowCreated = [&](QQuickView *window, QtQuick::MainWindow *parent) -> void {
        Q_UNUSED(window);
        Q_UNUSED(parent);
        callCount++;
    };
    QtQuick::FloatingWindow::setQuickWindowCreationCallback(onWindowCreated);

    auto dock0 = createDockWidget(
        "dock0", Platform::instance()->tests_createView({ true, {}, QSize(400, 400) }));
    dock0->setFloating(true);

    QCOMPARE(callCount, 1);
    QtQuick::FloatingWindow::setQuickWindowCreationCallback(nullptr);
}

int main(int argc, char *argv[])
{
#ifdef KDDW_HAS_SPDLOG
    FatalLogger::create();
#endif

    // Might be disabled by env var
    const auto frontends = Platform::frontendTypes();
    if (std::find(frontends.cbegin(), frontends.cend(), FrontendType::QtQuick) == frontends.cend())
        return 0;

    Core::Platform::tests_initPlatform(argc, argv, KDDockWidgets::FrontendType::QtQuick);

    TestQtQuick test;
    const int exitCode = QTest::qExec(&test, argc, argv);
    Core::Platform::tests_deinitPlatform();

    return exitCode;
}

#include "tst_qtquick.moc"

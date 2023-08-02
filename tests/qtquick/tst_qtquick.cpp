/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/// @file
/// @brief Here lives the tests that only apply to QtQuick

#include "kddockwidgets/KDDockWidgets.h"
#include "qtquick/views/TitleBar.h"
#include "core/MainWindow.h"
#include "core/Window_p.h"
#include "core/Platform.h"

#include "../utils.h"

#ifdef KDDW_HAS_SPDLOG
#include "../fatal_logger.h"
#endif

#include <QtTest/QTest>
#include <QQmlApplicationEngine>

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
    KDDW_CO_AWAIT Platform::instance()->tests_wait(1);
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

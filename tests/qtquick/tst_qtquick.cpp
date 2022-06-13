/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/// @file
/// @brief Here lives the tests that only apply to QtQuick

#include "Platform.h"
#include "KDDockWidgets.h"

#include "../utils.h"

#include <QtTest/QtTest>
#include <QQmlApplicationEngine>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Tests;
using namespace KDDockWidgets::Controllers;

class TestQtQuick : public QObject
{
    Q_OBJECT

public Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

private Q_SLOTS:
    void tst_restoreRestoresMainWindowPosition();
    void tst_hoverShowsDropIndicators();
};


void TestQtQuick::initTestCase()
{
    KDDockWidgets::Platform::instance()->installMessageHandler();
}

void TestQtQuick::cleanupTestCase()
{
    KDDockWidgets::Platform::instance()->uninstallMessageHandler();
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
    // For QtQuick on Windows, there was a bug where drop indicators wouldn't be shown if MainWindowBase
    // wasn't the root item.

    EnsureTopLevelsDeleted e;
    QQmlApplicationEngine engine(":/main2.qml");

    const auto mainWindows = DockRegistry::self()->mainwindows();
    QCOMPARE(mainWindows.size(), 1);
    MainWindow *m = mainWindows.first();

    m->window()->window()->setFramePosition(QPoint(500, 800));

    auto dock0 = createDockWidget("dock0", Platform::instance()->tests_createView({ true, {}, QSize(400, 400) }));

    auto floatingDockWidget = createDockWidget("floatingDockWidget", Platform::instance()->tests_createView({ true, {}, QSize(400, 400) }));

    m->addDockWidget(dock0, Location_OnLeft);

    const QPoint mainWindowCenterPos = m->mapToGlobal(m->geometry().center());

    QTest::qWait(100);

    auto fw = floatingDockWidget->floatingWindow();
    dragFloatingWindowTo(fw, mainWindowCenterPos);

    QCOMPARE(dock0->dptr()->frame()->dockWidgetCount(), 2);
}

int main(int argc, char *argv[])
{
    KDDockWidgets::Platform::tests_initPlatform(argc, argv, KDDockWidgets::FrontendType::QtQuick);

    TestQtQuick test;
    const int exitCode = QTest::qExec(&test, argc, argv);
    KDDockWidgets::Platform::tests_deinitPlatform();

    return exitCode;
}

#include "tst_qtquick.moc"

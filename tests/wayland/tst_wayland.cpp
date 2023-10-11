/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Joshua Goins <joshua.goins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "kddockwidgets/DockWidget.h"
#include "kddockwidgets/MainWindow.h"
#include "core/Group.h"
#include "core/Platform.h"
#include "core/TabBar.h"
#include "core/TitleBar.h"
#include "core/FloatingWindow.h"
#include "qtwidgets/views/FloatingWindow.h"
#include "qtwidgets/views/TabBar.h"

#include <KWayland/Client/connection_thread.h>
#include <KWayland/Client/fakeinput.h>
#include <KWayland/Client/registry.h>

#include <QApplication>
#include <QLabel>
#include <QSignalSpy>
#include <QStyle>
#include <QVBoxLayout>
#include <QtConcurrent>

// WAYLAND_TODO:
// - Remove QtConcurrent. We shouldn't run widget code on secondary threads.
// - Replace QThread::msleep() with QTest::qWait(), so event loop still runs


static KWayland::Client::FakeInput *input = nullptr;

QPoint getWindowTopLeft()
{
    const int titlebarHeight = QApplication::style()->pixelMetric(QStyle::PM_TitleBarHeight);
    return { 0, titlebarHeight + 10 };
}

QPoint getCenterOfTitlebar(const KDDockWidgets::QtWidgets::DockWidget &dockWidget)
{
    return dockWidget.actualTitleBar()->rect().center();
}

QPoint getCenterOfDockWidget(const KDDockWidgets::QtWidgets::DockWidget &dockWidget)
{
    return dockWidget.rect().center();
}

KDDockWidgets::QtWidgets::MainWindow *createMainWindow(const QString &name)
{
    auto mainWindow = new KDDockWidgets::QtWidgets::MainWindow(name);
    mainWindow->showMaximized();

    return mainWindow;
}

KDDockWidgets::QtWidgets::DockWidget *createDockWidget(const QString &name)
{
    auto dockWidget = new KDDockWidgets::QtWidgets::DockWidget(name);
    dockWidget->setWidget(new QWidget());
    return dockWidget;
}

// A QFuture for running the test, and the testing/cleanup function.
using TestFunc = std::pair<QFuture<void>, std::function<void()>>;

TestFunc tst_detachTitlebar()
{
    auto mainWindow = createMainWindow("detachtitle_window");

    auto dockWidget = createDockWidget(QStringLiteral("detachtitle_dock"));
    mainWindow->addDockWidget(dockWidget, KDDockWidgets::Location::Location_OnTop);

    auto tabbedDockWidget = createDockWidget(QStringLiteral("detachtitle_dock2"));
    mainWindow->addDockWidget(tabbedDockWidget, KDDockWidgets::Location::Location_OnRight);

    return { QtConcurrent::run([=]() {
                 // wait to settle
                 QThread::msleep(1000);

                 input->requestPointerMoveAbsolute(getWindowTopLeft() + getCenterOfTitlebar(*dockWidget));
                 input->requestPointerButtonPress(Qt::MouseButton::LeftButton);
                 QThread::msleep(1000);
                 input->requestPointerMoveAbsolute(getWindowTopLeft() + getCenterOfDockWidget(*dockWidget));
                 QThread::msleep(4000);
                 input->requestPointerButtonRelease(Qt::MouseButton::LeftButton);
                 QThread::msleep(1000);
             }),
             [=]() {
                 Q_ASSERT(dockWidget->isFloating());
                 mainWindow->close();
                 tabbedDockWidget->close();

                 mainWindow->deleteLater();
                 tabbedDockWidget->deleteLater();
             } };
}

TestFunc tst_detachTab()
{
    auto mainWindow = createMainWindow("detachtab_window");

    auto dockWidget = createDockWidget(QStringLiteral("detachtab_dock"));
    mainWindow->addDockWidget(dockWidget, KDDockWidgets::Location::Location_OnTop);

    auto tabbedDockWidget = createDockWidget(QStringLiteral("detachtab_dock2"));
    dockWidget->addDockWidgetAsTab(tabbedDockWidget);

    auto tabBar = dynamic_cast<KDDockWidgets::QtWidgets::TabBar *>(dockWidget->group()->tabBar()->view());

    return { QtConcurrent::run([=]() {
                 // wait to settle
                 QThread::msleep(1000);

                 const QRect secondTabRect = tabBar->rectForTab(1);

                 input->requestPointerMoveAbsolute(getWindowTopLeft() + tabBar->mapToGlobal(secondTabRect.center()));
                 input->requestPointerButtonClick(Qt::MouseButton::LeftButton);
                 QThread::msleep(10);
                 input->requestPointerButtonClick(Qt::MouseButton::LeftButton);
                 QThread::msleep(1000);
             }),
             [=]() {
                 Q_ASSERT(tabbedDockWidget->isFloating());
                 mainWindow->close();
                 tabbedDockWidget->close();

                 mainWindow->deleteLater();
                 tabbedDockWidget->deleteLater();
             } };
}

TestFunc tst_dragAndDrop()
{
    auto mainWindow = createMainWindow("draganddrop_window");

    auto dummyWidget = new QWidget();
    auto layout = new QVBoxLayout();
    dummyWidget->setLayout(layout);

    auto timeLabel = new QLabel("time:");
    layout->addWidget(timeLabel);

    // FIXME: This timer seems to be required for the tests to work? QEventLoop weirdness I bet...
    auto timer = new QTimer();
    timer->setInterval(1000);
    timer->setSingleShot(false);
    QObject::connect(timer, &QTimer::timeout, timer, [timeLabel] {
        static int time = 0;
        timeLabel->setText(QString("time: %1").arg(time++));
    });
    timer->start();

    auto dockWidget = createDockWidget(QStringLiteral("draganddrop_dock"));
    dockWidget->setWidget(dummyWidget);

    mainWindow->addDockWidget(dockWidget, KDDockWidgets::Location::Location_OnTop);

    auto tabbedDockWidget = createDockWidget(QStringLiteral("draganddrop_dock2"));
    tabbedDockWidget->open();

    auto window = dynamic_cast<KDDockWidgets::QtWidgets::FloatingWindow *>(tabbedDockWidget->group()->floatingWindow()->view());
    window->showMaximized();

    return { QtConcurrent::run([=]() {
                 // wait to settle
                 QThread::msleep(5000);

                 input->requestPointerMoveAbsolute(getWindowTopLeft() + getCenterOfTitlebar(*tabbedDockWidget));
                 QThread::msleep(1000);
                 input->requestPointerButtonPress(Qt::MouseButton::LeftButton);
                 QThread::msleep(1000);

                 input->requestPointerMove({ 100, 100 });
                 QThread::msleep(1000);

                 window->hide();

                 input->requestPointerMoveAbsolute(getWindowTopLeft() + getCenterOfDockWidget(*dockWidget));
                 QThread::msleep(1000);
                 input->requestPointerButtonRelease(Qt::MouseButton::LeftButton);
                 QThread::msleep(1000);
             }),
             [=]() {
                 Q_ASSERT(!tabbedDockWidget->isFloating());

                 mainWindow->close();
                 tabbedDockWidget->close();

                 mainWindow->deleteLater();
                 tabbedDockWidget->deleteLater();
             } };
}

const std::vector tests = {
    tst_dragAndDrop,
    tst_detachTab,
    tst_detachTitlebar,
};

static QFutureWatcher<void> watcher;
static std::function<void()> currentCleanupFunction;

void nextTest()
{
    static int currentTest = 0;

    if (currentTest >= static_cast<int>(tests.size())) {
        QApplication::quit();
        return;
    }

    const auto [future, cleanupFunction] = tests[currentTest++]();
    currentCleanupFunction = cleanupFunction;

    watcher.setFuture(future);
}

int main(int argc, char **argv)
{
    qputenv("QT_QPA_PLATFORM", "wayland");
    QApplication app(argc, argv);

    KWayland::Client::ConnectionThread *connection = KWayland::Client::ConnectionThread::fromApplication(qGuiApp);

    QObject::connect(&watcher, &QFutureWatcher<void>::finished, [] {
        currentCleanupFunction();
        nextTest();
    });

    KWayland::Client::Registry registry;
    registry.create(connection);
    registry.setup();

    QSignalSpy fakeInputSpy(&registry, &KWayland::Client::Registry::fakeInputAnnounced);
    fakeInputSpy.wait();

    const QList<QVariant> arguments = fakeInputSpy.takeFirst();

    input = registry.createFakeInput(arguments[0].toInt(), arguments[1].toInt(), connection);
    input->authenticate(QStringLiteral("KDDockWidgets Wayland Test"), QStringLiteral("For testing"));

    KDDockWidgets::initFrontend(KDDockWidgets::FrontendType::QtWidgets);

    nextTest();

    return QApplication::exec();
}

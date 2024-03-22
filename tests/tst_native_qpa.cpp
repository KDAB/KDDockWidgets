/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Config.h"
#include "utils.h"
#include "qtcommon/Window_p.h"
#include "core/MainWindow.h"
#include "core/DockWidget.h"
#include "core/Platform.h"

#include <QTimer>
#include <QtTest/QTest>


#ifdef KDDW_HAS_SPDLOG
#include "fatal_logger.h"
#endif

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;
using namespace KDDockWidgets::Tests;

/// Tests that should run in the native QPAs (windows, cocoa, xcb) instead of offscreen
/// To test functionality that usually is window manager dependent

class TestNativeQPA : public QObject
{
    Q_OBJECT
public Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

private Q_SLOTS:
    void tst_restoreNormalFromMaximized();
    void tst_restoreMaximizedFromNormal();
};

void TestNativeQPA::initTestCase()
{
    KDDockWidgets::Core::Platform::instance()->installMessageHandler();
}

void TestNativeQPA::cleanupTestCase()
{
    KDDockWidgets::Core::Platform::instance()->uninstallMessageHandler();
}

namespace {
// QWindow::windowStateChange() is not reliable, since we're only interested
// in the spontaneous events (async), as those reflect the window manager state
class MyEventFilter : public QObject
{
    Q_OBJECT
public:
    bool eventFilter(QObject *obj, QEvent *event) override
    {
        if (event->type() == QEvent::WindowStateChange) {
            if (event->spontaneous())
                Q_EMIT stateChanged(static_cast<QWindow *>(obj)->windowState());
        }

        return false;
    }

    bool waitForState(Qt::WindowState state)
    {
        bool result = false;
        QEventLoop loop;
        QTimer::singleShot(5000, &loop, [&loop] { loop.quit(); });
        connect(this, &MyEventFilter::stateChanged, &loop, [&](auto s) {
            if (state == s) {
                result = true;
                loop.quit();
            }
        });

        loop.exec();
        return result;
    }

Q_SIGNALS:
    void stateChanged(Qt::WindowState);
};
}

void TestNativeQPA::tst_restoreNormalFromMaximized()
{
    bool skip = false;

    if (qApp->platformName() == "cocoa") {
        // Broken on macOS
        skip = true;
    } else if (qApp->platformName() == "xcb") {
        // Broken on non-KDE maybe ?
        skip = qEnvironmentVariable("XDG_SESSION_DESKTOP") != QLatin1String("KDE");
    }

    if (skip)
        return;

    // Saves the window state while in normal state, then restores after the window is maximized
    // the window should become unmaximized.

    auto m = createMainWindow(Size(500, 500), MainWindowOption_None, "m1", false);

    auto windowptr = m->view()->window();
    auto window = static_cast<QtCommon::Window *>(windowptr.get());
    QWindow *qtwindow = window->qtWindow();
    MyEventFilter filter;
    qtwindow->installEventFilter(&filter);

    m->show();
    QVERIFY(m->isVisible());

    LayoutSaver saver;
    const QByteArray saved = saver.serializeLayout();

    m->view()->showMaximized();
    QVERIFY(filter.waitForState(Qt::WindowMaximized));
    QVERIFY(saver.restoreLayout(saved));
    QVERIFY(filter.waitForState(Qt::WindowNoState));
}

void TestNativeQPA::tst_restoreMaximizedFromNormal()
{
    // Saves the window state while in maximized state, then restores after the window is shown normal
    // the window should become maximized again.

    auto m = createMainWindow(Size(500, 500), MainWindowOption_None, "m1", false);

    auto windowptr = m->view()->window();
    auto window = static_cast<QtCommon::Window *>(windowptr.get());
    QWindow *qtwindow = window->qtWindow();
    MyEventFilter filter;
    qtwindow->installEventFilter(&filter);

    m->view()->showMaximized();
    QVERIFY(filter.waitForState(Qt::WindowMaximized));
    const auto expectedMaximizedGeometry = m->geometry();

    LayoutSaver saver;
    const QByteArray saved = saver.serializeLayout();

    m->view()->showNormal();
    QVERIFY(filter.waitForState(Qt::WindowNoState));

    QVERIFY(saver.restoreLayout(saved));
    QVERIFY(filter.waitForState(Qt::WindowMaximized));
    QVERIFY(m->isVisible());

    const bool isOffscreen = qApp->platformName() == QLatin1String("offscreen");
    if (Platform::instance()->isQtQuick() && !isOffscreen)
        QEXPECT_FAIL("", "Being fixed", Continue);

    QCOMPARE(m->geometry(), expectedMaximizedGeometry);
}

int main(int argc, char *argv[])
{
#ifdef Q_OS_LINUX
    if (!qEnvironmentVariableIsSet("DISPLAY")) {
        // Don't fail if we don't have X11. GitHub CI will use xvfb
        return 0;
    }
#endif

#ifdef KDDW_HAS_SPDLOG
    FatalLogger::create();
#endif

    int exitCode = 0;
    for (FrontendType type : Platform::frontendTypes()) {
        KDDockWidgets::Core::Platform::tests_initPlatform(argc, argv, type, /*defaultToOffscreenQPA=*/false);
        qDebug() << "\nTesting platform" << type << "on" << qApp->platformName() << "\n";

        TestNativeQPA test;

        const int code = QTest::qExec(&test, argc, argv);
        if (code != 0)
            exitCode = 1;
        KDDockWidgets::Core::Platform::tests_deinitPlatform();
    }

    return exitCode;
}

#include <tst_native_qpa.moc>

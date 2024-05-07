/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#define NOMINMAX

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
    void tst_restoreMaximizedFromMaximized();
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
            if (event->spontaneous()) {
                QWindow *window = static_cast<QWindow *>(obj);
                qDebug() << "WindowStateChange:" << int(window->windowState());
                m_lastState = window->windowState();
                Q_EMIT stateChanged(window->windowState());
            }
        } else if (event->type() == QEvent::Resize) {
            auto rev = static_cast<QResizeEvent *>(event);
            qDebug() << "Resize event. old=" << rev->oldSize() << "; new=" << rev->size();
        } else if (event->type() == QEvent::Move) {
            auto mev = static_cast<QMoveEvent *>(event);
            qDebug() << "Move event. old=" << mev->oldPos() << "; new=" << mev->pos();
        }

        return false;
    }

    bool waitForState(Qt::WindowState state)
    {
        if (m_lastState == state)
            return true;

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

public:
    int m_lastState = -1;
};
}

void TestNativeQPA::tst_restoreNormalFromMaximized()
{
#ifdef Q_OS_MACOS
    if (Platform::instance()->isQtQuick())
        return;
#endif

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
    if (qGuiApp->platformName() == QLatin1String("offscreen")) {
        // offscreen: calling showMaximized() on an hidden widget, puts it at pos=2,2 instead of 0,0
        // Ignore this QPA. This file is for testing native QPAs only. offscreen is nice to have
        // if it beahaves well only.
        return;
    }

#ifdef Q_OS_MACOS
    if (Platform::instance()->isQtQuick())
        return;
#endif

    // whitelist some macOS warning
    SetExpectedWarning warn("invalid window content view size");

    // Saves the window state while in maximized state, then restores after the window is shown normal
    // the window should become maximized again.
    // qDebug() << qApp->primaryScreen()->geometry();
    const QSize initialSize(500, 500);
    auto m = createMainWindow(initialSize, MainWindowOption_None, "m1", false);

    auto windowptr = m->view()->window();
    auto window = static_cast<QtCommon::Window *>(windowptr.get());
    QWindow *qtwindow = window->qtWindow();
    MyEventFilter filter;
    qtwindow->installEventFilter(&filter);

    m->view()->showMaximized();
    QVERIFY(filter.waitForState(Qt::WindowMaximized));

    int count = 0;
    // Qt annoyingly sends us 2 or 3 resize events before the fully maximized one, even when
    // already having state==Qt::WindowMaximized. Probably depends on platform.
    // Consume all resize events until window gets big.
    while (m->geometry().size().width() < 700) {
        QVERIFY(Platform::instance()->tests_waitForResize(m->view()));
        count++;
        QVERIFY(count < 5);
    }

    const auto expectedMaximizedGeometry = m->geometry();
    QVERIFY(initialSize != expectedMaximizedGeometry.size());

    LayoutSaver saver;
    const QByteArray saved = saver.serializeLayout();

    m->view()->showNormal();
    QVERIFY(filter.waitForState(Qt::WindowNoState));

    QVERIFY(saver.restoreLayout(saved));
    QVERIFY(filter.waitForState(Qt::WindowMaximized));
    QVERIFY(m->isVisible());

    /// Catch more resizes:
    QTest::qWait(1000);

    QCOMPARE(m->geometry(), expectedMaximizedGeometry);
}

void TestNativeQPA::tst_restoreMaximizedFromMaximized()
{
    if (qApp->platformName() == QLatin1String("offscreen")) {
        // offscreen: calling showMaximized() on an hidden widget, puts it at pos=2,2 instead of 0,0
        // Ignore this QPA. This file is for testing native QPAs only. offscreen is nice to have
        // if it beahaves well only.
        return;
    }

#ifdef Q_OS_MACOS
    if (Platform::instance()->isQtQuick())
        return;
#endif

    // whitelist some macOS warning
    SetExpectedWarning warn("invalid window content view size");

    // Saves the window state while in maximized state, then restores after the window is shown normal
    // the window should become maximized again.
    // qDebug() << qApp->primaryScreen()->geometry();
    const QSize initialSize(500, 500);
    auto m = createMainWindow(initialSize, MainWindowOption_None, "m1", false);

    auto windowptr = m->view()->window();
    auto window = static_cast<QtCommon::Window *>(windowptr.get());
    QWindow *qtwindow = window->qtWindow();
    MyEventFilter filter;
    qtwindow->installEventFilter(&filter);

    m->view()->showMaximized();
    QVERIFY(filter.waitForState(Qt::WindowMaximized));

    int count = 0;
    // Qt annoyingly sends us 2 or 3 resize events before the fully maximized one, even when
    // already having state==Qt::WindowMaximized. Probably depends on platform.
    // Consume all resize events until window gets big.
    while (m->geometry().size().width() < 700) {
        QVERIFY(Platform::instance()->tests_waitForResize(m->view()));
        count++;
        QVERIFY(count < 5);
    }

    const auto expectedMaximizedGeometry = m->geometry();
    QVERIFY(initialSize != expectedMaximizedGeometry.size());

    LayoutSaver saver;
    const QByteArray saved = saver.serializeLayout();

    QTest::qWait(1000);

    QVERIFY(saver.restoreLayout(saved));
    QVERIFY(filter.waitForState(Qt::WindowMaximized));

    // Catch more resizes:
    QTest::qWait(1000);

#if QT_VERSION > QT_VERSION_CHECK(6, 0, 0)
#ifdef Q_OS_LINUX
    if (Platform::instance()->isQtWidgets()) {
        // buggy on Linux, Qt6, QtWidgets. The window is visually maximixed but geometry is wrong
        return;
    }
#endif
#endif



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
        qDebug() << "\nTesting platform" << type << "on" << qGuiApp->platformName() << "\n";

        TestNativeQPA test;

        const int code = QTest::qExec(&test, argc, argv);
        if (code != 0)
            exitCode = 1;
        KDDockWidgets::Core::Platform::tests_deinitPlatform();
    }

    return exitCode;
}

#include <tst_native_qpa.moc>

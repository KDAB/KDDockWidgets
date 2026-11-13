/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// A minimal Wayland compositor for running KDDW tests against.
// Usage: kddw_test_compositor [options] -- <test executable> [test args]
//    or: kddw_test_compositor [options] --serve
//
// The first form runs the test as its only client and exits with the test's exit code.
// With --serve it prints the environment a client needs as KEY=VALUE lines followed by
// "READY", and runs until stdin is closed. Tests use it to start a compositor themselves.
// The test drives input through the kddw-test-v1 protocol, see ../protocol/kddw-test-v1.xml.

#include "TestExtension.h"

#include <QCommandLineParser>
#include <QFile>
#include <QGuiApplication>
#include <QProcess>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include <QSocketNotifier>
#include <QTemporaryDir>
#include <QTimer>
#include <QWaylandCompositor>
#include <QWaylandOutput>

#include <cstdio>

#include <unistd.h>

int main(int argc, char **argv)
{
    // Everything after "--" belongs to the client, don't let QGuiApplication parse it
    int compositorArgc = argc;
    QStringList clientArgs;
    for (int i = 1; i < argc; ++i) {
        if (qstrcmp(argv[i], "--") == 0) {
            compositorArgc = i;
            for (int j = i + 1; j < argc; ++j)
                clientArgs << QString::fromLocal8Bit(argv[j]);
            break;
        }
    }

    bool visible = false;
    for (int i = 1; i < compositorArgc; ++i) {
        if (qstrcmp(argv[i], "--visible") == 0)
            visible = true;
    }

    // By default nothing is shown and no GPU is needed. --visible shows the compositor in a
    // window on the current desktop, to watch what a test is doing.
    if (!visible)
        qputenv("QT_QPA_PLATFORM", "offscreen");
    QQuickWindow::setGraphicsApi(QSGRendererInterface::Software);

    QGuiApplication app(compositorArgc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription(QStringLiteral("Wayland compositor for running KDDockWidgets tests"));
    parser.addHelpOption();
    parser.addPositionalArgument(QStringLiteral("-- client"), QStringLiteral("The test to run, and its arguments"));
    const QCommandLineOption visibleOption(QStringLiteral("visible"),
                                           QStringLiteral("Show the compositor window"));
    const QCommandLineOption timeoutOption(QStringLiteral("timeout"),
                                           QStringLiteral("Kill the client after <seconds>"),
                                           QStringLiteral("seconds"), QStringLiteral("300"));
    const QCommandLineOption sizeOption(QStringLiteral("size"), QStringLiteral("Output size"),
                                        QStringLiteral("WxH"), QStringLiteral("1920x1080"));
    const QCommandLineOption stepDelayOption(QStringLiteral("step-delay"),
                                             QStringLiteral("Delay between input actions"),
                                             QStringLiteral("msecs"), QStringLiteral("5"));
    const QCommandLineOption serveOption(
        QStringLiteral("serve"),
        QStringLiteral("Don't start a client. Print the client environment and run until stdin is closed"));
    parser.addOptions({ visibleOption, timeoutOption, sizeOption, stepDelayOption, serveOption });
    parser.process(app);

    const bool serve = parser.isSet(serveOption);
    if (serve == !clientArgs.isEmpty()) {
        std::fputs("Usage: kddw_test_compositor [options] -- <client> [args]\n"
                   "       kddw_test_compositor [options] --serve\n",
                   stderr);
        return 2;
    }

    const QStringList size = parser.value(sizeOption).split(QLatin1Char('x'));
    const QSize outputSize = size.size() == 2 ? QSize(size[0].toInt(), size[1].toInt()) : QSize();
    if (outputSize.isEmpty()) {
        std::fputs("Invalid --size, expected WxH\n", stderr);
        return 2;
    }

    // Use a private runtime dir, so parallel runs don't clash and no session is required.
    // Set only after QGuiApplication, which in --visible mode already connected to the host.
    QTemporaryDir runtimeDir;
    if (!runtimeDir.isValid()) {
        std::fputs("Failed to create a runtime directory\n", stderr);
        return 2;
    }
    qputenv("XDG_RUNTIME_DIR", QFile::encodeName(runtimeDir.path()));
    const QString socketName = QStringLiteral("kddw-test-%1").arg(QCoreApplication::applicationPid());

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("kddwSocketName"), socketName);
    engine.rootContext()->setContextProperty(QStringLiteral("kddwOutputSize"), outputSize);
    engine.load(QUrl(QStringLiteral("qrc:/kddw_test_compositor/main.qml")));

    auto compositor = engine.rootObjects().isEmpty()
        ? nullptr
        : qobject_cast<QWaylandCompositor *>(engine.rootObjects().constFirst());
    if (!compositor || !compositor->isCreated()) {
        std::fputs("Failed to create the compositor\n", stderr);
        return 2;
    }

    auto window = qobject_cast<QQuickWindow *>(compositor->defaultOutput()->window());
    auto extension = new TestExtension(compositor, window);
    extension->setStepDelay(parser.value(stepDelayOption).toInt());
    extension->initialize();

    const QList<std::pair<QString, QString>> clientEnv = {
        { QStringLiteral("WAYLAND_DISPLAY"), socketName },
        { QStringLiteral("XDG_RUNTIME_DIR"), runtimeDir.path() },
        { QStringLiteral("QT_QPA_PLATFORM"), QStringLiteral("wayland") },
        { QStringLiteral("QT_WAYLAND_SHELL_INTEGRATION"), QStringLiteral("xdg-shell") },
        { QStringLiteral("QT_WAYLAND_DISABLE_WINDOWDECORATION"), QStringLiteral("1") },
        { QStringLiteral("QT_SCALE_FACTOR"), QStringLiteral("1") },
        // KDDW tests force the offscreen QPA otherwise
        { QStringLiteral("KDDW_NO_OFFSCREEN"), QStringLiteral("1") },
        // So tests know they don't need to start a compositor themselves
        { QStringLiteral("KDDW_IN_TEST_COMPOSITOR"), QStringLiteral("1") },
    };

    if (serve) {
        for (const auto &[name, value] : clientEnv)
            std::printf("%s=%s\n", qPrintable(name), qPrintable(value));
        std::puts("READY");
        std::fflush(stdout);
        // The client might stop reading stdout, don't risk SIGPIPE
        ::dup2(STDERR_FILENO, STDOUT_FILENO);

        // The client keeps our stdin open for as long as it's alive, even if it crashes
        QSocketNotifier stdinNotifier(STDIN_FILENO, QSocketNotifier::Read);
        QObject::connect(&stdinNotifier, &QSocketNotifier::activated, &app, [&app, &stdinNotifier] {
            char buf[64];
            if (::read(STDIN_FILENO, buf, sizeof(buf)) <= 0) {
                stdinNotifier.setEnabled(false);
                app.quit();
            }
        });

        return app.exec();
    }

    QProcess client;
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    for (const auto &[name, value] : clientEnv)
        env.insert(name, value);
    client.setProcessEnvironment(env);
    client.setProcessChannelMode(QProcess::ForwardedChannels);

    QObject::connect(&client, &QProcess::finished, &app, [&app](int exitCode, QProcess::ExitStatus status) {
        if (status == QProcess::CrashExit) {
            std::fputs("kddw_test_compositor: client crashed\n", stderr);
            app.exit(1);
        } else {
            app.exit(exitCode);
        }
    });

    QObject::connect(&client, &QProcess::errorOccurred, &app, [&app, &client](QProcess::ProcessError error) {
        if (error == QProcess::FailedToStart) {
            std::fprintf(stderr, "kddw_test_compositor: failed to start client: %s\n",
                         qPrintable(client.errorString()));
            app.exit(127);
        }
    });

    const int timeoutSecs = parser.value(timeoutOption).toInt();
    QTimer::singleShot(timeoutSecs * 1000, &app, [&app, &client, timeoutSecs] {
        std::fprintf(stderr, "kddw_test_compositor: client timed out after %ds\n", timeoutSecs);
        QObject::disconnect(&client, nullptr, &app, nullptr);
        client.kill();
        app.exit(124);
    });

    client.start(clientArgs.takeFirst(), clientArgs);

    const int exitCode = app.exec();

    if (client.state() != QProcess::NotRunning) {
        client.kill();
        client.waitForFinished();
    }

    return exitCode;
}

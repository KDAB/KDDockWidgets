/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include <QCommandLineParser>
#include <QCoreApplication>
#include <QFileInfo>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTextStream>

#include <cstdlib>

static QtMessageHandler s_oldMessageHandler = nullptr;

static void fatalMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    if (s_oldMessageHandler)
        s_oldMessageHandler(type, context, msg);

    if (type == QtDebugMsg || type == QtInfoMsg)
        return;

    if (msg.startsWith(QLatin1String("QFontDatabase:")))
        return;

    if (context.category && QString::fromLatin1(context.category).startsWith(QLatin1String("qt.qpa")))
        return;

    std::abort();
}

int main(int argc, char **argv)
{
    s_oldMessageHandler = qInstallMessageHandler(fatalMessageHandler);

    QGuiApplication app(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription(QStringLiteral("Loads a QML file, optionally adding an import path"));
    parser.addHelpOption();

    QCommandLineOption importPathOption(
        QStringList() << QStringLiteral("I"), QStringLiteral("Path to add to the QML import path"),
        QStringLiteral("path"));
    parser.addOption(importPathOption);

    parser.addPositionalArgument(
        QStringLiteral("file"), QStringLiteral("The .qml file to load"), QStringLiteral("file.qml"));

    parser.process(app);

    QTextStream errStream(stderr);

    const QStringList positionalArgs = parser.positionalArguments();
    if (positionalArgs.size() != 1) {
        errStream << "Error: Expected exactly one .qml file argument\n";
        return 1;
    }

    const QString &qmlFile = positionalArgs.first();
    if (!qmlFile.endsWith(QStringLiteral(".qml"), Qt::CaseInsensitive)) {
        errStream << "Error: File does not have a .qml extension: " << qmlFile << "\n";
        return 1;
    }

    if (!QFileInfo::exists(qmlFile)) {
        errStream << "Error: File does not exist: " << qmlFile << "\n";
        return 1;
    }

    QString importPath;
    if (parser.isSet(importPathOption)) {
        importPath = parser.value(importPathOption);
        if (!QFileInfo::exists(importPath)) {
            errStream << "Error: Import path does not exist: " << importPath << "\n";
            return 1;
        }
    }

    QQmlApplicationEngine engine;
    if (!importPath.isEmpty())
        engine.addImportPath(importPath);

    bool ok = true;
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
        [&ok] { ok = false; }, Qt::QueuedConnection);

    engine.load(QUrl::fromLocalFile(qmlFile));

    if (!ok || engine.rootObjects().isEmpty())
        return 1;

    return QGuiApplication::exec();
}

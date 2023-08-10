/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Config.h"
#include "qtwidgets/ViewFactory.h"

#include "core/MainWindow.h"
#include "core/DockWidget.h"
#include "core/Platform.h"

#include <QDebug>
#include <QString>
#include <QGuiApplication>
#include <QCommandLineParser>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;

struct LinterConfig
{
    QStringList filesToLint;

    bool isEmpty() const
    {
        return filesToLint.isEmpty();
    }
};

LinterConfig requestedLinterConfig(const QCommandLineParser &parser)
{
    LinterConfig c;
    c.filesToLint = parser.positionalArguments();

    return c;
}

static bool lint(const QString &filename, RestoreOptions options)
{
    DockWidgetFactoryFunc dwFunc = [](const QString &dwName) {
        return Config::self().viewFactory()->createDockWidget(dwName)->asDockWidgetController();
    };

    MainWindowFactoryFunc mwFunc = [](const QString &mwName, MainWindowOptions mainWindowOptions) {
        return Platform::instance()->createMainWindow(mwName, {}, mainWindowOptions);
    };

    KDDockWidgets::Config::self().setDockWidgetFactoryFunc(dwFunc);
    KDDockWidgets::Config::self().setMainWindowFactoryFunc(mwFunc);

    LayoutSaver restorer(options);
    return restorer.restoreFromFile(filename);
}

int main(int argc, char *argv[])
{
    const auto frontends = Platform::frontendTypes();
    if (frontends.empty()) {
        qWarning() << "Error: Your KDDockWidgets installation doesn't support any frontend!";
        return -1;
    }

    // Just take the 1st frontend, any is fine
    KDDockWidgets::Core::Platform::tests_initPlatform(argc, argv, frontends[0]);

    QCommandLineParser parser;
    parser.setApplicationDescription("KDDockWidgets layout linter");
    parser.addHelpOption();
    parser.addPositionalArgument("layout", "layout json file");
    parser.process(*qApp);

    const LinterConfig lc = requestedLinterConfig(parser);

    if (lc.isEmpty()) {
        qWarning() << "Expected a layout file";
        return 3;
    }

    const auto options = RestoreOption_None;

    int exitCode = 0;
    for (const QString &layout : lc.filesToLint) {
        if (!lint(qGuiApp->arguments().at(1), options))
            exitCode = 2;
    }

    KDDockWidgets::Core::Platform::tests_deinitPlatform();
    return exitCode;
}

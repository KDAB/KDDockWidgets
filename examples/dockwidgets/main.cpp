/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "MyWidget.h"
#include "MyMainWindow.h"
#include "MyFrameworkWidgetFactory.h"

#include <kddockwidgets/Config.h>

#include <QStyleFactory>
#include <QApplication>
#include <QDebug>
#include <QCommandLineParser>

using namespace KDDockWidgets;

int main(int argc, char **argv)
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication app(argc, argv);

    app.setOrganizationName(QStringLiteral("KDAB"));
    app.setApplicationName(QStringLiteral("Test app"));

    QCommandLineParser parser;
    parser.setApplicationDescription("KDDockWidgets example application");
    parser.addHelpOption();

    qApp->setStyle(QStyleFactory::create(QStringLiteral("Fusion")));

    QCommandLineOption customStyle("p", QCoreApplication::translate("main", "Shows how to style framework internals via FrameworkWidgetFactory"));
    parser.addOption(customStyle);

    QCommandLineOption reorderTabsOption("r", QCoreApplication::translate("main", "Support re-ordering tabs with mouse"));
    parser.addOption(reorderTabsOption);

    QCommandLineOption noTitleBars("t", QCoreApplication::translate("main", "Never show titlebars"));
    parser.addOption(noTitleBars);

#if defined(DOCKS_DEVELOPER_MODE)
    QCommandLineOption noCentralFrame("c", QCoreApplication::translate("main", "No central frame"));
    parser.addOption(noCentralFrame);
#endif

    parser.process(app);

    if (parser.isSet(customStyle)) {
        Config::self().setFrameworkWidgetFactory(new CustomWidgetFactory()); // Sets our custom factory

        // Increase the separator size, just for demo
        Config::self().setSeparatorThickness(10, /*static=*/ false);
    }

    MainWindowOptions options = MainWindowOption_None;
#if defined(DOCKS_DEVELOPER_MODE)
    options = parser.isSet(noCentralFrame) ? MainWindowOption_None
                                           : MainWindowOption_HasCentralFrame;
#endif

    auto flags = KDDockWidgets::Config::self().flags();
    if (parser.isSet(noTitleBars))
        flags |= KDDockWidgets::Config::Flag_HideTitleBarWhenTabsVisible | KDDockWidgets::Config::Flag_AlwaysShowTabs;

    if (parser.isSet(reorderTabsOption))
        flags |= KDDockWidgets::Config::Flag_AllowReorderTabs;

    KDDockWidgets::Config::self().setFlags(flags);

    MyMainWindow mainWindow(options);
    mainWindow.resize(1200, 1200);
    mainWindow.show();

    return app.exec();
}

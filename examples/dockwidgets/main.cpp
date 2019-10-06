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

#include <kddockwidgets/Config.h>

#include <QStyleFactory>
#include <QApplication>
#include <QDebug>
#include <QVBoxLayout>
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

    QCommandLineOption noTitleBars("t", QCoreApplication::translate("main", "Never show titlebars"));
    parser.addOption(noTitleBars);

    /// For testing QMainWindow embedded in MFC
    QCommandLineOption embeddedMainWindow("r", QCoreApplication::translate("main", "Embed main window"));
    QCommandLineOption noCentralFrame("c", QCoreApplication::translate("main", "No central frame"));

#if defined(DOCKS_DEVELOPER_MODE)
    parser.addOption(embeddedMainWindow);
    parser.addOption(noCentralFrame);
#endif

    parser.process(app);

    bool embedded = false;
    MainWindowOptions options = MainWindowOption_None;
#if defined(DOCKS_DEVELOPER_MODE)
    embedded = parser.isSet(embeddedMainWindow);
    options = parser.isSet(noCentralFrame) ? MainWindowOption_None
                                           : MainWindowOption_HasCentralFrame;
#endif

    if (parser.isSet(noTitleBars))
        KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flags() | KDDockWidgets::Config::Flag_HideTitleBarWhenTabsVisible | KDDockWidgets::Config::Flag_AlwaysShowTabs);

    MyMainWindow mainWindow(options);
    QWidget *window;
    if (embedded) {
        window = new QWidget();
        auto lay = new QVBoxLayout(window);
        lay->addWidget(&mainWindow);
    } else {
        window = &mainWindow;
    }

    window->resize(1000, 800);
    window->show();

    return app.exec();
}

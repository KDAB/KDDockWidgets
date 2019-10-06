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

using namespace KDDockWidgets;

int main(int argc, char **argv)
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication app(argc, argv);
    //KDDockWidgets::Config::self().setFlags( KDDockWidgets::Config::Flags() | KDDockWidgets::Config::Flag_HideTitleBarWhenTabsVisible | KDDockWidgets::Config::Flag_AlwaysShowTabs);
    //KDDockWidgets::Config::self().setFlags( KDDockWidgets::Config::Flags() | KDDockWidgets::Config::Flag_AlwaysShowTabs);
    app.setOrganizationName(QStringLiteral("KDAB"));
    app.setApplicationName(QStringLiteral("Test app"));
    qApp->setStyle(QStyleFactory::create(QStringLiteral("Fusion")));

    const bool embedded = app.arguments().contains(QStringLiteral("--embedded"));
    const bool noCentralFrame = app.arguments().contains(QStringLiteral("--no-central"));
    MainWindowOptions options = noCentralFrame ? MainWindowOption_None
                                               : MainWindowOption_HasCentralFrame;

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

/*
  This file is part of KDDockWidgets.

  Copyright (C) 2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "Config.h"
#include "DockWidget.h"
#include "MainWindow.h"

#include <QApplication>
#include <QDebug>
#include <QString>

using namespace KDDockWidgets;

static bool lint(const QString &filename)
{
    DockWidgetFactoryFunc dwFunc = [] (const QString &dwName) {
        return static_cast<DockWidgetBase*>(new DockWidget(dwName));
    };

    MainWindowFactoryFunc mwFunc = [] (const QString &dwName) {
        return static_cast<MainWindowBase*>(new MainWindow(dwName));
    };

    KDDockWidgets::Config::self().setDockWidgetFactoryFunc(dwFunc);
    KDDockWidgets::Config::self().setMainWindowFactoryFunc(mwFunc);

    LayoutSaver restorer;
    return restorer.restoreFromFile(filename);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if (app.arguments().size() != 2) {
        qDebug() << "Usage: kddockwidgets_linter <layout json file>";
        return 1;
    }

    return lint(app.arguments().at(1)) ? 0 : 2;
}

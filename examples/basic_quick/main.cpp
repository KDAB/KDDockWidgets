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


#include "DockRegistry_p.h"
#include "Config.h"

#include <QQuickView>
#include <QGuiApplication>


int main(int argc, char **argv)
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QGuiApplication app(argc, argv);
    app.setOrganizationName(QStringLiteral("KDAB"));
    app.setApplicationName(QStringLiteral("Test app"));

    KDDockWidgets::DockRegistry::self(); // TODO: Remove. Right now registers qml types.

    QQuickView view;

    KDDockWidgets::Config::self().setQmlEngine(view.engine());

    view.setSource(QUrl("qrc:/main.qml"));
    view.resize(500, 500);
    view.show();

    return app.exec();
}

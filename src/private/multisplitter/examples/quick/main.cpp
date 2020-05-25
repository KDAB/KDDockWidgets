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

#include "controller.h"
#include "Item_p.h"
#include "multisplitter.h"
#include "Config.h"
#include "Separator_quick.h"

#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>
#include <QQmlEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickView view;

    qmlRegisterType<Layouting::MultiSplitter>("com.kdab.kddockwidgets.multisplitter", 1, 0, "MultiSplitter");

    Layouting::Config::self().setSeparatorFactoryFunc([] (Layouting::Widget *parent) {
        return static_cast<Layouting::Separator*>(new Layouting::SeparatorQuick(parent));
    });

    view.setSource(QUrl("qrc:/main.qml"));
    auto multisplitter = qobject_cast<Layouting::MultiSplitter*>(view.rootObject());
    Controller controller(multisplitter); // just an object to expose properties to QML
    view.rootContext()->setContextProperty("_controller", &controller);

    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.resize(1200, 800);
    view.show();

    return app.exec();
}

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "controller.h"
#include "Item_p.h"
#include "multisplitter.h"
#include "MultiSplitterConfig.h"
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

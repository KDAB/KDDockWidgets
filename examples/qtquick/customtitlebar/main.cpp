/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sergio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/


#include <kddockwidgets/Config.h>
#include "qtquick/views/DockWidget_qtquick.h"
#include "qtquick/Platform_qtquick.h"
#include "qtquick/ViewFactory_qtquick.h"

#include <kddockwidgets/private/DockRegistry_p.h>

#include <QQuickView>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

class CustomViewFactory : public KDDockWidgets::ViewFactory_qtquick
{
public:
    ~CustomViewFactory() override;

    QUrl titleBarFilename() const override
    {
        return QUrl("qrc:/MyTitleBar.qml");
    }
};

CustomViewFactory::~CustomViewFactory() = default;

int main(int argc, char *argv[])
{
#ifdef Q_OS_WIN
    QGuiApplication::setAttribute(Qt::AA_UseOpenGLES);
#endif
    QGuiApplication app(argc, argv);

    auto &config = KDDockWidgets::Config::self();
    auto flags = config.flags();

    config.setFlags(flags);
    config.setViewFactory(new CustomViewFactory());

    QQmlApplicationEngine appEngine;
    KDDockWidgets::Platform_qtquick::instance()->setQmlEngine(&appEngine);
    appEngine.load((QUrl("qrc:/main.qml")));

    auto dw1 = new KDDockWidgets::Views::DockWidget_qtquick("Dock #1");

    dw1->setWidget(QStringLiteral("qrc:/Guest1.qml"));
    dw1->resize(QSize(800, 800));
    dw1->show();

    auto dw2 = new KDDockWidgets::Views::DockWidget_qtquick("Dock #2");
    dw2->setWidget(QStringLiteral("qrc:/Guest2.qml"));
    dw2->resize(QSize(800, 800));
    dw2->show();

    auto dw3 = new KDDockWidgets::Views::DockWidget_qtquick("Dock #3");
    dw3->setWidget(QStringLiteral("qrc:/Guest3.qml"));

    dw1->dockWidget()->addDockWidgetToContainingWindow(dw3->dockWidget(), KDDockWidgets::Location_OnRight);

    auto mainWindow = KDDockWidgets::DockRegistry::self()->mainwindows().constFirst();
    mainWindow->addDockWidget(dw2->dockWidget(), KDDockWidgets::Location_OnTop);
    return app.exec();
}

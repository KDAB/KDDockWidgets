/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sergio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/


#include <kddockwidgets/Config.h>
#include <kddockwidgets/core/DockRegistry.h>
#include <kddockwidgets/qtquick/views/DockWidget.h>
#include <kddockwidgets/qtquick/Platform.h>
#include <kddockwidgets/qtquick/ViewFactory.h>
#include <kddockwidgets/core/MainWindow.h>
#include <kddockwidgets/core/views/MainWindowViewInterface.h>

#include <QQuickView>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

class CustomViewFactory : public KDDockWidgets::QtQuick::ViewFactory
{
public:
    ~CustomViewFactory() override;

    QUrl tabbarFilename() const override
    {
        return QUrl("qrc:/MyTabBar.qml");
    }
};

CustomViewFactory::~CustomViewFactory() = default;

int main(int argc, char *argv[])
{
#ifdef Q_OS_WIN
    QGuiApplication::setAttribute(Qt::AA_UseOpenGLES);
#endif
    QGuiApplication app(argc, argv);
    KDDockWidgets::initFrontend(KDDockWidgets::FrontendType::QtQuick);

    auto &config = KDDockWidgets::Config::self();
    auto flags = config.flags();

    config.setFlags(flags);
    config.setViewFactory(new CustomViewFactory());

    QQmlApplicationEngine appEngine;
    KDDockWidgets::QtQuick::Platform::instance()->setQmlEngine(&appEngine);
    appEngine.load((QUrl("qrc:/main.qml")));

    auto dw1 = new KDDockWidgets::QtQuick::DockWidget("Dock #1");

    dw1->setGuestItem(QStringLiteral("qrc:/Guest1.qml"));

    auto dw2 = new KDDockWidgets::QtQuick::DockWidget("Dock #2");
    dw2->setGuestItem(QStringLiteral("qrc:/Guest2.qml"));

    auto dw3 = new KDDockWidgets::QtQuick::DockWidget("Dock #3");
    dw3->setGuestItem(QStringLiteral("qrc:/Guest3.qml"));

    // Access the main area we created in QML with DockingArea {}
    auto mainArea = KDDockWidgets::DockRegistry::self()->mainDockingAreas().constFirst();
    mainArea->addDockWidget(dw1, KDDockWidgets::Location_OnTop);

    dw1->addDockWidgetAsTab(dw2);
    dw1->addDockWidgetAsTab(dw3);

    return app.exec();
}

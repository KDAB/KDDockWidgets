/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sergio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/


#include <kddockwidgets/Config.h>
#include <kddockwidgets/core/DockRegistry.h>
#include <kddockwidgets/core/MDILayout.h>
#include <kddockwidgets/qtquick/ViewFactory.h>
#include <kddockwidgets/qtquick/Platform.h>
#include <kddockwidgets/qtquick/views/DockWidget.h>
#include <kddockwidgets/qtquick/views/MainWindow.h>
#include <kddockwidgets/qtquick/views/MDILayout.h>

#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <QCommandLineParser>

int main(int argc, char *argv[])
{
#ifdef Q_OS_WIN
    QGuiApplication::setAttribute(Qt::AA_UseOpenGLES);
#endif
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif
    QGuiApplication app(argc, argv);

    KDDockWidgets::initFrontend(KDDockWidgets::FrontendType::QtQuick);

    // Create your engine which loads main.qml. A simple QQuickView would work too.
    QQmlApplicationEngine appEngine;
    KDDockWidgets::QtQuick::Platform::instance()->setQmlEngine(&appEngine);
    appEngine.load((QUrl("qrc:/main.qml")));

    // Below we illustrate usage of our C++ API. Alternatively you can use declarative API.
    // See main.qml for examples of dockwidgets created directly in QML

    auto dw1 = new KDDockWidgets::QtQuick::DockWidget("Dock #1");

    dw1->setGuestItem(QStringLiteral("qrc:/Guest1.qml"));
    dw1->resize(QSize(800, 800));
    dw1->open();

    auto dw3 = new KDDockWidgets::QtQuick::DockWidget("Dock #3");
    dw3->setGuestItem(QStringLiteral("qrc:/Guest3.qml"));

    dw1->addDockWidgetToContainingWindow(dw3, KDDockWidgets::Location_OnRight);

    // Access the main area we created in QML with DockingArea {}
    auto mainArea = KDDockWidgets::DockRegistry::self()->mainDockingAreas().constFirst();
    auto mdiLayout = new KDDockWidgets::Core::MDILayout();
    mainArea->setPersistentCentralView(mdiLayout->view()->asWrapper());

    auto dwInMDI1 = new KDDockWidgets::QtQuick::DockWidget("Dock #mdi1");
    dwInMDI1->setGuestItem(QStringLiteral("qrc:/Guest3.qml"));

    auto dwInMDI2 = new KDDockWidgets::QtQuick::DockWidget("Dock #mdi2");
    dwInMDI2->setGuestItem(QStringLiteral("qrc:/Guest3.qml"));

    mdiLayout->addDockWidget(dwInMDI1->dockWidget(), { 100, 100 });
    mdiLayout->addDockWidget(dwInMDI2->dockWidget(), { 140, 140 });

    return app.exec();
}

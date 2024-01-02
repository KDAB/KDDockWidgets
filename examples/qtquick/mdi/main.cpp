/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sergio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/


#include <kddockwidgets/Config.h>
#include <kddockwidgets/qtquick/views/DockWidget.h>
#include <kddockwidgets/qtquick/views/MainWindowMDI.h>
#include <kddockwidgets/qtquick/Platform.h>
#include <kddockwidgets/core/DockRegistry.h>
#include "kddockwidgets/core/MainWindow.h"

#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <QCommandLineParser>

int main(int argc, char *argv[])
{
#ifdef Q_OS_WIN
    QGuiApplication::setAttribute(Qt::AA_UseOpenGLES);
#endif
    QGuiApplication app(argc, argv);
    KDDockWidgets::initFrontend(KDDockWidgets::FrontendType::QtQuick);

    QCommandLineParser parser;
    parser.setApplicationDescription("KDDockWidgets example application");
    parser.addHelpOption();

    QQmlApplicationEngine appEngine;
    KDDockWidgets::QtQuick::Platform::instance()->setQmlEngine(&appEngine);
    appEngine.load((QUrl("qrc:/main.qml")));

    auto dw1 = new KDDockWidgets::QtQuick::DockWidget("Dock #1");
    dw1->setGuestItem(QStringLiteral("qrc:/Guest1.qml"));
    dw1->resize(QSize(400, 400));

    auto dw2 = new KDDockWidgets::QtQuick::DockWidget("Dock #2");
    dw2->setGuestItem(QStringLiteral("qrc:/Guest2.qml"));
    dw2->resize(QSize(400, 400));

    auto dw3 = new KDDockWidgets::QtQuick::DockWidget("Dock #3");
    dw3->setGuestItem(QStringLiteral("qrc:/Guest3.qml"));


    // See main.qml for how to add dock widgets from QML.
    // Here's a low level C++ example just for educational purposes:
    auto mainAreaView = KDDockWidgets::DockRegistry::self()->mainDockingAreas().constFirst();
    auto mainAreaMDI = static_cast<KDDockWidgets::QtQuick::MainWindowMDI *>(mainAreaView);

    mainAreaMDI->addDockWidget(dw1, QPoint(10, 10));
    mainAreaMDI->addDockWidget(dw2, QPoint(50, 50));
    mainAreaMDI->addDockWidget(dw3, QPoint(90, 90));

    return app.exec();
}

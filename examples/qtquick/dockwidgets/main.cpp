/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sergio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/


#include <kddockwidgets/Config.h>
#include <kddockwidgets/core/DockRegistry.h>
#include <kddockwidgets/qtquick/ViewFactory.h>
#include <kddockwidgets/qtquick/Platform.h>
#include <kddockwidgets/qtquick/views/DockWidget.h>
#include <kddockwidgets/qtquick/views/MainWindow.h>

#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <QCommandLineParser>
#include <QQmlContext>

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

    QCommandLineParser parser;
    parser.setApplicationDescription("KDDockWidgets example application");
    parser.addHelpOption();

    QCommandLineOption noTitleBars(
        "t", QCoreApplication::translate("main", "Hide titlebars when tabs are visible"));
    parser.addOption(noTitleBars);

    QCommandLineOption alwaysTabs(
        "z", QCoreApplication::translate("main", "Show tabs even if there's only one"));
    parser.addOption(alwaysTabs);

    QCommandLineOption maximizeButtonOption(
        "b",
        QCoreApplication::translate(
            "main",
            "Floating dockWidgets have maximize/restore buttons instead of float/dock button"));
    parser.addOption(maximizeButtonOption);

    QCommandLineOption minimizeButtonOption(
        "k",
        QCoreApplication::translate("main",
                                    "Floating dockWidgets have a minimize button. Implies not "
                                    "being an utility window (~Qt::Tool)"));
    parser.addOption(minimizeButtonOption);

#ifdef Q_OS_WIN
    QCommandLineOption nativeTitleBar(
        "native-title-bar",
        QCoreApplication::translate("main", "(internal) FloatingWindows a native title bar"));
    parser.addOption(nativeTitleBar);
#endif

#if defined(DOCKS_DEVELOPER_MODE)
    QCommandLineOption noQtTool(
        "no-qttool", QCoreApplication::translate("main", "(internal) Don't use Qt::Tool"));
    QCommandLineOption noParentForFloating(
        "no-parent-for-floating",
        QCoreApplication::translate("main", "(internal) FloatingWindows won't have a parent"));
    QCommandLineOption noDropIndicators(
        "no-drop-indicators",
        QCoreApplication::translate("main", "(internal) Don't use any drop indicators"));

    parser.addOption(noQtTool);
    parser.addOption(noParentForFloating);
    parser.addOption(noDropIndicators);

#if defined(Q_OS_WIN)
    QCommandLineOption noAeroSnap(
        "no-aero-snap", QCoreApplication::translate("main", "(internal) Disable AeroSnap"));
    parser.addOption(noAeroSnap);
#endif
#endif

    parser.process(app);
    auto flags = KDDockWidgets::Config::self().flags();

#if defined(DOCKS_DEVELOPER_MODE)
    auto internalFlags = KDDockWidgets::Config::self().internalFlags();

    if (parser.isSet(noQtTool))
        internalFlags |= KDDockWidgets::Config::InternalFlag_DontUseQtToolWindowsForFloatingWindows;

    if (parser.isSet(noParentForFloating))
        internalFlags |= KDDockWidgets::Config::InternalFlag_DontUseParentForFloatingWindows;

    if (parser.isSet(noDropIndicators))
        KDDockWidgets::Core::ViewFactory::s_dropIndicatorType = KDDockWidgets::DropIndicatorType::None;

#if defined(Q_OS_WIN)
    if (parser.isSet(noAeroSnap))
        internalFlags |= KDDockWidgets::Config::InternalFlag_NoAeroSnap;
#endif

    // These are debug-only/development flags, which you can ignore.
    KDDockWidgets::Config::self().setInternalFlags(internalFlags);
#endif

#if defined(Q_OS_WIN)
    // On Linux the title bar doesn't send us NonClient mouse events
    if (parser.isSet(nativeTitleBar))
        flags |= KDDockWidgets::Config::Flag_NativeTitleBar;
#endif

    if (parser.isSet(noTitleBars))
        flags |= KDDockWidgets::Config::Flag_HideTitleBarWhenTabsVisible;

    if (parser.isSet(alwaysTabs))
        flags |= KDDockWidgets::Config::Flag_AlwaysShowTabs;

    if (parser.isSet(maximizeButtonOption))
        flags |= KDDockWidgets::Config::Flag_TitleBarHasMaximizeButton;

    if (parser.isSet(minimizeButtonOption))
        flags |= KDDockWidgets::Config::Flag_TitleBarHasMinimizeButton;

    // Set any required flags. The defaults are usually fine.
    KDDockWidgets::Config::self().setFlags(flags);

    // Create your engine which loads main.qml. A simple QQuickView would work too.
    QQmlApplicationEngine appEngine;
    appEngine.rootContext()->setContextProperty("_exampleShowsMaximize", parser.isSet(maximizeButtonOption));

    KDDockWidgets::QtQuick::Platform::instance()->setQmlEngine(&appEngine);
    appEngine.load((QUrl("qrc:/main.qml")));

    // Below we illustrate usage of our C++ API. Alternative you can use declarative API.
    // See main.qml for examples of dockwidgets created directly in QML

    auto dw1 = new KDDockWidgets::QtQuick::DockWidget("Dock #1");

    dw1->setGuestItem(QStringLiteral("qrc:/Guest1.qml"));
    dw1->resize(QSize(800, 800));
    dw1->open();

    auto dw2 = new KDDockWidgets::QtQuick::DockWidget("Dock #2");
    dw2->setGuestItem(QStringLiteral("qrc:/Guest2.qml"));
    dw2->resize(QSize(800, 800));
    dw2->open();

    auto dw3 = new KDDockWidgets::QtQuick::DockWidget("Dock #3");
    dw3->setGuestItem(QStringLiteral("qrc:/Guest3.qml"));

    dw1->addDockWidgetToContainingWindow(dw3, KDDockWidgets::Location_OnRight);

    // Access the main area we created in QML with DockingArea {}
    auto mainArea = KDDockWidgets::DockRegistry::self()->mainDockingAreas().constFirst();
    mainArea->addDockWidget(dw2, KDDockWidgets::Location_OnTop);

    return app.exec();
}

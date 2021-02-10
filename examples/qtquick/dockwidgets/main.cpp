/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sergio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/


#include <kddockwidgets/Config.h>
#include <kddockwidgets/DockWidgetQuick.h>
#include <kddockwidgets/private/DockRegistry_p.h>
#include <kddockwidgets/FrameworkWidgetFactory.h>

#include <QQuickView>
#include <QGuiApplication>
#include <QCommandLineParser>

#if defined(DOCKS_DEVELOPER_MODE)
// Block just here for my own debugging
# include "../../src/private/MDILayoutWidget_p.h"
#endif

int main(int argc, char *argv[])
{
#ifdef Q_OS_WIN
    QGuiApplication::setAttribute(Qt::AA_UseOpenGLES);
#endif
    QGuiApplication app(argc, argv);
    QCommandLineParser parser;
    parser.setApplicationDescription("KDDockWidgets example application");
    parser.addHelpOption();


#if defined(DOCKS_DEVELOPER_MODE)
    QCommandLineOption noQtTool("no-qttool", QCoreApplication::translate("main", "(internal) Don't use Qt::Tool"));
    QCommandLineOption noParentForFloating("no-parent-for-floating", QCoreApplication::translate("main", "(internal) FloatingWindows won't have a parent"));
    QCommandLineOption nativeTitleBar("native-title-bar", QCoreApplication::translate("main", "(internal) FloatingWindows a native title bar"));
    QCommandLineOption noDropIndicators("no-drop-indicators", QCoreApplication::translate("main", "(internal) Don't use any drop indicators"));
    QCommandLineOption mdiLayout("mdi-layout", QCoreApplication::translate("main", "Main Window will use an MDI layout instead")); // TODO: Expose once stable

    parser.addOption(noQtTool);
    parser.addOption(noParentForFloating);
    parser.addOption(nativeTitleBar);
    parser.addOption(noDropIndicators);
    parser.addOption(mdiLayout);

# if defined(Q_OS_WIN)
    QCommandLineOption noAeroSnap("no-aero-snap", QCoreApplication::translate("main", "(internal) Disable AeroSnap"));
    parser.addOption(noAeroSnap);
# endif
#endif

    auto flags = KDDockWidgets::Config::self().flags();
    KDDockWidgets::MainWindowOptions mainWindowsOptions = {};

#if defined(DOCKS_DEVELOPER_MODE)
    auto internalFlags = KDDockWidgets::Config::self().internalFlags();
    parser.process(app);

    if (parser.isSet(noQtTool))
        internalFlags |= KDDockWidgets::Config::InternalFlag_DontUseQtToolWindowsForFloatingWindows;

    if (parser.isSet(noParentForFloating))
        internalFlags |= KDDockWidgets::Config::InternalFlag_DontUseParentForFloatingWindows;

    if (parser.isSet(nativeTitleBar))
        flags |= KDDockWidgets::Config::Flag_NativeTitleBar;
    else if (parser.isSet(noDropIndicators))
        KDDockWidgets::DefaultWidgetFactory::s_dropIndicatorType = KDDockWidgets::DropIndicatorType::None;

    if (parser.isSet(mdiLayout))
        mainWindowsOptions |= KDDockWidgets::MainWindowOption_MDI; // TODO: Move outside of developer mode once stable

# if defined(Q_OS_WIN)
    if (parser.isSet(noAeroSnap))
        internalFlags |= KDDockWidgets::Config::InternalFlag_NoAeroSnap;
# endif

    KDDockWidgets::Config::self().setInternalFlags(internalFlags);
#endif

    KDDockWidgets::Config::self().setFlags(flags);

    QQuickView view;
    view.setObjectName("MainWindow QQuickView");
    KDDockWidgets::Config::self().setQmlEngine(view.engine());
    view.resize(1000, 800);
    view.show();
    view.setResizeMode(QQuickView::SizeRootObjectToView);

    auto dw1 = new KDDockWidgets::DockWidgetQuick("Dock #1");
    view.setSource(QUrl("qrc:/main.qml"));

    dw1->setWidget(QStringLiteral("qrc:/Guest1.qml"));
    dw1->resize(QSize(800, 800));
    dw1->show();

    auto dw2 = new KDDockWidgets::DockWidgetQuick("Dock #2");
    dw2->setWidget(QStringLiteral("qrc:/Guest2.qml"));
    dw2->resize(QSize(800, 800));
    dw2->show();

    auto dw3 = new KDDockWidgets::DockWidgetQuick("Dock #3");
    dw3->setWidget(QStringLiteral("qrc:/Guest3.qml"));

    dw1->addDockWidgetToContainingWindow(dw3, KDDockWidgets::Location_OnRight);

    KDDockWidgets::MainWindowBase *mainWindow = KDDockWidgets::DockRegistry::self()->mainwindows().constFirst();
    mainWindow->addDockWidget(dw2, KDDockWidgets::Location_OnTop);

#if defined(DOCKS_DEVELOPER_MODE)
    // MDI just for my internal tests
    if (mainWindow->isMDI()) {
        auto layout = qobject_cast<KDDockWidgets::MDILayoutWidget*>(mainWindow->layoutWidget());
        layout->addDockWidget(dw1, QPoint(10, 10));
        layout->addDockWidget(dw2, QPoint(50, 50));
        layout->addDockWidget(dw3, QPoint(90, 90));
    }
#endif

    return app.exec();
}

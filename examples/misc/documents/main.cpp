/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "MyWidget.h"

#include <kddockwidgets/MainWindow.h>
#include <kddockwidgets/DockWidget.h>
#include <kddockwidgets/LayoutSaver.h>
#include <kddockwidgets/core/MainWindow.h>
#include <kddockwidgets/core/DockRegistry.h>

#include <QStyleFactory>
#include <QApplication>
#include <QMenuBar>

// clazy:excludeall=qstring-allocations

using namespace KDDockWidgets;

int main(int argc, char **argv)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName(QStringLiteral("KDAB"));
    QCoreApplication::setApplicationName(QStringLiteral("Documents Example"));

    KDDockWidgets::initFrontend(KDDockWidgets::FrontendType::QtWidgets);

    qApp->setStyle(QStyleFactory::create(QStringLiteral("Fusion")));

    // 1. Create a main window with a persistent central group
    KDDockWidgets::QtWidgets::MainWindow mainWindow(QStringLiteral("MyMainWindow"),
                                                    MainWindowOption_HasCentralGroup);
    mainWindow.setWindowTitle("Documents Example");
    mainWindow.resize(1200, 800);
    mainWindow.show();

    // 2. Set up affinities: the main window supports both scopes
    mainWindow.setAffinities({ "global", "projects" });
    mainWindow.mainWindow()->setDocumentAffinity("projects");

    // 3. Create project dock widgets (tabbed in the central group)
    auto projectDock1 = new KDDockWidgets::QtWidgets::DockWidget(QStringLiteral("project1"));
    projectDock1->setWidget(new MyWidget1());
    projectDock1->setAffinities({ "projects" });
    mainWindow.addDockWidgetAsTab(projectDock1);

    auto projectDock2 = new KDDockWidgets::QtWidgets::DockWidget(QStringLiteral("project2"));
    projectDock2->setWidget(new MyWidget2());
    projectDock2->setAffinities({ "projects" });
    mainWindow.addDockWidgetAsTab(projectDock2);

    // 4. Create global dock widgets (docked to the sides)
    auto dockedGlobal = new KDDockWidgets::QtWidgets::DockWidget(QStringLiteral("dockedGlobal"));
    dockedGlobal->setWidget(new MyWidget3());
    dockedGlobal->setAffinities({ "global" });
    mainWindow.mainWindow()->addDockWidgetToSide(dockedGlobal->asDockWidgetController(), KDDockWidgets::Location_OnLeft);

    auto dockedGlobal2 = new KDDockWidgets::QtWidgets::DockWidget(QStringLiteral("dockedGlobal2"));
    dockedGlobal2->setWidget(new MyWidget1());
    dockedGlobal2->setAffinities({ "global" });
    mainWindow.mainWindow()->addDockWidgetToSide(dockedGlobal2->asDockWidgetController(), KDDockWidgets::Location_OnRight);

    // 5. Create floating dock widgets
    auto floatingGlobal = new KDDockWidgets::QtWidgets::DockWidget(QStringLiteral("floatingGlobal"));
    floatingGlobal->setWidget(new MyWidget2());
    floatingGlobal->setAffinities({ "global" });
    floatingGlobal->open();

    auto floatingProjects = new KDDockWidgets::QtWidgets::DockWidget(QStringLiteral("floatingProjects"));
    floatingProjects->setWidget(new MyWidget3());
    floatingProjects->setAffinities({ "projects" });
    floatingProjects->open();

    // 6. Create menu bar with save/load actions for each affinity scope
    QMenuBar *menuBar = mainWindow.menuBar();
    QMenu *layoutMenu = menuBar->addMenu(QStringLiteral("Layout"));

    layoutMenu->addAction(QStringLiteral("Save Project"), [&] {
        KDDockWidgets::LayoutSaver saver;
        saver.setAffinityNames({ "projects" });
        saver.saveToFile(QStringLiteral("projects_layout.json"));
    });

    layoutMenu->addAction(QStringLiteral("Load Project"), [&] {
        KDDockWidgets::LayoutSaver saver;
        saver.setAffinityNames({ "projects" });
        saver.restoreFromFile(QStringLiteral("projects_layout.json"));
    });

    layoutMenu->addSeparator();

    layoutMenu->addAction(QStringLiteral("Save Global"), [&] {
        KDDockWidgets::LayoutSaver saver;
        saver.setAffinityNames({ "global" });
        saver.saveToFile(QStringLiteral("global_layout.json"));
    });

    layoutMenu->addAction(QStringLiteral("Load Global"), [&] {
        KDDockWidgets::LayoutSaver saver;
        saver.setAffinityNames({ "global" });
        saver.restoreFromFile(QStringLiteral("global_layout.json"));
    });

    layoutMenu->addSeparator();

    layoutMenu->addAction(QStringLiteral("Close all"), [&] {
        KDDockWidgets::DockRegistry::self()->clear();
    });

    return app.exec();
}

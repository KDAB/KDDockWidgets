/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/// Small test to show how to change tabbar close button via stylesheet

#include <kddockwidgets/MainWindow.h>
#include <kddockwidgets/DockWidget.h>
#include <kddockwidgets/Config.h>

#include <QStyleFactory>
#include <QApplication>
#include <QFile>

// clazy:excludeall=qstring-allocations

using namespace KDDockWidgets;

int main(int argc, char **argv)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif
    QApplication app(argc, argv);
    app.setOrganizationName(QStringLiteral("KDAB"));
    app.setApplicationName(QStringLiteral("Test app"));

    KDDockWidgets::initFrontend(KDDockWidgets::FrontendType::QtWidgets);
    KDDockWidgets::Config::self().setFlags(KDDockWidgets::Config::Flag_TabsHaveCloseButton | KDDockWidgets::Config::Flag_HideTitleBarWhenTabsVisible);

    qApp->setStyle(QStyleFactory::create(QStringLiteral("Fusion")));
    QFile qssFile(":/stylesheet.qss");
    qssFile.open(QFile::ReadOnly);
    qApp->setStyleSheet(qssFile.readAll());

    KDDockWidgets::QtWidgets::MainWindow mainWindow(QStringLiteral("MyMainWindow"));
    mainWindow.setWindowTitle("Main Window");
    mainWindow.resize(1200, 1200);
    mainWindow.show();

    auto dock1 = new KDDockWidgets::QtWidgets::DockWidget(QStringLiteral("MyDock1"));
    auto dock2 = new KDDockWidgets::QtWidgets::DockWidget(QStringLiteral("MyDock2"));
    auto dock3 = new KDDockWidgets::QtWidgets::DockWidget(QStringLiteral("MyDock3"));

    mainWindow.addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    mainWindow.addDockWidget(dock2, KDDockWidgets::Location_OnTop);
    dock1->addDockWidgetAsTab(dock3);

    return app.exec();
}

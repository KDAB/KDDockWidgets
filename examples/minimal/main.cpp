/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "MyWidget.h"

#include <kddockwidgets/DockWidget.h>
#include <kddockwidgets/MainWindow.h>

// clazy:excludeall=qstring-allocations

using namespace KDDockWidgets;

int main(int argc, char **argv)
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication app(argc, argv);

    app.setOrganizationName(QStringLiteral("KDAB"));
    app.setApplicationName(QStringLiteral("Test app"));

    // # 1. Create our main window

    KDDockWidgets::MainWindow mainWindow(QStringLiteral("MyMainWindow"));
    mainWindow.setWindowTitle("Main Window");
    mainWindow.resize(1200, 1200);
    mainWindow.show();

    // # 2. Create a dock widget, it needs a unique name
    auto dock1 = new KDDockWidgets::DockWidget(QStringLiteral("MyDock1"));
    auto widget1 = new MyWidget();
    dock1->setWidget(widget1);

    auto dock2 = new KDDockWidgets::DockWidget(QStringLiteral("MyDock2"));
    auto widget2 = new MyWidget(QStringLiteral(":/assets/base.png"),
                                QStringLiteral(":/assets/KDAB_bubble_fulcolor.png"));
    dock2->setWidget(widget2);

    auto dock3 = new KDDockWidgets::DockWidget(QStringLiteral("MyDock3"));
    auto widget3 = new MyWidget(QStringLiteral(":/assets/base.png"),
                                QStringLiteral(":/assets/KDAB_bubble_fulcolor.png"));
    dock3->setWidget(widget3);

    auto dock4 = new KDDockWidgets::DockWidget(QStringLiteral("MyDock4"));
    auto widget4 = new MyWidget(QStringLiteral(":/assets/base.png"),
                                QStringLiteral(":/assets/KDAB_bubble_fulcolor.png"));
    dock4->setWidget(widget4);


    // 3. Add them to the main window
    mainWindow.addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
    mainWindow.addDockWidget(dock2, KDDockWidgets::Location_OnTop);

    // 4. Add dock3 to the right of dock2
    mainWindow.addDockWidget(dock3, KDDockWidgets::Location_OnRight, dock2);

    // 5. dock4 will be its own top level (floating window)
    dock4->show();

    return app.exec();
}

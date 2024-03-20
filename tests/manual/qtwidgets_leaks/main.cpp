/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include <kddockwidgets/MainWindow.h>
#include <kddockwidgets/DockWidget.h>
#include <kddockwidgets/core/DockRegistry.h>
#include <kddockwidgets/core/DockWidget.h>

#include <QStyleFactory>
#include <QApplication>
#include <QPointer>
#include <QTimer>

// Simple app to test leaks under valgrind

using namespace KDDockWidgets;

int main(int argc, char **argv)
{
    int result = 0;
    QPointer<DockRegistry> dr;

    {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif
        QApplication app(argc, argv);
        app.setOrganizationName(QStringLiteral("KDAB"));
        app.setApplicationName(QStringLiteral("Test app"));
        qApp->setStyle(QStyleFactory::create(QStringLiteral("Fusion")));

        KDDockWidgets::initFrontend(KDDockWidgets::FrontendType::QtWidgets);

        // Create our main window. Dock 1 dock widget, let the other float and let a 3rd be hidden
        KDDockWidgets::QtWidgets::MainWindow mainWindow(QStringLiteral("MyMainWindow"));
        mainWindow.setWindowTitle("Main Window");
        mainWindow.resize(1200, 1200);
        mainWindow.show();

        auto dock1 = new KDDockWidgets::QtWidgets::DockWidget(QStringLiteral("MyDock1"));
        auto dock2 = new KDDockWidgets::QtWidgets::DockWidget(QStringLiteral("MyDock2"));
        auto dock3 = new KDDockWidgets::QtWidgets::DockWidget(QStringLiteral("MyDock3"));

        mainWindow.addDockWidget(dock1, KDDockWidgets::Location_OnLeft);
        dock2->open();
        dr = DockRegistry::self();

        QTimer::singleShot(2000, &app, &QApplication::quit);

        result = app.exec();
    }

    if (dr) {
        const auto docks = dr->dockwidgets();
        if (!docks.isEmpty()) {
            qDebug() << "Deleting unparented dock widgets docks:" << docks.size();
            for (auto dw : docks) {
                delete dw;
            }
        }

        if (dr) {
            qDebug() << "Dock registry not empty yet docks= " << dr->dockwidgets().size() << "; mainWindows=" << dr->mainwindows().size();
        } else {
            qDebug() << "Dock registry is empty.";
        }
    }

    qDebug() << "exiting main";
    return result;
}

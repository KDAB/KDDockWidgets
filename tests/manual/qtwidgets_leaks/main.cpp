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
// $ valgrind --leak-check=full --show-leak-kinds=all --suppressions=../valgrind.sup ./bin/qtwidgets_leak_test

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

        QTimer::singleShot(1000, &app, [&] {
            // On Windows this is not needed, since they are parented it seems
            delete dock1;
            delete dock2;
            delete dock3;
            QTimer::singleShot(0, &app, &QCoreApplication::quit);
        });

        result = app.exec();
    }

    if (dr) {
        qDebug() << "Dock registry not empty yet docks= " << dr->dockwidgets().size() << "; mainWindows=" << dr->mainwindows().size();
    } else {
        qDebug() << "Dock registry is empty.";
    }

    if (!QApplication::allWidgets().isEmpty() || !QApplication::allWindows().isEmpty()) {
        qDebug() << "There's still widgets/windows:" << QApplication::allWidgets() << QApplication::allWindows();
    }


    qDebug() << "exiting main";
    return result;
}

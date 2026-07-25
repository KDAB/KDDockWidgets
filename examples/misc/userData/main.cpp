/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "MyViewFactory.h"

#include <kddockwidgets/MainWindow.h>
#include <kddockwidgets/DockWidget.h>
#include <kddockwidgets/core/DockWidget.h>
#include <kddockwidgets/Config.h>

#include <QApplication>
#include <QLabel>
#include <QStyleFactory>

// clazy:excludeall=qstring-allocations

using namespace KDDockWidgets;

namespace {
QtWidgets::DockWidget *createDockWidget(const QString &uniqueName, const QString &text,
                                        UserType userType)
{
    auto dock = new QtWidgets::DockWidget(uniqueName);

    auto label = new QLabel(text);
    label->setAlignment(Qt::AlignCenter);
    label->setWordWrap(true);
    dock->setWidget(label);

    // This is the whole point of the example: tag the dock widget with a type, which
    // UserDataViewFactory::createTitleBar() will use to pick a matching TitleBar sub-class.
    dock->dockWidget()->setUserType(userType);

    return dock;
}
}

int main(int argc, char **argv)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName(QStringLiteral("KDAB"));
    QCoreApplication::setApplicationName(QStringLiteral("UserData Example"));

    KDDockWidgets::initFrontend(KDDockWidgets::FrontendType::QtWidgets);

    qApp->setStyle(QStyleFactory::create(QStringLiteral("Fusion")));

    // Install our custom factory, so createTitleBar() picks a different TitleBar sub-class
    // depending on each dock widget's userType()
    Config::self().setViewFactory(new UserDataViewFactory());

    QtWidgets::MainWindow mainWindow(QStringLiteral("MyMainWindow"));
    mainWindow.setWindowTitle(QStringLiteral("userType()-based TitleBar example"));
    mainWindow.resize(900, 600);

    auto noteDock = createDockWidget(
        QStringLiteral("note1"), QStringLiteral("This dock widget has UserType_Note."),
        UserType_Note);
    auto noteDock2 = createDockWidget(
        QStringLiteral("note2"), QStringLiteral("Another UserType_Note dock widget, tabbed with the first one."),
        UserType_Note);
    auto taskDock = createDockWidget(
        QStringLiteral("task1"), QStringLiteral("This dock widget has UserType_Task."),
        UserType_Task);
    auto alertDock = createDockWidget(
        QStringLiteral("alert1"), QStringLiteral("This dock widget has UserType_Alert."),
        UserType_Alert);

    // Dock them side by side (not tabbed), so each gets its own Group/TitleBar and all
    // 3 stylings are visible at once.
    mainWindow.addDockWidget(noteDock, Location_OnLeft);
    mainWindow.addDockWidget(taskDock, Location_OnRight, noteDock);
    mainWindow.addDockWidget(alertDock, Location_OnBottom);

    // Tab a 2nd note into the first one, so its (themed) TabBar becomes visible too. Tabs are
    // only shown once a group has more than 1 dock widget.
    noteDock->dockWidget()->addDockWidgetAsTab(noteDock2->dockWidget());

    mainWindow.show();

    return app.exec();
}

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "QmlTypes.h"
#include "DockWidgetInstantiator.h"
#include "MainWindowInstantiator.h"
#include "MainWindowMDIInstantiator.h"
#include "LayoutSaverInstantiator.h"

#include "views/Group.h"
#include "views/TitleBar.h"
#include "views/TabBar.h"
#include "views/DropArea.h"
#include "views/FloatingWindow.h"

#include <QQmlEngine>
#include <QDebug>

void KDDockWidgets::registerQmlTypes()
{
    qmlRegisterType<MainWindowInstantiator>("com.kdab.dockwidgets", 2, 0, "DockingArea");
    qmlRegisterType<MainWindowMDIInstantiator>("com.kdab.dockwidgets", 2, 0, "MDIDockingArea");
    qmlRegisterType<DockWidgetInstantiator>("com.kdab.dockwidgets", 2, 0, "DockWidget");
    qmlRegisterType<LayoutSaverInstantiator>("com.kdab.dockwidgets", 2, 0, "LayoutSaver");
    qmlRegisterUncreatableMetaObject(KDDockWidgets::staticMetaObject, "com.kdab.dockwidgets", 2, 0,
                                     "KDDockWidgets", QStringLiteral("Enum access only"));

    qmlRegisterUncreatableType<QtQuick::Group>("com.kdab.dockwidgets", 2, 0,
                                               "GroupView", QStringLiteral("Internal usage only"));

    qmlRegisterUncreatableType<QtQuick::TitleBar>("com.kdab.dockwidgets", 2, 0,
                                                  "TitleBarView", QStringLiteral("Internal usage only"));

    qmlRegisterUncreatableType<QtQuick::TabBar>("com.kdab.dockwidgets", 2, 0,
                                                "TabBarView", QStringLiteral("Internal usage only"));

    qmlRegisterUncreatableType<QtQuick::DropArea>("com.kdab.dockwidgets", 2, 0,
                                                  "DropAreaView", QStringLiteral("Internal usage only"));

    qmlRegisterUncreatableType<QtQuick::FloatingWindow>("com.kdab.dockwidgets", 2, 0,
                                                        "FloatingWindowView", QStringLiteral("Internal usage only"));

    qmlRegisterUncreatableType<QtQuick::DockWidgetModel>("com.kdab.dockwidgets", 2, 0,
                                                         "DockWidgetModel", QStringLiteral("Internal usage only"));
}

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// We don't care about performance related checks in the tests
// clazy:excludeall=ctor-missing-parent-argument,missing-qobject-macro,range-loop,missing-typeinfo,detaching-member,function-args-by-ref,non-pod-global-static,reserve-candidates,qstring-allocations

#pragma once

#include "utils.h"
#include "kddockwidgets/ViewFactory.h"
#include "kddockwidgets/core/MainWindow.h"
#include "kddockwidgets/core/Window.h"
#include "kddockwidgets/core/Platform.h"

#include <QDebug>
#include <QtTest/QTest>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

namespace KDDockWidgets::Tests {

inline int osWindowMinWidth()
{
#ifdef Q_OS_WIN
    return GetSystemMetrics(SM_CXMIN);
#else
    return 140; // Some random value for our windows. It's only important on Windows
#endif
}

/// Helper function so we don't write such a big line everywhere
inline Core::DockWidget *newDockWidget(const QString &uniqueName,
                                       DockWidgetOptions opts = {})
{
    return Config::self()
        .viewFactory()
        ->createDockWidget(uniqueName, opts)
        ->asDockWidgetController();
}

inline Core::DockWidget *createAndNestDockWidget(KDDockWidgets::Core::DropArea *dropArea,
                                                 Core::Group *relativeTo,
                                                 KDDockWidgets::Location location)
{
    static int count = 0;
    count++;
    const QString name = QString("dock%1").arg(count);
    auto dock = createDockWidget(name);
    dock->setObjectName(name);
    nestDockWidget(dock, dropArea, relativeTo, location);
    dropArea->checkSanity();
    return dock;
}

inline std::unique_ptr<KDDockWidgets::Core::MainWindow>
createSimpleNestedMainWindow(Core::DockWidget **centralDock,
                             Core::DockWidget **leftDock,
                             Core::DockWidget **rightDock)
{
    auto window = createMainWindow({ 900, 500 });
    *centralDock = createDockWidget("centralDock");
    window->addDockWidgetAsTab(*centralDock);
    auto dropArea = window->dropArea();

    *leftDock = createAndNestDockWidget(dropArea, nullptr, KDDockWidgets::Location_OnLeft);
    *rightDock = createAndNestDockWidget(dropArea, nullptr, KDDockWidgets::Location_OnRight);
    return window;
}

}

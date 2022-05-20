/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// We don't care about performance related checks in the tests
// clazy:excludeall=ctor-missing-parent-argument,missing-qobject-macro,range-loop,missing-typeinfo,detaching-member,function-args-by-ref,non-pod-global-static,reserve-candidates,qstring-allocations

#ifndef KDDOCKWIDGETS_TESTING_H
#define KDDOCKWIDGETS_TESTING_H

#include "KDDockWidgets.h"
#include "controllers/MainWindow.h"
#include "controllers/DockWidget.h"
#include "DockRegistry_p.h"
#include "Platform.h"

#include <QSize>
#include <QRect>
#include <QVector>
#include <QEvent>
#include <QVariant>

/**
 * @file
 * @brief Namespace for tests related enums and classes
 */

namespace KDDockWidgets {

namespace Testing {


struct AddDockWidgetParams
{
    QString mainWindowName;
    QString dockWidgetName;
    QString relativeToName;
    KDDockWidgets::Location location;
    KDDockWidgets::InitialVisibilityOption addingOption;

    bool isNull() const
    {
        return mainWindowName.isEmpty();
    }

    QVariantMap toVariantMap() const
    {
        QVariantMap map;

        map["mainWindowName"] = mainWindowName;
        map["dockWidgetName"] = dockWidgetName;
        if (!relativeToName.isEmpty())
            map["relativeToName"] = relativeToName;
        map["location"] = location;
        map["addingOption"] = QVariant::fromValue(addingOption);

        return map;
    }

    static AddDockWidgetParams fillFromVariantMap(const QVariantMap &map)
    {
        AddDockWidgetParams params;

        params.mainWindowName = map["mainWindowName"].toString();
        params.dockWidgetName = map["dockWidgetName"].toString();
        params.relativeToName = map["relativeToName"].toString();
        params.location = KDDockWidgets::Location(map["location"].toInt());
        params.addingOption = map["addingOption"].value<KDDockWidgets::InitialVisibilityOption>();

        return params;
    }

    KDDockWidgets::Controllers::MainWindow *mainWindow() const
    {
        return KDDockWidgets::DockRegistry::self()->mainWindowByName(mainWindowName);
    }

    Controllers::DockWidget *dockWidget() const
    {
        return KDDockWidgets::DockRegistry::self()->dockByName(dockWidgetName);
    }

    Controllers::DockWidget *relativeTo() const
    {
        return KDDockWidgets::DockRegistry::self()->dockByName(relativeToName);
    }
};

bool waitForDeleted(QObject *o, int timeout = 2000);

}

}

#endif

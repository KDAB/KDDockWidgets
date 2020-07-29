/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "QmlTypes.h"
#include "DropAreaWithCentralFrame_p.h"
#include "quick/MainWindowQuick_p.h"
#include "TitleBar_p.h"

#include <QQmlEngine>
#include <QDebug>

void KDDockWidgets::registerQmlTypes()
{
    qDebug() << "Registering types";
    qmlRegisterType<DropAreaWithCentralFrame>("com.kdab.dockwidgets", 1, 0, "DropAreaWithCentralFrame");
    qmlRegisterType<MainWindowQuick>("com.kdab.dockwidgets", 1, 0, "MainWindowQuick");

    qmlRegisterUncreatableType<TitleBar>("com.kdab.dockwidgets", 1, 0, "TitleBar", QStringLiteral("Enum access only"));
    qRegisterMetaType<DropArea*>();
}

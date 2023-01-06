/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "RubberBand_qtquick.h"
#include "Config.h"
#include "qtquick/Platform_qtquick.h"

#include <QQmlEngine>

using namespace KDDockWidgets;

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

RubberBand_qtquick::RubberBand_qtquick(QQuickItem *parent)
    : View_qtquick(nullptr, Type::RubberBand, parent)
{
    setVisible(false);
    setZ(1000);
    QQuickItem *visualItem = createItem(
        plat()->qmlEngine(), QStringLiteral("qrc:/kddockwidgets/qtquick/views/qml/RubberBand.qml"));
    visualItem->setParent(this);
    visualItem->setParentItem(this);
}

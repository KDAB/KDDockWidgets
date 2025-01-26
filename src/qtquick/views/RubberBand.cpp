/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "RubberBand.h"
#include "qtquick/Platform.h"

#include <QQmlEngine>

using namespace KDDockWidgets;

using namespace KDDockWidgets;
using namespace KDDockWidgets::QtQuick;

namespace {
QString rubberbandFile()
{
#ifdef KDDW_QML_MODULE
    return QStringLiteral("qrc:/qt/qml/com/kdab/dockwidgets/RubberBand.qml");
#else
    return QStringLiteral("qrc:/kddockwidgets/qtquick/views/qml/RubberBand.qml");
#endif
}
}

RubberBand::RubberBand(QQuickItem *parent)
    : View(nullptr, Core::ViewType::RubberBand, parent)
{
    setVisible(false);
    setZ(1000);
    QQuickItem *visualItem = createItem(
        plat()->qmlEngine(), rubberbandFile());
    visualItem->setParent(this);
    visualItem->setParentItem(this);
}

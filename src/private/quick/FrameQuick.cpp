/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * @file
 * @brief The GUI counterpart of Frame.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#include "FrameQuick_p.h"
#include "Config.h"

#include <QDebug>

using namespace KDDockWidgets;

FrameQuick::FrameQuick(QWidgetAdapter *parent, Options options)
    : Frame(parent, options)
{
    qDebug() << Q_FUNC_INFO << "Created frame";
    auto component = new QQmlComponent(Config::self().qmlEngine(),
                                       QUrl(QStringLiteral("qrc:/kddockwidgets/quick/qml/Frame.qml")));

    auto item = static_cast<QQuickItem*>(component->create());
    item->setProperty("frameCpp", QVariant::fromValue(this));
    item->setParentItem(this);
    item->setParent(this);
}

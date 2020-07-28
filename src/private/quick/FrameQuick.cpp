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

FrameQuick::FrameQuick(QWidgetAdapter *parent, FrameOptions options)
    : Frame(parent, options)
{
    qDebug() << Q_FUNC_INFO << "Created frame";
    auto component = new QQmlComponent(Config::self().qmlEngine(),
                                       QUrl(QStringLiteral("qrc:/kddockwidgets/private/quick/qml/Frame.qml")));

    auto item = static_cast<QQuickItem*>(component->create());

    if (!item) {
        qWarning() << Q_FUNC_INFO << "Failed to create item" << component->errorString();
        return;
    }

    item->setProperty("frameCpp", QVariant::fromValue(this));
    item->setParentItem(this);
    item->setParent(this);
}

void FrameQuick::removeWidget_impl(DockWidgetBase *)
{

}

void FrameQuick::detachTab_impl(DockWidgetBase *)
{

}

int FrameQuick::indexOfDockWidget_impl(DockWidgetBase *)
{
    return 0;
}

int FrameQuick::currentIndex_impl() const
{
    return 0;
}

void FrameQuick::setCurrentTabIndex_impl(int index)
{
    Q_UNUSED(index)
}

void FrameQuick::setCurrentDockWidget_impl(DockWidgetBase *)
{

}

void FrameQuick::insertDockWidget_impl(DockWidgetBase *, int index)
{
    Q_UNUSED(index)
}

DockWidgetBase *FrameQuick::dockWidgetAt_impl(int index) const
{
    Q_UNUSED(index)
    return nullptr;
}

DockWidgetBase *FrameQuick::currentDockWidget_impl() const
{
    return nullptr;
}

int FrameQuick::dockWidgetCount_impl() const
{
    return 0;
}

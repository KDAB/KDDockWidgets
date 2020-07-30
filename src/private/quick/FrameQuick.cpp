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

void FrameQuick::removeWidget_impl(DockWidgetBase *dw)
{
    m_dockWidgets.removeOne(dw);
    onDockWidgetCountChanged();
}

void FrameQuick::detachTab_impl(DockWidgetBase *)
{

}

int FrameQuick::indexOfDockWidget_impl(DockWidgetBase *dw)
{
    return m_dockWidgets.indexOf(dw);
}

int FrameQuick::currentIndex_impl() const
{
    if (!m_currentDockWidget)
        return -1;

    return m_dockWidgets.indexOf(m_currentDockWidget);
}

void FrameQuick::setCurrentTabIndex_impl(int index)
{
    m_currentDockWidget = dockWidgetAt(index);
}

void FrameQuick::setCurrentDockWidget_impl(DockWidgetBase *dw)
{
    if (dw && !m_dockWidgets.contains(dw)) {
        qWarning() << Q_FUNC_INFO << "Shouldn't happen";
        return;
    }

    m_currentDockWidget = dw;
}

void FrameQuick::insertDockWidget_impl(DockWidgetBase *dw, int index)
{
    if (m_dockWidgets.contains(dw)) {
        qWarning() << Q_FUNC_INFO << "Shouldn't happen";
        return;
    }

    m_dockWidgets.insert(index, dw);
    dw->setParent(this);

    if (!m_currentDockWidget)
        m_currentDockWidget = dw;

    onDockWidgetCountChanged();
}

DockWidgetBase *FrameQuick::dockWidgetAt_impl(int index) const
{
    if (index < 0 || index >= m_dockWidgets.size()) {
        qWarning() << Q_FUNC_INFO << "Shouldn't happen" << index << m_dockWidgets.size();
        return nullptr;
    }

    return m_dockWidgets[index];
}

DockWidgetBase *FrameQuick::currentDockWidget_impl() const
{
    return m_currentDockWidget;
}

int FrameQuick::dockWidgetCount_impl() const
{
    return m_dockWidgets.size();
}

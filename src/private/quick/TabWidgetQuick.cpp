/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "TabWidgetQuick_p.h"
#include "Frame_p.h"
#include "Config.h"
#include "FrameworkWidgetFactory.h"

#include <QDebug>

using namespace KDDockWidgets;

TabWidgetQuick::TabWidgetQuick(Frame *parent)
    : QWidgetAdapter(parent)
    , TabWidget(this, parent)
    , m_dockWidgetModel(new DockWidgetModel(this))
    , m_tabBar(Config::self().frameworkWidgetFactory()->createTabBar(this))
{
    connect(m_dockWidgetModel, &DockWidgetModel::countChanged,
            this, &TabWidgetQuick::countChanged);
}

TabBar *TabWidgetQuick::tabBar() const
{
    return m_tabBar;
}

int TabWidgetQuick::numDockWidgets() const
{
    return m_dockWidgetModel->count();
}

void TabWidgetQuick::removeDockWidget(DockWidgetBase *dw)
{
    m_dockWidgetModel->remove(dw);
}

int TabWidgetQuick::indexOfDockWidget(DockWidgetBase *dw) const
{
    return m_dockWidgetModel->indexOf(dw);
}

bool TabWidgetQuick::isPositionDraggable(QPoint p) const
{
    Q_UNUSED(p);
    return true;
}

void TabWidgetQuick::setCurrentDockWidget(int index)
{
    setCurrentDockWidget(dockwidgetAt(index));
}

void TabWidgetQuick::setCurrentDockWidget(DockWidgetBase *dw)
{
    if (dw && !containsDockWidget(dw)) {
        qWarning() << Q_FUNC_INFO << "Shouldn't happen";
        return;
    }

    if (m_currentDockWidget != dw) {
        m_currentDockWidget = dw;
        Q_EMIT currentDockWidgetChanged(dw);
    }
}

bool TabWidgetQuick::containsDockWidget(DockWidgetBase *dw) const
{
    return m_dockWidgetModel->contains(dw);
}

DockWidgetBase *TabWidgetQuick::currentDockWidget() const
{
    return m_currentDockWidget;
}

bool TabWidgetQuick::insertDockWidget(int index, DockWidgetBase *dw, const QIcon &, const QString &title)
{
    Q_UNUSED(title); // todo
    return m_dockWidgetModel->insert(dw, index);
}

void TabWidgetQuick::setTabBarAutoHide(bool)
{
    qWarning() << Q_FUNC_INFO << "Not implemented";
}

void TabWidgetQuick::renameTab(int index, const QString &)
{
    Q_UNUSED(index);
    qWarning() << Q_FUNC_INFO << "Not implemented";
}

DockWidgetBase *TabWidgetQuick::dockwidgetAt(int index) const
{
    return m_dockWidgetModel->dockWidgetAt(index);
}

int TabWidgetQuick::currentIndex() const
{
    if (!m_currentDockWidget)
        return -1;

    return indexOfDockWidget(m_currentDockWidget);
}

DockWidgetModel *TabWidgetQuick::dockWidgetModel() const
{
    return m_dockWidgetModel;
}

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "TabWidgetQuick_p.h"
#include "Frame_p.h"

using namespace KDDockWidgets;

TabWidgetQuick::TabWidgetQuick(Frame *parent)
    : QWidgetAdapter(parent)
    , TabWidget(this, parent)
    , m_tabBar(nullptr)
{
}

TabBar *TabWidgetQuick::tabBar() const
{
    return m_tabBar;
}

int TabWidgetQuick::numDockWidgets() const
{
    return 0;
}

void TabWidgetQuick::removeDockWidget(DockWidgetBase *)
{

}

int TabWidgetQuick::indexOfDockWidget(DockWidgetBase *) const
{
    return -1;
}

bool TabWidgetQuick::isPositionDraggable(QPoint p) const
{
    Q_UNUSED(p);
    return true;
}

void TabWidgetQuick::setCurrentDockWidget(int index)
{
    Q_UNUSED(index);
}

void TabWidgetQuick::insertDockWidget(int index, DockWidgetBase *, const QIcon &, const QString &title)
{
    Q_UNUSED(index);
    Q_UNUSED(title);
}

void TabWidgetQuick::setTabBarAutoHide(bool)
{

}

void TabWidgetQuick::renameTab(int index, const QString &)
{
    Q_UNUSED(index);
}

DockWidgetBase *TabWidgetQuick::dockwidgetAt(int index) const
{
    Q_UNUSED(index);
    return nullptr;
}

int TabWidgetQuick::currentIndex() const
{
    return 1;
}

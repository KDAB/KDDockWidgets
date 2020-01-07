/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file
 * @brief The QWidget counter part of TabWidget. Handles GUI while TabWidget handles state.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#include "TabWidgetQuick_p.h"
#include "Frame_p.h"
#include "Config.h"
#include "FrameworkWidgetFactory.h"

using namespace KDDockWidgets;

TabWidgetQuick::TabWidgetQuick(Frame *parent)
    : TabWidget(this, parent)
    , m_tabBar(Config::self().frameworkWidgetFactory()->createTabBar(this))
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
    return 0;
}

bool TabWidgetQuick::isPositionDraggable(QPoint) const
{
   /* if (tabPosition() != QTabWidget::North) {
        qWarning() << Q_FUNC_INFO << "Not implemented yet. Only North is supported";
        return false;
    }*/

    return -1;
}

void TabWidgetQuick::setCurrentDockWidget(int)
{

}

void TabWidgetQuick::insertDockWidget(int , DockWidgetBase *,
                                      const QIcon &, const QString &)
{

}

void TabWidgetQuick::setTabBarAutoHide(bool)
{
}

void TabWidgetQuick::detachTab(DockWidgetBase *dockWidget)
{
    tabBar()->detachTab(dockWidget);
}

DockWidgetBase *TabWidgetQuick::dockwidgetAt(int) const
{
    return 0;
}

int TabWidgetQuick::currentIndex() const
{
    return -1;
}

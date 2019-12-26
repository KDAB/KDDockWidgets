/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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
 * @brief Implements a QTabWidget derived class with support for docking and undocking
 * KDockWidget::DockWidget as tabs .
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#include "TabBarWidget_p.h"
#include "Config.h"

#include <QMouseEvent>
#include <QApplication>

using namespace KDDockWidgets;

TabBarWidget::TabBarWidget(TabWidget *parent)
    : QTabBar(parent->asWidget())
    , TabBar(this, parent)
{
    setMovable(Config::self().flags() & Config::Flag_AllowReorderTabs);
}

int TabBarWidget::numDockWidgets() const
{
    return count();
}

int TabBarWidget::tabAt(QPoint localPos) const
{
    return QTabBar::tabAt(localPos);
}

void TabBarWidget::mousePressEvent(QMouseEvent *e)
{
    onMousePress(e->pos());
    QTabBar::mousePressEvent(e);
}

bool TabBarWidget::dragCanStart(QPoint pressPos, QPoint pos) const
{
    // Here we allow the user to re-order tabs instead of dragging them off.
    // To do that we just return false here, and QTabBar will handle the mouse event, assuming QTabBar::isMovable.

    const bool defaultResult = Draggable::dragCanStart(pressPos, pos);

    if (!defaultResult || !isMovable()) {
        // Nothing more to do. If the drag wouldn't start anyway, return false.
        // And if the tabs aren't movable, just return the default result, which just considers
        // QApplication::startDragDistances
        return defaultResult;
    }

    const int index = tabAt(mapFromGlobal(pos));
    if (index == -1)
        return defaultResult;

    const int deltaX = qAbs(pos.x() - pressPos.x());
    const int deltaY = qAbs(pos.y() - pressPos.y());

    if (deltaY > 5 * QApplication::startDragDistance()) {
        // Moving up or down too much results in a detach. No tab re-ordering allowed.
        return true;
    } else if (deltaY > QApplication::startDragDistance() && deltaX < QApplication::startDragDistance()) {
        // Moved a bit up or down, but not left/right, then detach too.
        // Only if it's going considerably left/right we allow to re-order tabs.
        return true;
    }

    return false;
}

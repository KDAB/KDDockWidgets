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

#include "TabWidget_p.h"
#include "Logging_p.h"
#include "DragController_p.h"
#include "FloatingWindow_p.h"
#include "Frame_p.h"
#include "WindowBeingDragged_p.h"

#include <QMouseEvent>

#include <memory>

using namespace KDDockWidgets;

TabBar::TabBar(TabWidget *parent)
    : QTabBar(parent)
    , Draggable(this)
    , m_tabWidget(parent)
{
    setMinimumWidth(30);
}

DockWidget *TabBar::dockWidgetAt(int index) const
{
    if (index < 0 || index >= count())
        return nullptr;

    return qobject_cast<DockWidget *>(m_tabWidget->widget(index));
}

DockWidget *TabBar::dockWidgetAt(QPoint localPos) const
{
    return dockWidgetAt(tabAt(localPos));
}

void TabBar::mousePressEvent(QMouseEvent *e)
{
    m_lastPressedDockWidget = dockWidgetAt(e->pos());
    QTabBar::mousePressEvent(e);
}

std::unique_ptr<WindowBeingDragged> TabBar::makeWindow()
{
    auto dock = m_lastPressedDockWidget;
    m_lastPressedDockWidget = nullptr; // TODO check if we still have this dock, it might have been deleted
    if (!dock) {
        qWarning() << "TabBar::makeWindow() Couldn't find dock widget at position" << QCursor::pos();
        return {};
    }

    FloatingWindow *floatingWindow = detachTab(dock);

    return std::unique_ptr<WindowBeingDragged>(new WindowBeingDragged(floatingWindow));
}

FloatingWindow * TabBar::detachTab(DockWidget *dockWidget)
{
    QRect r = dockWidget->geometry();
    m_tabWidget->removeDockWidget(dockWidget);

    auto newFrame = new Frame();
    newFrame->addWidget(dockWidget);

    auto floatingWindow = new FloatingWindow(newFrame);
    r.moveTopLeft(mapToGlobal(QPoint(0, 0)));
    floatingWindow->setGeometry(r);
    floatingWindow->show();

    return floatingWindow;
}

TabWidget::TabWidget(QWidget *parent)
    : QTabWidget(parent)
    , m_tabBar(new TabBar(this))
{
    setTabBarAutoHide(true);
    setTabBar(m_tabBar);
}

void TabWidget::addDockWidget(DockWidget *dock)
{
    Q_ASSERT(dock);
    addTab(dock, dock->name());
    setCurrentIndex(count() - 1);
}

void TabWidget::insertDockWidget(DockWidget *dock, int index)
{
    if (index < 0)
        index = 0;
    if (index > count())
        index = count();

    Q_ASSERT(dock);
    insertTab(index, dock, dock->name());
    setCurrentIndex(index);
}

void TabWidget::removeDockWidget(DockWidget *w)
{
    removeTab(indexOf(w));
}

void TabWidget::detachTab(DockWidget *dockWidget)
{
    m_tabBar->detachTab(dockWidget);
}

void TabWidget::tabInserted(int)
{
   Q_EMIT dockWidgetCountChanged();
}

void TabWidget::tabRemoved(int)
{
    Q_EMIT dockWidgetCountChanged();
}

void TabWidget::paintEvent(QPaintEvent *p)
{
    // When count is 1 we want to use the same background as a regular QWidget
    // Otherwise it looks weird because the colors change when transforming a QDockWidget into FloatingWindow
    if (count() > 1)
        QTabWidget::paintEvent(p);
}

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
 * @brief The QWidget counter part of TabWidgetWidget. Handles GUI while TabWidget handles state.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#include "TabWidgetWidget_p.h"
#include "Frame_p.h"
#include "Config.h"
#include "FrameworkWidgetFactory.h"

using namespace KDDockWidgets;

TabWidgetWidget::TabWidgetWidget(Frame *parent)
    : QTabWidget(parent)
    , TabWidget(this, parent)
    , m_tabBar(Config::self().frameworkWidgetFactory()->createTabBar(this))
{
    setTabBar(static_cast<QTabBar*>(m_tabBar->asWidget()));
    setTabsClosable(Config::self().flags() & Config::Flag_TabsHaveCloseButton);

    // In case tabs closable is set by the factory, a tabClosedRequested() is emitted when the user presses [x]
    connect(this, &QTabWidget::tabCloseRequested, this, [this] (int index) {
        if (DockWidgetBase *dw = dockwidgetAt(index)) {
            if (dw->options() & DockWidgetBase::Option_NotClosable) {
                qWarning() << "QTabWidget::tabCloseRequested: Refusing to close dock widget with Option_NotClosable option. name=" << dw->uniqueName();
            } else {
                dw->close();
            }
        } else {
            qWarning() << "QTabWidget::tabCloseRequested Couldn't find dock widget for index" << index << "; count=" << count();
        }
    });

}

TabBar *TabWidgetWidget::tabBar() const
{
    return m_tabBar;
}

int TabWidgetWidget::numDockWidgets() const
{
    return count();
}

void TabWidgetWidget::removeDockWidget(DockWidgetBase *dw)
{
    removeTab(indexOf(dw));
}

int TabWidgetWidget::indexOfDockWidget(DockWidgetBase *dw) const
{
    return indexOf(dw);
}

void TabWidgetWidget::paintEvent(QPaintEvent *p)
{
    // When count is 1 we want to use the same background as a regular QWidget
    // Otherwise it looks weird because the colors change when transforming a QDockWidget into FloatingWindow
    if (count() > 1)
        QTabWidget::paintEvent(p);
}

void TabWidgetWidget::tabInserted(int)
{
    onTabInserted();
}

void TabWidgetWidget::tabRemoved(int)
{
    onTabRemoved();
}

bool TabWidgetWidget::isPositionDraggable(QPoint p) const
{
    if (tabPosition() != QTabWidget::North) {
        qWarning() << Q_FUNC_INFO << "Not implemented yet. Only North is supported";
        return false;
    }

    return p.y() >= 0 && p.y() <= QTabWidget::tabBar()->height();
}

void TabWidgetWidget::setCurrentDockWidget(int index)
{
    setCurrentIndex(index);
}

void TabWidgetWidget::insertDockWidget(int index, DockWidgetBase *dw,
                                       const QIcon &icon, const QString &title)
{
    insertTab(index, dw, icon, title);
}

void TabWidgetWidget::setTabBarAutoHide(bool b)
{
    QTabWidget::setTabBarAutoHide(b);
}

void TabWidgetWidget::detachTab(DockWidgetBase *dockWidget)
{
    tabBar()->detachTab(dockWidget);
}

DockWidgetBase *TabWidgetWidget::dockwidgetAt(int index) const
{
    return qobject_cast<DockWidgetBase *>(widget(index));
}

int TabWidgetWidget::currentIndex() const
{
    return QTabWidget::currentIndex();
}

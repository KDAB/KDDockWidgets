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

#ifndef KD_TAB_WIDGET_P_H
#define KD_TAB_WIDGET_P_H

#include "docks_export.h"
#include "Draggable_p.h"
#include "Frame_p.h"

#include <QTabWidget>
#include <QTabBar>
#include <QVector>

#include <memory>

namespace KDDockWidgets {

class DockWidget;
class TabWidget;

class DOCKS_EXPORT_FOR_UNIT_TESTS TabBar : public QTabBar
    , public Draggable
{
    Q_OBJECT
public:
    typedef QVector<TabBar *> List;
    explicit TabBar(TabWidget *parent = nullptr);

    DockWidget *dockWidgetAt(int index) const;
    DockWidget *dockWidgetAt(QPoint localPos) const;

    // Draggable
    std::unique_ptr<WindowBeingDragged> makeWindow() override;

    /**
     * @brief detaches a dock widget and shows it as a floating dock widget
     * The dock widget is morphed into a FloatingWindow for convenience.
     * @param dockWidget the dock widget to detach
     * @returns the created FloatingWindow
     */
    FloatingWindow *detachTab(DockWidget *dockWidget);

protected:
    void mousePressEvent(QMouseEvent *) override;

private:
    TabWidget *const m_tabWidget;
    QPointer<DockWidget> m_lastPressedDockWidget = nullptr;
};

class DOCKS_EXPORT_FOR_UNIT_TESTS TabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit TabWidget(QWidget *parent);
    void addDockWidget(DockWidget *);

    /**
     * @brief inserts @p dockwidget into the TabWidget, at @p index
     * @param dockwidget the dockwidget to insert
     * @param index The index to where to put it
     */
    void insertDockWidget(DockWidget *dockwidget, int index);

    void removeDockWidget(DockWidget *);

    /**
     * @brief detaches a dock widget and shows it as a floating dock widget
     * @param dockWidget the dock widget to detach
     */
    void detachTab(DockWidget *dockWidget);

Q_SIGNALS:
    void dockWidgetCountChanged();
protected:
    void tabInserted(int index) override;
    void tabRemoved(int index) override;
    void paintEvent(QPaintEvent *) override;
private:
    TabBar *const m_tabBar;
    Q_DISABLE_COPY(TabWidget)
};
}

#endif

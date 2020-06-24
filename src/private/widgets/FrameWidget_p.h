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


#ifndef KD_FRAME_WIDGET_P_H
#define KD_FRAME_WIDGET_P_H

#include "../Frame_p.h"

QT_BEGIN_NAMESPACE
class QTabBar;
QT_END_NAMESPACE

namespace KDDockWidgets {

class TestDocks;
class TabWidget;

/**
 * @brief The GUI counterpart of Frame. Inherits Frame and implements paintEvent().
 */
class DOCKS_EXPORT FrameWidget : public Frame
{
    Q_OBJECT
public:
    explicit FrameWidget(QWidget *parent = nullptr, FrameOptions = FrameOption_None);
    ~FrameWidget();
    QTabBar *tabBar() const;
    TabWidget *tabWidget() const;

protected:
    void paintEvent(QPaintEvent *) override;
    QSize maxSizeHint() const override;
    void detachTab_impl(DockWidgetBase *) override;
    int indexOfDockWidget_impl(DockWidgetBase *) override;
    void setCurrentDockWidget_impl(DockWidgetBase *) override;
    int currentIndex_impl() const override;
    void insertDockWidget_impl(DockWidgetBase *, int index) override;
    void removeWidget_impl(DockWidgetBase *) override;
    void setCurrentTabIndex_impl(int) override;
    DockWidgetBase *currentDockWidget_impl() const override;
    DockWidgetBase *dockWidgetAt_impl(int index) const override;
    int dockWidgetCount_impl() const override;
    QRect dragRect() const override;
private:
    friend class TestDocks;
    TabWidget *const m_tabWidget;
};


}

#endif

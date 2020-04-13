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

#pragma once

#include <kddockwidgets/DockWidget.h>
#include <kddockwidgets/MainWindow.h>

class MyMainWindow : public KDDockWidgets::MainWindow
{
    Q_OBJECT
public:
    explicit MyMainWindow(const QString &uniqueName, KDDockWidgets::MainWindowOptions options,
                          bool dockWidget0IsNonClosable, bool nonDockableDockWidget9, bool restoreIsRelative,
                          const QString &affinityName = {}, // Usually not needed. Just here to show the feature.
                          QWidget *parent = nullptr);

private:
    void createDockWidgets();
    KDDockWidgets::DockWidgetBase* newDockWidget();
    QMenu *m_toggleMenu = nullptr;
    const bool m_dockWidget0IsNonClosable;
    const bool m_dockWidget9IsNonDockable;
    const bool m_restoreIsRelative;
    KDDockWidgets::DockWidget::List m_dockwidgets;
};

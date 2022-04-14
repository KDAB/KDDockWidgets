/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

class QPoint;
class QIcon;
class QString;

namespace KDDockWidgets {

namespace Controllers {
class DockWidget;
}

namespace Views {


/// @brief The interface that Stack views should implement
class Stack
{
public:
    virtual bool isPositionDraggable(QPoint p) const = 0;
    virtual void setTabBarAutoHide(bool is) = 0;
    virtual void renameTab(int index, const QString &) = 0;
    virtual int currentIndex() const = 0;
    virtual int numDockWidgets() const = 0;
    virtual void changeTabIcon(int index, const QIcon &icon) = 0;
    virtual Controllers::DockWidget *dockwidgetAt(int index) const = 0;
    virtual int indexOfDockWidget(const Controllers::DockWidget *dw) const = 0;
    virtual void removeDockWidget(Controllers::DockWidget *dw) = 0;
    virtual bool insertDockWidget(int index, Controllers::DockWidget *dw,
                                  const QIcon &icon, const QString &title) = 0;
    virtual void setCurrentDockWidget(int index) = 0;
    virtual void setDocumentMode(bool) = 0;
};

}

}

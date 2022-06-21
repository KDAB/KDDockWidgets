/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/docks_export.h"

class QString;
class QIcon;
class QRect;

namespace KDDockWidgets {

namespace Controllers {
class DockWidget;
class Group;
}

namespace Views {

/// @brief The interface that Frame views should implement
class DOCKS_EXPORT GroupViewInterface
{
public:
    explicit GroupViewInterface(Controllers::Group *);
    virtual ~GroupViewInterface();
    virtual void renameTab(int index, const QString &) = 0;
    virtual void changeTabIcon(int index, const QIcon &) = 0;
    virtual void removeWidget_impl(Controllers::DockWidget *) = 0;
    virtual int indexOfDockWidget_impl(const Controllers::DockWidget *) = 0;
    virtual int currentIndex_impl() const = 0;
    virtual void setCurrentTabIndex_impl(int index) = 0;
    virtual void setCurrentDockWidget_impl(Controllers::DockWidget *) = 0;
    virtual void insertDockWidget_impl(Controllers::DockWidget *, int index) = 0;
    virtual Controllers::DockWidget *dockWidgetAt_impl(int index) const = 0;
    virtual Controllers::DockWidget *currentDockWidget_impl() const = 0;
    virtual int nonContentsHeight() const = 0;
    virtual QRect dragRect() const = 0;

    bool isMDI() const;
    Controllers::Group *group() const;

protected:
    Controllers::Group *const m_group;
};

}

}

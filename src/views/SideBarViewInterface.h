/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/docks_export.h"

namespace KDDockWidgets {

namespace Controllers {
class DockWidget;
}

namespace Views {

/// @brief The interface that SideBar views should implement
class DOCKS_EXPORT SideBarViewInterface
{
public:
    virtual ~SideBarViewInterface();
    virtual void addDockWidget_Impl(Controllers::DockWidget *dock) = 0;
    virtual void removeDockWidget_Impl(Controllers::DockWidget *dock) = 0;
};

}

}

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/docks_export.h"

namespace KDDockWidgets {

namespace Core {
class DockWidget;
class SideBar;
}

namespace Views {

/// @brief The interface that SideBar views should implement
class DOCKS_EXPORT SideBarViewInterface
{
public:
    explicit SideBarViewInterface(Core::SideBar *);
    virtual ~SideBarViewInterface();
    virtual void addDockWidget_Impl(Core::DockWidget *dock) = 0;
    virtual void removeDockWidget_Impl(Core::DockWidget *dock) = 0;

    Core::SideBar *sideBar() const;

protected:
    Core::SideBar *const m_sideBar;
};

}

}

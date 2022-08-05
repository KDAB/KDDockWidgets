/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "SideBarViewInterface.h"
#include "kddockwidgets/controllers/SideBar.h"


namespace KDDockWidgets::Views {

SideBarViewInterface::SideBarViewInterface(Controllers::SideBar *controller)
    : m_sideBar(controller)
{
}

SideBarViewInterface::~SideBarViewInterface() = default;

Controllers::SideBar *SideBarViewInterface::sideBar() const
{
    return m_sideBar;
}

} // namespace

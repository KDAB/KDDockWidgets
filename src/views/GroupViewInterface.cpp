/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "GroupViewInterface.h"
#include "controllers/Group.h"
#include "controllers/TabBar.h"
#include "controllers/Stack.h"

namespace KDDockWidgets {

namespace Views {
GroupViewInterface::GroupViewInterface(Controllers::Group *controller)
    : m_group(controller)
{
}

GroupViewInterface::~GroupViewInterface() = default;

bool GroupViewInterface::isMDI() const
{
    return m_group->isMDI();
}

Controllers::Group *GroupViewInterface::group() const
{
    return m_group;
}

QRect GroupViewInterface::dragRect() const
{
    return {};
}

void GroupViewInterface::removeDockWidget(Controllers::DockWidget *dw)
{
    m_group->tabBar()->removeDockWidget(dw);
}

void GroupViewInterface::insertDockWidget(Controllers::DockWidget *dw, int index)
{
    m_group->stack()->insertDockWidget(dw, index);
}

} // namespace
} // namespace

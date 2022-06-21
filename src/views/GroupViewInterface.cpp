/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "GroupViewInterface.h"
#include "controllers/Group.h"

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

} // namespace
} // namespace

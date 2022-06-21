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
GroupViewInterface::GroupViewInterface(Controllers::Frame *controller)
    : m_frame(controller)
{
}

GroupViewInterface::~GroupViewInterface() = default;

bool GroupViewInterface::isMDI() const
{
    return m_frame->isMDI();
}

Controllers::Frame *GroupViewInterface::frame() const
{
    return m_frame;
}

} // namespace
} // namespace

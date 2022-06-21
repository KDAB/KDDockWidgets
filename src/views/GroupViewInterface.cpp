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
FrameViewInterface::FrameViewInterface(Controllers::Frame *controller)
    : m_frame(controller)
{
}

FrameViewInterface::~FrameViewInterface() = default;

bool FrameViewInterface::isMDI() const
{
    return m_frame->isMDI();
}

Controllers::Frame *FrameViewInterface::frame() const
{
    return m_frame;
}

} // namespace
} // namespace

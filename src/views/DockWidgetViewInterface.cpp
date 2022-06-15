/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "DockWidgetViewInterface.h"
#include "kddockwidgets/controllers/DockWidget.h"
#include "kddockwidgets/controllers/DockWidget_p.h"

namespace KDDockWidgets::Views {

DockWidgetViewInterface::DockWidgetViewInterface(Controllers::DockWidget *controller)
    : m_dockWidget(controller)
{
}

Controllers::Frame *DockWidgetViewInterface::frame() const
{
    return m_dockWidget->dptr()->frame();
}

Controllers::DockWidget *DockWidgetViewInterface::dockWidget() const
{
    return m_dockWidget;
}

Controllers::TitleBar *DockWidgetViewInterface::actualTitleBar() const
{
    if (Controllers::Frame *frame = this->frame())
        return frame->actualTitleBar();
    return nullptr;
}

DockWidgetViewInterface::~DockWidgetViewInterface() = default;

} // namespace

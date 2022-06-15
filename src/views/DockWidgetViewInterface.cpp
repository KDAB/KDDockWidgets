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

bool DockWidgetViewInterface::isFocused() const
{
    return m_dockWidget->isFocused();
}

bool DockWidgetViewInterface::isFloating() const
{
    return m_dockWidget->isFloating();
}

QString DockWidgetViewInterface::uniqueName() const
{
    return m_dockWidget->uniqueName();
}

QString DockWidgetViewInterface::title() const
{
    return m_dockWidget->title();
}

void DockWidgetViewInterface::setTitle(const QString &title)
{
    m_dockWidget->setTitle(title);
}

void DockWidgetViewInterface::setFloating(bool is)
{
    m_dockWidget->setFloating(is);
}

} // namespace

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "MainWindowMDIViewInterface.h"
#include "DockWidgetViewInterface.h"
#include "controllers/MDILayout.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;
using namespace KDDockWidgets::Controllers;

MainWindowMDIViewInterface::MainWindowMDIViewInterface(Controllers::MDILayout *layout)
    : m_mdiLayout(layout)
{
}

void MainWindowMDIViewInterface::addDockWidget(DockWidgetViewInterface *dockWidget, QPoint localPos,
                                               InitialOption addingOption)
{
    Controllers::DockWidget *dw = dockWidget ? dockWidget->dockWidget() : nullptr;
    m_mdiLayout->addDockWidget(dw, localPos, addingOption);
}

void MainWindowMDIViewInterface::addDockWidget(DockWidgetViewInterface *dockWidget,
                                               QPointF localPos, InitialOption addingOption)
{
    addDockWidget(dockWidget, localPos.toPoint(), addingOption);
}

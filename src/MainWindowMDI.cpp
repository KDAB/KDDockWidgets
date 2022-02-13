/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "MainWindowMDI.h"
#include "private/MDILayoutWidget_p.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::Controllers;

MainWindowMDI::MainWindowMDI(const QString &uniqueName, QWidget *parent, Qt::WindowFlags flags)
    : KDDockWidgets::MainWindow(uniqueName, MainWindowOption_MDI, parent, flags)
{
}

MainWindowMDI::~MainWindowMDI()
{
}

void MainWindowMDI::addDockWidget(DockWidgetBase *dockWidget, QPoint localPos, InitialOption addingOption)
{
    auto layout = static_cast<MDILayoutWidget *>(this->layoutWidget());
    layout->addDockWidget(dockWidget, localPos, addingOption);
}

void MainWindowMDI::addDockWidget(DockWidgetBase *dockWidget, QPointF localPos, InitialOption addingOption)
{
    MainWindowMDI::addDockWidget(dockWidget, localPos.toPoint(), addingOption);
}

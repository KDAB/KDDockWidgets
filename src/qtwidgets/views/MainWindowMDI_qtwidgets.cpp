/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "MainWindowMDI_qtwidgets.h"
#include "kddockwidgets/controllers/MDILayout.h"
#include "kddockwidgets/controllers/MainWindow.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;
using namespace KDDockWidgets::Controllers;

MainWindowMDI_qtwidgets::MainWindowMDI_qtwidgets(const QString &uniqueName, QWidget *parent,
                                                 Qt::WindowFlags flags)
    : Views::MainWindow_qtwidgets(uniqueName, MainWindowOption_MDI, parent, flags)
    , Views::MainWindowMDIViewInterface(mainWindow()->mdiLayout())
{
}

MainWindowMDI_qtwidgets::~MainWindowMDI_qtwidgets()
{
}

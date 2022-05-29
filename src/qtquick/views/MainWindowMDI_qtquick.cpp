/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "MainWindowMDI_qtquick.h"
#include "controllers/MDILayout.h"
#include "controllers/MainWindow.h"
#include "MainWindow_qtquick.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;
using namespace KDDockWidgets::Controllers;

MainWindowMDI_qtquick::MainWindowMDI_qtquick(const QString &uniqueName, QQuickItem *parent, Qt::WindowFlags flags)
    : Views::MainWindow_qtquick(uniqueName, MainWindowOption_MDI, parent, flags)
    , Views::MainWindowMDI(mainWindow()->mdiLayoutWidget())
{
}

MainWindowMDI_qtquick::~MainWindowMDI_qtquick()
{
}

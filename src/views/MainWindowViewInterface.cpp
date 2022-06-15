/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group
  company <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "MainWindowViewInterface.h"
#include "kddockwidgets/controllers/MainWindow.h"

namespace KDDockWidgets::Views {

MainWindowViewInterface::MainWindowViewInterface(Controllers::MainWindow *controller)
    : m_mainWindow(controller)
{
}

MainWindowViewInterface::~MainWindowViewInterface() = default;

Controllers::MainWindow *MainWindowViewInterface::mainWindow() const
{
    return m_mainWindow;
}

void MainWindowViewInterface::init(const QString &name)
{
    m_mainWindow->init(name);
}

}

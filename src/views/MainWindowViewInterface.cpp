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

QString MainWindowViewInterface::uniqueName() const
{
    return m_mainWindow->uniqueName();
}

QStringList MainWindowViewInterface::affinities() const
{
    return m_mainWindow->affinities();
}

void MainWindowViewInterface::setAffinities(const QStringList &names)
{
    m_mainWindow->setAffinities(names);
}

MainWindowOptions MainWindowViewInterface::options() const
{
    return m_mainWindow->options();
}

bool MainWindowViewInterface::isMDI() const
{
    return m_mainWindow->isMDI();
}

bool MainWindowViewInterface::closeDockWidgets(bool force)
{
    return m_mainWindow->closeDockWidgets(force);
}

bool MainWindowViewInterface::sideBarIsVisible(KDDockWidgets::SideBarLocation loc) const
{
    return m_mainWindow->sideBarIsVisible(loc);
}

void MainWindowViewInterface::clearSideBarOverlay(bool deleteFrame)
{
    m_mainWindow->clearSideBarOverlay(deleteFrame);
}

void MainWindowViewInterface::layoutEqually()
{
    m_mainWindow->layoutEqually();
}

bool MainWindowViewInterface::anySideBarIsVisible() const
{
    return m_mainWindow->anySideBarIsVisible();
}

}

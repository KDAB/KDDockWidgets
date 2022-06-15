/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group
  company <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "MainWindowViewInterface.h"
#include "DockWidgetViewInterface.h"
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

void MainWindowViewInterface::addDockWidgetAsTab(DockWidgetViewInterface *dockView)
{
    auto dw = dockView ? dockView->dockWidget() : nullptr;
    m_mainWindow->addDockWidgetAsTab(dw);
}

void MainWindowViewInterface::addDockWidget(DockWidgetViewInterface *dockView,
                                            KDDockWidgets::Location location,
                                            DockWidgetViewInterface *relativeToDockView,
                                            KDDockWidgets::InitialOption initialOption)
{
    auto dw = dockView ? dockView->dockWidget() : nullptr;
    auto relativeTo = relativeToDockView ? relativeToDockView->dockWidget() : nullptr;
    m_mainWindow->addDockWidget(dw, location, relativeTo, initialOption);
}

bool MainWindowViewInterface::anySideBarIsVisible() const
{
    return m_mainWindow->anySideBarIsVisible();
}

void MainWindowViewInterface::moveToSideBar(DockWidgetViewInterface *dockView)
{
    auto dw = dockView ? dockView->dockWidget() : nullptr;
    m_mainWindow->moveToSideBar(dw);
}

void MainWindowViewInterface::moveToSideBar(DockWidgetViewInterface *dockView, KDDockWidgets::SideBarLocation loc)
{
    auto dw = dockView ? dockView->dockWidget() : nullptr;
    m_mainWindow->moveToSideBar(dw, loc);
}

void MainWindowViewInterface::restoreFromSideBar(DockWidgetViewInterface *dockView)
{
    auto dw = dockView ? dockView->dockWidget() : nullptr;
    m_mainWindow->restoreFromSideBar(dw);
}

void MainWindowViewInterface::overlayOnSideBar(DockWidgetViewInterface *dockView)
{
    auto dw = dockView ? dockView->dockWidget() : nullptr;
    m_mainWindow->overlayOnSideBar(dw);
}

void MainWindowViewInterface::toggleOverlayOnSideBar(DockWidgetViewInterface *dockView)
{
    auto dw = dockView ? dockView->dockWidget() : nullptr;
    m_mainWindow->toggleOverlayOnSideBar(dw);
}

void MainWindowViewInterface::layoutParentContainerEqually(DockWidgetViewInterface *dockView)
{
    auto dw = dockView ? dockView->dockWidget() : nullptr;
    m_mainWindow->layoutParentContainerEqually(dw);
}

}

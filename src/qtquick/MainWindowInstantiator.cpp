/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "MainWindowInstantiator.h"
#include "kddockwidgets/views/MainWindow_qtquick.h"
#include "qtquick/views/MainWindowMDI_qtquick.h"
#include "kddockwidgets/controllers/DockWidget.h"
#include "kddockwidgets/controllers/MainWindow.h"

#include "DockWidgetInstantiator.h"

#include "DockRegistry.h"
#include "Platform_qtquick.h"

using namespace KDDockWidgets;

MainWindowInstantiator::MainWindowInstantiator()
    : QQuickItem()
{
}

QString MainWindowInstantiator::uniqueName() const
{
    return m_uniqueName;
}

void MainWindowInstantiator::setUniqueName(const QString &name)
{
    if (name != m_uniqueName) {
        m_uniqueName = name;
        Q_EMIT uniqueNameChanged();
    }
}

MainWindowOptions MainWindowInstantiator::options() const
{
    return m_options;
}

void MainWindowInstantiator::setOptions(MainWindowOptions options)
{
    if (m_options != options) {
        m_options = options;
        Q_EMIT optionsChanged();
    }
}

QStringList MainWindowInstantiator::affinities() const
{
    return m_mainWindow ? m_mainWindow->affinities() : QStringList();
}

bool MainWindowInstantiator::isMDI() const
{
    return m_mainWindow && m_mainWindow->isMDI();
}

void MainWindowInstantiator::addDockWidget(QQuickItem *dockWidget, Location location,
                                           QQuickItem *relativeTo, QSize initialSize,
                                           InitialVisibilityOption option)
{
    if (!dockWidget || !m_mainWindow)
        return;

    Controllers::DockWidget *dw = Platform_qtquick::dockWidgetForItem(dockWidget);
    Controllers::DockWidget *relativeToDw = Platform_qtquick::dockWidgetForItem(relativeTo);

    m_mainWindow->addDockWidget(dw, location,
                                relativeToDw, { option, initialSize });
}

void MainWindowInstantiator::layoutEqually()
{
    if (m_mainWindow)
        m_mainWindow->layoutEqually();
}

void MainWindowInstantiator::layoutParentContainerEqually(Controllers::DockWidget *dw)
{
    if (m_mainWindow)
        m_mainWindow->layoutParentContainerEqually(dw);
}

void MainWindowInstantiator::moveToSideBar(Controllers::DockWidget *dw)
{
    if (m_mainWindow)
        m_mainWindow->moveToSideBar(dw);
}

void MainWindowInstantiator::moveToSideBar(Controllers::DockWidget *dw, SideBarLocation loc)
{
    if (m_mainWindow)
        m_mainWindow->moveToSideBar(dw, loc);
}

void MainWindowInstantiator::restoreFromSideBar(Controllers::DockWidget *dw)
{
    if (m_mainWindow)
        m_mainWindow->restoreFromSideBar(dw);
}

void MainWindowInstantiator::overlayOnSideBar(Controllers::DockWidget *dw)
{
    if (m_mainWindow)
        m_mainWindow->overlayOnSideBar(dw);
}

void MainWindowInstantiator::toggleOverlayOnSideBar(Controllers::DockWidget *dw)
{
    if (m_mainWindow)
        m_mainWindow->toggleOverlayOnSideBar(dw);
}

void MainWindowInstantiator::clearSideBarOverlay(bool deleteFrame)
{
    if (m_mainWindow)
        m_mainWindow->clearSideBarOverlay(deleteFrame);
}

// TODOm3
// SideBar *MainWindowInstantiator::sideBarForDockWidget(const Controllers::DockWidget *dw) const
// {
//     return m_mainWindow ? m_mainWindow->sideBarForDockWidget(dw) : nullptr;
// }

bool MainWindowInstantiator::sideBarIsVisible(SideBarLocation loc) const
{
    return m_mainWindow && m_mainWindow->sideBarIsVisible(loc);
}

bool MainWindowInstantiator::closeDockWidgets(bool force)
{
    return m_mainWindow && m_mainWindow->closeDockWidgets(force);
}

void MainWindowInstantiator::classBegin()
{
    // Nothing interesting to do here.
}

void MainWindowInstantiator::componentComplete()
{
    if (m_uniqueName.isEmpty()) {
        qWarning() << Q_FUNC_INFO
                   << "Each DockWidget need an unique name. Set the uniqueName property.";
        return;
    }

    if (DockRegistry::self()->containsMainWindow(m_uniqueName)) {
        // MainWindow already exists
        return;
    }

    if (m_uniqueName.isEmpty()) {
        qWarning() << Q_FUNC_INFO << "Name can't be empty";
        return;
    }

    if (m_mainWindow) {
        qWarning() << Q_FUNC_INFO << "Main window is already initialized";
        return;
    }

    const auto mainWindowOptions = MainWindowOptions(m_options);

    View *view = nullptr;
    if (mainWindowOptions & MainWindowOption_MDI)
        view = new Views::MainWindowMDI_qtquick(m_uniqueName, this);
    else
        view = new Views::MainWindow_qtquick(m_uniqueName, mainWindowOptions, this);

    m_mainWindow = view->asMainWindowController();
}

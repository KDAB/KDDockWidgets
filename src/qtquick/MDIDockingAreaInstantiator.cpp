/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "MDIDockingAreaInstantiator.h"
#include "kddockwidgets/views/MainWindow_qtquick.h"
#include "qtquick/views/MainWindowMDI_qtquick.h"
#include "kddockwidgets/controllers/DockWidget.h"
#include "kddockwidgets/controllers/MainWindow.h"
#include "../controllers/MDILayout.h"

#include "DockWidgetInstantiator.h"

#include "DockRegistry.h"
#include "Platform_qtquick.h"

using namespace KDDockWidgets;

MDIDockingAreaInstantiator::MDIDockingAreaInstantiator()
    : QQuickItem()
{
}

QString MDIDockingAreaInstantiator::uniqueName() const
{
    return m_uniqueName;
}

void MDIDockingAreaInstantiator::setUniqueName(const QString &name)
{
    if (name != m_uniqueName) {
        m_uniqueName = name;
        Q_EMIT uniqueNameChanged();
    }
}

QStringList MDIDockingAreaInstantiator::affinities() const
{
    return m_mainWindow ? m_mainWindow->affinities() : QStringList();
}

void MDIDockingAreaInstantiator::addDockWidget(QQuickItem *dockWidget,
                                               QPoint localPos, InitialOption addingOption)
{
    if (!dockWidget || !m_mainWindow)
        return;

    Controllers::DockWidget *dw = Platform_qtquick::dockWidgetForItem(dockWidget);

    m_mainWindow->mdiLayoutWidget()->addDockWidget(dw, localPos, addingOption);
}

bool MDIDockingAreaInstantiator::closeDockWidgets(bool force)
{
    return m_mainWindow && m_mainWindow->closeDockWidgets(force);
}

void MDIDockingAreaInstantiator::classBegin()
{
    // Nothing interesting to do here.
}

void MDIDockingAreaInstantiator::componentComplete()
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

    View *view = new Views::MainWindowMDI_qtquick(m_uniqueName, this);
    m_mainWindow = view->asMainWindowController();
}

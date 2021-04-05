/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "MainWindowInstantiator_p.h"
#include "MainWindowQuick_p.h"
#include "MainWindowMDI.h"

#include "DockRegistry_p.h"

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

    if (mainWindowOptions & MainWindowOption_MDI)
        m_mainWindow = new MainWindowMDI(m_uniqueName, this);
    else
        m_mainWindow = new MainWindowQuick(m_uniqueName, mainWindowOptions, this);
}

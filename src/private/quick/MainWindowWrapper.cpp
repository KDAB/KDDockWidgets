/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "MainWindowWrapper_p.h"
#include "MainWindowQuick_p.h"
#include "MainWindowMDI.h"

using namespace KDDockWidgets;

MainWindowWrapper::MainWindowWrapper()
    : QWidgetAdapter()
{
}

void MainWindowWrapper::init(const QString &uniqueName, int options)
{
    if (uniqueName.isEmpty()) {
        qWarning() << Q_FUNC_INFO << "Name can't be empty";
        return;
    }

    if (m_mainWindow) {
        qWarning() << Q_FUNC_INFO << "Main window is already initialized";
        return;
    }

    const auto mainWindowOptions = MainWindowOptions(options);

    if (mainWindowOptions & MainWindowOption_MDI)
        m_mainWindow = new MainWindowMDI(uniqueName, this);
    else
        m_mainWindow = new MainWindowQuick(uniqueName, mainWindowOptions, this);
}

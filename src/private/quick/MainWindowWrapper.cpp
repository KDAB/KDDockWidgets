/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "MainWindowWrapper_p.h"
#include "MainWindowQuick_p.h"

using namespace KDDockWidgets;

MainWindowWrapper::MainWindowWrapper()
    : QWidgetAdapter()
{
}

void MainWindowWrapper::init(const QString &uniqueName)
{
    if (uniqueName.isEmpty()) {
        qWarning() << Q_FUNC_INFO << "Name can't be empty";
        return;
    }

    if (m_mainWindow) {
        qWarning() << Q_FUNC_INFO << "Main window is already initialized";
        return;
    }

    m_mainWindow = new MainWindowQuick(uniqueName, MainWindowOption_None, this);
}

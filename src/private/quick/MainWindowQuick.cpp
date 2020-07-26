/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "MainWindowQuick_p.h"
#include <QDebug>

using namespace KDDockWidgets;

MainWindowQuick::MainWindowQuick(const QString &uniqueName)
    : MainWindowBase(uniqueName, MainWindowOption_None)
{
    qDebug() << "Created";
}

DropAreaWithCentralFrame *MainWindowQuick::dropArea() const
{
    return m_dropArea;
}

void MainWindowQuick::setDropArea(DropAreaWithCentralFrame *dropArea)
{
    if (m_dropArea) {
        qWarning() << Q_FUNC_INFO << "Already contains a drop area!";
        return;
    }

    qDebug() << "Got drop area";
    m_dropArea = dropArea;
    Q_EMIT dropAreaChanged();
}

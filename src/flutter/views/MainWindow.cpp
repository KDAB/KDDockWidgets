/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "MainWindow.h"
#include "kddockwidgets/core/MainWindow.h"

using namespace KDDockWidgets::flutter;

MainWindow::MainWindow(const QString &uniqueName, MainWindowOptions options,
                       flutter::View *parent, Qt::WindowFlags flags)
    : View(new Core::MainWindow(this, uniqueName, options), Core::ViewType::MainWindow, parent,
           flags)
    , MainWindowViewInterface(static_cast<Core::MainWindow *>(View::controller()))
{
    m_mainWindow->init(uniqueName);
}

MainWindow::~MainWindow()
{
}

QMargins MainWindow::centerWidgetMargins() const
{
    qDebug() << Q_FUNC_INFO << "SideBar hasn't been implemented yet";
    return {};
}

QRect MainWindow::centralAreaGeometry() const
{
    qFatal("Not implemented");
    return {};
}

void MainWindow::setContentsMargins(int left, int top, int right, int bottom)
{
    Q_UNUSED(left);
    Q_UNUSED(right);
    Q_UNUSED(top);
    Q_UNUSED(bottom);
    qDebug() << Q_FUNC_INFO << "not implemented";
}

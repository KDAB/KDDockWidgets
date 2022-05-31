/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Window.h"

#include <QDebug>

using namespace KDDockWidgets;

Window::~Window() = default;

int Window::minWidth() const
{
    return minSize().width();
}

int Window::minHeight() const
{
    return minSize().height();
}

int Window::maxWidth() const
{
    return maxSize().width();
}

int Window::maxHeight() const
{
    return maxSize().height();
}

void Window::startSystemMove()
{
    qFatal("Not needed in this platform");
}

QPoint Window::framePosition() const
{
    return frameGeometry().topLeft();
}

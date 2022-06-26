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

bool Window::containsView(View *view) const
{
    if (!view)
        return false;

    return equals(view->window());
}

bool Window::containsView(Controller *c) const
{
    if (!c)
        return false;

    return containsView(c->view());
}

QSize Window::size() const
{
    return geometry().size();
}

void Window::setPosition(QPoint pos)
{
    QRect geo = geometry();
    geo.moveTopLeft(pos);
    setGeometry(geo);
}

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/


#include "Window_flutter.h"

#include <QDebug>

using namespace KDDockWidgets;

Window_flutter::Window_flutter()
    : Window()
{
}

Window_flutter::~Window_flutter() = default;

std::shared_ptr<View> Window_flutter::rootView() const
{
    return nullptr;
}

Window::Ptr Window_flutter::transientParent() const
{
    return nullptr;
}

void Window_flutter::setGeometry(QRect) const
{
}

void Window_flutter::setVisible(bool)
{
}

bool Window_flutter::supportsHonouringLayoutMinSize() const
{
    // maybe...
    return false;
}

void Window_flutter::setWindowState(WindowState)
{
}

QRect Window_flutter::geometry() const
{
    return {};
}

void Window_flutter::setProperty(const char *, const QVariant &)
{
}

QVariant Window_flutter::property(const char *) const
{
    return {};
}

bool Window_flutter::isVisible() const
{
    return {};
}

WId Window_flutter::handle() const
{
    return {};
}

bool Window_flutter::equals(std::shared_ptr<Window>) const
{
    return {};
}

void Window_flutter::setFramePosition(QPoint)
{
}

QRect Window_flutter::frameGeometry() const
{
    return {};
}

void Window_flutter::resize(int, int)
{
}

bool Window_flutter::isActive() const
{
    return {};
}

WindowState Window_flutter::windowState() const
{
    return {};
}

QPoint Window_flutter::mapFromGlobal(QPoint) const
{
    return {};
}

QPoint Window_flutter::mapToGlobal(QPoint) const
{
    return {};
}

void Window_flutter::destroy()
{
}

QSize Window_flutter::minSize() const
{
    return {};
}

QSize Window_flutter::maxSize() const
{
    return {};
}

QPoint Window_flutter::fromNativePixels(QPoint) const
{
    return {};
}

bool Window_flutter::isFullScreen() const
{
    return {};
}

Screen::Ptr Window_flutter::screen() const
{
    return {};
}

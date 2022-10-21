/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/


#include "Window_dummy.h"

#include <QDebug>

using namespace KDDockWidgets;

Window_dummy::Window_dummy()
    : Window()
{
}

Window_dummy::~Window_dummy() = default;

std::shared_ptr<View> Window_dummy::rootView() const
{
    return nullptr;
}

Window::Ptr Window_dummy::transientParent() const
{
    return nullptr;
}

void Window_dummy::setGeometry(QRect) const
{
}

void Window_dummy::setVisible(bool)
{
}

bool Window_dummy::supportsHonouringLayoutMinSize() const
{
    // maybe...
    return false;
}

void Window_dummy::setWindowState(WindowState)
{
}

QRect Window_dummy::geometry() const
{
    return {};
}

void Window_dummy::setProperty(const char *, const QVariant &)
{
}

QVariant Window_dummy::property(const char *) const
{
    return {};
}

bool Window_dummy::isVisible() const
{
    return {};
}

WId Window_dummy::handle() const
{
    return {};
}

bool Window_dummy::equals(std::shared_ptr<Window>) const
{
    return {};
}

void Window_dummy::setFramePosition(QPoint)
{
}

QRect Window_dummy::frameGeometry() const
{
    return {};
}

void Window_dummy::resize(int, int)
{
}

bool Window_dummy::isActive() const
{
    return {};
}

WindowState Window_dummy::windowState() const
{
    return {};
}

QPoint Window_dummy::mapFromGlobal(QPoint) const
{
    return {};
}

QPoint Window_dummy::mapToGlobal(QPoint) const
{
    return {};
}

void Window_dummy::destroy()
{
}

QSize Window_dummy::minSize() const
{
    return {};
}

QSize Window_dummy::maxSize() const
{
    return {};
}

QPoint Window_dummy::fromNativePixels(QPoint) const
{
    return {};
}

bool Window_dummy::isFullScreen() const
{
    return {};
}

Screen::Ptr Window_dummy::screen() const
{
    return {};
}

void Window_dummy::onScreenChanged(QObject *, WindowScreenChangedCallback)
{
}

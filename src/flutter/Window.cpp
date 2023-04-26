/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/


#include "Window.h"

#include <QDebug>

using namespace KDDockWidgets;
using namespace KDDockWidgets::flutter;

Window::Window(std::shared_ptr<Core::View> rootView, int id)
    : Core::Window()
    , m_rootView(rootView)
    , m_id(id)
{
    if (rootView)
        setGeometry(rootView->geometry());
}

Window::~Window() = default;

std::shared_ptr<Core::View> Window::rootView() const
{
    return m_rootView;
}

Core::Window::Ptr Window::transientParent() const
{
    return nullptr;
}

void Window::setGeometry(QRect r)
{
    m_geometry = r;
}

void Window::setVisible(bool)
{
}

bool Window::supportsHonouringLayoutMinSize() const
{
    // maybe...
    return false;
}

void Window::setWindowState(WindowState)
{
}

QRect Window::geometry() const
{
    return m_geometry;
}

void Window::setProperty(const char *, const QVariant &)
{
}

QVariant Window::property(const char *) const
{
    return {};
}

bool Window::isVisible() const
{
    return {};
}

WId Window::handle() const
{
    return WId(m_id);
}

bool Window::equals(std::shared_ptr<Core::Window> w) const
{
    if (!w)
        return false;

    auto window = std::static_pointer_cast<flutter::Window>(w);
    return window->m_id == m_id;
}

void Window::setFramePosition(QPoint)
{
}

QRect Window::frameGeometry() const
{
    return {};
}

void Window::resize(int, int)
{
}

bool Window::isActive() const
{
    return {};
}

WindowState Window::windowState() const
{
    return {};
}

QPoint Window::mapFromGlobal(QPoint) const
{
    return {};
}

QPoint Window::mapToGlobal(QPoint) const
{
    return {};
}

void Window::destroy()
{
}

QSize Window::minSize() const
{
    return {};
}

QSize Window::maxSize() const
{
    return {};
}

QPoint Window::fromNativePixels(QPoint) const
{
    return {};
}

bool Window::isFullScreen() const
{
    return {};
}

Core::Screen::Ptr Window::screen() const
{
    return {};
}

void Window::onScreenChanged(QObject *, WindowScreenChangedCallback)
{
}

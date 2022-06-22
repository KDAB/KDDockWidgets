/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/


#include "Window_gtk.h"

using namespace KDDockWidgets;

Window_gtk::Window_gtk(Gtk::Window *topLevel)
    : Window()
    , m_window(topLevel)
{
    m_window->show();
}

Window_gtk::~Window_gtk() = default;

std::shared_ptr<View> Window_gtk::rootView() const
{
    // TODOgtk
    return nullptr;
}

Window::Ptr Window_gtk::transientParent() const
{
    // TODOgtk
    return nullptr;
}

void Window_gtk::setGeometry(QRect rect) const
{
    m_window->move(rect.x(), rect.y());
    m_window->resize(rect.width(), rect.height());
}

void Window_gtk::setVisible(bool is)
{
    m_window->set_visible(is);
}

bool Window_gtk::supportsHonouringLayoutMinSize() const
{
    // maybe...
    return false;
}

void Window_gtk::setWindowState(WindowState state)
{
    switch (state) {
    case WindowState::None:
        // TODOgtk: Show normal
        break;
    case WindowState::Minimized:
        // TODOgtk: Show minimized
        break;
    case WindowState::Maximized:
        // TODOgtk: Show maximized
        break;
    case WindowState::FullScreen:
        // TODOgtkgtk: Show maximized
        break;
    }
}

QRect Window_gtk::geometry() const
{
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;

    m_window->get_position(x, y);
    m_window->get_size(width, height);

    return QRect(x, y, width, height);
}

bool Window_gtk::isVisible() const
{
    return m_window->is_visible();
}

WId Window_gtk::handle() const
{
    return WId(m_window);
}

bool Window_gtk::equals(std::shared_ptr<Window> other) const
{
    if (!other)
        return false;

    auto otherGtk = static_cast<Window_gtk *>(other.get());
    return m_window == otherGtk->m_window;
}

void Window_gtk::setFramePosition(QPoint)
{
}

QRect Window_gtk::frameGeometry() const
{
    return {};
}

void Window_gtk::resize(int width, int height)
{
    m_window->resize(width, height);
}

bool Window_gtk::isActive() const
{
    return m_window->is_active();
}

WindowState Window_gtk::windowState() const
{
    return {};
}

QPoint Window_gtk::mapFromGlobal(QPoint) const
{
    // TODOgtk
    return {};
}

QPoint Window_gtk::mapToGlobal(QPoint) const
{
    // TODOgtk
    return {};
}

QScreen *Window_gtk::screen() const
{
    // Needs a KDDockWidgets::Screen class
    return {};
}

void Window_gtk::destroy()
{
    delete m_window;
}

QSize Window_gtk::minSize() const
{
    // TODOgtk
    return {};
}

QSize Window_gtk::maxSize() const
{
    // TODOgtk
    return {};
}

QPoint Window_gtk::fromNativePixels(QPoint pt) const
{
    /// Only used on Windows...
    return pt;
}

bool Window_gtk::isFullScreen() const
{
    // TODOgtk
    return false;
}

void Window_gtk::setProperty(const char *, const QVariant &)
{
}

QVariant Window_gtk::property(const char *) const
{
    return {};
}

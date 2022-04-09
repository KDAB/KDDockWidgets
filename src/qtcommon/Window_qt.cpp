/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/


#include "Window_qt.h"

#include <QWindow>
#include <QScreen>

using namespace KDDockWidgets;

Window_qt::Window_qt(QWindow *window)
    : m_window(window)
{
    m_connection = QObject::connect(window, &QWindow::screenChanged, [this] {
        screenChanged.emit();
    });
}

Window_qt::~Window_qt()
{
    QObject::disconnect(m_connection);
}

void Window_qt::setWindowState(Qt::WindowState state)
{
    m_window->setWindowState(state);
}

Qt::WindowState Window_qt::windowState() const
{
    return m_window->windowState();
}

QRect Window_qt::geometry() const
{
    return m_window->geometry();
}

void Window_qt::setProperty(const char *name, const QVariant &value)
{
    m_window->setProperty(name, value);
}

bool Window_qt::isVisible() const
{
    return m_window->isVisible();
}

WId Window_qt::handle() const
{
    if (m_window->handle())
        return m_window->winId();
    return 0;
}

QWindow *Window_qt::qtWindow() const
{
    return m_window;
}

bool Window_qt::equals(std::shared_ptr<Window> other) const
{
    auto otherQt = static_cast<Window_qt *>(other.get());
    return other && otherQt->m_window == m_window;
}

void Window_qt::setFramePosition(QPoint targetPos)
{
    m_window->setFramePosition(targetPos);
}

void Window_qt::setPosition(QPoint targetPos)
{
    m_window->setFramePosition(targetPos);
}

QRect Window_qt::frameGeometry() const
{
    return m_window->frameGeometry();
}

void Window_qt::resize(int width, int height)
{
    m_window->resize(width, height);
}

bool Window_qt::isActive() const
{
    return m_window->isActive();
}

QSize Window_qt::size() const
{
    return m_window->size();
}
/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group
  company <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "ViewWrapper.h"

#include <QDebug>

using namespace KDDockWidgets;

ViewWrapper::ViewWrapper()
    : View(nullptr, Type::ViewWrapper, nullptr)
{
}

void ViewWrapper::setParent(View *)
{
    qFatal("Not implemented");
}

QSize ViewWrapper::minSize() const
{
    qFatal("Not implemented");
    return {};
}

QSize ViewWrapper::maxSizeHint() const
{
    qFatal("Not implemented");
    return {};
}

QSize ViewWrapper::minimumSizeHint() const
{
    qFatal("Not implemented");
    return {};
}

QSize ViewWrapper::maximumSize() const
{
    qFatal("Not implemented");
    return {};
}

QRect ViewWrapper::geometry() const
{
    qFatal("Not implemented");
    return {};
}

QRect ViewWrapper::normalGeometry() const
{
    qFatal("Not implemented");
    return {};
}

void ViewWrapper::setGeometry(QRect)
{
    qFatal("Not implemented");
}

bool ViewWrapper::isVisible() const
{
    qFatal("Not implemented");
    return {};
}

void ViewWrapper::setVisible(bool)
{
    qFatal("Not implemented");
}

void ViewWrapper::move(int, int)
{
    qFatal("Not implemented");
}

void ViewWrapper::move(QPoint)
{
    qFatal("Not implemented");
}

void ViewWrapper::setSize(int, int)
{
    qFatal("Not implemented");
}

void ViewWrapper::setWidth(int)
{
    qFatal("Not implemented");
}

void ViewWrapper::setHeight(int)
{
    qFatal("Not implemented");
}

void ViewWrapper::show()
{
    qFatal("Not implemented");
}

void ViewWrapper::hide()
{
    qFatal("Not implemented");
}

void ViewWrapper::update()
{
    qFatal("Not implemented");
}

void ViewWrapper::raiseAndActivate()
{
    qFatal("Not implemented");
}

void ViewWrapper::raise()
{
    qFatal("Not implemented");
}

void ViewWrapper::activateWindow()
{
    qFatal("Not implemented");
}

bool ViewWrapper::isTopLevel() const
{
    qFatal("Not implemented");
    return {};
}

QPoint ViewWrapper::mapToGlobal(QPoint) const
{
    qFatal("Not implemented");
    return {};
}

QPoint ViewWrapper::mapFromGlobal(QPoint) const
{
    qFatal("Not implemented");
    return {};
}

void ViewWrapper::setSizePolicy(QSizePolicy)
{
    qFatal("Not implemented");
}

QSizePolicy ViewWrapper::sizePolicy() const
{
    qFatal("Not implemented");
    return {};
}

void ViewWrapper::closeWindow()
{
    qFatal("Not implemented");
}

QRect ViewWrapper::windowGeometry() const
{
    qFatal("Not implemented");
    return {};
}

QSize ViewWrapper::parentSize() const
{
    qFatal("Not implemented");
    return {};
}

bool ViewWrapper::close()
{
    qFatal("Not implemented");
    return {};
}

void ViewWrapper::setFlag(Qt::WindowType, bool)
{
    qFatal("Not implemented");
}

void ViewWrapper::setAttribute(Qt::WidgetAttribute, bool)
{
    qFatal("Not implemented");
}

bool ViewWrapper::testAttribute(Qt::WidgetAttribute) const
{
    qFatal("Not implemented");
    return {};
}

Qt::WindowFlags ViewWrapper::flags() const
{
    qFatal("Not implemented");
    return {};
}

void ViewWrapper::setWindowTitle(const QString &)
{
    qFatal("Not implemented");
}

void ViewWrapper::setWindowIcon(const QIcon &)
{
    qFatal("Not implemented");
}

void ViewWrapper::showNormal()
{
    qFatal("Not implemented");
}

void ViewWrapper::showMinimized()
{
    qFatal("Not implemented");
}

void ViewWrapper::showMaximized()
{
    qFatal("Not implemented");
}

bool ViewWrapper::isMinimized() const
{
    qFatal("Not implemented");
    return {};
}

bool ViewWrapper::isMaximized() const
{
    qFatal("Not implemented");
    return {};
}

void ViewWrapper::setMaximumSize(QSize)
{
    qFatal("Not implemented");
}

bool ViewWrapper::isActiveWindow() const
{
    qFatal("Not implemented");
    return {};
}

QWindow *ViewWrapper::windowHandle() const
{
    qFatal("Not implemented");
    return {};
}

void ViewWrapper::setFixedWidth(int)
{
    qFatal("Not implemented");
}

void ViewWrapper::setFixedHeight(int)
{
    qFatal("Not implemented");
}

std::unique_ptr<ViewWrapper> ViewWrapper::window() const
{
    qFatal("Not implemented");
    return {};
}

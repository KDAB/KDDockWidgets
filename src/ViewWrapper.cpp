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


ViewWrapper::ViewWrapper(Controller *controller, QObject *thisObj)
    : View(controller, Type::ViewWrapper, thisObj)
{
}

void ViewWrapper::setMinimumSize(QSize)
{
    qFatal("Not implemented");
}

QSize ViewWrapper::maxSizeHint() const
{
    qFatal("Not implemented");
    return {};
}

QRect ViewWrapper::normalGeometry() const
{
    qFatal("Not implemented");
    return {};
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

void ViewWrapper::setSizePolicy(QSizePolicy)
{
    qFatal("Not implemented");
}

void ViewWrapper::setFlag(Qt::WindowType, bool)
{
    qFatal("Not implemented");
}

void ViewWrapper::setAttribute(Qt::WidgetAttribute, bool)
{
    qFatal("Not implemented");
}

Qt::WindowFlags ViewWrapper::flags() const
{
    qFatal("Not implemented");
    return {};
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

void ViewWrapper::setMaximumSize(QSize)
{
    qFatal("Not implemented");
}

bool ViewWrapper::isActiveWindow() const
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

void ViewWrapper::setWindowOpacity(double)
{
    qFatal("Not implemented");
}

void ViewWrapper::releaseKeyboard()
{
    qFatal("Not implemented");
}

void ViewWrapper::render(QPainter *)
{
    qFatal("Not implemented");
}

void ViewWrapper::setMouseTracking(bool)
{
    qFatal("Not implemented");
}

std::shared_ptr<ViewWrapper> ViewWrapper::asWrapper()
{
    // could be implemented with a weak pointer, but we have no use case
    qFatal("Don't call on wrappers");
    return {};
}

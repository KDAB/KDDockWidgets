/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "View_dummy.h"
#include "private/View_p.h"
#include "private/multisplitter/Item_p.h"
#include "../Window_dummy.h"


using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;


View_dummy::View_dummy(KDDockWidgets::Controller *controller, Type type,
                       void * /*parent*/, Qt::WindowFlags) // replace void with your type
    : View(controller, type)
{
}

void View_dummy::setGeometry(QRect)
{
}

void View_dummy::move(int, int)
{
}

bool View_dummy::close()
{
    return true;
}

bool View_dummy::isVisible() const
{
    return {};
}

void View_dummy::setVisible(bool)
{
}

void View_dummy::setSize(int, int)
{
}

std::shared_ptr<View> View_dummy::rootView() const
{
    return {};
}

void View_dummy::setAttribute(Qt::WidgetAttribute, bool)
{
}

bool View_dummy::testAttribute(Qt::WidgetAttribute) const
{
    return false;
}

void View_dummy::setFlag(Qt::WindowType, bool)
{
}

Qt::WindowFlags View_dummy::flags() const
{
    return {};
}

void View_dummy::free_impl()
{
    // QObject::deleteLater();
    delete this;
}

QSize View_dummy::sizeHint() const
{
    return {};
}

QSize View_dummy::minSize() const
{
    return {};
}

QSize View_dummy::maxSizeHint() const
{
    return {};
}

QSize View_dummy::maximumSize() const
{
    return {};
}

QRect View_dummy::geometry() const
{
    return {};
}

QRect View_dummy::normalGeometry() const
{
    return {};
}

void View_dummy::setNormalGeometry(QRect)
{
}

void View_dummy::setMaximumSize(QSize)
{
}

void View_dummy::setWidth(int)
{
}

void View_dummy::setHeight(int)
{
}

void View_dummy::setFixedWidth(int)
{
}

void View_dummy::setFixedHeight(int)
{
}

void View_dummy::show()
{
}

void View_dummy::hide()
{
}

void View_dummy::updateGeometry()
{
}

void View_dummy::update()
{
}



void View_dummy::setParent(View *)
{
}

void View_dummy::raiseAndActivate()
{
}

void View_dummy::activateWindow()
{
}

void View_dummy::raise()
{
}

QVariant View_dummy::property(const char *) const
{
    return {};
}

bool View_dummy::isRootView() const
{
    return {};
}

QPoint View_dummy::mapToGlobal(QPoint) const
{
    return {};
}

QPoint View_dummy::mapFromGlobal(QPoint) const
{
    return {};
}

QPoint View_dummy::mapTo(View *, QPoint) const
{
    return {};
}

void View_dummy::setWindowOpacity(double)
{
}

void View_dummy::setSizePolicy(SizePolicy, SizePolicy)
{
}

SizePolicy View_dummy::verticalSizePolicy() const
{
    return {};
}

SizePolicy View_dummy::horizontalSizePolicy() const
{
    return {};
}

void View_dummy::setWindowTitle(const QString &)
{
}

void View_dummy::setWindowIcon(const QIcon &)
{
}

bool View_dummy::isActiveWindow() const
{
    return false;
}

void View_dummy::showNormal()
{
}

void View_dummy::showMinimized()
{
}

void View_dummy::showMaximized()
{
}

bool View_dummy::isMinimized() const
{
    return {};
}

bool View_dummy::isMaximized() const
{
    return {};
}

std::shared_ptr<Window> View_dummy::window() const
{
    return {};
}

std::shared_ptr<View> View_dummy::childViewAt(QPoint) const
{
    return {};
}

std::shared_ptr<View> View_dummy::parentView() const
{
    return {};
}

std::shared_ptr<View> View_dummy::asWrapper()
{
    return {};
}

void View_dummy::setObjectName(const QString &)
{
}

void View_dummy::grabMouse()
{
}

void View_dummy::releaseMouse()
{
}

void View_dummy::releaseKeyboard()
{
    // Not needed for QtQuick
}

void View_dummy::setFocus(Qt::FocusReason)
{
}

bool View_dummy::hasFocus() const
{
    return false;
}

Qt::FocusPolicy View_dummy::focusPolicy() const
{
    return {};
}

void View_dummy::setFocusPolicy(Qt::FocusPolicy)
{
}

QString View_dummy::objectName() const
{
    return {};
}

void View_dummy::setMinimumSize(QSize)
{
}

void View_dummy::render(QPainter *)
{
}

void View_dummy::setCursor(Qt::CursorShape)
{
}

void View_dummy::setMouseTracking(bool)
{
}

QVector<std::shared_ptr<View>> View_dummy::childViews() const
{
    return {};
}

void View_dummy::setZOrder(int)
{
}

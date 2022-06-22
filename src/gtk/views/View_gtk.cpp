/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "View_gtk.h"
#include "private/Utils_p.h"
#include "private/View_p.h"
#include "private/multisplitter/Item_p.h"
#include "../Window_gtk.h"

#include <qpa/qplatformwindow.h>
#include <QGuiApplication>
#include <QFile>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;



View_gtk::View_gtk(KDDockWidgets::Controller *controller, Type type,
                   void *parent, Qt::WindowFlags)
    : View(controller, type)
{
    Q_UNUSED(parent);
}

void View_gtk::setGeometry(QRect)
{
}


void View_gtk::move(int, int)
{
}

bool View_gtk::close()
{
    return true;
}

bool View_gtk::isVisible() const
{
    return {};
}

void View_gtk::setVisible(bool)
{
}

void View_gtk::setSize(int, int)
{
}

std::shared_ptr<View> View_gtk::rootView() const
{
    return {};
}

void View_gtk::setAttribute(Qt::WidgetAttribute, bool)
{
}

bool View_gtk::testAttribute(Qt::WidgetAttribute) const
{
    return false;
}

void View_gtk::setFlag(Qt::WindowType, bool)
{
}

Qt::WindowFlags View_gtk::flags() const
{
    return {};
}

void View_gtk::free_impl()
{
    // QObject::deleteLater();
    delete this;
}

QSize View_gtk::sizeHint() const
{
    return {};
}

QSize View_gtk::minSize() const
{
    return {};
}

QSize View_gtk::maxSizeHint() const
{
    return {};
}

QSize View_gtk::maximumSize() const
{
    return {};
}

QRect View_gtk::geometry() const
{
    return {};
}

QRect View_gtk::normalGeometry() const
{
    return {};
}

void View_gtk::setNormalGeometry(QRect)
{
}

void View_gtk::setMaximumSize(QSize)
{
}

void View_gtk::setWidth(int)
{
}

void View_gtk::setHeight(int)
{
}

void View_gtk::setFixedWidth(int)
{
}

void View_gtk::setFixedHeight(int)
{
}

void View_gtk::show()
{
}

void View_gtk::hide()
{
}

void View_gtk::updateGeometry()
{
}

void View_gtk::update()
{
}



void View_gtk::setParent(View *)
{
}

void View_gtk::raiseAndActivate()
{
}

void View_gtk::activateWindow()
{
}

void View_gtk::raise()
{
}

QVariant View_gtk::property(const char *) const
{
    return {};
}

bool View_gtk::isRootView() const
{
    return {};
}

QPoint View_gtk::mapToGlobal(QPoint) const
{
    return {};
}

QPoint View_gtk::mapFromGlobal(QPoint) const
{
    return {};
}

QPoint View_gtk::mapTo(View *, QPoint) const
{
    return {};
}

void View_gtk::setWindowOpacity(double)
{
}

void View_gtk::setSizePolicy(SizePolicy, SizePolicy)
{
}

SizePolicy View_gtk::verticalSizePolicy() const
{
    return {};
}

SizePolicy View_gtk::horizontalSizePolicy() const
{
    return {};
}

void View_gtk::setWindowTitle(const QString &)
{
}

void View_gtk::setWindowIcon(const QIcon &)
{
}

bool View_gtk::isActiveWindow() const
{
    return false;
}

void View_gtk::showNormal()
{
}

void View_gtk::showMinimized()
{
}

void View_gtk::showMaximized()
{
}

bool View_gtk::isMinimized() const
{
    return {};
}

bool View_gtk::isMaximized() const
{
    return {};
}

std::shared_ptr<Window> View_gtk::window() const
{
    return {};
}

std::shared_ptr<View> View_gtk::childViewAt(QPoint) const
{
    return {};
}

std::shared_ptr<View> View_gtk::parentView() const
{
    return {};
}

std::shared_ptr<View> View_gtk::asWrapper()
{
    return {};
}

void View_gtk::setObjectName(const QString &)
{
}

void View_gtk::grabMouse()
{
}

void View_gtk::releaseMouse()
{
}

void View_gtk::releaseKeyboard()
{
    // Not needed for QtQuick
}

void View_gtk::setFocus(Qt::FocusReason)
{
}

bool View_gtk::hasFocus() const
{
    return false;
}

Qt::FocusPolicy View_gtk::focusPolicy() const
{
    return {};
}

void View_gtk::setFocusPolicy(Qt::FocusPolicy)
{
}

QString View_gtk::objectName() const
{
    return {};
}

void View_gtk::setMinimumSize(QSize)
{
}

void View_gtk::render(QPainter *)
{
}

void View_gtk::setCursor(Qt::CursorShape)
{
}

void View_gtk::setMouseTracking(bool)
{
}

QVector<std::shared_ptr<View>> View_gtk::childViews() const
{
    return {};
}

void View_gtk::setZOrder(int)
{
}

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Platform_gtk.h"
#include "kddockwidgets/KDDockWidgets.h"

#include "Window_gtk.h"
#include "views/View_gtk.h"
#include "private/Platform_p.h"
#include "ViewFactory_gtk.h"

#include <QScreen>
#include <QApplication>
#include <QLineEdit>
#include <QAbstractButton>

#include <memory.h>


using namespace KDDockWidgets;



Platform_gtk::Platform_gtk()
{
    init();
}

void Platform_gtk::init()
{
}

Platform_gtk::~Platform_gtk()
{
}

const char *Platform_gtk::name() const
{
    return "gtk";
}

bool Platform_gtk::hasActivePopup() const
{
    return false;
}

ViewFactory *Platform_gtk::createDefaultViewFactory()
{
    return new ViewFactory_gtk();
}

Window::Ptr Platform_gtk::windowAt(QPoint) const
{
    return {};
}

int Platform_gtk::screenNumberFor(View *) const
{
    return -1;
}

QSize Platform_gtk::screenSizeFor(View *) const
{
    return {};
}

View *Platform_gtk::createView(View *) const
{
    return nullptr;
}

bool Platform_gtk::usesFallbackMouseGrabber() const
{
    return false;
}

bool Platform_gtk::inDisallowedDragView(QPoint) const
{
    return false;
}

void Platform_gtk::ungrabMouse()
{
}

std::shared_ptr<View> Platform_gtk::focusedView() const
{
    return {};
}

QVector<std::shared_ptr<Window>> Platform_gtk::windows() const
{
    return {};
}

void Platform_gtk::sendEvent(View *, QEvent *) const
{
}

int Platform_gtk::screenNumberFor(std::shared_ptr<Window>) const
{
    return {};
}

void Platform_gtk::installMessageHandler()
{
}

void Platform_gtk::uninstallMessageHandler()
{
}

std::shared_ptr<Window> Platform_gtk::tests_createWindow()
{
    auto gtkWindow = new Gtk::Window();
    return std::make_shared<Window_gtk>(gtkWindow);
}

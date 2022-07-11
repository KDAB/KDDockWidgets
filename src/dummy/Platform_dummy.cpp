/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Platform_dummy.h"
#include "kddockwidgets/KDDockWidgets.h"

#include "Window_dummy.h"
#include "views/View_dummy.h"
#include "private/Platform_p.h"
#include "ViewFactory_dummy.h"

#include <memory.h>


using namespace KDDockWidgets;

Platform_dummy::Platform_dummy()
{
    init();
}

void Platform_dummy::init()
{
}

std::shared_ptr<View> Platform_dummy::focusedView() const
{
    return {};
}

QVector<std::shared_ptr<Window>> Platform_dummy::windows() const
{
    return {};
}

void Platform_dummy::sendEvent(View *, QEvent *) const
{
}

Platform_dummy::~Platform_dummy()
{
}

const char *Platform_dummy::name() const
{
    return nullptr;
}

bool Platform_dummy::hasActivePopup() const
{
    return false;
}

ViewFactory *Platform_dummy::createDefaultViewFactory()
{
    return new ViewFactory_dummy();
}

Window::Ptr Platform_dummy::windowAt(QPoint) const
{
    return {};
}

int Platform_dummy::screenNumberFor(View *) const
{
    return -1;
}

int Platform_dummy::screenNumberFor(std::shared_ptr<Window>) const
{
    return {};
}

void Platform_dummy::installMessageHandler()
{
}

void Platform_dummy::uninstallMessageHandler()
{
}

bool Platform_dummy::isProcessingAppQuitEvent() const
{
    return {};
}

QString Platform_dummy::applicationName() const
{
    return {};
}

QString Platform_dummy::organizationName() const
{
    return {};
}

void Platform_dummy::setMouseCursor(Qt::CursorShape)
{
}

void Platform_dummy::restoreMouseCursor()
{
}

Platform::DisplayType Platform_dummy::displayType() const
{
    return {};
}

bool Platform_dummy::isLeftMouseButtonPressed() const
{
    return {};
}

QSize Platform_dummy::screenSizeFor(View *) const
{
    return {};
}

View *Platform_dummy::createView(View *) const
{
    return nullptr;
}

bool Platform_dummy::usesFallbackMouseGrabber() const
{
    return false;
}

bool Platform_dummy::inDisallowedDragView(QPoint) const
{
    return false;
}

void Platform_dummy::ungrabMouse()
{
}

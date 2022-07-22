/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Platform_flutter.h"
#include "kddockwidgets/KDDockWidgets.h"

#include "Window_flutter.h"
#include "views/View_flutter.h"
#include "private/Platform_p.h"
#include "ViewFactory_flutter.h"

#include <memory.h>


using namespace KDDockWidgets;

Platform_flutter::Platform_flutter()
{
    init();
}

void Platform_flutter::init()
{
}

std::shared_ptr<View> Platform_flutter::focusedView() const
{
    return {};
}

QVector<std::shared_ptr<Window>> Platform_flutter::windows() const
{
    return {};
}

void Platform_flutter::sendEvent(View *, QEvent *) const
{
}

Platform_flutter::~Platform_flutter()
{
}

const char *Platform_flutter::name() const
{
    return nullptr;
}

bool Platform_flutter::hasActivePopup() const
{
    return false;
}

ViewFactory *Platform_flutter::createDefaultViewFactory()
{
    return new ViewFactory_flutter();
}

Window::Ptr Platform_flutter::windowAt(QPoint) const
{
    return {};
}

int Platform_flutter::screenNumberFor(View *) const
{
    return -1;
}

int Platform_flutter::screenNumberFor(std::shared_ptr<Window>) const
{
    return {};
}

bool Platform_flutter::isProcessingAppQuitEvent() const
{
    return {};
}

QString Platform_flutter::applicationName() const
{
    return {};
}

QString Platform_flutter::organizationName() const
{
    return {};
}

void Platform_flutter::setMouseCursor(Qt::CursorShape)
{
}

void Platform_flutter::restoreMouseCursor()
{
}

Platform::DisplayType Platform_flutter::displayType() const
{
    return {};
}

bool Platform_flutter::isLeftMouseButtonPressed() const
{
    return {};
}

QSize Platform_flutter::screenSizeFor(View *) const
{
    return {};
}

View *Platform_flutter::createView(Controller *, View *) const
{
    return nullptr;
}

bool Platform_flutter::usesFallbackMouseGrabber() const
{
    return false;
}

bool Platform_flutter::inDisallowedDragView(QPoint) const
{
    return false;
}

void Platform_flutter::ungrabMouse()
{
}

#ifdef DOCKS_DEVELOPER_MODE

void Platform_flutter::installMessageHandler()
{
}

void Platform_flutter::uninstallMessageHandler()
{
}

#endif

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Platform_flutter.h"
#include "kddockwidgets/KDDockWidgets.h"

#include "Window_flutter.h"
#include "views/View_flutter.h"
#include "core/Platform_p.h"
#include "ViewFactory_flutter.h"

#include <memory.h>


using namespace KDDockWidgets;
using namespace KDDockWidgets::flutter;

Platform_flutter::Platform_flutter()
{
    init();
}

void Platform_flutter::init()
{
}

std::shared_ptr<Core::View> Platform_flutter::focusedView() const
{
    return {};
}

QVector<std::shared_ptr<Core::Window>> Platform_flutter::windows() const
{
    return {};
}

void Platform_flutter::sendEvent(Core::View *, Event *) const
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

Core::ViewFactory *Platform_flutter::createDefaultViewFactory()
{
    return new ViewFactory_flutter();
}

Core::Window::Ptr Platform_flutter::windowAt(QPoint) const
{
    return {};
}

int Platform_flutter::screenNumberFor(Core::View *) const
{
    return -1;
}

int Platform_flutter::screenNumberFor(std::shared_ptr<Core::Window>) const
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

Core::Platform::DisplayType Platform_flutter::displayType() const
{
    return {};
}

bool Platform_flutter::isLeftMouseButtonPressed() const
{
    return {};
}

QSize Platform_flutter::screenSizeFor(Core::View *) const
{
    return {};
}

Core::View *Platform_flutter::createView(Core::Controller *, Core::View *) const
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

Core::Screen::List Platform_flutter::screens() const
{
    return {};
}

Core::Screen::Ptr Platform_flutter::primaryScreen() const
{
    return {};
}


void Platform_flutter::onFloatingWindowCreated(Core::FloatingWindow *)
{
}

void Platform_flutter::onFloatingWindowDestroyed(Core::FloatingWindow *)
{
}

QPoint Platform_flutter::cursorPos() const
{
    return {};
}

void Platform_flutter::setCursorPos(QPoint)
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

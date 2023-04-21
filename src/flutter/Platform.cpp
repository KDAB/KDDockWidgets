/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Platform.h"
#include "kddockwidgets/KDDockWidgets.h"

#include "Window.h"
#include "views/View.h"
#include "core/Platform_p.h"
#include "ViewFactory.h"

#include <memory.h>


using namespace KDDockWidgets;
using namespace KDDockWidgets::flutter;

Platform::Platform()
{
    init();
}

void Platform::init()
{
}

std::shared_ptr<Core::View> Platform::focusedView() const
{
    return {};
}

QVector<std::shared_ptr<Core::Window>> Platform::windows() const
{
    return {};
}

void Platform::sendEvent(Core::View *, Event *) const
{
}

Platform::~Platform()
{
}

const char *Platform::name() const
{
    return nullptr;
}

bool Platform::hasActivePopup() const
{
    return false;
}

Core::ViewFactory *Platform::createDefaultViewFactory()
{
    return new ViewFactory();
}

Core::Window::Ptr Platform::windowAt(QPoint) const
{
    return {};
}

int Platform::screenNumberFor(Core::View *) const
{
    return -1;
}

int Platform::screenNumberFor(std::shared_ptr<Core::Window>) const
{
    return {};
}

bool Platform::isProcessingAppQuitEvent() const
{
    return {};
}

QString Platform::applicationName() const
{
    return {};
}

QString Platform::organizationName() const
{
    return {};
}

void Platform::setMouseCursor(Qt::CursorShape)
{
}

void Platform::restoreMouseCursor()
{
}

Core::Platform::DisplayType Platform::displayType() const
{
    return {};
}

bool Platform::isLeftMouseButtonPressed() const
{
    return {};
}

QSize Platform::screenSizeFor(Core::View *) const
{
    return {};
}

Core::View *Platform::createView(Core::Controller *, Core::View *) const
{
    return nullptr;
}

bool Platform::usesFallbackMouseGrabber() const
{
    return false;
}

bool Platform::inDisallowedDragView(QPoint) const
{
    return false;
}

void Platform::ungrabMouse()
{
}

Core::Screen::List Platform::screens() const
{
    return {};
}

Core::Screen::Ptr Platform::primaryScreen() const
{
    return {};
}


void Platform::onFloatingWindowCreated(Core::FloatingWindow *)
{
}

void Platform::onFloatingWindowDestroyed(Core::FloatingWindow *)
{
}

QPoint Platform::cursorPos() const
{
    return {};
}

void Platform::setCursorPos(QPoint)
{
}


#ifdef DOCKS_DEVELOPER_MODE

void Platform::installMessageHandler()
{
}

void Platform::uninstallMessageHandler()
{
}

#endif

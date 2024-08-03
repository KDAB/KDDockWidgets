/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Platform.h"
#include "ViewFactory.h"

#include <qglobal.h>


using namespace KDDockWidgets;
using namespace KDDockWidgets::slint;

Platform::Platform()
{
}

Platform::~Platform()
{
}

const char *Platform::name() const
{
    return "Slint";
}

bool Platform::hasActivePopup() const
{
    return false;
}

Core::ViewFactory *Platform::createDefaultViewFactory()
{
    return new slint::ViewFactory();
}

std::shared_ptr<Core::Window> Platform::windowAt(Point globalPos) const
{
    Q_UNUSED(globalPos)
    return {};
}

int Platform::screenNumberForView(Core::View *) const
{
    return {};
}

Size Platform::screenSizeFor(Core::View *) const
{
    return {};
}

Core::View *Platform::createView(Core::Controller *controller, Core::View *parent) const
{
    Q_UNUSED(controller)
    Q_UNUSED(parent)
    return nullptr;
}

void Platform::runDelayed(int ms, Core::DelayedCall *c)
{
    Q_UNUSED(ms);
    Q_UNUSED(c);
}

std::shared_ptr<Core::View> Platform::focusedView() const
{
    return {};
}

Vector<std::shared_ptr<Core::Window>> Platform::windows() const
{
    return {};
}

void Platform::sendEvent(Core::View *, Event *) const
{
}

int Platform::screenNumberForWindow(std::shared_ptr<Core::Window>) const
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

void Platform::setMouseCursor(Qt::CursorShape, bool discardLast)
{
    Q_UNUSED(discardLast);
}

void Platform::restoreMouseCursor()
{
}

Platform::DisplayType Platform::displayType() const
{
    return DisplayType::Other;
}

bool Platform::isLeftMouseButtonPressed() const
{
    return false;
}

Point Platform::cursorPos() const
{
    return {};
}

void Platform::setCursorPos(Point)
{
}

#ifdef DOCKS_DEVELOPER_MODE

bool QtCommon::Platform_qt::tests_waitForWindowActive(std::shared_ptr<Core::Window>, int timeout) const
{
    Q_UNUSED(timeout);
    return true;
}

bool QtCommon::Platform_qt::tests_waitForEvent(Core::Object *, QEvent::Type type, int timeout) const
{
    Q_UNUSED(type);
    Q_UNUSED(timeout);
    return true;
}

bool QtCommon::Platform_qt::tests_waitForEvent(Core::View *, QEvent::Type type, int timeout) const
{
    Q_UNUSED(type);
    Q_UNUSED(timeout);
    return true;
}

bool QtCommon::Platform_qt::tests_wait(int ms) const
{
    Q_UNUSED(ms);
    return true;
}

void QtCommon::Platform_qt::tests_pressOn(QPoint globalPos, Core::View *receiver)
{
    Q_UNUSED(globalPos);
    Q_UNUSED(receiver);
}

void QtCommon::Platform_qt::tests_pressOn(QPoint globalPos, std::shared_ptr<Core::Window> receiver)
{
    Q_UNUSED(globalPos);
    Q_UNUSED(receiver);
}

bool QtCommon::Platform_qt::tests_releaseOn(QPoint globalPos, Core::View *receiver)
{
    Q_UNUSED(globalPos);
    Q_UNUSED(receiver);

    return false;
}

void QtCommon::Platform_qt::tests_doubleClickOn(QPoint globalPos, Core::View *receiver)
{
    Q_UNUSED(globalPos);
    Q_UNUSED(receiver);
}

void QtCommon::Platform_qt::tests_doubleClickOn(QPoint globalPos, std::shared_ptr<Core::Window> receiver)
{
    Q_UNUSED(globalPos);
    Q_UNUSED(receiver);
}

bool QtCommon::Platform_qt::tests_mouseMove(QPoint globalPos, Core::View *receiver)
{
    Q_UNUSED(globalPos);
    Q_UNUSED(receiver);
    return true;
}

bool QtCommon::Platform_qt::tests_waitForResize(Core::View *, int timeout) const
{
    Q_UNUSED(timeout);
    return true;
}

bool QtCommon::Platform_qt::tests_waitForResize(Core::Controller *, int timeout) const
{
    Q_UNUSED(timeout);
    return true;
}

bool QtCommon::Platform_qt::tests_waitForDeleted(Core::View *, int timeout) const
{
    Q_UNUSED(timeout);
    return true;
}

bool QtCommon::Platform_qt::tests_waitForDeleted(Core::Controller *, int timeout) const
{
    Q_UNUSED(timeout);
    return true;
}

#endif

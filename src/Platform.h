/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "docks_export.h"
#include "ViewWrapper.h"

#include "kdbindings/signal.h"

#include <QEvent>
#include <memory.h>

namespace KDDockWidgets {

class FrameworkWidgetFactory;
class Window;

/// @brief implements functions specific to a particular platform
/// A platform can be for example qtwidgets, qtquick, etc.
class DOCKS_EXPORT Platform
{
public:
    virtual ~Platform();
    /// @brief Returns the name of the platform, only "qtwidgets" and "qtquick"
    virtual const char *name() const = 0;

    /// @brief Returns the platform singleton
    static Platform *instance();

    /// @brief Returns whether a popup is open
    /// Usually not needed to override. Investigate further in case side bars aren't auto hidding
    virtual bool hasActivePopup() const;

    /// @brief Returns the focused view, if any
    virtual std::shared_ptr<ViewWrapper> focusedView() const = 0;

    /// @brief Returns the specified QObject casted to View
    /// Nullptr if it's not a view. TODOv2: This is shared between the
    /// QtQuick and QWidgets impl, but will be remove once we started removing Qt from backend
    virtual std::shared_ptr<ViewWrapper> qobjectAsView(QObject *) const = 0;
    virtual std::shared_ptr<Window> qobjectAsWindow(QObject *) const = 0;

    /// @brief Returns all windows
    virtual QVector<std::shared_ptr<Window>> windows() const = 0;

    /// @brief Creates and returns the default FrameworkWidgetFactory
    virtual FrameworkWidgetFactory *createDefaultFrameworkWidgetFactory() = 0;

#ifdef DOCKS_DEVELOPER_MODE
    /// @brief Waits for the specified window to be active (have the keyboard focus)
    /// Window::isActive() should return true
    /// @sa Window::isActive()
    virtual bool tests_waitForWindowActive(std::shared_ptr<Window>, int timeout = 5000) const = 0;

    /// @brief Waits for the specified view to receive a resize event
    /// Returns true if the view was resized until timeout was reached
    virtual bool tests_waitForResize(View *, int timeout = 2000) const = 0;
    virtual bool tests_waitForResize(Controller *, int timeout = 2000) const = 0;

    /// @brief Waits for the specified view to receive the specified event
    /// Returns true if the view received said event until timeout was reached
    virtual bool tests_waitForEvent(QObject *w, QEvent::Type type, int timeout = 5000) const = 0;
    virtual bool tests_waitForEvent(View *, QEvent::Type type, int timeout = 5000) const = 0;
    virtual bool tests_waitForEvent(std::shared_ptr<Window>, QEvent::Type type, int timeout = 5000) const = 0;

    virtual void tests_sendEvent(View *, QEvent *) const = 0;
    virtual void tests_sendEvent(std::shared_ptr<Window> window, QEvent *ev) const = 0;

#endif

public:
    /// @brief This signal is emitted when the currently focused view changes
    KDBindings::Signal<std::shared_ptr<ViewWrapper>> focusedViewChanged;

protected:
    Platform();
};

}

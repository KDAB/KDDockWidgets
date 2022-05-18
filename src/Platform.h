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
#include "KDDockWidgets.h"

#include "kdbindings/signal.h"

#include <QEvent>

#include <vector>
#include <memory.h>

#ifdef DOCKS_DEVELOPER_MODE
#include "private/multisplitter/Item_p.h"
#endif

namespace KDDockWidgets {

namespace Controllers {
class ClassicIndicators;
class SegmentedIndicators;
}

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

    /// @brief Returns the window at the specified global coordinates
    virtual std::shared_ptr<Window> windowAt(QPoint globalPos) const = 0;

    /// @brief Sends the specified event to the specified view
    virtual void sendEvent(View *, QEvent *) const = 0;

    /// @brief Returns the screen index for the specified view or window.
    /// It's up to the platform to decide how screens are ordered, kddw won't care.
    virtual int screenNumberFor(View *) const = 0;
    virtual int screenNumberFor(std::shared_ptr<Window>) const = 0;

    /// @brief Returns the size of the screen where this view is in
    virtual QSize screenSizeFor(View *) const = 0;

    /// @brief Create an empty view
    /// For Qt this would just returns a empty QWidget or QQuickItem
    /// other frontends can return something as basic.
    virtual View *createView(View *parent = nullptr) const = 0;

    /// @brief Creates the view that will parent the classic drop indicators
    virtual View *createClassicDropIndicatorOverlayView(Controllers::ClassicIndicators *controller, View *parent = nullptr) const = 0;

    /// @brief Creates the view that will parent the classic drop indicators
    virtual View *createSegmentedDropIndicatorOverlayView(Controllers::SegmentedIndicators *controller, View *parent = nullptr) const = 0;

    /// @brief Returns whether this platform is QtWidgets
    bool isQtWidgets() const;

    /// @brief Returns whether this platform is QtQuick
    bool isQtQuick() const;

    /// @brief Returns how many pixels the mouse must move for a drag to start
    virtual int startDragDistance() const;

#ifdef DOCKS_DEVELOPER_MODE

    struct CreateViewOptions
    {
        bool isVisible = false;
        QSize sizeHint = {};
        QSize minSize = { 200, 200 };
        QSize maxSize = Layouting::Item::hardcodedMaximumSize;
    };

    /// @brief list the list of frontend types supported by this build
    static std::vector<KDDockWidgets::FrontendType> frontendTypes();

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

    /// @brief Waits for the specified view to be deleted
    virtual bool tests_waitForDeleted(View *, int timeout = 2000) const = 0;

    virtual void tests_sendEvent(std::shared_ptr<Window> window, QEvent *ev) const = 0;

    /// @brief Creates the platform. Called by the tests at startup.
    /// For any custom behaviour in your derived Platform override tests_initPlatform_impl()
    static void tests_initPlatform(int &argc, char *argv[], KDDockWidgets::FrontendType);

    /// @brief Deletes the platform. Called at end of tests.
    /// For any custom behaviour in your derived Platform override tests_deinitPlatform_impl()
    static void tests_deinitPlatform();

    /// @brief Creates a view with the specified parent
    /// If the parent is null then a new window is created and the returned view will be the root view
    virtual View *tests_createView(CreateViewOptions, View *parent = nullptr) = 0;

    /// @brief Returns a view that can have keyboard focus
    /// For example a line edit. This is used to for testing focus related features.
    virtual View *tests_createFocusableView(CreateViewOptions, View *parent = nullptr) = 0;

    /// @brief Returns a view that rejects close events
    virtual View *tests_createNonClosableView(View *parent = nullptr) = 0;

    /// @brief halts the test during the specified number of milliseconds
    /// The event loop keeps running. Use this for debugging purposes so you can interact with your test
    /// and see what's goign on
    virtual void tests_wait(int ms) = 0;

protected:
    /// @brief Implement any needed initializations before tests starting to run, if any
    /// Override in derived classes for custom behavior.
    virtual void tests_initPlatform_impl()
    {
    }

    /// @brief Implement any needed cleanup after the tests runs, if any
    /// Override in derived classes for custom behavior.
    virtual void tests_deinitPlatform_impl()
    {
    }

#endif

public:
    /// @brief This signal is emitted when the currently focused view changes
    KDBindings::Signal<std::shared_ptr<ViewWrapper>> focusedViewChanged;

protected:
    Platform();
};

}

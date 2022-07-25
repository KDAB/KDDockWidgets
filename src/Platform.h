/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/docks_export.h"
#include "View.h"
#include "kddockwidgets/KDDockWidgets.h"

#include <QEvent>

#include <vector>
#include <memory.h>

namespace KDDockWidgets {

namespace Controllers {
class ClassicIndicators;
class SegmentedIndicators;
}

class EventFilterInterface;
class ViewFactory;
class Window;

/// @brief implements functions specific to a particular platform
/// A platform can be for example qtwidgets, qtquick, etc.
class DOCKS_EXPORT Platform
{
public:
    /// @brief Enum describing the graphics stack type
    enum class DisplayType {
        Other = 0,
        X11 = 1,
        Wayland = 2,
        QtOffscreen = 3,
        QtEGLFS = 4,
        Windows = 5
    };

    virtual ~Platform();
    /// @brief Returns the name of the platform, only "qtwidgets" and "qtquick"
    virtual const char *name() const = 0;

    /// @brief Returns the platform singleton
    static Platform *instance();

    /// @brief Returns whether a popup is open
    /// Usually not needed to override. Investigate further in case side bars aren't auto hiding
    virtual bool hasActivePopup() const;

    /// @brief Returns the focused view, if any
    virtual std::shared_ptr<View> focusedView() const = 0;

    /// @brief Returns all windows
    virtual QVector<std::shared_ptr<Window>> windows() const = 0;

    /// @brief Creates and returns the default ViewFactory
    virtual ViewFactory *createDefaultViewFactory() = 0;

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
    virtual View *createView(Controller *, View *parent = nullptr) const = 0;

    /// @brief Returns whether this platform is QtWidgets
    bool isQtWidgets() const;

    /// @brief Returns whether this platform is QtQuick
    bool isQtQuick() const;

    /// @brief Returns how many pixels the mouse must move for a drag to start
    /// This is usually 4 by default (QApplication::startDragDistance() for QtWidgets)
    /// You can override by calling Config::setStartDragDistance(), so you don't need to create
    /// a new Platform class.
    int startDragDistance() const;

    /// @brief Return whether we use the global event filter based mouse grabber
    virtual bool usesFallbackMouseGrabber() const = 0;

    /// @brief Returns whether the specified global position is on top of a view
    /// that isn't draggable. This is needed since not the entire title bar is draggable.
    /// For example, clicking on the close button shouldn't start a drag.
    virtual bool inDisallowedDragView(QPoint globalPos) const = 0;

    /// @brief Releases the mouse grab, if any
    virtual void ungrabMouse() = 0;

    /**
     * @brief Returns whether we're processing a QEvent::Quit
     *
     * Used internally to know if we should let Qt close a NonClosable dock widget at shutdown time.
     */
    virtual bool isProcessingAppQuitEvent() const = 0;

    /// @brief Installs a global event filter
    /// Events will be forwarded to the specified EventFilterInterface
    void installGlobalEventFilter(EventFilterInterface *);

    /// @brief Removes a global event filter
    void removeGlobalEventFilter(EventFilterInterface *);

    /// @brief Returns the application name
    /// This name will be used as title of floating dock widgets which contain more than 1 group
    virtual QString applicationName() const = 0;

    /// @brief Returns the organization name
    /// Used in the path for storing config
    virtual QString organizationName() const = 0;

    /// @brief Sets the mouse cursor to the specified shape, this has an application-wide effect
    /// Call restoreMouseCursor() to set the previous cursor shape
    virtual void setMouseCursor(Qt::CursorShape) = 0;

    /// @brief Undoes the call to setMouseCursor()
    virtual void restoreMouseCursor() = 0;

    /// @brief Returns the type of graphics stack being used
    virtual DisplayType displayType() const = 0;

    /// @brief Returns whether the left mouse button is pressed
    virtual bool isLeftMouseButtonPressed() const = 0;

    /// @brief Returns all available screens
    virtual Screen::List screens() const = 0;

    virtual Screen::Ptr primaryScreen() const = 0;

#ifdef DOCKS_DEVELOPER_MODE

    struct CreateViewOptions
    {
        bool isVisible = false;
        QSize sizeHint = {};
        QSize minSize = { 0, 0 };
        QSize maxSize = QSize(16777215, 16777215);
        QSize size = { 1000, 1000 };
        bool createWindow = false;
    };

    class WarningObserver
    {
        Q_DISABLE_COPY(WarningObserver)
    public:
        WarningObserver() = default;
        virtual ~WarningObserver();
        virtual void onFatal() = 0;
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
    virtual bool tests_waitForDeleted(QObject *, int timeout = 2000) const = 0;

    virtual void tests_sendEvent(std::shared_ptr<Window> window, QEvent *ev) const = 0;

    /// @brief Creates the platform. Called by the tests at startup.
    /// For any custom behaviour in your derived Platform override tests_initPlatform_impl()
    static void tests_initPlatform(int &argc, char *argv[], KDDockWidgets::FrontendType);

    /// @brief Deletes the platform. Called at end of tests.
    /// For any custom behaviour in your derived Platform override tests_deinitPlatform_impl()
    static void tests_deinitPlatform();

    /// @brief Creates a Window. For the sole purpose of unit-testing Window.
    /// The created window should be visible.
    virtual std::shared_ptr<Window> tests_createWindow() = 0;

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
    /// and see what's going on
    virtual void tests_wait(int ms) = 0;

    virtual void installMessageHandler() = 0;
    virtual void uninstallMessageHandler() = 0;

    /// @brief Creates a main window. This is not API that the user will use, but used
    /// internally by some tools that need a main window
    virtual Controllers::MainWindow *createMainWindow(const QString &uniqueName, CreateViewOptions,
                                                      MainWindowOptions options = MainWindowOption_HasCentralFrame,
                                                      View *parent = nullptr,
                                                      Qt::WindowFlags = {}) const = 0;

    static QString s_expectedWarning;
    static WarningObserver *s_warningObserver;
    int m_numWarningsEmitted = 0;

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
    class Private;
    Private *const d;

protected:
    virtual int startDragDistance_impl() const;
    Platform();
};

#ifdef DOCKS_DEVELOPER_MODE

struct SetExpectedWarning
{
    explicit SetExpectedWarning(const QString &s)
    {
        if (!s.isEmpty())
            Platform::s_expectedWarning = s;
    }

    ~SetExpectedWarning()
    {
        Platform::s_expectedWarning.clear();
    }

    Q_DISABLE_COPY(SetExpectedWarning)
};

#endif

}

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "docks_export.h"
#include "Controller.h"

#include <QSize> // TODO Remove Qt headers, introduce Size and Rect structs
#include <QRect>
#include <QObject>
#include <QSizePolicy>

#include "kdbindings/signal.h"

#include <memory>

namespace Layouting {
class Item;
}

class QCloseEvent;
class QFocusEvent;
class QSizePolicy;
class QScreen;
class QPainter;

namespace KDDockWidgets {

class ViewWrapper;
class Controller;
class Window;

namespace Controllers {
class MDILayout;
class DropArea;
class DockWidget;
class FloatingWindow;
class Frame;
class Layout;
class Stack;
class TabBar;
class TitleBar;
class MainWindow;
}

using HANDLE = const void *;
using WId = quintptr;

class DOCKS_EXPORT View
{
public:
    explicit View(Controller *controller, Type, QObject *thisObj);
    virtual ~View();

    virtual void init() {};
    QObject *asQObject() const;
    QObject *parent() const;

    /// @brief Returns this view's controller
    Controller *controller() const;

    ///@brief returns an id for corelation purposes for saving layouts
    QString id() const;

    ///@brief Returns the type of this view
    Type type() const;

    /// @brief Deletes this view.
    /// The default impl will just do a normal C++ "delete", but derived classes are free
    /// to implement other ways, for example QObject::deleteLater(), which is recommended for Qt.
    /// @sa free_impl()
    void free();

    /// @brief Returns whether free() has already been called
    bool freed() const;

    /// @brief Returns whether the DTOR is currently running. freed() might be true while inDtor false,
    /// as the implementation of free() is free to delay it (with deleteLater() for example)
    bool inDtor() const;

    /// @brief Returns whether this view represents the same GUI element as the other
    bool equals(const View *other) const;
    bool equals(const std::shared_ptr<ViewWrapper> &) const;

    /// @brief Returns a handle for the GUI element
    /// This value only makes sense to the frontend. For example, for QtQuick it might be a
    /// QQuickItem, while for QtWidgets it's a QWidget *. Can be whatever the frontend developer wants,
    /// as long as it uniquely identifies the GUI element. KDDW backend only uses it for comparison purposes
    HANDLE handle() const;

    /// @brief Returns whether the gui item represented by this view was already deleted
    /// Usually false, as KDDW internal gui elements inherit View, and nobody will access them after destruction.
    /// However, ViewWrapper derived classes, wrap an existing gui element, which might get deleted.
    /// Override isNull() in our ViewWrapper subclasses and return true if the wrapped gui element was already deleted
    virtual bool isNull() const;

    /// @brief Called by the layouting engine
    /// Override it in case your widget needs to know where it is in the layout. Usually only needed by Frame.
    virtual void setLayoutItem(Layouting::Item *) {};

    virtual void setParent(View *) = 0;
    virtual QSize sizeHint() const;
    virtual QSize minSize() const = 0;
    virtual void setMinimumSize(QSize) = 0;
    virtual int minimumWidth() const
    {
        return minSize().width();
    }

    virtual int minimumHeight() const
    {
        return minSize().height();
    }

    virtual Qt::FocusPolicy focusPolicy() const = 0;
    virtual bool hasFocus() const = 0;
    virtual QSize maxSizeHint() const = 0;
    virtual QSize maximumSize() const = 0;
    virtual QRect geometry() const = 0;
    virtual QRect normalGeometry() const = 0;
    virtual void setGeometry(QRect) = 0;
    virtual bool isVisible() const = 0;
    virtual void setVisible(bool) = 0;
    virtual void move(int x, int y) = 0;
    void move(QPoint);
    virtual void setSize(int width, int height) = 0;
    void setSize(QSize);
    virtual void setWidth(int width) = 0;
    virtual void setHeight(int height) = 0;
    virtual void show() = 0;
    virtual void hide() = 0;
    virtual void update() = 0;
    virtual void raiseAndActivate() = 0;
    virtual void raise() = 0;
    virtual void activateWindow() = 0;
    virtual bool isRootView() const = 0;
    virtual QPoint mapToGlobal(QPoint) const = 0;
    virtual QPoint mapFromGlobal(QPoint) const = 0;
    virtual QPoint mapTo(View *, QPoint) const = 0;
    virtual void setSizePolicy(QSizePolicy) = 0;
    virtual QSizePolicy sizePolicy() const = 0;
    void closeRootView();
    QRect windowGeometry() const;
    QSize parentSize() const;
    virtual bool close() = 0;
    virtual void setFlag(Qt::WindowType, bool = true) = 0;
    virtual void setAttribute(Qt::WidgetAttribute, bool enable = true) = 0;
    virtual bool testAttribute(Qt::WidgetAttribute) const = 0;
    virtual Qt::WindowFlags flags() const = 0;
    virtual void setWindowTitle(const QString &title) = 0;
    virtual void setWindowIcon(const QIcon &) = 0;

    // TODOm3: Move these to Window instead
    virtual void showNormal() = 0;
    virtual void showMinimized() = 0;
    virtual void showMaximized() = 0;
    virtual bool isMinimized() const = 0;
    virtual bool isMaximized() const = 0;

    virtual void createPlatformWindow();
    virtual void setMaximumSize(QSize sz) = 0;
    virtual bool isActiveWindow() const = 0;
    virtual void setFixedWidth(int) = 0;
    virtual void setFixedHeight(int) = 0;
    virtual void grabMouse() = 0;
    virtual void releaseMouse() = 0;
    virtual void releaseKeyboard() = 0;
    QScreen *screen() const;
    virtual void setFocus(Qt::FocusReason) = 0;
    virtual void setFocusPolicy(Qt::FocusPolicy) = 0;
    virtual void setWindowOpacity(double) = 0;
    virtual void setCursor(Qt::CursorShape) = 0;
    virtual void setMouseTracking(bool) = 0;

    // TODOm2: Check if these two should be in the controller or on view
    virtual void onLayoutRequest()
    {
    }

    virtual bool onResize(QSize /*newSize*/)
    {
        return false;
    }

    virtual bool onFocusInEvent(QFocusEvent *)
    {
        return false;
    }

    virtual QVariant property(const char *) const = 0;
    virtual void setObjectName(const QString &) = 0;
    virtual QString objectName() const = 0;
    virtual void render(QPainter *) = 0;

    /// @brief Returns the views's geometry, but always in global space
    QRect globalGeometry() const;

    QPoint pos() const;
    QSize size() const;
    QRect rect() const;
    int x() const;
    int y() const;
    int height() const;
    int width() const;
    void resize(QSize);
    void resize(int w, int h);

    static QSize hardcodedMinimumSize();
    static QSize boundedMaxSize(QSize min, QSize max);

    virtual std::shared_ptr<ViewWrapper> childViewAt(QPoint localPos) const = 0;

    /// @brief Returns the top-level gui element which this view is inside
    /// It's the root view of the window.
    virtual std::shared_ptr<ViewWrapper> rootView() const = 0;

    /// @brief Returns the window this view is inside
    /// For the Qt frontend, this wraps a QWindow.
    /// Like QWidget::window()
    virtual std::shared_ptr<Window> window() const = 0;

    /// @brief Convenience. See Window::transientWindow().
    std::shared_ptr<Window> transientWindow() const;

    /// @brief Returns the gui element's parent. Like QWidget::parentWidget()
    virtual std::shared_ptr<ViewWrapper> parentView() const = 0;

    /// @brief Returns this view, but as a wrapper
    virtual std::shared_ptr<ViewWrapper> asWrapper() = 0;

    /// @brief Returns whether the view is of the specified type
    /// Virtual so it can be overridden by ViewWrapper. When we're wrapping an existing GUI element
    /// only the specific frontend can know what's the actual type
    virtual bool is(Type) const;

    /// @brief Sets the z order
    /// Not supported on all platforms
    virtual void setZOrder(int) {};

    /// @brief if this view is a FloatingWindow, then returns its controller
    /// Mostly to save the call sites from having too many casts
    Controllers::FloatingWindow *asFloatingWindowController() const;
    Controllers::Frame *asFrameController() const;
    Controllers::TitleBar *asTitleBarController() const;
    Controllers::TabBar *asTabBarController() const;
    Controllers::Stack *asStackController() const;
    Controllers::DockWidget *asDockWidgetController() const;
    Controllers::MainWindow *asMainWindowController() const;
    Controllers::DropArea *asDropAreaController() const;
    Controllers::MDILayout *asMDILayoutController() const;
    Controllers::Layout *asLayout() const;

    /// @brief returns whether this view is inside the specified window
    bool isInWindow(std::shared_ptr<Window> window) const;

    /// @brief If true, it means destruction hasn't happen yet but is about to happen.
    /// Useful when a controller is under destructions and wants all related views to stop painting or
    /// doing anything that would call back into the controller.
    /// If false, it doesn't mean anything, as not all controllers are using this.
    void setAboutToBeDestroyed();
    bool aboutToBeDestroyed() const;

    /// @Returns a list of child views
    virtual QVector<std::shared_ptr<View>> childViews() const = 0;

    /// @brief Returns the controller of the first parent view of the specified type
    /// Goes up the view hierarchy chain until it finds it. Returns nullptr otherwise.
    static Controller *firstParentOfType(const QObject *child, KDDockWidgets::Type);

    /// @overload
    Controller *firstParentOfType(KDDockWidgets::Type) const;

public:
    /// @brief signal emitted once ~View starts
    KDBindings::Signal<> beingDestroyed;

    /// @brief signal emitted when something tried to close this view
    KDBindings::Signal<QCloseEvent *> closeRequested;

    /// @brief signal emitted when when constraints change, for example min/max sizes
    KDBindings::Signal<> layoutInvalidated;

protected:
    virtual void free_impl();

    Controller *const m_controller;
    QObject *const m_thisObj;

private:
    bool m_freed = false;
    bool m_inDtor = false;
    bool m_aboutToBeDestroyed = false;
    const QString m_id;
    const Type m_type;
};

}

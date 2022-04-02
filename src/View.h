/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/docks_export.h"
#include "Controller.h"

#include <QSize> // TODO Remove Qt headers, introduce Size and Rect structs
#include <QRect>
#include <QObject>
#include <QSizePolicy>

#include <memory>

namespace Layouting {
class Item;
}

class QFocusEvent;
class QSizePolicy;
class QWindow;
class QScreen;

namespace KDDockWidgets {

class ViewWrapper;
class Controller;

namespace Controllers {
class DockWidget;
class FloatingWindow;
class Frame;
class Stack;
class TabBar;
class TitleBar;
}

using HANDLE = const void *;

class DOCKS_EXPORT View
{
public:
    explicit View(Controller *controller, Type, QObject *thisObj);
    virtual ~View();

    virtual void init() {};
    QObject *asQObject() const;
    QWidget *asQWidget() const; // TODOv2: Remove
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
    bool equals(const std::unique_ptr<ViewWrapper> &) const;

    /// @brief Returns a handle for the GUI element
    /// This value only makes sense to the frontend. For example, for QtQuick it might be a
    /// QtQuickItem, while for QtWidgets it's a QWidget *. Can be whatever the frontend developer wants,
    /// as long as it uniquely identifies the GUI element. KDDW backend only uses it for comparison purposes
    virtual HANDLE handle() const = 0;

    /// @brief Called by the layouting engine
    /// Override it in case your widget needs to know where it is in the layout. Usually only needed by Frame.s
    virtual void setLayoutItem(Layouting::Item *) {};

    virtual void setParent(View *) = 0;
    virtual QSize sizeHint() const;
    virtual QSize minSize() const = 0;
    virtual int minimumWidth() const
    {
        return minSize().width();
    }

    virtual int minimumHeight() const
    {
        return minSize().height();
    }

    virtual QSize maxSizeHint() const = 0;
    virtual QSize minimumSizeHint() const = 0;
    virtual QSize maximumSize() const = 0;
    virtual QRect geometry() const = 0;
    virtual QRect normalGeometry() const = 0;
    virtual void setGeometry(QRect) = 0;
    virtual bool isVisible() const = 0;
    virtual void setVisible(bool) = 0;
    virtual void move(int x, int y) = 0;
    virtual void move(QPoint) = 0;
    virtual void setSize(int width, int height) = 0;
    virtual void setWidth(int width) = 0;
    virtual void setHeight(int height) = 0;
    virtual void show() = 0;
    virtual void hide() = 0;
    virtual void update() = 0;
    virtual void raiseAndActivate() = 0;
    virtual void raise() = 0;
    virtual void activateWindow() = 0;
    virtual bool isTopLevel() const = 0;
    bool isWindow() const
    {
        return isTopLevel();
    };
    virtual QPoint mapToGlobal(QPoint) const = 0;
    virtual QPoint mapFromGlobal(QPoint) const = 0;
    virtual void setSizePolicy(QSizePolicy) = 0;
    virtual QSizePolicy sizePolicy() const = 0;
    virtual void closeWindow() = 0;
    virtual QRect windowGeometry() const = 0;
    virtual QSize parentSize() const = 0;
    virtual bool close() = 0;
    virtual void setFlag(Qt::WindowType, bool = true) = 0;
    virtual void setAttribute(Qt::WidgetAttribute, bool enable = true) = 0;
    virtual bool testAttribute(Qt::WidgetAttribute) const = 0;
    virtual Qt::WindowFlags flags() const = 0;
    virtual void setWindowTitle(const QString &title) = 0;
    virtual void setWindowIcon(const QIcon &) = 0;
    virtual void showNormal() = 0;
    virtual void showMinimized() = 0;
    virtual void showMaximized() = 0;
    virtual bool isMinimized() const = 0;
    virtual bool isMaximized() const = 0;
    virtual void setMaximumSize(QSize sz) = 0;
    virtual bool isActiveWindow() const = 0;
    virtual QWindow *windowHandle() const = 0;
    virtual void setFixedWidth(int) = 0;
    virtual void setFixedHeight(int) = 0;
    virtual void grabMouse() = 0;
    virtual void releaseMouse() = 0;
    virtual QScreen *screen() const = 0;

    // TODOv2: Check if these two should be in the controller or on view
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

    virtual void setObjectName(const QString &) = 0;

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


    /// @brief Returns the top-level gui element which this one is on
    /// Like QWidget::window()
    virtual std::unique_ptr<ViewWrapper> window() const = 0;

    /// @brief Returns the gui element's parent. Like QWidget::parentWidget()
    virtual std::unique_ptr<ViewWrapper> parentView() const = 0;

    template<typename T>
    static QSize widgetMinSize(const T *w)
    {
        const int minW = w->minimumWidth() > 0 ? w->minimumWidth()
                                               : w->minimumSizeHint().width();

        const int minH = w->minimumHeight() > 0 ? w->minimumHeight()
                                                : w->minimumSizeHint().height();

        return QSize(minW, minH).expandedTo(View::hardcodedMinimumSize());
    }

    template<typename T>
    static QSize widgetMaxSize(const T *w)
    {
        // The max size is usually QWidget::maximumSize(), but we also honour the QSizePolicy::Fixed+sizeHint() case
        // as widgets don't need to have QWidget::maximumSize() to have a max size honoured

        const QSize min = widgetMinSize(w);
        QSize max = w->maximumSize();
        max = View::boundedMaxSize(min, max); // for safety against weird values

        const QSizePolicy policy = w->sizePolicy();

        if (policy.verticalPolicy() == QSizePolicy::Fixed || policy.verticalPolicy() == QSizePolicy::Maximum)
            max.setHeight(qMin(max.height(), w->sizeHint().height()));
        if (policy.horizontalPolicy() == QSizePolicy::Fixed || policy.horizontalPolicy() == QSizePolicy::Maximum)
            max.setWidth(qMin(max.width(), w->sizeHint().width()));

        max = View::boundedMaxSize(min, max); // for safety against weird values
        return max;
    }

    /// @brief Returns whether the view is of the specified type
    /// Virtual so it can be overridden by ViewWrapper. When we're wrapping an existing GUI element
    /// only the specific frontend can know what's the actual type
    virtual bool is(Type) const;


    /// @brief if this view is a FloatingWindow, then returns its controller
    /// Mostly to save the call sites from having too many casts
    Controllers::FloatingWindow *asFloatingWindowController() const;
    Controllers::Frame *asFrameController() const;
    Controllers::TitleBar *asTitleBarController() const;
    Controllers::TabBar *asTabBarController() const;
    Controllers::Stack *asStackController() const;
    Controllers::DockWidget *asDockWidgetController() const;

protected:
    virtual void free_impl();

    Controller *const m_controller;
    QObject *const m_thisObj;

private:
    bool m_freed = false;
    bool m_inDtor = false;
    const QString m_id;
    const Type m_type;
};

}

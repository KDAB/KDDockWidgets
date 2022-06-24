/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "View.h"

#include <QVector>

#include "kdbindings/signal.h"

QT_BEGIN_NAMESPACE
class QScreen;
QT_END_NAMESPACE

namespace KDDockWidgets {

/// @brief Represents a top-level window
/// In Qt for example, this would be equivalent to QWindow.
/// In doesn't take ownership, just gives a generic API to an existing window.

class DOCKS_EXPORT Window
{
public:
    using Ptr = std::shared_ptr<Window>;
    using List = QVector<Ptr>;

    virtual ~Window();
    virtual void setWindowState(Qt::WindowState) = 0;
    virtual QRect geometry() const = 0;
    virtual void setGeometry(QRect) const = 0;
    virtual void setProperty(const char *name, const QVariant &value) = 0;
    virtual QVariant property(const char *name) const = 0;
    virtual bool isVisible() const = 0;
    virtual void setVisible(bool) = 0;
    virtual WId handle() const = 0;
    virtual bool equals(std::shared_ptr<Window> other) const = 0;

    /// @brief Returns the root view of this window
    /// For example, for QtWidgets, this would be the top-level QWidget
    /// represented by this QWindow
    virtual std::shared_ptr<View> rootView() const = 0;

    /// @brief Returns the size of this window
    virtual QSize size() const = 0;

    /// @brief Sets the position of the window at targetPos
    /// This ignores any frame (native decos the window has)
    virtual void setPosition(QPoint targetPos) = 0;

    /// @brif Returns the position of the top-left corner, including native frame.
    QPoint framePosition() const;

    /// @brief Sets the position of the window at targetPos
    virtual void setFramePosition(QPoint targetPos) = 0;

    /// @brief Returns the geometry of the window including its frame (window decos)
    virtual QRect frameGeometry() const = 0;

    /// @brief Resizes the window
    virtual void resize(int width, int height) = 0;

    /// @brief Returns whether a window is active
    /// An active window has keyboard focus, and might have its window decos
    /// highlighted. Windows are usually become active after you click on their
    /// title bar, but can also be done programatically.
    virtual bool isActive() const = 0;

    /// @brief Returns the window state
    virtual Qt::WindowState windowState() const = 0;

    /// @brief Returns the parent of this window, if any
    /// Popups and utility windows usually have a parent window
    virtual Window::Ptr transientParent() const = 0;

    virtual QPoint mapFromGlobal(QPoint globalPos) const = 0;
    virtual QPoint mapToGlobal(QPoint localPos) const = 0;

    /// @brief Signal emitted when a window changes screen
    /// Like for example QWindow::screenChanged() for Qt.
    /// Needs to be emitted by the derived classes.
    KDBindings::Signal<> screenChanged;

    /// @brief Returns the screen this window is on
    virtual QScreen *screen() const = 0;

    /// Deletes the underlying window
    virtual void destroy() = 0;

    /// @brief Returns the Window's minimum size
    virtual QSize minSize() const = 0;
    virtual QSize maxSize() const = 0;
    virtual QPoint fromNativePixels(QPoint) const = 0;
    virtual void startSystemMove();

    int minWidth() const;
    int minHeight() const;
    int maxWidth() const;
    int maxHeight() const;

    bool containsView(Controller *) const;
    bool containsView(View *) const;

    /// @brief Returns whether this window is fullscreen currently
    virtual bool isFullScreen() const = 0;

    /// @brief Returns whether this window can't be shrinked to a size that would violate the layout's min size
    /// This is true for QtWidgets where the layout constraings propagate up to the window
    /// However, for QtQuick it difficult as there's no QLayout.
    //    - For QtQuick/FloatingWindow we try to not violate the min-size, which we have total control over
    //    - But for QtQuick/MainWindow it's more difficult, as we don't know how the user composed his
    //      main.qml. so this is false if the Window is not a FloatingWindow
    //
    // This method is only used to so we can surpress some warnings regarding layout being clipped due to
    // too small window.
    virtual bool supportsHonouringLayoutMinSize() const = 0;
};

inline bool operator==(Window::Ptr w1, Window::Ptr w2)
{
    if (!w1 && !w2)
        return true;

    if (w1 && w2)
        return w1->equals(w2);

    return false;
}

bool operator!=(Window::Ptr, Window::Ptr) = delete;

}

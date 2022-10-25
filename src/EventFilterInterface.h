/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include <memory>

QT_BEGIN_NAMESPACE
class QMouseEvent;
class QEvent;
QT_END_NAMESPACE

namespace KDDockWidgets {

class Window;
class View;

class EventFilterInterface
{
public:
    virtual ~EventFilterInterface();

    /// @brief Override to handle expose events for a certain window
    virtual bool onExposeEvent(std::shared_ptr<Window>)
    {
        return false;
    }

    /// @brief Override to handle when a view receives a mouse press event
    virtual bool onMouseButtonPress(View *, QMouseEvent *)
    {
        return false;
    }

    /// @brief Override to handle when a view receives a mouse press event
    virtual bool onMouseButtonRelease(View *, QMouseEvent *)
    {
        return false;
    }

    /// @brief Override to handle when a view receives a mouse press event
    virtual bool onMouseButtonMove(View *, QMouseEvent *)
    {
        return false;
    }

    /// @brief Override to handle when a view receives a mouse double click event
    virtual bool onMouseDoubleClick(View *, QMouseEvent *)
    {
        return false;
    }

    /// @brief Provided for convenience, aggregates all other overloads
    /// receives all mouse event types, if you return true here then the specialized counterparts
    /// won't be called Example, if true is returned here for a mouse press, then
    /// onMouseButtonPress() won't be called
    virtual bool onMouseEvent(View *, QMouseEvent *)
    {
        return false;
    }

    /// @brief Override to handle drag enter, drag leave, drag move and drop events
    virtual bool onDnDEvent(View *, QEvent *)
    {
        return false;
    }

    /// @brief Override to handle a move event
    virtual bool onMoveEvent(View *)
    {
        return false;
    }
};

}

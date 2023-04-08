/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

// The goal of this file is to provide fallback types when QtGui isn't present

class QMimeData;

// #ifdef QT_GUI_LIB
#ifndef FLUTTER_WITHOUT_QTGUITYPES // Remove once we don't link to QtGui in flutter
#include <QCloseEvent>
#include <QMouseEvent>
#include <QHoverEvent>
#include <QDropEvent>
#include <QIcon>
#else
#include <QPoint>
#endif

namespace KDDockWidgets {

// #ifdef QT_GUI_LIB
#ifndef FLUTTER_WITHOUT_QTGUITYPES

using Icon = QIcon;
using Event = QEvent;
using CloseEvent = QCloseEvent;
using MouseEvent = QMouseEvent;
using HoverEvent = QHoverEvent;
using DropEvent = QDropEvent;
using DragEnterEvent = QDragEnterEvent;
using DragMoveEvent = QDragMoveEvent;

#else

class Event
{
public:
    enum Type {
        MouseButtonPress,
        MouseButtonDblClick,
        MouseButtonRelease,
        MouseMove,
        NonClientAreaMouseButtonPress,
        NonClientAreaMouseButtonRelease,
        NonClientAreaMouseMove,
        NonClientAreaMouseButtonDblClick,
        HoverEnter,
        HoverLeave,
        HoverMove,
        DragEnter,
        DragLeave,
        DragMove,
        Drop,
        Move,
        FocusIn,
        WindowActivate,
        LayoutRequest
    };

    explicit Event(Type type)
        : m_type(type)
    {
    }

    bool
    isAccepted() const
    {
        return true;
    }

    void accept()
    {
        m_accepted = true;
    }

    void ignore()
    {
        m_accepted = false;
    }

    bool spontaneous() const
    {
        return m_spontaneous;
    }

    Type type() const
    {
        return m_type;
    }

    bool m_accepted = false;
    bool m_spontaneous = false;
    const Type m_type;
};

class CloseEvent : public Event
{
public:
};

class HoverEvent : public Event
{
public:
    using Event::Event;

    QPoint pos() const
    {
        return {};
    }
};

class MouseEvent : public Event
{
public:
    explicit MouseEvent(Type type, QPoint, QPoint, QPoint, Qt::MouseButtons, Qt::MouseButtons, Qt::KeyboardModifiers)
        : Event(type)
    {
    }

    QPoint pos() const
    {
        return {};
    }
    QPoint globalPos() const
    {
        return {};
    }

    Qt::MouseButton button() const
    {
        return {};
    }

    Qt::MouseButtons buttons() const
    {
        return {};
    }
};

class DropEvent : public Event
{
public:
    using Event::Event;

    QPoint pos() const
    {
        return {};
    }

    QMimeData *mimeData() const
    {
        return nullptr;
    }

    void setDropAction(Qt::DropAction)
    {
    }
};

class DragMoveEvent : public DropEvent
{
public:
    DragMoveEvent(Type type)
        : DropEvent(type)
    {
    }

    DragMoveEvent()
        : DropEvent(Event::DragMove)
    {
    }
};

class DragEnterEvent : public DragMoveEvent
{
public:
    DragEnterEvent()
        : DragMoveEvent(Event::DragEnter)
    {
    }
};

class Icon
{
public:
    bool isNull() const
    {
        return true;
    }
};

#endif

}

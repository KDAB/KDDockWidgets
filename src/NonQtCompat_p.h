/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

// The goal of this file is to provide fallback types when QtGui isn't present

#if defined(DOCKS_DEVELOPER_MODE) && defined(KDDW_FRONTEND_FLUTTER) && !defined(DARTAGNAN_BINDINGS_RUN)
#include "qcoro/core/qcorocore.h"
#endif

#ifdef QT_GUI_LIB
#include <QCloseEvent>
#include <QMouseEvent>
#include <QHoverEvent>
#include <QDropEvent>
#include <QIcon>
#include <QPixmap>
#include <QPolygon>
#include <QDrag>
#include <QTimer>
#include <QObject>
#else
#include <QPoint>
#include <QRect>
#include <QList>
#include <QObject>
#endif

QT_BEGIN_NAMESPACE
class QMimeData;
QT_END_NAMESPACE

namespace KDDockWidgets {

#ifdef QT_GUI_LIB

using Polygon = QPolygon;
using Icon = QIcon;
using Pixmap = QPixmap;
using Event = QEvent;
using Drag = QDrag;
using CloseEvent = QCloseEvent;
using FocusEvent = QFocusEvent;
using MouseEvent = QMouseEvent;
using HoverEvent = QHoverEvent;
using DropEvent = QDropEvent;
using DragEnterEvent = QDragEnterEvent;
using DragMoveEvent = QDragMoveEvent;

template<typename T>
inline T object_cast(QObject *o)
{
    return qobject_cast<T>(o);
}

template<typename T>
inline T object_cast(const QObject *o)
{
    return qobject_cast<T>(o);
}

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
        LayoutRequest,
        Close
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
    CloseEvent()
        : Event(Event::Close)
    {
    }
};

class HoverEvent : public Event
{
public:
    using Event::Event;

    QPoint pos() const
    {
        return {};
    }

    // Qt6 signature
    QPointF position() const
    {
        return {};
    }
};

class MouseEvent : public Event
{
public:
    explicit MouseEvent(Type type, QPoint localPos, QPoint /*windowPos*/,
                        QPoint globalPos, Qt::MouseButtons buttons, Qt::MouseButtons, Qt::KeyboardModifiers)
        : Event(type)
        , m_localPos(localPos)
        , m_globalPos(globalPos)
        , m_buttons(buttons)
    {
    }

    QPoint pos() const
    {
        return m_localPos;
    }

    QPoint globalPos() const
    {
        return m_globalPos;
    }

    // Qt6 signature:
    QPointF globalPosition() const
    {
        return m_globalPos;
    }

    Qt::MouseButton button() const
    {
        if (m_buttons & Qt::LeftButton)
            return Qt::LeftButton;

        // Nothing else matters
        return Qt::NoButton;
    }

    Qt::MouseButtons buttons() const
    {
        return m_buttons;
    }

    QPoint m_localPos;
    QPoint m_globalPos;
    Qt::MouseButtons m_buttons;
};

class DropEvent : public Event
{
public:
    using Event::Event;

    QPoint pos() const
    {
        return {};
    }

    // Qt6 signature
    QPointF position() const
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

class FocusEvent : public Event
{
public:
    Qt::FocusReason reason() const
    {
        return {};
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

// Only useful on wayland, to set a drag pixmap
class Pixmap
{
public:
};

// Used by segmented indicators controller
class Polygon : public QList<QPoint>
{
public:
    Polygon() = default;
    Polygon(QVector<QPoint>)
    {
    }

    QRect boundingRect() const
    {
        return {};
    }

    bool containsPoint(QPoint, Qt::FillRule) const
    {
        return false;
    }
};

// Only used by wayland, no rush in porting
class Drag
{
public:
    Drag(QObject *)
    {
    }
    void setPixmap(Pixmap)
    {
    }
    void setMimeData(QMimeData *)
    {
    }

    Qt::DropAction exec()
    {
        return {};
    }
};

#endif

}

#if defined(KDDW_FRONTEND_QT)
// Qt uses QObject, while Flutter uses Object.h
// Qt probably could also use Object.h, but for now reduce the churn for Qt users
namespace KDDockWidgets::Core {
using Object = QT_PREPEND_NAMESPACE(QObject);
}

#else

#include "core/Object_p.h"

#endif

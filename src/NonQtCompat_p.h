/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

// The goal of this file is to provide fallback types when QtGui isn't present

#include "flutter/qcoro.h"

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
#include <QString>
#else
#include "qtcompat/geometry_helpers_p.h"
#include "qtcompat/enums_p.h"
#include "qtcompat/string_p.h"
#include "kdtoolbox/KDStlContainerAdaptor.h"
#include <cstdint>
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

using Point = QT_PREPEND_NAMESPACE(QPoint);
using PointF = QT_PREPEND_NAMESPACE(QPointF);
using Size = QT_PREPEND_NAMESPACE(QSize);
using Rect = QT_PREPEND_NAMESPACE(QRect);
using Margins = QT_PREPEND_NAMESPACE(QMargins);

template<typename T>
using Vector = QVector<T>;

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

    Point pos() const
    {
        return {};
    }

    // Qt6 signature
    PointF position() const
    {
        return {};
    }
};

class MouseEvent : public Event
{
public:
    explicit MouseEvent(Type type, Point localPos, Point /*windowPos*/,
                        Point globalPos, Qt::MouseButtons buttons, Qt::MouseButtons, Qt::KeyboardModifiers)
        : Event(type)
        , m_localPos(localPos)
        , m_globalPos(globalPos)
        , m_buttons(buttons)
    {
    }

    Point pos() const
    {
        return m_localPos;
    }

    Point globalPos() const
    {
        return m_globalPos;
    }

    // Qt6 signature:
    PointF globalPosition() const
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

    Point m_localPos;
    Point m_globalPos;
    Qt::MouseButtons m_buttons;
};

class DropEvent : public Event
{
public:
    using Event::Event;

    Point pos() const
    {
        return {};
    }

    // Qt6 signature
    PointF position() const
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
class Polygon : public Vector<Point>
{
public:
    Polygon() = default;
    Polygon(Vector<Point>)
    {
    }

    Rect boundingRect() const
    {
        return Rect();
    }

    bool containsPoint(Point, Qt::FillRule) const
    {
        return false;
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

#define QT_DOCKS_EXPORT DOCKS_EXPORT

#else

#include "qtcompat/Object_p.h"

#ifndef Q_NAMESPACE
#define Q_NAMESPACE
#endif

#ifdef Q_ENUM_NS // TODOm4: Remove the ifdef
#undef Q_ENUM_NS
#endif
#define Q_ENUM_NS(name)

#ifdef Q_DECLARE_METATYPE // TODOm4: Remove the ifdef
#undef Q_DECLARE_METATYPE
#endif
#define Q_DECLARE_METATYPE(name)

#ifndef Q_INVOKABLE
#define Q_INVOKABLE
#endif

#ifndef Q_SLOTS
#define Q_SLOTS
#endif

#define qAsConst(name) name
#define QT_DOCKS_EXPORT
#define Q_DECLARE_OPERATORS_FOR_FLAGS(name)

using quintptr = unsigned long long int;
using qint64 = int64_t;

namespace Qt5Qt6Compat {
inline KDDockWidgets::Point eventGlobalPos(KDDockWidgets::MouseEvent *ev)
{
    return ev->globalPos();
}

}

#endif

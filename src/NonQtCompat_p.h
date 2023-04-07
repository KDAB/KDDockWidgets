/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

// The goal of this file is to provide fallback types when QtGui isn't present

#ifdef QT_GUI_LIB
#include <QCloseEvent>
#include <QMouseEvent>
#include <QHoverEvent>
#include <QDropEvent>
#else
#include <QPoint>
#endif

namespace KDDockWidgets {

#ifdef QT_GUI_LIB

using Event = QEvent;
using CloseEvent = QCloseEvent;
using MouseEvent = QMouseEvent;
using HoverEvent = QHoverEvent;
using DropEvent = QDropEvent;

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
    };

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
        return {};
    }

    bool m_accepted = false;
    bool m_spontaneous = false;
};

class CloseEvent : public Event
{
public:
};

class HoverEvent : public Event
{
public:
    QPoint pos() const
    {
        return {};
    }
};

class MouseEvent : public Event
{
public:
    QPoint pos() const
    {
        return {};
    }
    QPoint globalPos() const
    {
        return {};
    }

    int button() const
    {
        return 0;
    }

    int buttons() const
    {
        return 0;
    }
};

class DropEvent : public Event
{
public:
    QPoint pos() const
    {
        return {};
    }
};


#endif

}

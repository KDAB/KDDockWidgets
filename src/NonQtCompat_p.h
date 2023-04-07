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
#endif

namespace KDDockWidgets {

#ifdef QT_GUI_LIB

using Event = QEvent;
using CloseEvent = QCloseEvent;
using MouseEvent = QMouseEvent;
using HoverEvent = QHoverEvent;

#else

class Event
{
public:
    bool isAccepted() const
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

    bool m_accepted = false;
    bool m_spontaneous = false;
};

class CloseEvent : public Event
{
public:
};

#endif

}

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "TitleBarQuick_p.h"
#include "DragController_p.h"
#include "Frame_p.h"
#include "FloatingWindow_p.h"
#include "Logging_p.h"
#include "WindowBeingDragged_p.h"
#include "Utils_p.h"


using namespace KDDockWidgets;


TitleBarQuick::TitleBarQuick(Frame *parent)
    : TitleBar(parent)
{
}

TitleBarQuick::TitleBarQuick(FloatingWindow *parent)
    : TitleBar(parent)
{
}

TitleBarQuick::~TitleBarQuick()
{
}

void TitleBarQuick::filterEvents(QObject *obj)
{
    if (!m_eventFilterInstalled) {
        m_eventFilterInstalled = true;
        obj->installEventFilter(this);
    }
}

bool TitleBarQuick::eventFilter(QObject *, QEvent *ev)
{
    switch (ev->type()) {
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseMove:
    case QEvent::NonClientAreaMouseButtonPress:
    case QEvent::NonClientAreaMouseButtonRelease:
    case QEvent::NonClientAreaMouseMove:
        qApp->sendEvent(this, ev);
        return false;
    default:
        break;
    }

    return false;
}

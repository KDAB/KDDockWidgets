/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KDDOCKWIDGETS_QT5QT6_COMPAT_P_H
#define KDDOCKWIDGETS_QT5QT6_COMPAT_P_H

#include "QtCompat_p.h"

namespace KDDockWidgets {
namespace Qt5Qt6Compat {

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)

#define QQUICKITEMgeometryChanged geometryChange

using qintptr = ::qintptr;
using qhashtype = size_t;

inline QPoint eventPos(QDropEvent *ev)
{
    return ev->position().toPoint();
}

inline QPoint eventGlobalPos(QMouseEvent *ev)
{
    return ev->globalPosition().toPoint();
}

inline QPoint eventPos(QHoverEvent *ev)
{
    return ev->position().toPoint();
}

#else // Qt 5:

#define QQUICKITEMgeometryChanged geometryChanged

using qintptr = long;
using qhashtype = uint;

inline QPoint eventPos(QDropEvent *ev)
{
    return ev->pos();
}

inline QPoint eventPos(QHoverEvent *ev)
{
    return ev->pos();
}

inline QPoint eventGlobalPos(QMouseEvent *ev)
{
    return ev->globalPos();
}

#endif

}
}

#endif

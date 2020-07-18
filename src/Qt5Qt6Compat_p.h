/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KDDOCKWIDGETS_QT5QT6_COMPAT_P_H
#define KDDOCKWIDGETS_QT5QT6_COMPAT_P_H

#include <QMouseEvent>

namespace KDDockWidgets {
namespace Qt5Qt6Compat {

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)

using QEnterEvent = QEnterEvent;

inline QPoint eventGlobalPos(QMouseEvent *ev)
{
    return ev->globalPosition().toPoint();
}

#else

using QEnterEvent = QEvent;

// Qt 5:
inline QPoint eventGlobalPos(QMouseEvent *ev)
{
    return ev->globalPos();
}

#endif

}
}

#endif

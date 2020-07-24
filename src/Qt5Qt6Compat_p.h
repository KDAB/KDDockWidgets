/*
  This file is part of KDDockWidgets.

  Copyright (C) 2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef KDDOCKWIDGETS_QT5QT6_COMPAT_P_H
#define KDDOCKWIDGETS_QT5QT6_COMPAT_P_H

#include <QMouseEvent>

namespace KDDockWidgets {
namespace Qt5Qt6Compat {

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)

inline QPoint eventGlobalPos(QMouseEvent *ev)
{
    return ev->globalPosition().toPoint();
}

#else

// Qt 5:
inline QPoint eventGlobalPos(QMouseEvent *ev)
{
    return ev->globalPos();
}

#endif

}
}

#endif

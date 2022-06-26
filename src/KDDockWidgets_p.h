/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_KDDOCKWIDGETS_P_H
#define KD_KDDOCKWIDGETS_P_H
#pragma once

#include "KDDockWidgets.h"
#include <QString>

namespace KDDockWidgets {

inline QString locationStr(Location loc)
{
    switch (loc) {
    case KDDockWidgets::Location_None:
        return QStringLiteral("none");
    case KDDockWidgets::Location_OnLeft:
        return QStringLiteral("left");
    case KDDockWidgets::Location_OnTop:
        return QStringLiteral("top");
    case KDDockWidgets::Location_OnRight:
        return QStringLiteral("right");
    case KDDockWidgets::Location_OnBottom:
        return QStringLiteral("bottom");
    }

    return QString();
}

enum class WindowState
{
    None = 0,
    Minimized = 1,
    Maximized = 2,
    FullScreen = 4
};
Q_DECLARE_FLAGS(WindowStates, WindowState)

}

#endif

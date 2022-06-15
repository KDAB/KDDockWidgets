/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/docks_export.h"

class QPoint;
class QRect;
class QString;

namespace KDDockWidgets {

namespace Controllers {
class DockWidget;
}

namespace Views {

/// @brief The interface that TabBar views should implement
class DOCKS_EXPORT TabBar
{
public:
    virtual ~TabBar();
    virtual bool tabsAreMovable() const = 0;
    virtual int tabAt(QPoint localPt) const = 0;
    virtual void moveTabTo(int from, int to) = 0;
    virtual QRect rectForTab(int index) const = 0;
    virtual Controllers::DockWidget *currentDockWidget() const = 0;
    virtual QString text(int index) const = 0;
};

}

}

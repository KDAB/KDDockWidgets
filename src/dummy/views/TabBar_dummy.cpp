/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * @file
 * @brief Implements a QTabWidget derived class with support for docking and undocking
 * KDockWidget::DockWidget as tabs .
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#include "TabBar_dummy.h"
#include "kddockwidgets/controllers/TabBar.h"
#include "kddockwidgets/controllers/Stack.h"

#include <QMetaObject>
#include <QMouseEvent>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

TabBar_dummy::TabBar_dummy(Controllers::TabBar *controller, View *parent)
    : View_dummy(controller, Type::TabBar, parent)
    , TabBarViewInterface(controller)
{
}

void TabBar_dummy::init()
{
}

int TabBar_dummy::tabAt(QPoint) const
{
    return -1;
}


QString TabBar_dummy::text(int) const
{
    return {};
}

QRect TabBar_dummy::rectForTab(int) const
{
    return {};
}

void TabBar_dummy::moveTabTo(int from, int to)
{
    Q_UNUSED(from);
    Q_UNUSED(to);
    // Not implemented yet
}

Controllers::DockWidget *TabBar_dummy::currentDockWidget() const
{
    return nullptr;
}

bool TabBar_dummy::tabsAreMovable() const
{
    return false;
}

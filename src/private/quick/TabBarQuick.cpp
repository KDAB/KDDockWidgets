/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
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

#include "TabBarQuick_p.h"


using namespace KDDockWidgets;

TabBarQuick::TabBarQuick(TabWidget *parent)
    : QWidgetAdapter(parent->asWidget())
    , TabBar(this, parent)
{
}

int TabBarQuick::numDockWidgets() const
{
    return -1;
}

int TabBarQuick::tabAt(QPoint) const
{
   return -1;
}

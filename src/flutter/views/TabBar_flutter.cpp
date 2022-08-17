/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

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

#include "TabBar_flutter.h"
#include "kddockwidgets/controllers/TabBar.h"
#include "kddockwidgets/controllers/Stack.h"

#include <QMetaObject>
#include <QMouseEvent>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

TabBar_flutter::TabBar_flutter(Controllers::TabBar *controller, View *parent)
    : View_flutter(controller, Type::TabBar, parent)
    , TabBarViewInterface(controller)
{
}

void TabBar_flutter::init()
{
}

int TabBar_flutter::tabAt(QPoint) const
{
    return -1;
}


QString TabBar_flutter::text(int) const
{
    return {};
}

QRect TabBar_flutter::rectForTab(int) const
{
    return {};
}

void TabBar_flutter::moveTabTo(int from, int to)
{
    Q_UNUSED(from);
    Q_UNUSED(to);
    // Not implemented yet
}

void TabBar_flutter::changeTabIcon(int index, const QIcon &)
{
    qWarning() << Q_FUNC_INFO << "Not implemented" << index;
}

void TabBar_flutter::removeDockWidget(Controllers::DockWidget *dw)
{
    qWarning() << Q_FUNC_INFO << "Not implemented" << dw;
}

void TabBar_flutter::insertDockWidget(int, Controllers::DockWidget *, const QIcon &,
                                      const QString &)
{
    qWarning() << Q_FUNC_INFO << "Not implemented";
}

void TabBar_flutter::renameTab(int index, const QString &)
{
    qWarning() << Q_FUNC_INFO << "Not implemented" << index;
}

void TabBar_flutter::setCurrentIndex(int)
{
    qWarning() << Q_FUNC_INFO << "Not implemented";
}

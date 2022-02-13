/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "View_qtwidgets.h"

#include <QTabBar>
#include <QTabWidget>

using namespace KDDockWidgets::Views;

template<>
View_qtwidgets<QWidget>::View_qtwidgets(KDDockWidgets::Controller *controller, View::Type type, QWidget *parent, Qt::WindowFlags windowFlags)
    : QWidget(parent, windowFlags)
    , View(controller, type, this)
{
}

template<>
View_qtwidgets<QTabBar>::View_qtwidgets(KDDockWidgets::Controller *controller, Type type, QWidget *parent, Qt::WindowFlags)
    : QTabBar(parent)
    , View(controller, type, this)
{
}

template<>
View_qtwidgets<QTabWidget>::View_qtwidgets(KDDockWidgets::Controller *controller, Type type, QWidget *parent, Qt::WindowFlags)
    : QTabWidget(parent)
    , View(controller, type, this)
{
}

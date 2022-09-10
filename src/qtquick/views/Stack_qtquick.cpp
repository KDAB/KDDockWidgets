/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Stack_qtquick.h"
#include "Config.h"
#include "kddockwidgets/ViewFactory.h"

#include "kddockwidgets/controllers/Stack.h"
#include "kddockwidgets/controllers/Group.h"
#include "kddockwidgets/controllers/TabBar.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

Stack_qtquick::Stack_qtquick(Controllers::Stack *controller, QQuickItem *parent)
    : View_qtquick(controller, Type::Stack, parent)
    , StackViewInterface(controller)
{
}

void Stack_qtquick::init()
{

    m_tabBarAutoHideChanged =
        m_stack->tabBarAutoHideChanged.connect([this] { Q_EMIT tabBarAutoHideChanged(); });

    Q_EMIT tabBarChanged();
}

Controllers::Stack *Stack_qtquick::stack() const
{
    return m_stack;
}

QObject *Stack_qtquick::tabBarViewObj() const
{
    return View_qt::asQObject(m_stack->tabBar()->view());
}

bool Stack_qtquick::tabBarAutoHide() const
{
    return m_stack->tabBarAutoHide();
}

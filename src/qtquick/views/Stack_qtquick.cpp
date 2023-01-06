/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

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

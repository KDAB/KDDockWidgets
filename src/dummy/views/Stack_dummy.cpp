/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Stack_dummy.h"
#include "Controller.h"
#include "kddockwidgets/controllers/Stack.h"
#include "kddockwidgets/controllers/TitleBar.h"
#include "dummy/ViewFactory_dummy.h"
#include "DockRegistry.h"
#include "Config.h"
#include "Window.h"
#include "private/View_p.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

Stack_dummy::Stack_dummy(Controllers::Stack *controller, QWidget *parent)
    : View_dummy(controller, Type::Stack, parent)
    , StackViewInterface(controller)
{
}

void Stack_dummy::init()
{
}

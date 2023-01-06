/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Stack_flutter.h"
#include "Controller.h"
#include "kddockwidgets/controllers/Stack.h"
#include "kddockwidgets/controllers/TitleBar.h"
#include "flutter/ViewFactory_flutter.h"
#include "DockRegistry.h"
#include "Config.h"
#include "Window.h"
#include "private/View_p.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

Stack_flutter::Stack_flutter(Controllers::Stack *controller, View *parent)
    : View_flutter(controller, Type::Stack, parent)
    , StackViewInterface(controller)
{
}

void Stack_flutter::init()
{
}

void Stack_flutter::setDocumentMode(bool)
{
}

bool Stack_flutter::isPositionDraggable(QPoint) const
{
    return true;
}

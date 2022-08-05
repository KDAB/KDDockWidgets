/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "TitleBar_dummy.h"

#include "private/DragController_p.h"

#include "kddockwidgets/controllers/Group.h"
#include "kddockwidgets/controllers/FloatingWindow.h"
#include "kddockwidgets/controllers/TitleBar.h"


using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;


TitleBar_dummy::TitleBar_dummy(Controllers::TitleBar *controller, View *parent)
    : View_dummy(controller, Type::TitleBar, parent)
    , Views::TitleBarViewInterface(controller)
{
    setFixedHeight(30);
}

TitleBar_dummy::~TitleBar_dummy()
{
}

void TitleBar_dummy::init()
{
}

#ifdef DOCKS_DEVELOPER_MODE

bool TitleBar_dummy::isCloseButtonEnabled() const
{
    return true;
}

bool TitleBar_dummy::isCloseButtonVisible() const
{
    return true;
}

bool TitleBar_dummy::isFloatButtonVisible() const
{
    return true;
}

#endif

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "TitleBar.h"

#include "core/DragController_p.h"

#include "kddockwidgets/core/Group.h"
#include "kddockwidgets/core/FloatingWindow.h"
#include "kddockwidgets/core/TitleBar.h"


using namespace KDDockWidgets;
using namespace KDDockWidgets::flutter;


TitleBar_flutter::TitleBar_flutter(Core::TitleBar *controller, View *parent)
    : View_flutter(controller, Core::ViewType::TitleBar, parent)
    , Core::TitleBarViewInterface(controller)
{
    setFixedHeight(30);
}

TitleBar_flutter::~TitleBar_flutter()
{
}

void TitleBar_flutter::init()
{
}

#ifdef DOCKS_DEVELOPER_MODE

bool TitleBar_flutter::isCloseButtonEnabled() const
{
    return true;
}

bool TitleBar_flutter::isCloseButtonVisible() const
{
    return true;
}

bool TitleBar_flutter::isFloatButtonVisible() const
{
    return true;
}

#endif

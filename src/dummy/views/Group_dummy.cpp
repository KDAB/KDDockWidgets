/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * @file
 * @brief The GUI counterpart of Frame.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#include "Group_dummy.h"

#include "kddockwidgets/controllers/Group.h"
#include "kddockwidgets/controllers/Stack.h"
#include "kddockwidgets/controllers/TitleBar.h"
#include "kddockwidgets/controllers/DockWidget.h"
#include "kddockwidgets/controllers/DockWidget_p.h"

#include "dummy/ViewFactory_dummy.h"
#include "dummy/Platform_dummy.h"
#include "dummy/views/DockWidget_dummy.h"

#include "Stack_dummy.h"

#include "Config.h"
#include "kddockwidgets/ViewFactory.h"
#include "private/WidgetResizeHandler_p.h"

#include <QDebug>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

Group_dummy::Group_dummy(Controllers::Group *controller, View *parent)
    : View_dummy(controller, Type::Frame, parent)
    , GroupViewInterface(controller)
{
}

Group_dummy::~Group_dummy()
{
}

void Group_dummy::init()
{
}

QSize Group_dummy::minSize() const
{
    const QSize contentsSize = m_group->dockWidgetsMinSize();
    return contentsSize + QSize(0, nonContentsHeight());
}

QSize Group_dummy::maxSizeHint() const
{
    return View_dummy::maxSizeHint();
}

int Group_dummy::nonContentsHeight() const
{
    return 0;
}

QRect Group_dummy::dragRect() const
{
    qFatal("Not implemented");
    return {};
}

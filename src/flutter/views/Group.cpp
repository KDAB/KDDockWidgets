/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
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

#include "Group.h"

#include "kddockwidgets/core/Group.h"
#include "kddockwidgets/core/Stack.h"
#include "kddockwidgets/core/TitleBar.h"
#include "kddockwidgets/core/DockWidget.h"
#include "kddockwidgets/core/DockWidget_p.h"

#include "flutter/ViewFactory.h"
#include "flutter/Platform.h"
#include "flutter/views/DockWidget.h"

#include "Stack.h"

#include "Config.h"
#include "core/ViewFactory.h"
#include "core/WidgetResizeHandler_p.h"

#include <QDebug>

using namespace KDDockWidgets;
using namespace KDDockWidgets::flutter;

Group::Group(Core::Group *controller, Core::View *parent)
    : View(controller, Core::ViewType::Frame, parent)
    , GroupViewInterface(controller)
{
}

Group::~Group()
{
}

void Group::init()
{
}

int Group::currentIndex() const
{
    return 0;
}

QSize Group::minSize() const
{
    const QSize contentsSize = m_group->dockWidgetsMinSize();
    return contentsSize + QSize(0, nonContentsHeight());
}

QSize Group::maxSizeHint() const
{
    return View::maxSizeHint();
}

int Group::nonContentsHeight() const
{
    return 0;
}

QRect Group::dragRect() const
{
    // Not implemented for flutter
    return {};
}

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

#include "Group_flutter.h"

#include "kddockwidgets/core/Group.h"
#include "kddockwidgets/core/Stack.h"
#include "kddockwidgets/core/TitleBar.h"
#include "kddockwidgets/core/DockWidget.h"
#include "kddockwidgets/core/DockWidget_p.h"

#include "flutter/ViewFactory_flutter.h"
#include "flutter/Platform_flutter.h"
#include "flutter/views/DockWidget_flutter.h"

#include "Stack_flutter.h"

#include "Config.h"
#include "core/ViewFactory.h"
#include "core/WidgetResizeHandler_p.h"

#include <QDebug>

using namespace KDDockWidgets;
using namespace KDDockWidgets::flutter;

Group_flutter::Group_flutter(Core::Group *controller, View *parent)
    : View_flutter(controller, Core::ViewType::Frame, parent)
    , GroupViewInterface(controller)
{
}

Group_flutter::~Group_flutter()
{
}

void Group_flutter::init()
{
}

int Group_flutter::currentIndex() const
{
    return 0;
}

QSize Group_flutter::minSize() const
{
    const QSize contentsSize = m_group->dockWidgetsMinSize();
    return contentsSize + QSize(0, nonContentsHeight());
}

QSize Group_flutter::maxSizeHint() const
{
    return View_flutter::maxSizeHint();
}

int Group_flutter::nonContentsHeight() const
{
    return 0;
}

QRect Group_flutter::dragRect() const
{
    qFatal("Not implemented");
    return {};
}

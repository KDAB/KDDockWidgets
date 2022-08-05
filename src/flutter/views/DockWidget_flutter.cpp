/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "DockWidget_flutter.h"
#include "kddockwidgets/ViewFactory.h"

#include "kddockwidgets/controllers/TitleBar.h"
#include "kddockwidgets/controllers/DockWidget.h"
#include "kddockwidgets/controllers/DockWidget_p.h"
#include "kddockwidgets/controllers/Group.h"
#include "flutter/Platform_flutter.h"
#include "flutter/views/TitleBar_flutter.h"
#include "flutter/views/Group_flutter.h"
#include "flutter/ViewFactory_flutter.h"

#include <Config.h>

/**
 * @file
 * @brief Represents a dock widget.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

using namespace KDDockWidgets;
using namespace KDDockWidgets::Controllers;
using namespace KDDockWidgets::Views;


DockWidget_flutter::DockWidget_flutter(const QString &uniqueName, DockWidgetOptions options,
                                       LayoutSaverOptions layoutSaverOptions,
                                       Qt::WindowFlags windowFlags)
    : View_flutter(new DockWidget(this, uniqueName, options, layoutSaverOptions), Type::DockWidget,
                   nullptr, windowFlags)
    , Views::DockWidgetViewInterface(asDockWidgetController())
{
    init();
    m_dockWidget->init();
}

DockWidget_flutter::~DockWidget_flutter()
{
}

void DockWidget_flutter::init()
{
}


QSize DockWidget_flutter::minSize() const
{
    if (auto guestWidget = dockWidget()->guestView()) {
        // The guests min-size is the same as the widget's, there's no spacing or margins.
        return guestWidget->minSize();
    }

    return View_flutter::minSize();
}

QSize DockWidget_flutter::maximumSize() const
{
    if (auto guestWidget = dockWidget()->guestView()) {
        // The guests max-size is the same as the widget's, there's no spacing or margins.
        return guestWidget->maximumSize();
    }

    return View_flutter::maximumSize();
}

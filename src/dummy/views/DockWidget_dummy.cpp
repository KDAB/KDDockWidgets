/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "DockWidget_dummy.h"
#include "kddockwidgets/ViewFactory.h"

#include "kddockwidgets/controllers/TitleBar.h"
#include "kddockwidgets/controllers/DockWidget.h"
#include "kddockwidgets/controllers/DockWidget_p.h"
#include "kddockwidgets/controllers/Group.h"
#include "dummy/Platform_dummy.h"
#include "dummy/views/TitleBar_dummy.h"
#include "dummy/views/Group_dummy.h"
#include "dummy/ViewFactory_dummy.h"

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


DockWidget_dummy::DockWidget_dummy(const QString &uniqueName, DockWidgetOptions options,
                                   LayoutSaverOptions layoutSaverOptions,
                                   Qt::WindowFlags windowFlags)
    : View_dummy(new DockWidget(this, uniqueName, options, layoutSaverOptions), Type::DockWidget,
                 nullptr, windowFlags)
    , Views::DockWidgetViewInterface(asDockWidgetController())
{
    init();
    m_dockWidget->init();
}

DockWidget_dummy::~DockWidget_dummy()
{
}

void DockWidget_dummy::init()
{
}


QSize DockWidget_dummy::minSize() const
{
    if (auto guestWidget = dockWidget()->guestView()) {
        // The guests min-size is the same as the widget's, there's no spacing or margins.
        return guestWidget->minSize();
    }

    return View_dummy::minSize();
}

QSize DockWidget_dummy::maxSizeHint() const
{
    if (auto guestWidget = dockWidget()->guestView()) {
        // The guests max-size is the same as the widget's, there's no spacing or margins.
        return guestWidget->maxSizeHint();
    }

    return View_dummy::maxSizeHint();
}

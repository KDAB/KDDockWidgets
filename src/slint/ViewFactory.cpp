/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "ViewFactory.h"
#include "Config.h"
#include "Action_p.h"

#include "core/Utils_p.h"

#include "kddockwidgets/core/TabBar.h"
#include "kddockwidgets/core/Stack.h"
#include "kddockwidgets/core/FloatingWindow.h"
#include "kddockwidgets/core/indicators/ClassicDropIndicatorOverlay.h"
#include "kddockwidgets/core/indicators/NullDropIndicatorOverlay.h"
#include "kddockwidgets/core/indicators/SegmentedDropIndicatorOverlay.h"
#include "kddockwidgets/core/MainWindow.h"
#include "kddockwidgets/core/views/ClassicIndicatorWindowViewInterface.h"

// #include "slint/views/ClassicIndicatorsWindow.h"
// #include "slint/views/SegmentedDropIndicatorOverlay.h"
// #include "slint/views/FloatingWindow.h"
// #include "slint/views/DockWidget.h"
// #include "slint/views/DropArea.h"
// #include "slint/views/Group.h"
// #include "slint/views/View.h"
// #include "slint/views/Separator.h"
// #include "slint/views/TitleBar.h"
// #include "slint/views/TabBar.h"
// #include "slint/views/SideBar.h"
// #include "slint/views/Stack.h"
// #include "slint/views/MainWindow.h"
// #include "slint/views/MDILayout.h"
// #include "slint/views/RubberBand.h"

#include <QToolButton>


// clazy:excludeall=ctor-missing-parent-argument

using namespace KDDockWidgets;
using namespace KDDockWidgets::slint;


ViewFactory::~ViewFactory()
{
}

Core::View *ViewFactory::createDockWidget(const QString &uniqueName, DockWidgetOptions options,
                                          LayoutSaverOptions layoutSaverOptions,
                                          Qt::WindowFlags windowFlags) const
{
    Q_UNUSED(layoutSaverOptions)
    Q_UNUSED(windowFlags)
    Q_UNUSED(uniqueName)
    Q_UNUSED(options)
    return {};
}

Core::View *ViewFactory::createGroup(Core::Group *controller,
                                     Core::View *parent) const
{
    Q_UNUSED(controller)
    Q_UNUSED(parent)
    return {};
}

Core::View *ViewFactory::createTitleBar(Core::TitleBar *titleBar, Core::View *parent) const
{
    Q_UNUSED(titleBar)
    Q_UNUSED(parent)
    return {};
}

Core::View *ViewFactory::createTabBar(Core::TabBar *tabBar, Core::View *parent) const
{
    Q_UNUSED(tabBar)
    Q_UNUSED(parent)
    return {};
}

Core::View *ViewFactory::createStack(Core::Stack *controller, Core::View *parent) const
{
    Q_UNUSED(controller)
    Q_UNUSED(parent)
    return {};
}

Core::View *ViewFactory::createSeparator(Core::Separator *controller, Core::View *parent) const
{
    Q_UNUSED(controller)
    Q_UNUSED(parent)
    return {};
}

Core::View *ViewFactory::createFloatingWindow(Core::FloatingWindow *controller,
                                              Core::MainWindow *parent,
                                              Qt::WindowFlags windowFlags) const
{
    Q_UNUSED(controller)
    Q_UNUSED(parent)
    Q_UNUSED(windowFlags)
    return {};
}

Core::View *ViewFactory::createRubberBand(Core::View *parent) const
{
    Q_UNUSED(parent)
    return {};
}

Core::View *ViewFactory::createSideBar(Core::SideBar *controller, Core::View *parent) const
{
    Q_UNUSED(controller)
    Q_UNUSED(parent)
    return {};
}


// iconForButtonType impl is the same for QtQuick and QtWidgets
QIcon ViewFactory::iconForButtonType(TitleBarButtonType type, qreal dpr) const
{
    Q_UNUSED(type)
    Q_UNUSED(dpr)
    return {};
}

Core::View *ViewFactory::createDropArea(Core::DropArea *controller, Core::View *parent) const
{
    Q_UNUSED(controller)
    Q_UNUSED(parent)
    return {};
}

Core::View *ViewFactory::createMDILayout(Core::MDILayout *controller, Core::View *parent) const
{
    Q_UNUSED(controller)
    Q_UNUSED(parent)
    return {};
}

Core::View *ViewFactory::createSegmentedDropIndicatorOverlayView(
    Core::SegmentedDropIndicatorOverlay *controller, Core::View *parent) const
{
    Q_UNUSED(controller)
    Q_UNUSED(parent)
    return {};
}

Core::ClassicIndicatorWindowViewInterface *ViewFactory::createClassicIndicatorWindow(
    Core::ClassicDropIndicatorOverlay *classicIndicators, Core::View *parent) const
{
    Q_UNUSED(classicIndicators)
    Q_UNUSED(parent)
    return {};
}


KDDockWidgets::Core::Action *ViewFactory::createAction(Core::DockWidget *dw, const char *debugName) const
{
    Q_UNUSED(dw)
    Q_UNUSED(debugName)
    return nullptr;
}

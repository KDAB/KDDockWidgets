/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "ViewFactory_dummy.h"
#include "Config.h"

#include "private/Utils_p.h"

#include "kddockwidgets/controllers/TabBar.h"
#include "kddockwidgets/controllers/Stack.h"
#include "kddockwidgets/controllers/FloatingWindow.h"
#include "kddockwidgets/controllers/indicators/ClassicIndicators.h"
#include "kddockwidgets/controllers/indicators/NullIndicators.h"
#include "kddockwidgets/controllers/indicators/SegmentedIndicators.h"
#include "kddockwidgets/controllers/MainWindow.h"

// #include "qtwidgets/views/ClassicIndicatorsWindow_qtwidgets.h"
// #include "qtwidgets/views/SegmentedIndicatorsOverlay_qtwidgets.h"
// #include "qtwidgets/views/FloatingWindow_qtwidgets.h"
// #include "qtwidgets/views/DockWidget_qtwidgets.h"
// #include "qtwidgets/views/DropArea_qtwidgets.h"
// #include "qtwidgets/views/Group_qtwidgets.h"
// #include "qtwidgets/views/View_qtwidgets.h"
// #include "qtwidgets/views/Separator_qtwidgets.h"
// #include "qtwidgets/views/TitleBar_qtwidgets.h"
// #include "qtwidgets/views/TabBar_qtwidgets.h"
// #include "qtwidgets/views/SideBar_qtwidgets.h"
// #include "qtwidgets/views/Stack_qtwidgets.h"
// #include "qtwidgets/views/MainWindow_qtwidgets.h"
// #include "qtwidgets/views/MDILayout_qtwidgets.h"
// #include "qtwidgets/views/RubberBand_qtwidgets.h"

#include "views/ClassicIndicatorWindowViewInterface.h"


// clazy:excludeall=ctor-missing-parent-argument

using namespace KDDockWidgets;


ViewFactory_dummy::~ViewFactory_dummy()
{
}

View *ViewFactory_dummy::createDockWidget(const QString &, DockWidgetOptions, LayoutSaverOptions,
                                          Qt::WindowFlags) const
{
    return {};
}


View *ViewFactory_dummy::createGroup(Controllers::Group *, View * = nullptr) const
{
    return {};
}

View *ViewFactory_dummy::createTitleBar(Controllers::TitleBar *, View *) const
{
    return {};
}

View *ViewFactory_dummy::createTabBar(Controllers::TabBar *, View *) const
{
    return {};
}

View *ViewFactory_dummy::createStack(Controllers::Stack *, View *) const
{
    return {};
}

View *ViewFactory_dummy::createSeparator(Controllers::Separator *, View *) const
{
    return {};
}

View *ViewFactory_dummy::createFloatingWindow(Controllers::FloatingWindow *,
                                              Controllers::MainWindow *, Qt::WindowFlags) const
{
    return {};
}

View *ViewFactory_dummy::createRubberBand(View *) const
{
    return nullptr;
}

View *ViewFactory_dummy::createSideBar(Controllers::SideBar *, View *) const
{
    return {};
}

QAbstractButton *ViewFactory_dummy::createTitleBarButton(QWidget *, TitleBarButtonType) const
{
    return nullptr;
}

// iconForButtonType impl is the same for QtQuick and QtWidgets
QIcon ViewFactory_dummy::iconForButtonType(TitleBarButtonType, qreal) const
{
    return {};
}

View *ViewFactory_dummy::createDropArea(Controllers::DropArea *, View *) const
{
    return {};
}

View *ViewFactory_dummy::createMDILayout(Controllers::MDILayout *, View *) const
{
    return {};
}

View *ViewFactory_dummy::createSegmentedDropIndicatorOverlayView(Controllers::SegmentedIndicators *,
                                                                 View *) const
{
    return {};
}

Views::ClassicIndicatorWindowViewInterface *
ViewFactory_dummy::createClassicIndicatorWindow(Controllers::ClassicIndicators *) const
{
    return {};
}

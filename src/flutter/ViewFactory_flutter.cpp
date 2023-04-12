/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "ViewFactory_flutter.h"
#include "Config.h"

#include "private/Utils_p.h"

#include "kddockwidgets/core/TabBar.h"
#include "kddockwidgets/core/Stack.h"
#include "kddockwidgets/core/FloatingWindow.h"
#include "kddockwidgets/core/indicators/ClassicIndicators.h"
#include "kddockwidgets/core/indicators/NullIndicators.h"
#include "kddockwidgets/core/indicators/SegmentedIndicators.h"
#include "kddockwidgets/core/MainWindow.h"

// #include "qtwidgets/views/ClassicIndicatorsWindow.h"
// #include "qtwidgets/views/SegmentedIndicatorsOverlay.h"
// #include "qtwidgets/views/FloatingWindow.h"
// #include "qtwidgets/views/DockWidget.h"
// #include "qtwidgets/views/DropArea.h"
// #include "qtwidgets/views/Group.h"
// #include "qtwidgets/views/View.h"
// #include "qtwidgets/views/Separator.h"
// #include "qtwidgets/views/TitleBar.h"
// #include "qtwidgets/views/TabBar.h"
// #include "qtwidgets/views/SideBar.h"
// #include "qtwidgets/views/Stack.h"
// #include "qtwidgets/views/MainWindow.h"
// #include "qtwidgets/views/MDILayout.h"
// #include "qtwidgets/views/RubberBand.h"

#include "views/ClassicIndicatorWindowViewInterface.h"


// clazy:excludeall=ctor-missing-parent-argument

using namespace KDDockWidgets;


ViewFactory_flutter::~ViewFactory_flutter()
{
}

View *ViewFactory_flutter::createDockWidget(const QString &, DockWidgetOptions, LayoutSaverOptions,
                                            Qt::WindowFlags) const
{
    return {};
}


View *ViewFactory_flutter::createGroup(Core::Group *, View *) const
{
    Q_ASSERT(false);
    return {};
}

View *ViewFactory_flutter::createTitleBar(Core::TitleBar *, View *) const
{
    return {};
}

View *ViewFactory_flutter::createTabBar(Core::TabBar *, View *) const
{
    return {};
}

View *ViewFactory_flutter::createStack(Core::Stack *, View *) const
{
    return {};
}

View *ViewFactory_flutter::createSeparator(Core::Separator *, View *) const
{
    return {};
}

View *ViewFactory_flutter::createFloatingWindow(Core::FloatingWindow *,
                                                Core::MainWindow *, Qt::WindowFlags) const
{
    return {};
}

View *ViewFactory_flutter::createRubberBand(View *) const
{
    return nullptr;
}

View *ViewFactory_flutter::createSideBar(Core::SideBar *, View *) const
{
    return {};
}

QAbstractButton *ViewFactory_flutter::createTitleBarButton(QWidget *, TitleBarButtonType) const
{
    return nullptr;
}

// iconForButtonType impl is the same for QtQuick and QtWidgets
Icon ViewFactory_flutter::iconForButtonType(TitleBarButtonType, qreal) const
{
    return {};
}

View *ViewFactory_flutter::createDropArea(Core::DropArea *, View *) const
{
    return {};
}

View *ViewFactory_flutter::createMDILayout(Core::MDILayout *, View *) const
{
    return {};
}

View *
ViewFactory_flutter::createSegmentedDropIndicatorOverlayView(Core::SegmentedIndicators *,
                                                             View *) const
{
    return {};
}

Core::ClassicIndicatorWindowViewInterface *
ViewFactory_flutter::createClassicIndicatorWindow(Core::ClassicIndicators *) const
{
    return {};
}

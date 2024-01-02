/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sergio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// Tests that the includes are installed

#if KDDW_FRONTEND_QTWIDGETS
#include <kddockwidgets/qtwidgets/Platform.h>
#include <kddockwidgets/qtwidgets/ViewFactory.h>
#include <kddockwidgets/qtwidgets/views/ClassicIndicatorsWindow.h>
#include <kddockwidgets/qtwidgets/views/DockWidget.h>
#include <kddockwidgets/qtwidgets/views/DropArea.h>
#include <kddockwidgets/qtwidgets/views/FloatingWindow.h>
#include <kddockwidgets/qtwidgets/views/Group.h>
#include <kddockwidgets/qtwidgets/views/MainWindow.h>
#include <kddockwidgets/qtwidgets/views/MainWindowMDI.h>
#include <kddockwidgets/qtwidgets/views/MDILayout.h>
#include <kddockwidgets/qtwidgets/views/RubberBand.h>
#include <kddockwidgets/qtwidgets/views/Separator.h>
#include <kddockwidgets/qtwidgets/views/Stack.h>
#include <kddockwidgets/qtwidgets/views/TabBar.h>
#include <kddockwidgets/qtwidgets/views/TitleBar.h>
#include <kddockwidgets/qtwidgets/views/View.h>
#endif

#if KDDW_FRONTEND_QTQUICK
#include <kddockwidgets/qtquick/Action.h>
#include <kddockwidgets/qtquick/Platform.h>
#include <kddockwidgets/qtquick/ViewFactory.h>
#include <kddockwidgets/qtquick/views/ClassicIndicatorsWindow.h>
#include <kddockwidgets/qtquick/views/DockWidget.h>
#include <kddockwidgets/qtquick/views/DropArea.h>
#include <kddockwidgets/qtquick/views/FloatingWindow.h>
#include <kddockwidgets/qtquick/views/Group.h>
#include <kddockwidgets/qtquick/views/MainWindow.h>
#include <kddockwidgets/qtquick/views/MainWindowMDI.h>
#include <kddockwidgets/qtquick/views/MDILayout.h>
#include <kddockwidgets/qtquick/views/RubberBand.h>
#include <kddockwidgets/qtquick/views/Separator.h>
#include <kddockwidgets/qtquick/views/Stack.h>
#include <kddockwidgets/qtquick/views/TabBar.h>
#include <kddockwidgets/qtquick/views/TitleBar.h>
#include <kddockwidgets/qtquick/views/View.h>
#endif

#include <kddockwidgets/qtcommon/View.h>
#include <kddockwidgets/qtcommon/Platform.h>

#include <kddockwidgets/Config.h>
#include <kddockwidgets/docks_export.h>
#include <kddockwidgets/KDDockWidgets.h>
#include <kddockwidgets/LayoutSaver.h>
#include <kddockwidgets/Qt5Qt6Compat_p.h>
#include <kddockwidgets/QtCompat_p.h>

#include <kddockwidgets/core/Action.h>
#include <kddockwidgets/core/DockRegistry.h>
#include <kddockwidgets/core/Draggable_p.h>
#include <kddockwidgets/core/EventFilterInterface.h>
#include <kddockwidgets/core/Group.h>
#include <kddockwidgets/core/MDILayout.h>
#include <kddockwidgets/core/SideBar.h>
#include <kddockwidgets/core/TabBar.h>
#include <kddockwidgets/core/View.h>
#include <kddockwidgets/core/Controller.h>
#include <kddockwidgets/core/DockWidget.h>
#include <kddockwidgets/core/DropArea.h>
#include <kddockwidgets/core/DropIndicatorOverlay.h>
#include <kddockwidgets/core/FloatingWindow.h>
#include <kddockwidgets/core/FocusScope.h>
#include <kddockwidgets/core/Layout.h>
#include <kddockwidgets/core/MainWindow.h>
#include <kddockwidgets/core/Platform.h>
#include <kddockwidgets/core/Separator.h>
#include <kddockwidgets/core/Stack.h>
#include <kddockwidgets/core/TitleBar.h>
#include <kddockwidgets/core/ViewFactory.h>

// Will only be available upon request
// #include <kddockwidgets/core/WidgetResizeHandler_p.h>

int main()
{
    return 0;
}

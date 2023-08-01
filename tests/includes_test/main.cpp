/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sergio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// Tests that the includes are installed

#if KDDW_FRONTEND_QTWIDGETS
// #include <kddockwidgets/qtwidgets/Action.h>
#include <kddockwidgets/qtwidgets/Platform.h>
#include <kddockwidgets/qtwidgets/ViewFactory.h>
#include <kddockwidgets/qtwidgets/Window.h>
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
#include <kddockwidgets/qtquick/Window.h>
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

#if KDDW_FRONTEND_QT
#include <kddockwidgets/qtcommon/View.h>
#include <kddockwidgets/qtcommon/Platform.h>
#endif

int main()
{
    return 0;
}

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/


// TODOm4: Remove ?
#ifndef DOCKS_DEVELOPER_MODE
#define DOCKS_DEVELOPER_MODE
#endif

#ifndef QT_NO_CAST_TO_ASCII
#define QT_NO_CAST_TO_ASCII
#endif

#ifndef QT_NO_CAST_FROM_ASCII
#define QT_NO_CAST_FROM_ASCII
#endif

#ifndef QT_NO_URL_CAST_FROM_STRING
#define QT_NO_URL_CAST_FROM_STRING
#endif

#ifndef QT_NO_CAST_FROM_BYTEARRAY
#define QT_NO_CAST_FROM_BYTEARRAY
#endif

#define QT_NO_KEYWORDS

#include "Platform_flutter.h"
#include "ViewFactory_flutter.h"

#include "views/View_flutter.h"
#include "views/Stack_flutter.h"
#include "views/Group_flutter.h"
#include "views/TabBar_flutter.h"
#include "views/TitleBar_flutter.h"
#include "views/DockWidget_flutter.h"

#include "../core/Layout.h"
#include "../core/DropArea.h"
#include "../core/Group.h"
#include "../core/Stack.h"
#include "../core/TabBar.h"
#include "../core/TitleBar.h"
#include "../core/Separator.h"
#include "../core/SideBar.h"
#include "../core/MainWindow.h"
#include "../core/FloatingWindow.h"
#include "../core/DropIndicatorOverlay.h"
#include "../core/indicators/ClassicIndicators.h"
#include "../views/ClassicIndicatorWindowViewInterface.h"

#include "../KDDockWidgets.h"
#include "../Config.h"
#include "../DockRegistry.h"

#include "../private/layouting/Item_p.h"

// TODO: kdbindings is choking shiboken
// #include "Window_flutter.h"

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

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

#include "../controllers/Layout.h"
#include "../controllers/DropArea.h"
#include "../controllers/Group.h"
#include "../controllers/Stack.h"
#include "../controllers/TabBar.h"
#include "../controllers/TitleBar.h"
#include "../controllers/Separator.h"
#include "../controllers/SideBar.h"
#include "../controllers/FloatingWindow.h"
#include "../controllers/DropIndicatorOverlay.h"
#include "../controllers/indicators/ClassicIndicators.h"
#include "../views/ClassicIndicatorWindowViewInterface.h"

#include "../KDDockWidgets.h"
#include "../Config.h"

#include "../private/multisplitter/Item_p.h"

// TODO: kdbindings is choking shiboken
// #include "Window_flutter.h"

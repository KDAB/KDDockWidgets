/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
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

#include "Platform_flutter.h"
#include "ViewFactory_flutter.h"
#include "ViewFactory.h"
#include "views/View_flutter.h"
#include "../KDDockWidgets.h"
#include "../Config.h"

// TODO: kdbindings is choking shiboken
// #include "Window_flutter.h"
// #include "../private/multisplitter/Item_p.h"

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/


#include "kddockwidgets/KDDockWidgets.h"
#include "Config.h"

#ifdef KDDW_FRONTEND_QTWIDGETS
#include "qtwidgets/Platform.h"
#endif

#ifdef KDDW_FRONTEND_QTQUICK
#include "qtquick/Platform.h"
#endif

#ifdef KDDW_FRONTEND_FLUTTER
#include "flutter/Platform.h"
#endif

void KDDockWidgets::initFrontend(FrontendType type)
{
    if (Core::Platform::instance())
        return;

    switch (type) {
    case FrontendType::QtWidgets:
#ifdef KDDW_FRONTEND_QTWIDGETS
        new QtWidgets::Platform();
#endif
        break;
    case FrontendType::QtQuick:
#ifdef KDDW_FRONTEND_QTQUICK
        new QtQuick::Platform();
#endif
        break;
    case FrontendType::Flutter:
        // Nothing to do, called from Dart
        break;
    }

    ( void )Config::self(); // Ensure Config ctor runs, as it registers qml types
}

const char *KDDockWidgets::spdlogLoggerName()
{
    return "com.kdab.kddockwidgets";
}

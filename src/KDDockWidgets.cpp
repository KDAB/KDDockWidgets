/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/


#include "KDDockWidgets.h"

#ifdef KDDW_FRONTEND_QTWIDGETS
#include "qtwidgets/Platform_qtwidgets.h"
#endif

#ifdef KDDW_FRONTEND_QTQUICK
#include "qtquick/Platform_qtquick.h"
#endif

#include <QDebug>

void KDDockWidgets::initFrontend(FrontendType type)
{
    if (Platform::instance())
        return;

    switch (type) {
    case FrontendType::QtWidgets:
#ifdef KDDW_FRONTEND_QTWIDGETS
        new Platform_qtwidgets();
#endif
        break;
    case FrontendType::QtQuick:
#ifdef KDDW_FRONTEND_QTQUICK
        new Platform_qtquick();
#endif
        break;
    }
}

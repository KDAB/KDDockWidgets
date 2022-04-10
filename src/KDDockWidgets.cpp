/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/


#include "KDDockWidgets.h"

#include "qtwidgets/Platform_qtwidgets.h"
#include "qtquick/Platform_qtquick.h"

#include <QDebug>

void KDDockWidgets::initFrontend(FrontendType type)
{
    if (Platform::instance())
        return;

    switch (type) {
    case FrontendType::QtWidgets:
        new Platform_qtwidgets();
        break;
    case FrontendType::QtQuick:
        // new Platform_qtquick(); // TODOv2
        break;
    }
}

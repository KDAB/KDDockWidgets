/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Platform_qtquick.h"
#include "KDDockWidgets.h"
// #include "QmlTypes.h" // TODOv2

#include <QQuickWindow>

static KDDockWidgets::Platform_qtquick s_platformQtQuick;

using namespace KDDockWidgets;



Platform_qtquick::Platform_qtquick()
{
    // KDDockWidgets::registerQmlTypes(); // TODOv2
    QQuickWindow::setDefaultAlphaBuffer(true);
}

Platform_qtquick::~Platform_qtquick()
{
}

const char *Platform_qtquick::name() const
{
    return "qtquick";
}

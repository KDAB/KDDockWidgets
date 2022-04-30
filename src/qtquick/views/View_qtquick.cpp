/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "View_qtquick.h"

#include <QGuiApplication>

using namespace KDDockWidgets::Views;

View_qtquick::View_qtquick(KDDockWidgets::Controller *controller, Type type,
                           QQuickItem *parent,
                           Qt::WindowFlags)
    : QQuickItem(parent)
    , View(controller, type, this)
{
    qApp->installEventFilter(this);

    // setSize(800, 800);
}

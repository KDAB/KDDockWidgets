/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Waqar Ahmed <waqar.ahmed@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Screen.h"

#include <QRect>

using namespace KDDockWidgets::flutter;

Screen::~Screen() = default;

QString Screen::name() const
{
    return QStringLiteral("dummy-screen");
}

QSize Screen::size() const
{
    return geometry().size();
}

QRect Screen::geometry() const
{
    return QRect(0, 0, 1920, 1080);
}

qreal Screen::devicePixelRatio() const
{
    return 1.0;
}

QSize Screen::availableSize() const
{
    return availableGeometry().size();
}

QRect Screen::availableGeometry() const
{
    return geometry();
}

QSize Screen::virtualSize() const
{
    return size();
}

QRect Screen::virtualGeometry() const
{
    return availableGeometry();
}

bool Screen::equals(std::shared_ptr<Core::Screen>) const
{
    return true;
}

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "../main.h"
#include "controllers/Frame.h"
#include "controllers/Stack.h"

#include "qtquick/Platform_qtquick.h"

#include <QQmlContext>
#include <QQmlEngine>

TEST_CASE("Stack ctor")
{
    Controllers::Frame frame(nullptr, {});
    Controllers::Stack stack(&frame, {});
}

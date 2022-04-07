/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Platform_qt.h"

#include <QGuiApplication>

using namespace KDDockWidgets;


Platform_qt::Platform_qt()
{
}

Platform_qt::~Platform_qt()
{
}

std::shared_ptr<ViewWrapper> Platform_qt::focusedView() const
{
    return qobjectAsView(qApp->focusObject());
}

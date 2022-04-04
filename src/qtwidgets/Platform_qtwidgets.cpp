/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Platform_qtwidgets.h"
#include "KDDockWidgets.h"
#include "qtwidgets/DebugWindow_p.h"

static KDDockWidgets::Platform_qtwidgets s_platformQtWidgets;

using namespace KDDockWidgets;

Platform_qtwidgets::Platform_qtwidgets()
{
#ifdef DOCKS_DEVELOPER_MODE
    if (qEnvironmentVariableIntValue("KDDOCKWIDGETS_SHOW_DEBUG_WINDOW") == 1) {
        auto dv = new Debug::DebugWindow();
        dv->show();
    }
#endif
}

Platform_qtwidgets::~Platform_qtwidgets()
{
}

const char *Platform_qtwidgets::name() const
{
    return "qtwidgets";
}

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <Qt5Qt6Compat_p.h>
#include <qstring.h>

extern "C" {
// KDDockWidgets::initFrontend(KDDockWidgets::FrontendType arg__1)
KDDockWidgetsBindings_EXPORT void c_static_KDDockWidgets__initFrontend_FrontendType(int arg__1);
// KDDockWidgets::locationStr(KDDockWidgets::Location loc)
KDDockWidgetsBindings_EXPORT void *c_static_KDDockWidgets__locationStr_Location(int loc);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets_Finalizer(void *, void *cppObj, void *);
}

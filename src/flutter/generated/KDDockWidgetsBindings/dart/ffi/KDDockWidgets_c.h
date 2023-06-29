/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include "KDDockWidgets_p.h"

extern "C" {
// KDDockWidgets::initFrontend(KDDockWidgets::FrontendType arg__1)
KDDockWidgetsBindings_EXPORT void c_static_KDDockWidgets__initFrontend_FrontendType(int arg__1);
// KDDockWidgets::spdlogLoggerName()
KDDockWidgetsBindings_EXPORT const char *c_static_KDDockWidgets__spdlogLoggerName();
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets_Finalizer(void *cppObj);
}

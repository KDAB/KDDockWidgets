/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <KDDockWidgets.h>
#include <View_flutter.h>
#include <View.h>
#include <Controller.h>

extern "C" {
// KDDockWidgets::Views::asView_flutter(KDDockWidgets::Controller * controller)
KDDockWidgetsBindings_EXPORT void *c_static_KDDockWidgets__Views__asView_flutter_Controller(void *controller_);
// KDDockWidgets::Views::asView_flutter(KDDockWidgets::View * view)
KDDockWidgetsBindings_EXPORT void *c_static_KDDockWidgets__Views__asView_flutter_View(void *view_);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views_Finalizer(void *, void *cppObj, void *);
}

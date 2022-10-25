/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <Platform.h>

namespace KDDockWidgetsBindings_wrappersNS {
class CreateViewOptions_wrapper : public ::KDDockWidgets::CreateViewOptions
{
public:
    ~CreateViewOptions_wrapper();
    CreateViewOptions_wrapper();
};
}
extern "C" {
// KDDockWidgets::CreateViewOptions::CreateViewOptions()
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__CreateViewOptions__constructor();
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__CreateViewOptions__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__CreateViewOptions___get_isVisible(void *thisObj);
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__CreateViewOptions___get_createWindow(void *thisObj);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__CreateViewOptions___set_isVisible_bool(void *thisObj, bool isVisible_);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__CreateViewOptions___set_createWindow_bool(void *thisObj, bool createWindow_);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__CreateViewOptions_Finalizer(void *, void *cppObj,
                                                                               void *);
}

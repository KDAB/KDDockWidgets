/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// tag=1040
#include "KDDockWidgetsBindings_exports.h"
#include <Platform.h>

namespace KDDockWidgetsBindings_wrappersNS {
// tag=1043
class CreateViewOptions_wrapper : public ::KDDockWidgets::CreateViewOptions
{
public:
    ~CreateViewOptions_wrapper();
    // tag=1041
    CreateViewOptions_wrapper();
};
}
extern "C" {

// tag=1067
//  KDDockWidgets::CreateViewOptions::CreateViewOptions()
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__CreateViewOptions__constructor();

// tag=1066
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__CreateViewOptions__destructor(void *thisObj);

// tag=1044
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__CreateViewOptions___get_isVisible(void *thisObj);

// tag=1044
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__CreateViewOptions___get_createWindow(void *thisObj);

// tag=1045
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__CreateViewOptions___set_isVisible_bool(void *thisObj, bool isVisible_);

// tag=1045
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__CreateViewOptions___set_createWindow_bool(void *thisObj, bool createWindow_);

// tag=1047
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__CreateViewOptions_Finalizer(void *, void *cppObj, void *);
}

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <core/Platform.h>
#include <qsize.h>

namespace KDDockWidgetsBindings_wrappersNS {
class CreateViewOptions_wrapper : public ::KDDockWidgets::Core::CreateViewOptions
{
public:
    ~CreateViewOptions_wrapper();
    CreateViewOptions_wrapper();
    QSize getMaxSize() const;
    QSize getMinSize() const;
    QSize getSize() const;
};
}
extern "C" {
// KDDockWidgets::Core::CreateViewOptions::CreateViewOptions()
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__CreateViewOptions__constructor();
// KDDockWidgets::Core::CreateViewOptions::getMaxSize() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__CreateViewOptions__getMaxSize(void *thisObj);
// KDDockWidgets::Core::CreateViewOptions::getMinSize() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__CreateViewOptions__getMinSize(void *thisObj);
// KDDockWidgets::Core::CreateViewOptions::getSize() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__CreateViewOptions__getSize(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__CreateViewOptions__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__CreateViewOptions___get_isVisible(void *thisObj);
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__CreateViewOptions___get_createWindow(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__CreateViewOptions___set_isVisible_bool(void *thisObj, bool isVisible_);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__CreateViewOptions___set_createWindow_bool(void *thisObj, bool createWindow_);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__CreateViewOptions_Finalizer(void *, void *cppObj, void *);
}

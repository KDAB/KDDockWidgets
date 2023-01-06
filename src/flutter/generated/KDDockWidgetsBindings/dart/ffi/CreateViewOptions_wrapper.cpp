/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "CreateViewOptions_wrapper.h"


#include <QDebug>


namespace Dartagnan {

typedef int (*CleanupCallback)(void *thisPtr);
static CleanupCallback s_cleanupCallback = nullptr;

template<typename T>
struct ValueWrapper
{
    T value;
};

}
namespace KDDockWidgetsBindings_wrappersNS {
CreateViewOptions_wrapper::CreateViewOptions_wrapper()
    : ::KDDockWidgets::CreateViewOptions()
{
}
CreateViewOptions_wrapper::~CreateViewOptions_wrapper()
{
}

}
static KDDockWidgets::CreateViewOptions *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::CreateViewOptions *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::CreateViewOptions_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::CreateViewOptions_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__CreateViewOptions_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::CreateViewOptions_wrapper *>(cppObj);
}
void *c_KDDockWidgets__CreateViewOptions__constructor()
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::CreateViewOptions_wrapper();
    return reinterpret_cast<void *>(ptr);
}
void c_KDDockWidgets__CreateViewOptions__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
bool c_KDDockWidgets__CreateViewOptions___get_isVisible(void *thisObj)
{
    return fromPtr(thisObj)->isVisible;
}
bool c_KDDockWidgets__CreateViewOptions___get_createWindow(void *thisObj)
{
    return fromPtr(thisObj)->createWindow;
}
void c_KDDockWidgets__CreateViewOptions___set_isVisible_bool(void *thisObj, bool isVisible_)
{
    fromPtr(thisObj)->isVisible = isVisible_;
}
void c_KDDockWidgets__CreateViewOptions___set_createWindow_bool(void *thisObj, bool createWindow_)
{
    fromPtr(thisObj)->createWindow = createWindow_;
}
}

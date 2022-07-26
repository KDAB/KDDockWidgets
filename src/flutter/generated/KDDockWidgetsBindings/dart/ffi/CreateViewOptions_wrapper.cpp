/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
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
// tag=1006
CreateViewOptions_wrapper::CreateViewOptions_wrapper()
    : ::KDDockWidgets::CreateViewOptions()
{
}

// tag=1005
CreateViewOptions_wrapper::~CreateViewOptions_wrapper()
{
}

}
// tag=1013
static KDDockWidgets::CreateViewOptions *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::CreateViewOptions *>(ptr);
}
// tag=1014
static KDDockWidgetsBindings_wrappersNS::CreateViewOptions_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::CreateViewOptions_wrapper *>(ptr);
}
extern "C" {

// tag=1049
void c_KDDockWidgets__CreateViewOptions_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::CreateViewOptions_wrapper *>(cppObj);
}
void *c_KDDockWidgets__CreateViewOptions__constructor()
{

    // tag=1056
    auto ptr = new KDDockWidgetsBindings_wrappersNS::CreateViewOptions_wrapper();
    return reinterpret_cast<void *>(ptr);
}
void c_KDDockWidgets__CreateViewOptions__destructor(void *thisObj)
{

    // tag=1055
    delete fromPtr(thisObj);
}
bool c_KDDockWidgets__CreateViewOptions___get_isVisible(void *thisObj)
{

    // tag=1058
    return fromPtr(thisObj)->isVisible;
}
bool c_KDDockWidgets__CreateViewOptions___get_createWindow(void *thisObj)
{

    // tag=1058
    return fromPtr(thisObj)->createWindow;
}
void c_KDDockWidgets__CreateViewOptions___set_isVisible_bool(void *thisObj, bool isVisible_)
{

    // tag=1057
    fromPtr(thisObj)->isVisible = isVisible_;
}
void c_KDDockWidgets__CreateViewOptions___set_createWindow_bool(void *thisObj, bool createWindow_)
{

    // tag=1057
    fromPtr(thisObj)->createWindow = createWindow_;
}
}

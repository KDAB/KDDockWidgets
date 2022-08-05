/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "InitialOption_wrapper.h"


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
InitialOption_wrapper::InitialOption_wrapper()
    : ::KDDockWidgets::InitialOption()
{
}
InitialOption_wrapper::InitialOption_wrapper(KDDockWidgets::DefaultSizeMode mode)
    : ::KDDockWidgets::InitialOption(mode)
{
}
InitialOption_wrapper::InitialOption_wrapper(KDDockWidgets::InitialVisibilityOption v)
    : ::KDDockWidgets::InitialOption(v)
{
}
InitialOption_wrapper::InitialOption_wrapper(KDDockWidgets::InitialVisibilityOption v, QSize size)
    : ::KDDockWidgets::InitialOption(v, size)
{
}
InitialOption_wrapper::InitialOption_wrapper(QSize size)
    : ::KDDockWidgets::InitialOption(size)
{
}
bool InitialOption_wrapper::preservesCurrentTab() const
{
    return ::KDDockWidgets::InitialOption::preservesCurrentTab();
}
bool InitialOption_wrapper::startsHidden() const
{
    return ::KDDockWidgets::InitialOption::startsHidden();
}
InitialOption_wrapper::~InitialOption_wrapper()
{
}

}
static KDDockWidgets::InitialOption *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::InitialOption *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::InitialOption_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::InitialOption_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__InitialOption_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::InitialOption_wrapper *>(cppObj);
}
void *c_KDDockWidgets__InitialOption__constructor()
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::InitialOption_wrapper();
    return reinterpret_cast<void *>(ptr);
}
void *c_KDDockWidgets__InitialOption__constructor_DefaultSizeMode(int mode)
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::InitialOption_wrapper(
        static_cast<KDDockWidgets::DefaultSizeMode>(mode));
    return reinterpret_cast<void *>(ptr);
}
void *c_KDDockWidgets__InitialOption__constructor_InitialVisibilityOption(int v)
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::InitialOption_wrapper(
        static_cast<KDDockWidgets::InitialVisibilityOption>(v));
    return reinterpret_cast<void *>(ptr);
}
void *c_KDDockWidgets__InitialOption__constructor_InitialVisibilityOption_QSize(int v, void *size_)
{
    auto &size = *reinterpret_cast<QSize *>(size_);
    auto ptr = new KDDockWidgetsBindings_wrappersNS::InitialOption_wrapper(
        static_cast<KDDockWidgets::InitialVisibilityOption>(v), size);
    return reinterpret_cast<void *>(ptr);
}
void *c_KDDockWidgets__InitialOption__constructor_QSize(void *size_)
{
    auto &size = *reinterpret_cast<QSize *>(size_);
    auto ptr = new KDDockWidgetsBindings_wrappersNS::InitialOption_wrapper(size);
    return reinterpret_cast<void *>(ptr);
}
// preservesCurrentTab() const
bool c_KDDockWidgets__InitialOption__preservesCurrentTab(void *thisObj)
{
    return fromPtr(thisObj)->preservesCurrentTab();
}
// startsHidden() const
bool c_KDDockWidgets__InitialOption__startsHidden(void *thisObj)
{
    return fromPtr(thisObj)->startsHidden();
}
void c_KDDockWidgets__InitialOption__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
}

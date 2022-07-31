/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

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
// tag=1006
InitialOption_wrapper::InitialOption_wrapper()
    : ::KDDockWidgets::InitialOption()
{
}

// tag=1006
InitialOption_wrapper::InitialOption_wrapper(QSize size)
    : ::KDDockWidgets::InitialOption(size)
{
}
bool InitialOption_wrapper::preservesCurrentTab() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::InitialOption::preservesCurrentTab();
}
bool InitialOption_wrapper::startsHidden() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::InitialOption::startsHidden();
}

// tag=1005
InitialOption_wrapper::~InitialOption_wrapper()
{
}

}
// tag=1013
static KDDockWidgets::InitialOption *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::InitialOption *>(ptr);
}
// tag=1014
static KDDockWidgetsBindings_wrappersNS::InitialOption_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::InitialOption_wrapper *>(ptr);
}
extern "C" {

// tag=1049
void c_KDDockWidgets__InitialOption_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::InitialOption_wrapper *>(cppObj);
}
void *c_KDDockWidgets__InitialOption__constructor()
{

    // tag=1056
    auto ptr = new KDDockWidgetsBindings_wrappersNS::InitialOption_wrapper();
    return reinterpret_cast<void *>(ptr);
}
void *c_KDDockWidgets__InitialOption__constructor_QSize(void *size_)
{
    auto &size = *reinterpret_cast<QSize *>(size_);
    // tag=1056
    auto ptr = new KDDockWidgetsBindings_wrappersNS::InitialOption_wrapper(size);
    return reinterpret_cast<void *>(ptr);
}

// tag=1050
// preservesCurrentTab() const
bool c_KDDockWidgets__InitialOption__preservesCurrentTab(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->preservesCurrentTab();
}

// tag=1050
// startsHidden() const
bool c_KDDockWidgets__InitialOption__startsHidden(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->startsHidden();
}
void c_KDDockWidgets__InitialOption__destructor(void *thisObj)
{

    // tag=1055
    delete fromPtr(thisObj);
}
}

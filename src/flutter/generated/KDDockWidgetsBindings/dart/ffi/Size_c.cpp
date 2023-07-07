/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "Size_c.h"


#include <iostream>


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
Size_wrapper::Size_wrapper()
    : ::KDDockWidgets::Size()
{
}
Size_wrapper::Size_wrapper(int width, int height)
    : ::KDDockWidgets::Size(width, height)
{
}
KDDockWidgets::Size Size_wrapper::boundedTo(KDDockWidgets::Size arg__1) const
{
    return ::KDDockWidgets::Size::boundedTo(arg__1);
}
KDDockWidgets::Size Size_wrapper::expandedTo(KDDockWidgets::Size arg__1) const
{
    return ::KDDockWidgets::Size::expandedTo(arg__1);
}
int Size_wrapper::height() const
{
    return ::KDDockWidgets::Size::height();
}
bool Size_wrapper::isEmpty() const
{
    return ::KDDockWidgets::Size::isEmpty();
}
bool Size_wrapper::isNull() const
{
    return ::KDDockWidgets::Size::isNull();
}
bool Size_wrapper::isValid() const
{
    return ::KDDockWidgets::Size::isValid();
}
void Size_wrapper::setHeight(int h)
{
    ::KDDockWidgets::Size::setHeight(h);
}
void Size_wrapper::setWidth(int w)
{
    ::KDDockWidgets::Size::setWidth(w);
}
int Size_wrapper::width() const
{
    return ::KDDockWidgets::Size::width();
}
Size_wrapper::~Size_wrapper()
{
}

}
static KDDockWidgets::Size *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::Size *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::Size_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Size_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__Size_Finalizer(void *cppObj)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Size_wrapper *>(cppObj);
}
void *c_KDDockWidgets__Size__constructor()
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::Size_wrapper();
    return reinterpret_cast<void *>(ptr);
}
void *c_KDDockWidgets__Size__constructor_int_int(int width, int height)
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::Size_wrapper(width, height);
    return reinterpret_cast<void *>(ptr);
}
// boundedTo(KDDockWidgets::Size arg__1) const
void *c_KDDockWidgets__Size__boundedTo_Size(void *thisObj, void *arg__1_)
{
    assert(arg__1_);
    auto &arg__1 = *reinterpret_cast<KDDockWidgets::Size *>(arg__1_);
    return new Dartagnan::ValueWrapper<KDDockWidgets::Size> { fromPtr(thisObj)->boundedTo(arg__1) };
}
// expandedTo(KDDockWidgets::Size arg__1) const
void *c_KDDockWidgets__Size__expandedTo_Size(void *thisObj, void *arg__1_)
{
    assert(arg__1_);
    auto &arg__1 = *reinterpret_cast<KDDockWidgets::Size *>(arg__1_);
    return new Dartagnan::ValueWrapper<KDDockWidgets::Size> { fromPtr(thisObj)->expandedTo(arg__1) };
}
// height() const
int c_KDDockWidgets__Size__height(void *thisObj)
{
    return fromPtr(thisObj)->height();
}
// isEmpty() const
bool c_KDDockWidgets__Size__isEmpty(void *thisObj)
{
    return fromPtr(thisObj)->isEmpty();
}
// isNull() const
bool c_KDDockWidgets__Size__isNull(void *thisObj)
{
    return fromPtr(thisObj)->isNull();
}
// isValid() const
bool c_KDDockWidgets__Size__isValid(void *thisObj)
{
    return fromPtr(thisObj)->isValid();
}
// setHeight(int h)
void c_KDDockWidgets__Size__setHeight_int(void *thisObj, int h)
{
    fromPtr(thisObj)->setHeight(h);
}
// setWidth(int w)
void c_KDDockWidgets__Size__setWidth_int(void *thisObj, int w)
{
    fromPtr(thisObj)->setWidth(w);
}
// width() const
int c_KDDockWidgets__Size__width(void *thisObj)
{
    return fromPtr(thisObj)->width();
}
void c_KDDockWidgets__Size__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
}

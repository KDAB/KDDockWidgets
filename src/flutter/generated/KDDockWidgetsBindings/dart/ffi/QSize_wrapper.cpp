/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "QSize_wrapper.h"


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
QSize_wrapper::QSize_wrapper()
    : ::QSize()
{
}
QSize_wrapper::QSize_wrapper(int w, int h)
    : ::QSize(w, h)
{
}
QSize QSize_wrapper::boundedTo(const QSize &arg__1) const
{
    return ::QSize::boundedTo(arg__1);
}
QSize QSize_wrapper::expandedTo(const QSize &arg__1) const
{
    return ::QSize::expandedTo(arg__1);
}
int QSize_wrapper::height() const
{
    return ::QSize::height();
}
bool QSize_wrapper::isEmpty() const
{
    return ::QSize::isEmpty();
}
bool QSize_wrapper::isNull() const
{
    return ::QSize::isNull();
}
bool QSize_wrapper::isValid() const
{
    return ::QSize::isValid();
}
void QSize_wrapper::setHeight(int h)
{
    ::QSize::setHeight(h);
}
void QSize_wrapper::setWidth(int w)
{
    ::QSize::setWidth(w);
}
void QSize_wrapper::transpose()
{
    ::QSize::transpose();
}
QSize QSize_wrapper::transposed() const
{
    return ::QSize::transposed();
}
int QSize_wrapper::width() const
{
    return ::QSize::width();
}
QSize_wrapper::~QSize_wrapper()
{
}

}
static QSize *fromPtr(void *ptr)
{
    return reinterpret_cast<QSize *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::QSize_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QSize_wrapper *>(ptr);
}
extern "C" {
void c_QSize_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QSize_wrapper *>(cppObj);
}
void *c_QSize__constructor()
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QSize_wrapper();
    return reinterpret_cast<void *>(ptr);
}
void *c_QSize__constructor_int_int(int w, int h)
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QSize_wrapper(w, h);
    return reinterpret_cast<void *>(ptr);
}
// boundedTo(const QSize & arg__1) const
void *c_QSize__boundedTo_QSize(void *thisObj, void *arg__1_)
{
    assert(arg__1_);
    auto &arg__1 = *reinterpret_cast<QSize *>(arg__1_);
    return new Dartagnan::ValueWrapper<QSize> { fromPtr(thisObj)->boundedTo(arg__1) };
}
// expandedTo(const QSize & arg__1) const
void *c_QSize__expandedTo_QSize(void *thisObj, void *arg__1_)
{
    assert(arg__1_);
    auto &arg__1 = *reinterpret_cast<QSize *>(arg__1_);
    return new Dartagnan::ValueWrapper<QSize> { fromPtr(thisObj)->expandedTo(arg__1) };
}
// height() const
int c_QSize__height(void *thisObj)
{
    return fromPtr(thisObj)->height();
}
// isEmpty() const
bool c_QSize__isEmpty(void *thisObj)
{
    return fromPtr(thisObj)->isEmpty();
}
// isNull() const
bool c_QSize__isNull(void *thisObj)
{
    return fromPtr(thisObj)->isNull();
}
// isValid() const
bool c_QSize__isValid(void *thisObj)
{
    return fromPtr(thisObj)->isValid();
}
// setHeight(int h)
void c_QSize__setHeight_int(void *thisObj, int h)
{
    fromPtr(thisObj)->setHeight(h);
}
// setWidth(int w)
void c_QSize__setWidth_int(void *thisObj, int w)
{
    fromPtr(thisObj)->setWidth(w);
}
// transpose()
void c_QSize__transpose(void *thisObj)
{
    fromPtr(thisObj)->transpose();
}
// transposed() const
void *c_QSize__transposed(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { fromPtr(thisObj)->transposed() };
}
// width() const
int c_QSize__width(void *thisObj)
{
    return fromPtr(thisObj)->width();
}
void c_QSize__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
}

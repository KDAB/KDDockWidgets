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
// tag=1006
QSize_wrapper::QSize_wrapper()
    : ::QSize()
{
}

// tag=1006
QSize_wrapper::QSize_wrapper(int w, int h)
    : ::QSize(w, h)
{
}
QSize QSize_wrapper::boundedTo(const QSize &arg__1) const
{
    // tag=1000

    // tag=1004
    return ::QSize::boundedTo(arg__1);
}
QSize QSize_wrapper::expandedTo(const QSize &arg__1) const
{
    // tag=1000

    // tag=1004
    return ::QSize::expandedTo(arg__1);
}
int QSize_wrapper::height() const
{
    // tag=1000

    // tag=1004
    return ::QSize::height();
}
bool QSize_wrapper::isEmpty() const
{
    // tag=1000

    // tag=1004
    return ::QSize::isEmpty();
}
bool QSize_wrapper::isNull() const
{
    // tag=1000

    // tag=1004
    return ::QSize::isNull();
}
bool QSize_wrapper::isValid() const
{
    // tag=1000

    // tag=1004
    return ::QSize::isValid();
}
void QSize_wrapper::setHeight(int h)
{
    // tag=1000

    // tag=1004
    ::QSize::setHeight(h);
}
void QSize_wrapper::setWidth(int w)
{
    // tag=1000

    // tag=1004
    ::QSize::setWidth(w);
}
void QSize_wrapper::transpose()
{
    // tag=1000

    // tag=1004
    ::QSize::transpose();
}
QSize QSize_wrapper::transposed() const
{
    // tag=1000

    // tag=1004
    return ::QSize::transposed();
}
int QSize_wrapper::width() const
{
    // tag=1000

    // tag=1004
    return ::QSize::width();
}

// tag=1005
QSize_wrapper::~QSize_wrapper()
{
}

}
// tag=1013
static QSize *fromPtr(void *ptr)
{
    return reinterpret_cast<QSize *>(ptr);
}
// tag=1014
static KDDockWidgetsBindings_wrappersNS::QSize_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QSize_wrapper *>(ptr);
}
extern "C" {

// tag=1049
void c_QSize_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QSize_wrapper *>(cppObj);
}
void *c_QSize__constructor()
{

    // tag=1056
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QSize_wrapper();
    return reinterpret_cast<void *>(ptr);
}
void *c_QSize__constructor_int_int(int w, int h)
{

    // tag=1056
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QSize_wrapper(w, h);
    return reinterpret_cast<void *>(ptr);
}

// tag=1050
// boundedTo(const QSize & arg__1) const
void *c_QSize__boundedTo_QSize(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QSize *>(arg__1_);
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QSize> { fromPtr(thisObj)->boundedTo(arg__1) };
}

// tag=1050
// expandedTo(const QSize & arg__1) const
void *c_QSize__expandedTo_QSize(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QSize *>(arg__1_);
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QSize> { fromPtr(thisObj)->expandedTo(arg__1) };
}

// tag=1050
// height() const
int c_QSize__height(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->height();
}

// tag=1050
// isEmpty() const
bool c_QSize__isEmpty(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->isEmpty();
}

// tag=1050
// isNull() const
bool c_QSize__isNull(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->isNull();
}

// tag=1050
// isValid() const
bool c_QSize__isValid(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->isValid();
}

// tag=1050
// setHeight(int h)
void c_QSize__setHeight_int(void *thisObj, int h)
{
    // tag=1010
    fromPtr(thisObj)->setHeight(h);
}

// tag=1050
// setWidth(int w)
void c_QSize__setWidth_int(void *thisObj, int w)
{
    // tag=1010
    fromPtr(thisObj)->setWidth(w);
}

// tag=1050
// transpose()
void c_QSize__transpose(void *thisObj)
{
    // tag=1010
    fromPtr(thisObj)->transpose();
}

// tag=1050
// transposed() const
void *c_QSize__transposed(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QSize> { fromPtr(thisObj)->transposed() };
}

// tag=1050
// width() const
int c_QSize__width(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->width();
}
void c_QSize__destructor(void *thisObj)
{

    // tag=1055
    delete fromPtr(thisObj);
}
}

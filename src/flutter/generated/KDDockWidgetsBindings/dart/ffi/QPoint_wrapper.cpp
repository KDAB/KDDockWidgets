/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "QPoint_wrapper.h"


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
QPoint_wrapper::QPoint_wrapper()
    : ::QPoint()
{
}
QPoint_wrapper::QPoint_wrapper(int xpos, int ypos)
    : ::QPoint(xpos, ypos)
{
}
int QPoint_wrapper::dotProduct(const QPoint &p1, const QPoint &p2)
{
    return ::QPoint::dotProduct(p1, p2);
}
bool QPoint_wrapper::isNull() const
{
    return ::QPoint::isNull();
}
int QPoint_wrapper::manhattanLength() const
{
    return ::QPoint::manhattanLength();
}
void QPoint_wrapper::setX(int x)
{
    ::QPoint::setX(x);
}
void QPoint_wrapper::setY(int y)
{
    ::QPoint::setY(y);
}
QPoint QPoint_wrapper::transposed() const
{
    return ::QPoint::transposed();
}
int QPoint_wrapper::x() const
{
    return ::QPoint::x();
}
int QPoint_wrapper::y() const
{
    return ::QPoint::y();
}
QPoint_wrapper::~QPoint_wrapper()
{
}

}
static QPoint *fromPtr(void *ptr)
{
    return reinterpret_cast<QPoint *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::QPoint_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QPoint_wrapper *>(ptr);
}
extern "C" {
void c_QPoint_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QPoint_wrapper *>(cppObj);
}
void *c_QPoint__constructor()
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QPoint_wrapper();
    return reinterpret_cast<void *>(ptr);
}
void *c_QPoint__constructor_int_int(int xpos, int ypos)
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QPoint_wrapper(xpos, ypos);
    return reinterpret_cast<void *>(ptr);
}
// dotProduct(const QPoint & p1, const QPoint & p2)
int c_static_QPoint__dotProduct_QPoint_QPoint(void *p1_, void *p2_)
{
    auto &p1 = *reinterpret_cast<QPoint *>(p1_);
    auto &p2 = *reinterpret_cast<QPoint *>(p2_);
    return KDDockWidgetsBindings_wrappersNS::QPoint_wrapper::dotProduct(p1, p2);
}
// isNull() const
bool c_QPoint__isNull(void *thisObj)
{
    return fromPtr(thisObj)->isNull();
}
// manhattanLength() const
int c_QPoint__manhattanLength(void *thisObj)
{
    return fromPtr(thisObj)->manhattanLength();
}
// setX(int x)
void c_QPoint__setX_int(void *thisObj, int x)
{
    fromPtr(thisObj)->setX(x);
}
// setY(int y)
void c_QPoint__setY_int(void *thisObj, int y)
{
    fromPtr(thisObj)->setY(y);
}
// transposed() const
void *c_QPoint__transposed(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QPoint> { fromPtr(thisObj)->transposed() };
}
// x() const
int c_QPoint__x(void *thisObj)
{
    return fromPtr(thisObj)->x();
}
// y() const
int c_QPoint__y(void *thisObj)
{
    return fromPtr(thisObj)->y();
}
void c_QPoint__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
}

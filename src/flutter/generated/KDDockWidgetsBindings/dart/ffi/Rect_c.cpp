/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "Rect_c.h"


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
Rect_wrapper::Rect_wrapper()
    : ::KDDockWidgets::Rect()
{
}
Rect_wrapper::Rect_wrapper(KDDockWidgets::Point pos, KDDockWidgets::Size size)
    : ::KDDockWidgets::Rect(pos, size)
{
}
Rect_wrapper::Rect_wrapper(int x, int y, int width, int height)
    : ::KDDockWidgets::Rect(x, y, width, height)
{
}
void Rect_wrapper::adjust(int arg__1, int arg__2, int arg__3, int arg__4) const
{
    ::KDDockWidgets::Rect::adjust(arg__1, arg__2, arg__3, arg__4);
}
KDDockWidgets::Rect Rect_wrapper::adjusted(int arg__1, int arg__2, int arg__3, int arg__4) const
{
    return ::KDDockWidgets::Rect::adjusted(arg__1, arg__2, arg__3, arg__4);
}
int Rect_wrapper::bottom() const
{
    return ::KDDockWidgets::Rect::bottom();
}
KDDockWidgets::Point Rect_wrapper::bottomLeft() const
{
    return ::KDDockWidgets::Rect::bottomLeft();
}
KDDockWidgets::Point Rect_wrapper::bottomRight() const
{
    return ::KDDockWidgets::Rect::bottomRight();
}
KDDockWidgets::Point Rect_wrapper::center() const
{
    return ::KDDockWidgets::Rect::center();
}
bool Rect_wrapper::contains(KDDockWidgets::Point pt) const
{
    return ::KDDockWidgets::Rect::contains(pt);
}
bool Rect_wrapper::contains(KDDockWidgets::Rect arg__1) const
{
    return ::KDDockWidgets::Rect::contains(arg__1);
}
int Rect_wrapper::height() const
{
    return ::KDDockWidgets::Rect::height();
}
KDDockWidgets::Rect Rect_wrapper::intersected(KDDockWidgets::Rect arg__1) const
{
    return ::KDDockWidgets::Rect::intersected(arg__1);
}
bool Rect_wrapper::intersects(KDDockWidgets::Rect arg__1) const
{
    return ::KDDockWidgets::Rect::intersects(arg__1);
}
bool Rect_wrapper::isEmpty() const
{
    return ::KDDockWidgets::Rect::isEmpty();
}
bool Rect_wrapper::isNull() const
{
    return ::KDDockWidgets::Rect::isNull();
}
bool Rect_wrapper::isValid() const
{
    return ::KDDockWidgets::Rect::isValid();
}
int Rect_wrapper::left() const
{
    return ::KDDockWidgets::Rect::left();
}
void Rect_wrapper::moveBottom(int arg__1)
{
    ::KDDockWidgets::Rect::moveBottom(arg__1);
}
void Rect_wrapper::moveCenter(KDDockWidgets::Point arg__1)
{
    ::KDDockWidgets::Rect::moveCenter(arg__1);
}
void Rect_wrapper::moveLeft(int x)
{
    ::KDDockWidgets::Rect::moveLeft(x);
}
void Rect_wrapper::moveRight(int arg__1)
{
    ::KDDockWidgets::Rect::moveRight(arg__1);
}
void Rect_wrapper::moveTo(KDDockWidgets::Point arg__1)
{
    ::KDDockWidgets::Rect::moveTo(arg__1);
}
void Rect_wrapper::moveTo(int arg__1, int arg__2)
{
    ::KDDockWidgets::Rect::moveTo(arg__1, arg__2);
}
void Rect_wrapper::moveTop(int y)
{
    ::KDDockWidgets::Rect::moveTop(y);
}
void Rect_wrapper::moveTopLeft(KDDockWidgets::Point pt)
{
    ::KDDockWidgets::Rect::moveTopLeft(pt);
}
KDDockWidgets::Point Rect_wrapper::pos() const
{
    return ::KDDockWidgets::Rect::pos();
}
int Rect_wrapper::right() const
{
    return ::KDDockWidgets::Rect::right();
}
void Rect_wrapper::setBottom(int arg__1)
{
    ::KDDockWidgets::Rect::setBottom(arg__1);
}
void Rect_wrapper::setHeight(int h)
{
    ::KDDockWidgets::Rect::setHeight(h);
}
void Rect_wrapper::setLeft(int x)
{
    ::KDDockWidgets::Rect::setLeft(x);
}
void Rect_wrapper::setRight(int r)
{
    ::KDDockWidgets::Rect::setRight(r);
}
void Rect_wrapper::setSize(KDDockWidgets::Size sz)
{
    ::KDDockWidgets::Rect::setSize(sz);
}
void Rect_wrapper::setTop(int arg__1)
{
    ::KDDockWidgets::Rect::setTop(arg__1);
}
void Rect_wrapper::setTopLeft(KDDockWidgets::Point arg__1)
{
    ::KDDockWidgets::Rect::setTopLeft(arg__1);
}
void Rect_wrapper::setWidth(int w)
{
    ::KDDockWidgets::Rect::setWidth(w);
}
void Rect_wrapper::setX(int arg__1)
{
    ::KDDockWidgets::Rect::setX(arg__1);
}
void Rect_wrapper::setY(int arg__1)
{
    ::KDDockWidgets::Rect::setY(arg__1);
}
KDDockWidgets::Size Rect_wrapper::size() const
{
    return ::KDDockWidgets::Rect::size();
}
int Rect_wrapper::top() const
{
    return ::KDDockWidgets::Rect::top();
}
KDDockWidgets::Point Rect_wrapper::topLeft() const
{
    return ::KDDockWidgets::Rect::topLeft();
}
KDDockWidgets::Point Rect_wrapper::topRight() const
{
    return ::KDDockWidgets::Rect::topRight();
}
void Rect_wrapper::translate(KDDockWidgets::Point arg__1)
{
    ::KDDockWidgets::Rect::translate(arg__1);
}
int Rect_wrapper::width() const
{
    return ::KDDockWidgets::Rect::width();
}
int Rect_wrapper::x() const
{
    return ::KDDockWidgets::Rect::x();
}
int Rect_wrapper::y() const
{
    return ::KDDockWidgets::Rect::y();
}
Rect_wrapper::~Rect_wrapper()
{
}

}
static KDDockWidgets::Rect *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::Rect *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::Rect_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Rect_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__Rect_Finalizer(void *cppObj)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Rect_wrapper *>(cppObj);
}
void *c_KDDockWidgets__Rect__constructor()
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::Rect_wrapper();
    return reinterpret_cast<void *>(ptr);
}
void *c_KDDockWidgets__Rect__constructor_Point_Size(void *pos_, void *size_)
{
    assert(pos_);
    auto &pos = *reinterpret_cast<KDDockWidgets::Point *>(pos_);
    assert(size_);
    auto &size = *reinterpret_cast<KDDockWidgets::Size *>(size_);
    auto ptr = new KDDockWidgetsBindings_wrappersNS::Rect_wrapper(pos, size);
    return reinterpret_cast<void *>(ptr);
}
void *c_KDDockWidgets__Rect__constructor_int_int_int_int(int x, int y, int width, int height)
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::Rect_wrapper(x, y, width, height);
    return reinterpret_cast<void *>(ptr);
}
// adjust(int arg__1, int arg__2, int arg__3, int arg__4) const
void c_KDDockWidgets__Rect__adjust_int_int_int_int(void *thisObj, int arg__1, int arg__2, int arg__3, int arg__4)
{
    fromPtr(thisObj)->adjust(arg__1, arg__2, arg__3, arg__4);
}
// adjusted(int arg__1, int arg__2, int arg__3, int arg__4) const
void *c_KDDockWidgets__Rect__adjusted_int_int_int_int(void *thisObj, int arg__1, int arg__2, int arg__3, int arg__4)
{
    return new Dartagnan::ValueWrapper<KDDockWidgets::Rect> { fromPtr(thisObj)->adjusted(arg__1, arg__2, arg__3, arg__4) };
}
// bottom() const
int c_KDDockWidgets__Rect__bottom(void *thisObj)
{
    return fromPtr(thisObj)->bottom();
}
// bottomLeft() const
void *c_KDDockWidgets__Rect__bottomLeft(void *thisObj)
{
    return new Dartagnan::ValueWrapper<KDDockWidgets::Point> { fromPtr(thisObj)->bottomLeft() };
}
// bottomRight() const
void *c_KDDockWidgets__Rect__bottomRight(void *thisObj)
{
    return new Dartagnan::ValueWrapper<KDDockWidgets::Point> { fromPtr(thisObj)->bottomRight() };
}
// center() const
void *c_KDDockWidgets__Rect__center(void *thisObj)
{
    return new Dartagnan::ValueWrapper<KDDockWidgets::Point> { fromPtr(thisObj)->center() };
}
// contains(KDDockWidgets::Point pt) const
bool c_KDDockWidgets__Rect__contains_Point(void *thisObj, void *pt_)
{
    assert(pt_);
    auto &pt = *reinterpret_cast<KDDockWidgets::Point *>(pt_);
    return fromPtr(thisObj)->contains(pt);
}
// contains(KDDockWidgets::Rect arg__1) const
bool c_KDDockWidgets__Rect__contains_Rect(void *thisObj, void *arg__1_)
{
    assert(arg__1_);
    auto &arg__1 = *reinterpret_cast<KDDockWidgets::Rect *>(arg__1_);
    return fromPtr(thisObj)->contains(arg__1);
}
// height() const
int c_KDDockWidgets__Rect__height(void *thisObj)
{
    return fromPtr(thisObj)->height();
}
// intersected(KDDockWidgets::Rect arg__1) const
void *c_KDDockWidgets__Rect__intersected_Rect(void *thisObj, void *arg__1_)
{
    assert(arg__1_);
    auto &arg__1 = *reinterpret_cast<KDDockWidgets::Rect *>(arg__1_);
    return new Dartagnan::ValueWrapper<KDDockWidgets::Rect> { fromPtr(thisObj)->intersected(arg__1) };
}
// intersects(KDDockWidgets::Rect arg__1) const
bool c_KDDockWidgets__Rect__intersects_Rect(void *thisObj, void *arg__1_)
{
    assert(arg__1_);
    auto &arg__1 = *reinterpret_cast<KDDockWidgets::Rect *>(arg__1_);
    return fromPtr(thisObj)->intersects(arg__1);
}
// isEmpty() const
bool c_KDDockWidgets__Rect__isEmpty(void *thisObj)
{
    return fromPtr(thisObj)->isEmpty();
}
// isNull() const
bool c_KDDockWidgets__Rect__isNull(void *thisObj)
{
    return fromPtr(thisObj)->isNull();
}
// isValid() const
bool c_KDDockWidgets__Rect__isValid(void *thisObj)
{
    return fromPtr(thisObj)->isValid();
}
// left() const
int c_KDDockWidgets__Rect__left(void *thisObj)
{
    return fromPtr(thisObj)->left();
}
// moveBottom(int arg__1)
void c_KDDockWidgets__Rect__moveBottom_int(void *thisObj, int arg__1)
{
    fromPtr(thisObj)->moveBottom(arg__1);
}
// moveCenter(KDDockWidgets::Point arg__1)
void c_KDDockWidgets__Rect__moveCenter_Point(void *thisObj, void *arg__1_)
{
    assert(arg__1_);
    auto &arg__1 = *reinterpret_cast<KDDockWidgets::Point *>(arg__1_);
    fromPtr(thisObj)->moveCenter(arg__1);
}
// moveLeft(int x)
void c_KDDockWidgets__Rect__moveLeft_int(void *thisObj, int x)
{
    fromPtr(thisObj)->moveLeft(x);
}
// moveRight(int arg__1)
void c_KDDockWidgets__Rect__moveRight_int(void *thisObj, int arg__1)
{
    fromPtr(thisObj)->moveRight(arg__1);
}
// moveTo(KDDockWidgets::Point arg__1)
void c_KDDockWidgets__Rect__moveTo_Point(void *thisObj, void *arg__1_)
{
    assert(arg__1_);
    auto &arg__1 = *reinterpret_cast<KDDockWidgets::Point *>(arg__1_);
    fromPtr(thisObj)->moveTo(arg__1);
}
// moveTo(int arg__1, int arg__2)
void c_KDDockWidgets__Rect__moveTo_int_int(void *thisObj, int arg__1, int arg__2)
{
    fromPtr(thisObj)->moveTo(arg__1, arg__2);
}
// moveTop(int y)
void c_KDDockWidgets__Rect__moveTop_int(void *thisObj, int y)
{
    fromPtr(thisObj)->moveTop(y);
}
// moveTopLeft(KDDockWidgets::Point pt)
void c_KDDockWidgets__Rect__moveTopLeft_Point(void *thisObj, void *pt_)
{
    assert(pt_);
    auto &pt = *reinterpret_cast<KDDockWidgets::Point *>(pt_);
    fromPtr(thisObj)->moveTopLeft(pt);
}
// pos() const
void *c_KDDockWidgets__Rect__pos(void *thisObj)
{
    return new Dartagnan::ValueWrapper<KDDockWidgets::Point> { fromPtr(thisObj)->pos() };
}
// right() const
int c_KDDockWidgets__Rect__right(void *thisObj)
{
    return fromPtr(thisObj)->right();
}
// setBottom(int arg__1)
void c_KDDockWidgets__Rect__setBottom_int(void *thisObj, int arg__1)
{
    fromPtr(thisObj)->setBottom(arg__1);
}
// setHeight(int h)
void c_KDDockWidgets__Rect__setHeight_int(void *thisObj, int h)
{
    fromPtr(thisObj)->setHeight(h);
}
// setLeft(int x)
void c_KDDockWidgets__Rect__setLeft_int(void *thisObj, int x)
{
    fromPtr(thisObj)->setLeft(x);
}
// setRight(int r)
void c_KDDockWidgets__Rect__setRight_int(void *thisObj, int r)
{
    fromPtr(thisObj)->setRight(r);
}
// setSize(KDDockWidgets::Size sz)
void c_KDDockWidgets__Rect__setSize_Size(void *thisObj, void *sz_)
{
    assert(sz_);
    auto &sz = *reinterpret_cast<KDDockWidgets::Size *>(sz_);
    fromPtr(thisObj)->setSize(sz);
}
// setTop(int arg__1)
void c_KDDockWidgets__Rect__setTop_int(void *thisObj, int arg__1)
{
    fromPtr(thisObj)->setTop(arg__1);
}
// setTopLeft(KDDockWidgets::Point arg__1)
void c_KDDockWidgets__Rect__setTopLeft_Point(void *thisObj, void *arg__1_)
{
    assert(arg__1_);
    auto &arg__1 = *reinterpret_cast<KDDockWidgets::Point *>(arg__1_);
    fromPtr(thisObj)->setTopLeft(arg__1);
}
// setWidth(int w)
void c_KDDockWidgets__Rect__setWidth_int(void *thisObj, int w)
{
    fromPtr(thisObj)->setWidth(w);
}
// setX(int arg__1)
void c_KDDockWidgets__Rect__setX_int(void *thisObj, int arg__1)
{
    fromPtr(thisObj)->setX(arg__1);
}
// setY(int arg__1)
void c_KDDockWidgets__Rect__setY_int(void *thisObj, int arg__1)
{
    fromPtr(thisObj)->setY(arg__1);
}
// size() const
void *c_KDDockWidgets__Rect__size(void *thisObj)
{
    return new Dartagnan::ValueWrapper<KDDockWidgets::Size> { fromPtr(thisObj)->size() };
}
// top() const
int c_KDDockWidgets__Rect__top(void *thisObj)
{
    return fromPtr(thisObj)->top();
}
// topLeft() const
void *c_KDDockWidgets__Rect__topLeft(void *thisObj)
{
    return new Dartagnan::ValueWrapper<KDDockWidgets::Point> { fromPtr(thisObj)->topLeft() };
}
// topRight() const
void *c_KDDockWidgets__Rect__topRight(void *thisObj)
{
    return new Dartagnan::ValueWrapper<KDDockWidgets::Point> { fromPtr(thisObj)->topRight() };
}
// translate(KDDockWidgets::Point arg__1)
void c_KDDockWidgets__Rect__translate_Point(void *thisObj, void *arg__1_)
{
    assert(arg__1_);
    auto &arg__1 = *reinterpret_cast<KDDockWidgets::Point *>(arg__1_);
    fromPtr(thisObj)->translate(arg__1);
}
// width() const
int c_KDDockWidgets__Rect__width(void *thisObj)
{
    return fromPtr(thisObj)->width();
}
// x() const
int c_KDDockWidgets__Rect__x(void *thisObj)
{
    return fromPtr(thisObj)->x();
}
// y() const
int c_KDDockWidgets__Rect__y(void *thisObj)
{
    return fromPtr(thisObj)->y();
}
void c_KDDockWidgets__Rect__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
}

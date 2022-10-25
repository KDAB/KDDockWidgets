/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "QRect_wrapper.h"


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
QRect_wrapper::QRect_wrapper()
    : ::QRect()
{
}
QRect_wrapper::QRect_wrapper(const QPoint &topleft, const QPoint &bottomright)
    : ::QRect(topleft, bottomright)
{
}
QRect_wrapper::QRect_wrapper(const QPoint &topleft, const QSize &size)
    : ::QRect(topleft, size)
{
}
QRect_wrapper::QRect_wrapper(int left, int top, int width, int height)
    : ::QRect(left, top, width, height)
{
}
void QRect_wrapper::adjust(int x1, int y1, int x2, int y2)
{
    ::QRect::adjust(x1, y1, x2, y2);
}
QRect QRect_wrapper::adjusted(int x1, int y1, int x2, int y2) const
{
    return ::QRect::adjusted(x1, y1, x2, y2);
}
int QRect_wrapper::bottom() const
{
    return ::QRect::bottom();
}
QPoint QRect_wrapper::bottomLeft() const
{
    return ::QRect::bottomLeft();
}
QPoint QRect_wrapper::bottomRight() const
{
    return ::QRect::bottomRight();
}
QPoint QRect_wrapper::center() const
{
    return ::QRect::center();
}
bool QRect_wrapper::contains(const QPoint &p, bool proper) const
{
    return ::QRect::contains(p, proper);
}
bool QRect_wrapper::contains(const QRect &r, bool proper) const
{
    return ::QRect::contains(r, proper);
}
bool QRect_wrapper::contains(int x, int y) const
{
    return ::QRect::contains(x, y);
}
bool QRect_wrapper::contains(int x, int y, bool proper) const
{
    return ::QRect::contains(x, y, proper);
}
int QRect_wrapper::height() const
{
    return ::QRect::height();
}
QRect QRect_wrapper::intersected(const QRect &other) const
{
    return ::QRect::intersected(other);
}
bool QRect_wrapper::intersects(const QRect &r) const
{
    return ::QRect::intersects(r);
}
bool QRect_wrapper::isEmpty() const
{
    return ::QRect::isEmpty();
}
bool QRect_wrapper::isNull() const
{
    return ::QRect::isNull();
}
bool QRect_wrapper::isValid() const
{
    return ::QRect::isValid();
}
int QRect_wrapper::left() const
{
    return ::QRect::left();
}
void QRect_wrapper::moveBottom(int pos)
{
    ::QRect::moveBottom(pos);
}
void QRect_wrapper::moveBottomLeft(const QPoint &p)
{
    ::QRect::moveBottomLeft(p);
}
void QRect_wrapper::moveBottomRight(const QPoint &p)
{
    ::QRect::moveBottomRight(p);
}
void QRect_wrapper::moveCenter(const QPoint &p)
{
    ::QRect::moveCenter(p);
}
void QRect_wrapper::moveLeft(int pos)
{
    ::QRect::moveLeft(pos);
}
void QRect_wrapper::moveRight(int pos)
{
    ::QRect::moveRight(pos);
}
void QRect_wrapper::moveTo(const QPoint &p)
{
    ::QRect::moveTo(p);
}
void QRect_wrapper::moveTo(int x, int t)
{
    ::QRect::moveTo(x, t);
}
void QRect_wrapper::moveTop(int pos)
{
    ::QRect::moveTop(pos);
}
void QRect_wrapper::moveTopLeft(const QPoint &p)
{
    ::QRect::moveTopLeft(p);
}
void QRect_wrapper::moveTopRight(const QPoint &p)
{
    ::QRect::moveTopRight(p);
}
QRect QRect_wrapper::normalized() const
{
    return ::QRect::normalized();
}
int QRect_wrapper::right() const
{
    return ::QRect::right();
}
void QRect_wrapper::setBottom(int pos)
{
    ::QRect::setBottom(pos);
}
void QRect_wrapper::setBottomLeft(const QPoint &p)
{
    ::QRect::setBottomLeft(p);
}
void QRect_wrapper::setBottomRight(const QPoint &p)
{
    ::QRect::setBottomRight(p);
}
void QRect_wrapper::setCoords(int x1, int y1, int x2, int y2)
{
    ::QRect::setCoords(x1, y1, x2, y2);
}
void QRect_wrapper::setHeight(int h)
{
    ::QRect::setHeight(h);
}
void QRect_wrapper::setLeft(int pos)
{
    ::QRect::setLeft(pos);
}
void QRect_wrapper::setRect(int x, int y, int w, int h)
{
    ::QRect::setRect(x, y, w, h);
}
void QRect_wrapper::setRight(int pos)
{
    ::QRect::setRight(pos);
}
void QRect_wrapper::setSize(const QSize &s)
{
    ::QRect::setSize(s);
}
void QRect_wrapper::setTop(int pos)
{
    ::QRect::setTop(pos);
}
void QRect_wrapper::setTopLeft(const QPoint &p)
{
    ::QRect::setTopLeft(p);
}
void QRect_wrapper::setTopRight(const QPoint &p)
{
    ::QRect::setTopRight(p);
}
void QRect_wrapper::setWidth(int w)
{
    ::QRect::setWidth(w);
}
void QRect_wrapper::setX(int x)
{
    ::QRect::setX(x);
}
void QRect_wrapper::setY(int y)
{
    ::QRect::setY(y);
}
QSize QRect_wrapper::size() const
{
    return ::QRect::size();
}
int QRect_wrapper::top() const
{
    return ::QRect::top();
}
QPoint QRect_wrapper::topLeft() const
{
    return ::QRect::topLeft();
}
QPoint QRect_wrapper::topRight() const
{
    return ::QRect::topRight();
}
void QRect_wrapper::translate(const QPoint &p)
{
    ::QRect::translate(p);
}
void QRect_wrapper::translate(int dx, int dy)
{
    ::QRect::translate(dx, dy);
}
QRect QRect_wrapper::translated(const QPoint &p) const
{
    return ::QRect::translated(p);
}
QRect QRect_wrapper::translated(int dx, int dy) const
{
    return ::QRect::translated(dx, dy);
}
QRect QRect_wrapper::transposed() const
{
    return ::QRect::transposed();
}
QRect QRect_wrapper::united(const QRect &other) const
{
    return ::QRect::united(other);
}
int QRect_wrapper::width() const
{
    return ::QRect::width();
}
int QRect_wrapper::x() const
{
    return ::QRect::x();
}
int QRect_wrapper::y() const
{
    return ::QRect::y();
}
QRect_wrapper::~QRect_wrapper()
{
}

}
static QRect *fromPtr(void *ptr)
{
    return reinterpret_cast<QRect *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::QRect_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QRect_wrapper *>(ptr);
}
extern "C" {
void c_QRect_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QRect_wrapper *>(cppObj);
}
void *c_QRect__constructor()
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QRect_wrapper();
    return reinterpret_cast<void *>(ptr);
}
void *c_QRect__constructor_QPoint_QPoint(void *topleft_, void *bottomright_)
{
    assert(topleft_);
    auto &topleft = *reinterpret_cast<QPoint *>(topleft_);
    assert(bottomright_);
    auto &bottomright = *reinterpret_cast<QPoint *>(bottomright_);
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QRect_wrapper(topleft, bottomright);
    return reinterpret_cast<void *>(ptr);
}
void *c_QRect__constructor_QPoint_QSize(void *topleft_, void *size_)
{
    assert(topleft_);
    auto &topleft = *reinterpret_cast<QPoint *>(topleft_);
    assert(size_);
    auto &size = *reinterpret_cast<QSize *>(size_);
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QRect_wrapper(topleft, size);
    return reinterpret_cast<void *>(ptr);
}
void *c_QRect__constructor_int_int_int_int(int left, int top, int width, int height)
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QRect_wrapper(left, top, width, height);
    return reinterpret_cast<void *>(ptr);
}
// adjust(int x1, int y1, int x2, int y2)
void c_QRect__adjust_int_int_int_int(void *thisObj, int x1, int y1, int x2, int y2)
{
    fromPtr(thisObj)->adjust(x1, y1, x2, y2);
}
// adjusted(int x1, int y1, int x2, int y2) const
void *c_QRect__adjusted_int_int_int_int(void *thisObj, int x1, int y1, int x2, int y2)
{
    return new Dartagnan::ValueWrapper<QRect> { fromPtr(thisObj)->adjusted(x1, y1, x2, y2) };
}
// bottom() const
int c_QRect__bottom(void *thisObj)
{
    return fromPtr(thisObj)->bottom();
}
// bottomLeft() const
void *c_QRect__bottomLeft(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QPoint> { fromPtr(thisObj)->bottomLeft() };
}
// bottomRight() const
void *c_QRect__bottomRight(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QPoint> { fromPtr(thisObj)->bottomRight() };
}
// center() const
void *c_QRect__center(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QPoint> { fromPtr(thisObj)->center() };
}
// contains(const QPoint & p, bool proper) const
bool c_QRect__contains_QPoint_bool(void *thisObj, void *p_, bool proper)
{
    assert(p_);
    auto &p = *reinterpret_cast<QPoint *>(p_);
    return fromPtr(thisObj)->contains(p, proper);
}
// contains(const QRect & r, bool proper) const
bool c_QRect__contains_QRect_bool(void *thisObj, void *r_, bool proper)
{
    assert(r_);
    auto &r = *reinterpret_cast<QRect *>(r_);
    return fromPtr(thisObj)->contains(r, proper);
}
// contains(int x, int y) const
bool c_QRect__contains_int_int(void *thisObj, int x, int y)
{
    return fromPtr(thisObj)->contains(x, y);
}
// contains(int x, int y, bool proper) const
bool c_QRect__contains_int_int_bool(void *thisObj, int x, int y, bool proper)
{
    return fromPtr(thisObj)->contains(x, y, proper);
}
// height() const
int c_QRect__height(void *thisObj)
{
    return fromPtr(thisObj)->height();
}
// intersected(const QRect & other) const
void *c_QRect__intersected_QRect(void *thisObj, void *other_)
{
    assert(other_);
    auto &other = *reinterpret_cast<QRect *>(other_);
    return new Dartagnan::ValueWrapper<QRect> { fromPtr(thisObj)->intersected(other) };
}
// intersects(const QRect & r) const
bool c_QRect__intersects_QRect(void *thisObj, void *r_)
{
    assert(r_);
    auto &r = *reinterpret_cast<QRect *>(r_);
    return fromPtr(thisObj)->intersects(r);
}
// isEmpty() const
bool c_QRect__isEmpty(void *thisObj)
{
    return fromPtr(thisObj)->isEmpty();
}
// isNull() const
bool c_QRect__isNull(void *thisObj)
{
    return fromPtr(thisObj)->isNull();
}
// isValid() const
bool c_QRect__isValid(void *thisObj)
{
    return fromPtr(thisObj)->isValid();
}
// left() const
int c_QRect__left(void *thisObj)
{
    return fromPtr(thisObj)->left();
}
// moveBottom(int pos)
void c_QRect__moveBottom_int(void *thisObj, int pos)
{
    fromPtr(thisObj)->moveBottom(pos);
}
// moveBottomLeft(const QPoint & p)
void c_QRect__moveBottomLeft_QPoint(void *thisObj, void *p_)
{
    assert(p_);
    auto &p = *reinterpret_cast<QPoint *>(p_);
    fromPtr(thisObj)->moveBottomLeft(p);
}
// moveBottomRight(const QPoint & p)
void c_QRect__moveBottomRight_QPoint(void *thisObj, void *p_)
{
    assert(p_);
    auto &p = *reinterpret_cast<QPoint *>(p_);
    fromPtr(thisObj)->moveBottomRight(p);
}
// moveCenter(const QPoint & p)
void c_QRect__moveCenter_QPoint(void *thisObj, void *p_)
{
    assert(p_);
    auto &p = *reinterpret_cast<QPoint *>(p_);
    fromPtr(thisObj)->moveCenter(p);
}
// moveLeft(int pos)
void c_QRect__moveLeft_int(void *thisObj, int pos)
{
    fromPtr(thisObj)->moveLeft(pos);
}
// moveRight(int pos)
void c_QRect__moveRight_int(void *thisObj, int pos)
{
    fromPtr(thisObj)->moveRight(pos);
}
// moveTo(const QPoint & p)
void c_QRect__moveTo_QPoint(void *thisObj, void *p_)
{
    assert(p_);
    auto &p = *reinterpret_cast<QPoint *>(p_);
    fromPtr(thisObj)->moveTo(p);
}
// moveTo(int x, int t)
void c_QRect__moveTo_int_int(void *thisObj, int x, int t)
{
    fromPtr(thisObj)->moveTo(x, t);
}
// moveTop(int pos)
void c_QRect__moveTop_int(void *thisObj, int pos)
{
    fromPtr(thisObj)->moveTop(pos);
}
// moveTopLeft(const QPoint & p)
void c_QRect__moveTopLeft_QPoint(void *thisObj, void *p_)
{
    assert(p_);
    auto &p = *reinterpret_cast<QPoint *>(p_);
    fromPtr(thisObj)->moveTopLeft(p);
}
// moveTopRight(const QPoint & p)
void c_QRect__moveTopRight_QPoint(void *thisObj, void *p_)
{
    assert(p_);
    auto &p = *reinterpret_cast<QPoint *>(p_);
    fromPtr(thisObj)->moveTopRight(p);
}
// normalized() const
void *c_QRect__normalized(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QRect> { fromPtr(thisObj)->normalized() };
}
// right() const
int c_QRect__right(void *thisObj)
{
    return fromPtr(thisObj)->right();
}
// setBottom(int pos)
void c_QRect__setBottom_int(void *thisObj, int pos)
{
    fromPtr(thisObj)->setBottom(pos);
}
// setBottomLeft(const QPoint & p)
void c_QRect__setBottomLeft_QPoint(void *thisObj, void *p_)
{
    assert(p_);
    auto &p = *reinterpret_cast<QPoint *>(p_);
    fromPtr(thisObj)->setBottomLeft(p);
}
// setBottomRight(const QPoint & p)
void c_QRect__setBottomRight_QPoint(void *thisObj, void *p_)
{
    assert(p_);
    auto &p = *reinterpret_cast<QPoint *>(p_);
    fromPtr(thisObj)->setBottomRight(p);
}
// setCoords(int x1, int y1, int x2, int y2)
void c_QRect__setCoords_int_int_int_int(void *thisObj, int x1, int y1, int x2, int y2)
{
    fromPtr(thisObj)->setCoords(x1, y1, x2, y2);
}
// setHeight(int h)
void c_QRect__setHeight_int(void *thisObj, int h)
{
    fromPtr(thisObj)->setHeight(h);
}
// setLeft(int pos)
void c_QRect__setLeft_int(void *thisObj, int pos)
{
    fromPtr(thisObj)->setLeft(pos);
}
// setRect(int x, int y, int w, int h)
void c_QRect__setRect_int_int_int_int(void *thisObj, int x, int y, int w, int h)
{
    fromPtr(thisObj)->setRect(x, y, w, h);
}
// setRight(int pos)
void c_QRect__setRight_int(void *thisObj, int pos)
{
    fromPtr(thisObj)->setRight(pos);
}
// setSize(const QSize & s)
void c_QRect__setSize_QSize(void *thisObj, void *s_)
{
    assert(s_);
    auto &s = *reinterpret_cast<QSize *>(s_);
    fromPtr(thisObj)->setSize(s);
}
// setTop(int pos)
void c_QRect__setTop_int(void *thisObj, int pos)
{
    fromPtr(thisObj)->setTop(pos);
}
// setTopLeft(const QPoint & p)
void c_QRect__setTopLeft_QPoint(void *thisObj, void *p_)
{
    assert(p_);
    auto &p = *reinterpret_cast<QPoint *>(p_);
    fromPtr(thisObj)->setTopLeft(p);
}
// setTopRight(const QPoint & p)
void c_QRect__setTopRight_QPoint(void *thisObj, void *p_)
{
    assert(p_);
    auto &p = *reinterpret_cast<QPoint *>(p_);
    fromPtr(thisObj)->setTopRight(p);
}
// setWidth(int w)
void c_QRect__setWidth_int(void *thisObj, int w)
{
    fromPtr(thisObj)->setWidth(w);
}
// setX(int x)
void c_QRect__setX_int(void *thisObj, int x)
{
    fromPtr(thisObj)->setX(x);
}
// setY(int y)
void c_QRect__setY_int(void *thisObj, int y)
{
    fromPtr(thisObj)->setY(y);
}
// size() const
void *c_QRect__size(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { fromPtr(thisObj)->size() };
}
// top() const
int c_QRect__top(void *thisObj)
{
    return fromPtr(thisObj)->top();
}
// topLeft() const
void *c_QRect__topLeft(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QPoint> { fromPtr(thisObj)->topLeft() };
}
// topRight() const
void *c_QRect__topRight(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QPoint> { fromPtr(thisObj)->topRight() };
}
// translate(const QPoint & p)
void c_QRect__translate_QPoint(void *thisObj, void *p_)
{
    assert(p_);
    auto &p = *reinterpret_cast<QPoint *>(p_);
    fromPtr(thisObj)->translate(p);
}
// translate(int dx, int dy)
void c_QRect__translate_int_int(void *thisObj, int dx, int dy)
{
    fromPtr(thisObj)->translate(dx, dy);
}
// translated(const QPoint & p) const
void *c_QRect__translated_QPoint(void *thisObj, void *p_)
{
    assert(p_);
    auto &p = *reinterpret_cast<QPoint *>(p_);
    return new Dartagnan::ValueWrapper<QRect> { fromPtr(thisObj)->translated(p) };
}
// translated(int dx, int dy) const
void *c_QRect__translated_int_int(void *thisObj, int dx, int dy)
{
    return new Dartagnan::ValueWrapper<QRect> { fromPtr(thisObj)->translated(dx, dy) };
}
// transposed() const
void *c_QRect__transposed(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QRect> { fromPtr(thisObj)->transposed() };
}
// united(const QRect & other) const
void *c_QRect__united_QRect(void *thisObj, void *other_)
{
    assert(other_);
    auto &other = *reinterpret_cast<QRect *>(other_);
    return new Dartagnan::ValueWrapper<QRect> { fromPtr(thisObj)->united(other) };
}
// width() const
int c_QRect__width(void *thisObj)
{
    return fromPtr(thisObj)->width();
}
// x() const
int c_QRect__x(void *thisObj)
{
    return fromPtr(thisObj)->x();
}
// y() const
int c_QRect__y(void *thisObj)
{
    return fromPtr(thisObj)->y();
}
void c_QRect__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
}

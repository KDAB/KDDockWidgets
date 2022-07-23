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
namespace KDDockWidgets_wrappersNS {
// tag=1006
QRect_wrapper::QRect_wrapper()
    : ::QRect()
{
}

// tag=1006
QRect_wrapper::QRect_wrapper(const QPoint &topleft, const QPoint &bottomright)
    : ::QRect(topleft, bottomright)
{
}

// tag=1006
QRect_wrapper::QRect_wrapper(const QPoint &topleft, const QSize &size)
    : ::QRect(topleft, size)
{
}

// tag=1006
QRect_wrapper::QRect_wrapper(int left, int top, int width, int height)
    : ::QRect(left, top, width, height)
{
}
void QRect_wrapper::adjust(int x1, int y1, int x2, int y2)
{
    // tag=1000

    // tag=1004
    ::QRect::adjust(x1, y1, x2, y2);
}
QRect QRect_wrapper::adjusted(int x1, int y1, int x2, int y2) const
{
    // tag=1000

    // tag=1004
    return ::QRect::adjusted(x1, y1, x2, y2);
}
int QRect_wrapper::bottom() const
{
    // tag=1000

    // tag=1004
    return ::QRect::bottom();
}
QPoint QRect_wrapper::bottomLeft() const
{
    // tag=1000

    // tag=1004
    return ::QRect::bottomLeft();
}
QPoint QRect_wrapper::bottomRight() const
{
    // tag=1000

    // tag=1004
    return ::QRect::bottomRight();
}
QPoint QRect_wrapper::center() const
{
    // tag=1000

    // tag=1004
    return ::QRect::center();
}
bool QRect_wrapper::contains(const QPoint &p, bool proper) const
{
    // tag=1000

    // tag=1004
    return ::QRect::contains(p, proper);
}
bool QRect_wrapper::contains(const QRect &r, bool proper) const
{
    // tag=1000

    // tag=1004
    return ::QRect::contains(r, proper);
}
bool QRect_wrapper::contains(int x, int y) const
{
    // tag=1000

    // tag=1004
    return ::QRect::contains(x, y);
}
bool QRect_wrapper::contains(int x, int y, bool proper) const
{
    // tag=1000

    // tag=1004
    return ::QRect::contains(x, y, proper);
}
int QRect_wrapper::height() const
{
    // tag=1000

    // tag=1004
    return ::QRect::height();
}
QRect QRect_wrapper::intersected(const QRect &other) const
{
    // tag=1000

    // tag=1004
    return ::QRect::intersected(other);
}
bool QRect_wrapper::intersects(const QRect &r) const
{
    // tag=1000

    // tag=1004
    return ::QRect::intersects(r);
}
bool QRect_wrapper::isEmpty() const
{
    // tag=1000

    // tag=1004
    return ::QRect::isEmpty();
}
bool QRect_wrapper::isNull() const
{
    // tag=1000

    // tag=1004
    return ::QRect::isNull();
}
bool QRect_wrapper::isValid() const
{
    // tag=1000

    // tag=1004
    return ::QRect::isValid();
}
int QRect_wrapper::left() const
{
    // tag=1000

    // tag=1004
    return ::QRect::left();
}
void QRect_wrapper::moveBottom(int pos)
{
    // tag=1000

    // tag=1004
    ::QRect::moveBottom(pos);
}
void QRect_wrapper::moveBottomLeft(const QPoint &p)
{
    // tag=1000

    // tag=1004
    ::QRect::moveBottomLeft(p);
}
void QRect_wrapper::moveBottomRight(const QPoint &p)
{
    // tag=1000

    // tag=1004
    ::QRect::moveBottomRight(p);
}
void QRect_wrapper::moveCenter(const QPoint &p)
{
    // tag=1000

    // tag=1004
    ::QRect::moveCenter(p);
}
void QRect_wrapper::moveLeft(int pos)
{
    // tag=1000

    // tag=1004
    ::QRect::moveLeft(pos);
}
void QRect_wrapper::moveRight(int pos)
{
    // tag=1000

    // tag=1004
    ::QRect::moveRight(pos);
}
void QRect_wrapper::moveTo(const QPoint &p)
{
    // tag=1000

    // tag=1004
    ::QRect::moveTo(p);
}
void QRect_wrapper::moveTo(int x, int t)
{
    // tag=1000

    // tag=1004
    ::QRect::moveTo(x, t);
}
void QRect_wrapper::moveTop(int pos)
{
    // tag=1000

    // tag=1004
    ::QRect::moveTop(pos);
}
void QRect_wrapper::moveTopLeft(const QPoint &p)
{
    // tag=1000

    // tag=1004
    ::QRect::moveTopLeft(p);
}
void QRect_wrapper::moveTopRight(const QPoint &p)
{
    // tag=1000

    // tag=1004
    ::QRect::moveTopRight(p);
}
QRect QRect_wrapper::normalized() const
{
    // tag=1000

    // tag=1004
    return ::QRect::normalized();
}
int QRect_wrapper::right() const
{
    // tag=1000

    // tag=1004
    return ::QRect::right();
}
void QRect_wrapper::setBottom(int pos)
{
    // tag=1000

    // tag=1004
    ::QRect::setBottom(pos);
}
void QRect_wrapper::setBottomLeft(const QPoint &p)
{
    // tag=1000

    // tag=1004
    ::QRect::setBottomLeft(p);
}
void QRect_wrapper::setBottomRight(const QPoint &p)
{
    // tag=1000

    // tag=1004
    ::QRect::setBottomRight(p);
}
void QRect_wrapper::setCoords(int x1, int y1, int x2, int y2)
{
    // tag=1000

    // tag=1004
    ::QRect::setCoords(x1, y1, x2, y2);
}
void QRect_wrapper::setHeight(int h)
{
    // tag=1000

    // tag=1004
    ::QRect::setHeight(h);
}
void QRect_wrapper::setLeft(int pos)
{
    // tag=1000

    // tag=1004
    ::QRect::setLeft(pos);
}
void QRect_wrapper::setRect(int x, int y, int w, int h)
{
    // tag=1000

    // tag=1004
    ::QRect::setRect(x, y, w, h);
}
void QRect_wrapper::setRight(int pos)
{
    // tag=1000

    // tag=1004
    ::QRect::setRight(pos);
}
void QRect_wrapper::setSize(const QSize &s)
{
    // tag=1000

    // tag=1004
    ::QRect::setSize(s);
}
void QRect_wrapper::setTop(int pos)
{
    // tag=1000

    // tag=1004
    ::QRect::setTop(pos);
}
void QRect_wrapper::setTopLeft(const QPoint &p)
{
    // tag=1000

    // tag=1004
    ::QRect::setTopLeft(p);
}
void QRect_wrapper::setTopRight(const QPoint &p)
{
    // tag=1000

    // tag=1004
    ::QRect::setTopRight(p);
}
void QRect_wrapper::setWidth(int w)
{
    // tag=1000

    // tag=1004
    ::QRect::setWidth(w);
}
void QRect_wrapper::setX(int x)
{
    // tag=1000

    // tag=1004
    ::QRect::setX(x);
}
void QRect_wrapper::setY(int y)
{
    // tag=1000

    // tag=1004
    ::QRect::setY(y);
}
QSize QRect_wrapper::size() const
{
    // tag=1000

    // tag=1004
    return ::QRect::size();
}
int QRect_wrapper::top() const
{
    // tag=1000

    // tag=1004
    return ::QRect::top();
}
QPoint QRect_wrapper::topLeft() const
{
    // tag=1000

    // tag=1004
    return ::QRect::topLeft();
}
QPoint QRect_wrapper::topRight() const
{
    // tag=1000

    // tag=1004
    return ::QRect::topRight();
}
void QRect_wrapper::translate(const QPoint &p)
{
    // tag=1000

    // tag=1004
    ::QRect::translate(p);
}
void QRect_wrapper::translate(int dx, int dy)
{
    // tag=1000

    // tag=1004
    ::QRect::translate(dx, dy);
}
QRect QRect_wrapper::translated(const QPoint &p) const
{
    // tag=1000

    // tag=1004
    return ::QRect::translated(p);
}
QRect QRect_wrapper::translated(int dx, int dy) const
{
    // tag=1000

    // tag=1004
    return ::QRect::translated(dx, dy);
}
QRect QRect_wrapper::transposed() const
{
    // tag=1000

    // tag=1004
    return ::QRect::transposed();
}
QRect QRect_wrapper::united(const QRect &other) const
{
    // tag=1000

    // tag=1004
    return ::QRect::united(other);
}
int QRect_wrapper::width() const
{
    // tag=1000

    // tag=1004
    return ::QRect::width();
}
int QRect_wrapper::x() const
{
    // tag=1000

    // tag=1004
    return ::QRect::x();
}
int QRect_wrapper::y() const
{
    // tag=1000

    // tag=1004
    return ::QRect::y();
}

// tag=1005
QRect_wrapper::~QRect_wrapper()
{
}

}
// tag=1013
static QRect *fromPtr(void *ptr)
{
    return reinterpret_cast<QRect *>(ptr);
}
// tag=1014
static KDDockWidgets_wrappersNS::QRect_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets_wrappersNS::QRect_wrapper *>(ptr);
}
extern "C" {

// tag=1049
void c_QRect_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgets_wrappersNS::QRect_wrapper *>(cppObj);
}
void *c_QRect__constructor()
{

    // tag=1056
    auto ptr = new KDDockWidgets_wrappersNS::QRect_wrapper();
    return reinterpret_cast<void *>(ptr);
}
void *c_QRect__constructor_QPoint_QPoint(void *topleft_, void *bottomright_)
{
    auto &topleft = *reinterpret_cast<QPoint *>(topleft_);
    auto &bottomright = *reinterpret_cast<QPoint *>(bottomright_);
    // tag=1056
    auto ptr = new KDDockWidgets_wrappersNS::QRect_wrapper(topleft, bottomright);
    return reinterpret_cast<void *>(ptr);
}
void *c_QRect__constructor_QPoint_QSize(void *topleft_, void *size_)
{
    auto &topleft = *reinterpret_cast<QPoint *>(topleft_);
    auto &size = *reinterpret_cast<QSize *>(size_);
    // tag=1056
    auto ptr = new KDDockWidgets_wrappersNS::QRect_wrapper(topleft, size);
    return reinterpret_cast<void *>(ptr);
}
void *c_QRect__constructor_int_int_int_int(int left, int top, int width, int height)
{

    // tag=1056
    auto ptr = new KDDockWidgets_wrappersNS::QRect_wrapper(left, top, width, height);
    return reinterpret_cast<void *>(ptr);
}

// tag=1050
// adjust(int x1, int y1, int x2, int y2)
void c_QRect__adjust_int_int_int_int(void *thisObj, int x1, int y1, int x2, int y2)
{
    // tag=1010
    fromPtr(thisObj)->adjust(x1, y1, x2, y2);
}

// tag=1050
// adjusted(int x1, int y1, int x2, int y2) const
void *c_QRect__adjusted_int_int_int_int(void *thisObj, int x1, int y1, int x2, int y2)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QRect> { fromPtr(thisObj)->adjusted(x1, y1, x2, y2) };
}

// tag=1050
// bottom() const
int c_QRect__bottom(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->bottom();
}

// tag=1050
// bottomLeft() const
void *c_QRect__bottomLeft(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QPoint> { fromPtr(thisObj)->bottomLeft() };
}

// tag=1050
// bottomRight() const
void *c_QRect__bottomRight(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QPoint> { fromPtr(thisObj)->bottomRight() };
}

// tag=1050
// center() const
void *c_QRect__center(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QPoint> { fromPtr(thisObj)->center() };
}

// tag=1050
// contains(const QPoint & p, bool proper) const
bool c_QRect__contains_QPoint_bool(void *thisObj, void *p_, bool proper)
{
    auto &p = *reinterpret_cast<QPoint *>(p_);
    return
        // tag=1010
        fromPtr(thisObj)->contains(p, proper);
}

// tag=1050
// contains(const QRect & r, bool proper) const
bool c_QRect__contains_QRect_bool(void *thisObj, void *r_, bool proper)
{
    auto &r = *reinterpret_cast<QRect *>(r_);
    return
        // tag=1010
        fromPtr(thisObj)->contains(r, proper);
}

// tag=1050
// contains(int x, int y) const
bool c_QRect__contains_int_int(void *thisObj, int x, int y)
{
    return
        // tag=1010
        fromPtr(thisObj)->contains(x, y);
}

// tag=1050
// contains(int x, int y, bool proper) const
bool c_QRect__contains_int_int_bool(void *thisObj, int x, int y, bool proper)
{
    return
        // tag=1010
        fromPtr(thisObj)->contains(x, y, proper);
}

// tag=1050
// height() const
int c_QRect__height(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->height();
}

// tag=1050
// intersected(const QRect & other) const
void *c_QRect__intersected_QRect(void *thisObj, void *other_)
{
    auto &other = *reinterpret_cast<QRect *>(other_);
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QRect> { fromPtr(thisObj)->intersected(other) };
}

// tag=1050
// intersects(const QRect & r) const
bool c_QRect__intersects_QRect(void *thisObj, void *r_)
{
    auto &r = *reinterpret_cast<QRect *>(r_);
    return
        // tag=1010
        fromPtr(thisObj)->intersects(r);
}

// tag=1050
// isEmpty() const
bool c_QRect__isEmpty(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->isEmpty();
}

// tag=1050
// isNull() const
bool c_QRect__isNull(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->isNull();
}

// tag=1050
// isValid() const
bool c_QRect__isValid(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->isValid();
}

// tag=1050
// left() const
int c_QRect__left(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->left();
}

// tag=1050
// moveBottom(int pos)
void c_QRect__moveBottom_int(void *thisObj, int pos)
{
    // tag=1010
    fromPtr(thisObj)->moveBottom(pos);
}

// tag=1050
// moveBottomLeft(const QPoint & p)
void c_QRect__moveBottomLeft_QPoint(void *thisObj, void *p_)
{
    auto &p = *reinterpret_cast<QPoint *>(p_);
    // tag=1010
    fromPtr(thisObj)->moveBottomLeft(p);
}

// tag=1050
// moveBottomRight(const QPoint & p)
void c_QRect__moveBottomRight_QPoint(void *thisObj, void *p_)
{
    auto &p = *reinterpret_cast<QPoint *>(p_);
    // tag=1010
    fromPtr(thisObj)->moveBottomRight(p);
}

// tag=1050
// moveCenter(const QPoint & p)
void c_QRect__moveCenter_QPoint(void *thisObj, void *p_)
{
    auto &p = *reinterpret_cast<QPoint *>(p_);
    // tag=1010
    fromPtr(thisObj)->moveCenter(p);
}

// tag=1050
// moveLeft(int pos)
void c_QRect__moveLeft_int(void *thisObj, int pos)
{
    // tag=1010
    fromPtr(thisObj)->moveLeft(pos);
}

// tag=1050
// moveRight(int pos)
void c_QRect__moveRight_int(void *thisObj, int pos)
{
    // tag=1010
    fromPtr(thisObj)->moveRight(pos);
}

// tag=1050
// moveTo(const QPoint & p)
void c_QRect__moveTo_QPoint(void *thisObj, void *p_)
{
    auto &p = *reinterpret_cast<QPoint *>(p_);
    // tag=1010
    fromPtr(thisObj)->moveTo(p);
}

// tag=1050
// moveTo(int x, int t)
void c_QRect__moveTo_int_int(void *thisObj, int x, int t)
{
    // tag=1010
    fromPtr(thisObj)->moveTo(x, t);
}

// tag=1050
// moveTop(int pos)
void c_QRect__moveTop_int(void *thisObj, int pos)
{
    // tag=1010
    fromPtr(thisObj)->moveTop(pos);
}

// tag=1050
// moveTopLeft(const QPoint & p)
void c_QRect__moveTopLeft_QPoint(void *thisObj, void *p_)
{
    auto &p = *reinterpret_cast<QPoint *>(p_);
    // tag=1010
    fromPtr(thisObj)->moveTopLeft(p);
}

// tag=1050
// moveTopRight(const QPoint & p)
void c_QRect__moveTopRight_QPoint(void *thisObj, void *p_)
{
    auto &p = *reinterpret_cast<QPoint *>(p_);
    // tag=1010
    fromPtr(thisObj)->moveTopRight(p);
}

// tag=1050
// normalized() const
void *c_QRect__normalized(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QRect> { fromPtr(thisObj)->normalized() };
}

// tag=1050
// right() const
int c_QRect__right(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->right();
}

// tag=1050
// setBottom(int pos)
void c_QRect__setBottom_int(void *thisObj, int pos)
{
    // tag=1010
    fromPtr(thisObj)->setBottom(pos);
}

// tag=1050
// setBottomLeft(const QPoint & p)
void c_QRect__setBottomLeft_QPoint(void *thisObj, void *p_)
{
    auto &p = *reinterpret_cast<QPoint *>(p_);
    // tag=1010
    fromPtr(thisObj)->setBottomLeft(p);
}

// tag=1050
// setBottomRight(const QPoint & p)
void c_QRect__setBottomRight_QPoint(void *thisObj, void *p_)
{
    auto &p = *reinterpret_cast<QPoint *>(p_);
    // tag=1010
    fromPtr(thisObj)->setBottomRight(p);
}

// tag=1050
// setCoords(int x1, int y1, int x2, int y2)
void c_QRect__setCoords_int_int_int_int(void *thisObj, int x1, int y1, int x2, int y2)
{
    // tag=1010
    fromPtr(thisObj)->setCoords(x1, y1, x2, y2);
}

// tag=1050
// setHeight(int h)
void c_QRect__setHeight_int(void *thisObj, int h)
{
    // tag=1010
    fromPtr(thisObj)->setHeight(h);
}

// tag=1050
// setLeft(int pos)
void c_QRect__setLeft_int(void *thisObj, int pos)
{
    // tag=1010
    fromPtr(thisObj)->setLeft(pos);
}

// tag=1050
// setRect(int x, int y, int w, int h)
void c_QRect__setRect_int_int_int_int(void *thisObj, int x, int y, int w, int h)
{
    // tag=1010
    fromPtr(thisObj)->setRect(x, y, w, h);
}

// tag=1050
// setRight(int pos)
void c_QRect__setRight_int(void *thisObj, int pos)
{
    // tag=1010
    fromPtr(thisObj)->setRight(pos);
}

// tag=1050
// setSize(const QSize & s)
void c_QRect__setSize_QSize(void *thisObj, void *s_)
{
    auto &s = *reinterpret_cast<QSize *>(s_);
    // tag=1010
    fromPtr(thisObj)->setSize(s);
}

// tag=1050
// setTop(int pos)
void c_QRect__setTop_int(void *thisObj, int pos)
{
    // tag=1010
    fromPtr(thisObj)->setTop(pos);
}

// tag=1050
// setTopLeft(const QPoint & p)
void c_QRect__setTopLeft_QPoint(void *thisObj, void *p_)
{
    auto &p = *reinterpret_cast<QPoint *>(p_);
    // tag=1010
    fromPtr(thisObj)->setTopLeft(p);
}

// tag=1050
// setTopRight(const QPoint & p)
void c_QRect__setTopRight_QPoint(void *thisObj, void *p_)
{
    auto &p = *reinterpret_cast<QPoint *>(p_);
    // tag=1010
    fromPtr(thisObj)->setTopRight(p);
}

// tag=1050
// setWidth(int w)
void c_QRect__setWidth_int(void *thisObj, int w)
{
    // tag=1010
    fromPtr(thisObj)->setWidth(w);
}

// tag=1050
// setX(int x)
void c_QRect__setX_int(void *thisObj, int x)
{
    // tag=1010
    fromPtr(thisObj)->setX(x);
}

// tag=1050
// setY(int y)
void c_QRect__setY_int(void *thisObj, int y)
{
    // tag=1010
    fromPtr(thisObj)->setY(y);
}

// tag=1050
// size() const
void *c_QRect__size(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QSize> { fromPtr(thisObj)->size() };
}

// tag=1050
// top() const
int c_QRect__top(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->top();
}

// tag=1050
// topLeft() const
void *c_QRect__topLeft(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QPoint> { fromPtr(thisObj)->topLeft() };
}

// tag=1050
// topRight() const
void *c_QRect__topRight(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QPoint> { fromPtr(thisObj)->topRight() };
}

// tag=1050
// translate(const QPoint & p)
void c_QRect__translate_QPoint(void *thisObj, void *p_)
{
    auto &p = *reinterpret_cast<QPoint *>(p_);
    // tag=1010
    fromPtr(thisObj)->translate(p);
}

// tag=1050
// translate(int dx, int dy)
void c_QRect__translate_int_int(void *thisObj, int dx, int dy)
{
    // tag=1010
    fromPtr(thisObj)->translate(dx, dy);
}

// tag=1050
// translated(const QPoint & p) const
void *c_QRect__translated_QPoint(void *thisObj, void *p_)
{
    auto &p = *reinterpret_cast<QPoint *>(p_);
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QRect> { fromPtr(thisObj)->translated(p) };
}

// tag=1050
// translated(int dx, int dy) const
void *c_QRect__translated_int_int(void *thisObj, int dx, int dy)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QRect> { fromPtr(thisObj)->translated(dx, dy) };
}

// tag=1050
// transposed() const
void *c_QRect__transposed(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QRect> { fromPtr(thisObj)->transposed() };
}

// tag=1050
// united(const QRect & other) const
void *c_QRect__united_QRect(void *thisObj, void *other_)
{
    auto &other = *reinterpret_cast<QRect *>(other_);
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QRect> { fromPtr(thisObj)->united(other) };
}

// tag=1050
// width() const
int c_QRect__width(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->width();
}

// tag=1050
// x() const
int c_QRect__x(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->x();
}

// tag=1050
// y() const
int c_QRect__y(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->y();
}
void c_QRect__destructor(void *thisObj)
{

    // tag=1055
    delete fromPtr(thisObj);
}
}

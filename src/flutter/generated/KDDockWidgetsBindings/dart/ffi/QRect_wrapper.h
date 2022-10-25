/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <qrect.h>
#include <qpoint.h>
#include <qsize.h>

namespace KDDockWidgetsBindings_wrappersNS {
class QRect_wrapper : public ::QRect
{
public:
    ~QRect_wrapper();
    QRect_wrapper();
    QRect_wrapper(const QPoint &topleft, const QPoint &bottomright);
    QRect_wrapper(const QPoint &topleft, const QSize &size);
    QRect_wrapper(int left, int top, int width, int height);
    void adjust(int x1, int y1, int x2, int y2);
    QRect adjusted(int x1, int y1, int x2, int y2) const;
    int bottom() const;
    QPoint bottomLeft() const;
    QPoint bottomRight() const;
    QPoint center() const;
    bool contains(const QPoint &p, bool proper = false) const;
    bool contains(const QRect &r, bool proper = false) const;
    bool contains(int x, int y) const;
    bool contains(int x, int y, bool proper) const;
    int height() const;
    QRect intersected(const QRect &other) const;
    bool intersects(const QRect &r) const;
    bool isEmpty() const;
    bool isNull() const;
    bool isValid() const;
    int left() const;
    void moveBottom(int pos);
    void moveBottomLeft(const QPoint &p);
    void moveBottomRight(const QPoint &p);
    void moveCenter(const QPoint &p);
    void moveLeft(int pos);
    void moveRight(int pos);
    void moveTo(const QPoint &p);
    void moveTo(int x, int t);
    void moveTop(int pos);
    void moveTopLeft(const QPoint &p);
    void moveTopRight(const QPoint &p);
    QRect normalized() const;
    int right() const;
    void setBottom(int pos);
    void setBottomLeft(const QPoint &p);
    void setBottomRight(const QPoint &p);
    void setCoords(int x1, int y1, int x2, int y2);
    void setHeight(int h);
    void setLeft(int pos);
    void setRect(int x, int y, int w, int h);
    void setRight(int pos);
    void setSize(const QSize &s);
    void setTop(int pos);
    void setTopLeft(const QPoint &p);
    void setTopRight(const QPoint &p);
    void setWidth(int w);
    void setX(int x);
    void setY(int y);
    QSize size() const;
    int top() const;
    QPoint topLeft() const;
    QPoint topRight() const;
    void translate(const QPoint &p);
    void translate(int dx, int dy);
    QRect translated(const QPoint &p) const;
    QRect translated(int dx, int dy) const;
    QRect transposed() const;
    QRect united(const QRect &other) const;
    int width() const;
    int x() const;
    int y() const;
};
}
extern "C" {
// QRect::QRect()
KDDockWidgetsBindings_EXPORT void *c_QRect__constructor();
// QRect::QRect(const QPoint & topleft, const QPoint & bottomright)
KDDockWidgetsBindings_EXPORT void *c_QRect__constructor_QPoint_QPoint(void *topleft_,
                                                                      void *bottomright_);
// QRect::QRect(const QPoint & topleft, const QSize & size)
KDDockWidgetsBindings_EXPORT void *c_QRect__constructor_QPoint_QSize(void *topleft_, void *size_);
// QRect::QRect(int left, int top, int width, int height)
KDDockWidgetsBindings_EXPORT void *c_QRect__constructor_int_int_int_int(int left, int top,
                                                                        int width, int height);
// QRect::adjust(int x1, int y1, int x2, int y2)
KDDockWidgetsBindings_EXPORT void c_QRect__adjust_int_int_int_int(void *thisObj, int x1, int y1,
                                                                  int x2, int y2);
// QRect::adjusted(int x1, int y1, int x2, int y2) const
KDDockWidgetsBindings_EXPORT void *c_QRect__adjusted_int_int_int_int(void *thisObj, int x1, int y1,
                                                                     int x2, int y2);
// QRect::bottom() const
KDDockWidgetsBindings_EXPORT int c_QRect__bottom(void *thisObj);
// QRect::bottomLeft() const
KDDockWidgetsBindings_EXPORT void *c_QRect__bottomLeft(void *thisObj);
// QRect::bottomRight() const
KDDockWidgetsBindings_EXPORT void *c_QRect__bottomRight(void *thisObj);
// QRect::center() const
KDDockWidgetsBindings_EXPORT void *c_QRect__center(void *thisObj);
// QRect::contains(const QPoint & p, bool proper) const
KDDockWidgetsBindings_EXPORT bool c_QRect__contains_QPoint_bool(void *thisObj, void *p_,
                                                                bool proper);
// QRect::contains(const QRect & r, bool proper) const
KDDockWidgetsBindings_EXPORT bool c_QRect__contains_QRect_bool(void *thisObj, void *r_,
                                                               bool proper);
// QRect::contains(int x, int y) const
KDDockWidgetsBindings_EXPORT bool c_QRect__contains_int_int(void *thisObj, int x, int y);
// QRect::contains(int x, int y, bool proper) const
KDDockWidgetsBindings_EXPORT bool c_QRect__contains_int_int_bool(void *thisObj, int x, int y,
                                                                 bool proper);
// QRect::height() const
KDDockWidgetsBindings_EXPORT int c_QRect__height(void *thisObj);
// QRect::intersected(const QRect & other) const
KDDockWidgetsBindings_EXPORT void *c_QRect__intersected_QRect(void *thisObj, void *other_);
// QRect::intersects(const QRect & r) const
KDDockWidgetsBindings_EXPORT bool c_QRect__intersects_QRect(void *thisObj, void *r_);
// QRect::isEmpty() const
KDDockWidgetsBindings_EXPORT bool c_QRect__isEmpty(void *thisObj);
// QRect::isNull() const
KDDockWidgetsBindings_EXPORT bool c_QRect__isNull(void *thisObj);
// QRect::isValid() const
KDDockWidgetsBindings_EXPORT bool c_QRect__isValid(void *thisObj);
// QRect::left() const
KDDockWidgetsBindings_EXPORT int c_QRect__left(void *thisObj);
// QRect::moveBottom(int pos)
KDDockWidgetsBindings_EXPORT void c_QRect__moveBottom_int(void *thisObj, int pos);
// QRect::moveBottomLeft(const QPoint & p)
KDDockWidgetsBindings_EXPORT void c_QRect__moveBottomLeft_QPoint(void *thisObj, void *p_);
// QRect::moveBottomRight(const QPoint & p)
KDDockWidgetsBindings_EXPORT void c_QRect__moveBottomRight_QPoint(void *thisObj, void *p_);
// QRect::moveCenter(const QPoint & p)
KDDockWidgetsBindings_EXPORT void c_QRect__moveCenter_QPoint(void *thisObj, void *p_);
// QRect::moveLeft(int pos)
KDDockWidgetsBindings_EXPORT void c_QRect__moveLeft_int(void *thisObj, int pos);
// QRect::moveRight(int pos)
KDDockWidgetsBindings_EXPORT void c_QRect__moveRight_int(void *thisObj, int pos);
// QRect::moveTo(const QPoint & p)
KDDockWidgetsBindings_EXPORT void c_QRect__moveTo_QPoint(void *thisObj, void *p_);
// QRect::moveTo(int x, int t)
KDDockWidgetsBindings_EXPORT void c_QRect__moveTo_int_int(void *thisObj, int x, int t);
// QRect::moveTop(int pos)
KDDockWidgetsBindings_EXPORT void c_QRect__moveTop_int(void *thisObj, int pos);
// QRect::moveTopLeft(const QPoint & p)
KDDockWidgetsBindings_EXPORT void c_QRect__moveTopLeft_QPoint(void *thisObj, void *p_);
// QRect::moveTopRight(const QPoint & p)
KDDockWidgetsBindings_EXPORT void c_QRect__moveTopRight_QPoint(void *thisObj, void *p_);
// QRect::normalized() const
KDDockWidgetsBindings_EXPORT void *c_QRect__normalized(void *thisObj);
// QRect::right() const
KDDockWidgetsBindings_EXPORT int c_QRect__right(void *thisObj);
// QRect::setBottom(int pos)
KDDockWidgetsBindings_EXPORT void c_QRect__setBottom_int(void *thisObj, int pos);
// QRect::setBottomLeft(const QPoint & p)
KDDockWidgetsBindings_EXPORT void c_QRect__setBottomLeft_QPoint(void *thisObj, void *p_);
// QRect::setBottomRight(const QPoint & p)
KDDockWidgetsBindings_EXPORT void c_QRect__setBottomRight_QPoint(void *thisObj, void *p_);
// QRect::setCoords(int x1, int y1, int x2, int y2)
KDDockWidgetsBindings_EXPORT void c_QRect__setCoords_int_int_int_int(void *thisObj, int x1, int y1,
                                                                     int x2, int y2);
// QRect::setHeight(int h)
KDDockWidgetsBindings_EXPORT void c_QRect__setHeight_int(void *thisObj, int h);
// QRect::setLeft(int pos)
KDDockWidgetsBindings_EXPORT void c_QRect__setLeft_int(void *thisObj, int pos);
// QRect::setRect(int x, int y, int w, int h)
KDDockWidgetsBindings_EXPORT void c_QRect__setRect_int_int_int_int(void *thisObj, int x, int y,
                                                                   int w, int h);
// QRect::setRight(int pos)
KDDockWidgetsBindings_EXPORT void c_QRect__setRight_int(void *thisObj, int pos);
// QRect::setSize(const QSize & s)
KDDockWidgetsBindings_EXPORT void c_QRect__setSize_QSize(void *thisObj, void *s_);
// QRect::setTop(int pos)
KDDockWidgetsBindings_EXPORT void c_QRect__setTop_int(void *thisObj, int pos);
// QRect::setTopLeft(const QPoint & p)
KDDockWidgetsBindings_EXPORT void c_QRect__setTopLeft_QPoint(void *thisObj, void *p_);
// QRect::setTopRight(const QPoint & p)
KDDockWidgetsBindings_EXPORT void c_QRect__setTopRight_QPoint(void *thisObj, void *p_);
// QRect::setWidth(int w)
KDDockWidgetsBindings_EXPORT void c_QRect__setWidth_int(void *thisObj, int w);
// QRect::setX(int x)
KDDockWidgetsBindings_EXPORT void c_QRect__setX_int(void *thisObj, int x);
// QRect::setY(int y)
KDDockWidgetsBindings_EXPORT void c_QRect__setY_int(void *thisObj, int y);
// QRect::size() const
KDDockWidgetsBindings_EXPORT void *c_QRect__size(void *thisObj);
// QRect::top() const
KDDockWidgetsBindings_EXPORT int c_QRect__top(void *thisObj);
// QRect::topLeft() const
KDDockWidgetsBindings_EXPORT void *c_QRect__topLeft(void *thisObj);
// QRect::topRight() const
KDDockWidgetsBindings_EXPORT void *c_QRect__topRight(void *thisObj);
// QRect::translate(const QPoint & p)
KDDockWidgetsBindings_EXPORT void c_QRect__translate_QPoint(void *thisObj, void *p_);
// QRect::translate(int dx, int dy)
KDDockWidgetsBindings_EXPORT void c_QRect__translate_int_int(void *thisObj, int dx, int dy);
// QRect::translated(const QPoint & p) const
KDDockWidgetsBindings_EXPORT void *c_QRect__translated_QPoint(void *thisObj, void *p_);
// QRect::translated(int dx, int dy) const
KDDockWidgetsBindings_EXPORT void *c_QRect__translated_int_int(void *thisObj, int dx, int dy);
// QRect::transposed() const
KDDockWidgetsBindings_EXPORT void *c_QRect__transposed(void *thisObj);
// QRect::united(const QRect & other) const
KDDockWidgetsBindings_EXPORT void *c_QRect__united_QRect(void *thisObj, void *other_);
// QRect::width() const
KDDockWidgetsBindings_EXPORT int c_QRect__width(void *thisObj);
// QRect::x() const
KDDockWidgetsBindings_EXPORT int c_QRect__x(void *thisObj);
// QRect::y() const
KDDockWidgetsBindings_EXPORT int c_QRect__y(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_QRect__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_QRect_Finalizer(void *, void *cppObj, void *);
}

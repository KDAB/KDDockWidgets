/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <core/geometry_helpers_p.h>

namespace KDDockWidgetsBindings_wrappersNS {
class Rect_wrapper : public ::KDDockWidgets::Rect
{
public:
    ~Rect_wrapper();
    Rect_wrapper();
    Rect_wrapper(KDDockWidgets::Point pos, KDDockWidgets::Size size);
    Rect_wrapper(int x, int y, int width, int height);
    void adjust(int l, int t, int r, int b);
    KDDockWidgets::Rect adjusted(int l, int t, int r, int b) const;
    int bottom() const;
    KDDockWidgets::Point bottomLeft() const;
    KDDockWidgets::Point bottomRight() const;
    KDDockWidgets::Point center() const;
    bool contains(KDDockWidgets::Point pt) const;
    bool contains(KDDockWidgets::Rect other) const;
    int height() const;
    KDDockWidgets::Rect intersected(KDDockWidgets::Rect other) const;
    bool intersects(KDDockWidgets::Rect other) const;
    bool isEmpty() const;
    bool isNull() const;
    bool isValid() const;
    int left() const;
    void moveBottom(int b);
    void moveCenter(KDDockWidgets::Point pt);
    void moveLeft(int x);
    void moveRight(int r);
    void moveTo(KDDockWidgets::Point pt);
    void moveTo(int x, int y);
    void moveTop(int y);
    void moveTopLeft(KDDockWidgets::Point pt);
    KDDockWidgets::Point pos() const;
    int right() const;
    void setBottom(int b);
    void setHeight(int h);
    void setLeft(int x);
    void setRight(int r);
    void setSize(KDDockWidgets::Size sz);
    void setTop(int y);
    void setTopLeft(KDDockWidgets::Point pt);
    void setWidth(int w);
    void setX(int x);
    void setY(int y);
    KDDockWidgets::Size size() const;
    int top() const;
    KDDockWidgets::Point topLeft() const;
    KDDockWidgets::Point topRight() const;
    void translate(KDDockWidgets::Point pt);
    int width() const;
    int x() const;
    int y() const;
};
}
extern "C" {
// KDDockWidgets::Rect::Rect()
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Rect__constructor();
// KDDockWidgets::Rect::Rect(KDDockWidgets::Point pos, KDDockWidgets::Size size)
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Rect__constructor_Point_Size(void *pos_, void *size_);
// KDDockWidgets::Rect::Rect(int x, int y, int width, int height)
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Rect__constructor_int_int_int_int(int x, int y, int width, int height);
// KDDockWidgets::Rect::adjust(int l, int t, int r, int b)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__adjust_int_int_int_int(void *thisObj, int l, int t, int r, int b);
// KDDockWidgets::Rect::adjusted(int l, int t, int r, int b) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Rect__adjusted_int_int_int_int(void *thisObj, int l, int t, int r, int b);
// KDDockWidgets::Rect::bottom() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Rect__bottom(void *thisObj);
// KDDockWidgets::Rect::bottomLeft() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Rect__bottomLeft(void *thisObj);
// KDDockWidgets::Rect::bottomRight() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Rect__bottomRight(void *thisObj);
// KDDockWidgets::Rect::center() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Rect__center(void *thisObj);
// KDDockWidgets::Rect::contains(KDDockWidgets::Point pt) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Rect__contains_Point(void *thisObj, void *pt_);
// KDDockWidgets::Rect::contains(KDDockWidgets::Rect other) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Rect__contains_Rect(void *thisObj, void *other_);
// KDDockWidgets::Rect::height() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Rect__height(void *thisObj);
// KDDockWidgets::Rect::intersected(KDDockWidgets::Rect other) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Rect__intersected_Rect(void *thisObj, void *other_);
// KDDockWidgets::Rect::intersects(KDDockWidgets::Rect other) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Rect__intersects_Rect(void *thisObj, void *other_);
// KDDockWidgets::Rect::isEmpty() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Rect__isEmpty(void *thisObj);
// KDDockWidgets::Rect::isNull() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Rect__isNull(void *thisObj);
// KDDockWidgets::Rect::isValid() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Rect__isValid(void *thisObj);
// KDDockWidgets::Rect::left() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Rect__left(void *thisObj);
// KDDockWidgets::Rect::moveBottom(int b)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__moveBottom_int(void *thisObj, int b);
// KDDockWidgets::Rect::moveCenter(KDDockWidgets::Point pt)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__moveCenter_Point(void *thisObj, void *pt_);
// KDDockWidgets::Rect::moveLeft(int x)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__moveLeft_int(void *thisObj, int x);
// KDDockWidgets::Rect::moveRight(int r)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__moveRight_int(void *thisObj, int r);
// KDDockWidgets::Rect::moveTo(KDDockWidgets::Point pt)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__moveTo_Point(void *thisObj, void *pt_);
// KDDockWidgets::Rect::moveTo(int x, int y)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__moveTo_int_int(void *thisObj, int x, int y);
// KDDockWidgets::Rect::moveTop(int y)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__moveTop_int(void *thisObj, int y);
// KDDockWidgets::Rect::moveTopLeft(KDDockWidgets::Point pt)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__moveTopLeft_Point(void *thisObj, void *pt_);
// KDDockWidgets::Rect::pos() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Rect__pos(void *thisObj);
// KDDockWidgets::Rect::right() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Rect__right(void *thisObj);
// KDDockWidgets::Rect::setBottom(int b)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__setBottom_int(void *thisObj, int b);
// KDDockWidgets::Rect::setHeight(int h)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__setHeight_int(void *thisObj, int h);
// KDDockWidgets::Rect::setLeft(int x)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__setLeft_int(void *thisObj, int x);
// KDDockWidgets::Rect::setRight(int r)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__setRight_int(void *thisObj, int r);
// KDDockWidgets::Rect::setSize(KDDockWidgets::Size sz)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__setSize_Size(void *thisObj, void *sz_);
// KDDockWidgets::Rect::setTop(int y)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__setTop_int(void *thisObj, int y);
// KDDockWidgets::Rect::setTopLeft(KDDockWidgets::Point pt)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__setTopLeft_Point(void *thisObj, void *pt_);
// KDDockWidgets::Rect::setWidth(int w)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__setWidth_int(void *thisObj, int w);
// KDDockWidgets::Rect::setX(int x)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__setX_int(void *thisObj, int x);
// KDDockWidgets::Rect::setY(int y)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__setY_int(void *thisObj, int y);
// KDDockWidgets::Rect::size() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Rect__size(void *thisObj);
// KDDockWidgets::Rect::top() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Rect__top(void *thisObj);
// KDDockWidgets::Rect::topLeft() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Rect__topLeft(void *thisObj);
// KDDockWidgets::Rect::topRight() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Rect__topRight(void *thisObj);
// KDDockWidgets::Rect::translate(KDDockWidgets::Point pt)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__translate_Point(void *thisObj, void *pt_);
// KDDockWidgets::Rect::width() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Rect__width(void *thisObj);
// KDDockWidgets::Rect::x() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Rect__x(void *thisObj);
// KDDockWidgets::Rect::y() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Rect__y(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect_Finalizer(void *cppObj);
}

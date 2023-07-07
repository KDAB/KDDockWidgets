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
    void adjust(int arg__1, int arg__2, int arg__3, int arg__4) const;
    KDDockWidgets::Rect adjusted(int arg__1, int arg__2, int arg__3, int arg__4) const;
    int bottom() const;
    KDDockWidgets::Point bottomLeft() const;
    KDDockWidgets::Point bottomRight() const;
    KDDockWidgets::Point center() const;
    bool contains(KDDockWidgets::Point pt) const;
    bool contains(KDDockWidgets::Rect arg__1) const;
    int height() const;
    KDDockWidgets::Rect intersected(KDDockWidgets::Rect arg__1) const;
    bool intersects(KDDockWidgets::Rect arg__1) const;
    bool isEmpty() const;
    bool isNull() const;
    bool isValid() const;
    int left() const;
    void moveBottom(int arg__1);
    void moveCenter(KDDockWidgets::Point arg__1);
    void moveLeft(int x);
    void moveRight(int arg__1);
    void moveTo(KDDockWidgets::Point arg__1);
    void moveTo(int arg__1, int arg__2);
    void moveTop(int y);
    void moveTopLeft(KDDockWidgets::Point pt);
    KDDockWidgets::Point pos() const;
    int right() const;
    void setBottom(int arg__1);
    void setHeight(int h);
    void setLeft(int x);
    void setRight(int r);
    void setSize(KDDockWidgets::Size sz);
    void setTop(int arg__1);
    void setTopLeft(KDDockWidgets::Point arg__1);
    void setWidth(int w);
    void setX(int arg__1);
    void setY(int arg__1);
    KDDockWidgets::Size size() const;
    int top() const;
    KDDockWidgets::Point topLeft() const;
    KDDockWidgets::Point topRight() const;
    void translate(KDDockWidgets::Point arg__1);
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
// KDDockWidgets::Rect::adjust(int arg__1, int arg__2, int arg__3, int arg__4) const
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__adjust_int_int_int_int(void *thisObj, int arg__1, int arg__2, int arg__3, int arg__4);
// KDDockWidgets::Rect::adjusted(int arg__1, int arg__2, int arg__3, int arg__4) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Rect__adjusted_int_int_int_int(void *thisObj, int arg__1, int arg__2, int arg__3, int arg__4);
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
// KDDockWidgets::Rect::contains(KDDockWidgets::Rect arg__1) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Rect__contains_Rect(void *thisObj, void *arg__1_);
// KDDockWidgets::Rect::height() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Rect__height(void *thisObj);
// KDDockWidgets::Rect::intersected(KDDockWidgets::Rect arg__1) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Rect__intersected_Rect(void *thisObj, void *arg__1_);
// KDDockWidgets::Rect::intersects(KDDockWidgets::Rect arg__1) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Rect__intersects_Rect(void *thisObj, void *arg__1_);
// KDDockWidgets::Rect::isEmpty() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Rect__isEmpty(void *thisObj);
// KDDockWidgets::Rect::isNull() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Rect__isNull(void *thisObj);
// KDDockWidgets::Rect::isValid() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Rect__isValid(void *thisObj);
// KDDockWidgets::Rect::left() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Rect__left(void *thisObj);
// KDDockWidgets::Rect::moveBottom(int arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__moveBottom_int(void *thisObj, int arg__1);
// KDDockWidgets::Rect::moveCenter(KDDockWidgets::Point arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__moveCenter_Point(void *thisObj, void *arg__1_);
// KDDockWidgets::Rect::moveLeft(int x)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__moveLeft_int(void *thisObj, int x);
// KDDockWidgets::Rect::moveRight(int arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__moveRight_int(void *thisObj, int arg__1);
// KDDockWidgets::Rect::moveTo(KDDockWidgets::Point arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__moveTo_Point(void *thisObj, void *arg__1_);
// KDDockWidgets::Rect::moveTo(int arg__1, int arg__2)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__moveTo_int_int(void *thisObj, int arg__1, int arg__2);
// KDDockWidgets::Rect::moveTop(int y)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__moveTop_int(void *thisObj, int y);
// KDDockWidgets::Rect::moveTopLeft(KDDockWidgets::Point pt)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__moveTopLeft_Point(void *thisObj, void *pt_);
// KDDockWidgets::Rect::pos() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Rect__pos(void *thisObj);
// KDDockWidgets::Rect::right() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Rect__right(void *thisObj);
// KDDockWidgets::Rect::setBottom(int arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__setBottom_int(void *thisObj, int arg__1);
// KDDockWidgets::Rect::setHeight(int h)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__setHeight_int(void *thisObj, int h);
// KDDockWidgets::Rect::setLeft(int x)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__setLeft_int(void *thisObj, int x);
// KDDockWidgets::Rect::setRight(int r)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__setRight_int(void *thisObj, int r);
// KDDockWidgets::Rect::setSize(KDDockWidgets::Size sz)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__setSize_Size(void *thisObj, void *sz_);
// KDDockWidgets::Rect::setTop(int arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__setTop_int(void *thisObj, int arg__1);
// KDDockWidgets::Rect::setTopLeft(KDDockWidgets::Point arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__setTopLeft_Point(void *thisObj, void *arg__1_);
// KDDockWidgets::Rect::setWidth(int w)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__setWidth_int(void *thisObj, int w);
// KDDockWidgets::Rect::setX(int arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__setX_int(void *thisObj, int arg__1);
// KDDockWidgets::Rect::setY(int arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__setY_int(void *thisObj, int arg__1);
// KDDockWidgets::Rect::size() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Rect__size(void *thisObj);
// KDDockWidgets::Rect::top() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Rect__top(void *thisObj);
// KDDockWidgets::Rect::topLeft() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Rect__topLeft(void *thisObj);
// KDDockWidgets::Rect::topRight() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Rect__topRight(void *thisObj);
// KDDockWidgets::Rect::translate(KDDockWidgets::Point arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__translate_Point(void *thisObj, void *arg__1_);
// KDDockWidgets::Rect::width() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Rect__width(void *thisObj);
// KDDockWidgets::Rect::x() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Rect__x(void *thisObj);
// KDDockWidgets::Rect::y() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Rect__y(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Rect_Finalizer(void *cppObj);
}

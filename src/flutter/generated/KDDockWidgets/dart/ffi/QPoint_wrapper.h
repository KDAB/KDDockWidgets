/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// tag=1040
#include "KDDockWidgets_exports.h"
#include <qpoint.h>

namespace KDDockWidgets_wrappersNS {
// tag=1043
class QPoint_wrapper : public ::QPoint
{
public:
    ~QPoint_wrapper();
    // tag=1041
    QPoint_wrapper();
    // tag=1041
    QPoint_wrapper(int xpos, int ypos);
    // tag=1041
    static int dotProduct(const QPoint &p1, const QPoint &p2);
    // tag=1041
    bool isNull() const;
    // tag=1041
    int manhattanLength() const;
    // tag=1041
    void setX(int x);
    // tag=1041
    void setY(int y);
    // tag=1041
    QPoint transposed() const;
    // tag=1041
    int x() const;
    // tag=1041
    int y() const;
};
}
extern "C" {

// tag=1067
//  QPoint::QPoint()
KDDockWidgets_EXPORT void *c_QPoint__constructor();

// tag=1067
//  QPoint::QPoint(int xpos, int ypos)
KDDockWidgets_EXPORT void *c_QPoint__constructor_int_int(int xpos, int ypos);

// tag=1067
//  QPoint::dotProduct(const QPoint & p1, const QPoint & p2)
KDDockWidgets_EXPORT int c_static_QPoint__dotProduct_QPoint_QPoint(void *p1_, void *p2_);

// tag=1067
//  QPoint::isNull() const
KDDockWidgets_EXPORT bool c_QPoint__isNull(void *thisObj);

// tag=1067
//  QPoint::manhattanLength() const
KDDockWidgets_EXPORT int c_QPoint__manhattanLength(void *thisObj);

// tag=1067
//  QPoint::setX(int x)
KDDockWidgets_EXPORT void c_QPoint__setX_int(void *thisObj, int x);

// tag=1067
//  QPoint::setY(int y)
KDDockWidgets_EXPORT void c_QPoint__setY_int(void *thisObj, int y);

// tag=1067
//  QPoint::transposed() const
KDDockWidgets_EXPORT void *c_QPoint__transposed(void *thisObj);

// tag=1067
//  QPoint::x() const
KDDockWidgets_EXPORT int c_QPoint__x(void *thisObj);

// tag=1067
//  QPoint::y() const
KDDockWidgets_EXPORT int c_QPoint__y(void *thisObj);

// tag=1066
KDDockWidgets_EXPORT void c_QPoint__destructor(void *thisObj);

// tag=1047
KDDockWidgets_EXPORT void c_QPoint_Finalizer(void *, void *cppObj, void *);
}

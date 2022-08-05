/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <qpoint.h>

namespace KDDockWidgetsBindings_wrappersNS {
class QPoint_wrapper : public ::QPoint
{
public:
    ~QPoint_wrapper();
    QPoint_wrapper();
    QPoint_wrapper(int xpos, int ypos);
    static int dotProduct(const QPoint &p1, const QPoint &p2);
    bool isNull() const;
    int manhattanLength() const;
    void setX(int x);
    void setY(int y);
    QPoint transposed() const;
    int x() const;
    int y() const;
};
}
extern "C" {
// QPoint::QPoint()
KDDockWidgetsBindings_EXPORT void *c_QPoint__constructor();
// QPoint::QPoint(int xpos, int ypos)
KDDockWidgetsBindings_EXPORT void *c_QPoint__constructor_int_int(int xpos, int ypos);
// QPoint::dotProduct(const QPoint & p1, const QPoint & p2)
KDDockWidgetsBindings_EXPORT int c_static_QPoint__dotProduct_QPoint_QPoint(void *p1_, void *p2_);
// QPoint::isNull() const
KDDockWidgetsBindings_EXPORT bool c_QPoint__isNull(void *thisObj);
// QPoint::manhattanLength() const
KDDockWidgetsBindings_EXPORT int c_QPoint__manhattanLength(void *thisObj);
// QPoint::setX(int x)
KDDockWidgetsBindings_EXPORT void c_QPoint__setX_int(void *thisObj, int x);
// QPoint::setY(int y)
KDDockWidgetsBindings_EXPORT void c_QPoint__setY_int(void *thisObj, int y);
// QPoint::transposed() const
KDDockWidgetsBindings_EXPORT void *c_QPoint__transposed(void *thisObj);
// QPoint::x() const
KDDockWidgetsBindings_EXPORT int c_QPoint__x(void *thisObj);
// QPoint::y() const
KDDockWidgetsBindings_EXPORT int c_QPoint__y(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_QPoint__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_QPoint_Finalizer(void *, void *cppObj, void *);
}

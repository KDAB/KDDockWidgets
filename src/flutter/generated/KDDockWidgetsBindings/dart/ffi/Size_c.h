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
class Size_wrapper : public ::KDDockWidgets::Size
{
public:
    ~Size_wrapper();
    Size_wrapper();
    Size_wrapper(int width, int height);
    KDDockWidgets::Size boundedTo(KDDockWidgets::Size arg__1) const;
    KDDockWidgets::Size expandedTo(KDDockWidgets::Size arg__1) const;
    int height() const;
    bool isEmpty() const;
    bool isNull() const;
    bool isValid() const;
    void setHeight(int h);
    void setWidth(int w);
    int width() const;
};
}
extern "C" {
// KDDockWidgets::Size::Size()
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Size__constructor();
// KDDockWidgets::Size::Size(int width, int height)
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Size__constructor_int_int(int width, int height);
// KDDockWidgets::Size::boundedTo(KDDockWidgets::Size arg__1) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Size__boundedTo_Size(void *thisObj, void *arg__1_);
// KDDockWidgets::Size::expandedTo(KDDockWidgets::Size arg__1) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Size__expandedTo_Size(void *thisObj, void *arg__1_);
// KDDockWidgets::Size::height() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Size__height(void *thisObj);
// KDDockWidgets::Size::isEmpty() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Size__isEmpty(void *thisObj);
// KDDockWidgets::Size::isNull() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Size__isNull(void *thisObj);
// KDDockWidgets::Size::isValid() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Size__isValid(void *thisObj);
// KDDockWidgets::Size::setHeight(int h)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Size__setHeight_int(void *thisObj, int h);
// KDDockWidgets::Size::setWidth(int w)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Size__setWidth_int(void *thisObj, int w);
// KDDockWidgets::Size::width() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Size__width(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Size__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Size_Finalizer(void *cppObj);
}

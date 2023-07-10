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
class Margins_wrapper : public ::KDDockWidgets::Margins
{
public:
    ~Margins_wrapper();
    Margins_wrapper();
    Margins_wrapper(int l, int t, int r, int b);
    int bottom() const;
    int left() const;
    int right() const;
    int top() const;
};
}
extern "C" {
// KDDockWidgets::Margins::Margins()
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Margins__constructor();
// KDDockWidgets::Margins::Margins(int l, int t, int r, int b)
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Margins__constructor_int_int_int_int(int l, int t, int r, int b);
// KDDockWidgets::Margins::bottom() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Margins__bottom(void *thisObj);
// KDDockWidgets::Margins::left() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Margins__left(void *thisObj);
// KDDockWidgets::Margins::right() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Margins__right(void *thisObj);
// KDDockWidgets::Margins::top() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Margins__top(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Margins__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Margins_Finalizer(void *cppObj);
}

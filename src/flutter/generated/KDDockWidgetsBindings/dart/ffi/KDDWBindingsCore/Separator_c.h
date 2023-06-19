/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <Separator.h>
#include <core/View.h>
#include <qrect.h>
#include <qpoint.h>
#include <qsize.h>
#include <qstring.h>

namespace KDDockWidgetsBindings_wrappersNS {
namespace KDDWBindingsCore {
class Separator_wrapper : public ::KDDockWidgets::Core::Separator
{
public:
    ~Separator_wrapper();
    Separator_wrapper(KDDockWidgets::Core::View *host);
    static bool isResizing();
    bool isVertical() const;
    void move(int p);
    static int numSeparators();
    void onMouseDoubleClick();
    void onMouseMove(QPoint pos);
    void onMousePress();
    void onMouseReleased();
    int position() const;
    void setGeometry(QRect r);
    void setGeometry(int pos, int pos2, int length);
    virtual void setParentView_impl(KDDockWidgets::Core::View *parent);
    virtual void setParentView_impl_nocallback(KDDockWidgets::Core::View *parent);
    typedef void (*Callback_setParentView_impl)(void *, KDDockWidgets::Core::View *parent);
    Callback_setParentView_impl m_setParentView_implCallback = nullptr;
};
}
}
extern "C" {
// KDDockWidgets::Core::Separator::Separator(KDDockWidgets::Core::View * host)
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__Separator__constructor_View(void *host_);
// KDDockWidgets::Core::Separator::isResizing()
KDDockWidgetsBindings_EXPORT bool c_static_KDDockWidgets__Core__Separator__isResizing();
// KDDockWidgets::Core::Separator::isVertical() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__Separator__isVertical(void *thisObj);
// KDDockWidgets::Core::Separator::move(int p)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__Separator__move_int(void *thisObj, int p);
// KDDockWidgets::Core::Separator::numSeparators()
KDDockWidgetsBindings_EXPORT int c_static_KDDockWidgets__Core__Separator__numSeparators();
// KDDockWidgets::Core::Separator::onMouseDoubleClick()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__Separator__onMouseDoubleClick(void *thisObj);
// KDDockWidgets::Core::Separator::onMouseMove(QPoint pos)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__Separator__onMouseMove_QPoint(void *thisObj, void *pos_);
// KDDockWidgets::Core::Separator::onMousePress()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__Separator__onMousePress(void *thisObj);
// KDDockWidgets::Core::Separator::onMouseReleased()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__Separator__onMouseReleased(void *thisObj);
// KDDockWidgets::Core::Separator::position() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Core__Separator__position(void *thisObj);
// KDDockWidgets::Core::Separator::setGeometry(QRect r)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__Separator__setGeometry_QRect(void *thisObj, void *r_);
// KDDockWidgets::Core::Separator::setGeometry(int pos, int pos2, int length)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__Separator__setGeometry_int_int_int(void *thisObj, int pos, int pos2, int length);
// KDDockWidgets::Core::Separator::setParentView_impl(KDDockWidgets::Core::View * parent)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__Separator__setParentView_impl_View(void *thisObj, void *parent_);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__Separator__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__Separator__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__Separator_Finalizer(void *cppObj);
}

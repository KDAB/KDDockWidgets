/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <Controller.h>
#include <qstring.h>
#include <View.h>
#include <qrect.h>
#include <qpoint.h>
#include <qsize.h>
#include <qobject.h>
#include <qlist.h>
#include <qbytearray.h>

namespace KDDockWidgetsBindings_wrappersNS {
class Controller_wrapper : public ::KDDockWidgets::Controller
{
public:
    ~Controller_wrapper();
    Controller_wrapper(KDDockWidgets::Type type, KDDockWidgets::View *arg__2);
    bool close();
    QRect geometry() const;
    int height() const;
    bool inDtor() const;
    bool isVisible() const;
    QPoint mapToGlobal(QPoint arg__1) const;
    void parentViewChanged(KDDockWidgets::View *parent);
    QPoint pos() const;
    QRect rect() const;
    void setParentView(KDDockWidgets::View *parent);
    virtual void setParentView_impl(KDDockWidgets::View *parent);
    virtual void setParentView_impl_nocallback(KDDockWidgets::View *parent);
    void setVisible(bool arg__1);
    void show() const;
    QSize size() const;
    static QString tr(const char *s, const char *c, int n);
    KDDockWidgets::Type type() const;
    KDDockWidgets::View *view() const;
    void visibleChanged(bool arg__1);
    int width() const;
    int x() const;
    int y() const;
    typedef void (*Callback_setParentView_impl)(void *, KDDockWidgets::View *parent);
    Callback_setParentView_impl m_setParentView_implCallback = nullptr;
};
}
extern "C" {
// KDDockWidgets::Controller::Controller(KDDockWidgets::Type type, KDDockWidgets::View * arg__2)
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controller__constructor_Type_View(int type, void *arg__2_);
// KDDockWidgets::Controller::close()
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controller__close(void *thisObj);
// KDDockWidgets::Controller::geometry() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controller__geometry(void *thisObj);
// KDDockWidgets::Controller::height() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Controller__height(void *thisObj);
// KDDockWidgets::Controller::inDtor() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controller__inDtor(void *thisObj);
// KDDockWidgets::Controller::isVisible() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controller__isVisible(void *thisObj);
// KDDockWidgets::Controller::mapToGlobal(QPoint arg__1) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controller__mapToGlobal_QPoint(void *thisObj, void *arg__1_);
// KDDockWidgets::Controller::parentViewChanged(KDDockWidgets::View * parent)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controller__parentViewChanged_View(void *thisObj, void *parent_);
// KDDockWidgets::Controller::pos() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controller__pos(void *thisObj);
// KDDockWidgets::Controller::rect() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controller__rect(void *thisObj);
// KDDockWidgets::Controller::setParentView(KDDockWidgets::View * parent)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controller__setParentView_View(void *thisObj, void *parent_);
// KDDockWidgets::Controller::setParentView_impl(KDDockWidgets::View * parent)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controller__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Controller::setVisible(bool arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controller__setVisible_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Controller::show() const
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controller__show(void *thisObj);
// KDDockWidgets::Controller::size() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controller__size(void *thisObj);
// KDDockWidgets::Controller::tr(const char * s, const char * c, int n)
KDDockWidgetsBindings_EXPORT void *c_static_KDDockWidgets__Controller__tr_char_char_int(const char *s, const char *c, int n);
// KDDockWidgets::Controller::type() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Controller__type(void *thisObj);
// KDDockWidgets::Controller::view() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controller__view(void *thisObj);
// KDDockWidgets::Controller::visibleChanged(bool arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controller__visibleChanged_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Controller::width() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Controller__width(void *thisObj);
// KDDockWidgets::Controller::x() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Controller__x(void *thisObj);
// KDDockWidgets::Controller::y() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Controller__y(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controller__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controller__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controller_Finalizer(void *, void *cppObj, void *);
}

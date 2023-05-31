/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <core/Controller.h>
#include <qstring.h>
#include <core/View.h>
#include <qrect.h>
#include <qpoint.h>
#include <qsize.h>
#include <qlist.h>
#include <qobject.h>
#include <qbytearray.h>

namespace KDDockWidgetsBindings_wrappersNS {
namespace KDDWBindingsCore {
class Controller_wrapper : public ::KDDockWidgets::Core::Controller
{
public:
    ~Controller_wrapper();
    Controller_wrapper(KDDockWidgets::Core::ViewType type, KDDockWidgets::Core::View *arg__2);
    bool close();
    void destroyLater();
    QRect geometry() const;
    int height() const;
    bool inDtor() const;
    bool isVisible() const;
    QPoint mapToGlobal(QPoint arg__1) const;
    void parentViewChanged(KDDockWidgets::Core::View *parent);
    QPoint pos() const;
    QRect rect() const;
    void setParentView(KDDockWidgets::Core::View *parent);
    virtual void setParentView_impl(KDDockWidgets::Core::View *parent);
    virtual void setParentView_impl_nocallback(KDDockWidgets::Core::View *parent);
    void setVisible(bool arg__1);
    void show() const;
    QSize size() const;
    static QString tr(const char *s, const char *c, int n);
    KDDockWidgets::Core::ViewType type() const;
    KDDockWidgets::Core::View *view() const;
    int width() const;
    int x() const;
    int y() const;
    typedef void (*Callback_setParentView_impl)(void *, KDDockWidgets::Core::View *parent);
    Callback_setParentView_impl m_setParentView_implCallback = nullptr;
};
}
}
extern "C" {
// KDDockWidgets::Core::Controller::Controller(KDDockWidgets::Core::ViewType type, KDDockWidgets::Core::View * arg__2)
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__Controller__constructor_ViewType_View(int type, void *arg__2_);
// KDDockWidgets::Core::Controller::close()
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__Controller__close(void *thisObj);
// KDDockWidgets::Core::Controller::destroyLater()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__Controller__destroyLater(void *thisObj);
// KDDockWidgets::Core::Controller::geometry() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__Controller__geometry(void *thisObj);
// KDDockWidgets::Core::Controller::height() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Core__Controller__height(void *thisObj);
// KDDockWidgets::Core::Controller::inDtor() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__Controller__inDtor(void *thisObj);
// KDDockWidgets::Core::Controller::isVisible() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__Controller__isVisible(void *thisObj);
// KDDockWidgets::Core::Controller::mapToGlobal(QPoint arg__1) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__Controller__mapToGlobal_QPoint(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::Controller::parentViewChanged(KDDockWidgets::Core::View * parent)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__Controller__parentViewChanged_View(void *thisObj, void *parent_);
// KDDockWidgets::Core::Controller::pos() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__Controller__pos(void *thisObj);
// KDDockWidgets::Core::Controller::rect() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__Controller__rect(void *thisObj);
// KDDockWidgets::Core::Controller::setParentView(KDDockWidgets::Core::View * parent)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__Controller__setParentView_View(void *thisObj, void *parent_);
// KDDockWidgets::Core::Controller::setParentView_impl(KDDockWidgets::Core::View * parent)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__Controller__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Core::Controller::setVisible(bool arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__Controller__setVisible_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Core::Controller::show() const
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__Controller__show(void *thisObj);
// KDDockWidgets::Core::Controller::size() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__Controller__size(void *thisObj);
// KDDockWidgets::Core::Controller::tr(const char * s, const char * c, int n)
KDDockWidgetsBindings_EXPORT void *c_static_KDDockWidgets__Core__Controller__tr_char_char_int(const char *s, const char *c, int n);
// KDDockWidgets::Core::Controller::type() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Core__Controller__type(void *thisObj);
// KDDockWidgets::Core::Controller::view() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__Controller__view(void *thisObj);
// KDDockWidgets::Core::Controller::width() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Core__Controller__width(void *thisObj);
// KDDockWidgets::Core::Controller::x() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Core__Controller__x(void *thisObj);
// KDDockWidgets::Core::Controller::y() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Core__Controller__y(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__Controller__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__Controller__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__Controller_Finalizer(void *, void *cppObj, void *);
}

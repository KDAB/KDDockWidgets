/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// tag=1040
#include "KDDockWidgetsBindings_exports.h"
#include <Controller.h>
#include <qstring.h>
#include <View.h>
#include <qrect.h>
#include <qpoint.h>
#include <qsize.h>
#include <qobject.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qbytearray.h>

namespace KDDockWidgetsBindings_wrappersNS {
// tag=1017
class Controller_wrapper : public ::KDDockWidgets::Controller
{
public:
    ~Controller_wrapper();
    // tag=1041
    bool close();
    // tag=1041
    virtual void customEvent(QEvent *event);
    // tag=1008
    virtual void customEvent_nocallback(QEvent *event);
    // tag=1041
    virtual bool event(QEvent *event);
    // tag=1008
    virtual bool event_nocallback(QEvent *event);
    // tag=1041
    virtual bool eventFilter(QObject *watched, QEvent *event);
    // tag=1008
    virtual bool eventFilter_nocallback(QObject *watched, QEvent *event);
    // tag=1041
    QRect geometry() const;
    // tag=1041
    int height() const;
    // tag=1041
    bool inDtor() const;
    // tag=1041
    bool isVisible() const;
    // tag=1041
    QPoint mapToGlobal(QPoint arg__1) const;
    // tag=1041
    void parentViewChanged(KDDockWidgets::View *parent);
    // tag=1041
    QPoint pos() const;
    // tag=1041
    QRect rect() const;
    // tag=1041
    void setParentView(KDDockWidgets::View *parent);
    // tag=1041
    virtual void setParentView_impl(KDDockWidgets::View *parent);
    // tag=1008
    virtual void setParentView_impl_nocallback(KDDockWidgets::View *parent);
    // tag=1041
    void setVisible(bool arg__1);
    // tag=1041
    void show() const;
    // tag=1041
    QSize size() const;
    // tag=1041
    static QString tr(const char *s, const char *c, int n);
    // tag=1041
    KDDockWidgets::View *view() const;
    // tag=1041
    int width() const;
    // tag=1041
    int x() const;
    // tag=1041
    int y() const;
    // tag=1042
    typedef void (*Callback_customEvent)(void *, QEvent *event);
    Callback_customEvent m_customEventCallback = nullptr;
    // tag=1042
    typedef bool (*Callback_event)(void *, QEvent *event);
    Callback_event m_eventCallback = nullptr;
    // tag=1042
    typedef bool (*Callback_eventFilter)(void *, QObject *watched, QEvent *event);
    Callback_eventFilter m_eventFilterCallback = nullptr;
    // tag=1042
    typedef void (*Callback_setParentView_impl)(void *, KDDockWidgets::View *parent);
    Callback_setParentView_impl m_setParentView_implCallback = nullptr;
};
}
extern "C" {

// tag=1067
//  KDDockWidgets::Controller::close()
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controller__close(void *thisObj);

// tag=1067
//  KDDockWidgets::Controller::customEvent(QEvent * event)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controller__customEvent_QEvent(void *thisObj, void *event_);

// tag=1067
//  KDDockWidgets::Controller::event(QEvent * event)
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controller__event_QEvent(void *thisObj, void *event_);

// tag=1067
//  KDDockWidgets::Controller::eventFilter(QObject * watched, QEvent * event)
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controller__eventFilter_QObject_QEvent(void *thisObj, void *watched_, void *event_);

// tag=1067
//  KDDockWidgets::Controller::geometry() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controller__geometry(void *thisObj);

// tag=1067
//  KDDockWidgets::Controller::height() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Controller__height(void *thisObj);

// tag=1067
//  KDDockWidgets::Controller::inDtor() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controller__inDtor(void *thisObj);

// tag=1067
//  KDDockWidgets::Controller::isVisible() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controller__isVisible(void *thisObj);

// tag=1067
//  KDDockWidgets::Controller::mapToGlobal(QPoint arg__1) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controller__mapToGlobal_QPoint(void *thisObj, void *arg__1_);

// tag=1067
//  KDDockWidgets::Controller::parentViewChanged(KDDockWidgets::View * parent)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controller__parentViewChanged_View(void *thisObj, void *parent_);

// tag=1078
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controller__onParentViewChanged_View(void *thisObj, void *contextQObject, void *callback);
// tag=1067
//  KDDockWidgets::Controller::pos() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controller__pos(void *thisObj);

// tag=1067
//  KDDockWidgets::Controller::rect() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controller__rect(void *thisObj);

// tag=1067
//  KDDockWidgets::Controller::setParentView(KDDockWidgets::View * parent)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controller__setParentView_View(void *thisObj, void *parent_);

// tag=1067
//  KDDockWidgets::Controller::setParentView_impl(KDDockWidgets::View * parent)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controller__setParentView_impl_View(void *thisObj, void *parent_);

// tag=1067
//  KDDockWidgets::Controller::setVisible(bool arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controller__setVisible_bool(void *thisObj, bool arg__1);

// tag=1067
//  KDDockWidgets::Controller::show() const
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controller__show(void *thisObj);

// tag=1067
//  KDDockWidgets::Controller::size() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controller__size(void *thisObj);

// tag=1067
//  KDDockWidgets::Controller::tr(const char * s, const char * c, int n)
KDDockWidgetsBindings_EXPORT void *c_static_KDDockWidgets__Controller__tr_char_char_int(const char *s, const char *c, int n);

// tag=1067
//  KDDockWidgets::Controller::view() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controller__view(void *thisObj);

// tag=1067
//  KDDockWidgets::Controller::width() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Controller__width(void *thisObj);

// tag=1067
//  KDDockWidgets::Controller::x() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Controller__x(void *thisObj);

// tag=1067
//  KDDockWidgets::Controller::y() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Controller__y(void *thisObj);

// tag=1066
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controller__destructor(void *thisObj);

// tag=1046
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controller__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
// tag=1047
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controller_Finalizer(void *, void *cppObj, void *);
}

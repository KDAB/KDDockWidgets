/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "Controller_wrapper.h"


#include <QDebug>


namespace Dartagnan {

typedef int (*CleanupCallback)(void *thisPtr);
static CleanupCallback s_cleanupCallback = nullptr;

template<typename T>
struct ValueWrapper
{
    T value;
};

}
namespace KDDockWidgetsBindings_wrappersNS {
bool Controller_wrapper::close()
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Controller::close();
}
void Controller_wrapper::customEvent(QEvent *event)
{
    // tag=1000
    if (m_customEventCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_customEventCallback(const_cast<void *>(thisPtr), event);
    } else {
        // tag=1002
        ::KDDockWidgets::Controller::customEvent(event);
    }
}
// tag=1009
void Controller_wrapper::customEvent_nocallback(QEvent *event)
{
    // tag=1003
    ::KDDockWidgets::Controller::customEvent(event);
}
bool Controller_wrapper::event(QEvent *event)
{
    // tag=1000
    if (m_eventCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_eventCallback(const_cast<void *>(thisPtr), event);
    } else {
        // tag=1002
        return ::KDDockWidgets::Controller::event(event);
    }
}
// tag=1009
bool Controller_wrapper::event_nocallback(QEvent *event)
{
    // tag=1003
    return ::KDDockWidgets::Controller::event(event);
}
bool Controller_wrapper::eventFilter(QObject *watched, QEvent *event)
{
    // tag=1000
    if (m_eventFilterCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_eventFilterCallback(const_cast<void *>(thisPtr), watched, event);
    } else {
        // tag=1002
        return ::KDDockWidgets::Controller::eventFilter(watched, event);
    }
}
// tag=1009
bool Controller_wrapper::eventFilter_nocallback(QObject *watched, QEvent *event)
{
    // tag=1003
    return ::KDDockWidgets::Controller::eventFilter(watched, event);
}
QRect Controller_wrapper::geometry() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Controller::geometry();
}
int Controller_wrapper::height() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Controller::height();
}
bool Controller_wrapper::inDtor() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Controller::inDtor();
}
bool Controller_wrapper::isVisible() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Controller::isVisible();
}
QPoint Controller_wrapper::mapToGlobal(QPoint arg__1) const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Controller::mapToGlobal(arg__1);
}
void Controller_wrapper::parentViewChanged(KDDockWidgets::View *parent)
{
    // tag=1000

    // tag=1004
    ::KDDockWidgets::Controller::parentViewChanged(parent);
}
QPoint Controller_wrapper::pos() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Controller::pos();
}
QRect Controller_wrapper::rect() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Controller::rect();
}
void Controller_wrapper::setParentView(KDDockWidgets::View *parent)
{
    // tag=1000

    // tag=1004
    ::KDDockWidgets::Controller::setParentView(parent);
}
void Controller_wrapper::setParentView_impl(KDDockWidgets::View *parent)
{
    // tag=1000
    if (m_setParentView_implCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setParentView_implCallback(const_cast<void *>(thisPtr), parent);
    } else {
        // tag=1002
        ::KDDockWidgets::Controller::setParentView_impl(parent);
    }
}
// tag=1009
void Controller_wrapper::setParentView_impl_nocallback(KDDockWidgets::View *parent)
{
    // tag=1003
    ::KDDockWidgets::Controller::setParentView_impl(parent);
}
void Controller_wrapper::setVisible(bool arg__1)
{
    // tag=1000

    // tag=1004
    ::KDDockWidgets::Controller::setVisible(arg__1);
}
void Controller_wrapper::show() const
{
    // tag=1000

    // tag=1004
    ::KDDockWidgets::Controller::show();
}
QSize Controller_wrapper::size() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Controller::size();
}
QString Controller_wrapper::tr(const char *s, const char *c, int n)
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Controller::tr(s, c, n);
}
KDDockWidgets::View *Controller_wrapper::view() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Controller::view();
}
int Controller_wrapper::width() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Controller::width();
}
int Controller_wrapper::x() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Controller::x();
}
int Controller_wrapper::y() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Controller::y();
}

// tag=1005
Controller_wrapper::~Controller_wrapper()
{
}

}
// tag=1013
static KDDockWidgets::Controller *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::Controller *>(ptr);
}
// tag=1014
static KDDockWidgetsBindings_wrappersNS::Controller_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Controller_wrapper *>(ptr);
}
extern "C" {

// tag=1049
void c_KDDockWidgets__Controller_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Controller_wrapper *>(cppObj);
}
// tag=1050
// close()
bool c_KDDockWidgets__Controller__close(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->close();
}

// tag=1050
// customEvent(QEvent * event)
void c_KDDockWidgets__Controller__customEvent_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    // tag=1011

    // tag=1074
    fromWrapperPtr(thisObj)->customEvent_nocallback(event);
}

// tag=1079
void c_KDDockWidgets__Controller__onDestroyed_QObject(void *thisObj, void *contextQObject, void *callback)
{
    auto instance = reinterpret_cast<Controller *>(thisObj);
    auto context = reinterpret_cast<QObject *>(contextQObject);
    QObject::connect(instance, &Controller::destroyed, context ? context : instance, [thisObj, callback] {
typedef void (*SignalHandler_callback)(void *);
auto dartCallback = reinterpret_cast<SignalHandler_callback>(callback);
dartCallback(thisObj); });
}

// tag=1050
// event(QEvent * event)
bool c_KDDockWidgets__Controller__event_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Controller_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->event_nocallback(event);} else {    return targetPtr->event(event);} }();
}

// tag=1050
// eventFilter(QObject * watched, QEvent * event)
bool c_KDDockWidgets__Controller__eventFilter_QObject_QEvent(void *thisObj, void *watched_, void *event_)
{
    auto watched = reinterpret_cast<QObject *>(watched_);
    auto event = reinterpret_cast<QEvent *>(event_);
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Controller_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->eventFilter_nocallback(watched,event);} else {    return targetPtr->eventFilter(watched,event);} }();
}

// tag=1050
// geometry() const
void *c_KDDockWidgets__Controller__geometry(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QRect> { fromPtr(thisObj)->geometry() };
}

// tag=1050
// height() const
int c_KDDockWidgets__Controller__height(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->height();
}

// tag=1050
// inDtor() const
bool c_KDDockWidgets__Controller__inDtor(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->inDtor();
}

// tag=1050
// isVisible() const
bool c_KDDockWidgets__Controller__isVisible(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->isVisible();
}

// tag=1050
// mapToGlobal(QPoint arg__1) const
void *c_KDDockWidgets__Controller__mapToGlobal_QPoint(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QPoint *>(arg__1_);
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QPoint> { fromPtr(thisObj)->mapToGlobal(arg__1) };
}

// tag=1050
// parentViewChanged(KDDockWidgets::View * parent)
void c_KDDockWidgets__Controller__parentViewChanged_View(void *thisObj, void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    // tag=1010
    fromPtr(thisObj)->parentViewChanged(parent);
}

// tag=1079
void c_KDDockWidgets__Controller__onParentViewChanged_View(void *thisObj, void *contextQObject, void *callback)
{
    auto instance = reinterpret_cast<Controller *>(thisObj);
    auto context = reinterpret_cast<QObject *>(contextQObject);
    QObject::connect(instance, &Controller::parentViewChanged, context ? context : instance, [thisObj, callback] {
typedef void (*SignalHandler_callback)(void *);
auto dartCallback = reinterpret_cast<SignalHandler_callback>(callback);
dartCallback(thisObj); });
}

// tag=1050
// pos() const
void *c_KDDockWidgets__Controller__pos(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QPoint> { fromPtr(thisObj)->pos() };
}

// tag=1050
// rect() const
void *c_KDDockWidgets__Controller__rect(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QRect> { fromPtr(thisObj)->rect() };
}

// tag=1050
// setParentView(KDDockWidgets::View * parent)
void c_KDDockWidgets__Controller__setParentView_View(void *thisObj, void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    // tag=1010
    fromPtr(thisObj)->setParentView(parent);
}

// tag=1050
// setParentView_impl(KDDockWidgets::View * parent)
void c_KDDockWidgets__Controller__setParentView_impl_View(void *thisObj, void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    // tag=1011

    // tag=1074
    fromWrapperPtr(thisObj)->setParentView_impl_nocallback(parent);
}

// tag=1050
// setVisible(bool arg__1)
void c_KDDockWidgets__Controller__setVisible_bool(void *thisObj, bool arg__1)
{
    // tag=1010
    fromPtr(thisObj)->setVisible(arg__1);
}

// tag=1050
// show() const
void c_KDDockWidgets__Controller__show(void *thisObj)
{
    // tag=1010
    fromPtr(thisObj)->show();
}

// tag=1050
// size() const
void *c_KDDockWidgets__Controller__size(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QSize> { fromPtr(thisObj)->size() };
}

// tag=1050
// tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__Controller__tr_char_char_int(const char *s, const char *c, int n)
{
    return
        // tag=1068

        // tag=1072
        new Dartagnan::ValueWrapper<QString> { KDDockWidgetsBindings_wrappersNS::Controller_wrapper::tr(s, c, n) };
}

// tag=1050
// view() const
void *c_KDDockWidgets__Controller__view(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->view();
}

// tag=1050
// width() const
int c_KDDockWidgets__Controller__width(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->width();
}

// tag=1050
// x() const
int c_KDDockWidgets__Controller__x(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->x();
}

// tag=1050
// y() const
int c_KDDockWidgets__Controller__y(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->y();
}
void c_KDDockWidgets__Controller__destructor(void *thisObj)
{

    // tag=1055
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__Controller__registerVirtualMethodCallback(void *ptr, void *callback, int methodId)
{
    // tag=1048
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 294:
        wrapper->m_customEventCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Controller_wrapper::Callback_customEvent>(callback);
        break;
    case 305:
        wrapper->m_eventCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Controller_wrapper::Callback_event>(callback);
        break;
    case 306:
        wrapper->m_eventFilterCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Controller_wrapper::Callback_eventFilter>(callback);
        break;
    case 654:
        wrapper->m_setParentView_implCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Controller_wrapper::Callback_setParentView_impl>(callback);
        break;
    }
}
}

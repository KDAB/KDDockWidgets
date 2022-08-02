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
Controller_wrapper::Controller_wrapper(KDDockWidgets::Type type, KDDockWidgets::View *arg__2)
    : ::KDDockWidgets::Controller(type, arg__2)
{
}
bool Controller_wrapper::close()
{
    return ::KDDockWidgets::Controller::close();
}
void Controller_wrapper::customEvent(QEvent *event)
{
    if (m_customEventCallback) {
        const void *thisPtr = this;
        m_customEventCallback(const_cast<void *>(thisPtr), event);
    } else {
        ::KDDockWidgets::Controller::customEvent(event);
    }
}
void Controller_wrapper::customEvent_nocallback(QEvent *event)
{
    ::KDDockWidgets::Controller::customEvent(event);
}
bool Controller_wrapper::event(QEvent *event)
{
    if (m_eventCallback) {
        const void *thisPtr = this;
        return m_eventCallback(const_cast<void *>(thisPtr), event);
    } else {
        return ::KDDockWidgets::Controller::event(event);
    }
}
bool Controller_wrapper::event_nocallback(QEvent *event)
{
    return ::KDDockWidgets::Controller::event(event);
}
bool Controller_wrapper::eventFilter(QObject *watched, QEvent *event)
{
    if (m_eventFilterCallback) {
        const void *thisPtr = this;
        return m_eventFilterCallback(const_cast<void *>(thisPtr), watched, event);
    } else {
        return ::KDDockWidgets::Controller::eventFilter(watched, event);
    }
}
bool Controller_wrapper::eventFilter_nocallback(QObject *watched, QEvent *event)
{
    return ::KDDockWidgets::Controller::eventFilter(watched, event);
}
QRect Controller_wrapper::geometry() const
{
    return ::KDDockWidgets::Controller::geometry();
}
int Controller_wrapper::height() const
{
    return ::KDDockWidgets::Controller::height();
}
bool Controller_wrapper::inDtor() const
{
    return ::KDDockWidgets::Controller::inDtor();
}
bool Controller_wrapper::isVisible() const
{
    return ::KDDockWidgets::Controller::isVisible();
}
QPoint Controller_wrapper::mapToGlobal(QPoint arg__1) const
{
    return ::KDDockWidgets::Controller::mapToGlobal(arg__1);
}
void Controller_wrapper::parentViewChanged(KDDockWidgets::View *parent)
{
    ::KDDockWidgets::Controller::parentViewChanged(parent);
}
QPoint Controller_wrapper::pos() const
{
    return ::KDDockWidgets::Controller::pos();
}
QRect Controller_wrapper::rect() const
{
    return ::KDDockWidgets::Controller::rect();
}
void Controller_wrapper::setParentView(KDDockWidgets::View *parent)
{
    ::KDDockWidgets::Controller::setParentView(parent);
}
void Controller_wrapper::setParentView_impl(KDDockWidgets::View *parent)
{
    if (m_setParentView_implCallback) {
        const void *thisPtr = this;
        m_setParentView_implCallback(const_cast<void *>(thisPtr), parent);
    } else {
        ::KDDockWidgets::Controller::setParentView_impl(parent);
    }
}
void Controller_wrapper::setParentView_impl_nocallback(KDDockWidgets::View *parent)
{
    ::KDDockWidgets::Controller::setParentView_impl(parent);
}
void Controller_wrapper::setVisible(bool arg__1)
{
    ::KDDockWidgets::Controller::setVisible(arg__1);
}
void Controller_wrapper::show() const
{
    ::KDDockWidgets::Controller::show();
}
QSize Controller_wrapper::size() const
{
    return ::KDDockWidgets::Controller::size();
}
QString Controller_wrapper::tr(const char *s, const char *c, int n)
{
    return ::KDDockWidgets::Controller::tr(s, c, n);
}
KDDockWidgets::Type Controller_wrapper::type() const
{
    return ::KDDockWidgets::Controller::type();
}
KDDockWidgets::View *Controller_wrapper::view() const
{
    return ::KDDockWidgets::Controller::view();
}
int Controller_wrapper::width() const
{
    return ::KDDockWidgets::Controller::width();
}
int Controller_wrapper::x() const
{
    return ::KDDockWidgets::Controller::x();
}
int Controller_wrapper::y() const
{
    return ::KDDockWidgets::Controller::y();
}
Controller_wrapper::~Controller_wrapper()
{
}

}
static KDDockWidgets::Controller *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::Controller *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::Controller_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Controller_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__Controller_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Controller_wrapper *>(cppObj);
}
void *c_KDDockWidgets__Controller__constructor_Type_View(int type, void *arg__2_)
{
    auto arg__2 = reinterpret_cast<KDDockWidgets::View *>(arg__2_);
    auto ptr = new KDDockWidgetsBindings_wrappersNS::Controller_wrapper(static_cast<KDDockWidgets::Type>(type), arg__2);
    return reinterpret_cast<void *>(ptr);
}
// close()
bool c_KDDockWidgets__Controller__close(void *thisObj)
{
    return fromPtr(thisObj)->close();
}
// customEvent(QEvent * event)
void c_KDDockWidgets__Controller__customEvent_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    fromWrapperPtr(thisObj)->customEvent_nocallback(event);
}
// event(QEvent * event)
bool c_KDDockWidgets__Controller__event_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Controller_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->event_nocallback(event);} else {    return targetPtr->event(event);} }();
}
// eventFilter(QObject * watched, QEvent * event)
bool c_KDDockWidgets__Controller__eventFilter_QObject_QEvent(void *thisObj, void *watched_, void *event_)
{
    auto watched = reinterpret_cast<QObject *>(watched_);
    auto event = reinterpret_cast<QEvent *>(event_);
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Controller_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->eventFilter_nocallback(watched,event);} else {    return targetPtr->eventFilter(watched,event);} }();
}
// geometry() const
void *c_KDDockWidgets__Controller__geometry(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QRect> { fromPtr(thisObj)->geometry() };
}
// height() const
int c_KDDockWidgets__Controller__height(void *thisObj)
{
    return fromPtr(thisObj)->height();
}
// inDtor() const
bool c_KDDockWidgets__Controller__inDtor(void *thisObj)
{
    return fromPtr(thisObj)->inDtor();
}
// isVisible() const
bool c_KDDockWidgets__Controller__isVisible(void *thisObj)
{
    return fromPtr(thisObj)->isVisible();
}
// mapToGlobal(QPoint arg__1) const
void *c_KDDockWidgets__Controller__mapToGlobal_QPoint(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QPoint *>(arg__1_);
    return new Dartagnan::ValueWrapper<QPoint> { fromPtr(thisObj)->mapToGlobal(arg__1) };
}
// parentViewChanged(KDDockWidgets::View * parent)
void c_KDDockWidgets__Controller__parentViewChanged_View(void *thisObj, void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    fromPtr(thisObj)->parentViewChanged(parent);
}
// pos() const
void *c_KDDockWidgets__Controller__pos(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QPoint> { fromPtr(thisObj)->pos() };
}
// rect() const
void *c_KDDockWidgets__Controller__rect(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QRect> { fromPtr(thisObj)->rect() };
}
// setParentView(KDDockWidgets::View * parent)
void c_KDDockWidgets__Controller__setParentView_View(void *thisObj, void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    fromPtr(thisObj)->setParentView(parent);
}
// setParentView_impl(KDDockWidgets::View * parent)
void c_KDDockWidgets__Controller__setParentView_impl_View(void *thisObj, void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    fromWrapperPtr(thisObj)->setParentView_impl_nocallback(parent);
}
// setVisible(bool arg__1)
void c_KDDockWidgets__Controller__setVisible_bool(void *thisObj, bool arg__1)
{
    fromPtr(thisObj)->setVisible(arg__1);
}
// show() const
void c_KDDockWidgets__Controller__show(void *thisObj)
{
    fromPtr(thisObj)->show();
}
// size() const
void *c_KDDockWidgets__Controller__size(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { fromPtr(thisObj)->size() };
}
// tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__Controller__tr_char_char_int(const char *s, const char *c, int n)
{
    return new Dartagnan::ValueWrapper<QString> { KDDockWidgetsBindings_wrappersNS::Controller_wrapper::tr(s, c, n) };
}
// type() const
int c_KDDockWidgets__Controller__type(void *thisObj)
{
    return int(fromPtr(thisObj)->type());
}
// view() const
void *c_KDDockWidgets__Controller__view(void *thisObj)
{
    return fromPtr(thisObj)->view();
}
// width() const
int c_KDDockWidgets__Controller__width(void *thisObj)
{
    return fromPtr(thisObj)->width();
}
// x() const
int c_KDDockWidgets__Controller__x(void *thisObj)
{
    return fromPtr(thisObj)->x();
}
// y() const
int c_KDDockWidgets__Controller__y(void *thisObj)
{
    return fromPtr(thisObj)->y();
}
void c_KDDockWidgets__Controller__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__Controller__registerVirtualMethodCallback(void *ptr, void *callback, int methodId)
{
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 295:
        wrapper->m_customEventCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Controller_wrapper::Callback_customEvent>(callback);
        break;
    case 306:
        wrapper->m_eventCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Controller_wrapper::Callback_event>(callback);
        break;
    case 307:
        wrapper->m_eventFilterCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Controller_wrapper::Callback_eventFilter>(callback);
        break;
    case 817:
        wrapper->m_setParentView_implCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Controller_wrapper::Callback_setParentView_impl>(callback);
        break;
    }
}
}

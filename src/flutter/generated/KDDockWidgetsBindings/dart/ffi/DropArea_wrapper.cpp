/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "DropArea_wrapper.h"


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
// tag=1006
DropArea_wrapper::DropArea_wrapper(KDDockWidgets::View *parent, QFlags<KDDockWidgets::MainWindowOption> options, bool isMDIWrapper)
    : ::KDDockWidgets::Controllers::DropArea(parent, options, isMDIWrapper)
{
}
void DropArea_wrapper::customEvent(QEvent *event)
{
    // tag=1000
    if (m_customEventCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_customEventCallback(const_cast<void *>(thisPtr), event);
    } else {
        // tag=1002
        ::KDDockWidgets::Controllers::DropArea::customEvent(event);
    }
}
// tag=1009
void DropArea_wrapper::customEvent_nocallback(QEvent *event)
{
    // tag=1003
    ::KDDockWidgets::Controllers::DropArea::customEvent(event);
}
bool DropArea_wrapper::event(QEvent *event)
{
    // tag=1000
    if (m_eventCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_eventCallback(const_cast<void *>(thisPtr), event);
    } else {
        // tag=1002
        return ::KDDockWidgets::Controllers::DropArea::event(event);
    }
}
// tag=1009
bool DropArea_wrapper::event_nocallback(QEvent *event)
{
    // tag=1003
    return ::KDDockWidgets::Controllers::DropArea::event(event);
}
bool DropArea_wrapper::eventFilter(QObject *watched, QEvent *event)
{
    // tag=1000
    if (m_eventFilterCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_eventFilterCallback(const_cast<void *>(thisPtr), watched, event);
    } else {
        // tag=1002
        return ::KDDockWidgets::Controllers::DropArea::eventFilter(watched, event);
    }
}
// tag=1009
bool DropArea_wrapper::eventFilter_nocallback(QObject *watched, QEvent *event)
{
    // tag=1003
    return ::KDDockWidgets::Controllers::DropArea::eventFilter(watched, event);
}
bool DropArea_wrapper::hasSingleFloatingFrame() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Controllers::DropArea::hasSingleFloatingFrame();
}
bool DropArea_wrapper::hasSingleFrame() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Controllers::DropArea::hasSingleFrame();
}
bool DropArea_wrapper::isMDIWrapper() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Controllers::DropArea::isMDIWrapper();
}
void DropArea_wrapper::layoutEqually()
{
    // tag=1000

    // tag=1004
    ::KDDockWidgets::Controllers::DropArea::layoutEqually();
}
void DropArea_wrapper::removeHover()
{
    // tag=1000

    // tag=1004
    ::KDDockWidgets::Controllers::DropArea::removeHover();
}
void DropArea_wrapper::setParentView_impl(KDDockWidgets::View *parent)
{
    // tag=1000
    if (m_setParentView_implCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setParentView_implCallback(const_cast<void *>(thisPtr), parent);
    } else {
        // tag=1002
        ::KDDockWidgets::Controllers::DropArea::setParentView_impl(parent);
    }
}
// tag=1009
void DropArea_wrapper::setParentView_impl_nocallback(KDDockWidgets::View *parent)
{
    // tag=1003
    ::KDDockWidgets::Controllers::DropArea::setParentView_impl(parent);
}
QString DropArea_wrapper::tr(const char *s, const char *c, int n)
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Controllers::DropArea::tr(s, c, n);
}

// tag=1005
DropArea_wrapper::~DropArea_wrapper()
{
}

}
// tag=1013
static KDDockWidgets::Controllers::DropArea *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::Controllers::DropArea *>(ptr);
}
// tag=1014
static KDDockWidgetsBindings_wrappersNS::DropArea_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::DropArea_wrapper *>(ptr);
}
extern "C" {

// tag=1049
void c_KDDockWidgets__Controllers__DropArea_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::DropArea_wrapper *>(cppObj);
}
void *c_KDDockWidgets__Controllers__DropArea__constructor_View_MainWindowOptions_bool(void *parent_, int options_, bool isMDIWrapper)
{
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    auto options = static_cast<QFlags<KDDockWidgets::MainWindowOption>>(options_);
    // tag=1056
    auto ptr = new KDDockWidgetsBindings_wrappersNS::DropArea_wrapper(parent, options, isMDIWrapper);
    return reinterpret_cast<void *>(ptr);
}

// tag=1050
// customEvent(QEvent * event)
void c_KDDockWidgets__Controllers__DropArea__customEvent_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    // tag=1011

    // tag=1074
    fromWrapperPtr(thisObj)->customEvent_nocallback(event);
}

// tag=1050
// event(QEvent * event)
bool c_KDDockWidgets__Controllers__DropArea__event_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::DropArea_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->event_nocallback(event);} else {    return targetPtr->event(event);} }();
}

// tag=1050
// eventFilter(QObject * watched, QEvent * event)
bool c_KDDockWidgets__Controllers__DropArea__eventFilter_QObject_QEvent(void *thisObj, void *watched_, void *event_)
{
    auto watched = reinterpret_cast<QObject *>(watched_);
    auto event = reinterpret_cast<QEvent *>(event_);
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::DropArea_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->eventFilter_nocallback(watched,event);} else {    return targetPtr->eventFilter(watched,event);} }();
}

// tag=1050
// hasSingleFloatingFrame() const
bool c_KDDockWidgets__Controllers__DropArea__hasSingleFloatingFrame(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->hasSingleFloatingFrame();
}

// tag=1050
// hasSingleFrame() const
bool c_KDDockWidgets__Controllers__DropArea__hasSingleFrame(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->hasSingleFrame();
}

// tag=1050
// isMDIWrapper() const
bool c_KDDockWidgets__Controllers__DropArea__isMDIWrapper(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->isMDIWrapper();
}

// tag=1050
// layoutEqually()
void c_KDDockWidgets__Controllers__DropArea__layoutEqually(void *thisObj)
{
    // tag=1010
    fromPtr(thisObj)->layoutEqually();
}

// tag=1050
// removeHover()
void c_KDDockWidgets__Controllers__DropArea__removeHover(void *thisObj)
{
    // tag=1010
    fromPtr(thisObj)->removeHover();
}

// tag=1050
// setParentView_impl(KDDockWidgets::View * parent)
void c_KDDockWidgets__Controllers__DropArea__setParentView_impl_View(void *thisObj, void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    // tag=1011

    // tag=1074
    fromWrapperPtr(thisObj)->setParentView_impl_nocallback(parent);
}

// tag=1050
// tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__Controllers__DropArea__tr_char_char_int(const char *s, const char *c, int n)
{
    return
        // tag=1068

        // tag=1072
        new Dartagnan::ValueWrapper<QString> { KDDockWidgetsBindings_wrappersNS::DropArea_wrapper::tr(s, c, n) };
}
void c_KDDockWidgets__Controllers__DropArea__destructor(void *thisObj)
{

    // tag=1055
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__Controllers__DropArea__registerVirtualMethodCallback(void *ptr, void *callback, int methodId)
{
    // tag=1048
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 295:
        wrapper->m_customEventCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::DropArea_wrapper::Callback_customEvent>(callback);
        break;
    case 306:
        wrapper->m_eventCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::DropArea_wrapper::Callback_event>(callback);
        break;
    case 307:
        wrapper->m_eventFilterCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::DropArea_wrapper::Callback_eventFilter>(callback);
        break;
    case 719:
        wrapper->m_setParentView_implCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::DropArea_wrapper::Callback_setParentView_impl>(callback);
        break;
    }
}
}

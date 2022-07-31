/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "ViewFactory_wrapper.h"


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
ViewFactory_wrapper::ViewFactory_wrapper()
    : ::KDDockWidgets::ViewFactory()
{
}
KDDockWidgets::Views::ClassicIndicatorWindowViewInterface *ViewFactory_wrapper::createClassicIndicatorWindow(KDDockWidgets::Controllers::ClassicIndicators *arg__1) const
{
    // tag=1000
    if (m_createClassicIndicatorWindowCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_createClassicIndicatorWindowCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
// tag=1009
KDDockWidgets::Views::ClassicIndicatorWindowViewInterface *ViewFactory_wrapper::createClassicIndicatorWindow_nocallback(KDDockWidgets::Controllers::ClassicIndicators *arg__1) const
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
KDDockWidgets::View *ViewFactory_wrapper::createDropArea(KDDockWidgets::Controllers::DropArea *arg__1, KDDockWidgets::View *parent) const
{
    // tag=1000
    if (m_createDropAreaCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_createDropAreaCallback(const_cast<void *>(thisPtr), arg__1, parent);
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
// tag=1009
KDDockWidgets::View *ViewFactory_wrapper::createDropArea_nocallback(KDDockWidgets::Controllers::DropArea *arg__1, KDDockWidgets::View *parent) const
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
KDDockWidgets::View *ViewFactory_wrapper::createRubberBand(KDDockWidgets::View *parent) const
{
    // tag=1000
    if (m_createRubberBandCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_createRubberBandCallback(const_cast<void *>(thisPtr), parent);
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
// tag=1009
KDDockWidgets::View *ViewFactory_wrapper::createRubberBand_nocallback(KDDockWidgets::View *parent) const
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
void ViewFactory_wrapper::customEvent(QEvent *event)
{
    // tag=1000
    if (m_customEventCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_customEventCallback(const_cast<void *>(thisPtr), event);
    } else {
        // tag=1002
        ::KDDockWidgets::ViewFactory::customEvent(event);
    }
}
// tag=1009
void ViewFactory_wrapper::customEvent_nocallback(QEvent *event)
{
    // tag=1003
    ::KDDockWidgets::ViewFactory::customEvent(event);
}
bool ViewFactory_wrapper::event(QEvent *event)
{
    // tag=1000
    if (m_eventCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_eventCallback(const_cast<void *>(thisPtr), event);
    } else {
        // tag=1002
        return ::KDDockWidgets::ViewFactory::event(event);
    }
}
// tag=1009
bool ViewFactory_wrapper::event_nocallback(QEvent *event)
{
    // tag=1003
    return ::KDDockWidgets::ViewFactory::event(event);
}
bool ViewFactory_wrapper::eventFilter(QObject *watched, QEvent *event)
{
    // tag=1000
    if (m_eventFilterCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_eventFilterCallback(const_cast<void *>(thisPtr), watched, event);
    } else {
        // tag=1002
        return ::KDDockWidgets::ViewFactory::eventFilter(watched, event);
    }
}
// tag=1009
bool ViewFactory_wrapper::eventFilter_nocallback(QObject *watched, QEvent *event)
{
    // tag=1003
    return ::KDDockWidgets::ViewFactory::eventFilter(watched, event);
}
QString ViewFactory_wrapper::tr(const char *s, const char *c, int n)
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::ViewFactory::tr(s, c, n);
}

// tag=1005
ViewFactory_wrapper::~ViewFactory_wrapper()
{
}

}
// tag=1013
static KDDockWidgets::ViewFactory *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::ViewFactory *>(ptr);
}
// tag=1014
static KDDockWidgetsBindings_wrappersNS::ViewFactory_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_wrapper *>(ptr);
}
extern "C" {

// tag=1049
void c_KDDockWidgets__ViewFactory_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_wrapper *>(cppObj);
}
void *c_KDDockWidgets__ViewFactory__constructor()
{

    // tag=1056
    auto ptr = new KDDockWidgetsBindings_wrappersNS::ViewFactory_wrapper();
    return reinterpret_cast<void *>(ptr);
}

// tag=1050
// createClassicIndicatorWindow(KDDockWidgets::Controllers::ClassicIndicators * arg__1) const
void *c_KDDockWidgets__ViewFactory__createClassicIndicatorWindow_ClassicIndicators(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::ClassicIndicators *>(arg__1_);
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->createClassicIndicatorWindow_nocallback(arg__1);} else {    return targetPtr->createClassicIndicatorWindow(arg__1);} }();
}

// tag=1050
// createDropArea(KDDockWidgets::Controllers::DropArea * arg__1, KDDockWidgets::View * parent) const
void *c_KDDockWidgets__ViewFactory__createDropArea_DropArea_View(void *thisObj, void *arg__1_, void *parent_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::DropArea *>(arg__1_);
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->createDropArea_nocallback(arg__1,parent);} else {    return targetPtr->createDropArea(arg__1,parent);} }();
}

// tag=1050
// createRubberBand(KDDockWidgets::View * parent) const
void *c_KDDockWidgets__ViewFactory__createRubberBand_View(void *thisObj, void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->createRubberBand_nocallback(parent);} else {    return targetPtr->createRubberBand(parent);} }();
}

// tag=1050
// customEvent(QEvent * event)
void c_KDDockWidgets__ViewFactory__customEvent_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    // tag=1011

    // tag=1074
    fromWrapperPtr(thisObj)->customEvent_nocallback(event);
}

// tag=1050
// event(QEvent * event)
bool c_KDDockWidgets__ViewFactory__event_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->event_nocallback(event);} else {    return targetPtr->event(event);} }();
}

// tag=1050
// eventFilter(QObject * watched, QEvent * event)
bool c_KDDockWidgets__ViewFactory__eventFilter_QObject_QEvent(void *thisObj, void *watched_, void *event_)
{
    auto watched = reinterpret_cast<QObject *>(watched_);
    auto event = reinterpret_cast<QEvent *>(event_);
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->eventFilter_nocallback(watched,event);} else {    return targetPtr->eventFilter(watched,event);} }();
}

// tag=1050
// tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__ViewFactory__tr_char_char_int(const char *s, const char *c, int n)
{
    return
        // tag=1068

        // tag=1072
        new Dartagnan::ValueWrapper<QString> { KDDockWidgetsBindings_wrappersNS::ViewFactory_wrapper::tr(s, c, n) };
}
void c_KDDockWidgets__ViewFactory__destructor(void *thisObj)
{

    // tag=1055
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__ViewFactory__registerVirtualMethodCallback(void *ptr, void *callback, int methodId)
{
    // tag=1048
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 606:
        wrapper->m_createClassicIndicatorWindowCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_wrapper::Callback_createClassicIndicatorWindow>(callback);
        break;
    case 607:
        wrapper->m_createDropAreaCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_wrapper::Callback_createDropArea>(callback);
        break;
    case 608:
        wrapper->m_createRubberBandCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_wrapper::Callback_createRubberBand>(callback);
        break;
    case 295:
        wrapper->m_customEventCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_wrapper::Callback_customEvent>(callback);
        break;
    case 306:
        wrapper->m_eventCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_wrapper::Callback_event>(callback);
        break;
    case 307:
        wrapper->m_eventFilterCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_wrapper::Callback_eventFilter>(callback);
        break;
    }
}
}

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "ViewFactory_flutter_wrapper.h"


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
ViewFactory_flutter_wrapper::ViewFactory_flutter_wrapper()
    : ::KDDockWidgets::ViewFactory_flutter()
{
}
KDDockWidgets::Views::ClassicIndicatorWindowViewInterface *ViewFactory_flutter_wrapper::createClassicIndicatorWindow(KDDockWidgets::Controllers::ClassicIndicators *arg__1) const
{
    if (m_createClassicIndicatorWindowCallback) {
        const void *thisPtr = this;
        return m_createClassicIndicatorWindowCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        return ::KDDockWidgets::ViewFactory_flutter::createClassicIndicatorWindow(arg__1);
    }
}
KDDockWidgets::Views::ClassicIndicatorWindowViewInterface *ViewFactory_flutter_wrapper::createClassicIndicatorWindow_nocallback(KDDockWidgets::Controllers::ClassicIndicators *arg__1) const
{
    return ::KDDockWidgets::ViewFactory_flutter::createClassicIndicatorWindow(arg__1);
}
KDDockWidgets::View *ViewFactory_flutter_wrapper::createDropArea(KDDockWidgets::Controllers::DropArea *arg__1, KDDockWidgets::View *parent) const
{
    if (m_createDropAreaCallback) {
        const void *thisPtr = this;
        return m_createDropAreaCallback(const_cast<void *>(thisPtr), arg__1, parent);
    } else {
        return ::KDDockWidgets::ViewFactory_flutter::createDropArea(arg__1, parent);
    }
}
KDDockWidgets::View *ViewFactory_flutter_wrapper::createDropArea_nocallback(KDDockWidgets::Controllers::DropArea *arg__1, KDDockWidgets::View *parent) const
{
    return ::KDDockWidgets::ViewFactory_flutter::createDropArea(arg__1, parent);
}
KDDockWidgets::View *ViewFactory_flutter_wrapper::createRubberBand(KDDockWidgets::View *parent) const
{
    if (m_createRubberBandCallback) {
        const void *thisPtr = this;
        return m_createRubberBandCallback(const_cast<void *>(thisPtr), parent);
    } else {
        return ::KDDockWidgets::ViewFactory_flutter::createRubberBand(parent);
    }
}
KDDockWidgets::View *ViewFactory_flutter_wrapper::createRubberBand_nocallback(KDDockWidgets::View *parent) const
{
    return ::KDDockWidgets::ViewFactory_flutter::createRubberBand(parent);
}
void ViewFactory_flutter_wrapper::customEvent(QEvent *event)
{
    if (m_customEventCallback) {
        const void *thisPtr = this;
        m_customEventCallback(const_cast<void *>(thisPtr), event);
    } else {
        ::KDDockWidgets::ViewFactory_flutter::customEvent(event);
    }
}
void ViewFactory_flutter_wrapper::customEvent_nocallback(QEvent *event)
{
    ::KDDockWidgets::ViewFactory_flutter::customEvent(event);
}
bool ViewFactory_flutter_wrapper::event(QEvent *event)
{
    if (m_eventCallback) {
        const void *thisPtr = this;
        return m_eventCallback(const_cast<void *>(thisPtr), event);
    } else {
        return ::KDDockWidgets::ViewFactory_flutter::event(event);
    }
}
bool ViewFactory_flutter_wrapper::event_nocallback(QEvent *event)
{
    return ::KDDockWidgets::ViewFactory_flutter::event(event);
}
bool ViewFactory_flutter_wrapper::eventFilter(QObject *watched, QEvent *event)
{
    if (m_eventFilterCallback) {
        const void *thisPtr = this;
        return m_eventFilterCallback(const_cast<void *>(thisPtr), watched, event);
    } else {
        return ::KDDockWidgets::ViewFactory_flutter::eventFilter(watched, event);
    }
}
bool ViewFactory_flutter_wrapper::eventFilter_nocallback(QObject *watched, QEvent *event)
{
    return ::KDDockWidgets::ViewFactory_flutter::eventFilter(watched, event);
}
QString ViewFactory_flutter_wrapper::tr(const char *s, const char *c, int n)
{
    return ::KDDockWidgets::ViewFactory_flutter::tr(s, c, n);
}
ViewFactory_flutter_wrapper::~ViewFactory_flutter_wrapper()
{
}

}
static KDDockWidgets::ViewFactory_flutter *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::ViewFactory_flutter *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__ViewFactory_flutter_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper *>(cppObj);
}
void *c_KDDockWidgets__ViewFactory_flutter__constructor()
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper();
    return reinterpret_cast<void *>(ptr);
}
// createClassicIndicatorWindow(KDDockWidgets::Controllers::ClassicIndicators * arg__1) const
void *c_KDDockWidgets__ViewFactory_flutter__createClassicIndicatorWindow_ClassicIndicators(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::ClassicIndicators *>(arg__1_);
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->createClassicIndicatorWindow_nocallback(arg__1);} else {    return targetPtr->createClassicIndicatorWindow(arg__1);} }();
}
// createDropArea(KDDockWidgets::Controllers::DropArea * arg__1, KDDockWidgets::View * parent) const
void *c_KDDockWidgets__ViewFactory_flutter__createDropArea_DropArea_View(void *thisObj, void *arg__1_, void *parent_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::DropArea *>(arg__1_);
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->createDropArea_nocallback(arg__1,parent);} else {    return targetPtr->createDropArea(arg__1,parent);} }();
}
// createRubberBand(KDDockWidgets::View * parent) const
void *c_KDDockWidgets__ViewFactory_flutter__createRubberBand_View(void *thisObj, void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->createRubberBand_nocallback(parent);} else {    return targetPtr->createRubberBand(parent);} }();
}
// customEvent(QEvent * event)
void c_KDDockWidgets__ViewFactory_flutter__customEvent_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    fromWrapperPtr(thisObj)->customEvent_nocallback(event);
}
// event(QEvent * event)
bool c_KDDockWidgets__ViewFactory_flutter__event_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->event_nocallback(event);} else {    return targetPtr->event(event);} }();
}
// eventFilter(QObject * watched, QEvent * event)
bool c_KDDockWidgets__ViewFactory_flutter__eventFilter_QObject_QEvent(void *thisObj, void *watched_, void *event_)
{
    auto watched = reinterpret_cast<QObject *>(watched_);
    auto event = reinterpret_cast<QEvent *>(event_);
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->eventFilter_nocallback(watched,event);} else {    return targetPtr->eventFilter(watched,event);} }();
}
// tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__ViewFactory_flutter__tr_char_char_int(const char *s, const char *c, int n)
{
    return new Dartagnan::ValueWrapper<QString> { KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper::tr(s, c, n) };
}
void c_KDDockWidgets__ViewFactory_flutter__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__ViewFactory_flutter__registerVirtualMethodCallback(void *ptr, void *callback, int methodId)
{
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 681:
        wrapper->m_createClassicIndicatorWindowCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper::Callback_createClassicIndicatorWindow>(callback);
        break;
    case 682:
        wrapper->m_createDropAreaCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper::Callback_createDropArea>(callback);
        break;
    case 683:
        wrapper->m_createRubberBandCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper::Callback_createRubberBand>(callback);
        break;
    case 295:
        wrapper->m_customEventCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper::Callback_customEvent>(callback);
        break;
    case 306:
        wrapper->m_eventCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper::Callback_event>(callback);
        break;
    case 307:
        wrapper->m_eventFilterCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper::Callback_eventFilter>(callback);
        break;
    }
}
}

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
ViewFactory_wrapper::ViewFactory_wrapper()
    : ::KDDockWidgets::ViewFactory()
{
}
KDDockWidgets::Views::ClassicIndicatorWindowViewInterface *ViewFactory_wrapper::createClassicIndicatorWindow(KDDockWidgets::Controllers::ClassicIndicators *arg__1) const
{
    if (m_createClassicIndicatorWindowCallback) {
        const void *thisPtr = this;
        return m_createClassicIndicatorWindowCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
KDDockWidgets::Views::ClassicIndicatorWindowViewInterface *ViewFactory_wrapper::createClassicIndicatorWindow_nocallback(KDDockWidgets::Controllers::ClassicIndicators *arg__1) const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
KDDockWidgets::View *ViewFactory_wrapper::createDockWidget(const QString &uniqueName, QFlags<KDDockWidgets::DockWidgetOption> options, QFlags<KDDockWidgets::LayoutSaverOption> layoutSaverOptions, Qt::WindowFlags windowFlags) const
{
    if (m_createDockWidgetCallback) {
        const void *thisPtr = this;
        return m_createDockWidgetCallback(const_cast<void *>(thisPtr), uniqueName, options, layoutSaverOptions, windowFlags);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
KDDockWidgets::View *ViewFactory_wrapper::createDockWidget_nocallback(const QString &uniqueName, QFlags<KDDockWidgets::DockWidgetOption> options, QFlags<KDDockWidgets::LayoutSaverOption> layoutSaverOptions, Qt::WindowFlags windowFlags) const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
KDDockWidgets::View *ViewFactory_wrapper::createDropArea(KDDockWidgets::Controllers::DropArea *arg__1, KDDockWidgets::View *parent) const
{
    if (m_createDropAreaCallback) {
        const void *thisPtr = this;
        return m_createDropAreaCallback(const_cast<void *>(thisPtr), arg__1, parent);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
KDDockWidgets::View *ViewFactory_wrapper::createDropArea_nocallback(KDDockWidgets::Controllers::DropArea *arg__1, KDDockWidgets::View *parent) const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
KDDockWidgets::View *ViewFactory_wrapper::createRubberBand(KDDockWidgets::View *parent) const
{
    if (m_createRubberBandCallback) {
        const void *thisPtr = this;
        return m_createRubberBandCallback(const_cast<void *>(thisPtr), parent);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
KDDockWidgets::View *ViewFactory_wrapper::createRubberBand_nocallback(KDDockWidgets::View *parent) const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
void ViewFactory_wrapper::customEvent(QEvent *event)
{
    if (m_customEventCallback) {
        const void *thisPtr = this;
        m_customEventCallback(const_cast<void *>(thisPtr), event);
    } else {
        ::KDDockWidgets::ViewFactory::customEvent(event);
    }
}
void ViewFactory_wrapper::customEvent_nocallback(QEvent *event)
{
    ::KDDockWidgets::ViewFactory::customEvent(event);
}
bool ViewFactory_wrapper::event(QEvent *event)
{
    if (m_eventCallback) {
        const void *thisPtr = this;
        return m_eventCallback(const_cast<void *>(thisPtr), event);
    } else {
        return ::KDDockWidgets::ViewFactory::event(event);
    }
}
bool ViewFactory_wrapper::event_nocallback(QEvent *event)
{
    return ::KDDockWidgets::ViewFactory::event(event);
}
bool ViewFactory_wrapper::eventFilter(QObject *watched, QEvent *event)
{
    if (m_eventFilterCallback) {
        const void *thisPtr = this;
        return m_eventFilterCallback(const_cast<void *>(thisPtr), watched, event);
    } else {
        return ::KDDockWidgets::ViewFactory::eventFilter(watched, event);
    }
}
bool ViewFactory_wrapper::eventFilter_nocallback(QObject *watched, QEvent *event)
{
    return ::KDDockWidgets::ViewFactory::eventFilter(watched, event);
}
QString ViewFactory_wrapper::tr(const char *s, const char *c, int n)
{
    return ::KDDockWidgets::ViewFactory::tr(s, c, n);
}
ViewFactory_wrapper::~ViewFactory_wrapper()
{
}

}
static KDDockWidgets::ViewFactory *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::ViewFactory *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::ViewFactory_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__ViewFactory_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_wrapper *>(cppObj);
}
void *c_KDDockWidgets__ViewFactory__constructor()
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::ViewFactory_wrapper();
    return reinterpret_cast<void *>(ptr);
}
// createClassicIndicatorWindow(KDDockWidgets::Controllers::ClassicIndicators * arg__1) const
void *c_KDDockWidgets__ViewFactory__createClassicIndicatorWindow_ClassicIndicators(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::ClassicIndicators *>(arg__1_);
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->createClassicIndicatorWindow_nocallback(arg__1);} else {    return targetPtr->createClassicIndicatorWindow(arg__1);} }();
}
// createDockWidget(const QString & uniqueName, QFlags<KDDockWidgets::DockWidgetOption> options, QFlags<KDDockWidgets::LayoutSaverOption> layoutSaverOptions, Qt::WindowFlags windowFlags) const
void *c_KDDockWidgets__ViewFactory__createDockWidget_QString_DockWidgetOptions_LayoutSaverOptions_WindowFlags(void *thisObj, const char *uniqueName_, int options_, int layoutSaverOptions_, int windowFlags)
{
    const auto uniqueName = QString::fromUtf8(uniqueName_);
    auto options = static_cast<QFlags<KDDockWidgets::DockWidgetOption>>(options_);
    auto layoutSaverOptions = static_cast<QFlags<KDDockWidgets::LayoutSaverOption>>(layoutSaverOptions_);
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->createDockWidget_nocallback(uniqueName,options,layoutSaverOptions,static_cast<Qt::WindowFlags>(windowFlags));} else {    return targetPtr->createDockWidget(uniqueName,options,layoutSaverOptions,static_cast<Qt::WindowFlags>(windowFlags));} }();
}
// createDropArea(KDDockWidgets::Controllers::DropArea * arg__1, KDDockWidgets::View * parent) const
void *c_KDDockWidgets__ViewFactory__createDropArea_DropArea_View(void *thisObj, void *arg__1_, void *parent_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::DropArea *>(arg__1_);
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->createDropArea_nocallback(arg__1,parent);} else {    return targetPtr->createDropArea(arg__1,parent);} }();
}
// createRubberBand(KDDockWidgets::View * parent) const
void *c_KDDockWidgets__ViewFactory__createRubberBand_View(void *thisObj, void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->createRubberBand_nocallback(parent);} else {    return targetPtr->createRubberBand(parent);} }();
}
// customEvent(QEvent * event)
void c_KDDockWidgets__ViewFactory__customEvent_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    fromWrapperPtr(thisObj)->customEvent_nocallback(event);
}
// event(QEvent * event)
bool c_KDDockWidgets__ViewFactory__event_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->event_nocallback(event);} else {    return targetPtr->event(event);} }();
}
// eventFilter(QObject * watched, QEvent * event)
bool c_KDDockWidgets__ViewFactory__eventFilter_QObject_QEvent(void *thisObj, void *watched_, void *event_)
{
    auto watched = reinterpret_cast<QObject *>(watched_);
    auto event = reinterpret_cast<QEvent *>(event_);
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->eventFilter_nocallback(watched,event);} else {    return targetPtr->eventFilter(watched,event);} }();
}
// tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__ViewFactory__tr_char_char_int(const char *s, const char *c, int n)
{
    return new Dartagnan::ValueWrapper<QString> { KDDockWidgetsBindings_wrappersNS::ViewFactory_wrapper::tr(s, c, n) };
}
void c_KDDockWidgets__ViewFactory__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__ViewFactory__registerVirtualMethodCallback(void *ptr, void *callback, int methodId)
{
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 688:
        wrapper->m_createClassicIndicatorWindowCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_wrapper::Callback_createClassicIndicatorWindow>(callback);
        break;
    case 689:
        wrapper->m_createDockWidgetCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_wrapper::Callback_createDockWidget>(callback);
        break;
    case 690:
        wrapper->m_createDropAreaCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_wrapper::Callback_createDropArea>(callback);
        break;
    case 691:
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

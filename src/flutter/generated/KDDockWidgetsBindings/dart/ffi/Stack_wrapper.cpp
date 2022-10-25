/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "Stack_wrapper.h"


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
void Stack_wrapper::addDockWidget(KDDockWidgets::Controllers::DockWidget *arg__1)
{
    ::KDDockWidgets::Controllers::Stack::addDockWidget(arg__1);
}
bool Stack_wrapper::contains(KDDockWidgets::Controllers::DockWidget *dw) const
{
    return ::KDDockWidgets::Controllers::Stack::contains(dw);
}
void Stack_wrapper::customEvent(QEvent *event)
{
    if (m_customEventCallback) {
        const void *thisPtr = this;
        m_customEventCallback(const_cast<void *>(thisPtr), event);
    } else {
        ::KDDockWidgets::Controllers::Stack::customEvent(event);
    }
}
void Stack_wrapper::customEvent_nocallback(QEvent *event)
{
    ::KDDockWidgets::Controllers::Stack::customEvent(event);
}
bool Stack_wrapper::event(QEvent *event)
{
    if (m_eventCallback) {
        const void *thisPtr = this;
        return m_eventCallback(const_cast<void *>(thisPtr), event);
    } else {
        return ::KDDockWidgets::Controllers::Stack::event(event);
    }
}
bool Stack_wrapper::event_nocallback(QEvent *event)
{
    return ::KDDockWidgets::Controllers::Stack::event(event);
}
bool Stack_wrapper::eventFilter(QObject *watched, QEvent *event)
{
    if (m_eventFilterCallback) {
        const void *thisPtr = this;
        return m_eventFilterCallback(const_cast<void *>(thisPtr), watched, event);
    } else {
        return ::KDDockWidgets::Controllers::Stack::eventFilter(watched, event);
    }
}
bool Stack_wrapper::eventFilter_nocallback(QObject *watched, QEvent *event)
{
    return ::KDDockWidgets::Controllers::Stack::eventFilter(watched, event);
}
KDDockWidgets::Controllers::Group *Stack_wrapper::group() const
{
    return ::KDDockWidgets::Controllers::Stack::group();
}
bool Stack_wrapper::insertDockWidget(KDDockWidgets::Controllers::DockWidget *dockwidget, int index)
{
    return ::KDDockWidgets::Controllers::Stack::insertDockWidget(dockwidget, index);
}
bool Stack_wrapper::isMDI() const
{
    if (m_isMDICallback) {
        const void *thisPtr = this;
        return m_isMDICallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Controllers::Stack::isMDI();
    }
}
bool Stack_wrapper::isMDI_nocallback() const
{
    return ::KDDockWidgets::Controllers::Stack::isMDI();
}
bool Stack_wrapper::isPositionDraggable(QPoint p) const
{
    if (m_isPositionDraggableCallback) {
        const void *thisPtr = this;
        return m_isPositionDraggableCallback(const_cast<void *>(thisPtr), &p);
    } else {
        return ::KDDockWidgets::Controllers::Stack::isPositionDraggable(p);
    }
}
bool Stack_wrapper::isPositionDraggable_nocallback(QPoint p) const
{
    return ::KDDockWidgets::Controllers::Stack::isPositionDraggable(p);
}
bool Stack_wrapper::isWindow() const
{
    if (m_isWindowCallback) {
        const void *thisPtr = this;
        return m_isWindowCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Controllers::Stack::isWindow();
    }
}
bool Stack_wrapper::isWindow_nocallback() const
{
    return ::KDDockWidgets::Controllers::Stack::isWindow();
}
int Stack_wrapper::numDockWidgets() const
{
    return ::KDDockWidgets::Controllers::Stack::numDockWidgets();
}
bool Stack_wrapper::onMouseDoubleClick(QPoint localPos)
{
    return ::KDDockWidgets::Controllers::Stack::onMouseDoubleClick(localPos);
}
void Stack_wrapper::setDocumentMode(bool arg__1)
{
    ::KDDockWidgets::Controllers::Stack::setDocumentMode(arg__1);
}
void Stack_wrapper::setParentView_impl(KDDockWidgets::View *parent)
{
    if (m_setParentView_implCallback) {
        const void *thisPtr = this;
        m_setParentView_implCallback(const_cast<void *>(thisPtr), parent);
    } else {
        ::KDDockWidgets::Controllers::Stack::setParentView_impl(parent);
    }
}
void Stack_wrapper::setParentView_impl_nocallback(KDDockWidgets::View *parent)
{
    ::KDDockWidgets::Controllers::Stack::setParentView_impl(parent);
}
void Stack_wrapper::setTabBarAutoHide(bool arg__1)
{
    ::KDDockWidgets::Controllers::Stack::setTabBarAutoHide(arg__1);
}
KDDockWidgets::Controllers::DockWidget *Stack_wrapper::singleDockWidget() const
{
    if (m_singleDockWidgetCallback) {
        const void *thisPtr = this;
        return m_singleDockWidgetCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Controllers::Stack::singleDockWidget();
    }
}
KDDockWidgets::Controllers::DockWidget *Stack_wrapper::singleDockWidget_nocallback() const
{
    return ::KDDockWidgets::Controllers::Stack::singleDockWidget();
}
KDDockWidgets::Controllers::TabBar *Stack_wrapper::tabBar() const
{
    return ::KDDockWidgets::Controllers::Stack::tabBar();
}
bool Stack_wrapper::tabBarAutoHide() const
{
    return ::KDDockWidgets::Controllers::Stack::tabBarAutoHide();
}
QString Stack_wrapper::tr(const char *s, const char *c, int n)
{
    return ::KDDockWidgets::Controllers::Stack::tr(s, c, n);
}
Stack_wrapper::~Stack_wrapper()
{
}

}
static KDDockWidgets::Controllers::Stack *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::Controllers::Stack *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::Stack_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Stack_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__Controllers__Stack_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Stack_wrapper *>(cppObj);
} // addDockWidget(KDDockWidgets::Controllers::DockWidget * arg__1)
void c_KDDockWidgets__Controllers__Stack__addDockWidget_DockWidget(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::DockWidget *>(arg__1_);
    fromPtr(thisObj)->addDockWidget(arg__1);
}
// contains(KDDockWidgets::Controllers::DockWidget * dw) const
bool c_KDDockWidgets__Controllers__Stack__contains_DockWidget(void *thisObj, void *dw_)
{
    auto dw = reinterpret_cast<KDDockWidgets::Controllers::DockWidget *>(dw_);
    return fromPtr(thisObj)->contains(dw);
}
// customEvent(QEvent * event)
void c_KDDockWidgets__Controllers__Stack__customEvent_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    fromWrapperPtr(thisObj)->customEvent_nocallback(event);
}
// event(QEvent * event)
bool c_KDDockWidgets__Controllers__Stack__event_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Stack_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->event_nocallback(event);
        } else {
            return targetPtr->event(event);
        }
    }();
}
// eventFilter(QObject * watched, QEvent * event)
bool c_KDDockWidgets__Controllers__Stack__eventFilter_QObject_QEvent(void *thisObj, void *watched_,
                                                                     void *event_)
{
    auto watched = reinterpret_cast<QObject *>(watched_);
    auto event = reinterpret_cast<QEvent *>(event_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Stack_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->eventFilter_nocallback(watched, event);
        } else {
            return targetPtr->eventFilter(watched, event);
        }
    }();
}
// group() const
void *c_KDDockWidgets__Controllers__Stack__group(void *thisObj)
{
    return fromPtr(thisObj)->group();
}
// insertDockWidget(KDDockWidgets::Controllers::DockWidget * dockwidget, int index)
bool c_KDDockWidgets__Controllers__Stack__insertDockWidget_DockWidget_int(void *thisObj,
                                                                          void *dockwidget_,
                                                                          int index)
{
    auto dockwidget = reinterpret_cast<KDDockWidgets::Controllers::DockWidget *>(dockwidget_);
    return fromPtr(thisObj)->insertDockWidget(dockwidget, index);
}
// isMDI() const
bool c_KDDockWidgets__Controllers__Stack__isMDI(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Stack_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->isMDI_nocallback();
        } else {
            return targetPtr->isMDI();
        }
    }();
}
// isPositionDraggable(QPoint p) const
bool c_KDDockWidgets__Controllers__Stack__isPositionDraggable_QPoint(void *thisObj, void *p_)
{
    assert(p_);
    auto &p = *reinterpret_cast<QPoint *>(p_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Stack_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->isPositionDraggable_nocallback(p);
        } else {
            return targetPtr->isPositionDraggable(p);
        }
    }();
}
// isWindow() const
bool c_KDDockWidgets__Controllers__Stack__isWindow(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Stack_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->isWindow_nocallback();
        } else {
            return targetPtr->isWindow();
        }
    }();
}
// numDockWidgets() const
int c_KDDockWidgets__Controllers__Stack__numDockWidgets(void *thisObj)
{
    return fromPtr(thisObj)->numDockWidgets();
}
// onMouseDoubleClick(QPoint localPos)
bool c_KDDockWidgets__Controllers__Stack__onMouseDoubleClick_QPoint(void *thisObj, void *localPos_)
{
    assert(localPos_);
    auto &localPos = *reinterpret_cast<QPoint *>(localPos_);
    return fromPtr(thisObj)->onMouseDoubleClick(localPos);
}
// setDocumentMode(bool arg__1)
void c_KDDockWidgets__Controllers__Stack__setDocumentMode_bool(void *thisObj, bool arg__1)
{
    fromPtr(thisObj)->setDocumentMode(arg__1);
}
// setParentView_impl(KDDockWidgets::View * parent)
void c_KDDockWidgets__Controllers__Stack__setParentView_impl_View(void *thisObj, void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    fromWrapperPtr(thisObj)->setParentView_impl_nocallback(parent);
}
// setTabBarAutoHide(bool arg__1)
void c_KDDockWidgets__Controllers__Stack__setTabBarAutoHide_bool(void *thisObj, bool arg__1)
{
    fromPtr(thisObj)->setTabBarAutoHide(arg__1);
}
// singleDockWidget() const
void *c_KDDockWidgets__Controllers__Stack__singleDockWidget(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Stack_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->singleDockWidget_nocallback();
        } else {
            return targetPtr->singleDockWidget();
        }
    }();
}
// tabBar() const
void *c_KDDockWidgets__Controllers__Stack__tabBar(void *thisObj)
{
    return fromPtr(thisObj)->tabBar();
}
// tabBarAutoHide() const
bool c_KDDockWidgets__Controllers__Stack__tabBarAutoHide(void *thisObj)
{
    return fromPtr(thisObj)->tabBarAutoHide();
}
// tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__Controllers__Stack__tr_char_char_int(const char *s, const char *c,
                                                                   int n)
{
    return new Dartagnan::ValueWrapper<QString> {
        KDDockWidgetsBindings_wrappersNS::Stack_wrapper::tr(s, c, n)
    };
}
void c_KDDockWidgets__Controllers__Stack__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__Controllers__Stack__registerVirtualMethodCallback(void *ptr, void *callback,
                                                                        int methodId)
{
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 295:
        wrapper->m_customEventCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Stack_wrapper::Callback_customEvent>(
                callback);
        break;
    case 306:
        wrapper->m_eventCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Stack_wrapper::Callback_event>(
                callback);
        break;
    case 307:
        wrapper->m_eventFilterCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Stack_wrapper::Callback_eventFilter>(
                callback);
        break;
    case 1199:
        wrapper->m_isMDICallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Stack_wrapper::Callback_isMDI>(
                callback);
        break;
    case 1200:
        wrapper->m_isPositionDraggableCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Stack_wrapper::Callback_isPositionDraggable>(
            callback);
        break;
    case 1202:
        wrapper->m_isWindowCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Stack_wrapper::Callback_isWindow>(
                callback);
        break;
    case 891:
        wrapper->m_setParentView_implCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Stack_wrapper::Callback_setParentView_impl>(callback);
        break;
    case 1214:
        wrapper->m_singleDockWidgetCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Stack_wrapper::Callback_singleDockWidget>(callback);
        break;
    }
}
}

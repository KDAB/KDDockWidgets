/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "SideBar_wrapper.h"


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
void SideBar_wrapper::addDockWidget(KDDockWidgets::Controllers::DockWidget *dw)
{
    ::KDDockWidgets::Controllers::SideBar::addDockWidget(dw);
}
void SideBar_wrapper::clear()
{
    ::KDDockWidgets::Controllers::SideBar::clear();
}
bool SideBar_wrapper::containsDockWidget(KDDockWidgets::Controllers::DockWidget *arg__1) const
{
    return ::KDDockWidgets::Controllers::SideBar::containsDockWidget(arg__1);
}
void SideBar_wrapper::customEvent(QEvent *event)
{
    if (m_customEventCallback) {
        const void *thisPtr = this;
        m_customEventCallback(const_cast<void *>(thisPtr), event);
    } else {
        ::KDDockWidgets::Controllers::SideBar::customEvent(event);
    }
}
void SideBar_wrapper::customEvent_nocallback(QEvent *event)
{
    ::KDDockWidgets::Controllers::SideBar::customEvent(event);
}
bool SideBar_wrapper::event(QEvent *event)
{
    if (m_eventCallback) {
        const void *thisPtr = this;
        return m_eventCallback(const_cast<void *>(thisPtr), event);
    } else {
        return ::KDDockWidgets::Controllers::SideBar::event(event);
    }
}
bool SideBar_wrapper::event_nocallback(QEvent *event)
{
    return ::KDDockWidgets::Controllers::SideBar::event(event);
}
bool SideBar_wrapper::eventFilter(QObject *watched, QEvent *event)
{
    if (m_eventFilterCallback) {
        const void *thisPtr = this;
        return m_eventFilterCallback(const_cast<void *>(thisPtr), watched, event);
    } else {
        return ::KDDockWidgets::Controllers::SideBar::eventFilter(watched, event);
    }
}
bool SideBar_wrapper::eventFilter_nocallback(QObject *watched, QEvent *event)
{
    return ::KDDockWidgets::Controllers::SideBar::eventFilter(watched, event);
}
bool SideBar_wrapper::isEmpty() const
{
    return ::KDDockWidgets::Controllers::SideBar::isEmpty();
}
bool SideBar_wrapper::isVertical() const
{
    return ::KDDockWidgets::Controllers::SideBar::isVertical();
}
KDDockWidgets::Controllers::MainWindow *SideBar_wrapper::mainWindow() const
{
    return ::KDDockWidgets::Controllers::SideBar::mainWindow();
}
void SideBar_wrapper::onButtonClicked(KDDockWidgets::Controllers::DockWidget *dw)
{
    ::KDDockWidgets::Controllers::SideBar::onButtonClicked(dw);
}
void SideBar_wrapper::removeDockWidget(KDDockWidgets::Controllers::DockWidget *dw)
{
    ::KDDockWidgets::Controllers::SideBar::removeDockWidget(dw);
}
void SideBar_wrapper::setParentView_impl(KDDockWidgets::View *parent)
{
    if (m_setParentView_implCallback) {
        const void *thisPtr = this;
        m_setParentView_implCallback(const_cast<void *>(thisPtr), parent);
    } else {
        ::KDDockWidgets::Controllers::SideBar::setParentView_impl(parent);
    }
}
void SideBar_wrapper::setParentView_impl_nocallback(KDDockWidgets::View *parent)
{
    ::KDDockWidgets::Controllers::SideBar::setParentView_impl(parent);
}
void SideBar_wrapper::toggleOverlay(KDDockWidgets::Controllers::DockWidget *arg__1)
{
    ::KDDockWidgets::Controllers::SideBar::toggleOverlay(arg__1);
}
QString SideBar_wrapper::tr(const char *s, const char *c, int n)
{
    return ::KDDockWidgets::Controllers::SideBar::tr(s, c, n);
}
SideBar_wrapper::~SideBar_wrapper()
{
}

}
static KDDockWidgets::Controllers::SideBar *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::Controllers::SideBar *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::SideBar_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::SideBar_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__Controllers__SideBar_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::SideBar_wrapper *>(cppObj);
} // addDockWidget(KDDockWidgets::Controllers::DockWidget * dw)
void c_KDDockWidgets__Controllers__SideBar__addDockWidget_DockWidget(void *thisObj, void *dw_)
{
    auto dw = reinterpret_cast<KDDockWidgets::Controllers::DockWidget *>(dw_);
    fromPtr(thisObj)->addDockWidget(dw);
}
// clear()
void c_KDDockWidgets__Controllers__SideBar__clear(void *thisObj)
{
    fromPtr(thisObj)->clear();
}
// containsDockWidget(KDDockWidgets::Controllers::DockWidget * arg__1) const
bool c_KDDockWidgets__Controllers__SideBar__containsDockWidget_DockWidget(void *thisObj,
                                                                          void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::DockWidget *>(arg__1_);
    return fromPtr(thisObj)->containsDockWidget(arg__1);
}
// customEvent(QEvent * event)
void c_KDDockWidgets__Controllers__SideBar__customEvent_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    fromWrapperPtr(thisObj)->customEvent_nocallback(event);
}
// event(QEvent * event)
bool c_KDDockWidgets__Controllers__SideBar__event_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::SideBar_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->event_nocallback(event);
        } else {
            return targetPtr->event(event);
        }
    }();
}
// eventFilter(QObject * watched, QEvent * event)
bool c_KDDockWidgets__Controllers__SideBar__eventFilter_QObject_QEvent(void *thisObj,
                                                                       void *watched_, void *event_)
{
    auto watched = reinterpret_cast<QObject *>(watched_);
    auto event = reinterpret_cast<QEvent *>(event_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::SideBar_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->eventFilter_nocallback(watched, event);
        } else {
            return targetPtr->eventFilter(watched, event);
        }
    }();
}
// isEmpty() const
bool c_KDDockWidgets__Controllers__SideBar__isEmpty(void *thisObj)
{
    return fromPtr(thisObj)->isEmpty();
}
// isVertical() const
bool c_KDDockWidgets__Controllers__SideBar__isVertical(void *thisObj)
{
    return fromPtr(thisObj)->isVertical();
}
// mainWindow() const
void *c_KDDockWidgets__Controllers__SideBar__mainWindow(void *thisObj)
{
    return fromPtr(thisObj)->mainWindow();
}
// onButtonClicked(KDDockWidgets::Controllers::DockWidget * dw)
void c_KDDockWidgets__Controllers__SideBar__onButtonClicked_DockWidget(void *thisObj, void *dw_)
{
    auto dw = reinterpret_cast<KDDockWidgets::Controllers::DockWidget *>(dw_);
    fromPtr(thisObj)->onButtonClicked(dw);
}
// removeDockWidget(KDDockWidgets::Controllers::DockWidget * dw)
void c_KDDockWidgets__Controllers__SideBar__removeDockWidget_DockWidget(void *thisObj, void *dw_)
{
    auto dw = reinterpret_cast<KDDockWidgets::Controllers::DockWidget *>(dw_);
    fromPtr(thisObj)->removeDockWidget(dw);
}
// setParentView_impl(KDDockWidgets::View * parent)
void c_KDDockWidgets__Controllers__SideBar__setParentView_impl_View(void *thisObj, void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    fromWrapperPtr(thisObj)->setParentView_impl_nocallback(parent);
}
// toggleOverlay(KDDockWidgets::Controllers::DockWidget * arg__1)
void c_KDDockWidgets__Controllers__SideBar__toggleOverlay_DockWidget(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::DockWidget *>(arg__1_);
    fromPtr(thisObj)->toggleOverlay(arg__1);
}
// tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__Controllers__SideBar__tr_char_char_int(const char *s, const char *c,
                                                                     int n)
{
    return new Dartagnan::ValueWrapper<QString> {
        KDDockWidgetsBindings_wrappersNS::SideBar_wrapper::tr(s, c, n)
    };
}
void c_KDDockWidgets__Controllers__SideBar__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__Controllers__SideBar__registerVirtualMethodCallback(void *ptr, void *callback,
                                                                          int methodId)
{
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 295:
        wrapper->m_customEventCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::SideBar_wrapper::Callback_customEvent>(callback);
        break;
    case 306:
        wrapper->m_eventCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::SideBar_wrapper::Callback_event>(
                callback);
        break;
    case 307:
        wrapper->m_eventFilterCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::SideBar_wrapper::Callback_eventFilter>(callback);
        break;
    case 828:
        wrapper->m_setParentView_implCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::SideBar_wrapper::Callback_setParentView_impl>(
            callback);
        break;
    }
}
}

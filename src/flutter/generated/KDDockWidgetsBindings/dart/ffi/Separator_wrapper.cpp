/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "Separator_wrapper.h"


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
Separator_wrapper::Separator_wrapper(KDDockWidgets::View *host)
    : ::KDDockWidgets::Controllers::Separator(host)
{
}
void Separator_wrapper::customEvent(QEvent *event)
{
    if (m_customEventCallback) {
        const void *thisPtr = this;
        m_customEventCallback(const_cast<void *>(thisPtr), event);
    } else {
        ::KDDockWidgets::Controllers::Separator::customEvent(event);
    }
}
void Separator_wrapper::customEvent_nocallback(QEvent *event)
{
    ::KDDockWidgets::Controllers::Separator::customEvent(event);
}
bool Separator_wrapper::event(QEvent *event)
{
    if (m_eventCallback) {
        const void *thisPtr = this;
        return m_eventCallback(const_cast<void *>(thisPtr), event);
    } else {
        return ::KDDockWidgets::Controllers::Separator::event(event);
    }
}
bool Separator_wrapper::event_nocallback(QEvent *event)
{
    return ::KDDockWidgets::Controllers::Separator::event(event);
}
bool Separator_wrapper::eventFilter(QObject *watched, QEvent *event)
{
    if (m_eventFilterCallback) {
        const void *thisPtr = this;
        return m_eventFilterCallback(const_cast<void *>(thisPtr), watched, event);
    } else {
        return ::KDDockWidgets::Controllers::Separator::eventFilter(watched, event);
    }
}
bool Separator_wrapper::eventFilter_nocallback(QObject *watched, QEvent *event)
{
    return ::KDDockWidgets::Controllers::Separator::eventFilter(watched, event);
}
bool Separator_wrapper::isResizing()
{
    return ::KDDockWidgets::Controllers::Separator::isResizing();
}
bool Separator_wrapper::isVertical() const
{
    return ::KDDockWidgets::Controllers::Separator::isVertical();
}
void Separator_wrapper::move(int p)
{
    ::KDDockWidgets::Controllers::Separator::move(p);
}
int Separator_wrapper::numSeparators()
{
    return ::KDDockWidgets::Controllers::Separator::numSeparators();
}
void Separator_wrapper::onMouseDoubleClick()
{
    ::KDDockWidgets::Controllers::Separator::onMouseDoubleClick();
}
void Separator_wrapper::onMouseMove(QPoint pos)
{
    ::KDDockWidgets::Controllers::Separator::onMouseMove(pos);
}
void Separator_wrapper::onMousePress()
{
    ::KDDockWidgets::Controllers::Separator::onMousePress();
}
void Separator_wrapper::onMouseReleased()
{
    ::KDDockWidgets::Controllers::Separator::onMouseReleased();
}
int Separator_wrapper::position() const
{
    return ::KDDockWidgets::Controllers::Separator::position();
}
void Separator_wrapper::setGeometry(QRect r)
{
    ::KDDockWidgets::Controllers::Separator::setGeometry(r);
}
void Separator_wrapper::setGeometry(int pos, int pos2, int length)
{
    ::KDDockWidgets::Controllers::Separator::setGeometry(pos, pos2, length);
}
void Separator_wrapper::setParentView_impl(KDDockWidgets::View *parent)
{
    if (m_setParentView_implCallback) {
        const void *thisPtr = this;
        m_setParentView_implCallback(const_cast<void *>(thisPtr), parent);
    } else {
        ::KDDockWidgets::Controllers::Separator::setParentView_impl(parent);
    }
}
void Separator_wrapper::setParentView_impl_nocallback(KDDockWidgets::View *parent)
{
    ::KDDockWidgets::Controllers::Separator::setParentView_impl(parent);
}
Separator_wrapper::~Separator_wrapper()
{
}

}
static KDDockWidgets::Controllers::Separator *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::Controllers::Separator *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::Separator_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Separator_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__Controllers__Separator_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Separator_wrapper *>(cppObj);
}
void *c_KDDockWidgets__Controllers__Separator__constructor_View(void *host_)
{
    auto host = reinterpret_cast<KDDockWidgets::View *>(host_);
    auto ptr = new KDDockWidgetsBindings_wrappersNS::Separator_wrapper(host);
    return reinterpret_cast<void *>(ptr);
}
// customEvent(QEvent * event)
void c_KDDockWidgets__Controllers__Separator__customEvent_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    fromWrapperPtr(thisObj)->customEvent_nocallback(event);
}
// event(QEvent * event)
bool c_KDDockWidgets__Controllers__Separator__event_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Separator_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->event_nocallback(event);
        } else {
            return targetPtr->event(event);
        }
    }();
}
// eventFilter(QObject * watched, QEvent * event)
bool c_KDDockWidgets__Controllers__Separator__eventFilter_QObject_QEvent(void *thisObj,
                                                                         void *watched_,
                                                                         void *event_)
{
    auto watched = reinterpret_cast<QObject *>(watched_);
    auto event = reinterpret_cast<QEvent *>(event_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Separator_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->eventFilter_nocallback(watched, event);
        } else {
            return targetPtr->eventFilter(watched, event);
        }
    }();
}
// isResizing()
bool c_static_KDDockWidgets__Controllers__Separator__isResizing()
{
    return KDDockWidgetsBindings_wrappersNS::Separator_wrapper::isResizing();
}
// isVertical() const
bool c_KDDockWidgets__Controllers__Separator__isVertical(void *thisObj)
{
    return fromPtr(thisObj)->isVertical();
}
// move(int p)
void c_KDDockWidgets__Controllers__Separator__move_int(void *thisObj, int p)
{
    fromPtr(thisObj)->move(p);
}
// numSeparators()
int c_static_KDDockWidgets__Controllers__Separator__numSeparators()
{
    return KDDockWidgetsBindings_wrappersNS::Separator_wrapper::numSeparators();
}
// onMouseDoubleClick()
void c_KDDockWidgets__Controllers__Separator__onMouseDoubleClick(void *thisObj)
{
    fromPtr(thisObj)->onMouseDoubleClick();
}
// onMouseMove(QPoint pos)
void c_KDDockWidgets__Controllers__Separator__onMouseMove_QPoint(void *thisObj, void *pos_)
{
    assert(pos_);
    auto &pos = *reinterpret_cast<QPoint *>(pos_);
    fromPtr(thisObj)->onMouseMove(pos);
}
// onMousePress()
void c_KDDockWidgets__Controllers__Separator__onMousePress(void *thisObj)
{
    fromPtr(thisObj)->onMousePress();
}
// onMouseReleased()
void c_KDDockWidgets__Controllers__Separator__onMouseReleased(void *thisObj)
{
    fromPtr(thisObj)->onMouseReleased();
}
// position() const
int c_KDDockWidgets__Controllers__Separator__position(void *thisObj)
{
    return fromPtr(thisObj)->position();
}
// setGeometry(QRect r)
void c_KDDockWidgets__Controllers__Separator__setGeometry_QRect(void *thisObj, void *r_)
{
    assert(r_);
    auto &r = *reinterpret_cast<QRect *>(r_);
    fromPtr(thisObj)->setGeometry(r);
}
// setGeometry(int pos, int pos2, int length)
void c_KDDockWidgets__Controllers__Separator__setGeometry_int_int_int(void *thisObj, int pos,
                                                                      int pos2, int length)
{
    fromPtr(thisObj)->setGeometry(pos, pos2, length);
}
// setParentView_impl(KDDockWidgets::View * parent)
void c_KDDockWidgets__Controllers__Separator__setParentView_impl_View(void *thisObj, void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    fromWrapperPtr(thisObj)->setParentView_impl_nocallback(parent);
}
void c_KDDockWidgets__Controllers__Separator__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__Controllers__Separator__registerVirtualMethodCallback(void *ptr,
                                                                            void *callback,
                                                                            int methodId)
{
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 295:
        wrapper->m_customEventCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Separator_wrapper::Callback_customEvent>(callback);
        break;
    case 306:
        wrapper->m_eventCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Separator_wrapper::Callback_event>(
                callback);
        break;
    case 307:
        wrapper->m_eventFilterCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Separator_wrapper::Callback_eventFilter>(callback);
        break;
    case 891:
        wrapper->m_setParentView_implCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Separator_wrapper::Callback_setParentView_impl>(
            callback);
        break;
    }
}
}

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "Layout_wrapper.h"


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
Layout_wrapper::Layout_wrapper(KDDockWidgets::Type arg__1, KDDockWidgets::View *arg__2)
    : ::KDDockWidgets::Controllers::Layout(arg__1, arg__2)
{
}
KDDockWidgets::Controllers::DropArea *Layout_wrapper::asDropArea() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Controllers::Layout::asDropArea();
}
bool Layout_wrapper::checkSanity() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Controllers::Layout::checkSanity();
}
void Layout_wrapper::clearLayout()
{
    // tag=1000

    // tag=1004
    ::KDDockWidgets::Controllers::Layout::clearLayout();
}
int Layout_wrapper::count() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Controllers::Layout::count();
}
void Layout_wrapper::customEvent(QEvent *event)
{
    // tag=1000
    if (m_customEventCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_customEventCallback(const_cast<void *>(thisPtr), event);
    } else {
        // tag=1002
        ::KDDockWidgets::Controllers::Layout::customEvent(event);
    }
}
// tag=1009
void Layout_wrapper::customEvent_nocallback(QEvent *event)
{
    // tag=1003
    ::KDDockWidgets::Controllers::Layout::customEvent(event);
}
void Layout_wrapper::dumpLayout() const
{
    // tag=1000

    // tag=1004
    ::KDDockWidgets::Controllers::Layout::dumpLayout();
}
bool Layout_wrapper::event(QEvent *event)
{
    // tag=1000
    if (m_eventCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_eventCallback(const_cast<void *>(thisPtr), event);
    } else {
        // tag=1002
        return ::KDDockWidgets::Controllers::Layout::event(event);
    }
}
// tag=1009
bool Layout_wrapper::event_nocallback(QEvent *event)
{
    // tag=1003
    return ::KDDockWidgets::Controllers::Layout::event(event);
}
bool Layout_wrapper::eventFilter(QObject *watched, QEvent *event)
{
    // tag=1000
    if (m_eventFilterCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_eventFilterCallback(const_cast<void *>(thisPtr), watched, event);
    } else {
        // tag=1002
        return ::KDDockWidgets::Controllers::Layout::eventFilter(watched, event);
    }
}
// tag=1009
bool Layout_wrapper::eventFilter_nocallback(QObject *watched, QEvent *event)
{
    // tag=1003
    return ::KDDockWidgets::Controllers::Layout::eventFilter(watched, event);
}
bool Layout_wrapper::isInMainWindow(bool honourNesting) const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Controllers::Layout::isInMainWindow(honourNesting);
}
int Layout_wrapper::layoutHeight() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Controllers::Layout::layoutHeight();
}
QSize Layout_wrapper::layoutMaximumSizeHint() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Controllers::Layout::layoutMaximumSizeHint();
}
QSize Layout_wrapper::layoutMinimumSize() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Controllers::Layout::layoutMinimumSize();
}
QSize Layout_wrapper::layoutSize() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Controllers::Layout::layoutSize();
}
int Layout_wrapper::layoutWidth() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Controllers::Layout::layoutWidth();
}
int Layout_wrapper::placeholderCount() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Controllers::Layout::placeholderCount();
}
void Layout_wrapper::setLayoutMinimumSize(QSize arg__1)
{
    // tag=1000

    // tag=1004
    ::KDDockWidgets::Controllers::Layout::setLayoutMinimumSize(arg__1);
}
void Layout_wrapper::setLayoutSize(QSize arg__1)
{
    // tag=1000

    // tag=1004
    ::KDDockWidgets::Controllers::Layout::setLayoutSize(arg__1);
}
void Layout_wrapper::setParentView_impl(KDDockWidgets::View *parent)
{
    // tag=1000
    if (m_setParentView_implCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setParentView_implCallback(const_cast<void *>(thisPtr), parent);
    } else {
        // tag=1002
        ::KDDockWidgets::Controllers::Layout::setParentView_impl(parent);
    }
}
// tag=1009
void Layout_wrapper::setParentView_impl_nocallback(KDDockWidgets::View *parent)
{
    // tag=1003
    ::KDDockWidgets::Controllers::Layout::setParentView_impl(parent);
}
void Layout_wrapper::updateSizeConstraints()
{
    // tag=1000

    // tag=1004
    ::KDDockWidgets::Controllers::Layout::updateSizeConstraints();
}
void Layout_wrapper::viewAboutToBeDeleted()
{
    // tag=1000

    // tag=1004
    ::KDDockWidgets::Controllers::Layout::viewAboutToBeDeleted();
}
int Layout_wrapper::visibleCount() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Controllers::Layout::visibleCount();
}

// tag=1005
Layout_wrapper::~Layout_wrapper()
{
}

}
// tag=1013
static KDDockWidgets::Controllers::Layout *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::Controllers::Layout *>(ptr);
}
// tag=1014
static KDDockWidgetsBindings_wrappersNS::Layout_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Layout_wrapper *>(ptr);
}
extern "C" {

// tag=1049
void c_KDDockWidgets__Controllers__Layout_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Layout_wrapper *>(cppObj);
}
void *c_KDDockWidgets__Controllers__Layout__constructor_Type_View(int arg__1, void *arg__2_)
{
    auto arg__2 = reinterpret_cast<KDDockWidgets::View *>(arg__2_);
    // tag=1056
    auto ptr = new KDDockWidgetsBindings_wrappersNS::Layout_wrapper(static_cast<KDDockWidgets::Type>(arg__1), arg__2);
    return reinterpret_cast<void *>(ptr);
}

// tag=1050
// asDropArea() const
void *c_KDDockWidgets__Controllers__Layout__asDropArea(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->asDropArea();
}

// tag=1050
// checkSanity() const
bool c_KDDockWidgets__Controllers__Layout__checkSanity(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->checkSanity();
}

// tag=1050
// clearLayout()
void c_KDDockWidgets__Controllers__Layout__clearLayout(void *thisObj)
{
    // tag=1010
    fromPtr(thisObj)->clearLayout();
}

// tag=1050
// count() const
int c_KDDockWidgets__Controllers__Layout__count(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->count();
}

// tag=1050
// customEvent(QEvent * event)
void c_KDDockWidgets__Controllers__Layout__customEvent_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    // tag=1011

    // tag=1074
    fromWrapperPtr(thisObj)->customEvent_nocallback(event);
}

// tag=1050
// dumpLayout() const
void c_KDDockWidgets__Controllers__Layout__dumpLayout(void *thisObj)
{
    // tag=1010
    fromPtr(thisObj)->dumpLayout();
}

// tag=1050
// event(QEvent * event)
bool c_KDDockWidgets__Controllers__Layout__event_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Layout_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->event_nocallback(event);} else {    return targetPtr->event(event);} }();
}

// tag=1050
// eventFilter(QObject * watched, QEvent * event)
bool c_KDDockWidgets__Controllers__Layout__eventFilter_QObject_QEvent(void *thisObj, void *watched_, void *event_)
{
    auto watched = reinterpret_cast<QObject *>(watched_);
    auto event = reinterpret_cast<QEvent *>(event_);
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Layout_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->eventFilter_nocallback(watched,event);} else {    return targetPtr->eventFilter(watched,event);} }();
}

// tag=1050
// isInMainWindow(bool honourNesting) const
bool c_KDDockWidgets__Controllers__Layout__isInMainWindow_bool(void *thisObj, bool honourNesting)
{
    return
        // tag=1010
        fromPtr(thisObj)->isInMainWindow(honourNesting);
}

// tag=1050
// layoutHeight() const
int c_KDDockWidgets__Controllers__Layout__layoutHeight(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->layoutHeight();
}

// tag=1050
// layoutMaximumSizeHint() const
void *c_KDDockWidgets__Controllers__Layout__layoutMaximumSizeHint(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QSize> { fromPtr(thisObj)->layoutMaximumSizeHint() };
}

// tag=1050
// layoutMinimumSize() const
void *c_KDDockWidgets__Controllers__Layout__layoutMinimumSize(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QSize> { fromPtr(thisObj)->layoutMinimumSize() };
}

// tag=1050
// layoutSize() const
void *c_KDDockWidgets__Controllers__Layout__layoutSize(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QSize> { fromPtr(thisObj)->layoutSize() };
}

// tag=1050
// layoutWidth() const
int c_KDDockWidgets__Controllers__Layout__layoutWidth(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->layoutWidth();
}

// tag=1050
// placeholderCount() const
int c_KDDockWidgets__Controllers__Layout__placeholderCount(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->placeholderCount();
}

// tag=1050
// setLayoutMinimumSize(QSize arg__1)
void c_KDDockWidgets__Controllers__Layout__setLayoutMinimumSize_QSize(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QSize *>(arg__1_);
    // tag=1011

    // tag=1073
    fromWrapperPtr(thisObj)->setLayoutMinimumSize(arg__1);
}

// tag=1050
// setLayoutSize(QSize arg__1)
void c_KDDockWidgets__Controllers__Layout__setLayoutSize_QSize(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QSize *>(arg__1_);
    // tag=1010
    fromPtr(thisObj)->setLayoutSize(arg__1);
}

// tag=1050
// setParentView_impl(KDDockWidgets::View * parent)
void c_KDDockWidgets__Controllers__Layout__setParentView_impl_View(void *thisObj, void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    // tag=1011

    // tag=1074
    fromWrapperPtr(thisObj)->setParentView_impl_nocallback(parent);
}

// tag=1050
// updateSizeConstraints()
void c_KDDockWidgets__Controllers__Layout__updateSizeConstraints(void *thisObj)
{
    // tag=1010
    fromPtr(thisObj)->updateSizeConstraints();
}

// tag=1050
// viewAboutToBeDeleted()
void c_KDDockWidgets__Controllers__Layout__viewAboutToBeDeleted(void *thisObj)
{
    // tag=1010
    fromPtr(thisObj)->viewAboutToBeDeleted();
}

// tag=1050
// visibleCount() const
int c_KDDockWidgets__Controllers__Layout__visibleCount(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->visibleCount();
}
void c_KDDockWidgets__Controllers__Layout__destructor(void *thisObj)
{

    // tag=1055
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__Controllers__Layout__registerVirtualMethodCallback(void *ptr, void *callback, int methodId)
{
    // tag=1048
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 295:
        wrapper->m_customEventCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Layout_wrapper::Callback_customEvent>(callback);
        break;
    case 306:
        wrapper->m_eventCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Layout_wrapper::Callback_event>(callback);
        break;
    case 307:
        wrapper->m_eventFilterCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Layout_wrapper::Callback_eventFilter>(callback);
        break;
    case 725:
        wrapper->m_setParentView_implCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Layout_wrapper::Callback_setParentView_impl>(callback);
        break;
    }
}
}

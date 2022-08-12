/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "ClassicIndicators_wrapper.h"


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
ClassicIndicators_wrapper::ClassicIndicators_wrapper(KDDockWidgets::Controllers::DropArea *dropArea)
    : ::KDDockWidgets::Controllers::ClassicIndicators(dropArea)
{
}
void ClassicIndicators_wrapper::customEvent(QEvent *event)
{
    if (m_customEventCallback) {
        const void *thisPtr = this;
        m_customEventCallback(const_cast<void *>(thisPtr), event);
    } else {
        ::KDDockWidgets::Controllers::ClassicIndicators::customEvent(event);
    }
}
void ClassicIndicators_wrapper::customEvent_nocallback(QEvent *event)
{
    ::KDDockWidgets::Controllers::ClassicIndicators::customEvent(event);
}
bool ClassicIndicators_wrapper::dropIndicatorVisible(KDDockWidgets::DropLocation arg__1) const
{
    if (m_dropIndicatorVisibleCallback) {
        const void *thisPtr = this;
        return m_dropIndicatorVisibleCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        return ::KDDockWidgets::Controllers::ClassicIndicators::dropIndicatorVisible(arg__1);
    }
}
bool ClassicIndicators_wrapper::dropIndicatorVisible_nocallback(
    KDDockWidgets::DropLocation arg__1) const
{
    return ::KDDockWidgets::Controllers::ClassicIndicators::dropIndicatorVisible(arg__1);
}
bool ClassicIndicators_wrapper::event(QEvent *event)
{
    if (m_eventCallback) {
        const void *thisPtr = this;
        return m_eventCallback(const_cast<void *>(thisPtr), event);
    } else {
        return ::KDDockWidgets::Controllers::ClassicIndicators::event(event);
    }
}
bool ClassicIndicators_wrapper::event_nocallback(QEvent *event)
{
    return ::KDDockWidgets::Controllers::ClassicIndicators::event(event);
}
bool ClassicIndicators_wrapper::eventFilter(QObject *watched, QEvent *event)
{
    if (m_eventFilterCallback) {
        const void *thisPtr = this;
        return m_eventFilterCallback(const_cast<void *>(thisPtr), watched, event);
    } else {
        return ::KDDockWidgets::Controllers::ClassicIndicators::eventFilter(watched, event);
    }
}
bool ClassicIndicators_wrapper::eventFilter_nocallback(QObject *watched, QEvent *event)
{
    return ::KDDockWidgets::Controllers::ClassicIndicators::eventFilter(watched, event);
}
KDDockWidgets::DropLocation ClassicIndicators_wrapper::hover_impl(QPoint globalPos)
{
    if (m_hover_implCallback) {
        const void *thisPtr = this;
        return m_hover_implCallback(const_cast<void *>(thisPtr), &globalPos);
    } else {
        return ::KDDockWidgets::Controllers::ClassicIndicators::hover_impl(globalPos);
    }
}
KDDockWidgets::DropLocation ClassicIndicators_wrapper::hover_impl_nocallback(QPoint globalPos)
{
    return ::KDDockWidgets::Controllers::ClassicIndicators::hover_impl(globalPos);
}
void ClassicIndicators_wrapper::indicatorsVisibleChanged()
{
    ::KDDockWidgets::Controllers::ClassicIndicators::indicatorsVisibleChanged();
}
void ClassicIndicators_wrapper::onHoveredFrameChanged(KDDockWidgets::Controllers::Group *arg__1)
{
    if (m_onHoveredFrameChangedCallback) {
        const void *thisPtr = this;
        m_onHoveredFrameChangedCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        ::KDDockWidgets::Controllers::ClassicIndicators::onHoveredFrameChanged(arg__1);
    }
}
void ClassicIndicators_wrapper::onHoveredFrameChanged_nocallback(
    KDDockWidgets::Controllers::Group *arg__1)
{
    ::KDDockWidgets::Controllers::ClassicIndicators::onHoveredFrameChanged(arg__1);
}
bool ClassicIndicators_wrapper::onResize(QSize newSize)
{
    return ::KDDockWidgets::Controllers::ClassicIndicators::onResize(newSize);
}
QPoint ClassicIndicators_wrapper::posForIndicator(KDDockWidgets::DropLocation arg__1) const
{
    if (m_posForIndicatorCallback) {
        const void *thisPtr = this;
        return *m_posForIndicatorCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        return ::KDDockWidgets::Controllers::ClassicIndicators::posForIndicator(arg__1);
    }
}
QPoint
ClassicIndicators_wrapper::posForIndicator_nocallback(KDDockWidgets::DropLocation arg__1) const
{
    return ::KDDockWidgets::Controllers::ClassicIndicators::posForIndicator(arg__1);
}
void ClassicIndicators_wrapper::setDropLocation(KDDockWidgets::DropLocation arg__1)
{
    ::KDDockWidgets::Controllers::ClassicIndicators::setDropLocation(arg__1);
}
void ClassicIndicators_wrapper::setParentView_impl(KDDockWidgets::View *parent)
{
    if (m_setParentView_implCallback) {
        const void *thisPtr = this;
        m_setParentView_implCallback(const_cast<void *>(thisPtr), parent);
    } else {
        ::KDDockWidgets::Controllers::ClassicIndicators::setParentView_impl(parent);
    }
}
void ClassicIndicators_wrapper::setParentView_impl_nocallback(KDDockWidgets::View *parent)
{
    ::KDDockWidgets::Controllers::ClassicIndicators::setParentView_impl(parent);
}
QString ClassicIndicators_wrapper::tr(const char *s, const char *c, int n)
{
    return ::KDDockWidgets::Controllers::ClassicIndicators::tr(s, c, n);
}
void ClassicIndicators_wrapper::updateVisibility()
{
    if (m_updateVisibilityCallback) {
        const void *thisPtr = this;
        m_updateVisibilityCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Controllers::ClassicIndicators::updateVisibility();
    }
}
void ClassicIndicators_wrapper::updateVisibility_nocallback()
{
    ::KDDockWidgets::Controllers::ClassicIndicators::updateVisibility();
}
ClassicIndicators_wrapper::~ClassicIndicators_wrapper()
{
}

}
static KDDockWidgets::Controllers::ClassicIndicators *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::Controllers::ClassicIndicators *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__Controllers__ClassicIndicators_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper *>(cppObj);
}
void *c_KDDockWidgets__Controllers__ClassicIndicators__constructor_DropArea(void *dropArea_)
{
    auto dropArea = reinterpret_cast<KDDockWidgets::Controllers::DropArea *>(dropArea_);
    auto ptr = new KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper(dropArea);
    return reinterpret_cast<void *>(ptr);
}
// customEvent(QEvent * event)
void c_KDDockWidgets__Controllers__ClassicIndicators__customEvent_QEvent(void *thisObj,
                                                                         void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    fromWrapperPtr(thisObj)->customEvent_nocallback(event);
}
// dropIndicatorVisible(KDDockWidgets::DropLocation arg__1) const
bool c_KDDockWidgets__Controllers__ClassicIndicators__dropIndicatorVisible_DropLocation(
    void *thisObj, int arg__1)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->dropIndicatorVisible_nocallback(
                static_cast<KDDockWidgets::DropLocation>(arg__1));
        } else {
            return targetPtr->dropIndicatorVisible(
                static_cast<KDDockWidgets::DropLocation>(arg__1));
        }
    }();
}
// event(QEvent * event)
bool c_KDDockWidgets__Controllers__ClassicIndicators__event_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->event_nocallback(event);
        } else {
            return targetPtr->event(event);
        }
    }();
}
// eventFilter(QObject * watched, QEvent * event)
bool c_KDDockWidgets__Controllers__ClassicIndicators__eventFilter_QObject_QEvent(void *thisObj,
                                                                                 void *watched_,
                                                                                 void *event_)
{
    auto watched = reinterpret_cast<QObject *>(watched_);
    auto event = reinterpret_cast<QEvent *>(event_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->eventFilter_nocallback(watched, event);
        } else {
            return targetPtr->eventFilter(watched, event);
        }
    }();
}
// hover_impl(QPoint globalPos)
int c_KDDockWidgets__Controllers__ClassicIndicators__hover_impl_QPoint(void *thisObj,
                                                                       void *globalPos_)
{
    assert(globalPos_);
    auto &globalPos = *reinterpret_cast<QPoint *>(globalPos_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->hover_impl_nocallback(globalPos);
        } else {
            return targetPtr->hover_impl(globalPos);
        }
    }();
}
// indicatorsVisibleChanged()
void c_KDDockWidgets__Controllers__ClassicIndicators__indicatorsVisibleChanged(void *thisObj)
{
    fromPtr(thisObj)->indicatorsVisibleChanged();
}
// onHoveredFrameChanged(KDDockWidgets::Controllers::Group * arg__1)
void c_KDDockWidgets__Controllers__ClassicIndicators__onHoveredFrameChanged_Group(void *thisObj,
                                                                                  void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::Group *>(arg__1_);
    fromWrapperPtr(thisObj)->onHoveredFrameChanged_nocallback(arg__1);
}
// onResize(QSize newSize)
bool c_KDDockWidgets__Controllers__ClassicIndicators__onResize_QSize(void *thisObj, void *newSize_)
{
    assert(newSize_);
    auto &newSize = *reinterpret_cast<QSize *>(newSize_);
    return fromPtr(thisObj)->onResize(newSize);
}
// posForIndicator(KDDockWidgets::DropLocation arg__1) const
void *c_KDDockWidgets__Controllers__ClassicIndicators__posForIndicator_DropLocation(void *thisObj,
                                                                                    int arg__1)
{
    return new Dartagnan::ValueWrapper<QPoint> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->posForIndicator_nocallback(
                static_cast<KDDockWidgets::DropLocation>(arg__1));
        } else {
            return targetPtr->posForIndicator(static_cast<KDDockWidgets::DropLocation>(arg__1));
        }
    }() };
}
// setDropLocation(KDDockWidgets::DropLocation arg__1)
void c_KDDockWidgets__Controllers__ClassicIndicators__setDropLocation_DropLocation(void *thisObj,
                                                                                   int arg__1)
{
    fromPtr(thisObj)->setDropLocation(static_cast<KDDockWidgets::DropLocation>(arg__1));
}
// setParentView_impl(KDDockWidgets::View * parent)
void c_KDDockWidgets__Controllers__ClassicIndicators__setParentView_impl_View(void *thisObj,
                                                                              void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    fromWrapperPtr(thisObj)->setParentView_impl_nocallback(parent);
}
// tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__Controllers__ClassicIndicators__tr_char_char_int(const char *s,
                                                                               const char *c, int n)
{
    return new Dartagnan::ValueWrapper<QString> {
        KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper::tr(s, c, n)
    };
}
// updateVisibility()
void c_KDDockWidgets__Controllers__ClassicIndicators__updateVisibility(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->updateVisibility_nocallback();
        } else {
            return targetPtr->updateVisibility();
        }
    }();
}
void c_KDDockWidgets__Controllers__ClassicIndicators__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__Controllers__ClassicIndicators__registerVirtualMethodCallback(void *ptr,
                                                                                    void *callback,
                                                                                    int methodId)
{
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 295:
        wrapper->m_customEventCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper::Callback_customEvent>(
            callback);
        break;
    case 1489:
        wrapper->m_dropIndicatorVisibleCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper::
                                 Callback_dropIndicatorVisible>(callback);
        break;
    case 306:
        wrapper->m_eventCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper::Callback_event>(callback);
        break;
    case 307:
        wrapper->m_eventFilterCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper::Callback_eventFilter>(
            callback);
        break;
    case 1493:
        wrapper->m_hover_implCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper::Callback_hover_impl>(
            callback);
        break;
    case 1505:
        wrapper->m_onHoveredFrameChangedCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper::
                                 Callback_onHoveredFrameChanged>(callback);
        break;
    case 1508:
        wrapper->m_posForIndicatorCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper::Callback_posForIndicator>(
            callback);
        break;
    case 826:
        wrapper->m_setParentView_implCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper::
                                 Callback_setParentView_impl>(callback);
        break;
    case 1521:
        wrapper->m_updateVisibilityCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper::Callback_updateVisibility>(
            callback);
        break;
    }
}
}

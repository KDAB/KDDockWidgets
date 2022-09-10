/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "DropIndicatorOverlay_wrapper.h"


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
DropIndicatorOverlay_wrapper::DropIndicatorOverlay_wrapper(
    KDDockWidgets::Controllers::DropArea *dropArea)
    : ::KDDockWidgets::Controllers::DropIndicatorOverlay(dropArea)
{
}
KDDockWidgets::DropLocation DropIndicatorOverlay_wrapper::currentDropLocation() const
{
    return ::KDDockWidgets::Controllers::DropIndicatorOverlay::currentDropLocation();
}
void DropIndicatorOverlay_wrapper::currentDropLocationChanged()
{
    ::KDDockWidgets::Controllers::DropIndicatorOverlay::currentDropLocationChanged();
}
void DropIndicatorOverlay_wrapper::customEvent(QEvent *event)
{
    if (m_customEventCallback) {
        const void *thisPtr = this;
        m_customEventCallback(const_cast<void *>(thisPtr), event);
    } else {
        ::KDDockWidgets::Controllers::DropIndicatorOverlay::customEvent(event);
    }
}
void DropIndicatorOverlay_wrapper::customEvent_nocallback(QEvent *event)
{
    ::KDDockWidgets::Controllers::DropIndicatorOverlay::customEvent(event);
}
bool DropIndicatorOverlay_wrapper::dropIndicatorVisible(KDDockWidgets::DropLocation arg__1) const
{
    if (m_dropIndicatorVisibleCallback) {
        const void *thisPtr = this;
        return m_dropIndicatorVisibleCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        return ::KDDockWidgets::Controllers::DropIndicatorOverlay::dropIndicatorVisible(arg__1);
    }
}
bool DropIndicatorOverlay_wrapper::dropIndicatorVisible_nocallback(
    KDDockWidgets::DropLocation arg__1) const
{
    return ::KDDockWidgets::Controllers::DropIndicatorOverlay::dropIndicatorVisible(arg__1);
}
bool DropIndicatorOverlay_wrapper::event(QEvent *event)
{
    if (m_eventCallback) {
        const void *thisPtr = this;
        return m_eventCallback(const_cast<void *>(thisPtr), event);
    } else {
        return ::KDDockWidgets::Controllers::DropIndicatorOverlay::event(event);
    }
}
bool DropIndicatorOverlay_wrapper::event_nocallback(QEvent *event)
{
    return ::KDDockWidgets::Controllers::DropIndicatorOverlay::event(event);
}
bool DropIndicatorOverlay_wrapper::eventFilter(QObject *watched, QEvent *event)
{
    if (m_eventFilterCallback) {
        const void *thisPtr = this;
        return m_eventFilterCallback(const_cast<void *>(thisPtr), watched, event);
    } else {
        return ::KDDockWidgets::Controllers::DropIndicatorOverlay::eventFilter(watched, event);
    }
}
bool DropIndicatorOverlay_wrapper::eventFilter_nocallback(QObject *watched, QEvent *event)
{
    return ::KDDockWidgets::Controllers::DropIndicatorOverlay::eventFilter(watched, event);
}
KDDockWidgets::DropLocation DropIndicatorOverlay_wrapper::hover(QPoint globalPos)
{
    return ::KDDockWidgets::Controllers::DropIndicatorOverlay::hover(globalPos);
}
KDDockWidgets::DropLocation DropIndicatorOverlay_wrapper::hover_impl(QPoint globalPos)
{
    if (m_hover_implCallback) {
        const void *thisPtr = this;
        return m_hover_implCallback(const_cast<void *>(thisPtr), &globalPos);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
KDDockWidgets::DropLocation DropIndicatorOverlay_wrapper::hover_impl_nocallback(QPoint globalPos)
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
KDDockWidgets::Controllers::Group *DropIndicatorOverlay_wrapper::hoveredFrame() const
{
    return ::KDDockWidgets::Controllers::DropIndicatorOverlay::hoveredFrame();
}
void DropIndicatorOverlay_wrapper::hoveredFrameChanged(KDDockWidgets::Controllers::Group *arg__1)
{
    ::KDDockWidgets::Controllers::DropIndicatorOverlay::hoveredFrameChanged(arg__1);
}
QRect DropIndicatorOverlay_wrapper::hoveredFrameRect() const
{
    return ::KDDockWidgets::Controllers::DropIndicatorOverlay::hoveredFrameRect();
}
void DropIndicatorOverlay_wrapper::hoveredFrameRectChanged()
{
    ::KDDockWidgets::Controllers::DropIndicatorOverlay::hoveredFrameRectChanged();
}
bool DropIndicatorOverlay_wrapper::isHovered() const
{
    return ::KDDockWidgets::Controllers::DropIndicatorOverlay::isHovered();
}
KDDockWidgets::Location
DropIndicatorOverlay_wrapper::multisplitterLocationFor(KDDockWidgets::DropLocation arg__1)
{
    return ::KDDockWidgets::Controllers::DropIndicatorOverlay::multisplitterLocationFor(arg__1);
}
void DropIndicatorOverlay_wrapper::onHoveredFrameChanged(KDDockWidgets::Controllers::Group *arg__1)
{
    if (m_onHoveredFrameChangedCallback) {
        const void *thisPtr = this;
        m_onHoveredFrameChangedCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        ::KDDockWidgets::Controllers::DropIndicatorOverlay::onHoveredFrameChanged(arg__1);
    }
}
void DropIndicatorOverlay_wrapper::onHoveredFrameChanged_nocallback(
    KDDockWidgets::Controllers::Group *arg__1)
{
    ::KDDockWidgets::Controllers::DropIndicatorOverlay::onHoveredFrameChanged(arg__1);
}
QPoint DropIndicatorOverlay_wrapper::posForIndicator(KDDockWidgets::DropLocation arg__1) const
{
    if (m_posForIndicatorCallback) {
        const void *thisPtr = this;
        return *m_posForIndicatorCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
QPoint
DropIndicatorOverlay_wrapper::posForIndicator_nocallback(KDDockWidgets::DropLocation arg__1) const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
void DropIndicatorOverlay_wrapper::removeHover()
{
    ::KDDockWidgets::Controllers::DropIndicatorOverlay::removeHover();
}
void DropIndicatorOverlay_wrapper::setCurrentDropLocation(KDDockWidgets::DropLocation location)
{
    ::KDDockWidgets::Controllers::DropIndicatorOverlay::setCurrentDropLocation(location);
}
void DropIndicatorOverlay_wrapper::setHoveredFrame(KDDockWidgets::Controllers::Group *arg__1)
{
    ::KDDockWidgets::Controllers::DropIndicatorOverlay::setHoveredFrame(arg__1);
}
void DropIndicatorOverlay_wrapper::setParentView_impl(KDDockWidgets::View *parent)
{
    if (m_setParentView_implCallback) {
        const void *thisPtr = this;
        m_setParentView_implCallback(const_cast<void *>(thisPtr), parent);
    } else {
        ::KDDockWidgets::Controllers::DropIndicatorOverlay::setParentView_impl(parent);
    }
}
void DropIndicatorOverlay_wrapper::setParentView_impl_nocallback(KDDockWidgets::View *parent)
{
    ::KDDockWidgets::Controllers::DropIndicatorOverlay::setParentView_impl(parent);
}
void DropIndicatorOverlay_wrapper::setWindowBeingDragged(bool arg__1)
{
    ::KDDockWidgets::Controllers::DropIndicatorOverlay::setWindowBeingDragged(arg__1);
}
QString DropIndicatorOverlay_wrapper::tr(const char *s, const char *c, int n)
{
    return ::KDDockWidgets::Controllers::DropIndicatorOverlay::tr(s, c, n);
}
void DropIndicatorOverlay_wrapper::updateVisibility()
{
    if (m_updateVisibilityCallback) {
        const void *thisPtr = this;
        m_updateVisibilityCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Controllers::DropIndicatorOverlay::updateVisibility();
    }
}
void DropIndicatorOverlay_wrapper::updateVisibility_nocallback()
{
    ::KDDockWidgets::Controllers::DropIndicatorOverlay::updateVisibility();
}
DropIndicatorOverlay_wrapper::~DropIndicatorOverlay_wrapper()
{
}

}
static KDDockWidgets::Controllers::DropIndicatorOverlay *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::Controllers::DropIndicatorOverlay *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::DropIndicatorOverlay_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::DropIndicatorOverlay_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__Controllers__DropIndicatorOverlay_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::DropIndicatorOverlay_wrapper *>(
        cppObj);
}
void *c_KDDockWidgets__Controllers__DropIndicatorOverlay__constructor_DropArea(void *dropArea_)
{
    auto dropArea = reinterpret_cast<KDDockWidgets::Controllers::DropArea *>(dropArea_);
    auto ptr = new KDDockWidgetsBindings_wrappersNS::DropIndicatorOverlay_wrapper(dropArea);
    return reinterpret_cast<void *>(ptr);
}
// currentDropLocation() const
int c_KDDockWidgets__Controllers__DropIndicatorOverlay__currentDropLocation(void *thisObj)
{
    return int(fromPtr(thisObj)->currentDropLocation());
}
// currentDropLocationChanged()
void c_KDDockWidgets__Controllers__DropIndicatorOverlay__currentDropLocationChanged(void *thisObj)
{
    fromPtr(thisObj)->currentDropLocationChanged();
}
// customEvent(QEvent * event)
void c_KDDockWidgets__Controllers__DropIndicatorOverlay__customEvent_QEvent(void *thisObj,
                                                                            void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    fromWrapperPtr(thisObj)->customEvent_nocallback(event);
}
// dropIndicatorVisible(KDDockWidgets::DropLocation arg__1) const
bool c_KDDockWidgets__Controllers__DropIndicatorOverlay__dropIndicatorVisible_DropLocation(
    void *thisObj, int arg__1)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::DropIndicatorOverlay_wrapper *>(
                targetPtr);
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
bool c_KDDockWidgets__Controllers__DropIndicatorOverlay__event_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::DropIndicatorOverlay_wrapper *>(
                targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->event_nocallback(event);
        } else {
            return targetPtr->event(event);
        }
    }();
}
// eventFilter(QObject * watched, QEvent * event)
bool c_KDDockWidgets__Controllers__DropIndicatorOverlay__eventFilter_QObject_QEvent(void *thisObj,
                                                                                    void *watched_,
                                                                                    void *event_)
{
    auto watched = reinterpret_cast<QObject *>(watched_);
    auto event = reinterpret_cast<QEvent *>(event_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::DropIndicatorOverlay_wrapper *>(
                targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->eventFilter_nocallback(watched, event);
        } else {
            return targetPtr->eventFilter(watched, event);
        }
    }();
}
// hover(QPoint globalPos)
int c_KDDockWidgets__Controllers__DropIndicatorOverlay__hover_QPoint(void *thisObj,
                                                                     void *globalPos_)
{
    assert(globalPos_);
    auto &globalPos = *reinterpret_cast<QPoint *>(globalPos_);
    return int(fromPtr(thisObj)->hover(globalPos));
}
// hover_impl(QPoint globalPos)
int c_KDDockWidgets__Controllers__DropIndicatorOverlay__hover_impl_QPoint(void *thisObj,
                                                                          void *globalPos_)
{
    assert(globalPos_);
    auto &globalPos = *reinterpret_cast<QPoint *>(globalPos_);
    return fromWrapperPtr(thisObj)->hover_impl_nocallback(globalPos);
}
// hoveredFrame() const
void *c_KDDockWidgets__Controllers__DropIndicatorOverlay__hoveredFrame(void *thisObj)
{
    return fromPtr(thisObj)->hoveredFrame();
}
// hoveredFrameChanged(KDDockWidgets::Controllers::Group * arg__1)
void c_KDDockWidgets__Controllers__DropIndicatorOverlay__hoveredFrameChanged_Group(void *thisObj,
                                                                                   void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::Group *>(arg__1_);
    fromPtr(thisObj)->hoveredFrameChanged(arg__1);
}
// hoveredFrameRect() const
void *c_KDDockWidgets__Controllers__DropIndicatorOverlay__hoveredFrameRect(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QRect> { fromPtr(thisObj)->hoveredFrameRect() };
}
// hoveredFrameRectChanged()
void c_KDDockWidgets__Controllers__DropIndicatorOverlay__hoveredFrameRectChanged(void *thisObj)
{
    fromPtr(thisObj)->hoveredFrameRectChanged();
}
// isHovered() const
bool c_KDDockWidgets__Controllers__DropIndicatorOverlay__isHovered(void *thisObj)
{
    return fromPtr(thisObj)->isHovered();
}
// multisplitterLocationFor(KDDockWidgets::DropLocation arg__1)
int c_static_KDDockWidgets__Controllers__DropIndicatorOverlay__multisplitterLocationFor_DropLocation(
    int arg__1)
{
    return KDDockWidgetsBindings_wrappersNS::DropIndicatorOverlay_wrapper::multisplitterLocationFor(
        static_cast<KDDockWidgets::DropLocation>(arg__1));
}
// onHoveredFrameChanged(KDDockWidgets::Controllers::Group * arg__1)
void c_KDDockWidgets__Controllers__DropIndicatorOverlay__onHoveredFrameChanged_Group(void *thisObj,
                                                                                     void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::Group *>(arg__1_);
    fromWrapperPtr(thisObj)->onHoveredFrameChanged_nocallback(arg__1);
}
// posForIndicator(KDDockWidgets::DropLocation arg__1) const
void *
c_KDDockWidgets__Controllers__DropIndicatorOverlay__posForIndicator_DropLocation(void *thisObj,
                                                                                 int arg__1)
{
    return new Dartagnan::ValueWrapper<QPoint> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::DropIndicatorOverlay_wrapper *>(
                targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->posForIndicator_nocallback(
                static_cast<KDDockWidgets::DropLocation>(arg__1));
        } else {
            return targetPtr->posForIndicator(static_cast<KDDockWidgets::DropLocation>(arg__1));
        }
    }() };
}
// removeHover()
void c_KDDockWidgets__Controllers__DropIndicatorOverlay__removeHover(void *thisObj)
{
    fromPtr(thisObj)->removeHover();
}
// setCurrentDropLocation(KDDockWidgets::DropLocation location)
void c_KDDockWidgets__Controllers__DropIndicatorOverlay__setCurrentDropLocation_DropLocation(
    void *thisObj, int location)
{
    fromPtr(thisObj)->setCurrentDropLocation(static_cast<KDDockWidgets::DropLocation>(location));
}
// setHoveredFrame(KDDockWidgets::Controllers::Group * arg__1)
void c_KDDockWidgets__Controllers__DropIndicatorOverlay__setHoveredFrame_Group(void *thisObj,
                                                                               void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::Group *>(arg__1_);
    fromPtr(thisObj)->setHoveredFrame(arg__1);
}
// setParentView_impl(KDDockWidgets::View * parent)
void c_KDDockWidgets__Controllers__DropIndicatorOverlay__setParentView_impl_View(void *thisObj,
                                                                                 void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    fromWrapperPtr(thisObj)->setParentView_impl_nocallback(parent);
}
// setWindowBeingDragged(bool arg__1)
void c_KDDockWidgets__Controllers__DropIndicatorOverlay__setWindowBeingDragged_bool(void *thisObj,
                                                                                    bool arg__1)
{
    fromPtr(thisObj)->setWindowBeingDragged(arg__1);
}
// tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__Controllers__DropIndicatorOverlay__tr_char_char_int(const char *s,
                                                                                  const char *c,
                                                                                  int n)
{
    return new Dartagnan::ValueWrapper<QString> {
        KDDockWidgetsBindings_wrappersNS::DropIndicatorOverlay_wrapper::tr(s, c, n)
    };
}
// updateVisibility()
void c_KDDockWidgets__Controllers__DropIndicatorOverlay__updateVisibility(void *thisObj)
{
    fromWrapperPtr(thisObj)->updateVisibility_nocallback();
}
void c_KDDockWidgets__Controllers__DropIndicatorOverlay__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__Controllers__DropIndicatorOverlay__registerVirtualMethodCallback(
    void *ptr, void *callback, int methodId)
{
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 295:
        wrapper->m_customEventCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::DropIndicatorOverlay_wrapper::Callback_customEvent>(
            callback);
        break;
    case 1596:
        wrapper->m_dropIndicatorVisibleCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::DropIndicatorOverlay_wrapper::
                                 Callback_dropIndicatorVisible>(callback);
        break;
    case 306:
        wrapper->m_eventCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::DropIndicatorOverlay_wrapper::Callback_event>(
            callback);
        break;
    case 307:
        wrapper->m_eventFilterCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::DropIndicatorOverlay_wrapper::Callback_eventFilter>(
            callback);
        break;
    case 1600:
        wrapper->m_hover_implCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::DropIndicatorOverlay_wrapper::Callback_hover_impl>(
            callback);
        break;
    case 1612:
        wrapper->m_onHoveredFrameChangedCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::DropIndicatorOverlay_wrapper::
                                 Callback_onHoveredFrameChanged>(callback);
        break;
    case 1615:
        wrapper->m_posForIndicatorCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::DropIndicatorOverlay_wrapper::
                                 Callback_posForIndicator>(callback);
        break;
    case 888:
        wrapper->m_setParentView_implCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::DropIndicatorOverlay_wrapper::
                                 Callback_setParentView_impl>(callback);
        break;
    case 1628:
        wrapper->m_updateVisibilityCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::DropIndicatorOverlay_wrapper::
                                 Callback_updateVisibility>(callback);
        break;
    }
}
}

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "Item_wrapper.h"


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
Item_wrapper::Item_wrapper(KDDockWidgets::View *hostWidget)
    : ::Layouting::Item(hostWidget)
{
}
KDDockWidgets::Controllers::Group *Item_wrapper::asGroupController() const
{
    return ::Layouting::Item::asGroupController();
}
bool Item_wrapper::checkSanity()
{
    if (m_checkSanityCallback) {
        const void *thisPtr = this;
        return m_checkSanityCallback(const_cast<void *>(thisPtr));
    } else {
        return ::Layouting::Item::checkSanity();
    }
}
bool Item_wrapper::checkSanity_nocallback()
{
    return ::Layouting::Item::checkSanity();
}
void Item_wrapper::customEvent(QEvent *event)
{
    if (m_customEventCallback) {
        const void *thisPtr = this;
        m_customEventCallback(const_cast<void *>(thisPtr), event);
    } else {
        ::Layouting::Item::customEvent(event);
    }
}
void Item_wrapper::customEvent_nocallback(QEvent *event)
{
    ::Layouting::Item::customEvent(event);
}
void Item_wrapper::dumpLayout(int level)
{
    if (m_dumpLayoutCallback) {
        const void *thisPtr = this;
        m_dumpLayoutCallback(const_cast<void *>(thisPtr), level);
    } else {
        ::Layouting::Item::dumpLayout(level);
    }
}
void Item_wrapper::dumpLayout_nocallback(int level)
{
    ::Layouting::Item::dumpLayout(level);
}
bool Item_wrapper::event(QEvent *event)
{
    if (m_eventCallback) {
        const void *thisPtr = this;
        return m_eventCallback(const_cast<void *>(thisPtr), event);
    } else {
        return ::Layouting::Item::event(event);
    }
}
bool Item_wrapper::event_nocallback(QEvent *event)
{
    return ::Layouting::Item::event(event);
}
bool Item_wrapper::eventFilter(QObject *watched, QEvent *event)
{
    if (m_eventFilterCallback) {
        const void *thisPtr = this;
        return m_eventFilterCallback(const_cast<void *>(thisPtr), watched, event);
    } else {
        return ::Layouting::Item::eventFilter(watched, event);
    }
}
bool Item_wrapper::eventFilter_nocallback(QObject *watched, QEvent *event)
{
    return ::Layouting::Item::eventFilter(watched, event);
}
QRect Item_wrapper::geometry() const
{
    return ::Layouting::Item::geometry();
}
KDDockWidgets::View *Item_wrapper::guestView() const
{
    return ::Layouting::Item::guestView();
}
int Item_wrapper::height() const
{
    return ::Layouting::Item::height();
}
KDDockWidgets::View *Item_wrapper::hostView() const
{
    return ::Layouting::Item::hostView();
}
bool Item_wrapper::isBeingInserted() const
{
    return ::Layouting::Item::isBeingInserted();
}
bool Item_wrapper::isContainer() const
{
    return ::Layouting::Item::isContainer();
}
bool Item_wrapper::isMDI() const
{
    return ::Layouting::Item::isMDI();
}
bool Item_wrapper::isPlaceholder() const
{
    return ::Layouting::Item::isPlaceholder();
}
bool Item_wrapper::isRoot() const
{
    return ::Layouting::Item::isRoot();
}
bool Item_wrapper::isVisible(bool excludeBeingInserted) const
{
    if (m_isVisibleCallback) {
        const void *thisPtr = this;
        return m_isVisibleCallback(const_cast<void *>(thisPtr), excludeBeingInserted);
    } else {
        return ::Layouting::Item::isVisible(excludeBeingInserted);
    }
}
bool Item_wrapper::isVisible_nocallback(bool excludeBeingInserted) const
{
    return ::Layouting::Item::isVisible(excludeBeingInserted);
}
QPoint Item_wrapper::mapFromParent(QPoint arg__1) const
{
    return ::Layouting::Item::mapFromParent(arg__1);
}
QPoint Item_wrapper::mapFromRoot(QPoint arg__1) const
{
    return ::Layouting::Item::mapFromRoot(arg__1);
}
QRect Item_wrapper::mapFromRoot(QRect arg__1) const
{
    return ::Layouting::Item::mapFromRoot(arg__1);
}
QPoint Item_wrapper::mapToRoot(QPoint arg__1) const
{
    return ::Layouting::Item::mapToRoot(arg__1);
}
QRect Item_wrapper::mapToRoot(QRect arg__1) const
{
    return ::Layouting::Item::mapToRoot(arg__1);
}
QSize Item_wrapper::maxSizeHint() const
{
    if (m_maxSizeHintCallback) {
        const void *thisPtr = this;
        return *m_maxSizeHintCallback(const_cast<void *>(thisPtr));
    } else {
        return ::Layouting::Item::maxSizeHint();
    }
}
QSize Item_wrapper::maxSizeHint_nocallback() const
{
    return ::Layouting::Item::maxSizeHint();
}
QSize Item_wrapper::minSize() const
{
    if (m_minSizeCallback) {
        const void *thisPtr = this;
        return *m_minSizeCallback(const_cast<void *>(thisPtr));
    } else {
        return ::Layouting::Item::minSize();
    }
}
QSize Item_wrapper::minSize_nocallback() const
{
    return ::Layouting::Item::minSize();
}
QSize Item_wrapper::missingSize() const
{
    return ::Layouting::Item::missingSize();
}
QPoint Item_wrapper::pos() const
{
    return ::Layouting::Item::pos();
}
QRect Item_wrapper::rect() const
{
    return ::Layouting::Item::rect();
}
void Item_wrapper::ref()
{
    ::Layouting::Item::ref();
}
int Item_wrapper::refCount() const
{
    return ::Layouting::Item::refCount();
}
void Item_wrapper::restore(KDDockWidgets::View *guestView)
{
    ::Layouting::Item::restore(guestView);
}
void Item_wrapper::setBeingInserted(bool arg__1)
{
    ::Layouting::Item::setBeingInserted(arg__1);
}
void Item_wrapper::setGeometry(QRect rect)
{
    ::Layouting::Item::setGeometry(rect);
}
void Item_wrapper::setGeometry_recursive(QRect rect)
{
    if (m_setGeometry_recursiveCallback) {
        const void *thisPtr = this;
        m_setGeometry_recursiveCallback(const_cast<void *>(thisPtr), rect);
    } else {
        ::Layouting::Item::setGeometry_recursive(rect);
    }
}
void Item_wrapper::setGeometry_recursive_nocallback(QRect rect)
{
    ::Layouting::Item::setGeometry_recursive(rect);
}
void Item_wrapper::setGuestView(KDDockWidgets::View *arg__1)
{
    ::Layouting::Item::setGuestView(arg__1);
}
void Item_wrapper::setHostView(KDDockWidgets::View *arg__1)
{
    if (m_setHostViewCallback) {
        const void *thisPtr = this;
        m_setHostViewCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        ::Layouting::Item::setHostView(arg__1);
    }
}
void Item_wrapper::setHostView_nocallback(KDDockWidgets::View *arg__1)
{
    ::Layouting::Item::setHostView(arg__1);
}
void Item_wrapper::setIsVisible(bool arg__1)
{
    if (m_setIsVisibleCallback) {
        const void *thisPtr = this;
        m_setIsVisibleCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        ::Layouting::Item::setIsVisible(arg__1);
    }
}
void Item_wrapper::setIsVisible_nocallback(bool arg__1)
{
    ::Layouting::Item::setIsVisible(arg__1);
}
void Item_wrapper::setMaxSizeHint(QSize arg__1)
{
    ::Layouting::Item::setMaxSizeHint(arg__1);
}
void Item_wrapper::setMinSize(QSize arg__1)
{
    ::Layouting::Item::setMinSize(arg__1);
}
void Item_wrapper::setPos(QPoint arg__1)
{
    ::Layouting::Item::setPos(arg__1);
}
void Item_wrapper::setSize(QSize arg__1)
{
    ::Layouting::Item::setSize(arg__1);
}
QSize Item_wrapper::size() const
{
    return ::Layouting::Item::size();
}
QString Item_wrapper::tr(const char *s, const char *c, int n)
{
    return ::Layouting::Item::tr(s, c, n);
}
void Item_wrapper::unref()
{
    ::Layouting::Item::unref();
}
void Item_wrapper::updateWidgetGeometries()
{
    if (m_updateWidgetGeometriesCallback) {
        const void *thisPtr = this;
        m_updateWidgetGeometriesCallback(const_cast<void *>(thisPtr));
    } else {
        ::Layouting::Item::updateWidgetGeometries();
    }
}
void Item_wrapper::updateWidgetGeometries_nocallback()
{
    ::Layouting::Item::updateWidgetGeometries();
}
int Item_wrapper::visibleCount_recursive() const
{
    if (m_visibleCount_recursiveCallback) {
        const void *thisPtr = this;
        return m_visibleCount_recursiveCallback(const_cast<void *>(thisPtr));
    } else {
        return ::Layouting::Item::visibleCount_recursive();
    }
}
int Item_wrapper::visibleCount_recursive_nocallback() const
{
    return ::Layouting::Item::visibleCount_recursive();
}
int Item_wrapper::width() const
{
    return ::Layouting::Item::width();
}
int Item_wrapper::x() const
{
    return ::Layouting::Item::x();
}
int Item_wrapper::y() const
{
    return ::Layouting::Item::y();
}
Item_wrapper::~Item_wrapper()
{
}

}
static Layouting::Item *fromPtr(void *ptr)
{
    return reinterpret_cast<Layouting::Item *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::Item_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper *>(ptr);
}
extern "C" {
void c_Layouting__Item_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper *>(cppObj);
}
void *c_Layouting__Item__constructor_View(void *hostWidget_)
{
    auto hostWidget = reinterpret_cast<KDDockWidgets::View *>(hostWidget_);
    auto ptr = new KDDockWidgetsBindings_wrappersNS::Item_wrapper(hostWidget);
    return reinterpret_cast<void *>(ptr);
}
// asGroupController() const
void *c_Layouting__Item__asGroupController(void *thisObj)
{
    return fromPtr(thisObj)->asGroupController();
}
// checkSanity()
bool c_Layouting__Item__checkSanity(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->checkSanity_nocallback();} else {    return targetPtr->checkSanity();} }();
}
// customEvent(QEvent * event)
void c_Layouting__Item__customEvent_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    fromWrapperPtr(thisObj)->customEvent_nocallback(event);
}
// dumpLayout(int level)
void c_Layouting__Item__dumpLayout_int(void *thisObj, int level)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->dumpLayout_nocallback(level);} else {    return targetPtr->dumpLayout(level);} }();
}
// event(QEvent * event)
bool c_Layouting__Item__event_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->event_nocallback(event);} else {    return targetPtr->event(event);} }();
}
// eventFilter(QObject * watched, QEvent * event)
bool c_Layouting__Item__eventFilter_QObject_QEvent(void *thisObj, void *watched_, void *event_)
{
    auto watched = reinterpret_cast<QObject *>(watched_);
    auto event = reinterpret_cast<QEvent *>(event_);
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->eventFilter_nocallback(watched,event);} else {    return targetPtr->eventFilter(watched,event);} }();
}
// geometry() const
void *c_Layouting__Item__geometry(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QRect> { fromPtr(thisObj)->geometry() };
}
// guestView() const
void *c_Layouting__Item__guestView(void *thisObj)
{
    return fromPtr(thisObj)->guestView();
}
// height() const
int c_Layouting__Item__height(void *thisObj)
{
    return fromPtr(thisObj)->height();
}
// hostView() const
void *c_Layouting__Item__hostView(void *thisObj)
{
    return fromPtr(thisObj)->hostView();
}
// isBeingInserted() const
bool c_Layouting__Item__isBeingInserted(void *thisObj)
{
    return fromWrapperPtr(thisObj)->isBeingInserted();
}
// isContainer() const
bool c_Layouting__Item__isContainer(void *thisObj)
{
    return fromPtr(thisObj)->isContainer();
}
// isMDI() const
bool c_Layouting__Item__isMDI(void *thisObj)
{
    return fromPtr(thisObj)->isMDI();
}
// isPlaceholder() const
bool c_Layouting__Item__isPlaceholder(void *thisObj)
{
    return fromPtr(thisObj)->isPlaceholder();
}
// isRoot() const
bool c_Layouting__Item__isRoot(void *thisObj)
{
    return fromPtr(thisObj)->isRoot();
}
// isVisible(bool excludeBeingInserted) const
bool c_Layouting__Item__isVisible_bool(void *thisObj, bool excludeBeingInserted)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isVisible_nocallback(excludeBeingInserted);} else {    return targetPtr->isVisible(excludeBeingInserted);} }();
}
// mapFromParent(QPoint arg__1) const
void *c_Layouting__Item__mapFromParent_QPoint(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QPoint *>(arg__1_);
    return new Dartagnan::ValueWrapper<QPoint> { fromPtr(thisObj)->mapFromParent(arg__1) };
}
// mapFromRoot(QPoint arg__1) const
void *c_Layouting__Item__mapFromRoot_QPoint(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QPoint *>(arg__1_);
    return new Dartagnan::ValueWrapper<QPoint> { fromPtr(thisObj)->mapFromRoot(arg__1) };
}
// mapFromRoot(QRect arg__1) const
void *c_Layouting__Item__mapFromRoot_QRect(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QRect *>(arg__1_);
    return new Dartagnan::ValueWrapper<QRect> { fromPtr(thisObj)->mapFromRoot(arg__1) };
}
// mapToRoot(QPoint arg__1) const
void *c_Layouting__Item__mapToRoot_QPoint(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QPoint *>(arg__1_);
    return new Dartagnan::ValueWrapper<QPoint> { fromPtr(thisObj)->mapToRoot(arg__1) };
}
// mapToRoot(QRect arg__1) const
void *c_Layouting__Item__mapToRoot_QRect(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QRect *>(arg__1_);
    return new Dartagnan::ValueWrapper<QRect> { fromPtr(thisObj)->mapToRoot(arg__1) };
}
// maxSizeHint() const
void *c_Layouting__Item__maxSizeHint(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->maxSizeHint_nocallback();} else {    return targetPtr->maxSizeHint();} }() };
}
// minSize() const
void *c_Layouting__Item__minSize(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->minSize_nocallback();} else {    return targetPtr->minSize();} }() };
}
// missingSize() const
void *c_Layouting__Item__missingSize(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { fromWrapperPtr(thisObj)->missingSize() };
}
// pos() const
void *c_Layouting__Item__pos(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QPoint> { fromPtr(thisObj)->pos() };
}
// rect() const
void *c_Layouting__Item__rect(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QRect> { fromPtr(thisObj)->rect() };
}
// ref()
void c_Layouting__Item__ref(void *thisObj)
{
    fromPtr(thisObj)->ref();
}
// refCount() const
int c_Layouting__Item__refCount(void *thisObj)
{
    return fromPtr(thisObj)->refCount();
}
// restore(KDDockWidgets::View * guestView)
void c_Layouting__Item__restore_View(void *thisObj, void *guestView_)
{
    auto guestView = reinterpret_cast<KDDockWidgets::View *>(guestView_);
    fromPtr(thisObj)->restore(guestView);
}
// setBeingInserted(bool arg__1)
void c_Layouting__Item__setBeingInserted_bool(void *thisObj, bool arg__1)
{
    fromWrapperPtr(thisObj)->setBeingInserted(arg__1);
}
// setGeometry(QRect rect)
void c_Layouting__Item__setGeometry_QRect(void *thisObj, void *rect_)
{
    auto &rect = *reinterpret_cast<QRect *>(rect_);
    fromPtr(thisObj)->setGeometry(rect);
}
// setGeometry_recursive(QRect rect)
void c_Layouting__Item__setGeometry_recursive_QRect(void *thisObj, void *rect_)
{
    auto &rect = *reinterpret_cast<QRect *>(rect_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setGeometry_recursive_nocallback(rect);} else {    return targetPtr->setGeometry_recursive(rect);} }();
}
// setGuestView(KDDockWidgets::View * arg__1)
void c_Layouting__Item__setGuestView_View(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::View *>(arg__1_);
    fromPtr(thisObj)->setGuestView(arg__1);
}
// setHostView(KDDockWidgets::View * arg__1)
void c_Layouting__Item__setHostView_View(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::View *>(arg__1_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setHostView_nocallback(arg__1);} else {    return targetPtr->setHostView(arg__1);} }();
}
// setIsVisible(bool arg__1)
void c_Layouting__Item__setIsVisible_bool(void *thisObj, bool arg__1)
{
    fromWrapperPtr(thisObj)->setIsVisible_nocallback(arg__1);
}
// setMaxSizeHint(QSize arg__1)
void c_Layouting__Item__setMaxSizeHint_QSize(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QSize *>(arg__1_);
    fromPtr(thisObj)->setMaxSizeHint(arg__1);
}
// setMinSize(QSize arg__1)
void c_Layouting__Item__setMinSize_QSize(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QSize *>(arg__1_);
    fromPtr(thisObj)->setMinSize(arg__1);
}
// setPos(QPoint arg__1)
void c_Layouting__Item__setPos_QPoint(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QPoint *>(arg__1_);
    fromWrapperPtr(thisObj)->setPos(arg__1);
}
// setSize(QSize arg__1)
void c_Layouting__Item__setSize_QSize(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QSize *>(arg__1_);
    fromPtr(thisObj)->setSize(arg__1);
}
// size() const
void *c_Layouting__Item__size(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { fromPtr(thisObj)->size() };
}
// tr(const char * s, const char * c, int n)
void *c_static_Layouting__Item__tr_char_char_int(const char *s, const char *c, int n)
{
    return new Dartagnan::ValueWrapper<QString> { KDDockWidgetsBindings_wrappersNS::Item_wrapper::tr(s, c, n) };
}
// unref()
void c_Layouting__Item__unref(void *thisObj)
{
    fromPtr(thisObj)->unref();
}
// updateWidgetGeometries()
void c_Layouting__Item__updateWidgetGeometries(void *thisObj)
{
    fromWrapperPtr(thisObj)->updateWidgetGeometries_nocallback();
}
// visibleCount_recursive() const
int c_Layouting__Item__visibleCount_recursive(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->visibleCount_recursive_nocallback();} else {    return targetPtr->visibleCount_recursive();} }();
}
// width() const
int c_Layouting__Item__width(void *thisObj)
{
    return fromPtr(thisObj)->width();
}
// x() const
int c_Layouting__Item__x(void *thisObj)
{
    return fromPtr(thisObj)->x();
}
// y() const
int c_Layouting__Item__y(void *thisObj)
{
    return fromPtr(thisObj)->y();
}
void c_Layouting__Item__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
int c_static_Layouting__Item___get_separatorThickness()
{
    return KDDockWidgetsBindings_wrappersNS::Item_wrapper::separatorThickness;
}
bool c_static_Layouting__Item___get_s_silenceSanityChecks()
{
    return KDDockWidgetsBindings_wrappersNS::Item_wrapper::s_silenceSanityChecks;
}
void c_static_Layouting__Item___set_separatorThickness_int(int separatorThickness_)
{
    KDDockWidgetsBindings_wrappersNS::Item_wrapper::separatorThickness = separatorThickness_;
}
void c_static_Layouting__Item___set_s_silenceSanityChecks_bool(bool s_silenceSanityChecks_)
{
    KDDockWidgetsBindings_wrappersNS::Item_wrapper::s_silenceSanityChecks = s_silenceSanityChecks_;
}
void c_Layouting__Item__registerVirtualMethodCallback(void *ptr, void *callback, int methodId)
{
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 590:
        wrapper->m_checkSanityCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_checkSanity>(callback);
        break;
    case 295:
        wrapper->m_customEventCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_customEvent>(callback);
        break;
    case 597:
        wrapper->m_dumpLayoutCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_dumpLayout>(callback);
        break;
    case 306:
        wrapper->m_eventCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_event>(callback);
        break;
    case 307:
        wrapper->m_eventFilterCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_eventFilter>(callback);
        break;
    case 614:
        wrapper->m_isVisibleCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_isVisible>(callback);
        break;
    case 623:
        wrapper->m_maxSizeHintCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_maxSizeHint>(callback);
        break;
    case 624:
        wrapper->m_minSizeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_minSize>(callback);
        break;
    case 641:
        wrapper->m_setGeometry_recursiveCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_setGeometry_recursive>(callback);
        break;
    case 643:
        wrapper->m_setHostViewCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_setHostView>(callback);
        break;
    case 644:
        wrapper->m_setIsVisibleCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_setIsVisible>(callback);
        break;
    case 658:
        wrapper->m_updateWidgetGeometriesCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_updateWidgetGeometries>(callback);
        break;
    case 659:
        wrapper->m_visibleCount_recursiveCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_visibleCount_recursive>(callback);
        break;
    }
}
}

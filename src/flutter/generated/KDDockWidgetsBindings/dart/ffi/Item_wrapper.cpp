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
// tag=1006
Item_wrapper::Item_wrapper(KDDockWidgets::View *hostWidget)
    : ::Layouting::Item(hostWidget)
{
}
bool Item_wrapper::checkSanity()
{
    // tag=1000
    if (m_checkSanityCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_checkSanityCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        return ::Layouting::Item::checkSanity();
    }
}
// tag=1009
bool Item_wrapper::checkSanity_nocallback()
{
    // tag=1003
    return ::Layouting::Item::checkSanity();
}
void Item_wrapper::customEvent(QEvent *event)
{
    // tag=1000
    if (m_customEventCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_customEventCallback(const_cast<void *>(thisPtr), event);
    } else {
        // tag=1002
        ::Layouting::Item::customEvent(event);
    }
}
// tag=1009
void Item_wrapper::customEvent_nocallback(QEvent *event)
{
    // tag=1003
    ::Layouting::Item::customEvent(event);
}
void Item_wrapper::dumpLayout(int level)
{
    // tag=1000
    if (m_dumpLayoutCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_dumpLayoutCallback(const_cast<void *>(thisPtr), level);
    } else {
        // tag=1002
        ::Layouting::Item::dumpLayout(level);
    }
}
// tag=1009
void Item_wrapper::dumpLayout_nocallback(int level)
{
    // tag=1003
    ::Layouting::Item::dumpLayout(level);
}
bool Item_wrapper::event(QEvent *event)
{
    // tag=1000
    if (m_eventCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_eventCallback(const_cast<void *>(thisPtr), event);
    } else {
        // tag=1002
        return ::Layouting::Item::event(event);
    }
}
// tag=1009
bool Item_wrapper::event_nocallback(QEvent *event)
{
    // tag=1003
    return ::Layouting::Item::event(event);
}
bool Item_wrapper::eventFilter(QObject *watched, QEvent *event)
{
    // tag=1000
    if (m_eventFilterCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_eventFilterCallback(const_cast<void *>(thisPtr), watched, event);
    } else {
        // tag=1002
        return ::Layouting::Item::eventFilter(watched, event);
    }
}
// tag=1009
bool Item_wrapper::eventFilter_nocallback(QObject *watched, QEvent *event)
{
    // tag=1003
    return ::Layouting::Item::eventFilter(watched, event);
}
QRect Item_wrapper::geometry() const
{
    // tag=1000

    // tag=1004
    return ::Layouting::Item::geometry();
}
KDDockWidgets::View *Item_wrapper::guestView() const
{
    // tag=1000

    // tag=1004
    return ::Layouting::Item::guestView();
}
int Item_wrapper::height() const
{
    // tag=1000

    // tag=1004
    return ::Layouting::Item::height();
}
KDDockWidgets::View *Item_wrapper::hostView() const
{
    // tag=1000

    // tag=1004
    return ::Layouting::Item::hostView();
}
bool Item_wrapper::isBeingInserted() const
{
    // tag=1000

    // tag=1004
    return ::Layouting::Item::isBeingInserted();
}
bool Item_wrapper::isContainer() const
{
    // tag=1000

    // tag=1004
    return ::Layouting::Item::isContainer();
}
bool Item_wrapper::isMDI() const
{
    // tag=1000

    // tag=1004
    return ::Layouting::Item::isMDI();
}
bool Item_wrapper::isPlaceholder() const
{
    // tag=1000

    // tag=1004
    return ::Layouting::Item::isPlaceholder();
}
bool Item_wrapper::isRoot() const
{
    // tag=1000

    // tag=1004
    return ::Layouting::Item::isRoot();
}
bool Item_wrapper::isVisible(bool excludeBeingInserted) const
{
    // tag=1000
    if (m_isVisibleCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_isVisibleCallback(const_cast<void *>(thisPtr), excludeBeingInserted);
    } else {
        // tag=1002
        return ::Layouting::Item::isVisible(excludeBeingInserted);
    }
}
// tag=1009
bool Item_wrapper::isVisible_nocallback(bool excludeBeingInserted) const
{
    // tag=1003
    return ::Layouting::Item::isVisible(excludeBeingInserted);
}
QPoint Item_wrapper::mapFromParent(QPoint arg__1) const
{
    // tag=1000

    // tag=1004
    return ::Layouting::Item::mapFromParent(arg__1);
}
QPoint Item_wrapper::mapFromRoot(QPoint arg__1) const
{
    // tag=1000

    // tag=1004
    return ::Layouting::Item::mapFromRoot(arg__1);
}
QRect Item_wrapper::mapFromRoot(QRect arg__1) const
{
    // tag=1000

    // tag=1004
    return ::Layouting::Item::mapFromRoot(arg__1);
}
QPoint Item_wrapper::mapToRoot(QPoint arg__1) const
{
    // tag=1000

    // tag=1004
    return ::Layouting::Item::mapToRoot(arg__1);
}
QRect Item_wrapper::mapToRoot(QRect arg__1) const
{
    // tag=1000

    // tag=1004
    return ::Layouting::Item::mapToRoot(arg__1);
}
QSize Item_wrapper::maxSizeHint() const
{
    // tag=1000
    if (m_maxSizeHintCallback) {
        // tag=1001
        const void *thisPtr = this;
        return *m_maxSizeHintCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        return ::Layouting::Item::maxSizeHint();
    }
}
// tag=1009
QSize Item_wrapper::maxSizeHint_nocallback() const
{
    // tag=1003
    return ::Layouting::Item::maxSizeHint();
}
QSize Item_wrapper::minSize() const
{
    // tag=1000
    if (m_minSizeCallback) {
        // tag=1001
        const void *thisPtr = this;
        return *m_minSizeCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        return ::Layouting::Item::minSize();
    }
}
// tag=1009
QSize Item_wrapper::minSize_nocallback() const
{
    // tag=1003
    return ::Layouting::Item::minSize();
}
QSize Item_wrapper::missingSize() const
{
    // tag=1000

    // tag=1004
    return ::Layouting::Item::missingSize();
}
QPoint Item_wrapper::pos() const
{
    // tag=1000

    // tag=1004
    return ::Layouting::Item::pos();
}
QRect Item_wrapper::rect() const
{
    // tag=1000

    // tag=1004
    return ::Layouting::Item::rect();
}
void Item_wrapper::ref()
{
    // tag=1000

    // tag=1004
    ::Layouting::Item::ref();
}
int Item_wrapper::refCount() const
{
    // tag=1000

    // tag=1004
    return ::Layouting::Item::refCount();
}
void Item_wrapper::restore(KDDockWidgets::View *guestView)
{
    // tag=1000

    // tag=1004
    ::Layouting::Item::restore(guestView);
}
void Item_wrapper::setBeingInserted(bool arg__1)
{
    // tag=1000

    // tag=1004
    ::Layouting::Item::setBeingInserted(arg__1);
}
void Item_wrapper::setGeometry(QRect rect)
{
    // tag=1000

    // tag=1004
    ::Layouting::Item::setGeometry(rect);
}
void Item_wrapper::setGeometry_recursive(QRect rect)
{
    // tag=1000
    if (m_setGeometry_recursiveCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setGeometry_recursiveCallback(const_cast<void *>(thisPtr), rect);
    } else {
        // tag=1002
        ::Layouting::Item::setGeometry_recursive(rect);
    }
}
// tag=1009
void Item_wrapper::setGeometry_recursive_nocallback(QRect rect)
{
    // tag=1003
    ::Layouting::Item::setGeometry_recursive(rect);
}
void Item_wrapper::setGuestView(KDDockWidgets::View *arg__1)
{
    // tag=1000

    // tag=1004
    ::Layouting::Item::setGuestView(arg__1);
}
void Item_wrapper::setHostView(KDDockWidgets::View *arg__1)
{
    // tag=1000
    if (m_setHostViewCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setHostViewCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        // tag=1002
        ::Layouting::Item::setHostView(arg__1);
    }
}
// tag=1009
void Item_wrapper::setHostView_nocallback(KDDockWidgets::View *arg__1)
{
    // tag=1003
    ::Layouting::Item::setHostView(arg__1);
}
void Item_wrapper::setIsVisible(bool arg__1)
{
    // tag=1000
    if (m_setIsVisibleCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setIsVisibleCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        // tag=1002
        ::Layouting::Item::setIsVisible(arg__1);
    }
}
// tag=1009
void Item_wrapper::setIsVisible_nocallback(bool arg__1)
{
    // tag=1003
    ::Layouting::Item::setIsVisible(arg__1);
}
void Item_wrapper::setMaxSizeHint(QSize arg__1)
{
    // tag=1000

    // tag=1004
    ::Layouting::Item::setMaxSizeHint(arg__1);
}
void Item_wrapper::setMinSize(QSize arg__1)
{
    // tag=1000

    // tag=1004
    ::Layouting::Item::setMinSize(arg__1);
}
void Item_wrapper::setPos(QPoint arg__1)
{
    // tag=1000

    // tag=1004
    ::Layouting::Item::setPos(arg__1);
}
void Item_wrapper::setSize(QSize arg__1)
{
    // tag=1000

    // tag=1004
    ::Layouting::Item::setSize(arg__1);
}
QSize Item_wrapper::size() const
{
    // tag=1000

    // tag=1004
    return ::Layouting::Item::size();
}
QString Item_wrapper::tr(const char *s, const char *c, int n)
{
    // tag=1000

    // tag=1004
    return ::Layouting::Item::tr(s, c, n);
}
void Item_wrapper::unref()
{
    // tag=1000

    // tag=1004
    ::Layouting::Item::unref();
}
void Item_wrapper::updateWidgetGeometries()
{
    // tag=1000
    if (m_updateWidgetGeometriesCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_updateWidgetGeometriesCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        ::Layouting::Item::updateWidgetGeometries();
    }
}
// tag=1009
void Item_wrapper::updateWidgetGeometries_nocallback()
{
    // tag=1003
    ::Layouting::Item::updateWidgetGeometries();
}
int Item_wrapper::visibleCount_recursive() const
{
    // tag=1000
    if (m_visibleCount_recursiveCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_visibleCount_recursiveCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        return ::Layouting::Item::visibleCount_recursive();
    }
}
// tag=1009
int Item_wrapper::visibleCount_recursive_nocallback() const
{
    // tag=1003
    return ::Layouting::Item::visibleCount_recursive();
}
int Item_wrapper::width() const
{
    // tag=1000

    // tag=1004
    return ::Layouting::Item::width();
}
int Item_wrapper::x() const
{
    // tag=1000

    // tag=1004
    return ::Layouting::Item::x();
}
int Item_wrapper::y() const
{
    // tag=1000

    // tag=1004
    return ::Layouting::Item::y();
}

// tag=1005
Item_wrapper::~Item_wrapper()
{
}

}
// tag=1013
static Layouting::Item *fromPtr(void *ptr)
{
    return reinterpret_cast<Layouting::Item *>(ptr);
}
// tag=1014
static KDDockWidgetsBindings_wrappersNS::Item_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper *>(ptr);
}
extern "C" {

// tag=1049
void c_Layouting__Item_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper *>(cppObj);
}
void *c_Layouting__Item__constructor_View(void *hostWidget_)
{
    auto hostWidget = reinterpret_cast<KDDockWidgets::View *>(hostWidget_);
    // tag=1056
    auto ptr = new KDDockWidgetsBindings_wrappersNS::Item_wrapper(hostWidget);
    return reinterpret_cast<void *>(ptr);
}

// tag=1050
// checkSanity()
bool c_Layouting__Item__checkSanity(void *thisObj)
{
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->checkSanity_nocallback();} else {    return targetPtr->checkSanity();} }();
}

// tag=1050
// customEvent(QEvent * event)
void c_Layouting__Item__customEvent_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    // tag=1011

    // tag=1074
    fromWrapperPtr(thisObj)->customEvent_nocallback(event);
}

// tag=1050
// dumpLayout(int level)
void c_Layouting__Item__dumpLayout_int(void *thisObj, int level)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->dumpLayout_nocallback(level);} else {    return targetPtr->dumpLayout(level);} }();
}

// tag=1050
// event(QEvent * event)
bool c_Layouting__Item__event_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->event_nocallback(event);} else {    return targetPtr->event(event);} }();
}

// tag=1050
// eventFilter(QObject * watched, QEvent * event)
bool c_Layouting__Item__eventFilter_QObject_QEvent(void *thisObj, void *watched_, void *event_)
{
    auto watched = reinterpret_cast<QObject *>(watched_);
    auto event = reinterpret_cast<QEvent *>(event_);
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->eventFilter_nocallback(watched,event);} else {    return targetPtr->eventFilter(watched,event);} }();
}

// tag=1050
// geometry() const
void *c_Layouting__Item__geometry(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QRect> { fromPtr(thisObj)->geometry() };
}

// tag=1050
// guestView() const
void *c_Layouting__Item__guestView(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->guestView();
}

// tag=1050
// height() const
int c_Layouting__Item__height(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->height();
}

// tag=1050
// hostView() const
void *c_Layouting__Item__hostView(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->hostView();
}

// tag=1050
// isBeingInserted() const
bool c_Layouting__Item__isBeingInserted(void *thisObj)
{
    return
        // tag=1011

        // tag=1073
        fromWrapperPtr(thisObj)->isBeingInserted();
}

// tag=1050
// isContainer() const
bool c_Layouting__Item__isContainer(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->isContainer();
}

// tag=1050
// isMDI() const
bool c_Layouting__Item__isMDI(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->isMDI();
}

// tag=1050
// isPlaceholder() const
bool c_Layouting__Item__isPlaceholder(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->isPlaceholder();
}

// tag=1050
// isRoot() const
bool c_Layouting__Item__isRoot(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->isRoot();
}

// tag=1050
// isVisible(bool excludeBeingInserted) const
bool c_Layouting__Item__isVisible_bool(void *thisObj, bool excludeBeingInserted)
{
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isVisible_nocallback(excludeBeingInserted);} else {    return targetPtr->isVisible(excludeBeingInserted);} }();
}

// tag=1050
// mapFromParent(QPoint arg__1) const
void *c_Layouting__Item__mapFromParent_QPoint(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QPoint *>(arg__1_);
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QPoint> { fromPtr(thisObj)->mapFromParent(arg__1) };
}

// tag=1050
// mapFromRoot(QPoint arg__1) const
void *c_Layouting__Item__mapFromRoot_QPoint(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QPoint *>(arg__1_);
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QPoint> { fromPtr(thisObj)->mapFromRoot(arg__1) };
}

// tag=1050
// mapFromRoot(QRect arg__1) const
void *c_Layouting__Item__mapFromRoot_QRect(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QRect *>(arg__1_);
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QRect> { fromPtr(thisObj)->mapFromRoot(arg__1) };
}

// tag=1050
// mapToRoot(QPoint arg__1) const
void *c_Layouting__Item__mapToRoot_QPoint(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QPoint *>(arg__1_);
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QPoint> { fromPtr(thisObj)->mapToRoot(arg__1) };
}

// tag=1050
// mapToRoot(QRect arg__1) const
void *c_Layouting__Item__mapToRoot_QRect(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QRect *>(arg__1_);
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QRect> { fromPtr(thisObj)->mapToRoot(arg__1) };
}

// tag=1050
// maxSizeHint() const
void *c_Layouting__Item__maxSizeHint(void *thisObj)
{
    return
        // tag=1016

        // tag=1072
        new Dartagnan::ValueWrapper<QSize> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->maxSizeHint_nocallback();} else {    return targetPtr->maxSizeHint();} }() };
}

// tag=1050
// minSize() const
void *c_Layouting__Item__minSize(void *thisObj)
{
    return
        // tag=1016

        // tag=1072
        new Dartagnan::ValueWrapper<QSize> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->minSize_nocallback();} else {    return targetPtr->minSize();} }() };
}

// tag=1050
// missingSize() const
void *c_Layouting__Item__missingSize(void *thisObj)
{
    return
        // tag=1011

        // tag=1073

        // tag=1072
        new Dartagnan::ValueWrapper<QSize> { fromWrapperPtr(thisObj)->missingSize() };
}

// tag=1050
// pos() const
void *c_Layouting__Item__pos(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QPoint> { fromPtr(thisObj)->pos() };
}

// tag=1050
// rect() const
void *c_Layouting__Item__rect(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QRect> { fromPtr(thisObj)->rect() };
}

// tag=1050
// ref()
void c_Layouting__Item__ref(void *thisObj)
{
    // tag=1010
    fromPtr(thisObj)->ref();
}

// tag=1050
// refCount() const
int c_Layouting__Item__refCount(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->refCount();
}

// tag=1050
// restore(KDDockWidgets::View * guestView)
void c_Layouting__Item__restore_View(void *thisObj, void *guestView_)
{
    auto guestView = reinterpret_cast<KDDockWidgets::View *>(guestView_);
    // tag=1010
    fromPtr(thisObj)->restore(guestView);
}

// tag=1050
// setBeingInserted(bool arg__1)
void c_Layouting__Item__setBeingInserted_bool(void *thisObj, bool arg__1)
{
    // tag=1011

    // tag=1073
    fromWrapperPtr(thisObj)->setBeingInserted(arg__1);
}

// tag=1050
// setGeometry(QRect rect)
void c_Layouting__Item__setGeometry_QRect(void *thisObj, void *rect_)
{
    auto &rect = *reinterpret_cast<QRect *>(rect_);
    // tag=1010
    fromPtr(thisObj)->setGeometry(rect);
}

// tag=1050
// setGeometry_recursive(QRect rect)
void c_Layouting__Item__setGeometry_recursive_QRect(void *thisObj, void *rect_)
{
    auto &rect = *reinterpret_cast<QRect *>(rect_);
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setGeometry_recursive_nocallback(rect);} else {    return targetPtr->setGeometry_recursive(rect);} }();
}

// tag=1050
// setGuestView(KDDockWidgets::View * arg__1)
void c_Layouting__Item__setGuestView_View(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::View *>(arg__1_);
    // tag=1010
    fromPtr(thisObj)->setGuestView(arg__1);
}

// tag=1050
// setHostView(KDDockWidgets::View * arg__1)
void c_Layouting__Item__setHostView_View(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::View *>(arg__1_);
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setHostView_nocallback(arg__1);} else {    return targetPtr->setHostView(arg__1);} }();
}

// tag=1050
// setIsVisible(bool arg__1)
void c_Layouting__Item__setIsVisible_bool(void *thisObj, bool arg__1)
{
    // tag=1011

    // tag=1074
    fromWrapperPtr(thisObj)->setIsVisible_nocallback(arg__1);
}

// tag=1050
// setMaxSizeHint(QSize arg__1)
void c_Layouting__Item__setMaxSizeHint_QSize(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QSize *>(arg__1_);
    // tag=1010
    fromPtr(thisObj)->setMaxSizeHint(arg__1);
}

// tag=1050
// setMinSize(QSize arg__1)
void c_Layouting__Item__setMinSize_QSize(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QSize *>(arg__1_);
    // tag=1010
    fromPtr(thisObj)->setMinSize(arg__1);
}

// tag=1050
// setPos(QPoint arg__1)
void c_Layouting__Item__setPos_QPoint(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QPoint *>(arg__1_);
    // tag=1011

    // tag=1073
    fromWrapperPtr(thisObj)->setPos(arg__1);
}

// tag=1050
// setSize(QSize arg__1)
void c_Layouting__Item__setSize_QSize(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QSize *>(arg__1_);
    // tag=1010
    fromPtr(thisObj)->setSize(arg__1);
}

// tag=1050
// size() const
void *c_Layouting__Item__size(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QSize> { fromPtr(thisObj)->size() };
}

// tag=1050
// tr(const char * s, const char * c, int n)
void *c_static_Layouting__Item__tr_char_char_int(const char *s, const char *c, int n)
{
    return
        // tag=1068

        // tag=1072
        new Dartagnan::ValueWrapper<QString> { KDDockWidgetsBindings_wrappersNS::Item_wrapper::tr(s, c, n) };
}

// tag=1050
// unref()
void c_Layouting__Item__unref(void *thisObj)
{
    // tag=1010
    fromPtr(thisObj)->unref();
}

// tag=1050
// updateWidgetGeometries()
void c_Layouting__Item__updateWidgetGeometries(void *thisObj)
{
    // tag=1011

    // tag=1074
    fromWrapperPtr(thisObj)->updateWidgetGeometries_nocallback();
}

// tag=1050
// visibleCount_recursive() const
int c_Layouting__Item__visibleCount_recursive(void *thisObj)
{
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->visibleCount_recursive_nocallback();} else {    return targetPtr->visibleCount_recursive();} }();
}

// tag=1050
// width() const
int c_Layouting__Item__width(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->width();
}

// tag=1050
// x() const
int c_Layouting__Item__x(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->x();
}

// tag=1050
// y() const
int c_Layouting__Item__y(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->y();
}
void c_Layouting__Item__destructor(void *thisObj)
{

    // tag=1055
    delete fromPtr(thisObj);
}
int c_static_Layouting__Item___get_separatorThickness()
{

    // tag=1054
    return KDDockWidgetsBindings_wrappersNS::Item_wrapper::separatorThickness;
}
bool c_static_Layouting__Item___get_s_silenceSanityChecks()
{

    // tag=1054
    return KDDockWidgetsBindings_wrappersNS::Item_wrapper::s_silenceSanityChecks;
}
void c_static_Layouting__Item___set_separatorThickness_int(int separatorThickness_)
{

    // tag=1059
    KDDockWidgetsBindings_wrappersNS::Item_wrapper::separatorThickness = separatorThickness_;
}
void c_static_Layouting__Item___set_s_silenceSanityChecks_bool(bool s_silenceSanityChecks_)
{

    // tag=1059
    KDDockWidgetsBindings_wrappersNS::Item_wrapper::s_silenceSanityChecks = s_silenceSanityChecks_;
}
void c_Layouting__Item__registerVirtualMethodCallback(void *ptr, void *callback, int methodId)
{
    // tag=1048
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 589:
        wrapper->m_checkSanityCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_checkSanity>(callback);
        break;
    case 295:
        wrapper->m_customEventCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_customEvent>(callback);
        break;
    case 596:
        wrapper->m_dumpLayoutCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_dumpLayout>(callback);
        break;
    case 306:
        wrapper->m_eventCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_event>(callback);
        break;
    case 307:
        wrapper->m_eventFilterCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_eventFilter>(callback);
        break;
    case 613:
        wrapper->m_isVisibleCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_isVisible>(callback);
        break;
    case 622:
        wrapper->m_maxSizeHintCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_maxSizeHint>(callback);
        break;
    case 623:
        wrapper->m_minSizeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_minSize>(callback);
        break;
    case 640:
        wrapper->m_setGeometry_recursiveCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_setGeometry_recursive>(callback);
        break;
    case 642:
        wrapper->m_setHostViewCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_setHostView>(callback);
        break;
    case 643:
        wrapper->m_setIsVisibleCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_setIsVisible>(callback);
        break;
    case 657:
        wrapper->m_updateWidgetGeometriesCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_updateWidgetGeometries>(callback);
        break;
    case 658:
        wrapper->m_visibleCount_recursiveCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_visibleCount_recursive>(callback);
        break;
    }
}
}

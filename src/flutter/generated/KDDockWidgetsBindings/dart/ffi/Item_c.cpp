/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "Item_c.h"


#include <iostream>

#include <cassert>


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
Item_wrapper::Item_wrapper(KDDockWidgets::Core::View *hostWidget)
    : ::KDDockWidgets::Core::Item(hostWidget)
{
}
KDDockWidgets::Core::Group *Item_wrapper::asGroupController() const
{
    return ::KDDockWidgets::Core::Item::asGroupController();
}
bool Item_wrapper::checkSanity()
{
    if (m_checkSanityCallback) {
        const void *thisPtr = this;
        return m_checkSanityCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Core::Item::checkSanity();
    }
}
bool Item_wrapper::checkSanity_nocallback()
{
    return ::KDDockWidgets::Core::Item::checkSanity();
}
void Item_wrapper::dumpLayout(int level)
{
    if (m_dumpLayoutCallback) {
        const void *thisPtr = this;
        m_dumpLayoutCallback(const_cast<void *>(thisPtr), level);
    } else {
        ::KDDockWidgets::Core::Item::dumpLayout(level);
    }
}
void Item_wrapper::dumpLayout_nocallback(int level)
{
    ::KDDockWidgets::Core::Item::dumpLayout(level);
}
KDDockWidgets::Rect Item_wrapper::geometry() const
{
    return ::KDDockWidgets::Core::Item::geometry();
}
KDDockWidgets::Core::View *Item_wrapper::guestView() const
{
    return ::KDDockWidgets::Core::Item::guestView();
}
int Item_wrapper::height() const
{
    return ::KDDockWidgets::Core::Item::height();
}
KDDockWidgets::Core::View *Item_wrapper::hostView() const
{
    return ::KDDockWidgets::Core::Item::hostView();
}
bool Item_wrapper::isBeingInserted() const
{
    return ::KDDockWidgets::Core::Item::isBeingInserted();
}
bool Item_wrapper::isContainer() const
{
    return ::KDDockWidgets::Core::Item::isContainer();
}
bool Item_wrapper::isMDI() const
{
    return ::KDDockWidgets::Core::Item::isMDI();
}
bool Item_wrapper::isPlaceholder() const
{
    return ::KDDockWidgets::Core::Item::isPlaceholder();
}
bool Item_wrapper::isRoot() const
{
    return ::KDDockWidgets::Core::Item::isRoot();
}
bool Item_wrapper::isVisible(bool excludeBeingInserted) const
{
    if (m_isVisibleCallback) {
        const void *thisPtr = this;
        return m_isVisibleCallback(const_cast<void *>(thisPtr), excludeBeingInserted);
    } else {
        return ::KDDockWidgets::Core::Item::isVisible(excludeBeingInserted);
    }
}
bool Item_wrapper::isVisible_nocallback(bool excludeBeingInserted) const
{
    return ::KDDockWidgets::Core::Item::isVisible(excludeBeingInserted);
}
KDDockWidgets::Point Item_wrapper::mapFromParent(KDDockWidgets::Point arg__1) const
{
    return ::KDDockWidgets::Core::Item::mapFromParent(arg__1);
}
KDDockWidgets::Point Item_wrapper::mapFromRoot(KDDockWidgets::Point arg__1) const
{
    return ::KDDockWidgets::Core::Item::mapFromRoot(arg__1);
}
KDDockWidgets::Rect Item_wrapper::mapFromRoot(KDDockWidgets::Rect arg__1) const
{
    return ::KDDockWidgets::Core::Item::mapFromRoot(arg__1);
}
KDDockWidgets::Point Item_wrapper::mapToRoot(KDDockWidgets::Point arg__1) const
{
    return ::KDDockWidgets::Core::Item::mapToRoot(arg__1);
}
KDDockWidgets::Rect Item_wrapper::mapToRoot(KDDockWidgets::Rect arg__1) const
{
    return ::KDDockWidgets::Core::Item::mapToRoot(arg__1);
}
KDDockWidgets::Size Item_wrapper::maxSizeHint() const
{
    if (m_maxSizeHintCallback) {
        const void *thisPtr = this;
        return *m_maxSizeHintCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Core::Item::maxSizeHint();
    }
}
KDDockWidgets::Size Item_wrapper::maxSizeHint_nocallback() const
{
    return ::KDDockWidgets::Core::Item::maxSizeHint();
}
KDDockWidgets::Size Item_wrapper::minSize() const
{
    if (m_minSizeCallback) {
        const void *thisPtr = this;
        return *m_minSizeCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Core::Item::minSize();
    }
}
KDDockWidgets::Size Item_wrapper::minSize_nocallback() const
{
    return ::KDDockWidgets::Core::Item::minSize();
}
KDDockWidgets::Size Item_wrapper::missingSize() const
{
    return ::KDDockWidgets::Core::Item::missingSize();
}
KDDockWidgets::Point Item_wrapper::pos() const
{
    return ::KDDockWidgets::Core::Item::pos();
}
KDDockWidgets::Rect Item_wrapper::rect() const
{
    return ::KDDockWidgets::Core::Item::rect();
}
void Item_wrapper::ref()
{
    ::KDDockWidgets::Core::Item::ref();
}
int Item_wrapper::refCount() const
{
    return ::KDDockWidgets::Core::Item::refCount();
}
void Item_wrapper::restore(KDDockWidgets::Core::View *guestView)
{
    ::KDDockWidgets::Core::Item::restore(guestView);
}
void Item_wrapper::setBeingInserted(bool arg__1)
{
    ::KDDockWidgets::Core::Item::setBeingInserted(arg__1);
}
void Item_wrapper::setGeometry(KDDockWidgets::Rect rect)
{
    ::KDDockWidgets::Core::Item::setGeometry(rect);
}
void Item_wrapper::setGeometry_recursive(KDDockWidgets::Rect rect)
{
    if (m_setGeometry_recursiveCallback) {
        const void *thisPtr = this;
        m_setGeometry_recursiveCallback(const_cast<void *>(thisPtr), &rect);
    } else {
        ::KDDockWidgets::Core::Item::setGeometry_recursive(rect);
    }
}
void Item_wrapper::setGeometry_recursive_nocallback(KDDockWidgets::Rect rect)
{
    ::KDDockWidgets::Core::Item::setGeometry_recursive(rect);
}
void Item_wrapper::setGuestView(KDDockWidgets::Core::View *arg__1)
{
    ::KDDockWidgets::Core::Item::setGuestView(arg__1);
}
void Item_wrapper::setHostView(KDDockWidgets::Core::View *arg__1)
{
    if (m_setHostViewCallback) {
        const void *thisPtr = this;
        m_setHostViewCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        ::KDDockWidgets::Core::Item::setHostView(arg__1);
    }
}
void Item_wrapper::setHostView_nocallback(KDDockWidgets::Core::View *arg__1)
{
    ::KDDockWidgets::Core::Item::setHostView(arg__1);
}
void Item_wrapper::setIsVisible(bool arg__1)
{
    if (m_setIsVisibleCallback) {
        const void *thisPtr = this;
        m_setIsVisibleCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        ::KDDockWidgets::Core::Item::setIsVisible(arg__1);
    }
}
void Item_wrapper::setIsVisible_nocallback(bool arg__1)
{
    ::KDDockWidgets::Core::Item::setIsVisible(arg__1);
}
void Item_wrapper::setMaxSizeHint(KDDockWidgets::Size arg__1)
{
    ::KDDockWidgets::Core::Item::setMaxSizeHint(arg__1);
}
void Item_wrapper::setMinSize(KDDockWidgets::Size arg__1)
{
    ::KDDockWidgets::Core::Item::setMinSize(arg__1);
}
void Item_wrapper::setPos(KDDockWidgets::Point arg__1)
{
    ::KDDockWidgets::Core::Item::setPos(arg__1);
}
void Item_wrapper::setSize(KDDockWidgets::Size arg__1)
{
    ::KDDockWidgets::Core::Item::setSize(arg__1);
}
KDDockWidgets::Size Item_wrapper::size() const
{
    return ::KDDockWidgets::Core::Item::size();
}
void Item_wrapper::turnIntoPlaceholder()
{
    ::KDDockWidgets::Core::Item::turnIntoPlaceholder();
}
void Item_wrapper::unref()
{
    ::KDDockWidgets::Core::Item::unref();
}
void Item_wrapper::updateWidgetGeometries()
{
    if (m_updateWidgetGeometriesCallback) {
        const void *thisPtr = this;
        m_updateWidgetGeometriesCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Core::Item::updateWidgetGeometries();
    }
}
void Item_wrapper::updateWidgetGeometries_nocallback()
{
    ::KDDockWidgets::Core::Item::updateWidgetGeometries();
}
int Item_wrapper::visibleCount_recursive() const
{
    if (m_visibleCount_recursiveCallback) {
        const void *thisPtr = this;
        return m_visibleCount_recursiveCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Core::Item::visibleCount_recursive();
    }
}
int Item_wrapper::visibleCount_recursive_nocallback() const
{
    return ::KDDockWidgets::Core::Item::visibleCount_recursive();
}
int Item_wrapper::width() const
{
    return ::KDDockWidgets::Core::Item::width();
}
int Item_wrapper::x() const
{
    return ::KDDockWidgets::Core::Item::x();
}
int Item_wrapper::y() const
{
    return ::KDDockWidgets::Core::Item::y();
}
Item_wrapper::~Item_wrapper()
{
}

}
static KDDockWidgets::Core::Item *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::Core::Item *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::Item_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__Core__Item_Finalizer(void *cppObj)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper *>(cppObj);
}
void *c_KDDockWidgets__Core__Item__constructor_View(void *hostWidget_)
{
    auto hostWidget = reinterpret_cast<KDDockWidgets::Core::View *>(hostWidget_);
    auto ptr = new KDDockWidgetsBindings_wrappersNS::Item_wrapper(hostWidget);
    return reinterpret_cast<void *>(ptr);
}
// asGroupController() const
void *c_KDDockWidgets__Core__Item__asGroupController(void *thisObj)
{
    return fromPtr(thisObj)->asGroupController();
}
// checkSanity()
bool c_KDDockWidgets__Core__Item__checkSanity(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->checkSanity_nocallback();} else {    return targetPtr->checkSanity();} }();
}
// dumpLayout(int level)
void c_KDDockWidgets__Core__Item__dumpLayout_int(void *thisObj, int level)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->dumpLayout_nocallback(level);} else {    return targetPtr->dumpLayout(level);} }();
}
// geometry() const
void *c_KDDockWidgets__Core__Item__geometry(void *thisObj)
{
    return new Dartagnan::ValueWrapper<KDDockWidgets::Rect> { fromPtr(thisObj)->geometry() };
}
// guestView() const
void *c_KDDockWidgets__Core__Item__guestView(void *thisObj)
{
    return fromPtr(thisObj)->guestView();
}
// height() const
int c_KDDockWidgets__Core__Item__height(void *thisObj)
{
    return fromPtr(thisObj)->height();
}
// hostView() const
void *c_KDDockWidgets__Core__Item__hostView(void *thisObj)
{
    return fromPtr(thisObj)->hostView();
}
// isBeingInserted() const
bool c_KDDockWidgets__Core__Item__isBeingInserted(void *thisObj)
{
    return fromPtr(thisObj)->isBeingInserted();
}
// isContainer() const
bool c_KDDockWidgets__Core__Item__isContainer(void *thisObj)
{
    return fromPtr(thisObj)->isContainer();
}
// isMDI() const
bool c_KDDockWidgets__Core__Item__isMDI(void *thisObj)
{
    return fromPtr(thisObj)->isMDI();
}
// isPlaceholder() const
bool c_KDDockWidgets__Core__Item__isPlaceholder(void *thisObj)
{
    return fromPtr(thisObj)->isPlaceholder();
}
// isRoot() const
bool c_KDDockWidgets__Core__Item__isRoot(void *thisObj)
{
    return fromPtr(thisObj)->isRoot();
}
// isVisible(bool excludeBeingInserted) const
bool c_KDDockWidgets__Core__Item__isVisible_bool(void *thisObj, bool excludeBeingInserted)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isVisible_nocallback(excludeBeingInserted);} else {    return targetPtr->isVisible(excludeBeingInserted);} }();
}
// mapFromParent(KDDockWidgets::Point arg__1) const
void *c_KDDockWidgets__Core__Item__mapFromParent_Point(void *thisObj, void *arg__1_)
{
    assert(arg__1_);
    auto &arg__1 = *reinterpret_cast<KDDockWidgets::Point *>(arg__1_);
    return new Dartagnan::ValueWrapper<KDDockWidgets::Point> { fromPtr(thisObj)->mapFromParent(arg__1) };
}
// mapFromRoot(KDDockWidgets::Point arg__1) const
void *c_KDDockWidgets__Core__Item__mapFromRoot_Point(void *thisObj, void *arg__1_)
{
    assert(arg__1_);
    auto &arg__1 = *reinterpret_cast<KDDockWidgets::Point *>(arg__1_);
    return new Dartagnan::ValueWrapper<KDDockWidgets::Point> { fromPtr(thisObj)->mapFromRoot(arg__1) };
}
// mapFromRoot(KDDockWidgets::Rect arg__1) const
void *c_KDDockWidgets__Core__Item__mapFromRoot_Rect(void *thisObj, void *arg__1_)
{
    assert(arg__1_);
    auto &arg__1 = *reinterpret_cast<KDDockWidgets::Rect *>(arg__1_);
    return new Dartagnan::ValueWrapper<KDDockWidgets::Rect> { fromPtr(thisObj)->mapFromRoot(arg__1) };
}
// mapToRoot(KDDockWidgets::Point arg__1) const
void *c_KDDockWidgets__Core__Item__mapToRoot_Point(void *thisObj, void *arg__1_)
{
    assert(arg__1_);
    auto &arg__1 = *reinterpret_cast<KDDockWidgets::Point *>(arg__1_);
    return new Dartagnan::ValueWrapper<KDDockWidgets::Point> { fromPtr(thisObj)->mapToRoot(arg__1) };
}
// mapToRoot(KDDockWidgets::Rect arg__1) const
void *c_KDDockWidgets__Core__Item__mapToRoot_Rect(void *thisObj, void *arg__1_)
{
    assert(arg__1_);
    auto &arg__1 = *reinterpret_cast<KDDockWidgets::Rect *>(arg__1_);
    return new Dartagnan::ValueWrapper<KDDockWidgets::Rect> { fromPtr(thisObj)->mapToRoot(arg__1) };
}
// maxSizeHint() const
void *c_KDDockWidgets__Core__Item__maxSizeHint(void *thisObj)
{
    return new Dartagnan::ValueWrapper<KDDockWidgets::Size> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->maxSizeHint_nocallback();} else {    return targetPtr->maxSizeHint();} }() };
}
// minSize() const
void *c_KDDockWidgets__Core__Item__minSize(void *thisObj)
{
    return new Dartagnan::ValueWrapper<KDDockWidgets::Size> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->minSize_nocallback();} else {    return targetPtr->minSize();} }() };
}
// missingSize() const
void *c_KDDockWidgets__Core__Item__missingSize(void *thisObj)
{
    return new Dartagnan::ValueWrapper<KDDockWidgets::Size> { fromPtr(thisObj)->missingSize() };
}
// pos() const
void *c_KDDockWidgets__Core__Item__pos(void *thisObj)
{
    return new Dartagnan::ValueWrapper<KDDockWidgets::Point> { fromPtr(thisObj)->pos() };
}
// rect() const
void *c_KDDockWidgets__Core__Item__rect(void *thisObj)
{
    return new Dartagnan::ValueWrapper<KDDockWidgets::Rect> { fromPtr(thisObj)->rect() };
}
// ref()
void c_KDDockWidgets__Core__Item__ref(void *thisObj)
{
    fromPtr(thisObj)->ref();
}
// refCount() const
int c_KDDockWidgets__Core__Item__refCount(void *thisObj)
{
    return fromPtr(thisObj)->refCount();
}
// restore(KDDockWidgets::Core::View * guestView)
void c_KDDockWidgets__Core__Item__restore_View(void *thisObj, void *guestView_)
{
    auto guestView = reinterpret_cast<KDDockWidgets::Core::View *>(guestView_);
    fromPtr(thisObj)->restore(guestView);
}
// setBeingInserted(bool arg__1)
void c_KDDockWidgets__Core__Item__setBeingInserted_bool(void *thisObj, bool arg__1)
{
    fromPtr(thisObj)->setBeingInserted(arg__1);
}
// setGeometry(KDDockWidgets::Rect rect)
void c_KDDockWidgets__Core__Item__setGeometry_Rect(void *thisObj, void *rect_)
{
    assert(rect_);
    auto &rect = *reinterpret_cast<KDDockWidgets::Rect *>(rect_);
    fromPtr(thisObj)->setGeometry(rect);
}
// setGeometry_recursive(KDDockWidgets::Rect rect)
void c_KDDockWidgets__Core__Item__setGeometry_recursive_Rect(void *thisObj, void *rect_)
{
    assert(rect_);
    auto &rect = *reinterpret_cast<KDDockWidgets::Rect *>(rect_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setGeometry_recursive_nocallback(rect);} else {    return targetPtr->setGeometry_recursive(rect);} }();
}
// setGuestView(KDDockWidgets::Core::View * arg__1)
void c_KDDockWidgets__Core__Item__setGuestView_View(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Core::View *>(arg__1_);
    fromPtr(thisObj)->setGuestView(arg__1);
}
// setHostView(KDDockWidgets::Core::View * arg__1)
void c_KDDockWidgets__Core__Item__setHostView_View(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Core::View *>(arg__1_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setHostView_nocallback(arg__1);} else {    return targetPtr->setHostView(arg__1);} }();
}
// setIsVisible(bool arg__1)
void c_KDDockWidgets__Core__Item__setIsVisible_bool(void *thisObj, bool arg__1)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setIsVisible_nocallback(arg__1);} else {    return targetPtr->setIsVisible(arg__1);} }();
}
// setMaxSizeHint(KDDockWidgets::Size arg__1)
void c_KDDockWidgets__Core__Item__setMaxSizeHint_Size(void *thisObj, void *arg__1_)
{
    assert(arg__1_);
    auto &arg__1 = *reinterpret_cast<KDDockWidgets::Size *>(arg__1_);
    fromPtr(thisObj)->setMaxSizeHint(arg__1);
}
// setMinSize(KDDockWidgets::Size arg__1)
void c_KDDockWidgets__Core__Item__setMinSize_Size(void *thisObj, void *arg__1_)
{
    assert(arg__1_);
    auto &arg__1 = *reinterpret_cast<KDDockWidgets::Size *>(arg__1_);
    fromPtr(thisObj)->setMinSize(arg__1);
}
// setPos(KDDockWidgets::Point arg__1)
void c_KDDockWidgets__Core__Item__setPos_Point(void *thisObj, void *arg__1_)
{
    assert(arg__1_);
    auto &arg__1 = *reinterpret_cast<KDDockWidgets::Point *>(arg__1_);
    fromPtr(thisObj)->setPos(arg__1);
}
// setSize(KDDockWidgets::Size arg__1)
void c_KDDockWidgets__Core__Item__setSize_Size(void *thisObj, void *arg__1_)
{
    assert(arg__1_);
    auto &arg__1 = *reinterpret_cast<KDDockWidgets::Size *>(arg__1_);
    fromPtr(thisObj)->setSize(arg__1);
}
// size() const
void *c_KDDockWidgets__Core__Item__size(void *thisObj)
{
    return new Dartagnan::ValueWrapper<KDDockWidgets::Size> { fromPtr(thisObj)->size() };
}
// turnIntoPlaceholder()
void c_KDDockWidgets__Core__Item__turnIntoPlaceholder(void *thisObj)
{
    fromPtr(thisObj)->turnIntoPlaceholder();
}
// unref()
void c_KDDockWidgets__Core__Item__unref(void *thisObj)
{
    fromPtr(thisObj)->unref();
}
// updateWidgetGeometries()
void c_KDDockWidgets__Core__Item__updateWidgetGeometries(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->updateWidgetGeometries_nocallback();} else {    return targetPtr->updateWidgetGeometries();} }();
}
// visibleCount_recursive() const
int c_KDDockWidgets__Core__Item__visibleCount_recursive(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->visibleCount_recursive_nocallback();} else {    return targetPtr->visibleCount_recursive();} }();
}
// width() const
int c_KDDockWidgets__Core__Item__width(void *thisObj)
{
    return fromPtr(thisObj)->width();
}
// x() const
int c_KDDockWidgets__Core__Item__x(void *thisObj)
{
    return fromPtr(thisObj)->x();
}
// y() const
int c_KDDockWidgets__Core__Item__y(void *thisObj)
{
    return fromPtr(thisObj)->y();
}
void c_KDDockWidgets__Core__Item__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
int c_static_KDDockWidgets__Core__Item___get_separatorThickness()
{
    return KDDockWidgetsBindings_wrappersNS::Item_wrapper::separatorThickness;
}
bool c_static_KDDockWidgets__Core__Item___get_s_silenceSanityChecks()
{
    return KDDockWidgetsBindings_wrappersNS::Item_wrapper::s_silenceSanityChecks;
}
bool c_KDDockWidgets__Core__Item___get_m_isContainer(void *thisObj)
{
    return fromPtr(thisObj)->m_isContainer;
}
bool c_KDDockWidgets__Core__Item___get_m_isSettingGuest(void *thisObj)
{
    return fromPtr(thisObj)->m_isSettingGuest;
}
bool c_KDDockWidgets__Core__Item___get_m_inDtor(void *thisObj)
{
    return fromPtr(thisObj)->m_inDtor;
}
void c_static_KDDockWidgets__Core__Item___set_separatorThickness_int(int separatorThickness_)
{
    KDDockWidgetsBindings_wrappersNS::Item_wrapper::separatorThickness = separatorThickness_;
}
void c_static_KDDockWidgets__Core__Item___set_s_silenceSanityChecks_bool(bool s_silenceSanityChecks_)
{
    KDDockWidgetsBindings_wrappersNS::Item_wrapper::s_silenceSanityChecks = s_silenceSanityChecks_;
}
void c_KDDockWidgets__Core__Item___set_m_isSettingGuest_bool(void *thisObj, bool m_isSettingGuest_)
{
    fromPtr(thisObj)->m_isSettingGuest = m_isSettingGuest_;
}
void c_KDDockWidgets__Core__Item___set_m_inDtor_bool(void *thisObj, bool m_inDtor_)
{
    fromPtr(thisObj)->m_inDtor = m_inDtor_;
}
void c_KDDockWidgets__Core__Item__registerVirtualMethodCallback(void *ptr, void *callback, int methodId)
{
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 255:
        wrapper->m_checkSanityCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_checkSanity>(callback);
        break;
    case 256:
        wrapper->m_dumpLayoutCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_dumpLayout>(callback);
        break;
    case 266:
        wrapper->m_isVisibleCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_isVisible>(callback);
        break;
    case 272:
        wrapper->m_maxSizeHintCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_maxSizeHint>(callback);
        break;
    case 273:
        wrapper->m_minSizeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_minSize>(callback);
        break;
    case 287:
        wrapper->m_setGeometry_recursiveCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_setGeometry_recursive>(callback);
        break;
    case 289:
        wrapper->m_setHostViewCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_setHostView>(callback);
        break;
    case 290:
        wrapper->m_setIsVisibleCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_setIsVisible>(callback);
        break;
    case 302:
        wrapper->m_updateWidgetGeometriesCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_updateWidgetGeometries>(callback);
        break;
    case 303:
        wrapper->m_visibleCount_recursiveCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Item_wrapper::Callback_visibleCount_recursive>(callback);
        break;
    }
}
}

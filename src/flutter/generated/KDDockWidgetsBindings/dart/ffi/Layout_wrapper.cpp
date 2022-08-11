/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

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
Layout_wrapper::Layout_wrapper(KDDockWidgets::Type arg__1, KDDockWidgets::View *arg__2)
    : ::KDDockWidgets::Controllers::Layout(arg__1, arg__2)
{
}
KDDockWidgets::Controllers::DropArea *Layout_wrapper::asDropArea() const
{
    return ::KDDockWidgets::Controllers::Layout::asDropArea();
}
bool Layout_wrapper::checkSanity() const
{
    return ::KDDockWidgets::Controllers::Layout::checkSanity();
}
void Layout_wrapper::clearLayout()
{
    ::KDDockWidgets::Controllers::Layout::clearLayout();
}
bool Layout_wrapper::containsFrame(const KDDockWidgets::Controllers::Group *arg__1) const
{
    return ::KDDockWidgets::Controllers::Layout::containsFrame(arg__1);
}
bool Layout_wrapper::containsItem(const Layouting::Item *arg__1) const
{
    return ::KDDockWidgets::Controllers::Layout::containsItem(arg__1);
}
int Layout_wrapper::count() const
{
    return ::KDDockWidgets::Controllers::Layout::count();
}
void Layout_wrapper::customEvent(QEvent *event)
{
    if (m_customEventCallback) {
        const void *thisPtr = this;
        m_customEventCallback(const_cast<void *>(thisPtr), event);
    } else {
        ::KDDockWidgets::Controllers::Layout::customEvent(event);
    }
}
void Layout_wrapper::customEvent_nocallback(QEvent *event)
{
    ::KDDockWidgets::Controllers::Layout::customEvent(event);
}
void Layout_wrapper::dumpLayout() const
{
    ::KDDockWidgets::Controllers::Layout::dumpLayout();
}
bool Layout_wrapper::event(QEvent *event)
{
    if (m_eventCallback) {
        const void *thisPtr = this;
        return m_eventCallback(const_cast<void *>(thisPtr), event);
    } else {
        return ::KDDockWidgets::Controllers::Layout::event(event);
    }
}
bool Layout_wrapper::event_nocallback(QEvent *event)
{
    return ::KDDockWidgets::Controllers::Layout::event(event);
}
bool Layout_wrapper::eventFilter(QObject *watched, QEvent *event)
{
    if (m_eventFilterCallback) {
        const void *thisPtr = this;
        return m_eventFilterCallback(const_cast<void *>(thisPtr), watched, event);
    } else {
        return ::KDDockWidgets::Controllers::Layout::eventFilter(watched, event);
    }
}
bool Layout_wrapper::eventFilter_nocallback(QObject *watched, QEvent *event)
{
    return ::KDDockWidgets::Controllers::Layout::eventFilter(watched, event);
}
KDDockWidgets::Controllers::FloatingWindow *Layout_wrapper::floatingWindow() const
{
    return ::KDDockWidgets::Controllers::Layout::floatingWindow();
}
QList<KDDockWidgets::Controllers::Group *> Layout_wrapper::groups() const
{
    return ::KDDockWidgets::Controllers::Layout::groups();
}
QList<KDDockWidgets::Controllers::Group *>
Layout_wrapper::groupsFrom(KDDockWidgets::View *groupOrMultiSplitter) const
{
    return ::KDDockWidgets::Controllers::Layout::groupsFrom(groupOrMultiSplitter);
}
bool Layout_wrapper::isInMainWindow(bool honourNesting) const
{
    return ::KDDockWidgets::Controllers::Layout::isInMainWindow(honourNesting);
}
Layouting::Item *Layout_wrapper::itemForFrame(const KDDockWidgets::Controllers::Group *group) const
{
    return ::KDDockWidgets::Controllers::Layout::itemForFrame(group);
}
int Layout_wrapper::layoutHeight() const
{
    return ::KDDockWidgets::Controllers::Layout::layoutHeight();
}
QSize Layout_wrapper::layoutMaximumSizeHint() const
{
    return ::KDDockWidgets::Controllers::Layout::layoutMaximumSizeHint();
}
QSize Layout_wrapper::layoutMinimumSize() const
{
    return ::KDDockWidgets::Controllers::Layout::layoutMinimumSize();
}
QSize Layout_wrapper::layoutSize() const
{
    return ::KDDockWidgets::Controllers::Layout::layoutSize();
}
int Layout_wrapper::layoutWidth() const
{
    return ::KDDockWidgets::Controllers::Layout::layoutWidth();
}
int Layout_wrapper::placeholderCount() const
{
    return ::KDDockWidgets::Controllers::Layout::placeholderCount();
}
void Layout_wrapper::removeItem(Layouting::Item *item)
{
    ::KDDockWidgets::Controllers::Layout::removeItem(item);
}
void Layout_wrapper::setLayoutMinimumSize(QSize arg__1)
{
    ::KDDockWidgets::Controllers::Layout::setLayoutMinimumSize(arg__1);
}
void Layout_wrapper::setLayoutSize(QSize arg__1)
{
    ::KDDockWidgets::Controllers::Layout::setLayoutSize(arg__1);
}
void Layout_wrapper::setParentView_impl(KDDockWidgets::View *parent)
{
    if (m_setParentView_implCallback) {
        const void *thisPtr = this;
        m_setParentView_implCallback(const_cast<void *>(thisPtr), parent);
    } else {
        ::KDDockWidgets::Controllers::Layout::setParentView_impl(parent);
    }
}
void Layout_wrapper::setParentView_impl_nocallback(KDDockWidgets::View *parent)
{
    ::KDDockWidgets::Controllers::Layout::setParentView_impl(parent);
}
void Layout_wrapper::unrefOldPlaceholders(
    const QList<KDDockWidgets::Controllers::Group *> &groupsBeingAdded) const
{
    ::KDDockWidgets::Controllers::Layout::unrefOldPlaceholders(groupsBeingAdded);
}
void Layout_wrapper::updateSizeConstraints()
{
    ::KDDockWidgets::Controllers::Layout::updateSizeConstraints();
}
void Layout_wrapper::viewAboutToBeDeleted()
{
    ::KDDockWidgets::Controllers::Layout::viewAboutToBeDeleted();
}
int Layout_wrapper::visibleCount() const
{
    return ::KDDockWidgets::Controllers::Layout::visibleCount();
}
Layout_wrapper::~Layout_wrapper()
{
}

}
static KDDockWidgets::Controllers::Layout *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::Controllers::Layout *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::Layout_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Layout_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__Controllers__Layout_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Layout_wrapper *>(cppObj);
}
void *c_KDDockWidgets__Controllers__Layout__constructor_Type_View(int arg__1, void *arg__2_)
{
    auto arg__2 = reinterpret_cast<KDDockWidgets::View *>(arg__2_);
    auto ptr = new KDDockWidgetsBindings_wrappersNS::Layout_wrapper(
        static_cast<KDDockWidgets::Type>(arg__1), arg__2);
    return reinterpret_cast<void *>(ptr);
}
// asDropArea() const
void *c_KDDockWidgets__Controllers__Layout__asDropArea(void *thisObj)
{
    return fromPtr(thisObj)->asDropArea();
}
// checkSanity() const
bool c_KDDockWidgets__Controllers__Layout__checkSanity(void *thisObj)
{
    return fromPtr(thisObj)->checkSanity();
}
// clearLayout()
void c_KDDockWidgets__Controllers__Layout__clearLayout(void *thisObj)
{
    fromPtr(thisObj)->clearLayout();
}
// containsFrame(const KDDockWidgets::Controllers::Group * arg__1) const
bool c_KDDockWidgets__Controllers__Layout__containsFrame_Group(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::Group *>(arg__1_);
    return fromPtr(thisObj)->containsFrame(arg__1);
}
// containsItem(const Layouting::Item * arg__1) const
bool c_KDDockWidgets__Controllers__Layout__containsItem_Item(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<Layouting::Item *>(arg__1_);
    return fromPtr(thisObj)->containsItem(arg__1);
}
// count() const
int c_KDDockWidgets__Controllers__Layout__count(void *thisObj)
{
    return fromPtr(thisObj)->count();
}
// customEvent(QEvent * event)
void c_KDDockWidgets__Controllers__Layout__customEvent_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    fromWrapperPtr(thisObj)->customEvent_nocallback(event);
}
// dumpLayout() const
void c_KDDockWidgets__Controllers__Layout__dumpLayout(void *thisObj)
{
    fromPtr(thisObj)->dumpLayout();
}
// event(QEvent * event)
bool c_KDDockWidgets__Controllers__Layout__event_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Layout_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->event_nocallback(event);
        } else {
            return targetPtr->event(event);
        }
    }();
}
// eventFilter(QObject * watched, QEvent * event)
bool c_KDDockWidgets__Controllers__Layout__eventFilter_QObject_QEvent(void *thisObj, void *watched_,
                                                                      void *event_)
{
    auto watched = reinterpret_cast<QObject *>(watched_);
    auto event = reinterpret_cast<QEvent *>(event_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Layout_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->eventFilter_nocallback(watched, event);
        } else {
            return targetPtr->eventFilter(watched, event);
        }
    }();
}
// floatingWindow() const
void *c_KDDockWidgets__Controllers__Layout__floatingWindow(void *thisObj)
{
    return fromPtr(thisObj)->floatingWindow();
}
// groups() const
void *c_KDDockWidgets__Controllers__Layout__groups(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Controllers::Group *>> {
        fromPtr(thisObj)->groups()
    };
}
// groupsFrom(KDDockWidgets::View * groupOrMultiSplitter) const
void *c_KDDockWidgets__Controllers__Layout__groupsFrom_View(void *thisObj,
                                                            void *groupOrMultiSplitter_)
{
    auto groupOrMultiSplitter = reinterpret_cast<KDDockWidgets::View *>(groupOrMultiSplitter_);
    return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Controllers::Group *>> {
        fromWrapperPtr(thisObj)->groupsFrom(groupOrMultiSplitter)
    };
}
// isInMainWindow(bool honourNesting) const
bool c_KDDockWidgets__Controllers__Layout__isInMainWindow_bool(void *thisObj, bool honourNesting)
{
    return fromPtr(thisObj)->isInMainWindow(honourNesting);
}
// itemForFrame(const KDDockWidgets::Controllers::Group * group) const
void *c_KDDockWidgets__Controllers__Layout__itemForFrame_Group(void *thisObj, void *group_)
{
    auto group = reinterpret_cast<KDDockWidgets::Controllers::Group *>(group_);
    return fromPtr(thisObj)->itemForFrame(group);
}
// layoutHeight() const
int c_KDDockWidgets__Controllers__Layout__layoutHeight(void *thisObj)
{
    return fromPtr(thisObj)->layoutHeight();
}
// layoutMaximumSizeHint() const
void *c_KDDockWidgets__Controllers__Layout__layoutMaximumSizeHint(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { fromPtr(thisObj)->layoutMaximumSizeHint() };
}
// layoutMinimumSize() const
void *c_KDDockWidgets__Controllers__Layout__layoutMinimumSize(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { fromPtr(thisObj)->layoutMinimumSize() };
}
// layoutSize() const
void *c_KDDockWidgets__Controllers__Layout__layoutSize(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { fromPtr(thisObj)->layoutSize() };
}
// layoutWidth() const
int c_KDDockWidgets__Controllers__Layout__layoutWidth(void *thisObj)
{
    return fromPtr(thisObj)->layoutWidth();
}
// placeholderCount() const
int c_KDDockWidgets__Controllers__Layout__placeholderCount(void *thisObj)
{
    return fromPtr(thisObj)->placeholderCount();
}
// removeItem(Layouting::Item * item)
void c_KDDockWidgets__Controllers__Layout__removeItem_Item(void *thisObj, void *item_)
{
    auto item = reinterpret_cast<Layouting::Item *>(item_);
    fromPtr(thisObj)->removeItem(item);
}
// setLayoutMinimumSize(QSize arg__1)
void c_KDDockWidgets__Controllers__Layout__setLayoutMinimumSize_QSize(void *thisObj, void *arg__1_)
{
    assert(arg__1_);
    auto &arg__1 = *reinterpret_cast<QSize *>(arg__1_);
    fromWrapperPtr(thisObj)->setLayoutMinimumSize(arg__1);
}
// setLayoutSize(QSize arg__1)
void c_KDDockWidgets__Controllers__Layout__setLayoutSize_QSize(void *thisObj, void *arg__1_)
{
    assert(arg__1_);
    auto &arg__1 = *reinterpret_cast<QSize *>(arg__1_);
    fromPtr(thisObj)->setLayoutSize(arg__1);
}
// setParentView_impl(KDDockWidgets::View * parent)
void c_KDDockWidgets__Controllers__Layout__setParentView_impl_View(void *thisObj, void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    fromWrapperPtr(thisObj)->setParentView_impl_nocallback(parent);
}
// unrefOldPlaceholders(const QList<KDDockWidgets::Controllers::Group* > & groupsBeingAdded) const
void c_KDDockWidgets__Controllers__Layout__unrefOldPlaceholders_QList_Group(void *thisObj,
                                                                            void *groupsBeingAdded_)
{
    assert(groupsBeingAdded_);
    auto &groupsBeingAdded =
        *reinterpret_cast<QList<KDDockWidgets::Controllers::Group *> *>(groupsBeingAdded_);
    fromWrapperPtr(thisObj)->unrefOldPlaceholders(groupsBeingAdded);
}
// updateSizeConstraints()
void c_KDDockWidgets__Controllers__Layout__updateSizeConstraints(void *thisObj)
{
    fromPtr(thisObj)->updateSizeConstraints();
}
// viewAboutToBeDeleted()
void c_KDDockWidgets__Controllers__Layout__viewAboutToBeDeleted(void *thisObj)
{
    fromPtr(thisObj)->viewAboutToBeDeleted();
}
// visibleCount() const
int c_KDDockWidgets__Controllers__Layout__visibleCount(void *thisObj)
{
    return fromPtr(thisObj)->visibleCount();
}
void c_KDDockWidgets__Controllers__Layout__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__Controllers__Layout__registerVirtualMethodCallback(void *ptr, void *callback,
                                                                         int methodId)
{
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 295:
        wrapper->m_customEventCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Layout_wrapper::Callback_customEvent>(callback);
        break;
    case 306:
        wrapper->m_eventCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Layout_wrapper::Callback_event>(
                callback);
        break;
    case 307:
        wrapper->m_eventFilterCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Layout_wrapper::Callback_eventFilter>(callback);
        break;
    case 826:
        wrapper->m_setParentView_implCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Layout_wrapper::Callback_setParentView_impl>(
            callback);
        break;
    }
}
}

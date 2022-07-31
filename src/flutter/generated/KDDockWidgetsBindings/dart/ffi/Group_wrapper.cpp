/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "Group_wrapper.h"


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
Group_wrapper::Group_wrapper(KDDockWidgets::View *parent)
    : ::KDDockWidgets::Controllers::Group(parent)
{
}
void Group_wrapper::actualTitleBarChanged()
{
    ::KDDockWidgets::Controllers::Group::actualTitleBarChanged();
}
void Group_wrapper::addTab(KDDockWidgets::Controllers::Group *arg__1, KDDockWidgets::InitialOption arg__2)
{
    ::KDDockWidgets::Controllers::Group::addTab(arg__1, arg__2);
}
bool Group_wrapper::allDockWidgetsHave(KDDockWidgets::DockWidgetOption arg__1) const
{
    return ::KDDockWidgets::Controllers::Group::allDockWidgetsHave(arg__1);
}
bool Group_wrapper::allDockWidgetsHave(KDDockWidgets::LayoutSaverOption arg__1) const
{
    return ::KDDockWidgets::Controllers::Group::allDockWidgetsHave(arg__1);
}
bool Group_wrapper::alwaysShowsTabs() const
{
    return ::KDDockWidgets::Controllers::Group::alwaysShowsTabs();
}
bool Group_wrapper::anyDockWidgetsHas(KDDockWidgets::DockWidgetOption arg__1) const
{
    return ::KDDockWidgets::Controllers::Group::anyDockWidgetsHas(arg__1);
}
bool Group_wrapper::anyDockWidgetsHas(KDDockWidgets::LayoutSaverOption arg__1) const
{
    return ::KDDockWidgets::Controllers::Group::anyDockWidgetsHas(arg__1);
}
bool Group_wrapper::anyNonClosable() const
{
    return ::KDDockWidgets::Controllers::Group::anyNonClosable();
}
bool Group_wrapper::anyNonDockable() const
{
    return ::KDDockWidgets::Controllers::Group::anyNonDockable();
}
bool Group_wrapper::beingDeletedLater() const
{
    return ::KDDockWidgets::Controllers::Group::beingDeletedLater();
}
QSize Group_wrapper::biggestDockWidgetMaxSize() const
{
    return ::KDDockWidgets::Controllers::Group::biggestDockWidgetMaxSize();
}
bool Group_wrapper::containsMouse(QPoint globalPos) const
{
    return ::KDDockWidgets::Controllers::Group::containsMouse(globalPos);
}
int Group_wrapper::currentIndex() const
{
    return ::KDDockWidgets::Controllers::Group::currentIndex();
}
int Group_wrapper::currentTabIndex() const
{
    return ::KDDockWidgets::Controllers::Group::currentTabIndex();
}
void Group_wrapper::customEvent(QEvent *event)
{
    if (m_customEventCallback) {
        const void *thisPtr = this;
        m_customEventCallback(const_cast<void *>(thisPtr), event);
    } else {
        ::KDDockWidgets::Controllers::Group::customEvent(event);
    }
}
void Group_wrapper::customEvent_nocallback(QEvent *event)
{
    ::KDDockWidgets::Controllers::Group::customEvent(event);
}
int Group_wrapper::dbg_numFrames()
{
    return ::KDDockWidgets::Controllers::Group::dbg_numFrames();
}
int Group_wrapper::dockWidgetCount() const
{
    return ::KDDockWidgets::Controllers::Group::dockWidgetCount();
}
QSize Group_wrapper::dockWidgetsMinSize() const
{
    return ::KDDockWidgets::Controllers::Group::dockWidgetsMinSize();
}
QRect Group_wrapper::dragRect() const
{
    if (m_dragRectCallback) {
        const void *thisPtr = this;
        return *m_dragRectCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Controllers::Group::dragRect();
    }
}
QRect Group_wrapper::dragRect_nocallback() const
{
    return ::KDDockWidgets::Controllers::Group::dragRect();
}
bool Group_wrapper::event(QEvent *event)
{
    if (m_eventCallback) {
        const void *thisPtr = this;
        return m_eventCallback(const_cast<void *>(thisPtr), event);
    } else {
        return ::KDDockWidgets::Controllers::Group::event(event);
    }
}
bool Group_wrapper::event_nocallback(QEvent *event)
{
    return ::KDDockWidgets::Controllers::Group::event(event);
}
bool Group_wrapper::eventFilter(QObject *watched, QEvent *event)
{
    if (m_eventFilterCallback) {
        const void *thisPtr = this;
        return m_eventFilterCallback(const_cast<void *>(thisPtr), watched, event);
    } else {
        return ::KDDockWidgets::Controllers::Group::eventFilter(watched, event);
    }
}
bool Group_wrapper::eventFilter_nocallback(QObject *watched, QEvent *event)
{
    return ::KDDockWidgets::Controllers::Group::eventFilter(watched, event);
}
void Group_wrapper::focusedWidgetChanged()
{
    ::KDDockWidgets::Controllers::Group::focusedWidgetChanged();
}
void Group_wrapper::focusedWidgetChangedCallback()
{
    if (m_focusedWidgetChangedCallbackCallback) {
        const void *thisPtr = this;
        m_focusedWidgetChangedCallbackCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Controllers::Group::focusedWidgetChangedCallback();
    }
}
void Group_wrapper::focusedWidgetChangedCallback_nocallback()
{
    ::KDDockWidgets::Controllers::Group::focusedWidgetChangedCallback();
}
bool Group_wrapper::hasNestedMDIDockWidgets() const
{
    return ::KDDockWidgets::Controllers::Group::hasNestedMDIDockWidgets();
}
bool Group_wrapper::hasSingleDockWidget() const
{
    return ::KDDockWidgets::Controllers::Group::hasSingleDockWidget();
}
bool Group_wrapper::hasTabsVisible() const
{
    return ::KDDockWidgets::Controllers::Group::hasTabsVisible();
}
void Group_wrapper::hasTabsVisibleChanged()
{
    ::KDDockWidgets::Controllers::Group::hasTabsVisibleChanged();
}
bool Group_wrapper::isCentralFrame() const
{
    return ::KDDockWidgets::Controllers::Group::isCentralFrame();
}
bool Group_wrapper::isDockable() const
{
    return ::KDDockWidgets::Controllers::Group::isDockable();
}
bool Group_wrapper::isEmpty() const
{
    return ::KDDockWidgets::Controllers::Group::isEmpty();
}
bool Group_wrapper::isFloating() const
{
    return ::KDDockWidgets::Controllers::Group::isFloating();
}
void Group_wrapper::isFocusedChanged()
{
    ::KDDockWidgets::Controllers::Group::isFocusedChanged();
}
void Group_wrapper::isFocusedChangedCallback()
{
    if (m_isFocusedChangedCallbackCallback) {
        const void *thisPtr = this;
        m_isFocusedChangedCallbackCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Controllers::Group::isFocusedChangedCallback();
    }
}
void Group_wrapper::isFocusedChangedCallback_nocallback()
{
    ::KDDockWidgets::Controllers::Group::isFocusedChangedCallback();
}
bool Group_wrapper::isInFloatingWindow() const
{
    return ::KDDockWidgets::Controllers::Group::isInFloatingWindow();
}
bool Group_wrapper::isInMainWindow() const
{
    return ::KDDockWidgets::Controllers::Group::isInMainWindow();
}
void Group_wrapper::isInMainWindowChanged()
{
    ::KDDockWidgets::Controllers::Group::isInMainWindowChanged();
}
bool Group_wrapper::isMDI() const
{
    return ::KDDockWidgets::Controllers::Group::isMDI();
}
void Group_wrapper::isMDIChanged()
{
    ::KDDockWidgets::Controllers::Group::isMDIChanged();
}
bool Group_wrapper::isMDIWrapper() const
{
    return ::KDDockWidgets::Controllers::Group::isMDIWrapper();
}
bool Group_wrapper::isOverlayed() const
{
    return ::KDDockWidgets::Controllers::Group::isOverlayed();
}
bool Group_wrapper::isTheOnlyFrame() const
{
    return ::KDDockWidgets::Controllers::Group::isTheOnlyFrame();
}
Layouting::Item *Group_wrapper::layoutItem() const
{
    return ::KDDockWidgets::Controllers::Group::layoutItem();
}
KDDockWidgets::Controllers::DropArea *Group_wrapper::mdiDropAreaWrapper() const
{
    return ::KDDockWidgets::Controllers::Group::mdiDropAreaWrapper();
}
KDDockWidgets::Controllers::Group *Group_wrapper::mdiFrame() const
{
    return ::KDDockWidgets::Controllers::Group::mdiFrame();
}
int Group_wrapper::nonContentsHeight() const
{
    return ::KDDockWidgets::Controllers::Group::nonContentsHeight();
}
void Group_wrapper::numDockWidgetsChanged()
{
    ::KDDockWidgets::Controllers::Group::numDockWidgetsChanged();
}
void Group_wrapper::onCurrentTabChanged(int index)
{
    ::KDDockWidgets::Controllers::Group::onCurrentTabChanged(index);
}
void Group_wrapper::onDockWidgetCountChanged()
{
    ::KDDockWidgets::Controllers::Group::onDockWidgetCountChanged();
}
void Group_wrapper::onDockWidgetTitleChanged()
{
    ::KDDockWidgets::Controllers::Group::onDockWidgetTitleChanged();
}
void Group_wrapper::renameTab(int index, const QString &arg__2)
{
    ::KDDockWidgets::Controllers::Group::renameTab(index, arg__2);
}
void Group_wrapper::restoreToPreviousPosition()
{
    ::KDDockWidgets::Controllers::Group::restoreToPreviousPosition();
}
void Group_wrapper::setCurrentTabIndex(int index)
{
    ::KDDockWidgets::Controllers::Group::setCurrentTabIndex(index);
}
void Group_wrapper::setLayout(KDDockWidgets::Controllers::Layout *arg__1)
{
    ::KDDockWidgets::Controllers::Group::setLayout(arg__1);
}
void Group_wrapper::setLayoutItem(Layouting::Item *item)
{
    ::KDDockWidgets::Controllers::Group::setLayoutItem(item);
}
void Group_wrapper::setParentView_impl(KDDockWidgets::View *parent)
{
    if (m_setParentView_implCallback) {
        const void *thisPtr = this;
        m_setParentView_implCallback(const_cast<void *>(thisPtr), parent);
    } else {
        ::KDDockWidgets::Controllers::Group::setParentView_impl(parent);
    }
}
void Group_wrapper::setParentView_impl_nocallback(KDDockWidgets::View *parent)
{
    ::KDDockWidgets::Controllers::Group::setParentView_impl(parent);
}
QString Group_wrapper::title() const
{
    return ::KDDockWidgets::Controllers::Group::title();
}
QString Group_wrapper::tr(const char *s, const char *c, int n)
{
    return ::KDDockWidgets::Controllers::Group::tr(s, c, n);
}
void Group_wrapper::unoverlay()
{
    ::KDDockWidgets::Controllers::Group::unoverlay();
}
void Group_wrapper::updateFloatingActions()
{
    ::KDDockWidgets::Controllers::Group::updateFloatingActions();
}
void Group_wrapper::updateTitleAndIcon()
{
    ::KDDockWidgets::Controllers::Group::updateTitleAndIcon();
}
void Group_wrapper::updateTitleBarVisibility()
{
    ::KDDockWidgets::Controllers::Group::updateTitleBarVisibility();
}
int Group_wrapper::userType() const
{
    return ::KDDockWidgets::Controllers::Group::userType();
}
Group_wrapper::~Group_wrapper()
{
}

}
static KDDockWidgets::Controllers::Group *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::Controllers::Group *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::Group_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Group_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__Controllers__Group_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Group_wrapper *>(cppObj);
}
void *c_KDDockWidgets__Controllers__Group__constructor_View(void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    auto ptr = new KDDockWidgetsBindings_wrappersNS::Group_wrapper(parent);
    return reinterpret_cast<void *>(ptr);
}
// actualTitleBarChanged()
void c_KDDockWidgets__Controllers__Group__actualTitleBarChanged(void *thisObj)
{
    fromPtr(thisObj)->actualTitleBarChanged();
}
// addTab(KDDockWidgets::Controllers::Group * arg__1, KDDockWidgets::InitialOption arg__2)
void c_KDDockWidgets__Controllers__Group__addTab_Group_InitialOption(void *thisObj, void *arg__1_, void *arg__2_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::Group *>(arg__1_);
    auto &arg__2 = *reinterpret_cast<KDDockWidgets::InitialOption *>(arg__2_);
    fromPtr(thisObj)->addTab(arg__1, arg__2);
}
// allDockWidgetsHave(KDDockWidgets::DockWidgetOption arg__1) const
bool c_KDDockWidgets__Controllers__Group__allDockWidgetsHave_DockWidgetOption(void *thisObj, int arg__1)
{
    return fromPtr(thisObj)->allDockWidgetsHave(static_cast<KDDockWidgets::DockWidgetOption>(arg__1));
}
// allDockWidgetsHave(KDDockWidgets::LayoutSaverOption arg__1) const
bool c_KDDockWidgets__Controllers__Group__allDockWidgetsHave_LayoutSaverOption(void *thisObj, int arg__1)
{
    return fromPtr(thisObj)->allDockWidgetsHave(static_cast<KDDockWidgets::LayoutSaverOption>(arg__1));
}
// alwaysShowsTabs() const
bool c_KDDockWidgets__Controllers__Group__alwaysShowsTabs(void *thisObj)
{
    return fromPtr(thisObj)->alwaysShowsTabs();
}
// anyDockWidgetsHas(KDDockWidgets::DockWidgetOption arg__1) const
bool c_KDDockWidgets__Controllers__Group__anyDockWidgetsHas_DockWidgetOption(void *thisObj, int arg__1)
{
    return fromPtr(thisObj)->anyDockWidgetsHas(static_cast<KDDockWidgets::DockWidgetOption>(arg__1));
}
// anyDockWidgetsHas(KDDockWidgets::LayoutSaverOption arg__1) const
bool c_KDDockWidgets__Controllers__Group__anyDockWidgetsHas_LayoutSaverOption(void *thisObj, int arg__1)
{
    return fromPtr(thisObj)->anyDockWidgetsHas(static_cast<KDDockWidgets::LayoutSaverOption>(arg__1));
}
// anyNonClosable() const
bool c_KDDockWidgets__Controllers__Group__anyNonClosable(void *thisObj)
{
    return fromPtr(thisObj)->anyNonClosable();
}
// anyNonDockable() const
bool c_KDDockWidgets__Controllers__Group__anyNonDockable(void *thisObj)
{
    return fromPtr(thisObj)->anyNonDockable();
}
// beingDeletedLater() const
bool c_KDDockWidgets__Controllers__Group__beingDeletedLater(void *thisObj)
{
    return fromPtr(thisObj)->beingDeletedLater();
}
// biggestDockWidgetMaxSize() const
void *c_KDDockWidgets__Controllers__Group__biggestDockWidgetMaxSize(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { fromPtr(thisObj)->biggestDockWidgetMaxSize() };
}
// containsMouse(QPoint globalPos) const
bool c_KDDockWidgets__Controllers__Group__containsMouse_QPoint(void *thisObj, void *globalPos_)
{
    auto &globalPos = *reinterpret_cast<QPoint *>(globalPos_);
    return fromPtr(thisObj)->containsMouse(globalPos);
}
// currentIndex() const
int c_KDDockWidgets__Controllers__Group__currentIndex(void *thisObj)
{
    return fromPtr(thisObj)->currentIndex();
}
// currentTabIndex() const
int c_KDDockWidgets__Controllers__Group__currentTabIndex(void *thisObj)
{
    return fromPtr(thisObj)->currentTabIndex();
}
// customEvent(QEvent * event)
void c_KDDockWidgets__Controllers__Group__customEvent_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    fromWrapperPtr(thisObj)->customEvent_nocallback(event);
}
// dbg_numFrames()
int c_static_KDDockWidgets__Controllers__Group__dbg_numFrames()
{
    return KDDockWidgetsBindings_wrappersNS::Group_wrapper::dbg_numFrames();
}
// dockWidgetCount() const
int c_KDDockWidgets__Controllers__Group__dockWidgetCount(void *thisObj)
{
    return fromPtr(thisObj)->dockWidgetCount();
}
// dockWidgetsMinSize() const
void *c_KDDockWidgets__Controllers__Group__dockWidgetsMinSize(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { fromPtr(thisObj)->dockWidgetsMinSize() };
}
// dragRect() const
void *c_KDDockWidgets__Controllers__Group__dragRect(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QRect> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->dragRect_nocallback();} else {    return targetPtr->dragRect();} }() };
}
// event(QEvent * event)
bool c_KDDockWidgets__Controllers__Group__event_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->event_nocallback(event);} else {    return targetPtr->event(event);} }();
}
// eventFilter(QObject * watched, QEvent * event)
bool c_KDDockWidgets__Controllers__Group__eventFilter_QObject_QEvent(void *thisObj, void *watched_, void *event_)
{
    auto watched = reinterpret_cast<QObject *>(watched_);
    auto event = reinterpret_cast<QEvent *>(event_);
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->eventFilter_nocallback(watched,event);} else {    return targetPtr->eventFilter(watched,event);} }();
}
// focusedWidgetChanged()
void c_KDDockWidgets__Controllers__Group__focusedWidgetChanged(void *thisObj)
{
    fromPtr(thisObj)->focusedWidgetChanged();
}
// focusedWidgetChangedCallback()
void c_KDDockWidgets__Controllers__Group__focusedWidgetChangedCallback(void *thisObj)
{
    fromWrapperPtr(thisObj)->focusedWidgetChangedCallback_nocallback();
}
// hasNestedMDIDockWidgets() const
bool c_KDDockWidgets__Controllers__Group__hasNestedMDIDockWidgets(void *thisObj)
{
    return fromPtr(thisObj)->hasNestedMDIDockWidgets();
}
// hasSingleDockWidget() const
bool c_KDDockWidgets__Controllers__Group__hasSingleDockWidget(void *thisObj)
{
    return fromPtr(thisObj)->hasSingleDockWidget();
}
// hasTabsVisible() const
bool c_KDDockWidgets__Controllers__Group__hasTabsVisible(void *thisObj)
{
    return fromPtr(thisObj)->hasTabsVisible();
}
// hasTabsVisibleChanged()
void c_KDDockWidgets__Controllers__Group__hasTabsVisibleChanged(void *thisObj)
{
    fromPtr(thisObj)->hasTabsVisibleChanged();
}
// isCentralFrame() const
bool c_KDDockWidgets__Controllers__Group__isCentralFrame(void *thisObj)
{
    return fromPtr(thisObj)->isCentralFrame();
}
// isDockable() const
bool c_KDDockWidgets__Controllers__Group__isDockable(void *thisObj)
{
    return fromPtr(thisObj)->isDockable();
}
// isEmpty() const
bool c_KDDockWidgets__Controllers__Group__isEmpty(void *thisObj)
{
    return fromPtr(thisObj)->isEmpty();
}
// isFloating() const
bool c_KDDockWidgets__Controllers__Group__isFloating(void *thisObj)
{
    return fromPtr(thisObj)->isFloating();
}
// isFocusedChanged()
void c_KDDockWidgets__Controllers__Group__isFocusedChanged(void *thisObj)
{
    fromPtr(thisObj)->isFocusedChanged();
}
// isFocusedChangedCallback()
void c_KDDockWidgets__Controllers__Group__isFocusedChangedCallback(void *thisObj)
{
    fromWrapperPtr(thisObj)->isFocusedChangedCallback_nocallback();
}
// isInFloatingWindow() const
bool c_KDDockWidgets__Controllers__Group__isInFloatingWindow(void *thisObj)
{
    return fromPtr(thisObj)->isInFloatingWindow();
}
// isInMainWindow() const
bool c_KDDockWidgets__Controllers__Group__isInMainWindow(void *thisObj)
{
    return fromPtr(thisObj)->isInMainWindow();
}
// isInMainWindowChanged()
void c_KDDockWidgets__Controllers__Group__isInMainWindowChanged(void *thisObj)
{
    fromPtr(thisObj)->isInMainWindowChanged();
}
// isMDI() const
bool c_KDDockWidgets__Controllers__Group__isMDI(void *thisObj)
{
    return fromPtr(thisObj)->isMDI();
}
// isMDIChanged()
void c_KDDockWidgets__Controllers__Group__isMDIChanged(void *thisObj)
{
    fromPtr(thisObj)->isMDIChanged();
}
// isMDIWrapper() const
bool c_KDDockWidgets__Controllers__Group__isMDIWrapper(void *thisObj)
{
    return fromPtr(thisObj)->isMDIWrapper();
}
// isOverlayed() const
bool c_KDDockWidgets__Controllers__Group__isOverlayed(void *thisObj)
{
    return fromPtr(thisObj)->isOverlayed();
}
// isTheOnlyFrame() const
bool c_KDDockWidgets__Controllers__Group__isTheOnlyFrame(void *thisObj)
{
    return fromPtr(thisObj)->isTheOnlyFrame();
}
// layoutItem() const
void *c_KDDockWidgets__Controllers__Group__layoutItem(void *thisObj)
{
    return fromPtr(thisObj)->layoutItem();
}
// mdiDropAreaWrapper() const
void *c_KDDockWidgets__Controllers__Group__mdiDropAreaWrapper(void *thisObj)
{
    return fromPtr(thisObj)->mdiDropAreaWrapper();
}
// mdiFrame() const
void *c_KDDockWidgets__Controllers__Group__mdiFrame(void *thisObj)
{
    return fromPtr(thisObj)->mdiFrame();
}
// nonContentsHeight() const
int c_KDDockWidgets__Controllers__Group__nonContentsHeight(void *thisObj)
{
    return fromPtr(thisObj)->nonContentsHeight();
}
// numDockWidgetsChanged()
void c_KDDockWidgets__Controllers__Group__numDockWidgetsChanged(void *thisObj)
{
    fromPtr(thisObj)->numDockWidgetsChanged();
}
// onCurrentTabChanged(int index)
void c_KDDockWidgets__Controllers__Group__onCurrentTabChanged_int(void *thisObj, int index)
{
    fromWrapperPtr(thisObj)->onCurrentTabChanged(index);
}
// onDockWidgetCountChanged()
void c_KDDockWidgets__Controllers__Group__onDockWidgetCountChanged(void *thisObj)
{
    fromPtr(thisObj)->onDockWidgetCountChanged();
}
// onDockWidgetTitleChanged()
void c_KDDockWidgets__Controllers__Group__onDockWidgetTitleChanged(void *thisObj)
{
    fromPtr(thisObj)->onDockWidgetTitleChanged();
}
// renameTab(int index, const QString & arg__2)
void c_KDDockWidgets__Controllers__Group__renameTab_int_QString(void *thisObj, int index, const char *arg__2_)
{
    const auto arg__2 = QString::fromUtf8(arg__2_);
    fromPtr(thisObj)->renameTab(index, arg__2);
}
// restoreToPreviousPosition()
void c_KDDockWidgets__Controllers__Group__restoreToPreviousPosition(void *thisObj)
{
    fromPtr(thisObj)->restoreToPreviousPosition();
}
// setCurrentTabIndex(int index)
void c_KDDockWidgets__Controllers__Group__setCurrentTabIndex_int(void *thisObj, int index)
{
    fromPtr(thisObj)->setCurrentTabIndex(index);
}
// setLayout(KDDockWidgets::Controllers::Layout * arg__1)
void c_KDDockWidgets__Controllers__Group__setLayout_Layout(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::Layout *>(arg__1_);
    fromPtr(thisObj)->setLayout(arg__1);
}
// setLayoutItem(Layouting::Item * item)
void c_KDDockWidgets__Controllers__Group__setLayoutItem_Item(void *thisObj, void *item_)
{
    auto item = reinterpret_cast<Layouting::Item *>(item_);
    fromPtr(thisObj)->setLayoutItem(item);
}
// setParentView_impl(KDDockWidgets::View * parent)
void c_KDDockWidgets__Controllers__Group__setParentView_impl_View(void *thisObj, void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    fromWrapperPtr(thisObj)->setParentView_impl_nocallback(parent);
}
// title() const
void *c_KDDockWidgets__Controllers__Group__title(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QString> { fromPtr(thisObj)->title() };
}
// tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__Controllers__Group__tr_char_char_int(const char *s, const char *c, int n)
{
    return new Dartagnan::ValueWrapper<QString> { KDDockWidgetsBindings_wrappersNS::Group_wrapper::tr(s, c, n) };
}
// unoverlay()
void c_KDDockWidgets__Controllers__Group__unoverlay(void *thisObj)
{
    fromPtr(thisObj)->unoverlay();
}
// updateFloatingActions()
void c_KDDockWidgets__Controllers__Group__updateFloatingActions(void *thisObj)
{
    fromPtr(thisObj)->updateFloatingActions();
}
// updateTitleAndIcon()
void c_KDDockWidgets__Controllers__Group__updateTitleAndIcon(void *thisObj)
{
    fromPtr(thisObj)->updateTitleAndIcon();
}
// updateTitleBarVisibility()
void c_KDDockWidgets__Controllers__Group__updateTitleBarVisibility(void *thisObj)
{
    fromPtr(thisObj)->updateTitleBarVisibility();
}
// userType() const
int c_KDDockWidgets__Controllers__Group__userType(void *thisObj)
{
    return fromPtr(thisObj)->userType();
}
void c_KDDockWidgets__Controllers__Group__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__Controllers__Group__registerVirtualMethodCallback(void *ptr, void *callback, int methodId)
{
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 295:
        wrapper->m_customEventCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Group_wrapper::Callback_customEvent>(callback);
        break;
    case 1054:
        wrapper->m_dragRectCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Group_wrapper::Callback_dragRect>(callback);
        break;
    case 306:
        wrapper->m_eventCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Group_wrapper::Callback_event>(callback);
        break;
    case 307:
        wrapper->m_eventFilterCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Group_wrapper::Callback_eventFilter>(callback);
        break;
    case 1056:
        wrapper->m_focusedWidgetChangedCallbackCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Group_wrapper::Callback_focusedWidgetChangedCallback>(callback);
        break;
    case 1070:
        wrapper->m_isFocusedChangedCallbackCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Group_wrapper::Callback_isFocusedChangedCallback>(callback);
        break;
    case 814:
        wrapper->m_setParentView_implCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Group_wrapper::Callback_setParentView_impl>(callback);
        break;
    }
}
}

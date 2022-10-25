/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "TabBar_wrapper.h"


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
TabBar_wrapper::TabBar_wrapper(KDDockWidgets::Controllers::Stack *tabWidget)
    : ::KDDockWidgets::Controllers::TabBar(tabWidget)
{
}
void TabBar_wrapper::countChanged()
{
    ::KDDockWidgets::Controllers::TabBar::countChanged();
}
KDDockWidgets::Controllers::DockWidget *TabBar_wrapper::currentDockWidget() const
{
    return ::KDDockWidgets::Controllers::TabBar::currentDockWidget();
}
void TabBar_wrapper::currentDockWidgetChanged(KDDockWidgets::Controllers::DockWidget *arg__1)
{
    ::KDDockWidgets::Controllers::TabBar::currentDockWidgetChanged(arg__1);
}
int TabBar_wrapper::currentIndex() const
{
    return ::KDDockWidgets::Controllers::TabBar::currentIndex();
}
void TabBar_wrapper::customEvent(QEvent *event)
{
    if (m_customEventCallback) {
        const void *thisPtr = this;
        m_customEventCallback(const_cast<void *>(thisPtr), event);
    } else {
        ::KDDockWidgets::Controllers::TabBar::customEvent(event);
    }
}
void TabBar_wrapper::customEvent_nocallback(QEvent *event)
{
    ::KDDockWidgets::Controllers::TabBar::customEvent(event);
}
KDDockWidgets::Controllers::DockWidget *TabBar_wrapper::dockWidgetAt(QPoint localPos) const
{
    return ::KDDockWidgets::Controllers::TabBar::dockWidgetAt(localPos);
}
KDDockWidgets::Controllers::DockWidget *TabBar_wrapper::dockWidgetAt(int index) const
{
    return ::KDDockWidgets::Controllers::TabBar::dockWidgetAt(index);
}
bool TabBar_wrapper::dragCanStart(QPoint pressPos, QPoint pos) const
{
    if (m_dragCanStartCallback) {
        const void *thisPtr = this;
        return m_dragCanStartCallback(const_cast<void *>(thisPtr), &pressPos, &pos);
    } else {
        return ::KDDockWidgets::Controllers::TabBar::dragCanStart(pressPos, pos);
    }
}
bool TabBar_wrapper::dragCanStart_nocallback(QPoint pressPos, QPoint pos) const
{
    return ::KDDockWidgets::Controllers::TabBar::dragCanStart(pressPos, pos);
}
bool TabBar_wrapper::event(QEvent *event)
{
    if (m_eventCallback) {
        const void *thisPtr = this;
        return m_eventCallback(const_cast<void *>(thisPtr), event);
    } else {
        return ::KDDockWidgets::Controllers::TabBar::event(event);
    }
}
bool TabBar_wrapper::event_nocallback(QEvent *event)
{
    return ::KDDockWidgets::Controllers::TabBar::event(event);
}
bool TabBar_wrapper::eventFilter(QObject *watched, QEvent *event)
{
    if (m_eventFilterCallback) {
        const void *thisPtr = this;
        return m_eventFilterCallback(const_cast<void *>(thisPtr), watched, event);
    } else {
        return ::KDDockWidgets::Controllers::TabBar::eventFilter(watched, event);
    }
}
bool TabBar_wrapper::eventFilter_nocallback(QObject *watched, QEvent *event)
{
    return ::KDDockWidgets::Controllers::TabBar::eventFilter(watched, event);
}
KDDockWidgets::Controllers::Group *TabBar_wrapper::group() const
{
    return ::KDDockWidgets::Controllers::TabBar::group();
}
bool TabBar_wrapper::hasSingleDockWidget() const
{
    return ::KDDockWidgets::Controllers::TabBar::hasSingleDockWidget();
}
int TabBar_wrapper::indexOfDockWidget(const KDDockWidgets::Controllers::DockWidget *dw) const
{
    return ::KDDockWidgets::Controllers::TabBar::indexOfDockWidget(dw);
}
bool TabBar_wrapper::isMDI() const
{
    if (m_isMDICallback) {
        const void *thisPtr = this;
        return m_isMDICallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Controllers::TabBar::isMDI();
    }
}
bool TabBar_wrapper::isMDI_nocallback() const
{
    return ::KDDockWidgets::Controllers::TabBar::isMDI();
}
bool TabBar_wrapper::isWindow() const
{
    if (m_isWindowCallback) {
        const void *thisPtr = this;
        return m_isWindowCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Controllers::TabBar::isWindow();
    }
}
bool TabBar_wrapper::isWindow_nocallback() const
{
    return ::KDDockWidgets::Controllers::TabBar::isWindow();
}
void TabBar_wrapper::moveTabTo(int from, int to)
{
    ::KDDockWidgets::Controllers::TabBar::moveTabTo(from, to);
}
int TabBar_wrapper::numDockWidgets() const
{
    return ::KDDockWidgets::Controllers::TabBar::numDockWidgets();
}
void TabBar_wrapper::onMouseDoubleClick(QPoint localPos)
{
    ::KDDockWidgets::Controllers::TabBar::onMouseDoubleClick(localPos);
}
void TabBar_wrapper::onMousePress(QPoint localPos)
{
    ::KDDockWidgets::Controllers::TabBar::onMousePress(localPos);
}
QRect TabBar_wrapper::rectForTab(int index) const
{
    return ::KDDockWidgets::Controllers::TabBar::rectForTab(index);
}
void TabBar_wrapper::removeDockWidget(KDDockWidgets::Controllers::DockWidget *dw)
{
    ::KDDockWidgets::Controllers::TabBar::removeDockWidget(dw);
}
void TabBar_wrapper::renameTab(int index, const QString &arg__2)
{
    ::KDDockWidgets::Controllers::TabBar::renameTab(index, arg__2);
}
void TabBar_wrapper::setCurrentDockWidget(KDDockWidgets::Controllers::DockWidget *dw)
{
    ::KDDockWidgets::Controllers::TabBar::setCurrentDockWidget(dw);
}
void TabBar_wrapper::setCurrentIndex(int index)
{
    ::KDDockWidgets::Controllers::TabBar::setCurrentIndex(index);
}
void TabBar_wrapper::setParentView_impl(KDDockWidgets::View *parent)
{
    if (m_setParentView_implCallback) {
        const void *thisPtr = this;
        m_setParentView_implCallback(const_cast<void *>(thisPtr), parent);
    } else {
        ::KDDockWidgets::Controllers::TabBar::setParentView_impl(parent);
    }
}
void TabBar_wrapper::setParentView_impl_nocallback(KDDockWidgets::View *parent)
{
    ::KDDockWidgets::Controllers::TabBar::setParentView_impl(parent);
}
KDDockWidgets::Controllers::DockWidget *TabBar_wrapper::singleDockWidget() const
{
    if (m_singleDockWidgetCallback) {
        const void *thisPtr = this;
        return m_singleDockWidgetCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Controllers::TabBar::singleDockWidget();
    }
}
KDDockWidgets::Controllers::DockWidget *TabBar_wrapper::singleDockWidget_nocallback() const
{
    return ::KDDockWidgets::Controllers::TabBar::singleDockWidget();
}
KDDockWidgets::Controllers::Stack *TabBar_wrapper::stack() const
{
    return ::KDDockWidgets::Controllers::TabBar::stack();
}
bool TabBar_wrapper::tabsAreMovable() const
{
    return ::KDDockWidgets::Controllers::TabBar::tabsAreMovable();
}
QString TabBar_wrapper::text(int index) const
{
    return ::KDDockWidgets::Controllers::TabBar::text(index);
}
QString TabBar_wrapper::tr(const char *s, const char *c, int n)
{
    return ::KDDockWidgets::Controllers::TabBar::tr(s, c, n);
}
TabBar_wrapper::~TabBar_wrapper()
{
}

}
static KDDockWidgets::Controllers::TabBar *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::Controllers::TabBar *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::TabBar_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::TabBar_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__Controllers__TabBar_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::TabBar_wrapper *>(cppObj);
}
void *c_KDDockWidgets__Controllers__TabBar__constructor_Stack(void *tabWidget_)
{
    auto tabWidget = reinterpret_cast<KDDockWidgets::Controllers::Stack *>(tabWidget_);
    auto ptr = new KDDockWidgetsBindings_wrappersNS::TabBar_wrapper(tabWidget);
    return reinterpret_cast<void *>(ptr);
}
// countChanged()
void c_KDDockWidgets__Controllers__TabBar__countChanged(void *thisObj)
{
    fromPtr(thisObj)->countChanged();
}
// currentDockWidget() const
void *c_KDDockWidgets__Controllers__TabBar__currentDockWidget(void *thisObj)
{
    return fromPtr(thisObj)->currentDockWidget();
}
// currentDockWidgetChanged(KDDockWidgets::Controllers::DockWidget * arg__1)
void c_KDDockWidgets__Controllers__TabBar__currentDockWidgetChanged_DockWidget(void *thisObj,
                                                                               void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::DockWidget *>(arg__1_);
    fromPtr(thisObj)->currentDockWidgetChanged(arg__1);
}
// currentIndex() const
int c_KDDockWidgets__Controllers__TabBar__currentIndex(void *thisObj)
{
    return fromPtr(thisObj)->currentIndex();
}
// customEvent(QEvent * event)
void c_KDDockWidgets__Controllers__TabBar__customEvent_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    fromWrapperPtr(thisObj)->customEvent_nocallback(event);
}
// dockWidgetAt(QPoint localPos) const
void *c_KDDockWidgets__Controllers__TabBar__dockWidgetAt_QPoint(void *thisObj, void *localPos_)
{
    assert(localPos_);
    auto &localPos = *reinterpret_cast<QPoint *>(localPos_);
    return fromPtr(thisObj)->dockWidgetAt(localPos);
}
// dockWidgetAt(int index) const
void *c_KDDockWidgets__Controllers__TabBar__dockWidgetAt_int(void *thisObj, int index)
{
    return fromPtr(thisObj)->dockWidgetAt(index);
}
// dragCanStart(QPoint pressPos, QPoint pos) const
bool c_KDDockWidgets__Controllers__TabBar__dragCanStart_QPoint_QPoint(void *thisObj,
                                                                      void *pressPos_, void *pos_)
{
    assert(pressPos_);
    auto &pressPos = *reinterpret_cast<QPoint *>(pressPos_);
    assert(pos_);
    auto &pos = *reinterpret_cast<QPoint *>(pos_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TabBar_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->dragCanStart_nocallback(pressPos, pos);
        } else {
            return targetPtr->dragCanStart(pressPos, pos);
        }
    }();
}
// event(QEvent * event)
bool c_KDDockWidgets__Controllers__TabBar__event_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TabBar_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->event_nocallback(event);
        } else {
            return targetPtr->event(event);
        }
    }();
}
// eventFilter(QObject * watched, QEvent * event)
bool c_KDDockWidgets__Controllers__TabBar__eventFilter_QObject_QEvent(void *thisObj, void *watched_,
                                                                      void *event_)
{
    auto watched = reinterpret_cast<QObject *>(watched_);
    auto event = reinterpret_cast<QEvent *>(event_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TabBar_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->eventFilter_nocallback(watched, event);
        } else {
            return targetPtr->eventFilter(watched, event);
        }
    }();
}
// group() const
void *c_KDDockWidgets__Controllers__TabBar__group(void *thisObj)
{
    return fromPtr(thisObj)->group();
}
// hasSingleDockWidget() const
bool c_KDDockWidgets__Controllers__TabBar__hasSingleDockWidget(void *thisObj)
{
    return fromPtr(thisObj)->hasSingleDockWidget();
}
// indexOfDockWidget(const KDDockWidgets::Controllers::DockWidget * dw) const
int c_KDDockWidgets__Controllers__TabBar__indexOfDockWidget_DockWidget(void *thisObj, void *dw_)
{
    auto dw = reinterpret_cast<KDDockWidgets::Controllers::DockWidget *>(dw_);
    return fromPtr(thisObj)->indexOfDockWidget(dw);
}
// isMDI() const
bool c_KDDockWidgets__Controllers__TabBar__isMDI(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TabBar_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->isMDI_nocallback();
        } else {
            return targetPtr->isMDI();
        }
    }();
}
// isWindow() const
bool c_KDDockWidgets__Controllers__TabBar__isWindow(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TabBar_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->isWindow_nocallback();
        } else {
            return targetPtr->isWindow();
        }
    }();
}
// moveTabTo(int from, int to)
void c_KDDockWidgets__Controllers__TabBar__moveTabTo_int_int(void *thisObj, int from, int to)
{
    fromPtr(thisObj)->moveTabTo(from, to);
}
// numDockWidgets() const
int c_KDDockWidgets__Controllers__TabBar__numDockWidgets(void *thisObj)
{
    return fromPtr(thisObj)->numDockWidgets();
}
// onMouseDoubleClick(QPoint localPos)
void c_KDDockWidgets__Controllers__TabBar__onMouseDoubleClick_QPoint(void *thisObj, void *localPos_)
{
    assert(localPos_);
    auto &localPos = *reinterpret_cast<QPoint *>(localPos_);
    fromPtr(thisObj)->onMouseDoubleClick(localPos);
}
// onMousePress(QPoint localPos)
void c_KDDockWidgets__Controllers__TabBar__onMousePress_QPoint(void *thisObj, void *localPos_)
{
    assert(localPos_);
    auto &localPos = *reinterpret_cast<QPoint *>(localPos_);
    fromPtr(thisObj)->onMousePress(localPos);
}
// rectForTab(int index) const
void *c_KDDockWidgets__Controllers__TabBar__rectForTab_int(void *thisObj, int index)
{
    return new Dartagnan::ValueWrapper<QRect> { fromPtr(thisObj)->rectForTab(index) };
}
// removeDockWidget(KDDockWidgets::Controllers::DockWidget * dw)
void c_KDDockWidgets__Controllers__TabBar__removeDockWidget_DockWidget(void *thisObj, void *dw_)
{
    auto dw = reinterpret_cast<KDDockWidgets::Controllers::DockWidget *>(dw_);
    fromPtr(thisObj)->removeDockWidget(dw);
}
// renameTab(int index, const QString & arg__2)
void c_KDDockWidgets__Controllers__TabBar__renameTab_int_QString(void *thisObj, int index,
                                                                 const char *arg__2_)
{
    const auto arg__2 = QString::fromUtf8(arg__2_);
    fromPtr(thisObj)->renameTab(index, arg__2);
}
// setCurrentDockWidget(KDDockWidgets::Controllers::DockWidget * dw)
void c_KDDockWidgets__Controllers__TabBar__setCurrentDockWidget_DockWidget(void *thisObj, void *dw_)
{
    auto dw = reinterpret_cast<KDDockWidgets::Controllers::DockWidget *>(dw_);
    fromPtr(thisObj)->setCurrentDockWidget(dw);
}
// setCurrentIndex(int index)
void c_KDDockWidgets__Controllers__TabBar__setCurrentIndex_int(void *thisObj, int index)
{
    fromPtr(thisObj)->setCurrentIndex(index);
}
// setParentView_impl(KDDockWidgets::View * parent)
void c_KDDockWidgets__Controllers__TabBar__setParentView_impl_View(void *thisObj, void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    fromWrapperPtr(thisObj)->setParentView_impl_nocallback(parent);
}
// singleDockWidget() const
void *c_KDDockWidgets__Controllers__TabBar__singleDockWidget(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TabBar_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->singleDockWidget_nocallback();
        } else {
            return targetPtr->singleDockWidget();
        }
    }();
}
// stack() const
void *c_KDDockWidgets__Controllers__TabBar__stack(void *thisObj)
{
    return fromPtr(thisObj)->stack();
}
// tabsAreMovable() const
bool c_KDDockWidgets__Controllers__TabBar__tabsAreMovable(void *thisObj)
{
    return fromPtr(thisObj)->tabsAreMovable();
}
// text(int index) const
void *c_KDDockWidgets__Controllers__TabBar__text_int(void *thisObj, int index)
{
    return new Dartagnan::ValueWrapper<QString> { fromPtr(thisObj)->text(index) };
}
// tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__Controllers__TabBar__tr_char_char_int(const char *s, const char *c,
                                                                    int n)
{
    return new Dartagnan::ValueWrapper<QString> {
        KDDockWidgetsBindings_wrappersNS::TabBar_wrapper::tr(s, c, n)
    };
}
void c_KDDockWidgets__Controllers__TabBar__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__Controllers__TabBar__registerVirtualMethodCallback(void *ptr, void *callback,
                                                                         int methodId)
{
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 295:
        wrapper->m_customEventCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TabBar_wrapper::Callback_customEvent>(callback);
        break;
    case 1151:
        wrapper->m_dragCanStartCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TabBar_wrapper::Callback_dragCanStart>(callback);
        break;
    case 306:
        wrapper->m_eventCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::TabBar_wrapper::Callback_event>(
                callback);
        break;
    case 307:
        wrapper->m_eventFilterCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TabBar_wrapper::Callback_eventFilter>(callback);
        break;
    case 1159:
        wrapper->m_isMDICallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::TabBar_wrapper::Callback_isMDI>(
                callback);
        break;
    case 1161:
        wrapper->m_isWindowCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::TabBar_wrapper::Callback_isWindow>(
                callback);
        break;
    case 891:
        wrapper->m_setParentView_implCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TabBar_wrapper::Callback_setParentView_impl>(
            callback);
        break;
    case 1178:
        wrapper->m_singleDockWidgetCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TabBar_wrapper::Callback_singleDockWidget>(callback);
        break;
    }
}
}

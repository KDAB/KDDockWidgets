/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "DockRegistry_wrapper.h"


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
void DockRegistry_wrapper::checkSanityAll(bool dumpDebug)
{
    ::KDDockWidgets::DockRegistry::checkSanityAll(dumpDebug);
}
void DockRegistry_wrapper::clear()
{
    ::KDDockWidgets::DockRegistry::clear();
}
bool DockRegistry_wrapper::containsDockWidget(const QString &uniqueName) const
{
    return ::KDDockWidgets::DockRegistry::containsDockWidget(uniqueName);
}
bool DockRegistry_wrapper::containsMainWindow(const QString &uniqueName) const
{
    return ::KDDockWidgets::DockRegistry::containsMainWindow(uniqueName);
}
void DockRegistry_wrapper::customEvent(QEvent *event)
{
    if (m_customEventCallback) {
        const void *thisPtr = this;
        m_customEventCallback(const_cast<void *>(thisPtr), event);
    } else {
        ::KDDockWidgets::DockRegistry::customEvent(event);
    }
}
void DockRegistry_wrapper::customEvent_nocallback(QEvent *event)
{
    ::KDDockWidgets::DockRegistry::customEvent(event);
}
KDDockWidgets::Controllers::DockWidget *
DockRegistry_wrapper::dockByName(const QString &arg__1) const
{
    return ::KDDockWidgets::DockRegistry::dockByName(arg__1);
}
void DockRegistry_wrapper::dropIndicatorsInhibitedChanged(bool inhibited)
{
    ::KDDockWidgets::DockRegistry::dropIndicatorsInhibitedChanged(inhibited);
}
void DockRegistry_wrapper::ensureAllFloatingWidgetsAreMorphed()
{
    ::KDDockWidgets::DockRegistry::ensureAllFloatingWidgetsAreMorphed();
}
bool DockRegistry_wrapper::event(QEvent *event)
{
    if (m_eventCallback) {
        const void *thisPtr = this;
        return m_eventCallback(const_cast<void *>(thisPtr), event);
    } else {
        return ::KDDockWidgets::DockRegistry::event(event);
    }
}
bool DockRegistry_wrapper::event_nocallback(QEvent *event)
{
    return ::KDDockWidgets::DockRegistry::event(event);
}
bool DockRegistry_wrapper::eventFilter(QObject *watched, QEvent *event)
{
    if (m_eventFilterCallback) {
        const void *thisPtr = this;
        return m_eventFilterCallback(const_cast<void *>(thisPtr), watched, event);
    } else {
        return ::KDDockWidgets::DockRegistry::eventFilter(watched, event);
    }
}
bool DockRegistry_wrapper::eventFilter_nocallback(QObject *watched, QEvent *event)
{
    return ::KDDockWidgets::DockRegistry::eventFilter(watched, event);
}
KDDockWidgets::Controllers::DockWidget *DockRegistry_wrapper::focusedDockWidget() const
{
    return ::KDDockWidgets::DockRegistry::focusedDockWidget();
}
KDDockWidgets::Controllers::Group *DockRegistry_wrapper::groupInMDIResize() const
{
    return ::KDDockWidgets::DockRegistry::groupInMDIResize();
}
void DockRegistry_wrapper::groupInMDIResizeChanged()
{
    ::KDDockWidgets::DockRegistry::groupInMDIResizeChanged();
}
const QList<KDDockWidgets::Controllers::Group *> DockRegistry_wrapper::groups() const
{
    return ::KDDockWidgets::DockRegistry::groups();
}
bool DockRegistry_wrapper::hasFloatingWindows() const
{
    return ::KDDockWidgets::DockRegistry::hasFloatingWindows();
}
bool DockRegistry_wrapper::isEmpty(bool excludeBeingDeleted) const
{
    return ::KDDockWidgets::DockRegistry::isEmpty(excludeBeingDeleted);
}
bool DockRegistry_wrapper::isSane() const
{
    return ::KDDockWidgets::DockRegistry::isSane();
}
bool DockRegistry_wrapper::itemIsInMainWindow(const Layouting::Item *arg__1) const
{
    return ::KDDockWidgets::DockRegistry::itemIsInMainWindow(arg__1);
}
KDDockWidgets::Controllers::Layout *
DockRegistry_wrapper::layoutForItem(const Layouting::Item *arg__1) const
{
    return ::KDDockWidgets::DockRegistry::layoutForItem(arg__1);
}
KDDockWidgets::Controllers::MainWindow *
DockRegistry_wrapper::mainWindowByName(const QString &arg__1) const
{
    return ::KDDockWidgets::DockRegistry::mainWindowByName(arg__1);
}
void DockRegistry_wrapper::registerDockWidget(KDDockWidgets::Controllers::DockWidget *arg__1)
{
    ::KDDockWidgets::DockRegistry::registerDockWidget(arg__1);
}
void DockRegistry_wrapper::registerFloatingWindow(
    KDDockWidgets::Controllers::FloatingWindow *arg__1)
{
    ::KDDockWidgets::DockRegistry::registerFloatingWindow(arg__1);
}
void DockRegistry_wrapper::registerGroup(KDDockWidgets::Controllers::Group *arg__1)
{
    ::KDDockWidgets::DockRegistry::registerGroup(arg__1);
}
void DockRegistry_wrapper::registerLayout(KDDockWidgets::Controllers::Layout *arg__1)
{
    ::KDDockWidgets::DockRegistry::registerLayout(arg__1);
}
void DockRegistry_wrapper::registerMainWindow(KDDockWidgets::Controllers::MainWindow *arg__1)
{
    ::KDDockWidgets::DockRegistry::registerMainWindow(arg__1);
}
KDDockWidgets::DockRegistry *DockRegistry_wrapper::self()
{
    return ::KDDockWidgets::DockRegistry::self();
}
KDDockWidgets::Controllers::SideBar *DockRegistry_wrapper::sideBarForDockWidget(
    const KDDockWidgets::Controllers::DockWidget *arg__1) const
{
    return ::KDDockWidgets::DockRegistry::sideBarForDockWidget(arg__1);
}
QString DockRegistry_wrapper::tr(const char *s, const char *c, int n)
{
    return ::KDDockWidgets::DockRegistry::tr(s, c, n);
}
void DockRegistry_wrapper::unregisterDockWidget(KDDockWidgets::Controllers::DockWidget *arg__1)
{
    ::KDDockWidgets::DockRegistry::unregisterDockWidget(arg__1);
}
void DockRegistry_wrapper::unregisterFloatingWindow(
    KDDockWidgets::Controllers::FloatingWindow *arg__1)
{
    ::KDDockWidgets::DockRegistry::unregisterFloatingWindow(arg__1);
}
void DockRegistry_wrapper::unregisterGroup(KDDockWidgets::Controllers::Group *arg__1)
{
    ::KDDockWidgets::DockRegistry::unregisterGroup(arg__1);
}
void DockRegistry_wrapper::unregisterLayout(KDDockWidgets::Controllers::Layout *arg__1)
{
    ::KDDockWidgets::DockRegistry::unregisterLayout(arg__1);
}
void DockRegistry_wrapper::unregisterMainWindow(KDDockWidgets::Controllers::MainWindow *arg__1)
{
    ::KDDockWidgets::DockRegistry::unregisterMainWindow(arg__1);
}
DockRegistry_wrapper::~DockRegistry_wrapper()
{
}

}
static KDDockWidgets::DockRegistry *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::DockRegistry *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::DockRegistry_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::DockRegistry_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__DockRegistry_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::DockRegistry_wrapper *>(cppObj);
} // checkSanityAll(bool dumpDebug)
void c_KDDockWidgets__DockRegistry__checkSanityAll_bool(void *thisObj, bool dumpDebug)
{
    fromPtr(thisObj)->checkSanityAll(dumpDebug);
}
// clear()
void c_KDDockWidgets__DockRegistry__clear(void *thisObj)
{
    fromPtr(thisObj)->clear();
}
// containsDockWidget(const QString & uniqueName) const
bool c_KDDockWidgets__DockRegistry__containsDockWidget_QString(void *thisObj,
                                                               const char *uniqueName_)
{
    const auto uniqueName = QString::fromUtf8(uniqueName_);
    return fromPtr(thisObj)->containsDockWidget(uniqueName);
}
// containsMainWindow(const QString & uniqueName) const
bool c_KDDockWidgets__DockRegistry__containsMainWindow_QString(void *thisObj,
                                                               const char *uniqueName_)
{
    const auto uniqueName = QString::fromUtf8(uniqueName_);
    return fromPtr(thisObj)->containsMainWindow(uniqueName);
}
// customEvent(QEvent * event)
void c_KDDockWidgets__DockRegistry__customEvent_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    fromWrapperPtr(thisObj)->customEvent_nocallback(event);
}
// dockByName(const QString & arg__1) const
void *c_KDDockWidgets__DockRegistry__dockByName_QString(void *thisObj, const char *arg__1_)
{
    const auto arg__1 = QString::fromUtf8(arg__1_);
    return fromPtr(thisObj)->dockByName(arg__1);
}
// dropIndicatorsInhibitedChanged(bool inhibited)
void c_KDDockWidgets__DockRegistry__dropIndicatorsInhibitedChanged_bool(void *thisObj,
                                                                        bool inhibited)
{
    fromPtr(thisObj)->dropIndicatorsInhibitedChanged(inhibited);
}
// ensureAllFloatingWidgetsAreMorphed()
void c_KDDockWidgets__DockRegistry__ensureAllFloatingWidgetsAreMorphed(void *thisObj)
{
    fromPtr(thisObj)->ensureAllFloatingWidgetsAreMorphed();
}
// event(QEvent * event)
bool c_KDDockWidgets__DockRegistry__event_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::DockRegistry_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->event_nocallback(event);
        } else {
            return targetPtr->event(event);
        }
    }();
}
// eventFilter(QObject * watched, QEvent * event)
bool c_KDDockWidgets__DockRegistry__eventFilter_QObject_QEvent(void *thisObj, void *watched_,
                                                               void *event_)
{
    auto watched = reinterpret_cast<QObject *>(watched_);
    auto event = reinterpret_cast<QEvent *>(event_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::DockRegistry_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->eventFilter_nocallback(watched, event);
        } else {
            return targetPtr->eventFilter(watched, event);
        }
    }();
}
// focusedDockWidget() const
void *c_KDDockWidgets__DockRegistry__focusedDockWidget(void *thisObj)
{
    return fromPtr(thisObj)->focusedDockWidget();
}
// groupInMDIResize() const
void *c_KDDockWidgets__DockRegistry__groupInMDIResize(void *thisObj)
{
    return fromPtr(thisObj)->groupInMDIResize();
}
// groupInMDIResizeChanged()
void c_KDDockWidgets__DockRegistry__groupInMDIResizeChanged(void *thisObj)
{
    fromPtr(thisObj)->groupInMDIResizeChanged();
}
// groups() const
void *c_KDDockWidgets__DockRegistry__groups(void *thisObj)
{
    return new Dartagnan::ValueWrapper<const QList<KDDockWidgets::Controllers::Group *>> {
        fromPtr(thisObj)->groups()
    };
}
// hasFloatingWindows() const
bool c_KDDockWidgets__DockRegistry__hasFloatingWindows(void *thisObj)
{
    return fromPtr(thisObj)->hasFloatingWindows();
}
// isEmpty(bool excludeBeingDeleted) const
bool c_KDDockWidgets__DockRegistry__isEmpty_bool(void *thisObj, bool excludeBeingDeleted)
{
    return fromPtr(thisObj)->isEmpty(excludeBeingDeleted);
}
// isSane() const
bool c_KDDockWidgets__DockRegistry__isSane(void *thisObj)
{
    return fromPtr(thisObj)->isSane();
}
// itemIsInMainWindow(const Layouting::Item * arg__1) const
bool c_KDDockWidgets__DockRegistry__itemIsInMainWindow_Item(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<Layouting::Item *>(arg__1_);
    return fromPtr(thisObj)->itemIsInMainWindow(arg__1);
}
// layoutForItem(const Layouting::Item * arg__1) const
void *c_KDDockWidgets__DockRegistry__layoutForItem_Item(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<Layouting::Item *>(arg__1_);
    return fromPtr(thisObj)->layoutForItem(arg__1);
}
// mainWindowByName(const QString & arg__1) const
void *c_KDDockWidgets__DockRegistry__mainWindowByName_QString(void *thisObj, const char *arg__1_)
{
    const auto arg__1 = QString::fromUtf8(arg__1_);
    return fromPtr(thisObj)->mainWindowByName(arg__1);
}
// registerDockWidget(KDDockWidgets::Controllers::DockWidget * arg__1)
void c_KDDockWidgets__DockRegistry__registerDockWidget_DockWidget(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::DockWidget *>(arg__1_);
    fromPtr(thisObj)->registerDockWidget(arg__1);
}
// registerFloatingWindow(KDDockWidgets::Controllers::FloatingWindow * arg__1)
void c_KDDockWidgets__DockRegistry__registerFloatingWindow_FloatingWindow(void *thisObj,
                                                                          void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::FloatingWindow *>(arg__1_);
    fromPtr(thisObj)->registerFloatingWindow(arg__1);
}
// registerGroup(KDDockWidgets::Controllers::Group * arg__1)
void c_KDDockWidgets__DockRegistry__registerGroup_Group(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::Group *>(arg__1_);
    fromPtr(thisObj)->registerGroup(arg__1);
}
// registerLayout(KDDockWidgets::Controllers::Layout * arg__1)
void c_KDDockWidgets__DockRegistry__registerLayout_Layout(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::Layout *>(arg__1_);
    fromPtr(thisObj)->registerLayout(arg__1);
}
// registerMainWindow(KDDockWidgets::Controllers::MainWindow * arg__1)
void c_KDDockWidgets__DockRegistry__registerMainWindow_MainWindow(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::MainWindow *>(arg__1_);
    fromPtr(thisObj)->registerMainWindow(arg__1);
}
// self()
void *c_static_KDDockWidgets__DockRegistry__self()
{
    return KDDockWidgetsBindings_wrappersNS::DockRegistry_wrapper::self();
}
// sideBarForDockWidget(const KDDockWidgets::Controllers::DockWidget * arg__1) const
void *c_KDDockWidgets__DockRegistry__sideBarForDockWidget_DockWidget(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::DockWidget *>(arg__1_);
    return fromPtr(thisObj)->sideBarForDockWidget(arg__1);
}
// tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__DockRegistry__tr_char_char_int(const char *s, const char *c, int n)
{
    return new Dartagnan::ValueWrapper<QString> {
        KDDockWidgetsBindings_wrappersNS::DockRegistry_wrapper::tr(s, c, n)
    };
}
// unregisterDockWidget(KDDockWidgets::Controllers::DockWidget * arg__1)
void c_KDDockWidgets__DockRegistry__unregisterDockWidget_DockWidget(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::DockWidget *>(arg__1_);
    fromPtr(thisObj)->unregisterDockWidget(arg__1);
}
// unregisterFloatingWindow(KDDockWidgets::Controllers::FloatingWindow * arg__1)
void c_KDDockWidgets__DockRegistry__unregisterFloatingWindow_FloatingWindow(void *thisObj,
                                                                            void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::FloatingWindow *>(arg__1_);
    fromPtr(thisObj)->unregisterFloatingWindow(arg__1);
}
// unregisterGroup(KDDockWidgets::Controllers::Group * arg__1)
void c_KDDockWidgets__DockRegistry__unregisterGroup_Group(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::Group *>(arg__1_);
    fromPtr(thisObj)->unregisterGroup(arg__1);
}
// unregisterLayout(KDDockWidgets::Controllers::Layout * arg__1)
void c_KDDockWidgets__DockRegistry__unregisterLayout_Layout(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::Layout *>(arg__1_);
    fromPtr(thisObj)->unregisterLayout(arg__1);
}
// unregisterMainWindow(KDDockWidgets::Controllers::MainWindow * arg__1)
void c_KDDockWidgets__DockRegistry__unregisterMainWindow_MainWindow(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::MainWindow *>(arg__1_);
    fromPtr(thisObj)->unregisterMainWindow(arg__1);
}
void c_KDDockWidgets__DockRegistry__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__DockRegistry__registerVirtualMethodCallback(void *ptr, void *callback,
                                                                  int methodId)
{
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 295:
        wrapper->m_customEventCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::DockRegistry_wrapper::Callback_customEvent>(callback);
        break;
    case 306:
        wrapper->m_eventCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::DockRegistry_wrapper::Callback_event>(callback);
        break;
    case 307:
        wrapper->m_eventFilterCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::DockRegistry_wrapper::Callback_eventFilter>(callback);
        break;
    }
}
}

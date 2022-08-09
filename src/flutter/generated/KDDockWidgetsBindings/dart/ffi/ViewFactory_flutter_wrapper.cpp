/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "ViewFactory_flutter_wrapper.h"


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
ViewFactory_flutter_wrapper::ViewFactory_flutter_wrapper()
    : ::KDDockWidgets::ViewFactory_flutter()
{
}
KDDockWidgets::Views::ClassicIndicatorWindowViewInterface *
ViewFactory_flutter_wrapper::createClassicIndicatorWindow(
    KDDockWidgets::Controllers::ClassicIndicators *arg__1) const
{
    if (m_createClassicIndicatorWindowCallback) {
        const void *thisPtr = this;
        return m_createClassicIndicatorWindowCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        return ::KDDockWidgets::ViewFactory_flutter::createClassicIndicatorWindow(arg__1);
    }
}
KDDockWidgets::Views::ClassicIndicatorWindowViewInterface *
ViewFactory_flutter_wrapper::createClassicIndicatorWindow_nocallback(
    KDDockWidgets::Controllers::ClassicIndicators *arg__1) const
{
    return ::KDDockWidgets::ViewFactory_flutter::createClassicIndicatorWindow(arg__1);
}
KDDockWidgets::View *ViewFactory_flutter_wrapper::createDockWidget(
    const QString &uniqueName, QFlags<KDDockWidgets::DockWidgetOption> arg__2,
    QFlags<KDDockWidgets::LayoutSaverOption> arg__3, Qt::WindowFlags arg__4) const
{
    if (m_createDockWidgetCallback) {
        const void *thisPtr = this;
        return m_createDockWidgetCallback(const_cast<void *>(thisPtr), uniqueName, arg__2, arg__3,
                                          arg__4);
    } else {
        return ::KDDockWidgets::ViewFactory_flutter::createDockWidget(uniqueName, arg__2, arg__3,
                                                                      arg__4);
    }
}
KDDockWidgets::View *ViewFactory_flutter_wrapper::createDockWidget_nocallback(
    const QString &uniqueName, QFlags<KDDockWidgets::DockWidgetOption> arg__2,
    QFlags<KDDockWidgets::LayoutSaverOption> arg__3, Qt::WindowFlags arg__4) const
{
    return ::KDDockWidgets::ViewFactory_flutter::createDockWidget(uniqueName, arg__2, arg__3,
                                                                  arg__4);
}
KDDockWidgets::View *
ViewFactory_flutter_wrapper::createDropArea(KDDockWidgets::Controllers::DropArea *arg__1,
                                            KDDockWidgets::View *parent) const
{
    if (m_createDropAreaCallback) {
        const void *thisPtr = this;
        return m_createDropAreaCallback(const_cast<void *>(thisPtr), arg__1, parent);
    } else {
        return ::KDDockWidgets::ViewFactory_flutter::createDropArea(arg__1, parent);
    }
}
KDDockWidgets::View *
ViewFactory_flutter_wrapper::createDropArea_nocallback(KDDockWidgets::Controllers::DropArea *arg__1,
                                                       KDDockWidgets::View *parent) const
{
    return ::KDDockWidgets::ViewFactory_flutter::createDropArea(arg__1, parent);
}
KDDockWidgets::View *
ViewFactory_flutter_wrapper::createGroup(KDDockWidgets::Controllers::Group *arg__1,
                                         KDDockWidgets::View *parent) const
{
    if (m_createGroupCallback) {
        const void *thisPtr = this;
        return m_createGroupCallback(const_cast<void *>(thisPtr), arg__1, parent);
    } else {
        return ::KDDockWidgets::ViewFactory_flutter::createGroup(arg__1, parent);
    }
}
KDDockWidgets::View *
ViewFactory_flutter_wrapper::createGroup_nocallback(KDDockWidgets::Controllers::Group *arg__1,
                                                    KDDockWidgets::View *parent) const
{
    return ::KDDockWidgets::ViewFactory_flutter::createGroup(arg__1, parent);
}
KDDockWidgets::View *
ViewFactory_flutter_wrapper::createRubberBand(KDDockWidgets::View *parent) const
{
    if (m_createRubberBandCallback) {
        const void *thisPtr = this;
        return m_createRubberBandCallback(const_cast<void *>(thisPtr), parent);
    } else {
        return ::KDDockWidgets::ViewFactory_flutter::createRubberBand(parent);
    }
}
KDDockWidgets::View *
ViewFactory_flutter_wrapper::createRubberBand_nocallback(KDDockWidgets::View *parent) const
{
    return ::KDDockWidgets::ViewFactory_flutter::createRubberBand(parent);
}
KDDockWidgets::View *
ViewFactory_flutter_wrapper::createSeparator(KDDockWidgets::Controllers::Separator *arg__1,
                                             KDDockWidgets::View *parent) const
{
    if (m_createSeparatorCallback) {
        const void *thisPtr = this;
        return m_createSeparatorCallback(const_cast<void *>(thisPtr), arg__1, parent);
    } else {
        return ::KDDockWidgets::ViewFactory_flutter::createSeparator(arg__1, parent);
    }
}
KDDockWidgets::View *ViewFactory_flutter_wrapper::createSeparator_nocallback(
    KDDockWidgets::Controllers::Separator *arg__1, KDDockWidgets::View *parent) const
{
    return ::KDDockWidgets::ViewFactory_flutter::createSeparator(arg__1, parent);
}
KDDockWidgets::View *
ViewFactory_flutter_wrapper::createStack(KDDockWidgets::Controllers::Stack *arg__1,
                                         KDDockWidgets::View *parent) const
{
    if (m_createStackCallback) {
        const void *thisPtr = this;
        return m_createStackCallback(const_cast<void *>(thisPtr), arg__1, parent);
    } else {
        return ::KDDockWidgets::ViewFactory_flutter::createStack(arg__1, parent);
    }
}
KDDockWidgets::View *
ViewFactory_flutter_wrapper::createStack_nocallback(KDDockWidgets::Controllers::Stack *arg__1,
                                                    KDDockWidgets::View *parent) const
{
    return ::KDDockWidgets::ViewFactory_flutter::createStack(arg__1, parent);
}
KDDockWidgets::View *
ViewFactory_flutter_wrapper::createTabBar(KDDockWidgets::Controllers::TabBar *tabBar,
                                          KDDockWidgets::View *parent) const
{
    if (m_createTabBarCallback) {
        const void *thisPtr = this;
        return m_createTabBarCallback(const_cast<void *>(thisPtr), tabBar, parent);
    } else {
        return ::KDDockWidgets::ViewFactory_flutter::createTabBar(tabBar, parent);
    }
}
KDDockWidgets::View *
ViewFactory_flutter_wrapper::createTabBar_nocallback(KDDockWidgets::Controllers::TabBar *tabBar,
                                                     KDDockWidgets::View *parent) const
{
    return ::KDDockWidgets::ViewFactory_flutter::createTabBar(tabBar, parent);
}
KDDockWidgets::View *
ViewFactory_flutter_wrapper::createTitleBar(KDDockWidgets::Controllers::TitleBar *arg__1,
                                            KDDockWidgets::View *parent) const
{
    if (m_createTitleBarCallback) {
        const void *thisPtr = this;
        return m_createTitleBarCallback(const_cast<void *>(thisPtr), arg__1, parent);
    } else {
        return ::KDDockWidgets::ViewFactory_flutter::createTitleBar(arg__1, parent);
    }
}
KDDockWidgets::View *
ViewFactory_flutter_wrapper::createTitleBar_nocallback(KDDockWidgets::Controllers::TitleBar *arg__1,
                                                       KDDockWidgets::View *parent) const
{
    return ::KDDockWidgets::ViewFactory_flutter::createTitleBar(arg__1, parent);
}
void ViewFactory_flutter_wrapper::customEvent(QEvent *event)
{
    if (m_customEventCallback) {
        const void *thisPtr = this;
        m_customEventCallback(const_cast<void *>(thisPtr), event);
    } else {
        ::KDDockWidgets::ViewFactory_flutter::customEvent(event);
    }
}
void ViewFactory_flutter_wrapper::customEvent_nocallback(QEvent *event)
{
    ::KDDockWidgets::ViewFactory_flutter::customEvent(event);
}
bool ViewFactory_flutter_wrapper::event(QEvent *event)
{
    if (m_eventCallback) {
        const void *thisPtr = this;
        return m_eventCallback(const_cast<void *>(thisPtr), event);
    } else {
        return ::KDDockWidgets::ViewFactory_flutter::event(event);
    }
}
bool ViewFactory_flutter_wrapper::event_nocallback(QEvent *event)
{
    return ::KDDockWidgets::ViewFactory_flutter::event(event);
}
bool ViewFactory_flutter_wrapper::eventFilter(QObject *watched, QEvent *event)
{
    if (m_eventFilterCallback) {
        const void *thisPtr = this;
        return m_eventFilterCallback(const_cast<void *>(thisPtr), watched, event);
    } else {
        return ::KDDockWidgets::ViewFactory_flutter::eventFilter(watched, event);
    }
}
bool ViewFactory_flutter_wrapper::eventFilter_nocallback(QObject *watched, QEvent *event)
{
    return ::KDDockWidgets::ViewFactory_flutter::eventFilter(watched, event);
}
QString ViewFactory_flutter_wrapper::tr(const char *s, const char *c, int n)
{
    return ::KDDockWidgets::ViewFactory_flutter::tr(s, c, n);
}
ViewFactory_flutter_wrapper::~ViewFactory_flutter_wrapper()
{
}

}
static KDDockWidgets::ViewFactory_flutter *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::ViewFactory_flutter *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__ViewFactory_flutter_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper *>(
        cppObj);
}
void *c_KDDockWidgets__ViewFactory_flutter__constructor()
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper();
    return reinterpret_cast<void *>(ptr);
}
// createClassicIndicatorWindow(KDDockWidgets::Controllers::ClassicIndicators * arg__1) const
void *
c_KDDockWidgets__ViewFactory_flutter__createClassicIndicatorWindow_ClassicIndicators(void *thisObj,
                                                                                     void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::ClassicIndicators *>(arg__1_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper *>(
                targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->createClassicIndicatorWindow_nocallback(arg__1);
        } else {
            return targetPtr->createClassicIndicatorWindow(arg__1);
        }
    }();
}
// createDockWidget(const QString & uniqueName, QFlags<KDDockWidgets::DockWidgetOption> arg__2,
// QFlags<KDDockWidgets::LayoutSaverOption> arg__3, Qt::WindowFlags arg__4) const
void *
c_KDDockWidgets__ViewFactory_flutter__createDockWidget_QString_DockWidgetOptions_LayoutSaverOptions_WindowFlags(
    void *thisObj, const char *uniqueName_, int arg__2_, int arg__3_, int arg__4)
{
    const auto uniqueName = QString::fromUtf8(uniqueName_);
    auto arg__2 = static_cast<QFlags<KDDockWidgets::DockWidgetOption>>(arg__2_);
    auto arg__3 = static_cast<QFlags<KDDockWidgets::LayoutSaverOption>>(arg__3_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper *>(
                targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->createDockWidget_nocallback(uniqueName, arg__2, arg__3,
                                                           static_cast<Qt::WindowFlags>(arg__4));
        } else {
            return targetPtr->createDockWidget(uniqueName, arg__2, arg__3,
                                               static_cast<Qt::WindowFlags>(arg__4));
        }
    }();
}
// createDropArea(KDDockWidgets::Controllers::DropArea * arg__1, KDDockWidgets::View * parent) const
void *c_KDDockWidgets__ViewFactory_flutter__createDropArea_DropArea_View(void *thisObj,
                                                                         void *arg__1_,
                                                                         void *parent_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::DropArea *>(arg__1_);
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper *>(
                targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->createDropArea_nocallback(arg__1, parent);
        } else {
            return targetPtr->createDropArea(arg__1, parent);
        }
    }();
}
// createGroup(KDDockWidgets::Controllers::Group * arg__1, KDDockWidgets::View * parent) const
void *c_KDDockWidgets__ViewFactory_flutter__createGroup_Group_View(void *thisObj, void *arg__1_,
                                                                   void *parent_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::Group *>(arg__1_);
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper *>(
                targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->createGroup_nocallback(arg__1, parent);
        } else {
            return targetPtr->createGroup(arg__1, parent);
        }
    }();
}
// createRubberBand(KDDockWidgets::View * parent) const
void *c_KDDockWidgets__ViewFactory_flutter__createRubberBand_View(void *thisObj, void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper *>(
                targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->createRubberBand_nocallback(parent);
        } else {
            return targetPtr->createRubberBand(parent);
        }
    }();
}
// createSeparator(KDDockWidgets::Controllers::Separator * arg__1, KDDockWidgets::View * parent)
// const
void *c_KDDockWidgets__ViewFactory_flutter__createSeparator_Separator_View(void *thisObj,
                                                                           void *arg__1_,
                                                                           void *parent_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::Separator *>(arg__1_);
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper *>(
                targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->createSeparator_nocallback(arg__1, parent);
        } else {
            return targetPtr->createSeparator(arg__1, parent);
        }
    }();
}
// createStack(KDDockWidgets::Controllers::Stack * arg__1, KDDockWidgets::View * parent) const
void *c_KDDockWidgets__ViewFactory_flutter__createStack_Stack_View(void *thisObj, void *arg__1_,
                                                                   void *parent_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::Stack *>(arg__1_);
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper *>(
                targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->createStack_nocallback(arg__1, parent);
        } else {
            return targetPtr->createStack(arg__1, parent);
        }
    }();
}
// createTabBar(KDDockWidgets::Controllers::TabBar * tabBar, KDDockWidgets::View * parent) const
void *c_KDDockWidgets__ViewFactory_flutter__createTabBar_TabBar_View(void *thisObj, void *tabBar_,
                                                                     void *parent_)
{
    auto tabBar = reinterpret_cast<KDDockWidgets::Controllers::TabBar *>(tabBar_);
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper *>(
                targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->createTabBar_nocallback(tabBar, parent);
        } else {
            return targetPtr->createTabBar(tabBar, parent);
        }
    }();
}
// createTitleBar(KDDockWidgets::Controllers::TitleBar * arg__1, KDDockWidgets::View * parent) const
void *c_KDDockWidgets__ViewFactory_flutter__createTitleBar_TitleBar_View(void *thisObj,
                                                                         void *arg__1_,
                                                                         void *parent_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::TitleBar *>(arg__1_);
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper *>(
                targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->createTitleBar_nocallback(arg__1, parent);
        } else {
            return targetPtr->createTitleBar(arg__1, parent);
        }
    }();
}
// customEvent(QEvent * event)
void c_KDDockWidgets__ViewFactory_flutter__customEvent_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    fromWrapperPtr(thisObj)->customEvent_nocallback(event);
}
// event(QEvent * event)
bool c_KDDockWidgets__ViewFactory_flutter__event_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper *>(
                targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->event_nocallback(event);
        } else {
            return targetPtr->event(event);
        }
    }();
}
// eventFilter(QObject * watched, QEvent * event)
bool c_KDDockWidgets__ViewFactory_flutter__eventFilter_QObject_QEvent(void *thisObj, void *watched_,
                                                                      void *event_)
{
    auto watched = reinterpret_cast<QObject *>(watched_);
    auto event = reinterpret_cast<QEvent *>(event_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper *>(
                targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->eventFilter_nocallback(watched, event);
        } else {
            return targetPtr->eventFilter(watched, event);
        }
    }();
}
// tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__ViewFactory_flutter__tr_char_char_int(const char *s, const char *c,
                                                                    int n)
{
    return new Dartagnan::ValueWrapper<QString> {
        KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper::tr(s, c, n)
    };
}
void c_KDDockWidgets__ViewFactory_flutter__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__ViewFactory_flutter__registerVirtualMethodCallback(void *ptr, void *callback,
                                                                         int methodId)
{
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 689:
        wrapper->m_createClassicIndicatorWindowCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper::
                                 Callback_createClassicIndicatorWindow>(callback);
        break;
    case 690:
        wrapper->m_createDockWidgetCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper::
                                 Callback_createDockWidget>(callback);
        break;
    case 691:
        wrapper->m_createDropAreaCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper::Callback_createDropArea>(
            callback);
        break;
    case 692:
        wrapper->m_createGroupCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper::Callback_createGroup>(
            callback);
        break;
    case 693:
        wrapper->m_createRubberBandCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper::
                                 Callback_createRubberBand>(callback);
        break;
    case 694:
        wrapper->m_createSeparatorCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper::
                                 Callback_createSeparator>(callback);
        break;
    case 695:
        wrapper->m_createStackCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper::Callback_createStack>(
            callback);
        break;
    case 696:
        wrapper->m_createTabBarCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper::Callback_createTabBar>(
            callback);
        break;
    case 697:
        wrapper->m_createTitleBarCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper::Callback_createTitleBar>(
            callback);
        break;
    case 295:
        wrapper->m_customEventCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper::Callback_customEvent>(
            callback);
        break;
    case 306:
        wrapper->m_eventCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper::Callback_event>(
            callback);
        break;
    case 307:
        wrapper->m_eventFilterCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::ViewFactory_flutter_wrapper::Callback_eventFilter>(
            callback);
        break;
    }
}
}

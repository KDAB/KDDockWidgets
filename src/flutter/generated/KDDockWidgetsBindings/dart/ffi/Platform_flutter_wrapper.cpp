/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "Platform_flutter_wrapper.h"


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
Platform_flutter_wrapper::Platform_flutter_wrapper()
    : ::KDDockWidgets::Platform_flutter()
{
}
QString Platform_flutter_wrapper::applicationName() const
{
    if (m_applicationNameCallback) {
        const void *thisPtr = this;
        return *m_applicationNameCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Platform_flutter::applicationName();
    }
}
QString Platform_flutter_wrapper::applicationName_nocallback() const
{
    return ::KDDockWidgets::Platform_flutter::applicationName();
}
KDDockWidgets::ViewFactory *Platform_flutter_wrapper::createDefaultViewFactory()
{
    if (m_createDefaultViewFactoryCallback) {
        const void *thisPtr = this;
        return m_createDefaultViewFactoryCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Platform_flutter::createDefaultViewFactory();
    }
}
KDDockWidgets::ViewFactory *Platform_flutter_wrapper::createDefaultViewFactory_nocallback()
{
    return ::KDDockWidgets::Platform_flutter::createDefaultViewFactory();
}
KDDockWidgets::Controllers::MainWindow *Platform_flutter_wrapper::createMainWindow(
    const QString &uniqueName, KDDockWidgets::CreateViewOptions arg__2,
    QFlags<KDDockWidgets::MainWindowOption> options, KDDockWidgets::View *parent,
    Qt::WindowFlags arg__5) const
{
    if (m_createMainWindowCallback) {
        const void *thisPtr = this;
        return m_createMainWindowCallback(const_cast<void *>(thisPtr), uniqueName, &arg__2, options,
                                          parent, arg__5);
    } else {
        return ::KDDockWidgets::Platform_flutter::createMainWindow(uniqueName, arg__2, options,
                                                                   parent, arg__5);
    }
}
KDDockWidgets::Controllers::MainWindow *Platform_flutter_wrapper::createMainWindow_nocallback(
    const QString &uniqueName, KDDockWidgets::CreateViewOptions arg__2,
    QFlags<KDDockWidgets::MainWindowOption> options, KDDockWidgets::View *parent,
    Qt::WindowFlags arg__5) const
{
    return ::KDDockWidgets::Platform_flutter::createMainWindow(uniqueName, arg__2, options, parent,
                                                               arg__5);
}
KDDockWidgets::View *Platform_flutter_wrapper::createView(KDDockWidgets::Controller *controller,
                                                          KDDockWidgets::View *parent) const
{
    if (m_createViewCallback) {
        const void *thisPtr = this;
        return m_createViewCallback(const_cast<void *>(thisPtr), controller, parent);
    } else {
        return ::KDDockWidgets::Platform_flutter::createView(controller, parent);
    }
}
KDDockWidgets::View *
Platform_flutter_wrapper::createView_nocallback(KDDockWidgets::Controller *controller,
                                                KDDockWidgets::View *parent) const
{
    return ::KDDockWidgets::Platform_flutter::createView(controller, parent);
}
void Platform_flutter_wrapper::dumpManagedBacktrace()
{
    if (m_dumpManagedBacktraceCallback) {
        const void *thisPtr = this;
        m_dumpManagedBacktraceCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Platform_flutter::dumpManagedBacktrace();
    }
}
void Platform_flutter_wrapper::dumpManagedBacktrace_nocallback()
{
    ::KDDockWidgets::Platform_flutter::dumpManagedBacktrace();
}
bool Platform_flutter_wrapper::hasActivePopup() const
{
    if (m_hasActivePopupCallback) {
        const void *thisPtr = this;
        return m_hasActivePopupCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Platform_flutter::hasActivePopup();
    }
}
bool Platform_flutter_wrapper::hasActivePopup_nocallback() const
{
    return ::KDDockWidgets::Platform_flutter::hasActivePopup();
}
bool Platform_flutter_wrapper::inDisallowedDragView(QPoint globalPos) const
{
    if (m_inDisallowedDragViewCallback) {
        const void *thisPtr = this;
        return m_inDisallowedDragViewCallback(const_cast<void *>(thisPtr), &globalPos);
    } else {
        return ::KDDockWidgets::Platform_flutter::inDisallowedDragView(globalPos);
    }
}
bool Platform_flutter_wrapper::inDisallowedDragView_nocallback(QPoint globalPos) const
{
    return ::KDDockWidgets::Platform_flutter::inDisallowedDragView(globalPos);
}
void Platform_flutter_wrapper::init()
{
    ::KDDockWidgets::Platform_flutter::init();
}
void Platform_flutter_wrapper::installMessageHandler()
{
    if (m_installMessageHandlerCallback) {
        const void *thisPtr = this;
        m_installMessageHandlerCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Platform_flutter::installMessageHandler();
    }
}
void Platform_flutter_wrapper::installMessageHandler_nocallback()
{
    ::KDDockWidgets::Platform_flutter::installMessageHandler();
}
bool Platform_flutter_wrapper::isLeftMouseButtonPressed() const
{
    if (m_isLeftMouseButtonPressedCallback) {
        const void *thisPtr = this;
        return m_isLeftMouseButtonPressedCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Platform_flutter::isLeftMouseButtonPressed();
    }
}
bool Platform_flutter_wrapper::isLeftMouseButtonPressed_nocallback() const
{
    return ::KDDockWidgets::Platform_flutter::isLeftMouseButtonPressed();
}
bool Platform_flutter_wrapper::isProcessingAppQuitEvent() const
{
    if (m_isProcessingAppQuitEventCallback) {
        const void *thisPtr = this;
        return m_isProcessingAppQuitEventCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Platform_flutter::isProcessingAppQuitEvent();
    }
}
bool Platform_flutter_wrapper::isProcessingAppQuitEvent_nocallback() const
{
    return ::KDDockWidgets::Platform_flutter::isProcessingAppQuitEvent();
}
const char *Platform_flutter_wrapper::name() const
{
    if (m_nameCallback) {
        const void *thisPtr = this;
        return m_nameCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Platform_flutter::name();
    }
}
const char *Platform_flutter_wrapper::name_nocallback() const
{
    return ::KDDockWidgets::Platform_flutter::name();
}
void Platform_flutter_wrapper::onFloatingWindowCreated(
    KDDockWidgets::Controllers::FloatingWindow *arg__1)
{
    if (m_onFloatingWindowCreatedCallback) {
        const void *thisPtr = this;
        m_onFloatingWindowCreatedCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        ::KDDockWidgets::Platform_flutter::onFloatingWindowCreated(arg__1);
    }
}
void Platform_flutter_wrapper::onFloatingWindowCreated_nocallback(
    KDDockWidgets::Controllers::FloatingWindow *arg__1)
{
    ::KDDockWidgets::Platform_flutter::onFloatingWindowCreated(arg__1);
}
void Platform_flutter_wrapper::onFloatingWindowDestroyed(
    KDDockWidgets::Controllers::FloatingWindow *arg__1)
{
    if (m_onFloatingWindowDestroyedCallback) {
        const void *thisPtr = this;
        m_onFloatingWindowDestroyedCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        ::KDDockWidgets::Platform_flutter::onFloatingWindowDestroyed(arg__1);
    }
}
void Platform_flutter_wrapper::onFloatingWindowDestroyed_nocallback(
    KDDockWidgets::Controllers::FloatingWindow *arg__1)
{
    ::KDDockWidgets::Platform_flutter::onFloatingWindowDestroyed(arg__1);
}
QString Platform_flutter_wrapper::organizationName() const
{
    if (m_organizationNameCallback) {
        const void *thisPtr = this;
        return *m_organizationNameCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Platform_flutter::organizationName();
    }
}
QString Platform_flutter_wrapper::organizationName_nocallback() const
{
    return ::KDDockWidgets::Platform_flutter::organizationName();
}
KDDockWidgets::Platform_flutter *Platform_flutter_wrapper::platformFlutter()
{
    return ::KDDockWidgets::Platform_flutter::platformFlutter();
}
void Platform_flutter_wrapper::restoreMouseCursor()
{
    if (m_restoreMouseCursorCallback) {
        const void *thisPtr = this;
        m_restoreMouseCursorCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Platform_flutter::restoreMouseCursor();
    }
}
void Platform_flutter_wrapper::restoreMouseCursor_nocallback()
{
    ::KDDockWidgets::Platform_flutter::restoreMouseCursor();
}
int Platform_flutter_wrapper::screenNumberFor(KDDockWidgets::View *arg__1) const
{
    if (m_screenNumberForCallback) {
        const void *thisPtr = this;
        return m_screenNumberForCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        return ::KDDockWidgets::Platform_flutter::screenNumberFor(arg__1);
    }
}
int Platform_flutter_wrapper::screenNumberFor_nocallback(KDDockWidgets::View *arg__1) const
{
    return ::KDDockWidgets::Platform_flutter::screenNumberFor(arg__1);
}
QSize Platform_flutter_wrapper::screenSizeFor(KDDockWidgets::View *arg__1) const
{
    if (m_screenSizeForCallback) {
        const void *thisPtr = this;
        return *m_screenSizeForCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        return ::KDDockWidgets::Platform_flutter::screenSizeFor(arg__1);
    }
}
QSize Platform_flutter_wrapper::screenSizeFor_nocallback(KDDockWidgets::View *arg__1) const
{
    return ::KDDockWidgets::Platform_flutter::screenSizeFor(arg__1);
}
void Platform_flutter_wrapper::sendEvent(KDDockWidgets::View *arg__1, QEvent *arg__2) const
{
    if (m_sendEventCallback) {
        const void *thisPtr = this;
        m_sendEventCallback(const_cast<void *>(thisPtr), arg__1, arg__2);
    } else {
        ::KDDockWidgets::Platform_flutter::sendEvent(arg__1, arg__2);
    }
}
void Platform_flutter_wrapper::sendEvent_nocallback(KDDockWidgets::View *arg__1,
                                                    QEvent *arg__2) const
{
    ::KDDockWidgets::Platform_flutter::sendEvent(arg__1, arg__2);
}
void Platform_flutter_wrapper::setMouseCursor(Qt::CursorShape arg__1)
{
    if (m_setMouseCursorCallback) {
        const void *thisPtr = this;
        m_setMouseCursorCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        ::KDDockWidgets::Platform_flutter::setMouseCursor(arg__1);
    }
}
void Platform_flutter_wrapper::setMouseCursor_nocallback(Qt::CursorShape arg__1)
{
    ::KDDockWidgets::Platform_flutter::setMouseCursor(arg__1);
}
int Platform_flutter_wrapper::startDragDistance_impl() const
{
    if (m_startDragDistance_implCallback) {
        const void *thisPtr = this;
        return m_startDragDistance_implCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Platform_flutter::startDragDistance_impl();
    }
}
int Platform_flutter_wrapper::startDragDistance_impl_nocallback() const
{
    return ::KDDockWidgets::Platform_flutter::startDragDistance_impl();
}
KDDockWidgets::View *
Platform_flutter_wrapper::tests_createFocusableView(KDDockWidgets::CreateViewOptions arg__1,
                                                    KDDockWidgets::View *parent)
{
    if (m_tests_createFocusableViewCallback) {
        const void *thisPtr = this;
        return m_tests_createFocusableViewCallback(const_cast<void *>(thisPtr), &arg__1, parent);
    } else {
        return ::KDDockWidgets::Platform_flutter::tests_createFocusableView(arg__1, parent);
    }
}
KDDockWidgets::View *Platform_flutter_wrapper::tests_createFocusableView_nocallback(
    KDDockWidgets::CreateViewOptions arg__1, KDDockWidgets::View *parent)
{
    return ::KDDockWidgets::Platform_flutter::tests_createFocusableView(arg__1, parent);
}
KDDockWidgets::View *
Platform_flutter_wrapper::tests_createNonClosableView(KDDockWidgets::View *parent)
{
    if (m_tests_createNonClosableViewCallback) {
        const void *thisPtr = this;
        return m_tests_createNonClosableViewCallback(const_cast<void *>(thisPtr), parent);
    } else {
        return ::KDDockWidgets::Platform_flutter::tests_createNonClosableView(parent);
    }
}
KDDockWidgets::View *
Platform_flutter_wrapper::tests_createNonClosableView_nocallback(KDDockWidgets::View *parent)
{
    return ::KDDockWidgets::Platform_flutter::tests_createNonClosableView(parent);
}
KDDockWidgets::View *
Platform_flutter_wrapper::tests_createView(KDDockWidgets::CreateViewOptions arg__1,
                                           KDDockWidgets::View *parent)
{
    if (m_tests_createViewCallback) {
        const void *thisPtr = this;
        return m_tests_createViewCallback(const_cast<void *>(thisPtr), &arg__1, parent);
    } else {
        return ::KDDockWidgets::Platform_flutter::tests_createView(arg__1, parent);
    }
}
KDDockWidgets::View *
Platform_flutter_wrapper::tests_createView_nocallback(KDDockWidgets::CreateViewOptions arg__1,
                                                      KDDockWidgets::View *parent)
{
    return ::KDDockWidgets::Platform_flutter::tests_createView(arg__1, parent);
}
void Platform_flutter_wrapper::tests_deinitPlatform_impl()
{
    if (m_tests_deinitPlatform_implCallback) {
        const void *thisPtr = this;
        m_tests_deinitPlatform_implCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Platform_flutter::tests_deinitPlatform_impl();
    }
}
void Platform_flutter_wrapper::tests_deinitPlatform_impl_nocallback()
{
    ::KDDockWidgets::Platform_flutter::tests_deinitPlatform_impl();
}
void Platform_flutter_wrapper::tests_initPlatform_impl()
{
    if (m_tests_initPlatform_implCallback) {
        const void *thisPtr = this;
        m_tests_initPlatform_implCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Platform_flutter::tests_initPlatform_impl();
    }
}
void Platform_flutter_wrapper::tests_initPlatform_impl_nocallback()
{
    ::KDDockWidgets::Platform_flutter::tests_initPlatform_impl();
}
void Platform_flutter_wrapper::tests_wait(int ms)
{
    if (m_tests_waitCallback) {
        const void *thisPtr = this;
        m_tests_waitCallback(const_cast<void *>(thisPtr), ms);
    } else {
        ::KDDockWidgets::Platform_flutter::tests_wait(ms);
    }
}
void Platform_flutter_wrapper::tests_wait_nocallback(int ms)
{
    ::KDDockWidgets::Platform_flutter::tests_wait(ms);
}
void Platform_flutter_wrapper::ungrabMouse()
{
    if (m_ungrabMouseCallback) {
        const void *thisPtr = this;
        m_ungrabMouseCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Platform_flutter::ungrabMouse();
    }
}
void Platform_flutter_wrapper::ungrabMouse_nocallback()
{
    ::KDDockWidgets::Platform_flutter::ungrabMouse();
}
void Platform_flutter_wrapper::uninstallMessageHandler()
{
    if (m_uninstallMessageHandlerCallback) {
        const void *thisPtr = this;
        m_uninstallMessageHandlerCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Platform_flutter::uninstallMessageHandler();
    }
}
void Platform_flutter_wrapper::uninstallMessageHandler_nocallback()
{
    ::KDDockWidgets::Platform_flutter::uninstallMessageHandler();
}
bool Platform_flutter_wrapper::usesFallbackMouseGrabber() const
{
    if (m_usesFallbackMouseGrabberCallback) {
        const void *thisPtr = this;
        return m_usesFallbackMouseGrabberCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Platform_flutter::usesFallbackMouseGrabber();
    }
}
bool Platform_flutter_wrapper::usesFallbackMouseGrabber_nocallback() const
{
    return ::KDDockWidgets::Platform_flutter::usesFallbackMouseGrabber();
}
Platform_flutter_wrapper::~Platform_flutter_wrapper()
{
}

}
static KDDockWidgets::Platform_flutter *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::Platform_flutter *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__Platform_flutter_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper *>(cppObj);
}
void *c_KDDockWidgets__Platform_flutter__constructor()
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper();
    return reinterpret_cast<void *>(ptr);
}
// applicationName() const
void *c_KDDockWidgets__Platform_flutter__applicationName(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QString> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->applicationName_nocallback();
        } else {
            return targetPtr->applicationName();
        }
    }() };
}
// createDefaultViewFactory()
void *c_KDDockWidgets__Platform_flutter__createDefaultViewFactory(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->createDefaultViewFactory_nocallback();
        } else {
            return targetPtr->createDefaultViewFactory();
        }
    }();
}
// createMainWindow(const QString & uniqueName, KDDockWidgets::CreateViewOptions arg__2,
// QFlags<KDDockWidgets::MainWindowOption> options, KDDockWidgets::View * parent, Qt::WindowFlags
// arg__5) const
void *
c_KDDockWidgets__Platform_flutter__createMainWindow_QString_CreateViewOptions_MainWindowOptions_View_WindowFlags(
    void *thisObj, const char *uniqueName_, void *arg__2_, int options_, void *parent_, int arg__5)
{
    const auto uniqueName = QString::fromUtf8(uniqueName_);
    assert(arg__2_);
    auto &arg__2 = *reinterpret_cast<KDDockWidgets::CreateViewOptions *>(arg__2_);
    auto options = static_cast<QFlags<KDDockWidgets::MainWindowOption>>(options_);
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->createMainWindow_nocallback(uniqueName, arg__2, options, parent,
                                                           static_cast<Qt::WindowFlags>(arg__5));
        } else {
            return targetPtr->createMainWindow(uniqueName, arg__2, options, parent,
                                               static_cast<Qt::WindowFlags>(arg__5));
        }
    }();
}
// createView(KDDockWidgets::Controller * controller, KDDockWidgets::View * parent) const
void *c_KDDockWidgets__Platform_flutter__createView_Controller_View(void *thisObj,
                                                                    void *controller_,
                                                                    void *parent_)
{
    auto controller = reinterpret_cast<KDDockWidgets::Controller *>(controller_);
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->createView_nocallback(controller, parent);
        } else {
            return targetPtr->createView(controller, parent);
        }
    }();
}
// dumpManagedBacktrace()
void c_KDDockWidgets__Platform_flutter__dumpManagedBacktrace(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->dumpManagedBacktrace_nocallback();
        } else {
            return targetPtr->dumpManagedBacktrace();
        }
    }();
}
// hasActivePopup() const
bool c_KDDockWidgets__Platform_flutter__hasActivePopup(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->hasActivePopup_nocallback();
        } else {
            return targetPtr->hasActivePopup();
        }
    }();
}
// inDisallowedDragView(QPoint globalPos) const
bool c_KDDockWidgets__Platform_flutter__inDisallowedDragView_QPoint(void *thisObj, void *globalPos_)
{
    assert(globalPos_);
    auto &globalPos = *reinterpret_cast<QPoint *>(globalPos_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->inDisallowedDragView_nocallback(globalPos);
        } else {
            return targetPtr->inDisallowedDragView(globalPos);
        }
    }();
}
// init()
void c_KDDockWidgets__Platform_flutter__init(void *thisObj)
{
    fromWrapperPtr(thisObj)->init();
}
// installMessageHandler()
void c_KDDockWidgets__Platform_flutter__installMessageHandler(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->installMessageHandler_nocallback();
        } else {
            return targetPtr->installMessageHandler();
        }
    }();
}
// isLeftMouseButtonPressed() const
bool c_KDDockWidgets__Platform_flutter__isLeftMouseButtonPressed(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->isLeftMouseButtonPressed_nocallback();
        } else {
            return targetPtr->isLeftMouseButtonPressed();
        }
    }();
}
// isProcessingAppQuitEvent() const
bool c_KDDockWidgets__Platform_flutter__isProcessingAppQuitEvent(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->isProcessingAppQuitEvent_nocallback();
        } else {
            return targetPtr->isProcessingAppQuitEvent();
        }
    }();
}
// name() const
const char *c_KDDockWidgets__Platform_flutter__name(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->name_nocallback();
        } else {
            return targetPtr->name();
        }
    }();
}
// onFloatingWindowCreated(KDDockWidgets::Controllers::FloatingWindow * arg__1)
void c_KDDockWidgets__Platform_flutter__onFloatingWindowCreated_FloatingWindow(void *thisObj,
                                                                               void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::FloatingWindow *>(arg__1_);
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->onFloatingWindowCreated_nocallback(arg__1);
        } else {
            return targetPtr->onFloatingWindowCreated(arg__1);
        }
    }();
}
// onFloatingWindowDestroyed(KDDockWidgets::Controllers::FloatingWindow * arg__1)
void c_KDDockWidgets__Platform_flutter__onFloatingWindowDestroyed_FloatingWindow(void *thisObj,
                                                                                 void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::FloatingWindow *>(arg__1_);
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->onFloatingWindowDestroyed_nocallback(arg__1);
        } else {
            return targetPtr->onFloatingWindowDestroyed(arg__1);
        }
    }();
}
// organizationName() const
void *c_KDDockWidgets__Platform_flutter__organizationName(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QString> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->organizationName_nocallback();
        } else {
            return targetPtr->organizationName();
        }
    }() };
}
// platformFlutter()
void *c_static_KDDockWidgets__Platform_flutter__platformFlutter()
{
    return KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::platformFlutter();
}
// restoreMouseCursor()
void c_KDDockWidgets__Platform_flutter__restoreMouseCursor(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->restoreMouseCursor_nocallback();
        } else {
            return targetPtr->restoreMouseCursor();
        }
    }();
}
// screenNumberFor(KDDockWidgets::View * arg__1) const
int c_KDDockWidgets__Platform_flutter__screenNumberFor_View(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::View *>(arg__1_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->screenNumberFor_nocallback(arg__1);
        } else {
            return targetPtr->screenNumberFor(arg__1);
        }
    }();
}
// screenSizeFor(KDDockWidgets::View * arg__1) const
void *c_KDDockWidgets__Platform_flutter__screenSizeFor_View(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::View *>(arg__1_);
    return new Dartagnan::ValueWrapper<QSize> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->screenSizeFor_nocallback(arg__1);
        } else {
            return targetPtr->screenSizeFor(arg__1);
        }
    }() };
}
// sendEvent(KDDockWidgets::View * arg__1, QEvent * arg__2) const
void c_KDDockWidgets__Platform_flutter__sendEvent_View_QEvent(void *thisObj, void *arg__1_,
                                                              void *arg__2_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::View *>(arg__1_);
    auto arg__2 = reinterpret_cast<QEvent *>(arg__2_);
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->sendEvent_nocallback(arg__1, arg__2);
        } else {
            return targetPtr->sendEvent(arg__1, arg__2);
        }
    }();
}
// setMouseCursor(Qt::CursorShape arg__1)
void c_KDDockWidgets__Platform_flutter__setMouseCursor_CursorShape(void *thisObj, int arg__1)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setMouseCursor_nocallback(static_cast<Qt::CursorShape>(arg__1));
        } else {
            return targetPtr->setMouseCursor(static_cast<Qt::CursorShape>(arg__1));
        }
    }();
}
// startDragDistance_impl() const
int c_KDDockWidgets__Platform_flutter__startDragDistance_impl(void *thisObj)
{
    return fromWrapperPtr(thisObj)->startDragDistance_impl_nocallback();
}
// tests_createFocusableView(KDDockWidgets::CreateViewOptions arg__1, KDDockWidgets::View * parent)
void *c_KDDockWidgets__Platform_flutter__tests_createFocusableView_CreateViewOptions_View(
    void *thisObj, void *arg__1_, void *parent_)
{
    assert(arg__1_);
    auto &arg__1 = *reinterpret_cast<KDDockWidgets::CreateViewOptions *>(arg__1_);
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->tests_createFocusableView_nocallback(arg__1, parent);
        } else {
            return targetPtr->tests_createFocusableView(arg__1, parent);
        }
    }();
}
// tests_createNonClosableView(KDDockWidgets::View * parent)
void *c_KDDockWidgets__Platform_flutter__tests_createNonClosableView_View(void *thisObj,
                                                                          void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->tests_createNonClosableView_nocallback(parent);
        } else {
            return targetPtr->tests_createNonClosableView(parent);
        }
    }();
}
// tests_createView(KDDockWidgets::CreateViewOptions arg__1, KDDockWidgets::View * parent)
void *c_KDDockWidgets__Platform_flutter__tests_createView_CreateViewOptions_View(void *thisObj,
                                                                                 void *arg__1_,
                                                                                 void *parent_)
{
    assert(arg__1_);
    auto &arg__1 = *reinterpret_cast<KDDockWidgets::CreateViewOptions *>(arg__1_);
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->tests_createView_nocallback(arg__1, parent);
        } else {
            return targetPtr->tests_createView(arg__1, parent);
        }
    }();
}
// tests_deinitPlatform_impl()
void c_KDDockWidgets__Platform_flutter__tests_deinitPlatform_impl(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->tests_deinitPlatform_impl_nocallback();
        } else {
            return targetPtr->tests_deinitPlatform_impl();
        }
    }();
}
// tests_initPlatform_impl()
void c_KDDockWidgets__Platform_flutter__tests_initPlatform_impl(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->tests_initPlatform_impl_nocallback();
        } else {
            return targetPtr->tests_initPlatform_impl();
        }
    }();
}
// tests_wait(int ms)
void c_KDDockWidgets__Platform_flutter__tests_wait_int(void *thisObj, int ms)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->tests_wait_nocallback(ms);
        } else {
            return targetPtr->tests_wait(ms);
        }
    }();
}
// ungrabMouse()
void c_KDDockWidgets__Platform_flutter__ungrabMouse(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->ungrabMouse_nocallback();
        } else {
            return targetPtr->ungrabMouse();
        }
    }();
}
// uninstallMessageHandler()
void c_KDDockWidgets__Platform_flutter__uninstallMessageHandler(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->uninstallMessageHandler_nocallback();
        } else {
            return targetPtr->uninstallMessageHandler();
        }
    }();
}
// usesFallbackMouseGrabber() const
bool c_KDDockWidgets__Platform_flutter__usesFallbackMouseGrabber(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->usesFallbackMouseGrabber_nocallback();
        } else {
            return targetPtr->usesFallbackMouseGrabber();
        }
    }();
}
void c_KDDockWidgets__Platform_flutter__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__Platform_flutter__registerVirtualMethodCallback(void *ptr, void *callback,
                                                                      int methodId)
{
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 729:
        wrapper->m_applicationNameCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_applicationName>(
            callback);
        break;
    case 730:
        wrapper->m_createDefaultViewFactoryCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::
                                 Callback_createDefaultViewFactory>(callback);
        break;
    case 731:
        wrapper->m_createMainWindowCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_createMainWindow>(
            callback);
        break;
    case 732:
        wrapper->m_createViewCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_createView>(
            callback);
        break;
    case 733:
        wrapper->m_dumpManagedBacktraceCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::
                                 Callback_dumpManagedBacktrace>(callback);
        break;
    case 735:
        wrapper->m_hasActivePopupCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_hasActivePopup>(
            callback);
        break;
    case 736:
        wrapper->m_inDisallowedDragViewCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::
                                 Callback_inDisallowedDragView>(callback);
        break;
    case 737:
        wrapper->m_installMessageHandlerCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::
                                 Callback_installMessageHandler>(callback);
        break;
    case 739:
        wrapper->m_isLeftMouseButtonPressedCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::
                                 Callback_isLeftMouseButtonPressed>(callback);
        break;
    case 740:
        wrapper->m_isProcessingAppQuitEventCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::
                                 Callback_isProcessingAppQuitEvent>(callback);
        break;
    case 744:
        wrapper->m_nameCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_name>(callback);
        break;
    case 745:
        wrapper->m_onFloatingWindowCreatedCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::
                                 Callback_onFloatingWindowCreated>(callback);
        break;
    case 746:
        wrapper->m_onFloatingWindowDestroyedCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::
                                 Callback_onFloatingWindowDestroyed>(callback);
        break;
    case 747:
        wrapper->m_organizationNameCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_organizationName>(
            callback);
        break;
    case 748:
        wrapper->m_restoreMouseCursorCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::
                                 Callback_restoreMouseCursor>(callback);
        break;
    case 749:
        wrapper->m_screenNumberForCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_screenNumberFor>(
            callback);
        break;
    case 750:
        wrapper->m_screenSizeForCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_screenSizeFor>(
            callback);
        break;
    case 751:
        wrapper->m_sendEventCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_sendEvent>(
            callback);
        break;
    case 752:
        wrapper->m_setMouseCursorCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_setMouseCursor>(
            callback);
        break;
    case 754:
        wrapper->m_startDragDistance_implCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::
                                 Callback_startDragDistance_impl>(callback);
        break;
    case 755:
        wrapper->m_tests_createFocusableViewCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::
                                 Callback_tests_createFocusableView>(callback);
        break;
    case 756:
        wrapper->m_tests_createNonClosableViewCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::
                                 Callback_tests_createNonClosableView>(callback);
        break;
    case 757:
        wrapper->m_tests_createViewCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_tests_createView>(
            callback);
        break;
    case 759:
        wrapper->m_tests_deinitPlatform_implCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::
                                 Callback_tests_deinitPlatform_impl>(callback);
        break;
    case 761:
        wrapper->m_tests_initPlatform_implCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::
                                 Callback_tests_initPlatform_impl>(callback);
        break;
    case 762:
        wrapper->m_tests_waitCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_tests_wait>(
            callback);
        break;
    case 769:
        wrapper->m_ungrabMouseCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_ungrabMouse>(
            callback);
        break;
    case 770:
        wrapper->m_uninstallMessageHandlerCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::
                                 Callback_uninstallMessageHandler>(callback);
        break;
    case 771:
        wrapper->m_usesFallbackMouseGrabberCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::
                                 Callback_usesFallbackMouseGrabber>(callback);
        break;
    }
}
}

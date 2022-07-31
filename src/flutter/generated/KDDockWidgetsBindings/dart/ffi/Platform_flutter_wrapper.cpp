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
// tag=1006
Platform_flutter_wrapper::Platform_flutter_wrapper()
    : ::KDDockWidgets::Platform_flutter()
{
}
QString Platform_flutter_wrapper::applicationName() const
{
    // tag=1000
    if (m_applicationNameCallback) {
        // tag=1001
        const void *thisPtr = this;
        return *m_applicationNameCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        return ::KDDockWidgets::Platform_flutter::applicationName();
    }
}
// tag=1009
QString Platform_flutter_wrapper::applicationName_nocallback() const
{
    // tag=1003
    return ::KDDockWidgets::Platform_flutter::applicationName();
}
KDDockWidgets::ViewFactory *Platform_flutter_wrapper::createDefaultViewFactory()
{
    // tag=1000
    if (m_createDefaultViewFactoryCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_createDefaultViewFactoryCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        return ::KDDockWidgets::Platform_flutter::createDefaultViewFactory();
    }
}
// tag=1009
KDDockWidgets::ViewFactory *Platform_flutter_wrapper::createDefaultViewFactory_nocallback()
{
    // tag=1003
    return ::KDDockWidgets::Platform_flutter::createDefaultViewFactory();
}
KDDockWidgets::View *Platform_flutter_wrapper::createView(KDDockWidgets::Controller *controller, KDDockWidgets::View *parent) const
{
    // tag=1000
    if (m_createViewCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_createViewCallback(const_cast<void *>(thisPtr), controller, parent);
    } else {
        // tag=1002
        return ::KDDockWidgets::Platform_flutter::createView(controller, parent);
    }
}
// tag=1009
KDDockWidgets::View *Platform_flutter_wrapper::createView_nocallback(KDDockWidgets::Controller *controller, KDDockWidgets::View *parent) const
{
    // tag=1003
    return ::KDDockWidgets::Platform_flutter::createView(controller, parent);
}
bool Platform_flutter_wrapper::hasActivePopup() const
{
    // tag=1000
    if (m_hasActivePopupCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_hasActivePopupCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        return ::KDDockWidgets::Platform_flutter::hasActivePopup();
    }
}
// tag=1009
bool Platform_flutter_wrapper::hasActivePopup_nocallback() const
{
    // tag=1003
    return ::KDDockWidgets::Platform_flutter::hasActivePopup();
}
bool Platform_flutter_wrapper::inDisallowedDragView(QPoint globalPos) const
{
    // tag=1000
    if (m_inDisallowedDragViewCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_inDisallowedDragViewCallback(const_cast<void *>(thisPtr), globalPos);
    } else {
        // tag=1002
        return ::KDDockWidgets::Platform_flutter::inDisallowedDragView(globalPos);
    }
}
// tag=1009
bool Platform_flutter_wrapper::inDisallowedDragView_nocallback(QPoint globalPos) const
{
    // tag=1003
    return ::KDDockWidgets::Platform_flutter::inDisallowedDragView(globalPos);
}
void Platform_flutter_wrapper::init()
{
    // tag=1000

    // tag=1004
    ::KDDockWidgets::Platform_flutter::init();
}
void Platform_flutter_wrapper::installMessageHandler()
{
    // tag=1000
    if (m_installMessageHandlerCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_installMessageHandlerCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        ::KDDockWidgets::Platform_flutter::installMessageHandler();
    }
}
// tag=1009
void Platform_flutter_wrapper::installMessageHandler_nocallback()
{
    // tag=1003
    ::KDDockWidgets::Platform_flutter::installMessageHandler();
}
bool Platform_flutter_wrapper::isLeftMouseButtonPressed() const
{
    // tag=1000
    if (m_isLeftMouseButtonPressedCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_isLeftMouseButtonPressedCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        return ::KDDockWidgets::Platform_flutter::isLeftMouseButtonPressed();
    }
}
// tag=1009
bool Platform_flutter_wrapper::isLeftMouseButtonPressed_nocallback() const
{
    // tag=1003
    return ::KDDockWidgets::Platform_flutter::isLeftMouseButtonPressed();
}
bool Platform_flutter_wrapper::isProcessingAppQuitEvent() const
{
    // tag=1000
    if (m_isProcessingAppQuitEventCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_isProcessingAppQuitEventCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        return ::KDDockWidgets::Platform_flutter::isProcessingAppQuitEvent();
    }
}
// tag=1009
bool Platform_flutter_wrapper::isProcessingAppQuitEvent_nocallback() const
{
    // tag=1003
    return ::KDDockWidgets::Platform_flutter::isProcessingAppQuitEvent();
}
const char *Platform_flutter_wrapper::name() const
{
    // tag=1000
    if (m_nameCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_nameCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        return ::KDDockWidgets::Platform_flutter::name();
    }
}
// tag=1009
const char *Platform_flutter_wrapper::name_nocallback() const
{
    // tag=1003
    return ::KDDockWidgets::Platform_flutter::name();
}
QString Platform_flutter_wrapper::organizationName() const
{
    // tag=1000
    if (m_organizationNameCallback) {
        // tag=1001
        const void *thisPtr = this;
        return *m_organizationNameCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        return ::KDDockWidgets::Platform_flutter::organizationName();
    }
}
// tag=1009
QString Platform_flutter_wrapper::organizationName_nocallback() const
{
    // tag=1003
    return ::KDDockWidgets::Platform_flutter::organizationName();
}
void Platform_flutter_wrapper::restoreMouseCursor()
{
    // tag=1000
    if (m_restoreMouseCursorCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_restoreMouseCursorCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        ::KDDockWidgets::Platform_flutter::restoreMouseCursor();
    }
}
// tag=1009
void Platform_flutter_wrapper::restoreMouseCursor_nocallback()
{
    // tag=1003
    ::KDDockWidgets::Platform_flutter::restoreMouseCursor();
}
int Platform_flutter_wrapper::screenNumberFor(KDDockWidgets::View *arg__1) const
{
    // tag=1000
    if (m_screenNumberForCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_screenNumberForCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        // tag=1002
        return ::KDDockWidgets::Platform_flutter::screenNumberFor(arg__1);
    }
}
// tag=1009
int Platform_flutter_wrapper::screenNumberFor_nocallback(KDDockWidgets::View *arg__1) const
{
    // tag=1003
    return ::KDDockWidgets::Platform_flutter::screenNumberFor(arg__1);
}
QSize Platform_flutter_wrapper::screenSizeFor(KDDockWidgets::View *arg__1) const
{
    // tag=1000
    if (m_screenSizeForCallback) {
        // tag=1001
        const void *thisPtr = this;
        return *m_screenSizeForCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        // tag=1002
        return ::KDDockWidgets::Platform_flutter::screenSizeFor(arg__1);
    }
}
// tag=1009
QSize Platform_flutter_wrapper::screenSizeFor_nocallback(KDDockWidgets::View *arg__1) const
{
    // tag=1003
    return ::KDDockWidgets::Platform_flutter::screenSizeFor(arg__1);
}
void Platform_flutter_wrapper::sendEvent(KDDockWidgets::View *arg__1, QEvent *arg__2) const
{
    // tag=1000
    if (m_sendEventCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_sendEventCallback(const_cast<void *>(thisPtr), arg__1, arg__2);
    } else {
        // tag=1002
        ::KDDockWidgets::Platform_flutter::sendEvent(arg__1, arg__2);
    }
}
// tag=1009
void Platform_flutter_wrapper::sendEvent_nocallback(KDDockWidgets::View *arg__1, QEvent *arg__2) const
{
    // tag=1003
    ::KDDockWidgets::Platform_flutter::sendEvent(arg__1, arg__2);
}
void Platform_flutter_wrapper::setMouseCursor(Qt::CursorShape arg__1)
{
    // tag=1000
    if (m_setMouseCursorCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setMouseCursorCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        // tag=1002
        ::KDDockWidgets::Platform_flutter::setMouseCursor(arg__1);
    }
}
// tag=1009
void Platform_flutter_wrapper::setMouseCursor_nocallback(Qt::CursorShape arg__1)
{
    // tag=1003
    ::KDDockWidgets::Platform_flutter::setMouseCursor(arg__1);
}
KDDockWidgets::View *Platform_flutter_wrapper::tests_createFocusableView(KDDockWidgets::CreateViewOptions arg__1, KDDockWidgets::View *parent)
{
    // tag=1000
    if (m_tests_createFocusableViewCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_tests_createFocusableViewCallback(const_cast<void *>(thisPtr), arg__1, parent);
    } else {
        // tag=1002
        return ::KDDockWidgets::Platform_flutter::tests_createFocusableView(arg__1, parent);
    }
}
// tag=1009
KDDockWidgets::View *Platform_flutter_wrapper::tests_createFocusableView_nocallback(KDDockWidgets::CreateViewOptions arg__1, KDDockWidgets::View *parent)
{
    // tag=1003
    return ::KDDockWidgets::Platform_flutter::tests_createFocusableView(arg__1, parent);
}
KDDockWidgets::View *Platform_flutter_wrapper::tests_createNonClosableView(KDDockWidgets::View *parent)
{
    // tag=1000
    if (m_tests_createNonClosableViewCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_tests_createNonClosableViewCallback(const_cast<void *>(thisPtr), parent);
    } else {
        // tag=1002
        return ::KDDockWidgets::Platform_flutter::tests_createNonClosableView(parent);
    }
}
// tag=1009
KDDockWidgets::View *Platform_flutter_wrapper::tests_createNonClosableView_nocallback(KDDockWidgets::View *parent)
{
    // tag=1003
    return ::KDDockWidgets::Platform_flutter::tests_createNonClosableView(parent);
}
KDDockWidgets::View *Platform_flutter_wrapper::tests_createView(KDDockWidgets::CreateViewOptions arg__1, KDDockWidgets::View *parent)
{
    // tag=1000
    if (m_tests_createViewCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_tests_createViewCallback(const_cast<void *>(thisPtr), arg__1, parent);
    } else {
        // tag=1002
        return ::KDDockWidgets::Platform_flutter::tests_createView(arg__1, parent);
    }
}
// tag=1009
KDDockWidgets::View *Platform_flutter_wrapper::tests_createView_nocallback(KDDockWidgets::CreateViewOptions arg__1, KDDockWidgets::View *parent)
{
    // tag=1003
    return ::KDDockWidgets::Platform_flutter::tests_createView(arg__1, parent);
}
void Platform_flutter_wrapper::tests_deinitPlatform_impl()
{
    // tag=1000
    if (m_tests_deinitPlatform_implCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_tests_deinitPlatform_implCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        ::KDDockWidgets::Platform_flutter::tests_deinitPlatform_impl();
    }
}
// tag=1009
void Platform_flutter_wrapper::tests_deinitPlatform_impl_nocallback()
{
    // tag=1003
    ::KDDockWidgets::Platform_flutter::tests_deinitPlatform_impl();
}
void Platform_flutter_wrapper::tests_initPlatform_impl()
{
    // tag=1000
    if (m_tests_initPlatform_implCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_tests_initPlatform_implCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        ::KDDockWidgets::Platform_flutter::tests_initPlatform_impl();
    }
}
// tag=1009
void Platform_flutter_wrapper::tests_initPlatform_impl_nocallback()
{
    // tag=1003
    ::KDDockWidgets::Platform_flutter::tests_initPlatform_impl();
}
void Platform_flutter_wrapper::tests_wait(int ms)
{
    // tag=1000
    if (m_tests_waitCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_tests_waitCallback(const_cast<void *>(thisPtr), ms);
    } else {
        // tag=1002
        ::KDDockWidgets::Platform_flutter::tests_wait(ms);
    }
}
// tag=1009
void Platform_flutter_wrapper::tests_wait_nocallback(int ms)
{
    // tag=1003
    ::KDDockWidgets::Platform_flutter::tests_wait(ms);
}
bool Platform_flutter_wrapper::tests_waitForDeleted(KDDockWidgets::View *arg__1, int timeout) const
{
    // tag=1000
    if (m_tests_waitForDeletedCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_tests_waitForDeletedCallback(const_cast<void *>(thisPtr), arg__1, timeout);
    } else {
        // tag=1002
        return ::KDDockWidgets::Platform_flutter::tests_waitForDeleted(arg__1, timeout);
    }
}
// tag=1009
bool Platform_flutter_wrapper::tests_waitForDeleted_nocallback(KDDockWidgets::View *arg__1, int timeout) const
{
    // tag=1003
    return ::KDDockWidgets::Platform_flutter::tests_waitForDeleted(arg__1, timeout);
}
bool Platform_flutter_wrapper::tests_waitForDeleted(QObject *arg__1, int timeout) const
{
    // tag=1000
    if (m_tests_waitForDeleted_2Callback) {
        // tag=1001
        const void *thisPtr = this;
        return m_tests_waitForDeleted_2Callback(const_cast<void *>(thisPtr), arg__1, timeout);
    } else {
        // tag=1002
        return ::KDDockWidgets::Platform_flutter::tests_waitForDeleted(arg__1, timeout);
    }
}
// tag=1009
bool Platform_flutter_wrapper::tests_waitForDeleted_nocallback(QObject *arg__1, int timeout) const
{
    // tag=1003
    return ::KDDockWidgets::Platform_flutter::tests_waitForDeleted(arg__1, timeout);
}
bool Platform_flutter_wrapper::tests_waitForEvent(KDDockWidgets::View *arg__1, QEvent::Type type, int timeout) const
{
    // tag=1000
    if (m_tests_waitForEventCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_tests_waitForEventCallback(const_cast<void *>(thisPtr), arg__1, type, timeout);
    } else {
        // tag=1002
        return ::KDDockWidgets::Platform_flutter::tests_waitForEvent(arg__1, type, timeout);
    }
}
// tag=1009
bool Platform_flutter_wrapper::tests_waitForEvent_nocallback(KDDockWidgets::View *arg__1, QEvent::Type type, int timeout) const
{
    // tag=1003
    return ::KDDockWidgets::Platform_flutter::tests_waitForEvent(arg__1, type, timeout);
}
bool Platform_flutter_wrapper::tests_waitForEvent(QObject *w, QEvent::Type type, int timeout) const
{
    // tag=1000
    if (m_tests_waitForEvent_2Callback) {
        // tag=1001
        const void *thisPtr = this;
        return m_tests_waitForEvent_2Callback(const_cast<void *>(thisPtr), w, type, timeout);
    } else {
        // tag=1002
        return ::KDDockWidgets::Platform_flutter::tests_waitForEvent(w, type, timeout);
    }
}
// tag=1009
bool Platform_flutter_wrapper::tests_waitForEvent_nocallback(QObject *w, QEvent::Type type, int timeout) const
{
    // tag=1003
    return ::KDDockWidgets::Platform_flutter::tests_waitForEvent(w, type, timeout);
}
bool Platform_flutter_wrapper::tests_waitForResize(KDDockWidgets::Controller *arg__1, int timeout) const
{
    // tag=1000
    if (m_tests_waitForResizeCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_tests_waitForResizeCallback(const_cast<void *>(thisPtr), arg__1, timeout);
    } else {
        // tag=1002
        return ::KDDockWidgets::Platform_flutter::tests_waitForResize(arg__1, timeout);
    }
}
// tag=1009
bool Platform_flutter_wrapper::tests_waitForResize_nocallback(KDDockWidgets::Controller *arg__1, int timeout) const
{
    // tag=1003
    return ::KDDockWidgets::Platform_flutter::tests_waitForResize(arg__1, timeout);
}
bool Platform_flutter_wrapper::tests_waitForResize(KDDockWidgets::View *arg__1, int timeout) const
{
    // tag=1000
    if (m_tests_waitForResize_2Callback) {
        // tag=1001
        const void *thisPtr = this;
        return m_tests_waitForResize_2Callback(const_cast<void *>(thisPtr), arg__1, timeout);
    } else {
        // tag=1002
        return ::KDDockWidgets::Platform_flutter::tests_waitForResize(arg__1, timeout);
    }
}
// tag=1009
bool Platform_flutter_wrapper::tests_waitForResize_nocallback(KDDockWidgets::View *arg__1, int timeout) const
{
    // tag=1003
    return ::KDDockWidgets::Platform_flutter::tests_waitForResize(arg__1, timeout);
}
void Platform_flutter_wrapper::ungrabMouse()
{
    // tag=1000
    if (m_ungrabMouseCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_ungrabMouseCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        ::KDDockWidgets::Platform_flutter::ungrabMouse();
    }
}
// tag=1009
void Platform_flutter_wrapper::ungrabMouse_nocallback()
{
    // tag=1003
    ::KDDockWidgets::Platform_flutter::ungrabMouse();
}
void Platform_flutter_wrapper::uninstallMessageHandler()
{
    // tag=1000
    if (m_uninstallMessageHandlerCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_uninstallMessageHandlerCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        ::KDDockWidgets::Platform_flutter::uninstallMessageHandler();
    }
}
// tag=1009
void Platform_flutter_wrapper::uninstallMessageHandler_nocallback()
{
    // tag=1003
    ::KDDockWidgets::Platform_flutter::uninstallMessageHandler();
}
bool Platform_flutter_wrapper::usesFallbackMouseGrabber() const
{
    // tag=1000
    if (m_usesFallbackMouseGrabberCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_usesFallbackMouseGrabberCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        return ::KDDockWidgets::Platform_flutter::usesFallbackMouseGrabber();
    }
}
// tag=1009
bool Platform_flutter_wrapper::usesFallbackMouseGrabber_nocallback() const
{
    // tag=1003
    return ::KDDockWidgets::Platform_flutter::usesFallbackMouseGrabber();
}

// tag=1005
Platform_flutter_wrapper::~Platform_flutter_wrapper()
{
}

}
// tag=1013
static KDDockWidgets::Platform_flutter *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::Platform_flutter *>(ptr);
}
// tag=1014
static KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper *>(ptr);
}
extern "C" {

// tag=1049
void c_KDDockWidgets__Platform_flutter_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper *>(cppObj);
}
void *c_KDDockWidgets__Platform_flutter__constructor()
{

    // tag=1056
    auto ptr = new KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper();
    return reinterpret_cast<void *>(ptr);
}

// tag=1050
// applicationName() const
void *c_KDDockWidgets__Platform_flutter__applicationName(void *thisObj)
{
    return
        // tag=1016

        // tag=1072
        new Dartagnan::ValueWrapper<QString> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->applicationName_nocallback();} else {    return targetPtr->applicationName();} }() };
}

// tag=1050
// createDefaultViewFactory()
void *c_KDDockWidgets__Platform_flutter__createDefaultViewFactory(void *thisObj)
{
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->createDefaultViewFactory_nocallback();} else {    return targetPtr->createDefaultViewFactory();} }();
}

// tag=1050
// createView(KDDockWidgets::Controller * controller, KDDockWidgets::View * parent) const
void *c_KDDockWidgets__Platform_flutter__createView_Controller_View(void *thisObj, void *controller_, void *parent_)
{
    auto controller = reinterpret_cast<KDDockWidgets::Controller *>(controller_);
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->createView_nocallback(controller,parent);} else {    return targetPtr->createView(controller,parent);} }();
}

// tag=1050
// hasActivePopup() const
bool c_KDDockWidgets__Platform_flutter__hasActivePopup(void *thisObj)
{
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->hasActivePopup_nocallback();} else {    return targetPtr->hasActivePopup();} }();
}

// tag=1050
// inDisallowedDragView(QPoint globalPos) const
bool c_KDDockWidgets__Platform_flutter__inDisallowedDragView_QPoint(void *thisObj, void *globalPos_)
{
    auto &globalPos = *reinterpret_cast<QPoint *>(globalPos_);
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->inDisallowedDragView_nocallback(globalPos);} else {    return targetPtr->inDisallowedDragView(globalPos);} }();
}

// tag=1050
// init()
void c_KDDockWidgets__Platform_flutter__init(void *thisObj)
{
    // tag=1011

    // tag=1073
    fromWrapperPtr(thisObj)->init();
}

// tag=1050
// installMessageHandler()
void c_KDDockWidgets__Platform_flutter__installMessageHandler(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->installMessageHandler_nocallback();} else {    return targetPtr->installMessageHandler();} }();
}

// tag=1050
// isLeftMouseButtonPressed() const
bool c_KDDockWidgets__Platform_flutter__isLeftMouseButtonPressed(void *thisObj)
{
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isLeftMouseButtonPressed_nocallback();} else {    return targetPtr->isLeftMouseButtonPressed();} }();
}

// tag=1050
// isProcessingAppQuitEvent() const
bool c_KDDockWidgets__Platform_flutter__isProcessingAppQuitEvent(void *thisObj)
{
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isProcessingAppQuitEvent_nocallback();} else {    return targetPtr->isProcessingAppQuitEvent();} }();
}

// tag=1050
// name() const
const char *c_KDDockWidgets__Platform_flutter__name(void *thisObj)
{
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->name_nocallback();} else {    return targetPtr->name();} }();
}

// tag=1050
// organizationName() const
void *c_KDDockWidgets__Platform_flutter__organizationName(void *thisObj)
{
    return
        // tag=1016

        // tag=1072
        new Dartagnan::ValueWrapper<QString> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->organizationName_nocallback();} else {    return targetPtr->organizationName();} }() };
}

// tag=1050
// restoreMouseCursor()
void c_KDDockWidgets__Platform_flutter__restoreMouseCursor(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->restoreMouseCursor_nocallback();} else {    return targetPtr->restoreMouseCursor();} }();
}

// tag=1050
// screenNumberFor(KDDockWidgets::View * arg__1) const
int c_KDDockWidgets__Platform_flutter__screenNumberFor_View(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::View *>(arg__1_);
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->screenNumberFor_nocallback(arg__1);} else {    return targetPtr->screenNumberFor(arg__1);} }();
}

// tag=1050
// screenSizeFor(KDDockWidgets::View * arg__1) const
void *c_KDDockWidgets__Platform_flutter__screenSizeFor_View(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::View *>(arg__1_);
    return
        // tag=1016

        // tag=1072
        new Dartagnan::ValueWrapper<QSize> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->screenSizeFor_nocallback(arg__1);} else {    return targetPtr->screenSizeFor(arg__1);} }() };
}

// tag=1050
// sendEvent(KDDockWidgets::View * arg__1, QEvent * arg__2) const
void c_KDDockWidgets__Platform_flutter__sendEvent_View_QEvent(void *thisObj, void *arg__1_, void *arg__2_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::View *>(arg__1_);
    auto arg__2 = reinterpret_cast<QEvent *>(arg__2_);
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->sendEvent_nocallback(arg__1,arg__2);} else {    return targetPtr->sendEvent(arg__1,arg__2);} }();
}

// tag=1050
// setMouseCursor(Qt::CursorShape arg__1)
void c_KDDockWidgets__Platform_flutter__setMouseCursor_CursorShape(void *thisObj, int arg__1)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setMouseCursor_nocallback(static_cast<Qt::CursorShape>(arg__1));} else {    return targetPtr->setMouseCursor(static_cast<Qt::CursorShape>(arg__1));} }();
}

// tag=1050
// tests_createFocusableView(KDDockWidgets::CreateViewOptions arg__1, KDDockWidgets::View * parent)
void *c_KDDockWidgets__Platform_flutter__tests_createFocusableView_CreateViewOptions_View(void *thisObj, void *arg__1_, void *parent_)
{
    auto &arg__1 = *reinterpret_cast<KDDockWidgets::CreateViewOptions *>(arg__1_);
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->tests_createFocusableView_nocallback(arg__1,parent);} else {    return targetPtr->tests_createFocusableView(arg__1,parent);} }();
}

// tag=1050
// tests_createNonClosableView(KDDockWidgets::View * parent)
void *c_KDDockWidgets__Platform_flutter__tests_createNonClosableView_View(void *thisObj, void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->tests_createNonClosableView_nocallback(parent);} else {    return targetPtr->tests_createNonClosableView(parent);} }();
}

// tag=1050
// tests_createView(KDDockWidgets::CreateViewOptions arg__1, KDDockWidgets::View * parent)
void *c_KDDockWidgets__Platform_flutter__tests_createView_CreateViewOptions_View(void *thisObj, void *arg__1_, void *parent_)
{
    auto &arg__1 = *reinterpret_cast<KDDockWidgets::CreateViewOptions *>(arg__1_);
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->tests_createView_nocallback(arg__1,parent);} else {    return targetPtr->tests_createView(arg__1,parent);} }();
}

// tag=1050
// tests_deinitPlatform_impl()
void c_KDDockWidgets__Platform_flutter__tests_deinitPlatform_impl(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->tests_deinitPlatform_impl_nocallback();} else {    return targetPtr->tests_deinitPlatform_impl();} }();
}

// tag=1050
// tests_initPlatform_impl()
void c_KDDockWidgets__Platform_flutter__tests_initPlatform_impl(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->tests_initPlatform_impl_nocallback();} else {    return targetPtr->tests_initPlatform_impl();} }();
}

// tag=1050
// tests_wait(int ms)
void c_KDDockWidgets__Platform_flutter__tests_wait_int(void *thisObj, int ms)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->tests_wait_nocallback(ms);} else {    return targetPtr->tests_wait(ms);} }();
}

// tag=1050
// tests_waitForDeleted(KDDockWidgets::View * arg__1, int timeout) const
bool c_KDDockWidgets__Platform_flutter__tests_waitForDeleted_View_int(void *thisObj, void *arg__1_, int timeout)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::View *>(arg__1_);
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->tests_waitForDeleted_nocallback(arg__1,timeout);} else {    return targetPtr->tests_waitForDeleted(arg__1,timeout);} }();
}

// tag=1050
// tests_waitForDeleted(QObject * arg__1, int timeout) const
bool c_KDDockWidgets__Platform_flutter__tests_waitForDeleted_QObject_int(void *thisObj, void *arg__1_, int timeout)
{
    auto arg__1 = reinterpret_cast<QObject *>(arg__1_);
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->tests_waitForDeleted_nocallback(arg__1,timeout);} else {    return targetPtr->tests_waitForDeleted(arg__1,timeout);} }();
}

// tag=1050
// tests_waitForEvent(KDDockWidgets::View * arg__1, QEvent::Type type, int timeout) const
bool c_KDDockWidgets__Platform_flutter__tests_waitForEvent_View_Type_int(void *thisObj, void *arg__1_, int type, int timeout)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::View *>(arg__1_);
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->tests_waitForEvent_nocallback(arg__1,static_cast<QEvent::Type>(type),timeout);} else {    return targetPtr->tests_waitForEvent(arg__1,static_cast<QEvent::Type>(type),timeout);} }();
}

// tag=1050
// tests_waitForEvent(QObject * w, QEvent::Type type, int timeout) const
bool c_KDDockWidgets__Platform_flutter__tests_waitForEvent_QObject_Type_int(void *thisObj, void *w_, int type, int timeout)
{
    auto w = reinterpret_cast<QObject *>(w_);
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->tests_waitForEvent_nocallback(w,static_cast<QEvent::Type>(type),timeout);} else {    return targetPtr->tests_waitForEvent(w,static_cast<QEvent::Type>(type),timeout);} }();
}

// tag=1050
// tests_waitForResize(KDDockWidgets::Controller * arg__1, int timeout) const
bool c_KDDockWidgets__Platform_flutter__tests_waitForResize_Controller_int(void *thisObj, void *arg__1_, int timeout)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controller *>(arg__1_);
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->tests_waitForResize_nocallback(arg__1,timeout);} else {    return targetPtr->tests_waitForResize(arg__1,timeout);} }();
}

// tag=1050
// tests_waitForResize(KDDockWidgets::View * arg__1, int timeout) const
bool c_KDDockWidgets__Platform_flutter__tests_waitForResize_View_int(void *thisObj, void *arg__1_, int timeout)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::View *>(arg__1_);
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->tests_waitForResize_nocallback(arg__1,timeout);} else {    return targetPtr->tests_waitForResize(arg__1,timeout);} }();
}

// tag=1050
// ungrabMouse()
void c_KDDockWidgets__Platform_flutter__ungrabMouse(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->ungrabMouse_nocallback();} else {    return targetPtr->ungrabMouse();} }();
}

// tag=1050
// uninstallMessageHandler()
void c_KDDockWidgets__Platform_flutter__uninstallMessageHandler(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->uninstallMessageHandler_nocallback();} else {    return targetPtr->uninstallMessageHandler();} }();
}

// tag=1050
// usesFallbackMouseGrabber() const
bool c_KDDockWidgets__Platform_flutter__usesFallbackMouseGrabber(void *thisObj)
{
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->usesFallbackMouseGrabber_nocallback();} else {    return targetPtr->usesFallbackMouseGrabber();} }();
}
void c_KDDockWidgets__Platform_flutter__destructor(void *thisObj)
{

    // tag=1055
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__Platform_flutter__registerVirtualMethodCallback(void *ptr, void *callback, int methodId)
{
    // tag=1048
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 637:
        wrapper->m_applicationNameCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_applicationName>(callback);
        break;
    case 638:
        wrapper->m_createDefaultViewFactoryCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_createDefaultViewFactory>(callback);
        break;
    case 639:
        wrapper->m_createViewCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_createView>(callback);
        break;
    case 640:
        wrapper->m_hasActivePopupCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_hasActivePopup>(callback);
        break;
    case 641:
        wrapper->m_inDisallowedDragViewCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_inDisallowedDragView>(callback);
        break;
    case 643:
        wrapper->m_installMessageHandlerCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_installMessageHandler>(callback);
        break;
    case 644:
        wrapper->m_isLeftMouseButtonPressedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_isLeftMouseButtonPressed>(callback);
        break;
    case 645:
        wrapper->m_isProcessingAppQuitEventCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_isProcessingAppQuitEvent>(callback);
        break;
    case 646:
        wrapper->m_nameCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_name>(callback);
        break;
    case 647:
        wrapper->m_organizationNameCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_organizationName>(callback);
        break;
    case 648:
        wrapper->m_restoreMouseCursorCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_restoreMouseCursor>(callback);
        break;
    case 649:
        wrapper->m_screenNumberForCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_screenNumberFor>(callback);
        break;
    case 650:
        wrapper->m_screenSizeForCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_screenSizeFor>(callback);
        break;
    case 651:
        wrapper->m_sendEventCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_sendEvent>(callback);
        break;
    case 652:
        wrapper->m_setMouseCursorCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_setMouseCursor>(callback);
        break;
    case 653:
        wrapper->m_tests_createFocusableViewCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_tests_createFocusableView>(callback);
        break;
    case 654:
        wrapper->m_tests_createNonClosableViewCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_tests_createNonClosableView>(callback);
        break;
    case 655:
        wrapper->m_tests_createViewCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_tests_createView>(callback);
        break;
    case 656:
        wrapper->m_tests_deinitPlatform_implCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_tests_deinitPlatform_impl>(callback);
        break;
    case 657:
        wrapper->m_tests_initPlatform_implCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_tests_initPlatform_impl>(callback);
        break;
    case 658:
        wrapper->m_tests_waitCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_tests_wait>(callback);
        break;
    case 659:
        wrapper->m_tests_waitForDeletedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_tests_waitForDeleted>(callback);
        break;
    case 660:
        wrapper->m_tests_waitForDeleted_2Callback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_tests_waitForDeleted_2>(callback);
        break;
    case 661:
        wrapper->m_tests_waitForEventCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_tests_waitForEvent>(callback);
        break;
    case 662:
        wrapper->m_tests_waitForEvent_2Callback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_tests_waitForEvent_2>(callback);
        break;
    case 663:
        wrapper->m_tests_waitForResizeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_tests_waitForResize>(callback);
        break;
    case 664:
        wrapper->m_tests_waitForResize_2Callback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_tests_waitForResize_2>(callback);
        break;
    case 665:
        wrapper->m_ungrabMouseCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_ungrabMouse>(callback);
        break;
    case 666:
        wrapper->m_uninstallMessageHandlerCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_uninstallMessageHandler>(callback);
        break;
    case 667:
        wrapper->m_usesFallbackMouseGrabberCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_flutter_wrapper::Callback_usesFallbackMouseGrabber>(callback);
        break;
    }
}
}

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "Platform_wrapper.h"


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
Platform_wrapper::Platform_wrapper()
    : ::KDDockWidgets::Platform()
{
}
QString Platform_wrapper::applicationName() const
{
    if (m_applicationNameCallback) {
        const void *thisPtr = this;
        return *m_applicationNameCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
QString Platform_wrapper::applicationName_nocallback() const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
KDDockWidgets::ViewFactory *Platform_wrapper::createDefaultViewFactory()
{
    if (m_createDefaultViewFactoryCallback) {
        const void *thisPtr = this;
        return m_createDefaultViewFactoryCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
KDDockWidgets::ViewFactory *Platform_wrapper::createDefaultViewFactory_nocallback()
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
KDDockWidgets::View *Platform_wrapper::createView(KDDockWidgets::Controller *arg__1,
                                                  KDDockWidgets::View *parent) const
{
    if (m_createViewCallback) {
        const void *thisPtr = this;
        return m_createViewCallback(const_cast<void *>(thisPtr), arg__1, parent);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
KDDockWidgets::View *Platform_wrapper::createView_nocallback(KDDockWidgets::Controller *arg__1,
                                                             KDDockWidgets::View *parent) const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
void Platform_wrapper::dumpManagedBacktrace()
{
    if (m_dumpManagedBacktraceCallback) {
        const void *thisPtr = this;
        m_dumpManagedBacktraceCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Platform::dumpManagedBacktrace();
    }
}
void Platform_wrapper::dumpManagedBacktrace_nocallback()
{
    ::KDDockWidgets::Platform::dumpManagedBacktrace();
}
bool Platform_wrapper::hasActivePopup() const
{
    if (m_hasActivePopupCallback) {
        const void *thisPtr = this;
        return m_hasActivePopupCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Platform::hasActivePopup();
    }
}
bool Platform_wrapper::hasActivePopup_nocallback() const
{
    return ::KDDockWidgets::Platform::hasActivePopup();
}
bool Platform_wrapper::inDisallowedDragView(QPoint globalPos) const
{
    if (m_inDisallowedDragViewCallback) {
        const void *thisPtr = this;
        return m_inDisallowedDragViewCallback(const_cast<void *>(thisPtr), &globalPos);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
bool Platform_wrapper::inDisallowedDragView_nocallback(QPoint globalPos) const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
void Platform_wrapper::installMessageHandler()
{
    if (m_installMessageHandlerCallback) {
        const void *thisPtr = this;
        m_installMessageHandlerCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void Platform_wrapper::installMessageHandler_nocallback()
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
KDDockWidgets::Platform *Platform_wrapper::instance()
{
    return ::KDDockWidgets::Platform::instance();
}
bool Platform_wrapper::isLeftMouseButtonPressed() const
{
    if (m_isLeftMouseButtonPressedCallback) {
        const void *thisPtr = this;
        return m_isLeftMouseButtonPressedCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
bool Platform_wrapper::isLeftMouseButtonPressed_nocallback() const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
bool Platform_wrapper::isProcessingAppQuitEvent() const
{
    if (m_isProcessingAppQuitEventCallback) {
        const void *thisPtr = this;
        return m_isProcessingAppQuitEventCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
bool Platform_wrapper::isProcessingAppQuitEvent_nocallback() const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
bool Platform_wrapper::isQt() const
{
    return ::KDDockWidgets::Platform::isQt();
}
bool Platform_wrapper::isQtQuick() const
{
    return ::KDDockWidgets::Platform::isQtQuick();
}
bool Platform_wrapper::isQtWidgets() const
{
    return ::KDDockWidgets::Platform::isQtWidgets();
}
const char *Platform_wrapper::name() const
{
    if (m_nameCallback) {
        const void *thisPtr = this;
        return m_nameCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
const char *Platform_wrapper::name_nocallback() const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
QString Platform_wrapper::organizationName() const
{
    if (m_organizationNameCallback) {
        const void *thisPtr = this;
        return *m_organizationNameCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
QString Platform_wrapper::organizationName_nocallback() const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
void Platform_wrapper::restoreMouseCursor()
{
    if (m_restoreMouseCursorCallback) {
        const void *thisPtr = this;
        m_restoreMouseCursorCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void Platform_wrapper::restoreMouseCursor_nocallback()
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
int Platform_wrapper::screenNumberFor(KDDockWidgets::View *arg__1) const
{
    if (m_screenNumberForCallback) {
        const void *thisPtr = this;
        return m_screenNumberForCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
int Platform_wrapper::screenNumberFor_nocallback(KDDockWidgets::View *arg__1) const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
QSize Platform_wrapper::screenSizeFor(KDDockWidgets::View *arg__1) const
{
    if (m_screenSizeForCallback) {
        const void *thisPtr = this;
        return *m_screenSizeForCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
QSize Platform_wrapper::screenSizeFor_nocallback(KDDockWidgets::View *arg__1) const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
void Platform_wrapper::sendEvent(KDDockWidgets::View *arg__1, QEvent *arg__2) const
{
    if (m_sendEventCallback) {
        const void *thisPtr = this;
        m_sendEventCallback(const_cast<void *>(thisPtr), arg__1, arg__2);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void Platform_wrapper::sendEvent_nocallback(KDDockWidgets::View *arg__1, QEvent *arg__2) const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void Platform_wrapper::setMouseCursor(Qt::CursorShape arg__1)
{
    if (m_setMouseCursorCallback) {
        const void *thisPtr = this;
        m_setMouseCursorCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void Platform_wrapper::setMouseCursor_nocallback(Qt::CursorShape arg__1)
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
int Platform_wrapper::startDragDistance() const
{
    return ::KDDockWidgets::Platform::startDragDistance();
}
int Platform_wrapper::startDragDistance_impl() const
{
    if (m_startDragDistance_implCallback) {
        const void *thisPtr = this;
        return m_startDragDistance_implCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Platform::startDragDistance_impl();
    }
}
int Platform_wrapper::startDragDistance_impl_nocallback() const
{
    return ::KDDockWidgets::Platform::startDragDistance_impl();
}
KDDockWidgets::View *
Platform_wrapper::tests_createFocusableView(KDDockWidgets::CreateViewOptions arg__1,
                                            KDDockWidgets::View *parent)
{
    if (m_tests_createFocusableViewCallback) {
        const void *thisPtr = this;
        return m_tests_createFocusableViewCallback(const_cast<void *>(thisPtr), &arg__1, parent);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
KDDockWidgets::View *
Platform_wrapper::tests_createFocusableView_nocallback(KDDockWidgets::CreateViewOptions arg__1,
                                                       KDDockWidgets::View *parent)
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
KDDockWidgets::View *Platform_wrapper::tests_createNonClosableView(KDDockWidgets::View *parent)
{
    if (m_tests_createNonClosableViewCallback) {
        const void *thisPtr = this;
        return m_tests_createNonClosableViewCallback(const_cast<void *>(thisPtr), parent);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
KDDockWidgets::View *
Platform_wrapper::tests_createNonClosableView_nocallback(KDDockWidgets::View *parent)
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
KDDockWidgets::View *Platform_wrapper::tests_createView(KDDockWidgets::CreateViewOptions arg__1,
                                                        KDDockWidgets::View *parent)
{
    if (m_tests_createViewCallback) {
        const void *thisPtr = this;
        return m_tests_createViewCallback(const_cast<void *>(thisPtr), &arg__1, parent);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
KDDockWidgets::View *
Platform_wrapper::tests_createView_nocallback(KDDockWidgets::CreateViewOptions arg__1,
                                              KDDockWidgets::View *parent)
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
void Platform_wrapper::tests_deinitPlatform()
{
    ::KDDockWidgets::Platform::tests_deinitPlatform();
}
void Platform_wrapper::tests_deinitPlatform_impl()
{
    if (m_tests_deinitPlatform_implCallback) {
        const void *thisPtr = this;
        m_tests_deinitPlatform_implCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Platform::tests_deinitPlatform_impl();
    }
}
void Platform_wrapper::tests_deinitPlatform_impl_nocallback()
{
    ::KDDockWidgets::Platform::tests_deinitPlatform_impl();
}
void Platform_wrapper::tests_initPlatform_impl()
{
    if (m_tests_initPlatform_implCallback) {
        const void *thisPtr = this;
        m_tests_initPlatform_implCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Platform::tests_initPlatform_impl();
    }
}
void Platform_wrapper::tests_initPlatform_impl_nocallback()
{
    ::KDDockWidgets::Platform::tests_initPlatform_impl();
}
void Platform_wrapper::tests_wait(int ms)
{
    if (m_tests_waitCallback) {
        const void *thisPtr = this;
        m_tests_waitCallback(const_cast<void *>(thisPtr), ms);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void Platform_wrapper::tests_wait_nocallback(int ms)
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
bool Platform_wrapper::tests_waitForDeleted(KDDockWidgets::View *arg__1, int timeout) const
{
    if (m_tests_waitForDeletedCallback) {
        const void *thisPtr = this;
        return m_tests_waitForDeletedCallback(const_cast<void *>(thisPtr), arg__1, timeout);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
bool Platform_wrapper::tests_waitForDeleted_nocallback(KDDockWidgets::View *arg__1,
                                                       int timeout) const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
bool Platform_wrapper::tests_waitForDeleted(QObject *arg__1, int timeout) const
{
    if (m_tests_waitForDeleted_2Callback) {
        const void *thisPtr = this;
        return m_tests_waitForDeleted_2Callback(const_cast<void *>(thisPtr), arg__1, timeout);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
bool Platform_wrapper::tests_waitForDeleted_nocallback(QObject *arg__1, int timeout) const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
bool Platform_wrapper::tests_waitForEvent(KDDockWidgets::View *arg__1, QEvent::Type type,
                                          int timeout) const
{
    if (m_tests_waitForEventCallback) {
        const void *thisPtr = this;
        return m_tests_waitForEventCallback(const_cast<void *>(thisPtr), arg__1, type, timeout);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
bool Platform_wrapper::tests_waitForEvent_nocallback(KDDockWidgets::View *arg__1, QEvent::Type type,
                                                     int timeout) const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
bool Platform_wrapper::tests_waitForEvent(QObject *w, QEvent::Type type, int timeout) const
{
    if (m_tests_waitForEvent_2Callback) {
        const void *thisPtr = this;
        return m_tests_waitForEvent_2Callback(const_cast<void *>(thisPtr), w, type, timeout);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
bool Platform_wrapper::tests_waitForEvent_nocallback(QObject *w, QEvent::Type type,
                                                     int timeout) const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
bool Platform_wrapper::tests_waitForResize(KDDockWidgets::Controller *arg__1, int timeout) const
{
    if (m_tests_waitForResizeCallback) {
        const void *thisPtr = this;
        return m_tests_waitForResizeCallback(const_cast<void *>(thisPtr), arg__1, timeout);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
bool Platform_wrapper::tests_waitForResize_nocallback(KDDockWidgets::Controller *arg__1,
                                                      int timeout) const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
bool Platform_wrapper::tests_waitForResize(KDDockWidgets::View *arg__1, int timeout) const
{
    if (m_tests_waitForResize_2Callback) {
        const void *thisPtr = this;
        return m_tests_waitForResize_2Callback(const_cast<void *>(thisPtr), arg__1, timeout);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
bool Platform_wrapper::tests_waitForResize_nocallback(KDDockWidgets::View *arg__1,
                                                      int timeout) const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
void Platform_wrapper::ungrabMouse()
{
    if (m_ungrabMouseCallback) {
        const void *thisPtr = this;
        m_ungrabMouseCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void Platform_wrapper::ungrabMouse_nocallback()
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void Platform_wrapper::uninstallMessageHandler()
{
    if (m_uninstallMessageHandlerCallback) {
        const void *thisPtr = this;
        m_uninstallMessageHandlerCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void Platform_wrapper::uninstallMessageHandler_nocallback()
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
bool Platform_wrapper::usesFallbackMouseGrabber() const
{
    if (m_usesFallbackMouseGrabberCallback) {
        const void *thisPtr = this;
        return m_usesFallbackMouseGrabberCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
bool Platform_wrapper::usesFallbackMouseGrabber_nocallback() const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
Platform_wrapper::~Platform_wrapper()
{
}

}
static KDDockWidgets::Platform *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::Platform *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::Platform_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__Platform_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper *>(cppObj);
}
void *c_KDDockWidgets__Platform__constructor()
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::Platform_wrapper();
    return reinterpret_cast<void *>(ptr);
}
// applicationName() const
void *c_KDDockWidgets__Platform__applicationName(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QString> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->applicationName_nocallback();
        } else {
            return targetPtr->applicationName();
        }
    }() };
}
// createDefaultViewFactory()
void *c_KDDockWidgets__Platform__createDefaultViewFactory(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->createDefaultViewFactory_nocallback();
        } else {
            return targetPtr->createDefaultViewFactory();
        }
    }();
}
// createView(KDDockWidgets::Controller * arg__1, KDDockWidgets::View * parent) const
void *c_KDDockWidgets__Platform__createView_Controller_View(void *thisObj, void *arg__1_,
                                                            void *parent_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controller *>(arg__1_);
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->createView_nocallback(arg__1, parent);
        } else {
            return targetPtr->createView(arg__1, parent);
        }
    }();
}
// dumpManagedBacktrace()
void c_KDDockWidgets__Platform__dumpManagedBacktrace(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->dumpManagedBacktrace_nocallback();
        } else {
            return targetPtr->dumpManagedBacktrace();
        }
    }();
}
// hasActivePopup() const
bool c_KDDockWidgets__Platform__hasActivePopup(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->hasActivePopup_nocallback();
        } else {
            return targetPtr->hasActivePopup();
        }
    }();
}
// inDisallowedDragView(QPoint globalPos) const
bool c_KDDockWidgets__Platform__inDisallowedDragView_QPoint(void *thisObj, void *globalPos_)
{
    assert(globalPos_);
    auto &globalPos = *reinterpret_cast<QPoint *>(globalPos_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->inDisallowedDragView_nocallback(globalPos);
        } else {
            return targetPtr->inDisallowedDragView(globalPos);
        }
    }();
}
// installMessageHandler()
void c_KDDockWidgets__Platform__installMessageHandler(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->installMessageHandler_nocallback();
        } else {
            return targetPtr->installMessageHandler();
        }
    }();
}
// instance()
void *c_static_KDDockWidgets__Platform__instance()
{
    return KDDockWidgetsBindings_wrappersNS::Platform_wrapper::instance();
}
// isLeftMouseButtonPressed() const
bool c_KDDockWidgets__Platform__isLeftMouseButtonPressed(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->isLeftMouseButtonPressed_nocallback();
        } else {
            return targetPtr->isLeftMouseButtonPressed();
        }
    }();
}
// isProcessingAppQuitEvent() const
bool c_KDDockWidgets__Platform__isProcessingAppQuitEvent(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->isProcessingAppQuitEvent_nocallback();
        } else {
            return targetPtr->isProcessingAppQuitEvent();
        }
    }();
}
// isQt() const
bool c_KDDockWidgets__Platform__isQt(void *thisObj)
{
    return fromPtr(thisObj)->isQt();
}
// isQtQuick() const
bool c_KDDockWidgets__Platform__isQtQuick(void *thisObj)
{
    return fromPtr(thisObj)->isQtQuick();
}
// isQtWidgets() const
bool c_KDDockWidgets__Platform__isQtWidgets(void *thisObj)
{
    return fromPtr(thisObj)->isQtWidgets();
}
// name() const
const char *c_KDDockWidgets__Platform__name(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->name_nocallback();
        } else {
            return targetPtr->name();
        }
    }();
}
// organizationName() const
void *c_KDDockWidgets__Platform__organizationName(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QString> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->organizationName_nocallback();
        } else {
            return targetPtr->organizationName();
        }
    }() };
}
// restoreMouseCursor()
void c_KDDockWidgets__Platform__restoreMouseCursor(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->restoreMouseCursor_nocallback();
        } else {
            return targetPtr->restoreMouseCursor();
        }
    }();
}
// screenNumberFor(KDDockWidgets::View * arg__1) const
int c_KDDockWidgets__Platform__screenNumberFor_View(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::View *>(arg__1_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->screenNumberFor_nocallback(arg__1);
        } else {
            return targetPtr->screenNumberFor(arg__1);
        }
    }();
}
// screenSizeFor(KDDockWidgets::View * arg__1) const
void *c_KDDockWidgets__Platform__screenSizeFor_View(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::View *>(arg__1_);
    return new Dartagnan::ValueWrapper<QSize> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->screenSizeFor_nocallback(arg__1);
        } else {
            return targetPtr->screenSizeFor(arg__1);
        }
    }() };
}
// sendEvent(KDDockWidgets::View * arg__1, QEvent * arg__2) const
void c_KDDockWidgets__Platform__sendEvent_View_QEvent(void *thisObj, void *arg__1_, void *arg__2_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::View *>(arg__1_);
    auto arg__2 = reinterpret_cast<QEvent *>(arg__2_);
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->sendEvent_nocallback(arg__1, arg__2);
        } else {
            return targetPtr->sendEvent(arg__1, arg__2);
        }
    }();
}
// setMouseCursor(Qt::CursorShape arg__1)
void c_KDDockWidgets__Platform__setMouseCursor_CursorShape(void *thisObj, int arg__1)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setMouseCursor_nocallback(static_cast<Qt::CursorShape>(arg__1));
        } else {
            return targetPtr->setMouseCursor(static_cast<Qt::CursorShape>(arg__1));
        }
    }();
}
// startDragDistance() const
int c_KDDockWidgets__Platform__startDragDistance(void *thisObj)
{
    return fromPtr(thisObj)->startDragDistance();
}
// startDragDistance_impl() const
int c_KDDockWidgets__Platform__startDragDistance_impl(void *thisObj)
{
    return fromWrapperPtr(thisObj)->startDragDistance_impl_nocallback();
}
// tests_createFocusableView(KDDockWidgets::CreateViewOptions arg__1, KDDockWidgets::View * parent)
void *c_KDDockWidgets__Platform__tests_createFocusableView_CreateViewOptions_View(void *thisObj,
                                                                                  void *arg__1_,
                                                                                  void *parent_)
{
    assert(arg__1_);
    auto &arg__1 = *reinterpret_cast<KDDockWidgets::CreateViewOptions *>(arg__1_);
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->tests_createFocusableView_nocallback(arg__1, parent);
        } else {
            return targetPtr->tests_createFocusableView(arg__1, parent);
        }
    }();
}
// tests_createNonClosableView(KDDockWidgets::View * parent)
void *c_KDDockWidgets__Platform__tests_createNonClosableView_View(void *thisObj, void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->tests_createNonClosableView_nocallback(parent);
        } else {
            return targetPtr->tests_createNonClosableView(parent);
        }
    }();
}
// tests_createView(KDDockWidgets::CreateViewOptions arg__1, KDDockWidgets::View * parent)
void *c_KDDockWidgets__Platform__tests_createView_CreateViewOptions_View(void *thisObj,
                                                                         void *arg__1_,
                                                                         void *parent_)
{
    assert(arg__1_);
    auto &arg__1 = *reinterpret_cast<KDDockWidgets::CreateViewOptions *>(arg__1_);
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->tests_createView_nocallback(arg__1, parent);
        } else {
            return targetPtr->tests_createView(arg__1, parent);
        }
    }();
}
// tests_deinitPlatform()
void c_static_KDDockWidgets__Platform__tests_deinitPlatform()
{
    KDDockWidgetsBindings_wrappersNS::Platform_wrapper::tests_deinitPlatform();
}
// tests_deinitPlatform_impl()
void c_KDDockWidgets__Platform__tests_deinitPlatform_impl(void *thisObj)
{
    fromWrapperPtr(thisObj)->tests_deinitPlatform_impl_nocallback();
}
// tests_initPlatform_impl()
void c_KDDockWidgets__Platform__tests_initPlatform_impl(void *thisObj)
{
    fromWrapperPtr(thisObj)->tests_initPlatform_impl_nocallback();
}
// tests_wait(int ms)
void c_KDDockWidgets__Platform__tests_wait_int(void *thisObj, int ms)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->tests_wait_nocallback(ms);
        } else {
            return targetPtr->tests_wait(ms);
        }
    }();
}
// tests_waitForDeleted(KDDockWidgets::View * arg__1, int timeout) const
bool c_KDDockWidgets__Platform__tests_waitForDeleted_View_int(void *thisObj, void *arg__1_,
                                                              int timeout)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::View *>(arg__1_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->tests_waitForDeleted_nocallback(arg__1, timeout);
        } else {
            return targetPtr->tests_waitForDeleted(arg__1, timeout);
        }
    }();
}
// tests_waitForDeleted(QObject * arg__1, int timeout) const
bool c_KDDockWidgets__Platform__tests_waitForDeleted_QObject_int(void *thisObj, void *arg__1_,
                                                                 int timeout)
{
    auto arg__1 = reinterpret_cast<QObject *>(arg__1_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->tests_waitForDeleted_nocallback(arg__1, timeout);
        } else {
            return targetPtr->tests_waitForDeleted(arg__1, timeout);
        }
    }();
}
// tests_waitForEvent(KDDockWidgets::View * arg__1, QEvent::Type type, int timeout) const
bool c_KDDockWidgets__Platform__tests_waitForEvent_View_Type_int(void *thisObj, void *arg__1_,
                                                                 int type, int timeout)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::View *>(arg__1_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->tests_waitForEvent_nocallback(
                arg__1, static_cast<QEvent::Type>(type), timeout);
        } else {
            return targetPtr->tests_waitForEvent(arg__1, static_cast<QEvent::Type>(type), timeout);
        }
    }();
}
// tests_waitForEvent(QObject * w, QEvent::Type type, int timeout) const
bool c_KDDockWidgets__Platform__tests_waitForEvent_QObject_Type_int(void *thisObj, void *w_,
                                                                    int type, int timeout)
{
    auto w = reinterpret_cast<QObject *>(w_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->tests_waitForEvent_nocallback(w, static_cast<QEvent::Type>(type),
                                                             timeout);
        } else {
            return targetPtr->tests_waitForEvent(w, static_cast<QEvent::Type>(type), timeout);
        }
    }();
}
// tests_waitForResize(KDDockWidgets::Controller * arg__1, int timeout) const
bool c_KDDockWidgets__Platform__tests_waitForResize_Controller_int(void *thisObj, void *arg__1_,
                                                                   int timeout)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controller *>(arg__1_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->tests_waitForResize_nocallback(arg__1, timeout);
        } else {
            return targetPtr->tests_waitForResize(arg__1, timeout);
        }
    }();
}
// tests_waitForResize(KDDockWidgets::View * arg__1, int timeout) const
bool c_KDDockWidgets__Platform__tests_waitForResize_View_int(void *thisObj, void *arg__1_,
                                                             int timeout)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::View *>(arg__1_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->tests_waitForResize_nocallback(arg__1, timeout);
        } else {
            return targetPtr->tests_waitForResize(arg__1, timeout);
        }
    }();
}
// ungrabMouse()
void c_KDDockWidgets__Platform__ungrabMouse(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->ungrabMouse_nocallback();
        } else {
            return targetPtr->ungrabMouse();
        }
    }();
}
// uninstallMessageHandler()
void c_KDDockWidgets__Platform__uninstallMessageHandler(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->uninstallMessageHandler_nocallback();
        } else {
            return targetPtr->uninstallMessageHandler();
        }
    }();
}
// usesFallbackMouseGrabber() const
bool c_KDDockWidgets__Platform__usesFallbackMouseGrabber(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->usesFallbackMouseGrabber_nocallback();
        } else {
            return targetPtr->usesFallbackMouseGrabber();
        }
    }();
}
void c_KDDockWidgets__Platform__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
int c_KDDockWidgets__Platform___get_m_numWarningsEmitted(void *thisObj)
{
    return fromPtr(thisObj)->m_numWarningsEmitted;
}
void c_KDDockWidgets__Platform___set_m_numWarningsEmitted_int(void *thisObj,
                                                              int m_numWarningsEmitted_)
{
    fromPtr(thisObj)->m_numWarningsEmitted = m_numWarningsEmitted_;
}
void c_KDDockWidgets__Platform__registerVirtualMethodCallback(void *ptr, void *callback,
                                                              int methodId)
{
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 728:
        wrapper->m_applicationNameCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_applicationName>(callback);
        break;
    case 729:
        wrapper->m_createDefaultViewFactoryCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_createDefaultViewFactory>(
            callback);
        break;
    case 730:
        wrapper->m_createViewCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_createView>(callback);
        break;
    case 731:
        wrapper->m_dumpManagedBacktraceCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_dumpManagedBacktrace>(
            callback);
        break;
    case 733:
        wrapper->m_hasActivePopupCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_hasActivePopup>(callback);
        break;
    case 734:
        wrapper->m_inDisallowedDragViewCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_inDisallowedDragView>(
            callback);
        break;
    case 735:
        wrapper->m_installMessageHandlerCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_installMessageHandler>(
            callback);
        break;
    case 737:
        wrapper->m_isLeftMouseButtonPressedCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_isLeftMouseButtonPressed>(
            callback);
        break;
    case 738:
        wrapper->m_isProcessingAppQuitEventCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_isProcessingAppQuitEvent>(
            callback);
        break;
    case 742:
        wrapper->m_nameCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_name>(
                callback);
        break;
    case 743:
        wrapper->m_organizationNameCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_organizationName>(
            callback);
        break;
    case 744:
        wrapper->m_restoreMouseCursorCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_restoreMouseCursor>(
            callback);
        break;
    case 745:
        wrapper->m_screenNumberForCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_screenNumberFor>(callback);
        break;
    case 746:
        wrapper->m_screenSizeForCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_screenSizeFor>(callback);
        break;
    case 747:
        wrapper->m_sendEventCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_sendEvent>(callback);
        break;
    case 748:
        wrapper->m_setMouseCursorCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_setMouseCursor>(callback);
        break;
    case 750:
        wrapper->m_startDragDistance_implCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_startDragDistance_impl>(
            callback);
        break;
    case 751:
        wrapper->m_tests_createFocusableViewCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_tests_createFocusableView>(
            callback);
        break;
    case 752:
        wrapper->m_tests_createNonClosableViewCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Platform_wrapper::
                                 Callback_tests_createNonClosableView>(callback);
        break;
    case 753:
        wrapper->m_tests_createViewCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_tests_createView>(
            callback);
        break;
    case 755:
        wrapper->m_tests_deinitPlatform_implCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_tests_deinitPlatform_impl>(
            callback);
        break;
    case 757:
        wrapper->m_tests_initPlatform_implCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_tests_initPlatform_impl>(
            callback);
        break;
    case 758:
        wrapper->m_tests_waitCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_tests_wait>(callback);
        break;
    case 759:
        wrapper->m_tests_waitForDeletedCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_tests_waitForDeleted>(
            callback);
        break;
    case 760:
        wrapper->m_tests_waitForDeleted_2Callback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_tests_waitForDeleted_2>(
            callback);
        break;
    case 761:
        wrapper->m_tests_waitForEventCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_tests_waitForEvent>(
            callback);
        break;
    case 762:
        wrapper->m_tests_waitForEvent_2Callback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_tests_waitForEvent_2>(
            callback);
        break;
    case 763:
        wrapper->m_tests_waitForResizeCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_tests_waitForResize>(
            callback);
        break;
    case 764:
        wrapper->m_tests_waitForResize_2Callback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_tests_waitForResize_2>(
            callback);
        break;
    case 765:
        wrapper->m_ungrabMouseCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_ungrabMouse>(callback);
        break;
    case 766:
        wrapper->m_uninstallMessageHandlerCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_uninstallMessageHandler>(
            callback);
        break;
    case 767:
        wrapper->m_usesFallbackMouseGrabberCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Platform_wrapper::Callback_usesFallbackMouseGrabber>(
            callback);
        break;
    }
}
}

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <Platform_flutter.h>
#include <ViewFactory.h>
#include <View.h>
#include <qsize.h>
#include <Controller.h>
#include <qpoint.h>
#include <Platform.h>
#include <qcoreevent.h>
#include <qobject.h>
#include <qstring.h>

namespace KDDockWidgetsBindings_wrappersNS {
class Platform_flutter_wrapper : public ::KDDockWidgets::Platform_flutter
{
public:
    ~Platform_flutter_wrapper();
    Platform_flutter_wrapper();
    virtual QString applicationName() const;
    virtual QString applicationName_nocallback() const;
    virtual KDDockWidgets::ViewFactory *createDefaultViewFactory();
    virtual KDDockWidgets::ViewFactory *createDefaultViewFactory_nocallback();
    virtual KDDockWidgets::View *createView(KDDockWidgets::Controller *controller, KDDockWidgets::View *parent = nullptr) const;
    virtual KDDockWidgets::View *createView_nocallback(KDDockWidgets::Controller *controller, KDDockWidgets::View *parent = nullptr) const;
    virtual bool hasActivePopup() const;
    virtual bool hasActivePopup_nocallback() const;
    virtual bool inDisallowedDragView(QPoint globalPos) const;
    virtual bool inDisallowedDragView_nocallback(QPoint globalPos) const;
    void init();
    virtual void installMessageHandler();
    virtual void installMessageHandler_nocallback();
    virtual bool isLeftMouseButtonPressed() const;
    virtual bool isLeftMouseButtonPressed_nocallback() const;
    virtual bool isProcessingAppQuitEvent() const;
    virtual bool isProcessingAppQuitEvent_nocallback() const;
    virtual const char *name() const;
    virtual const char *name_nocallback() const;
    virtual QString organizationName() const;
    virtual QString organizationName_nocallback() const;
    virtual void restoreMouseCursor();
    virtual void restoreMouseCursor_nocallback();
    virtual int screenNumberFor(KDDockWidgets::View *arg__1) const;
    virtual int screenNumberFor_nocallback(KDDockWidgets::View *arg__1) const;
    virtual QSize screenSizeFor(KDDockWidgets::View *arg__1) const;
    virtual QSize screenSizeFor_nocallback(KDDockWidgets::View *arg__1) const;
    virtual void sendEvent(KDDockWidgets::View *arg__1, QEvent *arg__2) const;
    virtual void sendEvent_nocallback(KDDockWidgets::View *arg__1, QEvent *arg__2) const;
    virtual void setMouseCursor(Qt::CursorShape arg__1);
    virtual void setMouseCursor_nocallback(Qt::CursorShape arg__1);
    virtual KDDockWidgets::View *tests_createFocusableView(KDDockWidgets::CreateViewOptions arg__1, KDDockWidgets::View *parent = nullptr);
    virtual KDDockWidgets::View *tests_createFocusableView_nocallback(KDDockWidgets::CreateViewOptions arg__1, KDDockWidgets::View *parent = nullptr);
    virtual KDDockWidgets::View *tests_createNonClosableView(KDDockWidgets::View *parent = nullptr);
    virtual KDDockWidgets::View *tests_createNonClosableView_nocallback(KDDockWidgets::View *parent = nullptr);
    virtual KDDockWidgets::View *tests_createView(KDDockWidgets::CreateViewOptions arg__1, KDDockWidgets::View *parent = nullptr);
    virtual KDDockWidgets::View *tests_createView_nocallback(KDDockWidgets::CreateViewOptions arg__1, KDDockWidgets::View *parent = nullptr);
    virtual void tests_deinitPlatform_impl();
    virtual void tests_deinitPlatform_impl_nocallback();
    virtual void tests_initPlatform_impl();
    virtual void tests_initPlatform_impl_nocallback();
    virtual void tests_wait(int ms);
    virtual void tests_wait_nocallback(int ms);
    virtual bool tests_waitForDeleted(KDDockWidgets::View *arg__1, int timeout) const;
    virtual bool tests_waitForDeleted_nocallback(KDDockWidgets::View *arg__1, int timeout) const;
    virtual bool tests_waitForDeleted(QObject *arg__1, int timeout) const;
    virtual bool tests_waitForDeleted_nocallback(QObject *arg__1, int timeout) const;
    virtual bool tests_waitForEvent(KDDockWidgets::View *arg__1, QEvent::Type type, int timeout) const;
    virtual bool tests_waitForEvent_nocallback(KDDockWidgets::View *arg__1, QEvent::Type type, int timeout) const;
    virtual bool tests_waitForEvent(QObject *w, QEvent::Type type, int timeout) const;
    virtual bool tests_waitForEvent_nocallback(QObject *w, QEvent::Type type, int timeout) const;
    virtual bool tests_waitForResize(KDDockWidgets::Controller *arg__1, int timeout) const;
    virtual bool tests_waitForResize_nocallback(KDDockWidgets::Controller *arg__1, int timeout) const;
    virtual bool tests_waitForResize(KDDockWidgets::View *arg__1, int timeout) const;
    virtual bool tests_waitForResize_nocallback(KDDockWidgets::View *arg__1, int timeout) const;
    virtual void ungrabMouse();
    virtual void ungrabMouse_nocallback();
    virtual void uninstallMessageHandler();
    virtual void uninstallMessageHandler_nocallback();
    virtual bool usesFallbackMouseGrabber() const;
    virtual bool usesFallbackMouseGrabber_nocallback() const;
    typedef QString *(*Callback_applicationName)(void *);
    Callback_applicationName m_applicationNameCallback = nullptr;
    typedef KDDockWidgets::ViewFactory *(*Callback_createDefaultViewFactory)(void *);
    Callback_createDefaultViewFactory m_createDefaultViewFactoryCallback = nullptr;
    typedef KDDockWidgets::View *(*Callback_createView)(void *, KDDockWidgets::Controller *controller, KDDockWidgets::View *parent);
    Callback_createView m_createViewCallback = nullptr;
    typedef bool (*Callback_hasActivePopup)(void *);
    Callback_hasActivePopup m_hasActivePopupCallback = nullptr;
    typedef bool (*Callback_inDisallowedDragView)(void *, QPoint globalPos);
    Callback_inDisallowedDragView m_inDisallowedDragViewCallback = nullptr;
    typedef void (*Callback_installMessageHandler)(void *);
    Callback_installMessageHandler m_installMessageHandlerCallback = nullptr;
    typedef bool (*Callback_isLeftMouseButtonPressed)(void *);
    Callback_isLeftMouseButtonPressed m_isLeftMouseButtonPressedCallback = nullptr;
    typedef bool (*Callback_isProcessingAppQuitEvent)(void *);
    Callback_isProcessingAppQuitEvent m_isProcessingAppQuitEventCallback = nullptr;
    typedef const char *(*Callback_name)(void *);
    Callback_name m_nameCallback = nullptr;
    typedef QString *(*Callback_organizationName)(void *);
    Callback_organizationName m_organizationNameCallback = nullptr;
    typedef void (*Callback_restoreMouseCursor)(void *);
    Callback_restoreMouseCursor m_restoreMouseCursorCallback = nullptr;
    typedef int (*Callback_screenNumberFor)(void *, KDDockWidgets::View *arg__1);
    Callback_screenNumberFor m_screenNumberForCallback = nullptr;
    typedef QSize *(*Callback_screenSizeFor)(void *, KDDockWidgets::View *arg__1);
    Callback_screenSizeFor m_screenSizeForCallback = nullptr;
    typedef void (*Callback_sendEvent)(void *, KDDockWidgets::View *arg__1, QEvent *arg__2);
    Callback_sendEvent m_sendEventCallback = nullptr;
    typedef void (*Callback_setMouseCursor)(void *, Qt::CursorShape arg__1);
    Callback_setMouseCursor m_setMouseCursorCallback = nullptr;
    typedef KDDockWidgets::View *(*Callback_tests_createFocusableView)(void *, KDDockWidgets::CreateViewOptions arg__1, KDDockWidgets::View *parent);
    Callback_tests_createFocusableView m_tests_createFocusableViewCallback = nullptr;
    typedef KDDockWidgets::View *(*Callback_tests_createNonClosableView)(void *, KDDockWidgets::View *parent);
    Callback_tests_createNonClosableView m_tests_createNonClosableViewCallback = nullptr;
    typedef KDDockWidgets::View *(*Callback_tests_createView)(void *, KDDockWidgets::CreateViewOptions arg__1, KDDockWidgets::View *parent);
    Callback_tests_createView m_tests_createViewCallback = nullptr;
    typedef void (*Callback_tests_deinitPlatform_impl)(void *);
    Callback_tests_deinitPlatform_impl m_tests_deinitPlatform_implCallback = nullptr;
    typedef void (*Callback_tests_initPlatform_impl)(void *);
    Callback_tests_initPlatform_impl m_tests_initPlatform_implCallback = nullptr;
    typedef void (*Callback_tests_wait)(void *, int ms);
    Callback_tests_wait m_tests_waitCallback = nullptr;
    typedef bool (*Callback_tests_waitForDeleted)(void *, KDDockWidgets::View *arg__1, int timeout);
    Callback_tests_waitForDeleted m_tests_waitForDeletedCallback = nullptr;
    typedef bool (*Callback_tests_waitForDeleted_2)(void *, QObject *arg__1, int timeout);
    Callback_tests_waitForDeleted_2 m_tests_waitForDeleted_2Callback = nullptr;
    typedef bool (*Callback_tests_waitForEvent)(void *, KDDockWidgets::View *arg__1, QEvent::Type type, int timeout);
    Callback_tests_waitForEvent m_tests_waitForEventCallback = nullptr;
    typedef bool (*Callback_tests_waitForEvent_2)(void *, QObject *w, QEvent::Type type, int timeout);
    Callback_tests_waitForEvent_2 m_tests_waitForEvent_2Callback = nullptr;
    typedef bool (*Callback_tests_waitForResize)(void *, KDDockWidgets::Controller *arg__1, int timeout);
    Callback_tests_waitForResize m_tests_waitForResizeCallback = nullptr;
    typedef bool (*Callback_tests_waitForResize_2)(void *, KDDockWidgets::View *arg__1, int timeout);
    Callback_tests_waitForResize_2 m_tests_waitForResize_2Callback = nullptr;
    typedef void (*Callback_ungrabMouse)(void *);
    Callback_ungrabMouse m_ungrabMouseCallback = nullptr;
    typedef void (*Callback_uninstallMessageHandler)(void *);
    Callback_uninstallMessageHandler m_uninstallMessageHandlerCallback = nullptr;
    typedef bool (*Callback_usesFallbackMouseGrabber)(void *);
    Callback_usesFallbackMouseGrabber m_usesFallbackMouseGrabberCallback = nullptr;
};
}
extern "C" {
// KDDockWidgets::Platform_flutter::Platform_flutter()
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Platform_flutter__constructor();
// KDDockWidgets::Platform_flutter::applicationName() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Platform_flutter__applicationName(void *thisObj);
// KDDockWidgets::Platform_flutter::createDefaultViewFactory()
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Platform_flutter__createDefaultViewFactory(void *thisObj);
// KDDockWidgets::Platform_flutter::createView(KDDockWidgets::Controller * controller, KDDockWidgets::View * parent) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Platform_flutter__createView_Controller_View(void *thisObj, void *controller_, void *parent_);
// KDDockWidgets::Platform_flutter::hasActivePopup() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform_flutter__hasActivePopup(void *thisObj);
// KDDockWidgets::Platform_flutter::inDisallowedDragView(QPoint globalPos) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform_flutter__inDisallowedDragView_QPoint(void *thisObj, void *globalPos_);
// KDDockWidgets::Platform_flutter::init()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform_flutter__init(void *thisObj);
// KDDockWidgets::Platform_flutter::installMessageHandler()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform_flutter__installMessageHandler(void *thisObj);
// KDDockWidgets::Platform_flutter::isLeftMouseButtonPressed() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform_flutter__isLeftMouseButtonPressed(void *thisObj);
// KDDockWidgets::Platform_flutter::isProcessingAppQuitEvent() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform_flutter__isProcessingAppQuitEvent(void *thisObj);
// KDDockWidgets::Platform_flutter::name() const
KDDockWidgetsBindings_EXPORT const char *c_KDDockWidgets__Platform_flutter__name(void *thisObj);
// KDDockWidgets::Platform_flutter::organizationName() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Platform_flutter__organizationName(void *thisObj);
// KDDockWidgets::Platform_flutter::restoreMouseCursor()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform_flutter__restoreMouseCursor(void *thisObj);
// KDDockWidgets::Platform_flutter::screenNumberFor(KDDockWidgets::View * arg__1) const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Platform_flutter__screenNumberFor_View(void *thisObj, void *arg__1_);
// KDDockWidgets::Platform_flutter::screenSizeFor(KDDockWidgets::View * arg__1) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Platform_flutter__screenSizeFor_View(void *thisObj, void *arg__1_);
// KDDockWidgets::Platform_flutter::sendEvent(KDDockWidgets::View * arg__1, QEvent * arg__2) const
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform_flutter__sendEvent_View_QEvent(void *thisObj, void *arg__1_, void *arg__2_);
// KDDockWidgets::Platform_flutter::setMouseCursor(Qt::CursorShape arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform_flutter__setMouseCursor_CursorShape(void *thisObj, int arg__1);
// KDDockWidgets::Platform_flutter::tests_createFocusableView(KDDockWidgets::CreateViewOptions arg__1, KDDockWidgets::View * parent)
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Platform_flutter__tests_createFocusableView_CreateViewOptions_View(void *thisObj, void *arg__1_, void *parent_);
// KDDockWidgets::Platform_flutter::tests_createNonClosableView(KDDockWidgets::View * parent)
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Platform_flutter__tests_createNonClosableView_View(void *thisObj, void *parent_);
// KDDockWidgets::Platform_flutter::tests_createView(KDDockWidgets::CreateViewOptions arg__1, KDDockWidgets::View * parent)
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Platform_flutter__tests_createView_CreateViewOptions_View(void *thisObj, void *arg__1_, void *parent_);
// KDDockWidgets::Platform_flutter::tests_deinitPlatform_impl()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform_flutter__tests_deinitPlatform_impl(void *thisObj);
// KDDockWidgets::Platform_flutter::tests_initPlatform_impl()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform_flutter__tests_initPlatform_impl(void *thisObj);
// KDDockWidgets::Platform_flutter::tests_wait(int ms)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform_flutter__tests_wait_int(void *thisObj, int ms);
// KDDockWidgets::Platform_flutter::tests_waitForDeleted(KDDockWidgets::View * arg__1, int timeout) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform_flutter__tests_waitForDeleted_View_int(void *thisObj, void *arg__1_, int timeout);
// KDDockWidgets::Platform_flutter::tests_waitForDeleted(QObject * arg__1, int timeout) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform_flutter__tests_waitForDeleted_QObject_int(void *thisObj, void *arg__1_, int timeout);
// KDDockWidgets::Platform_flutter::tests_waitForEvent(KDDockWidgets::View * arg__1, QEvent::Type type, int timeout) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform_flutter__tests_waitForEvent_View_Type_int(void *thisObj, void *arg__1_, int type, int timeout);
// KDDockWidgets::Platform_flutter::tests_waitForEvent(QObject * w, QEvent::Type type, int timeout) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform_flutter__tests_waitForEvent_QObject_Type_int(void *thisObj, void *w_, int type, int timeout);
// KDDockWidgets::Platform_flutter::tests_waitForResize(KDDockWidgets::Controller * arg__1, int timeout) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform_flutter__tests_waitForResize_Controller_int(void *thisObj, void *arg__1_, int timeout);
// KDDockWidgets::Platform_flutter::tests_waitForResize(KDDockWidgets::View * arg__1, int timeout) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform_flutter__tests_waitForResize_View_int(void *thisObj, void *arg__1_, int timeout);
// KDDockWidgets::Platform_flutter::ungrabMouse()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform_flutter__ungrabMouse(void *thisObj);
// KDDockWidgets::Platform_flutter::uninstallMessageHandler()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform_flutter__uninstallMessageHandler(void *thisObj);
// KDDockWidgets::Platform_flutter::usesFallbackMouseGrabber() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform_flutter__usesFallbackMouseGrabber(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform_flutter__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform_flutter__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform_flutter_Finalizer(void *, void *cppObj, void *);
}

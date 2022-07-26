/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// tag=1040
#include "KDDockWidgetsBindings_exports.h"
#include <Platform_flutter.h>
#include <View.h>
#include <qsize.h>
#include <Controller.h>
#include <qpoint.h>
#include <qcoreevent.h>
#include <qobject.h>
#include <qstring.h>

namespace KDDockWidgetsBindings_wrappersNS {
// tag=1017
class Platform_flutter_wrapper : public ::KDDockWidgets::Platform_flutter
{
public:
    ~Platform_flutter_wrapper();
    // tag=1041
    Platform_flutter_wrapper();
    // tag=1041
    virtual QString applicationName() const;
    // tag=1008
    virtual QString applicationName_nocallback() const;
    // tag=1041
    virtual KDDockWidgets::View *createView(KDDockWidgets::Controller *controller, KDDockWidgets::View *parent = nullptr) const;
    // tag=1008
    virtual KDDockWidgets::View *createView_nocallback(KDDockWidgets::Controller *controller, KDDockWidgets::View *parent = nullptr) const;
    // tag=1041
    virtual bool hasActivePopup() const;
    // tag=1008
    virtual bool hasActivePopup_nocallback() const;
    // tag=1041
    virtual bool inDisallowedDragView(QPoint globalPos) const;
    // tag=1008
    virtual bool inDisallowedDragView_nocallback(QPoint globalPos) const;
    // tag=1041
    void init();
    // tag=1041
    virtual void installMessageHandler();
    // tag=1008
    virtual void installMessageHandler_nocallback();
    // tag=1041
    virtual bool isLeftMouseButtonPressed() const;
    // tag=1008
    virtual bool isLeftMouseButtonPressed_nocallback() const;
    // tag=1041
    virtual bool isProcessingAppQuitEvent() const;
    // tag=1008
    virtual bool isProcessingAppQuitEvent_nocallback() const;
    // tag=1041
    virtual const char *name() const;
    // tag=1008
    virtual const char *name_nocallback() const;
    // tag=1041
    virtual QString organizationName() const;
    // tag=1008
    virtual QString organizationName_nocallback() const;
    // tag=1041
    virtual void restoreMouseCursor();
    // tag=1008
    virtual void restoreMouseCursor_nocallback();
    // tag=1041
    virtual int screenNumberFor(KDDockWidgets::View *arg__1) const;
    // tag=1008
    virtual int screenNumberFor_nocallback(KDDockWidgets::View *arg__1) const;
    // tag=1041
    virtual QSize screenSizeFor(KDDockWidgets::View *arg__1) const;
    // tag=1008
    virtual QSize screenSizeFor_nocallback(KDDockWidgets::View *arg__1) const;
    // tag=1041
    virtual void sendEvent(KDDockWidgets::View *arg__1, QEvent *arg__2) const;
    // tag=1008
    virtual void sendEvent_nocallback(KDDockWidgets::View *arg__1, QEvent *arg__2) const;
    // tag=1041
    virtual void setMouseCursor(Qt::CursorShape arg__1);
    // tag=1008
    virtual void setMouseCursor_nocallback(Qt::CursorShape arg__1);
    // tag=1041
    virtual KDDockWidgets::View *tests_createNonClosableView(KDDockWidgets::View *parent = nullptr);
    // tag=1008
    virtual KDDockWidgets::View *tests_createNonClosableView_nocallback(KDDockWidgets::View *parent = nullptr);
    // tag=1041
    virtual void tests_deinitPlatform_impl();
    // tag=1008
    virtual void tests_deinitPlatform_impl_nocallback();
    // tag=1041
    virtual void tests_initPlatform_impl();
    // tag=1008
    virtual void tests_initPlatform_impl_nocallback();
    // tag=1041
    virtual void tests_wait(int ms);
    // tag=1008
    virtual void tests_wait_nocallback(int ms);
    // tag=1041
    virtual bool tests_waitForDeleted(KDDockWidgets::View *arg__1, int timeout) const;
    // tag=1008
    virtual bool tests_waitForDeleted_nocallback(KDDockWidgets::View *arg__1, int timeout) const;
    // tag=1041
    virtual bool tests_waitForDeleted(QObject *arg__1, int timeout) const;
    // tag=1008
    virtual bool tests_waitForDeleted_nocallback(QObject *arg__1, int timeout) const;
    // tag=1041
    virtual bool tests_waitForEvent(KDDockWidgets::View *arg__1, QEvent::Type type, int timeout) const;
    // tag=1008
    virtual bool tests_waitForEvent_nocallback(KDDockWidgets::View *arg__1, QEvent::Type type, int timeout) const;
    // tag=1041
    virtual bool tests_waitForEvent(QObject *w, QEvent::Type type, int timeout) const;
    // tag=1008
    virtual bool tests_waitForEvent_nocallback(QObject *w, QEvent::Type type, int timeout) const;
    // tag=1041
    virtual bool tests_waitForResize(KDDockWidgets::Controller *arg__1, int timeout) const;
    // tag=1008
    virtual bool tests_waitForResize_nocallback(KDDockWidgets::Controller *arg__1, int timeout) const;
    // tag=1041
    virtual bool tests_waitForResize(KDDockWidgets::View *arg__1, int timeout) const;
    // tag=1008
    virtual bool tests_waitForResize_nocallback(KDDockWidgets::View *arg__1, int timeout) const;
    // tag=1041
    virtual void ungrabMouse();
    // tag=1008
    virtual void ungrabMouse_nocallback();
    // tag=1041
    virtual void uninstallMessageHandler();
    // tag=1008
    virtual void uninstallMessageHandler_nocallback();
    // tag=1041
    virtual bool usesFallbackMouseGrabber() const;
    // tag=1008
    virtual bool usesFallbackMouseGrabber_nocallback() const;
    // tag=1042
    typedef QString *(*Callback_applicationName)(void *);
    Callback_applicationName m_applicationNameCallback = nullptr;
    // tag=1042
    typedef KDDockWidgets::View *(*Callback_createView)(void *, KDDockWidgets::Controller *controller, KDDockWidgets::View *parent);
    Callback_createView m_createViewCallback = nullptr;
    // tag=1042
    typedef bool (*Callback_hasActivePopup)(void *);
    Callback_hasActivePopup m_hasActivePopupCallback = nullptr;
    // tag=1042
    typedef bool (*Callback_inDisallowedDragView)(void *, QPoint globalPos);
    Callback_inDisallowedDragView m_inDisallowedDragViewCallback = nullptr;
    // tag=1042
    typedef void (*Callback_installMessageHandler)(void *);
    Callback_installMessageHandler m_installMessageHandlerCallback = nullptr;
    // tag=1042
    typedef bool (*Callback_isLeftMouseButtonPressed)(void *);
    Callback_isLeftMouseButtonPressed m_isLeftMouseButtonPressedCallback = nullptr;
    // tag=1042
    typedef bool (*Callback_isProcessingAppQuitEvent)(void *);
    Callback_isProcessingAppQuitEvent m_isProcessingAppQuitEventCallback = nullptr;
    // tag=1042
    typedef const char *(*Callback_name)(void *);
    Callback_name m_nameCallback = nullptr;
    // tag=1042
    typedef QString *(*Callback_organizationName)(void *);
    Callback_organizationName m_organizationNameCallback = nullptr;
    // tag=1042
    typedef void (*Callback_restoreMouseCursor)(void *);
    Callback_restoreMouseCursor m_restoreMouseCursorCallback = nullptr;
    // tag=1042
    typedef int (*Callback_screenNumberFor)(void *, KDDockWidgets::View *arg__1);
    Callback_screenNumberFor m_screenNumberForCallback = nullptr;
    // tag=1042
    typedef QSize *(*Callback_screenSizeFor)(void *, KDDockWidgets::View *arg__1);
    Callback_screenSizeFor m_screenSizeForCallback = nullptr;
    // tag=1042
    typedef void (*Callback_sendEvent)(void *, KDDockWidgets::View *arg__1, QEvent *arg__2);
    Callback_sendEvent m_sendEventCallback = nullptr;
    // tag=1042
    typedef void (*Callback_setMouseCursor)(void *, Qt::CursorShape arg__1);
    Callback_setMouseCursor m_setMouseCursorCallback = nullptr;
    // tag=1042
    typedef KDDockWidgets::View *(*Callback_tests_createNonClosableView)(void *, KDDockWidgets::View *parent);
    Callback_tests_createNonClosableView m_tests_createNonClosableViewCallback = nullptr;
    // tag=1042
    typedef void (*Callback_tests_deinitPlatform_impl)(void *);
    Callback_tests_deinitPlatform_impl m_tests_deinitPlatform_implCallback = nullptr;
    // tag=1042
    typedef void (*Callback_tests_initPlatform_impl)(void *);
    Callback_tests_initPlatform_impl m_tests_initPlatform_implCallback = nullptr;
    // tag=1042
    typedef void (*Callback_tests_wait)(void *, int ms);
    Callback_tests_wait m_tests_waitCallback = nullptr;
    // tag=1042
    typedef bool (*Callback_tests_waitForDeleted)(void *, KDDockWidgets::View *arg__1, int timeout);
    Callback_tests_waitForDeleted m_tests_waitForDeletedCallback = nullptr;
    // tag=1042
    typedef bool (*Callback_tests_waitForDeleted_2)(void *, QObject *arg__1, int timeout);
    Callback_tests_waitForDeleted_2 m_tests_waitForDeleted_2Callback = nullptr;
    // tag=1042
    typedef bool (*Callback_tests_waitForEvent)(void *, KDDockWidgets::View *arg__1, QEvent::Type type, int timeout);
    Callback_tests_waitForEvent m_tests_waitForEventCallback = nullptr;
    // tag=1042
    typedef bool (*Callback_tests_waitForEvent_2)(void *, QObject *w, QEvent::Type type, int timeout);
    Callback_tests_waitForEvent_2 m_tests_waitForEvent_2Callback = nullptr;
    // tag=1042
    typedef bool (*Callback_tests_waitForResize)(void *, KDDockWidgets::Controller *arg__1, int timeout);
    Callback_tests_waitForResize m_tests_waitForResizeCallback = nullptr;
    // tag=1042
    typedef bool (*Callback_tests_waitForResize_2)(void *, KDDockWidgets::View *arg__1, int timeout);
    Callback_tests_waitForResize_2 m_tests_waitForResize_2Callback = nullptr;
    // tag=1042
    typedef void (*Callback_ungrabMouse)(void *);
    Callback_ungrabMouse m_ungrabMouseCallback = nullptr;
    // tag=1042
    typedef void (*Callback_uninstallMessageHandler)(void *);
    Callback_uninstallMessageHandler m_uninstallMessageHandlerCallback = nullptr;
    // tag=1042
    typedef bool (*Callback_usesFallbackMouseGrabber)(void *);
    Callback_usesFallbackMouseGrabber m_usesFallbackMouseGrabberCallback = nullptr;
};
}
extern "C" {

// tag=1067
//  KDDockWidgets::Platform_flutter::Platform_flutter()
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Platform_flutter__constructor();

// tag=1067
//  KDDockWidgets::Platform_flutter::applicationName() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Platform_flutter__applicationName(void *thisObj);

// tag=1067
//  KDDockWidgets::Platform_flutter::createView(KDDockWidgets::Controller * controller, KDDockWidgets::View * parent) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Platform_flutter__createView_Controller_View(void *thisObj, void *controller_, void *parent_);

// tag=1067
//  KDDockWidgets::Platform_flutter::hasActivePopup() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform_flutter__hasActivePopup(void *thisObj);

// tag=1067
//  KDDockWidgets::Platform_flutter::inDisallowedDragView(QPoint globalPos) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform_flutter__inDisallowedDragView_QPoint(void *thisObj, void *globalPos_);

// tag=1067
//  KDDockWidgets::Platform_flutter::init()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform_flutter__init(void *thisObj);

// tag=1067
//  KDDockWidgets::Platform_flutter::installMessageHandler()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform_flutter__installMessageHandler(void *thisObj);

// tag=1067
//  KDDockWidgets::Platform_flutter::isLeftMouseButtonPressed() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform_flutter__isLeftMouseButtonPressed(void *thisObj);

// tag=1067
//  KDDockWidgets::Platform_flutter::isProcessingAppQuitEvent() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform_flutter__isProcessingAppQuitEvent(void *thisObj);

// tag=1067
//  KDDockWidgets::Platform_flutter::name() const
KDDockWidgetsBindings_EXPORT const char *c_KDDockWidgets__Platform_flutter__name(void *thisObj);

// tag=1067
//  KDDockWidgets::Platform_flutter::organizationName() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Platform_flutter__organizationName(void *thisObj);

// tag=1067
//  KDDockWidgets::Platform_flutter::restoreMouseCursor()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform_flutter__restoreMouseCursor(void *thisObj);

// tag=1067
//  KDDockWidgets::Platform_flutter::screenNumberFor(KDDockWidgets::View * arg__1) const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Platform_flutter__screenNumberFor_View(void *thisObj, void *arg__1_);

// tag=1067
//  KDDockWidgets::Platform_flutter::screenSizeFor(KDDockWidgets::View * arg__1) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Platform_flutter__screenSizeFor_View(void *thisObj, void *arg__1_);

// tag=1067
//  KDDockWidgets::Platform_flutter::sendEvent(KDDockWidgets::View * arg__1, QEvent * arg__2) const
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform_flutter__sendEvent_View_QEvent(void *thisObj, void *arg__1_, void *arg__2_);

// tag=1067
//  KDDockWidgets::Platform_flutter::setMouseCursor(Qt::CursorShape arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform_flutter__setMouseCursor_CursorShape(void *thisObj, int arg__1);

// tag=1067
//  KDDockWidgets::Platform_flutter::tests_createNonClosableView(KDDockWidgets::View * parent)
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Platform_flutter__tests_createNonClosableView_View(void *thisObj, void *parent_);

// tag=1067
//  KDDockWidgets::Platform_flutter::tests_deinitPlatform_impl()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform_flutter__tests_deinitPlatform_impl(void *thisObj);

// tag=1067
//  KDDockWidgets::Platform_flutter::tests_initPlatform_impl()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform_flutter__tests_initPlatform_impl(void *thisObj);

// tag=1067
//  KDDockWidgets::Platform_flutter::tests_wait(int ms)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform_flutter__tests_wait_int(void *thisObj, int ms);

// tag=1067
//  KDDockWidgets::Platform_flutter::tests_waitForDeleted(KDDockWidgets::View * arg__1, int timeout) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform_flutter__tests_waitForDeleted_View_int(void *thisObj, void *arg__1_, int timeout);

// tag=1067
//  KDDockWidgets::Platform_flutter::tests_waitForDeleted(QObject * arg__1, int timeout) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform_flutter__tests_waitForDeleted_QObject_int(void *thisObj, void *arg__1_, int timeout);

// tag=1067
//  KDDockWidgets::Platform_flutter::tests_waitForEvent(KDDockWidgets::View * arg__1, QEvent::Type type, int timeout) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform_flutter__tests_waitForEvent_View_Type_int(void *thisObj, void *arg__1_, int type, int timeout);

// tag=1067
//  KDDockWidgets::Platform_flutter::tests_waitForEvent(QObject * w, QEvent::Type type, int timeout) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform_flutter__tests_waitForEvent_QObject_Type_int(void *thisObj, void *w_, int type, int timeout);

// tag=1067
//  KDDockWidgets::Platform_flutter::tests_waitForResize(KDDockWidgets::Controller * arg__1, int timeout) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform_flutter__tests_waitForResize_Controller_int(void *thisObj, void *arg__1_, int timeout);

// tag=1067
//  KDDockWidgets::Platform_flutter::tests_waitForResize(KDDockWidgets::View * arg__1, int timeout) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform_flutter__tests_waitForResize_View_int(void *thisObj, void *arg__1_, int timeout);

// tag=1067
//  KDDockWidgets::Platform_flutter::ungrabMouse()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform_flutter__ungrabMouse(void *thisObj);

// tag=1067
//  KDDockWidgets::Platform_flutter::uninstallMessageHandler()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform_flutter__uninstallMessageHandler(void *thisObj);

// tag=1067
//  KDDockWidgets::Platform_flutter::usesFallbackMouseGrabber() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform_flutter__usesFallbackMouseGrabber(void *thisObj);

// tag=1066
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform_flutter__destructor(void *thisObj);

// tag=1046
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform_flutter__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
// tag=1047
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform_flutter_Finalizer(void *, void *cppObj, void *);
}

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// tag=1040
#include "KDDockWidgetsBindings_exports.h"
#include <Platform.h>
#include <ViewFactory.h>
#include <View.h>
#include <qsize.h>
#include <qpoint.h>
#include <qstring.h>
#include <qobject.h>

namespace KDDockWidgetsBindings_wrappersNS {
// tag=1017
class Platform_wrapper : public ::KDDockWidgets::Platform
{
public:
    ~Platform_wrapper();
    // tag=1041
    Platform_wrapper();
    // tag=1041
    virtual QString applicationName() const;
    // tag=1008
    virtual QString applicationName_nocallback() const;
    // tag=1041
    virtual KDDockWidgets::ViewFactory *createDefaultViewFactory();
    // tag=1008
    virtual KDDockWidgets::ViewFactory *createDefaultViewFactory_nocallback();
    // tag=1041
    virtual bool hasActivePopup() const;
    // tag=1008
    virtual bool hasActivePopup_nocallback() const;
    // tag=1041
    virtual bool inDisallowedDragView(QPoint globalPos) const;
    // tag=1008
    virtual bool inDisallowedDragView_nocallback(QPoint globalPos) const;
    // tag=1041
    virtual void installMessageHandler();
    // tag=1008
    virtual void installMessageHandler_nocallback();
    // tag=1041
    static KDDockWidgets::Platform *instance();
    // tag=1041
    virtual bool isLeftMouseButtonPressed() const;
    // tag=1008
    virtual bool isLeftMouseButtonPressed_nocallback() const;
    // tag=1041
    virtual bool isProcessingAppQuitEvent() const;
    // tag=1008
    virtual bool isProcessingAppQuitEvent_nocallback() const;
    // tag=1041
    bool isQtQuick() const;
    // tag=1041
    bool isQtWidgets() const;
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
    int startDragDistance() const;
    // tag=1041
    virtual int startDragDistance_impl() const;
    // tag=1008
    virtual int startDragDistance_impl_nocallback() const;
    // tag=1041
    virtual KDDockWidgets::View *tests_createNonClosableView(KDDockWidgets::View *parent = nullptr);
    // tag=1008
    virtual KDDockWidgets::View *tests_createNonClosableView_nocallback(KDDockWidgets::View *parent = nullptr);
    // tag=1041
    static void tests_deinitPlatform();
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
    virtual bool tests_waitForDeleted(KDDockWidgets::View *arg__1, int timeout = 2000) const;
    // tag=1008
    virtual bool tests_waitForDeleted_nocallback(KDDockWidgets::View *arg__1, int timeout = 2000) const;
    // tag=1041
    virtual bool tests_waitForDeleted(QObject *arg__1, int timeout = 2000) const;
    // tag=1008
    virtual bool tests_waitForDeleted_nocallback(QObject *arg__1, int timeout = 2000) const;
    // tag=1041
    virtual bool tests_waitForResize(KDDockWidgets::View *arg__1, int timeout = 2000) const;
    // tag=1008
    virtual bool tests_waitForResize_nocallback(KDDockWidgets::View *arg__1, int timeout = 2000) const;
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
    typedef KDDockWidgets::ViewFactory *(*Callback_createDefaultViewFactory)(void *);
    Callback_createDefaultViewFactory m_createDefaultViewFactoryCallback = nullptr;
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
    typedef int (*Callback_startDragDistance_impl)(void *);
    Callback_startDragDistance_impl m_startDragDistance_implCallback = nullptr;
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
    typedef bool (*Callback_tests_waitForResize)(void *, KDDockWidgets::View *arg__1, int timeout);
    Callback_tests_waitForResize m_tests_waitForResizeCallback = nullptr;
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
//  KDDockWidgets::Platform::Platform()
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Platform__constructor();

// tag=1067
//  KDDockWidgets::Platform::applicationName() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Platform__applicationName(void *thisObj);

// tag=1067
//  KDDockWidgets::Platform::createDefaultViewFactory()
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Platform__createDefaultViewFactory(void *thisObj);

// tag=1067
//  KDDockWidgets::Platform::hasActivePopup() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform__hasActivePopup(void *thisObj);

// tag=1067
//  KDDockWidgets::Platform::inDisallowedDragView(QPoint globalPos) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform__inDisallowedDragView_QPoint(void *thisObj, void *globalPos_);

// tag=1067
//  KDDockWidgets::Platform::installMessageHandler()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform__installMessageHandler(void *thisObj);

// tag=1067
//  KDDockWidgets::Platform::instance()
KDDockWidgetsBindings_EXPORT void *c_static_KDDockWidgets__Platform__instance();

// tag=1067
//  KDDockWidgets::Platform::isLeftMouseButtonPressed() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform__isLeftMouseButtonPressed(void *thisObj);

// tag=1067
//  KDDockWidgets::Platform::isProcessingAppQuitEvent() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform__isProcessingAppQuitEvent(void *thisObj);

// tag=1067
//  KDDockWidgets::Platform::isQtQuick() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform__isQtQuick(void *thisObj);

// tag=1067
//  KDDockWidgets::Platform::isQtWidgets() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform__isQtWidgets(void *thisObj);

// tag=1067
//  KDDockWidgets::Platform::name() const
KDDockWidgetsBindings_EXPORT const char *c_KDDockWidgets__Platform__name(void *thisObj);

// tag=1067
//  KDDockWidgets::Platform::organizationName() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Platform__organizationName(void *thisObj);

// tag=1067
//  KDDockWidgets::Platform::restoreMouseCursor()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform__restoreMouseCursor(void *thisObj);

// tag=1067
//  KDDockWidgets::Platform::screenNumberFor(KDDockWidgets::View * arg__1) const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Platform__screenNumberFor_View(void *thisObj, void *arg__1_);

// tag=1067
//  KDDockWidgets::Platform::screenSizeFor(KDDockWidgets::View * arg__1) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Platform__screenSizeFor_View(void *thisObj, void *arg__1_);

// tag=1067
//  KDDockWidgets::Platform::startDragDistance() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Platform__startDragDistance(void *thisObj);

// tag=1067
//  KDDockWidgets::Platform::startDragDistance_impl() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Platform__startDragDistance_impl(void *thisObj);

// tag=1067
//  KDDockWidgets::Platform::tests_createNonClosableView(KDDockWidgets::View * parent)
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Platform__tests_createNonClosableView_View(void *thisObj, void *parent_);

// tag=1067
//  KDDockWidgets::Platform::tests_deinitPlatform()
KDDockWidgetsBindings_EXPORT void c_static_KDDockWidgets__Platform__tests_deinitPlatform();

// tag=1067
//  KDDockWidgets::Platform::tests_deinitPlatform_impl()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform__tests_deinitPlatform_impl(void *thisObj);

// tag=1067
//  KDDockWidgets::Platform::tests_initPlatform_impl()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform__tests_initPlatform_impl(void *thisObj);

// tag=1067
//  KDDockWidgets::Platform::tests_wait(int ms)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform__tests_wait_int(void *thisObj, int ms);

// tag=1067
//  KDDockWidgets::Platform::tests_waitForDeleted(KDDockWidgets::View * arg__1, int timeout) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform__tests_waitForDeleted_View_int(void *thisObj, void *arg__1_, int timeout);

// tag=1067
//  KDDockWidgets::Platform::tests_waitForDeleted(QObject * arg__1, int timeout) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform__tests_waitForDeleted_QObject_int(void *thisObj, void *arg__1_, int timeout);

// tag=1067
//  KDDockWidgets::Platform::tests_waitForResize(KDDockWidgets::View * arg__1, int timeout) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform__tests_waitForResize_View_int(void *thisObj, void *arg__1_, int timeout);

// tag=1067
//  KDDockWidgets::Platform::ungrabMouse()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform__ungrabMouse(void *thisObj);

// tag=1067
//  KDDockWidgets::Platform::uninstallMessageHandler()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform__uninstallMessageHandler(void *thisObj);

// tag=1067
//  KDDockWidgets::Platform::usesFallbackMouseGrabber() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform__usesFallbackMouseGrabber(void *thisObj);

// tag=1066
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform__destructor(void *thisObj);

// tag=1044
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Platform___get_m_numWarningsEmitted(void *thisObj);

// tag=1045
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform___set_m_numWarningsEmitted_int(void *thisObj, int m_numWarningsEmitted_);

// tag=1046
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
// tag=1047
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform_Finalizer(void *, void *cppObj, void *);
}

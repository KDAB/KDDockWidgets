/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <Platform.h>
#include <ViewFactory.h>
#include <View.h>
#include <qcoreevent.h>
#include <qsize.h>
#include <Controller.h>
#include <qpoint.h>
#include <qstring.h>
#include <vector>
#include <qobject.h>
#include <MainWindow.h>

namespace KDDockWidgetsBindings_wrappersNS {
class Platform_wrapper : public ::KDDockWidgets::Platform
{
public:
    ~Platform_wrapper();
    Platform_wrapper();
    virtual QString applicationName() const;
    virtual QString applicationName_nocallback() const;
    virtual KDDockWidgets::ViewFactory *createDefaultViewFactory();
    virtual KDDockWidgets::ViewFactory *createDefaultViewFactory_nocallback();
    virtual KDDockWidgets::Controllers::MainWindow *
    createMainWindow(const QString &uniqueName, KDDockWidgets::CreateViewOptions arg__2,
                     QFlags<KDDockWidgets::MainWindowOption> options =
                         KDDockWidgets::MainWindowOption::MainWindowOption_HasCentralFrame,
                     KDDockWidgets::View *parent = nullptr, Qt::WindowFlags arg__5 = {}) const;
    virtual KDDockWidgets::Controllers::MainWindow *createMainWindow_nocallback(
        const QString &uniqueName, KDDockWidgets::CreateViewOptions arg__2,
        QFlags<KDDockWidgets::MainWindowOption> options =
            KDDockWidgets::MainWindowOption::MainWindowOption_HasCentralFrame,
        KDDockWidgets::View *parent = nullptr, Qt::WindowFlags arg__5 = {}) const;
    virtual KDDockWidgets::View *createView(KDDockWidgets::Controller *arg__1,
                                            KDDockWidgets::View *parent = nullptr) const;
    virtual KDDockWidgets::View *createView_nocallback(KDDockWidgets::Controller *arg__1,
                                                       KDDockWidgets::View *parent = nullptr) const;
    virtual void dumpManagedBacktrace();
    virtual void dumpManagedBacktrace_nocallback();
    virtual bool hasActivePopup() const;
    virtual bool hasActivePopup_nocallback() const;
    virtual bool inDisallowedDragView(QPoint globalPos) const;
    virtual bool inDisallowedDragView_nocallback(QPoint globalPos) const;
    virtual void installMessageHandler();
    virtual void installMessageHandler_nocallback();
    static KDDockWidgets::Platform *instance();
    virtual bool isLeftMouseButtonPressed() const;
    virtual bool isLeftMouseButtonPressed_nocallback() const;
    virtual bool isProcessingAppQuitEvent() const;
    virtual bool isProcessingAppQuitEvent_nocallback() const;
    bool isQt() const;
    bool isQtQuick() const;
    bool isQtWidgets() const;
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
    int startDragDistance() const;
    virtual int startDragDistance_impl() const;
    virtual int startDragDistance_impl_nocallback() const;
    virtual KDDockWidgets::View *tests_createFocusableView(KDDockWidgets::CreateViewOptions arg__1,
                                                           KDDockWidgets::View *parent = nullptr);
    virtual KDDockWidgets::View *
    tests_createFocusableView_nocallback(KDDockWidgets::CreateViewOptions arg__1,
                                         KDDockWidgets::View *parent = nullptr);
    virtual KDDockWidgets::View *tests_createNonClosableView(KDDockWidgets::View *parent = nullptr);
    virtual KDDockWidgets::View *
    tests_createNonClosableView_nocallback(KDDockWidgets::View *parent = nullptr);
    virtual KDDockWidgets::View *tests_createView(KDDockWidgets::CreateViewOptions arg__1,
                                                  KDDockWidgets::View *parent = nullptr);
    virtual KDDockWidgets::View *
    tests_createView_nocallback(KDDockWidgets::CreateViewOptions arg__1,
                                KDDockWidgets::View *parent = nullptr);
    static void tests_deinitPlatform();
    virtual void tests_deinitPlatform_impl();
    virtual void tests_deinitPlatform_impl_nocallback();
    virtual void tests_initPlatform_impl();
    virtual void tests_initPlatform_impl_nocallback();
    virtual void tests_wait(int ms);
    virtual void tests_wait_nocallback(int ms);
    virtual bool tests_waitForDeleted(KDDockWidgets::View *arg__1, int timeout = 2000) const;
    virtual bool tests_waitForDeleted_nocallback(KDDockWidgets::View *arg__1,
                                                 int timeout = 2000) const;
    virtual bool tests_waitForDeleted(QObject *arg__1, int timeout = 2000) const;
    virtual bool tests_waitForDeleted_nocallback(QObject *arg__1, int timeout = 2000) const;
    virtual bool tests_waitForEvent(KDDockWidgets::View *arg__1, QEvent::Type type,
                                    int timeout = 5000) const;
    virtual bool tests_waitForEvent_nocallback(KDDockWidgets::View *arg__1, QEvent::Type type,
                                               int timeout = 5000) const;
    virtual bool tests_waitForEvent(QObject *w, QEvent::Type type, int timeout = 5000) const;
    virtual bool tests_waitForEvent_nocallback(QObject *w, QEvent::Type type,
                                               int timeout = 5000) const;
    virtual bool tests_waitForResize(KDDockWidgets::Controller *arg__1, int timeout = 2000) const;
    virtual bool tests_waitForResize_nocallback(KDDockWidgets::Controller *arg__1,
                                                int timeout = 2000) const;
    virtual bool tests_waitForResize(KDDockWidgets::View *arg__1, int timeout = 2000) const;
    virtual bool tests_waitForResize_nocallback(KDDockWidgets::View *arg__1,
                                                int timeout = 2000) const;
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
    typedef KDDockWidgets::Controllers::MainWindow *(*Callback_createMainWindow)(
        void *, const QString &uniqueName, KDDockWidgets::CreateViewOptions *arg__2,
        QFlags<KDDockWidgets::MainWindowOption> options, KDDockWidgets::View *parent,
        Qt::WindowFlags arg__5);
    Callback_createMainWindow m_createMainWindowCallback = nullptr;
    typedef KDDockWidgets::View *(*Callback_createView)(void *, KDDockWidgets::Controller *arg__1,
                                                        KDDockWidgets::View *parent);
    Callback_createView m_createViewCallback = nullptr;
    typedef void (*Callback_dumpManagedBacktrace)(void *);
    Callback_dumpManagedBacktrace m_dumpManagedBacktraceCallback = nullptr;
    typedef bool (*Callback_hasActivePopup)(void *);
    Callback_hasActivePopup m_hasActivePopupCallback = nullptr;
    typedef bool (*Callback_inDisallowedDragView)(void *, QPoint *globalPos);
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
    typedef int (*Callback_startDragDistance_impl)(void *);
    Callback_startDragDistance_impl m_startDragDistance_implCallback = nullptr;
    typedef KDDockWidgets::View *(*Callback_tests_createFocusableView)(
        void *, KDDockWidgets::CreateViewOptions *arg__1, KDDockWidgets::View *parent);
    Callback_tests_createFocusableView m_tests_createFocusableViewCallback = nullptr;
    typedef KDDockWidgets::View *(*Callback_tests_createNonClosableView)(
        void *, KDDockWidgets::View *parent);
    Callback_tests_createNonClosableView m_tests_createNonClosableViewCallback = nullptr;
    typedef KDDockWidgets::View *(*Callback_tests_createView)(
        void *, KDDockWidgets::CreateViewOptions *arg__1, KDDockWidgets::View *parent);
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
    typedef bool (*Callback_tests_waitForEvent)(void *, KDDockWidgets::View *arg__1,
                                                QEvent::Type type, int timeout);
    Callback_tests_waitForEvent m_tests_waitForEventCallback = nullptr;
    typedef bool (*Callback_tests_waitForEvent_2)(void *, QObject *w, QEvent::Type type,
                                                  int timeout);
    Callback_tests_waitForEvent_2 m_tests_waitForEvent_2Callback = nullptr;
    typedef bool (*Callback_tests_waitForResize)(void *, KDDockWidgets::Controller *arg__1,
                                                 int timeout);
    Callback_tests_waitForResize m_tests_waitForResizeCallback = nullptr;
    typedef bool (*Callback_tests_waitForResize_2)(void *, KDDockWidgets::View *arg__1,
                                                   int timeout);
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
// KDDockWidgets::Platform::Platform()
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Platform__constructor();
// KDDockWidgets::Platform::applicationName() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Platform__applicationName(void *thisObj);
// KDDockWidgets::Platform::createDefaultViewFactory()
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Platform__createDefaultViewFactory(void *thisObj);
// KDDockWidgets::Platform::createMainWindow(const QString & uniqueName,
// KDDockWidgets::CreateViewOptions arg__2, QFlags<KDDockWidgets::MainWindowOption> options,
// KDDockWidgets::View * parent, Qt::WindowFlags arg__5) const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Platform__createMainWindow_QString_CreateViewOptions_MainWindowOptions_View_WindowFlags(
    void *thisObj, const char *uniqueName_, void *arg__2_, int options_, void *parent_, int arg__5);
// KDDockWidgets::Platform::createView(KDDockWidgets::Controller * arg__1, KDDockWidgets::View *
// parent) const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Platform__createView_Controller_View(void *thisObj, void *arg__1_, void *parent_);
// KDDockWidgets::Platform::dumpManagedBacktrace()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform__dumpManagedBacktrace(void *thisObj);
// KDDockWidgets::Platform::hasActivePopup() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform__hasActivePopup(void *thisObj);
// KDDockWidgets::Platform::inDisallowedDragView(QPoint globalPos) const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Platform__inDisallowedDragView_QPoint(void *thisObj, void *globalPos_);
// KDDockWidgets::Platform::installMessageHandler()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform__installMessageHandler(void *thisObj);
// KDDockWidgets::Platform::instance()
KDDockWidgetsBindings_EXPORT void *c_static_KDDockWidgets__Platform__instance();
// KDDockWidgets::Platform::isLeftMouseButtonPressed() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Platform__isLeftMouseButtonPressed(void *thisObj);
// KDDockWidgets::Platform::isProcessingAppQuitEvent() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Platform__isProcessingAppQuitEvent(void *thisObj);
// KDDockWidgets::Platform::isQt() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform__isQt(void *thisObj);
// KDDockWidgets::Platform::isQtQuick() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform__isQtQuick(void *thisObj);
// KDDockWidgets::Platform::isQtWidgets() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform__isQtWidgets(void *thisObj);
// KDDockWidgets::Platform::name() const
KDDockWidgetsBindings_EXPORT const char *c_KDDockWidgets__Platform__name(void *thisObj);
// KDDockWidgets::Platform::organizationName() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Platform__organizationName(void *thisObj);
// KDDockWidgets::Platform::restoreMouseCursor()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform__restoreMouseCursor(void *thisObj);
// KDDockWidgets::Platform::screenNumberFor(KDDockWidgets::View * arg__1) const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Platform__screenNumberFor_View(void *thisObj,
                                                                                 void *arg__1_);
// KDDockWidgets::Platform::screenSizeFor(KDDockWidgets::View * arg__1) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Platform__screenSizeFor_View(void *thisObj,
                                                                                 void *arg__1_);
// KDDockWidgets::Platform::sendEvent(KDDockWidgets::View * arg__1, QEvent * arg__2) const
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Platform__sendEvent_View_QEvent(void *thisObj, void *arg__1_, void *arg__2_);
// KDDockWidgets::Platform::setMouseCursor(Qt::CursorShape arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Platform__setMouseCursor_CursorShape(void *thisObj, int arg__1);
// KDDockWidgets::Platform::startDragDistance() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Platform__startDragDistance(void *thisObj);
// KDDockWidgets::Platform::startDragDistance_impl() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Platform__startDragDistance_impl(void *thisObj);
// KDDockWidgets::Platform::tests_createFocusableView(KDDockWidgets::CreateViewOptions arg__1,
// KDDockWidgets::View * parent)
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Platform__tests_createFocusableView_CreateViewOptions_View(void *thisObj,
                                                                            void *arg__1_,
                                                                            void *parent_);
// KDDockWidgets::Platform::tests_createNonClosableView(KDDockWidgets::View * parent)
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Platform__tests_createNonClosableView_View(void *thisObj, void *parent_);
// KDDockWidgets::Platform::tests_createView(KDDockWidgets::CreateViewOptions arg__1,
// KDDockWidgets::View * parent)
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Platform__tests_createView_CreateViewOptions_View(void *thisObj, void *arg__1_,
                                                                   void *parent_);
// KDDockWidgets::Platform::tests_deinitPlatform()
KDDockWidgetsBindings_EXPORT void c_static_KDDockWidgets__Platform__tests_deinitPlatform();
// KDDockWidgets::Platform::tests_deinitPlatform_impl()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Platform__tests_deinitPlatform_impl(void *thisObj);
// KDDockWidgets::Platform::tests_initPlatform_impl()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform__tests_initPlatform_impl(void *thisObj);
// KDDockWidgets::Platform::tests_wait(int ms)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform__tests_wait_int(void *thisObj, int ms);
// KDDockWidgets::Platform::tests_waitForDeleted(KDDockWidgets::View * arg__1, int timeout) const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Platform__tests_waitForDeleted_View_int(void *thisObj, void *arg__1_, int timeout);
// KDDockWidgets::Platform::tests_waitForDeleted(QObject * arg__1, int timeout) const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Platform__tests_waitForDeleted_QObject_int(void *thisObj, void *arg__1_,
                                                            int timeout);
// KDDockWidgets::Platform::tests_waitForEvent(KDDockWidgets::View * arg__1, QEvent::Type type, int
// timeout) const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Platform__tests_waitForEvent_View_Type_int(void *thisObj, void *arg__1_, int type,
                                                            int timeout);
// KDDockWidgets::Platform::tests_waitForEvent(QObject * w, QEvent::Type type, int timeout) const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Platform__tests_waitForEvent_QObject_Type_int(void *thisObj, void *w_, int type,
                                                               int timeout);
// KDDockWidgets::Platform::tests_waitForResize(KDDockWidgets::Controller * arg__1, int timeout)
// const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Platform__tests_waitForResize_Controller_int(void *thisObj, void *arg__1_,
                                                              int timeout);
// KDDockWidgets::Platform::tests_waitForResize(KDDockWidgets::View * arg__1, int timeout) const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Platform__tests_waitForResize_View_int(void *thisObj, void *arg__1_, int timeout);
// KDDockWidgets::Platform::ungrabMouse()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform__ungrabMouse(void *thisObj);
// KDDockWidgets::Platform::uninstallMessageHandler()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform__uninstallMessageHandler(void *thisObj);
// KDDockWidgets::Platform::usesFallbackMouseGrabber() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Platform__usesFallbackMouseGrabber(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT int
c_KDDockWidgets__Platform___get_m_numWarningsEmitted(void *thisObj);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Platform___set_m_numWarningsEmitted_int(void *thisObj, int m_numWarningsEmitted_);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Platform__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform_Finalizer(void *, void *cppObj, void *);
}

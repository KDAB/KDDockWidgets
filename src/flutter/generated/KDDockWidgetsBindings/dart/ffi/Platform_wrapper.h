/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

//tag=1040
#include "KDDockWidgetsBindings_exports.h"
#include <Platform.h>
#include <ViewFactory.h>
#include <View.h>
#include <qsize.h>
#include <qpoint.h>
#include <qstring.h>

namespace KDDockWidgetsBindings_wrappersNS {
//tag=1017
class Platform_wrapper : public ::KDDockWidgets::Platform {public:
~Platform_wrapper();
//tag=1041
 Platform_wrapper();
//tag=1041
virtual QString applicationName()const;
//tag=1008
virtual QString applicationName_nocallback()const;
//tag=1041
virtual KDDockWidgets::ViewFactory * createDefaultViewFactory();
//tag=1008
virtual KDDockWidgets::ViewFactory * createDefaultViewFactory_nocallback();
//tag=1041
virtual bool hasActivePopup()const;
//tag=1008
virtual bool hasActivePopup_nocallback()const;
//tag=1041
virtual bool inDisallowedDragView(QPoint globalPos)const;
//tag=1008
virtual bool inDisallowedDragView_nocallback(QPoint globalPos)const;
//tag=1041
static KDDockWidgets::Platform * instance();
//tag=1041
virtual bool isLeftMouseButtonPressed()const;
//tag=1008
virtual bool isLeftMouseButtonPressed_nocallback()const;
//tag=1041
virtual bool isProcessingAppQuitEvent()const;
//tag=1008
virtual bool isProcessingAppQuitEvent_nocallback()const;
//tag=1041
bool isQtQuick()const;
//tag=1041
bool isQtWidgets()const;
//tag=1041
virtual const char * name()const;
//tag=1008
virtual const char * name_nocallback()const;
//tag=1041
virtual QString organizationName()const;
//tag=1008
virtual QString organizationName_nocallback()const;
//tag=1041
virtual void restoreMouseCursor();
//tag=1008
virtual void restoreMouseCursor_nocallback();
//tag=1041
virtual int screenNumberFor(KDDockWidgets::View * arg__1)const;
//tag=1008
virtual int screenNumberFor_nocallback(KDDockWidgets::View * arg__1)const;
//tag=1041
virtual QSize screenSizeFor(KDDockWidgets::View * arg__1)const;
//tag=1008
virtual QSize screenSizeFor_nocallback(KDDockWidgets::View * arg__1)const;
//tag=1041
int startDragDistance()const;
//tag=1041
virtual int startDragDistance_impl()const;
//tag=1008
virtual int startDragDistance_impl_nocallback()const;
//tag=1041
virtual void ungrabMouse();
//tag=1008
virtual void ungrabMouse_nocallback();
//tag=1041
virtual bool usesFallbackMouseGrabber()const;
//tag=1008
virtual bool usesFallbackMouseGrabber_nocallback()const;
//tag=1042
typedef QString* (*Callback_applicationName)(void *);Callback_applicationName m_applicationNameCallback = nullptr;
//tag=1042
typedef KDDockWidgets::ViewFactory * (*Callback_createDefaultViewFactory)(void *);Callback_createDefaultViewFactory m_createDefaultViewFactoryCallback = nullptr;
//tag=1042
typedef bool (*Callback_hasActivePopup)(void *);Callback_hasActivePopup m_hasActivePopupCallback = nullptr;
//tag=1042
typedef bool (*Callback_inDisallowedDragView)(void *,QPoint globalPos);Callback_inDisallowedDragView m_inDisallowedDragViewCallback = nullptr;
//tag=1042
typedef bool (*Callback_isLeftMouseButtonPressed)(void *);Callback_isLeftMouseButtonPressed m_isLeftMouseButtonPressedCallback = nullptr;
//tag=1042
typedef bool (*Callback_isProcessingAppQuitEvent)(void *);Callback_isProcessingAppQuitEvent m_isProcessingAppQuitEventCallback = nullptr;
//tag=1042
typedef const char * (*Callback_name)(void *);Callback_name m_nameCallback = nullptr;
//tag=1042
typedef QString* (*Callback_organizationName)(void *);Callback_organizationName m_organizationNameCallback = nullptr;
//tag=1042
typedef void (*Callback_restoreMouseCursor)(void *);Callback_restoreMouseCursor m_restoreMouseCursorCallback = nullptr;
//tag=1042
typedef int (*Callback_screenNumberFor)(void *,KDDockWidgets::View * arg__1);Callback_screenNumberFor m_screenNumberForCallback = nullptr;
//tag=1042
typedef QSize* (*Callback_screenSizeFor)(void *,KDDockWidgets::View * arg__1);Callback_screenSizeFor m_screenSizeForCallback = nullptr;
//tag=1042
typedef int (*Callback_startDragDistance_impl)(void *);Callback_startDragDistance_impl m_startDragDistance_implCallback = nullptr;
//tag=1042
typedef void (*Callback_ungrabMouse)(void *);Callback_ungrabMouse m_ungrabMouseCallback = nullptr;
//tag=1042
typedef bool (*Callback_usesFallbackMouseGrabber)(void *);Callback_usesFallbackMouseGrabber m_usesFallbackMouseGrabberCallback = nullptr;

};
}extern "C" {

//tag=1067
// KDDockWidgets::Platform::Platform()
KDDockWidgetsBindings_EXPORT void * c_KDDockWidgets__Platform__constructor();

//tag=1067
// KDDockWidgets::Platform::applicationName() const
KDDockWidgetsBindings_EXPORT void* c_KDDockWidgets__Platform__applicationName(void *thisObj);

//tag=1067
// KDDockWidgets::Platform::createDefaultViewFactory()
KDDockWidgetsBindings_EXPORT void* c_KDDockWidgets__Platform__createDefaultViewFactory(void *thisObj);

//tag=1067
// KDDockWidgets::Platform::hasActivePopup() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform__hasActivePopup(void *thisObj);

//tag=1067
// KDDockWidgets::Platform::inDisallowedDragView(QPoint globalPos) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform__inDisallowedDragView_QPoint(void *thisObj,void* globalPos_);

//tag=1067
// KDDockWidgets::Platform::instance()
KDDockWidgetsBindings_EXPORT void* c_static_KDDockWidgets__Platform__instance();

//tag=1067
// KDDockWidgets::Platform::isLeftMouseButtonPressed() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform__isLeftMouseButtonPressed(void *thisObj);

//tag=1067
// KDDockWidgets::Platform::isProcessingAppQuitEvent() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform__isProcessingAppQuitEvent(void *thisObj);

//tag=1067
// KDDockWidgets::Platform::isQtQuick() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform__isQtQuick(void *thisObj);

//tag=1067
// KDDockWidgets::Platform::isQtWidgets() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform__isQtWidgets(void *thisObj);

//tag=1067
// KDDockWidgets::Platform::name() const
KDDockWidgetsBindings_EXPORT const char * c_KDDockWidgets__Platform__name(void *thisObj);

//tag=1067
// KDDockWidgets::Platform::organizationName() const
KDDockWidgetsBindings_EXPORT void* c_KDDockWidgets__Platform__organizationName(void *thisObj);

//tag=1067
// KDDockWidgets::Platform::restoreMouseCursor()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform__restoreMouseCursor(void *thisObj);

//tag=1067
// KDDockWidgets::Platform::screenNumberFor(KDDockWidgets::View * arg__1) const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Platform__screenNumberFor_View(void *thisObj,void* arg__1_);

//tag=1067
// KDDockWidgets::Platform::screenSizeFor(KDDockWidgets::View * arg__1) const
KDDockWidgetsBindings_EXPORT void* c_KDDockWidgets__Platform__screenSizeFor_View(void *thisObj,void* arg__1_);

//tag=1067
// KDDockWidgets::Platform::startDragDistance() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Platform__startDragDistance(void *thisObj);

//tag=1067
// KDDockWidgets::Platform::startDragDistance_impl() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Platform__startDragDistance_impl(void *thisObj);

//tag=1067
// KDDockWidgets::Platform::ungrabMouse()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform__ungrabMouse(void *thisObj);

//tag=1067
// KDDockWidgets::Platform::usesFallbackMouseGrabber() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Platform__usesFallbackMouseGrabber(void *thisObj);

//tag=1066
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform__destructor(void *thisObj);

//tag=1046
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Platform__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
//tag=1047
KDDockWidgetsBindings_EXPORT  void c_KDDockWidgets__Platform_Finalizer(void *, void *cppObj, void *);}

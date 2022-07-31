/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// tag=1040
#include "KDDockWidgetsBindings_exports.h"
#include <ViewFactory.h>
#include <qstring.h>
#include <ClassicIndicatorWindowViewInterface.h>
#include <ClassicIndicators.h>
#include <View.h>
#include <DropArea.h>
#include <qobject.h>
#include <qcoreevent.h>
#include <qlist.h>
#include <qbytearray.h>

namespace KDDockWidgetsBindings_wrappersNS {
// tag=1017
class ViewFactory_wrapper : public ::KDDockWidgets::ViewFactory
{
public:
    ~ViewFactory_wrapper();
    // tag=1041
    ViewFactory_wrapper();
    // tag=1041
    virtual KDDockWidgets::Views::ClassicIndicatorWindowViewInterface *createClassicIndicatorWindow(KDDockWidgets::Controllers::ClassicIndicators *arg__1) const;
    // tag=1008
    virtual KDDockWidgets::Views::ClassicIndicatorWindowViewInterface *createClassicIndicatorWindow_nocallback(KDDockWidgets::Controllers::ClassicIndicators *arg__1) const;
    // tag=1041
    virtual KDDockWidgets::View *createDropArea(KDDockWidgets::Controllers::DropArea *arg__1, KDDockWidgets::View *parent) const;
    // tag=1008
    virtual KDDockWidgets::View *createDropArea_nocallback(KDDockWidgets::Controllers::DropArea *arg__1, KDDockWidgets::View *parent) const;
    // tag=1041
    virtual KDDockWidgets::View *createRubberBand(KDDockWidgets::View *parent) const;
    // tag=1008
    virtual KDDockWidgets::View *createRubberBand_nocallback(KDDockWidgets::View *parent) const;
    // tag=1041
    virtual void customEvent(QEvent *event);
    // tag=1008
    virtual void customEvent_nocallback(QEvent *event);
    // tag=1041
    virtual bool event(QEvent *event);
    // tag=1008
    virtual bool event_nocallback(QEvent *event);
    // tag=1041
    virtual bool eventFilter(QObject *watched, QEvent *event);
    // tag=1008
    virtual bool eventFilter_nocallback(QObject *watched, QEvent *event);
    // tag=1041
    static QString tr(const char *s, const char *c, int n);
    // tag=1042
    typedef KDDockWidgets::Views::ClassicIndicatorWindowViewInterface *(*Callback_createClassicIndicatorWindow)(void *, KDDockWidgets::Controllers::ClassicIndicators *arg__1);
    Callback_createClassicIndicatorWindow m_createClassicIndicatorWindowCallback = nullptr;
    // tag=1042
    typedef KDDockWidgets::View *(*Callback_createDropArea)(void *, KDDockWidgets::Controllers::DropArea *arg__1, KDDockWidgets::View *parent);
    Callback_createDropArea m_createDropAreaCallback = nullptr;
    // tag=1042
    typedef KDDockWidgets::View *(*Callback_createRubberBand)(void *, KDDockWidgets::View *parent);
    Callback_createRubberBand m_createRubberBandCallback = nullptr;
    // tag=1042
    typedef void (*Callback_customEvent)(void *, QEvent *event);
    Callback_customEvent m_customEventCallback = nullptr;
    // tag=1042
    typedef bool (*Callback_event)(void *, QEvent *event);
    Callback_event m_eventCallback = nullptr;
    // tag=1042
    typedef bool (*Callback_eventFilter)(void *, QObject *watched, QEvent *event);
    Callback_eventFilter m_eventFilterCallback = nullptr;
};
}
extern "C" {

// tag=1067
//  KDDockWidgets::ViewFactory::ViewFactory()
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__ViewFactory__constructor();

// tag=1067
//  KDDockWidgets::ViewFactory::createClassicIndicatorWindow(KDDockWidgets::Controllers::ClassicIndicators * arg__1) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__ViewFactory__createClassicIndicatorWindow_ClassicIndicators(void *thisObj, void *arg__1_);

// tag=1067
//  KDDockWidgets::ViewFactory::createDropArea(KDDockWidgets::Controllers::DropArea * arg__1, KDDockWidgets::View * parent) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__ViewFactory__createDropArea_DropArea_View(void *thisObj, void *arg__1_, void *parent_);

// tag=1067
//  KDDockWidgets::ViewFactory::createRubberBand(KDDockWidgets::View * parent) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__ViewFactory__createRubberBand_View(void *thisObj, void *parent_);

// tag=1067
//  KDDockWidgets::ViewFactory::customEvent(QEvent * event)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__ViewFactory__customEvent_QEvent(void *thisObj, void *event_);

// tag=1067
//  KDDockWidgets::ViewFactory::event(QEvent * event)
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__ViewFactory__event_QEvent(void *thisObj, void *event_);

// tag=1067
//  KDDockWidgets::ViewFactory::eventFilter(QObject * watched, QEvent * event)
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__ViewFactory__eventFilter_QObject_QEvent(void *thisObj, void *watched_, void *event_);

// tag=1067
//  KDDockWidgets::ViewFactory::tr(const char * s, const char * c, int n)
KDDockWidgetsBindings_EXPORT void *c_static_KDDockWidgets__ViewFactory__tr_char_char_int(const char *s, const char *c, int n);

// tag=1066
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__ViewFactory__destructor(void *thisObj);

// tag=1046
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__ViewFactory__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
// tag=1047
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__ViewFactory_Finalizer(void *, void *cppObj, void *);
}

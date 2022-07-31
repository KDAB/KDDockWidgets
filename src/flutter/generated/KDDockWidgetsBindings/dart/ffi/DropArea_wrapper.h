/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// tag=1040
#include "KDDockWidgetsBindings_exports.h"
#include <DropArea.h>
#include <qstring.h>
#include <View.h>
#include <qsize.h>
#include <qcoreevent.h>
#include <qobject.h>

namespace KDDockWidgetsBindings_wrappersNS {
// tag=1017
class DropArea_wrapper : public ::KDDockWidgets::Controllers::DropArea
{
public:
    ~DropArea_wrapper();
    // tag=1041
    DropArea_wrapper(KDDockWidgets::View *parent, QFlags<KDDockWidgets::MainWindowOption> options, bool isMDIWrapper = false);
    // tag=1041
    void addMultiSplitter(KDDockWidgets::Controllers::DropArea *splitter, KDDockWidgets::Location location);
    // tag=1041
    void addWidget(KDDockWidgets::View *widget, KDDockWidgets::Location location);
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
    bool hasSingleFloatingFrame() const;
    // tag=1041
    bool hasSingleFrame() const;
    // tag=1041
    bool isMDIWrapper() const;
    // tag=1041
    void layoutEqually();
    // tag=1041
    void removeHover();
    // tag=1041
    virtual void setParentView_impl(KDDockWidgets::View *parent);
    // tag=1008
    virtual void setParentView_impl_nocallback(KDDockWidgets::View *parent);
    // tag=1041
    static QString tr(const char *s, const char *c, int n);
    // tag=1042
    typedef void (*Callback_customEvent)(void *, QEvent *event);
    Callback_customEvent m_customEventCallback = nullptr;
    // tag=1042
    typedef bool (*Callback_event)(void *, QEvent *event);
    Callback_event m_eventCallback = nullptr;
    // tag=1042
    typedef bool (*Callback_eventFilter)(void *, QObject *watched, QEvent *event);
    Callback_eventFilter m_eventFilterCallback = nullptr;
    // tag=1042
    typedef void (*Callback_setParentView_impl)(void *, KDDockWidgets::View *parent);
    Callback_setParentView_impl m_setParentView_implCallback = nullptr;
};
}
extern "C" {

// tag=1067
//  KDDockWidgets::Controllers::DropArea::DropArea(KDDockWidgets::View * parent, QFlags<KDDockWidgets::MainWindowOption> options, bool isMDIWrapper)
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controllers__DropArea__constructor_View_MainWindowOptions_bool(void *parent_, int options_, bool isMDIWrapper);

// tag=1067
//  KDDockWidgets::Controllers::DropArea::addMultiSplitter(KDDockWidgets::Controllers::DropArea * splitter, KDDockWidgets::Location location)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__DropArea__addMultiSplitter_DropArea_Location(void *thisObj, void *splitter_, int location);

// tag=1067
//  KDDockWidgets::Controllers::DropArea::addWidget(KDDockWidgets::View * widget, KDDockWidgets::Location location)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__DropArea__addWidget_View_Location(void *thisObj, void *widget_, int location);

// tag=1067
//  KDDockWidgets::Controllers::DropArea::customEvent(QEvent * event)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__DropArea__customEvent_QEvent(void *thisObj, void *event_);

// tag=1067
//  KDDockWidgets::Controllers::DropArea::event(QEvent * event)
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__DropArea__event_QEvent(void *thisObj, void *event_);

// tag=1067
//  KDDockWidgets::Controllers::DropArea::eventFilter(QObject * watched, QEvent * event)
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__DropArea__eventFilter_QObject_QEvent(void *thisObj, void *watched_, void *event_);

// tag=1067
//  KDDockWidgets::Controllers::DropArea::hasSingleFloatingFrame() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__DropArea__hasSingleFloatingFrame(void *thisObj);

// tag=1067
//  KDDockWidgets::Controllers::DropArea::hasSingleFrame() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__DropArea__hasSingleFrame(void *thisObj);

// tag=1067
//  KDDockWidgets::Controllers::DropArea::isMDIWrapper() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__DropArea__isMDIWrapper(void *thisObj);

// tag=1067
//  KDDockWidgets::Controllers::DropArea::layoutEqually()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__DropArea__layoutEqually(void *thisObj);

// tag=1067
//  KDDockWidgets::Controllers::DropArea::removeHover()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__DropArea__removeHover(void *thisObj);

// tag=1067
//  KDDockWidgets::Controllers::DropArea::setParentView_impl(KDDockWidgets::View * parent)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__DropArea__setParentView_impl_View(void *thisObj, void *parent_);

// tag=1067
//  KDDockWidgets::Controllers::DropArea::tr(const char * s, const char * c, int n)
KDDockWidgetsBindings_EXPORT void *c_static_KDDockWidgets__Controllers__DropArea__tr_char_char_int(const char *s, const char *c, int n);

// tag=1066
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__DropArea__destructor(void *thisObj);

// tag=1046
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__DropArea__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
// tag=1047
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__DropArea_Finalizer(void *, void *cppObj, void *);
}

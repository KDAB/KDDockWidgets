/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <SideBar.h>
#include <qstring.h>
#include <DockWidget.h>
#include <MainWindow.h>
#include <View.h>
#include <qrect.h>
#include <qcoreevent.h>
#include <qobject.h>
#include <qpoint.h>
#include <qsize.h>

namespace KDDockWidgetsBindings_wrappersNS {
class SideBar_wrapper : public ::KDDockWidgets::Controllers::SideBar
{
public:
    ~SideBar_wrapper();
    void addDockWidget(KDDockWidgets::Controllers::DockWidget *dw);
    void clear();
    bool containsDockWidget(KDDockWidgets::Controllers::DockWidget *arg__1) const;
    virtual void customEvent(QEvent *event);
    virtual void customEvent_nocallback(QEvent *event);
    virtual bool event(QEvent *event);
    virtual bool event_nocallback(QEvent *event);
    virtual bool eventFilter(QObject *watched, QEvent *event);
    virtual bool eventFilter_nocallback(QObject *watched, QEvent *event);
    bool isEmpty() const;
    bool isVertical() const;
    KDDockWidgets::Controllers::MainWindow *mainWindow() const;
    void onButtonClicked(KDDockWidgets::Controllers::DockWidget *dw);
    void removeDockWidget(KDDockWidgets::Controllers::DockWidget *dw);
    virtual void setParentView_impl(KDDockWidgets::View *parent);
    virtual void setParentView_impl_nocallback(KDDockWidgets::View *parent);
    void toggleOverlay(KDDockWidgets::Controllers::DockWidget *arg__1);
    static QString tr(const char *s, const char *c, int n);
    typedef void (*Callback_customEvent)(void *, QEvent *event);
    Callback_customEvent m_customEventCallback = nullptr;
    typedef bool (*Callback_event)(void *, QEvent *event);
    Callback_event m_eventCallback = nullptr;
    typedef bool (*Callback_eventFilter)(void *, QObject *watched, QEvent *event);
    Callback_eventFilter m_eventFilterCallback = nullptr;
    typedef void (*Callback_setParentView_impl)(void *, KDDockWidgets::View *parent);
    Callback_setParentView_impl m_setParentView_implCallback = nullptr;
};
}
extern "C" {
// KDDockWidgets::Controllers::SideBar::addDockWidget(KDDockWidgets::Controllers::DockWidget * dw)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__SideBar__addDockWidget_DockWidget(void *thisObj, void *dw_);
// KDDockWidgets::Controllers::SideBar::clear()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__SideBar__clear(void *thisObj);
// KDDockWidgets::Controllers::SideBar::containsDockWidget(KDDockWidgets::Controllers::DockWidget *
// arg__1) const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__SideBar__containsDockWidget_DockWidget(void *thisObj, void *arg__1_);
// KDDockWidgets::Controllers::SideBar::customEvent(QEvent * event)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__SideBar__customEvent_QEvent(void *thisObj, void *event_);
// KDDockWidgets::Controllers::SideBar::event(QEvent * event)
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__SideBar__event_QEvent(void *thisObj,
                                                                                      void *event_);
// KDDockWidgets::Controllers::SideBar::eventFilter(QObject * watched, QEvent * event)
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__SideBar__eventFilter_QObject_QEvent(void *thisObj, void *watched_,
                                                                  void *event_);
// KDDockWidgets::Controllers::SideBar::isEmpty() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__SideBar__isEmpty(void *thisObj);
// KDDockWidgets::Controllers::SideBar::isVertical() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__SideBar__isVertical(void *thisObj);
// KDDockWidgets::Controllers::SideBar::mainWindow() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controllers__SideBar__mainWindow(void *thisObj);
// KDDockWidgets::Controllers::SideBar::onButtonClicked(KDDockWidgets::Controllers::DockWidget * dw)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__SideBar__onButtonClicked_DockWidget(void *thisObj, void *dw_);
// KDDockWidgets::Controllers::SideBar::removeDockWidget(KDDockWidgets::Controllers::DockWidget *
// dw)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__SideBar__removeDockWidget_DockWidget(void *thisObj, void *dw_);
// KDDockWidgets::Controllers::SideBar::setParentView_impl(KDDockWidgets::View * parent)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__SideBar__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Controllers::SideBar::toggleOverlay(KDDockWidgets::Controllers::DockWidget *
// arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__SideBar__toggleOverlay_DockWidget(void *thisObj, void *arg__1_);
// KDDockWidgets::Controllers::SideBar::tr(const char * s, const char * c, int n)
KDDockWidgetsBindings_EXPORT void *
c_static_KDDockWidgets__Controllers__SideBar__tr_char_char_int(const char *s, const char *c, int n);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__SideBar__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__SideBar__registerVirtualMethodCallback(void *ptr, void *callback,
                                                                     int methodId);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__SideBar_Finalizer(void *, void *cppObj, void *);
}

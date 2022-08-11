/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <TabBar.h>
#include <qstring.h>
#include <Stack.h>
#include <qpoint.h>
#include <Group.h>
#include <qrect.h>
#include <View.h>
#include <qobject.h>
#include <qcoreevent.h>
#include <qsize.h>

namespace KDDockWidgetsBindings_wrappersNS {
class TabBar_wrapper : public ::KDDockWidgets::Controllers::TabBar
{
public:
    ~TabBar_wrapper();
    TabBar_wrapper(KDDockWidgets::Controllers::Stack *tabWidget = nullptr);
    virtual void customEvent(QEvent *event);
    virtual void customEvent_nocallback(QEvent *event);
    virtual bool dragCanStart(QPoint pressPos, QPoint pos) const;
    virtual bool dragCanStart_nocallback(QPoint pressPos, QPoint pos) const;
    virtual bool event(QEvent *event);
    virtual bool event_nocallback(QEvent *event);
    virtual bool eventFilter(QObject *watched, QEvent *event);
    virtual bool eventFilter_nocallback(QObject *watched, QEvent *event);
    KDDockWidgets::Controllers::Group *group() const;
    bool hasSingleDockWidget() const;
    virtual bool isMDI() const;
    virtual bool isMDI_nocallback() const;
    virtual bool isWindow() const;
    virtual bool isWindow_nocallback() const;
    void moveTabTo(int from, int to);
    int numDockWidgets() const;
    void onMouseDoubleClick(QPoint localPos);
    void onMousePress(QPoint localPos);
    QRect rectForTab(int index) const;
    virtual void setParentView_impl(KDDockWidgets::View *parent);
    virtual void setParentView_impl_nocallback(KDDockWidgets::View *parent);
    KDDockWidgets::Controllers::Stack *stack() const;
    bool tabsAreMovable() const;
    QString text(int index) const;
    static QString tr(const char *s, const char *c, int n);
    typedef void (*Callback_customEvent)(void *, QEvent *event);
    Callback_customEvent m_customEventCallback = nullptr;
    typedef bool (*Callback_dragCanStart)(void *, QPoint *pressPos, QPoint *pos);
    Callback_dragCanStart m_dragCanStartCallback = nullptr;
    typedef bool (*Callback_event)(void *, QEvent *event);
    Callback_event m_eventCallback = nullptr;
    typedef bool (*Callback_eventFilter)(void *, QObject *watched, QEvent *event);
    Callback_eventFilter m_eventFilterCallback = nullptr;
    typedef bool (*Callback_isMDI)(void *);
    Callback_isMDI m_isMDICallback = nullptr;
    typedef bool (*Callback_isWindow)(void *);
    Callback_isWindow m_isWindowCallback = nullptr;
    typedef void (*Callback_setParentView_impl)(void *, KDDockWidgets::View *parent);
    Callback_setParentView_impl m_setParentView_implCallback = nullptr;
};
}
extern "C" {
// KDDockWidgets::Controllers::TabBar::TabBar(KDDockWidgets::Controllers::Stack * tabWidget)
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__TabBar__constructor_Stack(void *tabWidget_);
// KDDockWidgets::Controllers::TabBar::customEvent(QEvent * event)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__TabBar__customEvent_QEvent(void *thisObj, void *event_);
// KDDockWidgets::Controllers::TabBar::dragCanStart(QPoint pressPos, QPoint pos) const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__TabBar__dragCanStart_QPoint_QPoint(void *thisObj, void *pressPos_,
                                                                 void *pos_);
// KDDockWidgets::Controllers::TabBar::event(QEvent * event)
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__TabBar__event_QEvent(void *thisObj,
                                                                                     void *event_);
// KDDockWidgets::Controllers::TabBar::eventFilter(QObject * watched, QEvent * event)
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__TabBar__eventFilter_QObject_QEvent(void *thisObj, void *watched_,
                                                                 void *event_);
// KDDockWidgets::Controllers::TabBar::group() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controllers__TabBar__group(void *thisObj);
// KDDockWidgets::Controllers::TabBar::hasSingleDockWidget() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__TabBar__hasSingleDockWidget(void *thisObj);
// KDDockWidgets::Controllers::TabBar::isMDI() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__TabBar__isMDI(void *thisObj);
// KDDockWidgets::Controllers::TabBar::isWindow() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__TabBar__isWindow(void *thisObj);
// KDDockWidgets::Controllers::TabBar::moveTabTo(int from, int to)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__TabBar__moveTabTo_int_int(void *thisObj, int from, int to);
// KDDockWidgets::Controllers::TabBar::numDockWidgets() const
KDDockWidgetsBindings_EXPORT int
c_KDDockWidgets__Controllers__TabBar__numDockWidgets(void *thisObj);
// KDDockWidgets::Controllers::TabBar::onMouseDoubleClick(QPoint localPos)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__TabBar__onMouseDoubleClick_QPoint(void *thisObj, void *localPos_);
// KDDockWidgets::Controllers::TabBar::onMousePress(QPoint localPos)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__TabBar__onMousePress_QPoint(void *thisObj, void *localPos_);
// KDDockWidgets::Controllers::TabBar::rectForTab(int index) const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__TabBar__rectForTab_int(void *thisObj, int index);
// KDDockWidgets::Controllers::TabBar::setParentView_impl(KDDockWidgets::View * parent)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__TabBar__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Controllers::TabBar::stack() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controllers__TabBar__stack(void *thisObj);
// KDDockWidgets::Controllers::TabBar::tabsAreMovable() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__TabBar__tabsAreMovable(void *thisObj);
// KDDockWidgets::Controllers::TabBar::text(int index) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controllers__TabBar__text_int(void *thisObj,
                                                                                  int index);
// KDDockWidgets::Controllers::TabBar::tr(const char * s, const char * c, int n)
KDDockWidgetsBindings_EXPORT void *
c_static_KDDockWidgets__Controllers__TabBar__tr_char_char_int(const char *s, const char *c, int n);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__TabBar__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__TabBar__registerVirtualMethodCallback(void *ptr, void *callback,
                                                                    int methodId);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__TabBar_Finalizer(void *, void *cppObj, void *);
}

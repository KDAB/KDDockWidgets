/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <Separator.h>
#include <View.h>
#include <qrect.h>
#include <qpoint.h>
#include <qstring.h>
#include <qcoreevent.h>
#include <qobject.h>
#include <qsize.h>

namespace KDDockWidgetsBindings_wrappersNS {
class Separator_wrapper : public ::KDDockWidgets::Controllers::Separator
{
public:
    ~Separator_wrapper();
    Separator_wrapper(KDDockWidgets::View *host);
    virtual void customEvent(QEvent *event);
    virtual void customEvent_nocallback(QEvent *event);
    virtual bool event(QEvent *event);
    virtual bool event_nocallback(QEvent *event);
    virtual bool eventFilter(QObject *watched, QEvent *event);
    virtual bool eventFilter_nocallback(QObject *watched, QEvent *event);
    static bool isResizing();
    bool isVertical() const;
    void move(int p);
    static int numSeparators();
    void onMouseDoubleClick();
    void onMouseMove(QPoint pos);
    void onMousePress();
    void onMouseReleased();
    int position() const;
    void setGeometry(QRect r);
    void setGeometry(int pos, int pos2, int length);
    virtual void setParentView_impl(KDDockWidgets::View *parent);
    virtual void setParentView_impl_nocallback(KDDockWidgets::View *parent);
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
// KDDockWidgets::Controllers::Separator::Separator(KDDockWidgets::View * host)
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__Separator__constructor_View(void *host_);
// KDDockWidgets::Controllers::Separator::customEvent(QEvent * event)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__Separator__customEvent_QEvent(void *thisObj, void *event_);
// KDDockWidgets::Controllers::Separator::event(QEvent * event)
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__Separator__event_QEvent(void *thisObj, void *event_);
// KDDockWidgets::Controllers::Separator::eventFilter(QObject * watched, QEvent * event)
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__Separator__eventFilter_QObject_QEvent(void *thisObj, void *watched_,
                                                                    void *event_);
// KDDockWidgets::Controllers::Separator::isResizing()
KDDockWidgetsBindings_EXPORT bool c_static_KDDockWidgets__Controllers__Separator__isResizing();
// KDDockWidgets::Controllers::Separator::isVertical() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__Separator__isVertical(void *thisObj);
// KDDockWidgets::Controllers::Separator::move(int p)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__Separator__move_int(void *thisObj,
                                                                                    int p);
// KDDockWidgets::Controllers::Separator::numSeparators()
KDDockWidgetsBindings_EXPORT int c_static_KDDockWidgets__Controllers__Separator__numSeparators();
// KDDockWidgets::Controllers::Separator::onMouseDoubleClick()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__Separator__onMouseDoubleClick(void *thisObj);
// KDDockWidgets::Controllers::Separator::onMouseMove(QPoint pos)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__Separator__onMouseMove_QPoint(void *thisObj, void *pos_);
// KDDockWidgets::Controllers::Separator::onMousePress()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__Separator__onMousePress(void *thisObj);
// KDDockWidgets::Controllers::Separator::onMouseReleased()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__Separator__onMouseReleased(void *thisObj);
// KDDockWidgets::Controllers::Separator::position() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Controllers__Separator__position(void *thisObj);
// KDDockWidgets::Controllers::Separator::setGeometry(QRect r)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__Separator__setGeometry_QRect(void *thisObj, void *r_);
// KDDockWidgets::Controllers::Separator::setGeometry(int pos, int pos2, int length)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__Separator__setGeometry_int_int_int(void *thisObj, int pos, int pos2,
                                                                 int length);
// KDDockWidgets::Controllers::Separator::setParentView_impl(KDDockWidgets::View * parent)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__Separator__setParentView_impl_View(void *thisObj, void *parent_);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__Separator__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__Separator__registerVirtualMethodCallback(void *ptr, void *callback,
                                                                       int methodId);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__Separator_Finalizer(void *, void *cppObj, void *);
}

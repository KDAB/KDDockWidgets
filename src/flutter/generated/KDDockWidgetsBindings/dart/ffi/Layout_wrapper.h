/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// tag=1040
#include "KDDockWidgetsBindings_exports.h"
#include <controllers/Layout.h>
#include <View.h>
#include <qsize.h>
#include <DropArea.h>
#include <qobject.h>
#include <qcoreevent.h>
#include <qstring.h>
#include <qpoint.h>
#include <qrect.h>

namespace KDDockWidgetsBindings_wrappersNS {
// tag=1017
class Layout_wrapper : public ::KDDockWidgets::Controllers::Layout
{
public:
    ~Layout_wrapper();
    // tag=1041
    Layout_wrapper(KDDockWidgets::Type arg__1, KDDockWidgets::View *arg__2);
    // tag=1041
    KDDockWidgets::Controllers::DropArea *asDropArea() const;
    // tag=1041
    bool checkSanity() const;
    // tag=1041
    void clearLayout();
    // tag=1041
    int count() const;
    // tag=1041
    virtual void customEvent(QEvent *event);
    // tag=1008
    virtual void customEvent_nocallback(QEvent *event);
    // tag=1041
    void dumpLayout() const;
    // tag=1041
    virtual bool event(QEvent *event);
    // tag=1008
    virtual bool event_nocallback(QEvent *event);
    // tag=1041
    virtual bool eventFilter(QObject *watched, QEvent *event);
    // tag=1008
    virtual bool eventFilter_nocallback(QObject *watched, QEvent *event);
    // tag=1041
    bool isInMainWindow(bool honourNesting = false) const;
    // tag=1041
    int layoutHeight() const;
    // tag=1041
    QSize layoutMaximumSizeHint() const;
    // tag=1041
    QSize layoutMinimumSize() const;
    // tag=1041
    QSize layoutSize() const;
    // tag=1041
    int layoutWidth() const;
    // tag=1041
    int placeholderCount() const;
    // tag=1041
    void setLayoutMinimumSize(QSize arg__1);
    // tag=1041
    void setLayoutSize(QSize arg__1);
    // tag=1041
    virtual void setParentView_impl(KDDockWidgets::View *parent);
    // tag=1008
    virtual void setParentView_impl_nocallback(KDDockWidgets::View *parent);
    // tag=1041
    void updateSizeConstraints();
    // tag=1041
    void viewAboutToBeDeleted();
    // tag=1041
    int visibleCount() const;
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
//  KDDockWidgets::Controllers::Layout::Layout(KDDockWidgets::Type arg__1, KDDockWidgets::View * arg__2)
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controllers__Layout__constructor_Type_View(int arg__1, void *arg__2_);

// tag=1067
//  KDDockWidgets::Controllers::Layout::asDropArea() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controllers__Layout__asDropArea(void *thisObj);

// tag=1067
//  KDDockWidgets::Controllers::Layout::checkSanity() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__Layout__checkSanity(void *thisObj);

// tag=1067
//  KDDockWidgets::Controllers::Layout::clearLayout()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__Layout__clearLayout(void *thisObj);

// tag=1067
//  KDDockWidgets::Controllers::Layout::count() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Controllers__Layout__count(void *thisObj);

// tag=1067
//  KDDockWidgets::Controllers::Layout::customEvent(QEvent * event)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__Layout__customEvent_QEvent(void *thisObj, void *event_);

// tag=1067
//  KDDockWidgets::Controllers::Layout::dumpLayout() const
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__Layout__dumpLayout(void *thisObj);

// tag=1067
//  KDDockWidgets::Controllers::Layout::event(QEvent * event)
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__Layout__event_QEvent(void *thisObj, void *event_);

// tag=1067
//  KDDockWidgets::Controllers::Layout::eventFilter(QObject * watched, QEvent * event)
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__Layout__eventFilter_QObject_QEvent(void *thisObj, void *watched_, void *event_);

// tag=1067
//  KDDockWidgets::Controllers::Layout::isInMainWindow(bool honourNesting) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__Layout__isInMainWindow_bool(void *thisObj, bool honourNesting);

// tag=1067
//  KDDockWidgets::Controllers::Layout::layoutHeight() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Controllers__Layout__layoutHeight(void *thisObj);

// tag=1067
//  KDDockWidgets::Controllers::Layout::layoutMaximumSizeHint() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controllers__Layout__layoutMaximumSizeHint(void *thisObj);

// tag=1067
//  KDDockWidgets::Controllers::Layout::layoutMinimumSize() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controllers__Layout__layoutMinimumSize(void *thisObj);

// tag=1067
//  KDDockWidgets::Controllers::Layout::layoutSize() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controllers__Layout__layoutSize(void *thisObj);

// tag=1067
//  KDDockWidgets::Controllers::Layout::layoutWidth() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Controllers__Layout__layoutWidth(void *thisObj);

// tag=1067
//  KDDockWidgets::Controllers::Layout::placeholderCount() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Controllers__Layout__placeholderCount(void *thisObj);

// tag=1067
//  KDDockWidgets::Controllers::Layout::setLayoutMinimumSize(QSize arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__Layout__setLayoutMinimumSize_QSize(void *thisObj, void *arg__1_);

// tag=1067
//  KDDockWidgets::Controllers::Layout::setLayoutSize(QSize arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__Layout__setLayoutSize_QSize(void *thisObj, void *arg__1_);

// tag=1067
//  KDDockWidgets::Controllers::Layout::setParentView_impl(KDDockWidgets::View * parent)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__Layout__setParentView_impl_View(void *thisObj, void *parent_);

// tag=1067
//  KDDockWidgets::Controllers::Layout::updateSizeConstraints()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__Layout__updateSizeConstraints(void *thisObj);

// tag=1067
//  KDDockWidgets::Controllers::Layout::viewAboutToBeDeleted()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__Layout__viewAboutToBeDeleted(void *thisObj);

// tag=1067
//  KDDockWidgets::Controllers::Layout::visibleCount() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Controllers__Layout__visibleCount(void *thisObj);

// tag=1066
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__Layout__destructor(void *thisObj);

// tag=1046
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__Layout__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
// tag=1047
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__Layout_Finalizer(void *, void *cppObj, void *);
}

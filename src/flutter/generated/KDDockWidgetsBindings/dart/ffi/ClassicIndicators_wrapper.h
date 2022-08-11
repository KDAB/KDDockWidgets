/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <ClassicIndicators.h>
#include <qstring.h>
#include <DropArea.h>
#include <qpoint.h>
#include <qsize.h>
#include <qrect.h>
#include <qcoreevent.h>
#include <Group.h>
#include <View.h>
#include <qobject.h>

namespace KDDockWidgetsBindings_wrappersNS {
class ClassicIndicators_wrapper : public ::KDDockWidgets::Controllers::ClassicIndicators
{
public:
    ~ClassicIndicators_wrapper();
    ClassicIndicators_wrapper(KDDockWidgets::Controllers::DropArea *dropArea);
    virtual void customEvent(QEvent *event);
    virtual void customEvent_nocallback(QEvent *event);
    virtual bool dropIndicatorVisible(KDDockWidgets::DropLocation arg__1) const;
    virtual bool dropIndicatorVisible_nocallback(KDDockWidgets::DropLocation arg__1) const;
    virtual bool event(QEvent *event);
    virtual bool event_nocallback(QEvent *event);
    virtual bool eventFilter(QObject *watched, QEvent *event);
    virtual bool eventFilter_nocallback(QObject *watched, QEvent *event);
    virtual KDDockWidgets::DropLocation hover_impl(QPoint globalPos);
    virtual KDDockWidgets::DropLocation hover_impl_nocallback(QPoint globalPos);
    void indicatorsVisibleChanged();
    virtual void onHoveredFrameChanged(KDDockWidgets::Controllers::Group *arg__1);
    virtual void onHoveredFrameChanged_nocallback(KDDockWidgets::Controllers::Group *arg__1);
    bool onResize(QSize newSize);
    virtual QPoint posForIndicator(KDDockWidgets::DropLocation arg__1) const;
    virtual QPoint posForIndicator_nocallback(KDDockWidgets::DropLocation arg__1) const;
    void setDropLocation(KDDockWidgets::DropLocation arg__1);
    virtual void setParentView_impl(KDDockWidgets::View *parent);
    virtual void setParentView_impl_nocallback(KDDockWidgets::View *parent);
    static QString tr(const char *s, const char *c, int n);
    virtual void updateVisibility();
    virtual void updateVisibility_nocallback();
    typedef void (*Callback_customEvent)(void *, QEvent *event);
    Callback_customEvent m_customEventCallback = nullptr;
    typedef bool (*Callback_dropIndicatorVisible)(void *, KDDockWidgets::DropLocation arg__1);
    Callback_dropIndicatorVisible m_dropIndicatorVisibleCallback = nullptr;
    typedef bool (*Callback_event)(void *, QEvent *event);
    Callback_event m_eventCallback = nullptr;
    typedef bool (*Callback_eventFilter)(void *, QObject *watched, QEvent *event);
    Callback_eventFilter m_eventFilterCallback = nullptr;
    typedef KDDockWidgets::DropLocation (*Callback_hover_impl)(void *, QPoint *globalPos);
    Callback_hover_impl m_hover_implCallback = nullptr;
    typedef void (*Callback_onHoveredFrameChanged)(void *,
                                                   KDDockWidgets::Controllers::Group *arg__1);
    Callback_onHoveredFrameChanged m_onHoveredFrameChangedCallback = nullptr;
    typedef QPoint *(*Callback_posForIndicator)(void *, KDDockWidgets::DropLocation arg__1);
    Callback_posForIndicator m_posForIndicatorCallback = nullptr;
    typedef void (*Callback_setParentView_impl)(void *, KDDockWidgets::View *parent);
    Callback_setParentView_impl m_setParentView_implCallback = nullptr;
    typedef void (*Callback_updateVisibility)(void *);
    Callback_updateVisibility m_updateVisibilityCallback = nullptr;
};
}
extern "C" {
// KDDockWidgets::Controllers::ClassicIndicators::ClassicIndicators(KDDockWidgets::Controllers::DropArea
// * dropArea)
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__ClassicIndicators__constructor_DropArea(void *dropArea_);
// KDDockWidgets::Controllers::ClassicIndicators::customEvent(QEvent * event)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__ClassicIndicators__customEvent_QEvent(void *thisObj, void *event_);
// KDDockWidgets::Controllers::ClassicIndicators::dropIndicatorVisible(KDDockWidgets::DropLocation
// arg__1) const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__ClassicIndicators__dropIndicatorVisible_DropLocation(void *thisObj,
                                                                                   int arg__1);
// KDDockWidgets::Controllers::ClassicIndicators::event(QEvent * event)
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__ClassicIndicators__event_QEvent(void *thisObj, void *event_);
// KDDockWidgets::Controllers::ClassicIndicators::eventFilter(QObject * watched, QEvent * event)
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__ClassicIndicators__eventFilter_QObject_QEvent(void *thisObj,
                                                                            void *watched_,
                                                                            void *event_);
// KDDockWidgets::Controllers::ClassicIndicators::hover_impl(QPoint globalPos)
KDDockWidgetsBindings_EXPORT int
c_KDDockWidgets__Controllers__ClassicIndicators__hover_impl_QPoint(void *thisObj, void *globalPos_);
// KDDockWidgets::Controllers::ClassicIndicators::indicatorsVisibleChanged()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__ClassicIndicators__indicatorsVisibleChanged(void *thisObj);
// KDDockWidgets::Controllers::ClassicIndicators::onHoveredFrameChanged(KDDockWidgets::Controllers::Group
// * arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__ClassicIndicators__onHoveredFrameChanged_Group(void *thisObj,
                                                                             void *arg__1_);
// KDDockWidgets::Controllers::ClassicIndicators::onResize(QSize newSize)
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__ClassicIndicators__onResize_QSize(void *thisObj, void *newSize_);
// KDDockWidgets::Controllers::ClassicIndicators::posForIndicator(KDDockWidgets::DropLocation
// arg__1) const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__ClassicIndicators__posForIndicator_DropLocation(void *thisObj,
                                                                              int arg__1);
// KDDockWidgets::Controllers::ClassicIndicators::setDropLocation(KDDockWidgets::DropLocation
// arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__ClassicIndicators__setDropLocation_DropLocation(void *thisObj,
                                                                              int arg__1);
// KDDockWidgets::Controllers::ClassicIndicators::setParentView_impl(KDDockWidgets::View * parent)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__ClassicIndicators__setParentView_impl_View(void *thisObj,
                                                                         void *parent_);
// KDDockWidgets::Controllers::ClassicIndicators::tr(const char * s, const char * c, int n)
KDDockWidgetsBindings_EXPORT void *
c_static_KDDockWidgets__Controllers__ClassicIndicators__tr_char_char_int(const char *s,
                                                                         const char *c, int n);
// KDDockWidgets::Controllers::ClassicIndicators::updateVisibility()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__ClassicIndicators__updateVisibility(void *thisObj);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__ClassicIndicators__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__ClassicIndicators__registerVirtualMethodCallback(void *ptr,
                                                                               void *callback,
                                                                               int methodId);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__ClassicIndicators_Finalizer(void *, void *cppObj, void *);
}

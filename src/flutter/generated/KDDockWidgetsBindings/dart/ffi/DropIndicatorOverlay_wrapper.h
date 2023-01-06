/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <controllers/DropIndicatorOverlay.h>
#include <qstring.h>
#include <DropArea.h>
#include <Group.h>
#include <qrect.h>
#include <qpoint.h>
#include <qobject.h>
#include <qcoreevent.h>
#include <qsize.h>
#include <View.h>

namespace KDDockWidgetsBindings_wrappersNS {
class DropIndicatorOverlay_wrapper : public ::KDDockWidgets::Controllers::DropIndicatorOverlay
{
public:
    ~DropIndicatorOverlay_wrapper();
    DropIndicatorOverlay_wrapper(KDDockWidgets::Controllers::DropArea *dropArea);
    KDDockWidgets::DropLocation currentDropLocation() const;
    void currentDropLocationChanged();
    virtual void customEvent(QEvent *event);
    virtual void customEvent_nocallback(QEvent *event);
    virtual bool dropIndicatorVisible(KDDockWidgets::DropLocation arg__1) const;
    virtual bool dropIndicatorVisible_nocallback(KDDockWidgets::DropLocation arg__1) const;
    virtual bool event(QEvent *event);
    virtual bool event_nocallback(QEvent *event);
    virtual bool eventFilter(QObject *watched, QEvent *event);
    virtual bool eventFilter_nocallback(QObject *watched, QEvent *event);
    KDDockWidgets::DropLocation hover(QPoint globalPos);
    virtual KDDockWidgets::DropLocation hover_impl(QPoint globalPos);
    virtual KDDockWidgets::DropLocation hover_impl_nocallback(QPoint globalPos);
    KDDockWidgets::Controllers::Group *hoveredFrame() const;
    void hoveredFrameChanged(KDDockWidgets::Controllers::Group *arg__1);
    QRect hoveredFrameRect() const;
    void hoveredFrameRectChanged();
    bool isHovered() const;
    static KDDockWidgets::Location multisplitterLocationFor(KDDockWidgets::DropLocation arg__1);
    virtual void onHoveredFrameChanged(KDDockWidgets::Controllers::Group *arg__1);
    virtual void onHoveredFrameChanged_nocallback(KDDockWidgets::Controllers::Group *arg__1);
    virtual QPoint posForIndicator(KDDockWidgets::DropLocation arg__1) const;
    virtual QPoint posForIndicator_nocallback(KDDockWidgets::DropLocation arg__1) const;
    void removeHover();
    void setCurrentDropLocation(KDDockWidgets::DropLocation location);
    void setHoveredFrame(KDDockWidgets::Controllers::Group *arg__1);
    virtual void setParentView_impl(KDDockWidgets::View *parent);
    virtual void setParentView_impl_nocallback(KDDockWidgets::View *parent);
    void setWindowBeingDragged(bool arg__1);
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
// KDDockWidgets::Controllers::DropIndicatorOverlay::DropIndicatorOverlay(KDDockWidgets::Controllers::DropArea
// * dropArea)
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__DropIndicatorOverlay__constructor_DropArea(void *dropArea_);
// KDDockWidgets::Controllers::DropIndicatorOverlay::currentDropLocation() const
KDDockWidgetsBindings_EXPORT int
c_KDDockWidgets__Controllers__DropIndicatorOverlay__currentDropLocation(void *thisObj);
// KDDockWidgets::Controllers::DropIndicatorOverlay::currentDropLocationChanged()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DropIndicatorOverlay__currentDropLocationChanged(void *thisObj);
// KDDockWidgets::Controllers::DropIndicatorOverlay::customEvent(QEvent * event)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DropIndicatorOverlay__customEvent_QEvent(void *thisObj, void *event_);
// KDDockWidgets::Controllers::DropIndicatorOverlay::dropIndicatorVisible(KDDockWidgets::DropLocation
// arg__1) const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__DropIndicatorOverlay__dropIndicatorVisible_DropLocation(void *thisObj,
                                                                                      int arg__1);
// KDDockWidgets::Controllers::DropIndicatorOverlay::event(QEvent * event)
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__DropIndicatorOverlay__event_QEvent(void *thisObj, void *event_);
// KDDockWidgets::Controllers::DropIndicatorOverlay::eventFilter(QObject * watched, QEvent * event)
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__DropIndicatorOverlay__eventFilter_QObject_QEvent(void *thisObj,
                                                                               void *watched_,
                                                                               void *event_);
// KDDockWidgets::Controllers::DropIndicatorOverlay::hover(QPoint globalPos)
KDDockWidgetsBindings_EXPORT int
c_KDDockWidgets__Controllers__DropIndicatorOverlay__hover_QPoint(void *thisObj, void *globalPos_);
// KDDockWidgets::Controllers::DropIndicatorOverlay::hover_impl(QPoint globalPos)
KDDockWidgetsBindings_EXPORT int
c_KDDockWidgets__Controllers__DropIndicatorOverlay__hover_impl_QPoint(void *thisObj,
                                                                      void *globalPos_);
// KDDockWidgets::Controllers::DropIndicatorOverlay::hoveredFrame() const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__DropIndicatorOverlay__hoveredFrame(void *thisObj);
// KDDockWidgets::Controllers::DropIndicatorOverlay::hoveredFrameChanged(KDDockWidgets::Controllers::Group
// * arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DropIndicatorOverlay__hoveredFrameChanged_Group(void *thisObj,
                                                                              void *arg__1_);
// KDDockWidgets::Controllers::DropIndicatorOverlay::hoveredFrameRect() const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__DropIndicatorOverlay__hoveredFrameRect(void *thisObj);
// KDDockWidgets::Controllers::DropIndicatorOverlay::hoveredFrameRectChanged()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DropIndicatorOverlay__hoveredFrameRectChanged(void *thisObj);
// KDDockWidgets::Controllers::DropIndicatorOverlay::isHovered() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__DropIndicatorOverlay__isHovered(void *thisObj);
// KDDockWidgets::Controllers::DropIndicatorOverlay::multisplitterLocationFor(KDDockWidgets::DropLocation
// arg__1)
KDDockWidgetsBindings_EXPORT int
c_static_KDDockWidgets__Controllers__DropIndicatorOverlay__multisplitterLocationFor_DropLocation(
    int arg__1);
// KDDockWidgets::Controllers::DropIndicatorOverlay::onHoveredFrameChanged(KDDockWidgets::Controllers::Group
// * arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DropIndicatorOverlay__onHoveredFrameChanged_Group(void *thisObj,
                                                                                void *arg__1_);
// KDDockWidgets::Controllers::DropIndicatorOverlay::posForIndicator(KDDockWidgets::DropLocation
// arg__1) const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__DropIndicatorOverlay__posForIndicator_DropLocation(void *thisObj,
                                                                                 int arg__1);
// KDDockWidgets::Controllers::DropIndicatorOverlay::removeHover()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DropIndicatorOverlay__removeHover(void *thisObj);
// KDDockWidgets::Controllers::DropIndicatorOverlay::setCurrentDropLocation(KDDockWidgets::DropLocation
// location)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DropIndicatorOverlay__setCurrentDropLocation_DropLocation(
    void *thisObj, int location);
// KDDockWidgets::Controllers::DropIndicatorOverlay::setHoveredFrame(KDDockWidgets::Controllers::Group
// * arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DropIndicatorOverlay__setHoveredFrame_Group(void *thisObj,
                                                                          void *arg__1_);
// KDDockWidgets::Controllers::DropIndicatorOverlay::setParentView_impl(KDDockWidgets::View *
// parent)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DropIndicatorOverlay__setParentView_impl_View(void *thisObj,
                                                                            void *parent_);
// KDDockWidgets::Controllers::DropIndicatorOverlay::setWindowBeingDragged(bool arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DropIndicatorOverlay__setWindowBeingDragged_bool(void *thisObj,
                                                                               bool arg__1);
// KDDockWidgets::Controllers::DropIndicatorOverlay::tr(const char * s, const char * c, int n)
KDDockWidgetsBindings_EXPORT void *
c_static_KDDockWidgets__Controllers__DropIndicatorOverlay__tr_char_char_int(const char *s,
                                                                            const char *c, int n);
// KDDockWidgets::Controllers::DropIndicatorOverlay::updateVisibility()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DropIndicatorOverlay__updateVisibility(void *thisObj);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DropIndicatorOverlay__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DropIndicatorOverlay__registerVirtualMethodCallback(void *ptr,
                                                                                  void *callback,
                                                                                  int methodId);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DropIndicatorOverlay_Finalizer(void *, void *cppObj, void *);
}

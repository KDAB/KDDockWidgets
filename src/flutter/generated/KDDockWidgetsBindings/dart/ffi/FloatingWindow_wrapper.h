/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <FloatingWindow.h>
#include <qstring.h>
#include <qrect.h>
#include <Group.h>
#include <DockWidget.h>
#include <DropArea.h>
#include <TitleBar.h>
#include <controllers/Layout.h>
#include <qpoint.h>
#include <KDDockWidgets.h>
#include <qsize.h>
#include <qcoreevent.h>
#include <qobject.h>
#include <View.h>

namespace KDDockWidgetsBindings_wrappersNS {
class FloatingWindow_wrapper : public ::KDDockWidgets::Controllers::FloatingWindow
{
public:
    ~FloatingWindow_wrapper();
    FloatingWindow_wrapper(KDDockWidgets::Controllers::Group *group, QRect suggestedGeometry);
    FloatingWindow_wrapper(QRect suggestedGeometry);
    void activatedChanged();
    void addDockWidget(KDDockWidgets::Controllers::DockWidget *arg__1,
                       KDDockWidgets::Location location,
                       KDDockWidgets::Controllers::DockWidget *relativeTo,
                       KDDockWidgets::InitialOption arg__4 = {});
    bool allDockWidgetsHave(KDDockWidgets::DockWidgetOption arg__1) const;
    bool allDockWidgetsHave(KDDockWidgets::LayoutSaverOption arg__1) const;
    bool anyDockWidgetsHas(KDDockWidgets::DockWidgetOption arg__1) const;
    bool anyDockWidgetsHas(KDDockWidgets::LayoutSaverOption arg__1) const;
    bool anyNonClosable() const;
    bool anyNonDockable() const;
    bool beingDeleted() const;
    virtual void customEvent(QEvent *event);
    virtual void customEvent_nocallback(QEvent *event);
    QRect dragRect() const;
    KDDockWidgets::Controllers::DropArea *dropArea() const;
    static void ensureRectIsOnScreen(QRect &geometry);
    virtual bool event(QEvent *event);
    virtual bool event_nocallback(QEvent *event);
    virtual bool eventFilter(QObject *watched, QEvent *event);
    virtual bool eventFilter_nocallback(QObject *watched, QEvent *event);
    bool hasSingleDockWidget() const;
    bool hasSingleFrame() const;
    bool isInDragArea(QPoint globalPoint) const;
    virtual bool isMDI() const;
    virtual bool isMDI_nocallback() const;
    virtual bool isWindow() const;
    virtual bool isWindow_nocallback() const;
    KDDockWidgets::Controllers::Layout *layout() const;
    void maybeCreateResizeHandler();
    KDDockWidgets::Controllers::DropArea *multiSplitter() const;
    void numFramesChanged();
    void scheduleDeleteLater();
    virtual void setParentView_impl(KDDockWidgets::View *parent);
    virtual void setParentView_impl_nocallback(KDDockWidgets::View *parent);
    void setSuggestedGeometry(QRect suggestedRect);
    virtual KDDockWidgets::Controllers::DockWidget *singleDockWidget() const;
    virtual KDDockWidgets::Controllers::DockWidget *singleDockWidget_nocallback() const;
    KDDockWidgets::Controllers::Group *singleFrame() const;
    KDDockWidgets::Controllers::TitleBar *titleBar() const;
    static QString tr(const char *s, const char *c, int n);
    void updateTitleAndIcon();
    void updateTitleBarVisibility();
    int userType() const;
    void windowStateChanged();
    typedef void (*Callback_customEvent)(void *, QEvent *event);
    Callback_customEvent m_customEventCallback = nullptr;
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
    typedef KDDockWidgets::Controllers::DockWidget *(*Callback_singleDockWidget)(void *);
    Callback_singleDockWidget m_singleDockWidgetCallback = nullptr;
};
}
extern "C" {
// KDDockWidgets::Controllers::FloatingWindow::FloatingWindow(KDDockWidgets::Controllers::Group *
// group, QRect suggestedGeometry)
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__FloatingWindow__constructor_Group_QRect(void *group_,
                                                                      void *suggestedGeometry_);
// KDDockWidgets::Controllers::FloatingWindow::FloatingWindow(QRect suggestedGeometry)
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__FloatingWindow__constructor_QRect(void *suggestedGeometry_);
// KDDockWidgets::Controllers::FloatingWindow::activatedChanged()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__FloatingWindow__activatedChanged(void *thisObj);
// KDDockWidgets::Controllers::FloatingWindow::addDockWidget(KDDockWidgets::Controllers::DockWidget
// * arg__1, KDDockWidgets::Location location, KDDockWidgets::Controllers::DockWidget * relativeTo,
// KDDockWidgets::InitialOption arg__4)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__FloatingWindow__addDockWidget_DockWidget_Location_DockWidget_InitialOption(
    void *thisObj, void *arg__1_, int location, void *relativeTo_, void *arg__4_);
// KDDockWidgets::Controllers::FloatingWindow::allDockWidgetsHave(KDDockWidgets::DockWidgetOption
// arg__1) const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__FloatingWindow__allDockWidgetsHave_DockWidgetOption(void *thisObj,
                                                                                  int arg__1);
// KDDockWidgets::Controllers::FloatingWindow::allDockWidgetsHave(KDDockWidgets::LayoutSaverOption
// arg__1) const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__FloatingWindow__allDockWidgetsHave_LayoutSaverOption(void *thisObj,
                                                                                   int arg__1);
// KDDockWidgets::Controllers::FloatingWindow::anyDockWidgetsHas(KDDockWidgets::DockWidgetOption
// arg__1) const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__FloatingWindow__anyDockWidgetsHas_DockWidgetOption(void *thisObj,
                                                                                 int arg__1);
// KDDockWidgets::Controllers::FloatingWindow::anyDockWidgetsHas(KDDockWidgets::LayoutSaverOption
// arg__1) const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__FloatingWindow__anyDockWidgetsHas_LayoutSaverOption(void *thisObj,
                                                                                  int arg__1);
// KDDockWidgets::Controllers::FloatingWindow::anyNonClosable() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__FloatingWindow__anyNonClosable(void *thisObj);
// KDDockWidgets::Controllers::FloatingWindow::anyNonDockable() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__FloatingWindow__anyNonDockable(void *thisObj);
// KDDockWidgets::Controllers::FloatingWindow::beingDeleted() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__FloatingWindow__beingDeleted(void *thisObj);
// KDDockWidgets::Controllers::FloatingWindow::customEvent(QEvent * event)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__FloatingWindow__customEvent_QEvent(void *thisObj, void *event_);
// KDDockWidgets::Controllers::FloatingWindow::dragRect() const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__FloatingWindow__dragRect(void *thisObj);
// KDDockWidgets::Controllers::FloatingWindow::dropArea() const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__FloatingWindow__dropArea(void *thisObj);
// KDDockWidgets::Controllers::FloatingWindow::ensureRectIsOnScreen(QRect & geometry)
KDDockWidgetsBindings_EXPORT void
c_static_KDDockWidgets__Controllers__FloatingWindow__ensureRectIsOnScreen_QRect(void *geometry_);
// KDDockWidgets::Controllers::FloatingWindow::event(QEvent * event)
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__FloatingWindow__event_QEvent(void *thisObj, void *event_);
// KDDockWidgets::Controllers::FloatingWindow::eventFilter(QObject * watched, QEvent * event)
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__FloatingWindow__eventFilter_QObject_QEvent(void *thisObj,
                                                                         void *watched_,
                                                                         void *event_);
// KDDockWidgets::Controllers::FloatingWindow::hasSingleDockWidget() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__FloatingWindow__hasSingleDockWidget(void *thisObj);
// KDDockWidgets::Controllers::FloatingWindow::hasSingleFrame() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__FloatingWindow__hasSingleFrame(void *thisObj);
// KDDockWidgets::Controllers::FloatingWindow::isInDragArea(QPoint globalPoint) const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__FloatingWindow__isInDragArea_QPoint(void *thisObj,
                                                                  void *globalPoint_);
// KDDockWidgets::Controllers::FloatingWindow::isMDI() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__FloatingWindow__isMDI(void *thisObj);
// KDDockWidgets::Controllers::FloatingWindow::isWindow() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__FloatingWindow__isWindow(void *thisObj);
// KDDockWidgets::Controllers::FloatingWindow::layout() const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__FloatingWindow__layout(void *thisObj);
// KDDockWidgets::Controllers::FloatingWindow::maybeCreateResizeHandler()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__FloatingWindow__maybeCreateResizeHandler(void *thisObj);
// KDDockWidgets::Controllers::FloatingWindow::multiSplitter() const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__FloatingWindow__multiSplitter(void *thisObj);
// KDDockWidgets::Controllers::FloatingWindow::numFramesChanged()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__FloatingWindow__numFramesChanged(void *thisObj);
// KDDockWidgets::Controllers::FloatingWindow::scheduleDeleteLater()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__FloatingWindow__scheduleDeleteLater(void *thisObj);
// KDDockWidgets::Controllers::FloatingWindow::setParentView_impl(KDDockWidgets::View * parent)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__FloatingWindow__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Controllers::FloatingWindow::setSuggestedGeometry(QRect suggestedRect)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__FloatingWindow__setSuggestedGeometry_QRect(void *thisObj,
                                                                         void *suggestedRect_);
// KDDockWidgets::Controllers::FloatingWindow::singleDockWidget() const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__FloatingWindow__singleDockWidget(void *thisObj);
// KDDockWidgets::Controllers::FloatingWindow::singleFrame() const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__FloatingWindow__singleFrame(void *thisObj);
// KDDockWidgets::Controllers::FloatingWindow::titleBar() const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__FloatingWindow__titleBar(void *thisObj);
// KDDockWidgets::Controllers::FloatingWindow::tr(const char * s, const char * c, int n)
KDDockWidgetsBindings_EXPORT void *
c_static_KDDockWidgets__Controllers__FloatingWindow__tr_char_char_int(const char *s, const char *c,
                                                                      int n);
// KDDockWidgets::Controllers::FloatingWindow::updateTitleAndIcon()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__FloatingWindow__updateTitleAndIcon(void *thisObj);
// KDDockWidgets::Controllers::FloatingWindow::updateTitleBarVisibility()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__FloatingWindow__updateTitleBarVisibility(void *thisObj);
// KDDockWidgets::Controllers::FloatingWindow::userType() const
KDDockWidgetsBindings_EXPORT int
c_KDDockWidgets__Controllers__FloatingWindow__userType(void *thisObj);
// KDDockWidgets::Controllers::FloatingWindow::windowStateChanged()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__FloatingWindow__windowStateChanged(void *thisObj);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__FloatingWindow__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__FloatingWindow__registerVirtualMethodCallback(void *ptr,
                                                                            void *callback,
                                                                            int methodId);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__FloatingWindow_Finalizer(void *, void *cppObj, void *);
}

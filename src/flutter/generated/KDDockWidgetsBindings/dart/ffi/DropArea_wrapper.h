/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <DropArea.h>
#include <qstring.h>
#include <View.h>
#include <qlist.h>
#include <Group.h>
#include <Item_p.h>
#include <controllers/DropIndicatorOverlay.h>
#include <DockWidget.h>
#include <KDDockWidgets.h>
#include <qsize.h>
#include <qpoint.h>
#include <FloatingWindow.h>
#include <qcoreevent.h>
#include <qobject.h>

namespace KDDockWidgetsBindings_wrappersNS {
class DropArea_wrapper : public ::KDDockWidgets::Controllers::DropArea
{
public:
    ~DropArea_wrapper();
    DropArea_wrapper(KDDockWidgets::View *parent, QFlags<KDDockWidgets::MainWindowOption> options,
                     bool isMDIWrapper = false);
    void addDockWidget(KDDockWidgets::Controllers::DockWidget *arg__1,
                       KDDockWidgets::Location location,
                       KDDockWidgets::Controllers::DockWidget *relativeTo,
                       KDDockWidgets::InitialOption arg__4 = {});
    void
    addMultiSplitter(KDDockWidgets::Controllers::DropArea *splitter,
                     KDDockWidgets::Location location,
                     KDDockWidgets::Controllers::Group *relativeTo = nullptr,
                     KDDockWidgets::InitialOption option = KDDockWidgets::DefaultSizeMode::Fair);
    void addWidget(KDDockWidgets::View *widget, KDDockWidgets::Location location,
                   KDDockWidgets::Controllers::Group *relativeTo = nullptr,
                   KDDockWidgets::InitialOption option = KDDockWidgets::DefaultSizeMode::Fair);
    Layouting::Item *centralFrame() const;
    bool containsDockWidget(KDDockWidgets::Controllers::DockWidget *arg__1) const;
    static KDDockWidgets::Controllers::Group *
    createCentralFrame(QFlags<KDDockWidgets::MainWindowOption> options);
    virtual void customEvent(QEvent *event);
    virtual void customEvent_nocallback(QEvent *event);
    KDDockWidgets::Controllers::DropIndicatorOverlay *dropIndicatorOverlay() const;
    virtual bool event(QEvent *event);
    virtual bool event_nocallback(QEvent *event);
    virtual bool eventFilter(QObject *watched, QEvent *event);
    virtual bool eventFilter_nocallback(QObject *watched, QEvent *event);
    QList<KDDockWidgets::Controllers::Group *> groups() const;
    bool hasSingleFloatingFrame() const;
    bool hasSingleFrame() const;
    bool isMDIWrapper() const;
    void layoutEqually();
    void layoutParentContainerEqually(KDDockWidgets::Controllers::DockWidget *arg__1);
    KDDockWidgets::Controllers::DockWidget *mdiDockWidgetWrapper() const;
    void removeHover();
    virtual void setParentView_impl(KDDockWidgets::View *parent);
    virtual void setParentView_impl_nocallback(KDDockWidgets::View *parent);
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
// KDDockWidgets::Controllers::DropArea::DropArea(KDDockWidgets::View * parent,
// QFlags<KDDockWidgets::MainWindowOption> options, bool isMDIWrapper)
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__DropArea__constructor_View_MainWindowOptions_bool(void *parent_,
                                                                                int options_,
                                                                                bool isMDIWrapper);
// KDDockWidgets::Controllers::DropArea::addDockWidget(KDDockWidgets::Controllers::DockWidget *
// arg__1, KDDockWidgets::Location location, KDDockWidgets::Controllers::DockWidget * relativeTo,
// KDDockWidgets::InitialOption arg__4)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DropArea__addDockWidget_DockWidget_Location_DockWidget_InitialOption(
    void *thisObj, void *arg__1_, int location, void *relativeTo_, void *arg__4_);
// KDDockWidgets::Controllers::DropArea::addMultiSplitter(KDDockWidgets::Controllers::DropArea *
// splitter, KDDockWidgets::Location location, KDDockWidgets::Controllers::Group * relativeTo,
// KDDockWidgets::InitialOption option)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DropArea__addMultiSplitter_DropArea_Location_Group_InitialOption(
    void *thisObj, void *splitter_, int location, void *relativeTo_, void *option_);
// KDDockWidgets::Controllers::DropArea::addWidget(KDDockWidgets::View * widget,
// KDDockWidgets::Location location, KDDockWidgets::Controllers::Group * relativeTo,
// KDDockWidgets::InitialOption option)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DropArea__addWidget_View_Location_Group_InitialOption(
    void *thisObj, void *widget_, int location, void *relativeTo_, void *option_);
// KDDockWidgets::Controllers::DropArea::centralFrame() const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__DropArea__centralFrame(void *thisObj);
// KDDockWidgets::Controllers::DropArea::containsDockWidget(KDDockWidgets::Controllers::DockWidget *
// arg__1) const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__DropArea__containsDockWidget_DockWidget(void *thisObj, void *arg__1_);
// KDDockWidgets::Controllers::DropArea::createCentralFrame(QFlags<KDDockWidgets::MainWindowOption>
// options)
KDDockWidgetsBindings_EXPORT void *
c_static_KDDockWidgets__Controllers__DropArea__createCentralFrame_MainWindowOptions(int options_);
// KDDockWidgets::Controllers::DropArea::customEvent(QEvent * event)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DropArea__customEvent_QEvent(void *thisObj, void *event_);
// KDDockWidgets::Controllers::DropArea::dropIndicatorOverlay() const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__DropArea__dropIndicatorOverlay(void *thisObj);
// KDDockWidgets::Controllers::DropArea::event(QEvent * event)
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__DropArea__event_QEvent(void *thisObj, void *event_);
// KDDockWidgets::Controllers::DropArea::eventFilter(QObject * watched, QEvent * event)
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__DropArea__eventFilter_QObject_QEvent(void *thisObj, void *watched_,
                                                                   void *event_);
// KDDockWidgets::Controllers::DropArea::groups() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controllers__DropArea__groups(void *thisObj);
// KDDockWidgets::Controllers::DropArea::hasSingleFloatingFrame() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__DropArea__hasSingleFloatingFrame(void *thisObj);
// KDDockWidgets::Controllers::DropArea::hasSingleFrame() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__DropArea__hasSingleFrame(void *thisObj);
// KDDockWidgets::Controllers::DropArea::isMDIWrapper() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__DropArea__isMDIWrapper(void *thisObj);
// KDDockWidgets::Controllers::DropArea::layoutEqually()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DropArea__layoutEqually(void *thisObj);
// KDDockWidgets::Controllers::DropArea::layoutParentContainerEqually(KDDockWidgets::Controllers::DockWidget
// * arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DropArea__layoutParentContainerEqually_DockWidget(void *thisObj,
                                                                                void *arg__1_);
// KDDockWidgets::Controllers::DropArea::mdiDockWidgetWrapper() const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__DropArea__mdiDockWidgetWrapper(void *thisObj);
// KDDockWidgets::Controllers::DropArea::removeHover()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DropArea__removeHover(void *thisObj);
// KDDockWidgets::Controllers::DropArea::setParentView_impl(KDDockWidgets::View * parent)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DropArea__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Controllers::DropArea::tr(const char * s, const char * c, int n)
KDDockWidgetsBindings_EXPORT void *
c_static_KDDockWidgets__Controllers__DropArea__tr_char_char_int(const char *s, const char *c,
                                                                int n);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__DropArea__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DropArea__registerVirtualMethodCallback(void *ptr, void *callback,
                                                                      int methodId);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DropArea_Finalizer(void *, void *cppObj, void *);
}

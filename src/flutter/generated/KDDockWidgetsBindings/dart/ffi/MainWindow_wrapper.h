/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <MainWindow.h>
#include <qstring.h>
#include <View.h>
#include <DockWidget.h>
#include <KDDockWidgets.h>
#include <SideBar.h>
#include <DropArea.h>
#include <controllers/Layout.h>
#include <qrect.h>
#include <qpoint.h>
#include <qcoreevent.h>
#include <qobject.h>
#include <qsize.h>

namespace KDDockWidgetsBindings_wrappersNS {
class MainWindow_wrapper : public ::KDDockWidgets::Controllers::MainWindow
{
public:
    ~MainWindow_wrapper();
    MainWindow_wrapper(KDDockWidgets::View *view, const QString &uniqueName,
                       QFlags<KDDockWidgets::MainWindowOption> options);
    void addDockWidget(KDDockWidgets::Controllers::DockWidget *dockWidget,
                       KDDockWidgets::Location location,
                       KDDockWidgets::Controllers::DockWidget *relativeTo = nullptr,
                       KDDockWidgets::InitialOption initialOption = {});
    void addDockWidgetAsTab(KDDockWidgets::Controllers::DockWidget *dockwidget);
    bool anySideBarIsVisible() const;
    QRect centralAreaGeometry() const;
    void clearSideBarOverlay(bool deleteFrame = true);
    bool closeDockWidgets(bool force = false);
    virtual void customEvent(QEvent *event);
    virtual void customEvent_nocallback(QEvent *event);
    KDDockWidgets::Controllers::DropArea *dropArea() const;
    virtual bool event(QEvent *event);
    virtual bool event_nocallback(QEvent *event);
    virtual bool eventFilter(QObject *watched, QEvent *event);
    virtual bool eventFilter_nocallback(QObject *watched, QEvent *event);
    void groupCountChanged(int arg__1);
    bool isMDI() const;
    KDDockWidgets::Controllers::Layout *layout() const;
    void layoutEqually();
    void layoutParentContainerEqually(KDDockWidgets::Controllers::DockWidget *dockWidget);
    void moveToSideBar(KDDockWidgets::Controllers::DockWidget *dw);
    KDDockWidgets::Controllers::DropArea *multiSplitter() const;
    QFlags<KDDockWidgets::MainWindowOption> options() const;
    int overlayMargin() const;
    void overlayMarginChanged(int margin);
    void overlayOnSideBar(KDDockWidgets::Controllers::DockWidget *dw);
    KDDockWidgets::Controllers::DockWidget *overlayedDockWidget() const;
    void restoreFromSideBar(KDDockWidgets::Controllers::DockWidget *dw);
    void setContentsMargins(int l, int t, int r, int b);
    void setOverlayMargin(int margin);
    virtual void setParentView_impl(KDDockWidgets::View *parent);
    virtual void setParentView_impl_nocallback(KDDockWidgets::View *parent);
    void setUniqueName(const QString &uniqueName);
    KDDockWidgets::Controllers::SideBar *
    sideBarForDockWidget(const KDDockWidgets::Controllers::DockWidget *dw) const;
    void toggleOverlayOnSideBar(KDDockWidgets::Controllers::DockWidget *dw);
    static QString tr(const char *s, const char *c, int n);
    QString uniqueName() const;
    void uniqueNameChanged();
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
// KDDockWidgets::Controllers::MainWindow::MainWindow(KDDockWidgets::View * view, const QString &
// uniqueName, QFlags<KDDockWidgets::MainWindowOption> options)
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__MainWindow__constructor_View_QString_MainWindowOptions(
    void *view_, const char *uniqueName_, int options_);
// KDDockWidgets::Controllers::MainWindow::addDockWidget(KDDockWidgets::Controllers::DockWidget *
// dockWidget, KDDockWidgets::Location location, KDDockWidgets::Controllers::DockWidget *
// relativeTo, KDDockWidgets::InitialOption initialOption)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__MainWindow__addDockWidget_DockWidget_Location_DockWidget_InitialOption(
    void *thisObj, void *dockWidget_, int location, void *relativeTo_, void *initialOption_);
// KDDockWidgets::Controllers::MainWindow::addDockWidgetAsTab(KDDockWidgets::Controllers::DockWidget
// * dockwidget)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__MainWindow__addDockWidgetAsTab_DockWidget(void *thisObj,
                                                                        void *dockwidget_);
// KDDockWidgets::Controllers::MainWindow::anySideBarIsVisible() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__MainWindow__anySideBarIsVisible(void *thisObj);
// KDDockWidgets::Controllers::MainWindow::centralAreaGeometry() const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__MainWindow__centralAreaGeometry(void *thisObj);
// KDDockWidgets::Controllers::MainWindow::clearSideBarOverlay(bool deleteFrame)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__MainWindow__clearSideBarOverlay_bool(void *thisObj, bool deleteFrame);
// KDDockWidgets::Controllers::MainWindow::closeDockWidgets(bool force)
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__MainWindow__closeDockWidgets_bool(void *thisObj, bool force);
// KDDockWidgets::Controllers::MainWindow::customEvent(QEvent * event)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__MainWindow__customEvent_QEvent(void *thisObj, void *event_);
// KDDockWidgets::Controllers::MainWindow::dropArea() const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__MainWindow__dropArea(void *thisObj);
// KDDockWidgets::Controllers::MainWindow::event(QEvent * event)
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__MainWindow__event_QEvent(void *thisObj, void *event_);
// KDDockWidgets::Controllers::MainWindow::eventFilter(QObject * watched, QEvent * event)
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__MainWindow__eventFilter_QObject_QEvent(void *thisObj, void *watched_,
                                                                     void *event_);
// KDDockWidgets::Controllers::MainWindow::groupCountChanged(int arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__MainWindow__groupCountChanged_int(void *thisObj, int arg__1);
// KDDockWidgets::Controllers::MainWindow::isMDI() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__MainWindow__isMDI(void *thisObj);
// KDDockWidgets::Controllers::MainWindow::layout() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controllers__MainWindow__layout(void *thisObj);
// KDDockWidgets::Controllers::MainWindow::layoutEqually()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__MainWindow__layoutEqually(void *thisObj);
// KDDockWidgets::Controllers::MainWindow::layoutParentContainerEqually(KDDockWidgets::Controllers::DockWidget
// * dockWidget)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__MainWindow__layoutParentContainerEqually_DockWidget(
    void *thisObj, void *dockWidget_);
// KDDockWidgets::Controllers::MainWindow::moveToSideBar(KDDockWidgets::Controllers::DockWidget *
// dw)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__MainWindow__moveToSideBar_DockWidget(void *thisObj, void *dw_);
// KDDockWidgets::Controllers::MainWindow::multiSplitter() const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__MainWindow__multiSplitter(void *thisObj);
// KDDockWidgets::Controllers::MainWindow::options() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Controllers__MainWindow__options(void *thisObj);
// KDDockWidgets::Controllers::MainWindow::overlayMargin() const
KDDockWidgetsBindings_EXPORT int
c_KDDockWidgets__Controllers__MainWindow__overlayMargin(void *thisObj);
// KDDockWidgets::Controllers::MainWindow::overlayMarginChanged(int margin)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__MainWindow__overlayMarginChanged_int(void *thisObj, int margin);
// KDDockWidgets::Controllers::MainWindow::overlayOnSideBar(KDDockWidgets::Controllers::DockWidget *
// dw)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__MainWindow__overlayOnSideBar_DockWidget(void *thisObj, void *dw_);
// KDDockWidgets::Controllers::MainWindow::overlayedDockWidget() const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__MainWindow__overlayedDockWidget(void *thisObj);
// KDDockWidgets::Controllers::MainWindow::restoreFromSideBar(KDDockWidgets::Controllers::DockWidget
// * dw)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__MainWindow__restoreFromSideBar_DockWidget(void *thisObj, void *dw_);
// KDDockWidgets::Controllers::MainWindow::setContentsMargins(int l, int t, int r, int b)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__MainWindow__setContentsMargins_int_int_int_int(void *thisObj, int l,
                                                                             int t, int r, int b);
// KDDockWidgets::Controllers::MainWindow::setOverlayMargin(int margin)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__MainWindow__setOverlayMargin_int(void *thisObj, int margin);
// KDDockWidgets::Controllers::MainWindow::setParentView_impl(KDDockWidgets::View * parent)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__MainWindow__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Controllers::MainWindow::setUniqueName(const QString & uniqueName)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__MainWindow__setUniqueName_QString(void *thisObj,
                                                                const char *uniqueName_);
// KDDockWidgets::Controllers::MainWindow::sideBarForDockWidget(const
// KDDockWidgets::Controllers::DockWidget * dw) const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__MainWindow__sideBarForDockWidget_DockWidget(void *thisObj, void *dw_);
// KDDockWidgets::Controllers::MainWindow::toggleOverlayOnSideBar(KDDockWidgets::Controllers::DockWidget
// * dw)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__MainWindow__toggleOverlayOnSideBar_DockWidget(void *thisObj,
                                                                            void *dw_);
// KDDockWidgets::Controllers::MainWindow::tr(const char * s, const char * c, int n)
KDDockWidgetsBindings_EXPORT void *
c_static_KDDockWidgets__Controllers__MainWindow__tr_char_char_int(const char *s, const char *c,
                                                                  int n);
// KDDockWidgets::Controllers::MainWindow::uniqueName() const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__MainWindow__uniqueName(void *thisObj);
// KDDockWidgets::Controllers::MainWindow::uniqueNameChanged()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__MainWindow__uniqueNameChanged(void *thisObj);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__MainWindow__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__MainWindow__registerVirtualMethodCallback(void *ptr, void *callback,
                                                                        int methodId);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__MainWindow_Finalizer(void *, void *cppObj, void *);
}

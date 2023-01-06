/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "MainWindow_wrapper.h"


#include <QDebug>


namespace Dartagnan {

typedef int (*CleanupCallback)(void *thisPtr);
static CleanupCallback s_cleanupCallback = nullptr;

template<typename T>
struct ValueWrapper
{
    T value;
};

}
namespace KDDockWidgetsBindings_wrappersNS {
MainWindow_wrapper::MainWindow_wrapper(KDDockWidgets::View *view, const QString &uniqueName,
                                       QFlags<KDDockWidgets::MainWindowOption> options)
    : ::KDDockWidgets::Controllers::MainWindow(view, uniqueName, options)
{
}
void MainWindow_wrapper::addDockWidget(KDDockWidgets::Controllers::DockWidget *dockWidget,
                                       KDDockWidgets::Location location,
                                       KDDockWidgets::Controllers::DockWidget *relativeTo,
                                       KDDockWidgets::InitialOption initialOption)
{
    ::KDDockWidgets::Controllers::MainWindow::addDockWidget(dockWidget, location, relativeTo,
                                                            initialOption);
}
void MainWindow_wrapper::addDockWidgetAsTab(KDDockWidgets::Controllers::DockWidget *dockwidget)
{
    ::KDDockWidgets::Controllers::MainWindow::addDockWidgetAsTab(dockwidget);
}
bool MainWindow_wrapper::anySideBarIsVisible() const
{
    return ::KDDockWidgets::Controllers::MainWindow::anySideBarIsVisible();
}
QRect MainWindow_wrapper::centralAreaGeometry() const
{
    return ::KDDockWidgets::Controllers::MainWindow::centralAreaGeometry();
}
void MainWindow_wrapper::clearSideBarOverlay(bool deleteFrame)
{
    ::KDDockWidgets::Controllers::MainWindow::clearSideBarOverlay(deleteFrame);
}
bool MainWindow_wrapper::closeDockWidgets(bool force)
{
    return ::KDDockWidgets::Controllers::MainWindow::closeDockWidgets(force);
}
void MainWindow_wrapper::customEvent(QEvent *event)
{
    if (m_customEventCallback) {
        const void *thisPtr = this;
        m_customEventCallback(const_cast<void *>(thisPtr), event);
    } else {
        ::KDDockWidgets::Controllers::MainWindow::customEvent(event);
    }
}
void MainWindow_wrapper::customEvent_nocallback(QEvent *event)
{
    ::KDDockWidgets::Controllers::MainWindow::customEvent(event);
}
KDDockWidgets::Controllers::DropArea *MainWindow_wrapper::dropArea() const
{
    return ::KDDockWidgets::Controllers::MainWindow::dropArea();
}
bool MainWindow_wrapper::event(QEvent *event)
{
    if (m_eventCallback) {
        const void *thisPtr = this;
        return m_eventCallback(const_cast<void *>(thisPtr), event);
    } else {
        return ::KDDockWidgets::Controllers::MainWindow::event(event);
    }
}
bool MainWindow_wrapper::event_nocallback(QEvent *event)
{
    return ::KDDockWidgets::Controllers::MainWindow::event(event);
}
bool MainWindow_wrapper::eventFilter(QObject *watched, QEvent *event)
{
    if (m_eventFilterCallback) {
        const void *thisPtr = this;
        return m_eventFilterCallback(const_cast<void *>(thisPtr), watched, event);
    } else {
        return ::KDDockWidgets::Controllers::MainWindow::eventFilter(watched, event);
    }
}
bool MainWindow_wrapper::eventFilter_nocallback(QObject *watched, QEvent *event)
{
    return ::KDDockWidgets::Controllers::MainWindow::eventFilter(watched, event);
}
void MainWindow_wrapper::groupCountChanged(int arg__1)
{
    ::KDDockWidgets::Controllers::MainWindow::groupCountChanged(arg__1);
}
bool MainWindow_wrapper::isMDI() const
{
    return ::KDDockWidgets::Controllers::MainWindow::isMDI();
}
KDDockWidgets::Controllers::Layout *MainWindow_wrapper::layout() const
{
    return ::KDDockWidgets::Controllers::MainWindow::layout();
}
void MainWindow_wrapper::layoutEqually()
{
    ::KDDockWidgets::Controllers::MainWindow::layoutEqually();
}
void MainWindow_wrapper::layoutParentContainerEqually(
    KDDockWidgets::Controllers::DockWidget *dockWidget)
{
    ::KDDockWidgets::Controllers::MainWindow::layoutParentContainerEqually(dockWidget);
}
void MainWindow_wrapper::moveToSideBar(KDDockWidgets::Controllers::DockWidget *dw)
{
    ::KDDockWidgets::Controllers::MainWindow::moveToSideBar(dw);
}
KDDockWidgets::Controllers::DropArea *MainWindow_wrapper::multiSplitter() const
{
    return ::KDDockWidgets::Controllers::MainWindow::multiSplitter();
}
QFlags<KDDockWidgets::MainWindowOption> MainWindow_wrapper::options() const
{
    return ::KDDockWidgets::Controllers::MainWindow::options();
}
int MainWindow_wrapper::overlayMargin() const
{
    return ::KDDockWidgets::Controllers::MainWindow::overlayMargin();
}
void MainWindow_wrapper::overlayMarginChanged(int margin)
{
    ::KDDockWidgets::Controllers::MainWindow::overlayMarginChanged(margin);
}
void MainWindow_wrapper::overlayOnSideBar(KDDockWidgets::Controllers::DockWidget *dw)
{
    ::KDDockWidgets::Controllers::MainWindow::overlayOnSideBar(dw);
}
KDDockWidgets::Controllers::DockWidget *MainWindow_wrapper::overlayedDockWidget() const
{
    return ::KDDockWidgets::Controllers::MainWindow::overlayedDockWidget();
}
void MainWindow_wrapper::restoreFromSideBar(KDDockWidgets::Controllers::DockWidget *dw)
{
    ::KDDockWidgets::Controllers::MainWindow::restoreFromSideBar(dw);
}
void MainWindow_wrapper::setContentsMargins(int l, int t, int r, int b)
{
    ::KDDockWidgets::Controllers::MainWindow::setContentsMargins(l, t, r, b);
}
void MainWindow_wrapper::setOverlayMargin(int margin)
{
    ::KDDockWidgets::Controllers::MainWindow::setOverlayMargin(margin);
}
void MainWindow_wrapper::setParentView_impl(KDDockWidgets::View *parent)
{
    if (m_setParentView_implCallback) {
        const void *thisPtr = this;
        m_setParentView_implCallback(const_cast<void *>(thisPtr), parent);
    } else {
        ::KDDockWidgets::Controllers::MainWindow::setParentView_impl(parent);
    }
}
void MainWindow_wrapper::setParentView_impl_nocallback(KDDockWidgets::View *parent)
{
    ::KDDockWidgets::Controllers::MainWindow::setParentView_impl(parent);
}
void MainWindow_wrapper::setUniqueName(const QString &uniqueName)
{
    ::KDDockWidgets::Controllers::MainWindow::setUniqueName(uniqueName);
}
KDDockWidgets::Controllers::SideBar *
MainWindow_wrapper::sideBarForDockWidget(const KDDockWidgets::Controllers::DockWidget *dw) const
{
    return ::KDDockWidgets::Controllers::MainWindow::sideBarForDockWidget(dw);
}
void MainWindow_wrapper::toggleOverlayOnSideBar(KDDockWidgets::Controllers::DockWidget *dw)
{
    ::KDDockWidgets::Controllers::MainWindow::toggleOverlayOnSideBar(dw);
}
QString MainWindow_wrapper::tr(const char *s, const char *c, int n)
{
    return ::KDDockWidgets::Controllers::MainWindow::tr(s, c, n);
}
QString MainWindow_wrapper::uniqueName() const
{
    return ::KDDockWidgets::Controllers::MainWindow::uniqueName();
}
void MainWindow_wrapper::uniqueNameChanged()
{
    ::KDDockWidgets::Controllers::MainWindow::uniqueNameChanged();
}
MainWindow_wrapper::~MainWindow_wrapper()
{
}

}
static KDDockWidgets::Controllers::MainWindow *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::Controllers::MainWindow *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::MainWindow_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::MainWindow_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__Controllers__MainWindow_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::MainWindow_wrapper *>(cppObj);
}
void *c_KDDockWidgets__Controllers__MainWindow__constructor_View_QString_MainWindowOptions(
    void *view_, const char *uniqueName_, int options_)
{
    auto view = reinterpret_cast<KDDockWidgets::View *>(view_);
    const auto uniqueName = QString::fromUtf8(uniqueName_);
    auto options = static_cast<QFlags<KDDockWidgets::MainWindowOption>>(options_);
    auto ptr = new KDDockWidgetsBindings_wrappersNS::MainWindow_wrapper(view, uniqueName, options);
    return reinterpret_cast<void *>(ptr);
}
// addDockWidget(KDDockWidgets::Controllers::DockWidget * dockWidget, KDDockWidgets::Location
// location, KDDockWidgets::Controllers::DockWidget * relativeTo, KDDockWidgets::InitialOption
// initialOption)
void c_KDDockWidgets__Controllers__MainWindow__addDockWidget_DockWidget_Location_DockWidget_InitialOption(
    void *thisObj, void *dockWidget_, int location, void *relativeTo_, void *initialOption_)
{
    auto dockWidget = reinterpret_cast<KDDockWidgets::Controllers::DockWidget *>(dockWidget_);
    auto relativeTo = reinterpret_cast<KDDockWidgets::Controllers::DockWidget *>(relativeTo_);
    assert(initialOption_);
    auto &initialOption = *reinterpret_cast<KDDockWidgets::InitialOption *>(initialOption_);
    fromPtr(thisObj)->addDockWidget(dockWidget, static_cast<KDDockWidgets::Location>(location),
                                    relativeTo, initialOption);
}
// addDockWidgetAsTab(KDDockWidgets::Controllers::DockWidget * dockwidget)
void c_KDDockWidgets__Controllers__MainWindow__addDockWidgetAsTab_DockWidget(void *thisObj,
                                                                             void *dockwidget_)
{
    auto dockwidget = reinterpret_cast<KDDockWidgets::Controllers::DockWidget *>(dockwidget_);
    fromPtr(thisObj)->addDockWidgetAsTab(dockwidget);
}
// anySideBarIsVisible() const
bool c_KDDockWidgets__Controllers__MainWindow__anySideBarIsVisible(void *thisObj)
{
    return fromPtr(thisObj)->anySideBarIsVisible();
}
// centralAreaGeometry() const
void *c_KDDockWidgets__Controllers__MainWindow__centralAreaGeometry(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QRect> { fromWrapperPtr(thisObj)->centralAreaGeometry() };
}
// clearSideBarOverlay(bool deleteFrame)
void c_KDDockWidgets__Controllers__MainWindow__clearSideBarOverlay_bool(void *thisObj,
                                                                        bool deleteFrame)
{
    fromPtr(thisObj)->clearSideBarOverlay(deleteFrame);
}
// closeDockWidgets(bool force)
bool c_KDDockWidgets__Controllers__MainWindow__closeDockWidgets_bool(void *thisObj, bool force)
{
    return fromPtr(thisObj)->closeDockWidgets(force);
}
// customEvent(QEvent * event)
void c_KDDockWidgets__Controllers__MainWindow__customEvent_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    fromWrapperPtr(thisObj)->customEvent_nocallback(event);
}
// dropArea() const
void *c_KDDockWidgets__Controllers__MainWindow__dropArea(void *thisObj)
{
    return fromPtr(thisObj)->dropArea();
}
// event(QEvent * event)
bool c_KDDockWidgets__Controllers__MainWindow__event_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::MainWindow_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->event_nocallback(event);
        } else {
            return targetPtr->event(event);
        }
    }();
}
// eventFilter(QObject * watched, QEvent * event)
bool c_KDDockWidgets__Controllers__MainWindow__eventFilter_QObject_QEvent(void *thisObj,
                                                                          void *watched_,
                                                                          void *event_)
{
    auto watched = reinterpret_cast<QObject *>(watched_);
    auto event = reinterpret_cast<QEvent *>(event_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::MainWindow_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->eventFilter_nocallback(watched, event);
        } else {
            return targetPtr->eventFilter(watched, event);
        }
    }();
}
// groupCountChanged(int arg__1)
void c_KDDockWidgets__Controllers__MainWindow__groupCountChanged_int(void *thisObj, int arg__1)
{
    fromPtr(thisObj)->groupCountChanged(arg__1);
}
// isMDI() const
bool c_KDDockWidgets__Controllers__MainWindow__isMDI(void *thisObj)
{
    return fromPtr(thisObj)->isMDI();
}
// layout() const
void *c_KDDockWidgets__Controllers__MainWindow__layout(void *thisObj)
{
    return fromPtr(thisObj)->layout();
}
// layoutEqually()
void c_KDDockWidgets__Controllers__MainWindow__layoutEqually(void *thisObj)
{
    fromPtr(thisObj)->layoutEqually();
}
// layoutParentContainerEqually(KDDockWidgets::Controllers::DockWidget * dockWidget)
void c_KDDockWidgets__Controllers__MainWindow__layoutParentContainerEqually_DockWidget(
    void *thisObj, void *dockWidget_)
{
    auto dockWidget = reinterpret_cast<KDDockWidgets::Controllers::DockWidget *>(dockWidget_);
    fromPtr(thisObj)->layoutParentContainerEqually(dockWidget);
}
// moveToSideBar(KDDockWidgets::Controllers::DockWidget * dw)
void c_KDDockWidgets__Controllers__MainWindow__moveToSideBar_DockWidget(void *thisObj, void *dw_)
{
    auto dw = reinterpret_cast<KDDockWidgets::Controllers::DockWidget *>(dw_);
    fromPtr(thisObj)->moveToSideBar(dw);
}
// multiSplitter() const
void *c_KDDockWidgets__Controllers__MainWindow__multiSplitter(void *thisObj)
{
    return fromPtr(thisObj)->multiSplitter();
}
// options() const
int c_KDDockWidgets__Controllers__MainWindow__options(void *thisObj)
{
    return fromPtr(thisObj)->options();
}
// overlayMargin() const
int c_KDDockWidgets__Controllers__MainWindow__overlayMargin(void *thisObj)
{
    return fromPtr(thisObj)->overlayMargin();
}
// overlayMarginChanged(int margin)
void c_KDDockWidgets__Controllers__MainWindow__overlayMarginChanged_int(void *thisObj, int margin)
{
    fromPtr(thisObj)->overlayMarginChanged(margin);
}
// overlayOnSideBar(KDDockWidgets::Controllers::DockWidget * dw)
void c_KDDockWidgets__Controllers__MainWindow__overlayOnSideBar_DockWidget(void *thisObj, void *dw_)
{
    auto dw = reinterpret_cast<KDDockWidgets::Controllers::DockWidget *>(dw_);
    fromPtr(thisObj)->overlayOnSideBar(dw);
}
// overlayedDockWidget() const
void *c_KDDockWidgets__Controllers__MainWindow__overlayedDockWidget(void *thisObj)
{
    return fromPtr(thisObj)->overlayedDockWidget();
}
// restoreFromSideBar(KDDockWidgets::Controllers::DockWidget * dw)
void c_KDDockWidgets__Controllers__MainWindow__restoreFromSideBar_DockWidget(void *thisObj,
                                                                             void *dw_)
{
    auto dw = reinterpret_cast<KDDockWidgets::Controllers::DockWidget *>(dw_);
    fromPtr(thisObj)->restoreFromSideBar(dw);
}
// setContentsMargins(int l, int t, int r, int b)
void c_KDDockWidgets__Controllers__MainWindow__setContentsMargins_int_int_int_int(void *thisObj,
                                                                                  int l, int t,
                                                                                  int r, int b)
{
    fromPtr(thisObj)->setContentsMargins(l, t, r, b);
}
// setOverlayMargin(int margin)
void c_KDDockWidgets__Controllers__MainWindow__setOverlayMargin_int(void *thisObj, int margin)
{
    fromPtr(thisObj)->setOverlayMargin(margin);
}
// setParentView_impl(KDDockWidgets::View * parent)
void c_KDDockWidgets__Controllers__MainWindow__setParentView_impl_View(void *thisObj, void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    fromWrapperPtr(thisObj)->setParentView_impl_nocallback(parent);
}
// setUniqueName(const QString & uniqueName)
void c_KDDockWidgets__Controllers__MainWindow__setUniqueName_QString(void *thisObj,
                                                                     const char *uniqueName_)
{
    const auto uniqueName = QString::fromUtf8(uniqueName_);
    fromWrapperPtr(thisObj)->setUniqueName(uniqueName);
}
// sideBarForDockWidget(const KDDockWidgets::Controllers::DockWidget * dw) const
void *c_KDDockWidgets__Controllers__MainWindow__sideBarForDockWidget_DockWidget(void *thisObj,
                                                                                void *dw_)
{
    auto dw = reinterpret_cast<KDDockWidgets::Controllers::DockWidget *>(dw_);
    return fromPtr(thisObj)->sideBarForDockWidget(dw);
}
// toggleOverlayOnSideBar(KDDockWidgets::Controllers::DockWidget * dw)
void c_KDDockWidgets__Controllers__MainWindow__toggleOverlayOnSideBar_DockWidget(void *thisObj,
                                                                                 void *dw_)
{
    auto dw = reinterpret_cast<KDDockWidgets::Controllers::DockWidget *>(dw_);
    fromPtr(thisObj)->toggleOverlayOnSideBar(dw);
}
// tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__Controllers__MainWindow__tr_char_char_int(const char *s,
                                                                        const char *c, int n)
{
    return new Dartagnan::ValueWrapper<QString> {
        KDDockWidgetsBindings_wrappersNS::MainWindow_wrapper::tr(s, c, n)
    };
}
// uniqueName() const
void *c_KDDockWidgets__Controllers__MainWindow__uniqueName(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QString> { fromPtr(thisObj)->uniqueName() };
}
// uniqueNameChanged()
void c_KDDockWidgets__Controllers__MainWindow__uniqueNameChanged(void *thisObj)
{
    fromPtr(thisObj)->uniqueNameChanged();
}
void c_KDDockWidgets__Controllers__MainWindow__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__Controllers__MainWindow__registerVirtualMethodCallback(void *ptr,
                                                                             void *callback,
                                                                             int methodId)
{
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 295:
        wrapper->m_customEventCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::MainWindow_wrapper::Callback_customEvent>(callback);
        break;
    case 306:
        wrapper->m_eventCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::MainWindow_wrapper::Callback_event>(
                callback);
        break;
    case 307:
        wrapper->m_eventFilterCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::MainWindow_wrapper::Callback_eventFilter>(callback);
        break;
    case 891:
        wrapper->m_setParentView_implCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::MainWindow_wrapper::Callback_setParentView_impl>(
            callback);
        break;
    }
}
}

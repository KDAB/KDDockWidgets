/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "DockWidget_wrapper.h"


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
DockWidget_wrapper::DockWidget_wrapper(KDDockWidgets::View *view, const QString &uniqueName,
                                       QFlags<KDDockWidgets::DockWidgetOption> options,
                                       QFlags<KDDockWidgets::LayoutSaverOption> layoutSaverOptions)
    : ::KDDockWidgets::Controllers::DockWidget(view, uniqueName, options, layoutSaverOptions)
{
}
void DockWidget_wrapper::aboutToDelete(KDDockWidgets::Controllers::DockWidget *arg__1)
{
    ::KDDockWidgets::Controllers::DockWidget::aboutToDelete(arg__1);
}
void DockWidget_wrapper::aboutToDeleteOnClose()
{
    ::KDDockWidgets::Controllers::DockWidget::aboutToDeleteOnClose();
}
void DockWidget_wrapper::actualTitleBarChanged()
{
    ::KDDockWidgets::Controllers::DockWidget::actualTitleBarChanged();
}
void DockWidget_wrapper::addDockWidgetAsTab(KDDockWidgets::Controllers::DockWidget *other,
                                            KDDockWidgets::InitialOption initialOption)
{
    ::KDDockWidgets::Controllers::DockWidget::addDockWidgetAsTab(other, initialOption);
}
void DockWidget_wrapper::addDockWidgetToContainingWindow(
    KDDockWidgets::Controllers::DockWidget *other, KDDockWidgets::Location location,
    KDDockWidgets::Controllers::DockWidget *relativeTo, KDDockWidgets::InitialOption initialOption)
{
    ::KDDockWidgets::Controllers::DockWidget::addDockWidgetToContainingWindow(
        other, location, relativeTo, initialOption);
}
KDDockWidgets::Controllers::DockWidget *DockWidget_wrapper::byName(const QString &uniqueName)
{
    return ::KDDockWidgets::Controllers::DockWidget::byName(uniqueName);
}
int DockWidget_wrapper::currentTabIndex() const
{
    return ::KDDockWidgets::Controllers::DockWidget::currentTabIndex();
}
void DockWidget_wrapper::customEvent(QEvent *event)
{
    if (m_customEventCallback) {
        const void *thisPtr = this;
        m_customEventCallback(const_cast<void *>(thisPtr), event);
    } else {
        ::KDDockWidgets::Controllers::DockWidget::customEvent(event);
    }
}
void DockWidget_wrapper::customEvent_nocallback(QEvent *event)
{
    ::KDDockWidgets::Controllers::DockWidget::customEvent(event);
}
bool DockWidget_wrapper::event(QEvent *event)
{
    if (m_eventCallback) {
        const void *thisPtr = this;
        return m_eventCallback(const_cast<void *>(thisPtr), event);
    } else {
        return ::KDDockWidgets::Controllers::DockWidget::event(event);
    }
}
bool DockWidget_wrapper::event_nocallback(QEvent *event)
{
    return ::KDDockWidgets::Controllers::DockWidget::event(event);
}
bool DockWidget_wrapper::eventFilter(QObject *watched, QEvent *event)
{
    if (m_eventFilterCallback) {
        const void *thisPtr = this;
        return m_eventFilterCallback(const_cast<void *>(thisPtr), watched, event);
    } else {
        return ::KDDockWidgets::Controllers::DockWidget::eventFilter(watched, event);
    }
}
bool DockWidget_wrapper::eventFilter_nocallback(QObject *watched, QEvent *event)
{
    return ::KDDockWidgets::Controllers::DockWidget::eventFilter(watched, event);
}
KDDockWidgets::Controllers::FloatingWindow *DockWidget_wrapper::floatingWindow() const
{
    return ::KDDockWidgets::Controllers::DockWidget::floatingWindow();
}
void DockWidget_wrapper::forceClose()
{
    ::KDDockWidgets::Controllers::DockWidget::forceClose();
}
QRect DockWidget_wrapper::groupGeometry() const
{
    return ::KDDockWidgets::Controllers::DockWidget::groupGeometry();
}
void DockWidget_wrapper::guestViewChanged()
{
    ::KDDockWidgets::Controllers::DockWidget::guestViewChanged();
}
bool DockWidget_wrapper::hasPreviousDockedLocation() const
{
    return ::KDDockWidgets::Controllers::DockWidget::hasPreviousDockedLocation();
}
void DockWidget_wrapper::hidden()
{
    ::KDDockWidgets::Controllers::DockWidget::hidden();
}
void DockWidget_wrapper::iconChanged()
{
    ::KDDockWidgets::Controllers::DockWidget::iconChanged();
}
void DockWidget_wrapper::init()
{
    ::KDDockWidgets::Controllers::DockWidget::init();
}
bool DockWidget_wrapper::isCurrentTab() const
{
    return ::KDDockWidgets::Controllers::DockWidget::isCurrentTab();
}
bool DockWidget_wrapper::isFloating() const
{
    return ::KDDockWidgets::Controllers::DockWidget::isFloating();
}
void DockWidget_wrapper::isFloatingChanged(bool arg__1)
{
    ::KDDockWidgets::Controllers::DockWidget::isFloatingChanged(arg__1);
}
bool DockWidget_wrapper::isFocused() const
{
    return ::KDDockWidgets::Controllers::DockWidget::isFocused();
}
void DockWidget_wrapper::isFocusedChanged(bool arg__1)
{
    ::KDDockWidgets::Controllers::DockWidget::isFocusedChanged(arg__1);
}
bool DockWidget_wrapper::isInMainWindow() const
{
    return ::KDDockWidgets::Controllers::DockWidget::isInMainWindow();
}
bool DockWidget_wrapper::isInSideBar() const
{
    return ::KDDockWidgets::Controllers::DockWidget::isInSideBar();
}
bool DockWidget_wrapper::isMainWindow() const
{
    return ::KDDockWidgets::Controllers::DockWidget::isMainWindow();
}
bool DockWidget_wrapper::isOpen() const
{
    return ::KDDockWidgets::Controllers::DockWidget::isOpen();
}
bool DockWidget_wrapper::isOverlayed() const
{
    return ::KDDockWidgets::Controllers::DockWidget::isOverlayed();
}
void DockWidget_wrapper::isOverlayedChanged(bool arg__1)
{
    ::KDDockWidgets::Controllers::DockWidget::isOverlayedChanged(arg__1);
}
bool DockWidget_wrapper::isPersistentCentralDockWidget() const
{
    return ::KDDockWidgets::Controllers::DockWidget::isPersistentCentralDockWidget();
}
bool DockWidget_wrapper::isTabbed() const
{
    return ::KDDockWidgets::Controllers::DockWidget::isTabbed();
}
QSize DockWidget_wrapper::lastOverlayedSize() const
{
    return ::KDDockWidgets::Controllers::DockWidget::lastOverlayedSize();
}
QFlags<KDDockWidgets::LayoutSaverOption> DockWidget_wrapper::layoutSaverOptions() const
{
    return ::KDDockWidgets::Controllers::DockWidget::layoutSaverOptions();
}
KDDockWidgets::Controllers::MainWindow *DockWidget_wrapper::mainWindow() const
{
    return ::KDDockWidgets::Controllers::DockWidget::mainWindow();
}
void DockWidget_wrapper::moveToSideBar()
{
    ::KDDockWidgets::Controllers::DockWidget::moveToSideBar();
}
void DockWidget_wrapper::onHidden(bool spontaneous)
{
    ::KDDockWidgets::Controllers::DockWidget::onHidden(spontaneous);
}
void DockWidget_wrapper::onResize(QSize newSize)
{
    ::KDDockWidgets::Controllers::DockWidget::onResize(newSize);
}
void DockWidget_wrapper::onShown(bool spontaneous)
{
    ::KDDockWidgets::Controllers::DockWidget::onShown(spontaneous);
}
QFlags<KDDockWidgets::DockWidgetOption> DockWidget_wrapper::options() const
{
    return ::KDDockWidgets::Controllers::DockWidget::options();
}
void DockWidget_wrapper::optionsChanged(QFlags<KDDockWidgets::DockWidgetOption> arg__1)
{
    ::KDDockWidgets::Controllers::DockWidget::optionsChanged(arg__1);
}
void DockWidget_wrapper::raise()
{
    ::KDDockWidgets::Controllers::DockWidget::raise();
}
void DockWidget_wrapper::removedFromSideBar()
{
    ::KDDockWidgets::Controllers::DockWidget::removedFromSideBar();
}
void DockWidget_wrapper::setAffinityName(const QString &name)
{
    ::KDDockWidgets::Controllers::DockWidget::setAffinityName(name);
}
void DockWidget_wrapper::setAsCurrentTab()
{
    ::KDDockWidgets::Controllers::DockWidget::setAsCurrentTab();
}
bool DockWidget_wrapper::setFloating(bool floats)
{
    return ::KDDockWidgets::Controllers::DockWidget::setFloating(floats);
}
void DockWidget_wrapper::setFloatingGeometry(QRect geo)
{
    ::KDDockWidgets::Controllers::DockWidget::setFloatingGeometry(geo);
}
void DockWidget_wrapper::setMDIPosition(QPoint pos)
{
    ::KDDockWidgets::Controllers::DockWidget::setMDIPosition(pos);
}
void DockWidget_wrapper::setMDISize(QSize size)
{
    ::KDDockWidgets::Controllers::DockWidget::setMDISize(size);
}
void DockWidget_wrapper::setMDIZ(int z)
{
    ::KDDockWidgets::Controllers::DockWidget::setMDIZ(z);
}
void DockWidget_wrapper::setOptions(QFlags<KDDockWidgets::DockWidgetOption> arg__1)
{
    ::KDDockWidgets::Controllers::DockWidget::setOptions(arg__1);
}
void DockWidget_wrapper::setParentView_impl(KDDockWidgets::View *parent)
{
    if (m_setParentView_implCallback) {
        const void *thisPtr = this;
        m_setParentView_implCallback(const_cast<void *>(thisPtr), parent);
    } else {
        ::KDDockWidgets::Controllers::DockWidget::setParentView_impl(parent);
    }
}
void DockWidget_wrapper::setParentView_impl_nocallback(KDDockWidgets::View *parent)
{
    ::KDDockWidgets::Controllers::DockWidget::setParentView_impl(parent);
}
void DockWidget_wrapper::setTitle(const QString &title)
{
    ::KDDockWidgets::Controllers::DockWidget::setTitle(title);
}
void DockWidget_wrapper::setUserType(int userType)
{
    ::KDDockWidgets::Controllers::DockWidget::setUserType(userType);
}
void DockWidget_wrapper::show()
{
    ::KDDockWidgets::Controllers::DockWidget::show();
}
void DockWidget_wrapper::shown()
{
    ::KDDockWidgets::Controllers::DockWidget::shown();
}
bool DockWidget_wrapper::skipsRestore() const
{
    return ::KDDockWidgets::Controllers::DockWidget::skipsRestore();
}
int DockWidget_wrapper::tabIndex() const
{
    return ::KDDockWidgets::Controllers::DockWidget::tabIndex();
}
QString DockWidget_wrapper::title() const
{
    return ::KDDockWidgets::Controllers::DockWidget::title();
}
KDDockWidgets::Controllers::TitleBar *DockWidget_wrapper::titleBar() const
{
    return ::KDDockWidgets::Controllers::DockWidget::titleBar();
}
void DockWidget_wrapper::titleChanged(const QString &title)
{
    ::KDDockWidgets::Controllers::DockWidget::titleChanged(title);
}
QString DockWidget_wrapper::tr(const char *s, const char *c, int n)
{
    return ::KDDockWidgets::Controllers::DockWidget::tr(s, c, n);
}
QString DockWidget_wrapper::uniqueName() const
{
    return ::KDDockWidgets::Controllers::DockWidget::uniqueName();
}
int DockWidget_wrapper::userType() const
{
    return ::KDDockWidgets::Controllers::DockWidget::userType();
}
void DockWidget_wrapper::windowActiveAboutToChange(bool activated)
{
    ::KDDockWidgets::Controllers::DockWidget::windowActiveAboutToChange(activated);
}
DockWidget_wrapper::~DockWidget_wrapper()
{
}

}
static KDDockWidgets::Controllers::DockWidget *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::Controllers::DockWidget *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::DockWidget_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::DockWidget_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__Controllers__DockWidget_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::DockWidget_wrapper *>(cppObj);
}
void *
c_KDDockWidgets__Controllers__DockWidget__constructor_View_QString_DockWidgetOptions_LayoutSaverOptions(
    void *view_, const char *uniqueName_, int options_, int layoutSaverOptions_)
{
    auto view = reinterpret_cast<KDDockWidgets::View *>(view_);
    const auto uniqueName = QString::fromUtf8(uniqueName_);
    auto options = static_cast<QFlags<KDDockWidgets::DockWidgetOption>>(options_);
    auto layoutSaverOptions =
        static_cast<QFlags<KDDockWidgets::LayoutSaverOption>>(layoutSaverOptions_);
    auto ptr = new KDDockWidgetsBindings_wrappersNS::DockWidget_wrapper(view, uniqueName, options,
                                                                        layoutSaverOptions);
    return reinterpret_cast<void *>(ptr);
}
// aboutToDelete(KDDockWidgets::Controllers::DockWidget * arg__1)
void c_KDDockWidgets__Controllers__DockWidget__aboutToDelete_DockWidget(void *thisObj,
                                                                        void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Controllers::DockWidget *>(arg__1_);
    fromPtr(thisObj)->aboutToDelete(arg__1);
}
// aboutToDeleteOnClose()
void c_KDDockWidgets__Controllers__DockWidget__aboutToDeleteOnClose(void *thisObj)
{
    fromPtr(thisObj)->aboutToDeleteOnClose();
}
// actualTitleBarChanged()
void c_KDDockWidgets__Controllers__DockWidget__actualTitleBarChanged(void *thisObj)
{
    fromPtr(thisObj)->actualTitleBarChanged();
}
// addDockWidgetAsTab(KDDockWidgets::Controllers::DockWidget * other, KDDockWidgets::InitialOption
// initialOption)
void c_KDDockWidgets__Controllers__DockWidget__addDockWidgetAsTab_DockWidget_InitialOption(
    void *thisObj, void *other_, void *initialOption_)
{
    auto other = reinterpret_cast<KDDockWidgets::Controllers::DockWidget *>(other_);
    assert(initialOption_);
    auto &initialOption = *reinterpret_cast<KDDockWidgets::InitialOption *>(initialOption_);
    fromPtr(thisObj)->addDockWidgetAsTab(other, initialOption);
}
// addDockWidgetToContainingWindow(KDDockWidgets::Controllers::DockWidget * other,
// KDDockWidgets::Location location, KDDockWidgets::Controllers::DockWidget * relativeTo,
// KDDockWidgets::InitialOption initialOption)
void c_KDDockWidgets__Controllers__DockWidget__addDockWidgetToContainingWindow_DockWidget_Location_DockWidget_InitialOption(
    void *thisObj, void *other_, int location, void *relativeTo_, void *initialOption_)
{
    auto other = reinterpret_cast<KDDockWidgets::Controllers::DockWidget *>(other_);
    auto relativeTo = reinterpret_cast<KDDockWidgets::Controllers::DockWidget *>(relativeTo_);
    assert(initialOption_);
    auto &initialOption = *reinterpret_cast<KDDockWidgets::InitialOption *>(initialOption_);
    fromPtr(thisObj)->addDockWidgetToContainingWindow(
        other, static_cast<KDDockWidgets::Location>(location), relativeTo, initialOption);
}
// byName(const QString & uniqueName)
void *c_static_KDDockWidgets__Controllers__DockWidget__byName_QString(const char *uniqueName_)
{
    const auto uniqueName = QString::fromUtf8(uniqueName_);
    return KDDockWidgetsBindings_wrappersNS::DockWidget_wrapper::byName(uniqueName);
}
// currentTabIndex() const
int c_KDDockWidgets__Controllers__DockWidget__currentTabIndex(void *thisObj)
{
    return fromPtr(thisObj)->currentTabIndex();
}
// customEvent(QEvent * event)
void c_KDDockWidgets__Controllers__DockWidget__customEvent_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    fromWrapperPtr(thisObj)->customEvent_nocallback(event);
}
// event(QEvent * event)
bool c_KDDockWidgets__Controllers__DockWidget__event_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::DockWidget_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->event_nocallback(event);
        } else {
            return targetPtr->event(event);
        }
    }();
}
// eventFilter(QObject * watched, QEvent * event)
bool c_KDDockWidgets__Controllers__DockWidget__eventFilter_QObject_QEvent(void *thisObj,
                                                                          void *watched_,
                                                                          void *event_)
{
    auto watched = reinterpret_cast<QObject *>(watched_);
    auto event = reinterpret_cast<QEvent *>(event_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::DockWidget_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->eventFilter_nocallback(watched, event);
        } else {
            return targetPtr->eventFilter(watched, event);
        }
    }();
}
// floatingWindow() const
void *c_KDDockWidgets__Controllers__DockWidget__floatingWindow(void *thisObj)
{
    return fromPtr(thisObj)->floatingWindow();
}
// forceClose()
void c_KDDockWidgets__Controllers__DockWidget__forceClose(void *thisObj)
{
    fromPtr(thisObj)->forceClose();
}
// groupGeometry() const
void *c_KDDockWidgets__Controllers__DockWidget__groupGeometry(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QRect> { fromPtr(thisObj)->groupGeometry() };
}
// guestViewChanged()
void c_KDDockWidgets__Controllers__DockWidget__guestViewChanged(void *thisObj)
{
    fromPtr(thisObj)->guestViewChanged();
}
// hasPreviousDockedLocation() const
bool c_KDDockWidgets__Controllers__DockWidget__hasPreviousDockedLocation(void *thisObj)
{
    return fromPtr(thisObj)->hasPreviousDockedLocation();
}
// hidden()
void c_KDDockWidgets__Controllers__DockWidget__hidden(void *thisObj)
{
    fromPtr(thisObj)->hidden();
}
// iconChanged()
void c_KDDockWidgets__Controllers__DockWidget__iconChanged(void *thisObj)
{
    fromPtr(thisObj)->iconChanged();
}
// init()
void c_KDDockWidgets__Controllers__DockWidget__init(void *thisObj)
{
    fromPtr(thisObj)->init();
}
// isCurrentTab() const
bool c_KDDockWidgets__Controllers__DockWidget__isCurrentTab(void *thisObj)
{
    return fromPtr(thisObj)->isCurrentTab();
}
// isFloating() const
bool c_KDDockWidgets__Controllers__DockWidget__isFloating(void *thisObj)
{
    return fromPtr(thisObj)->isFloating();
}
// isFloatingChanged(bool arg__1)
void c_KDDockWidgets__Controllers__DockWidget__isFloatingChanged_bool(void *thisObj, bool arg__1)
{
    fromPtr(thisObj)->isFloatingChanged(arg__1);
}
// isFocused() const
bool c_KDDockWidgets__Controllers__DockWidget__isFocused(void *thisObj)
{
    return fromPtr(thisObj)->isFocused();
}
// isFocusedChanged(bool arg__1)
void c_KDDockWidgets__Controllers__DockWidget__isFocusedChanged_bool(void *thisObj, bool arg__1)
{
    fromPtr(thisObj)->isFocusedChanged(arg__1);
}
// isInMainWindow() const
bool c_KDDockWidgets__Controllers__DockWidget__isInMainWindow(void *thisObj)
{
    return fromPtr(thisObj)->isInMainWindow();
}
// isInSideBar() const
bool c_KDDockWidgets__Controllers__DockWidget__isInSideBar(void *thisObj)
{
    return fromPtr(thisObj)->isInSideBar();
}
// isMainWindow() const
bool c_KDDockWidgets__Controllers__DockWidget__isMainWindow(void *thisObj)
{
    return fromPtr(thisObj)->isMainWindow();
}
// isOpen() const
bool c_KDDockWidgets__Controllers__DockWidget__isOpen(void *thisObj)
{
    return fromPtr(thisObj)->isOpen();
}
// isOverlayed() const
bool c_KDDockWidgets__Controllers__DockWidget__isOverlayed(void *thisObj)
{
    return fromPtr(thisObj)->isOverlayed();
}
// isOverlayedChanged(bool arg__1)
void c_KDDockWidgets__Controllers__DockWidget__isOverlayedChanged_bool(void *thisObj, bool arg__1)
{
    fromPtr(thisObj)->isOverlayedChanged(arg__1);
}
// isPersistentCentralDockWidget() const
bool c_KDDockWidgets__Controllers__DockWidget__isPersistentCentralDockWidget(void *thisObj)
{
    return fromPtr(thisObj)->isPersistentCentralDockWidget();
}
// isTabbed() const
bool c_KDDockWidgets__Controllers__DockWidget__isTabbed(void *thisObj)
{
    return fromPtr(thisObj)->isTabbed();
}
// lastOverlayedSize() const
void *c_KDDockWidgets__Controllers__DockWidget__lastOverlayedSize(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { fromPtr(thisObj)->lastOverlayedSize() };
}
// layoutSaverOptions() const
int c_KDDockWidgets__Controllers__DockWidget__layoutSaverOptions(void *thisObj)
{
    return fromPtr(thisObj)->layoutSaverOptions();
}
// mainWindow() const
void *c_KDDockWidgets__Controllers__DockWidget__mainWindow(void *thisObj)
{
    return fromPtr(thisObj)->mainWindow();
}
// moveToSideBar()
void c_KDDockWidgets__Controllers__DockWidget__moveToSideBar(void *thisObj)
{
    fromPtr(thisObj)->moveToSideBar();
}
// onHidden(bool spontaneous)
void c_KDDockWidgets__Controllers__DockWidget__onHidden_bool(void *thisObj, bool spontaneous)
{
    fromPtr(thisObj)->onHidden(spontaneous);
}
// onResize(QSize newSize)
void c_KDDockWidgets__Controllers__DockWidget__onResize_QSize(void *thisObj, void *newSize_)
{
    assert(newSize_);
    auto &newSize = *reinterpret_cast<QSize *>(newSize_);
    fromPtr(thisObj)->onResize(newSize);
}
// onShown(bool spontaneous)
void c_KDDockWidgets__Controllers__DockWidget__onShown_bool(void *thisObj, bool spontaneous)
{
    fromPtr(thisObj)->onShown(spontaneous);
}
// options() const
int c_KDDockWidgets__Controllers__DockWidget__options(void *thisObj)
{
    return fromPtr(thisObj)->options();
}
// optionsChanged(QFlags<KDDockWidgets::DockWidgetOption> arg__1)
void c_KDDockWidgets__Controllers__DockWidget__optionsChanged_DockWidgetOptions(void *thisObj,
                                                                                int arg__1_)
{
    auto arg__1 = static_cast<QFlags<KDDockWidgets::DockWidgetOption>>(arg__1_);
    fromPtr(thisObj)->optionsChanged(arg__1);
}
// raise()
void c_KDDockWidgets__Controllers__DockWidget__raise(void *thisObj)
{
    fromPtr(thisObj)->raise();
}
// removedFromSideBar()
void c_KDDockWidgets__Controllers__DockWidget__removedFromSideBar(void *thisObj)
{
    fromPtr(thisObj)->removedFromSideBar();
}
// setAffinityName(const QString & name)
void c_KDDockWidgets__Controllers__DockWidget__setAffinityName_QString(void *thisObj,
                                                                       const char *name_)
{
    const auto name = QString::fromUtf8(name_);
    fromPtr(thisObj)->setAffinityName(name);
}
// setAsCurrentTab()
void c_KDDockWidgets__Controllers__DockWidget__setAsCurrentTab(void *thisObj)
{
    fromPtr(thisObj)->setAsCurrentTab();
}
// setFloating(bool floats)
bool c_KDDockWidgets__Controllers__DockWidget__setFloating_bool(void *thisObj, bool floats)
{
    return fromPtr(thisObj)->setFloating(floats);
}
// setFloatingGeometry(QRect geo)
void c_KDDockWidgets__Controllers__DockWidget__setFloatingGeometry_QRect(void *thisObj, void *geo_)
{
    assert(geo_);
    auto &geo = *reinterpret_cast<QRect *>(geo_);
    fromPtr(thisObj)->setFloatingGeometry(geo);
}
// setMDIPosition(QPoint pos)
void c_KDDockWidgets__Controllers__DockWidget__setMDIPosition_QPoint(void *thisObj, void *pos_)
{
    assert(pos_);
    auto &pos = *reinterpret_cast<QPoint *>(pos_);
    fromPtr(thisObj)->setMDIPosition(pos);
}
// setMDISize(QSize size)
void c_KDDockWidgets__Controllers__DockWidget__setMDISize_QSize(void *thisObj, void *size_)
{
    assert(size_);
    auto &size = *reinterpret_cast<QSize *>(size_);
    fromPtr(thisObj)->setMDISize(size);
}
// setMDIZ(int z)
void c_KDDockWidgets__Controllers__DockWidget__setMDIZ_int(void *thisObj, int z)
{
    fromPtr(thisObj)->setMDIZ(z);
}
// setOptions(QFlags<KDDockWidgets::DockWidgetOption> arg__1)
void c_KDDockWidgets__Controllers__DockWidget__setOptions_DockWidgetOptions(void *thisObj,
                                                                            int arg__1_)
{
    auto arg__1 = static_cast<QFlags<KDDockWidgets::DockWidgetOption>>(arg__1_);
    fromPtr(thisObj)->setOptions(arg__1);
}
// setParentView_impl(KDDockWidgets::View * parent)
void c_KDDockWidgets__Controllers__DockWidget__setParentView_impl_View(void *thisObj, void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    fromWrapperPtr(thisObj)->setParentView_impl_nocallback(parent);
}
// setTitle(const QString & title)
void c_KDDockWidgets__Controllers__DockWidget__setTitle_QString(void *thisObj, const char *title_)
{
    const auto title = QString::fromUtf8(title_);
    fromPtr(thisObj)->setTitle(title);
}
// setUserType(int userType)
void c_KDDockWidgets__Controllers__DockWidget__setUserType_int(void *thisObj, int userType)
{
    fromPtr(thisObj)->setUserType(userType);
}
// show()
void c_KDDockWidgets__Controllers__DockWidget__show(void *thisObj)
{
    fromPtr(thisObj)->show();
}
// shown()
void c_KDDockWidgets__Controllers__DockWidget__shown(void *thisObj)
{
    fromPtr(thisObj)->shown();
}
// skipsRestore() const
bool c_KDDockWidgets__Controllers__DockWidget__skipsRestore(void *thisObj)
{
    return fromPtr(thisObj)->skipsRestore();
}
// tabIndex() const
int c_KDDockWidgets__Controllers__DockWidget__tabIndex(void *thisObj)
{
    return fromPtr(thisObj)->tabIndex();
}
// title() const
void *c_KDDockWidgets__Controllers__DockWidget__title(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QString> { fromPtr(thisObj)->title() };
}
// titleBar() const
void *c_KDDockWidgets__Controllers__DockWidget__titleBar(void *thisObj)
{
    return fromPtr(thisObj)->titleBar();
}
// titleChanged(const QString & title)
void c_KDDockWidgets__Controllers__DockWidget__titleChanged_QString(void *thisObj,
                                                                    const char *title_)
{
    const auto title = QString::fromUtf8(title_);
    fromPtr(thisObj)->titleChanged(title);
}
// tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__Controllers__DockWidget__tr_char_char_int(const char *s,
                                                                        const char *c, int n)
{
    return new Dartagnan::ValueWrapper<QString> {
        KDDockWidgetsBindings_wrappersNS::DockWidget_wrapper::tr(s, c, n)
    };
}
// uniqueName() const
void *c_KDDockWidgets__Controllers__DockWidget__uniqueName(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QString> { fromPtr(thisObj)->uniqueName() };
}
// userType() const
int c_KDDockWidgets__Controllers__DockWidget__userType(void *thisObj)
{
    return fromPtr(thisObj)->userType();
}
// windowActiveAboutToChange(bool activated)
void c_KDDockWidgets__Controllers__DockWidget__windowActiveAboutToChange_bool(void *thisObj,
                                                                              bool activated)
{
    fromPtr(thisObj)->windowActiveAboutToChange(activated);
}
void c_KDDockWidgets__Controllers__DockWidget__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__Controllers__DockWidget__registerVirtualMethodCallback(void *ptr,
                                                                             void *callback,
                                                                             int methodId)
{
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 295:
        wrapper->m_customEventCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::DockWidget_wrapper::Callback_customEvent>(callback);
        break;
    case 306:
        wrapper->m_eventCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::DockWidget_wrapper::Callback_event>(
                callback);
        break;
    case 307:
        wrapper->m_eventFilterCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::DockWidget_wrapper::Callback_eventFilter>(callback);
        break;
    case 828:
        wrapper->m_setParentView_implCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::DockWidget_wrapper::Callback_setParentView_impl>(
            callback);
        break;
    }
}
}

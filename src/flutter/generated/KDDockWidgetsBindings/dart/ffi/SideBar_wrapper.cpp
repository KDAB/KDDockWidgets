/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "SideBar_wrapper.h"


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
void SideBar_wrapper::addDockWidget(KDDockWidgets::Core::DockWidget *dw)
{
    ::KDDockWidgets::Core::SideBar::addDockWidget(dw);
}
void SideBar_wrapper::clear()
{
    ::KDDockWidgets::Core::SideBar::clear();
}
bool SideBar_wrapper::containsDockWidget(KDDockWidgets::Core::DockWidget *arg__1) const
{
    return ::KDDockWidgets::Core::SideBar::containsDockWidget(arg__1);
}
bool SideBar_wrapper::isEmpty() const
{
    return ::KDDockWidgets::Core::SideBar::isEmpty();
}
bool SideBar_wrapper::isVertical() const
{
    return ::KDDockWidgets::Core::SideBar::isVertical();
}
KDDockWidgets::Core::MainWindow *SideBar_wrapper::mainWindow() const
{
    return ::KDDockWidgets::Core::SideBar::mainWindow();
}
void SideBar_wrapper::onButtonClicked(KDDockWidgets::Core::DockWidget *dw)
{
    ::KDDockWidgets::Core::SideBar::onButtonClicked(dw);
}
void SideBar_wrapper::removeDockWidget(KDDockWidgets::Core::DockWidget *dw)
{
    ::KDDockWidgets::Core::SideBar::removeDockWidget(dw);
}
void SideBar_wrapper::setParentView_impl(KDDockWidgets::Core::View *parent)
{
    if (m_setParentView_implCallback) {
        const void *thisPtr = this;
        m_setParentView_implCallback(const_cast<void *>(thisPtr), parent);
    } else {
        ::KDDockWidgets::Core::SideBar::setParentView_impl(parent);
    }
}
void SideBar_wrapper::setParentView_impl_nocallback(KDDockWidgets::Core::View *parent)
{
    ::KDDockWidgets::Core::SideBar::setParentView_impl(parent);
}
void SideBar_wrapper::toggleOverlay(KDDockWidgets::Core::DockWidget *arg__1)
{
    ::KDDockWidgets::Core::SideBar::toggleOverlay(arg__1);
}
QString SideBar_wrapper::tr(const char *s, const char *c, int n)
{
    return ::KDDockWidgets::Core::SideBar::tr(s, c, n);
}
SideBar_wrapper::~SideBar_wrapper()
{
}

}
static KDDockWidgets::Core::SideBar *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::Core::SideBar *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::SideBar_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::SideBar_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__Controllers__SideBar_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::SideBar_wrapper *>(cppObj);
} // addDockWidget(KDDockWidgets::Core::DockWidget * dw)
void c_KDDockWidgets__Controllers__SideBar__addDockWidget_DockWidget(void *thisObj, void *dw_)
{
    auto dw = reinterpret_cast<KDDockWidgets::Core::DockWidget *>(dw_);
    fromPtr(thisObj)->addDockWidget(dw);
}
// clear()
void c_KDDockWidgets__Controllers__SideBar__clear(void *thisObj)
{
    fromPtr(thisObj)->clear();
}
// containsDockWidget(KDDockWidgets::Core::DockWidget * arg__1) const
bool c_KDDockWidgets__Controllers__SideBar__containsDockWidget_DockWidget(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Core::DockWidget *>(arg__1_);
    return fromPtr(thisObj)->containsDockWidget(arg__1);
}
// isEmpty() const
bool c_KDDockWidgets__Controllers__SideBar__isEmpty(void *thisObj)
{
    return fromPtr(thisObj)->isEmpty();
}
// isVertical() const
bool c_KDDockWidgets__Controllers__SideBar__isVertical(void *thisObj)
{
    return fromPtr(thisObj)->isVertical();
}
// mainWindow() const
void *c_KDDockWidgets__Controllers__SideBar__mainWindow(void *thisObj)
{
    return fromPtr(thisObj)->mainWindow();
}
// onButtonClicked(KDDockWidgets::Core::DockWidget * dw)
void c_KDDockWidgets__Controllers__SideBar__onButtonClicked_DockWidget(void *thisObj, void *dw_)
{
    auto dw = reinterpret_cast<KDDockWidgets::Core::DockWidget *>(dw_);
    fromPtr(thisObj)->onButtonClicked(dw);
}
// removeDockWidget(KDDockWidgets::Core::DockWidget * dw)
void c_KDDockWidgets__Controllers__SideBar__removeDockWidget_DockWidget(void *thisObj, void *dw_)
{
    auto dw = reinterpret_cast<KDDockWidgets::Core::DockWidget *>(dw_);
    fromPtr(thisObj)->removeDockWidget(dw);
}
// setParentView_impl(KDDockWidgets::Core::View * parent)
void c_KDDockWidgets__Controllers__SideBar__setParentView_impl_View(void *thisObj, void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::Core::View *>(parent_);
    fromWrapperPtr(thisObj)->setParentView_impl_nocallback(parent);
}
// toggleOverlay(KDDockWidgets::Core::DockWidget * arg__1)
void c_KDDockWidgets__Controllers__SideBar__toggleOverlay_DockWidget(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::Core::DockWidget *>(arg__1_);
    fromPtr(thisObj)->toggleOverlay(arg__1);
}
// tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__Controllers__SideBar__tr_char_char_int(const char *s, const char *c, int n)
{
    return new Dartagnan::ValueWrapper<QString> { KDDockWidgetsBindings_wrappersNS::SideBar_wrapper::tr(s, c, n) };
}
void c_KDDockWidgets__Controllers__SideBar__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__Controllers__SideBar__registerVirtualMethodCallback(void *ptr, void *callback, int methodId)
{
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 881:
        wrapper->m_setParentView_implCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::SideBar_wrapper::Callback_setParentView_impl>(callback);
        break;
    }
}
}

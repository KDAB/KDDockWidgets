/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <SideBar.h>
#include <qstring.h>
#include <DockWidget.h>
#include <MainWindow.h>
#include <View.h>
#include <qrect.h>
#include <qpoint.h>
#include <qsize.h>

namespace KDDockWidgetsBindings_wrappersNS {
class SideBar_wrapper : public ::KDDockWidgets::Core::SideBar
{
public:
    ~SideBar_wrapper();
    void addDockWidget(KDDockWidgets::Core::DockWidget *dw);
    void clear();
    bool containsDockWidget(KDDockWidgets::Core::DockWidget *arg__1) const;
    bool isEmpty() const;
    bool isVertical() const;
    KDDockWidgets::Core::MainWindow *mainWindow() const;
    void onButtonClicked(KDDockWidgets::Core::DockWidget *dw);
    void removeDockWidget(KDDockWidgets::Core::DockWidget *dw);
    virtual void setParentView_impl(KDDockWidgets::View *parent);
    virtual void setParentView_impl_nocallback(KDDockWidgets::View *parent);
    void toggleOverlay(KDDockWidgets::Core::DockWidget *arg__1);
    static QString tr(const char *s, const char *c, int n);
    typedef void (*Callback_setParentView_impl)(void *, KDDockWidgets::View *parent);
    Callback_setParentView_impl m_setParentView_implCallback = nullptr;
};
}
extern "C" {
// KDDockWidgets::Core::SideBar::addDockWidget(KDDockWidgets::Core::DockWidget * dw)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__SideBar__addDockWidget_DockWidget(void *thisObj, void *dw_);
// KDDockWidgets::Core::SideBar::clear()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__SideBar__clear(void *thisObj);
// KDDockWidgets::Core::SideBar::containsDockWidget(KDDockWidgets::Core::DockWidget * arg__1) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__SideBar__containsDockWidget_DockWidget(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::SideBar::isEmpty() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__SideBar__isEmpty(void *thisObj);
// KDDockWidgets::Core::SideBar::isVertical() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__SideBar__isVertical(void *thisObj);
// KDDockWidgets::Core::SideBar::mainWindow() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controllers__SideBar__mainWindow(void *thisObj);
// KDDockWidgets::Core::SideBar::onButtonClicked(KDDockWidgets::Core::DockWidget * dw)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__SideBar__onButtonClicked_DockWidget(void *thisObj, void *dw_);
// KDDockWidgets::Core::SideBar::removeDockWidget(KDDockWidgets::Core::DockWidget * dw)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__SideBar__removeDockWidget_DockWidget(void *thisObj, void *dw_);
// KDDockWidgets::Core::SideBar::setParentView_impl(KDDockWidgets::View * parent)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__SideBar__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Core::SideBar::toggleOverlay(KDDockWidgets::Core::DockWidget * arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__SideBar__toggleOverlay_DockWidget(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::SideBar::tr(const char * s, const char * c, int n)
KDDockWidgetsBindings_EXPORT void *c_static_KDDockWidgets__Controllers__SideBar__tr_char_char_int(const char *s, const char *c, int n);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__SideBar__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__SideBar__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__SideBar_Finalizer(void *, void *cppObj, void *);
}

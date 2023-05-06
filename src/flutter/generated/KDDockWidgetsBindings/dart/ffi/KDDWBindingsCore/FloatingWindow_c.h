/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <FloatingWindow.h>
#include <qstring.h>
#include <qrect.h>
#include <MainWindow.h>
#include <core/Group.h>
#include <core/DockWidget.h>
#include <DropArea.h>
#include "core/TitleBar.h"
#include <core/Layout.h>
#include <qpoint.h>
#include <KDDockWidgets.h>
#include <qsize.h>
#include <core/View.h>

namespace KDDockWidgetsBindings_wrappersNS {namespace KDDWBindingsCore {class FloatingWindow_wrapper : public ::KDDockWidgets::Core::FloatingWindow {public:
~FloatingWindow_wrapper(); FloatingWindow_wrapper(KDDockWidgets::Core::Group * group,QRect suggestedGeometry,KDDockWidgets::Core::MainWindow * parent = nullptr); FloatingWindow_wrapper(QRect suggestedGeometry,KDDockWidgets::Core::MainWindow * parent = nullptr);void activatedChanged();void addDockWidget(KDDockWidgets::Core::DockWidget * arg__1,KDDockWidgets::Location location,KDDockWidgets::Core::DockWidget * relativeTo,KDDockWidgets::InitialOption arg__4 = {});bool allDockWidgetsHave(KDDockWidgets::DockWidgetOption arg__1)const;bool allDockWidgetsHave(KDDockWidgets::LayoutSaverOption arg__1)const;bool anyDockWidgetsHas(KDDockWidgets::DockWidgetOption arg__1)const;bool anyDockWidgetsHas(KDDockWidgets::LayoutSaverOption arg__1)const;bool anyNonClosable()const;bool anyNonDockable()const;bool beingDeleted()const;QRect dragRect()const;KDDockWidgets::Core::DropArea * dropArea()const;static void ensureRectIsOnScreen(QRect & geometry);bool hasSingleDockWidget()const;bool hasSingleFrame()const;bool isInDragArea(QPoint globalPoint)const;virtual bool isMDI()const;virtual bool isMDI_nocallback()const;bool isUtilityWindow()const;virtual bool isWindow()const;virtual bool isWindow_nocallback()const;KDDockWidgets::Core::Layout * layout()const;KDDockWidgets::Core::MainWindow * mainWindow()const;void maybeCreateResizeHandler();KDDockWidgets::Core::DropArea * multiSplitter()const;void numDockWidgetsChanged();void numFramesChanged();void scheduleDeleteLater();virtual void setParentView_impl(KDDockWidgets::Core::View * parent);virtual void setParentView_impl_nocallback(KDDockWidgets::Core::View * parent);void setSuggestedGeometry(QRect suggestedRect);virtual KDDockWidgets::Core::DockWidget * singleDockWidget()const;virtual KDDockWidgets::Core::DockWidget * singleDockWidget_nocallback()const;KDDockWidgets::Core::Group * singleFrame()const;bool supportsMaximizeButton()const;bool supportsMinimizeButton()const;KDDockWidgets::Core::TitleBar * titleBar()const;static QString tr(const char * s,const char * c,int n);void updateTitleAndIcon();void updateTitleBarVisibility();int userType()const;void windowStateChanged();typedef bool (*Callback_isMDI)(void *);Callback_isMDI m_isMDICallback = nullptr;typedef bool (*Callback_isWindow)(void *);Callback_isWindow m_isWindowCallback = nullptr;typedef void (*Callback_setParentView_impl)(void *,KDDockWidgets::Core::View * parent);Callback_setParentView_impl m_setParentView_implCallback = nullptr;typedef KDDockWidgets::Core::DockWidget * (*Callback_singleDockWidget)(void *);Callback_singleDockWidget m_singleDockWidgetCallback = nullptr;

};
}}extern "C" {
// KDDockWidgets::Core::FloatingWindow::FloatingWindow(KDDockWidgets::Core::Group * group, QRect suggestedGeometry, KDDockWidgets::Core::MainWindow * parent)
KDDockWidgetsBindings_EXPORT void * c_KDDockWidgets__Core__FloatingWindow__constructor_Group_QRect_MainWindow(void* group_,void* suggestedGeometry_,void* parent_);
// KDDockWidgets::Core::FloatingWindow::FloatingWindow(QRect suggestedGeometry, KDDockWidgets::Core::MainWindow * parent)
KDDockWidgetsBindings_EXPORT void * c_KDDockWidgets__Core__FloatingWindow__constructor_QRect_MainWindow(void* suggestedGeometry_,void* parent_);
// KDDockWidgets::Core::FloatingWindow::activatedChanged()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__FloatingWindow__activatedChanged(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::addDockWidget(KDDockWidgets::Core::DockWidget * arg__1, KDDockWidgets::Location location, KDDockWidgets::Core::DockWidget * relativeTo, KDDockWidgets::InitialOption arg__4)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__FloatingWindow__addDockWidget_DockWidget_Location_DockWidget_InitialOption(void *thisObj,void* arg__1_,int location,void* relativeTo_,void* arg__4_);
// KDDockWidgets::Core::FloatingWindow::allDockWidgetsHave(KDDockWidgets::DockWidgetOption arg__1) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__FloatingWindow__allDockWidgetsHave_DockWidgetOption(void *thisObj,int arg__1);
// KDDockWidgets::Core::FloatingWindow::allDockWidgetsHave(KDDockWidgets::LayoutSaverOption arg__1) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__FloatingWindow__allDockWidgetsHave_LayoutSaverOption(void *thisObj,int arg__1);
// KDDockWidgets::Core::FloatingWindow::anyDockWidgetsHas(KDDockWidgets::DockWidgetOption arg__1) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__FloatingWindow__anyDockWidgetsHas_DockWidgetOption(void *thisObj,int arg__1);
// KDDockWidgets::Core::FloatingWindow::anyDockWidgetsHas(KDDockWidgets::LayoutSaverOption arg__1) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__FloatingWindow__anyDockWidgetsHas_LayoutSaverOption(void *thisObj,int arg__1);
// KDDockWidgets::Core::FloatingWindow::anyNonClosable() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__FloatingWindow__anyNonClosable(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::anyNonDockable() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__FloatingWindow__anyNonDockable(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::beingDeleted() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__FloatingWindow__beingDeleted(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::dragRect() const
KDDockWidgetsBindings_EXPORT void* c_KDDockWidgets__Core__FloatingWindow__dragRect(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::dropArea() const
KDDockWidgetsBindings_EXPORT void* c_KDDockWidgets__Core__FloatingWindow__dropArea(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::ensureRectIsOnScreen(QRect & geometry)
KDDockWidgetsBindings_EXPORT void c_static_KDDockWidgets__Core__FloatingWindow__ensureRectIsOnScreen_QRect(void* geometry_);
// KDDockWidgets::Core::FloatingWindow::hasSingleDockWidget() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__FloatingWindow__hasSingleDockWidget(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::hasSingleFrame() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__FloatingWindow__hasSingleFrame(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::isInDragArea(QPoint globalPoint) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__FloatingWindow__isInDragArea_QPoint(void *thisObj,void* globalPoint_);
// KDDockWidgets::Core::FloatingWindow::isMDI() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__FloatingWindow__isMDI(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::isUtilityWindow() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__FloatingWindow__isUtilityWindow(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::isWindow() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__FloatingWindow__isWindow(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::layout() const
KDDockWidgetsBindings_EXPORT void* c_KDDockWidgets__Core__FloatingWindow__layout(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::mainWindow() const
KDDockWidgetsBindings_EXPORT void* c_KDDockWidgets__Core__FloatingWindow__mainWindow(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::maybeCreateResizeHandler()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__FloatingWindow__maybeCreateResizeHandler(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::multiSplitter() const
KDDockWidgetsBindings_EXPORT void* c_KDDockWidgets__Core__FloatingWindow__multiSplitter(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::numDockWidgetsChanged()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__FloatingWindow__numDockWidgetsChanged(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::numFramesChanged()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__FloatingWindow__numFramesChanged(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::scheduleDeleteLater()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__FloatingWindow__scheduleDeleteLater(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::setParentView_impl(KDDockWidgets::Core::View * parent)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__FloatingWindow__setParentView_impl_View(void *thisObj,void* parent_);
// KDDockWidgets::Core::FloatingWindow::setSuggestedGeometry(QRect suggestedRect)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__FloatingWindow__setSuggestedGeometry_QRect(void *thisObj,void* suggestedRect_);
// KDDockWidgets::Core::FloatingWindow::singleDockWidget() const
KDDockWidgetsBindings_EXPORT void* c_KDDockWidgets__Core__FloatingWindow__singleDockWidget(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::singleFrame() const
KDDockWidgetsBindings_EXPORT void* c_KDDockWidgets__Core__FloatingWindow__singleFrame(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::supportsMaximizeButton() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__FloatingWindow__supportsMaximizeButton(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::supportsMinimizeButton() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__FloatingWindow__supportsMinimizeButton(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::titleBar() const
KDDockWidgetsBindings_EXPORT void* c_KDDockWidgets__Core__FloatingWindow__titleBar(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::tr(const char * s, const char * c, int n)
KDDockWidgetsBindings_EXPORT void* c_static_KDDockWidgets__Core__FloatingWindow__tr_char_char_int(const char * s,const char * c,int n);
// KDDockWidgets::Core::FloatingWindow::updateTitleAndIcon()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__FloatingWindow__updateTitleAndIcon(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::updateTitleBarVisibility()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__FloatingWindow__updateTitleBarVisibility(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::userType() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Core__FloatingWindow__userType(void *thisObj);
// KDDockWidgets::Core::FloatingWindow::windowStateChanged()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__FloatingWindow__windowStateChanged(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__FloatingWindow__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__FloatingWindow__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);KDDockWidgetsBindings_EXPORT  void c_KDDockWidgets__Core__FloatingWindow_Finalizer(void *, void *cppObj, void *);}

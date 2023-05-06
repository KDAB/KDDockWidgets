/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <core/Layout.h>
#include <core/View.h>
#include <MainWindow.h>
#include <FloatingWindow.h>
#include <qsize.h>
#include <core/DockWidget.h>
#include <Item_p.h>
#include <core/Group.h>
#include <qlist.h>
#include <DropArea.h>
#include <qstring.h>
#include <qrect.h>
#include <qpoint.h>

namespace KDDockWidgetsBindings_wrappersNS {namespace KDDWBindingsCore {class Layout_wrapper : public ::KDDockWidgets::Core::Layout {public:
~Layout_wrapper(); Layout_wrapper(KDDockWidgets::Core::ViewType arg__1,KDDockWidgets::Core::View * arg__2);KDDockWidgets::Core::DropArea * asDropArea()const;bool checkSanity()const;void clearLayout();bool containsFrame(const KDDockWidgets::Core::Group * arg__1)const;bool containsItem(const KDDockWidgets::Core::Item * arg__1)const;int count()const;void dumpLayout()const;KDDockWidgets::Core::FloatingWindow * floatingWindow()const;QList<KDDockWidgets::Core::Group* > groups()const;QList<KDDockWidgets::Core::Group* > groupsFrom(KDDockWidgets::Core::View * groupOrMultiSplitter)const;bool isInMainWindow(bool honourNesting = false)const;KDDockWidgets::Core::Item * itemForFrame(const KDDockWidgets::Core::Group * group)const;int layoutHeight()const;QSize layoutMaximumSizeHint()const;QSize layoutMinimumSize()const;QSize layoutSize()const;int layoutWidth()const;KDDockWidgets::Core::MainWindow * mainWindow(bool honourNesting = false)const;int placeholderCount()const;void removeItem(KDDockWidgets::Core::Item * item);void restorePlaceholder(KDDockWidgets::Core::DockWidget * dw,KDDockWidgets::Core::Item * arg__2,int tabIndex);void setLayoutMinimumSize(QSize arg__1);void setLayoutSize(QSize arg__1);virtual void setParentView_impl(KDDockWidgets::Core::View * parent);virtual void setParentView_impl_nocallback(KDDockWidgets::Core::View * parent);void unrefOldPlaceholders(const QList<KDDockWidgets::Core::Group* > & groupsBeingAdded)const;void updateSizeConstraints();void viewAboutToBeDeleted();int visibleCount()const;typedef void (*Callback_setParentView_impl)(void *,KDDockWidgets::Core::View * parent);Callback_setParentView_impl m_setParentView_implCallback = nullptr;

};
}}extern "C" {
// KDDockWidgets::Core::Layout::Layout(KDDockWidgets::Core::ViewType arg__1, KDDockWidgets::Core::View * arg__2)
KDDockWidgetsBindings_EXPORT void * c_KDDockWidgets__Core__Layout__constructor_ViewType_View(int arg__1,void* arg__2_);
// KDDockWidgets::Core::Layout::asDropArea() const
KDDockWidgetsBindings_EXPORT void* c_KDDockWidgets__Core__Layout__asDropArea(void *thisObj);
// KDDockWidgets::Core::Layout::checkSanity() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__Layout__checkSanity(void *thisObj);
// KDDockWidgets::Core::Layout::clearLayout()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__Layout__clearLayout(void *thisObj);
// KDDockWidgets::Core::Layout::containsFrame(const KDDockWidgets::Core::Group * arg__1) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__Layout__containsFrame_Group(void *thisObj,void* arg__1_);
// KDDockWidgets::Core::Layout::containsItem(const KDDockWidgets::Core::Item * arg__1) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__Layout__containsItem_Item(void *thisObj,void* arg__1_);
// KDDockWidgets::Core::Layout::count() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Core__Layout__count(void *thisObj);
// KDDockWidgets::Core::Layout::dumpLayout() const
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__Layout__dumpLayout(void *thisObj);
// KDDockWidgets::Core::Layout::floatingWindow() const
KDDockWidgetsBindings_EXPORT void* c_KDDockWidgets__Core__Layout__floatingWindow(void *thisObj);
// KDDockWidgets::Core::Layout::groups() const
KDDockWidgetsBindings_EXPORT void* c_KDDockWidgets__Core__Layout__groups(void *thisObj);
// KDDockWidgets::Core::Layout::groupsFrom(KDDockWidgets::Core::View * groupOrMultiSplitter) const
KDDockWidgetsBindings_EXPORT void* c_KDDockWidgets__Core__Layout__groupsFrom_View(void *thisObj,void* groupOrMultiSplitter_);
// KDDockWidgets::Core::Layout::isInMainWindow(bool honourNesting) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__Layout__isInMainWindow_bool(void *thisObj,bool honourNesting);
// KDDockWidgets::Core::Layout::itemForFrame(const KDDockWidgets::Core::Group * group) const
KDDockWidgetsBindings_EXPORT void* c_KDDockWidgets__Core__Layout__itemForFrame_Group(void *thisObj,void* group_);
// KDDockWidgets::Core::Layout::layoutHeight() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Core__Layout__layoutHeight(void *thisObj);
// KDDockWidgets::Core::Layout::layoutMaximumSizeHint() const
KDDockWidgetsBindings_EXPORT void* c_KDDockWidgets__Core__Layout__layoutMaximumSizeHint(void *thisObj);
// KDDockWidgets::Core::Layout::layoutMinimumSize() const
KDDockWidgetsBindings_EXPORT void* c_KDDockWidgets__Core__Layout__layoutMinimumSize(void *thisObj);
// KDDockWidgets::Core::Layout::layoutSize() const
KDDockWidgetsBindings_EXPORT void* c_KDDockWidgets__Core__Layout__layoutSize(void *thisObj);
// KDDockWidgets::Core::Layout::layoutWidth() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Core__Layout__layoutWidth(void *thisObj);
// KDDockWidgets::Core::Layout::mainWindow(bool honourNesting) const
KDDockWidgetsBindings_EXPORT void* c_KDDockWidgets__Core__Layout__mainWindow_bool(void *thisObj,bool honourNesting);
// KDDockWidgets::Core::Layout::placeholderCount() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Core__Layout__placeholderCount(void *thisObj);
// KDDockWidgets::Core::Layout::removeItem(KDDockWidgets::Core::Item * item)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__Layout__removeItem_Item(void *thisObj,void* item_);
// KDDockWidgets::Core::Layout::restorePlaceholder(KDDockWidgets::Core::DockWidget * dw, KDDockWidgets::Core::Item * arg__2, int tabIndex)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__Layout__restorePlaceholder_DockWidget_Item_int(void *thisObj,void* dw_,void* arg__2_,int tabIndex);
// KDDockWidgets::Core::Layout::setLayoutMinimumSize(QSize arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__Layout__setLayoutMinimumSize_QSize(void *thisObj,void* arg__1_);
// KDDockWidgets::Core::Layout::setLayoutSize(QSize arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__Layout__setLayoutSize_QSize(void *thisObj,void* arg__1_);
// KDDockWidgets::Core::Layout::setParentView_impl(KDDockWidgets::Core::View * parent)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__Layout__setParentView_impl_View(void *thisObj,void* parent_);
// KDDockWidgets::Core::Layout::unrefOldPlaceholders(const QList<KDDockWidgets::Core::Group* > & groupsBeingAdded) const
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__Layout__unrefOldPlaceholders_QList_Group(void *thisObj,void* groupsBeingAdded_);
// KDDockWidgets::Core::Layout::updateSizeConstraints()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__Layout__updateSizeConstraints(void *thisObj);
// KDDockWidgets::Core::Layout::viewAboutToBeDeleted()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__Layout__viewAboutToBeDeleted(void *thisObj);
// KDDockWidgets::Core::Layout::visibleCount() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Core__Layout__visibleCount(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__Layout__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__Layout__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);KDDockWidgetsBindings_EXPORT  void c_KDDockWidgets__Core__Layout_Finalizer(void *, void *cppObj, void *);}

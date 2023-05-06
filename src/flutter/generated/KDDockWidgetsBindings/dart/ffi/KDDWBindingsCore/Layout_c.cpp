/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "Layout_c.h"


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
namespace KDDockWidgetsBindings_wrappersNS {namespace KDDWBindingsCore {Layout_wrapper::Layout_wrapper(KDDockWidgets::Core::ViewType arg__1,KDDockWidgets::Core::View * arg__2) : ::KDDockWidgets::Core::Layout(arg__1,arg__2) {}
KDDockWidgets::Core::DropArea * Layout_wrapper::asDropArea()const{return ::KDDockWidgets::Core::Layout::asDropArea();}
bool Layout_wrapper::checkSanity()const{return ::KDDockWidgets::Core::Layout::checkSanity();}
void Layout_wrapper::clearLayout(){::KDDockWidgets::Core::Layout::clearLayout();}
bool Layout_wrapper::containsFrame(const KDDockWidgets::Core::Group * arg__1)const{return ::KDDockWidgets::Core::Layout::containsFrame(arg__1);}
bool Layout_wrapper::containsItem(const KDDockWidgets::Core::Item * arg__1)const{return ::KDDockWidgets::Core::Layout::containsItem(arg__1);}
int Layout_wrapper::count()const{return ::KDDockWidgets::Core::Layout::count();}
void Layout_wrapper::dumpLayout()const{::KDDockWidgets::Core::Layout::dumpLayout();}
KDDockWidgets::Core::FloatingWindow * Layout_wrapper::floatingWindow()const{return ::KDDockWidgets::Core::Layout::floatingWindow();}
QList<KDDockWidgets::Core::Group* > Layout_wrapper::groups()const{return ::KDDockWidgets::Core::Layout::groups();}
QList<KDDockWidgets::Core::Group* > Layout_wrapper::groupsFrom(KDDockWidgets::Core::View * groupOrMultiSplitter)const{return ::KDDockWidgets::Core::Layout::groupsFrom(groupOrMultiSplitter);}
bool Layout_wrapper::isInMainWindow(bool honourNesting)const{return ::KDDockWidgets::Core::Layout::isInMainWindow(honourNesting);}
KDDockWidgets::Core::Item * Layout_wrapper::itemForFrame(const KDDockWidgets::Core::Group * group)const{return ::KDDockWidgets::Core::Layout::itemForFrame(group);}
int Layout_wrapper::layoutHeight()const{return ::KDDockWidgets::Core::Layout::layoutHeight();}
QSize Layout_wrapper::layoutMaximumSizeHint()const{return ::KDDockWidgets::Core::Layout::layoutMaximumSizeHint();}
QSize Layout_wrapper::layoutMinimumSize()const{return ::KDDockWidgets::Core::Layout::layoutMinimumSize();}
QSize Layout_wrapper::layoutSize()const{return ::KDDockWidgets::Core::Layout::layoutSize();}
int Layout_wrapper::layoutWidth()const{return ::KDDockWidgets::Core::Layout::layoutWidth();}
KDDockWidgets::Core::MainWindow * Layout_wrapper::mainWindow(bool honourNesting)const{return ::KDDockWidgets::Core::Layout::mainWindow(honourNesting);}
int Layout_wrapper::placeholderCount()const{return ::KDDockWidgets::Core::Layout::placeholderCount();}
void Layout_wrapper::removeItem(KDDockWidgets::Core::Item * item){::KDDockWidgets::Core::Layout::removeItem(item);}
void Layout_wrapper::restorePlaceholder(KDDockWidgets::Core::DockWidget * dw,KDDockWidgets::Core::Item * arg__2,int tabIndex){::KDDockWidgets::Core::Layout::restorePlaceholder(dw,arg__2,tabIndex);}
void Layout_wrapper::setLayoutMinimumSize(QSize arg__1){::KDDockWidgets::Core::Layout::setLayoutMinimumSize(arg__1);}
void Layout_wrapper::setLayoutSize(QSize arg__1){::KDDockWidgets::Core::Layout::setLayoutSize(arg__1);}
void Layout_wrapper::setParentView_impl(KDDockWidgets::Core::View * parent){if (m_setParentView_implCallback) {const void* thisPtr = this;
m_setParentView_implCallback(const_cast<void *>(thisPtr),parent);} else {::KDDockWidgets::Core::Layout::setParentView_impl(parent);}}void Layout_wrapper::setParentView_impl_nocallback(KDDockWidgets::Core::View * parent){::KDDockWidgets::Core::Layout::setParentView_impl(parent);}
void Layout_wrapper::unrefOldPlaceholders(const QList<KDDockWidgets::Core::Group* > & groupsBeingAdded)const{::KDDockWidgets::Core::Layout::unrefOldPlaceholders(groupsBeingAdded);}
void Layout_wrapper::updateSizeConstraints(){::KDDockWidgets::Core::Layout::updateSizeConstraints();}
void Layout_wrapper::viewAboutToBeDeleted(){::KDDockWidgets::Core::Layout::viewAboutToBeDeleted();}
int Layout_wrapper::visibleCount()const{return ::KDDockWidgets::Core::Layout::visibleCount();}
Layout_wrapper::~Layout_wrapper() {}

}}static KDDockWidgets::Core::Layout* fromPtr(void *ptr)
{return reinterpret_cast<KDDockWidgets::Core::Layout*>(ptr);}static KDDockWidgetsBindings_wrappersNS::KDDWBindingsCore::Layout_wrapper* fromWrapperPtr(void *ptr)
{return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsCore::Layout_wrapper*>(ptr);}extern "C" {
 void c_KDDockWidgets__Core__Layout_Finalizer(void *, void *cppObj, void *){delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsCore::Layout_wrapper *>(cppObj);}void * c_KDDockWidgets__Core__Layout__constructor_ViewType_View(int arg__1,void* arg__2_)
{
auto arg__2 = reinterpret_cast<KDDockWidgets::Core::View *>(arg__2_);auto ptr = new KDDockWidgetsBindings_wrappersNS::KDDWBindingsCore::Layout_wrapper(static_cast<KDDockWidgets::Core::ViewType>(arg__1),arg__2);return reinterpret_cast<void*>(ptr);}
//asDropArea() const
void* c_KDDockWidgets__Core__Layout__asDropArea(void *thisObj){return fromPtr(thisObj)->asDropArea();}
//checkSanity() const
bool c_KDDockWidgets__Core__Layout__checkSanity(void *thisObj){return fromPtr(thisObj)->checkSanity();}
//clearLayout()
void c_KDDockWidgets__Core__Layout__clearLayout(void *thisObj){fromPtr(thisObj)->clearLayout();}
//containsFrame(const KDDockWidgets::Core::Group * arg__1) const
bool c_KDDockWidgets__Core__Layout__containsFrame_Group(void *thisObj,void* arg__1_){auto arg__1 = reinterpret_cast<KDDockWidgets::Core::Group *>(arg__1_);return fromPtr(thisObj)->containsFrame(arg__1);}
//containsItem(const KDDockWidgets::Core::Item * arg__1) const
bool c_KDDockWidgets__Core__Layout__containsItem_Item(void *thisObj,void* arg__1_){auto arg__1 = reinterpret_cast<KDDockWidgets::Core::Item *>(arg__1_);return fromPtr(thisObj)->containsItem(arg__1);}
//count() const
int c_KDDockWidgets__Core__Layout__count(void *thisObj){return fromPtr(thisObj)->count();}
//dumpLayout() const
void c_KDDockWidgets__Core__Layout__dumpLayout(void *thisObj){fromPtr(thisObj)->dumpLayout();}
//floatingWindow() const
void* c_KDDockWidgets__Core__Layout__floatingWindow(void *thisObj){return fromPtr(thisObj)->floatingWindow();}
//groups() const
void* c_KDDockWidgets__Core__Layout__groups(void *thisObj){return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::Group* >>{fromPtr(thisObj)->groups()};}
//groupsFrom(KDDockWidgets::Core::View * groupOrMultiSplitter) const
void* c_KDDockWidgets__Core__Layout__groupsFrom_View(void *thisObj,void* groupOrMultiSplitter_){auto groupOrMultiSplitter = reinterpret_cast<KDDockWidgets::Core::View *>(groupOrMultiSplitter_);return new Dartagnan::ValueWrapper<QList<KDDockWidgets::Core::Group* >>{fromWrapperPtr(thisObj)->groupsFrom(groupOrMultiSplitter)};}
//isInMainWindow(bool honourNesting) const
bool c_KDDockWidgets__Core__Layout__isInMainWindow_bool(void *thisObj,bool honourNesting){return fromPtr(thisObj)->isInMainWindow(honourNesting);}
//itemForFrame(const KDDockWidgets::Core::Group * group) const
void* c_KDDockWidgets__Core__Layout__itemForFrame_Group(void *thisObj,void* group_){auto group = reinterpret_cast<KDDockWidgets::Core::Group *>(group_);return fromPtr(thisObj)->itemForFrame(group);}
//layoutHeight() const
int c_KDDockWidgets__Core__Layout__layoutHeight(void *thisObj){return fromPtr(thisObj)->layoutHeight();}
//layoutMaximumSizeHint() const
void* c_KDDockWidgets__Core__Layout__layoutMaximumSizeHint(void *thisObj){return new Dartagnan::ValueWrapper<QSize>{fromPtr(thisObj)->layoutMaximumSizeHint()};}
//layoutMinimumSize() const
void* c_KDDockWidgets__Core__Layout__layoutMinimumSize(void *thisObj){return new Dartagnan::ValueWrapper<QSize>{fromPtr(thisObj)->layoutMinimumSize()};}
//layoutSize() const
void* c_KDDockWidgets__Core__Layout__layoutSize(void *thisObj){return new Dartagnan::ValueWrapper<QSize>{fromPtr(thisObj)->layoutSize()};}
//layoutWidth() const
int c_KDDockWidgets__Core__Layout__layoutWidth(void *thisObj){return fromPtr(thisObj)->layoutWidth();}
//mainWindow(bool honourNesting) const
void* c_KDDockWidgets__Core__Layout__mainWindow_bool(void *thisObj,bool honourNesting){return fromPtr(thisObj)->mainWindow(honourNesting);}
//placeholderCount() const
int c_KDDockWidgets__Core__Layout__placeholderCount(void *thisObj){return fromPtr(thisObj)->placeholderCount();}
//removeItem(KDDockWidgets::Core::Item * item)
void c_KDDockWidgets__Core__Layout__removeItem_Item(void *thisObj,void* item_){auto item = reinterpret_cast<KDDockWidgets::Core::Item *>(item_);fromPtr(thisObj)->removeItem(item);}
//restorePlaceholder(KDDockWidgets::Core::DockWidget * dw, KDDockWidgets::Core::Item * arg__2, int tabIndex)
void c_KDDockWidgets__Core__Layout__restorePlaceholder_DockWidget_Item_int(void *thisObj,void* dw_,void* arg__2_,int tabIndex){auto dw = reinterpret_cast<KDDockWidgets::Core::DockWidget *>(dw_);auto arg__2 = reinterpret_cast<KDDockWidgets::Core::Item *>(arg__2_);fromPtr(thisObj)->restorePlaceholder(dw,arg__2,tabIndex);}
//setLayoutMinimumSize(QSize arg__1)
void c_KDDockWidgets__Core__Layout__setLayoutMinimumSize_QSize(void *thisObj,void* arg__1_){assert(arg__1_);
auto &arg__1 = *reinterpret_cast<QSize *>(arg__1_);fromWrapperPtr(thisObj)->setLayoutMinimumSize(arg__1);}
//setLayoutSize(QSize arg__1)
void c_KDDockWidgets__Core__Layout__setLayoutSize_QSize(void *thisObj,void* arg__1_){assert(arg__1_);
auto &arg__1 = *reinterpret_cast<QSize *>(arg__1_);fromPtr(thisObj)->setLayoutSize(arg__1);}
//setParentView_impl(KDDockWidgets::Core::View * parent)
void c_KDDockWidgets__Core__Layout__setParentView_impl_View(void *thisObj,void* parent_){auto parent = reinterpret_cast<KDDockWidgets::Core::View *>(parent_);fromWrapperPtr(thisObj)->setParentView_impl_nocallback(parent);}
//unrefOldPlaceholders(const QList<KDDockWidgets::Core::Group* > & groupsBeingAdded) const
void c_KDDockWidgets__Core__Layout__unrefOldPlaceholders_QList_Group(void *thisObj,void* groupsBeingAdded_){assert(groupsBeingAdded_);
auto &groupsBeingAdded = *reinterpret_cast<QList<KDDockWidgets::Core::Group *> *>(groupsBeingAdded_);fromWrapperPtr(thisObj)->unrefOldPlaceholders(groupsBeingAdded);}
//updateSizeConstraints()
void c_KDDockWidgets__Core__Layout__updateSizeConstraints(void *thisObj){fromPtr(thisObj)->updateSizeConstraints();}
//viewAboutToBeDeleted()
void c_KDDockWidgets__Core__Layout__viewAboutToBeDeleted(void *thisObj){fromPtr(thisObj)->viewAboutToBeDeleted();}
//visibleCount() const
int c_KDDockWidgets__Core__Layout__visibleCount(void *thisObj){return fromPtr(thisObj)->visibleCount();}
void c_KDDockWidgets__Core__Layout__destructor(void *thisObj)
{
delete fromPtr(thisObj);}
void c_KDDockWidgets__Core__Layout__registerVirtualMethodCallback(void *ptr, void *callback, int methodId){auto wrapper = fromWrapperPtr(ptr);
switch (methodId) {
case 893:
wrapper->m_setParentView_implCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsCore::Layout_wrapper::Callback_setParentView_impl>(callback);break;}
}}

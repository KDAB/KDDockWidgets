/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <controllers/Layout.h>
#include <View.h>
#include <qsize.h>
#include <Item_p.h>
#include <Group.h>
#include <qlist.h>
#include <DropArea.h>
#include <qpoint.h>
#include <qobject.h>
#include <qcoreevent.h>
#include <qstring.h>
#include <qrect.h>

namespace KDDockWidgetsBindings_wrappersNS {
class Layout_wrapper : public ::KDDockWidgets::Controllers::Layout
{
public:
    ~Layout_wrapper();
    Layout_wrapper(KDDockWidgets::Type arg__1, KDDockWidgets::View *arg__2);
    KDDockWidgets::Controllers::DropArea *asDropArea() const;
    bool checkSanity() const;
    void clearLayout();
    bool containsFrame(const KDDockWidgets::Controllers::Group *arg__1) const;
    bool containsItem(const Layouting::Item *arg__1) const;
    int count() const;
    virtual void customEvent(QEvent *event);
    virtual void customEvent_nocallback(QEvent *event);
    void dumpLayout() const;
    virtual bool event(QEvent *event);
    virtual bool event_nocallback(QEvent *event);
    virtual bool eventFilter(QObject *watched, QEvent *event);
    virtual bool eventFilter_nocallback(QObject *watched, QEvent *event);
    QList<KDDockWidgets::Controllers::Group *> groups() const;
    QList<KDDockWidgets::Controllers::Group *> groupsFrom(KDDockWidgets::View *groupOrMultiSplitter) const;
    bool isInMainWindow(bool honourNesting = false) const;
    Layouting::Item *itemForFrame(const KDDockWidgets::Controllers::Group *group) const;
    int layoutHeight() const;
    QSize layoutMaximumSizeHint() const;
    QSize layoutMinimumSize() const;
    QSize layoutSize() const;
    int layoutWidth() const;
    int placeholderCount() const;
    void removeItem(Layouting::Item *item);
    void setLayoutMinimumSize(QSize arg__1);
    void setLayoutSize(QSize arg__1);
    virtual void setParentView_impl(KDDockWidgets::View *parent);
    virtual void setParentView_impl_nocallback(KDDockWidgets::View *parent);
    void unrefOldPlaceholders(const QList<KDDockWidgets::Controllers::Group *> &groupsBeingAdded) const;
    void updateSizeConstraints();
    void viewAboutToBeDeleted();
    int visibleCount() const;
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
// KDDockWidgets::Controllers::Layout::Layout(KDDockWidgets::Type arg__1, KDDockWidgets::View * arg__2)
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controllers__Layout__constructor_Type_View(int arg__1, void *arg__2_);
// KDDockWidgets::Controllers::Layout::asDropArea() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controllers__Layout__asDropArea(void *thisObj);
// KDDockWidgets::Controllers::Layout::checkSanity() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__Layout__checkSanity(void *thisObj);
// KDDockWidgets::Controllers::Layout::clearLayout()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__Layout__clearLayout(void *thisObj);
// KDDockWidgets::Controllers::Layout::containsFrame(const KDDockWidgets::Controllers::Group * arg__1) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__Layout__containsFrame_Group(void *thisObj, void *arg__1_);
// KDDockWidgets::Controllers::Layout::containsItem(const Layouting::Item * arg__1) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__Layout__containsItem_Item(void *thisObj, void *arg__1_);
// KDDockWidgets::Controllers::Layout::count() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Controllers__Layout__count(void *thisObj);
// KDDockWidgets::Controllers::Layout::customEvent(QEvent * event)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__Layout__customEvent_QEvent(void *thisObj, void *event_);
// KDDockWidgets::Controllers::Layout::dumpLayout() const
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__Layout__dumpLayout(void *thisObj);
// KDDockWidgets::Controllers::Layout::event(QEvent * event)
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__Layout__event_QEvent(void *thisObj, void *event_);
// KDDockWidgets::Controllers::Layout::eventFilter(QObject * watched, QEvent * event)
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__Layout__eventFilter_QObject_QEvent(void *thisObj, void *watched_, void *event_);
// KDDockWidgets::Controllers::Layout::groups() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controllers__Layout__groups(void *thisObj);
// KDDockWidgets::Controllers::Layout::groupsFrom(KDDockWidgets::View * groupOrMultiSplitter) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controllers__Layout__groupsFrom_View(void *thisObj, void *groupOrMultiSplitter_);
// KDDockWidgets::Controllers::Layout::isInMainWindow(bool honourNesting) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__Layout__isInMainWindow_bool(void *thisObj, bool honourNesting);
// KDDockWidgets::Controllers::Layout::itemForFrame(const KDDockWidgets::Controllers::Group * group) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controllers__Layout__itemForFrame_Group(void *thisObj, void *group_);
// KDDockWidgets::Controllers::Layout::layoutHeight() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Controllers__Layout__layoutHeight(void *thisObj);
// KDDockWidgets::Controllers::Layout::layoutMaximumSizeHint() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controllers__Layout__layoutMaximumSizeHint(void *thisObj);
// KDDockWidgets::Controllers::Layout::layoutMinimumSize() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controllers__Layout__layoutMinimumSize(void *thisObj);
// KDDockWidgets::Controllers::Layout::layoutSize() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controllers__Layout__layoutSize(void *thisObj);
// KDDockWidgets::Controllers::Layout::layoutWidth() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Controllers__Layout__layoutWidth(void *thisObj);
// KDDockWidgets::Controllers::Layout::placeholderCount() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Controllers__Layout__placeholderCount(void *thisObj);
// KDDockWidgets::Controllers::Layout::removeItem(Layouting::Item * item)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__Layout__removeItem_Item(void *thisObj, void *item_);
// KDDockWidgets::Controllers::Layout::setLayoutMinimumSize(QSize arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__Layout__setLayoutMinimumSize_QSize(void *thisObj, void *arg__1_);
// KDDockWidgets::Controllers::Layout::setLayoutSize(QSize arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__Layout__setLayoutSize_QSize(void *thisObj, void *arg__1_);
// KDDockWidgets::Controllers::Layout::setParentView_impl(KDDockWidgets::View * parent)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__Layout__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Controllers::Layout::unrefOldPlaceholders(const QList<KDDockWidgets::Controllers::Group* > & groupsBeingAdded) const
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__Layout__unrefOldPlaceholders_QList_Group(void *thisObj, void *groupsBeingAdded_);
// KDDockWidgets::Controllers::Layout::updateSizeConstraints()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__Layout__updateSizeConstraints(void *thisObj);
// KDDockWidgets::Controllers::Layout::viewAboutToBeDeleted()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__Layout__viewAboutToBeDeleted(void *thisObj);
// KDDockWidgets::Controllers::Layout::visibleCount() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Controllers__Layout__visibleCount(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__Layout__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__Layout__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__Layout_Finalizer(void *, void *cppObj, void *);
}

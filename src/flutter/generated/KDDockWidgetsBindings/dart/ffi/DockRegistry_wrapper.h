/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <DockRegistry.h>
#include <qstring.h>
#include <DockWidget.h>
#include <MainWindow.h>
#include <FloatingWindow.h>
#include <controllers/Layout.h>
#include <Group.h>
#include <qlist.h>
#include <Item_p.h>
#include <SideBar.h>
#include <qobject.h>
#include <qcoreevent.h>
#include <qbytearray.h>

namespace KDDockWidgetsBindings_wrappersNS {
class DockRegistry_wrapper : public ::KDDockWidgets::DockRegistry
{
public:
    ~DockRegistry_wrapper();
    void checkSanityAll(bool dumpDebug = false);
    void clear();
    bool containsDockWidget(const QString &uniqueName) const;
    bool containsMainWindow(const QString &uniqueName) const;
    virtual void customEvent(QEvent *event);
    virtual void customEvent_nocallback(QEvent *event);
    KDDockWidgets::Controllers::DockWidget *dockByName(const QString &arg__1) const;
    void dropIndicatorsInhibitedChanged(bool inhibited);
    void ensureAllFloatingWidgetsAreMorphed();
    virtual bool event(QEvent *event);
    virtual bool event_nocallback(QEvent *event);
    virtual bool eventFilter(QObject *watched, QEvent *event);
    virtual bool eventFilter_nocallback(QObject *watched, QEvent *event);
    KDDockWidgets::Controllers::DockWidget *focusedDockWidget() const;
    KDDockWidgets::Controllers::Group *groupInMDIResize() const;
    void groupInMDIResizeChanged();
    const QList<KDDockWidgets::Controllers::Group *> groups() const;
    bool hasFloatingWindows() const;
    bool isEmpty(bool excludeBeingDeleted = false) const;
    bool isSane() const;
    bool itemIsInMainWindow(const Layouting::Item *arg__1) const;
    KDDockWidgets::Controllers::Layout *layoutForItem(const Layouting::Item *arg__1) const;
    KDDockWidgets::Controllers::MainWindow *mainWindowByName(const QString &arg__1) const;
    void registerDockWidget(KDDockWidgets::Controllers::DockWidget *arg__1);
    void registerFloatingWindow(KDDockWidgets::Controllers::FloatingWindow *arg__1);
    void registerGroup(KDDockWidgets::Controllers::Group *arg__1);
    void registerLayout(KDDockWidgets::Controllers::Layout *arg__1);
    void registerMainWindow(KDDockWidgets::Controllers::MainWindow *arg__1);
    static KDDockWidgets::DockRegistry *self();
    KDDockWidgets::Controllers::SideBar *
    sideBarForDockWidget(const KDDockWidgets::Controllers::DockWidget *arg__1) const;
    static QString tr(const char *s, const char *c, int n);
    void unregisterDockWidget(KDDockWidgets::Controllers::DockWidget *arg__1);
    void unregisterFloatingWindow(KDDockWidgets::Controllers::FloatingWindow *arg__1);
    void unregisterGroup(KDDockWidgets::Controllers::Group *arg__1);
    void unregisterLayout(KDDockWidgets::Controllers::Layout *arg__1);
    void unregisterMainWindow(KDDockWidgets::Controllers::MainWindow *arg__1);
    typedef void (*Callback_customEvent)(void *, QEvent *event);
    Callback_customEvent m_customEventCallback = nullptr;
    typedef bool (*Callback_event)(void *, QEvent *event);
    Callback_event m_eventCallback = nullptr;
    typedef bool (*Callback_eventFilter)(void *, QObject *watched, QEvent *event);
    Callback_eventFilter m_eventFilterCallback = nullptr;
};
}
extern "C" {
// KDDockWidgets::DockRegistry::checkSanityAll(bool dumpDebug)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__DockRegistry__checkSanityAll_bool(void *thisObj, bool dumpDebug);
// KDDockWidgets::DockRegistry::clear()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__DockRegistry__clear(void *thisObj);
// KDDockWidgets::DockRegistry::containsDockWidget(const QString & uniqueName) const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__DockRegistry__containsDockWidget_QString(void *thisObj, const char *uniqueName_);
// KDDockWidgets::DockRegistry::containsMainWindow(const QString & uniqueName) const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__DockRegistry__containsMainWindow_QString(void *thisObj, const char *uniqueName_);
// KDDockWidgets::DockRegistry::customEvent(QEvent * event)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__DockRegistry__customEvent_QEvent(void *thisObj,
                                                                                    void *event_);
// KDDockWidgets::DockRegistry::dockByName(const QString & arg__1) const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__DockRegistry__dockByName_QString(void *thisObj, const char *arg__1_);
// KDDockWidgets::DockRegistry::dropIndicatorsInhibitedChanged(bool inhibited)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__DockRegistry__dropIndicatorsInhibitedChanged_bool(void *thisObj, bool inhibited);
// KDDockWidgets::DockRegistry::ensureAllFloatingWidgetsAreMorphed()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__DockRegistry__ensureAllFloatingWidgetsAreMorphed(void *thisObj);
// KDDockWidgets::DockRegistry::event(QEvent * event)
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__DockRegistry__event_QEvent(void *thisObj,
                                                                              void *event_);
// KDDockWidgets::DockRegistry::eventFilter(QObject * watched, QEvent * event)
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__DockRegistry__eventFilter_QObject_QEvent(void *thisObj, void *watched_,
                                                          void *event_);
// KDDockWidgets::DockRegistry::focusedDockWidget() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__DockRegistry__focusedDockWidget(void *thisObj);
// KDDockWidgets::DockRegistry::groupInMDIResize() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__DockRegistry__groupInMDIResize(void *thisObj);
// KDDockWidgets::DockRegistry::groupInMDIResizeChanged()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__DockRegistry__groupInMDIResizeChanged(void *thisObj);
// KDDockWidgets::DockRegistry::groups() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__DockRegistry__groups(void *thisObj);
// KDDockWidgets::DockRegistry::hasFloatingWindows() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__DockRegistry__hasFloatingWindows(void *thisObj);
// KDDockWidgets::DockRegistry::isEmpty(bool excludeBeingDeleted) const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__DockRegistry__isEmpty_bool(void *thisObj, bool excludeBeingDeleted);
// KDDockWidgets::DockRegistry::isSane() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__DockRegistry__isSane(void *thisObj);
// KDDockWidgets::DockRegistry::itemIsInMainWindow(const Layouting::Item * arg__1) const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__DockRegistry__itemIsInMainWindow_Item(void *thisObj, void *arg__1_);
// KDDockWidgets::DockRegistry::layoutForItem(const Layouting::Item * arg__1) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__DockRegistry__layoutForItem_Item(void *thisObj,
                                                                                     void *arg__1_);
// KDDockWidgets::DockRegistry::mainWindowByName(const QString & arg__1) const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__DockRegistry__mainWindowByName_QString(void *thisObj, const char *arg__1_);
// KDDockWidgets::DockRegistry::registerDockWidget(KDDockWidgets::Controllers::DockWidget * arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__DockRegistry__registerDockWidget_DockWidget(void *thisObj, void *arg__1_);
// KDDockWidgets::DockRegistry::registerFloatingWindow(KDDockWidgets::Controllers::FloatingWindow *
// arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__DockRegistry__registerFloatingWindow_FloatingWindow(void *thisObj, void *arg__1_);
// KDDockWidgets::DockRegistry::registerGroup(KDDockWidgets::Controllers::Group * arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__DockRegistry__registerGroup_Group(void *thisObj,
                                                                                     void *arg__1_);
// KDDockWidgets::DockRegistry::registerLayout(KDDockWidgets::Controllers::Layout * arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__DockRegistry__registerLayout_Layout(void *thisObj, void *arg__1_);
// KDDockWidgets::DockRegistry::registerMainWindow(KDDockWidgets::Controllers::MainWindow * arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__DockRegistry__registerMainWindow_MainWindow(void *thisObj, void *arg__1_);
// KDDockWidgets::DockRegistry::self()
KDDockWidgetsBindings_EXPORT void *c_static_KDDockWidgets__DockRegistry__self();
// KDDockWidgets::DockRegistry::sideBarForDockWidget(const KDDockWidgets::Controllers::DockWidget *
// arg__1) const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__DockRegistry__sideBarForDockWidget_DockWidget(void *thisObj, void *arg__1_);
// KDDockWidgets::DockRegistry::tr(const char * s, const char * c, int n)
KDDockWidgetsBindings_EXPORT void *
c_static_KDDockWidgets__DockRegistry__tr_char_char_int(const char *s, const char *c, int n);
// KDDockWidgets::DockRegistry::unregisterDockWidget(KDDockWidgets::Controllers::DockWidget *
// arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__DockRegistry__unregisterDockWidget_DockWidget(void *thisObj, void *arg__1_);
// KDDockWidgets::DockRegistry::unregisterFloatingWindow(KDDockWidgets::Controllers::FloatingWindow
// * arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__DockRegistry__unregisterFloatingWindow_FloatingWindow(void *thisObj,
                                                                       void *arg__1_);
// KDDockWidgets::DockRegistry::unregisterGroup(KDDockWidgets::Controllers::Group * arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__DockRegistry__unregisterGroup_Group(void *thisObj, void *arg__1_);
// KDDockWidgets::DockRegistry::unregisterLayout(KDDockWidgets::Controllers::Layout * arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__DockRegistry__unregisterLayout_Layout(void *thisObj, void *arg__1_);
// KDDockWidgets::DockRegistry::unregisterMainWindow(KDDockWidgets::Controllers::MainWindow *
// arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__DockRegistry__unregisterMainWindow_MainWindow(void *thisObj, void *arg__1_);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__DockRegistry__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__DockRegistry__registerVirtualMethodCallback(void *ptr, void *callback,
                                                             int methodId);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__DockRegistry_Finalizer(void *, void *cppObj,
                                                                          void *);
}

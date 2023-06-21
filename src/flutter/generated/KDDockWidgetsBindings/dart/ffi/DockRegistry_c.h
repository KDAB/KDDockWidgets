/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <DockRegistry.h>
#include <qstring.h>
#include <core/DockWidget.h>
#include "core/MainWindow.h"
#include <FloatingWindow.h>
#include <core/Layout.h>
#include <core/Group.h>
#include <Item_p.h>
#include <SideBar.h>
#include <qobject.h>

namespace KDDockWidgetsBindings_wrappersNS {
class DockRegistry_wrapper : public ::KDDockWidgets::DockRegistry
{
public:
    ~DockRegistry_wrapper();
    void checkSanityAll(bool dumpDebug = false);
    void clear();
    bool containsDockWidget(const QString &uniqueName) const;
    bool containsMainWindow(const QString &uniqueName) const;
    KDDockWidgets::Core::DockWidget *dockByName(const QString &arg__1) const;
    void dropIndicatorsInhibitedChanged(bool inhibited);
    void ensureAllFloatingWidgetsAreMorphed();
    KDDockWidgets::Core::DockWidget *focusedDockWidget() const;
    KDDockWidgets::Core::Group *groupInMDIResize() const;
    void groupInMDIResizeChanged();
    bool hasFloatingWindows() const;
    bool isEmpty(bool excludeBeingDeleted = false) const;
    bool isSane() const;
    bool itemIsInMainWindow(const KDDockWidgets::Core::Item *arg__1) const;
    KDDockWidgets::Core::Layout *layoutForItem(const KDDockWidgets::Core::Item *arg__1) const;
    KDDockWidgets::Core::MainWindow *mainWindowByName(const QString &arg__1) const;
    void registerDockWidget(KDDockWidgets::Core::DockWidget *arg__1);
    void registerFloatingWindow(KDDockWidgets::Core::FloatingWindow *arg__1);
    void registerGroup(KDDockWidgets::Core::Group *arg__1);
    void registerLayout(KDDockWidgets::Core::Layout *arg__1);
    void registerMainWindow(KDDockWidgets::Core::MainWindow *arg__1);
    static KDDockWidgets::DockRegistry *self();
    KDDockWidgets::Core::SideBar *sideBarForDockWidget(const KDDockWidgets::Core::DockWidget *arg__1) const;
    static QString tr(const char *s, const char *c, int n);
    void unregisterDockWidget(KDDockWidgets::Core::DockWidget *arg__1);
    void unregisterFloatingWindow(KDDockWidgets::Core::FloatingWindow *arg__1);
    void unregisterGroup(KDDockWidgets::Core::Group *arg__1);
    void unregisterLayout(KDDockWidgets::Core::Layout *arg__1);
    void unregisterMainWindow(KDDockWidgets::Core::MainWindow *arg__1);
};
}
extern "C" {
// KDDockWidgets::DockRegistry::checkSanityAll(bool dumpDebug)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__DockRegistry__checkSanityAll_bool(void *thisObj, bool dumpDebug);
// KDDockWidgets::DockRegistry::clear()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__DockRegistry__clear(void *thisObj);
// KDDockWidgets::DockRegistry::containsDockWidget(const QString & uniqueName) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__DockRegistry__containsDockWidget_QString(void *thisObj, const char *uniqueName_);
// KDDockWidgets::DockRegistry::containsMainWindow(const QString & uniqueName) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__DockRegistry__containsMainWindow_QString(void *thisObj, const char *uniqueName_);
// KDDockWidgets::DockRegistry::dockByName(const QString & arg__1) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__DockRegistry__dockByName_QString(void *thisObj, const char *arg__1_);
// KDDockWidgets::DockRegistry::dropIndicatorsInhibitedChanged(bool inhibited)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__DockRegistry__dropIndicatorsInhibitedChanged_bool(void *thisObj, bool inhibited);
// KDDockWidgets::DockRegistry::ensureAllFloatingWidgetsAreMorphed()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__DockRegistry__ensureAllFloatingWidgetsAreMorphed(void *thisObj);
// KDDockWidgets::DockRegistry::focusedDockWidget() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__DockRegistry__focusedDockWidget(void *thisObj);
// KDDockWidgets::DockRegistry::groupInMDIResize() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__DockRegistry__groupInMDIResize(void *thisObj);
// KDDockWidgets::DockRegistry::groupInMDIResizeChanged()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__DockRegistry__groupInMDIResizeChanged(void *thisObj);
// KDDockWidgets::DockRegistry::hasFloatingWindows() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__DockRegistry__hasFloatingWindows(void *thisObj);
// KDDockWidgets::DockRegistry::isEmpty(bool excludeBeingDeleted) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__DockRegistry__isEmpty_bool(void *thisObj, bool excludeBeingDeleted);
// KDDockWidgets::DockRegistry::isSane() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__DockRegistry__isSane(void *thisObj);
// KDDockWidgets::DockRegistry::itemIsInMainWindow(const KDDockWidgets::Core::Item * arg__1) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__DockRegistry__itemIsInMainWindow_Item(void *thisObj, void *arg__1_);
// KDDockWidgets::DockRegistry::layoutForItem(const KDDockWidgets::Core::Item * arg__1) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__DockRegistry__layoutForItem_Item(void *thisObj, void *arg__1_);
// KDDockWidgets::DockRegistry::mainWindowByName(const QString & arg__1) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__DockRegistry__mainWindowByName_QString(void *thisObj, const char *arg__1_);
// KDDockWidgets::DockRegistry::registerDockWidget(KDDockWidgets::Core::DockWidget * arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__DockRegistry__registerDockWidget_DockWidget(void *thisObj, void *arg__1_);
// KDDockWidgets::DockRegistry::registerFloatingWindow(KDDockWidgets::Core::FloatingWindow * arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__DockRegistry__registerFloatingWindow_FloatingWindow(void *thisObj, void *arg__1_);
// KDDockWidgets::DockRegistry::registerGroup(KDDockWidgets::Core::Group * arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__DockRegistry__registerGroup_Group(void *thisObj, void *arg__1_);
// KDDockWidgets::DockRegistry::registerLayout(KDDockWidgets::Core::Layout * arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__DockRegistry__registerLayout_Layout(void *thisObj, void *arg__1_);
// KDDockWidgets::DockRegistry::registerMainWindow(KDDockWidgets::Core::MainWindow * arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__DockRegistry__registerMainWindow_MainWindow(void *thisObj, void *arg__1_);
// KDDockWidgets::DockRegistry::self()
KDDockWidgetsBindings_EXPORT void *c_static_KDDockWidgets__DockRegistry__self();
// KDDockWidgets::DockRegistry::sideBarForDockWidget(const KDDockWidgets::Core::DockWidget * arg__1) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__DockRegistry__sideBarForDockWidget_DockWidget(void *thisObj, void *arg__1_);
// KDDockWidgets::DockRegistry::tr(const char * s, const char * c, int n)
KDDockWidgetsBindings_EXPORT void *c_static_KDDockWidgets__DockRegistry__tr_char_char_int(const char *s, const char *c, int n);
// KDDockWidgets::DockRegistry::unregisterDockWidget(KDDockWidgets::Core::DockWidget * arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__DockRegistry__unregisterDockWidget_DockWidget(void *thisObj, void *arg__1_);
// KDDockWidgets::DockRegistry::unregisterFloatingWindow(KDDockWidgets::Core::FloatingWindow * arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__DockRegistry__unregisterFloatingWindow_FloatingWindow(void *thisObj, void *arg__1_);
// KDDockWidgets::DockRegistry::unregisterGroup(KDDockWidgets::Core::Group * arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__DockRegistry__unregisterGroup_Group(void *thisObj, void *arg__1_);
// KDDockWidgets::DockRegistry::unregisterLayout(KDDockWidgets::Core::Layout * arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__DockRegistry__unregisterLayout_Layout(void *thisObj, void *arg__1_);
// KDDockWidgets::DockRegistry::unregisterMainWindow(KDDockWidgets::Core::MainWindow * arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__DockRegistry__unregisterMainWindow_MainWindow(void *thisObj, void *arg__1_);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__DockRegistry__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__DockRegistry__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__DockRegistry_Finalizer(void *cppObj);
}

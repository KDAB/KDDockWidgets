/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <ViewFactory.h>
#include <qstring.h>
#include <View.h>
#include <Group.h>
#include <TitleBar.h>
#include <Stack.h>
#include <TabBar.h>
#include <Separator.h>
#include <FloatingWindow.h>
#include <MainWindow.h>
#include <ClassicIndicatorWindowViewInterface.h>
#include <ClassicIndicators.h>
#include <DropArea.h>
#include <SideBar.h>
#include <qobject.h>
#include <qlist.h>
#include <qbytearray.h>

namespace KDDockWidgetsBindings_wrappersNS {
class ViewFactory_wrapper : public ::KDDockWidgets::ViewFactory
{
public:
    ~ViewFactory_wrapper();
    ViewFactory_wrapper();
    virtual KDDockWidgets::Views::ClassicIndicatorWindowViewInterface *createClassicIndicatorWindow(KDDockWidgets::Core::ClassicIndicators *arg__1) const;
    virtual KDDockWidgets::Views::ClassicIndicatorWindowViewInterface *createClassicIndicatorWindow_nocallback(KDDockWidgets::Core::ClassicIndicators *arg__1) const;
    virtual KDDockWidgets::View *createDockWidget(const QString &uniqueName, QFlags<KDDockWidgets::DockWidgetOption> options = {}, QFlags<KDDockWidgets::LayoutSaverOption> layoutSaverOptions = {}, Qt::WindowFlags windowFlags = {}) const;
    virtual KDDockWidgets::View *createDockWidget_nocallback(const QString &uniqueName, QFlags<KDDockWidgets::DockWidgetOption> options = {}, QFlags<KDDockWidgets::LayoutSaverOption> layoutSaverOptions = {}, Qt::WindowFlags windowFlags = {}) const;
    virtual KDDockWidgets::View *createDropArea(KDDockWidgets::Core::DropArea *arg__1, KDDockWidgets::View *parent) const;
    virtual KDDockWidgets::View *createDropArea_nocallback(KDDockWidgets::Core::DropArea *arg__1, KDDockWidgets::View *parent) const;
    virtual KDDockWidgets::View *createFloatingWindow(KDDockWidgets::Core::FloatingWindow *controller, KDDockWidgets::Core::MainWindow *parent = nullptr, Qt::WindowFlags windowFlags = {}) const;
    virtual KDDockWidgets::View *createFloatingWindow_nocallback(KDDockWidgets::Core::FloatingWindow *controller, KDDockWidgets::Core::MainWindow *parent = nullptr, Qt::WindowFlags windowFlags = {}) const;
    virtual KDDockWidgets::View *createGroup(KDDockWidgets::Core::Group *arg__1, KDDockWidgets::View *parent = nullptr) const;
    virtual KDDockWidgets::View *createGroup_nocallback(KDDockWidgets::Core::Group *arg__1, KDDockWidgets::View *parent = nullptr) const;
    virtual KDDockWidgets::View *createRubberBand(KDDockWidgets::View *parent) const;
    virtual KDDockWidgets::View *createRubberBand_nocallback(KDDockWidgets::View *parent) const;
    virtual KDDockWidgets::View *createSeparator(KDDockWidgets::Core::Separator *arg__1, KDDockWidgets::View *parent = nullptr) const;
    virtual KDDockWidgets::View *createSeparator_nocallback(KDDockWidgets::Core::Separator *arg__1, KDDockWidgets::View *parent = nullptr) const;
    virtual KDDockWidgets::View *createSideBar(KDDockWidgets::Core::SideBar *arg__1, KDDockWidgets::View *parent) const;
    virtual KDDockWidgets::View *createSideBar_nocallback(KDDockWidgets::Core::SideBar *arg__1, KDDockWidgets::View *parent) const;
    virtual KDDockWidgets::View *createStack(KDDockWidgets::Core::Stack *stack, KDDockWidgets::View *parent) const;
    virtual KDDockWidgets::View *createStack_nocallback(KDDockWidgets::Core::Stack *stack, KDDockWidgets::View *parent) const;
    virtual KDDockWidgets::View *createTabBar(KDDockWidgets::Core::TabBar *tabBar, KDDockWidgets::View *parent = nullptr) const;
    virtual KDDockWidgets::View *createTabBar_nocallback(KDDockWidgets::Core::TabBar *tabBar, KDDockWidgets::View *parent = nullptr) const;
    virtual KDDockWidgets::View *createTitleBar(KDDockWidgets::Core::TitleBar *controller, KDDockWidgets::View *parent) const;
    virtual KDDockWidgets::View *createTitleBar_nocallback(KDDockWidgets::Core::TitleBar *controller, KDDockWidgets::View *parent) const;
    static QString tr(const char *s, const char *c, int n);
    typedef KDDockWidgets::Views::ClassicIndicatorWindowViewInterface *(*Callback_createClassicIndicatorWindow)(void *, KDDockWidgets::Core::ClassicIndicators *arg__1);
    Callback_createClassicIndicatorWindow m_createClassicIndicatorWindowCallback = nullptr;
    typedef KDDockWidgets::View *(*Callback_createDockWidget)(void *, const QString &uniqueName, QFlags<KDDockWidgets::DockWidgetOption> options, QFlags<KDDockWidgets::LayoutSaverOption> layoutSaverOptions, Qt::WindowFlags windowFlags);
    Callback_createDockWidget m_createDockWidgetCallback = nullptr;
    typedef KDDockWidgets::View *(*Callback_createDropArea)(void *, KDDockWidgets::Core::DropArea *arg__1, KDDockWidgets::View *parent);
    Callback_createDropArea m_createDropAreaCallback = nullptr;
    typedef KDDockWidgets::View *(*Callback_createFloatingWindow)(void *, KDDockWidgets::Core::FloatingWindow *controller, KDDockWidgets::Core::MainWindow *parent, Qt::WindowFlags windowFlags);
    Callback_createFloatingWindow m_createFloatingWindowCallback = nullptr;
    typedef KDDockWidgets::View *(*Callback_createGroup)(void *, KDDockWidgets::Core::Group *arg__1, KDDockWidgets::View *parent);
    Callback_createGroup m_createGroupCallback = nullptr;
    typedef KDDockWidgets::View *(*Callback_createRubberBand)(void *, KDDockWidgets::View *parent);
    Callback_createRubberBand m_createRubberBandCallback = nullptr;
    typedef KDDockWidgets::View *(*Callback_createSeparator)(void *, KDDockWidgets::Core::Separator *arg__1, KDDockWidgets::View *parent);
    Callback_createSeparator m_createSeparatorCallback = nullptr;
    typedef KDDockWidgets::View *(*Callback_createSideBar)(void *, KDDockWidgets::Core::SideBar *arg__1, KDDockWidgets::View *parent);
    Callback_createSideBar m_createSideBarCallback = nullptr;
    typedef KDDockWidgets::View *(*Callback_createStack)(void *, KDDockWidgets::Core::Stack *stack, KDDockWidgets::View *parent);
    Callback_createStack m_createStackCallback = nullptr;
    typedef KDDockWidgets::View *(*Callback_createTabBar)(void *, KDDockWidgets::Core::TabBar *tabBar, KDDockWidgets::View *parent);
    Callback_createTabBar m_createTabBarCallback = nullptr;
    typedef KDDockWidgets::View *(*Callback_createTitleBar)(void *, KDDockWidgets::Core::TitleBar *controller, KDDockWidgets::View *parent);
    Callback_createTitleBar m_createTitleBarCallback = nullptr;
};
}
extern "C" {
// KDDockWidgets::ViewFactory::ViewFactory()
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__ViewFactory__constructor();
// KDDockWidgets::ViewFactory::createClassicIndicatorWindow(KDDockWidgets::Core::ClassicIndicators * arg__1) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__ViewFactory__createClassicIndicatorWindow_ClassicIndicators(void *thisObj, void *arg__1_);
// KDDockWidgets::ViewFactory::createDockWidget(const QString & uniqueName, QFlags<KDDockWidgets::DockWidgetOption> options, QFlags<KDDockWidgets::LayoutSaverOption> layoutSaverOptions, Qt::WindowFlags windowFlags) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__ViewFactory__createDockWidget_QString_DockWidgetOptions_LayoutSaverOptions_WindowFlags(void *thisObj, const char *uniqueName_, int options_, int layoutSaverOptions_, int windowFlags);
// KDDockWidgets::ViewFactory::createDropArea(KDDockWidgets::Core::DropArea * arg__1, KDDockWidgets::View * parent) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__ViewFactory__createDropArea_DropArea_View(void *thisObj, void *arg__1_, void *parent_);
// KDDockWidgets::ViewFactory::createFloatingWindow(KDDockWidgets::Core::FloatingWindow * controller, KDDockWidgets::Core::MainWindow * parent, Qt::WindowFlags windowFlags) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__ViewFactory__createFloatingWindow_FloatingWindow_MainWindow_WindowFlags(void *thisObj, void *controller_, void *parent_, int windowFlags);
// KDDockWidgets::ViewFactory::createGroup(KDDockWidgets::Core::Group * arg__1, KDDockWidgets::View * parent) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__ViewFactory__createGroup_Group_View(void *thisObj, void *arg__1_, void *parent_);
// KDDockWidgets::ViewFactory::createRubberBand(KDDockWidgets::View * parent) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__ViewFactory__createRubberBand_View(void *thisObj, void *parent_);
// KDDockWidgets::ViewFactory::createSeparator(KDDockWidgets::Core::Separator * arg__1, KDDockWidgets::View * parent) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__ViewFactory__createSeparator_Separator_View(void *thisObj, void *arg__1_, void *parent_);
// KDDockWidgets::ViewFactory::createSideBar(KDDockWidgets::Core::SideBar * arg__1, KDDockWidgets::View * parent) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__ViewFactory__createSideBar_SideBar_View(void *thisObj, void *arg__1_, void *parent_);
// KDDockWidgets::ViewFactory::createStack(KDDockWidgets::Core::Stack * stack, KDDockWidgets::View * parent) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__ViewFactory__createStack_Stack_View(void *thisObj, void *stack_, void *parent_);
// KDDockWidgets::ViewFactory::createTabBar(KDDockWidgets::Core::TabBar * tabBar, KDDockWidgets::View * parent) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__ViewFactory__createTabBar_TabBar_View(void *thisObj, void *tabBar_, void *parent_);
// KDDockWidgets::ViewFactory::createTitleBar(KDDockWidgets::Core::TitleBar * controller, KDDockWidgets::View * parent) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__ViewFactory__createTitleBar_TitleBar_View(void *thisObj, void *controller_, void *parent_);
// KDDockWidgets::ViewFactory::tr(const char * s, const char * c, int n)
KDDockWidgetsBindings_EXPORT void *c_static_KDDockWidgets__ViewFactory__tr_char_char_int(const char *s, const char *c, int n);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__ViewFactory__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__ViewFactory__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__ViewFactory_Finalizer(void *, void *cppObj, void *);
}

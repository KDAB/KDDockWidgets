/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include "core/MainWindow.h"
#include <core/View.h>
#include <qstring.h>
#include <core/DockWidget.h>
#include <KDDockWidgets.h>
#include <SideBar.h>
#include "core/DropArea.h"
#include <core/Layout.h>
#include <qrect.h>
#include <qsize.h>
#include <qpoint.h>

namespace KDDockWidgetsBindings_wrappersNS {
namespace KDDWBindingsCore {
class MainWindow_wrapper : public ::KDDockWidgets::Core::MainWindow
{
public:
    ~MainWindow_wrapper();
    MainWindow_wrapper(KDDockWidgets::Core::View *view, const QString &uniqueName, QFlags<KDDockWidgets::MainWindowOption> options);
    void addDockWidget(KDDockWidgets::Core::DockWidget *dockWidget, KDDockWidgets::Location location, KDDockWidgets::Core::DockWidget *relativeTo = nullptr, KDDockWidgets::InitialOption initialOption = {});
    void addDockWidgetAsTab(KDDockWidgets::Core::DockWidget *dockwidget);
    bool anySideBarIsVisible() const;
    QRect centralAreaGeometry() const;
    void clearSideBarOverlay(bool deleteFrame = true);
    bool closeDockWidgets(bool force = false);
    KDDockWidgets::Core::DropArea *dropArea() const;
    void init(const QString &name);
    bool isMDI() const;
    KDDockWidgets::Core::Layout *layout() const;
    void layoutEqually();
    void layoutParentContainerEqually(KDDockWidgets::Core::DockWidget *dockWidget);
    void moveToSideBar(KDDockWidgets::Core::DockWidget *dw);
    KDDockWidgets::Core::DropArea *multiSplitter() const;
    QFlags<KDDockWidgets::MainWindowOption> options() const;
    int overlayMargin() const;
    void overlayOnSideBar(KDDockWidgets::Core::DockWidget *dw);
    KDDockWidgets::Core::DockWidget *overlayedDockWidget() const;
    void restoreFromSideBar(KDDockWidgets::Core::DockWidget *dw);
    void setContentsMargins(int l, int t, int r, int b);
    void setOverlayMargin(int margin);
    virtual void setParentView_impl(KDDockWidgets::Core::View *parent);
    virtual void setParentView_impl_nocallback(KDDockWidgets::Core::View *parent);
    void setUniqueName(const QString &uniqueName);
    KDDockWidgets::Core::SideBar *sideBarForDockWidget(const KDDockWidgets::Core::DockWidget *dw) const;
    void toggleOverlayOnSideBar(KDDockWidgets::Core::DockWidget *dw);
    QString uniqueName() const;
    typedef void (*Callback_setParentView_impl)(void *, KDDockWidgets::Core::View *parent);
    Callback_setParentView_impl m_setParentView_implCallback = nullptr;
};
}
}
extern "C" {
// KDDockWidgets::Core::MainWindow::MainWindow(KDDockWidgets::Core::View * view, const QString & uniqueName, QFlags<KDDockWidgets::MainWindowOption> options)
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__MainWindow__constructor_View_QString_MainWindowOptions(void *view_, const char *uniqueName_, int options_);
// KDDockWidgets::Core::MainWindow::addDockWidget(KDDockWidgets::Core::DockWidget * dockWidget, KDDockWidgets::Location location, KDDockWidgets::Core::DockWidget * relativeTo, KDDockWidgets::InitialOption initialOption)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__MainWindow__addDockWidget_DockWidget_Location_DockWidget_InitialOption(void *thisObj, void *dockWidget_, int location, void *relativeTo_, void *initialOption_);
// KDDockWidgets::Core::MainWindow::addDockWidgetAsTab(KDDockWidgets::Core::DockWidget * dockwidget)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__MainWindow__addDockWidgetAsTab_DockWidget(void *thisObj, void *dockwidget_);
// KDDockWidgets::Core::MainWindow::anySideBarIsVisible() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__MainWindow__anySideBarIsVisible(void *thisObj);
// KDDockWidgets::Core::MainWindow::centralAreaGeometry() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__MainWindow__centralAreaGeometry(void *thisObj);
// KDDockWidgets::Core::MainWindow::clearSideBarOverlay(bool deleteFrame)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__MainWindow__clearSideBarOverlay_bool(void *thisObj, bool deleteFrame);
// KDDockWidgets::Core::MainWindow::closeDockWidgets(bool force)
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__MainWindow__closeDockWidgets_bool(void *thisObj, bool force);
// KDDockWidgets::Core::MainWindow::dropArea() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__MainWindow__dropArea(void *thisObj);
// KDDockWidgets::Core::MainWindow::init(const QString & name)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__MainWindow__init_QString(void *thisObj, const char *name_);
// KDDockWidgets::Core::MainWindow::isMDI() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__MainWindow__isMDI(void *thisObj);
// KDDockWidgets::Core::MainWindow::layout() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__MainWindow__layout(void *thisObj);
// KDDockWidgets::Core::MainWindow::layoutEqually()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__MainWindow__layoutEqually(void *thisObj);
// KDDockWidgets::Core::MainWindow::layoutParentContainerEqually(KDDockWidgets::Core::DockWidget * dockWidget)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__MainWindow__layoutParentContainerEqually_DockWidget(void *thisObj, void *dockWidget_);
// KDDockWidgets::Core::MainWindow::moveToSideBar(KDDockWidgets::Core::DockWidget * dw)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__MainWindow__moveToSideBar_DockWidget(void *thisObj, void *dw_);
// KDDockWidgets::Core::MainWindow::multiSplitter() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__MainWindow__multiSplitter(void *thisObj);
// KDDockWidgets::Core::MainWindow::options() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Core__MainWindow__options(void *thisObj);
// KDDockWidgets::Core::MainWindow::overlayMargin() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Core__MainWindow__overlayMargin(void *thisObj);
// KDDockWidgets::Core::MainWindow::overlayOnSideBar(KDDockWidgets::Core::DockWidget * dw)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__MainWindow__overlayOnSideBar_DockWidget(void *thisObj, void *dw_);
// KDDockWidgets::Core::MainWindow::overlayedDockWidget() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__MainWindow__overlayedDockWidget(void *thisObj);
// KDDockWidgets::Core::MainWindow::restoreFromSideBar(KDDockWidgets::Core::DockWidget * dw)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__MainWindow__restoreFromSideBar_DockWidget(void *thisObj, void *dw_);
// KDDockWidgets::Core::MainWindow::setContentsMargins(int l, int t, int r, int b)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__MainWindow__setContentsMargins_int_int_int_int(void *thisObj, int l, int t, int r, int b);
// KDDockWidgets::Core::MainWindow::setOverlayMargin(int margin)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__MainWindow__setOverlayMargin_int(void *thisObj, int margin);
// KDDockWidgets::Core::MainWindow::setParentView_impl(KDDockWidgets::Core::View * parent)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__MainWindow__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Core::MainWindow::setUniqueName(const QString & uniqueName)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__MainWindow__setUniqueName_QString(void *thisObj, const char *uniqueName_);
// KDDockWidgets::Core::MainWindow::sideBarForDockWidget(const KDDockWidgets::Core::DockWidget * dw) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__MainWindow__sideBarForDockWidget_DockWidget(void *thisObj, void *dw_);
// KDDockWidgets::Core::MainWindow::toggleOverlayOnSideBar(KDDockWidgets::Core::DockWidget * dw)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__MainWindow__toggleOverlayOnSideBar_DockWidget(void *thisObj, void *dw_);
// KDDockWidgets::Core::MainWindow::uniqueName() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__MainWindow__uniqueName(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__MainWindow__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__MainWindow__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__MainWindow_Finalizer(void *cppObj);
}

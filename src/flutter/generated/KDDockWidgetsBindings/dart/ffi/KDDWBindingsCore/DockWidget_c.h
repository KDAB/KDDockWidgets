/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <core/DockWidget.h>
#include <qstring.h>
#include <core/View.h>
#include <KDDockWidgets.h>
#include <FloatingWindow.h>
#include <qrect.h>
#include "core/TitleBar.h"
#include "core/MainWindow.h"
#include <qsize.h>
#include <qpoint.h>

namespace KDDockWidgetsBindings_wrappersNS {
namespace KDDWBindingsCore {
class DockWidget_wrapper : public ::KDDockWidgets::Core::DockWidget
{
public:
    ~DockWidget_wrapper();
    DockWidget_wrapper(KDDockWidgets::Core::View *view, const QString &uniqueName, QFlags<KDDockWidgets::DockWidgetOption> options = {}, QFlags<KDDockWidgets::LayoutSaverOption> layoutSaverOptions = {});
    void aboutToDelete(KDDockWidgets::Core::DockWidget *arg__1);
    void aboutToDeleteOnClose();
    void actualTitleBarChanged();
    void addDockWidgetAsTab(KDDockWidgets::Core::DockWidget *other, KDDockWidgets::InitialOption initialOption = {});
    void addDockWidgetToContainingWindow(KDDockWidgets::Core::DockWidget *other, KDDockWidgets::Location location, KDDockWidgets::Core::DockWidget *relativeTo = nullptr, KDDockWidgets::InitialOption initialOption = {});
    static KDDockWidgets::Core::DockWidget *byName(const QString &uniqueName);
    void closed();
    int currentTabIndex() const;
    KDDockWidgets::Core::FloatingWindow *floatingWindow() const;
    void forceClose();
    QRect groupGeometry() const;
    void guestViewChanged();
    bool hasPreviousDockedLocation() const;
    void iconChanged();
    void init();
    bool isCurrentTab() const;
    bool isFloating() const;
    void isFloatingChanged(bool arg__1);
    bool isFocused() const;
    void isFocusedChanged(bool arg__1);
    bool isInMainWindow() const;
    bool isInSideBar() const;
    bool isMainWindow() const;
    bool isOpen() const;
    void isOpenChanged(bool isOpen);
    bool isOverlayed() const;
    void isOverlayedChanged(bool arg__1);
    bool isPersistentCentralDockWidget() const;
    bool isTabbed() const;
    QSize lastOverlayedSize() const;
    QFlags<KDDockWidgets::LayoutSaverOption> layoutSaverOptions() const;
    KDDockWidgets::Core::MainWindow *mainWindow() const;
    void moveToSideBar();
    void onResize(QSize newSize);
    void open();
    QFlags<KDDockWidgets::DockWidgetOption> options() const;
    void optionsChanged(QFlags<KDDockWidgets::DockWidgetOption> arg__1);
    void raise();
    void removedFromSideBar();
    void setAffinityName(const QString &name);
    void setAsCurrentTab();
    bool setFloating(bool floats);
    void setFloatingGeometry(QRect geo);
    void setMDIPosition(QPoint pos);
    void setMDISize(QSize size);
    void setMDIZ(int z);
    void setOptions(QFlags<KDDockWidgets::DockWidgetOption> arg__1);
    virtual void setParentView_impl(KDDockWidgets::Core::View *parent);
    virtual void setParentView_impl_nocallback(KDDockWidgets::Core::View *parent);
    void setTitle(const QString &title);
    void setUserType(int userType);
    void show();
    bool skipsRestore() const;
    int tabIndex() const;
    QString title() const;
    KDDockWidgets::Core::TitleBar *titleBar() const;
    void titleChanged(const QString &title);
    static QString tr(const char *s, const char *c, int n);
    QString uniqueName() const;
    int userType() const;
    void windowActiveAboutToChange(bool activated);
    typedef void (*Callback_setParentView_impl)(void *, KDDockWidgets::Core::View *parent);
    Callback_setParentView_impl m_setParentView_implCallback = nullptr;
};
}
}
extern "C" {
// KDDockWidgets::Core::DockWidget::DockWidget(KDDockWidgets::Core::View * view, const QString & uniqueName, QFlags<KDDockWidgets::DockWidgetOption> options, QFlags<KDDockWidgets::LayoutSaverOption> layoutSaverOptions)
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__DockWidget__constructor_View_QString_DockWidgetOptions_LayoutSaverOptions(void *view_, const char *uniqueName_, int options_, int layoutSaverOptions_);
// KDDockWidgets::Core::DockWidget::aboutToDelete(KDDockWidgets::Core::DockWidget * arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget__aboutToDelete_DockWidget(void *thisObj, void *arg__1_);
// KDDockWidgets::Core::DockWidget::aboutToDeleteOnClose()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget__aboutToDeleteOnClose(void *thisObj);
// KDDockWidgets::Core::DockWidget::actualTitleBarChanged()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget__actualTitleBarChanged(void *thisObj);
// KDDockWidgets::Core::DockWidget::addDockWidgetAsTab(KDDockWidgets::Core::DockWidget * other, KDDockWidgets::InitialOption initialOption)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget__addDockWidgetAsTab_DockWidget_InitialOption(void *thisObj, void *other_, void *initialOption_);
// KDDockWidgets::Core::DockWidget::addDockWidgetToContainingWindow(KDDockWidgets::Core::DockWidget * other, KDDockWidgets::Location location, KDDockWidgets::Core::DockWidget * relativeTo, KDDockWidgets::InitialOption initialOption)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget__addDockWidgetToContainingWindow_DockWidget_Location_DockWidget_InitialOption(void *thisObj, void *other_, int location, void *relativeTo_, void *initialOption_);
// KDDockWidgets::Core::DockWidget::byName(const QString & uniqueName)
KDDockWidgetsBindings_EXPORT void *c_static_KDDockWidgets__Core__DockWidget__byName_QString(const char *uniqueName_);
// KDDockWidgets::Core::DockWidget::closed()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget__closed(void *thisObj);
// KDDockWidgets::Core::DockWidget::currentTabIndex() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Core__DockWidget__currentTabIndex(void *thisObj);
// KDDockWidgets::Core::DockWidget::floatingWindow() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__DockWidget__floatingWindow(void *thisObj);
// KDDockWidgets::Core::DockWidget::forceClose()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget__forceClose(void *thisObj);
// KDDockWidgets::Core::DockWidget::groupGeometry() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__DockWidget__groupGeometry(void *thisObj);
// KDDockWidgets::Core::DockWidget::guestViewChanged()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget__guestViewChanged(void *thisObj);
// KDDockWidgets::Core::DockWidget::hasPreviousDockedLocation() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__DockWidget__hasPreviousDockedLocation(void *thisObj);
// KDDockWidgets::Core::DockWidget::iconChanged()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget__iconChanged(void *thisObj);
// KDDockWidgets::Core::DockWidget::init()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget__init(void *thisObj);
// KDDockWidgets::Core::DockWidget::isCurrentTab() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__DockWidget__isCurrentTab(void *thisObj);
// KDDockWidgets::Core::DockWidget::isFloating() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__DockWidget__isFloating(void *thisObj);
// KDDockWidgets::Core::DockWidget::isFloatingChanged(bool arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget__isFloatingChanged_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Core::DockWidget::isFocused() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__DockWidget__isFocused(void *thisObj);
// KDDockWidgets::Core::DockWidget::isFocusedChanged(bool arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget__isFocusedChanged_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Core::DockWidget::isInMainWindow() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__DockWidget__isInMainWindow(void *thisObj);
// KDDockWidgets::Core::DockWidget::isInSideBar() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__DockWidget__isInSideBar(void *thisObj);
// KDDockWidgets::Core::DockWidget::isMainWindow() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__DockWidget__isMainWindow(void *thisObj);
// KDDockWidgets::Core::DockWidget::isOpen() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__DockWidget__isOpen(void *thisObj);
// KDDockWidgets::Core::DockWidget::isOpenChanged(bool isOpen)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget__isOpenChanged_bool(void *thisObj, bool isOpen);
// KDDockWidgets::Core::DockWidget::isOverlayed() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__DockWidget__isOverlayed(void *thisObj);
// KDDockWidgets::Core::DockWidget::isOverlayedChanged(bool arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget__isOverlayedChanged_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Core::DockWidget::isPersistentCentralDockWidget() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__DockWidget__isPersistentCentralDockWidget(void *thisObj);
// KDDockWidgets::Core::DockWidget::isTabbed() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__DockWidget__isTabbed(void *thisObj);
// KDDockWidgets::Core::DockWidget::lastOverlayedSize() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__DockWidget__lastOverlayedSize(void *thisObj);
// KDDockWidgets::Core::DockWidget::layoutSaverOptions() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Core__DockWidget__layoutSaverOptions(void *thisObj);
// KDDockWidgets::Core::DockWidget::mainWindow() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__DockWidget__mainWindow(void *thisObj);
// KDDockWidgets::Core::DockWidget::moveToSideBar()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget__moveToSideBar(void *thisObj);
// KDDockWidgets::Core::DockWidget::onResize(QSize newSize)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget__onResize_QSize(void *thisObj, void *newSize_);
// KDDockWidgets::Core::DockWidget::open()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget__open(void *thisObj);
// KDDockWidgets::Core::DockWidget::options() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Core__DockWidget__options(void *thisObj);
// KDDockWidgets::Core::DockWidget::optionsChanged(QFlags<KDDockWidgets::DockWidgetOption> arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget__optionsChanged_DockWidgetOptions(void *thisObj, int arg__1_);
// KDDockWidgets::Core::DockWidget::raise()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget__raise(void *thisObj);
// KDDockWidgets::Core::DockWidget::removedFromSideBar()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget__removedFromSideBar(void *thisObj);
// KDDockWidgets::Core::DockWidget::setAffinityName(const QString & name)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget__setAffinityName_QString(void *thisObj, const char *name_);
// KDDockWidgets::Core::DockWidget::setAsCurrentTab()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget__setAsCurrentTab(void *thisObj);
// KDDockWidgets::Core::DockWidget::setFloating(bool floats)
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__DockWidget__setFloating_bool(void *thisObj, bool floats);
// KDDockWidgets::Core::DockWidget::setFloatingGeometry(QRect geo)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget__setFloatingGeometry_QRect(void *thisObj, void *geo_);
// KDDockWidgets::Core::DockWidget::setMDIPosition(QPoint pos)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget__setMDIPosition_QPoint(void *thisObj, void *pos_);
// KDDockWidgets::Core::DockWidget::setMDISize(QSize size)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget__setMDISize_QSize(void *thisObj, void *size_);
// KDDockWidgets::Core::DockWidget::setMDIZ(int z)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget__setMDIZ_int(void *thisObj, int z);
// KDDockWidgets::Core::DockWidget::setOptions(QFlags<KDDockWidgets::DockWidgetOption> arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget__setOptions_DockWidgetOptions(void *thisObj, int arg__1_);
// KDDockWidgets::Core::DockWidget::setParentView_impl(KDDockWidgets::Core::View * parent)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Core::DockWidget::setTitle(const QString & title)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget__setTitle_QString(void *thisObj, const char *title_);
// KDDockWidgets::Core::DockWidget::setUserType(int userType)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget__setUserType_int(void *thisObj, int userType);
// KDDockWidgets::Core::DockWidget::show()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget__show(void *thisObj);
// KDDockWidgets::Core::DockWidget::skipsRestore() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__DockWidget__skipsRestore(void *thisObj);
// KDDockWidgets::Core::DockWidget::tabIndex() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Core__DockWidget__tabIndex(void *thisObj);
// KDDockWidgets::Core::DockWidget::title() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__DockWidget__title(void *thisObj);
// KDDockWidgets::Core::DockWidget::titleBar() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__DockWidget__titleBar(void *thisObj);
// KDDockWidgets::Core::DockWidget::titleChanged(const QString & title)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget__titleChanged_QString(void *thisObj, const char *title_);
// KDDockWidgets::Core::DockWidget::tr(const char * s, const char * c, int n)
KDDockWidgetsBindings_EXPORT void *c_static_KDDockWidgets__Core__DockWidget__tr_char_char_int(const char *s, const char *c, int n);
// KDDockWidgets::Core::DockWidget::uniqueName() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__DockWidget__uniqueName(void *thisObj);
// KDDockWidgets::Core::DockWidget::userType() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Core__DockWidget__userType(void *thisObj);
// KDDockWidgets::Core::DockWidget::windowActiveAboutToChange(bool activated)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget__windowActiveAboutToChange_bool(void *thisObj, bool activated);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__DockWidget_Finalizer(void *, void *cppObj, void *);
}

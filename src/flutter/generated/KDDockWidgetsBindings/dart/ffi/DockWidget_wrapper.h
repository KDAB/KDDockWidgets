/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <DockWidget.h>
#include <qstring.h>
#include <View.h>
#include <KDDockWidgets.h>
#include <FloatingWindow.h>
#include <qrect.h>
#include <TitleBar.h>
#include <MainWindow.h>
#include <qsize.h>
#include <qpoint.h>
#include <qobject.h>
#include <qcoreevent.h>

namespace KDDockWidgetsBindings_wrappersNS {
class DockWidget_wrapper : public ::KDDockWidgets::Controllers::DockWidget
{
public:
    ~DockWidget_wrapper();
    DockWidget_wrapper(KDDockWidgets::View *view, const QString &uniqueName,
                       QFlags<KDDockWidgets::DockWidgetOption> options = {},
                       QFlags<KDDockWidgets::LayoutSaverOption> layoutSaverOptions = {});
    void aboutToDelete(KDDockWidgets::Controllers::DockWidget *arg__1);
    void aboutToDeleteOnClose();
    void actualTitleBarChanged();
    void addDockWidgetAsTab(KDDockWidgets::Controllers::DockWidget *other,
                            KDDockWidgets::InitialOption initialOption = {});
    void
    addDockWidgetToContainingWindow(KDDockWidgets::Controllers::DockWidget *other,
                                    KDDockWidgets::Location location,
                                    KDDockWidgets::Controllers::DockWidget *relativeTo = nullptr,
                                    KDDockWidgets::InitialOption initialOption = {});
    static KDDockWidgets::Controllers::DockWidget *byName(const QString &uniqueName);
    int currentTabIndex() const;
    virtual void customEvent(QEvent *event);
    virtual void customEvent_nocallback(QEvent *event);
    virtual bool event(QEvent *event);
    virtual bool event_nocallback(QEvent *event);
    virtual bool eventFilter(QObject *watched, QEvent *event);
    virtual bool eventFilter_nocallback(QObject *watched, QEvent *event);
    KDDockWidgets::Controllers::FloatingWindow *floatingWindow() const;
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
    bool isOverlayed() const;
    void isOverlayedChanged(bool arg__1);
    bool isPersistentCentralDockWidget() const;
    bool isTabbed() const;
    QSize lastOverlayedSize() const;
    QFlags<KDDockWidgets::LayoutSaverOption> layoutSaverOptions() const;
    KDDockWidgets::Controllers::MainWindow *mainWindow() const;
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
    virtual void setParentView_impl(KDDockWidgets::View *parent);
    virtual void setParentView_impl_nocallback(KDDockWidgets::View *parent);
    void setTitle(const QString &title);
    void setUserType(int userType);
    void show();
    bool skipsRestore() const;
    int tabIndex() const;
    QString title() const;
    KDDockWidgets::Controllers::TitleBar *titleBar() const;
    void titleChanged(const QString &title);
    static QString tr(const char *s, const char *c, int n);
    QString uniqueName() const;
    int userType() const;
    void windowActiveAboutToChange(bool activated);
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
// KDDockWidgets::Controllers::DockWidget::DockWidget(KDDockWidgets::View * view, const QString &
// uniqueName, QFlags<KDDockWidgets::DockWidgetOption> options,
// QFlags<KDDockWidgets::LayoutSaverOption> layoutSaverOptions)
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__DockWidget__constructor_View_QString_DockWidgetOptions_LayoutSaverOptions(
    void *view_, const char *uniqueName_, int options_, int layoutSaverOptions_);
// KDDockWidgets::Controllers::DockWidget::aboutToDelete(KDDockWidgets::Controllers::DockWidget *
// arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DockWidget__aboutToDelete_DockWidget(void *thisObj, void *arg__1_);
// KDDockWidgets::Controllers::DockWidget::aboutToDeleteOnClose()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DockWidget__aboutToDeleteOnClose(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::actualTitleBarChanged()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DockWidget__actualTitleBarChanged(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::addDockWidgetAsTab(KDDockWidgets::Controllers::DockWidget
// * other, KDDockWidgets::InitialOption initialOption)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DockWidget__addDockWidgetAsTab_DockWidget_InitialOption(
    void *thisObj, void *other_, void *initialOption_);
// KDDockWidgets::Controllers::DockWidget::addDockWidgetToContainingWindow(KDDockWidgets::Controllers::DockWidget
// * other, KDDockWidgets::Location location, KDDockWidgets::Controllers::DockWidget * relativeTo,
// KDDockWidgets::InitialOption initialOption)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DockWidget__addDockWidgetToContainingWindow_DockWidget_Location_DockWidget_InitialOption(
    void *thisObj, void *other_, int location, void *relativeTo_, void *initialOption_);
// KDDockWidgets::Controllers::DockWidget::byName(const QString & uniqueName)
KDDockWidgetsBindings_EXPORT void *
c_static_KDDockWidgets__Controllers__DockWidget__byName_QString(const char *uniqueName_);
// KDDockWidgets::Controllers::DockWidget::currentTabIndex() const
KDDockWidgetsBindings_EXPORT int
c_KDDockWidgets__Controllers__DockWidget__currentTabIndex(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::customEvent(QEvent * event)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DockWidget__customEvent_QEvent(void *thisObj, void *event_);
// KDDockWidgets::Controllers::DockWidget::event(QEvent * event)
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__DockWidget__event_QEvent(void *thisObj, void *event_);
// KDDockWidgets::Controllers::DockWidget::eventFilter(QObject * watched, QEvent * event)
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__DockWidget__eventFilter_QObject_QEvent(void *thisObj, void *watched_,
                                                                     void *event_);
// KDDockWidgets::Controllers::DockWidget::floatingWindow() const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__DockWidget__floatingWindow(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::forceClose()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DockWidget__forceClose(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::groupGeometry() const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__DockWidget__groupGeometry(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::guestViewChanged()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DockWidget__guestViewChanged(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::hasPreviousDockedLocation() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__DockWidget__hasPreviousDockedLocation(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::iconChanged()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DockWidget__iconChanged(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::init()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__DockWidget__init(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::isCurrentTab() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__DockWidget__isCurrentTab(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::isFloating() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__DockWidget__isFloating(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::isFloatingChanged(bool arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DockWidget__isFloatingChanged_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Controllers::DockWidget::isFocused() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__DockWidget__isFocused(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::isFocusedChanged(bool arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DockWidget__isFocusedChanged_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Controllers::DockWidget::isInMainWindow() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__DockWidget__isInMainWindow(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::isInSideBar() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__DockWidget__isInSideBar(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::isMainWindow() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__DockWidget__isMainWindow(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::isOpen() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__DockWidget__isOpen(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::isOverlayed() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__DockWidget__isOverlayed(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::isOverlayedChanged(bool arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DockWidget__isOverlayedChanged_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Controllers::DockWidget::isPersistentCentralDockWidget() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__DockWidget__isPersistentCentralDockWidget(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::isTabbed() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__DockWidget__isTabbed(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::lastOverlayedSize() const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__DockWidget__lastOverlayedSize(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::layoutSaverOptions() const
KDDockWidgetsBindings_EXPORT int
c_KDDockWidgets__Controllers__DockWidget__layoutSaverOptions(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::mainWindow() const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__DockWidget__mainWindow(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::moveToSideBar()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DockWidget__moveToSideBar(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::onResize(QSize newSize)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DockWidget__onResize_QSize(void *thisObj, void *newSize_);
// KDDockWidgets::Controllers::DockWidget::open()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__DockWidget__open(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::options() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Controllers__DockWidget__options(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::optionsChanged(QFlags<KDDockWidgets::DockWidgetOption>
// arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DockWidget__optionsChanged_DockWidgetOptions(void *thisObj,
                                                                           int arg__1_);
// KDDockWidgets::Controllers::DockWidget::raise()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__DockWidget__raise(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::removedFromSideBar()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DockWidget__removedFromSideBar(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::setAffinityName(const QString & name)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DockWidget__setAffinityName_QString(void *thisObj, const char *name_);
// KDDockWidgets::Controllers::DockWidget::setAsCurrentTab()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DockWidget__setAsCurrentTab(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::setFloating(bool floats)
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__DockWidget__setFloating_bool(void *thisObj, bool floats);
// KDDockWidgets::Controllers::DockWidget::setFloatingGeometry(QRect geo)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DockWidget__setFloatingGeometry_QRect(void *thisObj, void *geo_);
// KDDockWidgets::Controllers::DockWidget::setMDIPosition(QPoint pos)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DockWidget__setMDIPosition_QPoint(void *thisObj, void *pos_);
// KDDockWidgets::Controllers::DockWidget::setMDISize(QSize size)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DockWidget__setMDISize_QSize(void *thisObj, void *size_);
// KDDockWidgets::Controllers::DockWidget::setMDIZ(int z)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DockWidget__setMDIZ_int(void *thisObj, int z);
// KDDockWidgets::Controllers::DockWidget::setOptions(QFlags<KDDockWidgets::DockWidgetOption>
// arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DockWidget__setOptions_DockWidgetOptions(void *thisObj, int arg__1_);
// KDDockWidgets::Controllers::DockWidget::setParentView_impl(KDDockWidgets::View * parent)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DockWidget__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Controllers::DockWidget::setTitle(const QString & title)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DockWidget__setTitle_QString(void *thisObj, const char *title_);
// KDDockWidgets::Controllers::DockWidget::setUserType(int userType)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DockWidget__setUserType_int(void *thisObj, int userType);
// KDDockWidgets::Controllers::DockWidget::show()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__DockWidget__show(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::skipsRestore() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__DockWidget__skipsRestore(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::tabIndex() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Controllers__DockWidget__tabIndex(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::title() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controllers__DockWidget__title(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::titleBar() const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__DockWidget__titleBar(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::titleChanged(const QString & title)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DockWidget__titleChanged_QString(void *thisObj, const char *title_);
// KDDockWidgets::Controllers::DockWidget::tr(const char * s, const char * c, int n)
KDDockWidgetsBindings_EXPORT void *
c_static_KDDockWidgets__Controllers__DockWidget__tr_char_char_int(const char *s, const char *c,
                                                                  int n);
// KDDockWidgets::Controllers::DockWidget::uniqueName() const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__DockWidget__uniqueName(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::userType() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Controllers__DockWidget__userType(void *thisObj);
// KDDockWidgets::Controllers::DockWidget::windowActiveAboutToChange(bool activated)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DockWidget__windowActiveAboutToChange_bool(void *thisObj,
                                                                         bool activated);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DockWidget__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DockWidget__registerVirtualMethodCallback(void *ptr, void *callback,
                                                                        int methodId);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__DockWidget_Finalizer(void *, void *cppObj, void *);
}

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <TitleBar.h>
#include <qstring.h>
#include <Group.h>
#include <FloatingWindow.h>
#include <DockWidget.h>
#include <TabBar.h>
#include <qrect.h>
#include <qpoint.h>
#include <qcoreevent.h>
#include <qsize.h>
#include <qobject.h>
#include <View.h>

namespace KDDockWidgetsBindings_wrappersNS {
class TitleBar_wrapper : public ::KDDockWidgets::Controllers::TitleBar
{
public:
    ~TitleBar_wrapper();
    TitleBar_wrapper(KDDockWidgets::Controllers::FloatingWindow *parent);
    TitleBar_wrapper(KDDockWidgets::Controllers::Group *parent);
    bool closeButtonEnabled() const;
    void closeButtonEnabledChanged(bool arg__1);
    virtual void customEvent(QEvent *event);
    virtual void customEvent_nocallback(QEvent *event);
    virtual bool event(QEvent *event);
    virtual bool event_nocallback(QEvent *event);
    virtual bool eventFilter(QObject *watched, QEvent *event);
    virtual bool eventFilter_nocallback(QObject *watched, QEvent *event);
    QString floatButtonToolTip() const;
    void floatButtonToolTipChanged(const QString &arg__1);
    bool floatButtonVisible() const;
    void floatButtonVisibleChanged(bool arg__1);
    KDDockWidgets::Controllers::FloatingWindow *floatingWindow() const;
    KDDockWidgets::Controllers::Group *group() const;
    bool hasIcon() const;
    void iconChanged();
    bool isCloseButtonEnabled() const;
    bool isCloseButtonVisible() const;
    bool isFloatButtonVisible() const;
    bool isFloating() const;
    bool isFocused() const;
    void isFocusedChanged();
    virtual bool isMDI() const;
    virtual bool isMDI_nocallback() const;
    bool isOverlayed() const;
    virtual bool isWindow() const;
    virtual bool isWindow_nocallback() const;
    void minimizeButtonChanged(bool visible, bool enabled);
    void onAutoHideClicked();
    void onCloseClicked();
    bool onDoubleClicked();
    void onFloatClicked();
    void onMaximizeClicked();
    void onMinimizeClicked();
    void setCloseButtonEnabled(bool arg__1);
    void setFloatButtonVisible(bool arg__1);
    virtual void setParentView_impl(KDDockWidgets::View *parent);
    virtual void setParentView_impl_nocallback(KDDockWidgets::View *parent);
    void setTitle(const QString &title);
    virtual KDDockWidgets::Controllers::DockWidget *singleDockWidget() const;
    virtual KDDockWidgets::Controllers::DockWidget *singleDockWidget_nocallback() const;
    bool supportsAutoHideButton() const;
    bool supportsFloatingButton() const;
    bool supportsMaximizeButton() const;
    bool supportsMinimizeButton() const;
    KDDockWidgets::Controllers::TabBar *tabBar() const;
    QString title() const;
    bool titleBarIsFocusable() const;
    void titleChanged();
    void toggleMaximized();
    static QString tr(const char *s, const char *c, int n);
    void updateButtons();
    typedef void (*Callback_customEvent)(void *, QEvent *event);
    Callback_customEvent m_customEventCallback = nullptr;
    typedef bool (*Callback_event)(void *, QEvent *event);
    Callback_event m_eventCallback = nullptr;
    typedef bool (*Callback_eventFilter)(void *, QObject *watched, QEvent *event);
    Callback_eventFilter m_eventFilterCallback = nullptr;
    typedef bool (*Callback_isMDI)(void *);
    Callback_isMDI m_isMDICallback = nullptr;
    typedef bool (*Callback_isWindow)(void *);
    Callback_isWindow m_isWindowCallback = nullptr;
    typedef void (*Callback_setParentView_impl)(void *, KDDockWidgets::View *parent);
    Callback_setParentView_impl m_setParentView_implCallback = nullptr;
    typedef KDDockWidgets::Controllers::DockWidget *(*Callback_singleDockWidget)(void *);
    Callback_singleDockWidget m_singleDockWidgetCallback = nullptr;
};
}
extern "C" {
// KDDockWidgets::Controllers::TitleBar::TitleBar(KDDockWidgets::Controllers::FloatingWindow *
// parent)
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__TitleBar__constructor_FloatingWindow(void *parent_);
// KDDockWidgets::Controllers::TitleBar::TitleBar(KDDockWidgets::Controllers::Group * parent)
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__TitleBar__constructor_Group(void *parent_);
// KDDockWidgets::Controllers::TitleBar::closeButtonEnabled() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__TitleBar__closeButtonEnabled(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::closeButtonEnabledChanged(bool arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__TitleBar__closeButtonEnabledChanged_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Controllers::TitleBar::customEvent(QEvent * event)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__TitleBar__customEvent_QEvent(void *thisObj, void *event_);
// KDDockWidgets::Controllers::TitleBar::event(QEvent * event)
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__TitleBar__event_QEvent(void *thisObj, void *event_);
// KDDockWidgets::Controllers::TitleBar::eventFilter(QObject * watched, QEvent * event)
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__TitleBar__eventFilter_QObject_QEvent(void *thisObj, void *watched_,
                                                                   void *event_);
// KDDockWidgets::Controllers::TitleBar::floatButtonToolTip() const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__TitleBar__floatButtonToolTip(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::floatButtonToolTipChanged(const QString & arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__TitleBar__floatButtonToolTipChanged_QString(void *thisObj,
                                                                          const char *arg__1_);
// KDDockWidgets::Controllers::TitleBar::floatButtonVisible() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__TitleBar__floatButtonVisible(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::floatButtonVisibleChanged(bool arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__TitleBar__floatButtonVisibleChanged_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Controllers::TitleBar::floatingWindow() const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__TitleBar__floatingWindow(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::group() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controllers__TitleBar__group(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::hasIcon() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__TitleBar__hasIcon(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::iconChanged()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__TitleBar__iconChanged(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::isCloseButtonEnabled() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__TitleBar__isCloseButtonEnabled(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::isCloseButtonVisible() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__TitleBar__isCloseButtonVisible(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::isFloatButtonVisible() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__TitleBar__isFloatButtonVisible(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::isFloating() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__TitleBar__isFloating(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::isFocused() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__TitleBar__isFocused(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::isFocusedChanged()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__TitleBar__isFocusedChanged(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::isMDI() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__TitleBar__isMDI(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::isOverlayed() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__TitleBar__isOverlayed(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::isWindow() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Controllers__TitleBar__isWindow(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::minimizeButtonChanged(bool visible, bool enabled)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__TitleBar__minimizeButtonChanged_bool_bool(void *thisObj, bool visible,
                                                                        bool enabled);
// KDDockWidgets::Controllers::TitleBar::onAutoHideClicked()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__TitleBar__onAutoHideClicked(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::onCloseClicked()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__TitleBar__onCloseClicked(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::onDoubleClicked()
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__TitleBar__onDoubleClicked(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::onFloatClicked()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__TitleBar__onFloatClicked(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::onMaximizeClicked()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__TitleBar__onMaximizeClicked(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::onMinimizeClicked()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__TitleBar__onMinimizeClicked(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::setCloseButtonEnabled(bool arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__TitleBar__setCloseButtonEnabled_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Controllers::TitleBar::setFloatButtonVisible(bool arg__1)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__TitleBar__setFloatButtonVisible_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Controllers::TitleBar::setParentView_impl(KDDockWidgets::View * parent)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__TitleBar__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Controllers::TitleBar::setTitle(const QString & title)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__TitleBar__setTitle_QString(void *thisObj, const char *title_);
// KDDockWidgets::Controllers::TitleBar::singleDockWidget() const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Controllers__TitleBar__singleDockWidget(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::supportsAutoHideButton() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__TitleBar__supportsAutoHideButton(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::supportsFloatingButton() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__TitleBar__supportsFloatingButton(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::supportsMaximizeButton() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__TitleBar__supportsMaximizeButton(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::supportsMinimizeButton() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__TitleBar__supportsMinimizeButton(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::tabBar() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controllers__TitleBar__tabBar(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::title() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Controllers__TitleBar__title(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::titleBarIsFocusable() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Controllers__TitleBar__titleBarIsFocusable(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::titleChanged()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__TitleBar__titleChanged(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::toggleMaximized()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__TitleBar__toggleMaximized(void *thisObj);
// KDDockWidgets::Controllers::TitleBar::tr(const char * s, const char * c, int n)
KDDockWidgetsBindings_EXPORT void *
c_static_KDDockWidgets__Controllers__TitleBar__tr_char_char_int(const char *s, const char *c,
                                                                int n);
// KDDockWidgets::Controllers::TitleBar::updateButtons()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__TitleBar__updateButtons(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Controllers__TitleBar__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__TitleBar__registerVirtualMethodCallback(void *ptr, void *callback,
                                                                      int methodId);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Controllers__TitleBar_Finalizer(void *, void *cppObj, void *);
}

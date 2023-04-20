/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <TitleBar.h>
#include <qstring.h>
#include <core/Group.h>
#include <FloatingWindow.h>
#include <core/DockWidget.h>
#include <MainWindow.h>
#include <TabBar.h>
#include <core/View.h>
#include <qrect.h>
#include <qpoint.h>
#include <qsize.h>

namespace KDDockWidgetsBindings_wrappersNS {
class TitleBar_wrapper : public ::KDDockWidgets::Core::TitleBar
{
public:
    ~TitleBar_wrapper();
    TitleBar_wrapper(KDDockWidgets::Core::FloatingWindow *parent);
    TitleBar_wrapper(KDDockWidgets::Core::Group *parent);
    bool closeButtonEnabled() const;
    void closeButtonEnabledChanged(bool arg__1);
    QString floatButtonToolTip() const;
    void floatButtonToolTipChanged(const QString &arg__1);
    bool floatButtonVisible() const;
    void floatButtonVisibleChanged(bool arg__1);
    KDDockWidgets::Core::FloatingWindow *floatingWindow() const;
    KDDockWidgets::Core::Group *group() const;
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
    KDDockWidgets::Core::MainWindow *mainWindow() const;
    bool maximizeButtonVisible() const;
    void minimizeButtonChanged(bool visible, bool enabled);
    void numDockWidgetsChanged();
    void onAutoHideClicked();
    void onCloseClicked();
    bool onDoubleClicked();
    void onFloatClicked();
    void onMaximizeClicked();
    void onMinimizeClicked();
    void setCloseButtonEnabled(bool arg__1);
    void setFloatButtonVisible(bool arg__1);
    virtual void setParentView_impl(KDDockWidgets::Core::View *parent);
    virtual void setParentView_impl_nocallback(KDDockWidgets::Core::View *parent);
    void setTitle(const QString &title);
    virtual KDDockWidgets::Core::DockWidget *singleDockWidget() const;
    virtual KDDockWidgets::Core::DockWidget *singleDockWidget_nocallback() const;
    bool supportsAutoHideButton() const;
    bool supportsFloatingButton() const;
    bool supportsMaximizeButton() const;
    bool supportsMinimizeButton() const;
    KDDockWidgets::Core::TabBar *tabBar() const;
    QString title() const;
    bool titleBarIsFocusable() const;
    void titleChanged();
    void toggleMaximized();
    static QString tr(const char *s, const char *c, int n);
    void updateButtons();
    typedef bool (*Callback_isMDI)(void *);
    Callback_isMDI m_isMDICallback = nullptr;
    typedef bool (*Callback_isWindow)(void *);
    Callback_isWindow m_isWindowCallback = nullptr;
    typedef void (*Callback_setParentView_impl)(void *, KDDockWidgets::Core::View *parent);
    Callback_setParentView_impl m_setParentView_implCallback = nullptr;
    typedef KDDockWidgets::Core::DockWidget *(*Callback_singleDockWidget)(void *);
    Callback_singleDockWidget m_singleDockWidgetCallback = nullptr;
};
}
extern "C" {
// KDDockWidgets::Core::TitleBar::TitleBar(KDDockWidgets::Core::FloatingWindow * parent)
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__TitleBar__constructor_FloatingWindow(void *parent_);
// KDDockWidgets::Core::TitleBar::TitleBar(KDDockWidgets::Core::Group * parent)
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__TitleBar__constructor_Group(void *parent_);
// KDDockWidgets::Core::TitleBar::closeButtonEnabled() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__TitleBar__closeButtonEnabled(void *thisObj);
// KDDockWidgets::Core::TitleBar::closeButtonEnabledChanged(bool arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__TitleBar__closeButtonEnabledChanged_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Core::TitleBar::floatButtonToolTip() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__TitleBar__floatButtonToolTip(void *thisObj);
// KDDockWidgets::Core::TitleBar::floatButtonToolTipChanged(const QString & arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__TitleBar__floatButtonToolTipChanged_QString(void *thisObj, const char *arg__1_);
// KDDockWidgets::Core::TitleBar::floatButtonVisible() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__TitleBar__floatButtonVisible(void *thisObj);
// KDDockWidgets::Core::TitleBar::floatButtonVisibleChanged(bool arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__TitleBar__floatButtonVisibleChanged_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Core::TitleBar::floatingWindow() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__TitleBar__floatingWindow(void *thisObj);
// KDDockWidgets::Core::TitleBar::group() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__TitleBar__group(void *thisObj);
// KDDockWidgets::Core::TitleBar::hasIcon() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__TitleBar__hasIcon(void *thisObj);
// KDDockWidgets::Core::TitleBar::iconChanged()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__TitleBar__iconChanged(void *thisObj);
// KDDockWidgets::Core::TitleBar::isCloseButtonEnabled() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__TitleBar__isCloseButtonEnabled(void *thisObj);
// KDDockWidgets::Core::TitleBar::isCloseButtonVisible() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__TitleBar__isCloseButtonVisible(void *thisObj);
// KDDockWidgets::Core::TitleBar::isFloatButtonVisible() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__TitleBar__isFloatButtonVisible(void *thisObj);
// KDDockWidgets::Core::TitleBar::isFloating() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__TitleBar__isFloating(void *thisObj);
// KDDockWidgets::Core::TitleBar::isFocused() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__TitleBar__isFocused(void *thisObj);
// KDDockWidgets::Core::TitleBar::isFocusedChanged()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__TitleBar__isFocusedChanged(void *thisObj);
// KDDockWidgets::Core::TitleBar::isMDI() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__TitleBar__isMDI(void *thisObj);
// KDDockWidgets::Core::TitleBar::isOverlayed() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__TitleBar__isOverlayed(void *thisObj);
// KDDockWidgets::Core::TitleBar::isWindow() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__TitleBar__isWindow(void *thisObj);
// KDDockWidgets::Core::TitleBar::mainWindow() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__TitleBar__mainWindow(void *thisObj);
// KDDockWidgets::Core::TitleBar::maximizeButtonVisible() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__TitleBar__maximizeButtonVisible(void *thisObj);
// KDDockWidgets::Core::TitleBar::minimizeButtonChanged(bool visible, bool enabled)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__TitleBar__minimizeButtonChanged_bool_bool(void *thisObj, bool visible, bool enabled);
// KDDockWidgets::Core::TitleBar::numDockWidgetsChanged()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__TitleBar__numDockWidgetsChanged(void *thisObj);
// KDDockWidgets::Core::TitleBar::onAutoHideClicked()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__TitleBar__onAutoHideClicked(void *thisObj);
// KDDockWidgets::Core::TitleBar::onCloseClicked()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__TitleBar__onCloseClicked(void *thisObj);
// KDDockWidgets::Core::TitleBar::onDoubleClicked()
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__TitleBar__onDoubleClicked(void *thisObj);
// KDDockWidgets::Core::TitleBar::onFloatClicked()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__TitleBar__onFloatClicked(void *thisObj);
// KDDockWidgets::Core::TitleBar::onMaximizeClicked()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__TitleBar__onMaximizeClicked(void *thisObj);
// KDDockWidgets::Core::TitleBar::onMinimizeClicked()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__TitleBar__onMinimizeClicked(void *thisObj);
// KDDockWidgets::Core::TitleBar::setCloseButtonEnabled(bool arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__TitleBar__setCloseButtonEnabled_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Core::TitleBar::setFloatButtonVisible(bool arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__TitleBar__setFloatButtonVisible_bool(void *thisObj, bool arg__1);
// KDDockWidgets::Core::TitleBar::setParentView_impl(KDDockWidgets::Core::View * parent)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__TitleBar__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Core::TitleBar::setTitle(const QString & title)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__TitleBar__setTitle_QString(void *thisObj, const char *title_);
// KDDockWidgets::Core::TitleBar::singleDockWidget() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__TitleBar__singleDockWidget(void *thisObj);
// KDDockWidgets::Core::TitleBar::supportsAutoHideButton() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__TitleBar__supportsAutoHideButton(void *thisObj);
// KDDockWidgets::Core::TitleBar::supportsFloatingButton() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__TitleBar__supportsFloatingButton(void *thisObj);
// KDDockWidgets::Core::TitleBar::supportsMaximizeButton() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__TitleBar__supportsMaximizeButton(void *thisObj);
// KDDockWidgets::Core::TitleBar::supportsMinimizeButton() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__TitleBar__supportsMinimizeButton(void *thisObj);
// KDDockWidgets::Core::TitleBar::tabBar() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__TitleBar__tabBar(void *thisObj);
// KDDockWidgets::Core::TitleBar::title() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__TitleBar__title(void *thisObj);
// KDDockWidgets::Core::TitleBar::titleBarIsFocusable() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__TitleBar__titleBarIsFocusable(void *thisObj);
// KDDockWidgets::Core::TitleBar::titleChanged()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__TitleBar__titleChanged(void *thisObj);
// KDDockWidgets::Core::TitleBar::toggleMaximized()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__TitleBar__toggleMaximized(void *thisObj);
// KDDockWidgets::Core::TitleBar::tr(const char * s, const char * c, int n)
KDDockWidgetsBindings_EXPORT void *c_static_KDDockWidgets__Core__TitleBar__tr_char_char_int(const char *s, const char *c, int n);
// KDDockWidgets::Core::TitleBar::updateButtons()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__TitleBar__updateButtons(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__TitleBar__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__TitleBar__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__TitleBar_Finalizer(void *, void *cppObj, void *);
}

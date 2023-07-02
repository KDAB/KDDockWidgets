/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <TabBar.h>
#include <qstring.h>
#include "core/Stack.h"
#include <core/DockWidget.h>
#include <qpoint.h>
#include <core/Group.h>
#include <qrect.h>
#include <qsize.h>
#include <core/View.h>

namespace KDDockWidgetsBindings_wrappersNS {
namespace KDDWBindingsCore {
class TabBar_wrapper : public ::KDDockWidgets::Core::TabBar
{
public:
    ~TabBar_wrapper();
    TabBar_wrapper(KDDockWidgets::Core::Stack *tabWidget = nullptr);
    KDDockWidgets::Core::DockWidget *currentDockWidget() const;
    int currentIndex() const;
    KDDockWidgets::Core::DockWidget *dockWidgetAt(QPoint localPos) const;
    KDDockWidgets::Core::DockWidget *dockWidgetAt(int index) const;
    virtual bool dragCanStart(QPoint pressPos, QPoint pos) const;
    virtual bool dragCanStart_nocallback(QPoint pressPos, QPoint pos) const;
    KDDockWidgets::Core::Group *group() const;
    bool hasSingleDockWidget() const;
    int indexOfDockWidget(const KDDockWidgets::Core::DockWidget *dw) const;
    virtual bool isMDI() const;
    virtual bool isMDI_nocallback() const;
    virtual bool isWindow() const;
    virtual bool isWindow_nocallback() const;
    void moveTabTo(int from, int to);
    int numDockWidgets() const;
    void onMouseDoubleClick(QPoint localPos);
    void onMousePress(QPoint localPos);
    QRect rectForTab(int index) const;
    void removeDockWidget(KDDockWidgets::Core::DockWidget *dw);
    void renameTab(int index, const QString &arg__2);
    void setCurrentDockWidget(KDDockWidgets::Core::DockWidget *dw);
    void setCurrentIndex(int index);
    virtual void setParentView_impl(KDDockWidgets::Core::View *parent);
    virtual void setParentView_impl_nocallback(KDDockWidgets::Core::View *parent);
    virtual KDDockWidgets::Core::DockWidget *singleDockWidget() const;
    virtual KDDockWidgets::Core::DockWidget *singleDockWidget_nocallback() const;
    KDDockWidgets::Core::Stack *stack() const;
    bool tabsAreMovable() const;
    QString text(int index) const;
    static QString tr(const char *s, const char *c, int n);
    typedef bool (*Callback_dragCanStart)(void *, QPoint *pressPos, QPoint *pos);
    Callback_dragCanStart m_dragCanStartCallback = nullptr;
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
}
extern "C" {
// KDDockWidgets::Core::TabBar::TabBar(KDDockWidgets::Core::Stack * tabWidget)
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__TabBar__constructor_Stack(void *tabWidget_);
// KDDockWidgets::Core::TabBar::currentDockWidget() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__TabBar__currentDockWidget(void *thisObj);
// KDDockWidgets::Core::TabBar::currentIndex() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Core__TabBar__currentIndex(void *thisObj);
// KDDockWidgets::Core::TabBar::dockWidgetAt(QPoint localPos) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__TabBar__dockWidgetAt_QPoint(void *thisObj, void *localPos_);
// KDDockWidgets::Core::TabBar::dockWidgetAt(int index) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__TabBar__dockWidgetAt_int(void *thisObj, int index);
// KDDockWidgets::Core::TabBar::dragCanStart(QPoint pressPos, QPoint pos) const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__TabBar__dragCanStart_QPoint_QPoint(void *thisObj, void *pressPos_, void *pos_);
// KDDockWidgets::Core::TabBar::group() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__TabBar__group(void *thisObj);
// KDDockWidgets::Core::TabBar::hasSingleDockWidget() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__TabBar__hasSingleDockWidget(void *thisObj);
// KDDockWidgets::Core::TabBar::indexOfDockWidget(const KDDockWidgets::Core::DockWidget * dw) const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Core__TabBar__indexOfDockWidget_DockWidget(void *thisObj, void *dw_);
// KDDockWidgets::Core::TabBar::isMDI() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__TabBar__isMDI(void *thisObj);
// KDDockWidgets::Core::TabBar::isWindow() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__TabBar__isWindow(void *thisObj);
// KDDockWidgets::Core::TabBar::moveTabTo(int from, int to)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__TabBar__moveTabTo_int_int(void *thisObj, int from, int to);
// KDDockWidgets::Core::TabBar::numDockWidgets() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Core__TabBar__numDockWidgets(void *thisObj);
// KDDockWidgets::Core::TabBar::onMouseDoubleClick(QPoint localPos)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__TabBar__onMouseDoubleClick_QPoint(void *thisObj, void *localPos_);
// KDDockWidgets::Core::TabBar::onMousePress(QPoint localPos)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__TabBar__onMousePress_QPoint(void *thisObj, void *localPos_);
// KDDockWidgets::Core::TabBar::rectForTab(int index) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__TabBar__rectForTab_int(void *thisObj, int index);
// KDDockWidgets::Core::TabBar::removeDockWidget(KDDockWidgets::Core::DockWidget * dw)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__TabBar__removeDockWidget_DockWidget(void *thisObj, void *dw_);
// KDDockWidgets::Core::TabBar::renameTab(int index, const QString & arg__2)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__TabBar__renameTab_int_QString(void *thisObj, int index, const char *arg__2_);
// KDDockWidgets::Core::TabBar::setCurrentDockWidget(KDDockWidgets::Core::DockWidget * dw)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__TabBar__setCurrentDockWidget_DockWidget(void *thisObj, void *dw_);
// KDDockWidgets::Core::TabBar::setCurrentIndex(int index)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__TabBar__setCurrentIndex_int(void *thisObj, int index);
// KDDockWidgets::Core::TabBar::setParentView_impl(KDDockWidgets::Core::View * parent)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__TabBar__setParentView_impl_View(void *thisObj, void *parent_);
// KDDockWidgets::Core::TabBar::singleDockWidget() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__TabBar__singleDockWidget(void *thisObj);
// KDDockWidgets::Core::TabBar::stack() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__TabBar__stack(void *thisObj);
// KDDockWidgets::Core::TabBar::tabsAreMovable() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Core__TabBar__tabsAreMovable(void *thisObj);
// KDDockWidgets::Core::TabBar::text(int index) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Core__TabBar__text_int(void *thisObj, int index);
// KDDockWidgets::Core::TabBar::tr(const char * s, const char * c, int n)
KDDockWidgetsBindings_EXPORT void *c_static_KDDockWidgets__Core__TabBar__tr_char_char_int(const char *s, const char *c, int n);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__TabBar__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__TabBar__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Core__TabBar_Finalizer(void *cppObj);
}

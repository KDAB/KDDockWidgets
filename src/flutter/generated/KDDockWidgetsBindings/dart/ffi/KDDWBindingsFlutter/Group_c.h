/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <Group.h>
#include <core/Group.h>
#include <core/View.h>
#include <qsize.h>
#include <qrect.h>
#include <qstring.h>
#include <qpoint.h>

namespace KDDockWidgetsBindings_wrappersNS {
namespace KDDWBindingsFlutter {
class Group_wrapper : public ::KDDockWidgets::flutter::Group
{
public:
    ~Group_wrapper();
    Group_wrapper(KDDockWidgets::Core::Group *controller, KDDockWidgets::Core::View *parent = nullptr);
    virtual void activateWindow();
    virtual void activateWindow_nocallback();
    virtual bool close();
    virtual bool close_nocallback();
    virtual void createPlatformWindow();
    virtual void createPlatformWindow_nocallback();
    int currentIndex() const;
    virtual QRect dragRect() const;
    virtual QRect dragRect_nocallback() const;
    virtual Qt::WindowFlags flags() const;
    virtual Qt::WindowFlags flags_nocallback() const;
    virtual QRect geometry() const;
    virtual QRect geometry_nocallback() const;
    virtual void grabMouse();
    virtual void grabMouse_nocallback();
    virtual bool hasFocus() const;
    virtual bool hasFocus_nocallback() const;
    virtual void hide();
    virtual void hide_nocallback();
    virtual bool isActiveWindow() const;
    virtual bool isActiveWindow_nocallback() const;
    virtual bool isExplicitlyHidden() const;
    virtual bool isExplicitlyHidden_nocallback() const;
    virtual bool isMaximized() const;
    virtual bool isMaximized_nocallback() const;
    virtual bool isMinimized() const;
    virtual bool isMinimized_nocallback() const;
    virtual bool isMounted() const;
    virtual bool isMounted_nocallback() const;
    virtual bool isNull() const;
    virtual bool isNull_nocallback() const;
    virtual bool isRootView() const;
    virtual bool isRootView_nocallback() const;
    virtual bool isVisible() const;
    virtual bool isVisible_nocallback() const;
    virtual QPoint mapFromGlobal(QPoint globalPt) const;
    virtual QPoint mapFromGlobal_nocallback(QPoint globalPt) const;
    virtual QPoint mapTo(KDDockWidgets::Core::View *parent, QPoint pos) const;
    virtual QPoint mapTo_nocallback(KDDockWidgets::Core::View *parent, QPoint pos) const;
    virtual QPoint mapToGlobal(QPoint localPt) const;
    virtual QPoint mapToGlobal_nocallback(QPoint localPt) const;
    virtual QSize maxSizeHint() const;
    virtual QSize maxSizeHint_nocallback() const;
    virtual QSize minSize() const;
    virtual QSize minSize_nocallback() const;
    virtual void move(int x, int y);
    virtual void move_nocallback(int x, int y);
    virtual int nonContentsHeight() const;
    virtual int nonContentsHeight_nocallback() const;
    virtual QRect normalGeometry() const;
    virtual QRect normalGeometry_nocallback() const;
    virtual void onChildAdded(KDDockWidgets::Core::View *childView);
    virtual void onChildAdded_nocallback(KDDockWidgets::Core::View *childView);
    virtual void onChildRemoved(KDDockWidgets::Core::View *childView);
    virtual void onChildRemoved_nocallback(KDDockWidgets::Core::View *childView);
    virtual void onChildVisibilityChanged(KDDockWidgets::Core::View *childView);
    virtual void onChildVisibilityChanged_nocallback(KDDockWidgets::Core::View *childView);
    virtual void onGeometryChanged();
    virtual void onGeometryChanged_nocallback();
    virtual void onRebuildRequested();
    virtual void onRebuildRequested_nocallback();
    virtual bool onResize(int h, int w);
    virtual bool onResize_nocallback(int h, int w);
    virtual void raise();
    virtual void raise_nocallback();
    virtual void raiseAndActivate();
    virtual void raiseAndActivate_nocallback();
    virtual void raiseChild(KDDockWidgets::Core::View *childView);
    virtual void raiseChild_nocallback(KDDockWidgets::Core::View *childView);
    virtual void raiseWindow(KDDockWidgets::Core::View *rootView);
    virtual void raiseWindow_nocallback(KDDockWidgets::Core::View *rootView);
    virtual void releaseKeyboard();
    virtual void releaseKeyboard_nocallback();
    virtual void releaseMouse();
    virtual void releaseMouse_nocallback();
    virtual void setCursor(Qt::CursorShape shape);
    virtual void setCursor_nocallback(Qt::CursorShape shape);
    virtual void setFixedHeight(int h);
    virtual void setFixedHeight_nocallback(int h);
    virtual void setFixedWidth(int w);
    virtual void setFixedWidth_nocallback(int w);
    virtual void setGeometry(QRect geometry);
    virtual void setGeometry_nocallback(QRect geometry);
    virtual void setHeight(int h);
    virtual void setHeight_nocallback(int h);
    virtual void setMaximumSize(QSize sz);
    virtual void setMaximumSize_nocallback(QSize sz);
    virtual void setMinimumSize(QSize sz);
    virtual void setMinimumSize_nocallback(QSize sz);
    virtual void setMouseTracking(bool enable);
    virtual void setMouseTracking_nocallback(bool enable);
    virtual void setParent(KDDockWidgets::Core::View *parent);
    virtual void setParent_nocallback(KDDockWidgets::Core::View *parent);
    virtual void setSize(int w, int h);
    virtual void setSize_nocallback(int w, int h);
    virtual void setViewName(const QString &name);
    virtual void setViewName_nocallback(const QString &name);
    virtual void setVisible(bool visible);
    virtual void setVisible_nocallback(bool visible);
    virtual void setWidth(int w);
    virtual void setWidth_nocallback(int w);
    virtual void setWindowOpacity(double v);
    virtual void setWindowOpacity_nocallback(double v);
    virtual void setWindowTitle(const QString &title);
    virtual void setWindowTitle_nocallback(const QString &title);
    virtual void setZOrder(int z);
    virtual void setZOrder_nocallback(int z);
    virtual void show();
    virtual void show_nocallback();
    virtual void showMaximized();
    virtual void showMaximized_nocallback();
    virtual void showMinimized();
    virtual void showMinimized_nocallback();
    virtual void showNormal();
    virtual void showNormal_nocallback();
    virtual void update();
    virtual void update_nocallback();
    virtual QString viewName() const;
    virtual QString viewName_nocallback() const;
    typedef void (*Callback_activateWindow)(void *);
    Callback_activateWindow m_activateWindowCallback = nullptr;
    typedef bool (*Callback_close)(void *);
    Callback_close m_closeCallback = nullptr;
    typedef void (*Callback_createPlatformWindow)(void *);
    Callback_createPlatformWindow m_createPlatformWindowCallback = nullptr;
    typedef QRect *(*Callback_dragRect)(void *);
    Callback_dragRect m_dragRectCallback = nullptr;
    typedef Qt::WindowFlags (*Callback_flags)(void *);
    Callback_flags m_flagsCallback = nullptr;
    typedef QRect *(*Callback_geometry)(void *);
    Callback_geometry m_geometryCallback = nullptr;
    typedef void (*Callback_grabMouse)(void *);
    Callback_grabMouse m_grabMouseCallback = nullptr;
    typedef bool (*Callback_hasFocus)(void *);
    Callback_hasFocus m_hasFocusCallback = nullptr;
    typedef void (*Callback_hide)(void *);
    Callback_hide m_hideCallback = nullptr;
    typedef bool (*Callback_isActiveWindow)(void *);
    Callback_isActiveWindow m_isActiveWindowCallback = nullptr;
    typedef bool (*Callback_isExplicitlyHidden)(void *);
    Callback_isExplicitlyHidden m_isExplicitlyHiddenCallback = nullptr;
    typedef bool (*Callback_isMaximized)(void *);
    Callback_isMaximized m_isMaximizedCallback = nullptr;
    typedef bool (*Callback_isMinimized)(void *);
    Callback_isMinimized m_isMinimizedCallback = nullptr;
    typedef bool (*Callback_isMounted)(void *);
    Callback_isMounted m_isMountedCallback = nullptr;
    typedef bool (*Callback_isNull)(void *);
    Callback_isNull m_isNullCallback = nullptr;
    typedef bool (*Callback_isRootView)(void *);
    Callback_isRootView m_isRootViewCallback = nullptr;
    typedef bool (*Callback_isVisible)(void *);
    Callback_isVisible m_isVisibleCallback = nullptr;
    typedef QPoint *(*Callback_mapFromGlobal)(void *, QPoint *globalPt);
    Callback_mapFromGlobal m_mapFromGlobalCallback = nullptr;
    typedef QPoint *(*Callback_mapTo)(void *, KDDockWidgets::Core::View *parent, QPoint *pos);
    Callback_mapTo m_mapToCallback = nullptr;
    typedef QPoint *(*Callback_mapToGlobal)(void *, QPoint *localPt);
    Callback_mapToGlobal m_mapToGlobalCallback = nullptr;
    typedef QSize *(*Callback_maxSizeHint)(void *);
    Callback_maxSizeHint m_maxSizeHintCallback = nullptr;
    typedef QSize *(*Callback_minSize)(void *);
    Callback_minSize m_minSizeCallback = nullptr;
    typedef void (*Callback_move_2)(void *, int x, int y);
    Callback_move_2 m_move_2Callback = nullptr;
    typedef int (*Callback_nonContentsHeight)(void *);
    Callback_nonContentsHeight m_nonContentsHeightCallback = nullptr;
    typedef QRect *(*Callback_normalGeometry)(void *);
    Callback_normalGeometry m_normalGeometryCallback = nullptr;
    typedef void (*Callback_onChildAdded)(void *, KDDockWidgets::Core::View *childView);
    Callback_onChildAdded m_onChildAddedCallback = nullptr;
    typedef void (*Callback_onChildRemoved)(void *, KDDockWidgets::Core::View *childView);
    Callback_onChildRemoved m_onChildRemovedCallback = nullptr;
    typedef void (*Callback_onChildVisibilityChanged)(void *, KDDockWidgets::Core::View *childView);
    Callback_onChildVisibilityChanged m_onChildVisibilityChangedCallback = nullptr;
    typedef void (*Callback_onGeometryChanged)(void *);
    Callback_onGeometryChanged m_onGeometryChangedCallback = nullptr;
    typedef void (*Callback_onRebuildRequested)(void *);
    Callback_onRebuildRequested m_onRebuildRequestedCallback = nullptr;
    typedef bool (*Callback_onResize_2)(void *, int h, int w);
    Callback_onResize_2 m_onResize_2Callback = nullptr;
    typedef void (*Callback_raise)(void *);
    Callback_raise m_raiseCallback = nullptr;
    typedef void (*Callback_raiseAndActivate)(void *);
    Callback_raiseAndActivate m_raiseAndActivateCallback = nullptr;
    typedef void (*Callback_raiseChild)(void *, KDDockWidgets::Core::View *childView);
    Callback_raiseChild m_raiseChildCallback = nullptr;
    typedef void (*Callback_raiseWindow)(void *, KDDockWidgets::Core::View *rootView);
    Callback_raiseWindow m_raiseWindowCallback = nullptr;
    typedef void (*Callback_releaseKeyboard)(void *);
    Callback_releaseKeyboard m_releaseKeyboardCallback = nullptr;
    typedef void (*Callback_releaseMouse)(void *);
    Callback_releaseMouse m_releaseMouseCallback = nullptr;
    typedef void (*Callback_setCursor)(void *, Qt::CursorShape shape);
    Callback_setCursor m_setCursorCallback = nullptr;
    typedef void (*Callback_setFixedHeight)(void *, int h);
    Callback_setFixedHeight m_setFixedHeightCallback = nullptr;
    typedef void (*Callback_setFixedWidth)(void *, int w);
    Callback_setFixedWidth m_setFixedWidthCallback = nullptr;
    typedef void (*Callback_setGeometry)(void *, QRect *geometry);
    Callback_setGeometry m_setGeometryCallback = nullptr;
    typedef void (*Callback_setHeight)(void *, int h);
    Callback_setHeight m_setHeightCallback = nullptr;
    typedef void (*Callback_setMaximumSize)(void *, QSize *sz);
    Callback_setMaximumSize m_setMaximumSizeCallback = nullptr;
    typedef void (*Callback_setMinimumSize)(void *, QSize *sz);
    Callback_setMinimumSize m_setMinimumSizeCallback = nullptr;
    typedef void (*Callback_setMouseTracking)(void *, bool enable);
    Callback_setMouseTracking m_setMouseTrackingCallback = nullptr;
    typedef void (*Callback_setParent)(void *, KDDockWidgets::Core::View *parent);
    Callback_setParent m_setParentCallback = nullptr;
    typedef void (*Callback_setSize_2)(void *, int w, int h);
    Callback_setSize_2 m_setSize_2Callback = nullptr;
    typedef void (*Callback_setViewName)(void *, const QString &name);
    Callback_setViewName m_setViewNameCallback = nullptr;
    typedef void (*Callback_setVisible)(void *, bool visible);
    Callback_setVisible m_setVisibleCallback = nullptr;
    typedef void (*Callback_setWidth)(void *, int w);
    Callback_setWidth m_setWidthCallback = nullptr;
    typedef void (*Callback_setWindowOpacity)(void *, double v);
    Callback_setWindowOpacity m_setWindowOpacityCallback = nullptr;
    typedef void (*Callback_setWindowTitle)(void *, const QString &title);
    Callback_setWindowTitle m_setWindowTitleCallback = nullptr;
    typedef void (*Callback_setZOrder)(void *, int z);
    Callback_setZOrder m_setZOrderCallback = nullptr;
    typedef void (*Callback_show)(void *);
    Callback_show m_showCallback = nullptr;
    typedef void (*Callback_showMaximized)(void *);
    Callback_showMaximized m_showMaximizedCallback = nullptr;
    typedef void (*Callback_showMinimized)(void *);
    Callback_showMinimized m_showMinimizedCallback = nullptr;
    typedef void (*Callback_showNormal)(void *);
    Callback_showNormal m_showNormalCallback = nullptr;
    typedef void (*Callback_update)(void *);
    Callback_update m_updateCallback = nullptr;
    typedef QString *(*Callback_viewName)(void *);
    Callback_viewName m_viewNameCallback = nullptr;
};
}
}
extern "C" {
// KDDockWidgets::flutter::Group::Group(KDDockWidgets::Core::Group * controller, KDDockWidgets::Core::View * parent)
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__Group__constructor_Group_View(void *controller_, void *parent_);
// KDDockWidgets::flutter::Group::activateWindow()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__activateWindow(void *thisObj);
// KDDockWidgets::flutter::Group::close()
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__flutter__Group__close(void *thisObj);
// KDDockWidgets::flutter::Group::createPlatformWindow()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__createPlatformWindow(void *thisObj);
// KDDockWidgets::flutter::Group::currentIndex() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__flutter__Group__currentIndex(void *thisObj);
// KDDockWidgets::flutter::Group::dragRect() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__Group__dragRect(void *thisObj);
// KDDockWidgets::flutter::Group::flags() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__flutter__Group__flags(void *thisObj);
// KDDockWidgets::flutter::Group::geometry() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__Group__geometry(void *thisObj);
// KDDockWidgets::flutter::Group::grabMouse()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__grabMouse(void *thisObj);
// KDDockWidgets::flutter::Group::hasFocus() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__flutter__Group__hasFocus(void *thisObj);
// KDDockWidgets::flutter::Group::hide()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__hide(void *thisObj);
// KDDockWidgets::flutter::Group::isActiveWindow() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__flutter__Group__isActiveWindow(void *thisObj);
// KDDockWidgets::flutter::Group::isExplicitlyHidden() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__flutter__Group__isExplicitlyHidden(void *thisObj);
// KDDockWidgets::flutter::Group::isMaximized() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__flutter__Group__isMaximized(void *thisObj);
// KDDockWidgets::flutter::Group::isMinimized() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__flutter__Group__isMinimized(void *thisObj);
// KDDockWidgets::flutter::Group::isMounted() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__flutter__Group__isMounted(void *thisObj);
// KDDockWidgets::flutter::Group::isNull() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__flutter__Group__isNull(void *thisObj);
// KDDockWidgets::flutter::Group::isRootView() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__flutter__Group__isRootView(void *thisObj);
// KDDockWidgets::flutter::Group::isVisible() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__flutter__Group__isVisible(void *thisObj);
// KDDockWidgets::flutter::Group::mapFromGlobal(QPoint globalPt) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__Group__mapFromGlobal_QPoint(void *thisObj, void *globalPt_);
// KDDockWidgets::flutter::Group::mapTo(KDDockWidgets::Core::View * parent, QPoint pos) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__Group__mapTo_View_QPoint(void *thisObj, void *parent_, void *pos_);
// KDDockWidgets::flutter::Group::mapToGlobal(QPoint localPt) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__Group__mapToGlobal_QPoint(void *thisObj, void *localPt_);
// KDDockWidgets::flutter::Group::maxSizeHint() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__Group__maxSizeHint(void *thisObj);
// KDDockWidgets::flutter::Group::minSize() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__Group__minSize(void *thisObj);
// KDDockWidgets::flutter::Group::move(int x, int y)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__move_int_int(void *thisObj, int x, int y);
// KDDockWidgets::flutter::Group::nonContentsHeight() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__flutter__Group__nonContentsHeight(void *thisObj);
// KDDockWidgets::flutter::Group::normalGeometry() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__Group__normalGeometry(void *thisObj);
// KDDockWidgets::flutter::Group::onChildAdded(KDDockWidgets::Core::View * childView)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__onChildAdded_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::Group::onChildRemoved(KDDockWidgets::Core::View * childView)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__onChildRemoved_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::Group::onChildVisibilityChanged(KDDockWidgets::Core::View * childView)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__onChildVisibilityChanged_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::Group::onGeometryChanged()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__onGeometryChanged(void *thisObj);
// KDDockWidgets::flutter::Group::onRebuildRequested()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__onRebuildRequested(void *thisObj);
// KDDockWidgets::flutter::Group::onResize(int h, int w)
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__flutter__Group__onResize_int_int(void *thisObj, int h, int w);
// KDDockWidgets::flutter::Group::raise()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__raise(void *thisObj);
// KDDockWidgets::flutter::Group::raiseAndActivate()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__raiseAndActivate(void *thisObj);
// KDDockWidgets::flutter::Group::raiseChild(KDDockWidgets::Core::View * childView)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__raiseChild_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::Group::raiseWindow(KDDockWidgets::Core::View * rootView)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__raiseWindow_View(void *thisObj, void *rootView_);
// KDDockWidgets::flutter::Group::releaseKeyboard()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__releaseKeyboard(void *thisObj);
// KDDockWidgets::flutter::Group::releaseMouse()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__releaseMouse(void *thisObj);
// KDDockWidgets::flutter::Group::setCursor(Qt::CursorShape shape)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__setCursor_CursorShape(void *thisObj, int shape);
// KDDockWidgets::flutter::Group::setFixedHeight(int h)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__setFixedHeight_int(void *thisObj, int h);
// KDDockWidgets::flutter::Group::setFixedWidth(int w)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__setFixedWidth_int(void *thisObj, int w);
// KDDockWidgets::flutter::Group::setGeometry(QRect geometry)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__setGeometry_QRect(void *thisObj, void *geometry_);
// KDDockWidgets::flutter::Group::setHeight(int h)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__setHeight_int(void *thisObj, int h);
// KDDockWidgets::flutter::Group::setMaximumSize(QSize sz)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__setMaximumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::flutter::Group::setMinimumSize(QSize sz)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__setMinimumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::flutter::Group::setMouseTracking(bool enable)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__setMouseTracking_bool(void *thisObj, bool enable);
// KDDockWidgets::flutter::Group::setParent(KDDockWidgets::Core::View * parent)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__setParent_View(void *thisObj, void *parent_);
// KDDockWidgets::flutter::Group::setSize(int w, int h)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__setSize_int_int(void *thisObj, int w, int h);
// KDDockWidgets::flutter::Group::setViewName(const QString & name)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__setViewName_QString(void *thisObj, const char *name_);
// KDDockWidgets::flutter::Group::setVisible(bool visible)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__setVisible_bool(void *thisObj, bool visible);
// KDDockWidgets::flutter::Group::setWidth(int w)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__setWidth_int(void *thisObj, int w);
// KDDockWidgets::flutter::Group::setWindowOpacity(double v)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__setWindowOpacity_double(void *thisObj, double v);
// KDDockWidgets::flutter::Group::setWindowTitle(const QString & title)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__setWindowTitle_QString(void *thisObj, const char *title_);
// KDDockWidgets::flutter::Group::setZOrder(int z)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__setZOrder_int(void *thisObj, int z);
// KDDockWidgets::flutter::Group::show()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__show(void *thisObj);
// KDDockWidgets::flutter::Group::showMaximized()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__showMaximized(void *thisObj);
// KDDockWidgets::flutter::Group::showMinimized()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__showMinimized(void *thisObj);
// KDDockWidgets::flutter::Group::showNormal()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__showNormal(void *thisObj);
// KDDockWidgets::flutter::Group::update()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__update(void *thisObj);
// KDDockWidgets::flutter::Group::viewName() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__Group__viewName(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Group_Finalizer(void *cppObj);
}

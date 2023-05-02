/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <View.h>
#include <core/Controller.h>
#include <core/View.h>
#include <qsize.h>
#include <qrect.h>
#include <qpoint.h>
#include <qstring.h>
#include "core/TitleBar.h"
#include <core/Layout.h>
#include "core/Stack.h"
#include <FloatingWindow.h>
#include <DropArea.h>
#include <core/DockWidget.h>
#include <core/Group.h>
#include <MainWindow.h>
#include <TabBar.h>

namespace KDDockWidgetsBindings_wrappersNS {
namespace KDDWBindingsFlutter {
class View_wrapper : public ::KDDockWidgets::flutter::View
{
public:
    ~View_wrapper();
    View_wrapper(KDDockWidgets::Core::Controller *controller, KDDockWidgets::Core::ViewType type, KDDockWidgets::Core::View *arg__3, Qt::WindowFlags windowFlags = {});
    virtual void activateWindow();
    virtual void activateWindow_nocallback();
    virtual bool close();
    virtual bool close_nocallback();
    virtual void createPlatformWindow();
    virtual void createPlatformWindow_nocallback();
    virtual Qt::WindowFlags flags() const;
    virtual Qt::WindowFlags flags_nocallback() const;
    virtual void free_impl();
    virtual void free_impl_nocallback();
    virtual QRect geometry() const;
    virtual QRect geometry_nocallback() const;
    virtual void grabMouse();
    virtual void grabMouse_nocallback();
    virtual bool hasFocus() const;
    virtual bool hasFocus_nocallback() const;
    virtual void hide();
    virtual void hide_nocallback();
    virtual void init();
    virtual void init_nocallback();
    virtual bool isActiveWindow() const;
    virtual bool isActiveWindow_nocallback() const;
    virtual bool isMaximized() const;
    virtual bool isMaximized_nocallback() const;
    virtual bool isMinimized() const;
    virtual bool isMinimized_nocallback() const;
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
    virtual int minimumHeight() const;
    virtual int minimumHeight_nocallback() const;
    virtual int minimumWidth() const;
    virtual int minimumWidth_nocallback() const;
    virtual void move(int x, int y);
    virtual void move_nocallback(int x, int y);
    virtual QRect normalGeometry() const;
    virtual QRect normalGeometry_nocallback() const;
    virtual QString objectName() const;
    virtual QString objectName_nocallback() const;
    virtual void onChildAdded(KDDockWidgets::Core::View *childView);
    virtual void onChildAdded_nocallback(KDDockWidgets::Core::View *childView);
    virtual void onChildRemoved(KDDockWidgets::Core::View *childView);
    virtual void onChildRemoved_nocallback(KDDockWidgets::Core::View *childView);
    virtual bool onResize(int w, int h);
    virtual bool onResize_nocallback(int w, int h);
    bool parentIsVisible() const;
    virtual void raise();
    virtual void raise_nocallback();
    virtual void raiseAndActivate();
    virtual void raiseAndActivate_nocallback();
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
    void setNormalGeometry(QRect geo);
    virtual void setObjectName(const QString &name);
    virtual void setObjectName_nocallback(const QString &name);
    virtual void setParent(KDDockWidgets::Core::View *parent);
    virtual void setParent_nocallback(KDDockWidgets::Core::View *parent);
    virtual void setSize(int w, int h);
    virtual void setSize_nocallback(int w, int h);
    void setSizeHint(QSize arg__1);
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
    virtual QSize sizeHint() const;
    virtual QSize sizeHint_nocallback() const;
    virtual void update();
    virtual void update_nocallback();
    void updateGeometry();
    typedef void (*Callback_activateWindow)(void *);
    Callback_activateWindow m_activateWindowCallback = nullptr;
    typedef bool (*Callback_close)(void *);
    Callback_close m_closeCallback = nullptr;
    typedef void (*Callback_createPlatformWindow)(void *);
    Callback_createPlatformWindow m_createPlatformWindowCallback = nullptr;
    typedef Qt::WindowFlags (*Callback_flags)(void *);
    Callback_flags m_flagsCallback = nullptr;
    typedef void (*Callback_free_impl)(void *);
    Callback_free_impl m_free_implCallback = nullptr;
    typedef QRect *(*Callback_geometry)(void *);
    Callback_geometry m_geometryCallback = nullptr;
    typedef void (*Callback_grabMouse)(void *);
    Callback_grabMouse m_grabMouseCallback = nullptr;
    typedef bool (*Callback_hasFocus)(void *);
    Callback_hasFocus m_hasFocusCallback = nullptr;
    typedef void (*Callback_hide)(void *);
    Callback_hide m_hideCallback = nullptr;
    typedef void (*Callback_init)(void *);
    Callback_init m_initCallback = nullptr;
    typedef bool (*Callback_isActiveWindow)(void *);
    Callback_isActiveWindow m_isActiveWindowCallback = nullptr;
    typedef bool (*Callback_isMaximized)(void *);
    Callback_isMaximized m_isMaximizedCallback = nullptr;
    typedef bool (*Callback_isMinimized)(void *);
    Callback_isMinimized m_isMinimizedCallback = nullptr;
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
    typedef int (*Callback_minimumHeight)(void *);
    Callback_minimumHeight m_minimumHeightCallback = nullptr;
    typedef int (*Callback_minimumWidth)(void *);
    Callback_minimumWidth m_minimumWidthCallback = nullptr;
    typedef void (*Callback_move_2)(void *, int x, int y);
    Callback_move_2 m_move_2Callback = nullptr;
    typedef QRect *(*Callback_normalGeometry)(void *);
    Callback_normalGeometry m_normalGeometryCallback = nullptr;
    typedef QString *(*Callback_objectName)(void *);
    Callback_objectName m_objectNameCallback = nullptr;
    typedef void (*Callback_onChildAdded)(void *, KDDockWidgets::Core::View *childView);
    Callback_onChildAdded m_onChildAddedCallback = nullptr;
    typedef void (*Callback_onChildRemoved)(void *, KDDockWidgets::Core::View *childView);
    Callback_onChildRemoved m_onChildRemovedCallback = nullptr;
    typedef bool (*Callback_onResize_2)(void *, int w, int h);
    Callback_onResize_2 m_onResize_2Callback = nullptr;
    typedef void (*Callback_raise)(void *);
    Callback_raise m_raiseCallback = nullptr;
    typedef void (*Callback_raiseAndActivate)(void *);
    Callback_raiseAndActivate m_raiseAndActivateCallback = nullptr;
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
    typedef void (*Callback_setObjectName)(void *, const QString &name);
    Callback_setObjectName m_setObjectNameCallback = nullptr;
    typedef void (*Callback_setParent)(void *, KDDockWidgets::Core::View *parent);
    Callback_setParent m_setParentCallback = nullptr;
    typedef void (*Callback_setSize_2)(void *, int w, int h);
    Callback_setSize_2 m_setSize_2Callback = nullptr;
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
    typedef QSize *(*Callback_sizeHint)(void *);
    Callback_sizeHint m_sizeHintCallback = nullptr;
    typedef void (*Callback_update)(void *);
    Callback_update m_updateCallback = nullptr;
};
}
}
extern "C" {
// KDDockWidgets::flutter::View::View(KDDockWidgets::Core::Controller * controller, KDDockWidgets::Core::ViewType type, KDDockWidgets::Core::View * arg__3, Qt::WindowFlags windowFlags)
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__View__constructor_Controller_ViewType_View_WindowFlags(void *controller_, int type, void *arg__3_, int windowFlags);
// KDDockWidgets::flutter::View::activateWindow()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__activateWindow(void *thisObj);
// KDDockWidgets::flutter::View::close()
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__flutter__View__close(void *thisObj);
// KDDockWidgets::flutter::View::createPlatformWindow()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__createPlatformWindow(void *thisObj);
// KDDockWidgets::flutter::View::flags() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__flutter__View__flags(void *thisObj);
// KDDockWidgets::flutter::View::free_impl()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__free_impl(void *thisObj);
// KDDockWidgets::flutter::View::geometry() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__View__geometry(void *thisObj);
// KDDockWidgets::flutter::View::grabMouse()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__grabMouse(void *thisObj);
// KDDockWidgets::flutter::View::hasFocus() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__flutter__View__hasFocus(void *thisObj);
// KDDockWidgets::flutter::View::hide()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__hide(void *thisObj);
// KDDockWidgets::flutter::View::init()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__init(void *thisObj);
// KDDockWidgets::flutter::View::isActiveWindow() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__flutter__View__isActiveWindow(void *thisObj);
// KDDockWidgets::flutter::View::isMaximized() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__flutter__View__isMaximized(void *thisObj);
// KDDockWidgets::flutter::View::isMinimized() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__flutter__View__isMinimized(void *thisObj);
// KDDockWidgets::flutter::View::isNull() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__flutter__View__isNull(void *thisObj);
// KDDockWidgets::flutter::View::isRootView() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__flutter__View__isRootView(void *thisObj);
// KDDockWidgets::flutter::View::isVisible() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__flutter__View__isVisible(void *thisObj);
// KDDockWidgets::flutter::View::mapFromGlobal(QPoint globalPt) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__View__mapFromGlobal_QPoint(void *thisObj, void *globalPt_);
// KDDockWidgets::flutter::View::mapTo(KDDockWidgets::Core::View * parent, QPoint pos) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__View__mapTo_View_QPoint(void *thisObj, void *parent_, void *pos_);
// KDDockWidgets::flutter::View::mapToGlobal(QPoint localPt) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__View__mapToGlobal_QPoint(void *thisObj, void *localPt_);
// KDDockWidgets::flutter::View::maxSizeHint() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__View__maxSizeHint(void *thisObj);
// KDDockWidgets::flutter::View::minSize() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__View__minSize(void *thisObj);
// KDDockWidgets::flutter::View::minimumHeight() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__flutter__View__minimumHeight(void *thisObj);
// KDDockWidgets::flutter::View::minimumWidth() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__flutter__View__minimumWidth(void *thisObj);
// KDDockWidgets::flutter::View::move(int x, int y)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__move_int_int(void *thisObj, int x, int y);
// KDDockWidgets::flutter::View::normalGeometry() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__View__normalGeometry(void *thisObj);
// KDDockWidgets::flutter::View::objectName() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__View__objectName(void *thisObj);
// KDDockWidgets::flutter::View::onChildAdded(KDDockWidgets::Core::View * childView)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__onChildAdded_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::View::onChildRemoved(KDDockWidgets::Core::View * childView)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__onChildRemoved_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::View::onResize(int w, int h)
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__flutter__View__onResize_int_int(void *thisObj, int w, int h);
// KDDockWidgets::flutter::View::parentIsVisible() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__flutter__View__parentIsVisible(void *thisObj);
// KDDockWidgets::flutter::View::raise()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__raise(void *thisObj);
// KDDockWidgets::flutter::View::raiseAndActivate()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__raiseAndActivate(void *thisObj);
// KDDockWidgets::flutter::View::releaseKeyboard()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__releaseKeyboard(void *thisObj);
// KDDockWidgets::flutter::View::releaseMouse()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__releaseMouse(void *thisObj);
// KDDockWidgets::flutter::View::setCursor(Qt::CursorShape shape)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__setCursor_CursorShape(void *thisObj, int shape);
// KDDockWidgets::flutter::View::setFixedHeight(int h)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__setFixedHeight_int(void *thisObj, int h);
// KDDockWidgets::flutter::View::setFixedWidth(int w)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__setFixedWidth_int(void *thisObj, int w);
// KDDockWidgets::flutter::View::setGeometry(QRect geometry)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__setGeometry_QRect(void *thisObj, void *geometry_);
// KDDockWidgets::flutter::View::setHeight(int h)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__setHeight_int(void *thisObj, int h);
// KDDockWidgets::flutter::View::setMaximumSize(QSize sz)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__setMaximumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::flutter::View::setMinimumSize(QSize sz)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__setMinimumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::flutter::View::setMouseTracking(bool enable)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__setMouseTracking_bool(void *thisObj, bool enable);
// KDDockWidgets::flutter::View::setNormalGeometry(QRect geo)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__setNormalGeometry_QRect(void *thisObj, void *geo_);
// KDDockWidgets::flutter::View::setObjectName(const QString & name)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__setObjectName_QString(void *thisObj, const char *name_);
// KDDockWidgets::flutter::View::setParent(KDDockWidgets::Core::View * parent)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__setParent_View(void *thisObj, void *parent_);
// KDDockWidgets::flutter::View::setSize(int w, int h)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__setSize_int_int(void *thisObj, int w, int h);
// KDDockWidgets::flutter::View::setSizeHint(QSize arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__setSizeHint_QSize(void *thisObj, void *arg__1_);
// KDDockWidgets::flutter::View::setVisible(bool visible)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__setVisible_bool(void *thisObj, bool visible);
// KDDockWidgets::flutter::View::setWidth(int w)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__setWidth_int(void *thisObj, int w);
// KDDockWidgets::flutter::View::setWindowOpacity(double v)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__setWindowOpacity_double(void *thisObj, double v);
// KDDockWidgets::flutter::View::setWindowTitle(const QString & title)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__setWindowTitle_QString(void *thisObj, const char *title_);
// KDDockWidgets::flutter::View::setZOrder(int z)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__setZOrder_int(void *thisObj, int z);
// KDDockWidgets::flutter::View::show()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__show(void *thisObj);
// KDDockWidgets::flutter::View::showMaximized()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__showMaximized(void *thisObj);
// KDDockWidgets::flutter::View::showMinimized()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__showMinimized(void *thisObj);
// KDDockWidgets::flutter::View::showNormal()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__showNormal(void *thisObj);
// KDDockWidgets::flutter::View::sizeHint() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__View__sizeHint(void *thisObj);
// KDDockWidgets::flutter::View::update()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__update(void *thisObj);
// KDDockWidgets::flutter::View::updateGeometry()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__updateGeometry(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__View_Finalizer(void *, void *cppObj, void *);
}

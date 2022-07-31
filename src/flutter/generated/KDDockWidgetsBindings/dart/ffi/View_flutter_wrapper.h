/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// tag=1040
#include "KDDockWidgetsBindings_exports.h"
#include <View_flutter.h>
#include <Controller.h>
#include <View.h>
#include <qsize.h>
#include <qrect.h>
#include <qpoint.h>
#include <qstring.h>
#include <controllers/Layout.h>
#include <DropArea.h>

namespace KDDockWidgetsBindings_wrappersNS {
// tag=1017
class View_flutter_wrapper : public ::KDDockWidgets::Views::View_flutter
{
public:
    ~View_flutter_wrapper();
    // tag=1041
    View_flutter_wrapper(KDDockWidgets::Controller *controller, KDDockWidgets::Type type, KDDockWidgets::View *arg__3, Qt::WindowFlags windowFlags = {});
    // tag=1041
    virtual void activateWindow();
    // tag=1008
    virtual void activateWindow_nocallback();
    // tag=1041
    virtual bool close();
    // tag=1008
    virtual bool close_nocallback();
    // tag=1041
    virtual void createPlatformWindow();
    // tag=1008
    virtual void createPlatformWindow_nocallback();
    // tag=1041
    virtual Qt::WindowFlags flags() const;
    // tag=1008
    virtual Qt::WindowFlags flags_nocallback() const;
    // tag=1041
    virtual void free_impl();
    // tag=1008
    virtual void free_impl_nocallback();
    // tag=1041
    virtual QRect geometry() const;
    // tag=1008
    virtual QRect geometry_nocallback() const;
    // tag=1041
    virtual void grabMouse();
    // tag=1008
    virtual void grabMouse_nocallback();
    // tag=1041
    virtual bool hasFocus() const;
    // tag=1008
    virtual bool hasFocus_nocallback() const;
    // tag=1041
    virtual void hide();
    // tag=1008
    virtual void hide_nocallback();
    // tag=1041
    virtual void init();
    // tag=1008
    virtual void init_nocallback();
    // tag=1041
    virtual bool isActiveWindow() const;
    // tag=1008
    virtual bool isActiveWindow_nocallback() const;
    // tag=1041
    virtual bool isMaximized() const;
    // tag=1008
    virtual bool isMaximized_nocallback() const;
    // tag=1041
    virtual bool isMinimized() const;
    // tag=1008
    virtual bool isMinimized_nocallback() const;
    // tag=1041
    virtual bool isNull() const;
    // tag=1008
    virtual bool isNull_nocallback() const;
    // tag=1041
    virtual bool isRootView() const;
    // tag=1008
    virtual bool isRootView_nocallback() const;
    // tag=1041
    virtual bool isVisible() const;
    // tag=1008
    virtual bool isVisible_nocallback() const;
    // tag=1041
    virtual QPoint mapFromGlobal(QPoint globalPt) const;
    // tag=1008
    virtual QPoint mapFromGlobal_nocallback(QPoint globalPt) const;
    // tag=1041
    virtual QPoint mapTo(KDDockWidgets::View *parent, QPoint pos) const;
    // tag=1008
    virtual QPoint mapTo_nocallback(KDDockWidgets::View *parent, QPoint pos) const;
    // tag=1041
    virtual QPoint mapToGlobal(QPoint localPt) const;
    // tag=1008
    virtual QPoint mapToGlobal_nocallback(QPoint localPt) const;
    // tag=1041
    virtual QSize maxSizeHint() const;
    // tag=1008
    virtual QSize maxSizeHint_nocallback() const;
    // tag=1041
    virtual QSize maximumSize() const;
    // tag=1008
    virtual QSize maximumSize_nocallback() const;
    // tag=1041
    virtual QSize minSize() const;
    // tag=1008
    virtual QSize minSize_nocallback() const;
    // tag=1041
    virtual int minimumHeight() const;
    // tag=1008
    virtual int minimumHeight_nocallback() const;
    // tag=1041
    virtual int minimumWidth() const;
    // tag=1008
    virtual int minimumWidth_nocallback() const;
    // tag=1041
    virtual void move(int x, int y);
    // tag=1008
    virtual void move_nocallback(int x, int y);
    // tag=1041
    virtual QRect normalGeometry() const;
    // tag=1008
    virtual QRect normalGeometry_nocallback() const;
    // tag=1041
    virtual QString objectName() const;
    // tag=1008
    virtual QString objectName_nocallback() const;
    // tag=1041
    virtual bool onResize(QSize newSize);
    // tag=1008
    virtual bool onResize_nocallback(QSize newSize);
    // tag=1041
    virtual void raise();
    // tag=1008
    virtual void raise_nocallback();
    // tag=1041
    virtual void raiseAndActivate();
    // tag=1008
    virtual void raiseAndActivate_nocallback();
    // tag=1041
    virtual void releaseKeyboard();
    // tag=1008
    virtual void releaseKeyboard_nocallback();
    // tag=1041
    virtual void releaseMouse();
    // tag=1008
    virtual void releaseMouse_nocallback();
    // tag=1041
    virtual void setCursor(Qt::CursorShape shape);
    // tag=1008
    virtual void setCursor_nocallback(Qt::CursorShape shape);
    // tag=1041
    virtual void setFixedHeight(int h);
    // tag=1008
    virtual void setFixedHeight_nocallback(int h);
    // tag=1041
    virtual void setFixedWidth(int w);
    // tag=1008
    virtual void setFixedWidth_nocallback(int w);
    // tag=1041
    virtual void setGeometry(QRect arg__1);
    // tag=1008
    virtual void setGeometry_nocallback(QRect arg__1);
    // tag=1041
    virtual void setHeight(int h);
    // tag=1008
    virtual void setHeight_nocallback(int h);
    // tag=1041
    virtual void setMaximumSize(QSize sz);
    // tag=1008
    virtual void setMaximumSize_nocallback(QSize sz);
    // tag=1041
    virtual void setMinimumSize(QSize sz);
    // tag=1008
    virtual void setMinimumSize_nocallback(QSize sz);
    // tag=1041
    virtual void setMouseTracking(bool enable);
    // tag=1008
    virtual void setMouseTracking_nocallback(bool enable);
    // tag=1041
    void setNormalGeometry(QRect geo);
    // tag=1041
    virtual void setObjectName(const QString &name);
    // tag=1008
    virtual void setObjectName_nocallback(const QString &name);
    // tag=1041
    virtual void setParent(KDDockWidgets::View *parent);
    // tag=1008
    virtual void setParent_nocallback(KDDockWidgets::View *parent);
    // tag=1041
    virtual void setSize(int w, int h);
    // tag=1008
    virtual void setSize_nocallback(int w, int h);
    // tag=1041
    virtual void setVisible(bool visible);
    // tag=1008
    virtual void setVisible_nocallback(bool visible);
    // tag=1041
    virtual void setWidth(int w);
    // tag=1008
    virtual void setWidth_nocallback(int w);
    // tag=1041
    virtual void setWindowOpacity(double v);
    // tag=1008
    virtual void setWindowOpacity_nocallback(double v);
    // tag=1041
    virtual void setWindowTitle(const QString &title);
    // tag=1008
    virtual void setWindowTitle_nocallback(const QString &title);
    // tag=1041
    virtual void setZOrder(int arg__1);
    // tag=1008
    virtual void setZOrder_nocallback(int arg__1);
    // tag=1041
    virtual void show();
    // tag=1008
    virtual void show_nocallback();
    // tag=1041
    virtual void showMaximized();
    // tag=1008
    virtual void showMaximized_nocallback();
    // tag=1041
    virtual void showMinimized();
    // tag=1008
    virtual void showMinimized_nocallback();
    // tag=1041
    virtual void showNormal();
    // tag=1008
    virtual void showNormal_nocallback();
    // tag=1041
    virtual QSize sizeHint() const;
    // tag=1008
    virtual QSize sizeHint_nocallback() const;
    // tag=1041
    virtual void update();
    // tag=1008
    virtual void update_nocallback();
    // tag=1041
    void updateGeometry();
    // tag=1042
    typedef void (*Callback_activateWindow)(void *);
    Callback_activateWindow m_activateWindowCallback = nullptr;
    // tag=1042
    typedef bool (*Callback_close)(void *);
    Callback_close m_closeCallback = nullptr;
    // tag=1042
    typedef void (*Callback_createPlatformWindow)(void *);
    Callback_createPlatformWindow m_createPlatformWindowCallback = nullptr;
    // tag=1042
    typedef Qt::WindowFlags (*Callback_flags)(void *);
    Callback_flags m_flagsCallback = nullptr;
    // tag=1042
    typedef void (*Callback_free_impl)(void *);
    Callback_free_impl m_free_implCallback = nullptr;
    // tag=1042
    typedef QRect *(*Callback_geometry)(void *);
    Callback_geometry m_geometryCallback = nullptr;
    // tag=1042
    typedef void (*Callback_grabMouse)(void *);
    Callback_grabMouse m_grabMouseCallback = nullptr;
    // tag=1042
    typedef bool (*Callback_hasFocus)(void *);
    Callback_hasFocus m_hasFocusCallback = nullptr;
    // tag=1042
    typedef void (*Callback_hide)(void *);
    Callback_hide m_hideCallback = nullptr;
    // tag=1042
    typedef void (*Callback_init)(void *);
    Callback_init m_initCallback = nullptr;
    // tag=1042
    typedef bool (*Callback_isActiveWindow)(void *);
    Callback_isActiveWindow m_isActiveWindowCallback = nullptr;
    // tag=1042
    typedef bool (*Callback_isMaximized)(void *);
    Callback_isMaximized m_isMaximizedCallback = nullptr;
    // tag=1042
    typedef bool (*Callback_isMinimized)(void *);
    Callback_isMinimized m_isMinimizedCallback = nullptr;
    // tag=1042
    typedef bool (*Callback_isNull)(void *);
    Callback_isNull m_isNullCallback = nullptr;
    // tag=1042
    typedef bool (*Callback_isRootView)(void *);
    Callback_isRootView m_isRootViewCallback = nullptr;
    // tag=1042
    typedef bool (*Callback_isVisible)(void *);
    Callback_isVisible m_isVisibleCallback = nullptr;
    // tag=1042
    typedef QPoint *(*Callback_mapFromGlobal)(void *, QPoint globalPt);
    Callback_mapFromGlobal m_mapFromGlobalCallback = nullptr;
    // tag=1042
    typedef QPoint *(*Callback_mapTo)(void *, KDDockWidgets::View *parent, QPoint pos);
    Callback_mapTo m_mapToCallback = nullptr;
    // tag=1042
    typedef QPoint *(*Callback_mapToGlobal)(void *, QPoint localPt);
    Callback_mapToGlobal m_mapToGlobalCallback = nullptr;
    // tag=1042
    typedef QSize *(*Callback_maxSizeHint)(void *);
    Callback_maxSizeHint m_maxSizeHintCallback = nullptr;
    // tag=1042
    typedef QSize *(*Callback_maximumSize)(void *);
    Callback_maximumSize m_maximumSizeCallback = nullptr;
    // tag=1042
    typedef QSize *(*Callback_minSize)(void *);
    Callback_minSize m_minSizeCallback = nullptr;
    // tag=1042
    typedef int (*Callback_minimumHeight)(void *);
    Callback_minimumHeight m_minimumHeightCallback = nullptr;
    // tag=1042
    typedef int (*Callback_minimumWidth)(void *);
    Callback_minimumWidth m_minimumWidthCallback = nullptr;
    // tag=1042
    typedef void (*Callback_move_2)(void *, int x, int y);
    Callback_move_2 m_move_2Callback = nullptr;
    // tag=1042
    typedef QRect *(*Callback_normalGeometry)(void *);
    Callback_normalGeometry m_normalGeometryCallback = nullptr;
    // tag=1042
    typedef QString *(*Callback_objectName)(void *);
    Callback_objectName m_objectNameCallback = nullptr;
    // tag=1042
    typedef bool (*Callback_onResize)(void *, QSize newSize);
    Callback_onResize m_onResizeCallback = nullptr;
    // tag=1042
    typedef void (*Callback_raise)(void *);
    Callback_raise m_raiseCallback = nullptr;
    // tag=1042
    typedef void (*Callback_raiseAndActivate)(void *);
    Callback_raiseAndActivate m_raiseAndActivateCallback = nullptr;
    // tag=1042
    typedef void (*Callback_releaseKeyboard)(void *);
    Callback_releaseKeyboard m_releaseKeyboardCallback = nullptr;
    // tag=1042
    typedef void (*Callback_releaseMouse)(void *);
    Callback_releaseMouse m_releaseMouseCallback = nullptr;
    // tag=1042
    typedef void (*Callback_setCursor)(void *, Qt::CursorShape shape);
    Callback_setCursor m_setCursorCallback = nullptr;
    // tag=1042
    typedef void (*Callback_setFixedHeight)(void *, int h);
    Callback_setFixedHeight m_setFixedHeightCallback = nullptr;
    // tag=1042
    typedef void (*Callback_setFixedWidth)(void *, int w);
    Callback_setFixedWidth m_setFixedWidthCallback = nullptr;
    // tag=1042
    typedef void (*Callback_setGeometry)(void *, QRect arg__1);
    Callback_setGeometry m_setGeometryCallback = nullptr;
    // tag=1042
    typedef void (*Callback_setHeight)(void *, int h);
    Callback_setHeight m_setHeightCallback = nullptr;
    // tag=1042
    typedef void (*Callback_setMaximumSize)(void *, QSize sz);
    Callback_setMaximumSize m_setMaximumSizeCallback = nullptr;
    // tag=1042
    typedef void (*Callback_setMinimumSize)(void *, QSize sz);
    Callback_setMinimumSize m_setMinimumSizeCallback = nullptr;
    // tag=1042
    typedef void (*Callback_setMouseTracking)(void *, bool enable);
    Callback_setMouseTracking m_setMouseTrackingCallback = nullptr;
    // tag=1042
    typedef void (*Callback_setObjectName)(void *, const QString &name);
    Callback_setObjectName m_setObjectNameCallback = nullptr;
    // tag=1042
    typedef void (*Callback_setParent)(void *, KDDockWidgets::View *parent);
    Callback_setParent m_setParentCallback = nullptr;
    // tag=1042
    typedef void (*Callback_setSize_2)(void *, int w, int h);
    Callback_setSize_2 m_setSize_2Callback = nullptr;
    // tag=1042
    typedef void (*Callback_setVisible)(void *, bool visible);
    Callback_setVisible m_setVisibleCallback = nullptr;
    // tag=1042
    typedef void (*Callback_setWidth)(void *, int w);
    Callback_setWidth m_setWidthCallback = nullptr;
    // tag=1042
    typedef void (*Callback_setWindowOpacity)(void *, double v);
    Callback_setWindowOpacity m_setWindowOpacityCallback = nullptr;
    // tag=1042
    typedef void (*Callback_setWindowTitle)(void *, const QString &title);
    Callback_setWindowTitle m_setWindowTitleCallback = nullptr;
    // tag=1042
    typedef void (*Callback_setZOrder)(void *, int arg__1);
    Callback_setZOrder m_setZOrderCallback = nullptr;
    // tag=1042
    typedef void (*Callback_show)(void *);
    Callback_show m_showCallback = nullptr;
    // tag=1042
    typedef void (*Callback_showMaximized)(void *);
    Callback_showMaximized m_showMaximizedCallback = nullptr;
    // tag=1042
    typedef void (*Callback_showMinimized)(void *);
    Callback_showMinimized m_showMinimizedCallback = nullptr;
    // tag=1042
    typedef void (*Callback_showNormal)(void *);
    Callback_showNormal m_showNormalCallback = nullptr;
    // tag=1042
    typedef QSize *(*Callback_sizeHint)(void *);
    Callback_sizeHint m_sizeHintCallback = nullptr;
    // tag=1042
    typedef void (*Callback_update)(void *);
    Callback_update m_updateCallback = nullptr;
};
}
extern "C" {

// tag=1067
//  KDDockWidgets::Views::View_flutter::View_flutter(KDDockWidgets::Controller * controller, KDDockWidgets::Type type, KDDockWidgets::View * arg__3, Qt::WindowFlags windowFlags)
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Views__View_flutter__constructor_Controller_Type_View_WindowFlags(void *controller_, int type, void *arg__3_, int windowFlags);

// tag=1067
//  KDDockWidgets::Views::View_flutter::activateWindow()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__activateWindow(void *thisObj);

// tag=1067
//  KDDockWidgets::Views::View_flutter::close()
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Views__View_flutter__close(void *thisObj);

// tag=1067
//  KDDockWidgets::Views::View_flutter::createPlatformWindow()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__createPlatformWindow(void *thisObj);

// tag=1067
//  KDDockWidgets::Views::View_flutter::flags() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Views__View_flutter__flags(void *thisObj);

// tag=1067
//  KDDockWidgets::Views::View_flutter::free_impl()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__free_impl(void *thisObj);

// tag=1067
//  KDDockWidgets::Views::View_flutter::geometry() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Views__View_flutter__geometry(void *thisObj);

// tag=1067
//  KDDockWidgets::Views::View_flutter::grabMouse()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__grabMouse(void *thisObj);

// tag=1067
//  KDDockWidgets::Views::View_flutter::hasFocus() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Views__View_flutter__hasFocus(void *thisObj);

// tag=1067
//  KDDockWidgets::Views::View_flutter::hide()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__hide(void *thisObj);

// tag=1067
//  KDDockWidgets::Views::View_flutter::init()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__init(void *thisObj);

// tag=1067
//  KDDockWidgets::Views::View_flutter::isActiveWindow() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Views__View_flutter__isActiveWindow(void *thisObj);

// tag=1067
//  KDDockWidgets::Views::View_flutter::isMaximized() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Views__View_flutter__isMaximized(void *thisObj);

// tag=1067
//  KDDockWidgets::Views::View_flutter::isMinimized() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Views__View_flutter__isMinimized(void *thisObj);

// tag=1067
//  KDDockWidgets::Views::View_flutter::isNull() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Views__View_flutter__isNull(void *thisObj);

// tag=1067
//  KDDockWidgets::Views::View_flutter::isRootView() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Views__View_flutter__isRootView(void *thisObj);

// tag=1067
//  KDDockWidgets::Views::View_flutter::isVisible() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Views__View_flutter__isVisible(void *thisObj);

// tag=1067
//  KDDockWidgets::Views::View_flutter::mapFromGlobal(QPoint globalPt) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Views__View_flutter__mapFromGlobal_QPoint(void *thisObj, void *globalPt_);

// tag=1067
//  KDDockWidgets::Views::View_flutter::mapTo(KDDockWidgets::View * parent, QPoint pos) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Views__View_flutter__mapTo_View_QPoint(void *thisObj, void *parent_, void *pos_);

// tag=1067
//  KDDockWidgets::Views::View_flutter::mapToGlobal(QPoint localPt) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Views__View_flutter__mapToGlobal_QPoint(void *thisObj, void *localPt_);

// tag=1067
//  KDDockWidgets::Views::View_flutter::maxSizeHint() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Views__View_flutter__maxSizeHint(void *thisObj);

// tag=1067
//  KDDockWidgets::Views::View_flutter::maximumSize() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Views__View_flutter__maximumSize(void *thisObj);

// tag=1067
//  KDDockWidgets::Views::View_flutter::minSize() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Views__View_flutter__minSize(void *thisObj);

// tag=1067
//  KDDockWidgets::Views::View_flutter::minimumHeight() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Views__View_flutter__minimumHeight(void *thisObj);

// tag=1067
//  KDDockWidgets::Views::View_flutter::minimumWidth() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Views__View_flutter__minimumWidth(void *thisObj);

// tag=1067
//  KDDockWidgets::Views::View_flutter::move(int x, int y)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__move_int_int(void *thisObj, int x, int y);

// tag=1067
//  KDDockWidgets::Views::View_flutter::normalGeometry() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Views__View_flutter__normalGeometry(void *thisObj);

// tag=1067
//  KDDockWidgets::Views::View_flutter::objectName() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Views__View_flutter__objectName(void *thisObj);

// tag=1067
//  KDDockWidgets::Views::View_flutter::onResize(QSize newSize)
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Views__View_flutter__onResize_QSize(void *thisObj, void *newSize_);

// tag=1067
//  KDDockWidgets::Views::View_flutter::raise()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__raise(void *thisObj);

// tag=1067
//  KDDockWidgets::Views::View_flutter::raiseAndActivate()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__raiseAndActivate(void *thisObj);

// tag=1067
//  KDDockWidgets::Views::View_flutter::releaseKeyboard()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__releaseKeyboard(void *thisObj);

// tag=1067
//  KDDockWidgets::Views::View_flutter::releaseMouse()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__releaseMouse(void *thisObj);

// tag=1067
//  KDDockWidgets::Views::View_flutter::setCursor(Qt::CursorShape shape)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__setCursor_CursorShape(void *thisObj, int shape);

// tag=1067
//  KDDockWidgets::Views::View_flutter::setFixedHeight(int h)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__setFixedHeight_int(void *thisObj, int h);

// tag=1067
//  KDDockWidgets::Views::View_flutter::setFixedWidth(int w)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__setFixedWidth_int(void *thisObj, int w);

// tag=1067
//  KDDockWidgets::Views::View_flutter::setGeometry(QRect arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__setGeometry_QRect(void *thisObj, void *arg__1_);

// tag=1067
//  KDDockWidgets::Views::View_flutter::setHeight(int h)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__setHeight_int(void *thisObj, int h);

// tag=1067
//  KDDockWidgets::Views::View_flutter::setMaximumSize(QSize sz)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__setMaximumSize_QSize(void *thisObj, void *sz_);

// tag=1067
//  KDDockWidgets::Views::View_flutter::setMinimumSize(QSize sz)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__setMinimumSize_QSize(void *thisObj, void *sz_);

// tag=1067
//  KDDockWidgets::Views::View_flutter::setMouseTracking(bool enable)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__setMouseTracking_bool(void *thisObj, bool enable);

// tag=1067
//  KDDockWidgets::Views::View_flutter::setNormalGeometry(QRect geo)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__setNormalGeometry_QRect(void *thisObj, void *geo_);

// tag=1067
//  KDDockWidgets::Views::View_flutter::setObjectName(const QString & name)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__setObjectName_QString(void *thisObj, const char *name_);

// tag=1067
//  KDDockWidgets::Views::View_flutter::setParent(KDDockWidgets::View * parent)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__setParent_View(void *thisObj, void *parent_);

// tag=1067
//  KDDockWidgets::Views::View_flutter::setSize(int w, int h)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__setSize_int_int(void *thisObj, int w, int h);

// tag=1067
//  KDDockWidgets::Views::View_flutter::setVisible(bool visible)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__setVisible_bool(void *thisObj, bool visible);

// tag=1067
//  KDDockWidgets::Views::View_flutter::setWidth(int w)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__setWidth_int(void *thisObj, int w);

// tag=1067
//  KDDockWidgets::Views::View_flutter::setWindowOpacity(double v)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__setWindowOpacity_double(void *thisObj, double v);

// tag=1067
//  KDDockWidgets::Views::View_flutter::setWindowTitle(const QString & title)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__setWindowTitle_QString(void *thisObj, const char *title_);

// tag=1067
//  KDDockWidgets::Views::View_flutter::setZOrder(int arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__setZOrder_int(void *thisObj, int arg__1);

// tag=1067
//  KDDockWidgets::Views::View_flutter::show()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__show(void *thisObj);

// tag=1067
//  KDDockWidgets::Views::View_flutter::showMaximized()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__showMaximized(void *thisObj);

// tag=1067
//  KDDockWidgets::Views::View_flutter::showMinimized()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__showMinimized(void *thisObj);

// tag=1067
//  KDDockWidgets::Views::View_flutter::showNormal()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__showNormal(void *thisObj);

// tag=1067
//  KDDockWidgets::Views::View_flutter::sizeHint() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Views__View_flutter__sizeHint(void *thisObj);

// tag=1067
//  KDDockWidgets::Views::View_flutter::update()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__update(void *thisObj);

// tag=1067
//  KDDockWidgets::Views::View_flutter::updateGeometry()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__updateGeometry(void *thisObj);

// tag=1066
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__destructor(void *thisObj);

// tag=1046
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
// tag=1047
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__View_flutter_Finalizer(void *, void *cppObj, void *);
}

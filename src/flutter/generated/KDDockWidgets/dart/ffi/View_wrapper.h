/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// tag=1040
#include "KDDockWidgets_exports.h"
#include <View.h>
#include <qsize.h>
#include <qrect.h>
#include <qpoint.h>
#include <qstring.h>

namespace KDDockWidgets_wrappersNS {
// tag=1017
class View_wrapper : public ::KDDockWidgets::View
{
public:
    ~View_wrapper();
    // tag=1041
    bool aboutToBeDestroyed() const;
    // tag=1041
    virtual void activateWindow();
    // tag=1008
    virtual void activateWindow_nocallback();
    // tag=1041
    static QSize boundedMaxSize(QSize min, QSize max);
    // tag=1041
    virtual bool close();
    // tag=1008
    virtual bool close_nocallback();
    // tag=1041
    void closeRootView();
    // tag=1041
    virtual void createPlatformWindow();
    // tag=1008
    virtual void createPlatformWindow_nocallback();
    // tag=1041
    static bool equals(const KDDockWidgets::View *one, const KDDockWidgets::View *two);
    // tag=1041
    bool equals(const KDDockWidgets::View *other) const;
    // tag=1041
    void free();
    // tag=1041
    virtual void free_impl();
    // tag=1008
    virtual void free_impl_nocallback();
    // tag=1041
    bool freed() const;
    // tag=1041
    virtual QRect geometry() const;
    // tag=1008
    virtual QRect geometry_nocallback() const;
    // tag=1041
    QRect globalGeometry() const;
    // tag=1041
    virtual void grabMouse();
    // tag=1008
    virtual void grabMouse_nocallback();
    // tag=1041
    static QSize hardcodedMinimumSize();
    // tag=1041
    virtual bool hasFocus() const;
    // tag=1008
    virtual bool hasFocus_nocallback() const;
    // tag=1041
    int height() const;
    // tag=1041
    virtual void hide();
    // tag=1008
    virtual void hide_nocallback();
    // tag=1041
    QString id() const;
    // tag=1041
    bool inDtor() const;
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
    virtual QPoint mapFromGlobal(QPoint arg__1) const;
    // tag=1008
    virtual QPoint mapFromGlobal_nocallback(QPoint arg__1) const;
    // tag=1041
    virtual QPoint mapTo(KDDockWidgets::View *arg__1, QPoint arg__2) const;
    // tag=1008
    virtual QPoint mapTo_nocallback(KDDockWidgets::View *arg__1, QPoint arg__2) const;
    // tag=1041
    virtual QPoint mapToGlobal(QPoint arg__1) const;
    // tag=1008
    virtual QPoint mapToGlobal_nocallback(QPoint arg__1) const;
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
    void move(QPoint arg__1);
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
    QSize parentSize() const;
    // tag=1041
    QPoint pos() const;
    // tag=1041
    virtual void raise();
    // tag=1008
    virtual void raise_nocallback();
    // tag=1041
    virtual void raiseAndActivate();
    // tag=1008
    virtual void raiseAndActivate_nocallback();
    // tag=1041
    QRect rect() const;
    // tag=1041
    virtual void releaseKeyboard();
    // tag=1008
    virtual void releaseKeyboard_nocallback();
    // tag=1041
    virtual void releaseMouse();
    // tag=1008
    virtual void releaseMouse_nocallback();
    // tag=1041
    void resize(QSize arg__1);
    // tag=1041
    void resize(int w, int h);
    // tag=1041
    void setAboutToBeDestroyed();
    // tag=1041
    virtual void setFixedHeight(int arg__1);
    // tag=1008
    virtual void setFixedHeight_nocallback(int arg__1);
    // tag=1041
    virtual void setFixedWidth(int arg__1);
    // tag=1008
    virtual void setFixedWidth_nocallback(int arg__1);
    // tag=1041
    virtual void setGeometry(QRect arg__1);
    // tag=1008
    virtual void setGeometry_nocallback(QRect arg__1);
    // tag=1041
    virtual void setHeight(int height);
    // tag=1008
    virtual void setHeight_nocallback(int height);
    // tag=1041
    virtual void setMaximumSize(QSize sz);
    // tag=1008
    virtual void setMaximumSize_nocallback(QSize sz);
    // tag=1041
    virtual void setMinimumSize(QSize arg__1);
    // tag=1008
    virtual void setMinimumSize_nocallback(QSize arg__1);
    // tag=1041
    virtual void setMouseTracking(bool arg__1);
    // tag=1008
    virtual void setMouseTracking_nocallback(bool arg__1);
    // tag=1041
    virtual void setObjectName(const QString &arg__1);
    // tag=1008
    virtual void setObjectName_nocallback(const QString &arg__1);
    // tag=1041
    virtual void setParent(KDDockWidgets::View *arg__1);
    // tag=1008
    virtual void setParent_nocallback(KDDockWidgets::View *arg__1);
    // tag=1041
    void setSize(QSize arg__1);
    // tag=1041
    virtual void setSize(int width, int height);
    // tag=1008
    virtual void setSize_nocallback(int width, int height);
    // tag=1041
    virtual void setVisible(bool arg__1);
    // tag=1008
    virtual void setVisible_nocallback(bool arg__1);
    // tag=1041
    virtual void setWidth(int width);
    // tag=1008
    virtual void setWidth_nocallback(int width);
    // tag=1041
    virtual void setWindowOpacity(double arg__1);
    // tag=1008
    virtual void setWindowOpacity_nocallback(double arg__1);
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
    QSize size() const;
    // tag=1041
    virtual QSize sizeHint() const;
    // tag=1008
    virtual QSize sizeHint_nocallback() const;
    // tag=1041
    virtual void update();
    // tag=1008
    virtual void update_nocallback();
    // tag=1041
    int width() const;
    // tag=1041
    QRect windowGeometry() const;
    // tag=1041
    int x() const;
    // tag=1041
    int y() const;
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
    typedef QPoint *(*Callback_mapFromGlobal)(void *, QPoint arg__1);
    Callback_mapFromGlobal m_mapFromGlobalCallback = nullptr;
    // tag=1042
    typedef QPoint *(*Callback_mapTo)(void *, KDDockWidgets::View *arg__1, QPoint arg__2);
    Callback_mapTo m_mapToCallback = nullptr;
    // tag=1042
    typedef QPoint *(*Callback_mapToGlobal)(void *, QPoint arg__1);
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
    typedef void (*Callback_setFixedHeight)(void *, int arg__1);
    Callback_setFixedHeight m_setFixedHeightCallback = nullptr;
    // tag=1042
    typedef void (*Callback_setFixedWidth)(void *, int arg__1);
    Callback_setFixedWidth m_setFixedWidthCallback = nullptr;
    // tag=1042
    typedef void (*Callback_setGeometry)(void *, QRect arg__1);
    Callback_setGeometry m_setGeometryCallback = nullptr;
    // tag=1042
    typedef void (*Callback_setHeight)(void *, int height);
    Callback_setHeight m_setHeightCallback = nullptr;
    // tag=1042
    typedef void (*Callback_setMaximumSize)(void *, QSize sz);
    Callback_setMaximumSize m_setMaximumSizeCallback = nullptr;
    // tag=1042
    typedef void (*Callback_setMinimumSize)(void *, QSize arg__1);
    Callback_setMinimumSize m_setMinimumSizeCallback = nullptr;
    // tag=1042
    typedef void (*Callback_setMouseTracking)(void *, bool arg__1);
    Callback_setMouseTracking m_setMouseTrackingCallback = nullptr;
    // tag=1042
    typedef void (*Callback_setObjectName)(void *, const QString &arg__1);
    Callback_setObjectName m_setObjectNameCallback = nullptr;
    // tag=1042
    typedef void (*Callback_setParent)(void *, KDDockWidgets::View *arg__1);
    Callback_setParent m_setParentCallback = nullptr;
    // tag=1042
    typedef void (*Callback_setSize_2)(void *, int width, int height);
    Callback_setSize_2 m_setSize_2Callback = nullptr;
    // tag=1042
    typedef void (*Callback_setVisible)(void *, bool arg__1);
    Callback_setVisible m_setVisibleCallback = nullptr;
    // tag=1042
    typedef void (*Callback_setWidth)(void *, int width);
    Callback_setWidth m_setWidthCallback = nullptr;
    // tag=1042
    typedef void (*Callback_setWindowOpacity)(void *, double arg__1);
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
//  KDDockWidgets::View::aboutToBeDestroyed() const
KDDockWidgets_EXPORT bool c_KDDockWidgets__View__aboutToBeDestroyed(void *thisObj);

// tag=1067
//  KDDockWidgets::View::activateWindow()
KDDockWidgets_EXPORT void c_KDDockWidgets__View__activateWindow(void *thisObj);

// tag=1067
//  KDDockWidgets::View::boundedMaxSize(QSize min, QSize max)
KDDockWidgets_EXPORT void *c_static_KDDockWidgets__View__boundedMaxSize_QSize_QSize(void *min_, void *max_);

// tag=1067
//  KDDockWidgets::View::close()
KDDockWidgets_EXPORT bool c_KDDockWidgets__View__close(void *thisObj);

// tag=1067
//  KDDockWidgets::View::closeRootView()
KDDockWidgets_EXPORT void c_KDDockWidgets__View__closeRootView(void *thisObj);

// tag=1067
//  KDDockWidgets::View::createPlatformWindow()
KDDockWidgets_EXPORT void c_KDDockWidgets__View__createPlatformWindow(void *thisObj);

// tag=1067
//  KDDockWidgets::View::equals(const KDDockWidgets::View * one, const KDDockWidgets::View * two)
KDDockWidgets_EXPORT bool c_static_KDDockWidgets__View__equals_View_View(void *one_, void *two_);

// tag=1067
//  KDDockWidgets::View::equals(const KDDockWidgets::View * other) const
KDDockWidgets_EXPORT bool c_KDDockWidgets__View__equals_View(void *thisObj, void *other_);

// tag=1067
//  KDDockWidgets::View::free()
KDDockWidgets_EXPORT void c_KDDockWidgets__View__free(void *thisObj);

// tag=1067
//  KDDockWidgets::View::free_impl()
KDDockWidgets_EXPORT void c_KDDockWidgets__View__free_impl(void *thisObj);

// tag=1067
//  KDDockWidgets::View::freed() const
KDDockWidgets_EXPORT bool c_KDDockWidgets__View__freed(void *thisObj);

// tag=1067
//  KDDockWidgets::View::geometry() const
KDDockWidgets_EXPORT void *c_KDDockWidgets__View__geometry(void *thisObj);

// tag=1067
//  KDDockWidgets::View::globalGeometry() const
KDDockWidgets_EXPORT void *c_KDDockWidgets__View__globalGeometry(void *thisObj);

// tag=1067
//  KDDockWidgets::View::grabMouse()
KDDockWidgets_EXPORT void c_KDDockWidgets__View__grabMouse(void *thisObj);

// tag=1067
//  KDDockWidgets::View::hardcodedMinimumSize()
KDDockWidgets_EXPORT void *c_static_KDDockWidgets__View__hardcodedMinimumSize();

// tag=1067
//  KDDockWidgets::View::hasFocus() const
KDDockWidgets_EXPORT bool c_KDDockWidgets__View__hasFocus(void *thisObj);

// tag=1067
//  KDDockWidgets::View::height() const
KDDockWidgets_EXPORT int c_KDDockWidgets__View__height(void *thisObj);

// tag=1067
//  KDDockWidgets::View::hide()
KDDockWidgets_EXPORT void c_KDDockWidgets__View__hide(void *thisObj);

// tag=1067
//  KDDockWidgets::View::id() const
KDDockWidgets_EXPORT void *c_KDDockWidgets__View__id(void *thisObj);

// tag=1067
//  KDDockWidgets::View::inDtor() const
KDDockWidgets_EXPORT bool c_KDDockWidgets__View__inDtor(void *thisObj);

// tag=1067
//  KDDockWidgets::View::init()
KDDockWidgets_EXPORT void c_KDDockWidgets__View__init(void *thisObj);

// tag=1067
//  KDDockWidgets::View::isActiveWindow() const
KDDockWidgets_EXPORT bool c_KDDockWidgets__View__isActiveWindow(void *thisObj);

// tag=1067
//  KDDockWidgets::View::isMaximized() const
KDDockWidgets_EXPORT bool c_KDDockWidgets__View__isMaximized(void *thisObj);

// tag=1067
//  KDDockWidgets::View::isMinimized() const
KDDockWidgets_EXPORT bool c_KDDockWidgets__View__isMinimized(void *thisObj);

// tag=1067
//  KDDockWidgets::View::isNull() const
KDDockWidgets_EXPORT bool c_KDDockWidgets__View__isNull(void *thisObj);

// tag=1067
//  KDDockWidgets::View::isRootView() const
KDDockWidgets_EXPORT bool c_KDDockWidgets__View__isRootView(void *thisObj);

// tag=1067
//  KDDockWidgets::View::isVisible() const
KDDockWidgets_EXPORT bool c_KDDockWidgets__View__isVisible(void *thisObj);

// tag=1067
//  KDDockWidgets::View::mapFromGlobal(QPoint arg__1) const
KDDockWidgets_EXPORT void *c_KDDockWidgets__View__mapFromGlobal_QPoint(void *thisObj, void *arg__1_);

// tag=1067
//  KDDockWidgets::View::mapTo(KDDockWidgets::View * arg__1, QPoint arg__2) const
KDDockWidgets_EXPORT void *c_KDDockWidgets__View__mapTo_View_QPoint(void *thisObj, void *arg__1_, void *arg__2_);

// tag=1067
//  KDDockWidgets::View::mapToGlobal(QPoint arg__1) const
KDDockWidgets_EXPORT void *c_KDDockWidgets__View__mapToGlobal_QPoint(void *thisObj, void *arg__1_);

// tag=1067
//  KDDockWidgets::View::maxSizeHint() const
KDDockWidgets_EXPORT void *c_KDDockWidgets__View__maxSizeHint(void *thisObj);

// tag=1067
//  KDDockWidgets::View::maximumSize() const
KDDockWidgets_EXPORT void *c_KDDockWidgets__View__maximumSize(void *thisObj);

// tag=1067
//  KDDockWidgets::View::minSize() const
KDDockWidgets_EXPORT void *c_KDDockWidgets__View__minSize(void *thisObj);

// tag=1067
//  KDDockWidgets::View::minimumHeight() const
KDDockWidgets_EXPORT int c_KDDockWidgets__View__minimumHeight(void *thisObj);

// tag=1067
//  KDDockWidgets::View::minimumWidth() const
KDDockWidgets_EXPORT int c_KDDockWidgets__View__minimumWidth(void *thisObj);

// tag=1067
//  KDDockWidgets::View::move(QPoint arg__1)
KDDockWidgets_EXPORT void c_KDDockWidgets__View__move_QPoint(void *thisObj, void *arg__1_);

// tag=1067
//  KDDockWidgets::View::move(int x, int y)
KDDockWidgets_EXPORT void c_KDDockWidgets__View__move_int_int(void *thisObj, int x, int y);

// tag=1067
//  KDDockWidgets::View::normalGeometry() const
KDDockWidgets_EXPORT void *c_KDDockWidgets__View__normalGeometry(void *thisObj);

// tag=1067
//  KDDockWidgets::View::objectName() const
KDDockWidgets_EXPORT void *c_KDDockWidgets__View__objectName(void *thisObj);

// tag=1067
//  KDDockWidgets::View::onResize(QSize newSize)
KDDockWidgets_EXPORT bool c_KDDockWidgets__View__onResize_QSize(void *thisObj, void *newSize_);

// tag=1067
//  KDDockWidgets::View::parentSize() const
KDDockWidgets_EXPORT void *c_KDDockWidgets__View__parentSize(void *thisObj);

// tag=1067
//  KDDockWidgets::View::pos() const
KDDockWidgets_EXPORT void *c_KDDockWidgets__View__pos(void *thisObj);

// tag=1067
//  KDDockWidgets::View::raise()
KDDockWidgets_EXPORT void c_KDDockWidgets__View__raise(void *thisObj);

// tag=1067
//  KDDockWidgets::View::raiseAndActivate()
KDDockWidgets_EXPORT void c_KDDockWidgets__View__raiseAndActivate(void *thisObj);

// tag=1067
//  KDDockWidgets::View::rect() const
KDDockWidgets_EXPORT void *c_KDDockWidgets__View__rect(void *thisObj);

// tag=1067
//  KDDockWidgets::View::releaseKeyboard()
KDDockWidgets_EXPORT void c_KDDockWidgets__View__releaseKeyboard(void *thisObj);

// tag=1067
//  KDDockWidgets::View::releaseMouse()
KDDockWidgets_EXPORT void c_KDDockWidgets__View__releaseMouse(void *thisObj);

// tag=1067
//  KDDockWidgets::View::resize(QSize arg__1)
KDDockWidgets_EXPORT void c_KDDockWidgets__View__resize_QSize(void *thisObj, void *arg__1_);

// tag=1067
//  KDDockWidgets::View::resize(int w, int h)
KDDockWidgets_EXPORT void c_KDDockWidgets__View__resize_int_int(void *thisObj, int w, int h);

// tag=1067
//  KDDockWidgets::View::setAboutToBeDestroyed()
KDDockWidgets_EXPORT void c_KDDockWidgets__View__setAboutToBeDestroyed(void *thisObj);

// tag=1067
//  KDDockWidgets::View::setFixedHeight(int arg__1)
KDDockWidgets_EXPORT void c_KDDockWidgets__View__setFixedHeight_int(void *thisObj, int arg__1);

// tag=1067
//  KDDockWidgets::View::setFixedWidth(int arg__1)
KDDockWidgets_EXPORT void c_KDDockWidgets__View__setFixedWidth_int(void *thisObj, int arg__1);

// tag=1067
//  KDDockWidgets::View::setGeometry(QRect arg__1)
KDDockWidgets_EXPORT void c_KDDockWidgets__View__setGeometry_QRect(void *thisObj, void *arg__1_);

// tag=1067
//  KDDockWidgets::View::setHeight(int height)
KDDockWidgets_EXPORT void c_KDDockWidgets__View__setHeight_int(void *thisObj, int height);

// tag=1067
//  KDDockWidgets::View::setMaximumSize(QSize sz)
KDDockWidgets_EXPORT void c_KDDockWidgets__View__setMaximumSize_QSize(void *thisObj, void *sz_);

// tag=1067
//  KDDockWidgets::View::setMinimumSize(QSize arg__1)
KDDockWidgets_EXPORT void c_KDDockWidgets__View__setMinimumSize_QSize(void *thisObj, void *arg__1_);

// tag=1067
//  KDDockWidgets::View::setMouseTracking(bool arg__1)
KDDockWidgets_EXPORT void c_KDDockWidgets__View__setMouseTracking_bool(void *thisObj, bool arg__1);

// tag=1067
//  KDDockWidgets::View::setObjectName(const QString & arg__1)
KDDockWidgets_EXPORT void c_KDDockWidgets__View__setObjectName_QString(void *thisObj, const char *arg__1_);

// tag=1067
//  KDDockWidgets::View::setParent(KDDockWidgets::View * arg__1)
KDDockWidgets_EXPORT void c_KDDockWidgets__View__setParent_View(void *thisObj, void *arg__1_);

// tag=1067
//  KDDockWidgets::View::setSize(QSize arg__1)
KDDockWidgets_EXPORT void c_KDDockWidgets__View__setSize_QSize(void *thisObj, void *arg__1_);

// tag=1067
//  KDDockWidgets::View::setSize(int width, int height)
KDDockWidgets_EXPORT void c_KDDockWidgets__View__setSize_int_int(void *thisObj, int width, int height);

// tag=1067
//  KDDockWidgets::View::setVisible(bool arg__1)
KDDockWidgets_EXPORT void c_KDDockWidgets__View__setVisible_bool(void *thisObj, bool arg__1);

// tag=1067
//  KDDockWidgets::View::setWidth(int width)
KDDockWidgets_EXPORT void c_KDDockWidgets__View__setWidth_int(void *thisObj, int width);

// tag=1067
//  KDDockWidgets::View::setWindowOpacity(double arg__1)
KDDockWidgets_EXPORT void c_KDDockWidgets__View__setWindowOpacity_double(void *thisObj, double arg__1);

// tag=1067
//  KDDockWidgets::View::setWindowTitle(const QString & title)
KDDockWidgets_EXPORT void c_KDDockWidgets__View__setWindowTitle_QString(void *thisObj, const char *title_);

// tag=1067
//  KDDockWidgets::View::setZOrder(int arg__1)
KDDockWidgets_EXPORT void c_KDDockWidgets__View__setZOrder_int(void *thisObj, int arg__1);

// tag=1067
//  KDDockWidgets::View::show()
KDDockWidgets_EXPORT void c_KDDockWidgets__View__show(void *thisObj);

// tag=1067
//  KDDockWidgets::View::showMaximized()
KDDockWidgets_EXPORT void c_KDDockWidgets__View__showMaximized(void *thisObj);

// tag=1067
//  KDDockWidgets::View::showMinimized()
KDDockWidgets_EXPORT void c_KDDockWidgets__View__showMinimized(void *thisObj);

// tag=1067
//  KDDockWidgets::View::showNormal()
KDDockWidgets_EXPORT void c_KDDockWidgets__View__showNormal(void *thisObj);

// tag=1067
//  KDDockWidgets::View::size() const
KDDockWidgets_EXPORT void *c_KDDockWidgets__View__size(void *thisObj);

// tag=1067
//  KDDockWidgets::View::sizeHint() const
KDDockWidgets_EXPORT void *c_KDDockWidgets__View__sizeHint(void *thisObj);

// tag=1067
//  KDDockWidgets::View::update()
KDDockWidgets_EXPORT void c_KDDockWidgets__View__update(void *thisObj);

// tag=1067
//  KDDockWidgets::View::width() const
KDDockWidgets_EXPORT int c_KDDockWidgets__View__width(void *thisObj);

// tag=1067
//  KDDockWidgets::View::windowGeometry() const
KDDockWidgets_EXPORT void *c_KDDockWidgets__View__windowGeometry(void *thisObj);

// tag=1067
//  KDDockWidgets::View::x() const
KDDockWidgets_EXPORT int c_KDDockWidgets__View__x(void *thisObj);

// tag=1067
//  KDDockWidgets::View::y() const
KDDockWidgets_EXPORT int c_KDDockWidgets__View__y(void *thisObj);

// tag=1066
KDDockWidgets_EXPORT void c_KDDockWidgets__View__destructor(void *thisObj);

// tag=1046
KDDockWidgets_EXPORT void c_KDDockWidgets__View__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
// tag=1047
KDDockWidgets_EXPORT void c_KDDockWidgets__View_Finalizer(void *, void *cppObj, void *);
}

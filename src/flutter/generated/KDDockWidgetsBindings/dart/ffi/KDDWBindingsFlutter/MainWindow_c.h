/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <MainWindow.h>
#include <qstring.h>
#include <View.h>
#include <qrect.h>
#include <qpoint.h>
#include <core/View.h>
#include <qsize.h>

namespace KDDockWidgetsBindings_wrappersNS {
namespace KDDWBindingsFlutter {
class MainWindow_wrapper : public ::KDDockWidgets::flutter::MainWindow
{
public:
    ~MainWindow_wrapper();
    MainWindow_wrapper(const QString &uniqueName, QFlags<KDDockWidgets::MainWindowOption> options = {}, KDDockWidgets::flutter::View *parent = nullptr, Qt::WindowFlags flags = {});
    virtual void activateWindow();
    virtual void activateWindow_nocallback();
    virtual QRect centralAreaGeometry() const;
    virtual QRect centralAreaGeometry_nocallback() const;
    virtual bool close();
    virtual bool close_nocallback();
    virtual void createPlatformWindow();
    virtual void createPlatformWindow_nocallback();
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
    virtual void init();
    virtual void init_nocallback();
    virtual bool isActiveWindow() const;
    virtual bool isActiveWindow_nocallback() const;
    virtual bool isExpicitlyHidden() const;
    virtual bool isExpicitlyHidden_nocallback() const;
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
    virtual void onChildVisibilityChanged(KDDockWidgets::Core::View *childView);
    virtual void onChildVisibilityChanged_nocallback(KDDockWidgets::Core::View *childView);
    virtual bool onResize(int h, int w);
    virtual bool onResize_nocallback(int h, int w);
    virtual void raise();
    virtual void raise_nocallback();
    virtual void raiseAndActivate();
    virtual void raiseAndActivate_nocallback();
    virtual void releaseKeyboard();
    virtual void releaseKeyboard_nocallback();
    virtual void releaseMouse();
    virtual void releaseMouse_nocallback();
    virtual void setContentsMargins(int left, int top, int right, int bottom);
    virtual void setContentsMargins_nocallback(int left, int top, int right, int bottom);
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
    virtual void setObjectName(const QString &name);
    virtual void setObjectName_nocallback(const QString &name);
    virtual void setParent(KDDockWidgets::Core::View *parent);
    virtual void setParent_nocallback(KDDockWidgets::Core::View *parent);
    virtual void setSize(int w, int h);
    virtual void setSize_nocallback(int w, int h);
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
    typedef void (*Callback_activateWindow)(void *);
    Callback_activateWindow m_activateWindowCallback = nullptr;
    typedef QRect *(*Callback_centralAreaGeometry)(void *);
    Callback_centralAreaGeometry m_centralAreaGeometryCallback = nullptr;
    typedef bool (*Callback_close)(void *);
    Callback_close m_closeCallback = nullptr;
    typedef void (*Callback_createPlatformWindow)(void *);
    Callback_createPlatformWindow m_createPlatformWindowCallback = nullptr;
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
    typedef void (*Callback_init)(void *);
    Callback_init m_initCallback = nullptr;
    typedef bool (*Callback_isActiveWindow)(void *);
    Callback_isActiveWindow m_isActiveWindowCallback = nullptr;
    typedef bool (*Callback_isExpicitlyHidden)(void *);
    Callback_isExpicitlyHidden m_isExpicitlyHiddenCallback = nullptr;
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
    typedef void (*Callback_onChildVisibilityChanged)(void *, KDDockWidgets::Core::View *childView);
    Callback_onChildVisibilityChanged m_onChildVisibilityChangedCallback = nullptr;
    typedef bool (*Callback_onResize_2)(void *, int h, int w);
    Callback_onResize_2 m_onResize_2Callback = nullptr;
    typedef void (*Callback_raise)(void *);
    Callback_raise m_raiseCallback = nullptr;
    typedef void (*Callback_raiseAndActivate)(void *);
    Callback_raiseAndActivate m_raiseAndActivateCallback = nullptr;
    typedef void (*Callback_releaseKeyboard)(void *);
    Callback_releaseKeyboard m_releaseKeyboardCallback = nullptr;
    typedef void (*Callback_releaseMouse)(void *);
    Callback_releaseMouse m_releaseMouseCallback = nullptr;
    typedef void (*Callback_setContentsMargins)(void *, int left, int top, int right, int bottom);
    Callback_setContentsMargins m_setContentsMarginsCallback = nullptr;
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
// KDDockWidgets::flutter::MainWindow::MainWindow(const QString & uniqueName, QFlags<KDDockWidgets::MainWindowOption> options, KDDockWidgets::flutter::View * parent, Qt::WindowFlags flags)
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__MainWindow__constructor_QString_MainWindowOptions_View_WindowFlags(const char *uniqueName_, int options_, void *parent_, int flags);
// KDDockWidgets::flutter::MainWindow::activateWindow()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__activateWindow(void *thisObj);
// KDDockWidgets::flutter::MainWindow::centralAreaGeometry() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__MainWindow__centralAreaGeometry(void *thisObj);
// KDDockWidgets::flutter::MainWindow::close()
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__flutter__MainWindow__close(void *thisObj);
// KDDockWidgets::flutter::MainWindow::createPlatformWindow()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__createPlatformWindow(void *thisObj);
// KDDockWidgets::flutter::MainWindow::flags() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__flutter__MainWindow__flags(void *thisObj);
// KDDockWidgets::flutter::MainWindow::geometry() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__MainWindow__geometry(void *thisObj);
// KDDockWidgets::flutter::MainWindow::grabMouse()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__grabMouse(void *thisObj);
// KDDockWidgets::flutter::MainWindow::hasFocus() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__flutter__MainWindow__hasFocus(void *thisObj);
// KDDockWidgets::flutter::MainWindow::hide()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__hide(void *thisObj);
// KDDockWidgets::flutter::MainWindow::init()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__init(void *thisObj);
// KDDockWidgets::flutter::MainWindow::isActiveWindow() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__flutter__MainWindow__isActiveWindow(void *thisObj);
// KDDockWidgets::flutter::MainWindow::isExpicitlyHidden() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__flutter__MainWindow__isExpicitlyHidden(void *thisObj);
// KDDockWidgets::flutter::MainWindow::isMaximized() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__flutter__MainWindow__isMaximized(void *thisObj);
// KDDockWidgets::flutter::MainWindow::isMinimized() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__flutter__MainWindow__isMinimized(void *thisObj);
// KDDockWidgets::flutter::MainWindow::isNull() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__flutter__MainWindow__isNull(void *thisObj);
// KDDockWidgets::flutter::MainWindow::isRootView() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__flutter__MainWindow__isRootView(void *thisObj);
// KDDockWidgets::flutter::MainWindow::isVisible() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__flutter__MainWindow__isVisible(void *thisObj);
// KDDockWidgets::flutter::MainWindow::mapFromGlobal(QPoint globalPt) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__MainWindow__mapFromGlobal_QPoint(void *thisObj, void *globalPt_);
// KDDockWidgets::flutter::MainWindow::mapTo(KDDockWidgets::Core::View * parent, QPoint pos) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__MainWindow__mapTo_View_QPoint(void *thisObj, void *parent_, void *pos_);
// KDDockWidgets::flutter::MainWindow::mapToGlobal(QPoint localPt) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__MainWindow__mapToGlobal_QPoint(void *thisObj, void *localPt_);
// KDDockWidgets::flutter::MainWindow::maxSizeHint() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__MainWindow__maxSizeHint(void *thisObj);
// KDDockWidgets::flutter::MainWindow::minSize() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__MainWindow__minSize(void *thisObj);
// KDDockWidgets::flutter::MainWindow::minimumHeight() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__flutter__MainWindow__minimumHeight(void *thisObj);
// KDDockWidgets::flutter::MainWindow::minimumWidth() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__flutter__MainWindow__minimumWidth(void *thisObj);
// KDDockWidgets::flutter::MainWindow::move(int x, int y)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__move_int_int(void *thisObj, int x, int y);
// KDDockWidgets::flutter::MainWindow::normalGeometry() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__MainWindow__normalGeometry(void *thisObj);
// KDDockWidgets::flutter::MainWindow::objectName() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__MainWindow__objectName(void *thisObj);
// KDDockWidgets::flutter::MainWindow::onChildAdded(KDDockWidgets::Core::View * childView)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__onChildAdded_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::MainWindow::onChildRemoved(KDDockWidgets::Core::View * childView)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__onChildRemoved_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::MainWindow::onChildVisibilityChanged(KDDockWidgets::Core::View * childView)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__onChildVisibilityChanged_View(void *thisObj, void *childView_);
// KDDockWidgets::flutter::MainWindow::onResize(int h, int w)
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__flutter__MainWindow__onResize_int_int(void *thisObj, int h, int w);
// KDDockWidgets::flutter::MainWindow::raise()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__raise(void *thisObj);
// KDDockWidgets::flutter::MainWindow::raiseAndActivate()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__raiseAndActivate(void *thisObj);
// KDDockWidgets::flutter::MainWindow::releaseKeyboard()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__releaseKeyboard(void *thisObj);
// KDDockWidgets::flutter::MainWindow::releaseMouse()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__releaseMouse(void *thisObj);
// KDDockWidgets::flutter::MainWindow::setContentsMargins(int left, int top, int right, int bottom)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__setContentsMargins_int_int_int_int(void *thisObj, int left, int top, int right, int bottom);
// KDDockWidgets::flutter::MainWindow::setCursor(Qt::CursorShape shape)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__setCursor_CursorShape(void *thisObj, int shape);
// KDDockWidgets::flutter::MainWindow::setFixedHeight(int h)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__setFixedHeight_int(void *thisObj, int h);
// KDDockWidgets::flutter::MainWindow::setFixedWidth(int w)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__setFixedWidth_int(void *thisObj, int w);
// KDDockWidgets::flutter::MainWindow::setGeometry(QRect geometry)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__setGeometry_QRect(void *thisObj, void *geometry_);
// KDDockWidgets::flutter::MainWindow::setHeight(int h)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__setHeight_int(void *thisObj, int h);
// KDDockWidgets::flutter::MainWindow::setMaximumSize(QSize sz)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__setMaximumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::flutter::MainWindow::setMinimumSize(QSize sz)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__setMinimumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::flutter::MainWindow::setMouseTracking(bool enable)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__setMouseTracking_bool(void *thisObj, bool enable);
// KDDockWidgets::flutter::MainWindow::setObjectName(const QString & name)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__setObjectName_QString(void *thisObj, const char *name_);
// KDDockWidgets::flutter::MainWindow::setParent(KDDockWidgets::Core::View * parent)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__setParent_View(void *thisObj, void *parent_);
// KDDockWidgets::flutter::MainWindow::setSize(int w, int h)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__setSize_int_int(void *thisObj, int w, int h);
// KDDockWidgets::flutter::MainWindow::setVisible(bool visible)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__setVisible_bool(void *thisObj, bool visible);
// KDDockWidgets::flutter::MainWindow::setWidth(int w)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__setWidth_int(void *thisObj, int w);
// KDDockWidgets::flutter::MainWindow::setWindowOpacity(double v)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__setWindowOpacity_double(void *thisObj, double v);
// KDDockWidgets::flutter::MainWindow::setWindowTitle(const QString & title)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__setWindowTitle_QString(void *thisObj, const char *title_);
// KDDockWidgets::flutter::MainWindow::setZOrder(int z)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__setZOrder_int(void *thisObj, int z);
// KDDockWidgets::flutter::MainWindow::show()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__show(void *thisObj);
// KDDockWidgets::flutter::MainWindow::showMaximized()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__showMaximized(void *thisObj);
// KDDockWidgets::flutter::MainWindow::showMinimized()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__showMinimized(void *thisObj);
// KDDockWidgets::flutter::MainWindow::showNormal()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__showNormal(void *thisObj);
// KDDockWidgets::flutter::MainWindow::sizeHint() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__MainWindow__sizeHint(void *thisObj);
// KDDockWidgets::flutter::MainWindow::update()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__update(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__MainWindow_Finalizer(void *, void *cppObj, void *);
}

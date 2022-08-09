/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <TitleBar_flutter.h>
#include <TitleBar.h>
#include <View.h>
#include <qsize.h>
#include <qrect.h>
#include <qpoint.h>
#include <qstring.h>

namespace KDDockWidgetsBindings_wrappersNS {
class TitleBar_flutter_wrapper : public ::KDDockWidgets::Views::TitleBar_flutter
{
public:
    ~TitleBar_flutter_wrapper();
    TitleBar_flutter_wrapper(KDDockWidgets::Controllers::TitleBar *controller,
                             KDDockWidgets::View *parent = nullptr);
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
    virtual bool isCloseButtonEnabled() const;
    virtual bool isCloseButtonEnabled_nocallback() const;
    virtual bool isCloseButtonVisible() const;
    virtual bool isCloseButtonVisible_nocallback() const;
    virtual bool isFloatButtonVisible() const;
    virtual bool isFloatButtonVisible_nocallback() const;
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
    virtual QPoint mapTo(KDDockWidgets::View *parent, QPoint pos) const;
    virtual QPoint mapTo_nocallback(KDDockWidgets::View *parent, QPoint pos) const;
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
    virtual void setParent(KDDockWidgets::View *parent);
    virtual void setParent_nocallback(KDDockWidgets::View *parent);
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
    typedef bool (*Callback_isCloseButtonEnabled)(void *);
    Callback_isCloseButtonEnabled m_isCloseButtonEnabledCallback = nullptr;
    typedef bool (*Callback_isCloseButtonVisible)(void *);
    Callback_isCloseButtonVisible m_isCloseButtonVisibleCallback = nullptr;
    typedef bool (*Callback_isFloatButtonVisible)(void *);
    Callback_isFloatButtonVisible m_isFloatButtonVisibleCallback = nullptr;
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
    typedef QPoint *(*Callback_mapTo)(void *, KDDockWidgets::View *parent, QPoint *pos);
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
    typedef void (*Callback_setParent)(void *, KDDockWidgets::View *parent);
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
extern "C" {
// KDDockWidgets::Views::TitleBar_flutter::TitleBar_flutter(KDDockWidgets::Controllers::TitleBar *
// controller, KDDockWidgets::View * parent)
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Views__TitleBar_flutter__constructor_TitleBar_View(void *controller_,
                                                                    void *parent_);
// KDDockWidgets::Views::TitleBar_flutter::activateWindow()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__TitleBar_flutter__activateWindow(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::close()
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Views__TitleBar_flutter__close(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::createPlatformWindow()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__TitleBar_flutter__createPlatformWindow(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::flags() const
KDDockWidgetsBindings_EXPORT int c_KDDockWidgets__Views__TitleBar_flutter__flags(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::free_impl()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__TitleBar_flutter__free_impl(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::geometry() const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Views__TitleBar_flutter__geometry(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::grabMouse()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__TitleBar_flutter__grabMouse(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::hasFocus() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Views__TitleBar_flutter__hasFocus(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::hide()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__TitleBar_flutter__hide(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::init()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__TitleBar_flutter__init(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::isActiveWindow() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Views__TitleBar_flutter__isActiveWindow(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::isCloseButtonEnabled() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Views__TitleBar_flutter__isCloseButtonEnabled(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::isCloseButtonVisible() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Views__TitleBar_flutter__isCloseButtonVisible(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::isFloatButtonVisible() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Views__TitleBar_flutter__isFloatButtonVisible(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::isMaximized() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Views__TitleBar_flutter__isMaximized(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::isMinimized() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Views__TitleBar_flutter__isMinimized(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::isNull() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__Views__TitleBar_flutter__isNull(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::isRootView() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Views__TitleBar_flutter__isRootView(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::isVisible() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Views__TitleBar_flutter__isVisible(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::mapFromGlobal(QPoint globalPt) const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Views__TitleBar_flutter__mapFromGlobal_QPoint(void *thisObj, void *globalPt_);
// KDDockWidgets::Views::TitleBar_flutter::mapTo(KDDockWidgets::View * parent, QPoint pos) const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Views__TitleBar_flutter__mapTo_View_QPoint(void *thisObj, void *parent_,
                                                            void *pos_);
// KDDockWidgets::Views::TitleBar_flutter::mapToGlobal(QPoint localPt) const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Views__TitleBar_flutter__mapToGlobal_QPoint(void *thisObj, void *localPt_);
// KDDockWidgets::Views::TitleBar_flutter::maxSizeHint() const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Views__TitleBar_flutter__maxSizeHint(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::minSize() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__Views__TitleBar_flutter__minSize(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::minimumHeight() const
KDDockWidgetsBindings_EXPORT int
c_KDDockWidgets__Views__TitleBar_flutter__minimumHeight(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::minimumWidth() const
KDDockWidgetsBindings_EXPORT int
c_KDDockWidgets__Views__TitleBar_flutter__minimumWidth(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::move(int x, int y)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__TitleBar_flutter__move_int_int(void *thisObj, int x, int y);
// KDDockWidgets::Views::TitleBar_flutter::normalGeometry() const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Views__TitleBar_flutter__normalGeometry(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::objectName() const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Views__TitleBar_flutter__objectName(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::onResize(int h, int w)
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__Views__TitleBar_flutter__onResize_int_int(void *thisObj, int h, int w);
// KDDockWidgets::Views::TitleBar_flutter::raise()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__TitleBar_flutter__raise(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::raiseAndActivate()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__TitleBar_flutter__raiseAndActivate(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::releaseKeyboard()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__TitleBar_flutter__releaseKeyboard(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::releaseMouse()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__TitleBar_flutter__releaseMouse(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::setCursor(Qt::CursorShape shape)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__TitleBar_flutter__setCursor_CursorShape(void *thisObj, int shape);
// KDDockWidgets::Views::TitleBar_flutter::setFixedHeight(int h)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__TitleBar_flutter__setFixedHeight_int(void *thisObj, int h);
// KDDockWidgets::Views::TitleBar_flutter::setFixedWidth(int w)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__TitleBar_flutter__setFixedWidth_int(void *thisObj, int w);
// KDDockWidgets::Views::TitleBar_flutter::setGeometry(QRect geometry)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__TitleBar_flutter__setGeometry_QRect(void *thisObj, void *geometry_);
// KDDockWidgets::Views::TitleBar_flutter::setHeight(int h)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__TitleBar_flutter__setHeight_int(void *thisObj, int h);
// KDDockWidgets::Views::TitleBar_flutter::setMaximumSize(QSize sz)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__TitleBar_flutter__setMaximumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::Views::TitleBar_flutter::setMinimumSize(QSize sz)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__TitleBar_flutter__setMinimumSize_QSize(void *thisObj, void *sz_);
// KDDockWidgets::Views::TitleBar_flutter::setMouseTracking(bool enable)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__TitleBar_flutter__setMouseTracking_bool(void *thisObj, bool enable);
// KDDockWidgets::Views::TitleBar_flutter::setObjectName(const QString & name)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__TitleBar_flutter__setObjectName_QString(void *thisObj, const char *name_);
// KDDockWidgets::Views::TitleBar_flutter::setParent(KDDockWidgets::View * parent)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__TitleBar_flutter__setParent_View(void *thisObj, void *parent_);
// KDDockWidgets::Views::TitleBar_flutter::setSize(int w, int h)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__TitleBar_flutter__setSize_int_int(void *thisObj, int w, int h);
// KDDockWidgets::Views::TitleBar_flutter::setVisible(bool visible)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__TitleBar_flutter__setVisible_bool(void *thisObj, bool visible);
// KDDockWidgets::Views::TitleBar_flutter::setWidth(int w)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__TitleBar_flutter__setWidth_int(void *thisObj, int w);
// KDDockWidgets::Views::TitleBar_flutter::setWindowOpacity(double v)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__TitleBar_flutter__setWindowOpacity_double(void *thisObj, double v);
// KDDockWidgets::Views::TitleBar_flutter::setWindowTitle(const QString & title)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__TitleBar_flutter__setWindowTitle_QString(void *thisObj, const char *title_);
// KDDockWidgets::Views::TitleBar_flutter::setZOrder(int z)
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__TitleBar_flutter__setZOrder_int(void *thisObj, int z);
// KDDockWidgets::Views::TitleBar_flutter::show()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__TitleBar_flutter__show(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::showMaximized()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__TitleBar_flutter__showMaximized(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::showMinimized()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__TitleBar_flutter__showMinimized(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::showNormal()
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__TitleBar_flutter__showNormal(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::sizeHint() const
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__Views__TitleBar_flutter__sizeHint(void *thisObj);
// KDDockWidgets::Views::TitleBar_flutter::update()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__Views__TitleBar_flutter__update(void *thisObj);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__TitleBar_flutter__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__TitleBar_flutter__registerVirtualMethodCallback(void *ptr, void *callback,
                                                                        int methodId);
KDDockWidgetsBindings_EXPORT void
c_KDDockWidgets__Views__TitleBar_flutter_Finalizer(void *, void *cppObj, void *);
}

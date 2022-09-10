/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "TitleBar_flutter_wrapper.h"


#include <QDebug>


namespace Dartagnan {

typedef int (*CleanupCallback)(void *thisPtr);
static CleanupCallback s_cleanupCallback = nullptr;

template<typename T>
struct ValueWrapper
{
    T value;
};

}
namespace KDDockWidgetsBindings_wrappersNS {
TitleBar_flutter_wrapper::TitleBar_flutter_wrapper(KDDockWidgets::Controllers::TitleBar *controller,
                                                   KDDockWidgets::View *parent)
    : ::KDDockWidgets::Views::TitleBar_flutter(controller, parent)
{
}
void TitleBar_flutter_wrapper::activateWindow()
{
    if (m_activateWindowCallback) {
        const void *thisPtr = this;
        m_activateWindowCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Views::TitleBar_flutter::activateWindow();
    }
}
void TitleBar_flutter_wrapper::activateWindow_nocallback()
{
    ::KDDockWidgets::Views::TitleBar_flutter::activateWindow();
}
bool TitleBar_flutter_wrapper::close()
{
    if (m_closeCallback) {
        const void *thisPtr = this;
        return m_closeCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::TitleBar_flutter::close();
    }
}
bool TitleBar_flutter_wrapper::close_nocallback()
{
    return ::KDDockWidgets::Views::TitleBar_flutter::close();
}
void TitleBar_flutter_wrapper::createPlatformWindow()
{
    if (m_createPlatformWindowCallback) {
        const void *thisPtr = this;
        m_createPlatformWindowCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Views::TitleBar_flutter::createPlatformWindow();
    }
}
void TitleBar_flutter_wrapper::createPlatformWindow_nocallback()
{
    ::KDDockWidgets::Views::TitleBar_flutter::createPlatformWindow();
}
Qt::WindowFlags TitleBar_flutter_wrapper::flags() const
{
    if (m_flagsCallback) {
        const void *thisPtr = this;
        return m_flagsCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::TitleBar_flutter::flags();
    }
}
Qt::WindowFlags TitleBar_flutter_wrapper::flags_nocallback() const
{
    return ::KDDockWidgets::Views::TitleBar_flutter::flags();
}
void TitleBar_flutter_wrapper::free_impl()
{
    if (m_free_implCallback) {
        const void *thisPtr = this;
        m_free_implCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Views::TitleBar_flutter::free_impl();
    }
}
void TitleBar_flutter_wrapper::free_impl_nocallback()
{
    ::KDDockWidgets::Views::TitleBar_flutter::free_impl();
}
QRect TitleBar_flutter_wrapper::geometry() const
{
    if (m_geometryCallback) {
        const void *thisPtr = this;
        return *m_geometryCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::TitleBar_flutter::geometry();
    }
}
QRect TitleBar_flutter_wrapper::geometry_nocallback() const
{
    return ::KDDockWidgets::Views::TitleBar_flutter::geometry();
}
void TitleBar_flutter_wrapper::grabMouse()
{
    if (m_grabMouseCallback) {
        const void *thisPtr = this;
        m_grabMouseCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Views::TitleBar_flutter::grabMouse();
    }
}
void TitleBar_flutter_wrapper::grabMouse_nocallback()
{
    ::KDDockWidgets::Views::TitleBar_flutter::grabMouse();
}
bool TitleBar_flutter_wrapper::hasFocus() const
{
    if (m_hasFocusCallback) {
        const void *thisPtr = this;
        return m_hasFocusCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::TitleBar_flutter::hasFocus();
    }
}
bool TitleBar_flutter_wrapper::hasFocus_nocallback() const
{
    return ::KDDockWidgets::Views::TitleBar_flutter::hasFocus();
}
void TitleBar_flutter_wrapper::hide()
{
    if (m_hideCallback) {
        const void *thisPtr = this;
        m_hideCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Views::TitleBar_flutter::hide();
    }
}
void TitleBar_flutter_wrapper::hide_nocallback()
{
    ::KDDockWidgets::Views::TitleBar_flutter::hide();
}
void TitleBar_flutter_wrapper::init()
{
    if (m_initCallback) {
        const void *thisPtr = this;
        m_initCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Views::TitleBar_flutter::init();
    }
}
void TitleBar_flutter_wrapper::init_nocallback()
{
    ::KDDockWidgets::Views::TitleBar_flutter::init();
}
bool TitleBar_flutter_wrapper::isActiveWindow() const
{
    if (m_isActiveWindowCallback) {
        const void *thisPtr = this;
        return m_isActiveWindowCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::TitleBar_flutter::isActiveWindow();
    }
}
bool TitleBar_flutter_wrapper::isActiveWindow_nocallback() const
{
    return ::KDDockWidgets::Views::TitleBar_flutter::isActiveWindow();
}
bool TitleBar_flutter_wrapper::isCloseButtonEnabled() const
{
    if (m_isCloseButtonEnabledCallback) {
        const void *thisPtr = this;
        return m_isCloseButtonEnabledCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::TitleBar_flutter::isCloseButtonEnabled();
    }
}
bool TitleBar_flutter_wrapper::isCloseButtonEnabled_nocallback() const
{
    return ::KDDockWidgets::Views::TitleBar_flutter::isCloseButtonEnabled();
}
bool TitleBar_flutter_wrapper::isCloseButtonVisible() const
{
    if (m_isCloseButtonVisibleCallback) {
        const void *thisPtr = this;
        return m_isCloseButtonVisibleCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::TitleBar_flutter::isCloseButtonVisible();
    }
}
bool TitleBar_flutter_wrapper::isCloseButtonVisible_nocallback() const
{
    return ::KDDockWidgets::Views::TitleBar_flutter::isCloseButtonVisible();
}
bool TitleBar_flutter_wrapper::isFloatButtonVisible() const
{
    if (m_isFloatButtonVisibleCallback) {
        const void *thisPtr = this;
        return m_isFloatButtonVisibleCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::TitleBar_flutter::isFloatButtonVisible();
    }
}
bool TitleBar_flutter_wrapper::isFloatButtonVisible_nocallback() const
{
    return ::KDDockWidgets::Views::TitleBar_flutter::isFloatButtonVisible();
}
bool TitleBar_flutter_wrapper::isMaximized() const
{
    if (m_isMaximizedCallback) {
        const void *thisPtr = this;
        return m_isMaximizedCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::TitleBar_flutter::isMaximized();
    }
}
bool TitleBar_flutter_wrapper::isMaximized_nocallback() const
{
    return ::KDDockWidgets::Views::TitleBar_flutter::isMaximized();
}
bool TitleBar_flutter_wrapper::isMinimized() const
{
    if (m_isMinimizedCallback) {
        const void *thisPtr = this;
        return m_isMinimizedCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::TitleBar_flutter::isMinimized();
    }
}
bool TitleBar_flutter_wrapper::isMinimized_nocallback() const
{
    return ::KDDockWidgets::Views::TitleBar_flutter::isMinimized();
}
bool TitleBar_flutter_wrapper::isNull() const
{
    if (m_isNullCallback) {
        const void *thisPtr = this;
        return m_isNullCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::TitleBar_flutter::isNull();
    }
}
bool TitleBar_flutter_wrapper::isNull_nocallback() const
{
    return ::KDDockWidgets::Views::TitleBar_flutter::isNull();
}
bool TitleBar_flutter_wrapper::isRootView() const
{
    if (m_isRootViewCallback) {
        const void *thisPtr = this;
        return m_isRootViewCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::TitleBar_flutter::isRootView();
    }
}
bool TitleBar_flutter_wrapper::isRootView_nocallback() const
{
    return ::KDDockWidgets::Views::TitleBar_flutter::isRootView();
}
bool TitleBar_flutter_wrapper::isVisible() const
{
    if (m_isVisibleCallback) {
        const void *thisPtr = this;
        return m_isVisibleCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::TitleBar_flutter::isVisible();
    }
}
bool TitleBar_flutter_wrapper::isVisible_nocallback() const
{
    return ::KDDockWidgets::Views::TitleBar_flutter::isVisible();
}
QPoint TitleBar_flutter_wrapper::mapFromGlobal(QPoint globalPt) const
{
    if (m_mapFromGlobalCallback) {
        const void *thisPtr = this;
        return *m_mapFromGlobalCallback(const_cast<void *>(thisPtr), &globalPt);
    } else {
        return ::KDDockWidgets::Views::TitleBar_flutter::mapFromGlobal(globalPt);
    }
}
QPoint TitleBar_flutter_wrapper::mapFromGlobal_nocallback(QPoint globalPt) const
{
    return ::KDDockWidgets::Views::TitleBar_flutter::mapFromGlobal(globalPt);
}
QPoint TitleBar_flutter_wrapper::mapTo(KDDockWidgets::View *parent, QPoint pos) const
{
    if (m_mapToCallback) {
        const void *thisPtr = this;
        return *m_mapToCallback(const_cast<void *>(thisPtr), parent, &pos);
    } else {
        return ::KDDockWidgets::Views::TitleBar_flutter::mapTo(parent, pos);
    }
}
QPoint TitleBar_flutter_wrapper::mapTo_nocallback(KDDockWidgets::View *parent, QPoint pos) const
{
    return ::KDDockWidgets::Views::TitleBar_flutter::mapTo(parent, pos);
}
QPoint TitleBar_flutter_wrapper::mapToGlobal(QPoint localPt) const
{
    if (m_mapToGlobalCallback) {
        const void *thisPtr = this;
        return *m_mapToGlobalCallback(const_cast<void *>(thisPtr), &localPt);
    } else {
        return ::KDDockWidgets::Views::TitleBar_flutter::mapToGlobal(localPt);
    }
}
QPoint TitleBar_flutter_wrapper::mapToGlobal_nocallback(QPoint localPt) const
{
    return ::KDDockWidgets::Views::TitleBar_flutter::mapToGlobal(localPt);
}
QSize TitleBar_flutter_wrapper::maxSizeHint() const
{
    if (m_maxSizeHintCallback) {
        const void *thisPtr = this;
        return *m_maxSizeHintCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::TitleBar_flutter::maxSizeHint();
    }
}
QSize TitleBar_flutter_wrapper::maxSizeHint_nocallback() const
{
    return ::KDDockWidgets::Views::TitleBar_flutter::maxSizeHint();
}
QSize TitleBar_flutter_wrapper::minSize() const
{
    if (m_minSizeCallback) {
        const void *thisPtr = this;
        return *m_minSizeCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::TitleBar_flutter::minSize();
    }
}
QSize TitleBar_flutter_wrapper::minSize_nocallback() const
{
    return ::KDDockWidgets::Views::TitleBar_flutter::minSize();
}
int TitleBar_flutter_wrapper::minimumHeight() const
{
    if (m_minimumHeightCallback) {
        const void *thisPtr = this;
        return m_minimumHeightCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::TitleBar_flutter::minimumHeight();
    }
}
int TitleBar_flutter_wrapper::minimumHeight_nocallback() const
{
    return ::KDDockWidgets::Views::TitleBar_flutter::minimumHeight();
}
int TitleBar_flutter_wrapper::minimumWidth() const
{
    if (m_minimumWidthCallback) {
        const void *thisPtr = this;
        return m_minimumWidthCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::TitleBar_flutter::minimumWidth();
    }
}
int TitleBar_flutter_wrapper::minimumWidth_nocallback() const
{
    return ::KDDockWidgets::Views::TitleBar_flutter::minimumWidth();
}
void TitleBar_flutter_wrapper::move(int x, int y)
{
    if (m_move_2Callback) {
        const void *thisPtr = this;
        m_move_2Callback(const_cast<void *>(thisPtr), x, y);
    } else {
        ::KDDockWidgets::Views::TitleBar_flutter::move(x, y);
    }
}
void TitleBar_flutter_wrapper::move_nocallback(int x, int y)
{
    ::KDDockWidgets::Views::TitleBar_flutter::move(x, y);
}
QRect TitleBar_flutter_wrapper::normalGeometry() const
{
    if (m_normalGeometryCallback) {
        const void *thisPtr = this;
        return *m_normalGeometryCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::TitleBar_flutter::normalGeometry();
    }
}
QRect TitleBar_flutter_wrapper::normalGeometry_nocallback() const
{
    return ::KDDockWidgets::Views::TitleBar_flutter::normalGeometry();
}
QString TitleBar_flutter_wrapper::objectName() const
{
    if (m_objectNameCallback) {
        const void *thisPtr = this;
        return *m_objectNameCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::TitleBar_flutter::objectName();
    }
}
QString TitleBar_flutter_wrapper::objectName_nocallback() const
{
    return ::KDDockWidgets::Views::TitleBar_flutter::objectName();
}
void TitleBar_flutter_wrapper::onChildAdded(KDDockWidgets::View *childView)
{
    if (m_onChildAddedCallback) {
        const void *thisPtr = this;
        m_onChildAddedCallback(const_cast<void *>(thisPtr), childView);
    } else {
        ::KDDockWidgets::Views::TitleBar_flutter::onChildAdded(childView);
    }
}
void TitleBar_flutter_wrapper::onChildAdded_nocallback(KDDockWidgets::View *childView)
{
    ::KDDockWidgets::Views::TitleBar_flutter::onChildAdded(childView);
}
void TitleBar_flutter_wrapper::onChildRemoved(KDDockWidgets::View *childView)
{
    if (m_onChildRemovedCallback) {
        const void *thisPtr = this;
        m_onChildRemovedCallback(const_cast<void *>(thisPtr), childView);
    } else {
        ::KDDockWidgets::Views::TitleBar_flutter::onChildRemoved(childView);
    }
}
void TitleBar_flutter_wrapper::onChildRemoved_nocallback(KDDockWidgets::View *childView)
{
    ::KDDockWidgets::Views::TitleBar_flutter::onChildRemoved(childView);
}
bool TitleBar_flutter_wrapper::onResize(int w, int h)
{
    if (m_onResize_2Callback) {
        const void *thisPtr = this;
        return m_onResize_2Callback(const_cast<void *>(thisPtr), w, h);
    } else {
        return ::KDDockWidgets::Views::TitleBar_flutter::onResize(w, h);
    }
}
bool TitleBar_flutter_wrapper::onResize_nocallback(int w, int h)
{
    return ::KDDockWidgets::Views::TitleBar_flutter::onResize(w, h);
}
void TitleBar_flutter_wrapper::raise()
{
    if (m_raiseCallback) {
        const void *thisPtr = this;
        m_raiseCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Views::TitleBar_flutter::raise();
    }
}
void TitleBar_flutter_wrapper::raise_nocallback()
{
    ::KDDockWidgets::Views::TitleBar_flutter::raise();
}
void TitleBar_flutter_wrapper::raiseAndActivate()
{
    if (m_raiseAndActivateCallback) {
        const void *thisPtr = this;
        m_raiseAndActivateCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Views::TitleBar_flutter::raiseAndActivate();
    }
}
void TitleBar_flutter_wrapper::raiseAndActivate_nocallback()
{
    ::KDDockWidgets::Views::TitleBar_flutter::raiseAndActivate();
}
void TitleBar_flutter_wrapper::releaseKeyboard()
{
    if (m_releaseKeyboardCallback) {
        const void *thisPtr = this;
        m_releaseKeyboardCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Views::TitleBar_flutter::releaseKeyboard();
    }
}
void TitleBar_flutter_wrapper::releaseKeyboard_nocallback()
{
    ::KDDockWidgets::Views::TitleBar_flutter::releaseKeyboard();
}
void TitleBar_flutter_wrapper::releaseMouse()
{
    if (m_releaseMouseCallback) {
        const void *thisPtr = this;
        m_releaseMouseCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Views::TitleBar_flutter::releaseMouse();
    }
}
void TitleBar_flutter_wrapper::releaseMouse_nocallback()
{
    ::KDDockWidgets::Views::TitleBar_flutter::releaseMouse();
}
void TitleBar_flutter_wrapper::setCursor(Qt::CursorShape shape)
{
    if (m_setCursorCallback) {
        const void *thisPtr = this;
        m_setCursorCallback(const_cast<void *>(thisPtr), shape);
    } else {
        ::KDDockWidgets::Views::TitleBar_flutter::setCursor(shape);
    }
}
void TitleBar_flutter_wrapper::setCursor_nocallback(Qt::CursorShape shape)
{
    ::KDDockWidgets::Views::TitleBar_flutter::setCursor(shape);
}
void TitleBar_flutter_wrapper::setFixedHeight(int h)
{
    if (m_setFixedHeightCallback) {
        const void *thisPtr = this;
        m_setFixedHeightCallback(const_cast<void *>(thisPtr), h);
    } else {
        ::KDDockWidgets::Views::TitleBar_flutter::setFixedHeight(h);
    }
}
void TitleBar_flutter_wrapper::setFixedHeight_nocallback(int h)
{
    ::KDDockWidgets::Views::TitleBar_flutter::setFixedHeight(h);
}
void TitleBar_flutter_wrapper::setFixedWidth(int w)
{
    if (m_setFixedWidthCallback) {
        const void *thisPtr = this;
        m_setFixedWidthCallback(const_cast<void *>(thisPtr), w);
    } else {
        ::KDDockWidgets::Views::TitleBar_flutter::setFixedWidth(w);
    }
}
void TitleBar_flutter_wrapper::setFixedWidth_nocallback(int w)
{
    ::KDDockWidgets::Views::TitleBar_flutter::setFixedWidth(w);
}
void TitleBar_flutter_wrapper::setGeometry(QRect geometry)
{
    if (m_setGeometryCallback) {
        const void *thisPtr = this;
        m_setGeometryCallback(const_cast<void *>(thisPtr), &geometry);
    } else {
        ::KDDockWidgets::Views::TitleBar_flutter::setGeometry(geometry);
    }
}
void TitleBar_flutter_wrapper::setGeometry_nocallback(QRect geometry)
{
    ::KDDockWidgets::Views::TitleBar_flutter::setGeometry(geometry);
}
void TitleBar_flutter_wrapper::setHeight(int h)
{
    if (m_setHeightCallback) {
        const void *thisPtr = this;
        m_setHeightCallback(const_cast<void *>(thisPtr), h);
    } else {
        ::KDDockWidgets::Views::TitleBar_flutter::setHeight(h);
    }
}
void TitleBar_flutter_wrapper::setHeight_nocallback(int h)
{
    ::KDDockWidgets::Views::TitleBar_flutter::setHeight(h);
}
void TitleBar_flutter_wrapper::setMaximumSize(QSize sz)
{
    if (m_setMaximumSizeCallback) {
        const void *thisPtr = this;
        m_setMaximumSizeCallback(const_cast<void *>(thisPtr), &sz);
    } else {
        ::KDDockWidgets::Views::TitleBar_flutter::setMaximumSize(sz);
    }
}
void TitleBar_flutter_wrapper::setMaximumSize_nocallback(QSize sz)
{
    ::KDDockWidgets::Views::TitleBar_flutter::setMaximumSize(sz);
}
void TitleBar_flutter_wrapper::setMinimumSize(QSize sz)
{
    if (m_setMinimumSizeCallback) {
        const void *thisPtr = this;
        m_setMinimumSizeCallback(const_cast<void *>(thisPtr), &sz);
    } else {
        ::KDDockWidgets::Views::TitleBar_flutter::setMinimumSize(sz);
    }
}
void TitleBar_flutter_wrapper::setMinimumSize_nocallback(QSize sz)
{
    ::KDDockWidgets::Views::TitleBar_flutter::setMinimumSize(sz);
}
void TitleBar_flutter_wrapper::setMouseTracking(bool enable)
{
    if (m_setMouseTrackingCallback) {
        const void *thisPtr = this;
        m_setMouseTrackingCallback(const_cast<void *>(thisPtr), enable);
    } else {
        ::KDDockWidgets::Views::TitleBar_flutter::setMouseTracking(enable);
    }
}
void TitleBar_flutter_wrapper::setMouseTracking_nocallback(bool enable)
{
    ::KDDockWidgets::Views::TitleBar_flutter::setMouseTracking(enable);
}
void TitleBar_flutter_wrapper::setObjectName(const QString &name)
{
    if (m_setObjectNameCallback) {
        const void *thisPtr = this;
        m_setObjectNameCallback(const_cast<void *>(thisPtr), name);
    } else {
        ::KDDockWidgets::Views::TitleBar_flutter::setObjectName(name);
    }
}
void TitleBar_flutter_wrapper::setObjectName_nocallback(const QString &name)
{
    ::KDDockWidgets::Views::TitleBar_flutter::setObjectName(name);
}
void TitleBar_flutter_wrapper::setParent(KDDockWidgets::View *parent)
{
    if (m_setParentCallback) {
        const void *thisPtr = this;
        m_setParentCallback(const_cast<void *>(thisPtr), parent);
    } else {
        ::KDDockWidgets::Views::TitleBar_flutter::setParent(parent);
    }
}
void TitleBar_flutter_wrapper::setParent_nocallback(KDDockWidgets::View *parent)
{
    ::KDDockWidgets::Views::TitleBar_flutter::setParent(parent);
}
void TitleBar_flutter_wrapper::setSize(int w, int h)
{
    if (m_setSize_2Callback) {
        const void *thisPtr = this;
        m_setSize_2Callback(const_cast<void *>(thisPtr), w, h);
    } else {
        ::KDDockWidgets::Views::TitleBar_flutter::setSize(w, h);
    }
}
void TitleBar_flutter_wrapper::setSize_nocallback(int w, int h)
{
    ::KDDockWidgets::Views::TitleBar_flutter::setSize(w, h);
}
void TitleBar_flutter_wrapper::setVisible(bool visible)
{
    if (m_setVisibleCallback) {
        const void *thisPtr = this;
        m_setVisibleCallback(const_cast<void *>(thisPtr), visible);
    } else {
        ::KDDockWidgets::Views::TitleBar_flutter::setVisible(visible);
    }
}
void TitleBar_flutter_wrapper::setVisible_nocallback(bool visible)
{
    ::KDDockWidgets::Views::TitleBar_flutter::setVisible(visible);
}
void TitleBar_flutter_wrapper::setWidth(int w)
{
    if (m_setWidthCallback) {
        const void *thisPtr = this;
        m_setWidthCallback(const_cast<void *>(thisPtr), w);
    } else {
        ::KDDockWidgets::Views::TitleBar_flutter::setWidth(w);
    }
}
void TitleBar_flutter_wrapper::setWidth_nocallback(int w)
{
    ::KDDockWidgets::Views::TitleBar_flutter::setWidth(w);
}
void TitleBar_flutter_wrapper::setWindowOpacity(double v)
{
    if (m_setWindowOpacityCallback) {
        const void *thisPtr = this;
        m_setWindowOpacityCallback(const_cast<void *>(thisPtr), v);
    } else {
        ::KDDockWidgets::Views::TitleBar_flutter::setWindowOpacity(v);
    }
}
void TitleBar_flutter_wrapper::setWindowOpacity_nocallback(double v)
{
    ::KDDockWidgets::Views::TitleBar_flutter::setWindowOpacity(v);
}
void TitleBar_flutter_wrapper::setWindowTitle(const QString &title)
{
    if (m_setWindowTitleCallback) {
        const void *thisPtr = this;
        m_setWindowTitleCallback(const_cast<void *>(thisPtr), title);
    } else {
        ::KDDockWidgets::Views::TitleBar_flutter::setWindowTitle(title);
    }
}
void TitleBar_flutter_wrapper::setWindowTitle_nocallback(const QString &title)
{
    ::KDDockWidgets::Views::TitleBar_flutter::setWindowTitle(title);
}
void TitleBar_flutter_wrapper::setZOrder(int z)
{
    if (m_setZOrderCallback) {
        const void *thisPtr = this;
        m_setZOrderCallback(const_cast<void *>(thisPtr), z);
    } else {
        ::KDDockWidgets::Views::TitleBar_flutter::setZOrder(z);
    }
}
void TitleBar_flutter_wrapper::setZOrder_nocallback(int z)
{
    ::KDDockWidgets::Views::TitleBar_flutter::setZOrder(z);
}
void TitleBar_flutter_wrapper::show()
{
    if (m_showCallback) {
        const void *thisPtr = this;
        m_showCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Views::TitleBar_flutter::show();
    }
}
void TitleBar_flutter_wrapper::show_nocallback()
{
    ::KDDockWidgets::Views::TitleBar_flutter::show();
}
void TitleBar_flutter_wrapper::showMaximized()
{
    if (m_showMaximizedCallback) {
        const void *thisPtr = this;
        m_showMaximizedCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Views::TitleBar_flutter::showMaximized();
    }
}
void TitleBar_flutter_wrapper::showMaximized_nocallback()
{
    ::KDDockWidgets::Views::TitleBar_flutter::showMaximized();
}
void TitleBar_flutter_wrapper::showMinimized()
{
    if (m_showMinimizedCallback) {
        const void *thisPtr = this;
        m_showMinimizedCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Views::TitleBar_flutter::showMinimized();
    }
}
void TitleBar_flutter_wrapper::showMinimized_nocallback()
{
    ::KDDockWidgets::Views::TitleBar_flutter::showMinimized();
}
void TitleBar_flutter_wrapper::showNormal()
{
    if (m_showNormalCallback) {
        const void *thisPtr = this;
        m_showNormalCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Views::TitleBar_flutter::showNormal();
    }
}
void TitleBar_flutter_wrapper::showNormal_nocallback()
{
    ::KDDockWidgets::Views::TitleBar_flutter::showNormal();
}
QSize TitleBar_flutter_wrapper::sizeHint() const
{
    if (m_sizeHintCallback) {
        const void *thisPtr = this;
        return *m_sizeHintCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::TitleBar_flutter::sizeHint();
    }
}
QSize TitleBar_flutter_wrapper::sizeHint_nocallback() const
{
    return ::KDDockWidgets::Views::TitleBar_flutter::sizeHint();
}
void TitleBar_flutter_wrapper::update()
{
    if (m_updateCallback) {
        const void *thisPtr = this;
        m_updateCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Views::TitleBar_flutter::update();
    }
}
void TitleBar_flutter_wrapper::update_nocallback()
{
    ::KDDockWidgets::Views::TitleBar_flutter::update();
}
TitleBar_flutter_wrapper::~TitleBar_flutter_wrapper()
{
}

}
static KDDockWidgets::Views::TitleBar_flutter *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::Views::TitleBar_flutter *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__Views__TitleBar_flutter_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(cppObj);
}
void *c_KDDockWidgets__Views__TitleBar_flutter__constructor_TitleBar_View(void *controller_,
                                                                          void *parent_)
{
    auto controller = reinterpret_cast<KDDockWidgets::Controllers::TitleBar *>(controller_);
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    auto ptr = new KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper(controller, parent);
    return reinterpret_cast<void *>(ptr);
}
// activateWindow()
void c_KDDockWidgets__Views__TitleBar_flutter__activateWindow(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->activateWindow_nocallback();
        } else {
            return targetPtr->activateWindow();
        }
    }();
}
// close()
bool c_KDDockWidgets__Views__TitleBar_flutter__close(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->close_nocallback();
        } else {
            return targetPtr->close();
        }
    }();
}
// createPlatformWindow()
void c_KDDockWidgets__Views__TitleBar_flutter__createPlatformWindow(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->createPlatformWindow_nocallback();
        } else {
            return targetPtr->createPlatformWindow();
        }
    }();
}
// flags() const
int c_KDDockWidgets__Views__TitleBar_flutter__flags(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->flags_nocallback();
        } else {
            return targetPtr->flags();
        }
    }();
}
// free_impl()
void c_KDDockWidgets__Views__TitleBar_flutter__free_impl(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->free_impl_nocallback();
        } else {
            return targetPtr->free_impl();
        }
    }();
}
// geometry() const
void *c_KDDockWidgets__Views__TitleBar_flutter__geometry(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QRect> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->geometry_nocallback();
        } else {
            return targetPtr->geometry();
        }
    }() };
}
// grabMouse()
void c_KDDockWidgets__Views__TitleBar_flutter__grabMouse(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->grabMouse_nocallback();
        } else {
            return targetPtr->grabMouse();
        }
    }();
}
// hasFocus() const
bool c_KDDockWidgets__Views__TitleBar_flutter__hasFocus(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->hasFocus_nocallback();
        } else {
            return targetPtr->hasFocus();
        }
    }();
}
// hide()
void c_KDDockWidgets__Views__TitleBar_flutter__hide(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->hide_nocallback();
        } else {
            return targetPtr->hide();
        }
    }();
}
// init()
void c_KDDockWidgets__Views__TitleBar_flutter__init(void *thisObj)
{
    fromWrapperPtr(thisObj)->init_nocallback();
}
// isActiveWindow() const
bool c_KDDockWidgets__Views__TitleBar_flutter__isActiveWindow(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->isActiveWindow_nocallback();
        } else {
            return targetPtr->isActiveWindow();
        }
    }();
}
// isCloseButtonEnabled() const
bool c_KDDockWidgets__Views__TitleBar_flutter__isCloseButtonEnabled(void *thisObj)
{
    return fromWrapperPtr(thisObj)->isCloseButtonEnabled_nocallback();
}
// isCloseButtonVisible() const
bool c_KDDockWidgets__Views__TitleBar_flutter__isCloseButtonVisible(void *thisObj)
{
    return fromWrapperPtr(thisObj)->isCloseButtonVisible_nocallback();
}
// isFloatButtonVisible() const
bool c_KDDockWidgets__Views__TitleBar_flutter__isFloatButtonVisible(void *thisObj)
{
    return fromWrapperPtr(thisObj)->isFloatButtonVisible_nocallback();
}
// isMaximized() const
bool c_KDDockWidgets__Views__TitleBar_flutter__isMaximized(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->isMaximized_nocallback();
        } else {
            return targetPtr->isMaximized();
        }
    }();
}
// isMinimized() const
bool c_KDDockWidgets__Views__TitleBar_flutter__isMinimized(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->isMinimized_nocallback();
        } else {
            return targetPtr->isMinimized();
        }
    }();
}
// isNull() const
bool c_KDDockWidgets__Views__TitleBar_flutter__isNull(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->isNull_nocallback();
        } else {
            return targetPtr->isNull();
        }
    }();
}
// isRootView() const
bool c_KDDockWidgets__Views__TitleBar_flutter__isRootView(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->isRootView_nocallback();
        } else {
            return targetPtr->isRootView();
        }
    }();
}
// isVisible() const
bool c_KDDockWidgets__Views__TitleBar_flutter__isVisible(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->isVisible_nocallback();
        } else {
            return targetPtr->isVisible();
        }
    }();
}
// mapFromGlobal(QPoint globalPt) const
void *c_KDDockWidgets__Views__TitleBar_flutter__mapFromGlobal_QPoint(void *thisObj, void *globalPt_)
{
    assert(globalPt_);
    auto &globalPt = *reinterpret_cast<QPoint *>(globalPt_);
    return new Dartagnan::ValueWrapper<QPoint> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->mapFromGlobal_nocallback(globalPt);
        } else {
            return targetPtr->mapFromGlobal(globalPt);
        }
    }() };
}
// mapTo(KDDockWidgets::View * parent, QPoint pos) const
void *c_KDDockWidgets__Views__TitleBar_flutter__mapTo_View_QPoint(void *thisObj, void *parent_,
                                                                  void *pos_)
{
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    assert(pos_);
    auto &pos = *reinterpret_cast<QPoint *>(pos_);
    return new Dartagnan::ValueWrapper<QPoint> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->mapTo_nocallback(parent, pos);
        } else {
            return targetPtr->mapTo(parent, pos);
        }
    }() };
}
// mapToGlobal(QPoint localPt) const
void *c_KDDockWidgets__Views__TitleBar_flutter__mapToGlobal_QPoint(void *thisObj, void *localPt_)
{
    assert(localPt_);
    auto &localPt = *reinterpret_cast<QPoint *>(localPt_);
    return new Dartagnan::ValueWrapper<QPoint> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->mapToGlobal_nocallback(localPt);
        } else {
            return targetPtr->mapToGlobal(localPt);
        }
    }() };
}
// maxSizeHint() const
void *c_KDDockWidgets__Views__TitleBar_flutter__maxSizeHint(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->maxSizeHint_nocallback();
        } else {
            return targetPtr->maxSizeHint();
        }
    }() };
}
// minSize() const
void *c_KDDockWidgets__Views__TitleBar_flutter__minSize(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->minSize_nocallback();
        } else {
            return targetPtr->minSize();
        }
    }() };
}
// minimumHeight() const
int c_KDDockWidgets__Views__TitleBar_flutter__minimumHeight(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->minimumHeight_nocallback();
        } else {
            return targetPtr->minimumHeight();
        }
    }();
}
// minimumWidth() const
int c_KDDockWidgets__Views__TitleBar_flutter__minimumWidth(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->minimumWidth_nocallback();
        } else {
            return targetPtr->minimumWidth();
        }
    }();
}
// move(int x, int y)
void c_KDDockWidgets__Views__TitleBar_flutter__move_int_int(void *thisObj, int x, int y)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->move_nocallback(x, y);
        } else {
            return targetPtr->move(x, y);
        }
    }();
}
// normalGeometry() const
void *c_KDDockWidgets__Views__TitleBar_flutter__normalGeometry(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QRect> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->normalGeometry_nocallback();
        } else {
            return targetPtr->normalGeometry();
        }
    }() };
}
// objectName() const
void *c_KDDockWidgets__Views__TitleBar_flutter__objectName(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QString> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->objectName_nocallback();
        } else {
            return targetPtr->objectName();
        }
    }() };
}
// onChildAdded(KDDockWidgets::View * childView)
void c_KDDockWidgets__Views__TitleBar_flutter__onChildAdded_View(void *thisObj, void *childView_)
{
    auto childView = reinterpret_cast<KDDockWidgets::View *>(childView_);
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->onChildAdded_nocallback(childView);
        } else {
            return targetPtr->onChildAdded(childView);
        }
    }();
}
// onChildRemoved(KDDockWidgets::View * childView)
void c_KDDockWidgets__Views__TitleBar_flutter__onChildRemoved_View(void *thisObj, void *childView_)
{
    auto childView = reinterpret_cast<KDDockWidgets::View *>(childView_);
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->onChildRemoved_nocallback(childView);
        } else {
            return targetPtr->onChildRemoved(childView);
        }
    }();
}
// onResize(int w, int h)
bool c_KDDockWidgets__Views__TitleBar_flutter__onResize_int_int(void *thisObj, int w, int h)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->onResize_nocallback(w, h);
        } else {
            return targetPtr->onResize(w, h);
        }
    }();
}
// raise()
void c_KDDockWidgets__Views__TitleBar_flutter__raise(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->raise_nocallback();
        } else {
            return targetPtr->raise();
        }
    }();
}
// raiseAndActivate()
void c_KDDockWidgets__Views__TitleBar_flutter__raiseAndActivate(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->raiseAndActivate_nocallback();
        } else {
            return targetPtr->raiseAndActivate();
        }
    }();
}
// releaseKeyboard()
void c_KDDockWidgets__Views__TitleBar_flutter__releaseKeyboard(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->releaseKeyboard_nocallback();
        } else {
            return targetPtr->releaseKeyboard();
        }
    }();
}
// releaseMouse()
void c_KDDockWidgets__Views__TitleBar_flutter__releaseMouse(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->releaseMouse_nocallback();
        } else {
            return targetPtr->releaseMouse();
        }
    }();
}
// setCursor(Qt::CursorShape shape)
void c_KDDockWidgets__Views__TitleBar_flutter__setCursor_CursorShape(void *thisObj, int shape)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setCursor_nocallback(static_cast<Qt::CursorShape>(shape));
        } else {
            return targetPtr->setCursor(static_cast<Qt::CursorShape>(shape));
        }
    }();
}
// setFixedHeight(int h)
void c_KDDockWidgets__Views__TitleBar_flutter__setFixedHeight_int(void *thisObj, int h)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setFixedHeight_nocallback(h);
        } else {
            return targetPtr->setFixedHeight(h);
        }
    }();
}
// setFixedWidth(int w)
void c_KDDockWidgets__Views__TitleBar_flutter__setFixedWidth_int(void *thisObj, int w)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setFixedWidth_nocallback(w);
        } else {
            return targetPtr->setFixedWidth(w);
        }
    }();
}
// setGeometry(QRect geometry)
void c_KDDockWidgets__Views__TitleBar_flutter__setGeometry_QRect(void *thisObj, void *geometry_)
{
    assert(geometry_);
    auto &geometry = *reinterpret_cast<QRect *>(geometry_);
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setGeometry_nocallback(geometry);
        } else {
            return targetPtr->setGeometry(geometry);
        }
    }();
}
// setHeight(int h)
void c_KDDockWidgets__Views__TitleBar_flutter__setHeight_int(void *thisObj, int h)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setHeight_nocallback(h);
        } else {
            return targetPtr->setHeight(h);
        }
    }();
}
// setMaximumSize(QSize sz)
void c_KDDockWidgets__Views__TitleBar_flutter__setMaximumSize_QSize(void *thisObj, void *sz_)
{
    assert(sz_);
    auto &sz = *reinterpret_cast<QSize *>(sz_);
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setMaximumSize_nocallback(sz);
        } else {
            return targetPtr->setMaximumSize(sz);
        }
    }();
}
// setMinimumSize(QSize sz)
void c_KDDockWidgets__Views__TitleBar_flutter__setMinimumSize_QSize(void *thisObj, void *sz_)
{
    assert(sz_);
    auto &sz = *reinterpret_cast<QSize *>(sz_);
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setMinimumSize_nocallback(sz);
        } else {
            return targetPtr->setMinimumSize(sz);
        }
    }();
}
// setMouseTracking(bool enable)
void c_KDDockWidgets__Views__TitleBar_flutter__setMouseTracking_bool(void *thisObj, bool enable)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setMouseTracking_nocallback(enable);
        } else {
            return targetPtr->setMouseTracking(enable);
        }
    }();
}
// setObjectName(const QString & name)
void c_KDDockWidgets__Views__TitleBar_flutter__setObjectName_QString(void *thisObj,
                                                                     const char *name_)
{
    const auto name = QString::fromUtf8(name_);
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setObjectName_nocallback(name);
        } else {
            return targetPtr->setObjectName(name);
        }
    }();
}
// setParent(KDDockWidgets::View * parent)
void c_KDDockWidgets__Views__TitleBar_flutter__setParent_View(void *thisObj, void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setParent_nocallback(parent);
        } else {
            return targetPtr->setParent(parent);
        }
    }();
}
// setSize(int w, int h)
void c_KDDockWidgets__Views__TitleBar_flutter__setSize_int_int(void *thisObj, int w, int h)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setSize_nocallback(w, h);
        } else {
            return targetPtr->setSize(w, h);
        }
    }();
}
// setVisible(bool visible)
void c_KDDockWidgets__Views__TitleBar_flutter__setVisible_bool(void *thisObj, bool visible)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setVisible_nocallback(visible);
        } else {
            return targetPtr->setVisible(visible);
        }
    }();
}
// setWidth(int w)
void c_KDDockWidgets__Views__TitleBar_flutter__setWidth_int(void *thisObj, int w)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setWidth_nocallback(w);
        } else {
            return targetPtr->setWidth(w);
        }
    }();
}
// setWindowOpacity(double v)
void c_KDDockWidgets__Views__TitleBar_flutter__setWindowOpacity_double(void *thisObj, double v)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setWindowOpacity_nocallback(v);
        } else {
            return targetPtr->setWindowOpacity(v);
        }
    }();
}
// setWindowTitle(const QString & title)
void c_KDDockWidgets__Views__TitleBar_flutter__setWindowTitle_QString(void *thisObj,
                                                                      const char *title_)
{
    const auto title = QString::fromUtf8(title_);
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setWindowTitle_nocallback(title);
        } else {
            return targetPtr->setWindowTitle(title);
        }
    }();
}
// setZOrder(int z)
void c_KDDockWidgets__Views__TitleBar_flutter__setZOrder_int(void *thisObj, int z)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setZOrder_nocallback(z);
        } else {
            return targetPtr->setZOrder(z);
        }
    }();
}
// show()
void c_KDDockWidgets__Views__TitleBar_flutter__show(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->show_nocallback();
        } else {
            return targetPtr->show();
        }
    }();
}
// showMaximized()
void c_KDDockWidgets__Views__TitleBar_flutter__showMaximized(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->showMaximized_nocallback();
        } else {
            return targetPtr->showMaximized();
        }
    }();
}
// showMinimized()
void c_KDDockWidgets__Views__TitleBar_flutter__showMinimized(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->showMinimized_nocallback();
        } else {
            return targetPtr->showMinimized();
        }
    }();
}
// showNormal()
void c_KDDockWidgets__Views__TitleBar_flutter__showNormal(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->showNormal_nocallback();
        } else {
            return targetPtr->showNormal();
        }
    }();
}
// sizeHint() const
void *c_KDDockWidgets__Views__TitleBar_flutter__sizeHint(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->sizeHint_nocallback();
        } else {
            return targetPtr->sizeHint();
        }
    }() };
}
// update()
void c_KDDockWidgets__Views__TitleBar_flutter__update(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->update_nocallback();
        } else {
            return targetPtr->update();
        }
    }();
}
void c_KDDockWidgets__Views__TitleBar_flutter__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__Views__TitleBar_flutter__registerVirtualMethodCallback(void *ptr,
                                                                             void *callback,
                                                                             int methodId)
{
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 843:
        wrapper->m_activateWindowCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_activateWindow>(
            callback);
        break;
    case 854:
        wrapper->m_closeCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_close>(callback);
        break;
    case 857:
        wrapper->m_createPlatformWindowCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::
                                 Callback_createPlatformWindow>(callback);
        break;
    case 862:
        wrapper->m_flagsCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_flags>(callback);
        break;
    case 864:
        wrapper->m_free_implCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_free_impl>(
            callback);
        break;
    case 866:
        wrapper->m_geometryCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_geometry>(
            callback);
        break;
    case 868:
        wrapper->m_grabMouseCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_grabMouse>(
            callback);
        break;
    case 871:
        wrapper->m_hasFocusCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_hasFocus>(
            callback);
        break;
    case 873:
        wrapper->m_hideCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_hide>(callback);
        break;
    case 876:
        wrapper->m_initCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_init>(callback);
        break;
    case 878:
        wrapper->m_isActiveWindowCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_isActiveWindow>(
            callback);
        break;
    case 978:
        wrapper->m_isCloseButtonEnabledCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::
                                 Callback_isCloseButtonEnabled>(callback);
        break;
    case 979:
        wrapper->m_isCloseButtonVisibleCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::
                                 Callback_isCloseButtonVisible>(callback);
        break;
    case 980:
        wrapper->m_isFloatButtonVisibleCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::
                                 Callback_isFloatButtonVisible>(callback);
        break;
    case 879:
        wrapper->m_isMaximizedCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_isMaximized>(
            callback);
        break;
    case 880:
        wrapper->m_isMinimizedCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_isMinimized>(
            callback);
        break;
    case 881:
        wrapper->m_isNullCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_isNull>(callback);
        break;
    case 882:
        wrapper->m_isRootViewCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_isRootView>(
            callback);
        break;
    case 883:
        wrapper->m_isVisibleCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_isVisible>(
            callback);
        break;
    case 884:
        wrapper->m_mapFromGlobalCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_mapFromGlobal>(
            callback);
        break;
    case 885:
        wrapper->m_mapToCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_mapTo>(callback);
        break;
    case 886:
        wrapper->m_mapToGlobalCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_mapToGlobal>(
            callback);
        break;
    case 887:
        wrapper->m_maxSizeHintCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_maxSizeHint>(
            callback);
        break;
    case 888:
        wrapper->m_minSizeCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_minSize>(callback);
        break;
    case 889:
        wrapper->m_minimumHeightCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_minimumHeight>(
            callback);
        break;
    case 890:
        wrapper->m_minimumWidthCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_minimumWidth>(
            callback);
        break;
    case 892:
        wrapper->m_move_2Callback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_move_2>(callback);
        break;
    case 893:
        wrapper->m_normalGeometryCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_normalGeometry>(
            callback);
        break;
    case 894:
        wrapper->m_objectNameCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_objectName>(
            callback);
        break;
    case 961:
        wrapper->m_onChildAddedCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_onChildAdded>(
            callback);
        break;
    case 962:
        wrapper->m_onChildRemovedCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_onChildRemoved>(
            callback);
        break;
    case 896:
        wrapper->m_onResize_2Callback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_onResize_2>(
            callback);
        break;
    case 899:
        wrapper->m_raiseCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_raise>(callback);
        break;
    case 900:
        wrapper->m_raiseAndActivateCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_raiseAndActivate>(
            callback);
        break;
    case 902:
        wrapper->m_releaseKeyboardCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_releaseKeyboard>(
            callback);
        break;
    case 903:
        wrapper->m_releaseMouseCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_releaseMouse>(
            callback);
        break;
    case 907:
        wrapper->m_setCursorCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_setCursor>(
            callback);
        break;
    case 908:
        wrapper->m_setFixedHeightCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_setFixedHeight>(
            callback);
        break;
    case 909:
        wrapper->m_setFixedWidthCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_setFixedWidth>(
            callback);
        break;
    case 910:
        wrapper->m_setGeometryCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_setGeometry>(
            callback);
        break;
    case 911:
        wrapper->m_setHeightCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_setHeight>(
            callback);
        break;
    case 912:
        wrapper->m_setMaximumSizeCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_setMaximumSize>(
            callback);
        break;
    case 913:
        wrapper->m_setMinimumSizeCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_setMinimumSize>(
            callback);
        break;
    case 914:
        wrapper->m_setMouseTrackingCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_setMouseTracking>(
            callback);
        break;
    case 915:
        wrapper->m_setObjectNameCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_setObjectName>(
            callback);
        break;
    case 916:
        wrapper->m_setParentCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_setParent>(
            callback);
        break;
    case 918:
        wrapper->m_setSize_2Callback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_setSize_2>(
            callback);
        break;
    case 919:
        wrapper->m_setVisibleCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_setVisible>(
            callback);
        break;
    case 920:
        wrapper->m_setWidthCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_setWidth>(
            callback);
        break;
    case 921:
        wrapper->m_setWindowOpacityCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_setWindowOpacity>(
            callback);
        break;
    case 922:
        wrapper->m_setWindowTitleCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_setWindowTitle>(
            callback);
        break;
    case 923:
        wrapper->m_setZOrderCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_setZOrder>(
            callback);
        break;
    case 924:
        wrapper->m_showCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_show>(callback);
        break;
    case 925:
        wrapper->m_showMaximizedCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_showMaximized>(
            callback);
        break;
    case 926:
        wrapper->m_showMinimizedCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_showMinimized>(
            callback);
        break;
    case 927:
        wrapper->m_showNormalCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_showNormal>(
            callback);
        break;
    case 929:
        wrapper->m_sizeHintCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_sizeHint>(
            callback);
        break;
    case 931:
        wrapper->m_updateCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::TitleBar_flutter_wrapper::Callback_update>(callback);
        break;
    }
}
}

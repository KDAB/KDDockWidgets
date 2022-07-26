/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "View_flutter_wrapper.h"


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
void View_flutter_wrapper::activateWindow()
{
    // tag=1000
    if (m_activateWindowCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_activateWindowCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        ::KDDockWidgets::Views::View_flutter::activateWindow();
    }
}
// tag=1009
void View_flutter_wrapper::activateWindow_nocallback()
{
    // tag=1003
    ::KDDockWidgets::Views::View_flutter::activateWindow();
}
bool View_flutter_wrapper::close()
{
    // tag=1000
    if (m_closeCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_closeCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        return ::KDDockWidgets::Views::View_flutter::close();
    }
}
// tag=1009
bool View_flutter_wrapper::close_nocallback()
{
    // tag=1003
    return ::KDDockWidgets::Views::View_flutter::close();
}
void View_flutter_wrapper::createPlatformWindow()
{
    // tag=1000
    if (m_createPlatformWindowCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_createPlatformWindowCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        ::KDDockWidgets::Views::View_flutter::createPlatformWindow();
    }
}
// tag=1009
void View_flutter_wrapper::createPlatformWindow_nocallback()
{
    // tag=1003
    ::KDDockWidgets::Views::View_flutter::createPlatformWindow();
}
void View_flutter_wrapper::free_impl()
{
    // tag=1000
    if (m_free_implCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_free_implCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        ::KDDockWidgets::Views::View_flutter::free_impl();
    }
}
// tag=1009
void View_flutter_wrapper::free_impl_nocallback()
{
    // tag=1003
    ::KDDockWidgets::Views::View_flutter::free_impl();
}
QRect View_flutter_wrapper::geometry() const
{
    // tag=1000
    if (m_geometryCallback) {
        // tag=1001
        const void *thisPtr = this;
        return *m_geometryCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        return ::KDDockWidgets::Views::View_flutter::geometry();
    }
}
// tag=1009
QRect View_flutter_wrapper::geometry_nocallback() const
{
    // tag=1003
    return ::KDDockWidgets::Views::View_flutter::geometry();
}
void View_flutter_wrapper::grabMouse()
{
    // tag=1000
    if (m_grabMouseCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_grabMouseCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        ::KDDockWidgets::Views::View_flutter::grabMouse();
    }
}
// tag=1009
void View_flutter_wrapper::grabMouse_nocallback()
{
    // tag=1003
    ::KDDockWidgets::Views::View_flutter::grabMouse();
}
bool View_flutter_wrapper::hasFocus() const
{
    // tag=1000
    if (m_hasFocusCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_hasFocusCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        return ::KDDockWidgets::Views::View_flutter::hasFocus();
    }
}
// tag=1009
bool View_flutter_wrapper::hasFocus_nocallback() const
{
    // tag=1003
    return ::KDDockWidgets::Views::View_flutter::hasFocus();
}
void View_flutter_wrapper::hide()
{
    // tag=1000
    if (m_hideCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_hideCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        ::KDDockWidgets::Views::View_flutter::hide();
    }
}
// tag=1009
void View_flutter_wrapper::hide_nocallback()
{
    // tag=1003
    ::KDDockWidgets::Views::View_flutter::hide();
}
void View_flutter_wrapper::init()
{
    // tag=1000
    if (m_initCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_initCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        ::KDDockWidgets::Views::View_flutter::init();
    }
}
// tag=1009
void View_flutter_wrapper::init_nocallback()
{
    // tag=1003
    ::KDDockWidgets::Views::View_flutter::init();
}
bool View_flutter_wrapper::isActiveWindow() const
{
    // tag=1000
    if (m_isActiveWindowCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_isActiveWindowCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        return ::KDDockWidgets::Views::View_flutter::isActiveWindow();
    }
}
// tag=1009
bool View_flutter_wrapper::isActiveWindow_nocallback() const
{
    // tag=1003
    return ::KDDockWidgets::Views::View_flutter::isActiveWindow();
}
bool View_flutter_wrapper::isMaximized() const
{
    // tag=1000
    if (m_isMaximizedCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_isMaximizedCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        return ::KDDockWidgets::Views::View_flutter::isMaximized();
    }
}
// tag=1009
bool View_flutter_wrapper::isMaximized_nocallback() const
{
    // tag=1003
    return ::KDDockWidgets::Views::View_flutter::isMaximized();
}
bool View_flutter_wrapper::isMinimized() const
{
    // tag=1000
    if (m_isMinimizedCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_isMinimizedCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        return ::KDDockWidgets::Views::View_flutter::isMinimized();
    }
}
// tag=1009
bool View_flutter_wrapper::isMinimized_nocallback() const
{
    // tag=1003
    return ::KDDockWidgets::Views::View_flutter::isMinimized();
}
bool View_flutter_wrapper::isNull() const
{
    // tag=1000
    if (m_isNullCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_isNullCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        return ::KDDockWidgets::Views::View_flutter::isNull();
    }
}
// tag=1009
bool View_flutter_wrapper::isNull_nocallback() const
{
    // tag=1003
    return ::KDDockWidgets::Views::View_flutter::isNull();
}
bool View_flutter_wrapper::isRootView() const
{
    // tag=1000
    if (m_isRootViewCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_isRootViewCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        return ::KDDockWidgets::Views::View_flutter::isRootView();
    }
}
// tag=1009
bool View_flutter_wrapper::isRootView_nocallback() const
{
    // tag=1003
    return ::KDDockWidgets::Views::View_flutter::isRootView();
}
bool View_flutter_wrapper::isVisible() const
{
    // tag=1000
    if (m_isVisibleCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_isVisibleCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        return ::KDDockWidgets::Views::View_flutter::isVisible();
    }
}
// tag=1009
bool View_flutter_wrapper::isVisible_nocallback() const
{
    // tag=1003
    return ::KDDockWidgets::Views::View_flutter::isVisible();
}
QPoint View_flutter_wrapper::mapFromGlobal(QPoint globalPt) const
{
    // tag=1000
    if (m_mapFromGlobalCallback) {
        // tag=1001
        const void *thisPtr = this;
        return *m_mapFromGlobalCallback(const_cast<void *>(thisPtr), globalPt);
    } else {
        // tag=1002
        return ::KDDockWidgets::Views::View_flutter::mapFromGlobal(globalPt);
    }
}
// tag=1009
QPoint View_flutter_wrapper::mapFromGlobal_nocallback(QPoint globalPt) const
{
    // tag=1003
    return ::KDDockWidgets::Views::View_flutter::mapFromGlobal(globalPt);
}
QPoint View_flutter_wrapper::mapTo(KDDockWidgets::View *parent, QPoint pos) const
{
    // tag=1000
    if (m_mapToCallback) {
        // tag=1001
        const void *thisPtr = this;
        return *m_mapToCallback(const_cast<void *>(thisPtr), parent, pos);
    } else {
        // tag=1002
        return ::KDDockWidgets::Views::View_flutter::mapTo(parent, pos);
    }
}
// tag=1009
QPoint View_flutter_wrapper::mapTo_nocallback(KDDockWidgets::View *parent, QPoint pos) const
{
    // tag=1003
    return ::KDDockWidgets::Views::View_flutter::mapTo(parent, pos);
}
QPoint View_flutter_wrapper::mapToGlobal(QPoint localPt) const
{
    // tag=1000
    if (m_mapToGlobalCallback) {
        // tag=1001
        const void *thisPtr = this;
        return *m_mapToGlobalCallback(const_cast<void *>(thisPtr), localPt);
    } else {
        // tag=1002
        return ::KDDockWidgets::Views::View_flutter::mapToGlobal(localPt);
    }
}
// tag=1009
QPoint View_flutter_wrapper::mapToGlobal_nocallback(QPoint localPt) const
{
    // tag=1003
    return ::KDDockWidgets::Views::View_flutter::mapToGlobal(localPt);
}
QSize View_flutter_wrapper::maxSizeHint() const
{
    // tag=1000
    if (m_maxSizeHintCallback) {
        // tag=1001
        const void *thisPtr = this;
        return *m_maxSizeHintCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        return ::KDDockWidgets::Views::View_flutter::maxSizeHint();
    }
}
// tag=1009
QSize View_flutter_wrapper::maxSizeHint_nocallback() const
{
    // tag=1003
    return ::KDDockWidgets::Views::View_flutter::maxSizeHint();
}
QSize View_flutter_wrapper::maximumSize() const
{
    // tag=1000
    if (m_maximumSizeCallback) {
        // tag=1001
        const void *thisPtr = this;
        return *m_maximumSizeCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        return ::KDDockWidgets::Views::View_flutter::maximumSize();
    }
}
// tag=1009
QSize View_flutter_wrapper::maximumSize_nocallback() const
{
    // tag=1003
    return ::KDDockWidgets::Views::View_flutter::maximumSize();
}
QSize View_flutter_wrapper::minSize() const
{
    // tag=1000
    if (m_minSizeCallback) {
        // tag=1001
        const void *thisPtr = this;
        return *m_minSizeCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        return ::KDDockWidgets::Views::View_flutter::minSize();
    }
}
// tag=1009
QSize View_flutter_wrapper::minSize_nocallback() const
{
    // tag=1003
    return ::KDDockWidgets::Views::View_flutter::minSize();
}
int View_flutter_wrapper::minimumHeight() const
{
    // tag=1000
    if (m_minimumHeightCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_minimumHeightCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        return ::KDDockWidgets::Views::View_flutter::minimumHeight();
    }
}
// tag=1009
int View_flutter_wrapper::minimumHeight_nocallback() const
{
    // tag=1003
    return ::KDDockWidgets::Views::View_flutter::minimumHeight();
}
int View_flutter_wrapper::minimumWidth() const
{
    // tag=1000
    if (m_minimumWidthCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_minimumWidthCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        return ::KDDockWidgets::Views::View_flutter::minimumWidth();
    }
}
// tag=1009
int View_flutter_wrapper::minimumWidth_nocallback() const
{
    // tag=1003
    return ::KDDockWidgets::Views::View_flutter::minimumWidth();
}
void View_flutter_wrapper::move(int x, int y)
{
    // tag=1000
    if (m_move_2Callback) {
        // tag=1001
        const void *thisPtr = this;
        m_move_2Callback(const_cast<void *>(thisPtr), x, y);
    } else {
        // tag=1002
        ::KDDockWidgets::Views::View_flutter::move(x, y);
    }
}
// tag=1009
void View_flutter_wrapper::move_nocallback(int x, int y)
{
    // tag=1003
    ::KDDockWidgets::Views::View_flutter::move(x, y);
}
QRect View_flutter_wrapper::normalGeometry() const
{
    // tag=1000
    if (m_normalGeometryCallback) {
        // tag=1001
        const void *thisPtr = this;
        return *m_normalGeometryCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        return ::KDDockWidgets::Views::View_flutter::normalGeometry();
    }
}
// tag=1009
QRect View_flutter_wrapper::normalGeometry_nocallback() const
{
    // tag=1003
    return ::KDDockWidgets::Views::View_flutter::normalGeometry();
}
QString View_flutter_wrapper::objectName() const
{
    // tag=1000
    if (m_objectNameCallback) {
        // tag=1001
        const void *thisPtr = this;
        return *m_objectNameCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        return ::KDDockWidgets::Views::View_flutter::objectName();
    }
}
// tag=1009
QString View_flutter_wrapper::objectName_nocallback() const
{
    // tag=1003
    return ::KDDockWidgets::Views::View_flutter::objectName();
}
bool View_flutter_wrapper::onResize(QSize newSize)
{
    // tag=1000
    if (m_onResizeCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_onResizeCallback(const_cast<void *>(thisPtr), newSize);
    } else {
        // tag=1002
        return ::KDDockWidgets::Views::View_flutter::onResize(newSize);
    }
}
// tag=1009
bool View_flutter_wrapper::onResize_nocallback(QSize newSize)
{
    // tag=1003
    return ::KDDockWidgets::Views::View_flutter::onResize(newSize);
}
void View_flutter_wrapper::raise()
{
    // tag=1000
    if (m_raiseCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_raiseCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        ::KDDockWidgets::Views::View_flutter::raise();
    }
}
// tag=1009
void View_flutter_wrapper::raise_nocallback()
{
    // tag=1003
    ::KDDockWidgets::Views::View_flutter::raise();
}
void View_flutter_wrapper::raiseAndActivate()
{
    // tag=1000
    if (m_raiseAndActivateCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_raiseAndActivateCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        ::KDDockWidgets::Views::View_flutter::raiseAndActivate();
    }
}
// tag=1009
void View_flutter_wrapper::raiseAndActivate_nocallback()
{
    // tag=1003
    ::KDDockWidgets::Views::View_flutter::raiseAndActivate();
}
void View_flutter_wrapper::releaseKeyboard()
{
    // tag=1000
    if (m_releaseKeyboardCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_releaseKeyboardCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        ::KDDockWidgets::Views::View_flutter::releaseKeyboard();
    }
}
// tag=1009
void View_flutter_wrapper::releaseKeyboard_nocallback()
{
    // tag=1003
    ::KDDockWidgets::Views::View_flutter::releaseKeyboard();
}
void View_flutter_wrapper::releaseMouse()
{
    // tag=1000
    if (m_releaseMouseCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_releaseMouseCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        ::KDDockWidgets::Views::View_flutter::releaseMouse();
    }
}
// tag=1009
void View_flutter_wrapper::releaseMouse_nocallback()
{
    // tag=1003
    ::KDDockWidgets::Views::View_flutter::releaseMouse();
}
void View_flutter_wrapper::setCursor(Qt::CursorShape shape)
{
    // tag=1000
    if (m_setCursorCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setCursorCallback(const_cast<void *>(thisPtr), shape);
    } else {
        // tag=1002
        ::KDDockWidgets::Views::View_flutter::setCursor(shape);
    }
}
// tag=1009
void View_flutter_wrapper::setCursor_nocallback(Qt::CursorShape shape)
{
    // tag=1003
    ::KDDockWidgets::Views::View_flutter::setCursor(shape);
}
void View_flutter_wrapper::setFixedHeight(int h)
{
    // tag=1000
    if (m_setFixedHeightCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setFixedHeightCallback(const_cast<void *>(thisPtr), h);
    } else {
        // tag=1002
        ::KDDockWidgets::Views::View_flutter::setFixedHeight(h);
    }
}
// tag=1009
void View_flutter_wrapper::setFixedHeight_nocallback(int h)
{
    // tag=1003
    ::KDDockWidgets::Views::View_flutter::setFixedHeight(h);
}
void View_flutter_wrapper::setFixedWidth(int w)
{
    // tag=1000
    if (m_setFixedWidthCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setFixedWidthCallback(const_cast<void *>(thisPtr), w);
    } else {
        // tag=1002
        ::KDDockWidgets::Views::View_flutter::setFixedWidth(w);
    }
}
// tag=1009
void View_flutter_wrapper::setFixedWidth_nocallback(int w)
{
    // tag=1003
    ::KDDockWidgets::Views::View_flutter::setFixedWidth(w);
}
void View_flutter_wrapper::setGeometry(QRect arg__1)
{
    // tag=1000
    if (m_setGeometryCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setGeometryCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        // tag=1002
        ::KDDockWidgets::Views::View_flutter::setGeometry(arg__1);
    }
}
// tag=1009
void View_flutter_wrapper::setGeometry_nocallback(QRect arg__1)
{
    // tag=1003
    ::KDDockWidgets::Views::View_flutter::setGeometry(arg__1);
}
void View_flutter_wrapper::setHeight(int h)
{
    // tag=1000
    if (m_setHeightCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setHeightCallback(const_cast<void *>(thisPtr), h);
    } else {
        // tag=1002
        ::KDDockWidgets::Views::View_flutter::setHeight(h);
    }
}
// tag=1009
void View_flutter_wrapper::setHeight_nocallback(int h)
{
    // tag=1003
    ::KDDockWidgets::Views::View_flutter::setHeight(h);
}
void View_flutter_wrapper::setMaximumSize(QSize sz)
{
    // tag=1000
    if (m_setMaximumSizeCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setMaximumSizeCallback(const_cast<void *>(thisPtr), sz);
    } else {
        // tag=1002
        ::KDDockWidgets::Views::View_flutter::setMaximumSize(sz);
    }
}
// tag=1009
void View_flutter_wrapper::setMaximumSize_nocallback(QSize sz)
{
    // tag=1003
    ::KDDockWidgets::Views::View_flutter::setMaximumSize(sz);
}
void View_flutter_wrapper::setMinimumSize(QSize sz)
{
    // tag=1000
    if (m_setMinimumSizeCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setMinimumSizeCallback(const_cast<void *>(thisPtr), sz);
    } else {
        // tag=1002
        ::KDDockWidgets::Views::View_flutter::setMinimumSize(sz);
    }
}
// tag=1009
void View_flutter_wrapper::setMinimumSize_nocallback(QSize sz)
{
    // tag=1003
    ::KDDockWidgets::Views::View_flutter::setMinimumSize(sz);
}
void View_flutter_wrapper::setMouseTracking(bool enable)
{
    // tag=1000
    if (m_setMouseTrackingCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setMouseTrackingCallback(const_cast<void *>(thisPtr), enable);
    } else {
        // tag=1002
        ::KDDockWidgets::Views::View_flutter::setMouseTracking(enable);
    }
}
// tag=1009
void View_flutter_wrapper::setMouseTracking_nocallback(bool enable)
{
    // tag=1003
    ::KDDockWidgets::Views::View_flutter::setMouseTracking(enable);
}
void View_flutter_wrapper::setNormalGeometry(QRect geo)
{
    // tag=1000

    // tag=1004
    ::KDDockWidgets::Views::View_flutter::setNormalGeometry(geo);
}
void View_flutter_wrapper::setObjectName(const QString &name)
{
    // tag=1000
    if (m_setObjectNameCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setObjectNameCallback(const_cast<void *>(thisPtr), name);
    } else {
        // tag=1002
        ::KDDockWidgets::Views::View_flutter::setObjectName(name);
    }
}
// tag=1009
void View_flutter_wrapper::setObjectName_nocallback(const QString &name)
{
    // tag=1003
    ::KDDockWidgets::Views::View_flutter::setObjectName(name);
}
void View_flutter_wrapper::setParent(KDDockWidgets::View *parent)
{
    // tag=1000
    if (m_setParentCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setParentCallback(const_cast<void *>(thisPtr), parent);
    } else {
        // tag=1002
        ::KDDockWidgets::Views::View_flutter::setParent(parent);
    }
}
// tag=1009
void View_flutter_wrapper::setParent_nocallback(KDDockWidgets::View *parent)
{
    // tag=1003
    ::KDDockWidgets::Views::View_flutter::setParent(parent);
}
void View_flutter_wrapper::setSize(int w, int h)
{
    // tag=1000
    if (m_setSize_2Callback) {
        // tag=1001
        const void *thisPtr = this;
        m_setSize_2Callback(const_cast<void *>(thisPtr), w, h);
    } else {
        // tag=1002
        ::KDDockWidgets::Views::View_flutter::setSize(w, h);
    }
}
// tag=1009
void View_flutter_wrapper::setSize_nocallback(int w, int h)
{
    // tag=1003
    ::KDDockWidgets::Views::View_flutter::setSize(w, h);
}
void View_flutter_wrapper::setVisible(bool visible)
{
    // tag=1000
    if (m_setVisibleCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setVisibleCallback(const_cast<void *>(thisPtr), visible);
    } else {
        // tag=1002
        ::KDDockWidgets::Views::View_flutter::setVisible(visible);
    }
}
// tag=1009
void View_flutter_wrapper::setVisible_nocallback(bool visible)
{
    // tag=1003
    ::KDDockWidgets::Views::View_flutter::setVisible(visible);
}
void View_flutter_wrapper::setWidth(int w)
{
    // tag=1000
    if (m_setWidthCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setWidthCallback(const_cast<void *>(thisPtr), w);
    } else {
        // tag=1002
        ::KDDockWidgets::Views::View_flutter::setWidth(w);
    }
}
// tag=1009
void View_flutter_wrapper::setWidth_nocallback(int w)
{
    // tag=1003
    ::KDDockWidgets::Views::View_flutter::setWidth(w);
}
void View_flutter_wrapper::setWindowOpacity(double v)
{
    // tag=1000
    if (m_setWindowOpacityCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setWindowOpacityCallback(const_cast<void *>(thisPtr), v);
    } else {
        // tag=1002
        ::KDDockWidgets::Views::View_flutter::setWindowOpacity(v);
    }
}
// tag=1009
void View_flutter_wrapper::setWindowOpacity_nocallback(double v)
{
    // tag=1003
    ::KDDockWidgets::Views::View_flutter::setWindowOpacity(v);
}
void View_flutter_wrapper::setWindowTitle(const QString &title)
{
    // tag=1000
    if (m_setWindowTitleCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setWindowTitleCallback(const_cast<void *>(thisPtr), title);
    } else {
        // tag=1002
        ::KDDockWidgets::Views::View_flutter::setWindowTitle(title);
    }
}
// tag=1009
void View_flutter_wrapper::setWindowTitle_nocallback(const QString &title)
{
    // tag=1003
    ::KDDockWidgets::Views::View_flutter::setWindowTitle(title);
}
void View_flutter_wrapper::setZOrder(int arg__1)
{
    // tag=1000
    if (m_setZOrderCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setZOrderCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        // tag=1002
        ::KDDockWidgets::Views::View_flutter::setZOrder(arg__1);
    }
}
// tag=1009
void View_flutter_wrapper::setZOrder_nocallback(int arg__1)
{
    // tag=1003
    ::KDDockWidgets::Views::View_flutter::setZOrder(arg__1);
}
void View_flutter_wrapper::show()
{
    // tag=1000
    if (m_showCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_showCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        ::KDDockWidgets::Views::View_flutter::show();
    }
}
// tag=1009
void View_flutter_wrapper::show_nocallback()
{
    // tag=1003
    ::KDDockWidgets::Views::View_flutter::show();
}
void View_flutter_wrapper::showMaximized()
{
    // tag=1000
    if (m_showMaximizedCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_showMaximizedCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        ::KDDockWidgets::Views::View_flutter::showMaximized();
    }
}
// tag=1009
void View_flutter_wrapper::showMaximized_nocallback()
{
    // tag=1003
    ::KDDockWidgets::Views::View_flutter::showMaximized();
}
void View_flutter_wrapper::showMinimized()
{
    // tag=1000
    if (m_showMinimizedCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_showMinimizedCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        ::KDDockWidgets::Views::View_flutter::showMinimized();
    }
}
// tag=1009
void View_flutter_wrapper::showMinimized_nocallback()
{
    // tag=1003
    ::KDDockWidgets::Views::View_flutter::showMinimized();
}
void View_flutter_wrapper::showNormal()
{
    // tag=1000
    if (m_showNormalCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_showNormalCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        ::KDDockWidgets::Views::View_flutter::showNormal();
    }
}
// tag=1009
void View_flutter_wrapper::showNormal_nocallback()
{
    // tag=1003
    ::KDDockWidgets::Views::View_flutter::showNormal();
}
QSize View_flutter_wrapper::sizeHint() const
{
    // tag=1000
    if (m_sizeHintCallback) {
        // tag=1001
        const void *thisPtr = this;
        return *m_sizeHintCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        return ::KDDockWidgets::Views::View_flutter::sizeHint();
    }
}
// tag=1009
QSize View_flutter_wrapper::sizeHint_nocallback() const
{
    // tag=1003
    return ::KDDockWidgets::Views::View_flutter::sizeHint();
}
void View_flutter_wrapper::update()
{
    // tag=1000
    if (m_updateCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_updateCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        ::KDDockWidgets::Views::View_flutter::update();
    }
}
// tag=1009
void View_flutter_wrapper::update_nocallback()
{
    // tag=1003
    ::KDDockWidgets::Views::View_flutter::update();
}
void View_flutter_wrapper::updateGeometry()
{
    // tag=1000

    // tag=1004
    ::KDDockWidgets::Views::View_flutter::updateGeometry();
}

// tag=1005
View_flutter_wrapper::~View_flutter_wrapper()
{
}

}
// tag=1013
static KDDockWidgets::Views::View_flutter *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::Views::View_flutter *>(ptr);
}
// tag=1014
static KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper *>(ptr);
}
extern "C" {

// tag=1049
void c_KDDockWidgets__Views__View_flutter_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper *>(cppObj);
}
// tag=1050
// activateWindow()
void c_KDDockWidgets__Views__View_flutter__activateWindow(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->activateWindow_nocallback();} else {    return targetPtr->activateWindow();} }();
}

// tag=1050
// close()
bool c_KDDockWidgets__Views__View_flutter__close(void *thisObj)
{
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->close_nocallback();} else {    return targetPtr->close();} }();
}

// tag=1050
// createPlatformWindow()
void c_KDDockWidgets__Views__View_flutter__createPlatformWindow(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->createPlatformWindow_nocallback();} else {    return targetPtr->createPlatformWindow();} }();
}

// tag=1050
// free_impl()
void c_KDDockWidgets__Views__View_flutter__free_impl(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->free_impl_nocallback();} else {    return targetPtr->free_impl();} }();
}

// tag=1050
// geometry() const
void *c_KDDockWidgets__Views__View_flutter__geometry(void *thisObj)
{
    return
        // tag=1016

        // tag=1072
        new Dartagnan::ValueWrapper<QRect> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->geometry_nocallback();} else {    return targetPtr->geometry();} }() };
}

// tag=1050
// grabMouse()
void c_KDDockWidgets__Views__View_flutter__grabMouse(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->grabMouse_nocallback();} else {    return targetPtr->grabMouse();} }();
}

// tag=1050
// hasFocus() const
bool c_KDDockWidgets__Views__View_flutter__hasFocus(void *thisObj)
{
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->hasFocus_nocallback();} else {    return targetPtr->hasFocus();} }();
}

// tag=1050
// hide()
void c_KDDockWidgets__Views__View_flutter__hide(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->hide_nocallback();} else {    return targetPtr->hide();} }();
}

// tag=1050
// init()
void c_KDDockWidgets__Views__View_flutter__init(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->init_nocallback();} else {    return targetPtr->init();} }();
}

// tag=1050
// isActiveWindow() const
bool c_KDDockWidgets__Views__View_flutter__isActiveWindow(void *thisObj)
{
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isActiveWindow_nocallback();} else {    return targetPtr->isActiveWindow();} }();
}

// tag=1050
// isMaximized() const
bool c_KDDockWidgets__Views__View_flutter__isMaximized(void *thisObj)
{
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isMaximized_nocallback();} else {    return targetPtr->isMaximized();} }();
}

// tag=1050
// isMinimized() const
bool c_KDDockWidgets__Views__View_flutter__isMinimized(void *thisObj)
{
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isMinimized_nocallback();} else {    return targetPtr->isMinimized();} }();
}

// tag=1050
// isNull() const
bool c_KDDockWidgets__Views__View_flutter__isNull(void *thisObj)
{
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isNull_nocallback();} else {    return targetPtr->isNull();} }();
}

// tag=1050
// isRootView() const
bool c_KDDockWidgets__Views__View_flutter__isRootView(void *thisObj)
{
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isRootView_nocallback();} else {    return targetPtr->isRootView();} }();
}

// tag=1050
// isVisible() const
bool c_KDDockWidgets__Views__View_flutter__isVisible(void *thisObj)
{
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isVisible_nocallback();} else {    return targetPtr->isVisible();} }();
}

// tag=1050
// mapFromGlobal(QPoint globalPt) const
void *c_KDDockWidgets__Views__View_flutter__mapFromGlobal_QPoint(void *thisObj, void *globalPt_)
{
    auto &globalPt = *reinterpret_cast<QPoint *>(globalPt_);
    return
        // tag=1016

        // tag=1072
        new Dartagnan::ValueWrapper<QPoint> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->mapFromGlobal_nocallback(globalPt);} else {    return targetPtr->mapFromGlobal(globalPt);} }() };
}

// tag=1050
// mapTo(KDDockWidgets::View * parent, QPoint pos) const
void *c_KDDockWidgets__Views__View_flutter__mapTo_View_QPoint(void *thisObj, void *parent_, void *pos_)
{
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    auto &pos = *reinterpret_cast<QPoint *>(pos_);
    return
        // tag=1016

        // tag=1072
        new Dartagnan::ValueWrapper<QPoint> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->mapTo_nocallback(parent,pos);} else {    return targetPtr->mapTo(parent,pos);} }() };
}

// tag=1050
// mapToGlobal(QPoint localPt) const
void *c_KDDockWidgets__Views__View_flutter__mapToGlobal_QPoint(void *thisObj, void *localPt_)
{
    auto &localPt = *reinterpret_cast<QPoint *>(localPt_);
    return
        // tag=1016

        // tag=1072
        new Dartagnan::ValueWrapper<QPoint> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->mapToGlobal_nocallback(localPt);} else {    return targetPtr->mapToGlobal(localPt);} }() };
}

// tag=1050
// maxSizeHint() const
void *c_KDDockWidgets__Views__View_flutter__maxSizeHint(void *thisObj)
{
    return
        // tag=1016

        // tag=1072
        new Dartagnan::ValueWrapper<QSize> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->maxSizeHint_nocallback();} else {    return targetPtr->maxSizeHint();} }() };
}

// tag=1050
// maximumSize() const
void *c_KDDockWidgets__Views__View_flutter__maximumSize(void *thisObj)
{
    return
        // tag=1016

        // tag=1072
        new Dartagnan::ValueWrapper<QSize> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->maximumSize_nocallback();} else {    return targetPtr->maximumSize();} }() };
}

// tag=1050
// minSize() const
void *c_KDDockWidgets__Views__View_flutter__minSize(void *thisObj)
{
    return
        // tag=1016

        // tag=1072
        new Dartagnan::ValueWrapper<QSize> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->minSize_nocallback();} else {    return targetPtr->minSize();} }() };
}

// tag=1050
// minimumHeight() const
int c_KDDockWidgets__Views__View_flutter__minimumHeight(void *thisObj)
{
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->minimumHeight_nocallback();} else {    return targetPtr->minimumHeight();} }();
}

// tag=1050
// minimumWidth() const
int c_KDDockWidgets__Views__View_flutter__minimumWidth(void *thisObj)
{
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->minimumWidth_nocallback();} else {    return targetPtr->minimumWidth();} }();
}

// tag=1050
// move(int x, int y)
void c_KDDockWidgets__Views__View_flutter__move_int_int(void *thisObj, int x, int y)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->move_nocallback(x,y);} else {    return targetPtr->move(x,y);} }();
}

// tag=1050
// normalGeometry() const
void *c_KDDockWidgets__Views__View_flutter__normalGeometry(void *thisObj)
{
    return
        // tag=1016

        // tag=1072
        new Dartagnan::ValueWrapper<QRect> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->normalGeometry_nocallback();} else {    return targetPtr->normalGeometry();} }() };
}

// tag=1050
// objectName() const
void *c_KDDockWidgets__Views__View_flutter__objectName(void *thisObj)
{
    return
        // tag=1016

        // tag=1072
        new Dartagnan::ValueWrapper<QString> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->objectName_nocallback();} else {    return targetPtr->objectName();} }() };
}

// tag=1050
// onResize(QSize newSize)
bool c_KDDockWidgets__Views__View_flutter__onResize_QSize(void *thisObj, void *newSize_)
{
    auto &newSize = *reinterpret_cast<QSize *>(newSize_);
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->onResize_nocallback(newSize);} else {    return targetPtr->onResize(newSize);} }();
}

// tag=1050
// raise()
void c_KDDockWidgets__Views__View_flutter__raise(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->raise_nocallback();} else {    return targetPtr->raise();} }();
}

// tag=1050
// raiseAndActivate()
void c_KDDockWidgets__Views__View_flutter__raiseAndActivate(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->raiseAndActivate_nocallback();} else {    return targetPtr->raiseAndActivate();} }();
}

// tag=1050
// releaseKeyboard()
void c_KDDockWidgets__Views__View_flutter__releaseKeyboard(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->releaseKeyboard_nocallback();} else {    return targetPtr->releaseKeyboard();} }();
}

// tag=1050
// releaseMouse()
void c_KDDockWidgets__Views__View_flutter__releaseMouse(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->releaseMouse_nocallback();} else {    return targetPtr->releaseMouse();} }();
}

// tag=1050
// setCursor(Qt::CursorShape shape)
void c_KDDockWidgets__Views__View_flutter__setCursor_CursorShape(void *thisObj, int shape)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setCursor_nocallback(static_cast<Qt::CursorShape>(shape));} else {    return targetPtr->setCursor(static_cast<Qt::CursorShape>(shape));} }();
}

// tag=1050
// setFixedHeight(int h)
void c_KDDockWidgets__Views__View_flutter__setFixedHeight_int(void *thisObj, int h)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setFixedHeight_nocallback(h);} else {    return targetPtr->setFixedHeight(h);} }();
}

// tag=1050
// setFixedWidth(int w)
void c_KDDockWidgets__Views__View_flutter__setFixedWidth_int(void *thisObj, int w)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setFixedWidth_nocallback(w);} else {    return targetPtr->setFixedWidth(w);} }();
}

// tag=1050
// setGeometry(QRect arg__1)
void c_KDDockWidgets__Views__View_flutter__setGeometry_QRect(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QRect *>(arg__1_);
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setGeometry_nocallback(arg__1);} else {    return targetPtr->setGeometry(arg__1);} }();
}

// tag=1050
// setHeight(int h)
void c_KDDockWidgets__Views__View_flutter__setHeight_int(void *thisObj, int h)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setHeight_nocallback(h);} else {    return targetPtr->setHeight(h);} }();
}

// tag=1050
// setMaximumSize(QSize sz)
void c_KDDockWidgets__Views__View_flutter__setMaximumSize_QSize(void *thisObj, void *sz_)
{
    auto &sz = *reinterpret_cast<QSize *>(sz_);
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setMaximumSize_nocallback(sz);} else {    return targetPtr->setMaximumSize(sz);} }();
}

// tag=1050
// setMinimumSize(QSize sz)
void c_KDDockWidgets__Views__View_flutter__setMinimumSize_QSize(void *thisObj, void *sz_)
{
    auto &sz = *reinterpret_cast<QSize *>(sz_);
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setMinimumSize_nocallback(sz);} else {    return targetPtr->setMinimumSize(sz);} }();
}

// tag=1050
// setMouseTracking(bool enable)
void c_KDDockWidgets__Views__View_flutter__setMouseTracking_bool(void *thisObj, bool enable)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setMouseTracking_nocallback(enable);} else {    return targetPtr->setMouseTracking(enable);} }();
}

// tag=1050
// setNormalGeometry(QRect geo)
void c_KDDockWidgets__Views__View_flutter__setNormalGeometry_QRect(void *thisObj, void *geo_)
{
    auto &geo = *reinterpret_cast<QRect *>(geo_);
    // tag=1010
    fromPtr(thisObj)->setNormalGeometry(geo);
}

// tag=1050
// setObjectName(const QString & name)
void c_KDDockWidgets__Views__View_flutter__setObjectName_QString(void *thisObj, const char *name_)
{
    const auto name = QString::fromUtf8(name_);
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setObjectName_nocallback(name);} else {    return targetPtr->setObjectName(name);} }();
}

// tag=1050
// setParent(KDDockWidgets::View * parent)
void c_KDDockWidgets__Views__View_flutter__setParent_View(void *thisObj, void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setParent_nocallback(parent);} else {    return targetPtr->setParent(parent);} }();
}

// tag=1050
// setSize(int w, int h)
void c_KDDockWidgets__Views__View_flutter__setSize_int_int(void *thisObj, int w, int h)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setSize_nocallback(w,h);} else {    return targetPtr->setSize(w,h);} }();
}

// tag=1050
// setVisible(bool visible)
void c_KDDockWidgets__Views__View_flutter__setVisible_bool(void *thisObj, bool visible)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setVisible_nocallback(visible);} else {    return targetPtr->setVisible(visible);} }();
}

// tag=1050
// setWidth(int w)
void c_KDDockWidgets__Views__View_flutter__setWidth_int(void *thisObj, int w)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setWidth_nocallback(w);} else {    return targetPtr->setWidth(w);} }();
}

// tag=1050
// setWindowOpacity(double v)
void c_KDDockWidgets__Views__View_flutter__setWindowOpacity_double(void *thisObj, double v)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setWindowOpacity_nocallback(v);} else {    return targetPtr->setWindowOpacity(v);} }();
}

// tag=1050
// setWindowTitle(const QString & title)
void c_KDDockWidgets__Views__View_flutter__setWindowTitle_QString(void *thisObj, const char *title_)
{
    const auto title = QString::fromUtf8(title_);
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setWindowTitle_nocallback(title);} else {    return targetPtr->setWindowTitle(title);} }();
}

// tag=1050
// setZOrder(int arg__1)
void c_KDDockWidgets__Views__View_flutter__setZOrder_int(void *thisObj, int arg__1)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setZOrder_nocallback(arg__1);} else {    return targetPtr->setZOrder(arg__1);} }();
}

// tag=1050
// show()
void c_KDDockWidgets__Views__View_flutter__show(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->show_nocallback();} else {    return targetPtr->show();} }();
}

// tag=1050
// showMaximized()
void c_KDDockWidgets__Views__View_flutter__showMaximized(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->showMaximized_nocallback();} else {    return targetPtr->showMaximized();} }();
}

// tag=1050
// showMinimized()
void c_KDDockWidgets__Views__View_flutter__showMinimized(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->showMinimized_nocallback();} else {    return targetPtr->showMinimized();} }();
}

// tag=1050
// showNormal()
void c_KDDockWidgets__Views__View_flutter__showNormal(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->showNormal_nocallback();} else {    return targetPtr->showNormal();} }();
}

// tag=1050
// sizeHint() const
void *c_KDDockWidgets__Views__View_flutter__sizeHint(void *thisObj)
{
    return
        // tag=1016

        // tag=1072
        new Dartagnan::ValueWrapper<QSize> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->sizeHint_nocallback();} else {    return targetPtr->sizeHint();} }() };
}

// tag=1050
// update()
void c_KDDockWidgets__Views__View_flutter__update(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->update_nocallback();} else {    return targetPtr->update();} }();
}

// tag=1050
// updateGeometry()
void c_KDDockWidgets__Views__View_flutter__updateGeometry(void *thisObj)
{
    // tag=1010
    fromPtr(thisObj)->updateGeometry();
}
void c_KDDockWidgets__Views__View_flutter__destructor(void *thisObj)
{

    // tag=1055
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__Views__View_flutter__registerVirtualMethodCallback(void *ptr, void *callback, int methodId)
{
    // tag=1048
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 704:
        wrapper->m_activateWindowCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_activateWindow>(callback);
        break;
    case 708:
        wrapper->m_closeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_close>(callback);
        break;
    case 711:
        wrapper->m_createPlatformWindowCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_createPlatformWindow>(callback);
        break;
    case 715:
        wrapper->m_free_implCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_free_impl>(callback);
        break;
    case 717:
        wrapper->m_geometryCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_geometry>(callback);
        break;
    case 719:
        wrapper->m_grabMouseCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_grabMouse>(callback);
        break;
    case 722:
        wrapper->m_hasFocusCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_hasFocus>(callback);
        break;
    case 724:
        wrapper->m_hideCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_hide>(callback);
        break;
    case 727:
        wrapper->m_initCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_init>(callback);
        break;
    case 728:
        wrapper->m_isActiveWindowCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_isActiveWindow>(callback);
        break;
    case 729:
        wrapper->m_isMaximizedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_isMaximized>(callback);
        break;
    case 730:
        wrapper->m_isMinimizedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_isMinimized>(callback);
        break;
    case 731:
        wrapper->m_isNullCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_isNull>(callback);
        break;
    case 732:
        wrapper->m_isRootViewCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_isRootView>(callback);
        break;
    case 733:
        wrapper->m_isVisibleCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_isVisible>(callback);
        break;
    case 734:
        wrapper->m_mapFromGlobalCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_mapFromGlobal>(callback);
        break;
    case 735:
        wrapper->m_mapToCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_mapTo>(callback);
        break;
    case 736:
        wrapper->m_mapToGlobalCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_mapToGlobal>(callback);
        break;
    case 737:
        wrapper->m_maxSizeHintCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_maxSizeHint>(callback);
        break;
    case 738:
        wrapper->m_maximumSizeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_maximumSize>(callback);
        break;
    case 739:
        wrapper->m_minSizeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_minSize>(callback);
        break;
    case 740:
        wrapper->m_minimumHeightCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_minimumHeight>(callback);
        break;
    case 741:
        wrapper->m_minimumWidthCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_minimumWidth>(callback);
        break;
    case 743:
        wrapper->m_move_2Callback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_move_2>(callback);
        break;
    case 744:
        wrapper->m_normalGeometryCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_normalGeometry>(callback);
        break;
    case 745:
        wrapper->m_objectNameCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_objectName>(callback);
        break;
    case 746:
        wrapper->m_onResizeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_onResize>(callback);
        break;
    case 749:
        wrapper->m_raiseCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_raise>(callback);
        break;
    case 750:
        wrapper->m_raiseAndActivateCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_raiseAndActivate>(callback);
        break;
    case 752:
        wrapper->m_releaseKeyboardCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_releaseKeyboard>(callback);
        break;
    case 753:
        wrapper->m_releaseMouseCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_releaseMouse>(callback);
        break;
    case 757:
        wrapper->m_setCursorCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_setCursor>(callback);
        break;
    case 758:
        wrapper->m_setFixedHeightCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_setFixedHeight>(callback);
        break;
    case 759:
        wrapper->m_setFixedWidthCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_setFixedWidth>(callback);
        break;
    case 760:
        wrapper->m_setGeometryCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_setGeometry>(callback);
        break;
    case 761:
        wrapper->m_setHeightCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_setHeight>(callback);
        break;
    case 762:
        wrapper->m_setMaximumSizeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_setMaximumSize>(callback);
        break;
    case 763:
        wrapper->m_setMinimumSizeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_setMinimumSize>(callback);
        break;
    case 764:
        wrapper->m_setMouseTrackingCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_setMouseTracking>(callback);
        break;
    case 765:
        wrapper->m_setObjectNameCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_setObjectName>(callback);
        break;
    case 766:
        wrapper->m_setParentCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_setParent>(callback);
        break;
    case 768:
        wrapper->m_setSize_2Callback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_setSize_2>(callback);
        break;
    case 769:
        wrapper->m_setVisibleCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_setVisible>(callback);
        break;
    case 770:
        wrapper->m_setWidthCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_setWidth>(callback);
        break;
    case 771:
        wrapper->m_setWindowOpacityCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_setWindowOpacity>(callback);
        break;
    case 772:
        wrapper->m_setWindowTitleCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_setWindowTitle>(callback);
        break;
    case 773:
        wrapper->m_setZOrderCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_setZOrder>(callback);
        break;
    case 774:
        wrapper->m_showCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_show>(callback);
        break;
    case 775:
        wrapper->m_showMaximizedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_showMaximized>(callback);
        break;
    case 776:
        wrapper->m_showMinimizedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_showMinimized>(callback);
        break;
    case 777:
        wrapper->m_showNormalCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_showNormal>(callback);
        break;
    case 779:
        wrapper->m_sizeHintCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_sizeHint>(callback);
        break;
    case 780:
        wrapper->m_updateCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_flutter_wrapper::Callback_update>(callback);
        break;
    }
}
}

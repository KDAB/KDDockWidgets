/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "TitleBar_c.h"


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
namespace KDDWBindingsFlutter {
TitleBar_wrapper::TitleBar_wrapper(KDDockWidgets::Core::TitleBar *controller, KDDockWidgets::Core::View *parent)
    : ::KDDockWidgets::flutter::TitleBar(controller, parent)
{
}
void TitleBar_wrapper::activateWindow()
{
    if (m_activateWindowCallback) {
        const void *thisPtr = this;
        m_activateWindowCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::TitleBar::activateWindow();
    }
}
void TitleBar_wrapper::activateWindow_nocallback()
{
    ::KDDockWidgets::flutter::TitleBar::activateWindow();
}
bool TitleBar_wrapper::close()
{
    if (m_closeCallback) {
        const void *thisPtr = this;
        return m_closeCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TitleBar::close();
    }
}
bool TitleBar_wrapper::close_nocallback()
{
    return ::KDDockWidgets::flutter::TitleBar::close();
}
void TitleBar_wrapper::createPlatformWindow()
{
    if (m_createPlatformWindowCallback) {
        const void *thisPtr = this;
        m_createPlatformWindowCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::TitleBar::createPlatformWindow();
    }
}
void TitleBar_wrapper::createPlatformWindow_nocallback()
{
    ::KDDockWidgets::flutter::TitleBar::createPlatformWindow();
}
Qt::WindowFlags TitleBar_wrapper::flags() const
{
    if (m_flagsCallback) {
        const void *thisPtr = this;
        return m_flagsCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TitleBar::flags();
    }
}
Qt::WindowFlags TitleBar_wrapper::flags_nocallback() const
{
    return ::KDDockWidgets::flutter::TitleBar::flags();
}
QRect TitleBar_wrapper::geometry() const
{
    if (m_geometryCallback) {
        const void *thisPtr = this;
        return *m_geometryCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TitleBar::geometry();
    }
}
QRect TitleBar_wrapper::geometry_nocallback() const
{
    return ::KDDockWidgets::flutter::TitleBar::geometry();
}
void TitleBar_wrapper::grabMouse()
{
    if (m_grabMouseCallback) {
        const void *thisPtr = this;
        m_grabMouseCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::TitleBar::grabMouse();
    }
}
void TitleBar_wrapper::grabMouse_nocallback()
{
    ::KDDockWidgets::flutter::TitleBar::grabMouse();
}
bool TitleBar_wrapper::hasFocus() const
{
    if (m_hasFocusCallback) {
        const void *thisPtr = this;
        return m_hasFocusCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TitleBar::hasFocus();
    }
}
bool TitleBar_wrapper::hasFocus_nocallback() const
{
    return ::KDDockWidgets::flutter::TitleBar::hasFocus();
}
void TitleBar_wrapper::hide()
{
    if (m_hideCallback) {
        const void *thisPtr = this;
        m_hideCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::TitleBar::hide();
    }
}
void TitleBar_wrapper::hide_nocallback()
{
    ::KDDockWidgets::flutter::TitleBar::hide();
}
void TitleBar_wrapper::init()
{
    if (m_initCallback) {
        const void *thisPtr = this;
        m_initCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::TitleBar::init();
    }
}
void TitleBar_wrapper::init_nocallback()
{
    ::KDDockWidgets::flutter::TitleBar::init();
}
bool TitleBar_wrapper::isActiveWindow() const
{
    if (m_isActiveWindowCallback) {
        const void *thisPtr = this;
        return m_isActiveWindowCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TitleBar::isActiveWindow();
    }
}
bool TitleBar_wrapper::isActiveWindow_nocallback() const
{
    return ::KDDockWidgets::flutter::TitleBar::isActiveWindow();
}
bool TitleBar_wrapper::isCloseButtonEnabled() const
{
    if (m_isCloseButtonEnabledCallback) {
        const void *thisPtr = this;
        return m_isCloseButtonEnabledCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TitleBar::isCloseButtonEnabled();
    }
}
bool TitleBar_wrapper::isCloseButtonEnabled_nocallback() const
{
    return ::KDDockWidgets::flutter::TitleBar::isCloseButtonEnabled();
}
bool TitleBar_wrapper::isCloseButtonVisible() const
{
    if (m_isCloseButtonVisibleCallback) {
        const void *thisPtr = this;
        return m_isCloseButtonVisibleCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TitleBar::isCloseButtonVisible();
    }
}
bool TitleBar_wrapper::isCloseButtonVisible_nocallback() const
{
    return ::KDDockWidgets::flutter::TitleBar::isCloseButtonVisible();
}
bool TitleBar_wrapper::isExplicitlyHidden() const
{
    if (m_isExplicitlyHiddenCallback) {
        const void *thisPtr = this;
        return m_isExplicitlyHiddenCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TitleBar::isExplicitlyHidden();
    }
}
bool TitleBar_wrapper::isExplicitlyHidden_nocallback() const
{
    return ::KDDockWidgets::flutter::TitleBar::isExplicitlyHidden();
}
bool TitleBar_wrapper::isFloatButtonVisible() const
{
    if (m_isFloatButtonVisibleCallback) {
        const void *thisPtr = this;
        return m_isFloatButtonVisibleCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TitleBar::isFloatButtonVisible();
    }
}
bool TitleBar_wrapper::isFloatButtonVisible_nocallback() const
{
    return ::KDDockWidgets::flutter::TitleBar::isFloatButtonVisible();
}
bool TitleBar_wrapper::isMaximized() const
{
    if (m_isMaximizedCallback) {
        const void *thisPtr = this;
        return m_isMaximizedCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TitleBar::isMaximized();
    }
}
bool TitleBar_wrapper::isMaximized_nocallback() const
{
    return ::KDDockWidgets::flutter::TitleBar::isMaximized();
}
bool TitleBar_wrapper::isMinimized() const
{
    if (m_isMinimizedCallback) {
        const void *thisPtr = this;
        return m_isMinimizedCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TitleBar::isMinimized();
    }
}
bool TitleBar_wrapper::isMinimized_nocallback() const
{
    return ::KDDockWidgets::flutter::TitleBar::isMinimized();
}
bool TitleBar_wrapper::isNull() const
{
    if (m_isNullCallback) {
        const void *thisPtr = this;
        return m_isNullCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TitleBar::isNull();
    }
}
bool TitleBar_wrapper::isNull_nocallback() const
{
    return ::KDDockWidgets::flutter::TitleBar::isNull();
}
bool TitleBar_wrapper::isRootView() const
{
    if (m_isRootViewCallback) {
        const void *thisPtr = this;
        return m_isRootViewCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TitleBar::isRootView();
    }
}
bool TitleBar_wrapper::isRootView_nocallback() const
{
    return ::KDDockWidgets::flutter::TitleBar::isRootView();
}
bool TitleBar_wrapper::isVisible() const
{
    if (m_isVisibleCallback) {
        const void *thisPtr = this;
        return m_isVisibleCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TitleBar::isVisible();
    }
}
bool TitleBar_wrapper::isVisible_nocallback() const
{
    return ::KDDockWidgets::flutter::TitleBar::isVisible();
}
QPoint TitleBar_wrapper::mapFromGlobal(QPoint globalPt) const
{
    if (m_mapFromGlobalCallback) {
        const void *thisPtr = this;
        return *m_mapFromGlobalCallback(const_cast<void *>(thisPtr), &globalPt);
    } else {
        return ::KDDockWidgets::flutter::TitleBar::mapFromGlobal(globalPt);
    }
}
QPoint TitleBar_wrapper::mapFromGlobal_nocallback(QPoint globalPt) const
{
    return ::KDDockWidgets::flutter::TitleBar::mapFromGlobal(globalPt);
}
QPoint TitleBar_wrapper::mapTo(KDDockWidgets::Core::View *parent, QPoint pos) const
{
    if (m_mapToCallback) {
        const void *thisPtr = this;
        return *m_mapToCallback(const_cast<void *>(thisPtr), parent, &pos);
    } else {
        return ::KDDockWidgets::flutter::TitleBar::mapTo(parent, pos);
    }
}
QPoint TitleBar_wrapper::mapTo_nocallback(KDDockWidgets::Core::View *parent, QPoint pos) const
{
    return ::KDDockWidgets::flutter::TitleBar::mapTo(parent, pos);
}
QPoint TitleBar_wrapper::mapToGlobal(QPoint localPt) const
{
    if (m_mapToGlobalCallback) {
        const void *thisPtr = this;
        return *m_mapToGlobalCallback(const_cast<void *>(thisPtr), &localPt);
    } else {
        return ::KDDockWidgets::flutter::TitleBar::mapToGlobal(localPt);
    }
}
QPoint TitleBar_wrapper::mapToGlobal_nocallback(QPoint localPt) const
{
    return ::KDDockWidgets::flutter::TitleBar::mapToGlobal(localPt);
}
QSize TitleBar_wrapper::maxSizeHint() const
{
    if (m_maxSizeHintCallback) {
        const void *thisPtr = this;
        return *m_maxSizeHintCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TitleBar::maxSizeHint();
    }
}
QSize TitleBar_wrapper::maxSizeHint_nocallback() const
{
    return ::KDDockWidgets::flutter::TitleBar::maxSizeHint();
}
QSize TitleBar_wrapper::minSize() const
{
    if (m_minSizeCallback) {
        const void *thisPtr = this;
        return *m_minSizeCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TitleBar::minSize();
    }
}
QSize TitleBar_wrapper::minSize_nocallback() const
{
    return ::KDDockWidgets::flutter::TitleBar::minSize();
}
int TitleBar_wrapper::minimumHeight() const
{
    if (m_minimumHeightCallback) {
        const void *thisPtr = this;
        return m_minimumHeightCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TitleBar::minimumHeight();
    }
}
int TitleBar_wrapper::minimumHeight_nocallback() const
{
    return ::KDDockWidgets::flutter::TitleBar::minimumHeight();
}
int TitleBar_wrapper::minimumWidth() const
{
    if (m_minimumWidthCallback) {
        const void *thisPtr = this;
        return m_minimumWidthCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TitleBar::minimumWidth();
    }
}
int TitleBar_wrapper::minimumWidth_nocallback() const
{
    return ::KDDockWidgets::flutter::TitleBar::minimumWidth();
}
void TitleBar_wrapper::move(int x, int y)
{
    if (m_move_2Callback) {
        const void *thisPtr = this;
        m_move_2Callback(const_cast<void *>(thisPtr), x, y);
    } else {
        ::KDDockWidgets::flutter::TitleBar::move(x, y);
    }
}
void TitleBar_wrapper::move_nocallback(int x, int y)
{
    ::KDDockWidgets::flutter::TitleBar::move(x, y);
}
QRect TitleBar_wrapper::normalGeometry() const
{
    if (m_normalGeometryCallback) {
        const void *thisPtr = this;
        return *m_normalGeometryCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TitleBar::normalGeometry();
    }
}
QRect TitleBar_wrapper::normalGeometry_nocallback() const
{
    return ::KDDockWidgets::flutter::TitleBar::normalGeometry();
}
QString TitleBar_wrapper::objectName() const
{
    if (m_objectNameCallback) {
        const void *thisPtr = this;
        return *m_objectNameCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TitleBar::objectName();
    }
}
QString TitleBar_wrapper::objectName_nocallback() const
{
    return ::KDDockWidgets::flutter::TitleBar::objectName();
}
void TitleBar_wrapper::onChildAdded(KDDockWidgets::Core::View *childView)
{
    if (m_onChildAddedCallback) {
        const void *thisPtr = this;
        m_onChildAddedCallback(const_cast<void *>(thisPtr), childView);
    } else {
        ::KDDockWidgets::flutter::TitleBar::onChildAdded(childView);
    }
}
void TitleBar_wrapper::onChildAdded_nocallback(KDDockWidgets::Core::View *childView)
{
    ::KDDockWidgets::flutter::TitleBar::onChildAdded(childView);
}
void TitleBar_wrapper::onChildRemoved(KDDockWidgets::Core::View *childView)
{
    if (m_onChildRemovedCallback) {
        const void *thisPtr = this;
        m_onChildRemovedCallback(const_cast<void *>(thisPtr), childView);
    } else {
        ::KDDockWidgets::flutter::TitleBar::onChildRemoved(childView);
    }
}
void TitleBar_wrapper::onChildRemoved_nocallback(KDDockWidgets::Core::View *childView)
{
    ::KDDockWidgets::flutter::TitleBar::onChildRemoved(childView);
}
void TitleBar_wrapper::onChildVisibilityChanged(KDDockWidgets::Core::View *childView)
{
    if (m_onChildVisibilityChangedCallback) {
        const void *thisPtr = this;
        m_onChildVisibilityChangedCallback(const_cast<void *>(thisPtr), childView);
    } else {
        ::KDDockWidgets::flutter::TitleBar::onChildVisibilityChanged(childView);
    }
}
void TitleBar_wrapper::onChildVisibilityChanged_nocallback(KDDockWidgets::Core::View *childView)
{
    ::KDDockWidgets::flutter::TitleBar::onChildVisibilityChanged(childView);
}
void TitleBar_wrapper::onGeometryChanged()
{
    if (m_onGeometryChangedCallback) {
        const void *thisPtr = this;
        m_onGeometryChangedCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::TitleBar::onGeometryChanged();
    }
}
void TitleBar_wrapper::onGeometryChanged_nocallback()
{
    ::KDDockWidgets::flutter::TitleBar::onGeometryChanged();
}
bool TitleBar_wrapper::onResize(int h, int w)
{
    if (m_onResize_2Callback) {
        const void *thisPtr = this;
        return m_onResize_2Callback(const_cast<void *>(thisPtr), h, w);
    } else {
        return ::KDDockWidgets::flutter::TitleBar::onResize(h, w);
    }
}
bool TitleBar_wrapper::onResize_nocallback(int h, int w)
{
    return ::KDDockWidgets::flutter::TitleBar::onResize(h, w);
}
void TitleBar_wrapper::raise()
{
    if (m_raiseCallback) {
        const void *thisPtr = this;
        m_raiseCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::TitleBar::raise();
    }
}
void TitleBar_wrapper::raise_nocallback()
{
    ::KDDockWidgets::flutter::TitleBar::raise();
}
void TitleBar_wrapper::raiseAndActivate()
{
    if (m_raiseAndActivateCallback) {
        const void *thisPtr = this;
        m_raiseAndActivateCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::TitleBar::raiseAndActivate();
    }
}
void TitleBar_wrapper::raiseAndActivate_nocallback()
{
    ::KDDockWidgets::flutter::TitleBar::raiseAndActivate();
}
void TitleBar_wrapper::releaseKeyboard()
{
    if (m_releaseKeyboardCallback) {
        const void *thisPtr = this;
        m_releaseKeyboardCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::TitleBar::releaseKeyboard();
    }
}
void TitleBar_wrapper::releaseKeyboard_nocallback()
{
    ::KDDockWidgets::flutter::TitleBar::releaseKeyboard();
}
void TitleBar_wrapper::releaseMouse()
{
    if (m_releaseMouseCallback) {
        const void *thisPtr = this;
        m_releaseMouseCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::TitleBar::releaseMouse();
    }
}
void TitleBar_wrapper::releaseMouse_nocallback()
{
    ::KDDockWidgets::flutter::TitleBar::releaseMouse();
}
void TitleBar_wrapper::setCursor(Qt::CursorShape shape)
{
    if (m_setCursorCallback) {
        const void *thisPtr = this;
        m_setCursorCallback(const_cast<void *>(thisPtr), shape);
    } else {
        ::KDDockWidgets::flutter::TitleBar::setCursor(shape);
    }
}
void TitleBar_wrapper::setCursor_nocallback(Qt::CursorShape shape)
{
    ::KDDockWidgets::flutter::TitleBar::setCursor(shape);
}
void TitleBar_wrapper::setFixedHeight(int h)
{
    if (m_setFixedHeightCallback) {
        const void *thisPtr = this;
        m_setFixedHeightCallback(const_cast<void *>(thisPtr), h);
    } else {
        ::KDDockWidgets::flutter::TitleBar::setFixedHeight(h);
    }
}
void TitleBar_wrapper::setFixedHeight_nocallback(int h)
{
    ::KDDockWidgets::flutter::TitleBar::setFixedHeight(h);
}
void TitleBar_wrapper::setFixedWidth(int w)
{
    if (m_setFixedWidthCallback) {
        const void *thisPtr = this;
        m_setFixedWidthCallback(const_cast<void *>(thisPtr), w);
    } else {
        ::KDDockWidgets::flutter::TitleBar::setFixedWidth(w);
    }
}
void TitleBar_wrapper::setFixedWidth_nocallback(int w)
{
    ::KDDockWidgets::flutter::TitleBar::setFixedWidth(w);
}
void TitleBar_wrapper::setGeometry(QRect geometry)
{
    if (m_setGeometryCallback) {
        const void *thisPtr = this;
        m_setGeometryCallback(const_cast<void *>(thisPtr), &geometry);
    } else {
        ::KDDockWidgets::flutter::TitleBar::setGeometry(geometry);
    }
}
void TitleBar_wrapper::setGeometry_nocallback(QRect geometry)
{
    ::KDDockWidgets::flutter::TitleBar::setGeometry(geometry);
}
void TitleBar_wrapper::setHeight(int h)
{
    if (m_setHeightCallback) {
        const void *thisPtr = this;
        m_setHeightCallback(const_cast<void *>(thisPtr), h);
    } else {
        ::KDDockWidgets::flutter::TitleBar::setHeight(h);
    }
}
void TitleBar_wrapper::setHeight_nocallback(int h)
{
    ::KDDockWidgets::flutter::TitleBar::setHeight(h);
}
void TitleBar_wrapper::setMaximumSize(QSize sz)
{
    if (m_setMaximumSizeCallback) {
        const void *thisPtr = this;
        m_setMaximumSizeCallback(const_cast<void *>(thisPtr), &sz);
    } else {
        ::KDDockWidgets::flutter::TitleBar::setMaximumSize(sz);
    }
}
void TitleBar_wrapper::setMaximumSize_nocallback(QSize sz)
{
    ::KDDockWidgets::flutter::TitleBar::setMaximumSize(sz);
}
void TitleBar_wrapper::setMinimumSize(QSize sz)
{
    if (m_setMinimumSizeCallback) {
        const void *thisPtr = this;
        m_setMinimumSizeCallback(const_cast<void *>(thisPtr), &sz);
    } else {
        ::KDDockWidgets::flutter::TitleBar::setMinimumSize(sz);
    }
}
void TitleBar_wrapper::setMinimumSize_nocallback(QSize sz)
{
    ::KDDockWidgets::flutter::TitleBar::setMinimumSize(sz);
}
void TitleBar_wrapper::setMouseTracking(bool enable)
{
    if (m_setMouseTrackingCallback) {
        const void *thisPtr = this;
        m_setMouseTrackingCallback(const_cast<void *>(thisPtr), enable);
    } else {
        ::KDDockWidgets::flutter::TitleBar::setMouseTracking(enable);
    }
}
void TitleBar_wrapper::setMouseTracking_nocallback(bool enable)
{
    ::KDDockWidgets::flutter::TitleBar::setMouseTracking(enable);
}
void TitleBar_wrapper::setObjectName(const QString &name)
{
    if (m_setObjectNameCallback) {
        const void *thisPtr = this;
        m_setObjectNameCallback(const_cast<void *>(thisPtr), name);
    } else {
        ::KDDockWidgets::flutter::TitleBar::setObjectName(name);
    }
}
void TitleBar_wrapper::setObjectName_nocallback(const QString &name)
{
    ::KDDockWidgets::flutter::TitleBar::setObjectName(name);
}
void TitleBar_wrapper::setParent(KDDockWidgets::Core::View *parent)
{
    if (m_setParentCallback) {
        const void *thisPtr = this;
        m_setParentCallback(const_cast<void *>(thisPtr), parent);
    } else {
        ::KDDockWidgets::flutter::TitleBar::setParent(parent);
    }
}
void TitleBar_wrapper::setParent_nocallback(KDDockWidgets::Core::View *parent)
{
    ::KDDockWidgets::flutter::TitleBar::setParent(parent);
}
void TitleBar_wrapper::setSize(int w, int h)
{
    if (m_setSize_2Callback) {
        const void *thisPtr = this;
        m_setSize_2Callback(const_cast<void *>(thisPtr), w, h);
    } else {
        ::KDDockWidgets::flutter::TitleBar::setSize(w, h);
    }
}
void TitleBar_wrapper::setSize_nocallback(int w, int h)
{
    ::KDDockWidgets::flutter::TitleBar::setSize(w, h);
}
void TitleBar_wrapper::setVisible(bool visible)
{
    if (m_setVisibleCallback) {
        const void *thisPtr = this;
        m_setVisibleCallback(const_cast<void *>(thisPtr), visible);
    } else {
        ::KDDockWidgets::flutter::TitleBar::setVisible(visible);
    }
}
void TitleBar_wrapper::setVisible_nocallback(bool visible)
{
    ::KDDockWidgets::flutter::TitleBar::setVisible(visible);
}
void TitleBar_wrapper::setWidth(int w)
{
    if (m_setWidthCallback) {
        const void *thisPtr = this;
        m_setWidthCallback(const_cast<void *>(thisPtr), w);
    } else {
        ::KDDockWidgets::flutter::TitleBar::setWidth(w);
    }
}
void TitleBar_wrapper::setWidth_nocallback(int w)
{
    ::KDDockWidgets::flutter::TitleBar::setWidth(w);
}
void TitleBar_wrapper::setWindowOpacity(double v)
{
    if (m_setWindowOpacityCallback) {
        const void *thisPtr = this;
        m_setWindowOpacityCallback(const_cast<void *>(thisPtr), v);
    } else {
        ::KDDockWidgets::flutter::TitleBar::setWindowOpacity(v);
    }
}
void TitleBar_wrapper::setWindowOpacity_nocallback(double v)
{
    ::KDDockWidgets::flutter::TitleBar::setWindowOpacity(v);
}
void TitleBar_wrapper::setWindowTitle(const QString &title)
{
    if (m_setWindowTitleCallback) {
        const void *thisPtr = this;
        m_setWindowTitleCallback(const_cast<void *>(thisPtr), title);
    } else {
        ::KDDockWidgets::flutter::TitleBar::setWindowTitle(title);
    }
}
void TitleBar_wrapper::setWindowTitle_nocallback(const QString &title)
{
    ::KDDockWidgets::flutter::TitleBar::setWindowTitle(title);
}
void TitleBar_wrapper::setZOrder(int z)
{
    if (m_setZOrderCallback) {
        const void *thisPtr = this;
        m_setZOrderCallback(const_cast<void *>(thisPtr), z);
    } else {
        ::KDDockWidgets::flutter::TitleBar::setZOrder(z);
    }
}
void TitleBar_wrapper::setZOrder_nocallback(int z)
{
    ::KDDockWidgets::flutter::TitleBar::setZOrder(z);
}
void TitleBar_wrapper::show()
{
    if (m_showCallback) {
        const void *thisPtr = this;
        m_showCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::TitleBar::show();
    }
}
void TitleBar_wrapper::show_nocallback()
{
    ::KDDockWidgets::flutter::TitleBar::show();
}
void TitleBar_wrapper::showMaximized()
{
    if (m_showMaximizedCallback) {
        const void *thisPtr = this;
        m_showMaximizedCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::TitleBar::showMaximized();
    }
}
void TitleBar_wrapper::showMaximized_nocallback()
{
    ::KDDockWidgets::flutter::TitleBar::showMaximized();
}
void TitleBar_wrapper::showMinimized()
{
    if (m_showMinimizedCallback) {
        const void *thisPtr = this;
        m_showMinimizedCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::TitleBar::showMinimized();
    }
}
void TitleBar_wrapper::showMinimized_nocallback()
{
    ::KDDockWidgets::flutter::TitleBar::showMinimized();
}
void TitleBar_wrapper::showNormal()
{
    if (m_showNormalCallback) {
        const void *thisPtr = this;
        m_showNormalCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::TitleBar::showNormal();
    }
}
void TitleBar_wrapper::showNormal_nocallback()
{
    ::KDDockWidgets::flutter::TitleBar::showNormal();
}
QSize TitleBar_wrapper::sizeHint() const
{
    if (m_sizeHintCallback) {
        const void *thisPtr = this;
        return *m_sizeHintCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TitleBar::sizeHint();
    }
}
QSize TitleBar_wrapper::sizeHint_nocallback() const
{
    return ::KDDockWidgets::flutter::TitleBar::sizeHint();
}
void TitleBar_wrapper::update()
{
    if (m_updateCallback) {
        const void *thisPtr = this;
        m_updateCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::TitleBar::update();
    }
}
void TitleBar_wrapper::update_nocallback()
{
    ::KDDockWidgets::flutter::TitleBar::update();
}
TitleBar_wrapper::~TitleBar_wrapper()
{
}

}
}
static KDDockWidgets::flutter::TitleBar *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::flutter::TitleBar *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__flutter__TitleBar_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper *>(cppObj);
}
void *c_KDDockWidgets__flutter__TitleBar__constructor_TitleBar_View(void *controller_, void *parent_)
{
    auto controller = reinterpret_cast<KDDockWidgets::Core::TitleBar *>(controller_);
    auto parent = reinterpret_cast<KDDockWidgets::Core::View *>(parent_);
    auto ptr = new KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper(controller, parent);
    return reinterpret_cast<void *>(ptr);
}
// activateWindow()
void c_KDDockWidgets__flutter__TitleBar__activateWindow(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->activateWindow_nocallback();} else {    return targetPtr->activateWindow();} }();
}
// close()
bool c_KDDockWidgets__flutter__TitleBar__close(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->close_nocallback();} else {    return targetPtr->close();} }();
}
// createPlatformWindow()
void c_KDDockWidgets__flutter__TitleBar__createPlatformWindow(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->createPlatformWindow_nocallback();} else {    return targetPtr->createPlatformWindow();} }();
}
// flags() const
int c_KDDockWidgets__flutter__TitleBar__flags(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->flags_nocallback();} else {    return targetPtr->flags();} }();
}
// geometry() const
void *c_KDDockWidgets__flutter__TitleBar__geometry(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QRect> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->geometry_nocallback();} else {    return targetPtr->geometry();} }() };
}
// grabMouse()
void c_KDDockWidgets__flutter__TitleBar__grabMouse(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->grabMouse_nocallback();} else {    return targetPtr->grabMouse();} }();
}
// hasFocus() const
bool c_KDDockWidgets__flutter__TitleBar__hasFocus(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->hasFocus_nocallback();} else {    return targetPtr->hasFocus();} }();
}
// hide()
void c_KDDockWidgets__flutter__TitleBar__hide(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->hide_nocallback();} else {    return targetPtr->hide();} }();
}
// init()
void c_KDDockWidgets__flutter__TitleBar__init(void *thisObj)
{
    fromWrapperPtr(thisObj)->init_nocallback();
}
// isActiveWindow() const
bool c_KDDockWidgets__flutter__TitleBar__isActiveWindow(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isActiveWindow_nocallback();} else {    return targetPtr->isActiveWindow();} }();
}
// isCloseButtonEnabled() const
bool c_KDDockWidgets__flutter__TitleBar__isCloseButtonEnabled(void *thisObj)
{
    return fromWrapperPtr(thisObj)->isCloseButtonEnabled_nocallback();
}
// isCloseButtonVisible() const
bool c_KDDockWidgets__flutter__TitleBar__isCloseButtonVisible(void *thisObj)
{
    return fromWrapperPtr(thisObj)->isCloseButtonVisible_nocallback();
}
// isExplicitlyHidden() const
bool c_KDDockWidgets__flutter__TitleBar__isExplicitlyHidden(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isExplicitlyHidden_nocallback();} else {    return targetPtr->isExplicitlyHidden();} }();
}
// isFloatButtonVisible() const
bool c_KDDockWidgets__flutter__TitleBar__isFloatButtonVisible(void *thisObj)
{
    return fromWrapperPtr(thisObj)->isFloatButtonVisible_nocallback();
}
// isMaximized() const
bool c_KDDockWidgets__flutter__TitleBar__isMaximized(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isMaximized_nocallback();} else {    return targetPtr->isMaximized();} }();
}
// isMinimized() const
bool c_KDDockWidgets__flutter__TitleBar__isMinimized(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isMinimized_nocallback();} else {    return targetPtr->isMinimized();} }();
}
// isNull() const
bool c_KDDockWidgets__flutter__TitleBar__isNull(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isNull_nocallback();} else {    return targetPtr->isNull();} }();
}
// isRootView() const
bool c_KDDockWidgets__flutter__TitleBar__isRootView(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isRootView_nocallback();} else {    return targetPtr->isRootView();} }();
}
// isVisible() const
bool c_KDDockWidgets__flutter__TitleBar__isVisible(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isVisible_nocallback();} else {    return targetPtr->isVisible();} }();
}
// mapFromGlobal(QPoint globalPt) const
void *c_KDDockWidgets__flutter__TitleBar__mapFromGlobal_QPoint(void *thisObj, void *globalPt_)
{
    assert(globalPt_);
    auto &globalPt = *reinterpret_cast<QPoint *>(globalPt_);
    return new Dartagnan::ValueWrapper<QPoint> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->mapFromGlobal_nocallback(globalPt);} else {    return targetPtr->mapFromGlobal(globalPt);} }() };
}
// mapTo(KDDockWidgets::Core::View * parent, QPoint pos) const
void *c_KDDockWidgets__flutter__TitleBar__mapTo_View_QPoint(void *thisObj, void *parent_, void *pos_)
{
    auto parent = reinterpret_cast<KDDockWidgets::Core::View *>(parent_);
    assert(pos_);
    auto &pos = *reinterpret_cast<QPoint *>(pos_);
    return new Dartagnan::ValueWrapper<QPoint> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->mapTo_nocallback(parent,pos);} else {    return targetPtr->mapTo(parent,pos);} }() };
}
// mapToGlobal(QPoint localPt) const
void *c_KDDockWidgets__flutter__TitleBar__mapToGlobal_QPoint(void *thisObj, void *localPt_)
{
    assert(localPt_);
    auto &localPt = *reinterpret_cast<QPoint *>(localPt_);
    return new Dartagnan::ValueWrapper<QPoint> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->mapToGlobal_nocallback(localPt);} else {    return targetPtr->mapToGlobal(localPt);} }() };
}
// maxSizeHint() const
void *c_KDDockWidgets__flutter__TitleBar__maxSizeHint(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->maxSizeHint_nocallback();} else {    return targetPtr->maxSizeHint();} }() };
}
// minSize() const
void *c_KDDockWidgets__flutter__TitleBar__minSize(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->minSize_nocallback();} else {    return targetPtr->minSize();} }() };
}
// minimumHeight() const
int c_KDDockWidgets__flutter__TitleBar__minimumHeight(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->minimumHeight_nocallback();} else {    return targetPtr->minimumHeight();} }();
}
// minimumWidth() const
int c_KDDockWidgets__flutter__TitleBar__minimumWidth(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->minimumWidth_nocallback();} else {    return targetPtr->minimumWidth();} }();
}
// move(int x, int y)
void c_KDDockWidgets__flutter__TitleBar__move_int_int(void *thisObj, int x, int y)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->move_nocallback(x,y);} else {    return targetPtr->move(x,y);} }();
}
// normalGeometry() const
void *c_KDDockWidgets__flutter__TitleBar__normalGeometry(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QRect> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->normalGeometry_nocallback();} else {    return targetPtr->normalGeometry();} }() };
}
// objectName() const
void *c_KDDockWidgets__flutter__TitleBar__objectName(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QString> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->objectName_nocallback();} else {    return targetPtr->objectName();} }() };
}
// onChildAdded(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__TitleBar__onChildAdded_View(void *thisObj, void *childView_)
{
    auto childView = reinterpret_cast<KDDockWidgets::Core::View *>(childView_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->onChildAdded_nocallback(childView);} else {    return targetPtr->onChildAdded(childView);} }();
}
// onChildRemoved(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__TitleBar__onChildRemoved_View(void *thisObj, void *childView_)
{
    auto childView = reinterpret_cast<KDDockWidgets::Core::View *>(childView_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->onChildRemoved_nocallback(childView);} else {    return targetPtr->onChildRemoved(childView);} }();
}
// onChildVisibilityChanged(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__TitleBar__onChildVisibilityChanged_View(void *thisObj, void *childView_)
{
    auto childView = reinterpret_cast<KDDockWidgets::Core::View *>(childView_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->onChildVisibilityChanged_nocallback(childView);} else {    return targetPtr->onChildVisibilityChanged(childView);} }();
}
// onGeometryChanged()
void c_KDDockWidgets__flutter__TitleBar__onGeometryChanged(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->onGeometryChanged_nocallback();} else {    return targetPtr->onGeometryChanged();} }();
}
// onResize(int h, int w)
bool c_KDDockWidgets__flutter__TitleBar__onResize_int_int(void *thisObj, int h, int w)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->onResize_nocallback(h,w);} else {    return targetPtr->onResize(h,w);} }();
}
// raise()
void c_KDDockWidgets__flutter__TitleBar__raise(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->raise_nocallback();} else {    return targetPtr->raise();} }();
}
// raiseAndActivate()
void c_KDDockWidgets__flutter__TitleBar__raiseAndActivate(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->raiseAndActivate_nocallback();} else {    return targetPtr->raiseAndActivate();} }();
}
// releaseKeyboard()
void c_KDDockWidgets__flutter__TitleBar__releaseKeyboard(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->releaseKeyboard_nocallback();} else {    return targetPtr->releaseKeyboard();} }();
}
// releaseMouse()
void c_KDDockWidgets__flutter__TitleBar__releaseMouse(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->releaseMouse_nocallback();} else {    return targetPtr->releaseMouse();} }();
}
// setCursor(Qt::CursorShape shape)
void c_KDDockWidgets__flutter__TitleBar__setCursor_CursorShape(void *thisObj, int shape)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setCursor_nocallback(static_cast<Qt::CursorShape>(shape));} else {    return targetPtr->setCursor(static_cast<Qt::CursorShape>(shape));} }();
}
// setFixedHeight(int h)
void c_KDDockWidgets__flutter__TitleBar__setFixedHeight_int(void *thisObj, int h)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setFixedHeight_nocallback(h);} else {    return targetPtr->setFixedHeight(h);} }();
}
// setFixedWidth(int w)
void c_KDDockWidgets__flutter__TitleBar__setFixedWidth_int(void *thisObj, int w)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setFixedWidth_nocallback(w);} else {    return targetPtr->setFixedWidth(w);} }();
}
// setGeometry(QRect geometry)
void c_KDDockWidgets__flutter__TitleBar__setGeometry_QRect(void *thisObj, void *geometry_)
{
    assert(geometry_);
    auto &geometry = *reinterpret_cast<QRect *>(geometry_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setGeometry_nocallback(geometry);} else {    return targetPtr->setGeometry(geometry);} }();
}
// setHeight(int h)
void c_KDDockWidgets__flutter__TitleBar__setHeight_int(void *thisObj, int h)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setHeight_nocallback(h);} else {    return targetPtr->setHeight(h);} }();
}
// setMaximumSize(QSize sz)
void c_KDDockWidgets__flutter__TitleBar__setMaximumSize_QSize(void *thisObj, void *sz_)
{
    assert(sz_);
    auto &sz = *reinterpret_cast<QSize *>(sz_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setMaximumSize_nocallback(sz);} else {    return targetPtr->setMaximumSize(sz);} }();
}
// setMinimumSize(QSize sz)
void c_KDDockWidgets__flutter__TitleBar__setMinimumSize_QSize(void *thisObj, void *sz_)
{
    assert(sz_);
    auto &sz = *reinterpret_cast<QSize *>(sz_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setMinimumSize_nocallback(sz);} else {    return targetPtr->setMinimumSize(sz);} }();
}
// setMouseTracking(bool enable)
void c_KDDockWidgets__flutter__TitleBar__setMouseTracking_bool(void *thisObj, bool enable)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setMouseTracking_nocallback(enable);} else {    return targetPtr->setMouseTracking(enable);} }();
}
// setObjectName(const QString & name)
void c_KDDockWidgets__flutter__TitleBar__setObjectName_QString(void *thisObj, const char *name_)
{
    const auto name = QString::fromUtf8(name_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setObjectName_nocallback(name);} else {    return targetPtr->setObjectName(name);} }();
}
// setParent(KDDockWidgets::Core::View * parent)
void c_KDDockWidgets__flutter__TitleBar__setParent_View(void *thisObj, void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::Core::View *>(parent_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setParent_nocallback(parent);} else {    return targetPtr->setParent(parent);} }();
}
// setSize(int w, int h)
void c_KDDockWidgets__flutter__TitleBar__setSize_int_int(void *thisObj, int w, int h)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setSize_nocallback(w,h);} else {    return targetPtr->setSize(w,h);} }();
}
// setVisible(bool visible)
void c_KDDockWidgets__flutter__TitleBar__setVisible_bool(void *thisObj, bool visible)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setVisible_nocallback(visible);} else {    return targetPtr->setVisible(visible);} }();
}
// setWidth(int w)
void c_KDDockWidgets__flutter__TitleBar__setWidth_int(void *thisObj, int w)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setWidth_nocallback(w);} else {    return targetPtr->setWidth(w);} }();
}
// setWindowOpacity(double v)
void c_KDDockWidgets__flutter__TitleBar__setWindowOpacity_double(void *thisObj, double v)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setWindowOpacity_nocallback(v);} else {    return targetPtr->setWindowOpacity(v);} }();
}
// setWindowTitle(const QString & title)
void c_KDDockWidgets__flutter__TitleBar__setWindowTitle_QString(void *thisObj, const char *title_)
{
    const auto title = QString::fromUtf8(title_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setWindowTitle_nocallback(title);} else {    return targetPtr->setWindowTitle(title);} }();
}
// setZOrder(int z)
void c_KDDockWidgets__flutter__TitleBar__setZOrder_int(void *thisObj, int z)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setZOrder_nocallback(z);} else {    return targetPtr->setZOrder(z);} }();
}
// show()
void c_KDDockWidgets__flutter__TitleBar__show(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->show_nocallback();} else {    return targetPtr->show();} }();
}
// showMaximized()
void c_KDDockWidgets__flutter__TitleBar__showMaximized(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->showMaximized_nocallback();} else {    return targetPtr->showMaximized();} }();
}
// showMinimized()
void c_KDDockWidgets__flutter__TitleBar__showMinimized(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->showMinimized_nocallback();} else {    return targetPtr->showMinimized();} }();
}
// showNormal()
void c_KDDockWidgets__flutter__TitleBar__showNormal(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->showNormal_nocallback();} else {    return targetPtr->showNormal();} }();
}
// sizeHint() const
void *c_KDDockWidgets__flutter__TitleBar__sizeHint(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->sizeHint_nocallback();} else {    return targetPtr->sizeHint();} }() };
}
// update()
void c_KDDockWidgets__flutter__TitleBar__update(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->update_nocallback();} else {    return targetPtr->update();} }();
}
void c_KDDockWidgets__flutter__TitleBar__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__flutter__TitleBar__registerVirtualMethodCallback(void *ptr, void *callback, int methodId)
{
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 920:
        wrapper->m_activateWindowCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_activateWindow>(callback);
        break;
    case 931:
        wrapper->m_closeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_close>(callback);
        break;
    case 934:
        wrapper->m_createPlatformWindowCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_createPlatformWindow>(callback);
        break;
    case 941:
        wrapper->m_flagsCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_flags>(callback);
        break;
    case 944:
        wrapper->m_geometryCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_geometry>(callback);
        break;
    case 946:
        wrapper->m_grabMouseCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_grabMouse>(callback);
        break;
    case 949:
        wrapper->m_hasFocusCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_hasFocus>(callback);
        break;
    case 951:
        wrapper->m_hideCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_hide>(callback);
        break;
    case 954:
        wrapper->m_initCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_init>(callback);
        break;
    case 956:
        wrapper->m_isActiveWindowCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_isActiveWindow>(callback);
        break;
    case 1065:
        wrapper->m_isCloseButtonEnabledCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_isCloseButtonEnabled>(callback);
        break;
    case 1066:
        wrapper->m_isCloseButtonVisibleCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_isCloseButtonVisible>(callback);
        break;
    case 957:
        wrapper->m_isExplicitlyHiddenCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_isExplicitlyHidden>(callback);
        break;
    case 1067:
        wrapper->m_isFloatButtonVisibleCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_isFloatButtonVisible>(callback);
        break;
    case 958:
        wrapper->m_isMaximizedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_isMaximized>(callback);
        break;
    case 959:
        wrapper->m_isMinimizedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_isMinimized>(callback);
        break;
    case 960:
        wrapper->m_isNullCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_isNull>(callback);
        break;
    case 961:
        wrapper->m_isRootViewCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_isRootView>(callback);
        break;
    case 962:
        wrapper->m_isVisibleCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_isVisible>(callback);
        break;
    case 963:
        wrapper->m_mapFromGlobalCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_mapFromGlobal>(callback);
        break;
    case 964:
        wrapper->m_mapToCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_mapTo>(callback);
        break;
    case 965:
        wrapper->m_mapToGlobalCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_mapToGlobal>(callback);
        break;
    case 966:
        wrapper->m_maxSizeHintCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_maxSizeHint>(callback);
        break;
    case 967:
        wrapper->m_minSizeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_minSize>(callback);
        break;
    case 968:
        wrapper->m_minimumHeightCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_minimumHeight>(callback);
        break;
    case 969:
        wrapper->m_minimumWidthCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_minimumWidth>(callback);
        break;
    case 971:
        wrapper->m_move_2Callback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_move_2>(callback);
        break;
    case 972:
        wrapper->m_normalGeometryCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_normalGeometry>(callback);
        break;
    case 973:
        wrapper->m_objectNameCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_objectName>(callback);
        break;
    case 1042:
        wrapper->m_onChildAddedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_onChildAdded>(callback);
        break;
    case 1043:
        wrapper->m_onChildRemovedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_onChildRemoved>(callback);
        break;
    case 1044:
        wrapper->m_onChildVisibilityChangedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_onChildVisibilityChanged>(callback);
        break;
    case 1046:
        wrapper->m_onGeometryChangedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_onGeometryChanged>(callback);
        break;
    case 975:
        wrapper->m_onResize_2Callback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_onResize_2>(callback);
        break;
    case 978:
        wrapper->m_raiseCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_raise>(callback);
        break;
    case 979:
        wrapper->m_raiseAndActivateCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_raiseAndActivate>(callback);
        break;
    case 981:
        wrapper->m_releaseKeyboardCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_releaseKeyboard>(callback);
        break;
    case 982:
        wrapper->m_releaseMouseCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_releaseMouse>(callback);
        break;
    case 986:
        wrapper->m_setCursorCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_setCursor>(callback);
        break;
    case 987:
        wrapper->m_setFixedHeightCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_setFixedHeight>(callback);
        break;
    case 988:
        wrapper->m_setFixedWidthCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_setFixedWidth>(callback);
        break;
    case 989:
        wrapper->m_setGeometryCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_setGeometry>(callback);
        break;
    case 990:
        wrapper->m_setHeightCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_setHeight>(callback);
        break;
    case 991:
        wrapper->m_setMaximumSizeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_setMaximumSize>(callback);
        break;
    case 992:
        wrapper->m_setMinimumSizeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_setMinimumSize>(callback);
        break;
    case 993:
        wrapper->m_setMouseTrackingCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_setMouseTracking>(callback);
        break;
    case 994:
        wrapper->m_setObjectNameCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_setObjectName>(callback);
        break;
    case 995:
        wrapper->m_setParentCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_setParent>(callback);
        break;
    case 997:
        wrapper->m_setSize_2Callback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_setSize_2>(callback);
        break;
    case 998:
        wrapper->m_setVisibleCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_setVisible>(callback);
        break;
    case 999:
        wrapper->m_setWidthCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_setWidth>(callback);
        break;
    case 1000:
        wrapper->m_setWindowOpacityCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_setWindowOpacity>(callback);
        break;
    case 1001:
        wrapper->m_setWindowTitleCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_setWindowTitle>(callback);
        break;
    case 1002:
        wrapper->m_setZOrderCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_setZOrder>(callback);
        break;
    case 1003:
        wrapper->m_showCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_show>(callback);
        break;
    case 1004:
        wrapper->m_showMaximizedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_showMaximized>(callback);
        break;
    case 1005:
        wrapper->m_showMinimizedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_showMinimized>(callback);
        break;
    case 1006:
        wrapper->m_showNormalCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_showNormal>(callback);
        break;
    case 1008:
        wrapper->m_sizeHintCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_sizeHint>(callback);
        break;
    case 1010:
        wrapper->m_updateCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TitleBar_wrapper::Callback_update>(callback);
        break;
    }
}
}

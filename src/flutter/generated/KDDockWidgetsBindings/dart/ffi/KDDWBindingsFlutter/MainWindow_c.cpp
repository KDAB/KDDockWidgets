/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "MainWindow_c.h"


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
MainWindow_wrapper::MainWindow_wrapper(const QString &uniqueName, QFlags<KDDockWidgets::MainWindowOption> options, KDDockWidgets::flutter::View *parent, Qt::WindowFlags flags)
    : ::KDDockWidgets::flutter::MainWindow(uniqueName, options, parent, flags)
{
}
void MainWindow_wrapper::activateWindow()
{
    if (m_activateWindowCallback) {
        const void *thisPtr = this;
        m_activateWindowCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::MainWindow::activateWindow();
    }
}
void MainWindow_wrapper::activateWindow_nocallback()
{
    ::KDDockWidgets::flutter::MainWindow::activateWindow();
}
QRect MainWindow_wrapper::centralAreaGeometry() const
{
    if (m_centralAreaGeometryCallback) {
        const void *thisPtr = this;
        return *m_centralAreaGeometryCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::MainWindow::centralAreaGeometry();
    }
}
QRect MainWindow_wrapper::centralAreaGeometry_nocallback() const
{
    return ::KDDockWidgets::flutter::MainWindow::centralAreaGeometry();
}
bool MainWindow_wrapper::close()
{
    if (m_closeCallback) {
        const void *thisPtr = this;
        return m_closeCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::MainWindow::close();
    }
}
bool MainWindow_wrapper::close_nocallback()
{
    return ::KDDockWidgets::flutter::MainWindow::close();
}
void MainWindow_wrapper::createPlatformWindow()
{
    if (m_createPlatformWindowCallback) {
        const void *thisPtr = this;
        m_createPlatformWindowCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::MainWindow::createPlatformWindow();
    }
}
void MainWindow_wrapper::createPlatformWindow_nocallback()
{
    ::KDDockWidgets::flutter::MainWindow::createPlatformWindow();
}
Qt::WindowFlags MainWindow_wrapper::flags() const
{
    if (m_flagsCallback) {
        const void *thisPtr = this;
        return m_flagsCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::MainWindow::flags();
    }
}
Qt::WindowFlags MainWindow_wrapper::flags_nocallback() const
{
    return ::KDDockWidgets::flutter::MainWindow::flags();
}
QRect MainWindow_wrapper::geometry() const
{
    if (m_geometryCallback) {
        const void *thisPtr = this;
        return *m_geometryCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::MainWindow::geometry();
    }
}
QRect MainWindow_wrapper::geometry_nocallback() const
{
    return ::KDDockWidgets::flutter::MainWindow::geometry();
}
void MainWindow_wrapper::grabMouse()
{
    if (m_grabMouseCallback) {
        const void *thisPtr = this;
        m_grabMouseCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::MainWindow::grabMouse();
    }
}
void MainWindow_wrapper::grabMouse_nocallback()
{
    ::KDDockWidgets::flutter::MainWindow::grabMouse();
}
bool MainWindow_wrapper::hasFocus() const
{
    if (m_hasFocusCallback) {
        const void *thisPtr = this;
        return m_hasFocusCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::MainWindow::hasFocus();
    }
}
bool MainWindow_wrapper::hasFocus_nocallback() const
{
    return ::KDDockWidgets::flutter::MainWindow::hasFocus();
}
void MainWindow_wrapper::hide()
{
    if (m_hideCallback) {
        const void *thisPtr = this;
        m_hideCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::MainWindow::hide();
    }
}
void MainWindow_wrapper::hide_nocallback()
{
    ::KDDockWidgets::flutter::MainWindow::hide();
}
void MainWindow_wrapper::init()
{
    if (m_initCallback) {
        const void *thisPtr = this;
        m_initCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::MainWindow::init();
    }
}
void MainWindow_wrapper::init_nocallback()
{
    ::KDDockWidgets::flutter::MainWindow::init();
}
bool MainWindow_wrapper::isActiveWindow() const
{
    if (m_isActiveWindowCallback) {
        const void *thisPtr = this;
        return m_isActiveWindowCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::MainWindow::isActiveWindow();
    }
}
bool MainWindow_wrapper::isActiveWindow_nocallback() const
{
    return ::KDDockWidgets::flutter::MainWindow::isActiveWindow();
}
bool MainWindow_wrapper::isExplicitlyHidden() const
{
    if (m_isExplicitlyHiddenCallback) {
        const void *thisPtr = this;
        return m_isExplicitlyHiddenCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::MainWindow::isExplicitlyHidden();
    }
}
bool MainWindow_wrapper::isExplicitlyHidden_nocallback() const
{
    return ::KDDockWidgets::flutter::MainWindow::isExplicitlyHidden();
}
bool MainWindow_wrapper::isMaximized() const
{
    if (m_isMaximizedCallback) {
        const void *thisPtr = this;
        return m_isMaximizedCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::MainWindow::isMaximized();
    }
}
bool MainWindow_wrapper::isMaximized_nocallback() const
{
    return ::KDDockWidgets::flutter::MainWindow::isMaximized();
}
bool MainWindow_wrapper::isMinimized() const
{
    if (m_isMinimizedCallback) {
        const void *thisPtr = this;
        return m_isMinimizedCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::MainWindow::isMinimized();
    }
}
bool MainWindow_wrapper::isMinimized_nocallback() const
{
    return ::KDDockWidgets::flutter::MainWindow::isMinimized();
}
bool MainWindow_wrapper::isMounted() const
{
    if (m_isMountedCallback) {
        const void *thisPtr = this;
        return m_isMountedCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::MainWindow::isMounted();
    }
}
bool MainWindow_wrapper::isMounted_nocallback() const
{
    return ::KDDockWidgets::flutter::MainWindow::isMounted();
}
bool MainWindow_wrapper::isNull() const
{
    if (m_isNullCallback) {
        const void *thisPtr = this;
        return m_isNullCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::MainWindow::isNull();
    }
}
bool MainWindow_wrapper::isNull_nocallback() const
{
    return ::KDDockWidgets::flutter::MainWindow::isNull();
}
bool MainWindow_wrapper::isRootView() const
{
    if (m_isRootViewCallback) {
        const void *thisPtr = this;
        return m_isRootViewCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::MainWindow::isRootView();
    }
}
bool MainWindow_wrapper::isRootView_nocallback() const
{
    return ::KDDockWidgets::flutter::MainWindow::isRootView();
}
bool MainWindow_wrapper::isVisible() const
{
    if (m_isVisibleCallback) {
        const void *thisPtr = this;
        return m_isVisibleCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::MainWindow::isVisible();
    }
}
bool MainWindow_wrapper::isVisible_nocallback() const
{
    return ::KDDockWidgets::flutter::MainWindow::isVisible();
}
QPoint MainWindow_wrapper::mapFromGlobal(QPoint globalPt) const
{
    if (m_mapFromGlobalCallback) {
        const void *thisPtr = this;
        return *m_mapFromGlobalCallback(const_cast<void *>(thisPtr), &globalPt);
    } else {
        return ::KDDockWidgets::flutter::MainWindow::mapFromGlobal(globalPt);
    }
}
QPoint MainWindow_wrapper::mapFromGlobal_nocallback(QPoint globalPt) const
{
    return ::KDDockWidgets::flutter::MainWindow::mapFromGlobal(globalPt);
}
QPoint MainWindow_wrapper::mapTo(KDDockWidgets::Core::View *parent, QPoint pos) const
{
    if (m_mapToCallback) {
        const void *thisPtr = this;
        return *m_mapToCallback(const_cast<void *>(thisPtr), parent, &pos);
    } else {
        return ::KDDockWidgets::flutter::MainWindow::mapTo(parent, pos);
    }
}
QPoint MainWindow_wrapper::mapTo_nocallback(KDDockWidgets::Core::View *parent, QPoint pos) const
{
    return ::KDDockWidgets::flutter::MainWindow::mapTo(parent, pos);
}
QPoint MainWindow_wrapper::mapToGlobal(QPoint localPt) const
{
    if (m_mapToGlobalCallback) {
        const void *thisPtr = this;
        return *m_mapToGlobalCallback(const_cast<void *>(thisPtr), &localPt);
    } else {
        return ::KDDockWidgets::flutter::MainWindow::mapToGlobal(localPt);
    }
}
QPoint MainWindow_wrapper::mapToGlobal_nocallback(QPoint localPt) const
{
    return ::KDDockWidgets::flutter::MainWindow::mapToGlobal(localPt);
}
QSize MainWindow_wrapper::maxSizeHint() const
{
    if (m_maxSizeHintCallback) {
        const void *thisPtr = this;
        return *m_maxSizeHintCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::MainWindow::maxSizeHint();
    }
}
QSize MainWindow_wrapper::maxSizeHint_nocallback() const
{
    return ::KDDockWidgets::flutter::MainWindow::maxSizeHint();
}
QSize MainWindow_wrapper::minSize() const
{
    if (m_minSizeCallback) {
        const void *thisPtr = this;
        return *m_minSizeCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::MainWindow::minSize();
    }
}
QSize MainWindow_wrapper::minSize_nocallback() const
{
    return ::KDDockWidgets::flutter::MainWindow::minSize();
}
void MainWindow_wrapper::move(int x, int y)
{
    if (m_move_2Callback) {
        const void *thisPtr = this;
        m_move_2Callback(const_cast<void *>(thisPtr), x, y);
    } else {
        ::KDDockWidgets::flutter::MainWindow::move(x, y);
    }
}
void MainWindow_wrapper::move_nocallback(int x, int y)
{
    ::KDDockWidgets::flutter::MainWindow::move(x, y);
}
QRect MainWindow_wrapper::normalGeometry() const
{
    if (m_normalGeometryCallback) {
        const void *thisPtr = this;
        return *m_normalGeometryCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::MainWindow::normalGeometry();
    }
}
QRect MainWindow_wrapper::normalGeometry_nocallback() const
{
    return ::KDDockWidgets::flutter::MainWindow::normalGeometry();
}
void MainWindow_wrapper::onChildAdded(KDDockWidgets::Core::View *childView)
{
    if (m_onChildAddedCallback) {
        const void *thisPtr = this;
        m_onChildAddedCallback(const_cast<void *>(thisPtr), childView);
    } else {
        ::KDDockWidgets::flutter::MainWindow::onChildAdded(childView);
    }
}
void MainWindow_wrapper::onChildAdded_nocallback(KDDockWidgets::Core::View *childView)
{
    ::KDDockWidgets::flutter::MainWindow::onChildAdded(childView);
}
void MainWindow_wrapper::onChildRemoved(KDDockWidgets::Core::View *childView)
{
    if (m_onChildRemovedCallback) {
        const void *thisPtr = this;
        m_onChildRemovedCallback(const_cast<void *>(thisPtr), childView);
    } else {
        ::KDDockWidgets::flutter::MainWindow::onChildRemoved(childView);
    }
}
void MainWindow_wrapper::onChildRemoved_nocallback(KDDockWidgets::Core::View *childView)
{
    ::KDDockWidgets::flutter::MainWindow::onChildRemoved(childView);
}
void MainWindow_wrapper::onChildVisibilityChanged(KDDockWidgets::Core::View *childView)
{
    if (m_onChildVisibilityChangedCallback) {
        const void *thisPtr = this;
        m_onChildVisibilityChangedCallback(const_cast<void *>(thisPtr), childView);
    } else {
        ::KDDockWidgets::flutter::MainWindow::onChildVisibilityChanged(childView);
    }
}
void MainWindow_wrapper::onChildVisibilityChanged_nocallback(KDDockWidgets::Core::View *childView)
{
    ::KDDockWidgets::flutter::MainWindow::onChildVisibilityChanged(childView);
}
void MainWindow_wrapper::onGeometryChanged()
{
    if (m_onGeometryChangedCallback) {
        const void *thisPtr = this;
        m_onGeometryChangedCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::MainWindow::onGeometryChanged();
    }
}
void MainWindow_wrapper::onGeometryChanged_nocallback()
{
    ::KDDockWidgets::flutter::MainWindow::onGeometryChanged();
}
void MainWindow_wrapper::onRebuildRequested()
{
    if (m_onRebuildRequestedCallback) {
        const void *thisPtr = this;
        m_onRebuildRequestedCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::MainWindow::onRebuildRequested();
    }
}
void MainWindow_wrapper::onRebuildRequested_nocallback()
{
    ::KDDockWidgets::flutter::MainWindow::onRebuildRequested();
}
bool MainWindow_wrapper::onResize(int h, int w)
{
    if (m_onResize_2Callback) {
        const void *thisPtr = this;
        return m_onResize_2Callback(const_cast<void *>(thisPtr), h, w);
    } else {
        return ::KDDockWidgets::flutter::MainWindow::onResize(h, w);
    }
}
bool MainWindow_wrapper::onResize_nocallback(int h, int w)
{
    return ::KDDockWidgets::flutter::MainWindow::onResize(h, w);
}
void MainWindow_wrapper::raise()
{
    if (m_raiseCallback) {
        const void *thisPtr = this;
        m_raiseCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::MainWindow::raise();
    }
}
void MainWindow_wrapper::raise_nocallback()
{
    ::KDDockWidgets::flutter::MainWindow::raise();
}
void MainWindow_wrapper::raiseAndActivate()
{
    if (m_raiseAndActivateCallback) {
        const void *thisPtr = this;
        m_raiseAndActivateCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::MainWindow::raiseAndActivate();
    }
}
void MainWindow_wrapper::raiseAndActivate_nocallback()
{
    ::KDDockWidgets::flutter::MainWindow::raiseAndActivate();
}
void MainWindow_wrapper::raiseChild(KDDockWidgets::Core::View *childView)
{
    if (m_raiseChildCallback) {
        const void *thisPtr = this;
        m_raiseChildCallback(const_cast<void *>(thisPtr), childView);
    } else {
        ::KDDockWidgets::flutter::MainWindow::raiseChild(childView);
    }
}
void MainWindow_wrapper::raiseChild_nocallback(KDDockWidgets::Core::View *childView)
{
    ::KDDockWidgets::flutter::MainWindow::raiseChild(childView);
}
void MainWindow_wrapper::raiseWindow(KDDockWidgets::Core::View *rootView)
{
    if (m_raiseWindowCallback) {
        const void *thisPtr = this;
        m_raiseWindowCallback(const_cast<void *>(thisPtr), rootView);
    } else {
        ::KDDockWidgets::flutter::MainWindow::raiseWindow(rootView);
    }
}
void MainWindow_wrapper::raiseWindow_nocallback(KDDockWidgets::Core::View *rootView)
{
    ::KDDockWidgets::flutter::MainWindow::raiseWindow(rootView);
}
void MainWindow_wrapper::releaseKeyboard()
{
    if (m_releaseKeyboardCallback) {
        const void *thisPtr = this;
        m_releaseKeyboardCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::MainWindow::releaseKeyboard();
    }
}
void MainWindow_wrapper::releaseKeyboard_nocallback()
{
    ::KDDockWidgets::flutter::MainWindow::releaseKeyboard();
}
void MainWindow_wrapper::releaseMouse()
{
    if (m_releaseMouseCallback) {
        const void *thisPtr = this;
        m_releaseMouseCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::MainWindow::releaseMouse();
    }
}
void MainWindow_wrapper::releaseMouse_nocallback()
{
    ::KDDockWidgets::flutter::MainWindow::releaseMouse();
}
void MainWindow_wrapper::setContentsMargins(int left, int top, int right, int bottom)
{
    if (m_setContentsMarginsCallback) {
        const void *thisPtr = this;
        m_setContentsMarginsCallback(const_cast<void *>(thisPtr), left, top, right, bottom);
    } else {
        ::KDDockWidgets::flutter::MainWindow::setContentsMargins(left, top, right, bottom);
    }
}
void MainWindow_wrapper::setContentsMargins_nocallback(int left, int top, int right, int bottom)
{
    ::KDDockWidgets::flutter::MainWindow::setContentsMargins(left, top, right, bottom);
}
void MainWindow_wrapper::setCursor(Qt::CursorShape shape)
{
    if (m_setCursorCallback) {
        const void *thisPtr = this;
        m_setCursorCallback(const_cast<void *>(thisPtr), shape);
    } else {
        ::KDDockWidgets::flutter::MainWindow::setCursor(shape);
    }
}
void MainWindow_wrapper::setCursor_nocallback(Qt::CursorShape shape)
{
    ::KDDockWidgets::flutter::MainWindow::setCursor(shape);
}
void MainWindow_wrapper::setFixedHeight(int h)
{
    if (m_setFixedHeightCallback) {
        const void *thisPtr = this;
        m_setFixedHeightCallback(const_cast<void *>(thisPtr), h);
    } else {
        ::KDDockWidgets::flutter::MainWindow::setFixedHeight(h);
    }
}
void MainWindow_wrapper::setFixedHeight_nocallback(int h)
{
    ::KDDockWidgets::flutter::MainWindow::setFixedHeight(h);
}
void MainWindow_wrapper::setFixedWidth(int w)
{
    if (m_setFixedWidthCallback) {
        const void *thisPtr = this;
        m_setFixedWidthCallback(const_cast<void *>(thisPtr), w);
    } else {
        ::KDDockWidgets::flutter::MainWindow::setFixedWidth(w);
    }
}
void MainWindow_wrapper::setFixedWidth_nocallback(int w)
{
    ::KDDockWidgets::flutter::MainWindow::setFixedWidth(w);
}
void MainWindow_wrapper::setGeometry(QRect geometry)
{
    if (m_setGeometryCallback) {
        const void *thisPtr = this;
        m_setGeometryCallback(const_cast<void *>(thisPtr), &geometry);
    } else {
        ::KDDockWidgets::flutter::MainWindow::setGeometry(geometry);
    }
}
void MainWindow_wrapper::setGeometry_nocallback(QRect geometry)
{
    ::KDDockWidgets::flutter::MainWindow::setGeometry(geometry);
}
void MainWindow_wrapper::setHeight(int h)
{
    if (m_setHeightCallback) {
        const void *thisPtr = this;
        m_setHeightCallback(const_cast<void *>(thisPtr), h);
    } else {
        ::KDDockWidgets::flutter::MainWindow::setHeight(h);
    }
}
void MainWindow_wrapper::setHeight_nocallback(int h)
{
    ::KDDockWidgets::flutter::MainWindow::setHeight(h);
}
void MainWindow_wrapper::setMaximumSize(QSize sz)
{
    if (m_setMaximumSizeCallback) {
        const void *thisPtr = this;
        m_setMaximumSizeCallback(const_cast<void *>(thisPtr), &sz);
    } else {
        ::KDDockWidgets::flutter::MainWindow::setMaximumSize(sz);
    }
}
void MainWindow_wrapper::setMaximumSize_nocallback(QSize sz)
{
    ::KDDockWidgets::flutter::MainWindow::setMaximumSize(sz);
}
void MainWindow_wrapper::setMinimumSize(QSize sz)
{
    if (m_setMinimumSizeCallback) {
        const void *thisPtr = this;
        m_setMinimumSizeCallback(const_cast<void *>(thisPtr), &sz);
    } else {
        ::KDDockWidgets::flutter::MainWindow::setMinimumSize(sz);
    }
}
void MainWindow_wrapper::setMinimumSize_nocallback(QSize sz)
{
    ::KDDockWidgets::flutter::MainWindow::setMinimumSize(sz);
}
void MainWindow_wrapper::setMouseTracking(bool enable)
{
    if (m_setMouseTrackingCallback) {
        const void *thisPtr = this;
        m_setMouseTrackingCallback(const_cast<void *>(thisPtr), enable);
    } else {
        ::KDDockWidgets::flutter::MainWindow::setMouseTracking(enable);
    }
}
void MainWindow_wrapper::setMouseTracking_nocallback(bool enable)
{
    ::KDDockWidgets::flutter::MainWindow::setMouseTracking(enable);
}
void MainWindow_wrapper::setParent(KDDockWidgets::Core::View *parent)
{
    if (m_setParentCallback) {
        const void *thisPtr = this;
        m_setParentCallback(const_cast<void *>(thisPtr), parent);
    } else {
        ::KDDockWidgets::flutter::MainWindow::setParent(parent);
    }
}
void MainWindow_wrapper::setParent_nocallback(KDDockWidgets::Core::View *parent)
{
    ::KDDockWidgets::flutter::MainWindow::setParent(parent);
}
void MainWindow_wrapper::setSize(int w, int h)
{
    if (m_setSize_2Callback) {
        const void *thisPtr = this;
        m_setSize_2Callback(const_cast<void *>(thisPtr), w, h);
    } else {
        ::KDDockWidgets::flutter::MainWindow::setSize(w, h);
    }
}
void MainWindow_wrapper::setSize_nocallback(int w, int h)
{
    ::KDDockWidgets::flutter::MainWindow::setSize(w, h);
}
void MainWindow_wrapper::setViewName(const QString &name)
{
    if (m_setViewNameCallback) {
        const void *thisPtr = this;
        m_setViewNameCallback(const_cast<void *>(thisPtr), name);
    } else {
        ::KDDockWidgets::flutter::MainWindow::setViewName(name);
    }
}
void MainWindow_wrapper::setViewName_nocallback(const QString &name)
{
    ::KDDockWidgets::flutter::MainWindow::setViewName(name);
}
void MainWindow_wrapper::setVisible(bool visible)
{
    if (m_setVisibleCallback) {
        const void *thisPtr = this;
        m_setVisibleCallback(const_cast<void *>(thisPtr), visible);
    } else {
        ::KDDockWidgets::flutter::MainWindow::setVisible(visible);
    }
}
void MainWindow_wrapper::setVisible_nocallback(bool visible)
{
    ::KDDockWidgets::flutter::MainWindow::setVisible(visible);
}
void MainWindow_wrapper::setWidth(int w)
{
    if (m_setWidthCallback) {
        const void *thisPtr = this;
        m_setWidthCallback(const_cast<void *>(thisPtr), w);
    } else {
        ::KDDockWidgets::flutter::MainWindow::setWidth(w);
    }
}
void MainWindow_wrapper::setWidth_nocallback(int w)
{
    ::KDDockWidgets::flutter::MainWindow::setWidth(w);
}
void MainWindow_wrapper::setWindowOpacity(double v)
{
    if (m_setWindowOpacityCallback) {
        const void *thisPtr = this;
        m_setWindowOpacityCallback(const_cast<void *>(thisPtr), v);
    } else {
        ::KDDockWidgets::flutter::MainWindow::setWindowOpacity(v);
    }
}
void MainWindow_wrapper::setWindowOpacity_nocallback(double v)
{
    ::KDDockWidgets::flutter::MainWindow::setWindowOpacity(v);
}
void MainWindow_wrapper::setWindowTitle(const QString &title)
{
    if (m_setWindowTitleCallback) {
        const void *thisPtr = this;
        m_setWindowTitleCallback(const_cast<void *>(thisPtr), title);
    } else {
        ::KDDockWidgets::flutter::MainWindow::setWindowTitle(title);
    }
}
void MainWindow_wrapper::setWindowTitle_nocallback(const QString &title)
{
    ::KDDockWidgets::flutter::MainWindow::setWindowTitle(title);
}
void MainWindow_wrapper::setZOrder(int z)
{
    if (m_setZOrderCallback) {
        const void *thisPtr = this;
        m_setZOrderCallback(const_cast<void *>(thisPtr), z);
    } else {
        ::KDDockWidgets::flutter::MainWindow::setZOrder(z);
    }
}
void MainWindow_wrapper::setZOrder_nocallback(int z)
{
    ::KDDockWidgets::flutter::MainWindow::setZOrder(z);
}
void MainWindow_wrapper::show()
{
    if (m_showCallback) {
        const void *thisPtr = this;
        m_showCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::MainWindow::show();
    }
}
void MainWindow_wrapper::show_nocallback()
{
    ::KDDockWidgets::flutter::MainWindow::show();
}
void MainWindow_wrapper::showMaximized()
{
    if (m_showMaximizedCallback) {
        const void *thisPtr = this;
        m_showMaximizedCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::MainWindow::showMaximized();
    }
}
void MainWindow_wrapper::showMaximized_nocallback()
{
    ::KDDockWidgets::flutter::MainWindow::showMaximized();
}
void MainWindow_wrapper::showMinimized()
{
    if (m_showMinimizedCallback) {
        const void *thisPtr = this;
        m_showMinimizedCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::MainWindow::showMinimized();
    }
}
void MainWindow_wrapper::showMinimized_nocallback()
{
    ::KDDockWidgets::flutter::MainWindow::showMinimized();
}
void MainWindow_wrapper::showNormal()
{
    if (m_showNormalCallback) {
        const void *thisPtr = this;
        m_showNormalCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::MainWindow::showNormal();
    }
}
void MainWindow_wrapper::showNormal_nocallback()
{
    ::KDDockWidgets::flutter::MainWindow::showNormal();
}
void MainWindow_wrapper::update()
{
    if (m_updateCallback) {
        const void *thisPtr = this;
        m_updateCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::MainWindow::update();
    }
}
void MainWindow_wrapper::update_nocallback()
{
    ::KDDockWidgets::flutter::MainWindow::update();
}
QString MainWindow_wrapper::viewName() const
{
    if (m_viewNameCallback) {
        const void *thisPtr = this;
        return *m_viewNameCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::MainWindow::viewName();
    }
}
QString MainWindow_wrapper::viewName_nocallback() const
{
    return ::KDDockWidgets::flutter::MainWindow::viewName();
}
MainWindow_wrapper::~MainWindow_wrapper()
{
}

}
}
static KDDockWidgets::flutter::MainWindow *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::flutter::MainWindow *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__flutter__MainWindow_Finalizer(void *cppObj)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper *>(cppObj);
}
void *c_KDDockWidgets__flutter__MainWindow__constructor_QString_MainWindowOptions_View_WindowFlags(const char *uniqueName_, int options_, void *parent_, int flags)
{
    const auto uniqueName = QString::fromUtf8(uniqueName_);
    auto options = static_cast<QFlags<KDDockWidgets::MainWindowOption>>(options_);
    auto parent = reinterpret_cast<KDDockWidgets::flutter::View *>(parent_);
    auto ptr = new KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper(uniqueName, options, parent, static_cast<Qt::WindowFlags>(flags));
    return reinterpret_cast<void *>(ptr);
}
// activateWindow()
void c_KDDockWidgets__flutter__MainWindow__activateWindow(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->activateWindow_nocallback();} else {    return targetPtr->activateWindow();} }();
}
// centralAreaGeometry() const
void *c_KDDockWidgets__flutter__MainWindow__centralAreaGeometry(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QRect> { fromWrapperPtr(thisObj)->centralAreaGeometry_nocallback() };
}
// close()
bool c_KDDockWidgets__flutter__MainWindow__close(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->close_nocallback();} else {    return targetPtr->close();} }();
}
// createPlatformWindow()
void c_KDDockWidgets__flutter__MainWindow__createPlatformWindow(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->createPlatformWindow_nocallback();} else {    return targetPtr->createPlatformWindow();} }();
}
// flags() const
int c_KDDockWidgets__flutter__MainWindow__flags(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->flags_nocallback();} else {    return targetPtr->flags();} }();
}
// geometry() const
void *c_KDDockWidgets__flutter__MainWindow__geometry(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QRect> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->geometry_nocallback();} else {    return targetPtr->geometry();} }() };
}
// grabMouse()
void c_KDDockWidgets__flutter__MainWindow__grabMouse(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->grabMouse_nocallback();} else {    return targetPtr->grabMouse();} }();
}
// hasFocus() const
bool c_KDDockWidgets__flutter__MainWindow__hasFocus(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->hasFocus_nocallback();} else {    return targetPtr->hasFocus();} }();
}
// hide()
void c_KDDockWidgets__flutter__MainWindow__hide(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->hide_nocallback();} else {    return targetPtr->hide();} }();
}
// init()
void c_KDDockWidgets__flutter__MainWindow__init(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->init_nocallback();} else {    return targetPtr->init();} }();
}
// isActiveWindow() const
bool c_KDDockWidgets__flutter__MainWindow__isActiveWindow(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isActiveWindow_nocallback();} else {    return targetPtr->isActiveWindow();} }();
}
// isExplicitlyHidden() const
bool c_KDDockWidgets__flutter__MainWindow__isExplicitlyHidden(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isExplicitlyHidden_nocallback();} else {    return targetPtr->isExplicitlyHidden();} }();
}
// isMaximized() const
bool c_KDDockWidgets__flutter__MainWindow__isMaximized(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isMaximized_nocallback();} else {    return targetPtr->isMaximized();} }();
}
// isMinimized() const
bool c_KDDockWidgets__flutter__MainWindow__isMinimized(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isMinimized_nocallback();} else {    return targetPtr->isMinimized();} }();
}
// isMounted() const
bool c_KDDockWidgets__flutter__MainWindow__isMounted(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isMounted_nocallback();} else {    return targetPtr->isMounted();} }();
}
// isNull() const
bool c_KDDockWidgets__flutter__MainWindow__isNull(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isNull_nocallback();} else {    return targetPtr->isNull();} }();
}
// isRootView() const
bool c_KDDockWidgets__flutter__MainWindow__isRootView(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isRootView_nocallback();} else {    return targetPtr->isRootView();} }();
}
// isVisible() const
bool c_KDDockWidgets__flutter__MainWindow__isVisible(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isVisible_nocallback();} else {    return targetPtr->isVisible();} }();
}
// mapFromGlobal(QPoint globalPt) const
void *c_KDDockWidgets__flutter__MainWindow__mapFromGlobal_QPoint(void *thisObj, void *globalPt_)
{
    assert(globalPt_);
    auto &globalPt = *reinterpret_cast<QPoint *>(globalPt_);
    return new Dartagnan::ValueWrapper<QPoint> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->mapFromGlobal_nocallback(globalPt);} else {    return targetPtr->mapFromGlobal(globalPt);} }() };
}
// mapTo(KDDockWidgets::Core::View * parent, QPoint pos) const
void *c_KDDockWidgets__flutter__MainWindow__mapTo_View_QPoint(void *thisObj, void *parent_, void *pos_)
{
    auto parent = reinterpret_cast<KDDockWidgets::Core::View *>(parent_);
    assert(pos_);
    auto &pos = *reinterpret_cast<QPoint *>(pos_);
    return new Dartagnan::ValueWrapper<QPoint> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->mapTo_nocallback(parent,pos);} else {    return targetPtr->mapTo(parent,pos);} }() };
}
// mapToGlobal(QPoint localPt) const
void *c_KDDockWidgets__flutter__MainWindow__mapToGlobal_QPoint(void *thisObj, void *localPt_)
{
    assert(localPt_);
    auto &localPt = *reinterpret_cast<QPoint *>(localPt_);
    return new Dartagnan::ValueWrapper<QPoint> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->mapToGlobal_nocallback(localPt);} else {    return targetPtr->mapToGlobal(localPt);} }() };
}
// maxSizeHint() const
void *c_KDDockWidgets__flutter__MainWindow__maxSizeHint(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->maxSizeHint_nocallback();} else {    return targetPtr->maxSizeHint();} }() };
}
// minSize() const
void *c_KDDockWidgets__flutter__MainWindow__minSize(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->minSize_nocallback();} else {    return targetPtr->minSize();} }() };
}
// move(int x, int y)
void c_KDDockWidgets__flutter__MainWindow__move_int_int(void *thisObj, int x, int y)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->move_nocallback(x,y);} else {    return targetPtr->move(x,y);} }();
}
// normalGeometry() const
void *c_KDDockWidgets__flutter__MainWindow__normalGeometry(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QRect> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->normalGeometry_nocallback();} else {    return targetPtr->normalGeometry();} }() };
}
// onChildAdded(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__MainWindow__onChildAdded_View(void *thisObj, void *childView_)
{
    auto childView = reinterpret_cast<KDDockWidgets::Core::View *>(childView_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->onChildAdded_nocallback(childView);} else {    return targetPtr->onChildAdded(childView);} }();
}
// onChildRemoved(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__MainWindow__onChildRemoved_View(void *thisObj, void *childView_)
{
    auto childView = reinterpret_cast<KDDockWidgets::Core::View *>(childView_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->onChildRemoved_nocallback(childView);} else {    return targetPtr->onChildRemoved(childView);} }();
}
// onChildVisibilityChanged(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__MainWindow__onChildVisibilityChanged_View(void *thisObj, void *childView_)
{
    auto childView = reinterpret_cast<KDDockWidgets::Core::View *>(childView_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->onChildVisibilityChanged_nocallback(childView);} else {    return targetPtr->onChildVisibilityChanged(childView);} }();
}
// onGeometryChanged()
void c_KDDockWidgets__flutter__MainWindow__onGeometryChanged(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->onGeometryChanged_nocallback();} else {    return targetPtr->onGeometryChanged();} }();
}
// onRebuildRequested()
void c_KDDockWidgets__flutter__MainWindow__onRebuildRequested(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->onRebuildRequested_nocallback();} else {    return targetPtr->onRebuildRequested();} }();
}
// onResize(int h, int w)
bool c_KDDockWidgets__flutter__MainWindow__onResize_int_int(void *thisObj, int h, int w)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->onResize_nocallback(h,w);} else {    return targetPtr->onResize(h,w);} }();
}
// raise()
void c_KDDockWidgets__flutter__MainWindow__raise(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->raise_nocallback();} else {    return targetPtr->raise();} }();
}
// raiseAndActivate()
void c_KDDockWidgets__flutter__MainWindow__raiseAndActivate(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->raiseAndActivate_nocallback();} else {    return targetPtr->raiseAndActivate();} }();
}
// raiseChild(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__MainWindow__raiseChild_View(void *thisObj, void *childView_)
{
    auto childView = reinterpret_cast<KDDockWidgets::Core::View *>(childView_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->raiseChild_nocallback(childView);} else {    return targetPtr->raiseChild(childView);} }();
}
// raiseWindow(KDDockWidgets::Core::View * rootView)
void c_KDDockWidgets__flutter__MainWindow__raiseWindow_View(void *thisObj, void *rootView_)
{
    auto rootView = reinterpret_cast<KDDockWidgets::Core::View *>(rootView_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->raiseWindow_nocallback(rootView);} else {    return targetPtr->raiseWindow(rootView);} }();
}
// releaseKeyboard()
void c_KDDockWidgets__flutter__MainWindow__releaseKeyboard(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->releaseKeyboard_nocallback();} else {    return targetPtr->releaseKeyboard();} }();
}
// releaseMouse()
void c_KDDockWidgets__flutter__MainWindow__releaseMouse(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->releaseMouse_nocallback();} else {    return targetPtr->releaseMouse();} }();
}
// setContentsMargins(int left, int top, int right, int bottom)
void c_KDDockWidgets__flutter__MainWindow__setContentsMargins_int_int_int_int(void *thisObj, int left, int top, int right, int bottom)
{
    fromWrapperPtr(thisObj)->setContentsMargins_nocallback(left, top, right, bottom);
}
// setCursor(Qt::CursorShape shape)
void c_KDDockWidgets__flutter__MainWindow__setCursor_CursorShape(void *thisObj, int shape)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setCursor_nocallback(static_cast<Qt::CursorShape>(shape));} else {    return targetPtr->setCursor(static_cast<Qt::CursorShape>(shape));} }();
}
// setFixedHeight(int h)
void c_KDDockWidgets__flutter__MainWindow__setFixedHeight_int(void *thisObj, int h)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setFixedHeight_nocallback(h);} else {    return targetPtr->setFixedHeight(h);} }();
}
// setFixedWidth(int w)
void c_KDDockWidgets__flutter__MainWindow__setFixedWidth_int(void *thisObj, int w)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setFixedWidth_nocallback(w);} else {    return targetPtr->setFixedWidth(w);} }();
}
// setGeometry(QRect geometry)
void c_KDDockWidgets__flutter__MainWindow__setGeometry_QRect(void *thisObj, void *geometry_)
{
    assert(geometry_);
    auto &geometry = *reinterpret_cast<QRect *>(geometry_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setGeometry_nocallback(geometry);} else {    return targetPtr->setGeometry(geometry);} }();
}
// setHeight(int h)
void c_KDDockWidgets__flutter__MainWindow__setHeight_int(void *thisObj, int h)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setHeight_nocallback(h);} else {    return targetPtr->setHeight(h);} }();
}
// setMaximumSize(QSize sz)
void c_KDDockWidgets__flutter__MainWindow__setMaximumSize_QSize(void *thisObj, void *sz_)
{
    assert(sz_);
    auto &sz = *reinterpret_cast<QSize *>(sz_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setMaximumSize_nocallback(sz);} else {    return targetPtr->setMaximumSize(sz);} }();
}
// setMinimumSize(QSize sz)
void c_KDDockWidgets__flutter__MainWindow__setMinimumSize_QSize(void *thisObj, void *sz_)
{
    assert(sz_);
    auto &sz = *reinterpret_cast<QSize *>(sz_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setMinimumSize_nocallback(sz);} else {    return targetPtr->setMinimumSize(sz);} }();
}
// setMouseTracking(bool enable)
void c_KDDockWidgets__flutter__MainWindow__setMouseTracking_bool(void *thisObj, bool enable)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setMouseTracking_nocallback(enable);} else {    return targetPtr->setMouseTracking(enable);} }();
}
// setParent(KDDockWidgets::Core::View * parent)
void c_KDDockWidgets__flutter__MainWindow__setParent_View(void *thisObj, void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::Core::View *>(parent_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setParent_nocallback(parent);} else {    return targetPtr->setParent(parent);} }();
}
// setSize(int w, int h)
void c_KDDockWidgets__flutter__MainWindow__setSize_int_int(void *thisObj, int w, int h)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setSize_nocallback(w,h);} else {    return targetPtr->setSize(w,h);} }();
}
// setViewName(const QString & name)
void c_KDDockWidgets__flutter__MainWindow__setViewName_QString(void *thisObj, const char *name_)
{
    const auto name = QString::fromUtf8(name_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setViewName_nocallback(name);} else {    return targetPtr->setViewName(name);} }();
}
// setVisible(bool visible)
void c_KDDockWidgets__flutter__MainWindow__setVisible_bool(void *thisObj, bool visible)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setVisible_nocallback(visible);} else {    return targetPtr->setVisible(visible);} }();
}
// setWidth(int w)
void c_KDDockWidgets__flutter__MainWindow__setWidth_int(void *thisObj, int w)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setWidth_nocallback(w);} else {    return targetPtr->setWidth(w);} }();
}
// setWindowOpacity(double v)
void c_KDDockWidgets__flutter__MainWindow__setWindowOpacity_double(void *thisObj, double v)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setWindowOpacity_nocallback(v);} else {    return targetPtr->setWindowOpacity(v);} }();
}
// setWindowTitle(const QString & title)
void c_KDDockWidgets__flutter__MainWindow__setWindowTitle_QString(void *thisObj, const char *title_)
{
    const auto title = QString::fromUtf8(title_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setWindowTitle_nocallback(title);} else {    return targetPtr->setWindowTitle(title);} }();
}
// setZOrder(int z)
void c_KDDockWidgets__flutter__MainWindow__setZOrder_int(void *thisObj, int z)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setZOrder_nocallback(z);} else {    return targetPtr->setZOrder(z);} }();
}
// show()
void c_KDDockWidgets__flutter__MainWindow__show(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->show_nocallback();} else {    return targetPtr->show();} }();
}
// showMaximized()
void c_KDDockWidgets__flutter__MainWindow__showMaximized(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->showMaximized_nocallback();} else {    return targetPtr->showMaximized();} }();
}
// showMinimized()
void c_KDDockWidgets__flutter__MainWindow__showMinimized(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->showMinimized_nocallback();} else {    return targetPtr->showMinimized();} }();
}
// showNormal()
void c_KDDockWidgets__flutter__MainWindow__showNormal(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->showNormal_nocallback();} else {    return targetPtr->showNormal();} }();
}
// update()
void c_KDDockWidgets__flutter__MainWindow__update(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->update_nocallback();} else {    return targetPtr->update();} }();
}
// viewName() const
void *c_KDDockWidgets__flutter__MainWindow__viewName(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QString> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->viewName_nocallback();} else {    return targetPtr->viewName();} }() };
}
void c_KDDockWidgets__flutter__MainWindow__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__flutter__MainWindow__registerVirtualMethodCallback(void *ptr, void *callback, int methodId)
{
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 824:
        wrapper->m_activateWindowCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_activateWindow>(callback);
        break;
    case 978:
        wrapper->m_centralAreaGeometryCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_centralAreaGeometry>(callback);
        break;
    case 834:
        wrapper->m_closeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_close>(callback);
        break;
    case 836:
        wrapper->m_createPlatformWindowCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_createPlatformWindow>(callback);
        break;
    case 842:
        wrapper->m_flagsCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_flags>(callback);
        break;
    case 843:
        wrapper->m_geometryCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_geometry>(callback);
        break;
    case 844:
        wrapper->m_grabMouseCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_grabMouse>(callback);
        break;
    case 847:
        wrapper->m_hasFocusCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_hasFocus>(callback);
        break;
    case 849:
        wrapper->m_hideCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_hide>(callback);
        break;
    case 851:
        wrapper->m_initCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_init>(callback);
        break;
    case 853:
        wrapper->m_isActiveWindowCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_isActiveWindow>(callback);
        break;
    case 854:
        wrapper->m_isExplicitlyHiddenCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_isExplicitlyHidden>(callback);
        break;
    case 855:
        wrapper->m_isMaximizedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_isMaximized>(callback);
        break;
    case 856:
        wrapper->m_isMinimizedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_isMinimized>(callback);
        break;
    case 926:
        wrapper->m_isMountedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_isMounted>(callback);
        break;
    case 857:
        wrapper->m_isNullCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_isNull>(callback);
        break;
    case 858:
        wrapper->m_isRootViewCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_isRootView>(callback);
        break;
    case 859:
        wrapper->m_isVisibleCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_isVisible>(callback);
        break;
    case 860:
        wrapper->m_mapFromGlobalCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_mapFromGlobal>(callback);
        break;
    case 861:
        wrapper->m_mapToCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_mapTo>(callback);
        break;
    case 862:
        wrapper->m_mapToGlobalCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_mapToGlobal>(callback);
        break;
    case 863:
        wrapper->m_maxSizeHintCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_maxSizeHint>(callback);
        break;
    case 864:
        wrapper->m_minSizeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_minSize>(callback);
        break;
    case 868:
        wrapper->m_move_2Callback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_move_2>(callback);
        break;
    case 869:
        wrapper->m_normalGeometryCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_normalGeometry>(callback);
        break;
    case 929:
        wrapper->m_onChildAddedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_onChildAdded>(callback);
        break;
    case 930:
        wrapper->m_onChildRemovedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_onChildRemoved>(callback);
        break;
    case 931:
        wrapper->m_onChildVisibilityChangedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_onChildVisibilityChanged>(callback);
        break;
    case 933:
        wrapper->m_onGeometryChangedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_onGeometryChanged>(callback);
        break;
    case 935:
        wrapper->m_onRebuildRequestedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_onRebuildRequested>(callback);
        break;
    case 871:
        wrapper->m_onResize_2Callback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_onResize_2>(callback);
        break;
    case 873:
        wrapper->m_raiseCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_raise>(callback);
        break;
    case 874:
        wrapper->m_raiseAndActivateCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_raiseAndActivate>(callback);
        break;
    case 938:
        wrapper->m_raiseChildCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_raiseChild>(callback);
        break;
    case 939:
        wrapper->m_raiseWindowCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_raiseWindow>(callback);
        break;
    case 876:
        wrapper->m_releaseKeyboardCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_releaseKeyboard>(callback);
        break;
    case 877:
        wrapper->m_releaseMouseCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_releaseMouse>(callback);
        break;
    case 981:
        wrapper->m_setContentsMarginsCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_setContentsMargins>(callback);
        break;
    case 880:
        wrapper->m_setCursorCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_setCursor>(callback);
        break;
    case 881:
        wrapper->m_setFixedHeightCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_setFixedHeight>(callback);
        break;
    case 882:
        wrapper->m_setFixedWidthCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_setFixedWidth>(callback);
        break;
    case 883:
        wrapper->m_setGeometryCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_setGeometry>(callback);
        break;
    case 884:
        wrapper->m_setHeightCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_setHeight>(callback);
        break;
    case 885:
        wrapper->m_setMaximumSizeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_setMaximumSize>(callback);
        break;
    case 886:
        wrapper->m_setMinimumSizeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_setMinimumSize>(callback);
        break;
    case 887:
        wrapper->m_setMouseTrackingCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_setMouseTracking>(callback);
        break;
    case 888:
        wrapper->m_setParentCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_setParent>(callback);
        break;
    case 890:
        wrapper->m_setSize_2Callback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_setSize_2>(callback);
        break;
    case 891:
        wrapper->m_setViewNameCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_setViewName>(callback);
        break;
    case 892:
        wrapper->m_setVisibleCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_setVisible>(callback);
        break;
    case 893:
        wrapper->m_setWidthCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_setWidth>(callback);
        break;
    case 894:
        wrapper->m_setWindowOpacityCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_setWindowOpacity>(callback);
        break;
    case 895:
        wrapper->m_setWindowTitleCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_setWindowTitle>(callback);
        break;
    case 896:
        wrapper->m_setZOrderCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_setZOrder>(callback);
        break;
    case 897:
        wrapper->m_showCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_show>(callback);
        break;
    case 898:
        wrapper->m_showMaximizedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_showMaximized>(callback);
        break;
    case 899:
        wrapper->m_showMinimizedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_showMinimized>(callback);
        break;
    case 900:
        wrapper->m_showNormalCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_showNormal>(callback);
        break;
    case 902:
        wrapper->m_updateCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_update>(callback);
        break;
    case 903:
        wrapper->m_viewNameCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::MainWindow_wrapper::Callback_viewName>(callback);
        break;
    }
}
}

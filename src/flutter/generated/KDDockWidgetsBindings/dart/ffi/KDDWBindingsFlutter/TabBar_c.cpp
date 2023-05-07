/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "TabBar_c.h"


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
TabBar_wrapper::TabBar_wrapper(KDDockWidgets::Core::TabBar *controller, KDDockWidgets::Core::View *parent)
    : ::KDDockWidgets::flutter::TabBar(controller, parent)
{
}
void TabBar_wrapper::activateWindow()
{
    if (m_activateWindowCallback) {
        const void *thisPtr = this;
        m_activateWindowCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::TabBar::activateWindow();
    }
}
void TabBar_wrapper::activateWindow_nocallback()
{
    ::KDDockWidgets::flutter::TabBar::activateWindow();
}
bool TabBar_wrapper::close()
{
    if (m_closeCallback) {
        const void *thisPtr = this;
        return m_closeCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TabBar::close();
    }
}
bool TabBar_wrapper::close_nocallback()
{
    return ::KDDockWidgets::flutter::TabBar::close();
}
void TabBar_wrapper::createPlatformWindow()
{
    if (m_createPlatformWindowCallback) {
        const void *thisPtr = this;
        m_createPlatformWindowCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::TabBar::createPlatformWindow();
    }
}
void TabBar_wrapper::createPlatformWindow_nocallback()
{
    ::KDDockWidgets::flutter::TabBar::createPlatformWindow();
}
Qt::WindowFlags TabBar_wrapper::flags() const
{
    if (m_flagsCallback) {
        const void *thisPtr = this;
        return m_flagsCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TabBar::flags();
    }
}
Qt::WindowFlags TabBar_wrapper::flags_nocallback() const
{
    return ::KDDockWidgets::flutter::TabBar::flags();
}
void TabBar_wrapper::free_impl()
{
    if (m_free_implCallback) {
        const void *thisPtr = this;
        m_free_implCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::TabBar::free_impl();
    }
}
void TabBar_wrapper::free_impl_nocallback()
{
    ::KDDockWidgets::flutter::TabBar::free_impl();
}
QRect TabBar_wrapper::geometry() const
{
    if (m_geometryCallback) {
        const void *thisPtr = this;
        return *m_geometryCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TabBar::geometry();
    }
}
QRect TabBar_wrapper::geometry_nocallback() const
{
    return ::KDDockWidgets::flutter::TabBar::geometry();
}
void TabBar_wrapper::grabMouse()
{
    if (m_grabMouseCallback) {
        const void *thisPtr = this;
        m_grabMouseCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::TabBar::grabMouse();
    }
}
void TabBar_wrapper::grabMouse_nocallback()
{
    ::KDDockWidgets::flutter::TabBar::grabMouse();
}
bool TabBar_wrapper::hasFocus() const
{
    if (m_hasFocusCallback) {
        const void *thisPtr = this;
        return m_hasFocusCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TabBar::hasFocus();
    }
}
bool TabBar_wrapper::hasFocus_nocallback() const
{
    return ::KDDockWidgets::flutter::TabBar::hasFocus();
}
void TabBar_wrapper::hide()
{
    if (m_hideCallback) {
        const void *thisPtr = this;
        m_hideCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::TabBar::hide();
    }
}
void TabBar_wrapper::hide_nocallback()
{
    ::KDDockWidgets::flutter::TabBar::hide();
}
void TabBar_wrapper::init()
{
    if (m_initCallback) {
        const void *thisPtr = this;
        m_initCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::TabBar::init();
    }
}
void TabBar_wrapper::init_nocallback()
{
    ::KDDockWidgets::flutter::TabBar::init();
}
bool TabBar_wrapper::isActiveWindow() const
{
    if (m_isActiveWindowCallback) {
        const void *thisPtr = this;
        return m_isActiveWindowCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TabBar::isActiveWindow();
    }
}
bool TabBar_wrapper::isActiveWindow_nocallback() const
{
    return ::KDDockWidgets::flutter::TabBar::isActiveWindow();
}
bool TabBar_wrapper::isExpicitlyHidden() const
{
    if (m_isExpicitlyHiddenCallback) {
        const void *thisPtr = this;
        return m_isExpicitlyHiddenCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TabBar::isExpicitlyHidden();
    }
}
bool TabBar_wrapper::isExpicitlyHidden_nocallback() const
{
    return ::KDDockWidgets::flutter::TabBar::isExpicitlyHidden();
}
bool TabBar_wrapper::isMaximized() const
{
    if (m_isMaximizedCallback) {
        const void *thisPtr = this;
        return m_isMaximizedCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TabBar::isMaximized();
    }
}
bool TabBar_wrapper::isMaximized_nocallback() const
{
    return ::KDDockWidgets::flutter::TabBar::isMaximized();
}
bool TabBar_wrapper::isMinimized() const
{
    if (m_isMinimizedCallback) {
        const void *thisPtr = this;
        return m_isMinimizedCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TabBar::isMinimized();
    }
}
bool TabBar_wrapper::isMinimized_nocallback() const
{
    return ::KDDockWidgets::flutter::TabBar::isMinimized();
}
bool TabBar_wrapper::isNull() const
{
    if (m_isNullCallback) {
        const void *thisPtr = this;
        return m_isNullCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TabBar::isNull();
    }
}
bool TabBar_wrapper::isNull_nocallback() const
{
    return ::KDDockWidgets::flutter::TabBar::isNull();
}
bool TabBar_wrapper::isRootView() const
{
    if (m_isRootViewCallback) {
        const void *thisPtr = this;
        return m_isRootViewCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TabBar::isRootView();
    }
}
bool TabBar_wrapper::isRootView_nocallback() const
{
    return ::KDDockWidgets::flutter::TabBar::isRootView();
}
bool TabBar_wrapper::isVisible() const
{
    if (m_isVisibleCallback) {
        const void *thisPtr = this;
        return m_isVisibleCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TabBar::isVisible();
    }
}
bool TabBar_wrapper::isVisible_nocallback() const
{
    return ::KDDockWidgets::flutter::TabBar::isVisible();
}
QPoint TabBar_wrapper::mapFromGlobal(QPoint globalPt) const
{
    if (m_mapFromGlobalCallback) {
        const void *thisPtr = this;
        return *m_mapFromGlobalCallback(const_cast<void *>(thisPtr), &globalPt);
    } else {
        return ::KDDockWidgets::flutter::TabBar::mapFromGlobal(globalPt);
    }
}
QPoint TabBar_wrapper::mapFromGlobal_nocallback(QPoint globalPt) const
{
    return ::KDDockWidgets::flutter::TabBar::mapFromGlobal(globalPt);
}
QPoint TabBar_wrapper::mapTo(KDDockWidgets::Core::View *parent, QPoint pos) const
{
    if (m_mapToCallback) {
        const void *thisPtr = this;
        return *m_mapToCallback(const_cast<void *>(thisPtr), parent, &pos);
    } else {
        return ::KDDockWidgets::flutter::TabBar::mapTo(parent, pos);
    }
}
QPoint TabBar_wrapper::mapTo_nocallback(KDDockWidgets::Core::View *parent, QPoint pos) const
{
    return ::KDDockWidgets::flutter::TabBar::mapTo(parent, pos);
}
QPoint TabBar_wrapper::mapToGlobal(QPoint localPt) const
{
    if (m_mapToGlobalCallback) {
        const void *thisPtr = this;
        return *m_mapToGlobalCallback(const_cast<void *>(thisPtr), &localPt);
    } else {
        return ::KDDockWidgets::flutter::TabBar::mapToGlobal(localPt);
    }
}
QPoint TabBar_wrapper::mapToGlobal_nocallback(QPoint localPt) const
{
    return ::KDDockWidgets::flutter::TabBar::mapToGlobal(localPt);
}
QSize TabBar_wrapper::maxSizeHint() const
{
    if (m_maxSizeHintCallback) {
        const void *thisPtr = this;
        return *m_maxSizeHintCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TabBar::maxSizeHint();
    }
}
QSize TabBar_wrapper::maxSizeHint_nocallback() const
{
    return ::KDDockWidgets::flutter::TabBar::maxSizeHint();
}
QSize TabBar_wrapper::minSize() const
{
    if (m_minSizeCallback) {
        const void *thisPtr = this;
        return *m_minSizeCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TabBar::minSize();
    }
}
QSize TabBar_wrapper::minSize_nocallback() const
{
    return ::KDDockWidgets::flutter::TabBar::minSize();
}
int TabBar_wrapper::minimumHeight() const
{
    if (m_minimumHeightCallback) {
        const void *thisPtr = this;
        return m_minimumHeightCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TabBar::minimumHeight();
    }
}
int TabBar_wrapper::minimumHeight_nocallback() const
{
    return ::KDDockWidgets::flutter::TabBar::minimumHeight();
}
int TabBar_wrapper::minimumWidth() const
{
    if (m_minimumWidthCallback) {
        const void *thisPtr = this;
        return m_minimumWidthCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TabBar::minimumWidth();
    }
}
int TabBar_wrapper::minimumWidth_nocallback() const
{
    return ::KDDockWidgets::flutter::TabBar::minimumWidth();
}
void TabBar_wrapper::move(int x, int y)
{
    if (m_move_2Callback) {
        const void *thisPtr = this;
        m_move_2Callback(const_cast<void *>(thisPtr), x, y);
    } else {
        ::KDDockWidgets::flutter::TabBar::move(x, y);
    }
}
void TabBar_wrapper::move_nocallback(int x, int y)
{
    ::KDDockWidgets::flutter::TabBar::move(x, y);
}
void TabBar_wrapper::moveTabTo(int from, int to)
{
    if (m_moveTabToCallback) {
        const void *thisPtr = this;
        m_moveTabToCallback(const_cast<void *>(thisPtr), from, to);
    } else {
        ::KDDockWidgets::flutter::TabBar::moveTabTo(from, to);
    }
}
void TabBar_wrapper::moveTabTo_nocallback(int from, int to)
{
    ::KDDockWidgets::flutter::TabBar::moveTabTo(from, to);
}
QRect TabBar_wrapper::normalGeometry() const
{
    if (m_normalGeometryCallback) {
        const void *thisPtr = this;
        return *m_normalGeometryCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TabBar::normalGeometry();
    }
}
QRect TabBar_wrapper::normalGeometry_nocallback() const
{
    return ::KDDockWidgets::flutter::TabBar::normalGeometry();
}
QString TabBar_wrapper::objectName() const
{
    if (m_objectNameCallback) {
        const void *thisPtr = this;
        return *m_objectNameCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TabBar::objectName();
    }
}
QString TabBar_wrapper::objectName_nocallback() const
{
    return ::KDDockWidgets::flutter::TabBar::objectName();
}
void TabBar_wrapper::onChildAdded(KDDockWidgets::Core::View *childView)
{
    if (m_onChildAddedCallback) {
        const void *thisPtr = this;
        m_onChildAddedCallback(const_cast<void *>(thisPtr), childView);
    } else {
        ::KDDockWidgets::flutter::TabBar::onChildAdded(childView);
    }
}
void TabBar_wrapper::onChildAdded_nocallback(KDDockWidgets::Core::View *childView)
{
    ::KDDockWidgets::flutter::TabBar::onChildAdded(childView);
}
void TabBar_wrapper::onChildRemoved(KDDockWidgets::Core::View *childView)
{
    if (m_onChildRemovedCallback) {
        const void *thisPtr = this;
        m_onChildRemovedCallback(const_cast<void *>(thisPtr), childView);
    } else {
        ::KDDockWidgets::flutter::TabBar::onChildRemoved(childView);
    }
}
void TabBar_wrapper::onChildRemoved_nocallback(KDDockWidgets::Core::View *childView)
{
    ::KDDockWidgets::flutter::TabBar::onChildRemoved(childView);
}
void TabBar_wrapper::onRebuildRequested()
{
    if (m_onRebuildRequestedCallback) {
        const void *thisPtr = this;
        m_onRebuildRequestedCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void TabBar_wrapper::onRebuildRequested_nocallback()
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
bool TabBar_wrapper::onResize(int w, int h)
{
    if (m_onResize_2Callback) {
        const void *thisPtr = this;
        return m_onResize_2Callback(const_cast<void *>(thisPtr), w, h);
    } else {
        return ::KDDockWidgets::flutter::TabBar::onResize(w, h);
    }
}
bool TabBar_wrapper::onResize_nocallback(int w, int h)
{
    return ::KDDockWidgets::flutter::TabBar::onResize(w, h);
}
void TabBar_wrapper::raise()
{
    if (m_raiseCallback) {
        const void *thisPtr = this;
        m_raiseCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::TabBar::raise();
    }
}
void TabBar_wrapper::raise_nocallback()
{
    ::KDDockWidgets::flutter::TabBar::raise();
}
void TabBar_wrapper::raiseAndActivate()
{
    if (m_raiseAndActivateCallback) {
        const void *thisPtr = this;
        m_raiseAndActivateCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::TabBar::raiseAndActivate();
    }
}
void TabBar_wrapper::raiseAndActivate_nocallback()
{
    ::KDDockWidgets::flutter::TabBar::raiseAndActivate();
}
QRect TabBar_wrapper::rectForTab(int index) const
{
    if (m_rectForTabCallback) {
        const void *thisPtr = this;
        return *m_rectForTabCallback(const_cast<void *>(thisPtr), index);
    } else {
        return ::KDDockWidgets::flutter::TabBar::rectForTab(index);
    }
}
QRect TabBar_wrapper::rectForTab_nocallback(int index) const
{
    return ::KDDockWidgets::flutter::TabBar::rectForTab(index);
}
void TabBar_wrapper::releaseKeyboard()
{
    if (m_releaseKeyboardCallback) {
        const void *thisPtr = this;
        m_releaseKeyboardCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::TabBar::releaseKeyboard();
    }
}
void TabBar_wrapper::releaseKeyboard_nocallback()
{
    ::KDDockWidgets::flutter::TabBar::releaseKeyboard();
}
void TabBar_wrapper::releaseMouse()
{
    if (m_releaseMouseCallback) {
        const void *thisPtr = this;
        m_releaseMouseCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::TabBar::releaseMouse();
    }
}
void TabBar_wrapper::releaseMouse_nocallback()
{
    ::KDDockWidgets::flutter::TabBar::releaseMouse();
}
void TabBar_wrapper::removeDockWidget(KDDockWidgets::Core::DockWidget *dw)
{
    if (m_removeDockWidgetCallback) {
        const void *thisPtr = this;
        m_removeDockWidgetCallback(const_cast<void *>(thisPtr), dw);
    } else {
        ::KDDockWidgets::flutter::TabBar::removeDockWidget(dw);
    }
}
void TabBar_wrapper::removeDockWidget_nocallback(KDDockWidgets::Core::DockWidget *dw)
{
    ::KDDockWidgets::flutter::TabBar::removeDockWidget(dw);
}
void TabBar_wrapper::renameTab(int index, const QString &name)
{
    if (m_renameTabCallback) {
        const void *thisPtr = this;
        m_renameTabCallback(const_cast<void *>(thisPtr), index, name);
    } else {
        ::KDDockWidgets::flutter::TabBar::renameTab(index, name);
    }
}
void TabBar_wrapper::renameTab_nocallback(int index, const QString &name)
{
    ::KDDockWidgets::flutter::TabBar::renameTab(index, name);
}
void TabBar_wrapper::setCurrentIndex(int index)
{
    if (m_setCurrentIndexCallback) {
        const void *thisPtr = this;
        m_setCurrentIndexCallback(const_cast<void *>(thisPtr), index);
    } else {
        ::KDDockWidgets::flutter::TabBar::setCurrentIndex(index);
    }
}
void TabBar_wrapper::setCurrentIndex_nocallback(int index)
{
    ::KDDockWidgets::flutter::TabBar::setCurrentIndex(index);
}
void TabBar_wrapper::setCursor(Qt::CursorShape shape)
{
    if (m_setCursorCallback) {
        const void *thisPtr = this;
        m_setCursorCallback(const_cast<void *>(thisPtr), shape);
    } else {
        ::KDDockWidgets::flutter::TabBar::setCursor(shape);
    }
}
void TabBar_wrapper::setCursor_nocallback(Qt::CursorShape shape)
{
    ::KDDockWidgets::flutter::TabBar::setCursor(shape);
}
void TabBar_wrapper::setFixedHeight(int h)
{
    if (m_setFixedHeightCallback) {
        const void *thisPtr = this;
        m_setFixedHeightCallback(const_cast<void *>(thisPtr), h);
    } else {
        ::KDDockWidgets::flutter::TabBar::setFixedHeight(h);
    }
}
void TabBar_wrapper::setFixedHeight_nocallback(int h)
{
    ::KDDockWidgets::flutter::TabBar::setFixedHeight(h);
}
void TabBar_wrapper::setFixedWidth(int w)
{
    if (m_setFixedWidthCallback) {
        const void *thisPtr = this;
        m_setFixedWidthCallback(const_cast<void *>(thisPtr), w);
    } else {
        ::KDDockWidgets::flutter::TabBar::setFixedWidth(w);
    }
}
void TabBar_wrapper::setFixedWidth_nocallback(int w)
{
    ::KDDockWidgets::flutter::TabBar::setFixedWidth(w);
}
void TabBar_wrapper::setGeometry(QRect geometry)
{
    if (m_setGeometryCallback) {
        const void *thisPtr = this;
        m_setGeometryCallback(const_cast<void *>(thisPtr), &geometry);
    } else {
        ::KDDockWidgets::flutter::TabBar::setGeometry(geometry);
    }
}
void TabBar_wrapper::setGeometry_nocallback(QRect geometry)
{
    ::KDDockWidgets::flutter::TabBar::setGeometry(geometry);
}
void TabBar_wrapper::setHeight(int h)
{
    if (m_setHeightCallback) {
        const void *thisPtr = this;
        m_setHeightCallback(const_cast<void *>(thisPtr), h);
    } else {
        ::KDDockWidgets::flutter::TabBar::setHeight(h);
    }
}
void TabBar_wrapper::setHeight_nocallback(int h)
{
    ::KDDockWidgets::flutter::TabBar::setHeight(h);
}
void TabBar_wrapper::setMaximumSize(QSize sz)
{
    if (m_setMaximumSizeCallback) {
        const void *thisPtr = this;
        m_setMaximumSizeCallback(const_cast<void *>(thisPtr), &sz);
    } else {
        ::KDDockWidgets::flutter::TabBar::setMaximumSize(sz);
    }
}
void TabBar_wrapper::setMaximumSize_nocallback(QSize sz)
{
    ::KDDockWidgets::flutter::TabBar::setMaximumSize(sz);
}
void TabBar_wrapper::setMinimumSize(QSize sz)
{
    if (m_setMinimumSizeCallback) {
        const void *thisPtr = this;
        m_setMinimumSizeCallback(const_cast<void *>(thisPtr), &sz);
    } else {
        ::KDDockWidgets::flutter::TabBar::setMinimumSize(sz);
    }
}
void TabBar_wrapper::setMinimumSize_nocallback(QSize sz)
{
    ::KDDockWidgets::flutter::TabBar::setMinimumSize(sz);
}
void TabBar_wrapper::setMouseTracking(bool enable)
{
    if (m_setMouseTrackingCallback) {
        const void *thisPtr = this;
        m_setMouseTrackingCallback(const_cast<void *>(thisPtr), enable);
    } else {
        ::KDDockWidgets::flutter::TabBar::setMouseTracking(enable);
    }
}
void TabBar_wrapper::setMouseTracking_nocallback(bool enable)
{
    ::KDDockWidgets::flutter::TabBar::setMouseTracking(enable);
}
void TabBar_wrapper::setObjectName(const QString &name)
{
    if (m_setObjectNameCallback) {
        const void *thisPtr = this;
        m_setObjectNameCallback(const_cast<void *>(thisPtr), name);
    } else {
        ::KDDockWidgets::flutter::TabBar::setObjectName(name);
    }
}
void TabBar_wrapper::setObjectName_nocallback(const QString &name)
{
    ::KDDockWidgets::flutter::TabBar::setObjectName(name);
}
void TabBar_wrapper::setParent(KDDockWidgets::Core::View *parent)
{
    if (m_setParentCallback) {
        const void *thisPtr = this;
        m_setParentCallback(const_cast<void *>(thisPtr), parent);
    } else {
        ::KDDockWidgets::flutter::TabBar::setParent(parent);
    }
}
void TabBar_wrapper::setParent_nocallback(KDDockWidgets::Core::View *parent)
{
    ::KDDockWidgets::flutter::TabBar::setParent(parent);
}
void TabBar_wrapper::setSize(int w, int h)
{
    if (m_setSize_2Callback) {
        const void *thisPtr = this;
        m_setSize_2Callback(const_cast<void *>(thisPtr), w, h);
    } else {
        ::KDDockWidgets::flutter::TabBar::setSize(w, h);
    }
}
void TabBar_wrapper::setSize_nocallback(int w, int h)
{
    ::KDDockWidgets::flutter::TabBar::setSize(w, h);
}
void TabBar_wrapper::setVisible(bool visible)
{
    if (m_setVisibleCallback) {
        const void *thisPtr = this;
        m_setVisibleCallback(const_cast<void *>(thisPtr), visible);
    } else {
        ::KDDockWidgets::flutter::TabBar::setVisible(visible);
    }
}
void TabBar_wrapper::setVisible_nocallback(bool visible)
{
    ::KDDockWidgets::flutter::TabBar::setVisible(visible);
}
void TabBar_wrapper::setWidth(int w)
{
    if (m_setWidthCallback) {
        const void *thisPtr = this;
        m_setWidthCallback(const_cast<void *>(thisPtr), w);
    } else {
        ::KDDockWidgets::flutter::TabBar::setWidth(w);
    }
}
void TabBar_wrapper::setWidth_nocallback(int w)
{
    ::KDDockWidgets::flutter::TabBar::setWidth(w);
}
void TabBar_wrapper::setWindowOpacity(double v)
{
    if (m_setWindowOpacityCallback) {
        const void *thisPtr = this;
        m_setWindowOpacityCallback(const_cast<void *>(thisPtr), v);
    } else {
        ::KDDockWidgets::flutter::TabBar::setWindowOpacity(v);
    }
}
void TabBar_wrapper::setWindowOpacity_nocallback(double v)
{
    ::KDDockWidgets::flutter::TabBar::setWindowOpacity(v);
}
void TabBar_wrapper::setWindowTitle(const QString &title)
{
    if (m_setWindowTitleCallback) {
        const void *thisPtr = this;
        m_setWindowTitleCallback(const_cast<void *>(thisPtr), title);
    } else {
        ::KDDockWidgets::flutter::TabBar::setWindowTitle(title);
    }
}
void TabBar_wrapper::setWindowTitle_nocallback(const QString &title)
{
    ::KDDockWidgets::flutter::TabBar::setWindowTitle(title);
}
void TabBar_wrapper::setZOrder(int z)
{
    if (m_setZOrderCallback) {
        const void *thisPtr = this;
        m_setZOrderCallback(const_cast<void *>(thisPtr), z);
    } else {
        ::KDDockWidgets::flutter::TabBar::setZOrder(z);
    }
}
void TabBar_wrapper::setZOrder_nocallback(int z)
{
    ::KDDockWidgets::flutter::TabBar::setZOrder(z);
}
void TabBar_wrapper::show()
{
    if (m_showCallback) {
        const void *thisPtr = this;
        m_showCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::TabBar::show();
    }
}
void TabBar_wrapper::show_nocallback()
{
    ::KDDockWidgets::flutter::TabBar::show();
}
void TabBar_wrapper::showMaximized()
{
    if (m_showMaximizedCallback) {
        const void *thisPtr = this;
        m_showMaximizedCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::TabBar::showMaximized();
    }
}
void TabBar_wrapper::showMaximized_nocallback()
{
    ::KDDockWidgets::flutter::TabBar::showMaximized();
}
void TabBar_wrapper::showMinimized()
{
    if (m_showMinimizedCallback) {
        const void *thisPtr = this;
        m_showMinimizedCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::TabBar::showMinimized();
    }
}
void TabBar_wrapper::showMinimized_nocallback()
{
    ::KDDockWidgets::flutter::TabBar::showMinimized();
}
void TabBar_wrapper::showNormal()
{
    if (m_showNormalCallback) {
        const void *thisPtr = this;
        m_showNormalCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::TabBar::showNormal();
    }
}
void TabBar_wrapper::showNormal_nocallback()
{
    ::KDDockWidgets::flutter::TabBar::showNormal();
}
QSize TabBar_wrapper::sizeHint() const
{
    if (m_sizeHintCallback) {
        const void *thisPtr = this;
        return *m_sizeHintCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::TabBar::sizeHint();
    }
}
QSize TabBar_wrapper::sizeHint_nocallback() const
{
    return ::KDDockWidgets::flutter::TabBar::sizeHint();
}
int TabBar_wrapper::tabAt(QPoint localPos) const
{
    if (m_tabAtCallback) {
        const void *thisPtr = this;
        return m_tabAtCallback(const_cast<void *>(thisPtr), &localPos);
    } else {
        return ::KDDockWidgets::flutter::TabBar::tabAt(localPos);
    }
}
int TabBar_wrapper::tabAt_nocallback(QPoint localPos) const
{
    return ::KDDockWidgets::flutter::TabBar::tabAt(localPos);
}
QString TabBar_wrapper::text(int index) const
{
    if (m_textCallback) {
        const void *thisPtr = this;
        return *m_textCallback(const_cast<void *>(thisPtr), index);
    } else {
        return ::KDDockWidgets::flutter::TabBar::text(index);
    }
}
QString TabBar_wrapper::text_nocallback(int index) const
{
    return ::KDDockWidgets::flutter::TabBar::text(index);
}
void TabBar_wrapper::update()
{
    if (m_updateCallback) {
        const void *thisPtr = this;
        m_updateCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::TabBar::update();
    }
}
void TabBar_wrapper::update_nocallback()
{
    ::KDDockWidgets::flutter::TabBar::update();
}
TabBar_wrapper::~TabBar_wrapper()
{
}

}
}
static KDDockWidgets::flutter::TabBar *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::flutter::TabBar *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__flutter__TabBar_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper *>(cppObj);
}
void *c_KDDockWidgets__flutter__TabBar__constructor_TabBar_View(void *controller_, void *parent_)
{
    auto controller = reinterpret_cast<KDDockWidgets::Core::TabBar *>(controller_);
    auto parent = reinterpret_cast<KDDockWidgets::Core::View *>(parent_);
    auto ptr = new KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper(controller, parent);
    return reinterpret_cast<void *>(ptr);
}
// activateWindow()
void c_KDDockWidgets__flutter__TabBar__activateWindow(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->activateWindow_nocallback();} else {    return targetPtr->activateWindow();} }();
}
// close()
bool c_KDDockWidgets__flutter__TabBar__close(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->close_nocallback();} else {    return targetPtr->close();} }();
}
// createPlatformWindow()
void c_KDDockWidgets__flutter__TabBar__createPlatformWindow(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->createPlatformWindow_nocallback();} else {    return targetPtr->createPlatformWindow();} }();
}
// flags() const
int c_KDDockWidgets__flutter__TabBar__flags(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->flags_nocallback();} else {    return targetPtr->flags();} }();
}
// free_impl()
void c_KDDockWidgets__flutter__TabBar__free_impl(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->free_impl_nocallback();} else {    return targetPtr->free_impl();} }();
}
// geometry() const
void *c_KDDockWidgets__flutter__TabBar__geometry(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QRect> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->geometry_nocallback();} else {    return targetPtr->geometry();} }() };
}
// grabMouse()
void c_KDDockWidgets__flutter__TabBar__grabMouse(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->grabMouse_nocallback();} else {    return targetPtr->grabMouse();} }();
}
// hasFocus() const
bool c_KDDockWidgets__flutter__TabBar__hasFocus(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->hasFocus_nocallback();} else {    return targetPtr->hasFocus();} }();
}
// hide()
void c_KDDockWidgets__flutter__TabBar__hide(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->hide_nocallback();} else {    return targetPtr->hide();} }();
}
// init()
void c_KDDockWidgets__flutter__TabBar__init(void *thisObj)
{
    fromWrapperPtr(thisObj)->init_nocallback();
}
// isActiveWindow() const
bool c_KDDockWidgets__flutter__TabBar__isActiveWindow(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isActiveWindow_nocallback();} else {    return targetPtr->isActiveWindow();} }();
}
// isExpicitlyHidden() const
bool c_KDDockWidgets__flutter__TabBar__isExpicitlyHidden(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isExpicitlyHidden_nocallback();} else {    return targetPtr->isExpicitlyHidden();} }();
}
// isMaximized() const
bool c_KDDockWidgets__flutter__TabBar__isMaximized(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isMaximized_nocallback();} else {    return targetPtr->isMaximized();} }();
}
// isMinimized() const
bool c_KDDockWidgets__flutter__TabBar__isMinimized(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isMinimized_nocallback();} else {    return targetPtr->isMinimized();} }();
}
// isNull() const
bool c_KDDockWidgets__flutter__TabBar__isNull(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isNull_nocallback();} else {    return targetPtr->isNull();} }();
}
// isRootView() const
bool c_KDDockWidgets__flutter__TabBar__isRootView(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isRootView_nocallback();} else {    return targetPtr->isRootView();} }();
}
// isVisible() const
bool c_KDDockWidgets__flutter__TabBar__isVisible(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isVisible_nocallback();} else {    return targetPtr->isVisible();} }();
}
// mapFromGlobal(QPoint globalPt) const
void *c_KDDockWidgets__flutter__TabBar__mapFromGlobal_QPoint(void *thisObj, void *globalPt_)
{
    assert(globalPt_);
    auto &globalPt = *reinterpret_cast<QPoint *>(globalPt_);
    return new Dartagnan::ValueWrapper<QPoint> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->mapFromGlobal_nocallback(globalPt);} else {    return targetPtr->mapFromGlobal(globalPt);} }() };
}
// mapTo(KDDockWidgets::Core::View * parent, QPoint pos) const
void *c_KDDockWidgets__flutter__TabBar__mapTo_View_QPoint(void *thisObj, void *parent_, void *pos_)
{
    auto parent = reinterpret_cast<KDDockWidgets::Core::View *>(parent_);
    assert(pos_);
    auto &pos = *reinterpret_cast<QPoint *>(pos_);
    return new Dartagnan::ValueWrapper<QPoint> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->mapTo_nocallback(parent,pos);} else {    return targetPtr->mapTo(parent,pos);} }() };
}
// mapToGlobal(QPoint localPt) const
void *c_KDDockWidgets__flutter__TabBar__mapToGlobal_QPoint(void *thisObj, void *localPt_)
{
    assert(localPt_);
    auto &localPt = *reinterpret_cast<QPoint *>(localPt_);
    return new Dartagnan::ValueWrapper<QPoint> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->mapToGlobal_nocallback(localPt);} else {    return targetPtr->mapToGlobal(localPt);} }() };
}
// maxSizeHint() const
void *c_KDDockWidgets__flutter__TabBar__maxSizeHint(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->maxSizeHint_nocallback();} else {    return targetPtr->maxSizeHint();} }() };
}
// minSize() const
void *c_KDDockWidgets__flutter__TabBar__minSize(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->minSize_nocallback();} else {    return targetPtr->minSize();} }() };
}
// minimumHeight() const
int c_KDDockWidgets__flutter__TabBar__minimumHeight(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->minimumHeight_nocallback();} else {    return targetPtr->minimumHeight();} }();
}
// minimumWidth() const
int c_KDDockWidgets__flutter__TabBar__minimumWidth(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->minimumWidth_nocallback();} else {    return targetPtr->minimumWidth();} }();
}
// move(int x, int y)
void c_KDDockWidgets__flutter__TabBar__move_int_int(void *thisObj, int x, int y)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->move_nocallback(x,y);} else {    return targetPtr->move(x,y);} }();
}
// moveTabTo(int from, int to)
void c_KDDockWidgets__flutter__TabBar__moveTabTo_int_int(void *thisObj, int from, int to)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->moveTabTo_nocallback(from,to);} else {    return targetPtr->moveTabTo(from,to);} }();
}
// normalGeometry() const
void *c_KDDockWidgets__flutter__TabBar__normalGeometry(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QRect> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->normalGeometry_nocallback();} else {    return targetPtr->normalGeometry();} }() };
}
// objectName() const
void *c_KDDockWidgets__flutter__TabBar__objectName(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QString> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->objectName_nocallback();} else {    return targetPtr->objectName();} }() };
}
// onChildAdded(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__TabBar__onChildAdded_View(void *thisObj, void *childView_)
{
    auto childView = reinterpret_cast<KDDockWidgets::Core::View *>(childView_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->onChildAdded_nocallback(childView);} else {    return targetPtr->onChildAdded(childView);} }();
}
// onChildRemoved(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__TabBar__onChildRemoved_View(void *thisObj, void *childView_)
{
    auto childView = reinterpret_cast<KDDockWidgets::Core::View *>(childView_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->onChildRemoved_nocallback(childView);} else {    return targetPtr->onChildRemoved(childView);} }();
}
// onRebuildRequested()
void c_KDDockWidgets__flutter__TabBar__onRebuildRequested(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->onRebuildRequested_nocallback();} else {    return targetPtr->onRebuildRequested();} }();
}
// onResize(int w, int h)
bool c_KDDockWidgets__flutter__TabBar__onResize_int_int(void *thisObj, int w, int h)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->onResize_nocallback(w,h);} else {    return targetPtr->onResize(w,h);} }();
}
// raise()
void c_KDDockWidgets__flutter__TabBar__raise(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->raise_nocallback();} else {    return targetPtr->raise();} }();
}
// raiseAndActivate()
void c_KDDockWidgets__flutter__TabBar__raiseAndActivate(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->raiseAndActivate_nocallback();} else {    return targetPtr->raiseAndActivate();} }();
}
// rectForTab(int index) const
void *c_KDDockWidgets__flutter__TabBar__rectForTab_int(void *thisObj, int index)
{
    return new Dartagnan::ValueWrapper<QRect> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->rectForTab_nocallback(index);} else {    return targetPtr->rectForTab(index);} }() };
}
// releaseKeyboard()
void c_KDDockWidgets__flutter__TabBar__releaseKeyboard(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->releaseKeyboard_nocallback();} else {    return targetPtr->releaseKeyboard();} }();
}
// releaseMouse()
void c_KDDockWidgets__flutter__TabBar__releaseMouse(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->releaseMouse_nocallback();} else {    return targetPtr->releaseMouse();} }();
}
// removeDockWidget(KDDockWidgets::Core::DockWidget * dw)
void c_KDDockWidgets__flutter__TabBar__removeDockWidget_DockWidget(void *thisObj, void *dw_)
{
    auto dw = reinterpret_cast<KDDockWidgets::Core::DockWidget *>(dw_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->removeDockWidget_nocallback(dw);} else {    return targetPtr->removeDockWidget(dw);} }();
}
// renameTab(int index, const QString & name)
void c_KDDockWidgets__flutter__TabBar__renameTab_int_QString(void *thisObj, int index, const char *name_)
{
    const auto name = QString::fromUtf8(name_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->renameTab_nocallback(index,name);} else {    return targetPtr->renameTab(index,name);} }();
}
// setCurrentIndex(int index)
void c_KDDockWidgets__flutter__TabBar__setCurrentIndex_int(void *thisObj, int index)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setCurrentIndex_nocallback(index);} else {    return targetPtr->setCurrentIndex(index);} }();
}
// setCursor(Qt::CursorShape shape)
void c_KDDockWidgets__flutter__TabBar__setCursor_CursorShape(void *thisObj, int shape)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setCursor_nocallback(static_cast<Qt::CursorShape>(shape));} else {    return targetPtr->setCursor(static_cast<Qt::CursorShape>(shape));} }();
}
// setFixedHeight(int h)
void c_KDDockWidgets__flutter__TabBar__setFixedHeight_int(void *thisObj, int h)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setFixedHeight_nocallback(h);} else {    return targetPtr->setFixedHeight(h);} }();
}
// setFixedWidth(int w)
void c_KDDockWidgets__flutter__TabBar__setFixedWidth_int(void *thisObj, int w)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setFixedWidth_nocallback(w);} else {    return targetPtr->setFixedWidth(w);} }();
}
// setGeometry(QRect geometry)
void c_KDDockWidgets__flutter__TabBar__setGeometry_QRect(void *thisObj, void *geometry_)
{
    assert(geometry_);
    auto &geometry = *reinterpret_cast<QRect *>(geometry_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setGeometry_nocallback(geometry);} else {    return targetPtr->setGeometry(geometry);} }();
}
// setHeight(int h)
void c_KDDockWidgets__flutter__TabBar__setHeight_int(void *thisObj, int h)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setHeight_nocallback(h);} else {    return targetPtr->setHeight(h);} }();
}
// setMaximumSize(QSize sz)
void c_KDDockWidgets__flutter__TabBar__setMaximumSize_QSize(void *thisObj, void *sz_)
{
    assert(sz_);
    auto &sz = *reinterpret_cast<QSize *>(sz_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setMaximumSize_nocallback(sz);} else {    return targetPtr->setMaximumSize(sz);} }();
}
// setMinimumSize(QSize sz)
void c_KDDockWidgets__flutter__TabBar__setMinimumSize_QSize(void *thisObj, void *sz_)
{
    assert(sz_);
    auto &sz = *reinterpret_cast<QSize *>(sz_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setMinimumSize_nocallback(sz);} else {    return targetPtr->setMinimumSize(sz);} }();
}
// setMouseTracking(bool enable)
void c_KDDockWidgets__flutter__TabBar__setMouseTracking_bool(void *thisObj, bool enable)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setMouseTracking_nocallback(enable);} else {    return targetPtr->setMouseTracking(enable);} }();
}
// setObjectName(const QString & name)
void c_KDDockWidgets__flutter__TabBar__setObjectName_QString(void *thisObj, const char *name_)
{
    const auto name = QString::fromUtf8(name_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setObjectName_nocallback(name);} else {    return targetPtr->setObjectName(name);} }();
}
// setParent(KDDockWidgets::Core::View * parent)
void c_KDDockWidgets__flutter__TabBar__setParent_View(void *thisObj, void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::Core::View *>(parent_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setParent_nocallback(parent);} else {    return targetPtr->setParent(parent);} }();
}
// setSize(int w, int h)
void c_KDDockWidgets__flutter__TabBar__setSize_int_int(void *thisObj, int w, int h)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setSize_nocallback(w,h);} else {    return targetPtr->setSize(w,h);} }();
}
// setVisible(bool visible)
void c_KDDockWidgets__flutter__TabBar__setVisible_bool(void *thisObj, bool visible)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setVisible_nocallback(visible);} else {    return targetPtr->setVisible(visible);} }();
}
// setWidth(int w)
void c_KDDockWidgets__flutter__TabBar__setWidth_int(void *thisObj, int w)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setWidth_nocallback(w);} else {    return targetPtr->setWidth(w);} }();
}
// setWindowOpacity(double v)
void c_KDDockWidgets__flutter__TabBar__setWindowOpacity_double(void *thisObj, double v)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setWindowOpacity_nocallback(v);} else {    return targetPtr->setWindowOpacity(v);} }();
}
// setWindowTitle(const QString & title)
void c_KDDockWidgets__flutter__TabBar__setWindowTitle_QString(void *thisObj, const char *title_)
{
    const auto title = QString::fromUtf8(title_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setWindowTitle_nocallback(title);} else {    return targetPtr->setWindowTitle(title);} }();
}
// setZOrder(int z)
void c_KDDockWidgets__flutter__TabBar__setZOrder_int(void *thisObj, int z)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setZOrder_nocallback(z);} else {    return targetPtr->setZOrder(z);} }();
}
// show()
void c_KDDockWidgets__flutter__TabBar__show(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->show_nocallback();} else {    return targetPtr->show();} }();
}
// showMaximized()
void c_KDDockWidgets__flutter__TabBar__showMaximized(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->showMaximized_nocallback();} else {    return targetPtr->showMaximized();} }();
}
// showMinimized()
void c_KDDockWidgets__flutter__TabBar__showMinimized(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->showMinimized_nocallback();} else {    return targetPtr->showMinimized();} }();
}
// showNormal()
void c_KDDockWidgets__flutter__TabBar__showNormal(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->showNormal_nocallback();} else {    return targetPtr->showNormal();} }();
}
// sizeHint() const
void *c_KDDockWidgets__flutter__TabBar__sizeHint(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->sizeHint_nocallback();} else {    return targetPtr->sizeHint();} }() };
}
// tabAt(QPoint localPos) const
int c_KDDockWidgets__flutter__TabBar__tabAt_QPoint(void *thisObj, void *localPos_)
{
    assert(localPos_);
    auto &localPos = *reinterpret_cast<QPoint *>(localPos_);
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->tabAt_nocallback(localPos);} else {    return targetPtr->tabAt(localPos);} }();
}
// text(int index) const
void *c_KDDockWidgets__flutter__TabBar__text_int(void *thisObj, int index)
{
    return new Dartagnan::ValueWrapper<QString> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->text_nocallback(index);} else {    return targetPtr->text(index);} }() };
}
// update()
void c_KDDockWidgets__flutter__TabBar__update(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->update_nocallback();} else {    return targetPtr->update();} }();
}
void c_KDDockWidgets__flutter__TabBar__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__flutter__TabBar__registerVirtualMethodCallback(void *ptr, void *callback, int methodId)
{
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 907:
        wrapper->m_activateWindowCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_activateWindow>(callback);
        break;
    case 918:
        wrapper->m_closeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_close>(callback);
        break;
    case 921:
        wrapper->m_createPlatformWindowCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_createPlatformWindow>(callback);
        break;
    case 927:
        wrapper->m_flagsCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_flags>(callback);
        break;
    case 929:
        wrapper->m_free_implCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_free_impl>(callback);
        break;
    case 931:
        wrapper->m_geometryCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_geometry>(callback);
        break;
    case 933:
        wrapper->m_grabMouseCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_grabMouse>(callback);
        break;
    case 936:
        wrapper->m_hasFocusCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_hasFocus>(callback);
        break;
    case 938:
        wrapper->m_hideCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_hide>(callback);
        break;
    case 941:
        wrapper->m_initCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_init>(callback);
        break;
    case 943:
        wrapper->m_isActiveWindowCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_isActiveWindow>(callback);
        break;
    case 944:
        wrapper->m_isExpicitlyHiddenCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_isExpicitlyHidden>(callback);
        break;
    case 945:
        wrapper->m_isMaximizedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_isMaximized>(callback);
        break;
    case 946:
        wrapper->m_isMinimizedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_isMinimized>(callback);
        break;
    case 947:
        wrapper->m_isNullCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_isNull>(callback);
        break;
    case 948:
        wrapper->m_isRootViewCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_isRootView>(callback);
        break;
    case 949:
        wrapper->m_isVisibleCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_isVisible>(callback);
        break;
    case 950:
        wrapper->m_mapFromGlobalCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_mapFromGlobal>(callback);
        break;
    case 951:
        wrapper->m_mapToCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_mapTo>(callback);
        break;
    case 952:
        wrapper->m_mapToGlobalCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_mapToGlobal>(callback);
        break;
    case 953:
        wrapper->m_maxSizeHintCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_maxSizeHint>(callback);
        break;
    case 954:
        wrapper->m_minSizeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_minSize>(callback);
        break;
    case 955:
        wrapper->m_minimumHeightCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_minimumHeight>(callback);
        break;
    case 956:
        wrapper->m_minimumWidthCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_minimumWidth>(callback);
        break;
    case 958:
        wrapper->m_move_2Callback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_move_2>(callback);
        break;
    case 1053:
        wrapper->m_moveTabToCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_moveTabTo>(callback);
        break;
    case 959:
        wrapper->m_normalGeometryCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_normalGeometry>(callback);
        break;
    case 960:
        wrapper->m_objectNameCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_objectName>(callback);
        break;
    case 1028:
        wrapper->m_onChildAddedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_onChildAdded>(callback);
        break;
    case 1029:
        wrapper->m_onChildRemovedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_onChildRemoved>(callback);
        break;
    case 1054:
        wrapper->m_onRebuildRequestedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_onRebuildRequested>(callback);
        break;
    case 962:
        wrapper->m_onResize_2Callback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_onResize_2>(callback);
        break;
    case 965:
        wrapper->m_raiseCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_raise>(callback);
        break;
    case 966:
        wrapper->m_raiseAndActivateCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_raiseAndActivate>(callback);
        break;
    case 1055:
        wrapper->m_rectForTabCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_rectForTab>(callback);
        break;
    case 968:
        wrapper->m_releaseKeyboardCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_releaseKeyboard>(callback);
        break;
    case 969:
        wrapper->m_releaseMouseCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_releaseMouse>(callback);
        break;
    case 1056:
        wrapper->m_removeDockWidgetCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_removeDockWidget>(callback);
        break;
    case 1057:
        wrapper->m_renameTabCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_renameTab>(callback);
        break;
    case 1058:
        wrapper->m_setCurrentIndexCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_setCurrentIndex>(callback);
        break;
    case 973:
        wrapper->m_setCursorCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_setCursor>(callback);
        break;
    case 974:
        wrapper->m_setFixedHeightCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_setFixedHeight>(callback);
        break;
    case 975:
        wrapper->m_setFixedWidthCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_setFixedWidth>(callback);
        break;
    case 976:
        wrapper->m_setGeometryCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_setGeometry>(callback);
        break;
    case 977:
        wrapper->m_setHeightCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_setHeight>(callback);
        break;
    case 978:
        wrapper->m_setMaximumSizeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_setMaximumSize>(callback);
        break;
    case 979:
        wrapper->m_setMinimumSizeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_setMinimumSize>(callback);
        break;
    case 980:
        wrapper->m_setMouseTrackingCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_setMouseTracking>(callback);
        break;
    case 981:
        wrapper->m_setObjectNameCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_setObjectName>(callback);
        break;
    case 982:
        wrapper->m_setParentCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_setParent>(callback);
        break;
    case 984:
        wrapper->m_setSize_2Callback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_setSize_2>(callback);
        break;
    case 985:
        wrapper->m_setVisibleCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_setVisible>(callback);
        break;
    case 986:
        wrapper->m_setWidthCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_setWidth>(callback);
        break;
    case 987:
        wrapper->m_setWindowOpacityCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_setWindowOpacity>(callback);
        break;
    case 988:
        wrapper->m_setWindowTitleCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_setWindowTitle>(callback);
        break;
    case 989:
        wrapper->m_setZOrderCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_setZOrder>(callback);
        break;
    case 990:
        wrapper->m_showCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_show>(callback);
        break;
    case 991:
        wrapper->m_showMaximizedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_showMaximized>(callback);
        break;
    case 992:
        wrapper->m_showMinimizedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_showMinimized>(callback);
        break;
    case 993:
        wrapper->m_showNormalCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_showNormal>(callback);
        break;
    case 995:
        wrapper->m_sizeHintCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_sizeHint>(callback);
        break;
    case 1061:
        wrapper->m_tabAtCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_tabAt>(callback);
        break;
    case 1062:
        wrapper->m_textCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_text>(callback);
        break;
    case 997:
        wrapper->m_updateCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::TabBar_wrapper::Callback_update>(callback);
        break;
    }
}
}

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "Stack_c.h"


#include <iostream>

#include <cassert>


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
Stack_wrapper::Stack_wrapper(KDDockWidgets::Core::Stack *controller, KDDockWidgets::Core::View *parent)
    : ::KDDockWidgets::flutter::Stack(controller, parent)
{
}
void Stack_wrapper::activateWindow()
{
    if (m_activateWindowCallback) {
        const void *thisPtr = this;
        m_activateWindowCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::Stack::activateWindow();
    }
}
void Stack_wrapper::activateWindow_nocallback()
{
    ::KDDockWidgets::flutter::Stack::activateWindow();
}
bool Stack_wrapper::close()
{
    if (m_closeCallback) {
        const void *thisPtr = this;
        return m_closeCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::Stack::close();
    }
}
bool Stack_wrapper::close_nocallback()
{
    return ::KDDockWidgets::flutter::Stack::close();
}
void Stack_wrapper::createPlatformWindow()
{
    if (m_createPlatformWindowCallback) {
        const void *thisPtr = this;
        m_createPlatformWindowCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::Stack::createPlatformWindow();
    }
}
void Stack_wrapper::createPlatformWindow_nocallback()
{
    ::KDDockWidgets::flutter::Stack::createPlatformWindow();
}
Qt::WindowFlags Stack_wrapper::flags() const
{
    if (m_flagsCallback) {
        const void *thisPtr = this;
        return m_flagsCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::Stack::flags();
    }
}
Qt::WindowFlags Stack_wrapper::flags_nocallback() const
{
    return ::KDDockWidgets::flutter::Stack::flags();
}
KDDockWidgets::Rect Stack_wrapper::geometry() const
{
    if (m_geometryCallback) {
        const void *thisPtr = this;
        return *m_geometryCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::Stack::geometry();
    }
}
KDDockWidgets::Rect Stack_wrapper::geometry_nocallback() const
{
    return ::KDDockWidgets::flutter::Stack::geometry();
}
void Stack_wrapper::grabMouse()
{
    if (m_grabMouseCallback) {
        const void *thisPtr = this;
        m_grabMouseCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::Stack::grabMouse();
    }
}
void Stack_wrapper::grabMouse_nocallback()
{
    ::KDDockWidgets::flutter::Stack::grabMouse();
}
bool Stack_wrapper::hasFocus() const
{
    if (m_hasFocusCallback) {
        const void *thisPtr = this;
        return m_hasFocusCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::Stack::hasFocus();
    }
}
bool Stack_wrapper::hasFocus_nocallback() const
{
    return ::KDDockWidgets::flutter::Stack::hasFocus();
}
void Stack_wrapper::hide()
{
    if (m_hideCallback) {
        const void *thisPtr = this;
        m_hideCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::Stack::hide();
    }
}
void Stack_wrapper::hide_nocallback()
{
    ::KDDockWidgets::flutter::Stack::hide();
}
void Stack_wrapper::init()
{
    if (m_initCallback) {
        const void *thisPtr = this;
        m_initCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::Stack::init();
    }
}
void Stack_wrapper::init_nocallback()
{
    ::KDDockWidgets::flutter::Stack::init();
}
bool Stack_wrapper::isActiveWindow() const
{
    if (m_isActiveWindowCallback) {
        const void *thisPtr = this;
        return m_isActiveWindowCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::Stack::isActiveWindow();
    }
}
bool Stack_wrapper::isActiveWindow_nocallback() const
{
    return ::KDDockWidgets::flutter::Stack::isActiveWindow();
}
bool Stack_wrapper::isExplicitlyHidden() const
{
    if (m_isExplicitlyHiddenCallback) {
        const void *thisPtr = this;
        return m_isExplicitlyHiddenCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::Stack::isExplicitlyHidden();
    }
}
bool Stack_wrapper::isExplicitlyHidden_nocallback() const
{
    return ::KDDockWidgets::flutter::Stack::isExplicitlyHidden();
}
bool Stack_wrapper::isMaximized() const
{
    if (m_isMaximizedCallback) {
        const void *thisPtr = this;
        return m_isMaximizedCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::Stack::isMaximized();
    }
}
bool Stack_wrapper::isMaximized_nocallback() const
{
    return ::KDDockWidgets::flutter::Stack::isMaximized();
}
bool Stack_wrapper::isMinimized() const
{
    if (m_isMinimizedCallback) {
        const void *thisPtr = this;
        return m_isMinimizedCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::Stack::isMinimized();
    }
}
bool Stack_wrapper::isMinimized_nocallback() const
{
    return ::KDDockWidgets::flutter::Stack::isMinimized();
}
bool Stack_wrapper::isMounted() const
{
    if (m_isMountedCallback) {
        const void *thisPtr = this;
        return m_isMountedCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::Stack::isMounted();
    }
}
bool Stack_wrapper::isMounted_nocallback() const
{
    return ::KDDockWidgets::flutter::Stack::isMounted();
}
bool Stack_wrapper::isNull() const
{
    if (m_isNullCallback) {
        const void *thisPtr = this;
        return m_isNullCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::Stack::isNull();
    }
}
bool Stack_wrapper::isNull_nocallback() const
{
    return ::KDDockWidgets::flutter::Stack::isNull();
}
bool Stack_wrapper::isPositionDraggable(KDDockWidgets::Point p) const
{
    if (m_isPositionDraggableCallback) {
        const void *thisPtr = this;
        return m_isPositionDraggableCallback(const_cast<void *>(thisPtr), &p);
    } else {
        return ::KDDockWidgets::flutter::Stack::isPositionDraggable(p);
    }
}
bool Stack_wrapper::isPositionDraggable_nocallback(KDDockWidgets::Point p) const
{
    return ::KDDockWidgets::flutter::Stack::isPositionDraggable(p);
}
bool Stack_wrapper::isRootView() const
{
    if (m_isRootViewCallback) {
        const void *thisPtr = this;
        return m_isRootViewCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::Stack::isRootView();
    }
}
bool Stack_wrapper::isRootView_nocallback() const
{
    return ::KDDockWidgets::flutter::Stack::isRootView();
}
bool Stack_wrapper::isVisible() const
{
    if (m_isVisibleCallback) {
        const void *thisPtr = this;
        return m_isVisibleCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::Stack::isVisible();
    }
}
bool Stack_wrapper::isVisible_nocallback() const
{
    return ::KDDockWidgets::flutter::Stack::isVisible();
}
KDDockWidgets::Point Stack_wrapper::mapFromGlobal(KDDockWidgets::Point globalPt) const
{
    if (m_mapFromGlobalCallback) {
        const void *thisPtr = this;
        return *m_mapFromGlobalCallback(const_cast<void *>(thisPtr), &globalPt);
    } else {
        return ::KDDockWidgets::flutter::Stack::mapFromGlobal(globalPt);
    }
}
KDDockWidgets::Point Stack_wrapper::mapFromGlobal_nocallback(KDDockWidgets::Point globalPt) const
{
    return ::KDDockWidgets::flutter::Stack::mapFromGlobal(globalPt);
}
KDDockWidgets::Point Stack_wrapper::mapTo(KDDockWidgets::Core::View *parent, KDDockWidgets::Point pos) const
{
    if (m_mapToCallback) {
        const void *thisPtr = this;
        return *m_mapToCallback(const_cast<void *>(thisPtr), parent, &pos);
    } else {
        return ::KDDockWidgets::flutter::Stack::mapTo(parent, pos);
    }
}
KDDockWidgets::Point Stack_wrapper::mapTo_nocallback(KDDockWidgets::Core::View *parent, KDDockWidgets::Point pos) const
{
    return ::KDDockWidgets::flutter::Stack::mapTo(parent, pos);
}
KDDockWidgets::Point Stack_wrapper::mapToGlobal(KDDockWidgets::Point localPt) const
{
    if (m_mapToGlobalCallback) {
        const void *thisPtr = this;
        return *m_mapToGlobalCallback(const_cast<void *>(thisPtr), &localPt);
    } else {
        return ::KDDockWidgets::flutter::Stack::mapToGlobal(localPt);
    }
}
KDDockWidgets::Point Stack_wrapper::mapToGlobal_nocallback(KDDockWidgets::Point localPt) const
{
    return ::KDDockWidgets::flutter::Stack::mapToGlobal(localPt);
}
KDDockWidgets::Size Stack_wrapper::maxSizeHint() const
{
    if (m_maxSizeHintCallback) {
        const void *thisPtr = this;
        return *m_maxSizeHintCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::Stack::maxSizeHint();
    }
}
KDDockWidgets::Size Stack_wrapper::maxSizeHint_nocallback() const
{
    return ::KDDockWidgets::flutter::Stack::maxSizeHint();
}
KDDockWidgets::Size Stack_wrapper::minSize() const
{
    if (m_minSizeCallback) {
        const void *thisPtr = this;
        return *m_minSizeCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::Stack::minSize();
    }
}
KDDockWidgets::Size Stack_wrapper::minSize_nocallback() const
{
    return ::KDDockWidgets::flutter::Stack::minSize();
}
void Stack_wrapper::move(int x, int y)
{
    if (m_move_2Callback) {
        const void *thisPtr = this;
        m_move_2Callback(const_cast<void *>(thisPtr), x, y);
    } else {
        ::KDDockWidgets::flutter::Stack::move(x, y);
    }
}
void Stack_wrapper::move_nocallback(int x, int y)
{
    ::KDDockWidgets::flutter::Stack::move(x, y);
}
KDDockWidgets::Rect Stack_wrapper::normalGeometry() const
{
    if (m_normalGeometryCallback) {
        const void *thisPtr = this;
        return *m_normalGeometryCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::Stack::normalGeometry();
    }
}
KDDockWidgets::Rect Stack_wrapper::normalGeometry_nocallback() const
{
    return ::KDDockWidgets::flutter::Stack::normalGeometry();
}
void Stack_wrapper::onChildAdded(KDDockWidgets::Core::View *childView)
{
    if (m_onChildAddedCallback) {
        const void *thisPtr = this;
        m_onChildAddedCallback(const_cast<void *>(thisPtr), childView);
    } else {
        ::KDDockWidgets::flutter::Stack::onChildAdded(childView);
    }
}
void Stack_wrapper::onChildAdded_nocallback(KDDockWidgets::Core::View *childView)
{
    ::KDDockWidgets::flutter::Stack::onChildAdded(childView);
}
void Stack_wrapper::onChildRemoved(KDDockWidgets::Core::View *childView)
{
    if (m_onChildRemovedCallback) {
        const void *thisPtr = this;
        m_onChildRemovedCallback(const_cast<void *>(thisPtr), childView);
    } else {
        ::KDDockWidgets::flutter::Stack::onChildRemoved(childView);
    }
}
void Stack_wrapper::onChildRemoved_nocallback(KDDockWidgets::Core::View *childView)
{
    ::KDDockWidgets::flutter::Stack::onChildRemoved(childView);
}
void Stack_wrapper::onChildVisibilityChanged(KDDockWidgets::Core::View *childView)
{
    if (m_onChildVisibilityChangedCallback) {
        const void *thisPtr = this;
        m_onChildVisibilityChangedCallback(const_cast<void *>(thisPtr), childView);
    } else {
        ::KDDockWidgets::flutter::Stack::onChildVisibilityChanged(childView);
    }
}
void Stack_wrapper::onChildVisibilityChanged_nocallback(KDDockWidgets::Core::View *childView)
{
    ::KDDockWidgets::flutter::Stack::onChildVisibilityChanged(childView);
}
void Stack_wrapper::onGeometryChanged()
{
    if (m_onGeometryChangedCallback) {
        const void *thisPtr = this;
        m_onGeometryChangedCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::Stack::onGeometryChanged();
    }
}
void Stack_wrapper::onGeometryChanged_nocallback()
{
    ::KDDockWidgets::flutter::Stack::onGeometryChanged();
}
void Stack_wrapper::onRebuildRequested()
{
    if (m_onRebuildRequestedCallback) {
        const void *thisPtr = this;
        m_onRebuildRequestedCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::Stack::onRebuildRequested();
    }
}
void Stack_wrapper::onRebuildRequested_nocallback()
{
    ::KDDockWidgets::flutter::Stack::onRebuildRequested();
}
bool Stack_wrapper::onResize(int h, int w)
{
    if (m_onResize_2Callback) {
        const void *thisPtr = this;
        return m_onResize_2Callback(const_cast<void *>(thisPtr), h, w);
    } else {
        return ::KDDockWidgets::flutter::Stack::onResize(h, w);
    }
}
bool Stack_wrapper::onResize_nocallback(int h, int w)
{
    return ::KDDockWidgets::flutter::Stack::onResize(h, w);
}
void Stack_wrapper::raise()
{
    if (m_raiseCallback) {
        const void *thisPtr = this;
        m_raiseCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::Stack::raise();
    }
}
void Stack_wrapper::raise_nocallback()
{
    ::KDDockWidgets::flutter::Stack::raise();
}
void Stack_wrapper::raiseAndActivate()
{
    if (m_raiseAndActivateCallback) {
        const void *thisPtr = this;
        m_raiseAndActivateCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::Stack::raiseAndActivate();
    }
}
void Stack_wrapper::raiseAndActivate_nocallback()
{
    ::KDDockWidgets::flutter::Stack::raiseAndActivate();
}
void Stack_wrapper::raiseChild(KDDockWidgets::Core::View *childView)
{
    if (m_raiseChildCallback) {
        const void *thisPtr = this;
        m_raiseChildCallback(const_cast<void *>(thisPtr), childView);
    } else {
        ::KDDockWidgets::flutter::Stack::raiseChild(childView);
    }
}
void Stack_wrapper::raiseChild_nocallback(KDDockWidgets::Core::View *childView)
{
    ::KDDockWidgets::flutter::Stack::raiseChild(childView);
}
void Stack_wrapper::raiseWindow(KDDockWidgets::Core::View *rootView)
{
    if (m_raiseWindowCallback) {
        const void *thisPtr = this;
        m_raiseWindowCallback(const_cast<void *>(thisPtr), rootView);
    } else {
        ::KDDockWidgets::flutter::Stack::raiseWindow(rootView);
    }
}
void Stack_wrapper::raiseWindow_nocallback(KDDockWidgets::Core::View *rootView)
{
    ::KDDockWidgets::flutter::Stack::raiseWindow(rootView);
}
void Stack_wrapper::releaseKeyboard()
{
    if (m_releaseKeyboardCallback) {
        const void *thisPtr = this;
        m_releaseKeyboardCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::Stack::releaseKeyboard();
    }
}
void Stack_wrapper::releaseKeyboard_nocallback()
{
    ::KDDockWidgets::flutter::Stack::releaseKeyboard();
}
void Stack_wrapper::releaseMouse()
{
    if (m_releaseMouseCallback) {
        const void *thisPtr = this;
        m_releaseMouseCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::Stack::releaseMouse();
    }
}
void Stack_wrapper::releaseMouse_nocallback()
{
    ::KDDockWidgets::flutter::Stack::releaseMouse();
}
void Stack_wrapper::setCursor(Qt::CursorShape shape)
{
    if (m_setCursorCallback) {
        const void *thisPtr = this;
        m_setCursorCallback(const_cast<void *>(thisPtr), shape);
    } else {
        ::KDDockWidgets::flutter::Stack::setCursor(shape);
    }
}
void Stack_wrapper::setCursor_nocallback(Qt::CursorShape shape)
{
    ::KDDockWidgets::flutter::Stack::setCursor(shape);
}
void Stack_wrapper::setDocumentMode(bool arg__1)
{
    if (m_setDocumentModeCallback) {
        const void *thisPtr = this;
        m_setDocumentModeCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        ::KDDockWidgets::flutter::Stack::setDocumentMode(arg__1);
    }
}
void Stack_wrapper::setDocumentMode_nocallback(bool arg__1)
{
    ::KDDockWidgets::flutter::Stack::setDocumentMode(arg__1);
}
void Stack_wrapper::setFixedHeight(int h)
{
    if (m_setFixedHeightCallback) {
        const void *thisPtr = this;
        m_setFixedHeightCallback(const_cast<void *>(thisPtr), h);
    } else {
        ::KDDockWidgets::flutter::Stack::setFixedHeight(h);
    }
}
void Stack_wrapper::setFixedHeight_nocallback(int h)
{
    ::KDDockWidgets::flutter::Stack::setFixedHeight(h);
}
void Stack_wrapper::setFixedWidth(int w)
{
    if (m_setFixedWidthCallback) {
        const void *thisPtr = this;
        m_setFixedWidthCallback(const_cast<void *>(thisPtr), w);
    } else {
        ::KDDockWidgets::flutter::Stack::setFixedWidth(w);
    }
}
void Stack_wrapper::setFixedWidth_nocallback(int w)
{
    ::KDDockWidgets::flutter::Stack::setFixedWidth(w);
}
void Stack_wrapper::setGeometry(KDDockWidgets::Rect geometry)
{
    if (m_setGeometryCallback) {
        const void *thisPtr = this;
        m_setGeometryCallback(const_cast<void *>(thisPtr), &geometry);
    } else {
        ::KDDockWidgets::flutter::Stack::setGeometry(geometry);
    }
}
void Stack_wrapper::setGeometry_nocallback(KDDockWidgets::Rect geometry)
{
    ::KDDockWidgets::flutter::Stack::setGeometry(geometry);
}
void Stack_wrapper::setHeight(int h)
{
    if (m_setHeightCallback) {
        const void *thisPtr = this;
        m_setHeightCallback(const_cast<void *>(thisPtr), h);
    } else {
        ::KDDockWidgets::flutter::Stack::setHeight(h);
    }
}
void Stack_wrapper::setHeight_nocallback(int h)
{
    ::KDDockWidgets::flutter::Stack::setHeight(h);
}
void Stack_wrapper::setMaximumSize(KDDockWidgets::Size sz)
{
    if (m_setMaximumSizeCallback) {
        const void *thisPtr = this;
        m_setMaximumSizeCallback(const_cast<void *>(thisPtr), &sz);
    } else {
        ::KDDockWidgets::flutter::Stack::setMaximumSize(sz);
    }
}
void Stack_wrapper::setMaximumSize_nocallback(KDDockWidgets::Size sz)
{
    ::KDDockWidgets::flutter::Stack::setMaximumSize(sz);
}
void Stack_wrapper::setMinimumSize(KDDockWidgets::Size sz)
{
    if (m_setMinimumSizeCallback) {
        const void *thisPtr = this;
        m_setMinimumSizeCallback(const_cast<void *>(thisPtr), &sz);
    } else {
        ::KDDockWidgets::flutter::Stack::setMinimumSize(sz);
    }
}
void Stack_wrapper::setMinimumSize_nocallback(KDDockWidgets::Size sz)
{
    ::KDDockWidgets::flutter::Stack::setMinimumSize(sz);
}
void Stack_wrapper::setMouseTracking(bool enable)
{
    if (m_setMouseTrackingCallback) {
        const void *thisPtr = this;
        m_setMouseTrackingCallback(const_cast<void *>(thisPtr), enable);
    } else {
        ::KDDockWidgets::flutter::Stack::setMouseTracking(enable);
    }
}
void Stack_wrapper::setMouseTracking_nocallback(bool enable)
{
    ::KDDockWidgets::flutter::Stack::setMouseTracking(enable);
}
void Stack_wrapper::setParent(KDDockWidgets::Core::View *parent)
{
    if (m_setParentCallback) {
        const void *thisPtr = this;
        m_setParentCallback(const_cast<void *>(thisPtr), parent);
    } else {
        ::KDDockWidgets::flutter::Stack::setParent(parent);
    }
}
void Stack_wrapper::setParent_nocallback(KDDockWidgets::Core::View *parent)
{
    ::KDDockWidgets::flutter::Stack::setParent(parent);
}
void Stack_wrapper::setSize(int w, int h)
{
    if (m_setSize_2Callback) {
        const void *thisPtr = this;
        m_setSize_2Callback(const_cast<void *>(thisPtr), w, h);
    } else {
        ::KDDockWidgets::flutter::Stack::setSize(w, h);
    }
}
void Stack_wrapper::setSize_nocallback(int w, int h)
{
    ::KDDockWidgets::flutter::Stack::setSize(w, h);
}
void Stack_wrapper::setViewName(const QString &name)
{
    if (m_setViewNameCallback) {
        const void *thisPtr = this;
        m_setViewNameCallback(const_cast<void *>(thisPtr), name);
    } else {
        ::KDDockWidgets::flutter::Stack::setViewName(name);
    }
}
void Stack_wrapper::setViewName_nocallback(const QString &name)
{
    ::KDDockWidgets::flutter::Stack::setViewName(name);
}
void Stack_wrapper::setVisible(bool visible)
{
    if (m_setVisibleCallback) {
        const void *thisPtr = this;
        m_setVisibleCallback(const_cast<void *>(thisPtr), visible);
    } else {
        ::KDDockWidgets::flutter::Stack::setVisible(visible);
    }
}
void Stack_wrapper::setVisible_nocallback(bool visible)
{
    ::KDDockWidgets::flutter::Stack::setVisible(visible);
}
void Stack_wrapper::setWidth(int w)
{
    if (m_setWidthCallback) {
        const void *thisPtr = this;
        m_setWidthCallback(const_cast<void *>(thisPtr), w);
    } else {
        ::KDDockWidgets::flutter::Stack::setWidth(w);
    }
}
void Stack_wrapper::setWidth_nocallback(int w)
{
    ::KDDockWidgets::flutter::Stack::setWidth(w);
}
void Stack_wrapper::setWindowOpacity(double v)
{
    if (m_setWindowOpacityCallback) {
        const void *thisPtr = this;
        m_setWindowOpacityCallback(const_cast<void *>(thisPtr), v);
    } else {
        ::KDDockWidgets::flutter::Stack::setWindowOpacity(v);
    }
}
void Stack_wrapper::setWindowOpacity_nocallback(double v)
{
    ::KDDockWidgets::flutter::Stack::setWindowOpacity(v);
}
void Stack_wrapper::setWindowTitle(const QString &title)
{
    if (m_setWindowTitleCallback) {
        const void *thisPtr = this;
        m_setWindowTitleCallback(const_cast<void *>(thisPtr), title);
    } else {
        ::KDDockWidgets::flutter::Stack::setWindowTitle(title);
    }
}
void Stack_wrapper::setWindowTitle_nocallback(const QString &title)
{
    ::KDDockWidgets::flutter::Stack::setWindowTitle(title);
}
void Stack_wrapper::setZOrder(int z)
{
    if (m_setZOrderCallback) {
        const void *thisPtr = this;
        m_setZOrderCallback(const_cast<void *>(thisPtr), z);
    } else {
        ::KDDockWidgets::flutter::Stack::setZOrder(z);
    }
}
void Stack_wrapper::setZOrder_nocallback(int z)
{
    ::KDDockWidgets::flutter::Stack::setZOrder(z);
}
void Stack_wrapper::show()
{
    if (m_showCallback) {
        const void *thisPtr = this;
        m_showCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::Stack::show();
    }
}
void Stack_wrapper::show_nocallback()
{
    ::KDDockWidgets::flutter::Stack::show();
}
void Stack_wrapper::showMaximized()
{
    if (m_showMaximizedCallback) {
        const void *thisPtr = this;
        m_showMaximizedCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::Stack::showMaximized();
    }
}
void Stack_wrapper::showMaximized_nocallback()
{
    ::KDDockWidgets::flutter::Stack::showMaximized();
}
void Stack_wrapper::showMinimized()
{
    if (m_showMinimizedCallback) {
        const void *thisPtr = this;
        m_showMinimizedCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::Stack::showMinimized();
    }
}
void Stack_wrapper::showMinimized_nocallback()
{
    ::KDDockWidgets::flutter::Stack::showMinimized();
}
void Stack_wrapper::showNormal()
{
    if (m_showNormalCallback) {
        const void *thisPtr = this;
        m_showNormalCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::Stack::showNormal();
    }
}
void Stack_wrapper::showNormal_nocallback()
{
    ::KDDockWidgets::flutter::Stack::showNormal();
}
void Stack_wrapper::update()
{
    if (m_updateCallback) {
        const void *thisPtr = this;
        m_updateCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::Stack::update();
    }
}
void Stack_wrapper::update_nocallback()
{
    ::KDDockWidgets::flutter::Stack::update();
}
QString Stack_wrapper::viewName() const
{
    if (m_viewNameCallback) {
        const void *thisPtr = this;
        return *m_viewNameCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::Stack::viewName();
    }
}
QString Stack_wrapper::viewName_nocallback() const
{
    return ::KDDockWidgets::flutter::Stack::viewName();
}
Stack_wrapper::~Stack_wrapper()
{
}

}
}
static KDDockWidgets::flutter::Stack *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::flutter::Stack *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__flutter__Stack_Finalizer(void *cppObj)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper *>(cppObj);
}
void *c_KDDockWidgets__flutter__Stack__constructor_Stack_View(void *controller_, void *parent_)
{
    auto controller = reinterpret_cast<KDDockWidgets::Core::Stack *>(controller_);
    auto parent = reinterpret_cast<KDDockWidgets::Core::View *>(parent_);
    auto ptr = new KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper(controller, parent);
    return reinterpret_cast<void *>(ptr);
}
// activateWindow()
void c_KDDockWidgets__flutter__Stack__activateWindow(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->activateWindow_nocallback();} else {    return targetPtr->activateWindow();} }();
}
// close()
bool c_KDDockWidgets__flutter__Stack__close(void *thisObj)
{
    const auto &result = [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->close_nocallback();} else {    return targetPtr->close();} }();
    return result;
}
// createPlatformWindow()
void c_KDDockWidgets__flutter__Stack__createPlatformWindow(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->createPlatformWindow_nocallback();} else {    return targetPtr->createPlatformWindow();} }();
}
// flags() const
int c_KDDockWidgets__flutter__Stack__flags(void *thisObj)
{
    const auto &result = [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->flags_nocallback();} else {    return targetPtr->flags();} }();
    return result;
}
// geometry() const
void *c_KDDockWidgets__flutter__Stack__geometry(void *thisObj)
{
    const auto &result = new Dartagnan::ValueWrapper<KDDockWidgets::Rect> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->geometry_nocallback();} else {    return targetPtr->geometry();} }() };
    return result;
}
// grabMouse()
void c_KDDockWidgets__flutter__Stack__grabMouse(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->grabMouse_nocallback();} else {    return targetPtr->grabMouse();} }();
}
// hasFocus() const
bool c_KDDockWidgets__flutter__Stack__hasFocus(void *thisObj)
{
    const auto &result = [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->hasFocus_nocallback();} else {    return targetPtr->hasFocus();} }();
    return result;
}
// hide()
void c_KDDockWidgets__flutter__Stack__hide(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->hide_nocallback();} else {    return targetPtr->hide();} }();
}
// init()
void c_KDDockWidgets__flutter__Stack__init(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->init_nocallback();} else {    return targetPtr->init();} }();
}
// isActiveWindow() const
bool c_KDDockWidgets__flutter__Stack__isActiveWindow(void *thisObj)
{
    const auto &result = [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isActiveWindow_nocallback();} else {    return targetPtr->isActiveWindow();} }();
    return result;
}
// isExplicitlyHidden() const
bool c_KDDockWidgets__flutter__Stack__isExplicitlyHidden(void *thisObj)
{
    const auto &result = [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isExplicitlyHidden_nocallback();} else {    return targetPtr->isExplicitlyHidden();} }();
    return result;
}
// isMaximized() const
bool c_KDDockWidgets__flutter__Stack__isMaximized(void *thisObj)
{
    const auto &result = [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isMaximized_nocallback();} else {    return targetPtr->isMaximized();} }();
    return result;
}
// isMinimized() const
bool c_KDDockWidgets__flutter__Stack__isMinimized(void *thisObj)
{
    const auto &result = [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isMinimized_nocallback();} else {    return targetPtr->isMinimized();} }();
    return result;
}
// isMounted() const
bool c_KDDockWidgets__flutter__Stack__isMounted(void *thisObj)
{
    const auto &result = [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isMounted_nocallback();} else {    return targetPtr->isMounted();} }();
    return result;
}
// isNull() const
bool c_KDDockWidgets__flutter__Stack__isNull(void *thisObj)
{
    const auto &result = [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isNull_nocallback();} else {    return targetPtr->isNull();} }();
    return result;
}
// isPositionDraggable(KDDockWidgets::Point p) const
bool c_KDDockWidgets__flutter__Stack__isPositionDraggable_Point(void *thisObj, void *p_)
{
    assert(p_);
    auto &p = *reinterpret_cast<KDDockWidgets::Point *>(p_);
    const auto &result = [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isPositionDraggable_nocallback(p);} else {    return targetPtr->isPositionDraggable(p);} }();
    return result;
}
// isRootView() const
bool c_KDDockWidgets__flutter__Stack__isRootView(void *thisObj)
{
    const auto &result = [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isRootView_nocallback();} else {    return targetPtr->isRootView();} }();
    return result;
}
// isVisible() const
bool c_KDDockWidgets__flutter__Stack__isVisible(void *thisObj)
{
    const auto &result = [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isVisible_nocallback();} else {    return targetPtr->isVisible();} }();
    return result;
}
// mapFromGlobal(KDDockWidgets::Point globalPt) const
void *c_KDDockWidgets__flutter__Stack__mapFromGlobal_Point(void *thisObj, void *globalPt_)
{
    assert(globalPt_);
    auto &globalPt = *reinterpret_cast<KDDockWidgets::Point *>(globalPt_);
    const auto &result = new Dartagnan::ValueWrapper<KDDockWidgets::Point> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->mapFromGlobal_nocallback(globalPt);} else {    return targetPtr->mapFromGlobal(globalPt);} }() };
    return result;
}
// mapTo(KDDockWidgets::Core::View * parent, KDDockWidgets::Point pos) const
void *c_KDDockWidgets__flutter__Stack__mapTo_View_Point(void *thisObj, void *parent_, void *pos_)
{
    auto parent = reinterpret_cast<KDDockWidgets::Core::View *>(parent_);
    assert(pos_);
    auto &pos = *reinterpret_cast<KDDockWidgets::Point *>(pos_);
    const auto &result = new Dartagnan::ValueWrapper<KDDockWidgets::Point> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->mapTo_nocallback(parent,pos);} else {    return targetPtr->mapTo(parent,pos);} }() };
    return result;
}
// mapToGlobal(KDDockWidgets::Point localPt) const
void *c_KDDockWidgets__flutter__Stack__mapToGlobal_Point(void *thisObj, void *localPt_)
{
    assert(localPt_);
    auto &localPt = *reinterpret_cast<KDDockWidgets::Point *>(localPt_);
    const auto &result = new Dartagnan::ValueWrapper<KDDockWidgets::Point> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->mapToGlobal_nocallback(localPt);} else {    return targetPtr->mapToGlobal(localPt);} }() };
    return result;
}
// maxSizeHint() const
void *c_KDDockWidgets__flutter__Stack__maxSizeHint(void *thisObj)
{
    const auto &result = new Dartagnan::ValueWrapper<KDDockWidgets::Size> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->maxSizeHint_nocallback();} else {    return targetPtr->maxSizeHint();} }() };
    return result;
}
// minSize() const
void *c_KDDockWidgets__flutter__Stack__minSize(void *thisObj)
{
    const auto &result = new Dartagnan::ValueWrapper<KDDockWidgets::Size> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->minSize_nocallback();} else {    return targetPtr->minSize();} }() };
    return result;
}
// move(int x, int y)
void c_KDDockWidgets__flutter__Stack__move_int_int(void *thisObj, int x, int y)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->move_nocallback(x,y);} else {    return targetPtr->move(x,y);} }();
}
// normalGeometry() const
void *c_KDDockWidgets__flutter__Stack__normalGeometry(void *thisObj)
{
    const auto &result = new Dartagnan::ValueWrapper<KDDockWidgets::Rect> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->normalGeometry_nocallback();} else {    return targetPtr->normalGeometry();} }() };
    return result;
}
// onChildAdded(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__Stack__onChildAdded_View(void *thisObj, void *childView_)
{
    auto childView = reinterpret_cast<KDDockWidgets::Core::View *>(childView_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->onChildAdded_nocallback(childView);} else {    return targetPtr->onChildAdded(childView);} }();
}
// onChildRemoved(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__Stack__onChildRemoved_View(void *thisObj, void *childView_)
{
    auto childView = reinterpret_cast<KDDockWidgets::Core::View *>(childView_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->onChildRemoved_nocallback(childView);} else {    return targetPtr->onChildRemoved(childView);} }();
}
// onChildVisibilityChanged(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__Stack__onChildVisibilityChanged_View(void *thisObj, void *childView_)
{
    auto childView = reinterpret_cast<KDDockWidgets::Core::View *>(childView_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->onChildVisibilityChanged_nocallback(childView);} else {    return targetPtr->onChildVisibilityChanged(childView);} }();
}
// onGeometryChanged()
void c_KDDockWidgets__flutter__Stack__onGeometryChanged(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->onGeometryChanged_nocallback();} else {    return targetPtr->onGeometryChanged();} }();
}
// onRebuildRequested()
void c_KDDockWidgets__flutter__Stack__onRebuildRequested(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->onRebuildRequested_nocallback();} else {    return targetPtr->onRebuildRequested();} }();
}
// onResize(int h, int w)
bool c_KDDockWidgets__flutter__Stack__onResize_int_int(void *thisObj, int h, int w)
{
    const auto &result = [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->onResize_nocallback(h,w);} else {    return targetPtr->onResize(h,w);} }();
    return result;
}
// raise()
void c_KDDockWidgets__flutter__Stack__raise(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->raise_nocallback();} else {    return targetPtr->raise();} }();
}
// raiseAndActivate()
void c_KDDockWidgets__flutter__Stack__raiseAndActivate(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->raiseAndActivate_nocallback();} else {    return targetPtr->raiseAndActivate();} }();
}
// raiseChild(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__Stack__raiseChild_View(void *thisObj, void *childView_)
{
    auto childView = reinterpret_cast<KDDockWidgets::Core::View *>(childView_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->raiseChild_nocallback(childView);} else {    return targetPtr->raiseChild(childView);} }();
}
// raiseWindow(KDDockWidgets::Core::View * rootView)
void c_KDDockWidgets__flutter__Stack__raiseWindow_View(void *thisObj, void *rootView_)
{
    auto rootView = reinterpret_cast<KDDockWidgets::Core::View *>(rootView_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->raiseWindow_nocallback(rootView);} else {    return targetPtr->raiseWindow(rootView);} }();
}
// releaseKeyboard()
void c_KDDockWidgets__flutter__Stack__releaseKeyboard(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->releaseKeyboard_nocallback();} else {    return targetPtr->releaseKeyboard();} }();
}
// releaseMouse()
void c_KDDockWidgets__flutter__Stack__releaseMouse(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->releaseMouse_nocallback();} else {    return targetPtr->releaseMouse();} }();
}
// setCursor(Qt::CursorShape shape)
void c_KDDockWidgets__flutter__Stack__setCursor_CursorShape(void *thisObj, int shape)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setCursor_nocallback(static_cast<Qt::CursorShape>(shape));} else {    return targetPtr->setCursor(static_cast<Qt::CursorShape>(shape));} }();
}
// setDocumentMode(bool arg__1)
void c_KDDockWidgets__flutter__Stack__setDocumentMode_bool(void *thisObj, bool arg__1)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setDocumentMode_nocallback(arg__1);} else {    return targetPtr->setDocumentMode(arg__1);} }();
}
// setFixedHeight(int h)
void c_KDDockWidgets__flutter__Stack__setFixedHeight_int(void *thisObj, int h)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setFixedHeight_nocallback(h);} else {    return targetPtr->setFixedHeight(h);} }();
}
// setFixedWidth(int w)
void c_KDDockWidgets__flutter__Stack__setFixedWidth_int(void *thisObj, int w)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setFixedWidth_nocallback(w);} else {    return targetPtr->setFixedWidth(w);} }();
}
// setGeometry(KDDockWidgets::Rect geometry)
void c_KDDockWidgets__flutter__Stack__setGeometry_Rect(void *thisObj, void *geometry_)
{
    assert(geometry_);
    auto &geometry = *reinterpret_cast<KDDockWidgets::Rect *>(geometry_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setGeometry_nocallback(geometry);} else {    return targetPtr->setGeometry(geometry);} }();
}
// setHeight(int h)
void c_KDDockWidgets__flutter__Stack__setHeight_int(void *thisObj, int h)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setHeight_nocallback(h);} else {    return targetPtr->setHeight(h);} }();
}
// setMaximumSize(KDDockWidgets::Size sz)
void c_KDDockWidgets__flutter__Stack__setMaximumSize_Size(void *thisObj, void *sz_)
{
    assert(sz_);
    auto &sz = *reinterpret_cast<KDDockWidgets::Size *>(sz_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setMaximumSize_nocallback(sz);} else {    return targetPtr->setMaximumSize(sz);} }();
}
// setMinimumSize(KDDockWidgets::Size sz)
void c_KDDockWidgets__flutter__Stack__setMinimumSize_Size(void *thisObj, void *sz_)
{
    assert(sz_);
    auto &sz = *reinterpret_cast<KDDockWidgets::Size *>(sz_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setMinimumSize_nocallback(sz);} else {    return targetPtr->setMinimumSize(sz);} }();
}
// setMouseTracking(bool enable)
void c_KDDockWidgets__flutter__Stack__setMouseTracking_bool(void *thisObj, bool enable)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setMouseTracking_nocallback(enable);} else {    return targetPtr->setMouseTracking(enable);} }();
}
// setParent(KDDockWidgets::Core::View * parent)
void c_KDDockWidgets__flutter__Stack__setParent_View(void *thisObj, void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::Core::View *>(parent_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setParent_nocallback(parent);} else {    return targetPtr->setParent(parent);} }();
}
// setSize(int w, int h)
void c_KDDockWidgets__flutter__Stack__setSize_int_int(void *thisObj, int w, int h)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setSize_nocallback(w,h);} else {    return targetPtr->setSize(w,h);} }();
}
// setViewName(const QString & name)
void c_KDDockWidgets__flutter__Stack__setViewName_QString(void *thisObj, const char *name_)
{
    const auto name = QString::fromUtf8(name_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setViewName_nocallback(name);} else {    return targetPtr->setViewName(name);} }();
    free(( char * )name_);
}
// setVisible(bool visible)
void c_KDDockWidgets__flutter__Stack__setVisible_bool(void *thisObj, bool visible)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setVisible_nocallback(visible);} else {    return targetPtr->setVisible(visible);} }();
}
// setWidth(int w)
void c_KDDockWidgets__flutter__Stack__setWidth_int(void *thisObj, int w)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setWidth_nocallback(w);} else {    return targetPtr->setWidth(w);} }();
}
// setWindowOpacity(double v)
void c_KDDockWidgets__flutter__Stack__setWindowOpacity_double(void *thisObj, double v)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setWindowOpacity_nocallback(v);} else {    return targetPtr->setWindowOpacity(v);} }();
}
// setWindowTitle(const QString & title)
void c_KDDockWidgets__flutter__Stack__setWindowTitle_QString(void *thisObj, const char *title_)
{
    const auto title = QString::fromUtf8(title_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setWindowTitle_nocallback(title);} else {    return targetPtr->setWindowTitle(title);} }();
    free(( char * )title_);
}
// setZOrder(int z)
void c_KDDockWidgets__flutter__Stack__setZOrder_int(void *thisObj, int z)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setZOrder_nocallback(z);} else {    return targetPtr->setZOrder(z);} }();
}
// show()
void c_KDDockWidgets__flutter__Stack__show(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->show_nocallback();} else {    return targetPtr->show();} }();
}
// showMaximized()
void c_KDDockWidgets__flutter__Stack__showMaximized(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->showMaximized_nocallback();} else {    return targetPtr->showMaximized();} }();
}
// showMinimized()
void c_KDDockWidgets__flutter__Stack__showMinimized(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->showMinimized_nocallback();} else {    return targetPtr->showMinimized();} }();
}
// showNormal()
void c_KDDockWidgets__flutter__Stack__showNormal(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->showNormal_nocallback();} else {    return targetPtr->showNormal();} }();
}
// update()
void c_KDDockWidgets__flutter__Stack__update(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->update_nocallback();} else {    return targetPtr->update();} }();
}
// viewName() const
void *c_KDDockWidgets__flutter__Stack__viewName(void *thisObj)
{
    const auto &result = new Dartagnan::ValueWrapper<QString> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->viewName_nocallback();} else {    return targetPtr->viewName();} }() };
    return result;
}
void c_KDDockWidgets__flutter__Stack__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__flutter__Stack__registerVirtualMethodCallback(void *ptr, void *callback, int methodId)
{
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 342:
        wrapper->m_activateWindowCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_activateWindow>(callback);
        break;
    case 352:
        wrapper->m_closeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_close>(callback);
        break;
    case 354:
        wrapper->m_createPlatformWindowCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_createPlatformWindow>(callback);
        break;
    case 360:
        wrapper->m_flagsCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_flags>(callback);
        break;
    case 361:
        wrapper->m_geometryCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_geometry>(callback);
        break;
    case 362:
        wrapper->m_grabMouseCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_grabMouse>(callback);
        break;
    case 365:
        wrapper->m_hasFocusCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_hasFocus>(callback);
        break;
    case 367:
        wrapper->m_hideCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_hide>(callback);
        break;
    case 369:
        wrapper->m_initCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_init>(callback);
        break;
    case 371:
        wrapper->m_isActiveWindowCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_isActiveWindow>(callback);
        break;
    case 372:
        wrapper->m_isExplicitlyHiddenCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_isExplicitlyHidden>(callback);
        break;
    case 373:
        wrapper->m_isMaximizedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_isMaximized>(callback);
        break;
    case 374:
        wrapper->m_isMinimizedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_isMinimized>(callback);
        break;
    case 444:
        wrapper->m_isMountedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_isMounted>(callback);
        break;
    case 375:
        wrapper->m_isNullCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_isNull>(callback);
        break;
    case 489:
        wrapper->m_isPositionDraggableCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_isPositionDraggable>(callback);
        break;
    case 376:
        wrapper->m_isRootViewCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_isRootView>(callback);
        break;
    case 377:
        wrapper->m_isVisibleCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_isVisible>(callback);
        break;
    case 378:
        wrapper->m_mapFromGlobalCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_mapFromGlobal>(callback);
        break;
    case 379:
        wrapper->m_mapToCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_mapTo>(callback);
        break;
    case 380:
        wrapper->m_mapToGlobalCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_mapToGlobal>(callback);
        break;
    case 381:
        wrapper->m_maxSizeHintCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_maxSizeHint>(callback);
        break;
    case 382:
        wrapper->m_minSizeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_minSize>(callback);
        break;
    case 386:
        wrapper->m_move_2Callback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_move_2>(callback);
        break;
    case 387:
        wrapper->m_normalGeometryCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_normalGeometry>(callback);
        break;
    case 447:
        wrapper->m_onChildAddedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_onChildAdded>(callback);
        break;
    case 448:
        wrapper->m_onChildRemovedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_onChildRemoved>(callback);
        break;
    case 449:
        wrapper->m_onChildVisibilityChangedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_onChildVisibilityChanged>(callback);
        break;
    case 451:
        wrapper->m_onGeometryChangedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_onGeometryChanged>(callback);
        break;
    case 453:
        wrapper->m_onRebuildRequestedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_onRebuildRequested>(callback);
        break;
    case 389:
        wrapper->m_onResize_2Callback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_onResize_2>(callback);
        break;
    case 391:
        wrapper->m_raiseCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_raise>(callback);
        break;
    case 392:
        wrapper->m_raiseAndActivateCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_raiseAndActivate>(callback);
        break;
    case 456:
        wrapper->m_raiseChildCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_raiseChild>(callback);
        break;
    case 457:
        wrapper->m_raiseWindowCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_raiseWindow>(callback);
        break;
    case 394:
        wrapper->m_releaseKeyboardCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_releaseKeyboard>(callback);
        break;
    case 395:
        wrapper->m_releaseMouseCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_releaseMouse>(callback);
        break;
    case 398:
        wrapper->m_setCursorCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_setCursor>(callback);
        break;
    case 492:
        wrapper->m_setDocumentModeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_setDocumentMode>(callback);
        break;
    case 399:
        wrapper->m_setFixedHeightCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_setFixedHeight>(callback);
        break;
    case 400:
        wrapper->m_setFixedWidthCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_setFixedWidth>(callback);
        break;
    case 401:
        wrapper->m_setGeometryCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_setGeometry>(callback);
        break;
    case 402:
        wrapper->m_setHeightCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_setHeight>(callback);
        break;
    case 403:
        wrapper->m_setMaximumSizeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_setMaximumSize>(callback);
        break;
    case 404:
        wrapper->m_setMinimumSizeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_setMinimumSize>(callback);
        break;
    case 405:
        wrapper->m_setMouseTrackingCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_setMouseTracking>(callback);
        break;
    case 406:
        wrapper->m_setParentCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_setParent>(callback);
        break;
    case 408:
        wrapper->m_setSize_2Callback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_setSize_2>(callback);
        break;
    case 409:
        wrapper->m_setViewNameCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_setViewName>(callback);
        break;
    case 410:
        wrapper->m_setVisibleCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_setVisible>(callback);
        break;
    case 411:
        wrapper->m_setWidthCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_setWidth>(callback);
        break;
    case 412:
        wrapper->m_setWindowOpacityCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_setWindowOpacity>(callback);
        break;
    case 413:
        wrapper->m_setWindowTitleCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_setWindowTitle>(callback);
        break;
    case 414:
        wrapper->m_setZOrderCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_setZOrder>(callback);
        break;
    case 415:
        wrapper->m_showCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_show>(callback);
        break;
    case 416:
        wrapper->m_showMaximizedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_showMaximized>(callback);
        break;
    case 417:
        wrapper->m_showMinimizedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_showMinimized>(callback);
        break;
    case 418:
        wrapper->m_showNormalCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_showNormal>(callback);
        break;
    case 420:
        wrapper->m_updateCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_update>(callback);
        break;
    case 421:
        wrapper->m_viewNameCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::Stack_wrapper::Callback_viewName>(callback);
        break;
    }
}
}

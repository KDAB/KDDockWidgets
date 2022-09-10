/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "Group_flutter_wrapper.h"


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
Group_flutter_wrapper::Group_flutter_wrapper(KDDockWidgets::Controllers::Group *controller,
                                             KDDockWidgets::View *parent)
    : ::KDDockWidgets::Views::Group_flutter(controller, parent)
{
}
void Group_flutter_wrapper::activateWindow()
{
    if (m_activateWindowCallback) {
        const void *thisPtr = this;
        m_activateWindowCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Views::Group_flutter::activateWindow();
    }
}
void Group_flutter_wrapper::activateWindow_nocallback()
{
    ::KDDockWidgets::Views::Group_flutter::activateWindow();
}
bool Group_flutter_wrapper::close()
{
    if (m_closeCallback) {
        const void *thisPtr = this;
        return m_closeCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::Group_flutter::close();
    }
}
bool Group_flutter_wrapper::close_nocallback()
{
    return ::KDDockWidgets::Views::Group_flutter::close();
}
void Group_flutter_wrapper::createPlatformWindow()
{
    if (m_createPlatformWindowCallback) {
        const void *thisPtr = this;
        m_createPlatformWindowCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Views::Group_flutter::createPlatformWindow();
    }
}
void Group_flutter_wrapper::createPlatformWindow_nocallback()
{
    ::KDDockWidgets::Views::Group_flutter::createPlatformWindow();
}
int Group_flutter_wrapper::currentIndex() const
{
    return ::KDDockWidgets::Views::Group_flutter::currentIndex();
}
QRect Group_flutter_wrapper::dragRect() const
{
    if (m_dragRectCallback) {
        const void *thisPtr = this;
        return *m_dragRectCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::Group_flutter::dragRect();
    }
}
QRect Group_flutter_wrapper::dragRect_nocallback() const
{
    return ::KDDockWidgets::Views::Group_flutter::dragRect();
}
Qt::WindowFlags Group_flutter_wrapper::flags() const
{
    if (m_flagsCallback) {
        const void *thisPtr = this;
        return m_flagsCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::Group_flutter::flags();
    }
}
Qt::WindowFlags Group_flutter_wrapper::flags_nocallback() const
{
    return ::KDDockWidgets::Views::Group_flutter::flags();
}
void Group_flutter_wrapper::free_impl()
{
    if (m_free_implCallback) {
        const void *thisPtr = this;
        m_free_implCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Views::Group_flutter::free_impl();
    }
}
void Group_flutter_wrapper::free_impl_nocallback()
{
    ::KDDockWidgets::Views::Group_flutter::free_impl();
}
QRect Group_flutter_wrapper::geometry() const
{
    if (m_geometryCallback) {
        const void *thisPtr = this;
        return *m_geometryCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::Group_flutter::geometry();
    }
}
QRect Group_flutter_wrapper::geometry_nocallback() const
{
    return ::KDDockWidgets::Views::Group_flutter::geometry();
}
void Group_flutter_wrapper::grabMouse()
{
    if (m_grabMouseCallback) {
        const void *thisPtr = this;
        m_grabMouseCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Views::Group_flutter::grabMouse();
    }
}
void Group_flutter_wrapper::grabMouse_nocallback()
{
    ::KDDockWidgets::Views::Group_flutter::grabMouse();
}
bool Group_flutter_wrapper::hasFocus() const
{
    if (m_hasFocusCallback) {
        const void *thisPtr = this;
        return m_hasFocusCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::Group_flutter::hasFocus();
    }
}
bool Group_flutter_wrapper::hasFocus_nocallback() const
{
    return ::KDDockWidgets::Views::Group_flutter::hasFocus();
}
void Group_flutter_wrapper::hide()
{
    if (m_hideCallback) {
        const void *thisPtr = this;
        m_hideCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Views::Group_flutter::hide();
    }
}
void Group_flutter_wrapper::hide_nocallback()
{
    ::KDDockWidgets::Views::Group_flutter::hide();
}
bool Group_flutter_wrapper::isActiveWindow() const
{
    if (m_isActiveWindowCallback) {
        const void *thisPtr = this;
        return m_isActiveWindowCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::Group_flutter::isActiveWindow();
    }
}
bool Group_flutter_wrapper::isActiveWindow_nocallback() const
{
    return ::KDDockWidgets::Views::Group_flutter::isActiveWindow();
}
bool Group_flutter_wrapper::isMaximized() const
{
    if (m_isMaximizedCallback) {
        const void *thisPtr = this;
        return m_isMaximizedCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::Group_flutter::isMaximized();
    }
}
bool Group_flutter_wrapper::isMaximized_nocallback() const
{
    return ::KDDockWidgets::Views::Group_flutter::isMaximized();
}
bool Group_flutter_wrapper::isMinimized() const
{
    if (m_isMinimizedCallback) {
        const void *thisPtr = this;
        return m_isMinimizedCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::Group_flutter::isMinimized();
    }
}
bool Group_flutter_wrapper::isMinimized_nocallback() const
{
    return ::KDDockWidgets::Views::Group_flutter::isMinimized();
}
bool Group_flutter_wrapper::isNull() const
{
    if (m_isNullCallback) {
        const void *thisPtr = this;
        return m_isNullCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::Group_flutter::isNull();
    }
}
bool Group_flutter_wrapper::isNull_nocallback() const
{
    return ::KDDockWidgets::Views::Group_flutter::isNull();
}
bool Group_flutter_wrapper::isRootView() const
{
    if (m_isRootViewCallback) {
        const void *thisPtr = this;
        return m_isRootViewCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::Group_flutter::isRootView();
    }
}
bool Group_flutter_wrapper::isRootView_nocallback() const
{
    return ::KDDockWidgets::Views::Group_flutter::isRootView();
}
bool Group_flutter_wrapper::isVisible() const
{
    if (m_isVisibleCallback) {
        const void *thisPtr = this;
        return m_isVisibleCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::Group_flutter::isVisible();
    }
}
bool Group_flutter_wrapper::isVisible_nocallback() const
{
    return ::KDDockWidgets::Views::Group_flutter::isVisible();
}
QPoint Group_flutter_wrapper::mapFromGlobal(QPoint globalPt) const
{
    if (m_mapFromGlobalCallback) {
        const void *thisPtr = this;
        return *m_mapFromGlobalCallback(const_cast<void *>(thisPtr), &globalPt);
    } else {
        return ::KDDockWidgets::Views::Group_flutter::mapFromGlobal(globalPt);
    }
}
QPoint Group_flutter_wrapper::mapFromGlobal_nocallback(QPoint globalPt) const
{
    return ::KDDockWidgets::Views::Group_flutter::mapFromGlobal(globalPt);
}
QPoint Group_flutter_wrapper::mapTo(KDDockWidgets::View *parent, QPoint pos) const
{
    if (m_mapToCallback) {
        const void *thisPtr = this;
        return *m_mapToCallback(const_cast<void *>(thisPtr), parent, &pos);
    } else {
        return ::KDDockWidgets::Views::Group_flutter::mapTo(parent, pos);
    }
}
QPoint Group_flutter_wrapper::mapTo_nocallback(KDDockWidgets::View *parent, QPoint pos) const
{
    return ::KDDockWidgets::Views::Group_flutter::mapTo(parent, pos);
}
QPoint Group_flutter_wrapper::mapToGlobal(QPoint localPt) const
{
    if (m_mapToGlobalCallback) {
        const void *thisPtr = this;
        return *m_mapToGlobalCallback(const_cast<void *>(thisPtr), &localPt);
    } else {
        return ::KDDockWidgets::Views::Group_flutter::mapToGlobal(localPt);
    }
}
QPoint Group_flutter_wrapper::mapToGlobal_nocallback(QPoint localPt) const
{
    return ::KDDockWidgets::Views::Group_flutter::mapToGlobal(localPt);
}
QSize Group_flutter_wrapper::maxSizeHint() const
{
    if (m_maxSizeHintCallback) {
        const void *thisPtr = this;
        return *m_maxSizeHintCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::Group_flutter::maxSizeHint();
    }
}
QSize Group_flutter_wrapper::maxSizeHint_nocallback() const
{
    return ::KDDockWidgets::Views::Group_flutter::maxSizeHint();
}
QSize Group_flutter_wrapper::minSize() const
{
    if (m_minSizeCallback) {
        const void *thisPtr = this;
        return *m_minSizeCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::Group_flutter::minSize();
    }
}
QSize Group_flutter_wrapper::minSize_nocallback() const
{
    return ::KDDockWidgets::Views::Group_flutter::minSize();
}
int Group_flutter_wrapper::minimumHeight() const
{
    if (m_minimumHeightCallback) {
        const void *thisPtr = this;
        return m_minimumHeightCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::Group_flutter::minimumHeight();
    }
}
int Group_flutter_wrapper::minimumHeight_nocallback() const
{
    return ::KDDockWidgets::Views::Group_flutter::minimumHeight();
}
int Group_flutter_wrapper::minimumWidth() const
{
    if (m_minimumWidthCallback) {
        const void *thisPtr = this;
        return m_minimumWidthCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::Group_flutter::minimumWidth();
    }
}
int Group_flutter_wrapper::minimumWidth_nocallback() const
{
    return ::KDDockWidgets::Views::Group_flutter::minimumWidth();
}
void Group_flutter_wrapper::move(int x, int y)
{
    if (m_move_2Callback) {
        const void *thisPtr = this;
        m_move_2Callback(const_cast<void *>(thisPtr), x, y);
    } else {
        ::KDDockWidgets::Views::Group_flutter::move(x, y);
    }
}
void Group_flutter_wrapper::move_nocallback(int x, int y)
{
    ::KDDockWidgets::Views::Group_flutter::move(x, y);
}
int Group_flutter_wrapper::nonContentsHeight() const
{
    if (m_nonContentsHeightCallback) {
        const void *thisPtr = this;
        return m_nonContentsHeightCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::Group_flutter::nonContentsHeight();
    }
}
int Group_flutter_wrapper::nonContentsHeight_nocallback() const
{
    return ::KDDockWidgets::Views::Group_flutter::nonContentsHeight();
}
QRect Group_flutter_wrapper::normalGeometry() const
{
    if (m_normalGeometryCallback) {
        const void *thisPtr = this;
        return *m_normalGeometryCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::Group_flutter::normalGeometry();
    }
}
QRect Group_flutter_wrapper::normalGeometry_nocallback() const
{
    return ::KDDockWidgets::Views::Group_flutter::normalGeometry();
}
QString Group_flutter_wrapper::objectName() const
{
    if (m_objectNameCallback) {
        const void *thisPtr = this;
        return *m_objectNameCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::Group_flutter::objectName();
    }
}
QString Group_flutter_wrapper::objectName_nocallback() const
{
    return ::KDDockWidgets::Views::Group_flutter::objectName();
}
void Group_flutter_wrapper::onChildAdded(KDDockWidgets::View *childView)
{
    if (m_onChildAddedCallback) {
        const void *thisPtr = this;
        m_onChildAddedCallback(const_cast<void *>(thisPtr), childView);
    } else {
        ::KDDockWidgets::Views::Group_flutter::onChildAdded(childView);
    }
}
void Group_flutter_wrapper::onChildAdded_nocallback(KDDockWidgets::View *childView)
{
    ::KDDockWidgets::Views::Group_flutter::onChildAdded(childView);
}
void Group_flutter_wrapper::onChildRemoved(KDDockWidgets::View *childView)
{
    if (m_onChildRemovedCallback) {
        const void *thisPtr = this;
        m_onChildRemovedCallback(const_cast<void *>(thisPtr), childView);
    } else {
        ::KDDockWidgets::Views::Group_flutter::onChildRemoved(childView);
    }
}
void Group_flutter_wrapper::onChildRemoved_nocallback(KDDockWidgets::View *childView)
{
    ::KDDockWidgets::Views::Group_flutter::onChildRemoved(childView);
}
bool Group_flutter_wrapper::onResize(int w, int h)
{
    if (m_onResize_2Callback) {
        const void *thisPtr = this;
        return m_onResize_2Callback(const_cast<void *>(thisPtr), w, h);
    } else {
        return ::KDDockWidgets::Views::Group_flutter::onResize(w, h);
    }
}
bool Group_flutter_wrapper::onResize_nocallback(int w, int h)
{
    return ::KDDockWidgets::Views::Group_flutter::onResize(w, h);
}
void Group_flutter_wrapper::raise()
{
    if (m_raiseCallback) {
        const void *thisPtr = this;
        m_raiseCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Views::Group_flutter::raise();
    }
}
void Group_flutter_wrapper::raise_nocallback()
{
    ::KDDockWidgets::Views::Group_flutter::raise();
}
void Group_flutter_wrapper::raiseAndActivate()
{
    if (m_raiseAndActivateCallback) {
        const void *thisPtr = this;
        m_raiseAndActivateCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Views::Group_flutter::raiseAndActivate();
    }
}
void Group_flutter_wrapper::raiseAndActivate_nocallback()
{
    ::KDDockWidgets::Views::Group_flutter::raiseAndActivate();
}
void Group_flutter_wrapper::releaseKeyboard()
{
    if (m_releaseKeyboardCallback) {
        const void *thisPtr = this;
        m_releaseKeyboardCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Views::Group_flutter::releaseKeyboard();
    }
}
void Group_flutter_wrapper::releaseKeyboard_nocallback()
{
    ::KDDockWidgets::Views::Group_flutter::releaseKeyboard();
}
void Group_flutter_wrapper::releaseMouse()
{
    if (m_releaseMouseCallback) {
        const void *thisPtr = this;
        m_releaseMouseCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Views::Group_flutter::releaseMouse();
    }
}
void Group_flutter_wrapper::releaseMouse_nocallback()
{
    ::KDDockWidgets::Views::Group_flutter::releaseMouse();
}
void Group_flutter_wrapper::setCursor(Qt::CursorShape shape)
{
    if (m_setCursorCallback) {
        const void *thisPtr = this;
        m_setCursorCallback(const_cast<void *>(thisPtr), shape);
    } else {
        ::KDDockWidgets::Views::Group_flutter::setCursor(shape);
    }
}
void Group_flutter_wrapper::setCursor_nocallback(Qt::CursorShape shape)
{
    ::KDDockWidgets::Views::Group_flutter::setCursor(shape);
}
void Group_flutter_wrapper::setFixedHeight(int h)
{
    if (m_setFixedHeightCallback) {
        const void *thisPtr = this;
        m_setFixedHeightCallback(const_cast<void *>(thisPtr), h);
    } else {
        ::KDDockWidgets::Views::Group_flutter::setFixedHeight(h);
    }
}
void Group_flutter_wrapper::setFixedHeight_nocallback(int h)
{
    ::KDDockWidgets::Views::Group_flutter::setFixedHeight(h);
}
void Group_flutter_wrapper::setFixedWidth(int w)
{
    if (m_setFixedWidthCallback) {
        const void *thisPtr = this;
        m_setFixedWidthCallback(const_cast<void *>(thisPtr), w);
    } else {
        ::KDDockWidgets::Views::Group_flutter::setFixedWidth(w);
    }
}
void Group_flutter_wrapper::setFixedWidth_nocallback(int w)
{
    ::KDDockWidgets::Views::Group_flutter::setFixedWidth(w);
}
void Group_flutter_wrapper::setGeometry(QRect geometry)
{
    if (m_setGeometryCallback) {
        const void *thisPtr = this;
        m_setGeometryCallback(const_cast<void *>(thisPtr), &geometry);
    } else {
        ::KDDockWidgets::Views::Group_flutter::setGeometry(geometry);
    }
}
void Group_flutter_wrapper::setGeometry_nocallback(QRect geometry)
{
    ::KDDockWidgets::Views::Group_flutter::setGeometry(geometry);
}
void Group_flutter_wrapper::setHeight(int h)
{
    if (m_setHeightCallback) {
        const void *thisPtr = this;
        m_setHeightCallback(const_cast<void *>(thisPtr), h);
    } else {
        ::KDDockWidgets::Views::Group_flutter::setHeight(h);
    }
}
void Group_flutter_wrapper::setHeight_nocallback(int h)
{
    ::KDDockWidgets::Views::Group_flutter::setHeight(h);
}
void Group_flutter_wrapper::setMaximumSize(QSize sz)
{
    if (m_setMaximumSizeCallback) {
        const void *thisPtr = this;
        m_setMaximumSizeCallback(const_cast<void *>(thisPtr), &sz);
    } else {
        ::KDDockWidgets::Views::Group_flutter::setMaximumSize(sz);
    }
}
void Group_flutter_wrapper::setMaximumSize_nocallback(QSize sz)
{
    ::KDDockWidgets::Views::Group_flutter::setMaximumSize(sz);
}
void Group_flutter_wrapper::setMinimumSize(QSize sz)
{
    if (m_setMinimumSizeCallback) {
        const void *thisPtr = this;
        m_setMinimumSizeCallback(const_cast<void *>(thisPtr), &sz);
    } else {
        ::KDDockWidgets::Views::Group_flutter::setMinimumSize(sz);
    }
}
void Group_flutter_wrapper::setMinimumSize_nocallback(QSize sz)
{
    ::KDDockWidgets::Views::Group_flutter::setMinimumSize(sz);
}
void Group_flutter_wrapper::setMouseTracking(bool enable)
{
    if (m_setMouseTrackingCallback) {
        const void *thisPtr = this;
        m_setMouseTrackingCallback(const_cast<void *>(thisPtr), enable);
    } else {
        ::KDDockWidgets::Views::Group_flutter::setMouseTracking(enable);
    }
}
void Group_flutter_wrapper::setMouseTracking_nocallback(bool enable)
{
    ::KDDockWidgets::Views::Group_flutter::setMouseTracking(enable);
}
void Group_flutter_wrapper::setObjectName(const QString &name)
{
    if (m_setObjectNameCallback) {
        const void *thisPtr = this;
        m_setObjectNameCallback(const_cast<void *>(thisPtr), name);
    } else {
        ::KDDockWidgets::Views::Group_flutter::setObjectName(name);
    }
}
void Group_flutter_wrapper::setObjectName_nocallback(const QString &name)
{
    ::KDDockWidgets::Views::Group_flutter::setObjectName(name);
}
void Group_flutter_wrapper::setParent(KDDockWidgets::View *parent)
{
    if (m_setParentCallback) {
        const void *thisPtr = this;
        m_setParentCallback(const_cast<void *>(thisPtr), parent);
    } else {
        ::KDDockWidgets::Views::Group_flutter::setParent(parent);
    }
}
void Group_flutter_wrapper::setParent_nocallback(KDDockWidgets::View *parent)
{
    ::KDDockWidgets::Views::Group_flutter::setParent(parent);
}
void Group_flutter_wrapper::setSize(int w, int h)
{
    if (m_setSize_2Callback) {
        const void *thisPtr = this;
        m_setSize_2Callback(const_cast<void *>(thisPtr), w, h);
    } else {
        ::KDDockWidgets::Views::Group_flutter::setSize(w, h);
    }
}
void Group_flutter_wrapper::setSize_nocallback(int w, int h)
{
    ::KDDockWidgets::Views::Group_flutter::setSize(w, h);
}
void Group_flutter_wrapper::setVisible(bool visible)
{
    if (m_setVisibleCallback) {
        const void *thisPtr = this;
        m_setVisibleCallback(const_cast<void *>(thisPtr), visible);
    } else {
        ::KDDockWidgets::Views::Group_flutter::setVisible(visible);
    }
}
void Group_flutter_wrapper::setVisible_nocallback(bool visible)
{
    ::KDDockWidgets::Views::Group_flutter::setVisible(visible);
}
void Group_flutter_wrapper::setWidth(int w)
{
    if (m_setWidthCallback) {
        const void *thisPtr = this;
        m_setWidthCallback(const_cast<void *>(thisPtr), w);
    } else {
        ::KDDockWidgets::Views::Group_flutter::setWidth(w);
    }
}
void Group_flutter_wrapper::setWidth_nocallback(int w)
{
    ::KDDockWidgets::Views::Group_flutter::setWidth(w);
}
void Group_flutter_wrapper::setWindowOpacity(double v)
{
    if (m_setWindowOpacityCallback) {
        const void *thisPtr = this;
        m_setWindowOpacityCallback(const_cast<void *>(thisPtr), v);
    } else {
        ::KDDockWidgets::Views::Group_flutter::setWindowOpacity(v);
    }
}
void Group_flutter_wrapper::setWindowOpacity_nocallback(double v)
{
    ::KDDockWidgets::Views::Group_flutter::setWindowOpacity(v);
}
void Group_flutter_wrapper::setWindowTitle(const QString &title)
{
    if (m_setWindowTitleCallback) {
        const void *thisPtr = this;
        m_setWindowTitleCallback(const_cast<void *>(thisPtr), title);
    } else {
        ::KDDockWidgets::Views::Group_flutter::setWindowTitle(title);
    }
}
void Group_flutter_wrapper::setWindowTitle_nocallback(const QString &title)
{
    ::KDDockWidgets::Views::Group_flutter::setWindowTitle(title);
}
void Group_flutter_wrapper::setZOrder(int z)
{
    if (m_setZOrderCallback) {
        const void *thisPtr = this;
        m_setZOrderCallback(const_cast<void *>(thisPtr), z);
    } else {
        ::KDDockWidgets::Views::Group_flutter::setZOrder(z);
    }
}
void Group_flutter_wrapper::setZOrder_nocallback(int z)
{
    ::KDDockWidgets::Views::Group_flutter::setZOrder(z);
}
void Group_flutter_wrapper::show()
{
    if (m_showCallback) {
        const void *thisPtr = this;
        m_showCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Views::Group_flutter::show();
    }
}
void Group_flutter_wrapper::show_nocallback()
{
    ::KDDockWidgets::Views::Group_flutter::show();
}
void Group_flutter_wrapper::showMaximized()
{
    if (m_showMaximizedCallback) {
        const void *thisPtr = this;
        m_showMaximizedCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Views::Group_flutter::showMaximized();
    }
}
void Group_flutter_wrapper::showMaximized_nocallback()
{
    ::KDDockWidgets::Views::Group_flutter::showMaximized();
}
void Group_flutter_wrapper::showMinimized()
{
    if (m_showMinimizedCallback) {
        const void *thisPtr = this;
        m_showMinimizedCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Views::Group_flutter::showMinimized();
    }
}
void Group_flutter_wrapper::showMinimized_nocallback()
{
    ::KDDockWidgets::Views::Group_flutter::showMinimized();
}
void Group_flutter_wrapper::showNormal()
{
    if (m_showNormalCallback) {
        const void *thisPtr = this;
        m_showNormalCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Views::Group_flutter::showNormal();
    }
}
void Group_flutter_wrapper::showNormal_nocallback()
{
    ::KDDockWidgets::Views::Group_flutter::showNormal();
}
QSize Group_flutter_wrapper::sizeHint() const
{
    if (m_sizeHintCallback) {
        const void *thisPtr = this;
        return *m_sizeHintCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::Views::Group_flutter::sizeHint();
    }
}
QSize Group_flutter_wrapper::sizeHint_nocallback() const
{
    return ::KDDockWidgets::Views::Group_flutter::sizeHint();
}
void Group_flutter_wrapper::update()
{
    if (m_updateCallback) {
        const void *thisPtr = this;
        m_updateCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Views::Group_flutter::update();
    }
}
void Group_flutter_wrapper::update_nocallback()
{
    ::KDDockWidgets::Views::Group_flutter::update();
}
Group_flutter_wrapper::~Group_flutter_wrapper()
{
}

}
static KDDockWidgets::Views::Group_flutter *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::Views::Group_flutter *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__Views__Group_flutter_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(cppObj);
}
void *c_KDDockWidgets__Views__Group_flutter__constructor_Group_View(void *controller_,
                                                                    void *parent_)
{
    auto controller = reinterpret_cast<KDDockWidgets::Controllers::Group *>(controller_);
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    auto ptr = new KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper(controller, parent);
    return reinterpret_cast<void *>(ptr);
}
// activateWindow()
void c_KDDockWidgets__Views__Group_flutter__activateWindow(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->activateWindow_nocallback();
        } else {
            return targetPtr->activateWindow();
        }
    }();
}
// close()
bool c_KDDockWidgets__Views__Group_flutter__close(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->close_nocallback();
        } else {
            return targetPtr->close();
        }
    }();
}
// createPlatformWindow()
void c_KDDockWidgets__Views__Group_flutter__createPlatformWindow(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->createPlatformWindow_nocallback();
        } else {
            return targetPtr->createPlatformWindow();
        }
    }();
}
// currentIndex() const
int c_KDDockWidgets__Views__Group_flutter__currentIndex(void *thisObj)
{
    return fromPtr(thisObj)->currentIndex();
}
// dragRect() const
void *c_KDDockWidgets__Views__Group_flutter__dragRect(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QRect> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->dragRect_nocallback();
        } else {
            return targetPtr->dragRect();
        }
    }() };
}
// flags() const
int c_KDDockWidgets__Views__Group_flutter__flags(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->flags_nocallback();
        } else {
            return targetPtr->flags();
        }
    }();
}
// free_impl()
void c_KDDockWidgets__Views__Group_flutter__free_impl(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->free_impl_nocallback();
        } else {
            return targetPtr->free_impl();
        }
    }();
}
// geometry() const
void *c_KDDockWidgets__Views__Group_flutter__geometry(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QRect> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->geometry_nocallback();
        } else {
            return targetPtr->geometry();
        }
    }() };
}
// grabMouse()
void c_KDDockWidgets__Views__Group_flutter__grabMouse(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->grabMouse_nocallback();
        } else {
            return targetPtr->grabMouse();
        }
    }();
}
// hasFocus() const
bool c_KDDockWidgets__Views__Group_flutter__hasFocus(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->hasFocus_nocallback();
        } else {
            return targetPtr->hasFocus();
        }
    }();
}
// hide()
void c_KDDockWidgets__Views__Group_flutter__hide(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->hide_nocallback();
        } else {
            return targetPtr->hide();
        }
    }();
}
// isActiveWindow() const
bool c_KDDockWidgets__Views__Group_flutter__isActiveWindow(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->isActiveWindow_nocallback();
        } else {
            return targetPtr->isActiveWindow();
        }
    }();
}
// isMaximized() const
bool c_KDDockWidgets__Views__Group_flutter__isMaximized(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->isMaximized_nocallback();
        } else {
            return targetPtr->isMaximized();
        }
    }();
}
// isMinimized() const
bool c_KDDockWidgets__Views__Group_flutter__isMinimized(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->isMinimized_nocallback();
        } else {
            return targetPtr->isMinimized();
        }
    }();
}
// isNull() const
bool c_KDDockWidgets__Views__Group_flutter__isNull(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->isNull_nocallback();
        } else {
            return targetPtr->isNull();
        }
    }();
}
// isRootView() const
bool c_KDDockWidgets__Views__Group_flutter__isRootView(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->isRootView_nocallback();
        } else {
            return targetPtr->isRootView();
        }
    }();
}
// isVisible() const
bool c_KDDockWidgets__Views__Group_flutter__isVisible(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->isVisible_nocallback();
        } else {
            return targetPtr->isVisible();
        }
    }();
}
// mapFromGlobal(QPoint globalPt) const
void *c_KDDockWidgets__Views__Group_flutter__mapFromGlobal_QPoint(void *thisObj, void *globalPt_)
{
    assert(globalPt_);
    auto &globalPt = *reinterpret_cast<QPoint *>(globalPt_);
    return new Dartagnan::ValueWrapper<QPoint> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->mapFromGlobal_nocallback(globalPt);
        } else {
            return targetPtr->mapFromGlobal(globalPt);
        }
    }() };
}
// mapTo(KDDockWidgets::View * parent, QPoint pos) const
void *c_KDDockWidgets__Views__Group_flutter__mapTo_View_QPoint(void *thisObj, void *parent_,
                                                               void *pos_)
{
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    assert(pos_);
    auto &pos = *reinterpret_cast<QPoint *>(pos_);
    return new Dartagnan::ValueWrapper<QPoint> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->mapTo_nocallback(parent, pos);
        } else {
            return targetPtr->mapTo(parent, pos);
        }
    }() };
}
// mapToGlobal(QPoint localPt) const
void *c_KDDockWidgets__Views__Group_flutter__mapToGlobal_QPoint(void *thisObj, void *localPt_)
{
    assert(localPt_);
    auto &localPt = *reinterpret_cast<QPoint *>(localPt_);
    return new Dartagnan::ValueWrapper<QPoint> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->mapToGlobal_nocallback(localPt);
        } else {
            return targetPtr->mapToGlobal(localPt);
        }
    }() };
}
// maxSizeHint() const
void *c_KDDockWidgets__Views__Group_flutter__maxSizeHint(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->maxSizeHint_nocallback();
        } else {
            return targetPtr->maxSizeHint();
        }
    }() };
}
// minSize() const
void *c_KDDockWidgets__Views__Group_flutter__minSize(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->minSize_nocallback();
        } else {
            return targetPtr->minSize();
        }
    }() };
}
// minimumHeight() const
int c_KDDockWidgets__Views__Group_flutter__minimumHeight(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->minimumHeight_nocallback();
        } else {
            return targetPtr->minimumHeight();
        }
    }();
}
// minimumWidth() const
int c_KDDockWidgets__Views__Group_flutter__minimumWidth(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->minimumWidth_nocallback();
        } else {
            return targetPtr->minimumWidth();
        }
    }();
}
// move(int x, int y)
void c_KDDockWidgets__Views__Group_flutter__move_int_int(void *thisObj, int x, int y)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->move_nocallback(x, y);
        } else {
            return targetPtr->move(x, y);
        }
    }();
}
// nonContentsHeight() const
int c_KDDockWidgets__Views__Group_flutter__nonContentsHeight(void *thisObj)
{
    return fromWrapperPtr(thisObj)->nonContentsHeight_nocallback();
}
// normalGeometry() const
void *c_KDDockWidgets__Views__Group_flutter__normalGeometry(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QRect> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->normalGeometry_nocallback();
        } else {
            return targetPtr->normalGeometry();
        }
    }() };
}
// objectName() const
void *c_KDDockWidgets__Views__Group_flutter__objectName(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QString> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->objectName_nocallback();
        } else {
            return targetPtr->objectName();
        }
    }() };
}
// onChildAdded(KDDockWidgets::View * childView)
void c_KDDockWidgets__Views__Group_flutter__onChildAdded_View(void *thisObj, void *childView_)
{
    auto childView = reinterpret_cast<KDDockWidgets::View *>(childView_);
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->onChildAdded_nocallback(childView);
        } else {
            return targetPtr->onChildAdded(childView);
        }
    }();
}
// onChildRemoved(KDDockWidgets::View * childView)
void c_KDDockWidgets__Views__Group_flutter__onChildRemoved_View(void *thisObj, void *childView_)
{
    auto childView = reinterpret_cast<KDDockWidgets::View *>(childView_);
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->onChildRemoved_nocallback(childView);
        } else {
            return targetPtr->onChildRemoved(childView);
        }
    }();
}
// onResize(int w, int h)
bool c_KDDockWidgets__Views__Group_flutter__onResize_int_int(void *thisObj, int w, int h)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->onResize_nocallback(w, h);
        } else {
            return targetPtr->onResize(w, h);
        }
    }();
}
// raise()
void c_KDDockWidgets__Views__Group_flutter__raise(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->raise_nocallback();
        } else {
            return targetPtr->raise();
        }
    }();
}
// raiseAndActivate()
void c_KDDockWidgets__Views__Group_flutter__raiseAndActivate(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->raiseAndActivate_nocallback();
        } else {
            return targetPtr->raiseAndActivate();
        }
    }();
}
// releaseKeyboard()
void c_KDDockWidgets__Views__Group_flutter__releaseKeyboard(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->releaseKeyboard_nocallback();
        } else {
            return targetPtr->releaseKeyboard();
        }
    }();
}
// releaseMouse()
void c_KDDockWidgets__Views__Group_flutter__releaseMouse(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->releaseMouse_nocallback();
        } else {
            return targetPtr->releaseMouse();
        }
    }();
}
// setCursor(Qt::CursorShape shape)
void c_KDDockWidgets__Views__Group_flutter__setCursor_CursorShape(void *thisObj, int shape)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setCursor_nocallback(static_cast<Qt::CursorShape>(shape));
        } else {
            return targetPtr->setCursor(static_cast<Qt::CursorShape>(shape));
        }
    }();
}
// setFixedHeight(int h)
void c_KDDockWidgets__Views__Group_flutter__setFixedHeight_int(void *thisObj, int h)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setFixedHeight_nocallback(h);
        } else {
            return targetPtr->setFixedHeight(h);
        }
    }();
}
// setFixedWidth(int w)
void c_KDDockWidgets__Views__Group_flutter__setFixedWidth_int(void *thisObj, int w)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setFixedWidth_nocallback(w);
        } else {
            return targetPtr->setFixedWidth(w);
        }
    }();
}
// setGeometry(QRect geometry)
void c_KDDockWidgets__Views__Group_flutter__setGeometry_QRect(void *thisObj, void *geometry_)
{
    assert(geometry_);
    auto &geometry = *reinterpret_cast<QRect *>(geometry_);
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setGeometry_nocallback(geometry);
        } else {
            return targetPtr->setGeometry(geometry);
        }
    }();
}
// setHeight(int h)
void c_KDDockWidgets__Views__Group_flutter__setHeight_int(void *thisObj, int h)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setHeight_nocallback(h);
        } else {
            return targetPtr->setHeight(h);
        }
    }();
}
// setMaximumSize(QSize sz)
void c_KDDockWidgets__Views__Group_flutter__setMaximumSize_QSize(void *thisObj, void *sz_)
{
    assert(sz_);
    auto &sz = *reinterpret_cast<QSize *>(sz_);
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setMaximumSize_nocallback(sz);
        } else {
            return targetPtr->setMaximumSize(sz);
        }
    }();
}
// setMinimumSize(QSize sz)
void c_KDDockWidgets__Views__Group_flutter__setMinimumSize_QSize(void *thisObj, void *sz_)
{
    assert(sz_);
    auto &sz = *reinterpret_cast<QSize *>(sz_);
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setMinimumSize_nocallback(sz);
        } else {
            return targetPtr->setMinimumSize(sz);
        }
    }();
}
// setMouseTracking(bool enable)
void c_KDDockWidgets__Views__Group_flutter__setMouseTracking_bool(void *thisObj, bool enable)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setMouseTracking_nocallback(enable);
        } else {
            return targetPtr->setMouseTracking(enable);
        }
    }();
}
// setObjectName(const QString & name)
void c_KDDockWidgets__Views__Group_flutter__setObjectName_QString(void *thisObj, const char *name_)
{
    const auto name = QString::fromUtf8(name_);
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setObjectName_nocallback(name);
        } else {
            return targetPtr->setObjectName(name);
        }
    }();
}
// setParent(KDDockWidgets::View * parent)
void c_KDDockWidgets__Views__Group_flutter__setParent_View(void *thisObj, void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setParent_nocallback(parent);
        } else {
            return targetPtr->setParent(parent);
        }
    }();
}
// setSize(int w, int h)
void c_KDDockWidgets__Views__Group_flutter__setSize_int_int(void *thisObj, int w, int h)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setSize_nocallback(w, h);
        } else {
            return targetPtr->setSize(w, h);
        }
    }();
}
// setVisible(bool visible)
void c_KDDockWidgets__Views__Group_flutter__setVisible_bool(void *thisObj, bool visible)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setVisible_nocallback(visible);
        } else {
            return targetPtr->setVisible(visible);
        }
    }();
}
// setWidth(int w)
void c_KDDockWidgets__Views__Group_flutter__setWidth_int(void *thisObj, int w)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setWidth_nocallback(w);
        } else {
            return targetPtr->setWidth(w);
        }
    }();
}
// setWindowOpacity(double v)
void c_KDDockWidgets__Views__Group_flutter__setWindowOpacity_double(void *thisObj, double v)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setWindowOpacity_nocallback(v);
        } else {
            return targetPtr->setWindowOpacity(v);
        }
    }();
}
// setWindowTitle(const QString & title)
void c_KDDockWidgets__Views__Group_flutter__setWindowTitle_QString(void *thisObj,
                                                                   const char *title_)
{
    const auto title = QString::fromUtf8(title_);
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setWindowTitle_nocallback(title);
        } else {
            return targetPtr->setWindowTitle(title);
        }
    }();
}
// setZOrder(int z)
void c_KDDockWidgets__Views__Group_flutter__setZOrder_int(void *thisObj, int z)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setZOrder_nocallback(z);
        } else {
            return targetPtr->setZOrder(z);
        }
    }();
}
// show()
void c_KDDockWidgets__Views__Group_flutter__show(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->show_nocallback();
        } else {
            return targetPtr->show();
        }
    }();
}
// showMaximized()
void c_KDDockWidgets__Views__Group_flutter__showMaximized(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->showMaximized_nocallback();
        } else {
            return targetPtr->showMaximized();
        }
    }();
}
// showMinimized()
void c_KDDockWidgets__Views__Group_flutter__showMinimized(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->showMinimized_nocallback();
        } else {
            return targetPtr->showMinimized();
        }
    }();
}
// showNormal()
void c_KDDockWidgets__Views__Group_flutter__showNormal(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->showNormal_nocallback();
        } else {
            return targetPtr->showNormal();
        }
    }();
}
// sizeHint() const
void *c_KDDockWidgets__Views__Group_flutter__sizeHint(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->sizeHint_nocallback();
        } else {
            return targetPtr->sizeHint();
        }
    }() };
}
// update()
void c_KDDockWidgets__Views__Group_flutter__update(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr =
            dynamic_cast<KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->update_nocallback();
        } else {
            return targetPtr->update();
        }
    }();
}
void c_KDDockWidgets__Views__Group_flutter__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__Views__Group_flutter__registerVirtualMethodCallback(void *ptr, void *callback,
                                                                          int methodId)
{
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 905:
        wrapper->m_activateWindowCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_activateWindow>(
            callback);
        break;
    case 916:
        wrapper->m_closeCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_close>(callback);
        break;
    case 919:
        wrapper->m_createPlatformWindowCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_createPlatformWindow>(
            callback);
        break;
    case 1063:
        wrapper->m_dragRectCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_dragRect>(callback);
        break;
    case 924:
        wrapper->m_flagsCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_flags>(callback);
        break;
    case 926:
        wrapper->m_free_implCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_free_impl>(callback);
        break;
    case 928:
        wrapper->m_geometryCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_geometry>(callback);
        break;
    case 930:
        wrapper->m_grabMouseCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_grabMouse>(callback);
        break;
    case 933:
        wrapper->m_hasFocusCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_hasFocus>(callback);
        break;
    case 935:
        wrapper->m_hideCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_hide>(callback);
        break;
    case 940:
        wrapper->m_isActiveWindowCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_isActiveWindow>(
            callback);
        break;
    case 941:
        wrapper->m_isMaximizedCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_isMaximized>(
            callback);
        break;
    case 942:
        wrapper->m_isMinimizedCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_isMinimized>(
            callback);
        break;
    case 943:
        wrapper->m_isNullCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_isNull>(callback);
        break;
    case 944:
        wrapper->m_isRootViewCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_isRootView>(callback);
        break;
    case 945:
        wrapper->m_isVisibleCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_isVisible>(callback);
        break;
    case 946:
        wrapper->m_mapFromGlobalCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_mapFromGlobal>(
            callback);
        break;
    case 947:
        wrapper->m_mapToCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_mapTo>(callback);
        break;
    case 948:
        wrapper->m_mapToGlobalCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_mapToGlobal>(
            callback);
        break;
    case 949:
        wrapper->m_maxSizeHintCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_maxSizeHint>(
            callback);
        break;
    case 950:
        wrapper->m_minSizeCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_minSize>(callback);
        break;
    case 951:
        wrapper->m_minimumHeightCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_minimumHeight>(
            callback);
        break;
    case 952:
        wrapper->m_minimumWidthCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_minimumWidth>(
            callback);
        break;
    case 954:
        wrapper->m_move_2Callback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_move_2>(callback);
        break;
    case 1064:
        wrapper->m_nonContentsHeightCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_nonContentsHeight>(
            callback);
        break;
    case 955:
        wrapper->m_normalGeometryCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_normalGeometry>(
            callback);
        break;
    case 956:
        wrapper->m_objectNameCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_objectName>(callback);
        break;
    case 1023:
        wrapper->m_onChildAddedCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_onChildAdded>(
            callback);
        break;
    case 1024:
        wrapper->m_onChildRemovedCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_onChildRemoved>(
            callback);
        break;
    case 958:
        wrapper->m_onResize_2Callback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_onResize_2>(callback);
        break;
    case 961:
        wrapper->m_raiseCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_raise>(callback);
        break;
    case 962:
        wrapper->m_raiseAndActivateCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_raiseAndActivate>(
            callback);
        break;
    case 964:
        wrapper->m_releaseKeyboardCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_releaseKeyboard>(
            callback);
        break;
    case 965:
        wrapper->m_releaseMouseCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_releaseMouse>(
            callback);
        break;
    case 969:
        wrapper->m_setCursorCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_setCursor>(callback);
        break;
    case 970:
        wrapper->m_setFixedHeightCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_setFixedHeight>(
            callback);
        break;
    case 971:
        wrapper->m_setFixedWidthCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_setFixedWidth>(
            callback);
        break;
    case 972:
        wrapper->m_setGeometryCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_setGeometry>(
            callback);
        break;
    case 973:
        wrapper->m_setHeightCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_setHeight>(callback);
        break;
    case 974:
        wrapper->m_setMaximumSizeCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_setMaximumSize>(
            callback);
        break;
    case 975:
        wrapper->m_setMinimumSizeCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_setMinimumSize>(
            callback);
        break;
    case 976:
        wrapper->m_setMouseTrackingCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_setMouseTracking>(
            callback);
        break;
    case 977:
        wrapper->m_setObjectNameCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_setObjectName>(
            callback);
        break;
    case 978:
        wrapper->m_setParentCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_setParent>(callback);
        break;
    case 980:
        wrapper->m_setSize_2Callback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_setSize_2>(callback);
        break;
    case 981:
        wrapper->m_setVisibleCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_setVisible>(callback);
        break;
    case 982:
        wrapper->m_setWidthCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_setWidth>(callback);
        break;
    case 983:
        wrapper->m_setWindowOpacityCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_setWindowOpacity>(
            callback);
        break;
    case 984:
        wrapper->m_setWindowTitleCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_setWindowTitle>(
            callback);
        break;
    case 985:
        wrapper->m_setZOrderCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_setZOrder>(callback);
        break;
    case 986:
        wrapper->m_showCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_show>(callback);
        break;
    case 987:
        wrapper->m_showMaximizedCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_showMaximized>(
            callback);
        break;
    case 988:
        wrapper->m_showMinimizedCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_showMinimized>(
            callback);
        break;
    case 989:
        wrapper->m_showNormalCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_showNormal>(callback);
        break;
    case 991:
        wrapper->m_sizeHintCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_sizeHint>(callback);
        break;
    case 993:
        wrapper->m_updateCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Group_flutter_wrapper::Callback_update>(callback);
        break;
    }
}
}

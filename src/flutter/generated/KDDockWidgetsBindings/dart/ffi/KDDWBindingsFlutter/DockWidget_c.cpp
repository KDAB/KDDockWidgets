/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "DockWidget_c.h"


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
DockWidget_wrapper::DockWidget_wrapper(const QString &uniqueName, QFlags<KDDockWidgets::DockWidgetOption> options, QFlags<KDDockWidgets::LayoutSaverOption> layoutSaverOptions)
    : ::KDDockWidgets::flutter::DockWidget(uniqueName, options, layoutSaverOptions)
{
}
void DockWidget_wrapper::activateWindow()
{
    if (m_activateWindowCallback) {
        const void *thisPtr = this;
        m_activateWindowCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::DockWidget::activateWindow();
    }
}
void DockWidget_wrapper::activateWindow_nocallback()
{
    ::KDDockWidgets::flutter::DockWidget::activateWindow();
}
bool DockWidget_wrapper::close()
{
    if (m_closeCallback) {
        const void *thisPtr = this;
        return m_closeCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::DockWidget::close();
    }
}
bool DockWidget_wrapper::close_nocallback()
{
    return ::KDDockWidgets::flutter::DockWidget::close();
}
void DockWidget_wrapper::createPlatformWindow()
{
    if (m_createPlatformWindowCallback) {
        const void *thisPtr = this;
        m_createPlatformWindowCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::DockWidget::createPlatformWindow();
    }
}
void DockWidget_wrapper::createPlatformWindow_nocallback()
{
    ::KDDockWidgets::flutter::DockWidget::createPlatformWindow();
}
KDDockWidgets::Core::DockWidget *DockWidget_wrapper::dockWidget() const
{
    return ::KDDockWidgets::flutter::DockWidget::dockWidget();
}
Qt::WindowFlags DockWidget_wrapper::flags() const
{
    if (m_flagsCallback) {
        const void *thisPtr = this;
        return m_flagsCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::DockWidget::flags();
    }
}
Qt::WindowFlags DockWidget_wrapper::flags_nocallback() const
{
    return ::KDDockWidgets::flutter::DockWidget::flags();
}
void DockWidget_wrapper::free_impl()
{
    if (m_free_implCallback) {
        const void *thisPtr = this;
        m_free_implCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::DockWidget::free_impl();
    }
}
void DockWidget_wrapper::free_impl_nocallback()
{
    ::KDDockWidgets::flutter::DockWidget::free_impl();
}
QRect DockWidget_wrapper::geometry() const
{
    if (m_geometryCallback) {
        const void *thisPtr = this;
        return *m_geometryCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::DockWidget::geometry();
    }
}
QRect DockWidget_wrapper::geometry_nocallback() const
{
    return ::KDDockWidgets::flutter::DockWidget::geometry();
}
void DockWidget_wrapper::grabMouse()
{
    if (m_grabMouseCallback) {
        const void *thisPtr = this;
        m_grabMouseCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::DockWidget::grabMouse();
    }
}
void DockWidget_wrapper::grabMouse_nocallback()
{
    ::KDDockWidgets::flutter::DockWidget::grabMouse();
}
bool DockWidget_wrapper::hasFocus() const
{
    if (m_hasFocusCallback) {
        const void *thisPtr = this;
        return m_hasFocusCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::DockWidget::hasFocus();
    }
}
bool DockWidget_wrapper::hasFocus_nocallback() const
{
    return ::KDDockWidgets::flutter::DockWidget::hasFocus();
}
void DockWidget_wrapper::hide()
{
    if (m_hideCallback) {
        const void *thisPtr = this;
        m_hideCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::DockWidget::hide();
    }
}
void DockWidget_wrapper::hide_nocallback()
{
    ::KDDockWidgets::flutter::DockWidget::hide();
}
void DockWidget_wrapper::init()
{
    if (m_initCallback) {
        const void *thisPtr = this;
        m_initCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::DockWidget::init();
    }
}
void DockWidget_wrapper::init_nocallback()
{
    ::KDDockWidgets::flutter::DockWidget::init();
}
bool DockWidget_wrapper::isActiveWindow() const
{
    if (m_isActiveWindowCallback) {
        const void *thisPtr = this;
        return m_isActiveWindowCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::DockWidget::isActiveWindow();
    }
}
bool DockWidget_wrapper::isActiveWindow_nocallback() const
{
    return ::KDDockWidgets::flutter::DockWidget::isActiveWindow();
}
bool DockWidget_wrapper::isMaximized() const
{
    if (m_isMaximizedCallback) {
        const void *thisPtr = this;
        return m_isMaximizedCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::DockWidget::isMaximized();
    }
}
bool DockWidget_wrapper::isMaximized_nocallback() const
{
    return ::KDDockWidgets::flutter::DockWidget::isMaximized();
}
bool DockWidget_wrapper::isMinimized() const
{
    if (m_isMinimizedCallback) {
        const void *thisPtr = this;
        return m_isMinimizedCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::DockWidget::isMinimized();
    }
}
bool DockWidget_wrapper::isMinimized_nocallback() const
{
    return ::KDDockWidgets::flutter::DockWidget::isMinimized();
}
bool DockWidget_wrapper::isNull() const
{
    if (m_isNullCallback) {
        const void *thisPtr = this;
        return m_isNullCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::DockWidget::isNull();
    }
}
bool DockWidget_wrapper::isNull_nocallback() const
{
    return ::KDDockWidgets::flutter::DockWidget::isNull();
}
bool DockWidget_wrapper::isRootView() const
{
    if (m_isRootViewCallback) {
        const void *thisPtr = this;
        return m_isRootViewCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::DockWidget::isRootView();
    }
}
bool DockWidget_wrapper::isRootView_nocallback() const
{
    return ::KDDockWidgets::flutter::DockWidget::isRootView();
}
bool DockWidget_wrapper::isVisible() const
{
    if (m_isVisibleCallback) {
        const void *thisPtr = this;
        return m_isVisibleCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::DockWidget::isVisible();
    }
}
bool DockWidget_wrapper::isVisible_nocallback() const
{
    return ::KDDockWidgets::flutter::DockWidget::isVisible();
}
QPoint DockWidget_wrapper::mapFromGlobal(QPoint globalPt) const
{
    if (m_mapFromGlobalCallback) {
        const void *thisPtr = this;
        return *m_mapFromGlobalCallback(const_cast<void *>(thisPtr), &globalPt);
    } else {
        return ::KDDockWidgets::flutter::DockWidget::mapFromGlobal(globalPt);
    }
}
QPoint DockWidget_wrapper::mapFromGlobal_nocallback(QPoint globalPt) const
{
    return ::KDDockWidgets::flutter::DockWidget::mapFromGlobal(globalPt);
}
QPoint DockWidget_wrapper::mapTo(KDDockWidgets::Core::View *parent, QPoint pos) const
{
    if (m_mapToCallback) {
        const void *thisPtr = this;
        return *m_mapToCallback(const_cast<void *>(thisPtr), parent, &pos);
    } else {
        return ::KDDockWidgets::flutter::DockWidget::mapTo(parent, pos);
    }
}
QPoint DockWidget_wrapper::mapTo_nocallback(KDDockWidgets::Core::View *parent, QPoint pos) const
{
    return ::KDDockWidgets::flutter::DockWidget::mapTo(parent, pos);
}
QPoint DockWidget_wrapper::mapToGlobal(QPoint localPt) const
{
    if (m_mapToGlobalCallback) {
        const void *thisPtr = this;
        return *m_mapToGlobalCallback(const_cast<void *>(thisPtr), &localPt);
    } else {
        return ::KDDockWidgets::flutter::DockWidget::mapToGlobal(localPt);
    }
}
QPoint DockWidget_wrapper::mapToGlobal_nocallback(QPoint localPt) const
{
    return ::KDDockWidgets::flutter::DockWidget::mapToGlobal(localPt);
}
QSize DockWidget_wrapper::maxSizeHint() const
{
    if (m_maxSizeHintCallback) {
        const void *thisPtr = this;
        return *m_maxSizeHintCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::DockWidget::maxSizeHint();
    }
}
QSize DockWidget_wrapper::maxSizeHint_nocallback() const
{
    return ::KDDockWidgets::flutter::DockWidget::maxSizeHint();
}
QSize DockWidget_wrapper::minSize() const
{
    if (m_minSizeCallback) {
        const void *thisPtr = this;
        return *m_minSizeCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::DockWidget::minSize();
    }
}
QSize DockWidget_wrapper::minSize_nocallback() const
{
    return ::KDDockWidgets::flutter::DockWidget::minSize();
}
int DockWidget_wrapper::minimumHeight() const
{
    if (m_minimumHeightCallback) {
        const void *thisPtr = this;
        return m_minimumHeightCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::DockWidget::minimumHeight();
    }
}
int DockWidget_wrapper::minimumHeight_nocallback() const
{
    return ::KDDockWidgets::flutter::DockWidget::minimumHeight();
}
int DockWidget_wrapper::minimumWidth() const
{
    if (m_minimumWidthCallback) {
        const void *thisPtr = this;
        return m_minimumWidthCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::DockWidget::minimumWidth();
    }
}
int DockWidget_wrapper::minimumWidth_nocallback() const
{
    return ::KDDockWidgets::flutter::DockWidget::minimumWidth();
}
void DockWidget_wrapper::move(int x, int y)
{
    if (m_move_2Callback) {
        const void *thisPtr = this;
        m_move_2Callback(const_cast<void *>(thisPtr), x, y);
    } else {
        ::KDDockWidgets::flutter::DockWidget::move(x, y);
    }
}
void DockWidget_wrapper::move_nocallback(int x, int y)
{
    ::KDDockWidgets::flutter::DockWidget::move(x, y);
}
QRect DockWidget_wrapper::normalGeometry() const
{
    if (m_normalGeometryCallback) {
        const void *thisPtr = this;
        return *m_normalGeometryCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::DockWidget::normalGeometry();
    }
}
QRect DockWidget_wrapper::normalGeometry_nocallback() const
{
    return ::KDDockWidgets::flutter::DockWidget::normalGeometry();
}
QString DockWidget_wrapper::objectName() const
{
    if (m_objectNameCallback) {
        const void *thisPtr = this;
        return *m_objectNameCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::DockWidget::objectName();
    }
}
QString DockWidget_wrapper::objectName_nocallback() const
{
    return ::KDDockWidgets::flutter::DockWidget::objectName();
}
void DockWidget_wrapper::onChildAdded(KDDockWidgets::Core::View *childView)
{
    if (m_onChildAddedCallback) {
        const void *thisPtr = this;
        m_onChildAddedCallback(const_cast<void *>(thisPtr), childView);
    } else {
        ::KDDockWidgets::flutter::DockWidget::onChildAdded(childView);
    }
}
void DockWidget_wrapper::onChildAdded_nocallback(KDDockWidgets::Core::View *childView)
{
    ::KDDockWidgets::flutter::DockWidget::onChildAdded(childView);
}
void DockWidget_wrapper::onChildRemoved(KDDockWidgets::Core::View *childView)
{
    if (m_onChildRemovedCallback) {
        const void *thisPtr = this;
        m_onChildRemovedCallback(const_cast<void *>(thisPtr), childView);
    } else {
        ::KDDockWidgets::flutter::DockWidget::onChildRemoved(childView);
    }
}
void DockWidget_wrapper::onChildRemoved_nocallback(KDDockWidgets::Core::View *childView)
{
    ::KDDockWidgets::flutter::DockWidget::onChildRemoved(childView);
}
bool DockWidget_wrapper::onResize(int w, int h)
{
    if (m_onResize_2Callback) {
        const void *thisPtr = this;
        return m_onResize_2Callback(const_cast<void *>(thisPtr), w, h);
    } else {
        return ::KDDockWidgets::flutter::DockWidget::onResize(w, h);
    }
}
bool DockWidget_wrapper::onResize_nocallback(int w, int h)
{
    return ::KDDockWidgets::flutter::DockWidget::onResize(w, h);
}
void DockWidget_wrapper::raise()
{
    if (m_raiseCallback) {
        const void *thisPtr = this;
        m_raiseCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::DockWidget::raise();
    }
}
void DockWidget_wrapper::raise_nocallback()
{
    ::KDDockWidgets::flutter::DockWidget::raise();
}
void DockWidget_wrapper::raiseAndActivate()
{
    if (m_raiseAndActivateCallback) {
        const void *thisPtr = this;
        m_raiseAndActivateCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::DockWidget::raiseAndActivate();
    }
}
void DockWidget_wrapper::raiseAndActivate_nocallback()
{
    ::KDDockWidgets::flutter::DockWidget::raiseAndActivate();
}
void DockWidget_wrapper::releaseKeyboard()
{
    if (m_releaseKeyboardCallback) {
        const void *thisPtr = this;
        m_releaseKeyboardCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::DockWidget::releaseKeyboard();
    }
}
void DockWidget_wrapper::releaseKeyboard_nocallback()
{
    ::KDDockWidgets::flutter::DockWidget::releaseKeyboard();
}
void DockWidget_wrapper::releaseMouse()
{
    if (m_releaseMouseCallback) {
        const void *thisPtr = this;
        m_releaseMouseCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::DockWidget::releaseMouse();
    }
}
void DockWidget_wrapper::releaseMouse_nocallback()
{
    ::KDDockWidgets::flutter::DockWidget::releaseMouse();
}
void DockWidget_wrapper::setCursor(Qt::CursorShape shape)
{
    if (m_setCursorCallback) {
        const void *thisPtr = this;
        m_setCursorCallback(const_cast<void *>(thisPtr), shape);
    } else {
        ::KDDockWidgets::flutter::DockWidget::setCursor(shape);
    }
}
void DockWidget_wrapper::setCursor_nocallback(Qt::CursorShape shape)
{
    ::KDDockWidgets::flutter::DockWidget::setCursor(shape);
}
void DockWidget_wrapper::setFixedHeight(int h)
{
    if (m_setFixedHeightCallback) {
        const void *thisPtr = this;
        m_setFixedHeightCallback(const_cast<void *>(thisPtr), h);
    } else {
        ::KDDockWidgets::flutter::DockWidget::setFixedHeight(h);
    }
}
void DockWidget_wrapper::setFixedHeight_nocallback(int h)
{
    ::KDDockWidgets::flutter::DockWidget::setFixedHeight(h);
}
void DockWidget_wrapper::setFixedWidth(int w)
{
    if (m_setFixedWidthCallback) {
        const void *thisPtr = this;
        m_setFixedWidthCallback(const_cast<void *>(thisPtr), w);
    } else {
        ::KDDockWidgets::flutter::DockWidget::setFixedWidth(w);
    }
}
void DockWidget_wrapper::setFixedWidth_nocallback(int w)
{
    ::KDDockWidgets::flutter::DockWidget::setFixedWidth(w);
}
void DockWidget_wrapper::setGeometry(QRect geometry)
{
    if (m_setGeometryCallback) {
        const void *thisPtr = this;
        m_setGeometryCallback(const_cast<void *>(thisPtr), &geometry);
    } else {
        ::KDDockWidgets::flutter::DockWidget::setGeometry(geometry);
    }
}
void DockWidget_wrapper::setGeometry_nocallback(QRect geometry)
{
    ::KDDockWidgets::flutter::DockWidget::setGeometry(geometry);
}
void DockWidget_wrapper::setHeight(int h)
{
    if (m_setHeightCallback) {
        const void *thisPtr = this;
        m_setHeightCallback(const_cast<void *>(thisPtr), h);
    } else {
        ::KDDockWidgets::flutter::DockWidget::setHeight(h);
    }
}
void DockWidget_wrapper::setHeight_nocallback(int h)
{
    ::KDDockWidgets::flutter::DockWidget::setHeight(h);
}
void DockWidget_wrapper::setMaximumSize(QSize sz)
{
    if (m_setMaximumSizeCallback) {
        const void *thisPtr = this;
        m_setMaximumSizeCallback(const_cast<void *>(thisPtr), &sz);
    } else {
        ::KDDockWidgets::flutter::DockWidget::setMaximumSize(sz);
    }
}
void DockWidget_wrapper::setMaximumSize_nocallback(QSize sz)
{
    ::KDDockWidgets::flutter::DockWidget::setMaximumSize(sz);
}
void DockWidget_wrapper::setMinimumSize(QSize sz)
{
    if (m_setMinimumSizeCallback) {
        const void *thisPtr = this;
        m_setMinimumSizeCallback(const_cast<void *>(thisPtr), &sz);
    } else {
        ::KDDockWidgets::flutter::DockWidget::setMinimumSize(sz);
    }
}
void DockWidget_wrapper::setMinimumSize_nocallback(QSize sz)
{
    ::KDDockWidgets::flutter::DockWidget::setMinimumSize(sz);
}
void DockWidget_wrapper::setMouseTracking(bool enable)
{
    if (m_setMouseTrackingCallback) {
        const void *thisPtr = this;
        m_setMouseTrackingCallback(const_cast<void *>(thisPtr), enable);
    } else {
        ::KDDockWidgets::flutter::DockWidget::setMouseTracking(enable);
    }
}
void DockWidget_wrapper::setMouseTracking_nocallback(bool enable)
{
    ::KDDockWidgets::flutter::DockWidget::setMouseTracking(enable);
}
void DockWidget_wrapper::setObjectName(const QString &name)
{
    if (m_setObjectNameCallback) {
        const void *thisPtr = this;
        m_setObjectNameCallback(const_cast<void *>(thisPtr), name);
    } else {
        ::KDDockWidgets::flutter::DockWidget::setObjectName(name);
    }
}
void DockWidget_wrapper::setObjectName_nocallback(const QString &name)
{
    ::KDDockWidgets::flutter::DockWidget::setObjectName(name);
}
void DockWidget_wrapper::setParent(KDDockWidgets::Core::View *parent)
{
    if (m_setParentCallback) {
        const void *thisPtr = this;
        m_setParentCallback(const_cast<void *>(thisPtr), parent);
    } else {
        ::KDDockWidgets::flutter::DockWidget::setParent(parent);
    }
}
void DockWidget_wrapper::setParent_nocallback(KDDockWidgets::Core::View *parent)
{
    ::KDDockWidgets::flutter::DockWidget::setParent(parent);
}
void DockWidget_wrapper::setSize(int w, int h)
{
    if (m_setSize_2Callback) {
        const void *thisPtr = this;
        m_setSize_2Callback(const_cast<void *>(thisPtr), w, h);
    } else {
        ::KDDockWidgets::flutter::DockWidget::setSize(w, h);
    }
}
void DockWidget_wrapper::setSize_nocallback(int w, int h)
{
    ::KDDockWidgets::flutter::DockWidget::setSize(w, h);
}
void DockWidget_wrapper::setVisible(bool visible)
{
    if (m_setVisibleCallback) {
        const void *thisPtr = this;
        m_setVisibleCallback(const_cast<void *>(thisPtr), visible);
    } else {
        ::KDDockWidgets::flutter::DockWidget::setVisible(visible);
    }
}
void DockWidget_wrapper::setVisible_nocallback(bool visible)
{
    ::KDDockWidgets::flutter::DockWidget::setVisible(visible);
}
void DockWidget_wrapper::setWidth(int w)
{
    if (m_setWidthCallback) {
        const void *thisPtr = this;
        m_setWidthCallback(const_cast<void *>(thisPtr), w);
    } else {
        ::KDDockWidgets::flutter::DockWidget::setWidth(w);
    }
}
void DockWidget_wrapper::setWidth_nocallback(int w)
{
    ::KDDockWidgets::flutter::DockWidget::setWidth(w);
}
void DockWidget_wrapper::setWindowOpacity(double v)
{
    if (m_setWindowOpacityCallback) {
        const void *thisPtr = this;
        m_setWindowOpacityCallback(const_cast<void *>(thisPtr), v);
    } else {
        ::KDDockWidgets::flutter::DockWidget::setWindowOpacity(v);
    }
}
void DockWidget_wrapper::setWindowOpacity_nocallback(double v)
{
    ::KDDockWidgets::flutter::DockWidget::setWindowOpacity(v);
}
void DockWidget_wrapper::setWindowTitle(const QString &title)
{
    if (m_setWindowTitleCallback) {
        const void *thisPtr = this;
        m_setWindowTitleCallback(const_cast<void *>(thisPtr), title);
    } else {
        ::KDDockWidgets::flutter::DockWidget::setWindowTitle(title);
    }
}
void DockWidget_wrapper::setWindowTitle_nocallback(const QString &title)
{
    ::KDDockWidgets::flutter::DockWidget::setWindowTitle(title);
}
void DockWidget_wrapper::setZOrder(int z)
{
    if (m_setZOrderCallback) {
        const void *thisPtr = this;
        m_setZOrderCallback(const_cast<void *>(thisPtr), z);
    } else {
        ::KDDockWidgets::flutter::DockWidget::setZOrder(z);
    }
}
void DockWidget_wrapper::setZOrder_nocallback(int z)
{
    ::KDDockWidgets::flutter::DockWidget::setZOrder(z);
}
void DockWidget_wrapper::show()
{
    if (m_showCallback) {
        const void *thisPtr = this;
        m_showCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::DockWidget::show();
    }
}
void DockWidget_wrapper::show_nocallback()
{
    ::KDDockWidgets::flutter::DockWidget::show();
}
void DockWidget_wrapper::showMaximized()
{
    if (m_showMaximizedCallback) {
        const void *thisPtr = this;
        m_showMaximizedCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::DockWidget::showMaximized();
    }
}
void DockWidget_wrapper::showMaximized_nocallback()
{
    ::KDDockWidgets::flutter::DockWidget::showMaximized();
}
void DockWidget_wrapper::showMinimized()
{
    if (m_showMinimizedCallback) {
        const void *thisPtr = this;
        m_showMinimizedCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::DockWidget::showMinimized();
    }
}
void DockWidget_wrapper::showMinimized_nocallback()
{
    ::KDDockWidgets::flutter::DockWidget::showMinimized();
}
void DockWidget_wrapper::showNormal()
{
    if (m_showNormalCallback) {
        const void *thisPtr = this;
        m_showNormalCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::DockWidget::showNormal();
    }
}
void DockWidget_wrapper::showNormal_nocallback()
{
    ::KDDockWidgets::flutter::DockWidget::showNormal();
}
QSize DockWidget_wrapper::sizeHint() const
{
    if (m_sizeHintCallback) {
        const void *thisPtr = this;
        return *m_sizeHintCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::DockWidget::sizeHint();
    }
}
QSize DockWidget_wrapper::sizeHint_nocallback() const
{
    return ::KDDockWidgets::flutter::DockWidget::sizeHint();
}
void DockWidget_wrapper::update()
{
    if (m_updateCallback) {
        const void *thisPtr = this;
        m_updateCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::DockWidget::update();
    }
}
void DockWidget_wrapper::update_nocallback()
{
    ::KDDockWidgets::flutter::DockWidget::update();
}
DockWidget_wrapper::~DockWidget_wrapper()
{
}

}
}
static KDDockWidgets::flutter::DockWidget *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::flutter::DockWidget *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__flutter__DockWidget_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper *>(cppObj);
}
void *c_KDDockWidgets__flutter__DockWidget__constructor_QString_DockWidgetOptions_LayoutSaverOptions(const char *uniqueName_, int options_, int layoutSaverOptions_)
{
    const auto uniqueName = QString::fromUtf8(uniqueName_);
    auto options = static_cast<QFlags<KDDockWidgets::DockWidgetOption>>(options_);
    auto layoutSaverOptions = static_cast<QFlags<KDDockWidgets::LayoutSaverOption>>(layoutSaverOptions_);
    auto ptr = new KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper(uniqueName, options, layoutSaverOptions);
    return reinterpret_cast<void *>(ptr);
}
// activateWindow()
void c_KDDockWidgets__flutter__DockWidget__activateWindow(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->activateWindow_nocallback();} else {    return targetPtr->activateWindow();} }();
}
// close()
bool c_KDDockWidgets__flutter__DockWidget__close(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->close_nocallback();} else {    return targetPtr->close();} }();
}
// createPlatformWindow()
void c_KDDockWidgets__flutter__DockWidget__createPlatformWindow(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->createPlatformWindow_nocallback();} else {    return targetPtr->createPlatformWindow();} }();
}
// dockWidget() const
void *c_KDDockWidgets__flutter__DockWidget__dockWidget(void *thisObj)
{
    return fromPtr(thisObj)->dockWidget();
}
// flags() const
int c_KDDockWidgets__flutter__DockWidget__flags(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->flags_nocallback();} else {    return targetPtr->flags();} }();
}
// free_impl()
void c_KDDockWidgets__flutter__DockWidget__free_impl(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->free_impl_nocallback();} else {    return targetPtr->free_impl();} }();
}
// geometry() const
void *c_KDDockWidgets__flutter__DockWidget__geometry(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QRect> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->geometry_nocallback();} else {    return targetPtr->geometry();} }() };
}
// grabMouse()
void c_KDDockWidgets__flutter__DockWidget__grabMouse(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->grabMouse_nocallback();} else {    return targetPtr->grabMouse();} }();
}
// hasFocus() const
bool c_KDDockWidgets__flutter__DockWidget__hasFocus(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->hasFocus_nocallback();} else {    return targetPtr->hasFocus();} }();
}
// hide()
void c_KDDockWidgets__flutter__DockWidget__hide(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->hide_nocallback();} else {    return targetPtr->hide();} }();
}
// init()
void c_KDDockWidgets__flutter__DockWidget__init(void *thisObj)
{
    fromWrapperPtr(thisObj)->init_nocallback();
}
// isActiveWindow() const
bool c_KDDockWidgets__flutter__DockWidget__isActiveWindow(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isActiveWindow_nocallback();} else {    return targetPtr->isActiveWindow();} }();
}
// isMaximized() const
bool c_KDDockWidgets__flutter__DockWidget__isMaximized(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isMaximized_nocallback();} else {    return targetPtr->isMaximized();} }();
}
// isMinimized() const
bool c_KDDockWidgets__flutter__DockWidget__isMinimized(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isMinimized_nocallback();} else {    return targetPtr->isMinimized();} }();
}
// isNull() const
bool c_KDDockWidgets__flutter__DockWidget__isNull(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isNull_nocallback();} else {    return targetPtr->isNull();} }();
}
// isRootView() const
bool c_KDDockWidgets__flutter__DockWidget__isRootView(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isRootView_nocallback();} else {    return targetPtr->isRootView();} }();
}
// isVisible() const
bool c_KDDockWidgets__flutter__DockWidget__isVisible(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isVisible_nocallback();} else {    return targetPtr->isVisible();} }();
}
// mapFromGlobal(QPoint globalPt) const
void *c_KDDockWidgets__flutter__DockWidget__mapFromGlobal_QPoint(void *thisObj, void *globalPt_)
{
    assert(globalPt_);
    auto &globalPt = *reinterpret_cast<QPoint *>(globalPt_);
    return new Dartagnan::ValueWrapper<QPoint> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->mapFromGlobal_nocallback(globalPt);} else {    return targetPtr->mapFromGlobal(globalPt);} }() };
}
// mapTo(KDDockWidgets::Core::View * parent, QPoint pos) const
void *c_KDDockWidgets__flutter__DockWidget__mapTo_View_QPoint(void *thisObj, void *parent_, void *pos_)
{
    auto parent = reinterpret_cast<KDDockWidgets::Core::View *>(parent_);
    assert(pos_);
    auto &pos = *reinterpret_cast<QPoint *>(pos_);
    return new Dartagnan::ValueWrapper<QPoint> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->mapTo_nocallback(parent,pos);} else {    return targetPtr->mapTo(parent,pos);} }() };
}
// mapToGlobal(QPoint localPt) const
void *c_KDDockWidgets__flutter__DockWidget__mapToGlobal_QPoint(void *thisObj, void *localPt_)
{
    assert(localPt_);
    auto &localPt = *reinterpret_cast<QPoint *>(localPt_);
    return new Dartagnan::ValueWrapper<QPoint> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->mapToGlobal_nocallback(localPt);} else {    return targetPtr->mapToGlobal(localPt);} }() };
}
// maxSizeHint() const
void *c_KDDockWidgets__flutter__DockWidget__maxSizeHint(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->maxSizeHint_nocallback();} else {    return targetPtr->maxSizeHint();} }() };
}
// minSize() const
void *c_KDDockWidgets__flutter__DockWidget__minSize(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->minSize_nocallback();} else {    return targetPtr->minSize();} }() };
}
// minimumHeight() const
int c_KDDockWidgets__flutter__DockWidget__minimumHeight(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->minimumHeight_nocallback();} else {    return targetPtr->minimumHeight();} }();
}
// minimumWidth() const
int c_KDDockWidgets__flutter__DockWidget__minimumWidth(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->minimumWidth_nocallback();} else {    return targetPtr->minimumWidth();} }();
}
// move(int x, int y)
void c_KDDockWidgets__flutter__DockWidget__move_int_int(void *thisObj, int x, int y)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->move_nocallback(x,y);} else {    return targetPtr->move(x,y);} }();
}
// normalGeometry() const
void *c_KDDockWidgets__flutter__DockWidget__normalGeometry(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QRect> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->normalGeometry_nocallback();} else {    return targetPtr->normalGeometry();} }() };
}
// objectName() const
void *c_KDDockWidgets__flutter__DockWidget__objectName(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QString> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->objectName_nocallback();} else {    return targetPtr->objectName();} }() };
}
// onChildAdded(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__DockWidget__onChildAdded_View(void *thisObj, void *childView_)
{
    auto childView = reinterpret_cast<KDDockWidgets::Core::View *>(childView_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->onChildAdded_nocallback(childView);} else {    return targetPtr->onChildAdded(childView);} }();
}
// onChildRemoved(KDDockWidgets::Core::View * childView)
void c_KDDockWidgets__flutter__DockWidget__onChildRemoved_View(void *thisObj, void *childView_)
{
    auto childView = reinterpret_cast<KDDockWidgets::Core::View *>(childView_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->onChildRemoved_nocallback(childView);} else {    return targetPtr->onChildRemoved(childView);} }();
}
// onResize(int w, int h)
bool c_KDDockWidgets__flutter__DockWidget__onResize_int_int(void *thisObj, int w, int h)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->onResize_nocallback(w,h);} else {    return targetPtr->onResize(w,h);} }();
}
// raise()
void c_KDDockWidgets__flutter__DockWidget__raise(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->raise_nocallback();} else {    return targetPtr->raise();} }();
}
// raiseAndActivate()
void c_KDDockWidgets__flutter__DockWidget__raiseAndActivate(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->raiseAndActivate_nocallback();} else {    return targetPtr->raiseAndActivate();} }();
}
// releaseKeyboard()
void c_KDDockWidgets__flutter__DockWidget__releaseKeyboard(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->releaseKeyboard_nocallback();} else {    return targetPtr->releaseKeyboard();} }();
}
// releaseMouse()
void c_KDDockWidgets__flutter__DockWidget__releaseMouse(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->releaseMouse_nocallback();} else {    return targetPtr->releaseMouse();} }();
}
// setCursor(Qt::CursorShape shape)
void c_KDDockWidgets__flutter__DockWidget__setCursor_CursorShape(void *thisObj, int shape)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setCursor_nocallback(static_cast<Qt::CursorShape>(shape));} else {    return targetPtr->setCursor(static_cast<Qt::CursorShape>(shape));} }();
}
// setFixedHeight(int h)
void c_KDDockWidgets__flutter__DockWidget__setFixedHeight_int(void *thisObj, int h)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setFixedHeight_nocallback(h);} else {    return targetPtr->setFixedHeight(h);} }();
}
// setFixedWidth(int w)
void c_KDDockWidgets__flutter__DockWidget__setFixedWidth_int(void *thisObj, int w)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setFixedWidth_nocallback(w);} else {    return targetPtr->setFixedWidth(w);} }();
}
// setGeometry(QRect geometry)
void c_KDDockWidgets__flutter__DockWidget__setGeometry_QRect(void *thisObj, void *geometry_)
{
    assert(geometry_);
    auto &geometry = *reinterpret_cast<QRect *>(geometry_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setGeometry_nocallback(geometry);} else {    return targetPtr->setGeometry(geometry);} }();
}
// setHeight(int h)
void c_KDDockWidgets__flutter__DockWidget__setHeight_int(void *thisObj, int h)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setHeight_nocallback(h);} else {    return targetPtr->setHeight(h);} }();
}
// setMaximumSize(QSize sz)
void c_KDDockWidgets__flutter__DockWidget__setMaximumSize_QSize(void *thisObj, void *sz_)
{
    assert(sz_);
    auto &sz = *reinterpret_cast<QSize *>(sz_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setMaximumSize_nocallback(sz);} else {    return targetPtr->setMaximumSize(sz);} }();
}
// setMinimumSize(QSize sz)
void c_KDDockWidgets__flutter__DockWidget__setMinimumSize_QSize(void *thisObj, void *sz_)
{
    assert(sz_);
    auto &sz = *reinterpret_cast<QSize *>(sz_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setMinimumSize_nocallback(sz);} else {    return targetPtr->setMinimumSize(sz);} }();
}
// setMouseTracking(bool enable)
void c_KDDockWidgets__flutter__DockWidget__setMouseTracking_bool(void *thisObj, bool enable)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setMouseTracking_nocallback(enable);} else {    return targetPtr->setMouseTracking(enable);} }();
}
// setObjectName(const QString & name)
void c_KDDockWidgets__flutter__DockWidget__setObjectName_QString(void *thisObj, const char *name_)
{
    const auto name = QString::fromUtf8(name_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setObjectName_nocallback(name);} else {    return targetPtr->setObjectName(name);} }();
}
// setParent(KDDockWidgets::Core::View * parent)
void c_KDDockWidgets__flutter__DockWidget__setParent_View(void *thisObj, void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::Core::View *>(parent_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setParent_nocallback(parent);} else {    return targetPtr->setParent(parent);} }();
}
// setSize(int w, int h)
void c_KDDockWidgets__flutter__DockWidget__setSize_int_int(void *thisObj, int w, int h)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setSize_nocallback(w,h);} else {    return targetPtr->setSize(w,h);} }();
}
// setVisible(bool visible)
void c_KDDockWidgets__flutter__DockWidget__setVisible_bool(void *thisObj, bool visible)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setVisible_nocallback(visible);} else {    return targetPtr->setVisible(visible);} }();
}
// setWidth(int w)
void c_KDDockWidgets__flutter__DockWidget__setWidth_int(void *thisObj, int w)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setWidth_nocallback(w);} else {    return targetPtr->setWidth(w);} }();
}
// setWindowOpacity(double v)
void c_KDDockWidgets__flutter__DockWidget__setWindowOpacity_double(void *thisObj, double v)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setWindowOpacity_nocallback(v);} else {    return targetPtr->setWindowOpacity(v);} }();
}
// setWindowTitle(const QString & title)
void c_KDDockWidgets__flutter__DockWidget__setWindowTitle_QString(void *thisObj, const char *title_)
{
    const auto title = QString::fromUtf8(title_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setWindowTitle_nocallback(title);} else {    return targetPtr->setWindowTitle(title);} }();
}
// setZOrder(int z)
void c_KDDockWidgets__flutter__DockWidget__setZOrder_int(void *thisObj, int z)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setZOrder_nocallback(z);} else {    return targetPtr->setZOrder(z);} }();
}
// show()
void c_KDDockWidgets__flutter__DockWidget__show(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->show_nocallback();} else {    return targetPtr->show();} }();
}
// showMaximized()
void c_KDDockWidgets__flutter__DockWidget__showMaximized(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->showMaximized_nocallback();} else {    return targetPtr->showMaximized();} }();
}
// showMinimized()
void c_KDDockWidgets__flutter__DockWidget__showMinimized(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->showMinimized_nocallback();} else {    return targetPtr->showMinimized();} }();
}
// showNormal()
void c_KDDockWidgets__flutter__DockWidget__showNormal(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->showNormal_nocallback();} else {    return targetPtr->showNormal();} }();
}
// sizeHint() const
void *c_KDDockWidgets__flutter__DockWidget__sizeHint(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->sizeHint_nocallback();} else {    return targetPtr->sizeHint();} }() };
}
// update()
void c_KDDockWidgets__flutter__DockWidget__update(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->update_nocallback();} else {    return targetPtr->update();} }();
}
void c_KDDockWidgets__flutter__DockWidget__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__flutter__DockWidget__registerVirtualMethodCallback(void *ptr, void *callback, int methodId)
{
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 886:
        wrapper->m_activateWindowCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_activateWindow>(callback);
        break;
    case 897:
        wrapper->m_closeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_close>(callback);
        break;
    case 900:
        wrapper->m_createPlatformWindowCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_createPlatformWindow>(callback);
        break;
    case 905:
        wrapper->m_flagsCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_flags>(callback);
        break;
    case 907:
        wrapper->m_free_implCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_free_impl>(callback);
        break;
    case 909:
        wrapper->m_geometryCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_geometry>(callback);
        break;
    case 911:
        wrapper->m_grabMouseCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_grabMouse>(callback);
        break;
    case 914:
        wrapper->m_hasFocusCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_hasFocus>(callback);
        break;
    case 916:
        wrapper->m_hideCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_hide>(callback);
        break;
    case 919:
        wrapper->m_initCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_init>(callback);
        break;
    case 921:
        wrapper->m_isActiveWindowCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_isActiveWindow>(callback);
        break;
    case 922:
        wrapper->m_isMaximizedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_isMaximized>(callback);
        break;
    case 923:
        wrapper->m_isMinimizedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_isMinimized>(callback);
        break;
    case 924:
        wrapper->m_isNullCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_isNull>(callback);
        break;
    case 925:
        wrapper->m_isRootViewCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_isRootView>(callback);
        break;
    case 926:
        wrapper->m_isVisibleCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_isVisible>(callback);
        break;
    case 927:
        wrapper->m_mapFromGlobalCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_mapFromGlobal>(callback);
        break;
    case 928:
        wrapper->m_mapToCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_mapTo>(callback);
        break;
    case 929:
        wrapper->m_mapToGlobalCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_mapToGlobal>(callback);
        break;
    case 930:
        wrapper->m_maxSizeHintCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_maxSizeHint>(callback);
        break;
    case 931:
        wrapper->m_minSizeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_minSize>(callback);
        break;
    case 932:
        wrapper->m_minimumHeightCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_minimumHeight>(callback);
        break;
    case 933:
        wrapper->m_minimumWidthCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_minimumWidth>(callback);
        break;
    case 935:
        wrapper->m_move_2Callback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_move_2>(callback);
        break;
    case 936:
        wrapper->m_normalGeometryCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_normalGeometry>(callback);
        break;
    case 937:
        wrapper->m_objectNameCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_objectName>(callback);
        break;
    case 1004:
        wrapper->m_onChildAddedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_onChildAdded>(callback);
        break;
    case 1005:
        wrapper->m_onChildRemovedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_onChildRemoved>(callback);
        break;
    case 939:
        wrapper->m_onResize_2Callback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_onResize_2>(callback);
        break;
    case 942:
        wrapper->m_raiseCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_raise>(callback);
        break;
    case 943:
        wrapper->m_raiseAndActivateCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_raiseAndActivate>(callback);
        break;
    case 945:
        wrapper->m_releaseKeyboardCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_releaseKeyboard>(callback);
        break;
    case 946:
        wrapper->m_releaseMouseCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_releaseMouse>(callback);
        break;
    case 950:
        wrapper->m_setCursorCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_setCursor>(callback);
        break;
    case 951:
        wrapper->m_setFixedHeightCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_setFixedHeight>(callback);
        break;
    case 952:
        wrapper->m_setFixedWidthCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_setFixedWidth>(callback);
        break;
    case 953:
        wrapper->m_setGeometryCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_setGeometry>(callback);
        break;
    case 954:
        wrapper->m_setHeightCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_setHeight>(callback);
        break;
    case 955:
        wrapper->m_setMaximumSizeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_setMaximumSize>(callback);
        break;
    case 956:
        wrapper->m_setMinimumSizeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_setMinimumSize>(callback);
        break;
    case 957:
        wrapper->m_setMouseTrackingCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_setMouseTracking>(callback);
        break;
    case 958:
        wrapper->m_setObjectNameCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_setObjectName>(callback);
        break;
    case 959:
        wrapper->m_setParentCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_setParent>(callback);
        break;
    case 961:
        wrapper->m_setSize_2Callback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_setSize_2>(callback);
        break;
    case 962:
        wrapper->m_setVisibleCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_setVisible>(callback);
        break;
    case 963:
        wrapper->m_setWidthCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_setWidth>(callback);
        break;
    case 964:
        wrapper->m_setWindowOpacityCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_setWindowOpacity>(callback);
        break;
    case 965:
        wrapper->m_setWindowTitleCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_setWindowTitle>(callback);
        break;
    case 966:
        wrapper->m_setZOrderCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_setZOrder>(callback);
        break;
    case 967:
        wrapper->m_showCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_show>(callback);
        break;
    case 968:
        wrapper->m_showMaximizedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_showMaximized>(callback);
        break;
    case 969:
        wrapper->m_showMinimizedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_showMinimized>(callback);
        break;
    case 970:
        wrapper->m_showNormalCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_showNormal>(callback);
        break;
    case 972:
        wrapper->m_sizeHintCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_sizeHint>(callback);
        break;
    case 974:
        wrapper->m_updateCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::DockWidget_wrapper::Callback_update>(callback);
        break;
    }
}
}

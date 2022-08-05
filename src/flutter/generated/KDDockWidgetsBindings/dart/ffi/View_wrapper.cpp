/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "View_wrapper.h"


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
View_wrapper::View_wrapper(KDDockWidgets::Controller *controller, KDDockWidgets::Type arg__2)
    : ::KDDockWidgets::View(controller, arg__2)
{
}
bool View_wrapper::aboutToBeDestroyed() const
{
    return ::KDDockWidgets::View::aboutToBeDestroyed();
}
void View_wrapper::activateWindow()
{
    if (m_activateWindowCallback) {
        const void *thisPtr = this;
        m_activateWindowCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void View_wrapper::activateWindow_nocallback()
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
KDDockWidgets::Controllers::DropArea *View_wrapper::asDropAreaController() const
{
    return ::KDDockWidgets::View::asDropAreaController();
}
KDDockWidgets::Controllers::Group *View_wrapper::asGroupController() const
{
    return ::KDDockWidgets::View::asGroupController();
}
KDDockWidgets::Controllers::Layout *View_wrapper::asLayout() const
{
    return ::KDDockWidgets::View::asLayout();
}
KDDockWidgets::Controllers::Stack *View_wrapper::asStackController() const
{
    return ::KDDockWidgets::View::asStackController();
}
KDDockWidgets::Controllers::TabBar *View_wrapper::asTabBarController() const
{
    return ::KDDockWidgets::View::asTabBarController();
}
KDDockWidgets::Controllers::TitleBar *View_wrapper::asTitleBarController() const
{
    return ::KDDockWidgets::View::asTitleBarController();
}
QSize View_wrapper::boundedMaxSize(QSize min, QSize max)
{
    return ::KDDockWidgets::View::boundedMaxSize(min, max);
}
bool View_wrapper::close()
{
    if (m_closeCallback) {
        const void *thisPtr = this;
        return m_closeCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
bool View_wrapper::close_nocallback()
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
void View_wrapper::closeRootView()
{
    ::KDDockWidgets::View::closeRootView();
}
KDDockWidgets::Controller *View_wrapper::controller() const
{
    return ::KDDockWidgets::View::controller();
}
void View_wrapper::createPlatformWindow()
{
    if (m_createPlatformWindowCallback) {
        const void *thisPtr = this;
        m_createPlatformWindowCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::View::createPlatformWindow();
    }
}
void View_wrapper::createPlatformWindow_nocallback()
{
    ::KDDockWidgets::View::createPlatformWindow();
}
bool View_wrapper::equals(const KDDockWidgets::View *one, const KDDockWidgets::View *two)
{
    return ::KDDockWidgets::View::equals(one, two);
}
bool View_wrapper::equals(const KDDockWidgets::View *other) const
{
    return ::KDDockWidgets::View::equals(other);
}
KDDockWidgets::Controller *View_wrapper::firstParentOfType(KDDockWidgets::Type arg__1) const
{
    return ::KDDockWidgets::View::firstParentOfType(arg__1);
}
KDDockWidgets::Controller *View_wrapper::firstParentOfType(KDDockWidgets::View *view,
                                                           KDDockWidgets::Type arg__2)
{
    return ::KDDockWidgets::View::firstParentOfType(view, arg__2);
}
Qt::WindowFlags View_wrapper::flags() const
{
    if (m_flagsCallback) {
        const void *thisPtr = this;
        return m_flagsCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
Qt::WindowFlags View_wrapper::flags_nocallback() const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
void View_wrapper::free()
{
    ::KDDockWidgets::View::free();
}
void View_wrapper::free_impl()
{
    if (m_free_implCallback) {
        const void *thisPtr = this;
        m_free_implCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::View::free_impl();
    }
}
void View_wrapper::free_impl_nocallback()
{
    ::KDDockWidgets::View::free_impl();
}
bool View_wrapper::freed() const
{
    return ::KDDockWidgets::View::freed();
}
QRect View_wrapper::geometry() const
{
    if (m_geometryCallback) {
        const void *thisPtr = this;
        return *m_geometryCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
QRect View_wrapper::geometry_nocallback() const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
QRect View_wrapper::globalGeometry() const
{
    return ::KDDockWidgets::View::globalGeometry();
}
void View_wrapper::grabMouse()
{
    if (m_grabMouseCallback) {
        const void *thisPtr = this;
        m_grabMouseCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void View_wrapper::grabMouse_nocallback()
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
QSize View_wrapper::hardcodedMinimumSize()
{
    return ::KDDockWidgets::View::hardcodedMinimumSize();
}
bool View_wrapper::hasFocus() const
{
    if (m_hasFocusCallback) {
        const void *thisPtr = this;
        return m_hasFocusCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
bool View_wrapper::hasFocus_nocallback() const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
int View_wrapper::height() const
{
    return ::KDDockWidgets::View::height();
}
void View_wrapper::hide()
{
    if (m_hideCallback) {
        const void *thisPtr = this;
        m_hideCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void View_wrapper::hide_nocallback()
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
QString View_wrapper::id() const
{
    return ::KDDockWidgets::View::id();
}
bool View_wrapper::inDtor() const
{
    return ::KDDockWidgets::View::inDtor();
}
void View_wrapper::init()
{
    if (m_initCallback) {
        const void *thisPtr = this;
        m_initCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::View::init();
    }
}
void View_wrapper::init_nocallback()
{
    ::KDDockWidgets::View::init();
}
bool View_wrapper::isActiveWindow() const
{
    if (m_isActiveWindowCallback) {
        const void *thisPtr = this;
        return m_isActiveWindowCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
bool View_wrapper::isActiveWindow_nocallback() const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
bool View_wrapper::isMaximized() const
{
    if (m_isMaximizedCallback) {
        const void *thisPtr = this;
        return m_isMaximizedCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
bool View_wrapper::isMaximized_nocallback() const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
bool View_wrapper::isMinimized() const
{
    if (m_isMinimizedCallback) {
        const void *thisPtr = this;
        return m_isMinimizedCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
bool View_wrapper::isMinimized_nocallback() const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
bool View_wrapper::isNull() const
{
    if (m_isNullCallback) {
        const void *thisPtr = this;
        return m_isNullCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::View::isNull();
    }
}
bool View_wrapper::isNull_nocallback() const
{
    return ::KDDockWidgets::View::isNull();
}
bool View_wrapper::isRootView() const
{
    if (m_isRootViewCallback) {
        const void *thisPtr = this;
        return m_isRootViewCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
bool View_wrapper::isRootView_nocallback() const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
bool View_wrapper::isVisible() const
{
    if (m_isVisibleCallback) {
        const void *thisPtr = this;
        return m_isVisibleCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
bool View_wrapper::isVisible_nocallback() const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
QPoint View_wrapper::mapFromGlobal(QPoint arg__1) const
{
    if (m_mapFromGlobalCallback) {
        const void *thisPtr = this;
        return *m_mapFromGlobalCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
QPoint View_wrapper::mapFromGlobal_nocallback(QPoint arg__1) const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
QPoint View_wrapper::mapTo(KDDockWidgets::View *arg__1, QPoint arg__2) const
{
    if (m_mapToCallback) {
        const void *thisPtr = this;
        return *m_mapToCallback(const_cast<void *>(thisPtr), arg__1, arg__2);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
QPoint View_wrapper::mapTo_nocallback(KDDockWidgets::View *arg__1, QPoint arg__2) const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
QPoint View_wrapper::mapToGlobal(QPoint arg__1) const
{
    if (m_mapToGlobalCallback) {
        const void *thisPtr = this;
        return *m_mapToGlobalCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
QPoint View_wrapper::mapToGlobal_nocallback(QPoint arg__1) const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
QSize View_wrapper::maxSizeHint() const
{
    if (m_maxSizeHintCallback) {
        const void *thisPtr = this;
        return *m_maxSizeHintCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
QSize View_wrapper::maxSizeHint_nocallback() const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
QSize View_wrapper::maximumSize() const
{
    if (m_maximumSizeCallback) {
        const void *thisPtr = this;
        return *m_maximumSizeCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
QSize View_wrapper::maximumSize_nocallback() const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
QSize View_wrapper::minSize() const
{
    if (m_minSizeCallback) {
        const void *thisPtr = this;
        return *m_minSizeCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
QSize View_wrapper::minSize_nocallback() const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
int View_wrapper::minimumHeight() const
{
    if (m_minimumHeightCallback) {
        const void *thisPtr = this;
        return m_minimumHeightCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::View::minimumHeight();
    }
}
int View_wrapper::minimumHeight_nocallback() const
{
    return ::KDDockWidgets::View::minimumHeight();
}
int View_wrapper::minimumWidth() const
{
    if (m_minimumWidthCallback) {
        const void *thisPtr = this;
        return m_minimumWidthCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::View::minimumWidth();
    }
}
int View_wrapper::minimumWidth_nocallback() const
{
    return ::KDDockWidgets::View::minimumWidth();
}
void View_wrapper::move(QPoint arg__1)
{
    ::KDDockWidgets::View::move(arg__1);
}
void View_wrapper::move(int x, int y)
{
    if (m_move_2Callback) {
        const void *thisPtr = this;
        m_move_2Callback(const_cast<void *>(thisPtr), x, y);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void View_wrapper::move_nocallback(int x, int y)
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
QRect View_wrapper::normalGeometry() const
{
    if (m_normalGeometryCallback) {
        const void *thisPtr = this;
        return *m_normalGeometryCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
QRect View_wrapper::normalGeometry_nocallback() const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
QString View_wrapper::objectName() const
{
    if (m_objectNameCallback) {
        const void *thisPtr = this;
        return *m_objectNameCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
QString View_wrapper::objectName_nocallback() const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
bool View_wrapper::onResize(QSize newSize)
{
    if (m_onResizeCallback) {
        const void *thisPtr = this;
        return m_onResizeCallback(const_cast<void *>(thisPtr), newSize);
    } else {
        return ::KDDockWidgets::View::onResize(newSize);
    }
}
bool View_wrapper::onResize_nocallback(QSize newSize)
{
    return ::KDDockWidgets::View::onResize(newSize);
}
QSize View_wrapper::parentSize() const
{
    return ::KDDockWidgets::View::parentSize();
}
QPoint View_wrapper::pos() const
{
    return ::KDDockWidgets::View::pos();
}
void View_wrapper::raise()
{
    if (m_raiseCallback) {
        const void *thisPtr = this;
        m_raiseCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void View_wrapper::raise_nocallback()
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::raiseAndActivate()
{
    if (m_raiseAndActivateCallback) {
        const void *thisPtr = this;
        m_raiseAndActivateCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void View_wrapper::raiseAndActivate_nocallback()
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
QRect View_wrapper::rect() const
{
    return ::KDDockWidgets::View::rect();
}
void View_wrapper::releaseKeyboard()
{
    if (m_releaseKeyboardCallback) {
        const void *thisPtr = this;
        m_releaseKeyboardCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void View_wrapper::releaseKeyboard_nocallback()
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::releaseMouse()
{
    if (m_releaseMouseCallback) {
        const void *thisPtr = this;
        m_releaseMouseCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void View_wrapper::releaseMouse_nocallback()
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::resize(QSize arg__1)
{
    ::KDDockWidgets::View::resize(arg__1);
}
void View_wrapper::resize(int w, int h)
{
    ::KDDockWidgets::View::resize(w, h);
}
void View_wrapper::setAboutToBeDestroyed()
{
    ::KDDockWidgets::View::setAboutToBeDestroyed();
}
void View_wrapper::setCursor(Qt::CursorShape arg__1)
{
    if (m_setCursorCallback) {
        const void *thisPtr = this;
        m_setCursorCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void View_wrapper::setCursor_nocallback(Qt::CursorShape arg__1)
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::setFixedHeight(int arg__1)
{
    if (m_setFixedHeightCallback) {
        const void *thisPtr = this;
        m_setFixedHeightCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void View_wrapper::setFixedHeight_nocallback(int arg__1)
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::setFixedWidth(int arg__1)
{
    if (m_setFixedWidthCallback) {
        const void *thisPtr = this;
        m_setFixedWidthCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void View_wrapper::setFixedWidth_nocallback(int arg__1)
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::setGeometry(QRect arg__1)
{
    if (m_setGeometryCallback) {
        const void *thisPtr = this;
        m_setGeometryCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void View_wrapper::setGeometry_nocallback(QRect arg__1)
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::setHeight(int height)
{
    if (m_setHeightCallback) {
        const void *thisPtr = this;
        m_setHeightCallback(const_cast<void *>(thisPtr), height);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void View_wrapper::setHeight_nocallback(int height)
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::setMaximumSize(QSize sz)
{
    if (m_setMaximumSizeCallback) {
        const void *thisPtr = this;
        m_setMaximumSizeCallback(const_cast<void *>(thisPtr), sz);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void View_wrapper::setMaximumSize_nocallback(QSize sz)
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::setMinimumSize(QSize arg__1)
{
    if (m_setMinimumSizeCallback) {
        const void *thisPtr = this;
        m_setMinimumSizeCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void View_wrapper::setMinimumSize_nocallback(QSize arg__1)
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::setMouseTracking(bool arg__1)
{
    if (m_setMouseTrackingCallback) {
        const void *thisPtr = this;
        m_setMouseTrackingCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void View_wrapper::setMouseTracking_nocallback(bool arg__1)
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::setObjectName(const QString &arg__1)
{
    if (m_setObjectNameCallback) {
        const void *thisPtr = this;
        m_setObjectNameCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void View_wrapper::setObjectName_nocallback(const QString &arg__1)
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::setParent(KDDockWidgets::View *arg__1)
{
    if (m_setParentCallback) {
        const void *thisPtr = this;
        m_setParentCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void View_wrapper::setParent_nocallback(KDDockWidgets::View *arg__1)
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::setSize(QSize arg__1)
{
    ::KDDockWidgets::View::setSize(arg__1);
}
void View_wrapper::setSize(int width, int height)
{
    if (m_setSize_2Callback) {
        const void *thisPtr = this;
        m_setSize_2Callback(const_cast<void *>(thisPtr), width, height);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void View_wrapper::setSize_nocallback(int width, int height)
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::setVisible(bool arg__1)
{
    if (m_setVisibleCallback) {
        const void *thisPtr = this;
        m_setVisibleCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void View_wrapper::setVisible_nocallback(bool arg__1)
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::setWidth(int width)
{
    if (m_setWidthCallback) {
        const void *thisPtr = this;
        m_setWidthCallback(const_cast<void *>(thisPtr), width);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void View_wrapper::setWidth_nocallback(int width)
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::setWindowOpacity(double arg__1)
{
    if (m_setWindowOpacityCallback) {
        const void *thisPtr = this;
        m_setWindowOpacityCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void View_wrapper::setWindowOpacity_nocallback(double arg__1)
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::setWindowTitle(const QString &title)
{
    if (m_setWindowTitleCallback) {
        const void *thisPtr = this;
        m_setWindowTitleCallback(const_cast<void *>(thisPtr), title);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void View_wrapper::setWindowTitle_nocallback(const QString &title)
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::setZOrder(int arg__1)
{
    if (m_setZOrderCallback) {
        const void *thisPtr = this;
        m_setZOrderCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        ::KDDockWidgets::View::setZOrder(arg__1);
    }
}
void View_wrapper::setZOrder_nocallback(int arg__1)
{
    ::KDDockWidgets::View::setZOrder(arg__1);
}
void View_wrapper::show()
{
    if (m_showCallback) {
        const void *thisPtr = this;
        m_showCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void View_wrapper::show_nocallback()
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::showMaximized()
{
    if (m_showMaximizedCallback) {
        const void *thisPtr = this;
        m_showMaximizedCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void View_wrapper::showMaximized_nocallback()
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::showMinimized()
{
    if (m_showMinimizedCallback) {
        const void *thisPtr = this;
        m_showMinimizedCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void View_wrapper::showMinimized_nocallback()
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::showNormal()
{
    if (m_showNormalCallback) {
        const void *thisPtr = this;
        m_showNormalCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void View_wrapper::showNormal_nocallback()
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
QSize View_wrapper::size() const
{
    return ::KDDockWidgets::View::size();
}
QSize View_wrapper::sizeHint() const
{
    if (m_sizeHintCallback) {
        const void *thisPtr = this;
        return *m_sizeHintCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::View::sizeHint();
    }
}
QSize View_wrapper::sizeHint_nocallback() const
{
    return ::KDDockWidgets::View::sizeHint();
}
KDDockWidgets::Type View_wrapper::type() const
{
    return ::KDDockWidgets::View::type();
}
void View_wrapper::update()
{
    if (m_updateCallback) {
        const void *thisPtr = this;
        m_updateCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void View_wrapper::update_nocallback()
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
int View_wrapper::width() const
{
    return ::KDDockWidgets::View::width();
}
QRect View_wrapper::windowGeometry() const
{
    return ::KDDockWidgets::View::windowGeometry();
}
int View_wrapper::x() const
{
    return ::KDDockWidgets::View::x();
}
int View_wrapper::y() const
{
    return ::KDDockWidgets::View::y();
}
View_wrapper::~View_wrapper()
{
}

}
static KDDockWidgets::View *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::View *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::View_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__View_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(cppObj);
}
void *c_KDDockWidgets__View__constructor_Controller_Type(void *controller_, int arg__2)
{
    auto controller = reinterpret_cast<KDDockWidgets::Controller *>(controller_);
    auto ptr = new KDDockWidgetsBindings_wrappersNS::View_wrapper(
        controller, static_cast<KDDockWidgets::Type>(arg__2));
    return reinterpret_cast<void *>(ptr);
}
// aboutToBeDestroyed() const
bool c_KDDockWidgets__View__aboutToBeDestroyed(void *thisObj)
{
    return fromPtr(thisObj)->aboutToBeDestroyed();
}
// activateWindow()
void c_KDDockWidgets__View__activateWindow(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->activateWindow_nocallback();
        } else {
            return targetPtr->activateWindow();
        }
    }();
}
// asDropAreaController() const
void *c_KDDockWidgets__View__asDropAreaController(void *thisObj)
{
    return fromPtr(thisObj)->asDropAreaController();
}
// asGroupController() const
void *c_KDDockWidgets__View__asGroupController(void *thisObj)
{
    return fromPtr(thisObj)->asGroupController();
}
// asLayout() const
void *c_KDDockWidgets__View__asLayout(void *thisObj)
{
    return fromPtr(thisObj)->asLayout();
}
// asStackController() const
void *c_KDDockWidgets__View__asStackController(void *thisObj)
{
    return fromPtr(thisObj)->asStackController();
}
// asTabBarController() const
void *c_KDDockWidgets__View__asTabBarController(void *thisObj)
{
    return fromPtr(thisObj)->asTabBarController();
}
// asTitleBarController() const
void *c_KDDockWidgets__View__asTitleBarController(void *thisObj)
{
    return fromPtr(thisObj)->asTitleBarController();
}
// boundedMaxSize(QSize min, QSize max)
void *c_static_KDDockWidgets__View__boundedMaxSize_QSize_QSize(void *min_, void *max_)
{
    auto &min = *reinterpret_cast<QSize *>(min_);
    auto &max = *reinterpret_cast<QSize *>(max_);
    return new Dartagnan::ValueWrapper<QSize> {
        KDDockWidgetsBindings_wrappersNS::View_wrapper::boundedMaxSize(min, max)
    };
}
// close()
bool c_KDDockWidgets__View__close(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->close_nocallback();
        } else {
            return targetPtr->close();
        }
    }();
}
// closeRootView()
void c_KDDockWidgets__View__closeRootView(void *thisObj)
{
    fromPtr(thisObj)->closeRootView();
}
// controller() const
void *c_KDDockWidgets__View__controller(void *thisObj)
{
    return fromPtr(thisObj)->controller();
}
// createPlatformWindow()
void c_KDDockWidgets__View__createPlatformWindow(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->createPlatformWindow_nocallback();
        } else {
            return targetPtr->createPlatformWindow();
        }
    }();
}
// equals(const KDDockWidgets::View * one, const KDDockWidgets::View * two)
bool c_static_KDDockWidgets__View__equals_View_View(void *one_, void *two_)
{
    auto one = reinterpret_cast<KDDockWidgets::View *>(one_);
    auto two = reinterpret_cast<KDDockWidgets::View *>(two_);
    return KDDockWidgetsBindings_wrappersNS::View_wrapper::equals(one, two);
}
// equals(const KDDockWidgets::View * other) const
bool c_KDDockWidgets__View__equals_View(void *thisObj, void *other_)
{
    auto other = reinterpret_cast<KDDockWidgets::View *>(other_);
    return fromPtr(thisObj)->equals(other);
}
// firstParentOfType(KDDockWidgets::Type arg__1) const
void *c_KDDockWidgets__View__firstParentOfType_Type(void *thisObj, int arg__1)
{
    return fromPtr(thisObj)->firstParentOfType(static_cast<KDDockWidgets::Type>(arg__1));
}
// firstParentOfType(KDDockWidgets::View * view, KDDockWidgets::Type arg__2)
void *c_static_KDDockWidgets__View__firstParentOfType_View_Type(void *view_, int arg__2)
{
    auto view = reinterpret_cast<KDDockWidgets::View *>(view_);
    return KDDockWidgetsBindings_wrappersNS::View_wrapper::firstParentOfType(
        view, static_cast<KDDockWidgets::Type>(arg__2));
}
// flags() const
int c_KDDockWidgets__View__flags(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->flags_nocallback();
        } else {
            return targetPtr->flags();
        }
    }();
}
// free()
void c_KDDockWidgets__View__free(void *thisObj)
{
    fromPtr(thisObj)->free();
}
// free_impl()
void c_KDDockWidgets__View__free_impl(void *thisObj)
{
    fromWrapperPtr(thisObj)->free_impl_nocallback();
}
// freed() const
bool c_KDDockWidgets__View__freed(void *thisObj)
{
    return fromPtr(thisObj)->freed();
}
// geometry() const
void *c_KDDockWidgets__View__geometry(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QRect> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->geometry_nocallback();
        } else {
            return targetPtr->geometry();
        }
    }() };
}
// globalGeometry() const
void *c_KDDockWidgets__View__globalGeometry(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QRect> { fromPtr(thisObj)->globalGeometry() };
}
// grabMouse()
void c_KDDockWidgets__View__grabMouse(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->grabMouse_nocallback();
        } else {
            return targetPtr->grabMouse();
        }
    }();
}
// hardcodedMinimumSize()
void *c_static_KDDockWidgets__View__hardcodedMinimumSize()
{
    return new Dartagnan::ValueWrapper<QSize> {
        KDDockWidgetsBindings_wrappersNS::View_wrapper::hardcodedMinimumSize()
    };
}
// hasFocus() const
bool c_KDDockWidgets__View__hasFocus(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->hasFocus_nocallback();
        } else {
            return targetPtr->hasFocus();
        }
    }();
}
// height() const
int c_KDDockWidgets__View__height(void *thisObj)
{
    return fromPtr(thisObj)->height();
}
// hide()
void c_KDDockWidgets__View__hide(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->hide_nocallback();
        } else {
            return targetPtr->hide();
        }
    }();
}
// id() const
void *c_KDDockWidgets__View__id(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QString> { fromPtr(thisObj)->id() };
}
// inDtor() const
bool c_KDDockWidgets__View__inDtor(void *thisObj)
{
    return fromPtr(thisObj)->inDtor();
}
// init()
void c_KDDockWidgets__View__init(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->init_nocallback();
        } else {
            return targetPtr->init();
        }
    }();
}
// isActiveWindow() const
bool c_KDDockWidgets__View__isActiveWindow(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->isActiveWindow_nocallback();
        } else {
            return targetPtr->isActiveWindow();
        }
    }();
}
// isMaximized() const
bool c_KDDockWidgets__View__isMaximized(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->isMaximized_nocallback();
        } else {
            return targetPtr->isMaximized();
        }
    }();
}
// isMinimized() const
bool c_KDDockWidgets__View__isMinimized(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->isMinimized_nocallback();
        } else {
            return targetPtr->isMinimized();
        }
    }();
}
// isNull() const
bool c_KDDockWidgets__View__isNull(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->isNull_nocallback();
        } else {
            return targetPtr->isNull();
        }
    }();
}
// isRootView() const
bool c_KDDockWidgets__View__isRootView(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->isRootView_nocallback();
        } else {
            return targetPtr->isRootView();
        }
    }();
}
// isVisible() const
bool c_KDDockWidgets__View__isVisible(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->isVisible_nocallback();
        } else {
            return targetPtr->isVisible();
        }
    }();
}
// mapFromGlobal(QPoint arg__1) const
void *c_KDDockWidgets__View__mapFromGlobal_QPoint(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QPoint *>(arg__1_);
    return new Dartagnan::ValueWrapper<QPoint> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->mapFromGlobal_nocallback(arg__1);
        } else {
            return targetPtr->mapFromGlobal(arg__1);
        }
    }() };
}
// mapTo(KDDockWidgets::View * arg__1, QPoint arg__2) const
void *c_KDDockWidgets__View__mapTo_View_QPoint(void *thisObj, void *arg__1_, void *arg__2_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::View *>(arg__1_);
    auto &arg__2 = *reinterpret_cast<QPoint *>(arg__2_);
    return new Dartagnan::ValueWrapper<QPoint> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->mapTo_nocallback(arg__1, arg__2);
        } else {
            return targetPtr->mapTo(arg__1, arg__2);
        }
    }() };
}
// mapToGlobal(QPoint arg__1) const
void *c_KDDockWidgets__View__mapToGlobal_QPoint(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QPoint *>(arg__1_);
    return new Dartagnan::ValueWrapper<QPoint> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->mapToGlobal_nocallback(arg__1);
        } else {
            return targetPtr->mapToGlobal(arg__1);
        }
    }() };
}
// maxSizeHint() const
void *c_KDDockWidgets__View__maxSizeHint(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->maxSizeHint_nocallback();
        } else {
            return targetPtr->maxSizeHint();
        }
    }() };
}
// maximumSize() const
void *c_KDDockWidgets__View__maximumSize(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->maximumSize_nocallback();
        } else {
            return targetPtr->maximumSize();
        }
    }() };
}
// minSize() const
void *c_KDDockWidgets__View__minSize(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->minSize_nocallback();
        } else {
            return targetPtr->minSize();
        }
    }() };
}
// minimumHeight() const
int c_KDDockWidgets__View__minimumHeight(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->minimumHeight_nocallback();
        } else {
            return targetPtr->minimumHeight();
        }
    }();
}
// minimumWidth() const
int c_KDDockWidgets__View__minimumWidth(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->minimumWidth_nocallback();
        } else {
            return targetPtr->minimumWidth();
        }
    }();
}
// move(QPoint arg__1)
void c_KDDockWidgets__View__move_QPoint(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QPoint *>(arg__1_);
    fromPtr(thisObj)->move(arg__1);
}
// move(int x, int y)
void c_KDDockWidgets__View__move_int_int(void *thisObj, int x, int y)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->move_nocallback(x, y);
        } else {
            return targetPtr->move(x, y);
        }
    }();
}
// normalGeometry() const
void *c_KDDockWidgets__View__normalGeometry(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QRect> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->normalGeometry_nocallback();
        } else {
            return targetPtr->normalGeometry();
        }
    }() };
}
// objectName() const
void *c_KDDockWidgets__View__objectName(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QString> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->objectName_nocallback();
        } else {
            return targetPtr->objectName();
        }
    }() };
}
// onResize(QSize newSize)
bool c_KDDockWidgets__View__onResize_QSize(void *thisObj, void *newSize_)
{
    auto &newSize = *reinterpret_cast<QSize *>(newSize_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->onResize_nocallback(newSize);
        } else {
            return targetPtr->onResize(newSize);
        }
    }();
}
// parentSize() const
void *c_KDDockWidgets__View__parentSize(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { fromPtr(thisObj)->parentSize() };
}
// pos() const
void *c_KDDockWidgets__View__pos(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QPoint> { fromPtr(thisObj)->pos() };
}
// raise()
void c_KDDockWidgets__View__raise(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->raise_nocallback();
        } else {
            return targetPtr->raise();
        }
    }();
}
// raiseAndActivate()
void c_KDDockWidgets__View__raiseAndActivate(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->raiseAndActivate_nocallback();
        } else {
            return targetPtr->raiseAndActivate();
        }
    }();
}
// rect() const
void *c_KDDockWidgets__View__rect(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QRect> { fromPtr(thisObj)->rect() };
}
// releaseKeyboard()
void c_KDDockWidgets__View__releaseKeyboard(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->releaseKeyboard_nocallback();
        } else {
            return targetPtr->releaseKeyboard();
        }
    }();
}
// releaseMouse()
void c_KDDockWidgets__View__releaseMouse(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->releaseMouse_nocallback();
        } else {
            return targetPtr->releaseMouse();
        }
    }();
}
// resize(QSize arg__1)
void c_KDDockWidgets__View__resize_QSize(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QSize *>(arg__1_);
    fromPtr(thisObj)->resize(arg__1);
}
// resize(int w, int h)
void c_KDDockWidgets__View__resize_int_int(void *thisObj, int w, int h)
{
    fromPtr(thisObj)->resize(w, h);
}
// setAboutToBeDestroyed()
void c_KDDockWidgets__View__setAboutToBeDestroyed(void *thisObj)
{
    fromPtr(thisObj)->setAboutToBeDestroyed();
}
// setCursor(Qt::CursorShape arg__1)
void c_KDDockWidgets__View__setCursor_CursorShape(void *thisObj, int arg__1)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setCursor_nocallback(static_cast<Qt::CursorShape>(arg__1));
        } else {
            return targetPtr->setCursor(static_cast<Qt::CursorShape>(arg__1));
        }
    }();
}
// setFixedHeight(int arg__1)
void c_KDDockWidgets__View__setFixedHeight_int(void *thisObj, int arg__1)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setFixedHeight_nocallback(arg__1);
        } else {
            return targetPtr->setFixedHeight(arg__1);
        }
    }();
}
// setFixedWidth(int arg__1)
void c_KDDockWidgets__View__setFixedWidth_int(void *thisObj, int arg__1)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setFixedWidth_nocallback(arg__1);
        } else {
            return targetPtr->setFixedWidth(arg__1);
        }
    }();
}
// setGeometry(QRect arg__1)
void c_KDDockWidgets__View__setGeometry_QRect(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QRect *>(arg__1_);
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setGeometry_nocallback(arg__1);
        } else {
            return targetPtr->setGeometry(arg__1);
        }
    }();
}
// setHeight(int height)
void c_KDDockWidgets__View__setHeight_int(void *thisObj, int height)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setHeight_nocallback(height);
        } else {
            return targetPtr->setHeight(height);
        }
    }();
}
// setMaximumSize(QSize sz)
void c_KDDockWidgets__View__setMaximumSize_QSize(void *thisObj, void *sz_)
{
    auto &sz = *reinterpret_cast<QSize *>(sz_);
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setMaximumSize_nocallback(sz);
        } else {
            return targetPtr->setMaximumSize(sz);
        }
    }();
}
// setMinimumSize(QSize arg__1)
void c_KDDockWidgets__View__setMinimumSize_QSize(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QSize *>(arg__1_);
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setMinimumSize_nocallback(arg__1);
        } else {
            return targetPtr->setMinimumSize(arg__1);
        }
    }();
}
// setMouseTracking(bool arg__1)
void c_KDDockWidgets__View__setMouseTracking_bool(void *thisObj, bool arg__1)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setMouseTracking_nocallback(arg__1);
        } else {
            return targetPtr->setMouseTracking(arg__1);
        }
    }();
}
// setObjectName(const QString & arg__1)
void c_KDDockWidgets__View__setObjectName_QString(void *thisObj, const char *arg__1_)
{
    const auto arg__1 = QString::fromUtf8(arg__1_);
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setObjectName_nocallback(arg__1);
        } else {
            return targetPtr->setObjectName(arg__1);
        }
    }();
}
// setParent(KDDockWidgets::View * arg__1)
void c_KDDockWidgets__View__setParent_View(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::View *>(arg__1_);
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setParent_nocallback(arg__1);
        } else {
            return targetPtr->setParent(arg__1);
        }
    }();
}
// setSize(QSize arg__1)
void c_KDDockWidgets__View__setSize_QSize(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QSize *>(arg__1_);
    fromPtr(thisObj)->setSize(arg__1);
}
// setSize(int width, int height)
void c_KDDockWidgets__View__setSize_int_int(void *thisObj, int width, int height)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setSize_nocallback(width, height);
        } else {
            return targetPtr->setSize(width, height);
        }
    }();
}
// setVisible(bool arg__1)
void c_KDDockWidgets__View__setVisible_bool(void *thisObj, bool arg__1)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setVisible_nocallback(arg__1);
        } else {
            return targetPtr->setVisible(arg__1);
        }
    }();
}
// setWidth(int width)
void c_KDDockWidgets__View__setWidth_int(void *thisObj, int width)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setWidth_nocallback(width);
        } else {
            return targetPtr->setWidth(width);
        }
    }();
}
// setWindowOpacity(double arg__1)
void c_KDDockWidgets__View__setWindowOpacity_double(void *thisObj, double arg__1)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setWindowOpacity_nocallback(arg__1);
        } else {
            return targetPtr->setWindowOpacity(arg__1);
        }
    }();
}
// setWindowTitle(const QString & title)
void c_KDDockWidgets__View__setWindowTitle_QString(void *thisObj, const char *title_)
{
    const auto title = QString::fromUtf8(title_);
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setWindowTitle_nocallback(title);
        } else {
            return targetPtr->setWindowTitle(title);
        }
    }();
}
// setZOrder(int arg__1)
void c_KDDockWidgets__View__setZOrder_int(void *thisObj, int arg__1)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setZOrder_nocallback(arg__1);
        } else {
            return targetPtr->setZOrder(arg__1);
        }
    }();
}
// show()
void c_KDDockWidgets__View__show(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->show_nocallback();
        } else {
            return targetPtr->show();
        }
    }();
}
// showMaximized()
void c_KDDockWidgets__View__showMaximized(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->showMaximized_nocallback();
        } else {
            return targetPtr->showMaximized();
        }
    }();
}
// showMinimized()
void c_KDDockWidgets__View__showMinimized(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->showMinimized_nocallback();
        } else {
            return targetPtr->showMinimized();
        }
    }();
}
// showNormal()
void c_KDDockWidgets__View__showNormal(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->showNormal_nocallback();
        } else {
            return targetPtr->showNormal();
        }
    }();
}
// size() const
void *c_KDDockWidgets__View__size(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { fromPtr(thisObj)->size() };
}
// sizeHint() const
void *c_KDDockWidgets__View__sizeHint(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->sizeHint_nocallback();
        } else {
            return targetPtr->sizeHint();
        }
    }() };
}
// type() const
int c_KDDockWidgets__View__type(void *thisObj)
{
    return int(fromPtr(thisObj)->type());
}
// update()
void c_KDDockWidgets__View__update(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->update_nocallback();
        } else {
            return targetPtr->update();
        }
    }();
}
// width() const
int c_KDDockWidgets__View__width(void *thisObj)
{
    return fromPtr(thisObj)->width();
}
// windowGeometry() const
void *c_KDDockWidgets__View__windowGeometry(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QRect> { fromPtr(thisObj)->windowGeometry() };
}
// x() const
int c_KDDockWidgets__View__x(void *thisObj)
{
    return fromPtr(thisObj)->x();
}
// y() const
int c_KDDockWidgets__View__y(void *thisObj)
{
    return fromPtr(thisObj)->y();
}
void c_KDDockWidgets__View__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__View__registerVirtualMethodCallback(void *ptr, void *callback, int methodId)
{
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 850:
        wrapper->m_activateWindowCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_activateWindow>(callback);
        break;
    case 858:
        wrapper->m_closeCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_close>(
                callback);
        break;
    case 861:
        wrapper->m_createPlatformWindowCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_createPlatformWindow>(
            callback);
        break;
    case 866:
        wrapper->m_flagsCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_flags>(
                callback);
        break;
    case 868:
        wrapper->m_free_implCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_free_impl>(
                callback);
        break;
    case 870:
        wrapper->m_geometryCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_geometry>(
                callback);
        break;
    case 872:
        wrapper->m_grabMouseCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_grabMouse>(
                callback);
        break;
    case 875:
        wrapper->m_hasFocusCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_hasFocus>(
                callback);
        break;
    case 877:
        wrapper->m_hideCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_hide>(
                callback);
        break;
    case 880:
        wrapper->m_initCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_init>(
                callback);
        break;
    case 882:
        wrapper->m_isActiveWindowCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_isActiveWindow>(callback);
        break;
    case 883:
        wrapper->m_isMaximizedCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_isMaximized>(
                callback);
        break;
    case 884:
        wrapper->m_isMinimizedCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_isMinimized>(
                callback);
        break;
    case 885:
        wrapper->m_isNullCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_isNull>(
                callback);
        break;
    case 886:
        wrapper->m_isRootViewCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_isRootView>(
                callback);
        break;
    case 887:
        wrapper->m_isVisibleCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_isVisible>(
                callback);
        break;
    case 888:
        wrapper->m_mapFromGlobalCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_mapFromGlobal>(callback);
        break;
    case 889:
        wrapper->m_mapToCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_mapTo>(
                callback);
        break;
    case 890:
        wrapper->m_mapToGlobalCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_mapToGlobal>(
                callback);
        break;
    case 891:
        wrapper->m_maxSizeHintCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_maxSizeHint>(
                callback);
        break;
    case 892:
        wrapper->m_maximumSizeCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_maximumSize>(
                callback);
        break;
    case 893:
        wrapper->m_minSizeCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_minSize>(
                callback);
        break;
    case 894:
        wrapper->m_minimumHeightCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_minimumHeight>(callback);
        break;
    case 895:
        wrapper->m_minimumWidthCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_minimumWidth>(
                callback);
        break;
    case 897:
        wrapper->m_move_2Callback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_move_2>(
                callback);
        break;
    case 898:
        wrapper->m_normalGeometryCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_normalGeometry>(callback);
        break;
    case 899:
        wrapper->m_objectNameCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_objectName>(
                callback);
        break;
    case 900:
        wrapper->m_onResizeCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_onResize>(
                callback);
        break;
    case 903:
        wrapper->m_raiseCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_raise>(
                callback);
        break;
    case 904:
        wrapper->m_raiseAndActivateCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_raiseAndActivate>(callback);
        break;
    case 906:
        wrapper->m_releaseKeyboardCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_releaseKeyboard>(callback);
        break;
    case 907:
        wrapper->m_releaseMouseCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_releaseMouse>(
                callback);
        break;
    case 911:
        wrapper->m_setCursorCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_setCursor>(
                callback);
        break;
    case 912:
        wrapper->m_setFixedHeightCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_setFixedHeight>(callback);
        break;
    case 913:
        wrapper->m_setFixedWidthCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_setFixedWidth>(callback);
        break;
    case 914:
        wrapper->m_setGeometryCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_setGeometry>(
                callback);
        break;
    case 915:
        wrapper->m_setHeightCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_setHeight>(
                callback);
        break;
    case 916:
        wrapper->m_setMaximumSizeCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_setMaximumSize>(callback);
        break;
    case 917:
        wrapper->m_setMinimumSizeCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_setMinimumSize>(callback);
        break;
    case 918:
        wrapper->m_setMouseTrackingCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_setMouseTracking>(callback);
        break;
    case 919:
        wrapper->m_setObjectNameCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_setObjectName>(callback);
        break;
    case 920:
        wrapper->m_setParentCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_setParent>(
                callback);
        break;
    case 922:
        wrapper->m_setSize_2Callback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_setSize_2>(
                callback);
        break;
    case 923:
        wrapper->m_setVisibleCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_setVisible>(
                callback);
        break;
    case 924:
        wrapper->m_setWidthCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_setWidth>(
                callback);
        break;
    case 925:
        wrapper->m_setWindowOpacityCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_setWindowOpacity>(callback);
        break;
    case 926:
        wrapper->m_setWindowTitleCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_setWindowTitle>(callback);
        break;
    case 927:
        wrapper->m_setZOrderCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_setZOrder>(
                callback);
        break;
    case 928:
        wrapper->m_showCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_show>(
                callback);
        break;
    case 929:
        wrapper->m_showMaximizedCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_showMaximized>(callback);
        break;
    case 930:
        wrapper->m_showMinimizedCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_showMinimized>(callback);
        break;
    case 931:
        wrapper->m_showNormalCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_showNormal>(
                callback);
        break;
    case 933:
        wrapper->m_sizeHintCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_sizeHint>(
                callback);
        break;
    case 935:
        wrapper->m_updateCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_update>(
                callback);
        break;
    }
}
}

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

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
// tag=1006
View_wrapper::View_wrapper(KDDockWidgets::Controller *controller, KDDockWidgets::Type arg__2)
    : ::KDDockWidgets::View(controller, arg__2)
{
}
bool View_wrapper::aboutToBeDestroyed() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::View::aboutToBeDestroyed();
}
void View_wrapper::activateWindow()
{
    // tag=1000
    if (m_activateWindowCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_activateWindowCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
// tag=1009
void View_wrapper::activateWindow_nocallback()
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
KDDockWidgets::Controllers::DropArea *View_wrapper::asDropAreaController() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::View::asDropAreaController();
}
KDDockWidgets::Controllers::Layout *View_wrapper::asLayout() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::View::asLayout();
}
QSize View_wrapper::boundedMaxSize(QSize min, QSize max)
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::View::boundedMaxSize(min, max);
}
bool View_wrapper::close()
{
    // tag=1000
    if (m_closeCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_closeCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
// tag=1009
bool View_wrapper::close_nocallback()
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
void View_wrapper::closeRootView()
{
    // tag=1000

    // tag=1004
    ::KDDockWidgets::View::closeRootView();
}
KDDockWidgets::Controller *View_wrapper::controller() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::View::controller();
}
void View_wrapper::createPlatformWindow()
{
    // tag=1000
    if (m_createPlatformWindowCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_createPlatformWindowCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        ::KDDockWidgets::View::createPlatformWindow();
    }
}
// tag=1009
void View_wrapper::createPlatformWindow_nocallback()
{
    // tag=1003
    ::KDDockWidgets::View::createPlatformWindow();
}
bool View_wrapper::equals(const KDDockWidgets::View *one, const KDDockWidgets::View *two)
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::View::equals(one, two);
}
bool View_wrapper::equals(const KDDockWidgets::View *other) const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::View::equals(other);
}
KDDockWidgets::Controller *View_wrapper::firstParentOfType(KDDockWidgets::Type arg__1) const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::View::firstParentOfType(arg__1);
}
KDDockWidgets::Controller *View_wrapper::firstParentOfType(KDDockWidgets::View *view, KDDockWidgets::Type arg__2)
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::View::firstParentOfType(view, arg__2);
}
Qt::WindowFlags View_wrapper::flags() const
{
    // tag=1000
    if (m_flagsCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_flagsCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
// tag=1009
Qt::WindowFlags View_wrapper::flags_nocallback() const
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
void View_wrapper::free()
{
    // tag=1000

    // tag=1004
    ::KDDockWidgets::View::free();
}
void View_wrapper::free_impl()
{
    // tag=1000
    if (m_free_implCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_free_implCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        ::KDDockWidgets::View::free_impl();
    }
}
// tag=1009
void View_wrapper::free_impl_nocallback()
{
    // tag=1003
    ::KDDockWidgets::View::free_impl();
}
bool View_wrapper::freed() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::View::freed();
}
QRect View_wrapper::geometry() const
{
    // tag=1000
    if (m_geometryCallback) {
        // tag=1001
        const void *thisPtr = this;
        return *m_geometryCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
// tag=1009
QRect View_wrapper::geometry_nocallback() const
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
QRect View_wrapper::globalGeometry() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::View::globalGeometry();
}
void View_wrapper::grabMouse()
{
    // tag=1000
    if (m_grabMouseCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_grabMouseCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
// tag=1009
void View_wrapper::grabMouse_nocallback()
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
QSize View_wrapper::hardcodedMinimumSize()
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::View::hardcodedMinimumSize();
}
bool View_wrapper::hasFocus() const
{
    // tag=1000
    if (m_hasFocusCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_hasFocusCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
// tag=1009
bool View_wrapper::hasFocus_nocallback() const
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
int View_wrapper::height() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::View::height();
}
void View_wrapper::hide()
{
    // tag=1000
    if (m_hideCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_hideCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
// tag=1009
void View_wrapper::hide_nocallback()
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
QString View_wrapper::id() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::View::id();
}
bool View_wrapper::inDtor() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::View::inDtor();
}
void View_wrapper::init()
{
    // tag=1000
    if (m_initCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_initCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        ::KDDockWidgets::View::init();
    }
}
// tag=1009
void View_wrapper::init_nocallback()
{
    // tag=1003
    ::KDDockWidgets::View::init();
}
bool View_wrapper::isActiveWindow() const
{
    // tag=1000
    if (m_isActiveWindowCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_isActiveWindowCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
// tag=1009
bool View_wrapper::isActiveWindow_nocallback() const
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
bool View_wrapper::isMaximized() const
{
    // tag=1000
    if (m_isMaximizedCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_isMaximizedCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
// tag=1009
bool View_wrapper::isMaximized_nocallback() const
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
bool View_wrapper::isMinimized() const
{
    // tag=1000
    if (m_isMinimizedCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_isMinimizedCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
// tag=1009
bool View_wrapper::isMinimized_nocallback() const
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
bool View_wrapper::isNull() const
{
    // tag=1000
    if (m_isNullCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_isNullCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        return ::KDDockWidgets::View::isNull();
    }
}
// tag=1009
bool View_wrapper::isNull_nocallback() const
{
    // tag=1003
    return ::KDDockWidgets::View::isNull();
}
bool View_wrapper::isRootView() const
{
    // tag=1000
    if (m_isRootViewCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_isRootViewCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
// tag=1009
bool View_wrapper::isRootView_nocallback() const
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
bool View_wrapper::isVisible() const
{
    // tag=1000
    if (m_isVisibleCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_isVisibleCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
// tag=1009
bool View_wrapper::isVisible_nocallback() const
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
QPoint View_wrapper::mapFromGlobal(QPoint arg__1) const
{
    // tag=1000
    if (m_mapFromGlobalCallback) {
        // tag=1001
        const void *thisPtr = this;
        return *m_mapFromGlobalCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
// tag=1009
QPoint View_wrapper::mapFromGlobal_nocallback(QPoint arg__1) const
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
QPoint View_wrapper::mapTo(KDDockWidgets::View *arg__1, QPoint arg__2) const
{
    // tag=1000
    if (m_mapToCallback) {
        // tag=1001
        const void *thisPtr = this;
        return *m_mapToCallback(const_cast<void *>(thisPtr), arg__1, arg__2);
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
// tag=1009
QPoint View_wrapper::mapTo_nocallback(KDDockWidgets::View *arg__1, QPoint arg__2) const
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
QPoint View_wrapper::mapToGlobal(QPoint arg__1) const
{
    // tag=1000
    if (m_mapToGlobalCallback) {
        // tag=1001
        const void *thisPtr = this;
        return *m_mapToGlobalCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
// tag=1009
QPoint View_wrapper::mapToGlobal_nocallback(QPoint arg__1) const
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
QSize View_wrapper::maxSizeHint() const
{
    // tag=1000
    if (m_maxSizeHintCallback) {
        // tag=1001
        const void *thisPtr = this;
        return *m_maxSizeHintCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
// tag=1009
QSize View_wrapper::maxSizeHint_nocallback() const
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
QSize View_wrapper::maximumSize() const
{
    // tag=1000
    if (m_maximumSizeCallback) {
        // tag=1001
        const void *thisPtr = this;
        return *m_maximumSizeCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
// tag=1009
QSize View_wrapper::maximumSize_nocallback() const
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
QSize View_wrapper::minSize() const
{
    // tag=1000
    if (m_minSizeCallback) {
        // tag=1001
        const void *thisPtr = this;
        return *m_minSizeCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
// tag=1009
QSize View_wrapper::minSize_nocallback() const
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
int View_wrapper::minimumHeight() const
{
    // tag=1000
    if (m_minimumHeightCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_minimumHeightCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        return ::KDDockWidgets::View::minimumHeight();
    }
}
// tag=1009
int View_wrapper::minimumHeight_nocallback() const
{
    // tag=1003
    return ::KDDockWidgets::View::minimumHeight();
}
int View_wrapper::minimumWidth() const
{
    // tag=1000
    if (m_minimumWidthCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_minimumWidthCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        return ::KDDockWidgets::View::minimumWidth();
    }
}
// tag=1009
int View_wrapper::minimumWidth_nocallback() const
{
    // tag=1003
    return ::KDDockWidgets::View::minimumWidth();
}
void View_wrapper::move(QPoint arg__1)
{
    // tag=1000

    // tag=1004
    ::KDDockWidgets::View::move(arg__1);
}
void View_wrapper::move(int x, int y)
{
    // tag=1000
    if (m_move_2Callback) {
        // tag=1001
        const void *thisPtr = this;
        m_move_2Callback(const_cast<void *>(thisPtr), x, y);
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
// tag=1009
void View_wrapper::move_nocallback(int x, int y)
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
QRect View_wrapper::normalGeometry() const
{
    // tag=1000
    if (m_normalGeometryCallback) {
        // tag=1001
        const void *thisPtr = this;
        return *m_normalGeometryCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
// tag=1009
QRect View_wrapper::normalGeometry_nocallback() const
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
QString View_wrapper::objectName() const
{
    // tag=1000
    if (m_objectNameCallback) {
        // tag=1001
        const void *thisPtr = this;
        return *m_objectNameCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
// tag=1009
QString View_wrapper::objectName_nocallback() const
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
bool View_wrapper::onResize(QSize newSize)
{
    // tag=1000
    if (m_onResizeCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_onResizeCallback(const_cast<void *>(thisPtr), newSize);
    } else {
        // tag=1002
        return ::KDDockWidgets::View::onResize(newSize);
    }
}
// tag=1009
bool View_wrapper::onResize_nocallback(QSize newSize)
{
    // tag=1003
    return ::KDDockWidgets::View::onResize(newSize);
}
QSize View_wrapper::parentSize() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::View::parentSize();
}
QPoint View_wrapper::pos() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::View::pos();
}
void View_wrapper::raise()
{
    // tag=1000
    if (m_raiseCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_raiseCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
// tag=1009
void View_wrapper::raise_nocallback()
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::raiseAndActivate()
{
    // tag=1000
    if (m_raiseAndActivateCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_raiseAndActivateCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
// tag=1009
void View_wrapper::raiseAndActivate_nocallback()
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
QRect View_wrapper::rect() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::View::rect();
}
void View_wrapper::releaseKeyboard()
{
    // tag=1000
    if (m_releaseKeyboardCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_releaseKeyboardCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
// tag=1009
void View_wrapper::releaseKeyboard_nocallback()
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::releaseMouse()
{
    // tag=1000
    if (m_releaseMouseCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_releaseMouseCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
// tag=1009
void View_wrapper::releaseMouse_nocallback()
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::resize(QSize arg__1)
{
    // tag=1000

    // tag=1004
    ::KDDockWidgets::View::resize(arg__1);
}
void View_wrapper::resize(int w, int h)
{
    // tag=1000

    // tag=1004
    ::KDDockWidgets::View::resize(w, h);
}
void View_wrapper::setAboutToBeDestroyed()
{
    // tag=1000

    // tag=1004
    ::KDDockWidgets::View::setAboutToBeDestroyed();
}
void View_wrapper::setCursor(Qt::CursorShape arg__1)
{
    // tag=1000
    if (m_setCursorCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setCursorCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
// tag=1009
void View_wrapper::setCursor_nocallback(Qt::CursorShape arg__1)
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::setFixedHeight(int arg__1)
{
    // tag=1000
    if (m_setFixedHeightCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setFixedHeightCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
// tag=1009
void View_wrapper::setFixedHeight_nocallback(int arg__1)
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::setFixedWidth(int arg__1)
{
    // tag=1000
    if (m_setFixedWidthCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setFixedWidthCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
// tag=1009
void View_wrapper::setFixedWidth_nocallback(int arg__1)
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::setGeometry(QRect arg__1)
{
    // tag=1000
    if (m_setGeometryCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setGeometryCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
// tag=1009
void View_wrapper::setGeometry_nocallback(QRect arg__1)
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::setHeight(int height)
{
    // tag=1000
    if (m_setHeightCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setHeightCallback(const_cast<void *>(thisPtr), height);
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
// tag=1009
void View_wrapper::setHeight_nocallback(int height)
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::setMaximumSize(QSize sz)
{
    // tag=1000
    if (m_setMaximumSizeCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setMaximumSizeCallback(const_cast<void *>(thisPtr), sz);
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
// tag=1009
void View_wrapper::setMaximumSize_nocallback(QSize sz)
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::setMinimumSize(QSize arg__1)
{
    // tag=1000
    if (m_setMinimumSizeCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setMinimumSizeCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
// tag=1009
void View_wrapper::setMinimumSize_nocallback(QSize arg__1)
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::setMouseTracking(bool arg__1)
{
    // tag=1000
    if (m_setMouseTrackingCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setMouseTrackingCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
// tag=1009
void View_wrapper::setMouseTracking_nocallback(bool arg__1)
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::setObjectName(const QString &arg__1)
{
    // tag=1000
    if (m_setObjectNameCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setObjectNameCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
// tag=1009
void View_wrapper::setObjectName_nocallback(const QString &arg__1)
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::setParent(KDDockWidgets::View *arg__1)
{
    // tag=1000
    if (m_setParentCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setParentCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
// tag=1009
void View_wrapper::setParent_nocallback(KDDockWidgets::View *arg__1)
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::setSize(QSize arg__1)
{
    // tag=1000

    // tag=1004
    ::KDDockWidgets::View::setSize(arg__1);
}
void View_wrapper::setSize(int width, int height)
{
    // tag=1000
    if (m_setSize_2Callback) {
        // tag=1001
        const void *thisPtr = this;
        m_setSize_2Callback(const_cast<void *>(thisPtr), width, height);
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
// tag=1009
void View_wrapper::setSize_nocallback(int width, int height)
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::setVisible(bool arg__1)
{
    // tag=1000
    if (m_setVisibleCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setVisibleCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
// tag=1009
void View_wrapper::setVisible_nocallback(bool arg__1)
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::setWidth(int width)
{
    // tag=1000
    if (m_setWidthCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setWidthCallback(const_cast<void *>(thisPtr), width);
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
// tag=1009
void View_wrapper::setWidth_nocallback(int width)
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::setWindowOpacity(double arg__1)
{
    // tag=1000
    if (m_setWindowOpacityCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setWindowOpacityCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
// tag=1009
void View_wrapper::setWindowOpacity_nocallback(double arg__1)
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::setWindowTitle(const QString &title)
{
    // tag=1000
    if (m_setWindowTitleCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setWindowTitleCallback(const_cast<void *>(thisPtr), title);
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
// tag=1009
void View_wrapper::setWindowTitle_nocallback(const QString &title)
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::setZOrder(int arg__1)
{
    // tag=1000
    if (m_setZOrderCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_setZOrderCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        // tag=1002
        ::KDDockWidgets::View::setZOrder(arg__1);
    }
}
// tag=1009
void View_wrapper::setZOrder_nocallback(int arg__1)
{
    // tag=1003
    ::KDDockWidgets::View::setZOrder(arg__1);
}
void View_wrapper::show()
{
    // tag=1000
    if (m_showCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_showCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
// tag=1009
void View_wrapper::show_nocallback()
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::showMaximized()
{
    // tag=1000
    if (m_showMaximizedCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_showMaximizedCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
// tag=1009
void View_wrapper::showMaximized_nocallback()
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::showMinimized()
{
    // tag=1000
    if (m_showMinimizedCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_showMinimizedCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
// tag=1009
void View_wrapper::showMinimized_nocallback()
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void View_wrapper::showNormal()
{
    // tag=1000
    if (m_showNormalCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_showNormalCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
// tag=1009
void View_wrapper::showNormal_nocallback()
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
QSize View_wrapper::size() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::View::size();
}
QSize View_wrapper::sizeHint() const
{
    // tag=1000
    if (m_sizeHintCallback) {
        // tag=1001
        const void *thisPtr = this;
        return *m_sizeHintCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        return ::KDDockWidgets::View::sizeHint();
    }
}
// tag=1009
QSize View_wrapper::sizeHint_nocallback() const
{
    // tag=1003
    return ::KDDockWidgets::View::sizeHint();
}
KDDockWidgets::Type View_wrapper::type() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::View::type();
}
void View_wrapper::update()
{
    // tag=1000
    if (m_updateCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_updateCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
// tag=1009
void View_wrapper::update_nocallback()
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
int View_wrapper::width() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::View::width();
}
QRect View_wrapper::windowGeometry() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::View::windowGeometry();
}
int View_wrapper::x() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::View::x();
}
int View_wrapper::y() const
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::View::y();
}

// tag=1005
View_wrapper::~View_wrapper()
{
}

}
// tag=1013
static KDDockWidgets::View *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::View *>(ptr);
}
// tag=1014
static KDDockWidgetsBindings_wrappersNS::View_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(ptr);
}
extern "C" {

// tag=1049
void c_KDDockWidgets__View_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper *>(cppObj);
}
void *c_KDDockWidgets__View__constructor_Controller_Type(void *controller_, int arg__2)
{
    auto controller = reinterpret_cast<KDDockWidgets::Controller *>(controller_);
    // tag=1056
    auto ptr = new KDDockWidgetsBindings_wrappersNS::View_wrapper(controller, static_cast<KDDockWidgets::Type>(arg__2));
    return reinterpret_cast<void *>(ptr);
}

// tag=1050
// aboutToBeDestroyed() const
bool c_KDDockWidgets__View__aboutToBeDestroyed(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->aboutToBeDestroyed();
}

// tag=1050
// activateWindow()
void c_KDDockWidgets__View__activateWindow(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->activateWindow_nocallback();} else {    return targetPtr->activateWindow();} }();
}

// tag=1050
// asDropAreaController() const
void *c_KDDockWidgets__View__asDropAreaController(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->asDropAreaController();
}

// tag=1050
// asLayout() const
void *c_KDDockWidgets__View__asLayout(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->asLayout();
}

// tag=1050
// boundedMaxSize(QSize min, QSize max)
void *c_static_KDDockWidgets__View__boundedMaxSize_QSize_QSize(void *min_, void *max_)
{
    auto &min = *reinterpret_cast<QSize *>(min_);
    auto &max = *reinterpret_cast<QSize *>(max_);
    return
        // tag=1068

        // tag=1072
        new Dartagnan::ValueWrapper<QSize> { KDDockWidgetsBindings_wrappersNS::View_wrapper::boundedMaxSize(min, max) };
}

// tag=1050
// close()
bool c_KDDockWidgets__View__close(void *thisObj)
{
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->close_nocallback();} else {    return targetPtr->close();} }();
}

// tag=1050
// closeRootView()
void c_KDDockWidgets__View__closeRootView(void *thisObj)
{
    // tag=1010
    fromPtr(thisObj)->closeRootView();
}

// tag=1050
// controller() const
void *c_KDDockWidgets__View__controller(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->controller();
}

// tag=1050
// createPlatformWindow()
void c_KDDockWidgets__View__createPlatformWindow(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->createPlatformWindow_nocallback();} else {    return targetPtr->createPlatformWindow();} }();
}

// tag=1050
// equals(const KDDockWidgets::View * one, const KDDockWidgets::View * two)
bool c_static_KDDockWidgets__View__equals_View_View(void *one_, void *two_)
{
    auto one = reinterpret_cast<KDDockWidgets::View *>(one_);
    auto two = reinterpret_cast<KDDockWidgets::View *>(two_);
    return
        // tag=1068
        KDDockWidgetsBindings_wrappersNS::View_wrapper::equals(one, two);
}

// tag=1050
// equals(const KDDockWidgets::View * other) const
bool c_KDDockWidgets__View__equals_View(void *thisObj, void *other_)
{
    auto other = reinterpret_cast<KDDockWidgets::View *>(other_);
    return
        // tag=1010
        fromPtr(thisObj)->equals(other);
}

// tag=1050
// firstParentOfType(KDDockWidgets::Type arg__1) const
void *c_KDDockWidgets__View__firstParentOfType_Type(void *thisObj, int arg__1)
{
    return
        // tag=1010
        fromPtr(thisObj)->firstParentOfType(static_cast<KDDockWidgets::Type>(arg__1));
}

// tag=1050
// firstParentOfType(KDDockWidgets::View * view, KDDockWidgets::Type arg__2)
void *c_static_KDDockWidgets__View__firstParentOfType_View_Type(void *view_, int arg__2)
{
    auto view = reinterpret_cast<KDDockWidgets::View *>(view_);
    return
        // tag=1068
        KDDockWidgetsBindings_wrappersNS::View_wrapper::firstParentOfType(view, static_cast<KDDockWidgets::Type>(arg__2));
}

// tag=1050
// flags() const
int c_KDDockWidgets__View__flags(void *thisObj)
{
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->flags_nocallback();} else {    return targetPtr->flags();} }();
}

// tag=1050
// free()
void c_KDDockWidgets__View__free(void *thisObj)
{
    // tag=1010
    fromPtr(thisObj)->free();
}

// tag=1050
// free_impl()
void c_KDDockWidgets__View__free_impl(void *thisObj)
{
    // tag=1011

    // tag=1074
    fromWrapperPtr(thisObj)->free_impl_nocallback();
}

// tag=1050
// freed() const
bool c_KDDockWidgets__View__freed(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->freed();
}

// tag=1050
// geometry() const
void *c_KDDockWidgets__View__geometry(void *thisObj)
{
    return
        // tag=1016

        // tag=1072
        new Dartagnan::ValueWrapper<QRect> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->geometry_nocallback();} else {    return targetPtr->geometry();} }() };
}

// tag=1050
// globalGeometry() const
void *c_KDDockWidgets__View__globalGeometry(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QRect> { fromPtr(thisObj)->globalGeometry() };
}

// tag=1050
// grabMouse()
void c_KDDockWidgets__View__grabMouse(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->grabMouse_nocallback();} else {    return targetPtr->grabMouse();} }();
}

// tag=1050
// hardcodedMinimumSize()
void *c_static_KDDockWidgets__View__hardcodedMinimumSize()
{
    return
        // tag=1068

        // tag=1072
        new Dartagnan::ValueWrapper<QSize> { KDDockWidgetsBindings_wrappersNS::View_wrapper::hardcodedMinimumSize() };
}

// tag=1050
// hasFocus() const
bool c_KDDockWidgets__View__hasFocus(void *thisObj)
{
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->hasFocus_nocallback();} else {    return targetPtr->hasFocus();} }();
}

// tag=1050
// height() const
int c_KDDockWidgets__View__height(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->height();
}

// tag=1050
// hide()
void c_KDDockWidgets__View__hide(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->hide_nocallback();} else {    return targetPtr->hide();} }();
}

// tag=1050
// id() const
void *c_KDDockWidgets__View__id(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QString> { fromPtr(thisObj)->id() };
}

// tag=1050
// inDtor() const
bool c_KDDockWidgets__View__inDtor(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->inDtor();
}

// tag=1050
// init()
void c_KDDockWidgets__View__init(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->init_nocallback();} else {    return targetPtr->init();} }();
}

// tag=1050
// isActiveWindow() const
bool c_KDDockWidgets__View__isActiveWindow(void *thisObj)
{
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isActiveWindow_nocallback();} else {    return targetPtr->isActiveWindow();} }();
}

// tag=1050
// isMaximized() const
bool c_KDDockWidgets__View__isMaximized(void *thisObj)
{
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isMaximized_nocallback();} else {    return targetPtr->isMaximized();} }();
}

// tag=1050
// isMinimized() const
bool c_KDDockWidgets__View__isMinimized(void *thisObj)
{
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isMinimized_nocallback();} else {    return targetPtr->isMinimized();} }();
}

// tag=1050
// isNull() const
bool c_KDDockWidgets__View__isNull(void *thisObj)
{
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isNull_nocallback();} else {    return targetPtr->isNull();} }();
}

// tag=1050
// isRootView() const
bool c_KDDockWidgets__View__isRootView(void *thisObj)
{
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isRootView_nocallback();} else {    return targetPtr->isRootView();} }();
}

// tag=1050
// isVisible() const
bool c_KDDockWidgets__View__isVisible(void *thisObj)
{
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isVisible_nocallback();} else {    return targetPtr->isVisible();} }();
}

// tag=1050
// mapFromGlobal(QPoint arg__1) const
void *c_KDDockWidgets__View__mapFromGlobal_QPoint(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QPoint *>(arg__1_);
    return
        // tag=1016

        // tag=1072
        new Dartagnan::ValueWrapper<QPoint> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->mapFromGlobal_nocallback(arg__1);} else {    return targetPtr->mapFromGlobal(arg__1);} }() };
}

// tag=1050
// mapTo(KDDockWidgets::View * arg__1, QPoint arg__2) const
void *c_KDDockWidgets__View__mapTo_View_QPoint(void *thisObj, void *arg__1_, void *arg__2_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::View *>(arg__1_);
    auto &arg__2 = *reinterpret_cast<QPoint *>(arg__2_);
    return
        // tag=1016

        // tag=1072
        new Dartagnan::ValueWrapper<QPoint> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->mapTo_nocallback(arg__1,arg__2);} else {    return targetPtr->mapTo(arg__1,arg__2);} }() };
}

// tag=1050
// mapToGlobal(QPoint arg__1) const
void *c_KDDockWidgets__View__mapToGlobal_QPoint(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QPoint *>(arg__1_);
    return
        // tag=1016

        // tag=1072
        new Dartagnan::ValueWrapper<QPoint> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->mapToGlobal_nocallback(arg__1);} else {    return targetPtr->mapToGlobal(arg__1);} }() };
}

// tag=1050
// maxSizeHint() const
void *c_KDDockWidgets__View__maxSizeHint(void *thisObj)
{
    return
        // tag=1016

        // tag=1072
        new Dartagnan::ValueWrapper<QSize> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->maxSizeHint_nocallback();} else {    return targetPtr->maxSizeHint();} }() };
}

// tag=1050
// maximumSize() const
void *c_KDDockWidgets__View__maximumSize(void *thisObj)
{
    return
        // tag=1016

        // tag=1072
        new Dartagnan::ValueWrapper<QSize> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->maximumSize_nocallback();} else {    return targetPtr->maximumSize();} }() };
}

// tag=1050
// minSize() const
void *c_KDDockWidgets__View__minSize(void *thisObj)
{
    return
        // tag=1016

        // tag=1072
        new Dartagnan::ValueWrapper<QSize> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->minSize_nocallback();} else {    return targetPtr->minSize();} }() };
}

// tag=1050
// minimumHeight() const
int c_KDDockWidgets__View__minimumHeight(void *thisObj)
{
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->minimumHeight_nocallback();} else {    return targetPtr->minimumHeight();} }();
}

// tag=1050
// minimumWidth() const
int c_KDDockWidgets__View__minimumWidth(void *thisObj)
{
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->minimumWidth_nocallback();} else {    return targetPtr->minimumWidth();} }();
}

// tag=1050
// move(QPoint arg__1)
void c_KDDockWidgets__View__move_QPoint(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QPoint *>(arg__1_);
    // tag=1010
    fromPtr(thisObj)->move(arg__1);
}

// tag=1050
// move(int x, int y)
void c_KDDockWidgets__View__move_int_int(void *thisObj, int x, int y)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->move_nocallback(x,y);} else {    return targetPtr->move(x,y);} }();
}

// tag=1050
// normalGeometry() const
void *c_KDDockWidgets__View__normalGeometry(void *thisObj)
{
    return
        // tag=1016

        // tag=1072
        new Dartagnan::ValueWrapper<QRect> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->normalGeometry_nocallback();} else {    return targetPtr->normalGeometry();} }() };
}

// tag=1050
// objectName() const
void *c_KDDockWidgets__View__objectName(void *thisObj)
{
    return
        // tag=1016

        // tag=1072
        new Dartagnan::ValueWrapper<QString> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->objectName_nocallback();} else {    return targetPtr->objectName();} }() };
}

// tag=1050
// onResize(QSize newSize)
bool c_KDDockWidgets__View__onResize_QSize(void *thisObj, void *newSize_)
{
    auto &newSize = *reinterpret_cast<QSize *>(newSize_);
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->onResize_nocallback(newSize);} else {    return targetPtr->onResize(newSize);} }();
}

// tag=1050
// parentSize() const
void *c_KDDockWidgets__View__parentSize(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QSize> { fromPtr(thisObj)->parentSize() };
}

// tag=1050
// pos() const
void *c_KDDockWidgets__View__pos(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QPoint> { fromPtr(thisObj)->pos() };
}

// tag=1050
// raise()
void c_KDDockWidgets__View__raise(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->raise_nocallback();} else {    return targetPtr->raise();} }();
}

// tag=1050
// raiseAndActivate()
void c_KDDockWidgets__View__raiseAndActivate(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->raiseAndActivate_nocallback();} else {    return targetPtr->raiseAndActivate();} }();
}

// tag=1050
// rect() const
void *c_KDDockWidgets__View__rect(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QRect> { fromPtr(thisObj)->rect() };
}

// tag=1050
// releaseKeyboard()
void c_KDDockWidgets__View__releaseKeyboard(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->releaseKeyboard_nocallback();} else {    return targetPtr->releaseKeyboard();} }();
}

// tag=1050
// releaseMouse()
void c_KDDockWidgets__View__releaseMouse(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->releaseMouse_nocallback();} else {    return targetPtr->releaseMouse();} }();
}

// tag=1050
// resize(QSize arg__1)
void c_KDDockWidgets__View__resize_QSize(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QSize *>(arg__1_);
    // tag=1010
    fromPtr(thisObj)->resize(arg__1);
}

// tag=1050
// resize(int w, int h)
void c_KDDockWidgets__View__resize_int_int(void *thisObj, int w, int h)
{
    // tag=1010
    fromPtr(thisObj)->resize(w, h);
}

// tag=1050
// setAboutToBeDestroyed()
void c_KDDockWidgets__View__setAboutToBeDestroyed(void *thisObj)
{
    // tag=1010
    fromPtr(thisObj)->setAboutToBeDestroyed();
}

// tag=1050
// setCursor(Qt::CursorShape arg__1)
void c_KDDockWidgets__View__setCursor_CursorShape(void *thisObj, int arg__1)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setCursor_nocallback(static_cast<Qt::CursorShape>(arg__1));} else {    return targetPtr->setCursor(static_cast<Qt::CursorShape>(arg__1));} }();
}

// tag=1050
// setFixedHeight(int arg__1)
void c_KDDockWidgets__View__setFixedHeight_int(void *thisObj, int arg__1)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setFixedHeight_nocallback(arg__1);} else {    return targetPtr->setFixedHeight(arg__1);} }();
}

// tag=1050
// setFixedWidth(int arg__1)
void c_KDDockWidgets__View__setFixedWidth_int(void *thisObj, int arg__1)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setFixedWidth_nocallback(arg__1);} else {    return targetPtr->setFixedWidth(arg__1);} }();
}

// tag=1050
// setGeometry(QRect arg__1)
void c_KDDockWidgets__View__setGeometry_QRect(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QRect *>(arg__1_);
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setGeometry_nocallback(arg__1);} else {    return targetPtr->setGeometry(arg__1);} }();
}

// tag=1050
// setHeight(int height)
void c_KDDockWidgets__View__setHeight_int(void *thisObj, int height)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setHeight_nocallback(height);} else {    return targetPtr->setHeight(height);} }();
}

// tag=1050
// setMaximumSize(QSize sz)
void c_KDDockWidgets__View__setMaximumSize_QSize(void *thisObj, void *sz_)
{
    auto &sz = *reinterpret_cast<QSize *>(sz_);
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setMaximumSize_nocallback(sz);} else {    return targetPtr->setMaximumSize(sz);} }();
}

// tag=1050
// setMinimumSize(QSize arg__1)
void c_KDDockWidgets__View__setMinimumSize_QSize(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QSize *>(arg__1_);
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setMinimumSize_nocallback(arg__1);} else {    return targetPtr->setMinimumSize(arg__1);} }();
}

// tag=1050
// setMouseTracking(bool arg__1)
void c_KDDockWidgets__View__setMouseTracking_bool(void *thisObj, bool arg__1)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setMouseTracking_nocallback(arg__1);} else {    return targetPtr->setMouseTracking(arg__1);} }();
}

// tag=1050
// setObjectName(const QString & arg__1)
void c_KDDockWidgets__View__setObjectName_QString(void *thisObj, const char *arg__1_)
{
    const auto arg__1 = QString::fromUtf8(arg__1_);
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setObjectName_nocallback(arg__1);} else {    return targetPtr->setObjectName(arg__1);} }();
}

// tag=1050
// setParent(KDDockWidgets::View * arg__1)
void c_KDDockWidgets__View__setParent_View(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<KDDockWidgets::View *>(arg__1_);
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setParent_nocallback(arg__1);} else {    return targetPtr->setParent(arg__1);} }();
}

// tag=1050
// setSize(QSize arg__1)
void c_KDDockWidgets__View__setSize_QSize(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QSize *>(arg__1_);
    // tag=1010
    fromPtr(thisObj)->setSize(arg__1);
}

// tag=1050
// setSize(int width, int height)
void c_KDDockWidgets__View__setSize_int_int(void *thisObj, int width, int height)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setSize_nocallback(width,height);} else {    return targetPtr->setSize(width,height);} }();
}

// tag=1050
// setVisible(bool arg__1)
void c_KDDockWidgets__View__setVisible_bool(void *thisObj, bool arg__1)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setVisible_nocallback(arg__1);} else {    return targetPtr->setVisible(arg__1);} }();
}

// tag=1050
// setWidth(int width)
void c_KDDockWidgets__View__setWidth_int(void *thisObj, int width)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setWidth_nocallback(width);} else {    return targetPtr->setWidth(width);} }();
}

// tag=1050
// setWindowOpacity(double arg__1)
void c_KDDockWidgets__View__setWindowOpacity_double(void *thisObj, double arg__1)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setWindowOpacity_nocallback(arg__1);} else {    return targetPtr->setWindowOpacity(arg__1);} }();
}

// tag=1050
// setWindowTitle(const QString & title)
void c_KDDockWidgets__View__setWindowTitle_QString(void *thisObj, const char *title_)
{
    const auto title = QString::fromUtf8(title_);
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setWindowTitle_nocallback(title);} else {    return targetPtr->setWindowTitle(title);} }();
}

// tag=1050
// setZOrder(int arg__1)
void c_KDDockWidgets__View__setZOrder_int(void *thisObj, int arg__1)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setZOrder_nocallback(arg__1);} else {    return targetPtr->setZOrder(arg__1);} }();
}

// tag=1050
// show()
void c_KDDockWidgets__View__show(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->show_nocallback();} else {    return targetPtr->show();} }();
}

// tag=1050
// showMaximized()
void c_KDDockWidgets__View__showMaximized(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->showMaximized_nocallback();} else {    return targetPtr->showMaximized();} }();
}

// tag=1050
// showMinimized()
void c_KDDockWidgets__View__showMinimized(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->showMinimized_nocallback();} else {    return targetPtr->showMinimized();} }();
}

// tag=1050
// showNormal()
void c_KDDockWidgets__View__showNormal(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->showNormal_nocallback();} else {    return targetPtr->showNormal();} }();
}

// tag=1050
// size() const
void *c_KDDockWidgets__View__size(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QSize> { fromPtr(thisObj)->size() };
}

// tag=1050
// sizeHint() const
void *c_KDDockWidgets__View__sizeHint(void *thisObj)
{
    return
        // tag=1016

        // tag=1072
        new Dartagnan::ValueWrapper<QSize> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->sizeHint_nocallback();} else {    return targetPtr->sizeHint();} }() };
}

// tag=1050
// type() const
int c_KDDockWidgets__View__type(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->type();
}

// tag=1050
// update()
void c_KDDockWidgets__View__update(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->update_nocallback();} else {    return targetPtr->update();} }();
}

// tag=1050
// width() const
int c_KDDockWidgets__View__width(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->width();
}

// tag=1050
// windowGeometry() const
void *c_KDDockWidgets__View__windowGeometry(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QRect> { fromPtr(thisObj)->windowGeometry() };
}

// tag=1050
// x() const
int c_KDDockWidgets__View__x(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->x();
}

// tag=1050
// y() const
int c_KDDockWidgets__View__y(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->y();
}
void c_KDDockWidgets__View__destructor(void *thisObj)
{

    // tag=1055
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__View__registerVirtualMethodCallback(void *ptr, void *callback, int methodId)
{
    // tag=1048
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 814:
        wrapper->m_activateWindowCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_activateWindow>(callback);
        break;
    case 818:
        wrapper->m_closeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_close>(callback);
        break;
    case 821:
        wrapper->m_createPlatformWindowCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_createPlatformWindow>(callback);
        break;
    case 826:
        wrapper->m_flagsCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_flags>(callback);
        break;
    case 828:
        wrapper->m_free_implCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_free_impl>(callback);
        break;
    case 830:
        wrapper->m_geometryCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_geometry>(callback);
        break;
    case 832:
        wrapper->m_grabMouseCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_grabMouse>(callback);
        break;
    case 835:
        wrapper->m_hasFocusCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_hasFocus>(callback);
        break;
    case 837:
        wrapper->m_hideCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_hide>(callback);
        break;
    case 840:
        wrapper->m_initCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_init>(callback);
        break;
    case 842:
        wrapper->m_isActiveWindowCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_isActiveWindow>(callback);
        break;
    case 843:
        wrapper->m_isMaximizedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_isMaximized>(callback);
        break;
    case 844:
        wrapper->m_isMinimizedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_isMinimized>(callback);
        break;
    case 845:
        wrapper->m_isNullCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_isNull>(callback);
        break;
    case 846:
        wrapper->m_isRootViewCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_isRootView>(callback);
        break;
    case 847:
        wrapper->m_isVisibleCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_isVisible>(callback);
        break;
    case 848:
        wrapper->m_mapFromGlobalCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_mapFromGlobal>(callback);
        break;
    case 849:
        wrapper->m_mapToCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_mapTo>(callback);
        break;
    case 850:
        wrapper->m_mapToGlobalCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_mapToGlobal>(callback);
        break;
    case 851:
        wrapper->m_maxSizeHintCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_maxSizeHint>(callback);
        break;
    case 852:
        wrapper->m_maximumSizeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_maximumSize>(callback);
        break;
    case 853:
        wrapper->m_minSizeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_minSize>(callback);
        break;
    case 854:
        wrapper->m_minimumHeightCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_minimumHeight>(callback);
        break;
    case 855:
        wrapper->m_minimumWidthCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_minimumWidth>(callback);
        break;
    case 857:
        wrapper->m_move_2Callback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_move_2>(callback);
        break;
    case 858:
        wrapper->m_normalGeometryCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_normalGeometry>(callback);
        break;
    case 859:
        wrapper->m_objectNameCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_objectName>(callback);
        break;
    case 860:
        wrapper->m_onResizeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_onResize>(callback);
        break;
    case 863:
        wrapper->m_raiseCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_raise>(callback);
        break;
    case 864:
        wrapper->m_raiseAndActivateCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_raiseAndActivate>(callback);
        break;
    case 866:
        wrapper->m_releaseKeyboardCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_releaseKeyboard>(callback);
        break;
    case 867:
        wrapper->m_releaseMouseCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_releaseMouse>(callback);
        break;
    case 871:
        wrapper->m_setCursorCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_setCursor>(callback);
        break;
    case 872:
        wrapper->m_setFixedHeightCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_setFixedHeight>(callback);
        break;
    case 873:
        wrapper->m_setFixedWidthCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_setFixedWidth>(callback);
        break;
    case 874:
        wrapper->m_setGeometryCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_setGeometry>(callback);
        break;
    case 875:
        wrapper->m_setHeightCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_setHeight>(callback);
        break;
    case 876:
        wrapper->m_setMaximumSizeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_setMaximumSize>(callback);
        break;
    case 877:
        wrapper->m_setMinimumSizeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_setMinimumSize>(callback);
        break;
    case 878:
        wrapper->m_setMouseTrackingCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_setMouseTracking>(callback);
        break;
    case 879:
        wrapper->m_setObjectNameCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_setObjectName>(callback);
        break;
    case 880:
        wrapper->m_setParentCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_setParent>(callback);
        break;
    case 882:
        wrapper->m_setSize_2Callback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_setSize_2>(callback);
        break;
    case 883:
        wrapper->m_setVisibleCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_setVisible>(callback);
        break;
    case 884:
        wrapper->m_setWidthCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_setWidth>(callback);
        break;
    case 885:
        wrapper->m_setWindowOpacityCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_setWindowOpacity>(callback);
        break;
    case 886:
        wrapper->m_setWindowTitleCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_setWindowTitle>(callback);
        break;
    case 887:
        wrapper->m_setZOrderCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_setZOrder>(callback);
        break;
    case 888:
        wrapper->m_showCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_show>(callback);
        break;
    case 889:
        wrapper->m_showMaximizedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_showMaximized>(callback);
        break;
    case 890:
        wrapper->m_showMinimizedCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_showMinimized>(callback);
        break;
    case 891:
        wrapper->m_showNormalCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_showNormal>(callback);
        break;
    case 893:
        wrapper->m_sizeHintCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_sizeHint>(callback);
        break;
    case 895:
        wrapper->m_updateCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::View_wrapper::Callback_update>(callback);
        break;
    }
}
}

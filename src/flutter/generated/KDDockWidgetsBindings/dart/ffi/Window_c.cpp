/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "Window_c.h"


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
Window_wrapper::Window_wrapper()
    : ::KDDockWidgets::flutter::Window()
{
}
void Window_wrapper::destroy()
{
    if (m_destroyCallback) {
        const void *thisPtr = this;
        m_destroyCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::Window::destroy();
    }
}
void Window_wrapper::destroy_nocallback()
{
    ::KDDockWidgets::flutter::Window::destroy();
}
QRect Window_wrapper::frameGeometry() const
{
    if (m_frameGeometryCallback) {
        const void *thisPtr = this;
        return *m_frameGeometryCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::Window::frameGeometry();
    }
}
QRect Window_wrapper::frameGeometry_nocallback() const
{
    return ::KDDockWidgets::flutter::Window::frameGeometry();
}
QPoint Window_wrapper::fromNativePixels(QPoint arg__1) const
{
    if (m_fromNativePixelsCallback) {
        const void *thisPtr = this;
        return *m_fromNativePixelsCallback(const_cast<void *>(thisPtr), &arg__1);
    } else {
        return ::KDDockWidgets::flutter::Window::fromNativePixels(arg__1);
    }
}
QPoint Window_wrapper::fromNativePixels_nocallback(QPoint arg__1) const
{
    return ::KDDockWidgets::flutter::Window::fromNativePixels(arg__1);
}
QRect Window_wrapper::geometry() const
{
    if (m_geometryCallback) {
        const void *thisPtr = this;
        return *m_geometryCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::Window::geometry();
    }
}
QRect Window_wrapper::geometry_nocallback() const
{
    return ::KDDockWidgets::flutter::Window::geometry();
}
bool Window_wrapper::isActive() const
{
    if (m_isActiveCallback) {
        const void *thisPtr = this;
        return m_isActiveCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::Window::isActive();
    }
}
bool Window_wrapper::isActive_nocallback() const
{
    return ::KDDockWidgets::flutter::Window::isActive();
}
bool Window_wrapper::isFullScreen() const
{
    if (m_isFullScreenCallback) {
        const void *thisPtr = this;
        return m_isFullScreenCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::Window::isFullScreen();
    }
}
bool Window_wrapper::isFullScreen_nocallback() const
{
    return ::KDDockWidgets::flutter::Window::isFullScreen();
}
bool Window_wrapper::isVisible() const
{
    if (m_isVisibleCallback) {
        const void *thisPtr = this;
        return m_isVisibleCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::Window::isVisible();
    }
}
bool Window_wrapper::isVisible_nocallback() const
{
    return ::KDDockWidgets::flutter::Window::isVisible();
}
QPoint Window_wrapper::mapFromGlobal(QPoint globalPos) const
{
    if (m_mapFromGlobalCallback) {
        const void *thisPtr = this;
        return *m_mapFromGlobalCallback(const_cast<void *>(thisPtr), &globalPos);
    } else {
        return ::KDDockWidgets::flutter::Window::mapFromGlobal(globalPos);
    }
}
QPoint Window_wrapper::mapFromGlobal_nocallback(QPoint globalPos) const
{
    return ::KDDockWidgets::flutter::Window::mapFromGlobal(globalPos);
}
QPoint Window_wrapper::mapToGlobal(QPoint localPos) const
{
    if (m_mapToGlobalCallback) {
        const void *thisPtr = this;
        return *m_mapToGlobalCallback(const_cast<void *>(thisPtr), &localPos);
    } else {
        return ::KDDockWidgets::flutter::Window::mapToGlobal(localPos);
    }
}
QPoint Window_wrapper::mapToGlobal_nocallback(QPoint localPos) const
{
    return ::KDDockWidgets::flutter::Window::mapToGlobal(localPos);
}
QSize Window_wrapper::maxSize() const
{
    if (m_maxSizeCallback) {
        const void *thisPtr = this;
        return *m_maxSizeCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::Window::maxSize();
    }
}
QSize Window_wrapper::maxSize_nocallback() const
{
    return ::KDDockWidgets::flutter::Window::maxSize();
}
QSize Window_wrapper::minSize() const
{
    if (m_minSizeCallback) {
        const void *thisPtr = this;
        return *m_minSizeCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::Window::minSize();
    }
}
QSize Window_wrapper::minSize_nocallback() const
{
    return ::KDDockWidgets::flutter::Window::minSize();
}
void Window_wrapper::resize(int width, int height)
{
    if (m_resizeCallback) {
        const void *thisPtr = this;
        m_resizeCallback(const_cast<void *>(thisPtr), width, height);
    } else {
        ::KDDockWidgets::flutter::Window::resize(width, height);
    }
}
void Window_wrapper::resize_nocallback(int width, int height)
{
    ::KDDockWidgets::flutter::Window::resize(width, height);
}
void Window_wrapper::setFramePosition(QPoint targetPos)
{
    if (m_setFramePositionCallback) {
        const void *thisPtr = this;
        m_setFramePositionCallback(const_cast<void *>(thisPtr), &targetPos);
    } else {
        ::KDDockWidgets::flutter::Window::setFramePosition(targetPos);
    }
}
void Window_wrapper::setFramePosition_nocallback(QPoint targetPos)
{
    ::KDDockWidgets::flutter::Window::setFramePosition(targetPos);
}
void Window_wrapper::setGeometry(QRect arg__1) const
{
    if (m_setGeometryCallback) {
        const void *thisPtr = this;
        m_setGeometryCallback(const_cast<void *>(thisPtr), &arg__1);
    } else {
        ::KDDockWidgets::flutter::Window::setGeometry(arg__1);
    }
}
void Window_wrapper::setGeometry_nocallback(QRect arg__1) const
{
    ::KDDockWidgets::flutter::Window::setGeometry(arg__1);
}
void Window_wrapper::setVisible(bool arg__1)
{
    if (m_setVisibleCallback) {
        const void *thisPtr = this;
        m_setVisibleCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        ::KDDockWidgets::flutter::Window::setVisible(arg__1);
    }
}
void Window_wrapper::setVisible_nocallback(bool arg__1)
{
    ::KDDockWidgets::flutter::Window::setVisible(arg__1);
}
bool Window_wrapper::supportsHonouringLayoutMinSize() const
{
    if (m_supportsHonouringLayoutMinSizeCallback) {
        const void *thisPtr = this;
        return m_supportsHonouringLayoutMinSizeCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::Window::supportsHonouringLayoutMinSize();
    }
}
bool Window_wrapper::supportsHonouringLayoutMinSize_nocallback() const
{
    return ::KDDockWidgets::flutter::Window::supportsHonouringLayoutMinSize();
}
Window_wrapper::~Window_wrapper()
{
}

}
static KDDockWidgets::flutter::Window *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::flutter::Window *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::Window_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Window_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__flutter__Window_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Window_wrapper *>(cppObj);
}
void *c_KDDockWidgets__flutter__Window__constructor()
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::Window_wrapper();
    return reinterpret_cast<void *>(ptr);
}
// destroy()
void c_KDDockWidgets__flutter__Window__destroy(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Window_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->destroy_nocallback();} else {    return targetPtr->destroy();} }();
}
// frameGeometry() const
void *c_KDDockWidgets__flutter__Window__frameGeometry(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QRect> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Window_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->frameGeometry_nocallback();} else {    return targetPtr->frameGeometry();} }() };
}
// fromNativePixels(QPoint arg__1) const
void *c_KDDockWidgets__flutter__Window__fromNativePixels_QPoint(void *thisObj, void *arg__1_)
{
    assert(arg__1_);
    auto &arg__1 = *reinterpret_cast<QPoint *>(arg__1_);
    return new Dartagnan::ValueWrapper<QPoint> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Window_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->fromNativePixels_nocallback(arg__1);} else {    return targetPtr->fromNativePixels(arg__1);} }() };
}
// geometry() const
void *c_KDDockWidgets__flutter__Window__geometry(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QRect> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Window_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->geometry_nocallback();} else {    return targetPtr->geometry();} }() };
}
// isActive() const
bool c_KDDockWidgets__flutter__Window__isActive(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Window_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isActive_nocallback();} else {    return targetPtr->isActive();} }();
}
// isFullScreen() const
bool c_KDDockWidgets__flutter__Window__isFullScreen(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Window_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isFullScreen_nocallback();} else {    return targetPtr->isFullScreen();} }();
}
// isVisible() const
bool c_KDDockWidgets__flutter__Window__isVisible(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Window_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isVisible_nocallback();} else {    return targetPtr->isVisible();} }();
}
// mapFromGlobal(QPoint globalPos) const
void *c_KDDockWidgets__flutter__Window__mapFromGlobal_QPoint(void *thisObj, void *globalPos_)
{
    assert(globalPos_);
    auto &globalPos = *reinterpret_cast<QPoint *>(globalPos_);
    return new Dartagnan::ValueWrapper<QPoint> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Window_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->mapFromGlobal_nocallback(globalPos);} else {    return targetPtr->mapFromGlobal(globalPos);} }() };
}
// mapToGlobal(QPoint localPos) const
void *c_KDDockWidgets__flutter__Window__mapToGlobal_QPoint(void *thisObj, void *localPos_)
{
    assert(localPos_);
    auto &localPos = *reinterpret_cast<QPoint *>(localPos_);
    return new Dartagnan::ValueWrapper<QPoint> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Window_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->mapToGlobal_nocallback(localPos);} else {    return targetPtr->mapToGlobal(localPos);} }() };
}
// maxSize() const
void *c_KDDockWidgets__flutter__Window__maxSize(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Window_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->maxSize_nocallback();} else {    return targetPtr->maxSize();} }() };
}
// minSize() const
void *c_KDDockWidgets__flutter__Window__minSize(void *thisObj)
{
    return new Dartagnan::ValueWrapper<QSize> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Window_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->minSize_nocallback();} else {    return targetPtr->minSize();} }() };
}
// resize(int width, int height)
void c_KDDockWidgets__flutter__Window__resize_int_int(void *thisObj, int width, int height)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Window_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->resize_nocallback(width,height);} else {    return targetPtr->resize(width,height);} }();
}
// setFramePosition(QPoint targetPos)
void c_KDDockWidgets__flutter__Window__setFramePosition_QPoint(void *thisObj, void *targetPos_)
{
    assert(targetPos_);
    auto &targetPos = *reinterpret_cast<QPoint *>(targetPos_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Window_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setFramePosition_nocallback(targetPos);} else {    return targetPtr->setFramePosition(targetPos);} }();
}
// setGeometry(QRect arg__1) const
void c_KDDockWidgets__flutter__Window__setGeometry_QRect(void *thisObj, void *arg__1_)
{
    assert(arg__1_);
    auto &arg__1 = *reinterpret_cast<QRect *>(arg__1_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Window_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setGeometry_nocallback(arg__1);} else {    return targetPtr->setGeometry(arg__1);} }();
}
// setVisible(bool arg__1)
void c_KDDockWidgets__flutter__Window__setVisible_bool(void *thisObj, bool arg__1)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Window_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setVisible_nocallback(arg__1);} else {    return targetPtr->setVisible(arg__1);} }();
}
// supportsHonouringLayoutMinSize() const
bool c_KDDockWidgets__flutter__Window__supportsHonouringLayoutMinSize(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::Window_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->supportsHonouringLayoutMinSize_nocallback();} else {    return targetPtr->supportsHonouringLayoutMinSize();} }();
}
void c_KDDockWidgets__flutter__Window__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__flutter__Window__registerVirtualMethodCallback(void *ptr, void *callback, int methodId)
{
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 587:
        wrapper->m_destroyCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Window_wrapper::Callback_destroy>(callback);
        break;
    case 588:
        wrapper->m_frameGeometryCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Window_wrapper::Callback_frameGeometry>(callback);
        break;
    case 589:
        wrapper->m_fromNativePixelsCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Window_wrapper::Callback_fromNativePixels>(callback);
        break;
    case 590:
        wrapper->m_geometryCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Window_wrapper::Callback_geometry>(callback);
        break;
    case 592:
        wrapper->m_isActiveCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Window_wrapper::Callback_isActive>(callback);
        break;
    case 593:
        wrapper->m_isFullScreenCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Window_wrapper::Callback_isFullScreen>(callback);
        break;
    case 594:
        wrapper->m_isVisibleCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Window_wrapper::Callback_isVisible>(callback);
        break;
    case 595:
        wrapper->m_mapFromGlobalCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Window_wrapper::Callback_mapFromGlobal>(callback);
        break;
    case 596:
        wrapper->m_mapToGlobalCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Window_wrapper::Callback_mapToGlobal>(callback);
        break;
    case 597:
        wrapper->m_maxSizeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Window_wrapper::Callback_maxSize>(callback);
        break;
    case 598:
        wrapper->m_minSizeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Window_wrapper::Callback_minSize>(callback);
        break;
    case 599:
        wrapper->m_resizeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Window_wrapper::Callback_resize>(callback);
        break;
    case 600:
        wrapper->m_setFramePositionCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Window_wrapper::Callback_setFramePosition>(callback);
        break;
    case 601:
        wrapper->m_setGeometryCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Window_wrapper::Callback_setGeometry>(callback);
        break;
    case 602:
        wrapper->m_setVisibleCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Window_wrapper::Callback_setVisible>(callback);
        break;
    case 603:
        wrapper->m_supportsHonouringLayoutMinSizeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Window_wrapper::Callback_supportsHonouringLayoutMinSize>(callback);
        break;
    }
}
}

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <Window.h>
#include <qrect.h>
#include <qpoint.h>
#include <qsize.h>

namespace KDDockWidgetsBindings_wrappersNS {
namespace KDDWBindingsFlutter {
class Window_wrapper : public ::KDDockWidgets::flutter::Window
{
public:
    ~Window_wrapper();
    virtual void destroy();
    virtual void destroy_nocallback();
    virtual QRect frameGeometry() const;
    virtual QRect frameGeometry_nocallback() const;
    virtual QPoint fromNativePixels(QPoint arg__1) const;
    virtual QPoint fromNativePixels_nocallback(QPoint arg__1) const;
    virtual QRect geometry() const;
    virtual QRect geometry_nocallback() const;
    virtual bool isActive() const;
    virtual bool isActive_nocallback() const;
    virtual bool isFullScreen() const;
    virtual bool isFullScreen_nocallback() const;
    virtual bool isVisible() const;
    virtual bool isVisible_nocallback() const;
    virtual QPoint mapFromGlobal(QPoint globalPos) const;
    virtual QPoint mapFromGlobal_nocallback(QPoint globalPos) const;
    virtual QPoint mapToGlobal(QPoint localPos) const;
    virtual QPoint mapToGlobal_nocallback(QPoint localPos) const;
    virtual QSize maxSize() const;
    virtual QSize maxSize_nocallback() const;
    virtual QSize minSize() const;
    virtual QSize minSize_nocallback() const;
    virtual void resize(int width, int height);
    virtual void resize_nocallback(int width, int height);
    virtual void setFramePosition(QPoint targetPos);
    virtual void setFramePosition_nocallback(QPoint targetPos);
    virtual void setGeometry(QRect arg__1);
    virtual void setGeometry_nocallback(QRect arg__1);
    virtual void setVisible(bool arg__1);
    virtual void setVisible_nocallback(bool arg__1);
    virtual bool supportsHonouringLayoutMinSize() const;
    virtual bool supportsHonouringLayoutMinSize_nocallback() const;
    typedef void (*Callback_destroy)(void *);
    Callback_destroy m_destroyCallback = nullptr;
    typedef QRect *(*Callback_frameGeometry)(void *);
    Callback_frameGeometry m_frameGeometryCallback = nullptr;
    typedef QPoint *(*Callback_fromNativePixels)(void *, QPoint *arg__1);
    Callback_fromNativePixels m_fromNativePixelsCallback = nullptr;
    typedef QRect *(*Callback_geometry)(void *);
    Callback_geometry m_geometryCallback = nullptr;
    typedef bool (*Callback_isActive)(void *);
    Callback_isActive m_isActiveCallback = nullptr;
    typedef bool (*Callback_isFullScreen)(void *);
    Callback_isFullScreen m_isFullScreenCallback = nullptr;
    typedef bool (*Callback_isVisible)(void *);
    Callback_isVisible m_isVisibleCallback = nullptr;
    typedef QPoint *(*Callback_mapFromGlobal)(void *, QPoint *globalPos);
    Callback_mapFromGlobal m_mapFromGlobalCallback = nullptr;
    typedef QPoint *(*Callback_mapToGlobal)(void *, QPoint *localPos);
    Callback_mapToGlobal m_mapToGlobalCallback = nullptr;
    typedef QSize *(*Callback_maxSize)(void *);
    Callback_maxSize m_maxSizeCallback = nullptr;
    typedef QSize *(*Callback_minSize)(void *);
    Callback_minSize m_minSizeCallback = nullptr;
    typedef void (*Callback_resize)(void *, int width, int height);
    Callback_resize m_resizeCallback = nullptr;
    typedef void (*Callback_setFramePosition)(void *, QPoint *targetPos);
    Callback_setFramePosition m_setFramePositionCallback = nullptr;
    typedef void (*Callback_setGeometry)(void *, QRect *arg__1);
    Callback_setGeometry m_setGeometryCallback = nullptr;
    typedef void (*Callback_setVisible)(void *, bool arg__1);
    Callback_setVisible m_setVisibleCallback = nullptr;
    typedef bool (*Callback_supportsHonouringLayoutMinSize)(void *);
    Callback_supportsHonouringLayoutMinSize m_supportsHonouringLayoutMinSizeCallback = nullptr;
};
}
}
extern "C" {
// KDDockWidgets::flutter::Window::destroy()
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Window__destroy(void *thisObj);
// KDDockWidgets::flutter::Window::frameGeometry() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__Window__frameGeometry(void *thisObj);
// KDDockWidgets::flutter::Window::fromNativePixels(QPoint arg__1) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__Window__fromNativePixels_QPoint(void *thisObj, void *arg__1_);
// KDDockWidgets::flutter::Window::geometry() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__Window__geometry(void *thisObj);
// KDDockWidgets::flutter::Window::isActive() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__flutter__Window__isActive(void *thisObj);
// KDDockWidgets::flutter::Window::isFullScreen() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__flutter__Window__isFullScreen(void *thisObj);
// KDDockWidgets::flutter::Window::isVisible() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__flutter__Window__isVisible(void *thisObj);
// KDDockWidgets::flutter::Window::mapFromGlobal(QPoint globalPos) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__Window__mapFromGlobal_QPoint(void *thisObj, void *globalPos_);
// KDDockWidgets::flutter::Window::mapToGlobal(QPoint localPos) const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__Window__mapToGlobal_QPoint(void *thisObj, void *localPos_);
// KDDockWidgets::flutter::Window::maxSize() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__Window__maxSize(void *thisObj);
// KDDockWidgets::flutter::Window::minSize() const
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__flutter__Window__minSize(void *thisObj);
// KDDockWidgets::flutter::Window::resize(int width, int height)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Window__resize_int_int(void *thisObj, int width, int height);
// KDDockWidgets::flutter::Window::setFramePosition(QPoint targetPos)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Window__setFramePosition_QPoint(void *thisObj, void *targetPos_);
// KDDockWidgets::flutter::Window::setGeometry(QRect arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Window__setGeometry_QRect(void *thisObj, void *arg__1_);
// KDDockWidgets::flutter::Window::setVisible(bool arg__1)
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Window__setVisible_bool(void *thisObj, bool arg__1);
// KDDockWidgets::flutter::Window::supportsHonouringLayoutMinSize() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__flutter__Window__supportsHonouringLayoutMinSize(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Window__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Window__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__flutter__Window_Finalizer(void *cppObj);
}

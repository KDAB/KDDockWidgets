/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "ClassicIndicatorWindowViewInterface_wrapper.h"


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
ClassicIndicatorWindowViewInterface_wrapper::ClassicIndicatorWindowViewInterface_wrapper()
    : ::KDDockWidgets::Views::ClassicIndicatorWindowViewInterface()
{
}
KDDockWidgets::DropLocation ClassicIndicatorWindowViewInterface_wrapper::hover(QPoint arg__1)
{
    if (m_hoverCallback) {
        const void *thisPtr = this;
        return m_hoverCallback(const_cast<void *>(thisPtr), &arg__1);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
KDDockWidgets::DropLocation
ClassicIndicatorWindowViewInterface_wrapper::hover_nocallback(QPoint arg__1)
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
bool ClassicIndicatorWindowViewInterface_wrapper::isWindow() const
{
    if (m_isWindowCallback) {
        const void *thisPtr = this;
        return m_isWindowCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
bool ClassicIndicatorWindowViewInterface_wrapper::isWindow_nocallback() const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
QPoint ClassicIndicatorWindowViewInterface_wrapper::posForIndicator(
    KDDockWidgets::DropLocation arg__1) const
{
    if (m_posForIndicatorCallback) {
        const void *thisPtr = this;
        return *m_posForIndicatorCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
QPoint ClassicIndicatorWindowViewInterface_wrapper::posForIndicator_nocallback(
    KDDockWidgets::DropLocation arg__1) const
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
void ClassicIndicatorWindowViewInterface_wrapper::raise()
{
    if (m_raiseCallback) {
        const void *thisPtr = this;
        m_raiseCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void ClassicIndicatorWindowViewInterface_wrapper::raise_nocallback()
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void ClassicIndicatorWindowViewInterface_wrapper::resize(QSize arg__1)
{
    if (m_resizeCallback) {
        const void *thisPtr = this;
        m_resizeCallback(const_cast<void *>(thisPtr), &arg__1);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void ClassicIndicatorWindowViewInterface_wrapper::resize_nocallback(QSize arg__1)
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void ClassicIndicatorWindowViewInterface_wrapper::setGeometry(QRect arg__1)
{
    if (m_setGeometryCallback) {
        const void *thisPtr = this;
        m_setGeometryCallback(const_cast<void *>(thisPtr), &arg__1);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void ClassicIndicatorWindowViewInterface_wrapper::setGeometry_nocallback(QRect arg__1)
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void ClassicIndicatorWindowViewInterface_wrapper::setObjectName(const QString &arg__1)
{
    if (m_setObjectNameCallback) {
        const void *thisPtr = this;
        m_setObjectNameCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void ClassicIndicatorWindowViewInterface_wrapper::setObjectName_nocallback(const QString &arg__1)
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void ClassicIndicatorWindowViewInterface_wrapper::setVisible(bool arg__1)
{
    if (m_setVisibleCallback) {
        const void *thisPtr = this;
        m_setVisibleCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void ClassicIndicatorWindowViewInterface_wrapper::setVisible_nocallback(bool arg__1)
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void ClassicIndicatorWindowViewInterface_wrapper::updatePositions()
{
    if (m_updatePositionsCallback) {
        const void *thisPtr = this;
        m_updatePositionsCallback(const_cast<void *>(thisPtr));
    } else {
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
void ClassicIndicatorWindowViewInterface_wrapper::updatePositions_nocallback()
{
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
ClassicIndicatorWindowViewInterface_wrapper::~ClassicIndicatorWindowViewInterface_wrapper()
{
}

}
static KDDockWidgets::Views::ClassicIndicatorWindowViewInterface *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::Views::ClassicIndicatorWindowViewInterface *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper *
fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<
        KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface_Finalizer(void *, void *cppObj,
                                                                           void *)
{
    delete reinterpret_cast<
        KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper *>(cppObj);
}
void *c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__constructor()
{
    auto ptr = new KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper();
    return reinterpret_cast<void *>(ptr);
}
// hover(QPoint arg__1)
int c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__hover_QPoint(void *thisObj,
                                                                              void *arg__1_)
{
    assert(arg__1_);
    auto &arg__1 = *reinterpret_cast<QPoint *>(arg__1_);
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<
            KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper *>(
            targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->hover_nocallback(arg__1);
        } else {
            return targetPtr->hover(arg__1);
        }
    }();
}
// isWindow() const
bool c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__isWindow(void *thisObj)
{
    return [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<
            KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper *>(
            targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->isWindow_nocallback();
        } else {
            return targetPtr->isWindow();
        }
    }();
}
// posForIndicator(KDDockWidgets::DropLocation arg__1) const
void *c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__posForIndicator_DropLocation(
    void *thisObj, int arg__1)
{
    return new Dartagnan::ValueWrapper<QPoint> { [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<
            KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper *>(
            targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->posForIndicator_nocallback(
                static_cast<KDDockWidgets::DropLocation>(arg__1));
        } else {
            return targetPtr->posForIndicator(static_cast<KDDockWidgets::DropLocation>(arg__1));
        }
    }() };
}
// raise()
void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__raise(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<
            KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper *>(
            targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->raise_nocallback();
        } else {
            return targetPtr->raise();
        }
    }();
}
// resize(QSize arg__1)
void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__resize_QSize(void *thisObj,
                                                                               void *arg__1_)
{
    assert(arg__1_);
    auto &arg__1 = *reinterpret_cast<QSize *>(arg__1_);
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<
            KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper *>(
            targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->resize_nocallback(arg__1);
        } else {
            return targetPtr->resize(arg__1);
        }
    }();
}
// setGeometry(QRect arg__1)
void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__setGeometry_QRect(void *thisObj,
                                                                                    void *arg__1_)
{
    assert(arg__1_);
    auto &arg__1 = *reinterpret_cast<QRect *>(arg__1_);
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<
            KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper *>(
            targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setGeometry_nocallback(arg__1);
        } else {
            return targetPtr->setGeometry(arg__1);
        }
    }();
}
// setObjectName(const QString & arg__1)
void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__setObjectName_QString(
    void *thisObj, const char *arg__1_)
{
    const auto arg__1 = QString::fromUtf8(arg__1_);
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<
            KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper *>(
            targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setObjectName_nocallback(arg__1);
        } else {
            return targetPtr->setObjectName(arg__1);
        }
    }();
}
// setVisible(bool arg__1)
void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__setVisible_bool(void *thisObj,
                                                                                  bool arg__1)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<
            KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper *>(
            targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->setVisible_nocallback(arg__1);
        } else {
            return targetPtr->setVisible(arg__1);
        }
    }();
}
// updatePositions()
void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__updatePositions(void *thisObj)
{
    [&] {
        auto targetPtr = fromPtr(thisObj);
        auto wrapperPtr = dynamic_cast<
            KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper *>(
            targetPtr);
        if (wrapperPtr) {
            return wrapperPtr->updatePositions_nocallback();
        } else {
            return targetPtr->updatePositions();
        }
    }();
}
void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__registerVirtualMethodCallback(
    void *ptr, void *callback, int methodId)
{
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 677:
        wrapper->m_hoverCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::
                                 ClassicIndicatorWindowViewInterface_wrapper::Callback_hover>(
                callback);
        break;
    case 678:
        wrapper->m_isWindowCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::
                                 ClassicIndicatorWindowViewInterface_wrapper::Callback_isWindow>(
                callback);
        break;
    case 679:
        wrapper->m_posForIndicatorCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper::
                Callback_posForIndicator>(callback);
        break;
    case 680:
        wrapper->m_raiseCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::
                                 ClassicIndicatorWindowViewInterface_wrapper::Callback_raise>(
                callback);
        break;
    case 681:
        wrapper->m_resizeCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::
                                 ClassicIndicatorWindowViewInterface_wrapper::Callback_resize>(
                callback);
        break;
    case 682:
        wrapper->m_setGeometryCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::
                                 ClassicIndicatorWindowViewInterface_wrapper::Callback_setGeometry>(
                callback);
        break;
    case 683:
        wrapper->m_setObjectNameCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper::
                Callback_setObjectName>(callback);
        break;
    case 684:
        wrapper->m_setVisibleCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::
                                 ClassicIndicatorWindowViewInterface_wrapper::Callback_setVisible>(
                callback);
        break;
    case 685:
        wrapper->m_updatePositionsCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper::
                Callback_updatePositions>(callback);
        break;
    }
}
}

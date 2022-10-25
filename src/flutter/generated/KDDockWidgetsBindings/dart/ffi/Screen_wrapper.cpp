/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "Screen_wrapper.h"


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
Screen_wrapper::Screen_wrapper()
    : ::KDDockWidgets::Screen()
{
}
QRect Screen_wrapper::availableGeometry() const
{
    // tag=1000
    if (m_availableGeometryCallback) {
        // tag=1001
        const void *thisPtr = this;
        return *m_availableGeometryCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
// tag=1009
QRect Screen_wrapper::availableGeometry_nocallback() const
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
QSize Screen_wrapper::availableSize() const
{
    // tag=1000
    if (m_availableSizeCallback) {
        // tag=1001
        const void *thisPtr = this;
        return *m_availableSizeCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
// tag=1009
QSize Screen_wrapper::availableSize_nocallback() const
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
qreal Screen_wrapper::devicePixelRatio() const
{
    // tag=1000
    if (m_devicePixelRatioCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_devicePixelRatioCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
// tag=1009
qreal Screen_wrapper::devicePixelRatio_nocallback() const
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
QRect Screen_wrapper::geometry() const
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
QRect Screen_wrapper::geometry_nocallback() const
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
QString Screen_wrapper::name() const
{
    // tag=1000
    if (m_nameCallback) {
        // tag=1001
        const void *thisPtr = this;
        return *m_nameCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
// tag=1009
QString Screen_wrapper::name_nocallback() const
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
QSize Screen_wrapper::size() const
{
    // tag=1000
    if (m_sizeCallback) {
        // tag=1001
        const void *thisPtr = this;
        return *m_sizeCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
// tag=1009
QSize Screen_wrapper::size_nocallback() const
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
QRect Screen_wrapper::virtualGeometry() const
{
    // tag=1000
    if (m_virtualGeometryCallback) {
        // tag=1001
        const void *thisPtr = this;
        return *m_virtualGeometryCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
// tag=1009
QRect Screen_wrapper::virtualGeometry_nocallback() const
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
QSize Screen_wrapper::virtualSize() const
{
    // tag=1000
    if (m_virtualSizeCallback) {
        // tag=1001
        const void *thisPtr = this;
        return *m_virtualSizeCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
// tag=1009
QSize Screen_wrapper::virtualSize_nocallback() const
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}

// tag=1005
Screen_wrapper::~Screen_wrapper()
{
}

}
// tag=1013
static KDDockWidgets::Screen *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::Screen *>(ptr);
}
// tag=1014
static KDDockWidgetsBindings_wrappersNS::Screen_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Screen_wrapper *>(ptr);
}
extern "C" {

// tag=1049
void c_KDDockWidgets__Screen_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Screen_wrapper *>(cppObj);
}
void *c_KDDockWidgets__Screen__constructor()
{

    // tag=1056
    auto ptr = new KDDockWidgetsBindings_wrappersNS::Screen_wrapper();
    return reinterpret_cast<void *>(ptr);
}

// tag=1050
// availableGeometry() const
void *c_KDDockWidgets__Screen__availableGeometry(void *thisObj)
{
    return
        // tag=1016

        // tag=1072
        new Dartagnan::ValueWrapper<QRect> { [&] {
            auto targetPtr = fromPtr(thisObj);
            auto wrapperPtr =
                dynamic_cast<KDDockWidgetsBindings_wrappersNS::Screen_wrapper *>(targetPtr);
            if (wrapperPtr) {
                return wrapperPtr->availableGeometry_nocallback();
            } else {
                return targetPtr->availableGeometry();
            }
        }() };
}

// tag=1050
// availableSize() const
void *c_KDDockWidgets__Screen__availableSize(void *thisObj)
{
    return
        // tag=1016

        // tag=1072
        new Dartagnan::ValueWrapper<QSize> { [&] {
            auto targetPtr = fromPtr(thisObj);
            auto wrapperPtr =
                dynamic_cast<KDDockWidgetsBindings_wrappersNS::Screen_wrapper *>(targetPtr);
            if (wrapperPtr) {
                return wrapperPtr->availableSize_nocallback();
            } else {
                return targetPtr->availableSize();
            }
        }() };
}

// tag=1050
// devicePixelRatio() const
qreal c_KDDockWidgets__Screen__devicePixelRatio(void *thisObj)
{
    return
        // tag=1016
        [&] {
            auto targetPtr = fromPtr(thisObj);
            auto wrapperPtr =
                dynamic_cast<KDDockWidgetsBindings_wrappersNS::Screen_wrapper *>(targetPtr);
            if (wrapperPtr) {
                return wrapperPtr->devicePixelRatio_nocallback();
            } else {
                return targetPtr->devicePixelRatio();
            }
        }();
}

// tag=1050
// geometry() const
void *c_KDDockWidgets__Screen__geometry(void *thisObj)
{
    return
        // tag=1016

        // tag=1072
        new Dartagnan::ValueWrapper<QRect> { [&] {
            auto targetPtr = fromPtr(thisObj);
            auto wrapperPtr =
                dynamic_cast<KDDockWidgetsBindings_wrappersNS::Screen_wrapper *>(targetPtr);
            if (wrapperPtr) {
                return wrapperPtr->geometry_nocallback();
            } else {
                return targetPtr->geometry();
            }
        }() };
}

// tag=1050
// name() const
void *c_KDDockWidgets__Screen__name(void *thisObj)
{
    return
        // tag=1016

        // tag=1072
        new Dartagnan::ValueWrapper<QString> { [&] {
            auto targetPtr = fromPtr(thisObj);
            auto wrapperPtr =
                dynamic_cast<KDDockWidgetsBindings_wrappersNS::Screen_wrapper *>(targetPtr);
            if (wrapperPtr) {
                return wrapperPtr->name_nocallback();
            } else {
                return targetPtr->name();
            }
        }() };
}

// tag=1050
// size() const
void *c_KDDockWidgets__Screen__size(void *thisObj)
{
    return
        // tag=1016

        // tag=1072
        new Dartagnan::ValueWrapper<QSize> { [&] {
            auto targetPtr = fromPtr(thisObj);
            auto wrapperPtr =
                dynamic_cast<KDDockWidgetsBindings_wrappersNS::Screen_wrapper *>(targetPtr);
            if (wrapperPtr) {
                return wrapperPtr->size_nocallback();
            } else {
                return targetPtr->size();
            }
        }() };
}

// tag=1050
// virtualGeometry() const
void *c_KDDockWidgets__Screen__virtualGeometry(void *thisObj)
{
    return
        // tag=1016

        // tag=1072
        new Dartagnan::ValueWrapper<QRect> { [&] {
            auto targetPtr = fromPtr(thisObj);
            auto wrapperPtr =
                dynamic_cast<KDDockWidgetsBindings_wrappersNS::Screen_wrapper *>(targetPtr);
            if (wrapperPtr) {
                return wrapperPtr->virtualGeometry_nocallback();
            } else {
                return targetPtr->virtualGeometry();
            }
        }() };
}

// tag=1050
// virtualSize() const
void *c_KDDockWidgets__Screen__virtualSize(void *thisObj)
{
    return
        // tag=1016

        // tag=1072
        new Dartagnan::ValueWrapper<QSize> { [&] {
            auto targetPtr = fromPtr(thisObj);
            auto wrapperPtr =
                dynamic_cast<KDDockWidgetsBindings_wrappersNS::Screen_wrapper *>(targetPtr);
            if (wrapperPtr) {
                return wrapperPtr->virtualSize_nocallback();
            } else {
                return targetPtr->virtualSize();
            }
        }() };
}
void c_KDDockWidgets__Screen__destructor(void *thisObj)
{

    // tag=1055
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__Screen__registerVirtualMethodCallback(void *ptr, void *callback, int methodId)
{
    // tag=1048
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 617:
        wrapper->m_availableGeometryCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Screen_wrapper::Callback_availableGeometry>(callback);
        break;
    case 618:
        wrapper->m_availableSizeCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Screen_wrapper::Callback_availableSize>(callback);
        break;
    case 619:
        wrapper->m_devicePixelRatioCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Screen_wrapper::Callback_devicePixelRatio>(callback);
        break;
    case 620:
        wrapper->m_geometryCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Screen_wrapper::Callback_geometry>(
                callback);
        break;
    case 621:
        wrapper->m_nameCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Screen_wrapper::Callback_name>(
                callback);
        break;
    case 622:
        wrapper->m_sizeCallback =
            reinterpret_cast<KDDockWidgetsBindings_wrappersNS::Screen_wrapper::Callback_size>(
                callback);
        break;
    case 623:
        wrapper->m_virtualGeometryCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Screen_wrapper::Callback_virtualGeometry>(callback);
        break;
    case 624:
        wrapper->m_virtualSizeCallback = reinterpret_cast<
            KDDockWidgetsBindings_wrappersNS::Screen_wrapper::Callback_virtualSize>(callback);
        break;
    }
}
}

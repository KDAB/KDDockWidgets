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
// tag=1006
ClassicIndicatorWindowViewInterface_wrapper::ClassicIndicatorWindowViewInterface_wrapper()
    : ::KDDockWidgets::Views::ClassicIndicatorWindowViewInterface()
{
}
KDDockWidgets::DropLocation ClassicIndicatorWindowViewInterface_wrapper::hover(QPoint arg__1)
{
    // tag=1000
    if (m_hoverCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_hoverCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
// tag=1009
KDDockWidgets::DropLocation ClassicIndicatorWindowViewInterface_wrapper::hover_nocallback(QPoint arg__1)
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
bool ClassicIndicatorWindowViewInterface_wrapper::isWindow() const
{
    // tag=1000
    if (m_isWindowCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_isWindowCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
// tag=1009
bool ClassicIndicatorWindowViewInterface_wrapper::isWindow_nocallback() const
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
QPoint ClassicIndicatorWindowViewInterface_wrapper::posForIndicator(KDDockWidgets::DropLocation arg__1) const
{
    // tag=1000
    if (m_posForIndicatorCallback) {
        // tag=1001
        const void *thisPtr = this;
        return *m_posForIndicatorCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
// tag=1009
QPoint ClassicIndicatorWindowViewInterface_wrapper::posForIndicator_nocallback(KDDockWidgets::DropLocation arg__1) const
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
void ClassicIndicatorWindowViewInterface_wrapper::raise()
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
void ClassicIndicatorWindowViewInterface_wrapper::raise_nocallback()
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void ClassicIndicatorWindowViewInterface_wrapper::resize(QSize arg__1)
{
    // tag=1000
    if (m_resizeCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_resizeCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
// tag=1009
void ClassicIndicatorWindowViewInterface_wrapper::resize_nocallback(QSize arg__1)
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void ClassicIndicatorWindowViewInterface_wrapper::setGeometry(QRect arg__1)
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
void ClassicIndicatorWindowViewInterface_wrapper::setGeometry_nocallback(QRect arg__1)
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void ClassicIndicatorWindowViewInterface_wrapper::setObjectName(const QString &arg__1)
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
void ClassicIndicatorWindowViewInterface_wrapper::setObjectName_nocallback(const QString &arg__1)
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void ClassicIndicatorWindowViewInterface_wrapper::setVisible(bool arg__1)
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
void ClassicIndicatorWindowViewInterface_wrapper::setVisible_nocallback(bool arg__1)
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}
void ClassicIndicatorWindowViewInterface_wrapper::updatePositions()
{
    // tag=1000
    if (m_updatePositionsCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_updatePositionsCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return;
    }
}
// tag=1009
void ClassicIndicatorWindowViewInterface_wrapper::updatePositions_nocallback()
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return;
}

// tag=1005
ClassicIndicatorWindowViewInterface_wrapper::~ClassicIndicatorWindowViewInterface_wrapper()
{
}

}
// tag=1013
static KDDockWidgets::Views::ClassicIndicatorWindowViewInterface *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::Views::ClassicIndicatorWindowViewInterface *>(ptr);
}
// tag=1014
static KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper *>(ptr);
}
extern "C" {

// tag=1049
void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper *>(cppObj);
}
void *c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__constructor()
{

    // tag=1056
    auto ptr = new KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper();
    return reinterpret_cast<void *>(ptr);
}

// tag=1050
// hover(QPoint arg__1)
int c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__hover_QPoint(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QPoint *>(arg__1_);
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->hover_nocallback(arg__1);} else {    return targetPtr->hover(arg__1);} }();
}

// tag=1050
// isWindow() const
bool c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__isWindow(void *thisObj)
{
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isWindow_nocallback();} else {    return targetPtr->isWindow();} }();
}

// tag=1050
// posForIndicator(KDDockWidgets::DropLocation arg__1) const
void *c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__posForIndicator_DropLocation(void *thisObj, int arg__1)
{
    return
        // tag=1016

        // tag=1072
        new Dartagnan::ValueWrapper<QPoint> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->posForIndicator_nocallback(static_cast<KDDockWidgets::DropLocation>(arg__1));} else {    return targetPtr->posForIndicator(static_cast<KDDockWidgets::DropLocation>(arg__1));} }() };
}

// tag=1050
// raise()
void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__raise(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->raise_nocallback();} else {    return targetPtr->raise();} }();
}

// tag=1050
// resize(QSize arg__1)
void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__resize_QSize(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QSize *>(arg__1_);
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->resize_nocallback(arg__1);} else {    return targetPtr->resize(arg__1);} }();
}

// tag=1050
// setGeometry(QRect arg__1)
void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__setGeometry_QRect(void *thisObj, void *arg__1_)
{
    auto &arg__1 = *reinterpret_cast<QRect *>(arg__1_);
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setGeometry_nocallback(arg__1);} else {    return targetPtr->setGeometry(arg__1);} }();
}

// tag=1050
// setObjectName(const QString & arg__1)
void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__setObjectName_QString(void *thisObj, const char *arg__1_)
{
    const auto arg__1 = QString::fromUtf8(arg__1_);
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setObjectName_nocallback(arg__1);} else {    return targetPtr->setObjectName(arg__1);} }();
}

// tag=1050
// setVisible(bool arg__1)
void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__setVisible_bool(void *thisObj, bool arg__1)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setVisible_nocallback(arg__1);} else {    return targetPtr->setVisible(arg__1);} }();
}

// tag=1050
// updatePositions()
void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__updatePositions(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->updatePositions_nocallback();} else {    return targetPtr->updatePositions();} }();
}
void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__destructor(void *thisObj)
{

    // tag=1055
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__registerVirtualMethodCallback(void *ptr, void *callback, int methodId)
{
    // tag=1048
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 594:
        wrapper->m_hoverCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper::Callback_hover>(callback);
        break;
    case 595:
        wrapper->m_isWindowCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper::Callback_isWindow>(callback);
        break;
    case 596:
        wrapper->m_posForIndicatorCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper::Callback_posForIndicator>(callback);
        break;
    case 597:
        wrapper->m_raiseCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper::Callback_raise>(callback);
        break;
    case 598:
        wrapper->m_resizeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper::Callback_resize>(callback);
        break;
    case 599:
        wrapper->m_setGeometryCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper::Callback_setGeometry>(callback);
        break;
    case 600:
        wrapper->m_setObjectNameCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper::Callback_setObjectName>(callback);
        break;
    case 601:
        wrapper->m_setVisibleCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper::Callback_setVisible>(callback);
        break;
    case 602:
        wrapper->m_updatePositionsCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicatorWindowViewInterface_wrapper::Callback_updatePositions>(callback);
        break;
    }
}
}

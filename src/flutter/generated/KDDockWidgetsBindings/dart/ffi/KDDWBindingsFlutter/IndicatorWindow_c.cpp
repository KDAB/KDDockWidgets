/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "IndicatorWindow_c.h"


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
IndicatorWindow_wrapper::IndicatorWindow_wrapper(KDDockWidgets::Core::ClassicIndicators *classicIndicators)
    : ::KDDockWidgets::flutter::IndicatorWindow(classicIndicators)
{
}
KDDockWidgets::DropLocation IndicatorWindow_wrapper::hover(QPoint globalPos)
{
    if (m_hoverCallback) {
        const void *thisPtr = this;
        return m_hoverCallback(const_cast<void *>(thisPtr), &globalPos);
    } else {
        return ::KDDockWidgets::flutter::IndicatorWindow::hover(globalPos);
    }
}
KDDockWidgets::DropLocation IndicatorWindow_wrapper::hover_nocallback(QPoint globalPos)
{
    return ::KDDockWidgets::flutter::IndicatorWindow::hover(globalPos);
}
bool IndicatorWindow_wrapper::isWindow() const
{
    if (m_isWindowCallback) {
        const void *thisPtr = this;
        return m_isWindowCallback(const_cast<void *>(thisPtr));
    } else {
        return ::KDDockWidgets::flutter::IndicatorWindow::isWindow();
    }
}
bool IndicatorWindow_wrapper::isWindow_nocallback() const
{
    return ::KDDockWidgets::flutter::IndicatorWindow::isWindow();
}
QPoint IndicatorWindow_wrapper::posForIndicator(KDDockWidgets::DropLocation arg__1) const
{
    if (m_posForIndicatorCallback) {
        const void *thisPtr = this;
        return *m_posForIndicatorCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        return ::KDDockWidgets::flutter::IndicatorWindow::posForIndicator(arg__1);
    }
}
QPoint IndicatorWindow_wrapper::posForIndicator_nocallback(KDDockWidgets::DropLocation arg__1) const
{
    return ::KDDockWidgets::flutter::IndicatorWindow::posForIndicator(arg__1);
}
void IndicatorWindow_wrapper::raise()
{
    if (m_raiseCallback) {
        const void *thisPtr = this;
        m_raiseCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::IndicatorWindow::raise();
    }
}
void IndicatorWindow_wrapper::raise_nocallback()
{
    ::KDDockWidgets::flutter::IndicatorWindow::raise();
}
void IndicatorWindow_wrapper::resize(QSize arg__1)
{
    if (m_resizeCallback) {
        const void *thisPtr = this;
        m_resizeCallback(const_cast<void *>(thisPtr), &arg__1);
    } else {
        ::KDDockWidgets::flutter::IndicatorWindow::resize(arg__1);
    }
}
void IndicatorWindow_wrapper::resize_nocallback(QSize arg__1)
{
    ::KDDockWidgets::flutter::IndicatorWindow::resize(arg__1);
}
void IndicatorWindow_wrapper::setGeometry(QRect arg__1)
{
    if (m_setGeometryCallback) {
        const void *thisPtr = this;
        m_setGeometryCallback(const_cast<void *>(thisPtr), &arg__1);
    } else {
        ::KDDockWidgets::flutter::IndicatorWindow::setGeometry(arg__1);
    }
}
void IndicatorWindow_wrapper::setGeometry_nocallback(QRect arg__1)
{
    ::KDDockWidgets::flutter::IndicatorWindow::setGeometry(arg__1);
}
void IndicatorWindow_wrapper::setObjectName(const QString &arg__1)
{
    if (m_setObjectNameCallback) {
        const void *thisPtr = this;
        m_setObjectNameCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        ::KDDockWidgets::flutter::IndicatorWindow::setObjectName(arg__1);
    }
}
void IndicatorWindow_wrapper::setObjectName_nocallback(const QString &arg__1)
{
    ::KDDockWidgets::flutter::IndicatorWindow::setObjectName(arg__1);
}
void IndicatorWindow_wrapper::setVisible(bool arg__1)
{
    if (m_setVisibleCallback) {
        const void *thisPtr = this;
        m_setVisibleCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        ::KDDockWidgets::flutter::IndicatorWindow::setVisible(arg__1);
    }
}
void IndicatorWindow_wrapper::setVisible_nocallback(bool arg__1)
{
    ::KDDockWidgets::flutter::IndicatorWindow::setVisible(arg__1);
}
void IndicatorWindow_wrapper::updatePositions()
{
    if (m_updatePositionsCallback) {
        const void *thisPtr = this;
        m_updatePositionsCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::flutter::IndicatorWindow::updatePositions();
    }
}
void IndicatorWindow_wrapper::updatePositions_nocallback()
{
    ::KDDockWidgets::flutter::IndicatorWindow::updatePositions();
}
IndicatorWindow_wrapper::~IndicatorWindow_wrapper()
{
}

}
}
static KDDockWidgets::flutter::IndicatorWindow *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::flutter::IndicatorWindow *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::IndicatorWindow_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::IndicatorWindow_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__flutter__IndicatorWindow_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::IndicatorWindow_wrapper *>(cppObj);
}
void *c_KDDockWidgets__flutter__IndicatorWindow__constructor_ClassicIndicators(void *classicIndicators_)
{
    auto classicIndicators = reinterpret_cast<KDDockWidgets::Core::ClassicIndicators *>(classicIndicators_);
    auto ptr = new KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::IndicatorWindow_wrapper(classicIndicators);
    return reinterpret_cast<void *>(ptr);
}
// hover(QPoint globalPos)
int c_KDDockWidgets__flutter__IndicatorWindow__hover_QPoint(void *thisObj, void *globalPos_)
{
    assert(globalPos_);
    auto &globalPos = *reinterpret_cast<QPoint *>(globalPos_);
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::IndicatorWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->hover_nocallback(globalPos);} else {    return targetPtr->hover(globalPos);} }();
}
// isWindow() const
bool c_KDDockWidgets__flutter__IndicatorWindow__isWindow(void *thisObj)
{
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::IndicatorWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->isWindow_nocallback();} else {    return targetPtr->isWindow();} }();
}
// posForIndicator(KDDockWidgets::DropLocation arg__1) const
void *c_KDDockWidgets__flutter__IndicatorWindow__posForIndicator_DropLocation(void *thisObj, int arg__1)
{
    return new Dartagnan::ValueWrapper<QPoint> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::IndicatorWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->posForIndicator_nocallback(static_cast<KDDockWidgets::DropLocation>(arg__1));} else {    return targetPtr->posForIndicator(static_cast<KDDockWidgets::DropLocation>(arg__1));} }() };
}
// raise()
void c_KDDockWidgets__flutter__IndicatorWindow__raise(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::IndicatorWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->raise_nocallback();} else {    return targetPtr->raise();} }();
}
// resize(QSize arg__1)
void c_KDDockWidgets__flutter__IndicatorWindow__resize_QSize(void *thisObj, void *arg__1_)
{
    assert(arg__1_);
    auto &arg__1 = *reinterpret_cast<QSize *>(arg__1_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::IndicatorWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->resize_nocallback(arg__1);} else {    return targetPtr->resize(arg__1);} }();
}
// setGeometry(QRect arg__1)
void c_KDDockWidgets__flutter__IndicatorWindow__setGeometry_QRect(void *thisObj, void *arg__1_)
{
    assert(arg__1_);
    auto &arg__1 = *reinterpret_cast<QRect *>(arg__1_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::IndicatorWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setGeometry_nocallback(arg__1);} else {    return targetPtr->setGeometry(arg__1);} }();
}
// setObjectName(const QString & arg__1)
void c_KDDockWidgets__flutter__IndicatorWindow__setObjectName_QString(void *thisObj, const char *arg__1_)
{
    const auto arg__1 = QString::fromUtf8(arg__1_);
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::IndicatorWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setObjectName_nocallback(arg__1);} else {    return targetPtr->setObjectName(arg__1);} }();
}
// setVisible(bool arg__1)
void c_KDDockWidgets__flutter__IndicatorWindow__setVisible_bool(void *thisObj, bool arg__1)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::IndicatorWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->setVisible_nocallback(arg__1);} else {    return targetPtr->setVisible(arg__1);} }();
}
// updatePositions()
void c_KDDockWidgets__flutter__IndicatorWindow__updatePositions(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::IndicatorWindow_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->updatePositions_nocallback();} else {    return targetPtr->updatePositions();} }();
}
void c_KDDockWidgets__flutter__IndicatorWindow__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__flutter__IndicatorWindow__registerVirtualMethodCallback(void *ptr, void *callback, int methodId)
{
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 1784:
        wrapper->m_hoverCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::IndicatorWindow_wrapper::Callback_hover>(callback);
        break;
    case 1785:
        wrapper->m_isWindowCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::IndicatorWindow_wrapper::Callback_isWindow>(callback);
        break;
    case 1786:
        wrapper->m_posForIndicatorCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::IndicatorWindow_wrapper::Callback_posForIndicator>(callback);
        break;
    case 1787:
        wrapper->m_raiseCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::IndicatorWindow_wrapper::Callback_raise>(callback);
        break;
    case 1788:
        wrapper->m_resizeCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::IndicatorWindow_wrapper::Callback_resize>(callback);
        break;
    case 1789:
        wrapper->m_setGeometryCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::IndicatorWindow_wrapper::Callback_setGeometry>(callback);
        break;
    case 1790:
        wrapper->m_setObjectNameCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::IndicatorWindow_wrapper::Callback_setObjectName>(callback);
        break;
    case 1791:
        wrapper->m_setVisibleCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::IndicatorWindow_wrapper::Callback_setVisible>(callback);
        break;
    case 1792:
        wrapper->m_updatePositionsCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::KDDWBindingsFlutter::IndicatorWindow_wrapper::Callback_updatePositions>(callback);
        break;
    }
}
}

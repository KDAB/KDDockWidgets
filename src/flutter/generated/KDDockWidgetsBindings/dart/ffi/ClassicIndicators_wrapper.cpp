/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "ClassicIndicators_wrapper.h"


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
ClassicIndicators_wrapper::ClassicIndicators_wrapper(KDDockWidgets::Controllers::DropArea *dropArea)
    : ::KDDockWidgets::Controllers::ClassicIndicators(dropArea)
{
}
KDDockWidgets::DropLocation ClassicIndicators_wrapper::hover_impl(QPoint globalPos)
{
    if (m_hover_implCallback) {
        const void *thisPtr = this;
        return m_hover_implCallback(const_cast<void *>(thisPtr), globalPos);
    } else {
        return ::KDDockWidgets::Controllers::ClassicIndicators::hover_impl(globalPos);
    }
}
KDDockWidgets::DropLocation ClassicIndicators_wrapper::hover_impl_nocallback(QPoint globalPos)
{
    return ::KDDockWidgets::Controllers::ClassicIndicators::hover_impl(globalPos);
}
void ClassicIndicators_wrapper::indicatorsVisibleChanged()
{
    ::KDDockWidgets::Controllers::ClassicIndicators::indicatorsVisibleChanged();
}
bool ClassicIndicators_wrapper::onResize(QSize newSize)
{
    return ::KDDockWidgets::Controllers::ClassicIndicators::onResize(newSize);
}
QPoint ClassicIndicators_wrapper::posForIndicator(KDDockWidgets::DropLocation arg__1) const
{
    if (m_posForIndicatorCallback) {
        const void *thisPtr = this;
        return *m_posForIndicatorCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        return ::KDDockWidgets::Controllers::ClassicIndicators::posForIndicator(arg__1);
    }
}
QPoint ClassicIndicators_wrapper::posForIndicator_nocallback(KDDockWidgets::DropLocation arg__1) const
{
    return ::KDDockWidgets::Controllers::ClassicIndicators::posForIndicator(arg__1);
}
void ClassicIndicators_wrapper::setDropLocation(KDDockWidgets::DropLocation arg__1)
{
    ::KDDockWidgets::Controllers::ClassicIndicators::setDropLocation(arg__1);
}
QString ClassicIndicators_wrapper::tr(const char *s, const char *c, int n)
{
    return ::KDDockWidgets::Controllers::ClassicIndicators::tr(s, c, n);
}
void ClassicIndicators_wrapper::updateVisibility()
{
    if (m_updateVisibilityCallback) {
        const void *thisPtr = this;
        m_updateVisibilityCallback(const_cast<void *>(thisPtr));
    } else {
        ::KDDockWidgets::Controllers::ClassicIndicators::updateVisibility();
    }
}
void ClassicIndicators_wrapper::updateVisibility_nocallback()
{
    ::KDDockWidgets::Controllers::ClassicIndicators::updateVisibility();
}
ClassicIndicators_wrapper::~ClassicIndicators_wrapper()
{
}

}
static KDDockWidgets::Controllers::ClassicIndicators *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::Controllers::ClassicIndicators *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper *>(ptr);
}
extern "C" {
void c_KDDockWidgets__Controllers__ClassicIndicators_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper *>(cppObj);
}
void *c_KDDockWidgets__Controllers__ClassicIndicators__constructor_DropArea(void *dropArea_)
{
    auto dropArea = reinterpret_cast<KDDockWidgets::Controllers::DropArea *>(dropArea_);
    auto ptr = new KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper(dropArea);
    return reinterpret_cast<void *>(ptr);
}
// hover_impl(QPoint globalPos)
int c_KDDockWidgets__Controllers__ClassicIndicators__hover_impl_QPoint(void *thisObj, void *globalPos_)
{
    auto &globalPos = *reinterpret_cast<QPoint *>(globalPos_);
    return [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->hover_impl_nocallback(globalPos);} else {    return targetPtr->hover_impl(globalPos);} }();
}
// indicatorsVisibleChanged()
void c_KDDockWidgets__Controllers__ClassicIndicators__indicatorsVisibleChanged(void *thisObj)
{
    fromPtr(thisObj)->indicatorsVisibleChanged();
}
// onResize(QSize newSize)
bool c_KDDockWidgets__Controllers__ClassicIndicators__onResize_QSize(void *thisObj, void *newSize_)
{
    auto &newSize = *reinterpret_cast<QSize *>(newSize_);
    return fromPtr(thisObj)->onResize(newSize);
}
// posForIndicator(KDDockWidgets::DropLocation arg__1) const
void *c_KDDockWidgets__Controllers__ClassicIndicators__posForIndicator_DropLocation(void *thisObj, int arg__1)
{
    return new Dartagnan::ValueWrapper<QPoint> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->posForIndicator_nocallback(static_cast<KDDockWidgets::DropLocation>(arg__1));} else {    return targetPtr->posForIndicator(static_cast<KDDockWidgets::DropLocation>(arg__1));} }() };
}
// setDropLocation(KDDockWidgets::DropLocation arg__1)
void c_KDDockWidgets__Controllers__ClassicIndicators__setDropLocation_DropLocation(void *thisObj, int arg__1)
{
    fromPtr(thisObj)->setDropLocation(static_cast<KDDockWidgets::DropLocation>(arg__1));
}
// tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__Controllers__ClassicIndicators__tr_char_char_int(const char *s, const char *c, int n)
{
    return new Dartagnan::ValueWrapper<QString> { KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper::tr(s, c, n) };
}
// updateVisibility()
void c_KDDockWidgets__Controllers__ClassicIndicators__updateVisibility(void *thisObj)
{
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->updateVisibility_nocallback();} else {    return targetPtr->updateVisibility();} }();
}
void c_KDDockWidgets__Controllers__ClassicIndicators__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__Controllers__ClassicIndicators__registerVirtualMethodCallback(void *ptr, void *callback, int methodId)
{
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 789:
        wrapper->m_hover_implCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper::Callback_hover_impl>(callback);
        break;
    case 792:
        wrapper->m_posForIndicatorCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper::Callback_posForIndicator>(callback);
        break;
    case 797:
        wrapper->m_updateVisibilityCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper::Callback_updateVisibility>(callback);
        break;
    }
}
}

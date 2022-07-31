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
// tag=1006
ClassicIndicators_wrapper::ClassicIndicators_wrapper(KDDockWidgets::Controllers::DropArea *dropArea)
    : ::KDDockWidgets::Controllers::ClassicIndicators(dropArea)
{
}
KDDockWidgets::DropLocation ClassicIndicators_wrapper::hover_impl(QPoint globalPos)
{
    // tag=1000
    if (m_hover_implCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_hover_implCallback(const_cast<void *>(thisPtr), globalPos);
    } else {
        // tag=1002
        return ::KDDockWidgets::Controllers::ClassicIndicators::hover_impl(globalPos);
    }
}
// tag=1009
KDDockWidgets::DropLocation ClassicIndicators_wrapper::hover_impl_nocallback(QPoint globalPos)
{
    // tag=1003
    return ::KDDockWidgets::Controllers::ClassicIndicators::hover_impl(globalPos);
}
void ClassicIndicators_wrapper::indicatorsVisibleChanged()
{
    // tag=1000

    // tag=1004
    ::KDDockWidgets::Controllers::ClassicIndicators::indicatorsVisibleChanged();
}
bool ClassicIndicators_wrapper::onResize(QSize newSize)
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Controllers::ClassicIndicators::onResize(newSize);
}
QPoint ClassicIndicators_wrapper::posForIndicator(KDDockWidgets::DropLocation arg__1) const
{
    // tag=1000
    if (m_posForIndicatorCallback) {
        // tag=1001
        const void *thisPtr = this;
        return *m_posForIndicatorCallback(const_cast<void *>(thisPtr), arg__1);
    } else {
        // tag=1002
        return ::KDDockWidgets::Controllers::ClassicIndicators::posForIndicator(arg__1);
    }
}
// tag=1009
QPoint ClassicIndicators_wrapper::posForIndicator_nocallback(KDDockWidgets::DropLocation arg__1) const
{
    // tag=1003
    return ::KDDockWidgets::Controllers::ClassicIndicators::posForIndicator(arg__1);
}
void ClassicIndicators_wrapper::setDropLocation(KDDockWidgets::DropLocation arg__1)
{
    // tag=1000

    // tag=1004
    ::KDDockWidgets::Controllers::ClassicIndicators::setDropLocation(arg__1);
}
QString ClassicIndicators_wrapper::tr(const char *s, const char *c, int n)
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::Controllers::ClassicIndicators::tr(s, c, n);
}
void ClassicIndicators_wrapper::updateVisibility()
{
    // tag=1000
    if (m_updateVisibilityCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_updateVisibilityCallback(const_cast<void *>(thisPtr));
    } else {
        // tag=1002
        ::KDDockWidgets::Controllers::ClassicIndicators::updateVisibility();
    }
}
// tag=1009
void ClassicIndicators_wrapper::updateVisibility_nocallback()
{
    // tag=1003
    ::KDDockWidgets::Controllers::ClassicIndicators::updateVisibility();
}

// tag=1005
ClassicIndicators_wrapper::~ClassicIndicators_wrapper()
{
}

}
// tag=1013
static KDDockWidgets::Controllers::ClassicIndicators *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::Controllers::ClassicIndicators *>(ptr);
}
// tag=1014
static KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper *>(ptr);
}
extern "C" {

// tag=1049
void c_KDDockWidgets__Controllers__ClassicIndicators_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper *>(cppObj);
}
void *c_KDDockWidgets__Controllers__ClassicIndicators__constructor_DropArea(void *dropArea_)
{
    auto dropArea = reinterpret_cast<KDDockWidgets::Controllers::DropArea *>(dropArea_);
    // tag=1056
    auto ptr = new KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper(dropArea);
    return reinterpret_cast<void *>(ptr);
}

// tag=1050
// hover_impl(QPoint globalPos)
int c_KDDockWidgets__Controllers__ClassicIndicators__hover_impl_QPoint(void *thisObj, void *globalPos_)
{
    auto &globalPos = *reinterpret_cast<QPoint *>(globalPos_);
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->hover_impl_nocallback(globalPos);} else {    return targetPtr->hover_impl(globalPos);} }();
}

// tag=1050
// indicatorsVisibleChanged()
void c_KDDockWidgets__Controllers__ClassicIndicators__indicatorsVisibleChanged(void *thisObj)
{
    // tag=1010
    fromPtr(thisObj)->indicatorsVisibleChanged();
}

// tag=1050
// onResize(QSize newSize)
bool c_KDDockWidgets__Controllers__ClassicIndicators__onResize_QSize(void *thisObj, void *newSize_)
{
    auto &newSize = *reinterpret_cast<QSize *>(newSize_);
    return
        // tag=1010
        fromPtr(thisObj)->onResize(newSize);
}

// tag=1050
// posForIndicator(KDDockWidgets::DropLocation arg__1) const
void *c_KDDockWidgets__Controllers__ClassicIndicators__posForIndicator_DropLocation(void *thisObj, int arg__1)
{
    return
        // tag=1016

        // tag=1072
        new Dartagnan::ValueWrapper<QPoint> { [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->posForIndicator_nocallback(static_cast<KDDockWidgets::DropLocation>(arg__1));} else {    return targetPtr->posForIndicator(static_cast<KDDockWidgets::DropLocation>(arg__1));} }() };
}

// tag=1050
// setDropLocation(KDDockWidgets::DropLocation arg__1)
void c_KDDockWidgets__Controllers__ClassicIndicators__setDropLocation_DropLocation(void *thisObj, int arg__1)
{
    // tag=1010
    fromPtr(thisObj)->setDropLocation(static_cast<KDDockWidgets::DropLocation>(arg__1));
}

// tag=1050
// tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__Controllers__ClassicIndicators__tr_char_char_int(const char *s, const char *c, int n)
{
    return
        // tag=1068

        // tag=1072
        new Dartagnan::ValueWrapper<QString> { KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper::tr(s, c, n) };
}

// tag=1050
// updateVisibility()
void c_KDDockWidgets__Controllers__ClassicIndicators__updateVisibility(void *thisObj)
{
    // tag=1016
    [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->updateVisibility_nocallback();} else {    return targetPtr->updateVisibility();} }();
}
void c_KDDockWidgets__Controllers__ClassicIndicators__destructor(void *thisObj)
{

    // tag=1055
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__Controllers__ClassicIndicators__registerVirtualMethodCallback(void *ptr, void *callback, int methodId)
{
    // tag=1048
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 672:
        wrapper->m_hover_implCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper::Callback_hover_impl>(callback);
        break;
    case 675:
        wrapper->m_posForIndicatorCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper::Callback_posForIndicator>(callback);
        break;
    case 680:
        wrapper->m_updateVisibilityCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::ClassicIndicators_wrapper::Callback_updateVisibility>(callback);
        break;
    }
}
}

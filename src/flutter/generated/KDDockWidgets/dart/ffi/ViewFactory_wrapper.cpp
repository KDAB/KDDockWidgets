/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "ViewFactory_wrapper.h"


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
namespace KDDockWidgets_wrappersNS {
// tag=1006
ViewFactory_wrapper::ViewFactory_wrapper()
    : ::KDDockWidgets::ViewFactory()
{
}
KDDockWidgets::View *ViewFactory_wrapper::createRubberBand(KDDockWidgets::View *parent) const
{
    // tag=1000
    if (m_createRubberBandCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_createRubberBandCallback(const_cast<void *>(thisPtr), parent);
    } else {
        // tag=1015
        qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
        return {};
    }
}
// tag=1009
KDDockWidgets::View *ViewFactory_wrapper::createRubberBand_nocallback(KDDockWidgets::View *parent) const
{
    // tag=1003

    // tag=1007
    qWarning() << Q_FUNC_INFO << "Warning: Calling pure-virtual";
    return {};
}
QString ViewFactory_wrapper::tr(const char *s, const char *c, int n)
{
    // tag=1000

    // tag=1004
    return ::KDDockWidgets::ViewFactory::tr(s, c, n);
}

// tag=1005
ViewFactory_wrapper::~ViewFactory_wrapper()
{
}

}
// tag=1013
static KDDockWidgets::ViewFactory *fromPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets::ViewFactory *>(ptr);
}
// tag=1014
static KDDockWidgets_wrappersNS::ViewFactory_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgets_wrappersNS::ViewFactory_wrapper *>(ptr);
}
extern "C" {

// tag=1049
void c_KDDockWidgets__ViewFactory_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgets_wrappersNS::ViewFactory_wrapper *>(cppObj);
}
void *c_KDDockWidgets__ViewFactory__constructor()
{

    // tag=1056
    auto ptr = new KDDockWidgets_wrappersNS::ViewFactory_wrapper();
    return reinterpret_cast<void *>(ptr);
}

// tag=1050
// createRubberBand(KDDockWidgets::View * parent) const
void *c_KDDockWidgets__ViewFactory__createRubberBand_View(void *thisObj, void *parent_)
{
    auto parent = reinterpret_cast<KDDockWidgets::View *>(parent_);
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgets_wrappersNS::ViewFactory_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->createRubberBand_nocallback(parent);} else {    return targetPtr->createRubberBand(parent);} }();
}

// tag=1079
void c_KDDockWidgets__ViewFactory__onDestroyed_QObject(void *thisObj, void *contextQObject, void *callback)
{
    auto instance = reinterpret_cast<ViewFactory *>(thisObj);
    auto context = reinterpret_cast<QObject *>(contextQObject);
    QObject::connect(instance, &ViewFactory::destroyed, context ? context : instance, [thisObj, callback] {
typedef void (*SignalHandler_callback)(void *);
auto dartCallback = reinterpret_cast<SignalHandler_callback>(callback);
dartCallback(thisObj); });
}

// tag=1050
// tr(const char * s, const char * c, int n)
void *c_static_KDDockWidgets__ViewFactory__tr_char_char_int(const char *s, const char *c, int n)
{
    return
        // tag=1068

        // tag=1072
        new Dartagnan::ValueWrapper<QString> { KDDockWidgets_wrappersNS::ViewFactory_wrapper::tr(s, c, n) };
}
void c_KDDockWidgets__ViewFactory__destructor(void *thisObj)
{

    // tag=1055
    delete fromPtr(thisObj);
}
void c_KDDockWidgets__ViewFactory__registerVirtualMethodCallback(void *ptr, void *callback, int methodId)
{
    // tag=1048
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 574:
        wrapper->m_createRubberBandCallback = reinterpret_cast<KDDockWidgets_wrappersNS::ViewFactory_wrapper::Callback_createRubberBand>(callback);
        break;
    }
}
}

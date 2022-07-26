/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "QEvent_wrapper.h"


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
QEvent_wrapper::QEvent_wrapper(QEvent::Type type)
    : ::QEvent(type)
{
}
void QEvent_wrapper::accept()
{
    // tag=1000

    // tag=1004
    ::QEvent::accept();
}
void QEvent_wrapper::ignore()
{
    // tag=1000

    // tag=1004
    ::QEvent::ignore();
}
bool QEvent_wrapper::isAccepted() const
{
    // tag=1000

    // tag=1004
    return ::QEvent::isAccepted();
}
int QEvent_wrapper::registerEventType(int hint)
{
    // tag=1000

    // tag=1004
    return ::QEvent::registerEventType(hint);
}
void QEvent_wrapper::setAccepted(bool accepted)
{
    // tag=1000

    // tag=1004
    ::QEvent::setAccepted(accepted);
}
bool QEvent_wrapper::spontaneous() const
{
    // tag=1000

    // tag=1004
    return ::QEvent::spontaneous();
}
QEvent::Type QEvent_wrapper::type() const
{
    // tag=1000

    // tag=1004
    return ::QEvent::type();
}

// tag=1005
QEvent_wrapper::~QEvent_wrapper()
{
}

}
// tag=1013
static QEvent *fromPtr(void *ptr)
{
    return reinterpret_cast<QEvent *>(ptr);
}
// tag=1014
static KDDockWidgetsBindings_wrappersNS::QEvent_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QEvent_wrapper *>(ptr);
}
extern "C" {

// tag=1049
void c_QEvent_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QEvent_wrapper *>(cppObj);
}
void *c_QEvent__constructor_Type(int type)
{

    // tag=1056
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QEvent_wrapper(static_cast<QEvent::Type>(type));
    return reinterpret_cast<void *>(ptr);
}

// tag=1050
// accept()
void c_QEvent__accept(void *thisObj)
{
    // tag=1010
    fromPtr(thisObj)->accept();
}

// tag=1050
// ignore()
void c_QEvent__ignore(void *thisObj)
{
    // tag=1010
    fromPtr(thisObj)->ignore();
}

// tag=1050
// isAccepted() const
bool c_QEvent__isAccepted(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->isAccepted();
}

// tag=1050
// registerEventType(int hint)
int c_static_QEvent__registerEventType_int(int hint)
{
    return
        // tag=1068
        KDDockWidgetsBindings_wrappersNS::QEvent_wrapper::registerEventType(hint);
}

// tag=1050
// setAccepted(bool accepted)
void c_QEvent__setAccepted_bool(void *thisObj, bool accepted)
{
    // tag=1010
    fromPtr(thisObj)->setAccepted(accepted);
}

// tag=1050
// spontaneous() const
bool c_QEvent__spontaneous(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->spontaneous();
}

// tag=1050
// type() const
int c_QEvent__type(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->type();
}
void c_QEvent__destructor(void *thisObj)
{

    // tag=1055
    delete fromPtr(thisObj);
}
void c_QEvent__registerVirtualMethodCallback(void *ptr, void *callback, int methodId)
{
    // tag=1048
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    }
}
}

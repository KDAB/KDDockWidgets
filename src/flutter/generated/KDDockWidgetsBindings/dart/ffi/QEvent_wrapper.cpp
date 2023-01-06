/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
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
QEvent_wrapper::QEvent_wrapper(QEvent::Type type)
    : ::QEvent(type)
{
}
void QEvent_wrapper::accept()
{
    ::QEvent::accept();
}
void QEvent_wrapper::ignore()
{
    ::QEvent::ignore();
}
bool QEvent_wrapper::isAccepted() const
{
    return ::QEvent::isAccepted();
}
int QEvent_wrapper::registerEventType(int hint)
{
    return ::QEvent::registerEventType(hint);
}
void QEvent_wrapper::setAccepted(bool accepted)
{
    ::QEvent::setAccepted(accepted);
}
bool QEvent_wrapper::spontaneous() const
{
    return ::QEvent::spontaneous();
}
QEvent::Type QEvent_wrapper::type() const
{
    return ::QEvent::type();
}
QEvent_wrapper::~QEvent_wrapper()
{
}

}
static QEvent *fromPtr(void *ptr)
{
    return reinterpret_cast<QEvent *>(ptr);
}
static KDDockWidgetsBindings_wrappersNS::QEvent_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QEvent_wrapper *>(ptr);
}
extern "C" {
void c_QEvent_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QEvent_wrapper *>(cppObj);
}
void *c_QEvent__constructor_Type(int type)
{
    auto ptr =
        new KDDockWidgetsBindings_wrappersNS::QEvent_wrapper(static_cast<QEvent::Type>(type));
    return reinterpret_cast<void *>(ptr);
}
// accept()
void c_QEvent__accept(void *thisObj)
{
    fromPtr(thisObj)->accept();
}
// ignore()
void c_QEvent__ignore(void *thisObj)
{
    fromPtr(thisObj)->ignore();
}
// isAccepted() const
bool c_QEvent__isAccepted(void *thisObj)
{
    return fromPtr(thisObj)->isAccepted();
}
// registerEventType(int hint)
int c_static_QEvent__registerEventType_int(int hint)
{
    return KDDockWidgetsBindings_wrappersNS::QEvent_wrapper::registerEventType(hint);
}
// setAccepted(bool accepted)
void c_QEvent__setAccepted_bool(void *thisObj, bool accepted)
{
    fromPtr(thisObj)->setAccepted(accepted);
}
// spontaneous() const
bool c_QEvent__spontaneous(void *thisObj)
{
    return fromPtr(thisObj)->spontaneous();
}
// type() const
int c_QEvent__type(void *thisObj)
{
    return int(fromPtr(thisObj)->type());
}
void c_QEvent__destructor(void *thisObj)
{
    delete fromPtr(thisObj);
}
void c_QEvent__registerVirtualMethodCallback(void *ptr, void *callback, int methodId)
{
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    }
}
}

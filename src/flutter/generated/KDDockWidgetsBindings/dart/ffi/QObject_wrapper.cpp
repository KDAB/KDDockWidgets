/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "QObject_wrapper.h"


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
QObject_wrapper::QObject_wrapper(QObject *parent)
    : ::QObject(parent)
{
}
bool QObject_wrapper::blockSignals(bool b)
{
    // tag=1000

    // tag=1004
    return ::QObject::blockSignals(b);
}
const QList<QObject *> &QObject_wrapper::children() const
{
    // tag=1000

    // tag=1004
    return ::QObject::children();
}
void QObject_wrapper::customEvent(QEvent *event)
{
    // tag=1000
    if (m_customEventCallback) {
        // tag=1001
        const void *thisPtr = this;
        m_customEventCallback(const_cast<void *>(thisPtr), event);
    } else {
        // tag=1002
        ::QObject::customEvent(event);
    }
}
// tag=1009
void QObject_wrapper::customEvent_nocallback(QEvent *event)
{
    // tag=1003
    ::QObject::customEvent(event);
}
void QObject_wrapper::deleteLater()
{
    // tag=1000

    // tag=1004
    ::QObject::deleteLater();
}
void QObject_wrapper::destroyed(QObject *arg__1)
{
    // tag=1000

    // tag=1004
    ::QObject::destroyed(arg__1);
}
bool QObject_wrapper::disconnect(const QObject *receiver, const char *member) const
{
    // tag=1000

    // tag=1004
    return ::QObject::disconnect(receiver, member);
}
bool QObject_wrapper::disconnect(const QObject *sender, const char *signal, const QObject *receiver, const char *member)
{
    // tag=1000

    // tag=1004
    return ::QObject::disconnect(sender, signal, receiver, member);
}
bool QObject_wrapper::disconnect(const char *signal, const QObject *receiver, const char *member) const
{
    // tag=1000

    // tag=1004
    return ::QObject::disconnect(signal, receiver, member);
}
void QObject_wrapper::dumpObjectInfo()
{
    // tag=1000

    // tag=1004
    ::QObject::dumpObjectInfo();
}
void QObject_wrapper::dumpObjectTree()
{
    // tag=1000

    // tag=1004
    ::QObject::dumpObjectTree();
}
QList<QByteArray> QObject_wrapper::dynamicPropertyNames() const
{
    // tag=1000

    // tag=1004
    return ::QObject::dynamicPropertyNames();
}
bool QObject_wrapper::event(QEvent *event)
{
    // tag=1000
    if (m_eventCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_eventCallback(const_cast<void *>(thisPtr), event);
    } else {
        // tag=1002
        return ::QObject::event(event);
    }
}
// tag=1009
bool QObject_wrapper::event_nocallback(QEvent *event)
{
    // tag=1003
    return ::QObject::event(event);
}
bool QObject_wrapper::eventFilter(QObject *watched, QEvent *event)
{
    // tag=1000
    if (m_eventFilterCallback) {
        // tag=1001
        const void *thisPtr = this;
        return m_eventFilterCallback(const_cast<void *>(thisPtr), watched, event);
    } else {
        // tag=1002
        return ::QObject::eventFilter(watched, event);
    }
}
// tag=1009
bool QObject_wrapper::eventFilter_nocallback(QObject *watched, QEvent *event)
{
    // tag=1003
    return ::QObject::eventFilter(watched, event);
}
bool QObject_wrapper::inherits(const char *classname) const
{
    // tag=1000

    // tag=1004
    return ::QObject::inherits(classname);
}
void QObject_wrapper::installEventFilter(QObject *filterObj)
{
    // tag=1000

    // tag=1004
    ::QObject::installEventFilter(filterObj);
}
bool QObject_wrapper::isWidgetType() const
{
    // tag=1000

    // tag=1004
    return ::QObject::isWidgetType();
}
bool QObject_wrapper::isWindowType() const
{
    // tag=1000

    // tag=1004
    return ::QObject::isWindowType();
}
void QObject_wrapper::killTimer(int id)
{
    // tag=1000

    // tag=1004
    ::QObject::killTimer(id);
}
QString QObject_wrapper::objectName() const
{
    // tag=1000

    // tag=1004
    return ::QObject::objectName();
}
QObject *QObject_wrapper::parent() const
{
    // tag=1000

    // tag=1004
    return ::QObject::parent();
}
int QObject_wrapper::receivers(const char *signal) const
{
    // tag=1000

    // tag=1004
    return ::QObject::receivers(signal);
}
void QObject_wrapper::removeEventFilter(QObject *obj)
{
    // tag=1000

    // tag=1004
    ::QObject::removeEventFilter(obj);
}
QObject *QObject_wrapper::sender() const
{
    // tag=1000

    // tag=1004
    return ::QObject::sender();
}
int QObject_wrapper::senderSignalIndex() const
{
    // tag=1000

    // tag=1004
    return ::QObject::senderSignalIndex();
}
void QObject_wrapper::setObjectName(const QString &name)
{
    // tag=1000

    // tag=1004
    ::QObject::setObjectName(name);
}
void QObject_wrapper::setParent(QObject *parent)
{
    // tag=1000

    // tag=1004
    ::QObject::setParent(parent);
}
bool QObject_wrapper::signalsBlocked() const
{
    // tag=1000

    // tag=1004
    return ::QObject::signalsBlocked();
}
int QObject_wrapper::startTimer(int interval)
{
    // tag=1000

    // tag=1004
    return ::QObject::startTimer(interval);
}
QString QObject_wrapper::tr(const char *s, const char *c, int n)
{
    // tag=1000

    // tag=1004
    return ::QObject::tr(s, c, n);
}

// tag=1005
QObject_wrapper::~QObject_wrapper()
{
}

}
// tag=1013
static QObject *fromPtr(void *ptr)
{
    return reinterpret_cast<QObject *>(ptr);
}
// tag=1014
static KDDockWidgetsBindings_wrappersNS::QObject_wrapper *fromWrapperPtr(void *ptr)
{
    return reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QObject_wrapper *>(ptr);
}
extern "C" {

// tag=1049
void c_QObject_Finalizer(void *, void *cppObj, void *)
{
    delete reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QObject_wrapper *>(cppObj);
}
void *c_QObject__constructor_QObject(void *parent_)
{
    auto parent = reinterpret_cast<QObject *>(parent_);
    // tag=1056
    auto ptr = new KDDockWidgetsBindings_wrappersNS::QObject_wrapper(parent);
    return reinterpret_cast<void *>(ptr);
}

// tag=1050
// blockSignals(bool b)
bool c_QObject__blockSignals_bool(void *thisObj, bool b)
{
    return
        // tag=1010
        fromPtr(thisObj)->blockSignals(b);
}

// tag=1050
// children() const
void *c_QObject__children(void *thisObj)
{
    return
        // tag=1010

        // tag=1071
        const_cast<void *>(static_cast<const void *>(&fromPtr(thisObj)->children()));
}

// tag=1050
// customEvent(QEvent * event)
void c_QObject__customEvent_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    // tag=1011

    // tag=1074
    fromWrapperPtr(thisObj)->customEvent_nocallback(event);
}

// tag=1050
// deleteLater()
void c_QObject__deleteLater(void *thisObj)
{
    // tag=1010
    fromPtr(thisObj)->deleteLater();
}

// tag=1050
// destroyed(QObject * arg__1)
void c_QObject__destroyed_QObject(void *thisObj, void *arg__1_)
{
    auto arg__1 = reinterpret_cast<QObject *>(arg__1_);
    // tag=1010
    fromPtr(thisObj)->destroyed(arg__1);
}

// tag=1050
// disconnect(const QObject * receiver, const char * member) const
bool c_QObject__disconnect_QObject_char(void *thisObj, void *receiver_, const char *member)
{
    auto receiver = reinterpret_cast<QObject *>(receiver_);
    return
        // tag=1010
        fromPtr(thisObj)->disconnect(receiver, member);
}

// tag=1050
// disconnect(const QObject * sender, const char * signal, const QObject * receiver, const char * member)
bool c_static_QObject__disconnect_QObject_char_QObject_char(void *sender_, const char *signal, void *receiver_, const char *member)
{
    auto sender = reinterpret_cast<QObject *>(sender_);
    auto receiver = reinterpret_cast<QObject *>(receiver_);
    return
        // tag=1068
        KDDockWidgetsBindings_wrappersNS::QObject_wrapper::disconnect(sender, signal, receiver, member);
}

// tag=1050
// disconnect(const char * signal, const QObject * receiver, const char * member) const
bool c_QObject__disconnect_char_QObject_char(void *thisObj, const char *signal, void *receiver_, const char *member)
{
    auto receiver = reinterpret_cast<QObject *>(receiver_);
    return
        // tag=1010
        fromPtr(thisObj)->disconnect(signal, receiver, member);
}

// tag=1050
// dumpObjectInfo()
void c_QObject__dumpObjectInfo(void *thisObj)
{
    // tag=1010
    fromPtr(thisObj)->dumpObjectInfo();
}

// tag=1050
// dumpObjectTree()
void c_QObject__dumpObjectTree(void *thisObj)
{
    // tag=1010
    fromPtr(thisObj)->dumpObjectTree();
}

// tag=1050
// dynamicPropertyNames() const
void *c_QObject__dynamicPropertyNames(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QList<QByteArray>> { fromPtr(thisObj)->dynamicPropertyNames() };
}

// tag=1050
// event(QEvent * event)
bool c_QObject__event_QEvent(void *thisObj, void *event_)
{
    auto event = reinterpret_cast<QEvent *>(event_);
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::QObject_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->event_nocallback(event);} else {    return targetPtr->event(event);} }();
}

// tag=1050
// eventFilter(QObject * watched, QEvent * event)
bool c_QObject__eventFilter_QObject_QEvent(void *thisObj, void *watched_, void *event_)
{
    auto watched = reinterpret_cast<QObject *>(watched_);
    auto event = reinterpret_cast<QEvent *>(event_);
    return
        // tag=1016
        [&] {auto targetPtr = fromPtr(thisObj);auto wrapperPtr = dynamic_cast<KDDockWidgetsBindings_wrappersNS::QObject_wrapper*>(targetPtr);if (wrapperPtr) {    return wrapperPtr->eventFilter_nocallback(watched,event);} else {    return targetPtr->eventFilter(watched,event);} }();
}

// tag=1050
// inherits(const char * classname) const
bool c_QObject__inherits_char(void *thisObj, const char *classname)
{
    return
        // tag=1010
        fromPtr(thisObj)->inherits(classname);
}

// tag=1050
// installEventFilter(QObject * filterObj)
void c_QObject__installEventFilter_QObject(void *thisObj, void *filterObj_)
{
    auto filterObj = reinterpret_cast<QObject *>(filterObj_);
    // tag=1010
    fromPtr(thisObj)->installEventFilter(filterObj);
}

// tag=1050
// isWidgetType() const
bool c_QObject__isWidgetType(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->isWidgetType();
}

// tag=1050
// isWindowType() const
bool c_QObject__isWindowType(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->isWindowType();
}

// tag=1050
// killTimer(int id)
void c_QObject__killTimer_int(void *thisObj, int id)
{
    // tag=1010
    fromPtr(thisObj)->killTimer(id);
}

// tag=1050
// objectName() const
void *c_QObject__objectName(void *thisObj)
{
    return
        // tag=1010

        // tag=1072
        new Dartagnan::ValueWrapper<QString> { fromPtr(thisObj)->objectName() };
}

// tag=1050
// parent() const
void *c_QObject__parent(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->parent();
}

// tag=1050
// receivers(const char * signal) const
int c_QObject__receivers_char(void *thisObj, const char *signal)
{
    return
        // tag=1011

        // tag=1073
        fromWrapperPtr(thisObj)->receivers(signal);
}

// tag=1050
// removeEventFilter(QObject * obj)
void c_QObject__removeEventFilter_QObject(void *thisObj, void *obj_)
{
    auto obj = reinterpret_cast<QObject *>(obj_);
    // tag=1010
    fromPtr(thisObj)->removeEventFilter(obj);
}

// tag=1050
// sender() const
void *c_QObject__sender(void *thisObj)
{
    return
        // tag=1011

        // tag=1073
        fromWrapperPtr(thisObj)->sender();
}

// tag=1050
// senderSignalIndex() const
int c_QObject__senderSignalIndex(void *thisObj)
{
    return
        // tag=1011

        // tag=1073
        fromWrapperPtr(thisObj)->senderSignalIndex();
}

// tag=1050
// setObjectName(const QString & name)
void c_QObject__setObjectName_QString(void *thisObj, const char *name_)
{
    const auto name = QString::fromUtf8(name_);
    // tag=1010
    fromPtr(thisObj)->setObjectName(name);
}

// tag=1050
// setParent(QObject * parent)
void c_QObject__setParent_QObject(void *thisObj, void *parent_)
{
    auto parent = reinterpret_cast<QObject *>(parent_);
    // tag=1010
    fromPtr(thisObj)->setParent(parent);
}

// tag=1050
// signalsBlocked() const
bool c_QObject__signalsBlocked(void *thisObj)
{
    return
        // tag=1010
        fromPtr(thisObj)->signalsBlocked();
}

// tag=1050
// startTimer(int interval)
int c_QObject__startTimer_int(void *thisObj, int interval)
{
    return
        // tag=1010
        fromPtr(thisObj)->startTimer(interval);
}

// tag=1050
// tr(const char * s, const char * c, int n)
void *c_static_QObject__tr_char_char_int(const char *s, const char *c, int n)
{
    return
        // tag=1068

        // tag=1072
        new Dartagnan::ValueWrapper<QString> { KDDockWidgetsBindings_wrappersNS::QObject_wrapper::tr(s, c, n) };
}
void c_QObject__destructor(void *thisObj)
{

    // tag=1055
    delete fromPtr(thisObj);
}
void c_QObject__registerVirtualMethodCallback(void *ptr, void *callback, int methodId)
{
    // tag=1048
    auto wrapper = fromWrapperPtr(ptr);
    switch (methodId) {
    case 295:
        wrapper->m_customEventCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QObject_wrapper::Callback_customEvent>(callback);
        break;
    case 306:
        wrapper->m_eventCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QObject_wrapper::Callback_event>(callback);
        break;
    case 307:
        wrapper->m_eventFilterCallback = reinterpret_cast<KDDockWidgetsBindings_wrappersNS::QObject_wrapper::Callback_eventFilter>(callback);
        break;
    }
}
}


// tag=1040
#include "KDDockWidgets_exports.h"
#include <qobject.h>
#include <qstring.h>
#include <qlist.h>
#include <qbytearray.h>

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
namespace KDDockWidgets_wrappersNS {
// tag=1017
class QObject_wrapper : public ::QObject
{
public:
    ~QObject_wrapper();
    // tag=1041
    QObject_wrapper(QObject *parent = nullptr);
    // tag=1041
    bool blockSignals(bool b);
    // tag=1041
    const QList<QObject *> &children() const;
    // tag=1041
    void deleteLater();
    // tag=1041
    void destroyed(QObject *arg__1 = nullptr);
    // tag=1041
    bool disconnect(const QObject *receiver, const char *member = nullptr) const;
    // tag=1041
    static bool disconnect(const QObject *sender, const char *signal, const QObject *receiver, const char *member);
    // tag=1041
    bool disconnect(const char *signal = nullptr, const QObject *receiver = nullptr, const char *member = nullptr) const;
    // tag=1041
    void dumpObjectInfo();
    // tag=1041
    void dumpObjectTree();
    // tag=1041
    QList<QByteArray> dynamicPropertyNames() const;
    // tag=1041
    bool inherits(const char *classname) const;
    // tag=1041
    void installEventFilter(QObject *filterObj);
    // tag=1041
    bool isWidgetType() const;
    // tag=1041
    bool isWindowType() const;
    // tag=1041
    void killTimer(int id);
    // tag=1041
    QString objectName() const;
    // tag=1041
    QObject *parent() const;
    // tag=1041
    int receivers(const char *signal) const;
    // tag=1041
    void removeEventFilter(QObject *obj);
    // tag=1041
    QObject *sender() const;
    // tag=1041
    int senderSignalIndex() const;
    // tag=1041
    void setObjectName(const QString &name);
    // tag=1041
    void setParent(QObject *parent);
    // tag=1041
    bool signalsBlocked() const;
    // tag=1041
    int startTimer(int interval);
    // tag=1041
    static QString tr(const char *s, const char *c, int n);
};
}
extern "C" {

// tag=1067
//  QObject::QObject(QObject * parent)
KDDockWidgets_EXPORT void *c_QObject__constructor_QObject(void *parent_);

// tag=1067
//  QObject::blockSignals(bool b)
KDDockWidgets_EXPORT bool c_QObject__blockSignals_bool(void *thisObj, bool b);

// tag=1067
//  QObject::children() const
KDDockWidgets_EXPORT void *c_QObject__children(void *thisObj);

// tag=1067
//  QObject::deleteLater()
KDDockWidgets_EXPORT void c_QObject__deleteLater(void *thisObj);

// tag=1067
//  QObject::destroyed(QObject * arg__1)
KDDockWidgets_EXPORT void c_QObject__destroyed_QObject(void *thisObj, void *arg__1_);

// tag=1078
KDDockWidgets_EXPORT void c_QObject__onDestroyed_QObject(void *thisObj, void *contextQObject, void *callback);
// tag=1067
//  QObject::disconnect(const QObject * receiver, const char * member) const
KDDockWidgets_EXPORT bool c_QObject__disconnect_QObject_char(void *thisObj, void *receiver_, const char *member);

// tag=1067
//  QObject::disconnect(const QObject * sender, const char * signal, const QObject * receiver, const char * member)
KDDockWidgets_EXPORT bool c_static_QObject__disconnect_QObject_char_QObject_char(void *sender_, const char *signal, void *receiver_, const char *member);

// tag=1067
//  QObject::disconnect(const char * signal, const QObject * receiver, const char * member) const
KDDockWidgets_EXPORT bool c_QObject__disconnect_char_QObject_char(void *thisObj, const char *signal, void *receiver_, const char *member);

// tag=1067
//  QObject::dumpObjectInfo()
KDDockWidgets_EXPORT void c_QObject__dumpObjectInfo(void *thisObj);

// tag=1067
//  QObject::dumpObjectTree()
KDDockWidgets_EXPORT void c_QObject__dumpObjectTree(void *thisObj);

// tag=1067
//  QObject::dynamicPropertyNames() const
KDDockWidgets_EXPORT void *c_QObject__dynamicPropertyNames(void *thisObj);

// tag=1067
//  QObject::inherits(const char * classname) const
KDDockWidgets_EXPORT bool c_QObject__inherits_char(void *thisObj, const char *classname);

// tag=1067
//  QObject::installEventFilter(QObject * filterObj)
KDDockWidgets_EXPORT void c_QObject__installEventFilter_QObject(void *thisObj, void *filterObj_);

// tag=1067
//  QObject::isWidgetType() const
KDDockWidgets_EXPORT bool c_QObject__isWidgetType(void *thisObj);

// tag=1067
//  QObject::isWindowType() const
KDDockWidgets_EXPORT bool c_QObject__isWindowType(void *thisObj);

// tag=1067
//  QObject::killTimer(int id)
KDDockWidgets_EXPORT void c_QObject__killTimer_int(void *thisObj, int id);

// tag=1067
//  QObject::objectName() const
KDDockWidgets_EXPORT void *c_QObject__objectName(void *thisObj);

// tag=1067
//  QObject::parent() const
KDDockWidgets_EXPORT void *c_QObject__parent(void *thisObj);

// tag=1067
//  QObject::receivers(const char * signal) const
KDDockWidgets_EXPORT int c_QObject__receivers_char(void *thisObj, const char *signal);

// tag=1067
//  QObject::removeEventFilter(QObject * obj)
KDDockWidgets_EXPORT void c_QObject__removeEventFilter_QObject(void *thisObj, void *obj_);

// tag=1067
//  QObject::sender() const
KDDockWidgets_EXPORT void *c_QObject__sender(void *thisObj);

// tag=1067
//  QObject::senderSignalIndex() const
KDDockWidgets_EXPORT int c_QObject__senderSignalIndex(void *thisObj);

// tag=1067
//  QObject::setObjectName(const QString & name)
KDDockWidgets_EXPORT void c_QObject__setObjectName_QString(void *thisObj, const char *name_);

// tag=1067
//  QObject::setParent(QObject * parent)
KDDockWidgets_EXPORT void c_QObject__setParent_QObject(void *thisObj, void *parent_);

// tag=1067
//  QObject::signalsBlocked() const
KDDockWidgets_EXPORT bool c_QObject__signalsBlocked(void *thisObj);

// tag=1067
//  QObject::startTimer(int interval)
KDDockWidgets_EXPORT int c_QObject__startTimer_int(void *thisObj, int interval);

// tag=1067
//  QObject::tr(const char * s, const char * c, int n)
KDDockWidgets_EXPORT void *c_static_QObject__tr_char_char_int(const char *s, const char *c, int n);

// tag=1066
KDDockWidgets_EXPORT void c_QObject__destructor(void *thisObj);

// tag=1046
KDDockWidgets_EXPORT void c_QObject__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
// tag=1047
KDDockWidgets_EXPORT void c_QObject_Finalizer(void *, void *cppObj, void *);
}

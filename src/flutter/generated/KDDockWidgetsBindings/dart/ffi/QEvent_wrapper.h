/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// tag=1040
#include "KDDockWidgetsBindings_exports.h"
#include <qcoreevent.h>

namespace KDDockWidgetsBindings_wrappersNS {
// tag=1017
class QEvent_wrapper : public ::QEvent
{
public:
    ~QEvent_wrapper();
    // tag=1041
    QEvent_wrapper(QEvent::Type type);
    // tag=1041
    void accept();
    // tag=1041
    void ignore();
    // tag=1041
    bool isAccepted() const;
    // tag=1041
    static int registerEventType(int hint = -1);
    // tag=1041
    void setAccepted(bool accepted);
    // tag=1041
    bool spontaneous() const;
    // tag=1041
    QEvent::Type type() const;
};
}
extern "C" {

// tag=1067
//  QEvent::QEvent(QEvent::Type type)
KDDockWidgetsBindings_EXPORT void *c_QEvent__constructor_Type(int type);

// tag=1067
//  QEvent::accept()
KDDockWidgetsBindings_EXPORT void c_QEvent__accept(void *thisObj);

// tag=1067
//  QEvent::ignore()
KDDockWidgetsBindings_EXPORT void c_QEvent__ignore(void *thisObj);

// tag=1067
//  QEvent::isAccepted() const
KDDockWidgetsBindings_EXPORT bool c_QEvent__isAccepted(void *thisObj);

// tag=1067
//  QEvent::registerEventType(int hint)
KDDockWidgetsBindings_EXPORT int c_static_QEvent__registerEventType_int(int hint);

// tag=1067
//  QEvent::setAccepted(bool accepted)
KDDockWidgetsBindings_EXPORT void c_QEvent__setAccepted_bool(void *thisObj, bool accepted);

// tag=1067
//  QEvent::spontaneous() const
KDDockWidgetsBindings_EXPORT bool c_QEvent__spontaneous(void *thisObj);

// tag=1067
//  QEvent::type() const
KDDockWidgetsBindings_EXPORT int c_QEvent__type(void *thisObj);

// tag=1066
KDDockWidgetsBindings_EXPORT void c_QEvent__destructor(void *thisObj);

// tag=1046
KDDockWidgetsBindings_EXPORT void c_QEvent__registerVirtualMethodCallback(void *ptr, void *callback, int methodId);
// tag=1047
KDDockWidgetsBindings_EXPORT void c_QEvent_Finalizer(void *, void *cppObj, void *);
}

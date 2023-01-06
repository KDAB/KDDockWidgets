/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <qcoreevent.h>

namespace KDDockWidgetsBindings_wrappersNS {
class QEvent_wrapper : public ::QEvent
{
public:
    ~QEvent_wrapper();
    QEvent_wrapper(QEvent::Type type);
    void accept();
    void ignore();
    bool isAccepted() const;
    static int registerEventType(int hint = -1);
    void setAccepted(bool accepted);
    bool spontaneous() const;
    QEvent::Type type() const;
};
}
extern "C" {
// QEvent::QEvent(QEvent::Type type)
KDDockWidgetsBindings_EXPORT void *c_QEvent__constructor_Type(int type);
// QEvent::accept()
KDDockWidgetsBindings_EXPORT void c_QEvent__accept(void *thisObj);
// QEvent::ignore()
KDDockWidgetsBindings_EXPORT void c_QEvent__ignore(void *thisObj);
// QEvent::isAccepted() const
KDDockWidgetsBindings_EXPORT bool c_QEvent__isAccepted(void *thisObj);
// QEvent::registerEventType(int hint)
KDDockWidgetsBindings_EXPORT int c_static_QEvent__registerEventType_int(int hint);
// QEvent::setAccepted(bool accepted)
KDDockWidgetsBindings_EXPORT void c_QEvent__setAccepted_bool(void *thisObj, bool accepted);
// QEvent::spontaneous() const
KDDockWidgetsBindings_EXPORT bool c_QEvent__spontaneous(void *thisObj);
// QEvent::type() const
KDDockWidgetsBindings_EXPORT int c_QEvent__type(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_QEvent__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_QEvent__registerVirtualMethodCallback(void *ptr, void *callback,
                                                                          int methodId);
KDDockWidgetsBindings_EXPORT void c_QEvent_Finalizer(void *, void *cppObj, void *);
}

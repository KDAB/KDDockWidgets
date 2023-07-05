/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/// Implements a QObject replacement, for Flutter

#pragma once

#include "docks_export.h"

#include <vector>

#include <QString>

#include <kdbindings/signal.h>

#if defined(DOCKS_DEVELOPER_MODE) && defined(KDDW_FRONTEND_FLUTTER) && !defined(DARTAGNAN_BINDINGS_RUN)
#include "qcoro/core/qcorocore.h"
#endif

#if defined(Q_OBJECT) // TODOm4: Remove this ifdef and the undef
#undef Q_OBJECT
#define Q_OBJECT
#endif

namespace KDDockWidgets {

namespace Core {

class DOCKS_EXPORT_FOR_UNIT_TESTS Object
{
public:
    explicit Object(Object *parent = nullptr);
    virtual ~Object();

    void setParent(Object *parent);
    Object *parent() const;

    QString objectName() const;
    void setObjectName(const QString &);

    QString tr(const char *) const;

    KDBindings::Signal<> aboutToBeDeleted;

private:
    void removeChild(Object *child);
    void addChild(Object *child);

    Object *m_parent = nullptr;
    std::vector<Object *> m_children;
    QString m_name;
};

}

template<typename T>
inline T object_cast(Core::Object *o)
{
    return dynamic_cast<T>(o);
}

template<typename T>
inline T object_cast(const Core::Object *o)
{
    return dynamic_cast<T>(o);
}

};

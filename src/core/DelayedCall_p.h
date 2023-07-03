/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "KDDockWidgets.h"
#include "ObjectGuard_p.h"

namespace KDDockWidgets::Core {

class DelayedCall
{
public:
    DelayedCall() = default;
    virtual ~DelayedCall();
    virtual void call() = 0;

    KDDW_DELETE_COPY_CTOR(DelayedCall)
};

class DelayedDelete : public DelayedCall
{
public:
    explicit DelayedDelete(QObject *obj);
    ~DelayedDelete() override;

    void call() override;

    KDDW_DELETE_COPY_CTOR(DelayedDelete)
private:
    ObjectGuard<QObject> m_object;
};

}

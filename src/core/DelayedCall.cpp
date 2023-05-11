/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "DelayedCall.h"

#include <QObject>

using namespace KDDockWidgets::Core;

DelayedCall::~DelayedCall() = default;


DelayedDelete::DelayedDelete(QObject *obj)
    : m_object(obj)
{
}

DelayedDelete::~DelayedDelete() = default;


void DelayedDelete::call()
{
    // Can't use deleteLater() here due to QTBUG-83030 (deleteLater() never delivered if
    // triggered by a sendEvent() before event loop starts)
    delete m_object;
}

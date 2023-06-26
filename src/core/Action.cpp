/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/


#include "Action.h"

#if !defined(QT_WIDGETS_LIB)

#include "Logging_p.h"

QAction::~QAction() = default;

void QAction::setIcon(const KDDockWidgets::Icon &)
{
    KDDW_ERROR("Not implemented for QtQuick");
}

KDDockWidgets::Icon QAction::icon() const
{
    KDDW_ERROR("Not implemented for QtQuick/Flutter");
    return {};
}

#endif

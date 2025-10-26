/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Action.h"
#include "core/Action_p.h"
#include "core/Logging_p.h"
#include "core/DockWidget.h"

#include <QScopedValueRollback>

using namespace KDDockWidgets::QtQuick;

Action::Action(Core::DockWidget *dw, const char *debugName)
    : QObject(dw)
    , KDDockWidgets::Core::Action(dw, debugName)
{
}

Action::~Action() = default;

void Action::setIcon(const QIcon &)
{
    KDDW_ERROR("Not implemented for QtQuick");
}

QIcon Action::icon() const
{
    KDDW_ERROR("Not implemented for QtQuick");
    return {};
}

bool Action::blockSignals(bool b)
{
    return QObject::blockSignals(b);
}

void Action::setChecked(bool checked)
{
    if (m_checked == checked || m_isToggling)
        return;

    QScopedValueRollback<bool> toggling(m_isToggling, true);

    m_checked = checked;

    if (!signalsBlocked()) {
        KDDW_TRACE("Emitting Action::toggled({})", checked);

        // For core/, which does not support Qt signals
        d->toggled.emit(checked);

        // For QML:
        Q_EMIT toggled(checked);
    }
}

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

// Pimpl class so we can keep kdbindings private

#include "Group.h"
#include "ObjectGuard_p.h"

#include <kdbindings/signal.h>

#include <unordered_map>
#include <vector>

namespace KDDockWidgets {

namespace Core {

class Group ::Private
{
public:
    ObjectGuard<Core::Item> m_layoutItem;

    KDBindings::Signal<> numDockWidgetsChanged;
    KDBindings::Signal<> hasTabsVisibleChanged;
    KDBindings::Signal<> isInMainWindowChanged;
    KDBindings::Signal<> isFocusedChanged;
    KDBindings::Signal<> focusedWidgetChanged;
    KDBindings::Signal<> actualTitleBarChanged;
    KDBindings::Signal<> isMDIChanged;

    KDBindings::ScopedConnection m_visibleWidgetCountChangedConnection;

    std::unordered_map<Core::DockWidget *, KDBindings::ScopedConnection>
        titleChangedConnections;

    std::unordered_map<Core::DockWidget *, KDBindings::ScopedConnection>
        iconChangedConnections;
};

}

}

/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

// Pimpl class so we can keep kdbindings private

#include "TabBar.h"

#include <kdbindings/signal.h>

namespace KDDockWidgets {

namespace Core {

class TabBar::Private
{
public:
    KDBindings::Signal<KDDockWidgets::Core::DockWidget *> currentDockWidgetChanged;
    KDBindings::Signal<> countChanged;
    std::unordered_map<KDDockWidgets::Core::DockWidget *, KDBindings::ScopedConnection> aboutToDeleteConnections;
};

}

}

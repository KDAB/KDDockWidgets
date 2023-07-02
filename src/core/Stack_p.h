/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

// Pimpl class so we can keep kdbindings private

#include "Stack.h"
#include "TabBar.h"

#include <QPointer>

namespace KDDockWidgets {

namespace Core {

class TabBar;

class Stack::Private
{
public:
    explicit Private(Group *group, StackOptions options, Stack *qq)
        : q(qq)
        , m_tabBar(new TabBar(q))
        , m_group(group)
        , m_options(options)
    {
    }
    Stack *const q;
    QPointer<TabBar> m_tabBar;
    Group *const m_group;
    bool m_tabBarAutoHide = true;
    const StackOptions m_options;
};

}

}

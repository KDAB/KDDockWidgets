/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "../View.h"
#include "kdbindings/signal.h"

namespace KDDockWidgets {
class View::Private
{
public:
    /// @brief signal emitted once ~View starts
    KDBindings::Signal<> beingDestroyed;

    /// @brief signal emitted when something tried to close this view
    KDBindings::Signal<QCloseEvent *> closeRequested;

    /// @brief signal emitted when constraints change, for example min/max sizes
    KDBindings::Signal<> layoutInvalidated;

    /// @brief signal emitted when the view is resized
    KDBindings::Signal<QSize> resized;

    /// @brief signal emitted when the view's parent has changed
    KDBindings::Signal<> parentChanged;

    /// @brief signal emitted when the view's debug name has changed
    /// Used for debug only
    KDBindings::Signal<> debugNameChanged;
};
}

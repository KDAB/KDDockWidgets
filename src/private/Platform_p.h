/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "../Platform.h"
#include "kdbindings/signal.h"

namespace KDDockWidgets {
class Platform::Private
{
public:
    /// @brief This signal is emitted when the currently focused view changes
    KDBindings::Signal<std::shared_ptr<View>> focusedViewChanged;
};
}

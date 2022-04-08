/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "View.h"

namespace KDDockWidgets {

/// @brief Represents a top-level window
/// In Qt for example, this would be equivalent to QWindow.
/// In doesn't take ownership, just gives a generic API to an existing window.

class Window
{
public:
    virtual ~Window();
};

}

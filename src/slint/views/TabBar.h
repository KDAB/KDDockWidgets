/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "View.h"
#include "core/views/TabBarViewInterface.h"

namespace KDDockWidgets {
namespace slint {

class DOCKS_EXPORT TabBar : public slint::View, public Core::TabBarViewInterface
{
public:
};

}
}

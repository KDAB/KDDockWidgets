/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "View.h"
#include "kddockwidgets/docks_export.h"
#include "core/views/TitleBarViewInterface.h"

namespace KDDockWidgets {
namespace slint {

class DOCKS_EXPORT TitleBar : public slint::View, public Core::TitleBarViewInterface
{
public:
};

}
}

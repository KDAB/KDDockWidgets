/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "Platform.h"

namespace KDDockWidgets {

/// @brief implements functions specific to a particular platform
/// A platform can be for example qtwidgets, qtquick, etc.
class DOCKS_EXPORT Platform_qtquick : public Platform
{
public:
    Platform_qtquick();
    ~Platform_qtquick() override;
    const char *name() const override;
    std::shared_ptr<ViewWrapper> focusedView() const override;
    std::shared_ptr<ViewWrapper> qobjectAsView(QObject *) const override;

private:
    void init();
};

}

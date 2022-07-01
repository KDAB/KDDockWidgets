/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include <memory>

namespace KDDockWidgets {

class Window;
class View;

class EventFilterInterface
{
public:
    virtual ~EventFilterInterface();

    /// @brief Override to handle expose events for a certain window
    virtual bool onExposeEvent(std::shared_ptr<Window>)
    {
        return false;
    }
};

}

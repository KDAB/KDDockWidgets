/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "docks_export.h"
#include "ViewWrapper.h"

#include "kdbindings/signal.h"
#include <memory.h>

namespace KDDockWidgets {

/// @brief implements functions specific to a particular platform
/// A platform can be for example qtwidgets, qtquick, etc.
class DOCKS_EXPORT Platform
{
public:
    virtual ~Platform();
    /// @brief Returns the name of the platform, only "qtwidgets" and "qtquick"
    virtual const char *name() const = 0;

    /// @brief Returns the platform singleton
    static Platform *instance();

    /// @brief Returns whether a popup is open
    /// Usually not needed to override. Investigate further in case side bars aren't auto hidding
    virtual bool hasActivePopup() const;

    /// @brief Returns the focused view, if any
    virtual std::shared_ptr<ViewWrapper> focusedView() const = 0;

    /// @brief Returns the specified QObject casted to View
    /// Nullptr if it's not a view. TODOv2: This is shared between the
    /// QtQuick and QWidgets impl, but will be remove once we started removing Qt from backend
    virtual std::shared_ptr<ViewWrapper> qobjectAsView(QObject *) const = 0;

public:
    /// @brief This signal is emitted when the currently focused view changes
    KDBindings::Signal<std::shared_ptr<ViewWrapper>> focusedViewChanged;

protected:
    Platform();
};

}

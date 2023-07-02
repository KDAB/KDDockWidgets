/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "FloatingWindow.h"
#include "Config.h"

#include <kdbindings/signal.h>

#pragma once


namespace KDDockWidgets {

namespace Core {

static FloatingWindowFlags flagsForFloatingWindow(FloatingWindowFlags requestedFlags)
{
    if (!(requestedFlags & FloatingWindowFlag::FromGlobalConfig)) {
        // User requested specific flags for this floating window
        return requestedFlags;
    }

    // Use from KDDockWidgets::Config instead. This is app-wide and not per window.

    FloatingWindowFlags flags = {};

    if ((Config::self().flags() & Config::Flag_TitleBarHasMinimizeButton)
        == Config::Flag_TitleBarHasMinimizeButton)
        flags |= FloatingWindowFlag::TitleBarHasMinimizeButton;

    if (Config::self().flags() & Config::Flag_TitleBarHasMaximizeButton)
        flags |= FloatingWindowFlag::TitleBarHasMaximizeButton;

    if (Config::self().flags() & Config::Flag_KeepAboveIfNotUtilityWindow)
        flags |= FloatingWindowFlag::KeepAboveIfNotUtilityWindow;

    if (Config::self().flags() & Config::Flag_NativeTitleBar)
        flags |= FloatingWindowFlag::NativeTitleBar;

    if (Config::self().flags() & Config::Flag_HideTitleBarWhenTabsVisible)
        flags |= FloatingWindowFlag::HideTitleBarWhenTabsVisible;

    if (Config::self().flags() & Config::Flag_AlwaysTitleBarWhenFloating)
        flags |= FloatingWindowFlag::AlwaysTitleBarWhenFloating;

    if (Config::self().internalFlags() & Config::InternalFlag_DontUseParentForFloatingWindows)
        flags |= FloatingWindowFlag::DontUseParentForFloatingWindows;

    if (Config::self().internalFlags() & Config::InternalFlag_DontUseQtToolWindowsForFloatingWindows)
        flags |= FloatingWindowFlag::UseQtWindow;

    return flags;
}

class FloatingWindow::Private
{
public:
    explicit Private(FloatingWindowFlags requestedFlags)
        : m_flags(flagsForFloatingWindow(requestedFlags))
    {
    }

    KDBindings::Signal<> activatedChanged;
    KDBindings::Signal<> numFramesChanged;
    KDBindings::Signal<> numDockWidgetsChanged;
    KDBindings::Signal<> windowStateChanged;

    KDBindings::ScopedConnection m_visibleWidgetCountConnection;
    KDBindings::ScopedConnection m_currentStateChangedConnection;

    const FloatingWindowFlags m_flags;
};

}

}

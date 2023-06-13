/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_DOCK_LOGGING_P_H
#define KD_DOCK_LOGGING_P_H

#include <QLoggingCategory>

/// The general and more useful category to enable
Q_DECLARE_LOGGING_CATEGORY(general)

/// Very verbose logging of mouse events
Q_DECLARE_LOGGING_CATEGORY(mouseevents)

/// Verbose logging regarding OS related top level windows
Q_DECLARE_LOGGING_CATEGORY(toplevels)

/// Verbose logging in ctors and dtors
Q_DECLARE_LOGGING_CATEGORY(creation)

#endif

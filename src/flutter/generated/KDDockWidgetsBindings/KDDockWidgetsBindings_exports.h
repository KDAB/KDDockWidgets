/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#pragma once

#include <QtCore/QtGlobal>

#if defined(BUILDING_KDDockWidgetsBindings)
#define KDDockWidgetsBindings_EXPORT Q_DECL_EXPORT
#else
#define KDDockWidgetsBindings_EXPORT Q_DECL_IMPORT
#endif

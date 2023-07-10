/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#if defined(DOCKS_DEVELOPER_MODE) && defined(KDDW_FRONTEND_FLUTTER) && !defined(DARTAGNAN_BINDINGS_RUN) && !defined(KDDW_NO_FLUTTER_BINDINGS)
#define KDDW_FLUTTER_HAS_COROUTINES
#endif

#ifdef KDDW_FLUTTER_HAS_COROUTINES
#include "qcoro/core/qcorocore.h"
#define KDDW_QCORO_TASK QCoro::Task<bool>
#define KDDW_CO_AWAIT co_await
#define KDDW_CO_RETURN co_return
#ifdef QStringLiteral
#undef QStringLiteral
#endif
#else
#define KDDW_QCORO_TASK bool
#define KDDW_CO_AWAIT
#define KDDW_CO_RETURN return
#endif

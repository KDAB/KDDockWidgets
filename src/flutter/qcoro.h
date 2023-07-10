/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#if defined(DOCKS_DEVELOPER_MODE) && defined(KDDW_FRONTEND_FLUTTER) && !defined(DARTAGNAN_BINDINGS_RUN)
#include "qcoro/core/qcorocore.h"
#endif

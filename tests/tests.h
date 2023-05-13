/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "KDDockWidgets.h"

#ifdef KDDW_FRONTEND_FLUTTER

#include "flutter_tests_embedder/tests_embedder.h"
#include <qcoro5/qcoro/qcorocore.h>

#endif

#define KDDW_TEST_RETURN(res)                                             \
    if (!res)                                                             \
        qDebug() << "FAILED: at" << Q_FUNC_INFO << "; line=" << __LINE__; \
    KDDW_CO_RETURN res;

// TODOm4: Investigate something more fancy
#define CHECK Q_ASSERT
#define CHECK_EQ(a, b) Q_ASSERT(a == b)

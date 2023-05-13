/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "docks_export.h"
#include <qcoro5/qcoro/qcorocore.h>

namespace KDDockWidgets {
namespace flutter {

class DOCKS_EXPORT CoRoutines
{
public:
    /// Suspends a coroutine for a certain amount of time
    /// While running the C++ tests we sometimes want to go back to the
    /// dart event loop for some time and then resume the C++
    QCoro::Task<> wait(int ms);

    /// Checks if we can wake up from the wait
    void maybeResume();
};


}
}

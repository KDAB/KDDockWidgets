/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgets_wrapper.h"


#include <QDebug>


namespace Dartagnan {

typedef int (*CleanupCallback)(void *thisPtr);
static CleanupCallback s_cleanupCallback = nullptr;

template<typename T>
struct ValueWrapper
{
    T value;
};

}
extern "C" {

// tag=1050
// qt_getEnumName(QFlags<KDDockWidgets::MainWindowOption> arg__1)
const char *c_static_KDDockWidgets__qt_getEnumName_MainWindowOptions(int arg__1_)
{
    auto arg__1 = static_cast<QFlags<KDDockWidgets::MainWindowOption>>(arg__1_);
    return
        // tag=1068
        KDDockWidgets::qt_getEnumName(arg__1);
}
}

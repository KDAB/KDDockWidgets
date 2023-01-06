/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
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
// initFrontend(KDDockWidgets::FrontendType arg__1)
void c_static_KDDockWidgets__initFrontend_FrontendType(int arg__1)
{
    KDDockWidgets::initFrontend(static_cast<KDDockWidgets::FrontendType>(arg__1));
}
// locationStr(KDDockWidgets::Location loc)
void *c_static_KDDockWidgets__locationStr_Location(int loc)
{
    return new Dartagnan::ValueWrapper<QString> { KDDockWidgets::locationStr(
        static_cast<KDDockWidgets::Location>(loc)) };
}
}

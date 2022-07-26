/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "Qt_wrapper.h"


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
// qt_getEnumName(Qt::CursorShape arg__1)
const char *c_static_Qt__qt_getEnumName_CursorShape(int arg__1)
{
    return
        // tag=1068
        Qt::qt_getEnumName(static_cast<Qt::CursorShape>(arg__1));
}
}

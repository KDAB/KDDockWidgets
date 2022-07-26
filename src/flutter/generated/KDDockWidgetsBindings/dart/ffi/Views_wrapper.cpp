/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "Views_wrapper.h"


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
// asView_flutter(KDDockWidgets::Controller * controller)
void *c_static_KDDockWidgets__Views__asView_flutter_Controller(void *controller_)
{
    auto controller = reinterpret_cast<KDDockWidgets::Controller *>(controller_);
    return
        // tag=1068
        Views::asView_flutter(controller);
}

// tag=1050
// asView_flutter(KDDockWidgets::View * view)
void *c_static_KDDockWidgets__Views__asView_flutter_View(void *view_)
{
    auto view = reinterpret_cast<KDDockWidgets::View *>(view_);
    return
        // tag=1068
        Views::asView_flutter(view);
}
}

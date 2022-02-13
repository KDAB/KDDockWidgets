/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/


#include "FrameView.h"
#include "controllers/Frame.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

FrameView::FrameView(Controllers::Frame *controller, QObject *thisObj)
    : View(controller, View::Type::Frame, thisObj)
{
}

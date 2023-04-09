/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "RubberBand.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::qtwidgets;

RubberBand::RubberBand(QWidget *parent)
    : View_qtwidgets<QRubberBand>(nullptr, Core::ViewType::RubberBand, parent)
{
}

RubberBand::~RubberBand()
{
}

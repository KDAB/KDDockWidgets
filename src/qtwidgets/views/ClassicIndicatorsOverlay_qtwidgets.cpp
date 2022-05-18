/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "ClassicIndicatorsOverlay_qtwidgets.h"
#include "private/indicators/ClassicIndicators_p.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

ClassicIndicatorsOverlay_qtwidgets::ClassicIndicatorsOverlay_qtwidgets(ClassicIndicators *controller,
                                                                       QWidget *parent)
    : View_qtwidgets<QWidget>(controller, Type::None, parent)
    , m_controller(controller)
{
}

ClassicIndicatorsOverlay_qtwidgets::~ClassicIndicatorsOverlay_qtwidgets()
{
}

bool ClassicIndicatorsOverlay_qtwidgets::onResize(QSize newSize)
{
    m_controller->onResize(newSize);
    return false;
}

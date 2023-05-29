/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "ClassicIndicatorsWindow.h"
#include "kddockwidgets/core/indicators/ClassicDropIndicatorOverlay.h"
#include "kddockwidgets/core/Group.h"
#include "View.h"
#include "core/Utils_p.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;
using namespace KDDockWidgets::flutter;

IndicatorWindow::IndicatorWindow(ClassicDropIndicatorOverlay *controller, Core::View *parent)
    : flutter::View(controller, ViewType::DropAreaIndicatorOverlay, parent)
    , classicIndicators(controller)
{
}


QPoint IndicatorWindow::posForIndicator(DropLocation loc) const
{
    Q_UNUSED(loc);
    return {};
}

DropLocation IndicatorWindow::hover(QPoint globalPos)
{
    DropLocation loc = DropLocation_None;

    Q_UNUSED(globalPos);
    return loc;
}

void IndicatorWindow::updatePositions()
{
}

void IndicatorWindow::raise()
{
}

void IndicatorWindow::setGeometry(QRect)
{
}

void IndicatorWindow::setObjectName(const QString &)
{
}

void IndicatorWindow::setVisible(bool)
{
}

void IndicatorWindow::resize(QSize)
{
}

bool IndicatorWindow::isWindow() const
{
    return true;
}

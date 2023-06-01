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
    qWarning() << Q_FUNC_INFO << "Implement me" << loc;
    return {};
}

DropLocation IndicatorWindow::hover(QPoint globalPos)
{
    if (!isMounted())
        return DropLocation_None;

    const QPoint localPos = mapFromGlobal(globalPos);
    return hover_flutter(localPos);
}

void IndicatorWindow::updatePositions()
{
    auto sz = size();
    updatePositions_flutter(sz.width(), sz.height(), classicIndicators->hoveredGroup());
}

void IndicatorWindow::raise()
{
    // Nothing to do for flutter, it's raised
}

void IndicatorWindow::setGeometry(QRect)
{
    // TODOm3: Only needed once real multi-window
}

void IndicatorWindow::setObjectName(const QString &)
{
    // Not needed for flutter
}

void IndicatorWindow::setVisible(bool is)
{
    flutter::View::setVisible(is);
}

void IndicatorWindow::resize(QSize)
{
    // TODOm3: Only needed once real multi-window
}

bool IndicatorWindow::isWindow() const
{
    // TODOm3: Change to true once real multi-window
    return false;
}

DropLocation IndicatorWindow::hover_flutter(QPoint)
{
    qWarning() << Q_FUNC_INFO << "Implemented in dart instead";
    return {};
}

void IndicatorWindow::updatePositions_flutter(int, int, Core::Group *)
{
    qWarning() << Q_FUNC_INFO << "Implemented in dart instead";
}

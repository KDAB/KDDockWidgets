/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2021 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * @file
 * @brief A widget that supports an arbitrary number of splitters (called Separators) in any
 * combination of vertical/horizontal.
 *
 * This is a widget wrapper around the multisplitter layout (Layouting::Item)
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifndef KDDOCKWIDGETS_LAYOUTWIDGET_P_H
#define KDDOCKWIDGETS_LAYOUTWIDGET_P_H

#pragma once

#include "docks_export.h"
#include "kddockwidgets/KDDockWidgets.h"
#include "kddockwidgets/QWidgetAdapter.h"

namespace KDDockWidgets {

/**
 * @brief The widget (QWidget or QQuickItem) which holds a layout of dock widgets.
 *
 * Usually this would simply be MultiSplitter, but we've introduced this base class to support
 * different layouts, like MDI layouts, which are very different than traditional dock widget
 * layouts.
 *
 * This class makes the bridge between the GUI world (QWidget) and Layouting::Item world.
 * It's suitable to be set as a main window central widget for instance. The actual layouting is
 * then done by the root Item.
 */
class DOCKS_EXPORT LayoutWidget : public LayoutGuestWidget
{
    Q_OBJECT
public:
    explicit LayoutWidget(QWidgetOrQuick *parent = nullptr);
    ~LayoutWidget() override;
};

}

#endif

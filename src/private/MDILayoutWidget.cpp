/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "ItemFreeContainer_p.h"
#include "MDILayoutWidget_p.h"

using namespace KDDockWidgets;

MDILayoutWidget::MDILayoutWidget(QWidgetOrQuick *parent)
    : LayoutWidget(parent)
    , m_rootItem(new Layouting::ItemFreeContainer(this))
{
    setRootItem(m_rootItem);
}

MDILayoutWidget::~MDILayoutWidget()
{
}

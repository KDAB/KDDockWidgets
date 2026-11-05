/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "DropArea.h"
#include "core/View_p.h"
#include "kddockwidgets/core/DropArea.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::QtQuick;

DropArea::DropArea(Core::DropArea *dropArea, Core::View *parent)
    : QtQuick::View(dropArea, Core::ViewType::DropArea, asQQuickItem(parent))
    , m_dropArea(dropArea)
{
    Q_ASSERT(dropArea);

    // Wayland docks through QDrag, whose events Qt Quick only sends to items accepting drops
    QQuickItem::setFlag(ItemAcceptsDrops);
}

DropArea::~DropArea()
{
    if (!Core::View::d->freed())
        m_dropArea->viewAboutToBeDeleted();
}

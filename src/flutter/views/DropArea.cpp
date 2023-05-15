/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "DropArea.h"
#include "kddockwidgets/core/DropArea.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::flutter;

DropArea::DropArea(Core::DropArea *dropArea, Core::View *parent)
    : flutter::View(dropArea, Core::ViewType::DropArea, parent)
    , m_dropArea(dropArea)
{
    Q_ASSERT(dropArea);
}

DropArea::~DropArea()
{
    if (!freed())
        m_dropArea->viewAboutToBeDeleted();
}

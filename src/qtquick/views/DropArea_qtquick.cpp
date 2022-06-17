/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "DropArea_qtquick.h"
#include "private/Utils_p.h"
#include "kddockwidgets/controllers/DropArea.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

DropArea_qtquick::DropArea_qtquick(Controllers::DropArea *dropArea, View *parent)
    : Views::View_qtquick(dropArea, Type::DropArea, asQQuickItem(parent))
    , m_dropArea(dropArea)
{
    Q_ASSERT(dropArea);
    if (isWayland()) {
        qWarning() << "Dropping not implement for QtQuick on Wayland yet!";
    }
}

DropArea_qtquick::~DropArea_qtquick()
{
    if (!freed())
        m_dropArea->viewAboutToBeDeleted();
}

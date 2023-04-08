/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "DropArea_qtwidgets.h"
#include "private/Utils_p.h"
#include "kddockwidgets/core/DropArea.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::qtwidgets;

DropArea_qtwidgets::DropArea_qtwidgets(Core::DropArea *dropArea, View *parent)
    : qtwidgets::View_qtwidgets<QWidget>(dropArea, Type::DropArea, View_qt::asQWidget(parent))
    , m_dropArea(dropArea)
{
    Q_ASSERT(dropArea);
    if (isWayland()) {
        setAcceptDrops(true);
    }
}

DropArea_qtwidgets::~DropArea_qtwidgets()
{
    if (!freed())
        m_dropArea->viewAboutToBeDeleted();
}

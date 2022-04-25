/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "DropArea_qtwidgets.h"
#include "private/Utils_p.h"
#include "controllers/DropArea.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

DropArea_qtwidgets::DropArea_qtwidgets(Controllers::DropArea *dropArea, View *parent)
    : Views::View_qtwidgets<QWidget>(dropArea, Type::DropArea, parent ? qobject_cast<QWidget *>(parent->asQObject()) : nullptr)
    , m_dropArea(dropArea)
{
    Q_ASSERT(dropArea);
    if (isWayland()) {
#ifdef KDDOCKWIDGETS_QTWIDGETS
        setAcceptDrops(true);
#else
        qWarning() << "Dropping not implement for QtQuick on Wayland yet!";
#endif
    }
}

DropArea_qtwidgets::~DropArea_qtwidgets()
{
    if (!freed())
        m_dropArea->viewAboutToBeDeleted();
}

void DropArea_qtwidgets::onLayoutRequest()
{
    m_dropArea->updateSizeConstraints();
}

bool DropArea_qtwidgets::onResize(QSize newSize)
{
    return m_dropArea->onResize(newSize);
}

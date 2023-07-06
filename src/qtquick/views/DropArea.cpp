/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "DropArea.h"
#include "core/Utils_p.h"
#include "core/View_p.h"
#include "kddockwidgets/core/DropArea.h"
#include "qtcommon/DragControllerWayland_p.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::QtQuick;

DropArea::DropArea(Core::DropArea *dropArea, Core::View *parent)
    : QtQuick::View(dropArea, Core::ViewType::DropArea, asQQuickItem(parent))
    , m_dropArea(dropArea)
{
    Q_ASSERT(dropArea);

    auto item = createQQuickItem(QStringLiteral(":/kddockwidgets/qtquick/views/qml/DropArea.qml"), this);
    Q_ASSERT(item);

    qvariant_cast<QObject *>(item->property("anchors"))->setProperty("fill", QVariant::fromValue(asQQuickItem(this)));
    item->setProperty("dropAreaCpp", QVariant::fromValue(this));
}

DropArea::~DropArea()
{
    if (!Core::View::d->freed())
        m_dropArea->viewAboutToBeDeleted();
}

void DropArea::beginDrag(QPoint point, QObject *source)
{
    if (auto stateWayland = qobject_cast<Core::StateDraggingWayland *>(source)) {
        m_dropArea->hover(stateWayland->q->windowBeingDragged(), point);
    }
}

void DropArea::drop(QPoint point, QObject *source)
{
    if (auto stateWayland = qobject_cast<Core::StateDraggingWayland *>(source)) {
        m_dropArea->drop(stateWayland->q->windowBeingDragged(), point);
        stop();
    }
}

void DropArea::stop()
{
    m_dropArea->removeHover();
}

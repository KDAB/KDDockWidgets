/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Separator_qtquick.h"
#include "kddockwidgets/controllers/Separator.h"
#include "private/Logging_p.h"
#include "private/multisplitter/Item_p.h"
// #include "Rubberband_quick.h"

#include <QTimer>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

Separator_qtquick::Separator_qtquick(Controllers::Separator *controller, QQuickItem *parent)
    : View_qtquick(controller, Type::Separator, parent)
    , m_controller(controller)
{
}

void Separator_qtquick::init()
{
    createQQuickItem(QStringLiteral(":/kddockwidgets/qtquick/views/qml/Separator.qml"), this);

    // Only set on Separator::init(), so single-shot
    QTimer::singleShot(0, this, &Separator_qtquick::isVerticalChanged);
}

bool Separator_qtquick::isVertical() const
{
    return m_controller->isVertical();
}

void Separator_qtquick::onMousePressed()
{
    if (freed())
        return;

    m_controller->onMousePress();
}

void Separator_qtquick::onMouseMoved(QPointF localPos)
{
    if (freed())
        return;

    const QPointF pos = QQuickItem::mapToItem(parentItem(), localPos);
    m_controller->onMouseMove(pos.toPoint());
}

void Separator_qtquick::onMouseReleased()
{
    if (freed())
        return;

    m_controller->onMouseReleased();
}

void Separator_qtquick::onMouseDoubleClicked()
{
    if (freed())
        return;

    m_controller->onMouseDoubleClick();
}

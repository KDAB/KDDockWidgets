/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Separator_qtquick.h"
#include "controllers/Separator.h"
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
    createQQuickItem(QStringLiteral(":/kddockwidgets/multisplitter/private/multisplitter/qml/Separator.qml"), this);

    // Only set on Separator::init(), so single-shot
    QTimer::singleShot(0, this, &Separator_qtquick::isVerticalChanged);
}

bool Separator_qtquick::isVertical() const
{
    return m_controller->isVertical();
}

// TODOv2
// Layouting::Widget *Separator_qtquick::createRubberBand(Layouting::Widget *parent)
// {
//     if (!parent) {
//         qWarning() << Q_FUNC_INFO << "Parent is required";
//         return nullptr;
//     }

//     return new Layouting::Widget_quick(new Layouting::RubberBand(parent));
// }

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

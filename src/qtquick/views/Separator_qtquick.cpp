#include "Separator_qtquick.h"
/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "View_qtquick.h"

#include "Config.h"
#include "private/Logging_p.h"
#include "controllers/Separator.h"

#include <QMouseEvent>
#include <QPainter>
#include <QStyleOption>

using namespace KDDockWidgets::Views;

Separator_qtquick::Separator_qtquick(Controllers::Separator *controller, QWidget *parent)
    : View_qtquick(controller, Type::Separator, parent)
    , m_controller(controller)
{
    setMouseTracking(true);
}

void Separator_qtquick::paintEvent(QPaintEvent *ev)
{
    if (freed())
        return;

    if (KDDockWidgets::Config::self().disabledPaintEvents() & KDDockWidgets::Config::CustomizableWidget_Separator) {
        QWidget::paintEvent(ev);
        return;
    }

    QPainter p(this);

    QStyleOption opt;
    opt.palette = palette();
    opt.rect = QWidget::rect();
    opt.state = QStyle::State_None;
    if (!m_controller->isVertical())
        opt.state |= QStyle::State_Horizontal;

    if (isEnabled())
        opt.state |= QStyle::State_Enabled;

    QWidget::parentWidget()->style()->drawControl(QStyle::CE_Splitter, &opt, &p, this);
}

void Separator_qtquick::enterEvent(KDDockWidgets::Qt5Qt6Compat::QEnterEvent *)
{
    if (freed())
        return;

    qCDebug(separators) << Q_FUNC_INFO << this;
    if (m_controller->isVertical())
        setCursor(Qt::SizeVerCursor);
    else
        setCursor(Qt::SizeHorCursor);
}

void Separator_qtquick::leaveEvent(QEvent *)
{
    setCursor(Qt::ArrowCursor);
}

void Separator_qtquick::mousePressEvent(QMouseEvent *)
{
    if (freed())
        return;

    m_controller->onMousePress();
}

void Separator_qtquick::mouseMoveEvent(QMouseEvent *ev)
{
    if (freed())
        return;

    m_controller->onMouseMove(mapToParent(ev->pos()));
}

void Separator_qtquick::mouseReleaseEvent(QMouseEvent *)
{
    if (freed())
        return;

    m_controller->onMouseReleased();
}

void Separator_qtquick::mouseDoubleClickEvent(QMouseEvent *)
{
    if (freed())
        return;

    m_controller->onMouseDoubleClick();
}

/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "multisplitter/Widget_qwidget.h"
#include "SeparatorWidget_p.h"
#include "Logging_p.h"

#include <QPainter>
#include <QStyleOption>

using namespace KDDockWidgets;

SeparatorWidget::SeparatorWidget(QWidget *parent)
    : Separator(new Layouting::Widget_qwidget(parent))
{
    setMouseTracking(true);
}

void SeparatorWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    QStyleOption opt;
    opt.palette = palette();
    opt.rect = rect();
    opt.state = QStyle::State_None;
    if (!isVertical())
        opt.state |= QStyle::State_Horizontal;

    if (isEnabled())
        opt.state |= QStyle::State_Enabled;

    parentWidget()->style()->drawControl(QStyle::CE_Splitter, &opt, &p, this);
}

void SeparatorWidget::enterEvent(QEvent *)
{
    qCDebug(anchors) << Q_FUNC_INFO << this;
    if (isVertical())
        setCursor(Qt::SizeVerCursor);
    else
        setCursor(Qt::SizeHorCursor);
}

void SeparatorWidget::leaveEvent(QEvent *)
{
    setCursor(Qt::ArrowCursor);
}

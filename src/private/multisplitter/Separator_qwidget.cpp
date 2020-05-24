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

#include "Widget_qwidget.h"
#include "Separator_qwidget.h"
#include "Logging_p.h"

#include <QPainter>
#include <QStyleOption>
#include <QRubberBand>
#include <QMouseEvent>

using namespace Layouting;

namespace Layouting {
class RubberBand : public QRubberBand
                 , public Layouting::Widget_qwidget
{

public:
    RubberBand(Layouting::Widget *parent)
        : QRubberBand(QRubberBand::Line, parent ? parent->asQWidget() : nullptr)
        , Layouting::Widget_qwidget(this) {
    }
};

}

SeparatorWidget::SeparatorWidget(Layouting::Widget *parent)
    : Separator(parent)
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
    qCDebug(separators) << Q_FUNC_INFO << this;
    if (isVertical())
        setCursor(Qt::SizeVerCursor);
    else
        setCursor(Qt::SizeHorCursor);
}

void SeparatorWidget::leaveEvent(QEvent *)
{
    setCursor(Qt::ArrowCursor);
}

void SeparatorWidget::mousePressEvent(QMouseEvent *)
{
    onMousePress();
}

void SeparatorWidget::mouseMoveEvent(QMouseEvent *ev)
{
    onMouseMove(ev->pos());
}

void SeparatorWidget::mouseReleaseEvent(QMouseEvent *)
{
    onMouseReleased();
}

void SeparatorWidget::mouseDoubleClickEvent(QMouseEvent *)
{
    onMouseDoubleClick();
}

Layouting::Widget *SeparatorWidget::createRubberBand(Layouting::Widget *parent)
{
    if (!parent) {
        qWarning() << Q_FUNC_INFO << "Parent is required";
        return nullptr;
    }

    return new Layouting::Widget_qwidget(new RubberBand(parent));
}

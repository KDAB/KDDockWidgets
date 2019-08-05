/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "FloatingWindowWidget_p.h"
#include "Logging_p.h"

#include <QApplication>
#include <QCloseEvent>
#include <QPainter>

using namespace KDDockWidgets;

FloatingWindowWidget::FloatingWindowWidget(QWidget *parent)
    : FloatingWindow(parent)
{
}

FloatingWindowWidget::FloatingWindowWidget(Frame *frame, QWidget *parent)
    : FloatingWindow(frame, parent)
{
}

void FloatingWindowWidget::closeEvent(QCloseEvent *e)
{
    qCDebug(closing) << "Frame::closeEvent";
    e->accept(); // Accepted by default (will close unless ignored)

    Frame::List frames = this->frames();
    for (Frame *frame : frames) {
        qApp->sendEvent(frame, e);
        if (!e->isAccepted())
            break; // Stop when the first frame prevents closing
    }
}

void FloatingWindowWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setPen(0x666666);
    p.drawRect(rect().adjusted(0, 0, -1, -1));
}

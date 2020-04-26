/*  This file is part of KDDockWidgets.

  Copyright (C) 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY;



  without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file
 * @brief A class that is QWidget when building for QtWidgets, and QObject when building for QtQuick.
 *
 * Allows to have the same code base supporting both stacks.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#include "QWidgetAdapter_widgets_p.h"
#include "../FloatingWindow_p.h"

#include <QResizeEvent>
#include <QMouseEvent>

using namespace KDDockWidgets;

QWidgetAdapter::QWidgetAdapter(QWidget *parent, Qt::WindowFlags f)
    : QWidget(parent, f)
{
}

QWidgetAdapter::~QWidgetAdapter()
{
}

FloatingWindow *QWidgetAdapter::floatingWindow() const
{
    if (auto fw = qobject_cast<FloatingWindow*>(window()))
        return fw;

    return nullptr;
}

void QWidgetAdapter::raiseAndActivate()
{
    window()->raise();
    window()->activateWindow();
}

bool QWidgetAdapter::event(QEvent *e)
{
    if (e->type() == QEvent::LayoutRequest)
        onLayoutRequest();

    return QWidget::event(e);
}

void QWidgetAdapter::resizeEvent(QResizeEvent *ev)
{
    if (!onResize(ev->size()))
        QWidget::resizeEvent(ev);
}

void QWidgetAdapter::mousePressEvent(QMouseEvent *)
{
    onMousePress();
}

void QWidgetAdapter::mouseMoveEvent(QMouseEvent *ev)
{
    onMouseMove(ev->globalPos());
}

void QWidgetAdapter::mouseReleaseEvent(QMouseEvent *)
{
    onMouseRelease();
}

void QWidgetAdapter::closeEvent(QCloseEvent *e)
{
    onCloseEvent(e);
}

void QWidgetAdapter::setFlag(Qt::WindowType f, bool on)
{
    QWidget::setWindowFlag(f, on);
}

bool QWidgetAdapter::onResize(QSize) { return false; }
void QWidgetAdapter::onLayoutRequest() {}

void QWidgetAdapter::onMousePress() {}
void QWidgetAdapter::onMouseMove(QPoint) {}
void QWidgetAdapter::onMouseRelease() {}

void QWidgetAdapter::onCloseEvent(QCloseEvent *) {}

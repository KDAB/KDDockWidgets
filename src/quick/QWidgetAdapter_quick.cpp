/*  This file is part of KDDockWidgets.

  Copyright (C) 2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "QWidgetAdapter_quick_p.h"
#include "FloatingWindow_p.h"

#include <QResizeEvent>
#include <QMouseEvent>
#include <QWindow>

using namespace KDDockWidgets;

QWidgetAdapter::QWidgetAdapter(QObject *parent, Qt::WindowFlags)
    : QObject (parent)
{
}

QWidgetAdapter::~QWidgetAdapter()
{
}

void QWidgetAdapter::raiseAndActivate()
{
}

bool QWidgetAdapter::onResize(QSize, QSize) { return false; }
void QWidgetAdapter::onLayoutRequest() {}
void QWidgetAdapter::onMousePress() {}
void QWidgetAdapter::onMouseMove(QPoint) {}
void QWidgetAdapter::onMouseRelease() {}
void QWidgetAdapter::onCloseEvent(QCloseEvent *) {}


void QWidgetAdapter::raise() {}

FloatingWindow * QWidgetAdapter::floatingWindow() const
{
    return nullptr;
}

QRect QWidgetAdapter::geometry() const
{
    return {};
}

QRect QWidgetAdapter::rect() const
{
    return {};
}

void QWidgetAdapter::show()
{
}

void QWidgetAdapter::setGeometry(QRect) {}
void QWidgetAdapter::setVisible(bool) {}

void QWidgetAdapter::grabMouse() {}
void QWidgetAdapter::releaseMouse() {}
void QWidgetAdapter::setMinimumSize(QSize) {}
void QWidgetAdapter::resize(QSize) {}
QWindow *QWidgetAdapter::windowHandle() const { return nullptr; }

void QWidgetAdapter::setFlag(Qt::WindowType f, bool on)
{
    if (auto w = windowHandle()) {
        w->setFlag(f, on);
    } else {
        qWarning() << Q_FUNC_INFO << "Implement me";
    }
}


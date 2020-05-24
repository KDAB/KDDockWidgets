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

///@file
///@brief An abstraction/wrapper around QWidget, QtQuickItem or anything else

#pragma once

#include <qglobal.h>

QT_BEGIN_NAMESPACE
class QWidget; // TODO: Remove
class QSize;
class QObject;
QT_END_NAMESPACE

namespace Layouting {

class Item;

///@brief An abstraction/wrapper around QWidget, QtQuickItem or anything else
///
/// So the layout can host QWidget, etc without depending on it.
class Widget
{
public:
    Widget() = default;
    virtual void setLayoutItem(Item *) = 0;
    virtual QWidget *asWidget() const = 0; // TODO: Move down
    virtual QSize minSize() const = 0;
    virtual QSize maxSize() const = 0;
    virtual QSize size() const = 0;
    virtual void setParent(QObject *) = 0;

private:
    Q_DISABLE_COPY(Widget)
};

}

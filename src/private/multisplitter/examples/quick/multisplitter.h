/*
  This file is part of KDDockWidgets.

  Copyright (C) 2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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


#ifndef KDMULTISPLITTER_QUICK_H
#define KDMULTISPLITTER_QUICK_H

#include "Widget_quick.h"
#include "Item_p.h"

#include <QQuickItem>

namespace Layouting {

class MultiSplitter
        : public QQuickItem
        , public Layouting::Widget_quick
{
    Q_OBJECT
public:
    MultiSplitter();
    void addItem(const QString &filename, Layouting::Item::Location);

private:
    void onSizeChanged();
    Layouting::ItemContainer *const m_rootContainer;
};
}

#endif

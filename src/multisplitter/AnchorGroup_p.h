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

#ifndef KD_MULTISPLITTER_ANCHORGROUP_P_H
#define KD_MULTISPLITTER_ANCHORGROUP_P_H

#include "KDDockWidgets.h"
#include "Anchor_p.h"

#include <QDebug>

namespace KDDockWidgets {

class MultiSplitterLayout;
class Anchor;
class Item;

struct AnchorGroup {
    explicit AnchorGroup(MultiSplitterLayout *);

    void addItem(Item *item);
    void addItem(MultiSplitterLayout *);
    void removeItem(Item *item);
    void turnIntoPlaceholder();
    bool isValid() const { return top && left && bottom && right; }

    int width() const;
    int height() const;

    Anchor *oppositeAnchor(Anchor*) const;
    Anchor *createAnchorFrom(KDDockWidgets::Location fromAnchorLocation, Item *relativeTo);
    void setAnchor(Anchor *a, Qt::Orientation orientation, Anchor::Side side);

    Anchor *adjacentAnchor(Anchor*) const;
    Anchor *anchor(KDDockWidgets::Location) const;
    Anchor *anchor(Anchor::Side side, Qt::Orientation orientation) const;
    void setAnchor(Anchor *anchor, KDDockWidgets::Location);
    Anchor *anchorFollowing() const;
    Anchor::Side sideForAnchor(Anchor*) const;
    bool isStatic() const;
    void updateItemSizes();

    Anchor *top = nullptr;
    Anchor *left = nullptr;
    Anchor *bottom = nullptr;
    Anchor *right = nullptr;
    MultiSplitterLayout *layout;

    QDebug debug(QDebug d) const;
};
}

inline QDebug operator<< (QDebug d, KDDockWidgets::AnchorGroup *group)
{
    // out-of-line as it needs to include MultiSplitterLayout
    return group->debug(d);
}

#endif

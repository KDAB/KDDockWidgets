/*
  This file is part of KDDockWidgets.

  Copyright (C) 2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

/**
 * @file
 * @brief Class to hold the layout of the MultiSplitter, even for invisible items.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#include "LayoutMemory_p.h"
#include <QDebug>

using namespace KDDockWidgets;

void LayoutMemory::addWidget(const QWidget *widget,
                             KDDockWidgets::Location location,
                             QWidget *relativeTo)
{
    Q_ASSERT(widget);

    if (containsWidget(widget)) {
        // Doesn't happen!
        Q_ASSERT(false);
        qWarning() << "LayoutMemory::addWidget: already contained widget!" << widget;
        return;
    }

    const bool relativeToWindow = !relativeTo;

    if (!relativeToWindow && !containsWidget(relativeTo)) {
        // Doesn't happen!
        Q_ASSERT(false);
        qWarning() << "LayoutMemory::addWidget: Doesn't know about relativeTo" << widget << relativeTo;
        return;
    }

    auto item = std::make_shared<MemoryItem>(widget);

    if (relativeToWindow) {
        auto currentBorderItems = itemsAtBorder(location);
        for (auto &borderItem : currentBorderItems) {
            borderItem->itemsAtLocation(location).push_back(item);
            item->itemsAtLocation(oppositeLocation(location)).push_back(item);
        }
    } else {
        // For documentation purposes let's assume location=left. (It will work the same with bottom, right, top).

        auto relativeToItem = itemForWidget(relativeTo);
        // If adding to the left of X, then it will share the neighbour widgets on top and bottom of relativeToItem
        // adjacentLocation(left) returns top.
        // opposite(top) returns bottom
        Location adjLoc = adjacentLocation(location); // top
        item->itemsAtLocation(adjLoc) = relativeToItem->itemsAtLocation(adjLoc);
        adjLoc = oppositeLocation(adjLoc); // bottom
        item->itemsAtLocation(adjLoc) = relativeToItem->itemsAtLocation(adjLoc);

        // right
        const Location oppositeLoc = oppositeLocation(location);

        // The item at our right will be the relativeToItem
        item->itemsAtLocation(oppositeLoc) = { relativeToItem };

        // The items at our left will be the old items at the left of relativeToItem
        item->itemsAtLocation(location) = relativeToItem->itemsAtLocation(location);

        // And the relativeToItem will only have us at the left
        relativeToItem->itemsAtLocation(location) = { item };
    }

    QObject::connect(widget, &QObject::destroyed, widget, [this, widget] {
        removeWidget(widget);
    });

    m_items.push_back(item);
}

void LayoutMemory::removeWidget(const QWidget *widget)
{    
    auto item = itemForWidget(widget);
    if (!item) {
        Q_ASSERT(false);
        qWarning() << "LayoutMemory::removeWidget: Couldn't find widget" << widget;
        return;
    }

    m_items.removeOne(item);
    for (auto i : m_items)
        i->removeItem(item);

    for (auto loc : {Location_OnTop, Location_OnLeft, Location_OnRight, Location_OnBottom}) {

        // For example purposes, the code naming assumes loc=top, just so you can read and understand better.
        // for left, right, bottom it would be similar.

        auto &topNeighbours = item->itemsAtLocation(loc);
        const Location oppositeLoc = oppositeLocation(loc); // bottom
        bool found = false;
        for (auto neighbour : topNeighbours) {
            if (neighbour->itemsAtLocation(oppositeLoc).isEmpty()) {
                neighbour->itemsAtLocation(oppositeLoc) = item->itemsAtLocation(oppositeLoc);
            }
        }

        if (found) {
            const Location adjLoc = adjacentLocation(loc); // right
            const Location oppAdjLoc = oppositeLocation(adjLoc); // left

            auto rightMostItem = locMostItem(adjLoc, topNeighbours);
            auto leftMostItem =  locMostItem(oppAdjLoc, topNeighbours);

            auto rightNeighbours = item->itemsAtLocation(adjLoc);
            auto leftNeighbours = item->itemsAtLocation(oppAdjLoc);

            for (auto rightNeighbour : rightNeighbours) {
                if (!rightNeighbour->itemsAtLocation(oppAdjLoc).contains(rightMostItem)) {
                    rightNeighbour->itemsAtLocation(oppAdjLoc).push_back(rightMostItem);
                }
            }

            for (auto leftNeighbour : leftNeighbours) {
                if (!leftNeighbour->itemsAtLocation(oppAdjLoc).contains(leftMostItem)) {
                    leftNeighbour->itemsAtLocation(oppAdjLoc).push_back(leftMostItem);
                }
            }
        }
    }
}

LayoutMemory::MemoryItem::List LayoutMemory::itemsAtBorder(Location location) const
{
    LayoutMemory::MemoryItem::List result;

    for (auto &item : m_items) {
        if (item->isAtBorder(location))
            result.push_back(item);
    }

    return result;
}

LayoutMemory::MemoryItem::Ptr LayoutMemory::itemForWidget(const QWidget *widget) const
{
    for (auto &item : m_items) {
        if (item->m_widget == widget)
            return item;
    }

    Q_ASSERT(false);
    return {};
}

bool LayoutMemory::containsWidget(const QWidget *widget) const
{
    return itemForWidget(widget).get() != nullptr;
}

LayoutMemory::MemoryItem::Ptr LayoutMemory::locMostItem(Location location,
                                                        const LayoutMemory::MemoryItem::List &contiguousItems) const
{
    // For example purposes let's assume location=right, so we're finding the right-most item.
    for (auto &item : contiguousItems) {
        // Our neihbours to the right of us
        auto neighours = item->itemsAtLocation(location);

        bool itsTheOne = true;
        for (auto &neighbour : neighours) {
            if (contiguousItems.contains(neighbour)) {
                // One of the contiguousItems is our neighbour at the right, so we're not the right-most
                itsTheOne = false;
                break;
            }
        }

        if (itsTheOne)
            return item;
    }

    // Doesn't happen
    qWarning() << "LayoutMemory::locMostItem Couldn't find item";
    Q_ASSERT(false);
    return {};
}

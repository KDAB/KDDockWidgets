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

#ifndef KD_DOCKWIDGETS_LAYOUT_MEMORY_H
#define KD_DOCKWIDGETS_LAYOUT_MEMORY_H

#include "KDDockWidgets.h"

#include <QWidget>
#include <QVector>

#include <memory>

namespace KDDockWidgets
{

/**
 * @brief The LayoutMemory struct contains a simplified layout of a MultiSplitter.
 *
 * By layout, what is meant is the list of all widgets in the MultiSplitter and their relations
 * (neighbours to the left/right/top/bottom).
 *
 * MultiSplitter already stores its own layout, via the list of Anchor instances. LayoutMemory
 * effectively is a secondary layout, which duplicates the same information, but with two differences:
 * 1. LayoutMemory keeps the dock widgets in the layout even when they are closed, hidden or floating.
 *    This way MultiSplitter can query LayoutMemory to ask where to restore a widget to. This is the
 *    whole point of LayoutMemory, and also why it's called 'Memory'. It remembers.
 *
 * 2. LayoutMemory is very minimal and doesn't store any sizing or position information. It only
 *    has relations, so you can know which widgets are at the left of another widget, etc.
 *
 * This design keeps the MultiSplitter code sane. We could easily add some type of placeholders to
 * the MultiSplitter, so it could remember. But that would increase the code complexity an order of
 * magnitute. This way, each class does a single thing and does it right.
 */
struct LayoutMemory
{
    struct MemoryItem
    {
        typedef std::shared_ptr<MemoryItem> Ptr;
        typedef QVector<MemoryItem::Ptr> List;

        explicit MemoryItem(const QWidget *w)
            : m_widget(w) {}

        List& itemsAtLocation(KDDockWidgets::Location location)
        {
            switch (location) {
            case KDDockWidgets::Location_OnLeft:
                return m_leftItems;
            case KDDockWidgets::Location_OnTop:
                return m_topItems;
            case KDDockWidgets::Location_OnRight:
                return m_rightItems;
            case KDDockWidgets::Location_OnBottom:
                return m_bottomItems;
            default:
                Q_ASSERT(false);
                return m_leftItems;
            }
        }

        ///@brief Returns whether this item is at the @p border of the window
        bool isAtBorder(KDDockWidgets::Location border)
        {
            return itemsAtLocation(border).isEmpty();
        }

        void removeItem(const MemoryItem::Ptr &item)
        {
            m_topItems.removeOne(item);
            m_bottomItems.removeOne(item);
            m_leftItems.removeOne(item);
            m_rightItems.removeOne(item);
        }

        const QWidget *const m_widget;
        List m_topItems;
        List m_bottomItems;
        List m_leftItems;
        List m_rightItems;
    };

    LayoutMemory();
    void addWidget(const QWidget *widget, Location location, QWidget *relativeTo = nullptr);
    void removeWidget(const QWidget *widget);
    MemoryItem::List itemsAtBorder(KDDockWidgets::Location) const;
    MemoryItem::Ptr itemForWidget(const QWidget *widget) const;
    bool containsWidget(const QWidget *widget) const;

    ///@brief returns the right-most, top-most, etc. item from a list of @p contiguousItems
    MemoryItem::Ptr locMostItem(Location location, const MemoryItem::List &contiguousItems) const;

    MemoryItem::List m_items;
};

}

#endif

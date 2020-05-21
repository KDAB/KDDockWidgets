/*
  This file is part of KDDockWidgets.

  Copyright (C) 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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
 * @file Helper class so dockwidgets can be restored to their previous position.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifndef KDDOCKWIDGETS_POSITION_P_H
#define KDDOCKWIDGETS_POSITION_P_H

#include "docks_export.h"
#include "Logging_p.h"
#include "LayoutSaver_p.h"
#include "multisplitter/Item_p.h"
#include "QWidgetAdapter.h"

#include <QScopedValueRollback>
#include <QPointer>

#include <memory>

namespace Layouting {
class Item;
}

namespace KDDockWidgets {

class MultiSplitter;

// Just a RAII class so we don't forget to unref
struct ItemRef
{
    ItemRef(const QMetaObject::Connection &conn, Layouting::Item *it);
    ~ItemRef();

    Layouting::Item *const item;
    const QPointer<Layouting::Item> guard;
    const QMetaObject::Connection connection;
private:
    Q_DISABLE_COPY(ItemRef)
};


class DockWidgetBase;
class Frame;

/**
 * @internal
 * @brief Represents the DockWidget's last position.
 *
 * The DockWidget's position is saved when it's closed and restored when it's shown.
 * This class holds that position.
 */
class DOCKS_EXPORT_FOR_UNIT_TESTS Position
{
    Q_DISABLE_COPY(Position)
public:
    typedef std::shared_ptr<Position> Ptr;
    Position() = default;
    ~Position();

    void deserialize(const LayoutSaver::Position &);
    LayoutSaver::Position serialize() const;

    /**
     * @brief Returns whether the Position is valid. If invalid then the DockWidget was never
     * in a MainWindow.
     */
    bool isValid() const { return layoutItem() != nullptr; }

    /**
     * @brief returns if the dock widget was in a tab
     * @return if the position is tabbed, false otherwise
     */
    bool isTabbed() const
    {
        return m_tabIndex != -1;
    }

    ///@brief The tab index in case the dock widget was in a TabWidget, -1 otherwise.
    int m_tabIndex = -1;

    ///@brief true if the DockWidget was floating when it was closed
    bool m_wasFloating = false;

    ///@brief Adds the last layout item where the dock widget was (or is)
    void addPlaceholderItem(Layouting::Item *placeholder);


    QWidgetOrQuick *window() const;
    Layouting::Item* layoutItem() const;

    bool containsPlaceholder(Layouting::Item*) const;
    void removePlaceholders();

    const std::vector<std::unique_ptr<ItemRef>>& placeholders() const { return m_placeholders; }

    ///@brief Removes the placeholders that belong to this multisplitter
    void removePlaceholders(const MultiSplitter *);

    ///@brief Removes the placeholders that reference a FloatingWindow
    void removeNonMainWindowPlaceholders();

    ///@brief removes the Item @p placeholder
    void removePlaceholder(Layouting::Item *placeholder);

private:
    friend inline QDebug operator<<(QDebug, const KDDockWidgets::Position::Ptr &);

    // The last places where this dock widget was (or is), so it can be restored when setFloating(false) or show() is called.
    std::vector<std::unique_ptr<ItemRef>> m_placeholders;
    bool m_clearing = false; // to prevent re-entrancy
};

struct LastPositions
{
    // TODO: Support multiple old positions, one per main window

    bool isValid() const {
        return lastPosition->isValid();
    }

    void addPosition(Layouting::Item *item) {
        lastPosition->addPlaceholderItem(item);
    }

    void setLastFloatingGeometry(QRect geo) {
        m_lastFloatingGeometry = geo;
    }

    bool wasFloating() const {
        return lastPosition->m_wasFloating;
    }

    QRect lastFloatingGeometry() const {
        return m_lastFloatingGeometry;
    }

    LayoutSaver::Position serialize()
    {
        LayoutSaver::Position result = lastPosition->serialize();
        result.lastFloatingGeometry = lastFloatingGeometry();
        return result;
    }

    void deserialize(const LayoutSaver::Position &p)
    {
        m_lastFloatingGeometry = p.lastFloatingGeometry;
        lastPosition->deserialize(p);
    }

    Layouting::Item* lastItem() const {
        return lastPosition->layoutItem();
    }

    Layouting::Item::List layoutItems() const {
        Layouting::Item::List items;
        return items;
    }

    void saveTabIndex(int tabIndex, bool isFloating) {
        lastPosition->m_tabIndex = tabIndex;
        lastPosition->m_wasFloating = isFloating;
    }

    void removePlaceholders() const {
        lastPosition->removePlaceholders();
    }

    void removePlaceholders(MultiSplitter *hostWidget) const {
        lastPosition->removePlaceholders(hostWidget);
    }

    int lastTabIndex() const {
        return lastPosition->m_tabIndex;
    }

private:
    QRect m_lastFloatingGeometry;

    friend inline QDebug operator<<(QDebug d, const KDDockWidgets::LastPositions &);
    Position::Ptr lastPosition = std::make_shared<Position>();
};

inline QDebug operator<<(QDebug d, const KDDockWidgets::Position::Ptr &p)
{
    if (!p)
        return d;

    d << "; placeholdersSize=" << p->m_placeholders.size();
    return d;
}

inline QDebug operator<<(QDebug d, const KDDockWidgets::LastPositions &p)
{
    d << p.lastPosition << "; lastFloatingGeometry=" << p.m_lastFloatingGeometry;
    return d;
}

}

#endif

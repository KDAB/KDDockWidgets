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
 * @file Helper class so dockwidgets can be restored to their previous position.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifndef KD_LAST_POSITION_P_H
#define KD_LAST_POSITION_P_H

#include "docks_export.h"
#include "multisplitter/Item_p.h"
#include "Logging_p.h"

#include <QPointer>
#include <memory>

namespace KDDockWidgets {

// Just a RAII class so we don't forget to unref
struct ItemRef
{
    ItemRef(const QMetaObject::Connection &conn, Item *it)
        : item(it)
        , guard(it)
        , connection(conn)
    {
        item->ref();
    }

    ~ItemRef()
    {
        if (guard) {
            QObject::disconnect(connection);
            item->unref();
        }
    }

    Item *const item;
    const QPointer<Item> guard;
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
 * The DockWidget's position is saved when its closed and restored when it's shown.
 * This class holds that position.
 */
class DOCKS_EXPORT_FOR_UNIT_TESTS LastPosition
{
    Q_DISABLE_COPY(LastPosition)
public:
    LastPosition() = default;
    ~LastPosition();

    void fillFromDataStream(QDataStream &ds);

    /**
     * @brief Returns whether the LastPosition is valid. If invalid then the DockWidget was never
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
    void addPlaceholderItem(Item *placeholder);


    QWidgetOrQuick *window() const;
    Item* layoutItem() const;

    bool containsPlaceholder(Item*) const;
    void removePlaceholders() { m_clearing = true; m_placeholders.clear(); m_clearing = false;}

    const std::vector<std::unique_ptr<ItemRef>>& placeholders() const { return m_placeholders; }

    ///@brief Removes the placeholders that belong to @p layout
    void removePlaceholders(const MultiSplitterLayout *layout);

    ///@brief Removes the placeholders that reference a FloatingWindow
    void removeNonMainWindowPlaceholders();

    ///@brief removes the Item @p placeholder
    void removePlaceholder(Item *placeholder);

    void dumpDebug()
    {
        qDebug() << "; placeholdersSize=" << m_placeholders.size();
    }

    void setLastFloatingGeometry(QRect);
    QRect lastFloatingGeometry() const;

private:

    // The last places where this dock widget was (or is), so it can be restored when setFloating(false) or show() is called.
    std::vector<std::unique_ptr<ItemRef>> m_placeholders;
    bool m_clearing = false; // to prevent re-entrancy

    QRect m_lastFloatingGeo;
};

QDataStream &operator<<(QDataStream &ds, LastPosition *);

}

#endif

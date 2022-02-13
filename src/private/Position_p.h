/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * @file Helper class so dockwidgets can be restored to their previous position.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifndef KDDOCKWIDGETS_POSITION_P_H
#define KDDOCKWIDGETS_POSITION_P_H

#include "kddockwidgets/docks_export.h"

#include "Logging_p.h"
#include "kddockwidgets/LayoutSaver.h"

#include <QHash>
#include <QPointer>
#include <QScopedValueRollback>

#include <memory>

namespace Layouting {
class Item;
}

namespace KDDockWidgets {

namespace Controllers {
class DockWidgetBase;
class Frame;
}

class LayoutWidget;

// Just a RAII class so we don't forget to unref
struct ItemRef
{
    explicit ItemRef(const QMetaObject::Connection &, Layouting::Item *);
    ~ItemRef();

    bool isInMainWindow() const;

    Layouting::Item *const item;
    const QPointer<Layouting::Item> guard;
    const QMetaObject::Connection connection;

private:
    Q_DISABLE_COPY(ItemRef)
};


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
    bool isValid() const
    {
        return layoutItem() != nullptr;
    }

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

    Layouting::Item *layoutItem() const;

    bool containsPlaceholder(Layouting::Item *) const;
    void removePlaceholders();

    /// @brief Returns the last places where the dock widget was or is
    const std::vector<std::unique_ptr<ItemRef>> &placeholders() const
    {
        return m_placeholders;
    }

    ///@brief Removes the placeholders that belong to this multisplitter
    void removePlaceholders(const LayoutWidget *);

    ///@brief Removes the placeholders that reference a FloatingWindow
    void removeNonMainWindowPlaceholders();

    ///@brief removes the Item @p placeholder
    void removePlaceholder(Layouting::Item *placeholder);

    void saveTabIndex(int tabIndex, bool isFloating)
    {
        m_tabIndex = tabIndex;
        m_wasFloating = isFloating;
    }

    void setLastFloatingGeometry(QRect geo)
    {
        m_lastFloatingGeometry = geo;
    }

    bool wasFloating() const
    {
        return m_wasFloating;
    }

    QRect lastFloatingGeometry() const
    {
        return m_lastFloatingGeometry;
    }

    Layouting::Item *lastItem() const
    {
        return layoutItem();
    }

    int lastTabIndex() const
    {
        return m_tabIndex;
    }

    QRect lastOverlayedGeometry(SideBarLocation loc) const
    {
        return m_lastOverlayedGeometries.value(loc);
    }

    void setLastOverlayedGeometry(SideBarLocation loc, QRect rect)
    {
        m_lastOverlayedGeometries[loc] = rect;
    }

private:
    friend inline QDebug operator<<(QDebug, const KDDockWidgets::Position::Ptr &);

    // The last places where this dock widget was (or is), so it can be restored when setFloating(false) or show() is called.
    std::vector<std::unique_ptr<ItemRef>> m_placeholders;
    QRect m_lastFloatingGeometry;
    QHash<SideBarLocation, QRect> m_lastOverlayedGeometries;
    bool m_clearing = false; // to prevent re-entrancy
};

inline QDebug operator<<(QDebug d, const KDDockWidgets::Position::Ptr &p)
{
    if (!p)
        return d;

    d << "; placeholdersSize=" << p->m_placeholders.size();
    return d;
}

}

#endif
